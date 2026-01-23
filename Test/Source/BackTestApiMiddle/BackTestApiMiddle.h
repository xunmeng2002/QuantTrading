#pragma once
#include "BackTestApi.h"


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
	
	virtual int ReqSubMarketData(ReqSubMarketDataField* reqSubMarketData, int requestID) override;
	virtual int ReqSubMarketDataFinished(ReqSubMarketDataFinishedField* reqSubMarketDataFinished, int requestID) override;
	virtual int ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID) override;
	virtual int ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID) override;

private:
	BackTestApi* m_BackTestApi;
};
