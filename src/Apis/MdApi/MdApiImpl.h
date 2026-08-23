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
	
	virtual int ReqMdUserLogin(ReqMdUserLoginField* reqMdUserLogin, int requestID) override;
	virtual int ReqMdUserLogout(ReqMdUserLogoutField* reqMdUserLogout, int requestID) override;
	virtual int ReqSubMarketData(ReqSubMarketDataField* reqSubMarketData, int requestID) override;
	virtual int ReqUnSubMarketData(ReqUnSubMarketDataField* reqUnSubMarketData, int requestID) override;
};
}
