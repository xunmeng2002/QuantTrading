// 本文件由 ../Templates/Cpp/ApiTest/ApiMiddle.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include <QuantTrading/BackTestApi.h>


namespace QuantTrading
{
class BackTestApiMiddle : public BackTestApi
{
public:
	static BackTestApiMiddle* CreateBackTestApiMiddle();
	static const char* GetApiVersion();
	virtual bool Init() override;
	virtual void Join() override;
	virtual void Release() override;
	virtual void RegisterFront(const char* address) override;
	virtual void RegisterSpi(BackTestSpi* spi) override;
	
	virtual int ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestId) override;
	virtual int ReqSubMarketDataFinished(const ReqSubMarketDataFinishedField* reqSubMarketDataFinished, int requestId) override;
	virtual int ReqRegisterAccount(const ReqRegisterAccountField* reqRegisterAccount, int requestId) override;
	virtual int ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestId) override;
	virtual int ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestId) override;

private:
	BackTestApi* backTestApi_;
};
}
