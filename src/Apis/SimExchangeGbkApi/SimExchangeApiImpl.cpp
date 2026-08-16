#include "SimExchangeApiImpl.h"
#include "Error.h"
#include "Packages.h"
#include <Spark/Network/Protocol/Items.h>
#include <Spark/Serialization/Encode/Encode.h>


SimExchangeApi* SimExchangeApi::CreateSimExchangeApi()
{
	return new SimExchangeApiImpl();
}
SimExchangeApiImpl::SimExchangeApiImpl()
{
}

void SimExchangeApiImpl::OnMessage(Package* package)
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
		m_SimExchangeSpi->OnRspAccountLogin(rspAccountLogin, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
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
		m_SimExchangeSpi->OnRspAccountLogout(rspAccountLogout, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
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
		m_SimExchangeSpi->OnRspQryOrder(order, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
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
		m_SimExchangeSpi->OnRspQryTrade(trade, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
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
		m_SimExchangeSpi->OnRspQryInstrument(instrument, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
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
		m_SimExchangeSpi->OnRspInsertOrder(reqInsertOrder, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
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
		m_SimExchangeSpi->OnRspCancelOrder(reqCancelOrder, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
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
		m_SimExchangeSpi->OnRtnOrder(order);
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
		m_SimExchangeSpi->OnRtnTrade(trade);
		break;
	}
	default:
		break;
	}
	package->Deallocate();
}


int SimExchangeApiImpl::ReqAccountLogin(ReqAccountLoginField* reqAccountLogin, int requestID)
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
int SimExchangeApiImpl::ReqAccountLogout(ReqAccountLogoutField* reqAccountLogout, int requestID)
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
int SimExchangeApiImpl::ReqQryOrder(ReqQryOrderField* reqQryOrder, int requestID)
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
int SimExchangeApiImpl::ReqQryTrade(ReqQryTradeField* reqQryTrade, int requestID)
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
int SimExchangeApiImpl::ReqQryInstrument(ReqQryInstrumentField* reqQryInstrument, int requestID)
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
int SimExchangeApiImpl::ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID)
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
int SimExchangeApiImpl::ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID)
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

