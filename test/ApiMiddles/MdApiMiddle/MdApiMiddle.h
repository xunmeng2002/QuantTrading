// 本文件由 ../Templates/Cpp/ApiTest/ApiMiddle.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include <QuantTrading/MdApi.h>


namespace QuantTrading
{
class MdApiMiddle : public MdApi
{
public:
	static MdApiMiddle* CreateMdApiMiddle();
	static const char* GetApiVersion();
	virtual bool Init() override;
	virtual void Join() override;
	virtual void Release() override;
	virtual void RegisterFront(const char* address) override;
	virtual void RegisterSpi(MdSpi* spi) override;
	
	virtual int ReqMdUserLogin(const ReqMdUserLoginField* reqMdUserLogin, int requestID) override;
	virtual int ReqMdUserLogout(const ReqMdUserLogoutField* reqMdUserLogout, int requestID) override;
	virtual int ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestID) override;
	virtual int ReqUnSubMarketData(const ReqUnSubMarketDataField* reqUnSubMarketData, int requestID) override;

private:
	MdApi* mdApi;
};
}
