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
	auto tradingDay = m_Mdb->t_TradingDay->m_PrimaryKey->Select(1);
	if (tradingDay != nullptr)
	{
		strcpy(m_TradingDay, tradingDay->CurrTradingDay);
	}

	m_OrderMatch = OrderMatch::CreateOrderMatch(matchMode, m_TradingDay);
	m_OrderMatch->Subscribe(this);

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
	auto positionItPair = m_Mdb->t_Position->m_PrimaryKey->SelectAll();
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
    m_Mdb->t_Order->Update(order, newOrder);
    SendRtnOrder(order);
}
void SimExchange::OnTrade(mdb::Trade* trade)
{
    m_Mdb->t_Trade->Insert(trade);
	SendRtnTrade(trade);
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
		switch (package->Head.PackageID)
		{
		case RspMdUserLoginPackage::PackageID:
			HandleRspMdUserLogin((RspMdUserLoginPackage*)package);
			break;
		case RspMdUserLogoutPackage::PackageID:
			HandleRspMdUserLogout((RspMdUserLogoutPackage*)package);
			break;
		case RtnDepthMarketDataPackage::PackageID:
			HandleDepthMarketData((RtnDepthMarketDataPackage*)package);
			break;
		case RtnBarMarketDataPackage::PackageID:
			HandleBarMarketData((RtnBarMarketDataPackage*)package);
			break;
		case NotifyDisConnectPackage::PackageID:
			HandleNotifyDisConnect((NotifyDisConnectPackage*)package);
			break;
		case ReqAccountLoginPackage::PackageID:
			HandleAccountLogin((ReqAccountLoginPackage*)package);
			break;
		case ReqAccountLogoutPackage::PackageID:
			HandleAccountLogout((ReqAccountLogoutPackage*)package);
			break;
		case ReqInsertOrderPackage::PackageID:
			HandleInsertOrder((ReqInsertOrderPackage*)package);
			break;
		case ReqCancelOrderPackage::PackageID:
			HandleCancelOrder((ReqCancelOrderPackage*)package);
			break;
		case ReqQryOrderPackage::PackageID:
			HandleQryOrder((ReqQryOrderPackage*)package);
			break;
		case ReqQryTradePackage::PackageID:
			HandleQryTrade((ReqQryTradePackage*)package);
			break;
		case ReqQryInstrumentPackage::PackageID:
			HandleQryInstrument((ReqQryInstrumentPackage*)package);
			break;
		default:
			WriteLog(LogLevel::Warning, "UnExpect Package, PackageID:%d", package->Head.PackageID);
			break;
		}
		package->Deallocate();
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
void SimExchange::HandleDepthMarketData(RtnDepthMarketDataPackage* rtnPackage)
{
	WriteLog(LogLevel::Info, "HandleDepthMarketData %s", rtnPackage->GetDebugString());
	auto mdTick = mdb::DepthMarketData::Allocate();
    FieldToMdb(rtnPackage->DepthMarketData, mdTick);
	auto oldMdTick = m_Mdb->t_DepthMarketData->m_PrimaryKey->Select(mdTick->TradingDay, mdTick->ExchangeID, mdTick->InstrumentID);
	if (oldMdTick == nullptr)
	{
		m_Mdb->t_DepthMarketData->Insert(mdTick);
	}
	else
	{
		m_Mdb->t_DepthMarketData->Update(oldMdTick, mdTick);
	}
	m_OrderMatch->OnTick(mdTick);
}
void SimExchange::HandleBarMarketData(RtnBarMarketDataPackage* rtnPackage)
{
	WriteLog(LogLevel::Info, "HandleBarMarketData %s", rtnPackage->GetDebugString());
	auto mdBar = mdb::BarMarketData::Allocate();
    FieldToMdb(rtnPackage->BarMarketData, mdBar);
	m_Mdb->t_BarMarketData->Insert(mdBar);
	m_OrderMatch->OnBar(mdBar);
}

void SimExchange::HandleNotifyDisConnect(NotifyDisConnectPackage* notifyPackage)
{
	WriteLog(LogLevel::Info, "HandleNotifyDisConnect %s", notifyPackage->GetDebugString());
	auto loginSession = m_Mdb->t_AccountLoginSession->m_PrimaryKey->Select(notifyPackage->NotifyDisConnect->SessionID);
	if (loginSession != nullptr)
	{
		m_Mdb->t_AccountLoginSession->Erase(loginSession);
	}
}
void SimExchange::HandleAccountLogin(ReqAccountLoginPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleAccountLogin %s", reqPackage->GetDebugString());
	auto errorID = ErrorNone;
	auto primaryAccount = m_Mdb->t_PrimaryAccount->m_PrimaryKey->Select(reqPackage->ReqAccountLogin->AccountID);
	if (primaryAccount == nullptr)
	{
		errorID = ErrorBrokerNotExist;
	}
	else if (strcmp(primaryAccount->Password, reqPackage->ReqAccountLogin->Password) != 0)
	{
		errorID = ErrorIncorrectPassword;
	}
	else
	{
		auto accountLoginSession = m_Mdb->t_AccountLoginSession->m_PrimaryKey->Select(reqPackage->SessionID);
		if (accountLoginSession != nullptr)
		{
			errorID = ErrorSessionAlreadyLogin;
		}
		else
		{
			accountLoginSession = mdb::AccountLoginSession::Allocate();
			memset(accountLoginSession, 0, sizeof(mdb::AccountLoginSession));
			strcpy(accountLoginSession->AccountID, reqPackage->ReqAccountLogin->AccountID);
			accountLoginSession->SessionID = reqPackage->SessionID;
			strcpy(accountLoginSession->IPAddress, reqPackage->IPAddress);
			m_Mdb->t_AccountLoginSession->Insert(accountLoginSession);
		}
	}
	SendRspAccountLogin(reqPackage, primaryAccount, errorID);
}
void SimExchange::HandleAccountLogout(ReqAccountLogoutPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleBrokerLogout %s", reqPackage->GetDebugString());
	
	m_RspAccountLogoutPackage->Prepare(reqPackage->SessionID, false, reqPackage->Head.MsgSeqNum);

	strcpy(m_RspAccountLogoutPackage->RspAccountLogout->AccountID, reqPackage->ReqAccountLogout->AccountID);
	auto loginSession = m_Mdb->t_AccountLoginSession->m_PrimaryKey->Select(reqPackage->SessionID);
	if (loginSession != nullptr)
	{
		m_Mdb->t_AccountLoginSession->Erase(loginSession);

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

void SimExchange::HandleInsertOrder(ReqInsertOrderPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleInsertOrder %s", reqPackage->GetDebugString());
	auto errorID = ErrorNone;
	if (!CheckSessionLogin(reqPackage->SessionID))
	{
		SendRspInsertOrder(reqPackage, ErrorSessionNotLogin);
		return;
	}
	auto instrument = m_Mdb->t_Instrument->m_PrimaryKey->Select(reqPackage->ReqInsertOrder->ExchangeID, reqPackage->ReqInsertOrder->InstrumentID);
	if (instrument == nullptr)
	{
		errorID = ErrorInstrumentNotExist;
	}
	else
	{
		errorID = CheckForInsertOrder(reqPackage->ReqInsertOrder, instrument);
		ReqSubMarketData(instrument->ExchangeID, instrument->InstrumentID);
	}
	auto account = m_Mdb->t_Account->m_PrimaryKey->Select(reqPackage->ReqInsertOrder->AccountID);
	if (account == nullptr)
	{
		errorID = ErrorAccountNotExist;
	}
	SendRspInsertOrder(reqPackage, errorID);
	if (errorID != ErrorNone)
	{
		return;
	}
	TimeUtility::GetLocalDateTime(m_CurrDate, m_CurrTime);
	auto order = CreateOrder(reqPackage, account, instrument, m_TradingDay, m_CurrDate, m_CurrTime);
	m_Mdb->t_Order->Insert(order);
	m_OrderMatch->InsertOrder(order);
}
void SimExchange::HandleCancelOrder(ReqCancelOrderPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleCancelOrder %s", reqPackage->GetDebugString());
	auto errorID = ErrorNone;
	if (!CheckSessionLogin(reqPackage->SessionID))
	{
		SendRspCancelOrder(reqPackage, ErrorSessionNotLogin);
		return;
	}
	auto order = m_Mdb->t_Order->m_PrimaryKey->Select(m_TradingDay, reqPackage->ReqCancelOrder->AccountID, reqPackage->ReqCancelOrder->ExchangeID,
		reqPackage->ReqCancelOrder->InstrumentID, reqPackage->ReqCancelOrder->OrderID);
	if (order == nullptr)
	{
		order = m_Mdb->t_Order->m_ClientOrderIDUniqueKey->Select(m_TradingDay, reqPackage->ReqCancelOrder->AccountID, reqPackage->ReqCancelOrder->ExchangeID,
			reqPackage->ReqCancelOrder->InstrumentID, reqPackage->ReqCancelOrder->SessionID, reqPackage->ReqCancelOrder->ClientCancelOrderID);
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
void SimExchange::HandleQryOrder(ReqQryOrderPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleQryOrder %s", reqPackage->GetDebugString());
	auto errorID = ErrorNone;
	if (!CheckSessionLogin(reqPackage->SessionID))
	{
		SendRspQryOrder(reqPackage, ErrorSessionNotLogin, true);
		return;
	}
	auto orderRange = m_Mdb->t_Order->m_AccountIDIndex->EqualRange(m_TradingDay, reqPackage->ReqQryOrder->AccountID);
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
void SimExchange::HandleQryTrade(ReqQryTradePackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleQryTrade %s", reqPackage->GetDebugString());
	auto errorID = ErrorNone;
	if (!CheckSessionLogin(reqPackage->SessionID))
	{
		SendRspQryTrade(reqPackage, ErrorSessionNotLogin, true);
		return;
	}
	auto tradeRange = m_Mdb->t_Trade->m_AccountIDIndex->EqualRange(m_TradingDay, reqPackage->ReqQryTrade->AccountID);
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
void SimExchange::HandleQryInstrument(ReqQryInstrumentPackage* reqPackage)
{
	WriteLog(LogLevel::Info, "HandleQryInstrument %s", reqPackage->GetDebugString());
	auto errorID = ErrorNone;
	if (!CheckSessionLogin(reqPackage->SessionID))
	{
		SendRspQryInstrument(reqPackage, ErrorSessionNotLogin, true);
		return;
	}
	m_RspQryInstrumentPackage->Instrument = Allocate<InstrumentField>();
	if (strlen(reqPackage->ReqQryInstrument->ExchangeID) != 0 && strlen(reqPackage->ReqQryInstrument->InstrumentID) != 0)
	{
		auto instrument = m_Mdb->t_Instrument->m_PrimaryKey->Select(reqPackage->ReqQryInstrument->ExchangeID, reqPackage->ReqQryInstrument->InstrumentID);
		SendRspQryInstrument(reqPackage, ErrorNone, true, instrument);
	}
	else if (strlen(reqPackage->ReqQryInstrument->ExchangeID) != 0)
	{
		auto range = m_Mdb->t_Instrument->m_ExchangeIDIndex->EqualRange(reqPackage->ReqQryInstrument->ExchangeID);
		for (auto& it = range.first; it != range.second; )
		{
			auto record = *it;
			SendRspQryInstrument(reqPackage, ErrorNone, ++it == range.second, record);
		}
	}
	else
	{
		auto range = m_Mdb->t_Instrument->m_PrimaryKey->SelectAll();
		for (auto& it = range.first; it != range.second; )
		{
			auto record = *it;
			SendRspQryInstrument(reqPackage, ErrorNone, ++it == range.second, record);
		}
	}
	::Deallocate(m_RspQryInstrumentPackage->Instrument);
	m_RspQryInstrumentPackage->Instrument = nullptr;
}

bool SimExchange::CheckSessionLogin(const SessionIDType& sessionID)
{
	auto accountLoginSession = m_Mdb->t_AccountLoginSession->m_PrimaryKey->Select(sessionID);
	return accountLoginSession != nullptr;
}

void SimExchange::SendRspAccountLogin(ReqAccountLoginPackage* reqPackage, mdb::PrimaryAccount* primaryAccount, int errorID)
{
	auto rspPackage = ::Allocate<RspAccountLoginPackage>();
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
		strcpy(m_RspQryOrderPackage->Order->TradingDay, order->TradingDay);
		strcpy(m_RspQryOrderPackage->Order->AccountID, order->AccountID);
		strcpy(m_RspQryOrderPackage->Order->ExchangeID, order->ExchangeID);
		strcpy(m_RspQryOrderPackage->Order->InstrumentID, order->InstrumentID);
		m_RspQryOrderPackage->Order->ProductClass = order->ProductClass;
		m_RspQryOrderPackage->Order->OrderID = order->OrderID;
		strcpy(m_RspQryOrderPackage->Order->OrderSysID, order->OrderSysID);
		m_RspQryOrderPackage->Order->Direction = order->Direction;
		m_RspQryOrderPackage->Order->OffsetFlag = order->OffsetFlag;
		m_RspQryOrderPackage->Order->OrderPriceType = order->OrderPriceType;
		m_RspQryOrderPackage->Order->Price = order->Price;
		m_RspQryOrderPackage->Order->Volume = order->Volume;
		m_RspQryOrderPackage->Order->VolumeTotal = order->VolumeTotal;
		m_RspQryOrderPackage->Order->VolumeTraded = order->VolumeTraded;
		m_RspQryOrderPackage->Order->VolumeMultiple = order->VolumeMultiple;
		m_RspQryOrderPackage->Order->OrderStatus = order->OrderStatus;
		
		strcpy(m_RspQryOrderPackage->Order->OrderDate, order->OrderDate);
		strcpy(m_RspQryOrderPackage->Order->OrderTime, order->OrderTime);
		strcpy(m_RspQryOrderPackage->Order->CancelDate, order->CancelDate);
		strcpy(m_RspQryOrderPackage->Order->CancelTime, order->CancelTime);
		m_RspQryOrderPackage->Order->SessionID = order->SessionID;
		m_RspQryOrderPackage->Order->ClientOrderID = order->ClientOrderID;
		m_RspQryOrderPackage->Order->RequestID = order->RequestID;
		m_RspQryOrderPackage->Order->FrozenCash = order->FrozenCash;
		m_RspQryOrderPackage->Order->FrozenMargin = order->FrozenMargin;
		m_RspQryOrderPackage->Order->FrozenCommission = order->FrozenCommission;
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
		strcpy(m_RspQryTradePackage->Trade->TradingDay, trade->TradingDay);
		strcpy(m_RspQryTradePackage->Trade->AccountID, trade->AccountID);
		strcpy(m_RspQryTradePackage->Trade->ExchangeID, trade->ExchangeID);
		strcpy(m_RspQryTradePackage->Trade->InstrumentID, trade->InstrumentID);
		m_RspQryTradePackage->Trade->ProductClass = trade->ProductClass;
		m_RspQryTradePackage->Trade->OrderID = trade->OrderID;
		strcpy(m_RspQryTradePackage->Trade->OrderSysID, trade->OrderSysID);
		strcpy(m_RspQryTradePackage->Trade->TradeID, trade->TradeID);
		m_RspQryTradePackage->Trade->Direction = trade->Direction;
		m_RspQryTradePackage->Trade->OffsetFlag = trade->OffsetFlag;
		m_RspQryTradePackage->Trade->Price = trade->Price;
		m_RspQryTradePackage->Trade->Volume = trade->Volume;
		m_RspQryTradePackage->Trade->VolumeMultiple = trade->VolumeMultiple;
		m_RspQryTradePackage->Trade->TradeAmount = trade->TradeAmount;
		m_RspQryTradePackage->Trade->Commission = trade->Commission;
		strcpy(m_RspQryTradePackage->Trade->TradeDate, trade->TradeDate);
		strcpy(m_RspQryTradePackage->Trade->TradeTime, trade->TradeTime);
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
	strcpy(m_RtnOrderPackage->Order->TradingDay, order->TradingDay);
	strcpy(m_RtnOrderPackage->Order->AccountID, order->AccountID);
	strcpy(m_RtnOrderPackage->Order->ExchangeID, order->ExchangeID);
	strcpy(m_RtnOrderPackage->Order->InstrumentID, order->InstrumentID);
	m_RtnOrderPackage->Order->ProductClass = order->ProductClass;
	m_RtnOrderPackage->Order->OrderID = order->OrderID;
	strcpy(m_RtnOrderPackage->Order->OrderSysID, order->OrderSysID);
	m_RtnOrderPackage->Order->Direction = order->Direction;
	m_RtnOrderPackage->Order->OffsetFlag = order->OffsetFlag;
	m_RtnOrderPackage->Order->OrderPriceType = order->OrderPriceType;
	m_RtnOrderPackage->Order->Price = order->Price;
	m_RtnOrderPackage->Order->Volume = order->Volume;
	m_RtnOrderPackage->Order->VolumeTotal = order->VolumeTotal;
	m_RtnOrderPackage->Order->VolumeTraded = order->VolumeTraded;
	m_RtnOrderPackage->Order->VolumeMultiple = order->VolumeMultiple;
	m_RtnOrderPackage->Order->OrderStatus = order->OrderStatus;
	strcpy(m_RtnOrderPackage->Order->OrderDate, order->OrderDate);
	strcpy(m_RtnOrderPackage->Order->OrderTime, order->OrderTime);
	strcpy(m_RtnOrderPackage->Order->CancelDate, order->CancelDate);
	strcpy(m_RtnOrderPackage->Order->CancelTime, order->CancelTime);
	m_RtnOrderPackage->Order->SessionID = order->SessionID;
	m_RtnOrderPackage->Order->ClientOrderID = order->ClientOrderID;
	m_RtnOrderPackage->Order->RequestID = order->RequestID;
	m_RtnOrderPackage->Order->FrozenCash = order->FrozenCash;
	m_RtnOrderPackage->Order->FrozenMargin = order->FrozenMargin;
	m_RtnOrderPackage->Order->FrozenCommission = order->FrozenCommission;

	auto brokerLoginSessionRange = m_Mdb->t_AccountLoginSession->m_AccountIDIndex->EqualRange(order->AccountID);
	for (auto& it = brokerLoginSessionRange.first; it != brokerLoginSessionRange.second; ++it)
	{
		m_RtnOrderPackage->Prepare((*it)->SessionID, false, 0);
		m_TradeFront->Send(m_RtnOrderPackage);
	}
}
void SimExchange::SendRtnTrade(mdb::Trade* trade)
{
	strcpy(m_RtnTradePackage->Trade->TradingDay, trade->TradingDay);
	strcpy(m_RtnTradePackage->Trade->AccountID, trade->AccountID);
	strcpy(m_RtnTradePackage->Trade->ExchangeID, trade->ExchangeID);
	strcpy(m_RtnTradePackage->Trade->InstrumentID, trade->InstrumentID);
	m_RtnTradePackage->Trade->ProductClass = trade->ProductClass;
	m_RtnTradePackage->Trade->OrderID = trade->OrderID;
	strcpy(m_RtnTradePackage->Trade->OrderSysID, trade->OrderSysID);
	strcpy(m_RtnTradePackage->Trade->TradeID, trade->TradeID);
	m_RtnTradePackage->Trade->Direction = trade->Direction;
	m_RtnTradePackage->Trade->OffsetFlag = trade->OffsetFlag;
	m_RtnTradePackage->Trade->Price = trade->Price;
	m_RtnTradePackage->Trade->Volume = trade->Volume;
	m_RtnTradePackage->Trade->VolumeMultiple = trade->VolumeMultiple;
	m_RtnTradePackage->Trade->TradeAmount = trade->TradeAmount;
	m_RtnTradePackage->Trade->Commission = trade->Commission;
	strcpy(m_RtnTradePackage->Trade->TradeDate, trade->TradeDate);
	strcpy(m_RtnTradePackage->Trade->TradeTime, trade->TradeTime);

	auto accountLoginSessionRange = m_Mdb->t_AccountLoginSession->m_AccountIDIndex->EqualRange(trade->AccountID);
	for (auto& it = accountLoginSessionRange.first; it != accountLoginSessionRange.second; ++it)
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
