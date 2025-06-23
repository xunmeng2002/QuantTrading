#include "SimExchange.h"
#include "InitMdbFromCsv.h"
#include "Error.h"
#include "TimeUtility.h"

using namespace std;
using namespace mdb;

SimExchange::SimExchange(const Config& config)
	:ThreadBase("SimExchange"), m_Mdb(nullptr)
{
	m_Mdb = new mdb::Mdb();
	InitMdbFromCsv::LoadTables(m_Mdb, config.CsvPath.c_str());
}
SimExchange::~SimExchange()
{

}
void SimExchange::Init()
{

}
int SimExchange::ReqSEInsertOrder(ReqSEInsertOrderField* reqInsertOrder, int requestID)
{
	return ErrorNone;
}
int SimExchange::ReqSECancelOrder(ReqSECancelOrderField* reqCancelOrder, int requestID)
{
	return ErrorNone;
}

void SimExchange::Run()
{
	HandlePackages();
}
void SimExchange::HandlePackages()
{
	Package* package = nullptr;
	for (auto i = 0; i < 100; ++i)
	{
		if (m_Packages.empty())
			break;
		package = m_Packages.front();
		switch (package->Head.PackageID)
		{
		case ReqSEBrokerLoginPackage::PackageID:
			HandleBrokerLogin((ReqSEBrokerLoginPackage*)package);
			break;
		case ReqSEInsertOrderPackage::PackageID:
			HandleInsertOrder((ReqSEInsertOrderPackage*)package);
			break;
		case ReqSECancelOrderPackage::PackageID:
			HandleCancelOrder((ReqSECancelOrderPackage*)package);
			break;
		case ReqQrySEOrderPackage::PackageID:
			HandleQryOrder((ReqQrySEOrderPackage*)package);
			break;
		case ReqQrySETradePackage::PackageID:
			HandleQryTrade((ReqQrySETradePackage*)package);
			break;
		case ReqQryInstrumentPackage::PackageID:
			HandleQryInstrument((ReqQryInstrumentPackage*)package);
			break;
		default:
			break;
		}
		package->Free();
	}
}

void SimExchange::HandleBrokerLogin(ReqSEBrokerLoginPackage* reqPackage)
{
	auto errorID = ErrorNone;
	auto broker = m_Mdb->t_SEBroker->m_PrimaryKey->Select(reqPackage->ReqSEBrokerLogin->BrokerID);
	if (broker == nullptr)
	{
		errorID = ErrorBrokerNotExist;
	}
	else if (strcmp(broker->Password, reqPackage->ReqSEBrokerLogin->Password) != 0)
	{
		errorID = ErrorIncorrectPassword;
	}
	else
	{
		auto brokerLoginSession = m_Mdb->t_SEBrokerLoginSession->m_PrimaryKey->Select(reqPackage->SessionID);
		if (brokerLoginSession != nullptr)
		{
			errorID = ErrorSessionAlreadyLogin;
		}
		else
		{
			brokerLoginSession = SEBrokerLoginSession::Allocate();
			memset(brokerLoginSession, 0, sizeof(SEBrokerLoginSession));
			brokerLoginSession->BrokerID = reqPackage->ReqSEBrokerLogin->BrokerID;
			brokerLoginSession->SessionID = reqPackage->SessionID;
			strcpy(brokerLoginSession->IPAddress, reqPackage->IPAddress);
			m_Mdb->t_SEBrokerLoginSession->Insert(brokerLoginSession);
		}
	}
	SendRspBrokerLogin(reqPackage, broker, errorID);
}
void SimExchange::HandleInsertOrder(ReqSEInsertOrderPackage* reqPackage)
{
	auto errorID = ErrorNone;
	auto instrument = m_Mdb->t_SEInstrument->m_PrimaryKey->Select(reqPackage->ReqSEInsertOrder->ExchangeID, reqPackage->ReqSEInsertOrder->InstrumentID);
	if (instrument == nullptr)
	{
		errorID = ErrorInstrumentNotExist;
	}
	else
	{
		errorID = CheckForInsertOrder(reqPackage->ReqSEInsertOrder, instrument);
	}
	SendRspInsertOrder(reqPackage, errorID);
	if (errorID != ErrorNone)
	{
		return;
	}
	auto order = SEOrder::Allocate();
	memset(order, 0, sizeof(SEOrder));
	memcpy(order->TradingDay, m_TradingDay, sizeof(DateType));
	order->BrokerID = reqPackage->ReqSEInsertOrder->BrokerID;
	memcpy(order->AccountID, reqPackage->ReqSEInsertOrder->AccountID, sizeof(AccountIDType));
	memcpy(order->ExchangeID, reqPackage->ReqSEInsertOrder->ExchangeID, sizeof(ExchangeIDType));
	memcpy(order->InstrumentID, reqPackage->ReqSEInsertOrder->InstrumentID, sizeof(InstrumentIDType));
	order->ProductClass = instrument->ProductClass;
	order->OrderID = GetNextOrderID();
	order->Direction = reqPackage->ReqSEInsertOrder->Direction;
	order->OffsetFlag = reqPackage->ReqSEInsertOrder->OffsetFlag;
	order->OrderPriceType = reqPackage->ReqSEInsertOrder->OrderPriceType;
	order->Price = reqPackage->ReqSEInsertOrder->Price;
	order->Volume = reqPackage->ReqSEInsertOrder->Volume;
	order->VolumeTotal = reqPackage->ReqSEInsertOrder->Volume;
	order->VolumeTraded = 0;
	order->VolumeMultiple = instrument->VolumeMultiple;
	order->OrderStatus = OrderStatusType::Inserted;
	memcpy(order->OrderDate, m_TradingDay, sizeof(DateType));
	strcpy(order->OrderTime, GetLocalTime().c_str());
	order->SessionID = reqPackage->SessionID;
	order->ClientOrderID = reqPackage->ReqSEInsertOrder->ClientOrderID;
	m_Mdb->t_SEOrder->Insert(order);

	CheckMatchForOrderQueue(order);
	if (order->VolumeTotal > 0)
	{
		AddOrderToQueue(order);
	}
	if (order->VolumeTraded == 0)
	{
		SendRtnOrder(order);
	}
}
void SimExchange::HandleCancelOrder(ReqSECancelOrderPackage* reqPackage)
{
}
void SimExchange::HandleQryOrder(ReqQrySEOrderPackage* reqPackage)
{
}
void SimExchange::HandleQryTrade(ReqQrySETradePackage* reqPackage)
{
}
void SimExchange::HandleQryInstrument(ReqQryInstrumentPackage* reqPackage)
{
}


int SimExchange::CheckForInsertOrder(ReqSEInsertOrderField* reqInsertOrder, mdb::SEInstrument* instrument)
{
	if (strlen(reqInsertOrder->AccountID) == 0)
		return ErrorAccountNotExist;
	if (reqInsertOrder->Direction != DirectionType::Buy && reqInsertOrder->Direction != DirectionType::Sell)
		return ErrorInvalidDirection;
	if (reqInsertOrder->OffsetFlag != OffsetFlagType::Open && reqInsertOrder->OffsetFlag != OffsetFlagType::Close && reqInsertOrder->OffsetFlag != OffsetFlagType::CloseToday)
		return ErrorInvalidOffsetFlag;
	if (reqInsertOrder->OrderPriceType != OrderPriceTypeType::LimitPrice && reqInsertOrder->OrderPriceType != OrderPriceTypeType::AnyPrice)
		return ErrorInvalidOrderPriceType;
	if (reqInsertOrder->OrderPriceType == OrderPriceTypeType::LimitPrice && (reqInsertOrder->Price > instrument->UpperLimitPrice || reqInsertOrder->Price < instrument->LowerLimitPrice))
		return ErrorInvalidOrderPrice;
	if (reqInsertOrder->Volume <= 0)
		return ErrorInvalidOrderVolume;
	if (reqInsertOrder->OrderPriceType == OrderPriceTypeType::LimitPrice)
	{
		if (instrument->MaxLimitOrderVolume > 0 && reqInsertOrder->Volume > instrument->MaxLimitOrderVolume)
			return ErrorInvalidOrderVolume;
		if (instrument->MinLimitOrderVolume > 0 && reqInsertOrder->Volume < instrument->MinLimitOrderVolume)
			return ErrorInvalidOrderVolume;
	}
	if (reqInsertOrder->OrderPriceType == OrderPriceTypeType::AnyPrice)
	{
		if (instrument->MaxMarketOrderVolume > 0 && reqInsertOrder->Volume > instrument->MaxMarketOrderVolume)
			return ErrorInvalidOrderVolume;
		if (instrument->MinMarketOrderVolume > 0 && reqInsertOrder->Volume < instrument->MinMarketOrderVolume)
			return ErrorInvalidOrderVolume;
	}
	return ErrorNone;
}
void SimExchange::CheckMatchForOrderQueue(mdb::SEOrder* order)
{
	if (order->Direction == DirectionType::Buy)
	{
		auto& queueOrders = m_SellOrders[order->InstrumentID];
		for (auto queueOrder : queueOrders)
		{
			if (!CheckMatchForTwoOrder(order, queueOrder))
			{
				break;
			}
		}
	}
	else
	{
		auto& queueOrders = m_BuyOrders[order->InstrumentID];
		for (auto queueOrder : queueOrders)
		{
			if (!CheckMatchForTwoOrder(order, queueOrder))
			{
				break;
			}
		}
	}
}
bool SimExchange::CheckMatchForTwoOrder(mdb::SEOrder* order, mdb::SEOrder* queueOrder)
{
	if (order->VolumeTotal <= 0)
		return false;
	if (queueOrder->VolumeTotal <= 0)
		return true;
	if (order->OrderPriceType == OrderPriceTypeType::LimitPrice)
	{
		if (order->Direction == DirectionType::Buy && order->Price < queueOrder->Price)
			return false;
		if (order->Direction == DirectionType::Sell && order->Price > queueOrder->Price)
			return false;
	}

	VolumeType matchVolume = 0;
	PriceType matchPrice = 0.0;
	matchVolume = min(order->VolumeTotal, queueOrder->VolumeTotal);
	matchPrice = queueOrder->Price;

	TradeIDType tradeID;
	GetNextTradeID(tradeID);
	Match(queueOrder, matchPrice, matchVolume, tradeID, order->OrderTime);
	Match(order, matchPrice, matchVolume, tradeID, order->OrderTime);
	return true;
}
void SimExchange::Match(mdb::SEOrder* order, const PriceType& price, VolumeType volume, const TradeIDType& tradeID, const TimeType& tradeTime)
{
	order->VolumeTraded += volume;
	order->VolumeTotal -= volume;
	order->OrderStatus = order->VolumeTotal > 0 ? OrderStatusType::PartTraded : OrderStatusType::AllTraded;
	SendRtnOrder(order);

	auto trade = SETrade::Allocate();
	memset(trade, 0, sizeof(SETrade));
	strcpy(trade->TradingDay, m_TradingDay);
	trade->BrokerID = order->BrokerID;
	strcpy(trade->AccountID, order->AccountID);
	strcpy(trade->ExchangeID, order->ExchangeID);
	strcpy(trade->InstrumentID, order->InstrumentID);
	trade->ProductClass = order->ProductClass;
	trade->OrderID = order->OrderID;
	strcpy(trade->TradeID, tradeID);
	trade->Direction = order->Direction;
	trade->OffsetFlag = order->OffsetFlag;
	trade->Price = price;
	trade->Volume = volume;
	trade->VolumeMultiple = order->VolumeMultiple;
	trade->TradeAmount = price * volume * order->VolumeMultiple;;
	trade->Commission = 0;
	strcpy(trade->TradeDate, order->OrderDate);
	strcpy(trade->TradeTime, tradeTime);
	m_Mdb->t_SETrade->Insert(trade);

	SendRtnTrade(trade);
}

void SimExchange::SendRspBrokerLogin(ReqSEBrokerLoginPackage* reqPackage, mdb::SEBroker* broker, int errorID)
{
	m_RspBrokerLoginPackage->Prepare(reqPackage->SessionID, false, reqPackage->Head.MsgSeqNum);
	m_RspBrokerLoginPackage->RspInfo->ErrorID = errorID;
	strcpy(m_RspBrokerLoginPackage->RspInfo->ErrorMsg, GetErrorMessage(errorID));
	
	m_RspBrokerLoginPackage->RspSEBrokerLogin->BrokerID = reqPackage->ReqSEBrokerLogin->BrokerID;
	strcpy(m_RspBrokerLoginPackage->RspSEBrokerLogin->BrokerName, broker->BrokerName);
	m_RspBrokerLoginPackage->RspSEBrokerLogin->SessionID = reqPackage->SessionID;
	strcpy(m_RspBrokerLoginPackage->RspSEBrokerLogin->IPAddress, reqPackage->IPAddress);

	m_TradeFront->Send(m_RspBrokerLoginPackage);
}
void SimExchange::SendRspInsertOrder(ReqSEInsertOrderPackage* reqPackage, int errorID)
{
	m_RspInsertOrderPackage->Prepare(reqPackage->SessionID, false, reqPackage->Head.MsgSeqNum);
	m_RspInsertOrderPackage->RspInfo->ErrorID = errorID;
	strcpy(m_RspInsertOrderPackage->RspInfo->ErrorMsg, GetErrorMessage(errorID));
	memcpy(m_RspInsertOrderPackage->ReqSEInsertOrder, reqPackage->ReqSEInsertOrder, sizeof(ReqSEInsertOrderField));
	m_TradeFront->Send(m_RspInsertOrderPackage);
}
void SimExchange::SendRspCancelOrder(ReqSECancelOrderPackage* reqPackage, int errorID)
{
	m_RspCancelOrderPackage->Prepare(reqPackage->SessionID, false, errorID);
	m_RspCancelOrderPackage->RspInfo->ErrorID = errorID;
	strcpy(m_RspCancelOrderPackage->RspInfo->ErrorMsg, GetErrorMessage(errorID));
	memcpy(m_RspCancelOrderPackage->ReqSECancelOrder, reqPackage->ReqSECancelOrder, sizeof(ReqSEInsertOrderField));
	m_TradeFront->Send(m_RspCancelOrderPackage);
}
void SimExchange::SendRtnOrder(mdb::SEOrder* order)
{
	strcpy(m_RtnOrderPackage->SEOrder->TradingDay, order->TradingDay);
	m_RtnOrderPackage->SEOrder->BrokerID = order->BrokerID;
	strcpy(m_RtnOrderPackage->SEOrder->AccountID, order->AccountID);
	strcpy(m_RtnOrderPackage->SEOrder->ExchangeID, order->ExchangeID);
	strcpy(m_RtnOrderPackage->SEOrder->InstrumentID, order->InstrumentID);
	m_RtnOrderPackage->SEOrder->ProductClass = order->ProductClass;
	m_RtnOrderPackage->SEOrder->OrderID = order->OrderID;
	m_RtnOrderPackage->SEOrder->Direction = order->Direction;
	m_RtnOrderPackage->SEOrder->OffsetFlag = order->OffsetFlag;
	m_RtnOrderPackage->SEOrder->OrderPriceType = order->OrderPriceType;
	m_RtnOrderPackage->SEOrder->Price = order->Price;
	m_RtnOrderPackage->SEOrder->Volume = order->Volume;
	m_RtnOrderPackage->SEOrder->VolumeTotal = order->VolumeTotal;
	m_RtnOrderPackage->SEOrder->VolumeTraded = order->VolumeTraded;
	m_RtnOrderPackage->SEOrder->VolumeMultiple = order->VolumeMultiple;
	m_RtnOrderPackage->SEOrder->OrderStatus = order->OrderStatus;
	strcpy(m_RtnOrderPackage->SEOrder->OrderDate, order->OrderDate);
	strcpy(m_RtnOrderPackage->SEOrder->OrderTime, order->OrderTime);
	strcpy(m_RtnOrderPackage->SEOrder->CancelDate, order->CancelDate);
	strcpy(m_RtnOrderPackage->SEOrder->CancelTime, order->CancelTime);
	m_RtnOrderPackage->SEOrder->SessionID = order->SessionID;
	m_RtnOrderPackage->SEOrder->ClientOrderID = order->ClientOrderID;

	auto brokerLoginSessionRange = m_Mdb->t_SEBrokerLoginSession->m_BrokerIDIndex->EqualRange(order->BrokerID);
	for (auto& it = brokerLoginSessionRange.first; it != brokerLoginSessionRange.second; ++it)
	{
		m_RtnOrderPackage->Prepare((*it)->SessionID, false, 0);
		m_TradeFront->Send(m_RtnOrderPackage);
	}
}
void SimExchange::SendRtnTrade(mdb::SETrade* trade)
{
	strcpy(m_RtnTradePackage->SETrade->TradingDay, trade->TradingDay);
	m_RtnTradePackage->SETrade->BrokerID = trade->BrokerID;
	strcpy(m_RtnTradePackage->SETrade->AccountID, trade->AccountID);
	strcpy(m_RtnTradePackage->SETrade->ExchangeID, trade->ExchangeID);
	strcpy(m_RtnTradePackage->SETrade->InstrumentID, trade->InstrumentID);
	m_RtnTradePackage->SETrade->ProductClass = trade->ProductClass;
	m_RtnTradePackage->SETrade->OrderID = trade->OrderID;
	strcpy(m_RtnTradePackage->SETrade->TradeID, trade->TradeID);
	m_RtnTradePackage->SETrade->Direction = trade->Direction;
	m_RtnTradePackage->SETrade->OffsetFlag = trade->OffsetFlag;
	m_RtnTradePackage->SETrade->Price = trade->Price;
	m_RtnTradePackage->SETrade->Volume = trade->Volume;
	m_RtnTradePackage->SETrade->VolumeMultiple = trade->VolumeMultiple;
	m_RtnTradePackage->SETrade->TradeAmount = trade->TradeAmount;
	m_RtnTradePackage->SETrade->Commission = trade->Commission;
	strcpy(m_RtnTradePackage->SETrade->TradeDate, trade->TradeDate);
	strcpy(m_RtnTradePackage->SETrade->TradeTime, trade->TradeTime);

	auto brokerLoginSessionRange = m_Mdb->t_SEBrokerLoginSession->m_BrokerIDIndex->EqualRange(trade->BrokerID);
	for (auto& it = brokerLoginSessionRange.first; it != brokerLoginSessionRange.second; ++it)
	{
		m_RtnTradePackage->Prepare((*it)->SessionID, false, 0);
		m_TradeFront->Send(m_RtnTradePackage);
	}
}

OrderIDType SimExchange::GetNextOrderID()
{
	return ++m_MaxOrderID;
}
void SimExchange::GetNextTradeID(TradeIDType& tradeID)
{
	sprintf(tradeID, "%s%08d", m_TradingDay, ++m_MaxTradeID);
}
void SimExchange::AddOrderToQueue(mdb::SEOrder* order)
{
	if (order->OrderPriceType == OrderPriceTypeType::LimitPrice)
	{
		if (order->Direction == DirectionType::Buy)
		{
			m_BuyOrders[order->InstrumentID].insert(order);
		}
		else
		{
			m_SellOrders[order->InstrumentID].insert(order);
		}
	}
	else
	{
		if (order->Direction == DirectionType::Buy)
		{
			m_MarketBuyOrders[order->InstrumentID].insert(order);
		}
		else
		{
			m_MarketSellOrders[order->InstrumentID].insert(order);
		}
	}
}

