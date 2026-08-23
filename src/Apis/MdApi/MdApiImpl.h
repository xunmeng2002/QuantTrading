#pragma once
#include "MdApiBase.h"


namespace quanttrading
{
class MdApiImpl : public MdApiBase
{
public:
	MdApiImpl();
	virtual void OnMessage(Package* package) override;
	
	virtual int ReqMdUserLogin(ReqMdUserLoginField* reqMdUserLogin, int requestID) override;
	virtual int ReqMdUserLogout(ReqMdUserLogoutField* reqMdUserLogout, int requestID) override;
	virtual int ReqSubMarketData(ReqSubMarketDataField* reqSubMarketData, int requestID) override;
	virtual int ReqUnSubMarketData(ReqUnSubMarketDataField* reqUnSubMarketData, int requestID) override;
};
}
