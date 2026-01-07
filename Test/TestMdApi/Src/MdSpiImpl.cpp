#include "MdSpiImpl.h"
#include "Utility.h"
#include "Config.h"

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
	MdSpiMiddle::OnRtnDepthMarketData(depthMarketData);
}
void MdSpiImpl::ReqUserLogin()
{
	ReqMdUserLoginField reqMdUserLogin;
	memset(&reqMdUserLogin, 0, sizeof(ReqMdUserLoginField));
	Strcpy(reqMdUserLogin.UserID, Config::GetInstance().MdUser.c_str());
	Strcpy(reqMdUserLogin.Password, Config::GetInstance().MdPassword.c_str());
	m_MdApi->ReqMdUserLogin(&reqMdUserLogin, ++m_RequestID);
}
void MdSpiImpl::ReqSubscribeMd()
{
	for (auto instrument : Config::GetInstance().SubscribeInstruments)
	{
		Strcpy(m_ReqSubMarketData->ExchangeID, instrument->ExchangeID.c_str());
		Strcpy(m_ReqSubMarketData->InstrumentID, instrument->InstrumentID.c_str());
		m_MdApi->ReqSubMarketData(m_ReqSubMarketData, ++m_RequestID);
	}
}
