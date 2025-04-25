#include "MdCApi.h"
#include "MdApi.h"
#include "MdSpiWrap.h"
#include "Encode.h"
#include <cstring>

static MdApi* s_MdApi = nullptr;
static MdSpiWrap* s_MdSpiWrap = nullptr;

void CreateMdApi()
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
const char* GetApiVersion()
{
	return s_MdApi->GetApiVersion();
}
void Init()
{
	s_MdApi->Init();
}
void Join()
{
	s_MdApi->Join();
}
void Release()
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
void RegisterFront(const char* address)
{
	s_MdApi->RegisterFront(address);
}
void RegisterSpi(MdCSpi* spi)
{
	s_MdApi->RegisterSpi(s_MdSpiWrap);
	s_MdSpiWrap->RegisterSpi(spi);
}

int ReqMdUserLogin(ReqMdUserLoginField* reqMdUserLogin, int requestID)
{
	return s_MdApi->ReqMdUserLogin(reqMdUserLogin, requestID);
}
int ReqMdUserLogout(ReqMdUserLogoutField* reqMdUserLogout, int requestID)
{
	return s_MdApi->ReqMdUserLogout(reqMdUserLogout, requestID);
}
int ReqSubMarketData(ReqSubMarketDataField* reqSubMarketData, int requestID)
{
	return s_MdApi->ReqSubMarketData(reqSubMarketData, requestID);
}
int ReqUnSubMarketData(ReqUnSubMarketDataField* reqUnSubMarketData, int requestID)
{
	return s_MdApi->ReqUnSubMarketData(reqUnSubMarketData, requestID);
}

