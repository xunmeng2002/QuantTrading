#pragma once
#include "MdApi.h"


class MdApiMiddle : public MdApi
{
public:
	static MdApiMiddle* CreateMdApiMiddle();
	static const char* GetApiVersion();
	virtual void Init() override;
	virtual void Join() override;
	virtual void Release() override;
	virtual void RegisterFront(const char* address) override;
	virtual void RegisterSpi(MdSpi* pSpi) override;
	
	virtual int ReqMdUserLogin(ReqMdUserLoginField* reqMdUserLogin, int requestID) override;
	virtual int ReqMdUserLogout(ReqMdUserLogoutField* reqMdUserLogout, int requestID) override;
	virtual int ReqSubMarketData(ReqSubMarketDataField* reqSubMarketData, int requestID) override;
	virtual int ReqUnSubMarketData(ReqUnSubMarketDataField* reqUnSubMarketData, int requestID) override;

private:
	MdApi* m_MdApi;
};
