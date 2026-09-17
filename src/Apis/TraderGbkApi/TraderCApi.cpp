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

TRADERAPI_EXPORTS int TRADERAPI_CALL ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestId)
{
	return TraderApiInstance->ReqAccountLogin(reqAccountLogin, requestId);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestId)
{
	return TraderApiInstance->ReqAccountLogout(reqAccountLogout, requestId);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryHolderAccount(const ReqQryHolderAccountField* reqQryHolderAccount, int requestId)
{
	return TraderApiInstance->ReqQryHolderAccount(reqQryHolderAccount, requestId);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryCapital(const ReqQryCapitalField* reqQryCapital, int requestId)
{
	return TraderApiInstance->ReqQryCapital(reqQryCapital, requestId);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryPosition(const ReqQryPositionField* reqQryPosition, int requestId)
{
	return TraderApiInstance->ReqQryPosition(reqQryPosition, requestId);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestId)
{
	return TraderApiInstance->ReqQryOrder(reqQryOrder, requestId);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestId)
{
	return TraderApiInstance->ReqQryTrade(reqQryTrade, requestId);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestId)
{
	return TraderApiInstance->ReqQryInstrument(reqQryInstrument, requestId);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryOptionInstrument(const ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestId)
{
	return TraderApiInstance->ReqQryOptionInstrument(reqQryOptionInstrument, requestId);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryCommissionRate(const ReqQryCommissionRateField* reqQryCommissionRate, int requestId)
{
	return TraderApiInstance->ReqQryCommissionRate(reqQryCommissionRate, requestId);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqQryMoneyTransfer(const ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestId)
{
	return TraderApiInstance->ReqQryMoneyTransfer(reqQryMoneyTransfer, requestId);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestId)
{
	return TraderApiInstance->ReqInsertOrder(reqInsertOrder, requestId);
}
TRADERAPI_EXPORTS int TRADERAPI_CALL ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestId)
{
	return TraderApiInstance->ReqCancelOrder(reqCancelOrder, requestId);
}

