// 本文件由 ../Templates/Cpp/Api/ApiImpl.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "TraderApiImpl.h"
#include "Error.h"
#include "Packages.h"
#include <Spark/Network/Protocol/Items.h>

using namespace Spark;
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
	switch (package->Head.PackageID)
	{
	case RspAccountLoginPackage::PackageID:
	{
		traderSpi->OnRspAccountLogin(static_cast<RspAccountLoginPackage*>(package)->RspAccountLogin, static_cast<RspAccountLoginPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspAccountLogoutPackage::PackageID:
	{
		traderSpi->OnRspAccountLogout(static_cast<RspAccountLogoutPackage*>(package)->RspAccountLogout, static_cast<RspAccountLogoutPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryHolderAccountPackage::PackageID:
	{
		traderSpi->OnRspQryHolderAccount(static_cast<RspQryHolderAccountPackage*>(package)->HolderAccount, static_cast<RspQryHolderAccountPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryCapitalPackage::PackageID:
	{
		traderSpi->OnRspQryCapital(static_cast<RspQryCapitalPackage*>(package)->Capital, static_cast<RspQryCapitalPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryPositionPackage::PackageID:
	{
		traderSpi->OnRspQryPosition(static_cast<RspQryPositionPackage*>(package)->Position, static_cast<RspQryPositionPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryOrderPackage::PackageID:
	{
		traderSpi->OnRspQryOrder(static_cast<RspQryOrderPackage*>(package)->Order, static_cast<RspQryOrderPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryTradePackage::PackageID:
	{
		traderSpi->OnRspQryTrade(static_cast<RspQryTradePackage*>(package)->Trade, static_cast<RspQryTradePackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryInstrumentPackage::PackageID:
	{
		traderSpi->OnRspQryInstrument(static_cast<RspQryInstrumentPackage*>(package)->Instrument, static_cast<RspQryInstrumentPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryOptionInstrumentPackage::PackageID:
	{
		traderSpi->OnRspQryOptionInstrument(static_cast<RspQryOptionInstrumentPackage*>(package)->OptionInstrument, static_cast<RspQryOptionInstrumentPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryCommissionRatePackage::PackageID:
	{
		traderSpi->OnRspQryCommissionRate(static_cast<RspQryCommissionRatePackage*>(package)->CommissionRate, static_cast<RspQryCommissionRatePackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryMoneyTransferPackage::PackageID:
	{
		traderSpi->OnRspQryMoneyTransfer(static_cast<RspQryMoneyTransferPackage*>(package)->MoneyTransfer, static_cast<RspQryMoneyTransferPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspInsertOrderPackage::PackageID:
	{
		traderSpi->OnRspInsertOrder(static_cast<RspInsertOrderPackage*>(package)->ReqInsertOrder, static_cast<RspInsertOrderPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspCancelOrderPackage::PackageID:
	{
		traderSpi->OnRspCancelOrder(static_cast<RspCancelOrderPackage*>(package)->ReqCancelOrder, static_cast<RspCancelOrderPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RtnOrderPackage::PackageID:
	{
		traderSpi->OnRtnOrder(static_cast<RtnOrderPackage*>(package)->Order);
		break;
	}
	case RtnTradePackage::PackageID:
	{
		traderSpi->OnRtnTrade(static_cast<RtnTradePackage*>(package)->Trade);
		break;
	}
	case RtnMoneyTransferPackage::PackageID:
	{
		traderSpi->OnRtnMoneyTransfer(static_cast<RtnMoneyTransferPackage*>(package)->MoneyTransfer);
		break;
	}
	case RtnAccountLogoutPackage::PackageID:
	{
		traderSpi->OnRtnAccountLogout(static_cast<RtnAccountLogoutPackage*>(package)->AccountLogout);
		break;
	}
	default:
		break;
	}
	package->Deallocate();
}


int TraderApiImpl::ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestID)
{
	ReqAccountLoginPackage* reqPackage = ReqAccountLoginPackage::Allocate();
	reqPackage->Prepare(sessionID, false, requestID);
	reqPackage->ReqAccountLogin = Allocate<ReqAccountLoginField>();
	memcpy(reqPackage->ReqAccountLogin, reqAccountLogin, sizeof(ReqAccountLoginField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestID)
{
	ReqAccountLogoutPackage* reqPackage = ReqAccountLogoutPackage::Allocate();
	reqPackage->Prepare(sessionID, false, requestID);
	reqPackage->ReqAccountLogout = Allocate<ReqAccountLogoutField>();
	memcpy(reqPackage->ReqAccountLogout, reqAccountLogout, sizeof(ReqAccountLogoutField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryHolderAccount(const ReqQryHolderAccountField* reqQryHolderAccount, int requestID)
{
	ReqQryHolderAccountPackage* reqPackage = ReqQryHolderAccountPackage::Allocate();
	reqPackage->Prepare(sessionID, false, requestID);
	reqPackage->ReqQryHolderAccount = Allocate<ReqQryHolderAccountField>();
	memcpy(reqPackage->ReqQryHolderAccount, reqQryHolderAccount, sizeof(ReqQryHolderAccountField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryCapital(const ReqQryCapitalField* reqQryCapital, int requestID)
{
	ReqQryCapitalPackage* reqPackage = ReqQryCapitalPackage::Allocate();
	reqPackage->Prepare(sessionID, false, requestID);
	reqPackage->ReqQryCapital = Allocate<ReqQryCapitalField>();
	memcpy(reqPackage->ReqQryCapital, reqQryCapital, sizeof(ReqQryCapitalField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryPosition(const ReqQryPositionField* reqQryPosition, int requestID)
{
	ReqQryPositionPackage* reqPackage = ReqQryPositionPackage::Allocate();
	reqPackage->Prepare(sessionID, false, requestID);
	reqPackage->ReqQryPosition = Allocate<ReqQryPositionField>();
	memcpy(reqPackage->ReqQryPosition, reqQryPosition, sizeof(ReqQryPositionField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestID)
{
	ReqQryOrderPackage* reqPackage = ReqQryOrderPackage::Allocate();
	reqPackage->Prepare(sessionID, false, requestID);
	reqPackage->ReqQryOrder = Allocate<ReqQryOrderField>();
	memcpy(reqPackage->ReqQryOrder, reqQryOrder, sizeof(ReqQryOrderField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestID)
{
	ReqQryTradePackage* reqPackage = ReqQryTradePackage::Allocate();
	reqPackage->Prepare(sessionID, false, requestID);
	reqPackage->ReqQryTrade = Allocate<ReqQryTradeField>();
	memcpy(reqPackage->ReqQryTrade, reqQryTrade, sizeof(ReqQryTradeField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestID)
{
	ReqQryInstrumentPackage* reqPackage = ReqQryInstrumentPackage::Allocate();
	reqPackage->Prepare(sessionID, false, requestID);
	reqPackage->ReqQryInstrument = Allocate<ReqQryInstrumentField>();
	memcpy(reqPackage->ReqQryInstrument, reqQryInstrument, sizeof(ReqQryInstrumentField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryOptionInstrument(const ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestID)
{
	ReqQryOptionInstrumentPackage* reqPackage = ReqQryOptionInstrumentPackage::Allocate();
	reqPackage->Prepare(sessionID, false, requestID);
	reqPackage->ReqQryOptionInstrument = Allocate<ReqQryOptionInstrumentField>();
	memcpy(reqPackage->ReqQryOptionInstrument, reqQryOptionInstrument, sizeof(ReqQryOptionInstrumentField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryCommissionRate(const ReqQryCommissionRateField* reqQryCommissionRate, int requestID)
{
	ReqQryCommissionRatePackage* reqPackage = ReqQryCommissionRatePackage::Allocate();
	reqPackage->Prepare(sessionID, false, requestID);
	reqPackage->ReqQryCommissionRate = Allocate<ReqQryCommissionRateField>();
	memcpy(reqPackage->ReqQryCommissionRate, reqQryCommissionRate, sizeof(ReqQryCommissionRateField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryMoneyTransfer(const ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestID)
{
	ReqQryMoneyTransferPackage* reqPackage = ReqQryMoneyTransferPackage::Allocate();
	reqPackage->Prepare(sessionID, false, requestID);
	reqPackage->ReqQryMoneyTransfer = Allocate<ReqQryMoneyTransferField>();
	memcpy(reqPackage->ReqQryMoneyTransfer, reqQryMoneyTransfer, sizeof(ReqQryMoneyTransferField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestID)
{
	ReqInsertOrderPackage* reqPackage = ReqInsertOrderPackage::Allocate();
	reqPackage->Prepare(sessionID, false, requestID);
	reqPackage->ReqInsertOrder = Allocate<ReqInsertOrderField>();
	memcpy(reqPackage->ReqInsertOrder, reqInsertOrder, sizeof(ReqInsertOrderField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestID)
{
	ReqCancelOrderPackage* reqPackage = ReqCancelOrderPackage::Allocate();
	reqPackage->Prepare(sessionID, false, requestID);
	reqPackage->ReqCancelOrder = Allocate<ReqCancelOrderField>();
	memcpy(reqPackage->ReqCancelOrder, reqCancelOrder, sizeof(ReqCancelOrderField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
}
