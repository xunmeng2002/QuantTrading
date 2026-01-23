#include "TradeCApi.h"
#include "TradeApi.h"
#include "TradeSpiWrap.h"
#include "Encode.h"
#include "Logger.h"
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
void SetExternLogger(WriteLogFunc externLogger)
{
	Logger::SetExternLogger(externLogger);
}
const char* GetApiVersion()
{
	return s_TradeApi->GetApiVersion();
}
bool Init()
{
	return s_TradeApi->Init();
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
#ifdef WINDOWS
	TrunsferGbkToUtf8(reqAccountLogin->AccountID);
	TrunsferGbkToUtf8(reqAccountLogin->Password);
#endif

	return s_TradeApi->ReqAccountLogin(reqAccountLogin, requestID);
}
int ReqAccountLogout(ReqAccountLogoutField* reqAccountLogout, int requestID)
{
#ifdef WINDOWS
	TrunsferGbkToUtf8(reqAccountLogout->AccountID);
#endif

	return s_TradeApi->ReqAccountLogout(reqAccountLogout, requestID);
}
int ReqQryHolderAccount(ReqQryHolderAccountField* reqQryHolderAccount, int requestID)
{
#ifdef WINDOWS
	TrunsferGbkToUtf8(reqQryHolderAccount->AccountID);
#endif

	return s_TradeApi->ReqQryHolderAccount(reqQryHolderAccount, requestID);
}
int ReqQryCapital(ReqQryCapitalField* reqQryCapital, int requestID)
{
#ifdef WINDOWS
	TrunsferGbkToUtf8(reqQryCapital->AccountID);
#endif

	return s_TradeApi->ReqQryCapital(reqQryCapital, requestID);
}
int ReqQryPosition(ReqQryPositionField* reqQryPosition, int requestID)
{
#ifdef WINDOWS
	TrunsferGbkToUtf8(reqQryPosition->AccountID);
#endif

	return s_TradeApi->ReqQryPosition(reqQryPosition, requestID);
}
int ReqQryOrder(ReqQryOrderField* reqQryOrder, int requestID)
{
#ifdef WINDOWS
	TrunsferGbkToUtf8(reqQryOrder->AccountID);
#endif

	return s_TradeApi->ReqQryOrder(reqQryOrder, requestID);
}
int ReqQryTrade(ReqQryTradeField* reqQryTrade, int requestID)
{
#ifdef WINDOWS
	TrunsferGbkToUtf8(reqQryTrade->AccountID);
#endif

	return s_TradeApi->ReqQryTrade(reqQryTrade, requestID);
}
int ReqQryInstrument(ReqQryInstrumentField* reqQryInstrument, int requestID)
{
#ifdef WINDOWS
	TrunsferGbkToUtf8(reqQryInstrument->ExchangeID);
	TrunsferGbkToUtf8(reqQryInstrument->InstrumentID);
#endif

	return s_TradeApi->ReqQryInstrument(reqQryInstrument, requestID);
}
int ReqQryOptionInstrument(ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestID)
{
#ifdef WINDOWS
	TrunsferGbkToUtf8(reqQryOptionInstrument->ExchangeID);
	TrunsferGbkToUtf8(reqQryOptionInstrument->InstrumentID);
#endif

	return s_TradeApi->ReqQryOptionInstrument(reqQryOptionInstrument, requestID);
}
int ReqQryCommissionRate(ReqQryCommissionRateField* reqQryCommissionRate, int requestID)
{
#ifdef WINDOWS
	TrunsferGbkToUtf8(reqQryCommissionRate->AccountID);
	TrunsferGbkToUtf8(reqQryCommissionRate->ExchangeID);
#endif

	return s_TradeApi->ReqQryCommissionRate(reqQryCommissionRate, requestID);
}
int ReqQryMoneyTransfer(ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestID)
{
#ifdef WINDOWS
	TrunsferGbkToUtf8(reqQryMoneyTransfer->AccountID);
#endif

	return s_TradeApi->ReqQryMoneyTransfer(reqQryMoneyTransfer, requestID);
}
int ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID)
{
#ifdef WINDOWS
	TrunsferGbkToUtf8(reqInsertOrder->AccountID);
	TrunsferGbkToUtf8(reqInsertOrder->ExchangeID);
	TrunsferGbkToUtf8(reqInsertOrder->InstrumentID);
#endif

	return s_TradeApi->ReqInsertOrder(reqInsertOrder, requestID);
}
int ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID)
{
#ifdef WINDOWS
	TrunsferGbkToUtf8(reqCancelOrder->AccountID);
	TrunsferGbkToUtf8(reqCancelOrder->ExchangeID);
	TrunsferGbkToUtf8(reqCancelOrder->InstrumentID);
	TrunsferGbkToUtf8(reqCancelOrder->OrderSysID);
#endif

	return s_TradeApi->ReqCancelOrder(reqCancelOrder, requestID);
}

