#include "TraderSpiImpl.h"
#include <Spark/Core/Logger/Logger.h>
#include <Spark/Core/Utility/Utility.h>


namespace quanttrading::testtraderapi
{
TraderSpiImpl::TraderSpiImpl(TraderApi* api)
	:m_TraderApi(api), m_AccountInfo(nullptr), m_Instrument{}, m_HasInstrument(false), m_MaxRequestID(0), m_MaxClientOrderID(0), m_OrderCount(0),
	m_InitStatus(false), m_Finished(false)
{
}
TraderSpiImpl::~TraderSpiImpl()
{
}
void TraderSpiImpl::SetAccountInfo(AccountInfo* accountInfo)
{
	m_AccountInfo = accountInfo;
}
void TraderSpiImpl::OnConnected()
{
	TraderSpiMiddle::OnConnected();
	ReqAccountLogin();
}
void TraderSpiImpl::OnRspAccountLogin(RspAccountLoginField* rspAccountLogin, RspInfoField* rspInfo, int requestID, bool isLast)
{
	TraderSpiMiddle::OnRspAccountLogin(rspAccountLogin, rspInfo, requestID, isLast);
	ReqQryInstrument();
}
void TraderSpiImpl::OnRspAccountLogout(RspAccountLogoutField* rspAccountLogout, RspInfoField* rspInfo, int requestID, bool isLast)
{
	TraderSpiMiddle::OnRspAccountLogout(rspAccountLogout, rspInfo, requestID, isLast);
}
void TraderSpiImpl::OnRspInsertOrder(ReqInsertOrderField* reqSEInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast)
{
	TraderSpiMiddle::OnRspInsertOrder(reqSEInsertOrder, rspInfo, requestID, isLast);
	if (++m_OrderCount < 10000 && m_OrderCount % 10 == 0)
	{
		ReqInsertOrders();
	}
	else if (m_OrderCount >= 10000)
	{
		m_Finished = true;
	}
}
void TraderSpiImpl::OnRspQryInstrument(InstrumentField* sEInstrument, RspInfoField* rspInfo, int requestID, bool isLast)
{
	TraderSpiMiddle::OnRspQryInstrument(sEInstrument, rspInfo, requestID, isLast);
	if (m_HasInstrument == false && sEInstrument != nullptr && strcmp(sEInstrument->ExchangeID, "CFFEX") == 0)
	{
		m_Instrument = *sEInstrument;
		m_HasInstrument = true;
	}
	if (isLast)
	{
		m_InitStatus = true;
		if (m_HasInstrument)
		{
			ReqInsertOrders();
		}
		else
		{
			m_Finished = true;
		}
	}
}

void TraderSpiImpl::OnRtnOrder(OrderField* order)
{
	TraderSpiMiddle::OnRtnOrder(order);
}

void TraderSpiImpl::ReqQryOrder()
{
	ReqQryOrderField qryOrder;
	memset(&qryOrder, 0, sizeof(ReqQryOrderField));
	strcpy(qryOrder.AccountID, m_AccountInfo->InvestorID);
	m_TraderApi->ReqQryOrder(&qryOrder, ++m_MaxRequestID);
}
void TraderSpiImpl::ReqInsertOrders()
{
	//if (m_OrderCount % 100 == 0)
	//{
	//	WriteLog(LogLevel::Warning, "ReqInsertOrders OrderCount:%d", m_OrderCount);
	//}
	auto price = 3000.0;
	ReqInsertOrder(DirectionType::Buy, OffsetFlagType::Open, OrderPriceTypeType::LimitPrice, price, 1);
	ReqInsertOrder(DirectionType::Buy, OffsetFlagType::Open, OrderPriceTypeType::LimitPrice, price - 1, 1);
	ReqInsertOrder(DirectionType::Buy, OffsetFlagType::Open, OrderPriceTypeType::LimitPrice, price + 1, 1);
	ReqInsertOrder(DirectionType::Buy, OffsetFlagType::Open, OrderPriceTypeType::LimitPrice, price - 5, 1);
	ReqInsertOrder(DirectionType::Buy, OffsetFlagType::Open, OrderPriceTypeType::LimitPrice, price, 1);
	ReqInsertOrder(DirectionType::Sell, OffsetFlagType::Open, OrderPriceTypeType::LimitPrice, price, 1);
	ReqInsertOrder(DirectionType::Sell, OffsetFlagType::Open, OrderPriceTypeType::LimitPrice, price + 1, 1);
	ReqInsertOrder(DirectionType::Sell, OffsetFlagType::Open, OrderPriceTypeType::LimitPrice, price - 1, 1);
	ReqInsertOrder(DirectionType::Sell, OffsetFlagType::Open, OrderPriceTypeType::LimitPrice, price + 5, 1);
	ReqInsertOrder(DirectionType::Sell, OffsetFlagType::Open, OrderPriceTypeType::AnyPrice, price, 1);
}
void TraderSpiImpl::ReqAccountLogin()
{
	ReqAccountLoginField brokerLogin;
	memset(&brokerLogin, 0, sizeof(ReqAccountLoginField));
	strcpy(brokerLogin.AccountID, m_AccountInfo->InvestorID);
	strcpy(brokerLogin.Password, m_AccountInfo->Password);
	m_TraderApi->ReqAccountLogin(&brokerLogin, ++m_MaxRequestID);
}
void TraderSpiImpl::ReqQryInstrument()
{
	ReqQryInstrumentField qryInstrument;
	memset(&qryInstrument, 0, sizeof(ReqQryInstrumentField));
	m_TraderApi->ReqQryInstrument(&qryInstrument, ++m_MaxRequestID);
}
void TraderSpiImpl::ReqInsertOrder(DirectionType direction, OffsetFlagType offsetFlag, OrderPriceTypeType orderPriceType, PriceType price, VolumeType volume)
{
	ReqInsertOrderField insertOrder;
	memset(&insertOrder, 0, sizeof(ReqInsertOrderField));
	strcpy(insertOrder.AccountID, m_AccountInfo->InvestorID);
	strcpy(insertOrder.ExchangeID, m_Instrument.ExchangeID);
	strcpy(insertOrder.InstrumentID, m_Instrument.InstrumentID);
	insertOrder.Direction = direction;
	insertOrder.OffsetFlag = offsetFlag;
	insertOrder.OrderPriceType = orderPriceType;
	insertOrder.Price = price;
	insertOrder.Volume = volume;
	insertOrder.ClientOrderID = ++m_MaxClientOrderID;

	m_TraderApi->ReqInsertOrder(&insertOrder, ++m_MaxRequestID);
}
void TraderSpiImpl::ReqCancelOrder(OrderField* order)
{
	ReqCancelOrderField cancelOrder;
	memset(&cancelOrder, 0, sizeof(ReqCancelOrderField));
	strcpy(cancelOrder.AccountID, order->AccountID);
	strcpy(cancelOrder.ExchangeID, order->ExchangeID);
	strcpy(cancelOrder.InstrumentID, order->InstrumentID);
	cancelOrder.ClientCancelOrderID = ++m_MaxClientOrderID;
	cancelOrder.OrderID = order->OrderID;
	strcpy(cancelOrder.OrderSysID, order->OrderSysID);
	cancelOrder.SessionID = order->SessionID;
	cancelOrder.ClientOrderID = order->ClientOrderID;

	m_TraderApi->ReqCancelOrder(&cancelOrder, ++m_MaxRequestID);
}
}
