#include "MdSpiImpl.h"
#include "Config/Config.h"
#include <Spark/Core/Utility/Utility.h>


namespace QuantTrading::TestMdApi
{
MdSpiImpl::MdSpiImpl(MdApi* mdApi)
	:mdApi_(mdApi), requestId_(0)
{
	reqSubMarketData_ = new ReqSubMarketDataField();
	memset(reqSubMarketData_, 0, sizeof(ReqSubMarketDataField));
}
MdSpiImpl::~MdSpiImpl()
{
	delete reqSubMarketData_;
	reqSubMarketData_ = nullptr;
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
void MdSpiImpl::OnRspMdUserLogin(const RspMdUserLoginField* rspMdUserLogin, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	MdSpiMiddle::OnRspMdUserLogin(rspMdUserLogin, rspInfo, requestId, isLast);
	++RspMdUserLoginCount;
	ReqSubscribeMd();
}
void MdSpiImpl::OnRspMdUserLogout(const RspMdUserLogoutField* rspMdUserLogout, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	MdSpiMiddle::OnRspMdUserLogout(rspMdUserLogout, rspInfo, requestId, isLast);
	++RspMdUserLogoutCount;
	// 同一条连接立即重登：内核按传输层 SessionId 清理会话记录，重登应回 ErrorNone，
	// 清理失效则回 ErrorSessionAlreadyLogin，故这次重登本身就是对该清理的验证
	ReqUserLogin();
}
void MdSpiImpl::OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData)
{
	MdSpiMiddle::OnRtnDepthMarketData(depthMarketData);
	++RtnMdCount;
}
void MdSpiImpl::ReqUserLogin()
{
	ReqMdUserLoginField reqMdUserLogin;
	memset(&reqMdUserLogin, 0, sizeof(ReqMdUserLoginField));
	Utility::Strcpy(reqMdUserLogin.UserId, Config::GetInstance().MdUser.c_str());
    Utility::Strcpy(reqMdUserLogin.Password, Config::GetInstance().MdPassword.c_str());
	mdApi_->ReqMdUserLogin(&reqMdUserLogin, ++requestId_);
}
void MdSpiImpl::ReqUserLogout()
{
	ReqMdUserLogoutField reqMdUserLogout;
	memset(&reqMdUserLogout, 0, sizeof(ReqMdUserLogoutField));
	Utility::Strcpy(reqMdUserLogout.UserId, Config::GetInstance().MdUser.c_str());
	mdApi_->ReqMdUserLogout(&reqMdUserLogout, ++requestId_);
}
void MdSpiImpl::ReqSubscribeMd()
{
	for (auto instrument : Config::GetInstance().SubscribeInstruments)
	{
        Utility::Strcpy(reqSubMarketData_->ExchangeId, instrument->ExchangeId.c_str());
        Utility::Strcpy(reqSubMarketData_->InstrumentId, instrument->InstrumentId.c_str());
		mdApi_->ReqSubMarketData(reqSubMarketData_, ++requestId_);
	}
}
}
