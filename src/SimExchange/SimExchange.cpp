#include "SimExchange.h"
#include "Error.h"
#include "QuantUtility.h"
#include "InitMdbFromCsv.h"
#include "MdbFieldConverter.h"
#include "OrderUtility.h"
#include <Spark/Core/Logger/Logger.h>
#include <Spark/Core/Utility/Utility.h>
#include <Spark/Core/Utility/TimeUtility.h>


using namespace std;
using namespace QuantTrading;
using namespace Spark;
using namespace Spark::Core;
using namespace QuantTrading::OrderMatch;


namespace QuantTrading::SimExchange
{
SimExchange::SimExchange(QuantTrading::Mdb* mdb, TradeFront* tradeFront, MdFront* mdFront, MdSpiImpl* mdSpi, MatchModeType matchMode)
	:ThreadBase("SimExchange"), mdb_(mdb), tradeFront_(tradeFront), mdFront_(mdFront), mdSpi_(mdSpi), tradingDay_(""), currDate_(""), currTime_(""), isMdLogged_(false)
{
	auto tradingDay = mdb_->TradingDay->PrimaryKey->Select(1);
	if (tradingDay != nullptr)
	{
		strcpy(tradingDay_, tradingDay->CurrTradingDay);
	}

	orderMatch_ = QuantTrading::OrderMatch::OrderMatch::CreateOrderMatch(matchMode, tradingDay_);
	orderMatch_->Subscribe(this);
	positionMaintenance_ = new QuantTrading::Settlement::PositionMaintenance(mdb_);

	rspAccountLoginPackage_ = Allocate<RspAccountLoginPackage>();
	rspAccountLoginPackage_->RspInfo = Allocate<RspInfoField>();
	rspAccountLoginPackage_->RspAccountLogin = Allocate<RspAccountLoginField>();
	rspAccountLogoutPackage_ = Allocate<RspAccountLogoutPackage>();
	rspAccountLogoutPackage_->RspInfo = Allocate<RspInfoField>();
	rspAccountLogoutPackage_->RspAccountLogout = Allocate<RspAccountLogoutField>();

	rspInsertOrderPackage_ = Allocate<RspInsertOrderPackage>();
	rspInsertOrderPackage_->RspInfo = Allocate<RspInfoField>();
	rspInsertOrderPackage_->ReqInsertOrder = Allocate<ReqInsertOrderField>();
	rspCancelOrderPackage_ = Allocate<RspCancelOrderPackage>();
	rspCancelOrderPackage_->RspInfo = Allocate<RspInfoField>();
	rspCancelOrderPackage_->ReqCancelOrder = Allocate<ReqCancelOrderField>();

	rspQryOrderPackage_ = Allocate<RspQryOrderPackage>();
	rspQryOrderPackage_->RspInfo = Allocate<RspInfoField>();
	rspQryTradePackage_ = Allocate<RspQryTradePackage>();
	rspQryTradePackage_->RspInfo = Allocate<RspInfoField>();
	rspQryInstrumentPackage_ = Allocate<RspQryInstrumentPackage>();
	rspQryInstrumentPackage_->RspInfo = Allocate<RspInfoField>();

	rtnOrderPackage_ = Allocate<RtnOrderPackage>();
	rtnOrderPackage_->Order = Allocate<OrderField>();
	rtnTradePackage_ = Allocate<RtnTradePackage>();
	rtnTradePackage_->Trade = Allocate<TradeField>();
}
SimExchange::~SimExchange()
{

}
void SimExchange::Init()
{
	SeedNextOrderIDFromOrders(mdb_->Order);
	auto positionItPair = mdb_->Position->PrimaryKey->SelectAll();
	for (auto& it = positionItPair.first; it != positionItPair.second; ++it)
	{
		auto position = *it;
		ReqSubMarketData(position->ExchangeId, position->InstrumentId);
	}
}

void SimExchange::OnProtocolConnect(SessionIdType sessionId, const char* ip, int port)
{
	WriteLog(LogLevel::Info, "TradeFront::OnProtocolConnect SessionId:%lld, ip:%s, port:%d", sessionId, ip, port);
}
void SimExchange::OnProtocolDisConnect(SessionIdType sessionId, const char* ip, int port)
{
	WriteLog(LogLevel::Info, "TradeFront::OnProtocolDisConnect SessionId:%lld, ip:%s, port:%d", sessionId, ip, port);
	NotifyDisConnectPackage* package = NotifyDisConnectPackage::Allocate();
	package->Prepare(sessionId, false, 0);
	package->NotifyDisConnect = Allocate<NotifyDisConnectField>();
	package->NotifyDisConnect->SessionId = sessionId;
	strcpy(package->NotifyDisConnect->IpAddress, ip);
	package->NotifyDisConnect->Port = port;
	OnMessage(package);
}
void SimExchange::OnMdDisConnected()
{
	WriteLog(LogLevel::Info, "OnMdDisConnected: Reset Md Login State.");
	isMdLogged_ = false;
}
void SimExchange::OnMessage(Package* package)
{
	{
		lock_guard<mutex> guard(mutex_);
		packages_.push_back(package);
	}
	conditionVariable_.notify_one();
}

void SimExchange::OnOrder(QuantTrading::Order* order)
{
	SendRtnOrder(order);
}
void SimExchange::OnOrderUpdate(QuantTrading::Order* order, QuantTrading::Order* newOrder)
{
    mdb_->Order->Update(order, newOrder);
    SendRtnOrder(order);
}
void SimExchange::OnTrade(QuantTrading::Trade* trade)
{
    mdb_->Trade->Insert(trade);
	SendRtnTrade(trade);
	positionMaintenance_->UpdateOnTrade(trade);
}

void SimExchange::Run()
{
	CheckPackages();
	HandlePackages();
}
void SimExchange::CheckPackages()
{
	std::unique_lock<std::mutex> guard(mutex_);
	conditionVariable_.wait_for(guard, timeOut_, [this]() {
		return !packages_.empty();
		});
}
void SimExchange::HandlePackages()
{
	Package* package = nullptr;
	for (auto i = 0; i < 100; ++i)
	{
		package = GetNextPackage();
		if (package == nullptr)
			break;
		if (DispatchPackage(package))
		{
			package->Deallocate();
		}
	}
}

void SimExchange::HandleRspMdUserLogin(RspMdUserLoginPackage* package)
{
	isMdLogged_ = true;
	for (auto& reqSubMd : subscribeInstruments_)
	{
		mdSpi_->ReqSubMarketData(&reqSubMd);
	}
}
void SimExchange::HandleRspMdUserLogout(RspMdUserLogoutPackage* package)
{
	isMdLogged_ = false;
}
void SimExchange::HandleRtnDepthMarketData(RtnDepthMarketDataPackage* rtnPackage)
{
	WriteLog(LogLevel::Info, "HandleRtnDepthMarketData %s", rtnPackage->GetDebugString());
	auto mdTick = QuantTrading::DepthMarketData::Allocate();
    FieldToMdb(rtnPackage->DepthMarketData, mdTick);
	orderMatch_->OnTick(mdTick);
	auto oldMdTick = mdb_->DepthMarketData->PrimaryKey->Select(mdTick->TradingDay, mdTick->ExchangeId, mdTick->InstrumentId);
	if (oldMdTick == nullptr)
	{
		mdb_->DepthMarketData->Insert(mdTick);
	}
	else
	{
		mdb_->DepthMarketData->Update(oldMdTick, mdTick);
	}
}
void SimExchange::HandleRtnBarMarketData(RtnBarMarketDataPackage* rtnPackage)
{
	WriteLog(LogLevel::Info, "HandleRtnBarMarketData %s", rtnPackage->GetDebugString());
	auto mdBar = QuantTrading::BarMarketData::Allocate();
    FieldToMdb(rtnPackage->BarMarketData, mdBar);
	orderMatch_->OnBar(mdBar);
	mdb_->BarMarketData->Insert(mdBar);
}

void SimExchange::HandleNotifyDisConnect(NotifyDisConnectPackage* notifyPackage)
{
	WriteLog(LogLevel::Info, "HandleNotifyDisConnect %s", notifyPackage->GetDebugString());
	mdb_->PrimaryAccountLoginSession->EraseBySessionIdIndex(notifyPackage->NotifyDisConnect->SessionId);
}
void SimExchange::HandleReqAccountLogin(ReqAccountLoginPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleReqAccountLogin %s", reqPackage->GetDebugString());
	auto errorId = ErrorNone;
	auto primaryAccount = mdb_->PrimaryAccount->PrimaryKey->Select(reqPackage->ReqAccountLogin->AccountId);
	if (primaryAccount == nullptr)
	{
		errorId = ErrorPrimaryAccountNotExist;
	}
	else if (strcmp(primaryAccount->Password, reqPackage->ReqAccountLogin->Password) != 0)
	{
		errorId = ErrorIncorrectPassword;
	}
	else
	{
		auto primaryAccountLoginSession = mdb_->PrimaryAccountLoginSession->PrimaryKey->Select(reqPackage->ReqAccountLogin->AccountId, reqPackage->SessionId);
		if (primaryAccountLoginSession != nullptr)
		{
			errorId = ErrorAccountAlreadyLogin;
		}
		else
		{
			primaryAccountLoginSession = QuantTrading::PrimaryAccountLoginSession::Allocate();
			memset(primaryAccountLoginSession, 0, sizeof(QuantTrading::PrimaryAccountLoginSession));
			strcpy(primaryAccountLoginSession->PrimaryAccountId, reqPackage->ReqAccountLogin->AccountId);
			primaryAccountLoginSession->SessionId = reqPackage->SessionId;
			strcpy(primaryAccountLoginSession->IpAddress, reqPackage->IpAddress);
			mdb_->PrimaryAccountLoginSession->Insert(primaryAccountLoginSession);
		}
	}
	SendRspAccountLogin(reqPackage, primaryAccount, errorId);
}
void SimExchange::HandleReqAccountLogout(ReqAccountLogoutPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleBrokerLogout %s", reqPackage->GetDebugString());
	
	rspAccountLogoutPackage_->Prepare(reqPackage->SessionId, false, reqPackage->Head.MsgSeqNum);

	strcpy(rspAccountLogoutPackage_->RspAccountLogout->AccountId, reqPackage->ReqAccountLogout->AccountId);
	auto primaryAccountLoginSession = mdb_->PrimaryAccountLoginSession->PrimaryKey->Select(reqPackage->ReqAccountLogout->AccountId, reqPackage->SessionId);
	if (primaryAccountLoginSession != nullptr)
	{
		mdb_->PrimaryAccountLoginSession->Erase(primaryAccountLoginSession);

		rspAccountLogoutPackage_->RspInfo->ErrorId = ErrorNone;
		strcpy(rspAccountLogoutPackage_->RspInfo->ErrorMsg, GetErrorMessage(ErrorNone));
	}
	else
	{
		rspAccountLogoutPackage_->RspInfo->ErrorId = ErrorAccountNotLogin;
		strcpy(rspAccountLogoutPackage_->RspInfo->ErrorMsg, GetErrorMessage(ErrorAccountNotLogin));
	}

	tradeFront_->Send(rspAccountLogoutPackage_);
}

void SimExchange::HandleReqInsertOrder(ReqInsertOrderPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleReqInsertOrder %s", reqPackage->GetDebugString());
	auto errorId = CheckSessionLogin(reqPackage->ReqInsertOrder->AccountId, reqPackage->SessionId);
	if (errorId != ErrorNone)
	{
		SendRspInsertOrder(reqPackage, errorId);
		return;
	}
	auto instrument = mdb_->Instrument->PrimaryKey->Select(reqPackage->ReqInsertOrder->ExchangeId, reqPackage->ReqInsertOrder->InstrumentId);
	if (instrument == nullptr)
	{
		SendRspInsertOrder(reqPackage, ErrorInstrumentNotExist);
		return;
	}
	auto account = mdb_->Account->PrimaryKey->Select(reqPackage->ReqInsertOrder->AccountId);
	if (account == nullptr)
	{
		SendRspInsertOrder(reqPackage, ErrorAccountNotExist);
		return;
	}
	errorId = CheckForInsertOrder(reqPackage->ReqInsertOrder, instrument);
	ReqSubMarketData(instrument->ExchangeId, instrument->InstrumentId);
	SendRspInsertOrder(reqPackage, errorId);
	if (errorId != ErrorNone)
	{
		return;
	}
	TimeUtility::GetLocalDateTime(currDate_, currTime_);
	auto order = CreateOrder(reqPackage, account, instrument, tradingDay_, currDate_, currTime_);
	mdb_->Order->Insert(order);
	orderMatch_->InsertOrder(order);
}
void SimExchange::HandleReqCancelOrder(ReqCancelOrderPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleReqCancelOrder %s", reqPackage->GetDebugString());
	auto errorId = CheckSessionLogin(reqPackage->ReqCancelOrder->AccountId, reqPackage->SessionId);
	if (errorId != ErrorNone)
	{
		SendRspCancelOrder(reqPackage, errorId);
		return;
	}
	auto order = mdb_->Order->PrimaryKey->Select(tradingDay_, reqPackage->ReqCancelOrder->AccountId, reqPackage->ReqCancelOrder->ExchangeId,
		reqPackage->ReqCancelOrder->InstrumentId, reqPackage->ReqCancelOrder->OrderId);
	if (order == nullptr)
	{
		order = mdb_->Order->ClientOrderIdUniqueKey->Select(tradingDay_, reqPackage->ReqCancelOrder->AccountId, reqPackage->ReqCancelOrder->ExchangeId,
			reqPackage->ReqCancelOrder->InstrumentId, reqPackage->ReqCancelOrder->SessionId, reqPackage->ReqCancelOrder->ClientOrderId);
		if (order == nullptr)
		{
			errorId = ErrorOrderNotExist;
		}
	}
	if (order != nullptr)
	{
		errorId = CheckForCancelOrder(order);
	}
	SendRspCancelOrder(reqPackage, errorId);
	if (errorId != ErrorNone)
	{
		return;
	}
	orderMatch_->CancelOrder(order);
}
void SimExchange::HandleReqQryOrder(ReqQryOrderPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleReqQryOrder %s", reqPackage->GetDebugString());
	auto errorId = CheckSessionLogin(reqPackage->ReqQryOrder->AccountId, reqPackage->SessionId);
	if (errorId != ErrorNone)
	{
		SendRspQryOrder(reqPackage, errorId, true);
		return;
	}
	auto orderRange = mdb_->Order->AccountIdIndex->EqualRange(tradingDay_, reqPackage->ReqQryOrder->AccountId);
	if (orderRange.first == orderRange.second)
	{
		SendRspQryOrder(reqPackage, ErrorNone, true);
	}
	else
	{
		rspQryOrderPackage_->Order = Allocate<OrderField>();
		for (auto& it = orderRange.first; it != orderRange.second; )
		{
			auto record = *it;
			SendRspQryOrder(reqPackage, ErrorNone, ++it == orderRange.second, record);
		}
		::Deallocate(rspQryOrderPackage_->Order);
		rspQryOrderPackage_->Order = nullptr;
	}
}
void SimExchange::HandleReqQryTrade(ReqQryTradePackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleReqQryTrade %s", reqPackage->GetDebugString());
	auto errorId = CheckSessionLogin(reqPackage->ReqQryTrade->AccountId, reqPackage->SessionId);
	if (errorId != ErrorNone)
	{
		SendRspQryTrade(reqPackage, errorId, true);
		return;
	}
	auto tradeRange = mdb_->Trade->AccountIdIndex->EqualRange(tradingDay_, reqPackage->ReqQryTrade->AccountId);
	if (tradeRange.first == tradeRange.second)
	{
		SendRspQryTrade(reqPackage, ErrorNone, true);
	}
	else
	{
		rspQryTradePackage_->Trade = Allocate<TradeField>();
		for (auto& it = tradeRange.first; it != tradeRange.second; )
		{
			auto record = *it;
			SendRspQryTrade(reqPackage, ErrorNone, ++it == tradeRange.second, record);
		}
		::Deallocate(rspQryTradePackage_->Trade);
		rspQryTradePackage_->Trade = nullptr;
	}
}
void SimExchange::HandleReqQryInstrument(ReqQryInstrumentPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleReqQryInstrument %s", reqPackage->GetDebugString());
	auto errorId = CheckSessionLogin(reqPackage->SessionId);
	if (errorId != ErrorNone)
	{
		SendRspQryInstrument(reqPackage, errorId, true);
		return;
	}
	rspQryInstrumentPackage_->Instrument = Allocate<InstrumentField>();
	if (strlen(reqPackage->ReqQryInstrument->ExchangeId) != 0 && strlen(reqPackage->ReqQryInstrument->InstrumentId) != 0)
	{
		auto instrument = mdb_->Instrument->PrimaryKey->Select(reqPackage->ReqQryInstrument->ExchangeId, reqPackage->ReqQryInstrument->InstrumentId);
		SendRspQryInstrument(reqPackage, ErrorNone, true, instrument);
	}
	else if (strlen(reqPackage->ReqQryInstrument->ExchangeId) != 0)
	{
		auto range = mdb_->Instrument->ExchangeIdIndex->EqualRange(reqPackage->ReqQryInstrument->ExchangeId);
		for (auto& it = range.first; it != range.second; )
		{
			auto record = *it;
			SendRspQryInstrument(reqPackage, ErrorNone, ++it == range.second, record);
		}
	}
	else
	{
		auto range = mdb_->Instrument->PrimaryKey->SelectAll();
		for (auto& it = range.first; it != range.second; )
		{
			auto record = *it;
			SendRspQryInstrument(reqPackage, ErrorNone, ++it == range.second, record);
		}
	}
	::Deallocate(rspQryInstrumentPackage_->Instrument);
	rspQryInstrumentPackage_->Instrument = nullptr;
}

int SimExchange::CheckSessionLogin(const SessionIdType& sessionId)
{
	auto sessionIDRange = mdb_->PrimaryAccountLoginSession->SessionIdIndex->EqualRange(sessionId);
	return sessionIDRange.first != sessionIDRange.second ? ErrorNone : ErrorSessionNotLogin;
}

int SimExchange::CheckSessionLogin(const AccountIdType& primaryAccountID, const SessionIdType& sessionId)
{
	auto primaryAccountLoginSession = mdb_->PrimaryAccountLoginSession->PrimaryKey->Select(primaryAccountID, sessionId);
	if (primaryAccountLoginSession != nullptr)
	{
		return ErrorNone;
	}
	return ErrorAccountNotLogin;
}

void SimExchange::SendRspAccountLogin(ReqAccountLoginPackage* reqPackage, QuantTrading::PrimaryAccount* primaryAccount, int errorId)
{
	rspAccountLoginPackage_->Prepare(reqPackage->SessionId, false, reqPackage->Head.MsgSeqNum);
	rspAccountLoginPackage_->RspInfo->ErrorId = errorId;
	strcpy(rspAccountLoginPackage_->RspInfo->ErrorMsg, GetErrorMessage(errorId));
	
	strcpy(rspAccountLoginPackage_->RspAccountLogin->AccountId, reqPackage->ReqAccountLogin->AccountId);
	rspAccountLoginPackage_->RspAccountLogin->SessionId = reqPackage->SessionId;
    TimeUtility::GetLocalDateTime(rspAccountLoginPackage_->RspAccountLogin->LoginDate, rspAccountLoginPackage_->RspAccountLogin->LoginTime);

	tradeFront_->Send(rspAccountLoginPackage_);
}
void SimExchange::SendRspInsertOrder(ReqInsertOrderPackage* reqPackage, int errorId)
{
	rspInsertOrderPackage_->Prepare(reqPackage->SessionId, false, reqPackage->Head.MsgSeqNum);
	rspInsertOrderPackage_->RspInfo->ErrorId = errorId;
	strcpy(rspInsertOrderPackage_->RspInfo->ErrorMsg, GetErrorMessage(errorId));
	memcpy(rspInsertOrderPackage_->ReqInsertOrder, reqPackage->ReqInsertOrder, sizeof(ReqInsertOrderField));
	tradeFront_->Send(rspInsertOrderPackage_);
}
void SimExchange::SendRspCancelOrder(ReqCancelOrderPackage* reqPackage, int errorId)
{
	rspCancelOrderPackage_->Prepare(reqPackage->SessionId, false, reqPackage->Head.MsgSeqNum);
	rspCancelOrderPackage_->RspInfo->ErrorId = errorId;
	strcpy(rspCancelOrderPackage_->RspInfo->ErrorMsg, GetErrorMessage(errorId));
	memcpy(rspCancelOrderPackage_->ReqCancelOrder, reqPackage->ReqCancelOrder, sizeof(ReqCancelOrderField));
	tradeFront_->Send(rspCancelOrderPackage_);
}
void SimExchange::SendRspQryOrder(ReqQryOrderPackage* reqPackage, int errorId, bool isLast, QuantTrading::Order* order)
{
	rspQryOrderPackage_->Prepare(reqPackage->SessionId, !isLast, reqPackage->Head.MsgSeqNum);
	rspQryOrderPackage_->RspInfo->ErrorId = errorId;
	strcpy(rspQryOrderPackage_->RspInfo->ErrorMsg, GetErrorMessage(errorId));
	if (order != nullptr)
	{
		MdbToField(order, rspQryOrderPackage_->Order);
	}
	tradeFront_->Send(rspQryOrderPackage_);
}
void SimExchange::SendRspQryTrade(ReqQryTradePackage* reqPackage, int errorId, bool isLast, QuantTrading::Trade* trade)
{
	rspQryTradePackage_->Prepare(reqPackage->SessionId, !isLast, reqPackage->Head.MsgSeqNum);
	rspQryTradePackage_->RspInfo->ErrorId = errorId;
	strcpy(rspQryTradePackage_->RspInfo->ErrorMsg, GetErrorMessage(errorId));
	if (trade != nullptr)
	{
		MdbToField(trade, rspQryTradePackage_->Trade);
	}
	tradeFront_->Send(rspQryTradePackage_);
}
void SimExchange::SendRspQryInstrument(ReqQryInstrumentPackage* reqPackage, int errorId, bool isLast, QuantTrading::Instrument* instrument)
{
	rspQryInstrumentPackage_->Prepare(reqPackage->SessionId, !isLast, reqPackage->Head.MsgSeqNum);
	rspQryInstrumentPackage_->RspInfo->ErrorId = errorId;
	strcpy(rspQryInstrumentPackage_->RspInfo->ErrorMsg, GetErrorMessage(errorId));
	if (instrument != nullptr)
	{
		strcpy(rspQryInstrumentPackage_->Instrument->ExchangeId, instrument->ExchangeId);
		strcpy(rspQryInstrumentPackage_->Instrument->InstrumentId, instrument->InstrumentId);
		strcpy(rspQryInstrumentPackage_->Instrument->ExchangeInstId, instrument->ExchangeInstId);
		strcpy(rspQryInstrumentPackage_->Instrument->InstrumentName, instrument->InstrumentName);
		strcpy(rspQryInstrumentPackage_->Instrument->ProductId, instrument->ProductId);
		rspQryInstrumentPackage_->Instrument->ProductClass = instrument->ProductClass;
		rspQryInstrumentPackage_->Instrument->VolumeMultiple = instrument->VolumeMultiple;
		rspQryInstrumentPackage_->Instrument->PriceTick = instrument->PriceTick;
		rspQryInstrumentPackage_->Instrument->MaxMarketOrderVolume = instrument->MaxMarketOrderVolume;
		rspQryInstrumentPackage_->Instrument->MinMarketOrderVolume = instrument->MinMarketOrderVolume;
		rspQryInstrumentPackage_->Instrument->MaxLimitOrderVolume = instrument->MaxLimitOrderVolume;
		rspQryInstrumentPackage_->Instrument->MinLimitOrderVolume = instrument->MinLimitOrderVolume;
		strcpy(rspQryInstrumentPackage_->Instrument->SessionName, instrument->SessionName);
	}
	tradeFront_->Send(rspQryInstrumentPackage_);
}

void SimExchange::SendRtnOrder(QuantTrading::Order* order)
{
	MdbToField(order, rtnOrderPackage_->Order);

	auto primaryAccountLoginSessionRange = mdb_->PrimaryAccountLoginSession->PrimaryAccountIdIndex->EqualRange(order->AccountId);
	for (auto& it = primaryAccountLoginSessionRange.first; it != primaryAccountLoginSessionRange.second; ++it)
	{
		rtnOrderPackage_->Prepare((*it)->SessionId, false, 0);
		tradeFront_->Send(rtnOrderPackage_);
	}
}
void SimExchange::SendRtnTrade(QuantTrading::Trade* trade)
{
	MdbToField(trade, rtnTradePackage_->Trade);

	auto primaryAccountLoginSessionRange = mdb_->PrimaryAccountLoginSession->PrimaryAccountIdIndex->EqualRange(trade->AccountId);
	for (auto& it = primaryAccountLoginSessionRange.first; it != primaryAccountLoginSessionRange.second; ++it)
	{
		rtnTradePackage_->Prepare((*it)->SessionId, false, 0);
		tradeFront_->Send(rtnTradePackage_);
	}
}

Package* SimExchange::GetNextPackage()
{
	lock_guard<mutex> guard(mutex_);
	if (packages_.empty())
		return nullptr;
	auto package = packages_.front();
	packages_.pop_front();
	return package;
}
void SimExchange::ReqSubMarketData(const ExchangeIdType& exchangeId, const InstrumentIdType& instrumentId)
{
    ReqSubMarketDataField reqSubMd{0};
	Utility::Strcpy(reqSubMd.ExchangeId, exchangeId);
	Utility::Strcpy(reqSubMd.InstrumentId, instrumentId);
    auto [canonicalIt, isNew] = subscribeInstruments_.insert(reqSubMd);
    if (isNew && isMdLogged_)
    {
        mdSpi_->ReqSubMarketData(&*canonicalIt);
    }
}
}
