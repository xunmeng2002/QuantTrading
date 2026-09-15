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
using namespace mdb;
using namespace spark;
using namespace spark::core;
using namespace quanttrading::ordermatch;


namespace quanttrading::simexchange
{
SimExchange::SimExchange(mdb::Mdb* mdb, TradeFront* tradeFront, MdFront* mdFront, MdSpiImpl* mdSpi, MatchModeType matchMode)
	:ThreadBase("SimExchange"), m_Mdb(mdb), m_TradeFront(tradeFront), m_MdFront(mdFront), m_MdSpi(mdSpi), m_TradingDay(""), m_CurrDate(""), m_CurrTime(""), m_IsMdLogged(false)
{
	auto tradingDay = m_Mdb->tradingDay->primaryKey->Select(1);
	if (tradingDay != nullptr)
	{
		strcpy(m_TradingDay, tradingDay->CurrTradingDay);
	}

	m_OrderMatch = OrderMatch::CreateOrderMatch(matchMode, m_TradingDay);
	m_OrderMatch->Subscribe(this);
	m_PositionMaintenance = new quanttrading::settlement::PositionMaintenance(m_Mdb);

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
	SeedNextOrderIDFromOrders(m_Mdb->order);
	auto positionItPair = m_Mdb->position->primaryKey->SelectAll();
	for (auto& it = positionItPair.first; it != positionItPair.second; ++it)
	{
		auto position = *it;
		ReqSubMarketData(position->ExchangeID, position->InstrumentID);
	}
}

void SimExchange::OnProtocolConnect(SessionIDType sessionID, const char* ip, int port)
{
	WriteLog(LogLevel::Info, "TradeFront::OnProtocolConnect SessionID:%lld, ip:%s, port:%d", sessionID, ip, port);
}
void SimExchange::OnProtocolDisConnect(SessionIDType sessionID, const char* ip, int port)
{
	WriteLog(LogLevel::Info, "TradeFront::OnProtocolDisConnect SessionID:%lld, ip:%s, port:%d", sessionID, ip, port);
	NotifyDisConnectPackage* package = NotifyDisConnectPackage::Allocate();
	package->Prepare(sessionID, false, 0);
	package->NotifyDisConnect = Allocate<NotifyDisConnectField>();
	package->NotifyDisConnect->SessionID = sessionID;
	strcpy(package->NotifyDisConnect->IPAddress, ip);
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

void SimExchange::OnOrder(mdb::Order* order)
{
	SendRtnOrder(order);
}
void SimExchange::OnOrderUpdate(mdb::Order* order, mdb::Order* newOrder)
{
    m_Mdb->order->Update(order, newOrder);
    SendRtnOrder(order);
}
void SimExchange::OnTrade(mdb::Trade* trade)
{
    m_Mdb->trade->Insert(trade);
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
	m_ConditionVariable.wait_for(guard, m_TimeOut, [this]() {
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
	auto mdTick = mdb::DepthMarketData::Allocate();
    FieldToMdb(rtnPackage->DepthMarketData, mdTick);
	m_OrderMatch->OnTick(mdTick);
	auto oldMdTick = m_Mdb->depthMarketData->primaryKey->Select(mdTick->TradingDay, mdTick->ExchangeID, mdTick->InstrumentID);
	if (oldMdTick == nullptr)
	{
		m_Mdb->depthMarketData->Insert(mdTick);
	}
	else
	{
		m_Mdb->depthMarketData->Update(oldMdTick, mdTick);
	}
}
void SimExchange::HandleRtnBarMarketData(RtnBarMarketDataPackage* rtnPackage)
{
	WriteLog(LogLevel::Info, "HandleRtnBarMarketData %s", rtnPackage->GetDebugString());
	auto mdBar = mdb::BarMarketData::Allocate();
    FieldToMdb(rtnPackage->BarMarketData, mdBar);
	m_OrderMatch->OnBar(mdBar);
	m_Mdb->barMarketData->Insert(mdBar);
}

void SimExchange::HandleNotifyDisConnect(NotifyDisConnectPackage* notifyPackage)
{
	WriteLog(LogLevel::Info, "HandleNotifyDisConnect %s", notifyPackage->GetDebugString());
	m_Mdb->primaryAccountLoginSession->EraseBySessionIDIndex(notifyPackage->NotifyDisConnect->SessionID);
}
void SimExchange::HandleReqAccountLogin(ReqAccountLoginPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleReqAccountLogin %s", reqPackage->GetDebugString());
	auto errorID = ErrorNone;
	auto primaryAccount = m_Mdb->primaryAccount->primaryKey->Select(reqPackage->ReqAccountLogin->AccountID);
	if (primaryAccount == nullptr)
	{
		errorID = ErrorPrimaryAccountNotExist;
	}
	else if (strcmp(primaryAccount->Password, reqPackage->ReqAccountLogin->Password) != 0)
	{
		errorID = ErrorIncorrectPassword;
	}
	else
	{
		auto primaryAccountLoginSession = m_Mdb->primaryAccountLoginSession->primaryKey->Select(reqPackage->ReqAccountLogin->AccountID, reqPackage->SessionID);
		if (primaryAccountLoginSession != nullptr)
		{
			errorID = ErrorAccountAlreadyLogin;
		}
		else
		{
			primaryAccountLoginSession = mdb::PrimaryAccountLoginSession::Allocate();
			memset(primaryAccountLoginSession, 0, sizeof(mdb::PrimaryAccountLoginSession));
			strcpy(primaryAccountLoginSession->PrimaryAccountID, reqPackage->ReqAccountLogin->AccountID);
			primaryAccountLoginSession->SessionID = reqPackage->SessionID;
			strcpy(primaryAccountLoginSession->IPAddress, reqPackage->IPAddress);
			m_Mdb->primaryAccountLoginSession->Insert(primaryAccountLoginSession);
		}
	}
	SendRspAccountLogin(reqPackage, primaryAccount, errorID);
}
void SimExchange::HandleReqAccountLogout(ReqAccountLogoutPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleBrokerLogout %s", reqPackage->GetDebugString());
	
	m_RspAccountLogoutPackage->Prepare(reqPackage->SessionID, false, reqPackage->Head.MsgSeqNum);

	strcpy(m_RspAccountLogoutPackage->RspAccountLogout->AccountID, reqPackage->ReqAccountLogout->AccountID);
	auto primaryAccountLoginSession = m_Mdb->primaryAccountLoginSession->primaryKey->Select(reqPackage->ReqAccountLogout->AccountID, reqPackage->SessionID);
	if (primaryAccountLoginSession != nullptr)
	{
		m_Mdb->primaryAccountLoginSession->Erase(primaryAccountLoginSession);

		m_RspAccountLogoutPackage->RspInfo->ErrorID = ErrorNone;
		strcpy(m_RspAccountLogoutPackage->RspInfo->ErrorMsg, GetErrorMessage(ErrorNone));
	}
	else
	{
		m_RspAccountLogoutPackage->RspInfo->ErrorID = ErrorAccountNotLogin;
		strcpy(m_RspAccountLogoutPackage->RspInfo->ErrorMsg, GetErrorMessage(ErrorAccountNotLogin));
	}

	m_TradeFront->Send(m_RspAccountLogoutPackage);
}

void SimExchange::HandleReqInsertOrder(ReqInsertOrderPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleReqInsertOrder %s", reqPackage->GetDebugString());
	auto errorID = CheckSessionLogin(reqPackage->ReqInsertOrder->AccountID, reqPackage->SessionID);
	if (errorID != ErrorNone)
	{
		SendRspInsertOrder(reqPackage, errorID);
		return;
	}
	auto instrument = m_Mdb->instrument->primaryKey->Select(reqPackage->ReqInsertOrder->ExchangeID, reqPackage->ReqInsertOrder->InstrumentID);
	if (instrument == nullptr)
	{
		SendRspInsertOrder(reqPackage, ErrorInstrumentNotExist);
		return;
	}
	auto account = m_Mdb->account->primaryKey->Select(reqPackage->ReqInsertOrder->AccountID);
	if (account == nullptr)
	{
		SendRspInsertOrder(reqPackage, ErrorAccountNotExist);
		return;
	}
	errorID = CheckForInsertOrder(reqPackage->ReqInsertOrder, instrument);
	ReqSubMarketData(instrument->ExchangeID, instrument->InstrumentID);
	SendRspInsertOrder(reqPackage, errorID);
	if (errorID != ErrorNone)
	{
		return;
	}
	TimeUtility::GetLocalDateTime(m_CurrDate, m_CurrTime);
	auto order = CreateOrder(reqPackage, account, instrument, m_TradingDay, m_CurrDate, m_CurrTime);
	m_Mdb->order->Insert(order);
	m_OrderMatch->InsertOrder(order);
}
void SimExchange::HandleReqCancelOrder(ReqCancelOrderPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleReqCancelOrder %s", reqPackage->GetDebugString());
	auto errorID = CheckSessionLogin(reqPackage->ReqCancelOrder->AccountID, reqPackage->SessionID);
	if (errorID != ErrorNone)
	{
		SendRspCancelOrder(reqPackage, errorID);
		return;
	}
	auto order = m_Mdb->order->primaryKey->Select(m_TradingDay, reqPackage->ReqCancelOrder->AccountID, reqPackage->ReqCancelOrder->ExchangeID,
		reqPackage->ReqCancelOrder->InstrumentID, reqPackage->ReqCancelOrder->OrderID);
	if (order == nullptr)
	{
		order = m_Mdb->order->clientOrderIDUniqueKey->Select(m_TradingDay, reqPackage->ReqCancelOrder->AccountID, reqPackage->ReqCancelOrder->ExchangeID,
			reqPackage->ReqCancelOrder->InstrumentID, reqPackage->ReqCancelOrder->SessionID, reqPackage->ReqCancelOrder->ClientOrderID);
		if (order == nullptr)
		{
			errorID = ErrorOrderNotExist;
		}
	}
	if (order != nullptr)
	{
		errorID = CheckForCancelOrder(order);
	}
	SendRspCancelOrder(reqPackage, errorID);
	if (errorID != ErrorNone)
	{
		return;
	}
	m_OrderMatch->CancelOrder(order);
}
void SimExchange::HandleReqQryOrder(ReqQryOrderPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleReqQryOrder %s", reqPackage->GetDebugString());
	auto errorID = CheckSessionLogin(reqPackage->ReqQryOrder->AccountID, reqPackage->SessionID);
	if (errorID != ErrorNone)
	{
		SendRspQryOrder(reqPackage, errorID, true);
		return;
	}
	auto orderRange = m_Mdb->order->accountIDIndex->EqualRange(m_TradingDay, reqPackage->ReqQryOrder->AccountID);
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
	auto errorID = CheckSessionLogin(reqPackage->ReqQryTrade->AccountID, reqPackage->SessionID);
	if (errorID != ErrorNone)
	{
		SendRspQryTrade(reqPackage, errorID, true);
		return;
	}
	auto tradeRange = m_Mdb->trade->accountIDIndex->EqualRange(m_TradingDay, reqPackage->ReqQryTrade->AccountID);
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
	auto errorID = CheckSessionLogin(reqPackage->SessionID);
	if (errorID != ErrorNone)
	{
		SendRspQryInstrument(reqPackage, errorID, true);
		return;
	}
	m_RspQryInstrumentPackage->Instrument = Allocate<InstrumentField>();
	if (strlen(reqPackage->ReqQryInstrument->ExchangeID) != 0 && strlen(reqPackage->ReqQryInstrument->InstrumentID) != 0)
	{
		auto instrument = m_Mdb->instrument->primaryKey->Select(reqPackage->ReqQryInstrument->ExchangeID, reqPackage->ReqQryInstrument->InstrumentID);
		SendRspQryInstrument(reqPackage, ErrorNone, true, instrument);
	}
	else if (strlen(reqPackage->ReqQryInstrument->ExchangeID) != 0)
	{
		auto range = m_Mdb->instrument->exchangeIDIndex->EqualRange(reqPackage->ReqQryInstrument->ExchangeID);
		for (auto& it = range.first; it != range.second; )
		{
			auto record = *it;
			SendRspQryInstrument(reqPackage, ErrorNone, ++it == range.second, record);
		}
	}
	else
	{
		auto range = m_Mdb->instrument->primaryKey->SelectAll();
		for (auto& it = range.first; it != range.second; )
		{
			auto record = *it;
			SendRspQryInstrument(reqPackage, ErrorNone, ++it == range.second, record);
		}
	}
	::Deallocate(m_RspQryInstrumentPackage->Instrument);
	m_RspQryInstrumentPackage->Instrument = nullptr;
}

int SimExchange::CheckSessionLogin(const SessionIDType& sessionID)
{
	auto sessionIDRange = m_Mdb->primaryAccountLoginSession->sessionIDIndex->EqualRange(sessionID);
	return sessionIDRange.first != sessionIDRange.second ? ErrorNone : ErrorSessionNotLogin;
}

int SimExchange::CheckSessionLogin(const AccountIDType& primaryAccountID, const SessionIDType& sessionID)
{
	auto primaryAccountLoginSession = m_Mdb->primaryAccountLoginSession->primaryKey->Select(primaryAccountID, sessionID);
	if (primaryAccountLoginSession != nullptr)
	{
		return ErrorNone;
	}
	return ErrorAccountNotLogin;
}

void SimExchange::SendRspAccountLogin(ReqAccountLoginPackage* reqPackage, mdb::PrimaryAccount* primaryAccount, int errorID)
{
	m_RspAccountLoginPackage->Prepare(reqPackage->SessionID, false, reqPackage->Head.MsgSeqNum);
	m_RspAccountLoginPackage->RspInfo->ErrorID = errorID;
	strcpy(m_RspAccountLoginPackage->RspInfo->ErrorMsg, GetErrorMessage(errorID));
	
	strcpy(m_RspAccountLoginPackage->RspAccountLogin->AccountID, reqPackage->ReqAccountLogin->AccountID);
	m_RspAccountLoginPackage->RspAccountLogin->SessionID = reqPackage->SessionID;
    TimeUtility::GetLocalDateTime(m_RspAccountLoginPackage->RspAccountLogin->LoginDate, m_RspAccountLoginPackage->RspAccountLogin->LoginTime);

	m_TradeFront->Send(m_RspAccountLoginPackage);
}
void SimExchange::SendRspInsertOrder(ReqInsertOrderPackage* reqPackage, int errorID)
{
	m_RspInsertOrderPackage->Prepare(reqPackage->SessionID, false, reqPackage->Head.MsgSeqNum);
	m_RspInsertOrderPackage->RspInfo->ErrorID = errorID;
	strcpy(m_RspInsertOrderPackage->RspInfo->ErrorMsg, GetErrorMessage(errorID));
	memcpy(m_RspInsertOrderPackage->ReqInsertOrder, reqPackage->ReqInsertOrder, sizeof(ReqInsertOrderField));
	m_TradeFront->Send(m_RspInsertOrderPackage);
}
void SimExchange::SendRspCancelOrder(ReqCancelOrderPackage* reqPackage, int errorID)
{
	m_RspCancelOrderPackage->Prepare(reqPackage->SessionID, false, reqPackage->Head.MsgSeqNum);
	m_RspCancelOrderPackage->RspInfo->ErrorID = errorID;
	strcpy(m_RspCancelOrderPackage->RspInfo->ErrorMsg, GetErrorMessage(errorID));
	memcpy(m_RspCancelOrderPackage->ReqCancelOrder, reqPackage->ReqCancelOrder, sizeof(ReqCancelOrderField));
	m_TradeFront->Send(m_RspCancelOrderPackage);
}
void SimExchange::SendRspQryOrder(ReqQryOrderPackage* reqPackage, int errorID, bool isLast, mdb::Order* order)
{
	m_RspQryOrderPackage->Prepare(reqPackage->SessionID, !isLast, reqPackage->Head.MsgSeqNum);
	m_RspQryOrderPackage->RspInfo->ErrorID = errorID;
	strcpy(m_RspQryOrderPackage->RspInfo->ErrorMsg, GetErrorMessage(errorID));
	if (order != nullptr)
	{
		MdbToField(order, m_RspQryOrderPackage->Order);
	}
	m_TradeFront->Send(m_RspQryOrderPackage);
}
void SimExchange::SendRspQryTrade(ReqQryTradePackage* reqPackage, int errorID, bool isLast, mdb::Trade* trade)
{
	m_RspQryTradePackage->Prepare(reqPackage->SessionID, !isLast, reqPackage->Head.MsgSeqNum);
	m_RspQryTradePackage->RspInfo->ErrorID = errorID;
	strcpy(m_RspQryTradePackage->RspInfo->ErrorMsg, GetErrorMessage(errorID));
	if (trade != nullptr)
	{
		MdbToField(trade, m_RspQryTradePackage->Trade);
	}
	m_TradeFront->Send(m_RspQryTradePackage);
}
void SimExchange::SendRspQryInstrument(ReqQryInstrumentPackage* reqPackage, int errorID, bool isLast, mdb::Instrument* instrument)
{
	m_RspQryInstrumentPackage->Prepare(reqPackage->SessionID, !isLast, reqPackage->Head.MsgSeqNum);
	m_RspQryInstrumentPackage->RspInfo->ErrorID = errorID;
	strcpy(m_RspQryInstrumentPackage->RspInfo->ErrorMsg, GetErrorMessage(errorID));
	if (instrument != nullptr)
	{
		strcpy(m_RspQryInstrumentPackage->Instrument->ExchangeID, instrument->ExchangeID);
		strcpy(m_RspQryInstrumentPackage->Instrument->InstrumentID, instrument->InstrumentID);
		strcpy(m_RspQryInstrumentPackage->Instrument->ExchangeInstID, instrument->ExchangeInstID);
		strcpy(m_RspQryInstrumentPackage->Instrument->InstrumentName, instrument->InstrumentName);
		strcpy(m_RspQryInstrumentPackage->Instrument->ProductID, instrument->ProductID);
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

void SimExchange::SendRtnOrder(mdb::Order* order)
{
	MdbToField(order, m_RtnOrderPackage->Order);

	auto primaryAccountLoginSessionRange = m_Mdb->primaryAccountLoginSession->primaryAccountIDIndex->EqualRange(order->AccountID);
	for (auto& it = primaryAccountLoginSessionRange.first; it != primaryAccountLoginSessionRange.second; ++it)
	{
		m_RtnOrderPackage->Prepare((*it)->SessionID, false, 0);
		m_TradeFront->Send(m_RtnOrderPackage);
	}
}
void SimExchange::SendRtnTrade(mdb::Trade* trade)
{
	MdbToField(trade, m_RtnTradePackage->Trade);

	auto primaryAccountLoginSessionRange = m_Mdb->primaryAccountLoginSession->primaryAccountIDIndex->EqualRange(trade->AccountID);
	for (auto& it = primaryAccountLoginSessionRange.first; it != primaryAccountLoginSessionRange.second; ++it)
	{
		m_RtnTradePackage->Prepare((*it)->SessionID, false, 0);
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
void SimExchange::ReqSubMarketData(const ExchangeIDType& exchangeID, const InstrumentIDType& instrumentID)
{
    ReqSubMarketDataField reqSubMd{0};
	Utility::Strcpy(reqSubMd.ExchangeID, exchangeID);
	Utility::Strcpy(reqSubMd.InstrumentID, instrumentID);
    auto [canonicalIt, isNew] = m_SubscribeInstruments.insert(reqSubMd);
    if (isNew && m_IsMdLogged)
    {
        m_MdSpi->ReqSubMarketData(&*canonicalIt);
    }
}
}
