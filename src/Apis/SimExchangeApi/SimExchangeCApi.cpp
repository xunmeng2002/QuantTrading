#include <QuantTrading/SimExchangeCApi.h>
#include <QuantTrading/SimExchangeApi.h>
#include "SimExchangeSpiWrap.h"

using namespace quanttrading;

static SimExchangeApi* s_SimExchangeApi = nullptr;
static SimExchangeSpiWrap* s_SimExchangeSpiWrap = nullptr;

SIMEXCHANGEAPI_EXPORTS void SIMEXCHANGEAPI_CALL  CreateSimExchangeCApi()
{
	if (s_SimExchangeApi == nullptr)
	{
		s_SimExchangeApi = SimExchangeApi::CreateSimExchangeApi();
	}
	if (s_SimExchangeSpiWrap == nullptr)
	{
		s_SimExchangeSpiWrap = new SimExchangeSpiWrap();
	}
}
SIMEXCHANGEAPI_EXPORTS const char* SIMEXCHANGEAPI_CALL GetApiVersion()
{
	return s_SimExchangeApi->GetApiVersion();
}
SIMEXCHANGEAPI_EXPORTS bool SIMEXCHANGEAPI_CALL Init()
{
	return s_SimExchangeApi->Init();
}
SIMEXCHANGEAPI_EXPORTS void SIMEXCHANGEAPI_CALL Join()
{
	s_SimExchangeApi->Join();
}
SIMEXCHANGEAPI_EXPORTS void SIMEXCHANGEAPI_CALL Release()
{
	if (s_SimExchangeApi != nullptr)
	{
		s_SimExchangeApi->Release();
	}
	s_SimExchangeApi = nullptr;
	if (s_SimExchangeSpiWrap != nullptr)
	{
		delete s_SimExchangeSpiWrap;
	}
	s_SimExchangeSpiWrap = nullptr;
}
SIMEXCHANGEAPI_EXPORTS void SIMEXCHANGEAPI_CALL RegisterFront(const char* address)
{
	s_SimExchangeApi->RegisterFront(address);
}
SIMEXCHANGEAPI_EXPORTS void SIMEXCHANGEAPI_CALL RegisterSpi(SimExchangeCSpi* spi)
{
	s_SimExchangeApi->RegisterSpi(s_SimExchangeSpiWrap);
	s_SimExchangeSpiWrap->RegisterSpi(spi);
}

SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestID)
{
	return s_SimExchangeApi->ReqAccountLogin(reqAccountLogin, requestID);
}
SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestID)
{
	return s_SimExchangeApi->ReqAccountLogout(reqAccountLogout, requestID);
}
SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestID)
{
	return s_SimExchangeApi->ReqQryOrder(reqQryOrder, requestID);
}
SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestID)
{
	return s_SimExchangeApi->ReqQryTrade(reqQryTrade, requestID);
}
SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestID)
{
	return s_SimExchangeApi->ReqQryInstrument(reqQryInstrument, requestID);
}
SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestID)
{
	return s_SimExchangeApi->ReqInsertOrder(reqInsertOrder, requestID);
}
SIMEXCHANGEAPI_EXPORTS int SIMEXCHANGEAPI_CALL ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestID)
{
	return s_SimExchangeApi->ReqCancelOrder(reqCancelOrder, requestID);
}

