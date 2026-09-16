// 本文件由 ../Templates/Cpp/Api/CApi.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include <QuantTrading/SimExchangeCApi.h>
#include <QuantTrading/SimExchangeApi.h>
#include "SimExchangeSpiWrap.h"

using namespace QuantTrading;

static SimExchangeApi* SimExchangeApiInstance = nullptr;
static SimExchangeSpiWrap* SimExchangeSpiWrapInstance = nullptr;

SIMEXCHANGEAPI_EXPORTS void SIMEXCHANGEAPI_CALL  CreateSimExchangeCApi()
{
	if (SimExchangeApiInstance == nullptr)
	{
		SimExchangeApiInstance = SimExchangeApi::CreateSimExchangeApi();
	}
	if (SimExchangeSpiWrapInstance == nullptr)
	{
		SimExchangeSpiWrapInstance = new SimExchangeSpiWrap();
	}
}
SIMEXCHANGEAPI_EXPORTS const char* SIMEXCHANGEAPI_CALL GetApiVersion()
{
	return SimExchangeApiInstance->GetApiVersion();
}
SIMEXCHANGEAPI_EXPORTS bool SIMEXCHANGEAPI_CALL Init()
{
	return SimExchangeApiInstance->Init();
}
SIMEXCHANGEAPI_EXPORTS void SIMEXCHANGEAPI_CALL Join()
{
	SimExchangeApiInstance->Join();
}
SIMEXCHANGEAPI_EXPORTS void SIMEXCHANGEAPI_CALL Release()
{
	if (SimExchangeApiInstance != nullptr)
	{
		SimExchangeApiInstance->Release();
	}
	SimExchangeApiInstance = nullptr;
	if (SimExchangeSpiWrapInstance != nullptr)
	{
		delete SimExchangeSpiWrapInstance;
	}
	SimExchangeSpiWrapInstance = nullptr;
}
SIMEXCHANGEAPI_EXPORTS void SIMEXCHANGEAPI_CALL RegisterFront(const char* address)
{
	SimExchangeApiInstance->RegisterFront(address);
}
SIMEXCHANGEAPI_EXPORTS void SIMEXCHANGEAPI_CALL RegisterSpi(SimExchangeCSpi* spi)
{
	SimExchangeApiInstance->RegisterSpi(SimExchangeSpiWrapInstance);
	SimExchangeSpiWrapInstance->RegisterSpi(spi);
}

SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestID)
{
	return SimExchangeApiInstance->ReqAccountLogin(reqAccountLogin, requestID);
}
SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestID)
{
	return SimExchangeApiInstance->ReqAccountLogout(reqAccountLogout, requestID);
}
SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestID)
{
	return SimExchangeApiInstance->ReqQryOrder(reqQryOrder, requestID);
}
SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestID)
{
	return SimExchangeApiInstance->ReqQryTrade(reqQryTrade, requestID);
}
SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestID)
{
	return SimExchangeApiInstance->ReqQryInstrument(reqQryInstrument, requestID);
}
SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestID)
{
	return SimExchangeApiInstance->ReqInsertOrder(reqInsertOrder, requestID);
}
SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestID)
{
	return SimExchangeApiInstance->ReqCancelOrder(reqCancelOrder, requestID);
}

