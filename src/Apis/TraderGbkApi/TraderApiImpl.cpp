// 本文件由 ../Templates/Cpp/Api/GbkApiImpl.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "TraderApiImpl.h"
#include "Error.h"
#include "Packages.h"
#include <Spark/Network/Protocol/Items.h>
#include <Spark/Serialization/Encode/Encode.h>

using namespace Spark;
using namespace Spark::Serialization;
using namespace QuantTrading::Packages;

namespace QuantTrading
{
TraderApi* TraderApi::CreateTraderApi()
{
	return new TraderApiImpl();
}
TraderApiImpl::TraderApiImpl()
{
}

void TraderApiImpl::OnMessage(Package* package)
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
		traderSpi->OnRspAccountLogin(rspAccountLogin, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
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
		traderSpi->OnRspAccountLogout(rspAccountLogout, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryHolderAccountPackage::PackageId:
	{
		auto holderAccount = static_cast<RspQryHolderAccountPackage*>(package)->HolderAccount;
		if (holderAccount != nullptr)
		{
			TrunsferUtf8ToGbk(holderAccount->ExchangeId);
			TrunsferUtf8ToGbk(holderAccount->HolderAccountId);
		}
		auto rspInfo = static_cast<RspQryHolderAccountPackage*>(package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		traderSpi->OnRspQryHolderAccount(holderAccount, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryCapitalPackage::PackageId:
	{
		auto capital = static_cast<RspQryCapitalPackage*>(package)->Capital;
		if (capital != nullptr)
		{
			TrunsferUtf8ToGbk(capital->TradingDay);
			TrunsferUtf8ToGbk(capital->AccountId);
		}
		auto rspInfo = static_cast<RspQryCapitalPackage*>(package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		traderSpi->OnRspQryCapital(capital, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryPositionPackage::PackageId:
	{
		auto position = static_cast<RspQryPositionPackage*>(package)->Position;
		if (position != nullptr)
		{
			TrunsferUtf8ToGbk(position->TradingDay);
			TrunsferUtf8ToGbk(position->AccountId);
			TrunsferUtf8ToGbk(position->ExchangeId);
			TrunsferUtf8ToGbk(position->InstrumentId);
		}
		auto rspInfo = static_cast<RspQryPositionPackage*>(package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		traderSpi->OnRspQryPosition(position, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
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
		traderSpi->OnRspQryOrder(order, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
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
		traderSpi->OnRspQryTrade(trade, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
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
		traderSpi->OnRspQryInstrument(instrument, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryOptionInstrumentPackage::PackageId:
	{
		auto optionInstrument = static_cast<RspQryOptionInstrumentPackage*>(package)->OptionInstrument;
		if (optionInstrument != nullptr)
		{
			TrunsferUtf8ToGbk(optionInstrument->ExchangeId);
			TrunsferUtf8ToGbk(optionInstrument->InstrumentId);
			TrunsferUtf8ToGbk(optionInstrument->ExchangeInstId);
			TrunsferUtf8ToGbk(optionInstrument->InstrumentName);
			TrunsferUtf8ToGbk(optionInstrument->UnderlyingInstrumentId);
			TrunsferUtf8ToGbk(optionInstrument->ExpiringDate);
		}
		auto rspInfo = static_cast<RspQryOptionInstrumentPackage*>(package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		traderSpi->OnRspQryOptionInstrument(optionInstrument, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryCommissionRatePackage::PackageId:
	{
		auto commissionRate = static_cast<RspQryCommissionRatePackage*>(package)->CommissionRate;
		if (commissionRate != nullptr)
		{
			TrunsferUtf8ToGbk(commissionRate->AccountId);
			TrunsferUtf8ToGbk(commissionRate->ExchangeId);
		}
		auto rspInfo = static_cast<RspQryCommissionRatePackage*>(package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		traderSpi->OnRspQryCommissionRate(commissionRate, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryMoneyTransferPackage::PackageId:
	{
		auto moneyTransfer = static_cast<RspQryMoneyTransferPackage*>(package)->MoneyTransfer;
		if (moneyTransfer != nullptr)
		{
			TrunsferUtf8ToGbk(moneyTransfer->TradingDay);
			TrunsferUtf8ToGbk(moneyTransfer->AccountId);
			TrunsferUtf8ToGbk(moneyTransfer->InfoMessage);
			TrunsferUtf8ToGbk(moneyTransfer->UserId);
			TrunsferUtf8ToGbk(moneyTransfer->TransferDate);
			TrunsferUtf8ToGbk(moneyTransfer->TransferTime);
		}
		auto rspInfo = static_cast<RspQryMoneyTransferPackage*>(package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		traderSpi->OnRspQryMoneyTransfer(moneyTransfer, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
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
		traderSpi->OnRspInsertOrder(reqInsertOrder, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
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
		traderSpi->OnRspCancelOrder(reqCancelOrder, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
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
		traderSpi->OnRtnOrder(order);
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
		traderSpi->OnRtnTrade(trade);
		break;
	}
	case RtnMoneyTransferPackage::PackageId:
	{
		auto moneyTransfer = static_cast<RtnMoneyTransferPackage*>(package)->MoneyTransfer;
		if (moneyTransfer != nullptr)
		{
			TrunsferUtf8ToGbk(moneyTransfer->TradingDay);
			TrunsferUtf8ToGbk(moneyTransfer->AccountId);
			TrunsferUtf8ToGbk(moneyTransfer->InfoMessage);
			TrunsferUtf8ToGbk(moneyTransfer->UserId);
			TrunsferUtf8ToGbk(moneyTransfer->TransferDate);
			TrunsferUtf8ToGbk(moneyTransfer->TransferTime);
		}
		traderSpi->OnRtnMoneyTransfer(moneyTransfer);
		break;
	}
	case RtnAccountLogoutPackage::PackageId:
	{
		auto accountLogout = static_cast<RtnAccountLogoutPackage*>(package)->AccountLogout;
		if (accountLogout != nullptr)
		{
			TrunsferUtf8ToGbk(accountLogout->AccountId);
			TrunsferUtf8ToGbk(accountLogout->ErrorMsg);
		}
		traderSpi->OnRtnAccountLogout(accountLogout);
		break;
	}
	default:
		break;
	}
	package->Deallocate();
}


int TraderApiImpl::ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestId)
{
	ReqAccountLoginPackage* reqPackage = ReqAccountLoginPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqAccountLogin = Allocate<ReqAccountLoginField>();
	memcpy(reqPackage->ReqAccountLogin, reqAccountLogin, sizeof(ReqAccountLoginField));
	TrunsferGbkToUtf8(reqPackage->ReqAccountLogin->AccountId);
	TrunsferGbkToUtf8(reqPackage->ReqAccountLogin->Password);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestId)
{
	ReqAccountLogoutPackage* reqPackage = ReqAccountLogoutPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqAccountLogout = Allocate<ReqAccountLogoutField>();
	memcpy(reqPackage->ReqAccountLogout, reqAccountLogout, sizeof(ReqAccountLogoutField));
	TrunsferGbkToUtf8(reqPackage->ReqAccountLogout->AccountId);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryHolderAccount(const ReqQryHolderAccountField* reqQryHolderAccount, int requestId)
{
	ReqQryHolderAccountPackage* reqPackage = ReqQryHolderAccountPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryHolderAccount = Allocate<ReqQryHolderAccountField>();
	memcpy(reqPackage->ReqQryHolderAccount, reqQryHolderAccount, sizeof(ReqQryHolderAccountField));
	TrunsferGbkToUtf8(reqPackage->ReqQryHolderAccount->AccountId);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryCapital(const ReqQryCapitalField* reqQryCapital, int requestId)
{
	ReqQryCapitalPackage* reqPackage = ReqQryCapitalPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryCapital = Allocate<ReqQryCapitalField>();
	memcpy(reqPackage->ReqQryCapital, reqQryCapital, sizeof(ReqQryCapitalField));
	TrunsferGbkToUtf8(reqPackage->ReqQryCapital->AccountId);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryPosition(const ReqQryPositionField* reqQryPosition, int requestId)
{
	ReqQryPositionPackage* reqPackage = ReqQryPositionPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryPosition = Allocate<ReqQryPositionField>();
	memcpy(reqPackage->ReqQryPosition, reqQryPosition, sizeof(ReqQryPositionField));
	TrunsferGbkToUtf8(reqPackage->ReqQryPosition->AccountId);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestId)
{
	ReqQryOrderPackage* reqPackage = ReqQryOrderPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryOrder = Allocate<ReqQryOrderField>();
	memcpy(reqPackage->ReqQryOrder, reqQryOrder, sizeof(ReqQryOrderField));
	TrunsferGbkToUtf8(reqPackage->ReqQryOrder->AccountId);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestId)
{
	ReqQryTradePackage* reqPackage = ReqQryTradePackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryTrade = Allocate<ReqQryTradeField>();
	memcpy(reqPackage->ReqQryTrade, reqQryTrade, sizeof(ReqQryTradeField));
	TrunsferGbkToUtf8(reqPackage->ReqQryTrade->AccountId);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestId)
{
	ReqQryInstrumentPackage* reqPackage = ReqQryInstrumentPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryInstrument = Allocate<ReqQryInstrumentField>();
	memcpy(reqPackage->ReqQryInstrument, reqQryInstrument, sizeof(ReqQryInstrumentField));
	TrunsferGbkToUtf8(reqPackage->ReqQryInstrument->ExchangeId);
	TrunsferGbkToUtf8(reqPackage->ReqQryInstrument->InstrumentId);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryOptionInstrument(const ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestId)
{
	ReqQryOptionInstrumentPackage* reqPackage = ReqQryOptionInstrumentPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryOptionInstrument = Allocate<ReqQryOptionInstrumentField>();
	memcpy(reqPackage->ReqQryOptionInstrument, reqQryOptionInstrument, sizeof(ReqQryOptionInstrumentField));
	TrunsferGbkToUtf8(reqPackage->ReqQryOptionInstrument->ExchangeId);
	TrunsferGbkToUtf8(reqPackage->ReqQryOptionInstrument->InstrumentId);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryCommissionRate(const ReqQryCommissionRateField* reqQryCommissionRate, int requestId)
{
	ReqQryCommissionRatePackage* reqPackage = ReqQryCommissionRatePackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryCommissionRate = Allocate<ReqQryCommissionRateField>();
	memcpy(reqPackage->ReqQryCommissionRate, reqQryCommissionRate, sizeof(ReqQryCommissionRateField));
	TrunsferGbkToUtf8(reqPackage->ReqQryCommissionRate->AccountId);
	TrunsferGbkToUtf8(reqPackage->ReqQryCommissionRate->ExchangeId);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryMoneyTransfer(const ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestId)
{
	ReqQryMoneyTransferPackage* reqPackage = ReqQryMoneyTransferPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryMoneyTransfer = Allocate<ReqQryMoneyTransferField>();
	memcpy(reqPackage->ReqQryMoneyTransfer, reqQryMoneyTransfer, sizeof(ReqQryMoneyTransferField));
	TrunsferGbkToUtf8(reqPackage->ReqQryMoneyTransfer->AccountId);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestId)
{
	ReqInsertOrderPackage* reqPackage = ReqInsertOrderPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqInsertOrder = Allocate<ReqInsertOrderField>();
	memcpy(reqPackage->ReqInsertOrder, reqInsertOrder, sizeof(ReqInsertOrderField));
	TrunsferGbkToUtf8(reqPackage->ReqInsertOrder->AccountId);
	TrunsferGbkToUtf8(reqPackage->ReqInsertOrder->ExchangeId);
	TrunsferGbkToUtf8(reqPackage->ReqInsertOrder->InstrumentId);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestId)
{
	ReqCancelOrderPackage* reqPackage = ReqCancelOrderPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqCancelOrder = Allocate<ReqCancelOrderField>();
	memcpy(reqPackage->ReqCancelOrder, reqCancelOrder, sizeof(ReqCancelOrderField));
	TrunsferGbkToUtf8(reqPackage->ReqCancelOrder->AccountId);
	TrunsferGbkToUtf8(reqPackage->ReqCancelOrder->ExchangeId);
	TrunsferGbkToUtf8(reqPackage->ReqCancelOrder->InstrumentId);
	TrunsferGbkToUtf8(reqPackage->ReqCancelOrder->OrderSysId);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
}
