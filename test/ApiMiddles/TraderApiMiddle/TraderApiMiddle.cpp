// 本文件由 ../Templates/Cpp/ApiTest/ApiMiddle.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "TraderApiMiddle.h"
#include <Spark/Core/Logger/Logger.h>

using namespace Spark::Core;


namespace QuantTrading
{
TraderApiMiddle* TraderApiMiddle::CreateTraderApiMiddle()
{
	WriteLog(LogLevel::Info, "CreateTraderApi");
	
	auto api = TraderApi::CreateTraderApi();
	auto apiMiddle = new TraderApiMiddle();
	apiMiddle->traderApi_ = api;
	
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
	return traderApi_->Init();
}
void TraderApiMiddle::Join()
{
	WriteLog(LogLevel::Info, "Join");
	traderApi_->Join();
}
void TraderApiMiddle::Release()
{
	WriteLog(LogLevel::Info, "Release");
	traderApi_->Release();
}
void TraderApiMiddle::RegisterFront(const char* address)
{
	WriteLog(LogLevel::Info, "RegisterFront:%s", address);
	traderApi_->RegisterFront(address);
}
void TraderApiMiddle::RegisterSpi(TraderSpi* spi)
{
	WriteLog(LogLevel::Info, "RegisterSpi");
	traderApi_->RegisterSpi(spi);
}

int TraderApiMiddle::ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestId)
{
	WriteLog(LogLevel::Info, "ReqAccountLogin: RequestID:%d", requestId);
	if (reqAccountLogin != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqAccountLoginField:AccountId:[%s]",
			reqAccountLogin->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqAccountLogin is nullptr");
	}
	return traderApi_->ReqAccountLogin(reqAccountLogin, requestId);
}
int TraderApiMiddle::ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestId)
{
	WriteLog(LogLevel::Info, "ReqAccountLogout: RequestID:%d", requestId);
	if (reqAccountLogout != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqAccountLogoutField:AccountId:[%s]",
			reqAccountLogout->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqAccountLogout is nullptr");
	}
	return traderApi_->ReqAccountLogout(reqAccountLogout, requestId);
}
int TraderApiMiddle::ReqQryHolderAccount(const ReqQryHolderAccountField* reqQryHolderAccount, int requestId)
{
	WriteLog(LogLevel::Info, "ReqQryHolderAccount: RequestID:%d", requestId);
	if (reqQryHolderAccount != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryHolderAccountField:AccountId:[%s]",
			reqQryHolderAccount->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryHolderAccount is nullptr");
	}
	return traderApi_->ReqQryHolderAccount(reqQryHolderAccount, requestId);
}
int TraderApiMiddle::ReqQryCapital(const ReqQryCapitalField* reqQryCapital, int requestId)
{
	WriteLog(LogLevel::Info, "ReqQryCapital: RequestID:%d", requestId);
	if (reqQryCapital != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryCapitalField:AccountId:[%s]",
			reqQryCapital->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryCapital is nullptr");
	}
	return traderApi_->ReqQryCapital(reqQryCapital, requestId);
}
int TraderApiMiddle::ReqQryPosition(const ReqQryPositionField* reqQryPosition, int requestId)
{
	WriteLog(LogLevel::Info, "ReqQryPosition: RequestID:%d", requestId);
	if (reqQryPosition != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryPositionField:AccountId:[%s]",
			reqQryPosition->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryPosition is nullptr");
	}
	return traderApi_->ReqQryPosition(reqQryPosition, requestId);
}
int TraderApiMiddle::ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestId)
{
	WriteLog(LogLevel::Info, "ReqQryOrder: RequestID:%d", requestId);
	if (reqQryOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryOrderField:AccountId:[%s]",
			reqQryOrder->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryOrder is nullptr");
	}
	return traderApi_->ReqQryOrder(reqQryOrder, requestId);
}
int TraderApiMiddle::ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestId)
{
	WriteLog(LogLevel::Info, "ReqQryTrade: RequestID:%d", requestId);
	if (reqQryTrade != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryTradeField:AccountId:[%s]",
			reqQryTrade->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryTrade is nullptr");
	}
	return traderApi_->ReqQryTrade(reqQryTrade, requestId);
}
int TraderApiMiddle::ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestId)
{
	WriteLog(LogLevel::Info, "ReqQryInstrument: RequestID:%d", requestId);
	if (reqQryInstrument != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryInstrumentField:ExchangeId:[%s], InstrumentId:[%s]",
			reqQryInstrument->ExchangeId, reqQryInstrument->InstrumentId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryInstrument is nullptr");
	}
	return traderApi_->ReqQryInstrument(reqQryInstrument, requestId);
}
int TraderApiMiddle::ReqQryOptionInstrument(const ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestId)
{
	WriteLog(LogLevel::Info, "ReqQryOptionInstrument: RequestID:%d", requestId);
	if (reqQryOptionInstrument != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryOptionInstrumentField:ExchangeId:[%s], InstrumentId:[%s]",
			reqQryOptionInstrument->ExchangeId, reqQryOptionInstrument->InstrumentId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryOptionInstrument is nullptr");
	}
	return traderApi_->ReqQryOptionInstrument(reqQryOptionInstrument, requestId);
}
int TraderApiMiddle::ReqQryCommissionRate(const ReqQryCommissionRateField* reqQryCommissionRate, int requestId)
{
	WriteLog(LogLevel::Info, "ReqQryCommissionRate: RequestID:%d", requestId);
	if (reqQryCommissionRate != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryCommissionRateField:AccountId:[%s], ExchangeId:[%s], ProductClass:[%d]",
			reqQryCommissionRate->AccountId, reqQryCommissionRate->ExchangeId, static_cast<int>(reqQryCommissionRate->ProductClass));
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryCommissionRate is nullptr");
	}
	return traderApi_->ReqQryCommissionRate(reqQryCommissionRate, requestId);
}
int TraderApiMiddle::ReqQryMoneyTransfer(const ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestId)
{
	WriteLog(LogLevel::Info, "ReqQryMoneyTransfer: RequestID:%d", requestId);
	if (reqQryMoneyTransfer != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqQryMoneyTransferField:AccountId:[%s]",
			reqQryMoneyTransfer->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqQryMoneyTransfer is nullptr");
	}
	return traderApi_->ReqQryMoneyTransfer(reqQryMoneyTransfer, requestId);
}
int TraderApiMiddle::ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestId)
{
	WriteLog(LogLevel::Info, "ReqInsertOrder: RequestID:%d", requestId);
	if (reqInsertOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqInsertOrderField:AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], ClientOrderId:[%d]",
			reqInsertOrder->AccountId, reqInsertOrder->ExchangeId, reqInsertOrder->InstrumentId, static_cast<int>(reqInsertOrder->Direction), static_cast<int>(reqInsertOrder->OffsetFlag), static_cast<int>(reqInsertOrder->OrderPriceType), reqInsertOrder->Price, reqInsertOrder->Volume, reqInsertOrder->ClientOrderId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqInsertOrder is nullptr");
	}
	return traderApi_->ReqInsertOrder(reqInsertOrder, requestId);
}
int TraderApiMiddle::ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestId)
{
	WriteLog(LogLevel::Info, "ReqCancelOrder: RequestID:%d", requestId);
	if (reqCancelOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqCancelOrderField:AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], ClientCancelOrderId:[%d], OrderId:[%d], OrderSysId:[%s], SessionId:[%lld], ClientOrderId:[%d]",
			reqCancelOrder->AccountId, reqCancelOrder->ExchangeId, reqCancelOrder->InstrumentId, reqCancelOrder->ClientCancelOrderId, reqCancelOrder->OrderId, reqCancelOrder->OrderSysId, reqCancelOrder->SessionId, reqCancelOrder->ClientOrderId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqCancelOrder is nullptr");
	}
	return traderApi_->ReqCancelOrder(reqCancelOrder, requestId);
}
}
