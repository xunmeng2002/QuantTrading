#include "BackTestSpiImpl.h"
#include "QuantUtility.h"
#include <Spark/Core/Logger/Logger.h>
#include <stdexcept>
#include <string.h>

using namespace Spark::Core;

namespace QuantTrading::TestBackTest
{
BackTestSpiImpl::BackTestSpiImpl(BackTestApi* backTestApi, const BackTestSpiParams& params)
	:params_(params), backTestApi_(backTestApi), lastOrderTickMd_(nullptr), lastOrderBarMd_(nullptr), maxRequestId_(0), maxClientOrderId_(0)
{
	if (params_.OrderTriggerRatio <= 0.0 || params_.OrderTriggerRatio >= 1.0)
	{
		WriteLog(LogLevel::Error, "BackTestSpiImpl rejected: OrderTriggerRatio:%f, must be in (0, 1)", params_.OrderTriggerRatio);
		throw std::logic_error("OrderTriggerRatio must be in (0, 1)");
	}
	if (params_.OrderVolume < 1)
	{
		WriteLog(LogLevel::Error, "BackTestSpiImpl rejected: OrderVolume:%d, need >= 1", params_.OrderVolume);
		throw std::logic_error("OrderVolume must be at least 1");
	}
	strcpy(accountId_, params_.AccountId.c_str());
	strcpy(exchangeId_, params_.ExchangeId.c_str());
	strcpy(instrumentId_, params_.InstrumentId.c_str());
}

BackTestSpiImpl::~BackTestSpiImpl()
{
	delete lastOrderTickMd_;
	delete lastOrderBarMd_;
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
// 首帧只建基准并以本帧价开一手；此后与「上一笔下单时的价格」比较，越阈反向开单并重锚基准价。
// 基准价始终是「上一笔下单时的价格」，故同向连续小幅波动不会累积成一次触发。
// 价格不可用即不动作：不可用价既不得起基准、也不得覆盖基准（否则基准会落进不可用态）
template <typename MdField, typename PriceReader>
void BackTestSpiImpl::ApplyPriceTrigger(const MdField* currentFrame, MdField*& lastOrderFrame, PriceReader readPrice)
{
	if (currentFrame == nullptr)
	{
		return;
	}
	const PriceType currentPrice = readPrice(currentFrame);
	if (lastOrderFrame == nullptr)
	{
		if (!QuantTrading::IsUsablePrice(currentPrice))
		{
			return;
		}
		lastOrderFrame = new MdField(*currentFrame);
		ReqInsertOrder(lastOrderFrame->ExchangeId, lastOrderFrame->InstrumentId, currentPrice, DirectionType::Buy);
		return;
	}
	DirectionType direction = DirectionType::Buy;
	if (!TryDecideReversalDirection(readPrice(lastOrderFrame), currentPrice, direction))
	{
		return;
	}
	ReqInsertOrder(currentFrame->ExchangeId, currentFrame->InstrumentId, currentPrice, direction);
	*lastOrderFrame = *currentFrame;
}
void BackTestSpiImpl::OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData)
{
	ApplyPriceTrigger(depthMarketData, lastOrderTickMd_, [](const DepthMarketDataField* frame) { return frame->LastPrice; });
}
// 与 OnRtnDepthMarketData 同一口径，仅取价字段不同（Bar 回放模式无 tick，以 Close 为价）
void BackTestSpiImpl::OnRtnBarMarketData(const BarMarketDataField* barMarketData)
{
	ApplyPriceTrigger(barMarketData, lastOrderBarMd_, [](const BarMarketDataField* frame) { return frame->Close; });
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
	reqInsertOrder.Volume = params_.OrderVolume;
	reqInsertOrder.ClientOrderId = ++maxClientOrderId_;
	backTestApi_->ReqInsertOrder(&reqInsertOrder, ++maxRequestId_);
}
// Tick 与 Bar 回放共用的触发判据：涨幅越阈卖、跌幅越阈买，阈内不动作。
// 两侧价格任一不可用即返回 false，除法只在此处发生（参考价为 0 会得到 inf，故先用判据收口）
bool BackTestSpiImpl::TryDecideReversalDirection(PriceType lastOrderPrice, PriceType currentPrice, DirectionType& direction) const
{
	if (!QuantTrading::IsUsablePrice(lastOrderPrice) || !QuantTrading::IsUsablePrice(currentPrice))
	{
		return false;
	}
	const double priceChangeRatio = (currentPrice - lastOrderPrice) / lastOrderPrice;
	if (priceChangeRatio > params_.OrderTriggerRatio)
	{
		direction = DirectionType::Sell;
		return true;
	}
	if (priceChangeRatio < -params_.OrderTriggerRatio)
	{
		direction = DirectionType::Buy;
		return true;
	}
	return false;
}
}
