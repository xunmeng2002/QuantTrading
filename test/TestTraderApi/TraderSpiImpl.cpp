#include "TraderSpiImpl.h"
#include <Spark/Core/Logger/Logger.h>
#include <Spark/Core/Utility/Utility.h>


namespace QuantTrading::TestTraderApi
{
TraderSpiImpl::TraderSpiImpl(TraderApi* api)
	:traderApi_(api), accountInfo_(nullptr), instrument_{}, hasInstrument_(false), maxRequestId_(0), maxClientOrderId_(0), orderCount_(0),
	InitStatus(false), Finished(false)
{
}
TraderSpiImpl::~TraderSpiImpl()
{
}
void TraderSpiImpl::SetAccountInfo(AccountInfo* accountInfo)
{
	accountInfo_ = accountInfo;
}
void TraderSpiImpl::OnConnected()
{
	TraderSpiMiddle::OnConnected();
	ReqAccountLogin();
}
void TraderSpiImpl::OnRspAccountLogin(const RspAccountLoginField* rspAccountLogin, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	TraderSpiMiddle::OnRspAccountLogin(rspAccountLogin, rspInfo, requestId, isLast);
	ReqQryInstrument();
}
void TraderSpiImpl::OnRspAccountLogout(const RspAccountLogoutField* rspAccountLogout, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	TraderSpiMiddle::OnRspAccountLogout(rspAccountLogout, rspInfo, requestId, isLast);
}
void TraderSpiImpl::OnRspInsertOrder(const ReqInsertOrderField* reqSEInsertOrder, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	TraderSpiMiddle::OnRspInsertOrder(reqSEInsertOrder, rspInfo, requestId, isLast);
	if (++orderCount_ < 10000 && orderCount_ % 10 == 0)
	{
		ReqInsertOrders();
	}
	else if (orderCount_ >= 10000)
	{
		Finished = true;
	}
}
void TraderSpiImpl::OnRspQryInstrument(const InstrumentField* sEInstrument, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	TraderSpiMiddle::OnRspQryInstrument(sEInstrument, rspInfo, requestId, isLast);
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

void TraderSpiImpl::OnRtnOrder(const OrderField* order)
{
	TraderSpiMiddle::OnRtnOrder(order);
}

void TraderSpiImpl::ReqQryOrder()
{
	ReqQryOrderField qryOrder;
	memset(&qryOrder, 0, sizeof(ReqQryOrderField));
	strcpy(qryOrder.AccountId, accountInfo_->InvestorId);
	traderApi_->ReqQryOrder(&qryOrder, ++maxRequestId_);
}
void TraderSpiImpl::ReqInsertOrders()
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
void TraderSpiImpl::ReqAccountLogin()
{
	ReqAccountLoginField brokerLogin;
	memset(&brokerLogin, 0, sizeof(ReqAccountLoginField));
	strcpy(brokerLogin.AccountId, accountInfo_->InvestorId);
	strcpy(brokerLogin.Password, accountInfo_->Password);
	traderApi_->ReqAccountLogin(&brokerLogin, ++maxRequestId_);
}
void TraderSpiImpl::ReqQryInstrument()
{
	ReqQryInstrumentField qryInstrument;
	memset(&qryInstrument, 0, sizeof(ReqQryInstrumentField));
	traderApi_->ReqQryInstrument(&qryInstrument, ++maxRequestId_);
}
void TraderSpiImpl::ReqInsertOrder(DirectionType direction, OffsetFlagType offsetFlag, OrderPriceTypeType orderPriceType, PriceType price, VolumeType volume)
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

	traderApi_->ReqInsertOrder(&insertOrder, ++maxRequestId_);
}
void TraderSpiImpl::ReqCancelOrder(const OrderField* order)
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

	traderApi_->ReqCancelOrder(&cancelOrder, ++maxRequestId_);
}
}
