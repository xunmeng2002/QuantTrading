// 本文件由 ../Templates/Cpp/Api/CApi.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include <QuantTrading/TraderCApi.h>
#include <QuantTrading/TraderApi.h>
#include "TraderSpiWrap.h"

using namespace QuantTrading;

static TraderApi* TraderApiInstance = nullptr;
static TraderSpiWrap* TraderSpiWrapInstance = nullptr;

TRADERAPI_EXPORTS void TRADERAPI_CALL  CreateTraderCApi()
{
	if (TraderApiInstance == nullptr)
	{
		TraderApiInstance = TraderApi::CreateTraderApi();
	}
	if (TraderSpiWrapInstance == nullptr)
	{
		TraderSpiWrapInstance = new TraderSpiWrap();
	}
}
TRADERAPI_EXPORTS const char* TRADERAPI_CALL GetApiVersion()
{
	return TraderApiInstance->GetApiVersion();
}
TRADERAPI_EXPORTS bool TRADERAPI_CALL Init()
{
	return TraderApiInstance->Init();
}
TRADERAPI_EXPORTS void TRADERAPI_CALL Join()
{
	TraderApiInstance->Join();
}
TRADERAPI_EXPORTS void TRADERAPI_CALL Release()
{
	if (TraderApiInstance != nullptr)
	{
		TraderApiInstance->Release();
	}
	TraderApiInstance = nullptr;
	if (TraderSpiWrapInstance != nullptr)
	{
		delete TraderSpiWrapInstance;
	}
	TraderSpiWrapInstance = nullptr;
}
TRADERAPI_EXPORTS void TRADERAPI_CALL RegisterFront(const char* address)
{
	TraderApiInstance->RegisterFront(address);
}
TRADERAPI_EXPORTS void TRADERAPI_CALL RegisterSpi(TraderCSpi* spi)
{
	TraderApiInstance->RegisterSpi(TraderSpiWrapInstance);
	TraderSpiWrapInstance->RegisterSpi(spi);
}

TRADERAPI_EXPORTS int TRADERAPI_CALL ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestID)
{
	return TraderApiInstance->ReqAccountLogin(reqAccountLogin, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestID)
{
	return TraderApiInstance->ReqAccountLogout(reqAccountLogout, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryHolderAccount(const ReqQryHolderAccountField* reqQryHolderAccount, int requestID)
{
	return TraderApiInstance->ReqQryHolderAccount(reqQryHolderAccount, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryCapital(const ReqQryCapitalField* reqQryCapital, int requestID)
{
	return TraderApiInstance->ReqQryCapital(reqQryCapital, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryPosition(const ReqQryPositionField* reqQryPosition, int requestID)
{
	return TraderApiInstance->ReqQryPosition(reqQryPosition, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestID)
{
	return TraderApiInstance->ReqQryOrder(reqQryOrder, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestID)
{
	return TraderApiInstance->ReqQryTrade(reqQryTrade, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestID)
{
	return TraderApiInstance->ReqQryInstrument(reqQryInstrument, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryOptionInstrument(const ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestID)
{
	return TraderApiInstance->ReqQryOptionInstrument(reqQryOptionInstrument, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryCommissionRate(const ReqQryCommissionRateField* reqQryCommissionRate, int requestID)
{
	return TraderApiInstance->ReqQryCommissionRate(reqQryCommissionRate, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryMoneyTransfer(const ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestID)
{
	return TraderApiInstance->ReqQryMoneyTransfer(reqQryMoneyTransfer, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestID)
{
	return TraderApiInstance->ReqInsertOrder(reqInsertOrder, requestID);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestID)
{
	return TraderApiInstance->ReqCancelOrder(reqCancelOrder, requestID);
}

