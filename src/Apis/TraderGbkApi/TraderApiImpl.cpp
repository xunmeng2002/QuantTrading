#include "TraderApiImpl.h"
#include "Error.h"
#include "Packages.h"
#include <Spark/Network/Protocol/Items.h>
#include <Spark/Serialization/Encode/Encode.h>

using namespace spark;
using namespace spark::serialization;

TraderApi* TraderApi::CreateTraderApi()
{
	return new TraderApiImpl();
}
TraderApiImpl::TraderApiImpl()
{
}

void TraderApiImpl::OnMessage(Package* package)
{
	switch (package->Head.PackageID)
	{
	case RspAccountLoginPackage::PackageID:
	{
		auto rspAccountLogin = ((RspAccountLoginPackage*)package)->RspAccountLogin;
		if (rspAccountLogin != nullptr)
		{
			TrunsferUtf8ToGbk(rspAccountLogin->AccountID);
			TrunsferUtf8ToGbk(rspAccountLogin->LoginDate);
			TrunsferUtf8ToGbk(rspAccountLogin->LoginTime);
		}
		auto rspInfo = ((RspAccountLoginPackage*)package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		m_TraderSpi->OnRspAccountLogin(rspAccountLogin, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspAccountLogoutPackage::PackageID:
	{
		auto rspAccountLogout = ((RspAccountLogoutPackage*)package)->RspAccountLogout;
		if (rspAccountLogout != nullptr)
		{
			TrunsferUtf8ToGbk(rspAccountLogout->AccountID);
		}
		auto rspInfo = ((RspAccountLogoutPackage*)package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		m_TraderSpi->OnRspAccountLogout(rspAccountLogout, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryHolderAccountPackage::PackageID:
	{
		auto holderAccount = ((RspQryHolderAccountPackage*)package)->HolderAccount;
		if (holderAccount != nullptr)
		{
			TrunsferUtf8ToGbk(holderAccount->ExchangeID);
			TrunsferUtf8ToGbk(holderAccount->HolderAccountID);
		}
		auto rspInfo = ((RspQryHolderAccountPackage*)package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		m_TraderSpi->OnRspQryHolderAccount(holderAccount, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryCapitalPackage::PackageID:
	{
		auto capital = ((RspQryCapitalPackage*)package)->Capital;
		if (capital != nullptr)
		{
			TrunsferUtf8ToGbk(capital->TradingDay);
			TrunsferUtf8ToGbk(capital->AccountID);
		}
		auto rspInfo = ((RspQryCapitalPackage*)package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		m_TraderSpi->OnRspQryCapital(capital, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryPositionPackage::PackageID:
	{
		auto position = ((RspQryPositionPackage*)package)->Position;
		if (position != nullptr)
		{
			TrunsferUtf8ToGbk(position->TradingDay);
			TrunsferUtf8ToGbk(position->AccountID);
			TrunsferUtf8ToGbk(position->ExchangeID);
			TrunsferUtf8ToGbk(position->InstrumentID);
		}
		auto rspInfo = ((RspQryPositionPackage*)package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		m_TraderSpi->OnRspQryPosition(position, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryOrderPackage::PackageID:
	{
		auto order = ((RspQryOrderPackage*)package)->Order;
		if (order != nullptr)
		{
			TrunsferUtf8ToGbk(order->TradingDay);
			TrunsferUtf8ToGbk(order->AccountID);
			TrunsferUtf8ToGbk(order->ExchangeID);
			TrunsferUtf8ToGbk(order->InstrumentID);
			TrunsferUtf8ToGbk(order->OrderSysID);
			TrunsferUtf8ToGbk(order->OrderDate);
			TrunsferUtf8ToGbk(order->OrderTime);
			TrunsferUtf8ToGbk(order->CancelDate);
			TrunsferUtf8ToGbk(order->CancelTime);
		}
		auto rspInfo = ((RspQryOrderPackage*)package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		m_TraderSpi->OnRspQryOrder(order, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryTradePackage::PackageID:
	{
		auto trade = ((RspQryTradePackage*)package)->Trade;
		if (trade != nullptr)
		{
			TrunsferUtf8ToGbk(trade->TradingDay);
			TrunsferUtf8ToGbk(trade->AccountID);
			TrunsferUtf8ToGbk(trade->ExchangeID);
			TrunsferUtf8ToGbk(trade->InstrumentID);
			TrunsferUtf8ToGbk(trade->OrderSysID);
			TrunsferUtf8ToGbk(trade->TradeID);
			TrunsferUtf8ToGbk(trade->TradeDate);
			TrunsferUtf8ToGbk(trade->TradeTime);
		}
		auto rspInfo = ((RspQryTradePackage*)package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		m_TraderSpi->OnRspQryTrade(trade, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryInstrumentPackage::PackageID:
	{
		auto instrument = ((RspQryInstrumentPackage*)package)->Instrument;
		if (instrument != nullptr)
		{
			TrunsferUtf8ToGbk(instrument->ExchangeID);
			TrunsferUtf8ToGbk(instrument->InstrumentID);
			TrunsferUtf8ToGbk(instrument->ExchangeInstID);
			TrunsferUtf8ToGbk(instrument->InstrumentName);
			TrunsferUtf8ToGbk(instrument->ProductID);
			TrunsferUtf8ToGbk(instrument->SessionName);
		}
		auto rspInfo = ((RspQryInstrumentPackage*)package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		m_TraderSpi->OnRspQryInstrument(instrument, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryOptionInstrumentPackage::PackageID:
	{
		auto optionInstrument = ((RspQryOptionInstrumentPackage*)package)->OptionInstrument;
		if (optionInstrument != nullptr)
		{
			TrunsferUtf8ToGbk(optionInstrument->ExchangeID);
			TrunsferUtf8ToGbk(optionInstrument->InstrumentID);
			TrunsferUtf8ToGbk(optionInstrument->ExchangeInstID);
			TrunsferUtf8ToGbk(optionInstrument->InstrumentName);
			TrunsferUtf8ToGbk(optionInstrument->UnderlyingInstrumentID);
			TrunsferUtf8ToGbk(optionInstrument->ExpiringDate);
		}
		auto rspInfo = ((RspQryOptionInstrumentPackage*)package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		m_TraderSpi->OnRspQryOptionInstrument(optionInstrument, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryCommissionRatePackage::PackageID:
	{
		auto commissionRate = ((RspQryCommissionRatePackage*)package)->CommissionRate;
		if (commissionRate != nullptr)
		{
			TrunsferUtf8ToGbk(commissionRate->AccountID);
			TrunsferUtf8ToGbk(commissionRate->ExchangeID);
		}
		auto rspInfo = ((RspQryCommissionRatePackage*)package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		m_TraderSpi->OnRspQryCommissionRate(commissionRate, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryMoneyTransferPackage::PackageID:
	{
		auto moneyTransfer = ((RspQryMoneyTransferPackage*)package)->MoneyTransfer;
		if (moneyTransfer != nullptr)
		{
			TrunsferUtf8ToGbk(moneyTransfer->TradingDay);
			TrunsferUtf8ToGbk(moneyTransfer->AccountID);
			TrunsferUtf8ToGbk(moneyTransfer->InfoMessage);
			TrunsferUtf8ToGbk(moneyTransfer->UserID);
			TrunsferUtf8ToGbk(moneyTransfer->TransferDate);
			TrunsferUtf8ToGbk(moneyTransfer->TransferTime);
		}
		auto rspInfo = ((RspQryMoneyTransferPackage*)package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		m_TraderSpi->OnRspQryMoneyTransfer(moneyTransfer, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspInsertOrderPackage::PackageID:
	{
		auto reqInsertOrder = ((RspInsertOrderPackage*)package)->ReqInsertOrder;
		if (reqInsertOrder != nullptr)
		{
			TrunsferUtf8ToGbk(reqInsertOrder->AccountID);
			TrunsferUtf8ToGbk(reqInsertOrder->ExchangeID);
			TrunsferUtf8ToGbk(reqInsertOrder->InstrumentID);
		}
		auto rspInfo = ((RspInsertOrderPackage*)package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		m_TraderSpi->OnRspInsertOrder(reqInsertOrder, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspCancelOrderPackage::PackageID:
	{
		auto reqCancelOrder = ((RspCancelOrderPackage*)package)->ReqCancelOrder;
		if (reqCancelOrder != nullptr)
		{
			TrunsferUtf8ToGbk(reqCancelOrder->AccountID);
			TrunsferUtf8ToGbk(reqCancelOrder->ExchangeID);
			TrunsferUtf8ToGbk(reqCancelOrder->InstrumentID);
			TrunsferUtf8ToGbk(reqCancelOrder->OrderSysID);
		}
		auto rspInfo = ((RspCancelOrderPackage*)package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		m_TraderSpi->OnRspCancelOrder(reqCancelOrder, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RtnOrderPackage::PackageID:
	{
		auto order = ((RtnOrderPackage*)package)->Order;
		if (order != nullptr)
		{
			TrunsferUtf8ToGbk(order->TradingDay);
			TrunsferUtf8ToGbk(order->AccountID);
			TrunsferUtf8ToGbk(order->ExchangeID);
			TrunsferUtf8ToGbk(order->InstrumentID);
			TrunsferUtf8ToGbk(order->OrderSysID);
			TrunsferUtf8ToGbk(order->OrderDate);
			TrunsferUtf8ToGbk(order->OrderTime);
			TrunsferUtf8ToGbk(order->CancelDate);
			TrunsferUtf8ToGbk(order->CancelTime);
		}
		m_TraderSpi->OnRtnOrder(order);
		break;
	}
	case RtnTradePackage::PackageID:
	{
		auto trade = ((RtnTradePackage*)package)->Trade;
		if (trade != nullptr)
		{
			TrunsferUtf8ToGbk(trade->TradingDay);
			TrunsferUtf8ToGbk(trade->AccountID);
			TrunsferUtf8ToGbk(trade->ExchangeID);
			TrunsferUtf8ToGbk(trade->InstrumentID);
			TrunsferUtf8ToGbk(trade->OrderSysID);
			TrunsferUtf8ToGbk(trade->TradeID);
			TrunsferUtf8ToGbk(trade->TradeDate);
			TrunsferUtf8ToGbk(trade->TradeTime);
		}
		m_TraderSpi->OnRtnTrade(trade);
		break;
	}
	case RtnMoneyTransferPackage::PackageID:
	{
		auto moneyTransfer = ((RtnMoneyTransferPackage*)package)->MoneyTransfer;
		if (moneyTransfer != nullptr)
		{
			TrunsferUtf8ToGbk(moneyTransfer->TradingDay);
			TrunsferUtf8ToGbk(moneyTransfer->AccountID);
			TrunsferUtf8ToGbk(moneyTransfer->InfoMessage);
			TrunsferUtf8ToGbk(moneyTransfer->UserID);
			TrunsferUtf8ToGbk(moneyTransfer->TransferDate);
			TrunsferUtf8ToGbk(moneyTransfer->TransferTime);
		}
		m_TraderSpi->OnRtnMoneyTransfer(moneyTransfer);
		break;
	}
	case RtnAccountLogoutPackage::PackageID:
	{
		auto accountLogout = ((RtnAccountLogoutPackage*)package)->AccountLogout;
		if (accountLogout != nullptr)
		{
			TrunsferUtf8ToGbk(accountLogout->AccountID);
			TrunsferUtf8ToGbk(accountLogout->ErrorMsg);
		}
		m_TraderSpi->OnRtnAccountLogout(accountLogout);
		break;
	}
	default:
		break;
	}
	package->Deallocate();
}


int TraderApiImpl::ReqAccountLogin(ReqAccountLoginField* reqAccountLogin, int requestID)
{
	ReqAccountLoginPackage* reqPackage = ReqAccountLoginPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqAccountLogin = Allocate<ReqAccountLoginField>();
	memcpy(reqPackage->ReqAccountLogin, reqAccountLogin, sizeof(ReqAccountLoginField));
	TrunsferGbkToUtf8(reqPackage->ReqAccountLogin->AccountID);
	TrunsferGbkToUtf8(reqPackage->ReqAccountLogin->Password);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqAccountLogout(ReqAccountLogoutField* reqAccountLogout, int requestID)
{
	ReqAccountLogoutPackage* reqPackage = ReqAccountLogoutPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqAccountLogout = Allocate<ReqAccountLogoutField>();
	memcpy(reqPackage->ReqAccountLogout, reqAccountLogout, sizeof(ReqAccountLogoutField));
	TrunsferGbkToUtf8(reqPackage->ReqAccountLogout->AccountID);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryHolderAccount(ReqQryHolderAccountField* reqQryHolderAccount, int requestID)
{
	ReqQryHolderAccountPackage* reqPackage = ReqQryHolderAccountPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqQryHolderAccount = Allocate<ReqQryHolderAccountField>();
	memcpy(reqPackage->ReqQryHolderAccount, reqQryHolderAccount, sizeof(ReqQryHolderAccountField));
	TrunsferGbkToUtf8(reqPackage->ReqQryHolderAccount->AccountID);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryCapital(ReqQryCapitalField* reqQryCapital, int requestID)
{
	ReqQryCapitalPackage* reqPackage = ReqQryCapitalPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqQryCapital = Allocate<ReqQryCapitalField>();
	memcpy(reqPackage->ReqQryCapital, reqQryCapital, sizeof(ReqQryCapitalField));
	TrunsferGbkToUtf8(reqPackage->ReqQryCapital->AccountID);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryPosition(ReqQryPositionField* reqQryPosition, int requestID)
{
	ReqQryPositionPackage* reqPackage = ReqQryPositionPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqQryPosition = Allocate<ReqQryPositionField>();
	memcpy(reqPackage->ReqQryPosition, reqQryPosition, sizeof(ReqQryPositionField));
	TrunsferGbkToUtf8(reqPackage->ReqQryPosition->AccountID);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryOrder(ReqQryOrderField* reqQryOrder, int requestID)
{
	ReqQryOrderPackage* reqPackage = ReqQryOrderPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqQryOrder = Allocate<ReqQryOrderField>();
	memcpy(reqPackage->ReqQryOrder, reqQryOrder, sizeof(ReqQryOrderField));
	TrunsferGbkToUtf8(reqPackage->ReqQryOrder->AccountID);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryTrade(ReqQryTradeField* reqQryTrade, int requestID)
{
	ReqQryTradePackage* reqPackage = ReqQryTradePackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqQryTrade = Allocate<ReqQryTradeField>();
	memcpy(reqPackage->ReqQryTrade, reqQryTrade, sizeof(ReqQryTradeField));
	TrunsferGbkToUtf8(reqPackage->ReqQryTrade->AccountID);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryInstrument(ReqQryInstrumentField* reqQryInstrument, int requestID)
{
	ReqQryInstrumentPackage* reqPackage = ReqQryInstrumentPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqQryInstrument = Allocate<ReqQryInstrumentField>();
	memcpy(reqPackage->ReqQryInstrument, reqQryInstrument, sizeof(ReqQryInstrumentField));
	TrunsferGbkToUtf8(reqPackage->ReqQryInstrument->ExchangeID);
	TrunsferGbkToUtf8(reqPackage->ReqQryInstrument->InstrumentID);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryOptionInstrument(ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestID)
{
	ReqQryOptionInstrumentPackage* reqPackage = ReqQryOptionInstrumentPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqQryOptionInstrument = Allocate<ReqQryOptionInstrumentField>();
	memcpy(reqPackage->ReqQryOptionInstrument, reqQryOptionInstrument, sizeof(ReqQryOptionInstrumentField));
	TrunsferGbkToUtf8(reqPackage->ReqQryOptionInstrument->ExchangeID);
	TrunsferGbkToUtf8(reqPackage->ReqQryOptionInstrument->InstrumentID);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryCommissionRate(ReqQryCommissionRateField* reqQryCommissionRate, int requestID)
{
	ReqQryCommissionRatePackage* reqPackage = ReqQryCommissionRatePackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqQryCommissionRate = Allocate<ReqQryCommissionRateField>();
	memcpy(reqPackage->ReqQryCommissionRate, reqQryCommissionRate, sizeof(ReqQryCommissionRateField));
	TrunsferGbkToUtf8(reqPackage->ReqQryCommissionRate->AccountID);
	TrunsferGbkToUtf8(reqPackage->ReqQryCommissionRate->ExchangeID);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryMoneyTransfer(ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestID)
{
	ReqQryMoneyTransferPackage* reqPackage = ReqQryMoneyTransferPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqQryMoneyTransfer = Allocate<ReqQryMoneyTransferField>();
	memcpy(reqPackage->ReqQryMoneyTransfer, reqQryMoneyTransfer, sizeof(ReqQryMoneyTransferField));
	TrunsferGbkToUtf8(reqPackage->ReqQryMoneyTransfer->AccountID);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID)
{
	ReqInsertOrderPackage* reqPackage = ReqInsertOrderPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqInsertOrder = Allocate<ReqInsertOrderField>();
	memcpy(reqPackage->ReqInsertOrder, reqInsertOrder, sizeof(ReqInsertOrderField));
	TrunsferGbkToUtf8(reqPackage->ReqInsertOrder->AccountID);
	TrunsferGbkToUtf8(reqPackage->ReqInsertOrder->ExchangeID);
	TrunsferGbkToUtf8(reqPackage->ReqInsertOrder->InstrumentID);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID)
{
	ReqCancelOrderPackage* reqPackage = ReqCancelOrderPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqCancelOrder = Allocate<ReqCancelOrderField>();
	memcpy(reqPackage->ReqCancelOrder, reqCancelOrder, sizeof(ReqCancelOrderField));
	TrunsferGbkToUtf8(reqPackage->ReqCancelOrder->AccountID);
	TrunsferGbkToUtf8(reqPackage->ReqCancelOrder->ExchangeID);
	TrunsferGbkToUtf8(reqPackage->ReqCancelOrder->InstrumentID);
	TrunsferGbkToUtf8(reqPackage->ReqCancelOrder->OrderSysID);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}

