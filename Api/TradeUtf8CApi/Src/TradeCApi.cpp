#include "TradeCApi.h"
#include "TradeApi.h"
#include "TradeSpiWrap.h"
#include "Encode.h"
#include <cstring>

static TradeApi* s_TradeApi = nullptr;
static TradeSpiWrap* s_TradeSpiWrap = nullptr;

void CreateTradeApi()
{
	if (s_TradeApi == nullptr)
	{
		s_TradeApi = TradeApi::CreateTradeApi();
	}
	if (s_TradeSpiWrap == nullptr)
	{
		s_TradeSpiWrap = new TradeSpiWrap();
	}
}
const char* GetApiVersion()
{
	return s_TradeApi->GetApiVersion();
}
void Init()
{
	s_TradeApi->Init();
}
void Join()
{
	s_TradeApi->Join();
}
void Release()
{
	if (s_TradeApi != nullptr)
	{
		s_TradeApi->Release();
	}
	s_TradeApi = nullptr;
	if (s_TradeSpiWrap != nullptr)
	{
		delete s_TradeSpiWrap;
	}
	s_TradeSpiWrap = nullptr;
}
void RegisterFront(const char* address)
{
	s_TradeApi->RegisterFront(address);
}
void RegisterSpi(TradeCSpi* spi)
{
	s_TradeApi->RegisterSpi(s_TradeSpiWrap);
	s_TradeSpiWrap->RegisterSpi(spi);
}

int ReqAccountLogin(ReqAccountLoginField* reqAccountLogin, int requestID)
{
	return s_TradeApi->ReqAccountLogin(reqAccountLogin, requestID);
}
int ReqAccountLogout(ReqAccountLogoutField* reqAccountLogout, int requestID)
{
	return s_TradeApi->ReqAccountLogout(reqAccountLogout, requestID);
}
int ReqQryHolderAccount(ReqQryHolderAccountField* reqQryHolderAccount, int requestID)
{
	return s_TradeApi->ReqQryHolderAccount(reqQryHolderAccount, requestID);
}
int ReqQryCapital(ReqQryCapitalField* reqQryCapital, int requestID)
{
	return s_TradeApi->ReqQryCapital(reqQryCapital, requestID);
}
int ReqQryPosition(ReqQryPositionField* reqQryPosition, int requestID)
{
	return s_TradeApi->ReqQryPosition(reqQryPosition, requestID);
}
int ReqQryOrder(ReqQryOrderField* reqQryOrder, int requestID)
{
	return s_TradeApi->ReqQryOrder(reqQryOrder, requestID);
}
int ReqQryTrade(ReqQryTradeField* reqQryTrade, int requestID)
{
	return s_TradeApi->ReqQryTrade(reqQryTrade, requestID);
}
int ReqQryInstrument(ReqQryInstrumentField* reqQryInstrument, int requestID)
{
	return s_TradeApi->ReqQryInstrument(reqQryInstrument, requestID);
}
int ReqQryOptionInstrument(ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestID)
{
	return s_TradeApi->ReqQryOptionInstrument(reqQryOptionInstrument, requestID);
}
int ReqQryCommissionRate(ReqQryCommissionRateField* reqQryCommissionRate, int requestID)
{
	return s_TradeApi->ReqQryCommissionRate(reqQryCommissionRate, requestID);
}
int ReqQryMoneyTransfer(ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestID)
{
	return s_TradeApi->ReqQryMoneyTransfer(reqQryMoneyTransfer, requestID);
}
int ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID)
{
	return s_TradeApi->ReqInsertOrder(reqInsertOrder, requestID);
}
int ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID)
{
	return s_TradeApi->ReqCancelOrder(reqCancelOrder, requestID);
}

