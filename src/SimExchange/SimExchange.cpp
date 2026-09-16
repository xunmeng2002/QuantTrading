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
using namespace QuantTrading::ordermatch;


namespace QuantTrading::SimExchange
{
SimExchange::SimExchange(QuantTrading::Mdb* mdb, TradeFront* tradeFront, MdFront* mdFront, MdSpiImpl* mdSpi, MatchModeType matchMode)
	:ThreadBase("SimExchange"), m_Mdb(mdb), m_TradeFront(tradeFront), m_MdFront(mdFront), m_MdSpi(mdSpi), m_TradingDay(""), m_CurrDate(""), m_CurrTime(""), m_IsMdLogged(false)
{
	auto tradingDay = m_Mdb->TradingDay->PrimaryKey->Select(1);
	if (tradingDay != nullptr)
	{
		strcpy(m_TradingDay, tradingDay->CurrTradingDay);
	}

	m_OrderMatch = OrderMatch::CreateOrderMatch(matchMode, m_TradingDay);
	m_OrderMatch->Subscribe(this);
	m_PositionMaintenance = new QuantTrading::Settlement::PositionMaintenance(m_Mdb);

	m_RspAccountLoginPackage = Allocate<RspAccountLoginPackage>();
	m_RspAccountLoginPackage->RspInfo = Allocate<RspInfoField>();
	m_RspAccountLoginPackage->RspAccountLogin = Allocate<RspAccountLoginField>();
	m_RspAccountLogoutPackage = Allocate<RspAccountLogoutPackage>();
	m_RspAccountLogoutPackage->RspInfo = Allocate<RspInfoField>();
	m_RspAccountLogoutPackage->RspAccountLogout = Allocate<RspAccountLogoutField>();

	m_RspInsertOrderPackage = Allocate<RspInsertOrderPackage>();
	m_RspInsertOrderPackage->RspInfo = Allocate<RspInfoField>();
	m_RspInsertOrderPackage->ReqInsertOrder = Allocate<ReqInsertOrderField>();
	m_RspCancelOrderPackage = Allocate<RspCancelOrderPackage>();
	m_RspCancelOrderPackage->RspInfo = Allocate<RspInfoField>();
	m_RspCancelOrderPackage->ReqCancelOrder = Allocate<ReqCancelOrderField>();

	m_RspQryOrderPackage = Allocate<RspQryOrderPackage>();
	m_RspQryOrderPackage->RspInfo = Allocate<RspInfoField>();
	m_RspQryTradePackage = Allocate<RspQryTradePackage>();
	m_RspQryTradePackage->RspInfo = Allocate<RspInfoField>();
	m_RspQryInstrumentPackage = Allocate<RspQryInstrumentPackage>();
	m_RspQryInstrumentPackage->RspInfo = Allocate<RspInfoField>();

	m_RtnOrderPackage = Allocate<RtnOrderPackage>();
	m_RtnOrderPackage->Order = Allocate<OrderField>();
	m_RtnTradePackage = Allocate<RtnTradePackage>();
	m_RtnTradePackage->Trade = Allocate<TradeField>();
}
SimExchange::~SimExchange()
{

}
void SimExchange::Init()
{
	SeedNextOrderIDFromOrders(m_Mdb->Order);
	auto positionItPair = m_Mdb->Position->PrimaryKey->SelectAll();
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
	m_IsMdLogged = false;
}
void SimExchange::OnMessage(Package* package)
{
	{
		lock_guard<mutex> guard(m_Mutex);
		m_Packages.push_back(package);
	}
	m_ConditionVariable.notify_one();
}

void SimExchange::OnOrder(QuantTrading::Order* order)
{
	SendRtnOrder(order);
}
void SimExchange::OnOrderUpdate(QuantTrading::Order* order, QuantTrading::Order* newOrder)
{
    m_Mdb->Order->Update(order, newOrder);
    SendRtnOrder(order);
}
void SimExchange::OnTrade(QuantTrading::Trade* trade)
{
    m_Mdb->Trade->Insert(trade);
	SendRtnTrade(trade);
	m_PositionMaintenance->UpdateOnTrade(trade);
}

void SimExchange::Run()
{
	CheckPackages();
	HandlePackages();
}
void SimExchange::CheckPackages()
{
	std::unique_lock<std::mutex> guard(m_Mutex);
	m_ConditionVariable.wait_for(guard, timeOut_, [this]() {
		return !m_Packages.empty();
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
	m_IsMdLogged = true;
	for (auto& reqSubMd : m_SubscribeInstruments)
	{
		m_MdSpi->ReqSubMarketData(&reqSubMd);
	}
}
void SimExchange::HandleRspMdUserLogout(RspMdUserLogoutPackage* package)
{
	m_IsMdLogged = false;
}
void SimExchange::HandleRtnDepthMarketData(RtnDepthMarketDataPackage* rtnPackage)
{
	WriteLog(LogLevel::Info, "HandleRtnDepthMarketData %s", rtnPackage->GetDebugString());
	auto mdTick = QuantTrading::DepthMarketData::Allocate();
    FieldToMdb(rtnPackage->DepthMarketData, mdTick);
	m_OrderMatch->OnTick(mdTick);
	auto oldMdTick = m_Mdb->DepthMarketData->PrimaryKey->Select(mdTick->TradingDay, mdTick->ExchangeId, mdTick->InstrumentId);
	if (oldMdTick == nullptr)
	{
		m_Mdb->DepthMarketData->Insert(mdTick);
	}
	else
	{
		m_Mdb->DepthMarketData->Update(oldMdTick, mdTick);
	}
}
void SimExchange::HandleRtnBarMarketData(RtnBarMarketDataPackage* rtnPackage)
{
	WriteLog(LogLevel::Info, "HandleRtnBarMarketData %s", rtnPackage->GetDebugString());
	auto mdBar = QuantTrading::BarMarketData::Allocate();
    FieldToMdb(rtnPackage->BarMarketData, mdBar);
	m_OrderMatch->OnBar(mdBar);
	m_Mdb->BarMarketData->Insert(mdBar);
}

void SimExchange::HandleNotifyDisConnect(NotifyDisConnectPackage* notifyPackage)
{
	WriteLog(LogLevel::Info, "HandleNotifyDisConnect %s", notifyPackage->GetDebugString());
	m_Mdb->PrimaryAccountLoginSession->EraseBySessionIdIndex(notifyPackage->NotifyDisConnect->SessionId);
}
void SimExchange::HandleReqAccountLogin(ReqAccountLoginPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleReqAccountLogin %s", reqPackage->GetDebugString());
	auto errorId = ErrorNone;
	auto primaryAccount = m_Mdb->PrimaryAccount->PrimaryKey->Select(reqPackage->ReqAccountLogin->AccountId);
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
		auto primaryAccountLoginSession = m_Mdb->PrimaryAccountLoginSession->PrimaryKey->Select(reqPackage->ReqAccountLogin->AccountId, reqPackage->SessionId);
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
			m_Mdb->PrimaryAccountLoginSession->Insert(primaryAccountLoginSession);
		}
	}
	SendRspAccountLogin(reqPackage, primaryAccount, errorId);
}
void SimExchange::HandleReqAccountLogout(ReqAccountLogoutPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleBrokerLogout %s", reqPackage->GetDebugString());
	
	m_RspAccountLogoutPackage->Prepare(reqPackage->SessionId, false, reqPackage->Head.MsgSeqNum);

	strcpy(m_RspAccountLogoutPackage->RspAccountLogout->AccountId, reqPackage->ReqAccountLogout->AccountId);
	auto primaryAccountLoginSession = m_Mdb->PrimaryAccountLoginSession->PrimaryKey->Select(reqPackage->ReqAccountLogout->AccountId, reqPackage->SessionId);
	if (primaryAccountLoginSession != nullptr)
	{
		m_Mdb->PrimaryAccountLoginSession->Erase(primaryAccountLoginSession);

		m_RspAccountLogoutPackage->RspInfo->ErrorId = ErrorNone;
		strcpy(m_RspAccountLogoutPackage->RspInfo->ErrorMsg, GetErrorMessage(ErrorNone));
	}
	else
	{
		m_RspAccountLogoutPackage->RspInfo->ErrorId = ErrorAccountNotLogin;
		strcpy(m_RspAccountLogoutPackage->RspInfo->ErrorMsg, GetErrorMessage(ErrorAccountNotLogin));
	}

	m_TradeFront->Send(m_RspAccountLogoutPackage);
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
	auto instrument = m_Mdb->Instrument->PrimaryKey->Select(reqPackage->ReqInsertOrder->ExchangeId, reqPackage->ReqInsertOrder->InstrumentId);
	if (instrument == nullptr)
	{
		SendRspInsertOrder(reqPackage, ErrorInstrumentNotExist);
		return;
	}
	auto account = m_Mdb->Account->PrimaryKey->Select(reqPackage->ReqInsertOrder->AccountId);
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
	TimeUtility::GetLocalDateTime(m_CurrDate, m_CurrTime);
	auto order = CreateOrder(reqPackage, account, instrument, m_TradingDay, m_CurrDate, m_CurrTime);
	m_Mdb->Order->Insert(order);
	m_OrderMatch->InsertOrder(order);
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
	auto order = m_Mdb->Order->PrimaryKey->Select(m_TradingDay, reqPackage->ReqCancelOrder->AccountId, reqPackage->ReqCancelOrder->ExchangeId,
		reqPackage->ReqCancelOrder->InstrumentId, reqPackage->ReqCancelOrder->OrderId);
	if (order == nullptr)
	{
		order = m_Mdb->Order->ClientOrderIdUniqueKey->Select(m_TradingDay, reqPackage->ReqCancelOrder->AccountId, reqPackage->ReqCancelOrder->ExchangeId,
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
	m_OrderMatch->CancelOrder(order);
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
	auto orderRange = m_Mdb->Order->AccountIdIndex->EqualRange(m_TradingDay, reqPackage->ReqQryOrder->AccountId);
	if (orderRange.first == orderRange.second)
	{
		SendRspQryOrder(reqPackage, ErrorNone, true);
	}
	else
	{
		m_RspQryOrderPackage->Order = Allocate<OrderField>();
		for (auto& it = orderRange.first; it != orderRange.second; )
		{
			auto record = *it;
			SendRspQryOrder(reqPackage, ErrorNone, ++it == orderRange.second, record);
		}
		::Deallocate(m_RspQryOrderPackage->Order);
		m_RspQryOrderPackage->Order = nullptr;
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
	auto tradeRange = m_Mdb->Trade->AccountIdIndex->EqualRange(m_TradingDay, reqPackage->ReqQryTrade->AccountId);
	if (tradeRange.first == tradeRange.second)
	{
		SendRspQryTrade(reqPackage, ErrorNone, true);
	}
	else
	{
		m_RspQryTradePackage->Trade = Allocate<TradeField>();
		for (auto& it = tradeRange.first; it != tradeRange.second; )
		{
			auto record = *it;
			SendRspQryTrade(reqPackage, ErrorNone, ++it == tradeRange.second, record);
		}
		::Deallocate(m_RspQryTradePackage->Trade);
		m_RspQryTradePackage->Trade = nullptr;
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
	m_RspQryInstrumentPackage->Instrument = Allocate<InstrumentField>();
	if (strlen(reqPackage->ReqQryInstrument->ExchangeId) != 0 && strlen(reqPackage->ReqQryInstrument->InstrumentId) != 0)
	{
		auto instrument = m_Mdb->Instrument->PrimaryKey->Select(reqPackage->ReqQryInstrument->ExchangeId, reqPackage->ReqQryInstrument->InstrumentId);
		SendRspQryInstrument(reqPackage, ErrorNone, true, instrument);
	}
	else if (strlen(reqPackage->ReqQryInstrument->ExchangeId) != 0)
	{
		auto range = m_Mdb->Instrument->ExchangeIdIndex->EqualRange(reqPackage->ReqQryInstrument->ExchangeId);
		for (auto& it = range.first; it != range.second; )
		{
			auto record = *it;
			SendRspQryInstrument(reqPackage, ErrorNone, ++it == range.second, record);
		}
	}
	else
	{
		auto range = m_Mdb->Instrument->PrimaryKey->SelectAll();
		for (auto& it = range.first; it != range.second; )
		{
			auto record = *it;
			SendRspQryInstrument(reqPackage, ErrorNone, ++it == range.second, record);
		}
	}
	::Deallocate(m_RspQryInstrumentPackage->Instrument);
	m_RspQryInstrumentPackage->Instrument = nullptr;
}

int SimExchange::CheckSessionLogin(const SessionIdType& sessionId)
{
	auto sessionIDRange = m_Mdb->PrimaryAccountLoginSession->SessionIdIndex->EqualRange(sessionId);
	return sessionIDRange.first != sessionIDRange.second ? ErrorNone : ErrorSessionNotLogin;
}

int SimExchange::CheckSessionLogin(const AccountIdType& primaryAccountID, const SessionIdType& sessionId)
{
	auto primaryAccountLoginSession = m_Mdb->PrimaryAccountLoginSession->PrimaryKey->Select(primaryAccountID, sessionId);
	if (primaryAccountLoginSession != nullptr)
	{
		return ErrorNone;
	}
	return ErrorAccountNotLogin;
}

void SimExchange::SendRspAccountLogin(ReqAccountLoginPackage* reqPackage, QuantTrading::PrimaryAccount* primaryAccount, int errorId)
{
	m_RspAccountLoginPackage->Prepare(reqPackage->SessionId, false, reqPackage->Head.MsgSeqNum);
	m_RspAccountLoginPackage->RspInfo->ErrorId = errorId;
	strcpy(m_RspAccountLoginPackage->RspInfo->ErrorMsg, GetErrorMessage(errorId));
	
	strcpy(m_RspAccountLoginPackage->RspAccountLogin->AccountId, reqPackage->ReqAccountLogin->AccountId);
	m_RspAccountLoginPackage->RspAccountLogin->SessionId = reqPackage->SessionId;
    TimeUtility::GetLocalDateTime(m_RspAccountLoginPackage->RspAccountLogin->LoginDate, m_RspAccountLoginPackage->RspAccountLogin->LoginTime);

	m_TradeFront->Send(m_RspAccountLoginPackage);
}
void SimExchange::SendRspInsertOrder(ReqInsertOrderPackage* reqPackage, int errorId)
{
	m_RspInsertOrderPackage->Prepare(reqPackage->SessionId, false, reqPackage->Head.MsgSeqNum);
	m_RspInsertOrderPackage->RspInfo->ErrorId = errorId;
	strcpy(m_RspInsertOrderPackage->RspInfo->ErrorMsg, GetErrorMessage(errorId));
	memcpy(m_RspInsertOrderPackage->ReqInsertOrder, reqPackage->ReqInsertOrder, sizeof(ReqInsertOrderField));
	m_TradeFront->Send(m_RspInsertOrderPackage);
}
void SimExchange::SendRspCancelOrder(ReqCancelOrderPackage* reqPackage, int errorId)
{
	m_RspCancelOrderPackage->Prepare(reqPackage->SessionId, false, reqPackage->Head.MsgSeqNum);
	m_RspCancelOrderPackage->RspInfo->ErrorId = errorId;
	strcpy(m_RspCancelOrderPackage->RspInfo->ErrorMsg, GetErrorMessage(errorId));
	memcpy(m_RspCancelOrderPackage->ReqCancelOrder, reqPackage->ReqCancelOrder, sizeof(ReqCancelOrderField));
	m_TradeFront->Send(m_RspCancelOrderPackage);
}
void SimExchange::SendRspQryOrder(ReqQryOrderPackage* reqPackage, int errorId, bool isLast, QuantTrading::Order* order)
{
	m_RspQryOrderPackage->Prepare(reqPackage->SessionId, !isLast, reqPackage->Head.MsgSeqNum);
	m_RspQryOrderPackage->RspInfo->ErrorId = errorId;
	strcpy(m_RspQryOrderPackage->RspInfo->ErrorMsg, GetErrorMessage(errorId));
	if (order != nullptr)
	{
		MdbToField(order, m_RspQryOrderPackage->Order);
	}
	m_TradeFront->Send(m_RspQryOrderPackage);
}
void SimExchange::SendRspQryTrade(ReqQryTradePackage* reqPackage, int errorId, bool isLast, QuantTrading::Trade* trade)
{
	m_RspQryTradePackage->Prepare(reqPackage->SessionId, !isLast, reqPackage->Head.MsgSeqNum);
	m_RspQryTradePackage->RspInfo->ErrorId = errorId;
	strcpy(m_RspQryTradePackage->RspInfo->ErrorMsg, GetErrorMessage(errorId));
	if (trade != nullptr)
	{
		MdbToField(trade, m_RspQryTradePackage->Trade);
	}
	m_TradeFront->Send(m_RspQryTradePackage);
}
void SimExchange::SendRspQryInstrument(ReqQryInstrumentPackage* reqPackage, int errorId, bool isLast, QuantTrading::Instrument* instrument)
{
	m_RspQryInstrumentPackage->Prepare(reqPackage->SessionId, !isLast, reqPackage->Head.MsgSeqNum);
	m_RspQryInstrumentPackage->RspInfo->ErrorId = errorId;
	strcpy(m_RspQryInstrumentPackage->RspInfo->ErrorMsg, GetErrorMessage(errorId));
	if (instrument != nullptr)
	{
		strcpy(m_RspQryInstrumentPackage->Instrument->ExchangeId, instrument->ExchangeId);
		strcpy(m_RspQryInstrumentPackage->Instrument->InstrumentId, instrument->InstrumentId);
		strcpy(m_RspQryInstrumentPackage->Instrument->ExchangeInstId, instrument->ExchangeInstId);
		strcpy(m_RspQryInstrumentPackage->Instrument->InstrumentName, instrument->InstrumentName);
		strcpy(m_RspQryInstrumentPackage->Instrument->ProductId, instrument->ProductId);
		m_RspQryInstrumentPackage->Instrument->ProductClass = instrument->ProductClass;
		m_RspQryInstrumentPackage->Instrument->VolumeMultiple = instrument->VolumeMultiple;
		m_RspQryInstrumentPackage->Instrument->PriceTick = instrument->PriceTick;
		m_RspQryInstrumentPackage->Instrument->MaxMarketOrderVolume = instrument->MaxMarketOrderVolume;
		m_RspQryInstrumentPackage->Instrument->MinMarketOrderVolume = instrument->MinMarketOrderVolume;
		m_RspQryInstrumentPackage->Instrument->MaxLimitOrderVolume = instrument->MaxLimitOrderVolume;
		m_RspQryInstrumentPackage->Instrument->MinLimitOrderVolume = instrument->MinLimitOrderVolume;
		strcpy(m_RspQryInstrumentPackage->Instrument->SessionName, instrument->SessionName);
	}
	m_TradeFront->Send(m_RspQryInstrumentPackage);
}

void SimExchange::SendRtnOrder(QuantTrading::Order* order)
{
	MdbToField(order, m_RtnOrderPackage->Order);

	auto primaryAccountLoginSessionRange = m_Mdb->PrimaryAccountLoginSession->PrimaryAccountIdIndex->EqualRange(order->AccountId);
	for (auto& it = primaryAccountLoginSessionRange.first; it != primaryAccountLoginSessionRange.second; ++it)
	{
		m_RtnOrderPackage->Prepare((*it)->SessionId, false, 0);
		m_TradeFront->Send(m_RtnOrderPackage);
	}
}
void SimExchange::SendRtnTrade(QuantTrading::Trade* trade)
{
	MdbToField(trade, m_RtnTradePackage->Trade);

	auto primaryAccountLoginSessionRange = m_Mdb->PrimaryAccountLoginSession->PrimaryAccountIdIndex->EqualRange(trade->AccountId);
	for (auto& it = primaryAccountLoginSessionRange.first; it != primaryAccountLoginSessionRange.second; ++it)
	{
		m_RtnTradePackage->Prepare((*it)->SessionId, false, 0);
		m_TradeFront->Send(m_RtnTradePackage);
	}
}

Package* SimExchange::GetNextPackage()
{
	lock_guard<mutex> guard(m_Mutex);
	if (m_Packages.empty())
		return nullptr;
	auto package = m_Packages.front();
	m_Packages.pop_front();
	return package;
}
void SimExchange::ReqSubMarketData(const ExchangeIdType& exchangeId, const InstrumentIdType& instrumentId)
{
    ReqSubMarketDataField reqSubMd{0};
	Utility::Strcpy(reqSubMd.ExchangeId, exchangeId);
	Utility::Strcpy(reqSubMd.InstrumentId, instrumentId);
    auto [canonicalIt, isNew] = m_SubscribeInstruments.insert(reqSubMd);
    if (isNew && m_IsMdLogged)
    {
        m_MdSpi->ReqSubMarketData(&*canonicalIt);
    }
}
}
