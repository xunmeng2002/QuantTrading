#include "BackTestSpiImpl.h"
#include <Spark/Core/Logger/Logger.h>
#include <string.h>

namespace QuantTrading::TestBackTest
{
BackTestSpiImpl::BackTestSpiImpl(BackTestApi* backTestApi, const Config& config)
	:backTestApi_(backTestApi), lastOrderTickMd_(nullptr), lastOrderBarMd_(nullptr), maxRequestId_(0), maxClientOrderId_(0)
{
	strcpy(accountId_, config.AccountId.c_str());
	strcpy(exchangeId_, config.ExchangeId.c_str());
	strcpy(instrumentId_, config.InstrumentId.c_str());
}

void BackTestSpiImpl::OnConnected()
{
	BackTestSpiMiddle::OnConnected();
}
void BackTestSpiImpl::OnDisConnected()
{
	BackTestSpiMiddle::OnDisConnected();
}
void BackTestSpiImpl::OnRspSubMarketData(const RspSubMarketDataField* rspSubMarketData, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	BackTestSpiMiddle::OnRspSubMarketData(rspSubMarketData, rspInfo, requestId, isLast);
}
void BackTestSpiImpl::OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData)
{
	//BackTestSpiMiddle::OnRtnDepthMarketData(depthMarketData);
    
	if (lastOrderTickMd_ == nullptr)
	{
		lastOrderTickMd_ = new DepthMarketDataField();
		ReqInsertOrder(lastOrderTickMd_->ExchangeId, lastOrderTickMd_->InstrumentId, lastOrderTickMd_->LastPrice, DirectionType::Buy);
		memcpy(lastOrderTickMd_, depthMarketData, sizeof(DepthMarketDataField));
	}
    else
    {
        auto percentChange = (depthMarketData->LastPrice - lastOrderTickMd_->LastPrice) / lastOrderTickMd_->LastPrice;
        if (percentChange > 0.1)
        {
            ReqInsertOrder(depthMarketData->ExchangeId, depthMarketData->InstrumentId, depthMarketData->LastPrice, DirectionType::Sell);
            memcpy(lastOrderTickMd_, depthMarketData, sizeof(DepthMarketDataField));
        }
        else if (percentChange < -0.1)
        {
            ReqInsertOrder(depthMarketData->ExchangeId, depthMarketData->InstrumentId, depthMarketData->LastPrice, DirectionType::Buy);
            memcpy(lastOrderTickMd_, depthMarketData, sizeof(DepthMarketDataField));
        }
    }
}
void BackTestSpiImpl::OnRtnBarMarketData(const BarMarketDataField* barMarketData)
{
	//BackTestSpiMiddle::OnRtnBarMarketData(barMarketData);
	if (lastOrderBarMd_ == nullptr)
	{
		lastOrderBarMd_ = new BarMarketDataField();
		memcpy(lastOrderBarMd_, barMarketData, sizeof(BarMarketDataField));
		ReqInsertOrder(lastOrderBarMd_->ExchangeId, lastOrderBarMd_->InstrumentId, lastOrderBarMd_->Close, DirectionType::Buy);
	}
	else
	{
		auto percentChange = (barMarketData->Close - lastOrderBarMd_->Close) / lastOrderBarMd_->Close;
		if (percentChange > 0.1)
		{
			memcpy(lastOrderBarMd_, barMarketData, sizeof(BarMarketDataField));
			ReqInsertOrder(barMarketData->ExchangeId, barMarketData->InstrumentId, barMarketData->Close, DirectionType::Sell);
		}
		else if (percentChange < -0.1)
		{
			memcpy(lastOrderBarMd_, barMarketData, sizeof(BarMarketDataField));
			ReqInsertOrder(barMarketData->ExchangeId, barMarketData->InstrumentId, barMarketData->Close, DirectionType::Buy);
		}
	}
}
void BackTestSpiImpl::OnRtnSessionBegin(const SessionBeginField* sessionBegin)
{
	BackTestSpiMiddle::OnRtnSessionBegin(sessionBegin);
}
void BackTestSpiImpl::OnRtnSessionEnd(const SessionEndField* sessionEnd)
{
	BackTestSpiMiddle::OnRtnSessionEnd(sessionEnd);
}
void BackTestSpiImpl::OnRtnMarketDataEnd(const MarketDataEndField* marketDataEnd)
{
	BackTestSpiMiddle::OnRtnMarketDataEnd(marketDataEnd);
	backTestApi_->Release();
}
void BackTestSpiImpl::OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	BackTestSpiMiddle::OnRspInsertOrder(reqInsertOrder, rspInfo, requestId, isLast);
}
void BackTestSpiImpl::OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	BackTestSpiMiddle::OnRspCancelOrder(reqCancelOrder, rspInfo, requestId, isLast);
}
void BackTestSpiImpl::OnRtnOrder(const OrderField* order)
{
	BackTestSpiMiddle::OnRtnOrder(order);
}
void BackTestSpiImpl::OnRtnTrade(const TradeField* trade)
{
	BackTestSpiMiddle::OnRtnTrade(trade);
}

// 裸 SPI 不经 StrategyBase::Start 的自动注册，须在订阅行情前显式注册账户（引擎按需自建 Account/Capital）
void BackTestSpiImpl::ReqRegisterAccount()
{
	ReqRegisterAccountField reqRegisterAccount;
	memset(&reqRegisterAccount, 0, sizeof(ReqRegisterAccountField));
	strcpy(reqRegisterAccount.AccountId, accountId_);
	backTestApi_->ReqRegisterAccount(&reqRegisterAccount, ++maxRequestId_);
}

void BackTestSpiImpl::ReqSubMarketData()
{
	// BarPeriod 留 0 = 不做周期聚合，按数据集精度收 bar
	ReqSubMarketDataField reqSubMd;
	memset(&reqSubMd, 0, sizeof(ReqSubMarketDataField));
	strcpy(reqSubMd.ExchangeId, exchangeId_);
	strcpy(reqSubMd.InstrumentId, instrumentId_);
	backTestApi_->ReqSubMarketData(&reqSubMd, ++maxRequestId_);
	ReqSubMarketDataFinishedField reqSubMdFinished;
	memset(&reqSubMdFinished, 0, sizeof(ReqSubMarketDataFinishedField));
	backTestApi_->ReqSubMarketDataFinished(&reqSubMdFinished, ++maxRequestId_);
}
void BackTestSpiImpl::ReqInsertOrder(const ExchangeIdType& exchangeId, const InstrumentIdType& instrumentId, const double& price, DirectionType direction)
{
	ReqInsertOrderField reqInsertOrder;
	memset(&reqInsertOrder, 0, sizeof(ReqInsertOrderField));
	strcpy(reqInsertOrder.AccountId, accountId_);
	strcpy(reqInsertOrder.ExchangeId, exchangeId);
	strcpy(reqInsertOrder.InstrumentId, instrumentId);
	reqInsertOrder.Direction = direction;
	reqInsertOrder.OffsetFlag = OffsetFlagType::Open;
	reqInsertOrder.OrderPriceType = OrderPriceTypeType::LimitPrice;
	reqInsertOrder.Price = price;
	reqInsertOrder.Volume = 1;
	reqInsertOrder.ClientOrderId = ++maxClientOrderId_;
	backTestApi_->ReqInsertOrder(&reqInsertOrder, ++maxRequestId_);
}
}
