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
	virtual void OnMessage(Spark::network::Package* package) override;
	
	virtual int ReqMdUserLogin(const ReqMdUserLoginField* reqMdUserLogin, int requestID) override;
	virtual int ReqMdUserLogout(const ReqMdUserLogoutField* reqMdUserLogout, int requestID) override;
	virtual int ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestID) override;
	virtual int ReqUnSubMarketData(const ReqUnSubMarketDataField* reqUnSubMarketData, int requestID) override;
};
}
