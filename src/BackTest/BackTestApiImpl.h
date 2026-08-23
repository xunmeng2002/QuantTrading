#pragma once
#include "MdbStructs.h"
#include "QuantTrading/BackTestApi.h"

namespace quanttrading::backtest
{
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

	virtual int ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestID) override;
	virtual int ReqSubMarketDataFinished(const ReqSubMarketDataFinishedField* reqSubMarketDataFinished, int requestID) override;
	virtual int ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestID) override;
	virtual int ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestID) override;

private:
	SimExchange* m_SimExchange;
};
}


