#include "TradeApiImpl.h"
#include "Items.h"
#include "Packages.h"
#include "MemCacheTemplateSingleton.h"
#include "Logger.h"
#include "Error.h"
#include <cstring>


TradeApi* TradeApi::CreateTradeApi()
{
	return new TradeApiImpl();
}
void TradeApi::SetExternLogger(WriteLogFunc externLogger)
{
	Logger::SetExternLogger(externLogger);
}
TradeApiImpl::TradeApiImpl()
{
}

void TradeApiImpl::OnMessage(Package* package)
{
	switch (package->Head.PackageID)
	{
	case RspAccountLoginPackage::PackageID:
	{
		m_TradeSpi->OnRspAccountLogin(((RspAccountLoginPackage*)package)->RspAccountLogin, ((RspAccountLoginPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspAccountLogoutPackage::PackageID:
	{
		m_TradeSpi->OnRspAccountLogout(((RspAccountLogoutPackage*)package)->RspAccountLogout, ((RspAccountLogoutPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryHolderAccountPackage::PackageID:
	{
		m_TradeSpi->OnRspQryHolderAccount(((RspQryHolderAccountPackage*)package)->HolderAccount, ((RspQryHolderAccountPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryCapitalPackage::PackageID:
	{
		m_TradeSpi->OnRspQryCapital(((RspQryCapitalPackage*)package)->Capital, ((RspQryCapitalPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryPositionPackage::PackageID:
	{
		m_TradeSpi->OnRspQryPosition(((RspQryPositionPackage*)package)->Position, ((RspQryPositionPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryOrderPackage::PackageID:
	{
		m_TradeSpi->OnRspQryOrder(((RspQryOrderPackage*)package)->Order, ((RspQryOrderPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryTradePackage::PackageID:
	{
		m_TradeSpi->OnRspQryTrade(((RspQryTradePackage*)package)->Trade, ((RspQryTradePackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryInstrumentPackage::PackageID:
	{
		m_TradeSpi->OnRspQryInstrument(((RspQryInstrumentPackage*)package)->Instrument, ((RspQryInstrumentPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryOptionInstrumentPackage::PackageID:
	{
		m_TradeSpi->OnRspQryOptionInstrument(((RspQryOptionInstrumentPackage*)package)->OptionInstrument, ((RspQryOptionInstrumentPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryCommissionRatePackage::PackageID:
	{
		m_TradeSpi->OnRspQryCommissionRate(((RspQryCommissionRatePackage*)package)->CommissionRate, ((RspQryCommissionRatePackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryMoneyTransferPackage::PackageID:
	{
		m_TradeSpi->OnRspQryMoneyTransfer(((RspQryMoneyTransferPackage*)package)->MoneyTransfer, ((RspQryMoneyTransferPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspInsertOrderPackage::PackageID:
	{
		m_TradeSpi->OnRspInsertOrder(((RspInsertOrderPackage*)package)->ReqInsertOrder, ((RspInsertOrderPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspCancelOrderPackage::PackageID:
	{
		m_TradeSpi->OnRspCancelOrder(((RspCancelOrderPackage*)package)->ReqCancelOrder, ((RspCancelOrderPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RtnOrderPackage::PackageID:
	{
		m_TradeSpi->OnRtnOrder(((RtnOrderPackage*)package)->Order);
		break;
	}
	case RtnTradePackage::PackageID:
	{
		m_TradeSpi->OnRtnTrade(((RtnTradePackage*)package)->Trade);
		break;
	}
	case RtnMoneyTransferPackage::PackageID:
	{
		m_TradeSpi->OnRtnMoneyTransfer(((RtnMoneyTransferPackage*)package)->MoneyTransfer);
		break;
	}
	case RtnAccountLogoutPackage::PackageID:
	{
		m_TradeSpi->OnRtnAccountLogout(((RtnAccountLogoutPackage*)package)->AccountLogout);
		break;
	}
	default:
		break;
	}
	package->Free();
}


int TradeApiImpl::ReqAccountLogin(ReqAccountLoginField* reqAccountLogin, int requestID)
{
	ReqAccountLoginPackage* reqPackage = ReqAccountLoginPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqAccountLogin = Allocate<ReqAccountLoginField>();
	memcpy(reqPackage->ReqAccountLogin, reqAccountLogin, sizeof(ReqAccountLoginField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int TradeApiImpl::ReqAccountLogout(ReqAccountLogoutField* reqAccountLogout, int requestID)
{
	ReqAccountLogoutPackage* reqPackage = ReqAccountLogoutPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqAccountLogout = Allocate<ReqAccountLogoutField>();
	memcpy(reqPackage->ReqAccountLogout, reqAccountLogout, sizeof(ReqAccountLogoutField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int TradeApiImpl::ReqQryHolderAccount(ReqQryHolderAccountField* reqQryHolderAccount, int requestID)
{
	ReqQryHolderAccountPackage* reqPackage = ReqQryHolderAccountPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqQryHolderAccount = Allocate<ReqQryHolderAccountField>();
	memcpy(reqPackage->ReqQryHolderAccount, reqQryHolderAccount, sizeof(ReqQryHolderAccountField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int TradeApiImpl::ReqQryCapital(ReqQryCapitalField* reqQryCapital, int requestID)
{
	ReqQryCapitalPackage* reqPackage = ReqQryCapitalPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqQryCapital = Allocate<ReqQryCapitalField>();
	memcpy(reqPackage->ReqQryCapital, reqQryCapital, sizeof(ReqQryCapitalField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int TradeApiImpl::ReqQryPosition(ReqQryPositionField* reqQryPosition, int requestID)
{
	ReqQryPositionPackage* reqPackage = ReqQryPositionPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqQryPosition = Allocate<ReqQryPositionField>();
	memcpy(reqPackage->ReqQryPosition, reqQryPosition, sizeof(ReqQryPositionField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int TradeApiImpl::ReqQryOrder(ReqQryOrderField* reqQryOrder, int requestID)
{
	ReqQryOrderPackage* reqPackage = ReqQryOrderPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqQryOrder = Allocate<ReqQryOrderField>();
	memcpy(reqPackage->ReqQryOrder, reqQryOrder, sizeof(ReqQryOrderField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int TradeApiImpl::ReqQryTrade(ReqQryTradeField* reqQryTrade, int requestID)
{
	ReqQryTradePackage* reqPackage = ReqQryTradePackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqQryTrade = Allocate<ReqQryTradeField>();
	memcpy(reqPackage->ReqQryTrade, reqQryTrade, sizeof(ReqQryTradeField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int TradeApiImpl::ReqQryInstrument(ReqQryInstrumentField* reqQryInstrument, int requestID)
{
	ReqQryInstrumentPackage* reqPackage = ReqQryInstrumentPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqQryInstrument = Allocate<ReqQryInstrumentField>();
	memcpy(reqPackage->ReqQryInstrument, reqQryInstrument, sizeof(ReqQryInstrumentField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int TradeApiImpl::ReqQryOptionInstrument(ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestID)
{
	ReqQryOptionInstrumentPackage* reqPackage = ReqQryOptionInstrumentPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqQryOptionInstrument = Allocate<ReqQryOptionInstrumentField>();
	memcpy(reqPackage->ReqQryOptionInstrument, reqQryOptionInstrument, sizeof(ReqQryOptionInstrumentField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int TradeApiImpl::ReqQryCommissionRate(ReqQryCommissionRateField* reqQryCommissionRate, int requestID)
{
	ReqQryCommissionRatePackage* reqPackage = ReqQryCommissionRatePackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqQryCommissionRate = Allocate<ReqQryCommissionRateField>();
	memcpy(reqPackage->ReqQryCommissionRate, reqQryCommissionRate, sizeof(ReqQryCommissionRateField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int TradeApiImpl::ReqQryMoneyTransfer(ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestID)
{
	ReqQryMoneyTransferPackage* reqPackage = ReqQryMoneyTransferPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqQryMoneyTransfer = Allocate<ReqQryMoneyTransferField>();
	memcpy(reqPackage->ReqQryMoneyTransfer, reqQryMoneyTransfer, sizeof(ReqQryMoneyTransferField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int TradeApiImpl::ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID)
{
	ReqInsertOrderPackage* reqPackage = ReqInsertOrderPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqInsertOrder = Allocate<ReqInsertOrderField>();
	memcpy(reqPackage->ReqInsertOrder, reqInsertOrder, sizeof(ReqInsertOrderField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int TradeApiImpl::ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID)
{
	ReqCancelOrderPackage* reqPackage = ReqCancelOrderPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqCancelOrder = Allocate<ReqCancelOrderField>();
	memcpy(reqPackage->ReqCancelOrder, reqCancelOrder, sizeof(ReqCancelOrderField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}

