#pragma once
#include <QuantTrading/BackTestApi.h>


namespace quanttrading
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
	virtual void RegisterSpi(BackTestSpi* pSpi) override;
	
	virtual int ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestID) override;
	virtual int ReqSubMarketDataFinished(const ReqSubMarketDataFinishedField* reqSubMarketDataFinished, int requestID) override;
	virtual int ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestID) override;
	virtual int ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestID) override;

private:
	BackTestApi* m_BackTestApi;
};
}
