#pragma once
#include "Fields.h"
#include <QuantTrading/MdApi/MdApiExport.h>


class MdSpi
{
public:
	virtual void OnConnected() {}
	virtual void OnDisConnected() {}
	virtual void OnRspMdUserLogin(RspMdUserLoginField* rspMdUserLogin, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspMdUserLogout(RspMdUserLogoutField* rspMdUserLogout, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspSubMarketData(RspSubMarketDataField* rspSubMarketData, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspUnSubMarketData(RspUnSubMarketDataField* rspUnSubMarketData, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRtnDepthMarketData(DepthMarketDataField* depthMarketData) {}
	virtual void OnRtnBarMarketData(BarMarketDataField* barMarketData) {}
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
	
	virtual int ReqMdUserLogin(ReqMdUserLoginField* reqMdUserLogin, int requestID) = 0;
	virtual int ReqMdUserLogout(ReqMdUserLogoutField* reqMdUserLogout, int requestID) = 0;
	virtual int ReqSubMarketData(ReqSubMarketDataField* reqSubMarketData, int requestID) = 0;
	virtual int ReqUnSubMarketData(ReqUnSubMarketDataField* reqUnSubMarketData, int requestID) = 0;
};

