#include "MdSpiImpl.h"
#include "Utility.h"

MdSpiImpl::MdSpiImpl(MdApi* mdApi)
	:m_MdApi(mdApi), m_RequestID(0)
{
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
void MdSpiImpl::OnRspMdUserLogin(RspInfoField* rspInfo, RspMdUserLoginField* rspMdUserLogin, int requestID, bool isLast)
{
	MdSpiMiddle::OnRspMdUserLogin(rspInfo, rspMdUserLogin, requestID, isLast);
	ReqSubscribeMd();
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
	ReqSubMarketDataField reqSubMarketData;
	memset(&reqSubMarketData, 0, sizeof(ReqSubMarketDataField));
	Strcpy(reqSubMarketData.ExchangeID, "CFFEX");
	Strcpy(reqSubMarketData.InstrumentID, "IC2509");
	m_MdApi->ReqSubMarketData(&reqSubMarketData, ++m_RequestID);

	Strcpy(reqSubMarketData.ExchangeID, "CFFEX");
	Strcpy(reqSubMarketData.InstrumentID, "IF2509");
	m_MdApi->ReqSubMarketData(&reqSubMarketData, ++m_RequestID);

	Strcpy(reqSubMarketData.ExchangeID, "CFFEX");
	Strcpy(reqSubMarketData.InstrumentID, "IM2509");
	m_MdApi->ReqSubMarketData(&reqSubMarketData, ++m_RequestID);
}
