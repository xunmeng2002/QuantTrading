#include "MdSpiImpl.h"
#include "Utility.h"

MdSpiImpl::MdSpiImpl(MdApi* mdApi)
	:m_MdApi(mdApi), m_RequestID(0)
{
	m_ReqSubMarketData = new ReqSubMarketDataField();
}
MdSpiImpl::~MdSpiImpl()
{
	delete m_ReqSubMarketData;
	m_ReqSubMarketData = nullptr;
}
void MdSpiImpl::OnConnected()
{
	MdSpiMiddle::OnConnected();
	ReqUserLogin();
}
void MdSpiImpl::OnDisConnected()
{
	MdSpiMiddle::OnDisConnected();
}
void MdSpiImpl::OnRspMdUserLogin(RspMdUserLoginField* rspMdUserLogin, RspInfoField* rspInfo, int requestID, bool isLast)
{
	MdSpiMiddle::OnRspMdUserLogin(rspMdUserLogin, rspInfo, requestID, isLast);
	ReqSubscribeMd();
}
void MdSpiImpl::OnRtnDepthMarketData(DepthMarketDataField* depthMarketData)
{
	if (++m_DepthMdCounts[depthMarketData->InstrumentID] % 10 == 0)
	{
		MdSpiMiddle::OnRtnDepthMarketData(depthMarketData);
	}
}
void MdSpiImpl::ReqUserLogin()
{
	ReqMdUserLoginField reqMdUserLogin;
	memset(&reqMdUserLogin, 0, sizeof(ReqMdUserLoginField));
	Strcpy(reqMdUserLogin.UserID, "MdUser");
	Strcpy(reqMdUserLogin.Password, "123456");
	m_MdApi->ReqMdUserLogin(&reqMdUserLogin, ++m_RequestID);
}
void MdSpiImpl::ReqSubscribeMd()
{
	Strcpy(m_ReqSubMarketData->ExchangeID, "CFFEX");
	Strcpy(m_ReqSubMarketData->InstrumentID, "IC2509");
	m_MdApi->ReqSubMarketData(m_ReqSubMarketData, ++m_RequestID);

	Strcpy(m_ReqSubMarketData->ExchangeID, "CFFEX");
	Strcpy(m_ReqSubMarketData->InstrumentID, "IF2509");
	m_MdApi->ReqSubMarketData(m_ReqSubMarketData, ++m_RequestID);

	Strcpy(m_ReqSubMarketData->ExchangeID, "CFFEX");
	Strcpy(m_ReqSubMarketData->InstrumentID, "IM2509");
	m_MdApi->ReqSubMarketData(m_ReqSubMarketData, ++m_RequestID);
}
