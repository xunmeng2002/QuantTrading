#pragma once
#include "MdApiBase.h"
#include <Spark/Network/Protocol/Package.h>


namespace quanttrading
{
class MdApiImpl : public MdApiBase
{
public:
	MdApiImpl();
	virtual void OnMessage(spark::network::Package* package) override;
	
	virtual int ReqMdUserLogin(const ReqMdUserLoginField* reqMdUserLogin, int requestID) override;
	virtual int ReqMdUserLogout(const ReqMdUserLogoutField* reqMdUserLogout, int requestID) override;
	virtual int ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestID) override;
	virtual int ReqUnSubMarketData(const ReqUnSubMarketDataField* reqUnSubMarketData, int requestID) override;
};
}
