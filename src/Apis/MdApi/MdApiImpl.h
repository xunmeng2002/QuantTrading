// 本文件由 ../Templates/Cpp/Api/ApiImpl.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include "MdApiBase.h"
#include <Spark/Network/Protocol/Package.h>


namespace QuantTrading
{
class MdApiImpl : public MdApiBase
{
public:
	MdApiImpl();
	virtual void OnMessage(Spark::Network::Package* package) override;
	
	virtual int ReqMdUserLogin(const ReqMdUserLoginField* reqMdUserLogin, int requestId) override;
	virtual int ReqMdUserLogout(const ReqMdUserLogoutField* reqMdUserLogout, int requestId) override;
	virtual int ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestId) override;
	virtual int ReqUnSubMarketData(const ReqUnSubMarketDataField* reqUnSubMarketData, int requestId) override;
};
}
