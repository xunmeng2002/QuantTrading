// 本文件由 ../Templates/Cpp/ApiTest/ApiMiddle.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "TraderApiMiddle.h"
#include <Spark/Core/Logger/Logger.h>

using namespace Spark::core;


namespace QuantTrading
{
TraderApiMiddle* TraderApiMiddle::CreateTraderApiMiddle()
{
	WriteLog(LogLevel::Info, "CreateTraderApi");
	
	auto api = TraderApi::CreateTraderApi();
	auto apiMiddle = new TraderApiMiddle();
	apiMiddle->traderApi = api;
	
	return apiMiddle;
}
const char* TraderApiMiddle::GetApiVersion()
{
	WriteLog(LogLevel::Info, "GetApiVersion");
	return TraderApi::GetApiVersion();
}
bool TraderApiMiddle::Init()
{
	WriteLog(LogLevel::Info, "Init");
	return traderApi->Init();
}
void TraderApiMiddle::Join()
{
	WriteLog(LogLevel::Info, "Join");
	traderApi->Join();
}
void TraderApiMiddle::Release()
{
	WriteLog(LogLevel::Info, "Release");
	traderApi->Release();
}
void TraderApiMiddle::RegisterFront(const char* address)
{
	WriteLog(LogLevel::Info, "RegisterFront:%s", address);
	traderApi->RegisterFront(address);
}
void TraderApiMiddle::RegisterSpi(TraderSpi* pSpi)
{
	WriteLog(LogLevel::Info, "RegisterSpi");
	traderApi->RegisterSpi(pSpi);
}

int TraderApiMiddle::ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestID)
{
	WriteLog(LogLevel::Info, "ReqAccountLogin: RequestID:%d", requestID);
	if (reqAccountLogin != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqAccountLoginField:AccountId:[%s]",
			reqAccountLogin->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqAccountLogin is nullptr");
	}
	return traderApi->ReqAccountLogin(reqAccountLogin, requestID);
}
int TraderApiMiddle::ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestID)
{
	WriteLog(LogLevel::Info, "ReqAccountLogout: RequestID:%d", requestID);
	if (reqAccountLogout != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqAccountLogoutField:AccountId:[%s]",
			reqAccountLogout->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqAccountLogout is nullptr");
	}
	return traderApi->ReqAccountLogout(reqAccountLogout, requestID);
}
int TraderApiMiddle::ReqQryHolderAccount(const ReqQryHolderAccountField* reqQryHolderAccount, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQryHolderAccount: RequestID:%d", requestID);
	if (reqQryHolderAccount != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryHolderAccountField:AccountId:[%s]",
			reqQryHolderAccount->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryHolderAccount is nullptr");
	}
	return traderApi->ReqQryHolderAccount(reqQryHolderAccount, requestID);
}
int TraderApiMiddle::ReqQryCapital(const ReqQryCapitalField* reqQryCapital, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQryCapital: RequestID:%d", requestID);
	if (reqQryCapital != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryCapitalField:AccountId:[%s]",
			reqQryCapital->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryCapital is nullptr");
	}
	return traderApi->ReqQryCapital(reqQryCapital, requestID);
}
int TraderApiMiddle::ReqQryPosition(const ReqQryPositionField* reqQryPosition, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQryPosition: RequestID:%d", requestID);
	if (reqQryPosition != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryPositionField:AccountId:[%s]",
			reqQryPosition->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryPosition is nullptr");
	}
	return traderApi->ReqQryPosition(reqQryPosition, requestID);
}
int TraderApiMiddle::ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQryOrder: RequestID:%d", requestID);
	if (reqQryOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryOrderField:AccountId:[%s]",
			reqQryOrder->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryOrder is nullptr");
	}
	return traderApi->ReqQryOrder(reqQryOrder, requestID);
}
int TraderApiMiddle::ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQryTrade: RequestID:%d", requestID);
	if (reqQryTrade != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryTradeField:AccountId:[%s]",
			reqQryTrade->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryTrade is nullptr");
	}
	return traderApi->ReqQryTrade(reqQryTrade, requestID);
}
int TraderApiMiddle::ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQryInstrument: RequestID:%d", requestID);
	if (reqQryInstrument != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryInstrumentField:ExchangeId:[%s], InstrumentId:[%s]",
			reqQryInstrument->ExchangeId, reqQryInstrument->InstrumentId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryInstrument is nullptr");
	}
	return traderApi->ReqQryInstrument(reqQryInstrument, requestID);
}
int TraderApiMiddle::ReqQryOptionInstrument(const ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQryOptionInstrument: RequestID:%d", requestID);
	if (reqQryOptionInstrument != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryOptionInstrumentField:ExchangeId:[%s], InstrumentId:[%s]",
			reqQryOptionInstrument->ExchangeId, reqQryOptionInstrument->InstrumentId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryOptionInstrument is nullptr");
	}
	return traderApi->ReqQryOptionInstrument(reqQryOptionInstrument, requestID);
}
int TraderApiMiddle::ReqQryCommissionRate(const ReqQryCommissionRateField* reqQryCommissionRate, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQryCommissionRate: RequestID:%d", requestID);
	if (reqQryCommissionRate != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryCommissionRateField:AccountId:[%s], ExchangeId:[%s], ProductClass:[%d]",
			reqQryCommissionRate->AccountId, reqQryCommissionRate->ExchangeId, static_cast<int>(reqQryCommissionRate->ProductClass));
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryCommissionRate is nullptr");
	}
	return traderApi->ReqQryCommissionRate(reqQryCommissionRate, requestID);
}
int TraderApiMiddle::ReqQryMoneyTransfer(const ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestID)
{
	WriteLog(LogLevel::Info, "ReqQryMoneyTransfer: RequestID:%d", requestID);
	if (reqQryMoneyTransfer != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryMoneyTransferField:AccountId:[%s]",
			reqQryMoneyTransfer->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryMoneyTransfer is nullptr");
	}
	return traderApi->ReqQryMoneyTransfer(reqQryMoneyTransfer, requestID);
}
int TraderApiMiddle::ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestID)
{
	WriteLog(LogLevel::Info, "ReqInsertOrder: RequestID:%d", requestID);
	if (reqInsertOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqInsertOrderField:AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], ClientOrderId:[%d]",
			reqInsertOrder->AccountId, reqInsertOrder->ExchangeId, reqInsertOrder->InstrumentId, static_cast<int>(reqInsertOrder->Direction), static_cast<int>(reqInsertOrder->OffsetFlag), static_cast<int>(reqInsertOrder->OrderPriceType), reqInsertOrder->Price, reqInsertOrder->Volume, reqInsertOrder->ClientOrderId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqInsertOrder is nullptr");
	}
	return traderApi->ReqInsertOrder(reqInsertOrder, requestID);
}
int TraderApiMiddle::ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestID)
{
	WriteLog(LogLevel::Info, "ReqCancelOrder: RequestID:%d", requestID);
	if (reqCancelOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqCancelOrderField:AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], ClientCancelOrderId:[%d], OrderId:[%d], OrderSysId:[%s], SessionId:[%lld], ClientOrderId:[%d]",
			reqCancelOrder->AccountId, reqCancelOrder->ExchangeId, reqCancelOrder->InstrumentId, reqCancelOrder->ClientCancelOrderId, reqCancelOrder->OrderId, reqCancelOrder->OrderSysId, reqCancelOrder->SessionId, reqCancelOrder->ClientOrderId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqCancelOrder is nullptr");
	}
	return traderApi->ReqCancelOrder(reqCancelOrder, requestID);
}
}
