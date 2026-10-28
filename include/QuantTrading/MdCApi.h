// 本文件由 ../Templates/Cpp/Api/CApi.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include "Fields.h"
#include <QuantTrading/MdApi/MdApiExport.h>

#ifdef _WIN32
#define MDAPI_CALL _stdcall
#else
#define MDAPI_CALL
#endif


extern "C"
{
	typedef void (MDAPI_CALL *OnConnected)();
	typedef void (MDAPI_CALL *OnDisConnected)();
	typedef void (MDAPI_CALL *OnRspMdUserLogin)(const QuantTrading::RspMdUserLoginField* rspMdUserLogin, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (MDAPI_CALL *OnRspMdUserLogout)(const QuantTrading::RspMdUserLogoutField* rspMdUserLogout, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (MDAPI_CALL *OnRspSubMarketData)(const QuantTrading::RspSubMarketDataField* rspSubMarketData, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (MDAPI_CALL *OnRspUnSubMarketData)(const QuantTrading::RspUnSubMarketDataField* rspUnSubMarketData, const QuantTrading::RspInfoField* rspInfo, int requestId, bool isLast);
	typedef void (MDAPI_CALL *OnRtnDepthMarketData)(const QuantTrading::DepthMarketDataField* depthMarketData);
	typedef void (MDAPI_CALL *OnRtnBarMarketData)(const QuantTrading::BarMarketDataField* barMarketData);
	
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
	MDAPI_EXPORTS int MDAPI_CALL ReqMdUserLogin(const QuantTrading::ReqMdUserLoginField* reqMdUserLogin, int requestId);
	MDAPI_EXPORTS int MDAPI_CALL ReqMdUserLogout(const QuantTrading::ReqMdUserLogoutField* reqMdUserLogout, int requestId);
	MDAPI_EXPORTS int MDAPI_CALL ReqSubMarketData(const QuantTrading::ReqSubMarketDataField* reqSubMarketData, int requestId);
	MDAPI_EXPORTS int MDAPI_CALL ReqUnSubMarketData(const QuantTrading::ReqUnSubMarketDataField* reqUnSubMarketData, int requestId);
}
