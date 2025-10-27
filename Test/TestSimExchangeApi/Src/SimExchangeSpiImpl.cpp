#include "SimExchangeSpiImpl.h"
#include "Utility.h"
#include "Logger.h"


SimExchangeSpiImpl::SimExchangeSpiImpl(SimExchangeApi* api)
	:m_SimExchangeApi(api), m_MaxRequestID(0), m_MaxClientOrderID(0), m_InitStatus(false), m_Finished(false), m_OrderCount(0)
{
	strcpy(m_AccountID, "18019749894");
	m_SEInstrument = new SEInstrumentField();
}
SimExchangeSpiImpl::~SimExchangeSpiImpl()
{
}
void SimExchangeSpiImpl::OnConnected()
{
	SimExchangeSpiMiddle::OnConnected();
	ReqBrokerLogin();
}
void SimExchangeSpiImpl::OnRspSEBrokerLogin(RspSEBrokerLoginField* rspSEBrokerLogin, RspInfoField* rspInfo, int requestID, bool isLast)
{
	SimExchangeSpiMiddle::OnRspSEBrokerLogin(rspSEBrokerLogin, rspInfo, requestID, isLast);
	ReqQryInstrument();
}
void SimExchangeSpiImpl::OnRspSEInsertOrder(ReqSEInsertOrderField* reqSEInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast)
{
	SimExchangeSpiMiddle::OnRspSEInsertOrder(reqSEInsertOrder, rspInfo, requestID, isLast);
	if (++m_OrderCount < 10000 && m_OrderCount % 10 == 0)
	{
		ReqInsertOrders();
	}
	else if (m_OrderCount >= 10000)
	{
		m_Finished = true;
	}
}
void SimExchangeSpiImpl::OnRspQrySEInstrument(SEInstrumentField* sEInstrument, RspInfoField* rspInfo, int requestID, bool isLast)
{
	SimExchangeSpiMiddle::OnRspQrySEInstrument(sEInstrument, rspInfo, requestID, isLast);
	if (isLast && sEInstrument != nullptr)
	{
		memcpy(m_SEInstrument, sEInstrument, sizeof(SEInstrumentField));
		m_InitStatus = true;
		ReqInsertOrders();
	}
}

void SimExchangeSpiImpl::OnRtnSEOrder(SEOrderField* sEOrder)
{
	SimExchangeSpiMiddle::OnRtnSEOrder(sEOrder);
}

void SimExchangeSpiImpl::ReqQryOrder()
{
	ReqQrySEOrderField qryOrder;
	strcpy(qryOrder.AccountID, m_AccountID);
	m_SimExchangeApi->ReqQrySEOrder(&qryOrder, ++m_MaxRequestID);
}
void SimExchangeSpiImpl::ReqInsertOrders()
{
	//if (m_OrderCount % 100 == 0)
	//{
	//	WriteLog(LogLevel::Warning, "ReqInsertOrders OrderCount:%d", m_OrderCount);
	//}
	auto price = (m_SEInstrument->UpperLimitPrice + m_SEInstrument->LowerLimitPrice) / 2;
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
void SimExchangeSpiImpl::ReqBrokerLogin()
{
	ReqSEBrokerLoginField brokerLogin;
	brokerLogin.BrokerID = m_BrokerID;
	strcpy(brokerLogin.Password, "123456");
	m_SimExchangeApi->ReqSEBrokerLogin(&brokerLogin, ++m_MaxRequestID);
}
void SimExchangeSpiImpl::ReqQryInstrument()
{
	ReqQrySEInstrumentField qryInstrument;
	memset(&qryInstrument, 0, sizeof(ReqQrySEInstrumentField));
	m_SimExchangeApi->ReqQrySEInstrument(&qryInstrument, ++m_MaxRequestID);
}
void SimExchangeSpiImpl::ReqInsertOrder(DirectionType direction, OffsetFlagType offsetFlag, OrderPriceTypeType orderPriceType, PriceType price, VolumeType volume)
{
	ReqSEInsertOrderField insertOrder;
	insertOrder.BrokerID = m_BrokerID;
	strcpy(insertOrder.AccountID, m_AccountID);
	strcpy(insertOrder.ExchangeID, m_SEInstrument->ExchangeID);
	strcpy(insertOrder.InstrumentID, m_SEInstrument->InstrumentID);
	insertOrder.Direction = direction;
	insertOrder.OffsetFlag = offsetFlag;
	insertOrder.OrderPriceType = orderPriceType;
	insertOrder.Price = price;
	insertOrder.Volume = volume;
	insertOrder.ClientOrderID = ++m_MaxClientOrderID;

	m_SimExchangeApi->ReqSEInsertOrder(&insertOrder, ++m_MaxRequestID);
}
void SimExchangeSpiImpl::ReqCancelOrder(SEOrderField* order)
{
	ReqSECancelOrderField cancelOrder;
	cancelOrder.BrokerID = order->BrokerID;
	strcpy(cancelOrder.AccountID, order->AccountID);
	strcpy(cancelOrder.ExchangeID, order->ExchangeID);
	strcpy(cancelOrder.InstrumentID, order->InstrumentID);
	cancelOrder.CancelOrderID = ++m_MaxClientOrderID;
	cancelOrder.OrderID = order->OrderID;
	cancelOrder.ClientOrderID = order->ClientOrderID;
	cancelOrder.SessionID = order->SessionID;

	m_SimExchangeApi->ReqSECancelOrder(&cancelOrder, ++m_MaxRequestID);
}

