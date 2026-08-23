#include <QuantTrading/MdCApi.h>
#include <QuantTrading/MdApi.h>
#include "MdSpiWrap.h"

using namespace quanttrading;

static MdApi* s_MdApi = nullptr;
static MdSpiWrap* s_MdSpiWrap = nullptr;

MDAPI_EXPORTS void MDAPI_CALL  CreateMdCApi()
{
	if (s_MdApi == nullptr)
	{
		s_MdApi = MdApi::CreateMdApi();
	}
	if (s_MdSpiWrap == nullptr)
	{
		s_MdSpiWrap = new MdSpiWrap();
	}
}
MDAPI_EXPORTS const char* MDAPI_CALL GetApiVersion()
{
	return s_MdApi->GetApiVersion();
}
MDAPI_EXPORTS bool MDAPI_CALL Init()
{
	return s_MdApi->Init();
}
MDAPI_EXPORTS void MDAPI_CALL Join()
{
	s_MdApi->Join();
}
MDAPI_EXPORTS void MDAPI_CALL Release()
{
	if (s_MdApi != nullptr)
	{
		s_MdApi->Release();
	}
	s_MdApi = nullptr;
	if (s_MdSpiWrap != nullptr)
	{
		delete s_MdSpiWrap;
	}
	s_MdSpiWrap = nullptr;
}
MDAPI_EXPORTS void MDAPI_CALLRegisterFront(const char* address)
{
	s_MdApi->RegisterFront(address);
}
MDAPI_EXPORTS void MDAPI_CALL RegisterSpi(MdCSpi* spi)
{
	s_MdApi->RegisterSpi(s_MdSpiWrap);
	s_MdSpiWrap->RegisterSpi(spi);
}

MDAPI_EXPORTS int MDAPI_CALL ReqMdUserLogin(ReqMdUserLoginField* reqMdUserLogin, int requestID)
{
	return s_MdApi->ReqMdUserLogin(reqMdUserLogin, requestID);
}
MDAPI_EXPORTS int MDAPI_CALL ReqMdUserLogout(ReqMdUserLogoutField* reqMdUserLogout, int requestID)
{
	return s_MdApi->ReqMdUserLogout(reqMdUserLogout, requestID);
}
MDAPI_EXPORTS int MDAPI_CALL ReqSubMarketData(ReqSubMarketDataField* reqSubMarketData, int requestID)
{
	return s_MdApi->ReqSubMarketData(reqSubMarketData, requestID);
}
MDAPI_EXPORTS int MDAPI_CALL ReqUnSubMarketData(ReqUnSubMarketDataField* reqUnSubMarketData, int requestID)
{
	return s_MdApi->ReqUnSubMarketData(reqUnSubMarketData, requestID);
}

