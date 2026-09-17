#include "SimExchangeSpiImpl.h"
#include <Spark/Core/Logger/Logger.h>
#include <Spark/Core/Utility/Utility.h>


namespace QuantTrading::TestSimExchangeApi
{
SimExchangeSpiImpl::SimExchangeSpiImpl(SimExchangeApi* api)
	:simExchangeApi_(api), accountInfo_(nullptr), instrument_{}, hasInstrument_(false), maxRequestId_(0), maxClientOrderId_(0), orderCount_(0),
	InitStatus(false), Finished(false)
{
}
SimExchangeSpiImpl::~SimExchangeSpiImpl()
{
}
void SimExchangeSpiImpl::SetAccountInfo(AccountInfo* accountInfo)
{
	accountInfo_ = accountInfo;
}
void SimExchangeSpiImpl::OnConnected()
{
	SimExchangeSpiMiddle::OnConnected();
	ReqAccountLogin();
}
void SimExchangeSpiImpl::OnRspAccountLogin(const RspAccountLoginField* rspAccountLogin, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	SimExchangeSpiMiddle::OnRspAccountLogin(rspAccountLogin, rspInfo, requestId, isLast);
	ReqQryInstrument();
}
void SimExchangeSpiImpl::OnRspAccountLogout(const RspAccountLogoutField* rspAccountLogout, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	SimExchangeSpiMiddle::OnRspAccountLogout(rspAccountLogout, rspInfo, requestId, isLast);
}
void SimExchangeSpiImpl::OnRspInsertOrder(const ReqInsertOrderField* reqSEInsertOrder, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	SimExchangeSpiMiddle::OnRspInsertOrder(reqSEInsertOrder, rspInfo, requestId, isLast);
	if (++orderCount_ < 10000 && orderCount_ % 10 == 0)
	{
		ReqInsertOrders();
	}
	else if (orderCount_ >= 10000)
	{
		Finished = true;
	}
}
void SimExchangeSpiImpl::OnRspQryInstrument(const InstrumentField* sEInstrument, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	SimExchangeSpiMiddle::OnRspQryInstrument(sEInstrument, rspInfo, requestId, isLast);
	if (hasInstrument_ == false && sEInstrument != nullptr && strcmp(sEInstrument->ExchangeId, "CFFEX") == 0)
	{
		instrument_ = *sEInstrument;
		hasInstrument_ = true;
	}
	if (isLast)
	{
		InitStatus = true;
		if (hasInstrument_)
		{
			ReqInsertOrders();
		}
		else
		{
			Finished = true;
		}
	}
}

void SimExchangeSpiImpl::OnRtnOrder(const OrderField* order)
{
	SimExchangeSpiMiddle::OnRtnOrder(order);
}

void SimExchangeSpiImpl::ReqQryOrder()
{
	ReqQryOrderField qryOrder;
	memset(&qryOrder, 0, sizeof(ReqQryOrderField));
	strcpy(qryOrder.AccountId, accountInfo_->InvestorId);
	simExchangeApi_->ReqQryOrder(&qryOrder, ++maxRequestId_);
}
void SimExchangeSpiImpl::ReqInsertOrders()
{
	//if (orderCount_ % 100 == 0)
	//{
	//	WriteLog(LogLevel::Warning, "ReqInsertOrders OrderCount:%d", orderCount_);
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
void SimExchangeSpiImpl::ReqAccountLogin()
{
	ReqAccountLoginField brokerLogin;
	memset(&brokerLogin, 0, sizeof(ReqAccountLoginField));
	strcpy(brokerLogin.AccountId, accountInfo_->InvestorId);
	strcpy(brokerLogin.Password, accountInfo_->Password);
	simExchangeApi_->ReqAccountLogin(&brokerLogin, ++maxRequestId_);
}
void SimExchangeSpiImpl::ReqQryInstrument()
{
	ReqQryInstrumentField qryInstrument;
	memset(&qryInstrument, 0, sizeof(ReqQryInstrumentField));
	simExchangeApi_->ReqQryInstrument(&qryInstrument, ++maxRequestId_);
}
void SimExchangeSpiImpl::ReqInsertOrder(DirectionType direction, OffsetFlagType offsetFlag, OrderPriceTypeType orderPriceType, PriceType price, VolumeType volume)
{
	ReqInsertOrderField insertOrder;
	memset(&insertOrder, 0, sizeof(ReqInsertOrderField));
	strcpy(insertOrder.AccountId, accountInfo_->InvestorId);
	strcpy(insertOrder.ExchangeId, instrument_.ExchangeId);
	strcpy(insertOrder.InstrumentId, instrument_.InstrumentId);
	insertOrder.Direction = direction;
	insertOrder.OffsetFlag = offsetFlag;
	insertOrder.OrderPriceType = orderPriceType;
	insertOrder.Price = price;
	insertOrder.Volume = volume;
	insertOrder.ClientOrderId = ++maxClientOrderId_;

	simExchangeApi_->ReqInsertOrder(&insertOrder, ++maxRequestId_);
}
void SimExchangeSpiImpl::ReqCancelOrder(const OrderField* order)
{
	ReqCancelOrderField cancelOrder;
	memset(&cancelOrder, 0, sizeof(ReqCancelOrderField));
	strcpy(cancelOrder.AccountId, order->AccountId);
	strcpy(cancelOrder.ExchangeId, order->ExchangeId);
	strcpy(cancelOrder.InstrumentId, order->InstrumentId);
	cancelOrder.ClientCancelOrderId = ++maxClientOrderId_;
	cancelOrder.OrderId = order->OrderId;
	strcpy(cancelOrder.OrderSysId, order->OrderSysId);
	cancelOrder.SessionId = order->SessionId;
	cancelOrder.ClientOrderId = order->ClientOrderId;

	simExchangeApi_->ReqCancelOrder(&cancelOrder, ++maxRequestId_);
}
}

