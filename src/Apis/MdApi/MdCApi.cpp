// 本文件由 ../Templates/Cpp/Api/CApi.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include <QuantTrading/MdCApi.h>
#include <QuantTrading/MdApi.h>
#include "MdSpiWrap.h"

using namespace QuantTrading;

static MdApi* MdApiInstance = nullptr;
static MdSpiWrap* MdSpiWrapInstance = nullptr;

MDAPI_EXPORTS void MDAPI_CALL  CreateMdCApi()
{
	if (MdApiInstance == nullptr)
	{
		MdApiInstance = MdApi::CreateMdApi();
	}
	if (MdSpiWrapInstance == nullptr)
	{
		MdSpiWrapInstance = new MdSpiWrap();
	}
}
MDAPI_EXPORTS const char* MDAPI_CALL GetApiVersion()
{
	return MdApiInstance->GetApiVersion();
}
MDAPI_EXPORTS bool MDAPI_CALL Init()
{
	return MdApiInstance->Init();
}
MDAPI_EXPORTS void MDAPI_CALL Join()
{
	MdApiInstance->Join();
}
MDAPI_EXPORTS void MDAPI_CALL Release()
{
	if (MdApiInstance != nullptr)
	{
		MdApiInstance->Release();
	}
	MdApiInstance = nullptr;
	if (MdSpiWrapInstance != nullptr)
	{
		delete MdSpiWrapInstance;
	}
	MdSpiWrapInstance = nullptr;
}
MDAPI_EXPORTS void MDAPI_CALL RegisterFront(const char* address)
{
	MdApiInstance->RegisterFront(address);
}
MDAPI_EXPORTS void MDAPI_CALL RegisterSpi(MdCSpi* spi)
{
	MdApiInstance->RegisterSpi(MdSpiWrapInstance);
	MdSpiWrapInstance->RegisterSpi(spi);
}

MDAPI_EXPORTS int MDAPI_CALL ReqMdUserLogin(const ReqMdUserLoginField* reqMdUserLogin, int requestID)
{
	return MdApiInstance->ReqMdUserLogin(reqMdUserLogin, requestID);
}
MDAPI_EXPORTS int MDAPI_CALL ReqMdUserLogout(const ReqMdUserLogoutField* reqMdUserLogout, int requestID)
{
	return MdApiInstance->ReqMdUserLogout(reqMdUserLogout, requestID);
}
MDAPI_EXPORTS int MDAPI_CALL ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestID)
{
	return MdApiInstance->ReqSubMarketData(reqSubMarketData, requestID);
}
MDAPI_EXPORTS int MDAPI_CALL ReqUnSubMarketData(const ReqUnSubMarketDataField* reqUnSubMarketData, int requestID)
{
	return MdApiInstance->ReqUnSubMarketData(reqUnSubMarketData, requestID);
}

