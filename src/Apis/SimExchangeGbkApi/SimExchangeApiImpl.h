// 本文件由 ../Templates/Cpp/Api/ApiImpl.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include "SimExchangeApiBase.h"
#include <Spark/Network/Protocol/Package.h>


namespace QuantTrading
{
class SimExchangeApiImpl : public SimExchangeApiBase
{
public:
	SimExchangeApiImpl();
	virtual void OnMessage(Spark::Network::Package* package) override;
	
	virtual int ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestId) override;
	virtual int ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestId) override;
	virtual int ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestId) override;
	virtual int ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestId) override;
	virtual int ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestId) override;
	virtual int ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestId) override;
	virtual int ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestId) override;
};
}
