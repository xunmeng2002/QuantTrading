#pragma once
#include "MdFields.h"

#ifdef WIN32
#define MD_CAPI_CALL _stdcall
#ifdef LIB_MD_CAPI_EXPORT
#define MD_CAPI_EXPORT __declspec(dllexport)
#else
#define MD_CAPI_EXPORT __declspec(dllimport)
#endif
#else
#define MD_CAPI_CALL
#define MD_CAPI_EXPORT
#endif


extern "C"
{
	typedef MD_CAPI_EXPORT void (MD_CAPI_CALL *OnConnected)();
	typedef MD_CAPI_EXPORT void (MD_CAPI_CALL *OnDisConnected)();
	typedef MD_CAPI_EXPORT void (MD_CAPI_CALL *OnRspMdUserLogin)(RspInfoField* rspInfo, RspMdUserLoginField* rspMdUserLogin, int requestID, bool isLast);
	typedef MD_CAPI_EXPORT void (MD_CAPI_CALL *OnRspSubMarketData)(RspInfoField* rspInfo, RspSubMarketDataField* rspSubMarketData, int requestID, bool isLast);
	typedef MD_CAPI_EXPORT void (MD_CAPI_CALL *OnRspUnSubMarketData)(RspInfoField* rspInfo, RspUnSubMarketDataField* rspUnSubMarketData, int requestID, bool isLast);
	typedef MD_CAPI_EXPORT void (MD_CAPI_CALL *OnRtnDepthMarketData)(DepthMarketDataField* depthMarketData);
	typedef MD_CAPI_EXPORT void (MD_CAPI_CALL *OnRtnBarMarketData)(BarMarketDataField* barMarketData);
	
	struct MD_CAPI_EXPORT MdCSpi
	{
	public:
		OnConnected OnConnected;
		OnDisConnected OnDisConnected;
		OnRspMdUserLogin OnRspMdUserLogin;
		OnRspSubMarketData OnRspSubMarketData;
		OnRspUnSubMarketData OnRspUnSubMarketData;
		OnRtnDepthMarketData OnRtnDepthMarketData;
		OnRtnBarMarketData OnRtnBarMarketData;
	};

	MD_CAPI_EXPORT void MD_CAPI_CALL CreateMdApi();
	MD_CAPI_EXPORT const char* MD_CAPI_CALL GetApiVersion();
	MD_CAPI_EXPORT void MD_CAPI_CALL Init();
	MD_CAPI_EXPORT void MD_CAPI_CALL Join();
	MD_CAPI_EXPORT void MD_CAPI_CALL Release();
	MD_CAPI_EXPORT void MD_CAPI_CALL RegisterFront(const char* address);
	MD_CAPI_EXPORT void MD_CAPI_CALL RegisterSpi(MdCSpi* spi);
	MD_CAPI_EXPORT int MD_CAPI_CALL ReqMdUserLogin(ReqMdUserLoginField* reqMdUserLogin, int requestID);
	MD_CAPI_EXPORT int MD_CAPI_CALL ReqSubMarketData(ReqSubMarketDataField* reqSubMarketData, int requestID);
	MD_CAPI_EXPORT int MD_CAPI_CALL ReqUnSubMarketData(ReqUnSubMarketDataField* reqUnSubMarketData, int requestID);
}
