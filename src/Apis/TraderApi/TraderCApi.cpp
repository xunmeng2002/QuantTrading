#include <QuantTrading/TraderCApi.h>
#include <QuantTrading/TraderApi.h>
#include "TraderSpiWrap.h"

using namespace quanttrading;

static TraderApi* s_TraderApi = nullptr;
static TraderSpiWrap* s_TraderSpiWrap = nullptr;

TRADERAPI_EXPORTS void TRADERAPI_CALL  CreateTraderCApi()
{
	if (s_TraderApi == nullptr)
	{
		s_TraderApi = TraderApi::CreateTraderApi();
	}
	if (s_TraderSpiWrap == nullptr)
	{
		s_TraderSpiWrap = new TraderSpiWrap();
	}
}
TRADERAPI_EXPORTS const char* TRADERAPI_CALL GetApiVersion()
{
	return s_TraderApi->GetApiVersion();
}
TRADERAPI_EXPORTS bool TRADERAPI_CALL Init()
{
	return s_TraderApi->Init();
}
TRADERAPI_EXPORTS void TRADERAPI_CALL Join()
{
	s_TraderApi->Join();
}
TRADERAPI_EXPORTS void TRADERAPI_CALL Release()
{
	if (s_TraderApi != nullptr)
	{
		s_TraderApi->Release();
	}
	s_TraderApi = nullptr;
	if (s_TraderSpiWrap != nullptr)
	{
		delete s_TraderSpiWrap;
	}
	s_TraderSpiWrap = nullptr;
}
TRADERAPI_EXPORTS void TRADERAPI_CALL RegisterFront(const char* address)
{
	s_TraderApi->RegisterFront(address);
}
TRADERAPI_EXPORTS void TRADERAPI_CALL RegisterSpi(TraderCSpi* spi)
{
	s_TraderApi->RegisterSpi(s_TraderSpiWrap);
	s_TraderSpiWrap->RegisterSpi(spi);
}

TRADERAPI_EXPORTS int TRADERAPI_CALL ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestID)
{
	return s_TraderApi->ReqAccountLogin(reqAccountLogin, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestID)
{
	return s_TraderApi->ReqAccountLogout(reqAccountLogout, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryHolderAccount(const ReqQryHolderAccountField* reqQryHolderAccount, int requestID)
{
	return s_TraderApi->ReqQryHolderAccount(reqQryHolderAccount, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryCapital(const ReqQryCapitalField* reqQryCapital, int requestID)
{
	return s_TraderApi->ReqQryCapital(reqQryCapital, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryPosition(const ReqQryPositionField* reqQryPosition, int requestID)
{
	return s_TraderApi->ReqQryPosition(reqQryPosition, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestID)
{
	return s_TraderApi->ReqQryOrder(reqQryOrder, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestID)
{
	return s_TraderApi->ReqQryTrade(reqQryTrade, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestID)
{
	return s_TraderApi->ReqQryInstrument(reqQryInstrument, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryOptionInstrument(const ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestID)
{
	return s_TraderApi->ReqQryOptionInstrument(reqQryOptionInstrument, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryCommissionRate(const ReqQryCommissionRateField* reqQryCommissionRate, int requestID)
{
	return s_TraderApi->ReqQryCommissionRate(reqQryCommissionRate, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryMoneyTransfer(const ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestID)
{
	return s_TraderApi->ReqQryMoneyTransfer(reqQryMoneyTransfer, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestID)
{
	return s_TraderApi->ReqInsertOrder(reqInsertOrder, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestID)
{
	return s_TraderApi->ReqCancelOrder(reqCancelOrder, requestID);
}

