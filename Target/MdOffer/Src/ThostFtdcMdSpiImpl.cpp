#include "ThostFtdcMdSpiImpl.h"
#include "Logger.h"
#include "MdKernel.h"
#include "Utility.h"
#include "TimeUtility.h"
#include <string.h>
#include <vector>

using namespace std;


CThostFtdcMdSpiImpl::CThostFtdcMdSpiImpl(CThostFtdcMdApi* MdApi, MdKernel* mdKernel)
	:m_MdApi(MdApi), m_MdKernel(mdKernel), m_RequestID(0), m_AccountInfo(nullptr)
{
}
void CThostFtdcMdSpiImpl::OnFrontConnected()
{
	CThostFtdcMdSpiMiddle::OnFrontConnected();
	ReqUserLogin();
}
void CThostFtdcMdSpiImpl::OnFrontDisconnected(int nReason)
{
	CThostFtdcMdSpiMiddle::OnFrontDisconnected(nReason);
}
void CThostFtdcMdSpiImpl::OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	CThostFtdcMdSpiMiddle::OnRspUserLogin(pRspUserLogin, pRspInfo, nRequestID, bIsLast);
	ReqSubscribeMd();
}
void CThostFtdcMdSpiImpl::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData)
{
	RtnDepthMarketDataPackage* package = RtnDepthMarketDataPackage::Allocate();
	package->DepthMarketData = ::Allocate<DepthMarketDataField>();
	memset(package->DepthMarketData, 0, sizeof(DepthMarketDataField));
	Strcpy(package->DepthMarketData->TradingDay, pDepthMarketData->ActionDay);
	Strcpy(package->DepthMarketData->ExchangeID, pDepthMarketData->ExchangeID);
	Strcpy(package->DepthMarketData->InstrumentID, pDepthMarketData->InstrumentID);
	package->DepthMarketData->LastPrice = pDepthMarketData->LastPrice;
	package->DepthMarketData->PreSettlementPrice = pDepthMarketData->PreSettlementPrice;
	package->DepthMarketData->PreClosePrice = pDepthMarketData->PreClosePrice;
	package->DepthMarketData->PreOpenInterest = pDepthMarketData->PreOpenInterest;
	package->DepthMarketData->OpenPrice = pDepthMarketData->OpenPrice;
	package->DepthMarketData->HighestPrice = pDepthMarketData->HighestPrice;
	package->DepthMarketData->LowestPrice = pDepthMarketData->LowestPrice;
	package->DepthMarketData->ClosePrice = pDepthMarketData->ClosePrice;
	package->DepthMarketData->Volume = pDepthMarketData->Volume;
	package->DepthMarketData->Turnover = pDepthMarketData->Turnover;
	package->DepthMarketData->OpenInterest = pDepthMarketData->OpenInterest;
	package->DepthMarketData->SettlementPrice = pDepthMarketData->SettlementPrice;
	package->DepthMarketData->UpperLimitPrice = pDepthMarketData->UpperLimitPrice;
	package->DepthMarketData->LowerLimitPrice = pDepthMarketData->LowerLimitPrice;
	package->DepthMarketData->AveragePrice = pDepthMarketData->AveragePrice;
	package->DepthMarketData->UpdateTs = pDepthMarketData->LastPrice;
	package->DepthMarketData->UpdateTs = atoll(pDepthMarketData->ActionDay) * 1000000000LL + GetTimeFromTimeString(pDepthMarketData->UpdateTime) * 1000LL + pDepthMarketData->UpdateMillisec;

	package->DepthMarketData->AskPrice1 = pDepthMarketData->AskPrice1;
	package->DepthMarketData->AskPrice2 = pDepthMarketData->AskPrice2;
	package->DepthMarketData->AskPrice3 = pDepthMarketData->AskPrice3;
	package->DepthMarketData->AskPrice4 = pDepthMarketData->AskPrice4;
	package->DepthMarketData->AskPrice5 = pDepthMarketData->AskPrice5;
	package->DepthMarketData->AskVolume1 = pDepthMarketData->AskVolume1;
	package->DepthMarketData->AskVolume2 = pDepthMarketData->AskVolume2;
	package->DepthMarketData->AskVolume3 = pDepthMarketData->AskVolume3;
	package->DepthMarketData->AskVolume4 = pDepthMarketData->AskVolume4;
	package->DepthMarketData->AskVolume5 = pDepthMarketData->AskVolume5;
	
	package->DepthMarketData->BidPrice1 = pDepthMarketData->BidPrice1;
	package->DepthMarketData->BidPrice2 = pDepthMarketData->BidPrice2;
	package->DepthMarketData->BidPrice3 = pDepthMarketData->BidPrice3;
	package->DepthMarketData->BidPrice4 = pDepthMarketData->BidPrice4;
	package->DepthMarketData->BidPrice5 = pDepthMarketData->BidPrice5;
	package->DepthMarketData->BidVolume1 = pDepthMarketData->BidVolume1;
	package->DepthMarketData->BidVolume2 = pDepthMarketData->BidVolume2;
	package->DepthMarketData->BidVolume3 = pDepthMarketData->BidVolume3;
	package->DepthMarketData->BidVolume4 = pDepthMarketData->BidVolume4;
	package->DepthMarketData->BidVolume5 = pDepthMarketData->BidVolume5;

	m_MdKernel->OnMessage(package);
}

void CThostFtdcMdSpiImpl::SetAccountInfo(AccountInfo* accountInfo)
{
	m_AccountInfo = accountInfo;
}
void CThostFtdcMdSpiImpl::SubscribeMd(ReqSubMarketDataField* reqSubMd)
{
	vector<char*> instruments;
	instruments.push_back(reqSubMd->InstrumentID);
	int ret = m_MdApi->SubscribeMarketData(instruments.data(), instruments.size());
	WriteLog(LogLevel::Info, "SubscribeMd: ExchangeID:%s, InstrumentID:%s, ret:%d", reqSubMd->ExchangeID, reqSubMd->InstrumentID, ret);
}

void CThostFtdcMdSpiImpl::ReqUserLogin()
{
	CThostFtdcReqUserLoginField userLogin;
	::memset(&userLogin, 0, sizeof(userLogin));
	strcpy(userLogin.TradingDay, "");
	strcpy(userLogin.BrokerID, m_AccountInfo->BrokerID);
	strcpy(userLogin.UserID, m_AccountInfo->InvestorID);
	strcpy(userLogin.Password, m_AccountInfo->Password);
	strcpy(userLogin.UserProductInfo, m_AccountInfo->UserProductInfo);

	int ret = m_MdApi->ReqUserLogin(&userLogin, m_RequestID++);
	WriteLog(LogLevel::Info, "ReqUserLogin: ret[%d]", ret);
}
void CThostFtdcMdSpiImpl::ReqSubscribeMd()
{
	vector<const char*> instruments;
	instruments.push_back("IC2603");
	instruments.push_back("IC2509");
	instruments.push_back("IC25012");

	int ret = m_MdApi->SubscribeMarketData((char**)instruments.data(), instruments.size());
	WriteLog(LogLevel::Info, "SubscribeMarketData: ret[%d]", ret);
}
