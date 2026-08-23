#pragma once
#include "Fields.h"
#include <QuantTrading/MdApi/MdApiExport.h>

#ifdef WIN32
#define MDAPI_CALL _stdcall
#else
#define MDAPI_CALL
#endif


extern "C"
{
	typedef void (MDAPI_CALL *OnConnected)();
	typedef void (MDAPI_CALL *OnDisConnected)();
	typedef void (MDAPI_CALL *OnRspMdUserLogin)(const RspMdUserLoginField* rspMdUserLogin, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (MDAPI_CALL *OnRspMdUserLogout)(const RspMdUserLogoutField* rspMdUserLogout, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (MDAPI_CALL *OnRspSubMarketData)(const RspSubMarketDataField* rspSubMarketData, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (MDAPI_CALL *OnRspUnSubMarketData)(const RspUnSubMarketDataField* rspUnSubMarketData, const RspInfoField* rspInfo, int requestID, bool isLast);
	typedef void (MDAPI_CALL *OnRtnDepthMarketData)(const DepthMarketDataField* depthMarketData);
	typedef void (MDAPI_CALL *OnRtnBarMarketData)(const BarMarketDataField* barMarketData);
	
	struct MdCSpi
	{
	public:
		OnConnected OnConnected;
		OnDisConnected OnDisConnected;
		OnRspMdUserLogin OnRspMdUserLogin;
		OnRspMdUserLogout OnRspMdUserLogout;
		OnRspSubMarketData OnRspSubMarketData;
		OnRspUnSubMarketData OnRspUnSubMarketData;
		OnRtnDepthMarketData OnRtnDepthMarketData;
		OnRtnBarMarketData OnRtnBarMarketData;
	};

	MDAPI_EXPORTS void MDAPI_CALL CreateMdCApi();
	MDAPI_EXPORTS const char* MDAPI_CALL GetApiVersion();
	MDAPI_EXPORTS bool MDAPI_CALL Init();
	MDAPI_EXPORTS void MDAPI_CALL Join();
	MDAPI_EXPORTS void MDAPI_CALL Release();
	MDAPI_EXPORTS void MDAPI_CALL RegisterFront(const char* address);
	MDAPI_EXPORTS void MDAPI_CALL RegisterSpi(MdCSpi* spi);
	MDAPI_EXPORTS int MDAPI_CALL ReqMdUserLogin(const ReqMdUserLoginField* reqMdUserLogin, int requestID);
	MDAPI_EXPORTS int MDAPI_CALL ReqMdUserLogout(const ReqMdUserLogoutField* reqMdUserLogout, int requestID);
	MDAPI_EXPORTS int MDAPI_CALL ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestID);
	MDAPI_EXPORTS int MDAPI_CALL ReqUnSubMarketData(const ReqUnSubMarketDataField* reqUnSubMarketData, int requestID);
}
