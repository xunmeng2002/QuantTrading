#pragma once
#include "Fields.h"
#include <QuantTrading/MdApi/MdApiExport.h>

namespace quanttrading
{
class MdSpi
{
public:
	virtual void OnConnected() {}
	virtual void OnDisConnected() {}
	virtual void OnRspMdUserLogin(const RspMdUserLoginField* rspMdUserLogin, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspMdUserLogout(const RspMdUserLogoutField* rspMdUserLogout, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspSubMarketData(const RspSubMarketDataField* rspSubMarketData, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspUnSubMarketData(const RspUnSubMarketDataField* rspUnSubMarketData, const RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData) {}
	virtual void OnRtnBarMarketData(const BarMarketDataField* barMarketData) {}
};

class MDAPI_EXPORTS MdApi
{
public:
	static MdApi* CreateMdApi();
	static const char* GetApiVersion();
	virtual bool Init() = 0;
	virtual void Join() = 0;
	virtual void Release() = 0;
	virtual void RegisterFront(const char* address) = 0;
	virtual void RegisterSpi(MdSpi* pSpi) = 0;
	
	virtual int ReqMdUserLogin(const ReqMdUserLoginField* reqMdUserLogin, int requestID) = 0;
	virtual int ReqMdUserLogout(const ReqMdUserLogoutField* reqMdUserLogout, int requestID) = 0;
	virtual int ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestID) = 0;
	virtual int ReqUnSubMarketData(const ReqUnSubMarketDataField* reqUnSubMarketData, int requestID) = 0;
};
}
