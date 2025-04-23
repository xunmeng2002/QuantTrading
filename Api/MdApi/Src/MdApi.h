#pragma once
#include "MdFields.h"

#ifdef WIN32
#ifdef LIB_MD_API_EXPORT
#define MD_API_EXPORT				__declspec(dllexport)
#else
#define MD_API_EXPORT				__declspec(dllimport)
#endif
#else
#define MD_API_EXPORT
#endif


class MdSpi
{
public:
	virtual void OnConnected() {}
	virtual void OnDisConnected() {}
	virtual void OnRspMdUserLogin(RspInfoField* rspInfo, RspMdUserLoginField* rspMdUserLogin, int requestID, bool isLast) {}
	virtual void OnRspSubMarketData(RspInfoField* rspInfo, RspSubMarketDataField* rspSubMarketData, int requestID, bool isLast) {}
	virtual void OnRspUnSubMarketData(RspInfoField* rspInfo, RspUnSubMarketDataField* rspUnSubMarketData, int requestID, bool isLast) {}
	virtual void OnRtnDepthMarketData(DepthMarketDataField* depthMarketData) {}
	virtual void OnRtnBarMarketData(BarMarketDataField* barMarketData) {}
};

class MD_API_EXPORT MdApi
{
public:
	static MdApi* CreateMdApi(const char* logPath = "");
	static const char* GetApiVersion();
	virtual void Init() = 0;
	virtual void Join() = 0;
	virtual void Release() = 0;
	virtual void RegisterFront(const char* address) = 0;
	virtual void RegisterSpi(MdSpi* pSpi) = 0;
	
	virtual int ReqMdUserLogin(ReqMdUserLoginField* reqMdUserLogin, int requestID) = 0;
	virtual int ReqSubMarketData(ReqSubMarketDataField* reqSubMarketData, int requestID) = 0;
	virtual int ReqUnSubMarketData(ReqUnSubMarketDataField* reqUnSubMarketData, int requestID) = 0;
};

