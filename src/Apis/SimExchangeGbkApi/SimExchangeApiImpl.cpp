// 本文件由 ../Templates/Cpp/Api/GbkApiImpl.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "SimExchangeApiImpl.h"
#include "Error.h"
#include "Packages.h"
#include <Spark/Network/Protocol/Items.h>
#include <Spark/Serialization/Encode/Encode.h>

using namespace Spark;
using namespace Spark::Serialization;
using namespace QuantTrading::Packages;

namespace QuantTrading
{
SimExchangeApi* SimExchangeApi::CreateSimExchangeApi()
{
	return new SimExchangeApiImpl();
}
SimExchangeApiImpl::SimExchangeApiImpl()
{
}

void SimExchangeApiImpl::OnMessage(Package* package)
{
	switch (package->Head.PackageId)
	{
	case RspAccountLoginPackage::PackageId:
	{
		auto rspAccountLogin = static_cast<RspAccountLoginPackage*>(package)->RspAccountLogin;
		if (rspAccountLogin != nullptr)
		{
			TrunsferUtf8ToGbk(rspAccountLogin->AccountId);
			TrunsferUtf8ToGbk(rspAccountLogin->LoginDate);
			TrunsferUtf8ToGbk(rspAccountLogin->LoginTime);
		}
		auto rspInfo = static_cast<RspAccountLoginPackage*>(package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		simExchangeSpi_->OnRspAccountLogin(rspAccountLogin, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspAccountLogoutPackage::PackageId:
	{
		auto rspAccountLogout = static_cast<RspAccountLogoutPackage*>(package)->RspAccountLogout;
		if (rspAccountLogout != nullptr)
		{
			TrunsferUtf8ToGbk(rspAccountLogout->AccountId);
		}
		auto rspInfo = static_cast<RspAccountLogoutPackage*>(package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		simExchangeSpi_->OnRspAccountLogout(rspAccountLogout, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryOrderPackage::PackageId:
	{
		auto order = static_cast<RspQryOrderPackage*>(package)->Order;
		if (order != nullptr)
		{
			TrunsferUtf8ToGbk(order->TradingDay);
			TrunsferUtf8ToGbk(order->AccountId);
			TrunsferUtf8ToGbk(order->ExchangeId);
			TrunsferUtf8ToGbk(order->InstrumentId);
			TrunsferUtf8ToGbk(order->OrderSysId);
			TrunsferUtf8ToGbk(order->OrderDate);
			TrunsferUtf8ToGbk(order->OrderTime);
			TrunsferUtf8ToGbk(order->CancelDate);
			TrunsferUtf8ToGbk(order->CancelTime);
		}
		auto rspInfo = static_cast<RspQryOrderPackage*>(package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		simExchangeSpi_->OnRspQryOrder(order, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryTradePackage::PackageId:
	{
		auto trade = static_cast<RspQryTradePackage*>(package)->Trade;
		if (trade != nullptr)
		{
			TrunsferUtf8ToGbk(trade->TradingDay);
			TrunsferUtf8ToGbk(trade->AccountId);
			TrunsferUtf8ToGbk(trade->ExchangeId);
			TrunsferUtf8ToGbk(trade->InstrumentId);
			TrunsferUtf8ToGbk(trade->OrderSysId);
			TrunsferUtf8ToGbk(trade->TradeId);
			TrunsferUtf8ToGbk(trade->TradeDate);
			TrunsferUtf8ToGbk(trade->TradeTime);
		}
		auto rspInfo = static_cast<RspQryTradePackage*>(package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		simExchangeSpi_->OnRspQryTrade(trade, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryInstrumentPackage::PackageId:
	{
		auto instrument = static_cast<RspQryInstrumentPackage*>(package)->Instrument;
		if (instrument != nullptr)
		{
			TrunsferUtf8ToGbk(instrument->ExchangeId);
			TrunsferUtf8ToGbk(instrument->InstrumentId);
			TrunsferUtf8ToGbk(instrument->ExchangeInstId);
			TrunsferUtf8ToGbk(instrument->InstrumentName);
			TrunsferUtf8ToGbk(instrument->ProductId);
			TrunsferUtf8ToGbk(instrument->SessionName);
		}
		auto rspInfo = static_cast<RspQryInstrumentPackage*>(package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		simExchangeSpi_->OnRspQryInstrument(instrument, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspInsertOrderPackage::PackageId:
	{
		auto reqInsertOrder = static_cast<RspInsertOrderPackage*>(package)->ReqInsertOrder;
		if (reqInsertOrder != nullptr)
		{
			TrunsferUtf8ToGbk(reqInsertOrder->AccountId);
			TrunsferUtf8ToGbk(reqInsertOrder->ExchangeId);
			TrunsferUtf8ToGbk(reqInsertOrder->InstrumentId);
		}
		auto rspInfo = static_cast<RspInsertOrderPackage*>(package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		simExchangeSpi_->OnRspInsertOrder(reqInsertOrder, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspCancelOrderPackage::PackageId:
	{
		auto reqCancelOrder = static_cast<RspCancelOrderPackage*>(package)->ReqCancelOrder;
		if (reqCancelOrder != nullptr)
		{
			TrunsferUtf8ToGbk(reqCancelOrder->AccountId);
			TrunsferUtf8ToGbk(reqCancelOrder->ExchangeId);
			TrunsferUtf8ToGbk(reqCancelOrder->InstrumentId);
			TrunsferUtf8ToGbk(reqCancelOrder->OrderSysId);
		}
		auto rspInfo = static_cast<RspCancelOrderPackage*>(package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		simExchangeSpi_->OnRspCancelOrder(reqCancelOrder, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RtnOrderPackage::PackageId:
	{
		auto order = static_cast<RtnOrderPackage*>(package)->Order;
		if (order != nullptr)
		{
			TrunsferUtf8ToGbk(order->TradingDay);
			TrunsferUtf8ToGbk(order->AccountId);
			TrunsferUtf8ToGbk(order->ExchangeId);
			TrunsferUtf8ToGbk(order->InstrumentId);
			TrunsferUtf8ToGbk(order->OrderSysId);
			TrunsferUtf8ToGbk(order->OrderDate);
			TrunsferUtf8ToGbk(order->OrderTime);
			TrunsferUtf8ToGbk(order->CancelDate);
			TrunsferUtf8ToGbk(order->CancelTime);
		}
		simExchangeSpi_->OnRtnOrder(order);
		break;
	}
	case RtnTradePackage::PackageId:
	{
		auto trade = static_cast<RtnTradePackage*>(package)->Trade;
		if (trade != nullptr)
		{
			TrunsferUtf8ToGbk(trade->TradingDay);
			TrunsferUtf8ToGbk(trade->AccountId);
			TrunsferUtf8ToGbk(trade->ExchangeId);
			TrunsferUtf8ToGbk(trade->InstrumentId);
			TrunsferUtf8ToGbk(trade->OrderSysId);
			TrunsferUtf8ToGbk(trade->TradeId);
			TrunsferUtf8ToGbk(trade->TradeDate);
			TrunsferUtf8ToGbk(trade->TradeTime);
		}
		simExchangeSpi_->OnRtnTrade(trade);
		break;
	}
	default:
		break;
	}
	package->Deallocate();
}


int SimExchangeApiImpl::ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestId)
{
	ReqAccountLoginPackage* reqPackage = ReqAccountLoginPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqAccountLogin = Allocate<ReqAccountLoginField>();
	memcpy(reqPackage->ReqAccountLogin, reqAccountLogin, sizeof(ReqAccountLoginField));
	TrunsferGbkToUtf8(reqPackage->ReqAccountLogin->AccountId);
	TrunsferGbkToUtf8(reqPackage->ReqAccountLogin->Password);
	
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int SimExchangeApiImpl::ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestId)
{
	ReqAccountLogoutPackage* reqPackage = ReqAccountLogoutPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqAccountLogout = Allocate<ReqAccountLogoutField>();
	memcpy(reqPackage->ReqAccountLogout, reqAccountLogout, sizeof(ReqAccountLogoutField));
	TrunsferGbkToUtf8(reqPackage->ReqAccountLogout->AccountId);
	
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int SimExchangeApiImpl::ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestId)
{
	ReqQryOrderPackage* reqPackage = ReqQryOrderPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryOrder = Allocate<ReqQryOrderField>();
	memcpy(reqPackage->ReqQryOrder, reqQryOrder, sizeof(ReqQryOrderField));
	TrunsferGbkToUtf8(reqPackage->ReqQryOrder->AccountId);
	
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int SimExchangeApiImpl::ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestId)
{
	ReqQryTradePackage* reqPackage = ReqQryTradePackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryTrade = Allocate<ReqQryTradeField>();
	memcpy(reqPackage->ReqQryTrade, reqQryTrade, sizeof(ReqQryTradeField));
	TrunsferGbkToUtf8(reqPackage->ReqQryTrade->AccountId);
	
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int SimExchangeApiImpl::ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestId)
{
	ReqQryInstrumentPackage* reqPackage = ReqQryInstrumentPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryInstrument = Allocate<ReqQryInstrumentField>();
	memcpy(reqPackage->ReqQryInstrument, reqQryInstrument, sizeof(ReqQryInstrumentField));
	TrunsferGbkToUtf8(reqPackage->ReqQryInstrument->ExchangeId);
	TrunsferGbkToUtf8(reqPackage->ReqQryInstrument->InstrumentId);
	
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int SimExchangeApiImpl::ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestId)
{
	ReqInsertOrderPackage* reqPackage = ReqInsertOrderPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqInsertOrder = Allocate<ReqInsertOrderField>();
	memcpy(reqPackage->ReqInsertOrder, reqInsertOrder, sizeof(ReqInsertOrderField));
	TrunsferGbkToUtf8(reqPackage->ReqInsertOrder->AccountId);
	TrunsferGbkToUtf8(reqPackage->ReqInsertOrder->ExchangeId);
	TrunsferGbkToUtf8(reqPackage->ReqInsertOrder->InstrumentId);
	
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int SimExchangeApiImpl::ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestId)
{
	ReqCancelOrderPackage* reqPackage = ReqCancelOrderPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqCancelOrder = Allocate<ReqCancelOrderField>();
	memcpy(reqPackage->ReqCancelOrder, reqCancelOrder, sizeof(ReqCancelOrderField));
	TrunsferGbkToUtf8(reqPackage->ReqCancelOrder->AccountId);
	TrunsferGbkToUtf8(reqPackage->ReqCancelOrder->ExchangeId);
	TrunsferGbkToUtf8(reqPackage->ReqCancelOrder->InstrumentId);
	TrunsferGbkToUtf8(reqPackage->ReqCancelOrder->OrderSysId);
	
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
}
