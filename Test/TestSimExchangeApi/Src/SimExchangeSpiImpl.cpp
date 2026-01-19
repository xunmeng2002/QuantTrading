#include "SimExchangeSpiImpl.h"
#include "Utility.h"
#include "Logger.h"


SimExchangeSpiImpl::SimExchangeSpiImpl(SimExchangeApi* api)
	:m_SimExchangeApi(api), m_AccountInfo(nullptr), m_Instrument(nullptr), m_MaxRequestID(0), m_MaxClientOrderID(0), m_OrderCount(0), 
	m_InitStatus(false), m_Finished(false)
{
}
SimExchangeSpiImpl::~SimExchangeSpiImpl()
{
}
void SimExchangeSpiImpl::SetAccountInfo(AccountInfo* accountInfo)
{
	m_AccountInfo = accountInfo;
}
void SimExchangeSpiImpl::OnConnected()
{
	SimExchangeSpiMiddle::OnConnected();
	ReqAccountLogin();
}
void SimExchangeSpiImpl::OnRspAccountLogin(RspAccountLoginField* rspAccountLogin, RspInfoField* rspInfo, int requestID, bool isLast)
{
	SimExchangeSpiMiddle::OnRspAccountLogin(rspAccountLogin, rspInfo, requestID, isLast);
	ReqQryInstrument();
}
void SimExchangeSpiImpl::OnRspAccountLogout(RspAccountLogoutField* rspAccountLogout, RspInfoField* rspInfo, int requestID, bool isLast)
{
	SimExchangeSpiMiddle::OnRspAccountLogout(rspAccountLogout, rspInfo, requestID, isLast);
}
void SimExchangeSpiImpl::OnRspInsertOrder(ReqInsertOrderField* reqSEInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast)
{
	SimExchangeSpiMiddle::OnRspInsertOrder(reqSEInsertOrder, rspInfo, requestID, isLast);
	if (++m_OrderCount < 10000 && m_OrderCount % 10 == 0)
	{
		ReqInsertOrders();
	}
	else if (m_OrderCount >= 10000)
	{
		m_Finished = true;
	}
}
void SimExchangeSpiImpl::OnRspQryInstrument(InstrumentField* sEInstrument, RspInfoField* rspInfo, int requestID, bool isLast)
{
	SimExchangeSpiMiddle::OnRspQryInstrument(sEInstrument, rspInfo, requestID, isLast);
	if (m_Instrument == nullptr && strcmp(sEInstrument->ExchangeID, "CFFEX") == 0)
	{
		m_Instrument = new InstrumentField();
		memcpy(m_Instrument, sEInstrument, sizeof(InstrumentField));
	}
	if (isLast)
	{
		m_InitStatus = true;
		ReqInsertOrders();
	}
}

void SimExchangeSpiImpl::OnRtnOrder(OrderField* order)
{
	SimExchangeSpiMiddle::OnRtnOrder(order);
}

void SimExchangeSpiImpl::ReqQryOrder()
{
	ReqQryOrderField qryOrder;
	strcpy(qryOrder.AccountID, m_AccountInfo->InvestorID);
	m_SimExchangeApi->ReqQryOrder(&qryOrder, ++m_MaxRequestID);
}
void SimExchangeSpiImpl::ReqInsertOrders()
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
void SimExchangeSpiImpl::ReqAccountLogin()
{
	ReqAccountLoginField brokerLogin;
	strcpy(brokerLogin.AccountID, m_AccountInfo->InvestorID);
	strcpy(brokerLogin.Password, m_AccountInfo->Password);
	m_SimExchangeApi->ReqAccountLogin(&brokerLogin, ++m_MaxRequestID);
}
void SimExchangeSpiImpl::ReqQryInstrument()
{
	ReqQryInstrumentField qryInstrument;
	memset(&qryInstrument, 0, sizeof(ReqQryInstrumentField));
	m_SimExchangeApi->ReqQryInstrument(&qryInstrument, ++m_MaxRequestID);
}
void SimExchangeSpiImpl::ReqInsertOrder(DirectionType direction, OffsetFlagType offsetFlag, OrderPriceTypeType orderPriceType, PriceType price, VolumeType volume)
{
	ReqInsertOrderField insertOrder;
	strcpy(insertOrder.AccountID, m_AccountInfo->InvestorID);
	strcpy(insertOrder.ExchangeID, m_Instrument->ExchangeID);
	strcpy(insertOrder.InstrumentID, m_Instrument->InstrumentID);
	insertOrder.Direction = direction;
	insertOrder.OffsetFlag = offsetFlag;
	insertOrder.OrderPriceType = orderPriceType;
	insertOrder.Price = price;
	insertOrder.Volume = volume;
	insertOrder.ClientOrderID = ++m_MaxClientOrderID;

	m_SimExchangeApi->ReqInsertOrder(&insertOrder, ++m_MaxRequestID);
}
void SimExchangeSpiImpl::ReqCancelOrder(OrderField* order)
{
	ReqCancelOrderField cancelOrder;
	strcpy(cancelOrder.AccountID, order->AccountID);
	strcpy(cancelOrder.ExchangeID, order->ExchangeID);
	strcpy(cancelOrder.InstrumentID, order->InstrumentID);
	cancelOrder.ClientCancelOrderID = ++m_MaxClientOrderID;
	cancelOrder.OrderID = order->OrderID;
	strcpy(cancelOrder.OrderSysID, order->OrderSysID);
	cancelOrder.SessionID = order->SessionID;
	cancelOrder.ClientOrderID = order->ClientOrderID;

	m_SimExchangeApi->ReqCancelOrder(&cancelOrder, ++m_MaxRequestID);
}

