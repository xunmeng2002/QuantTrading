#include "MdSpiImpl.h"
#include "Config/Config.h"
#include <Spark/Core/Utility/Utility.h>


namespace QuantTrading::TestMdApi
{
MdSpiImpl::MdSpiImpl(MdApi* mdApi)
	:m_MdApi(mdApi), m_RequestID(0)
{
	m_ReqSubMarketData = new ReqSubMarketDataField();
	memset(m_ReqSubMarketData, 0, sizeof(ReqSubMarketDataField));
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
void MdSpiImpl::OnRspMdUserLogin(const RspMdUserLoginField* rspMdUserLogin, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	MdSpiMiddle::OnRspMdUserLogin(rspMdUserLogin, rspInfo, requestID, isLast);
	++m_RspMdUserLoginCount;
	ReqSubscribeMd();
}
void MdSpiImpl::OnRspMdUserLogout(const RspMdUserLogoutField* rspMdUserLogout, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	MdSpiMiddle::OnRspMdUserLogout(rspMdUserLogout, rspInfo, requestID, isLast);
	++m_RspMdUserLogoutCount;
	// 同一条连接立即重登：内核按传输层 SessionId 清理会话记录，重登应回 ErrorNone，
	// 清理失效则回 ErrorSessionAlreadyLogin，故这次重登本身就是对该清理的验证
	ReqUserLogin();
}
void MdSpiImpl::OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData)
{
	MdSpiMiddle::OnRtnDepthMarketData(depthMarketData);
	++m_RtnMdCount;
}
void MdSpiImpl::ReqUserLogin()
{
	ReqMdUserLoginField reqMdUserLogin;
	memset(&reqMdUserLogin, 0, sizeof(ReqMdUserLoginField));
	Utility::Strcpy(reqMdUserLogin.UserId, Config::GetInstance().MdUser.c_str());
    Utility::Strcpy(reqMdUserLogin.Password, Config::GetInstance().MdPassword.c_str());
	m_MdApi->ReqMdUserLogin(&reqMdUserLogin, ++m_RequestID);
}
void MdSpiImpl::ReqUserLogout()
{
	ReqMdUserLogoutField reqMdUserLogout;
	memset(&reqMdUserLogout, 0, sizeof(ReqMdUserLogoutField));
	Utility::Strcpy(reqMdUserLogout.UserId, Config::GetInstance().MdUser.c_str());
	m_MdApi->ReqMdUserLogout(&reqMdUserLogout, ++m_RequestID);
}
void MdSpiImpl::ReqSubscribeMd()
{
	for (auto instrument : Config::GetInstance().SubscribeInstruments)
	{
        Utility::Strcpy(m_ReqSubMarketData->ExchangeId, instrument->ExchangeId.c_str());
        Utility::Strcpy(m_ReqSubMarketData->InstrumentId, instrument->InstrumentId.c_str());
		m_MdApi->ReqSubMarketData(m_ReqSubMarketData, ++m_RequestID);
	}
}
}
