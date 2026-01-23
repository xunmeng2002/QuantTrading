#pragma once
#include "MdbStructs.h"
#include "BackTestApi.h"

class SimExchange;
class BackTestApiImpl : public BackTestApi
{
public:
	BackTestApiImpl();
	~BackTestApiImpl();

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
	SimExchange* m_SimExchange;
};


