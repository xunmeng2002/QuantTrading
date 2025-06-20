#include "BackTestSpiImpl.h"
#include "Logger.h"
#include <string.h>

BackTestSpiImpl::BackTestSpiImpl(BackTestApi* backTestApi)
	:m_BackTestApi(backTestApi), m_LastOrderTickMd(nullptr), m_LastOrderBarMd(nullptr), m_MaxRequestID(0), m_MaxClientOrderID(0)
{
	strcpy(m_AccountID, "18511899894");
}

void BackTestSpiImpl::OnConnected()
{
	BackTestSpiMiddle::OnConnected();
}
void BackTestSpiImpl::OnDisConnected()
{
	BackTestSpiMiddle::OnDisConnected();
}
void BackTestSpiImpl::OnRspSubMarketData(RspSubMarketDataField* rspSubMarketData, RspInfoField* rspInfo, int requestID, bool isLast)
{
	BackTestSpiMiddle::OnRspSubMarketData(rspSubMarketData, rspInfo, requestID, isLast);
}
void BackTestSpiImpl::OnRtnDepthMarketData(DepthMarketDataField* depthMarketData)
{
	//BackTestSpiMiddle::OnRtnDepthMarketData(depthMarketData);
	if (m_LastOrderTickMd == nullptr)
	{
		m_LastOrderTickMd = new DepthMarketDataField();
		memcpy(m_LastOrderTickMd, depthMarketData, sizeof(DepthMarketDataField));
		ReqInsertOrder(m_LastOrderTickMd->ExchangeID, m_LastOrderTickMd->InstrumentID, m_LastOrderTickMd->LastPrice, DirectionType::Buy);
	}
	else if (m_LastOrderTickMd->LastPrice - depthMarketData->LastPrice > 10)
	{
		memcpy(m_LastOrderTickMd, depthMarketData, sizeof(DepthMarketDataField));
		ReqInsertOrder(m_LastOrderTickMd->ExchangeID, m_LastOrderTickMd->InstrumentID, m_LastOrderTickMd->LastPrice, DirectionType::Sell);
	}
	else if (m_LastOrderTickMd->LastPrice - depthMarketData->LastPrice < -10)
	{
		memcpy(m_LastOrderTickMd, depthMarketData, sizeof(DepthMarketDataField));
		ReqInsertOrder(m_LastOrderTickMd->ExchangeID, m_LastOrderTickMd->InstrumentID, m_LastOrderTickMd->LastPrice, DirectionType::Buy);
	}
}
void BackTestSpiImpl::OnRtnBarMarketData(BarMarketDataField* barMarketData)
{
	//BackTestSpiMiddle::OnRtnBarMarketData(barMarketData);
	if (m_LastOrderBarMd == nullptr)
	{
		m_LastOrderBarMd = new BarMarketDataField();
		memcpy(m_LastOrderBarMd, barMarketData, sizeof(BarMarketDataField));
		ReqInsertOrder(m_LastOrderBarMd->ExchangeID, m_LastOrderBarMd->InstrumentID, m_LastOrderBarMd->Close, DirectionType::Buy);
	}
	else if (m_LastOrderBarMd->Close - barMarketData->Close > 10)
	{
		memcpy(m_LastOrderBarMd, barMarketData, sizeof(BarMarketDataField));
		ReqInsertOrder(m_LastOrderBarMd->ExchangeID, m_LastOrderBarMd->InstrumentID, m_LastOrderBarMd->Close, DirectionType::Sell);
	}
	else if (m_LastOrderBarMd->Close - barMarketData->Close < -10)
	{
		memcpy(m_LastOrderBarMd, barMarketData, sizeof(BarMarketDataField));
		ReqInsertOrder(m_LastOrderBarMd->ExchangeID, m_LastOrderBarMd->InstrumentID, m_LastOrderBarMd->Close, DirectionType::Buy);
	}
}
void BackTestSpiImpl::OnRtnSessionBegin(SessionBeginField* sessionBegin)
{
	BackTestSpiMiddle::OnRtnSessionBegin(sessionBegin);
}
void BackTestSpiImpl::OnRtnSessionEnd(SessionEndField* sessionEnd)
{
	BackTestSpiMiddle::OnRtnSessionEnd(sessionEnd);
}
void BackTestSpiImpl::OnRtnMarketDataEnd(MarketDataEndField* marketDataEnd)
{
	BackTestSpiMiddle::OnRtnMarketDataEnd(marketDataEnd);
	m_BackTestApi->Release();
}
void BackTestSpiImpl::OnRspInsertOrder(ReqInsertOrderField* reqInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast)
{
	BackTestSpiMiddle::OnRspInsertOrder(reqInsertOrder, rspInfo, requestID, isLast);
}
void BackTestSpiImpl::OnRspCancelOrder(ReqCancelOrderField* reqCancelOrder, RspInfoField* rspInfo, int requestID, bool isLast)
{
	BackTestSpiMiddle::OnRspCancelOrder(reqCancelOrder, rspInfo, requestID, isLast);
}
void BackTestSpiImpl::OnRtnOrder(OrderField* order)
{
	BackTestSpiMiddle::OnRtnOrder(order);
}
void BackTestSpiImpl::OnRtnTrade(TradeField* trade)
{
	BackTestSpiMiddle::OnRtnTrade(trade);
}

void BackTestSpiImpl::ReqSubMarketData()
{
	ReqSubMarketDataField reqSubMd;
	strcpy(reqSubMd.ExchangeID, "CFFEX");
	strcpy(reqSubMd.InstrumentID, "IF2503");
	m_BackTestApi->ReqSubMarketData(&reqSubMd, ++m_MaxRequestID);
	ReqSubMarketDataFinishedField reqSubMdFinished;
	m_BackTestApi->ReqSubMarketDataFinished(&reqSubMdFinished, ++m_MaxRequestID);
}
void BackTestSpiImpl::ReqInsertOrder(const ExchangeIDType& exchangeID, const InstrumentIDType& instrumentID, const double& price, DirectionType direction)
{
	ReqInsertOrderField reqInsertOrder;
	memset(&reqInsertOrder, 0, sizeof(ReqInsertOrderField));
	strcpy(reqInsertOrder.AccountID, m_AccountID);
	strcpy(reqInsertOrder.ExchangeID, exchangeID);
	strcpy(reqInsertOrder.InstrumentID, instrumentID);
	reqInsertOrder.Direction = direction;
	reqInsertOrder.OffsetFlag = OffsetFlagType::Open;
	reqInsertOrder.OrderPriceType = OrderPriceTypeType::LimitPrice;
	reqInsertOrder.Price = price;
	reqInsertOrder.Volume = 1;
	reqInsertOrder.ClientOrderID = ++m_MaxClientOrderID;
	m_BackTestApi->ReqInsertOrder(&reqInsertOrder, ++m_MaxRequestID);
}
