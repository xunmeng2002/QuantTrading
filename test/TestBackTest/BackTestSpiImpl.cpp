#include "BackTestSpiImpl.h"
#include <Spark/Core/Logger/Logger.h>
#include <string.h>

namespace QuantTrading::testbacktest
{
BackTestSpiImpl::BackTestSpiImpl(BackTestApi* backTestApi, const Config& config)
	:m_BackTestApi(backTestApi), m_LastOrderTickMd(nullptr), m_LastOrderBarMd(nullptr), m_MaxRequestID(0), m_MaxClientOrderID(0)
{
	strcpy(m_AccountID, config.AccountId.c_str());
	strcpy(m_ExchangeID, config.ExchangeId.c_str());
	strcpy(m_InstrumentID, config.InstrumentId.c_str());
}

void BackTestSpiImpl::OnConnected()
{
	BackTestSpiMiddle::OnConnected();
}
void BackTestSpiImpl::OnDisConnected()
{
	BackTestSpiMiddle::OnDisConnected();
}
void BackTestSpiImpl::OnRspSubMarketData(const RspSubMarketDataField* rspSubMarketData, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	BackTestSpiMiddle::OnRspSubMarketData(rspSubMarketData, rspInfo, requestID, isLast);
}
void BackTestSpiImpl::OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData)
{
	//BackTestSpiMiddle::OnRtnDepthMarketData(depthMarketData);
    
	if (m_LastOrderTickMd == nullptr)
	{
		m_LastOrderTickMd = new DepthMarketDataField();
		ReqInsertOrder(m_LastOrderTickMd->ExchangeId, m_LastOrderTickMd->InstrumentId, m_LastOrderTickMd->LastPrice, DirectionType::Buy);
		memcpy(m_LastOrderTickMd, depthMarketData, sizeof(DepthMarketDataField));
	}
    else
    {
        auto percentChange = (depthMarketData->LastPrice - m_LastOrderTickMd->LastPrice) / m_LastOrderTickMd->LastPrice;
        if (percentChange > 0.1)
        {
            ReqInsertOrder(depthMarketData->ExchangeId, depthMarketData->InstrumentId, depthMarketData->LastPrice, DirectionType::Sell);
            memcpy(m_LastOrderTickMd, depthMarketData, sizeof(DepthMarketDataField));
        }
        else if (percentChange < -0.1)
        {
            ReqInsertOrder(depthMarketData->ExchangeId, depthMarketData->InstrumentId, depthMarketData->LastPrice, DirectionType::Buy);
            memcpy(m_LastOrderTickMd, depthMarketData, sizeof(DepthMarketDataField));
        }
    }
}
void BackTestSpiImpl::OnRtnBarMarketData(const BarMarketDataField* barMarketData)
{
	//BackTestSpiMiddle::OnRtnBarMarketData(barMarketData);
	if (m_LastOrderBarMd == nullptr)
	{
		m_LastOrderBarMd = new BarMarketDataField();
		memcpy(m_LastOrderBarMd, barMarketData, sizeof(BarMarketDataField));
		ReqInsertOrder(m_LastOrderBarMd->ExchangeId, m_LastOrderBarMd->InstrumentId, m_LastOrderBarMd->Close, DirectionType::Buy);
	}
	else
	{
		auto percentChange = (barMarketData->Close - m_LastOrderBarMd->Close) / m_LastOrderBarMd->Close;
		if (percentChange > 0.1)
		{
			memcpy(m_LastOrderBarMd, barMarketData, sizeof(BarMarketDataField));
			ReqInsertOrder(barMarketData->ExchangeId, barMarketData->InstrumentId, barMarketData->Close, DirectionType::Sell);
		}
		else if (percentChange < -0.1)
		{
			memcpy(m_LastOrderBarMd, barMarketData, sizeof(BarMarketDataField));
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
	m_BackTestApi->Release();
}
void BackTestSpiImpl::OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	BackTestSpiMiddle::OnRspInsertOrder(reqInsertOrder, rspInfo, requestID, isLast);
}
void BackTestSpiImpl::OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	BackTestSpiMiddle::OnRspCancelOrder(reqCancelOrder, rspInfo, requestID, isLast);
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
	strcpy(reqRegisterAccount.AccountId, m_AccountID);
	m_BackTestApi->ReqRegisterAccount(&reqRegisterAccount, ++m_MaxRequestID);
}

void BackTestSpiImpl::ReqSubMarketData()
{
	// BarPeriod 留 0 = 不做周期聚合，按数据集精度收 bar
	ReqSubMarketDataField reqSubMd;
	memset(&reqSubMd, 0, sizeof(ReqSubMarketDataField));
	strcpy(reqSubMd.ExchangeId, m_ExchangeID);
	strcpy(reqSubMd.InstrumentId, m_InstrumentID);
	m_BackTestApi->ReqSubMarketData(&reqSubMd, ++m_MaxRequestID);
	ReqSubMarketDataFinishedField reqSubMdFinished;
	memset(&reqSubMdFinished, 0, sizeof(ReqSubMarketDataFinishedField));
	m_BackTestApi->ReqSubMarketDataFinished(&reqSubMdFinished, ++m_MaxRequestID);
}
void BackTestSpiImpl::ReqInsertOrder(const ExchangeIdType& exchangeId, const InstrumentIdType& instrumentId, const double& price, DirectionType direction)
{
	ReqInsertOrderField reqInsertOrder;
	memset(&reqInsertOrder, 0, sizeof(ReqInsertOrderField));
	strcpy(reqInsertOrder.AccountId, m_AccountID);
	strcpy(reqInsertOrder.ExchangeId, exchangeId);
	strcpy(reqInsertOrder.InstrumentId, instrumentId);
	reqInsertOrder.Direction = direction;
	reqInsertOrder.OffsetFlag = OffsetFlagType::Open;
	reqInsertOrder.OrderPriceType = OrderPriceTypeType::LimitPrice;
	reqInsertOrder.Price = price;
	reqInsertOrder.Volume = 1;
	reqInsertOrder.ClientOrderId = ++m_MaxClientOrderID;
	m_BackTestApi->ReqInsertOrder(&reqInsertOrder, ++m_MaxRequestID);
}
}
