#include "TraderSpiImpl.h"
#include <Spark/Core/Logger/Logger.h>
#include <Spark/Core/Utility/Utility.h>


namespace QuantTrading::testtraderapi
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
void TraderSpiImpl::OnRspAccountLogin(const RspAccountLoginField* rspAccountLogin, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	TraderSpiMiddle::OnRspAccountLogin(rspAccountLogin, rspInfo, requestID, isLast);
	ReqQryInstrument();
}
void TraderSpiImpl::OnRspAccountLogout(const RspAccountLogoutField* rspAccountLogout, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	TraderSpiMiddle::OnRspAccountLogout(rspAccountLogout, rspInfo, requestID, isLast);
}
void TraderSpiImpl::OnRspInsertOrder(const ReqInsertOrderField* reqSEInsertOrder, const RspInfoField* rspInfo, int requestID, bool isLast)
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
void TraderSpiImpl::OnRspQryInstrument(const InstrumentField* sEInstrument, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	TraderSpiMiddle::OnRspQryInstrument(sEInstrument, rspInfo, requestID, isLast);
	if (m_HasInstrument == false && sEInstrument != nullptr && strcmp(sEInstrument->ExchangeId, "CFFEX") == 0)
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

void TraderSpiImpl::OnRtnOrder(const OrderField* order)
{
	TraderSpiMiddle::OnRtnOrder(order);
}

void TraderSpiImpl::ReqQryOrder()
{
	ReqQryOrderField qryOrder;
	memset(&qryOrder, 0, sizeof(ReqQryOrderField));
	strcpy(qryOrder.AccountId, m_AccountInfo->InvestorId);
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
	ReqInsertOrder(DirectionType::Sell, OffsetFlagType::Open, OrderPriceTypeType::AnyPriceFAK, price, 1);
}
void TraderSpiImpl::ReqAccountLogin()
{
	ReqAccountLoginField brokerLogin;
	memset(&brokerLogin, 0, sizeof(ReqAccountLoginField));
	strcpy(brokerLogin.AccountId, m_AccountInfo->InvestorId);
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
	strcpy(insertOrder.AccountId, m_AccountInfo->InvestorId);
	strcpy(insertOrder.ExchangeId, m_Instrument.ExchangeId);
	strcpy(insertOrder.InstrumentId, m_Instrument.InstrumentId);
	insertOrder.Direction = direction;
	insertOrder.OffsetFlag = offsetFlag;
	insertOrder.OrderPriceType = orderPriceType;
	insertOrder.Price = price;
	insertOrder.Volume = volume;
	insertOrder.ClientOrderId = ++m_MaxClientOrderID;

	m_TraderApi->ReqInsertOrder(&insertOrder, ++m_MaxRequestID);
}
void TraderSpiImpl::ReqCancelOrder(const OrderField* order)
{
	ReqCancelOrderField cancelOrder;
	memset(&cancelOrder, 0, sizeof(ReqCancelOrderField));
	strcpy(cancelOrder.AccountId, order->AccountId);
	strcpy(cancelOrder.ExchangeId, order->ExchangeId);
	strcpy(cancelOrder.InstrumentId, order->InstrumentId);
	cancelOrder.ClientCancelOrderID = ++m_MaxClientOrderID;
	cancelOrder.OrderId = order->OrderId;
	strcpy(cancelOrder.OrderSysId, order->OrderSysId);
	cancelOrder.SessionId = order->SessionId;
	cancelOrder.ClientOrderId = order->ClientOrderId;

	m_TraderApi->ReqCancelOrder(&cancelOrder, ++m_MaxRequestID);
}
}
