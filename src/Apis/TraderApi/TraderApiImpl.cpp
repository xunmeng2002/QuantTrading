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
	switch (package->Head.PackageId)
	{
	case RspAccountLoginPackage::PackageId:
	{
		traderSpi_->OnRspAccountLogin(static_cast<RspAccountLoginPackage*>(package)->RspAccountLogin, static_cast<RspAccountLoginPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspAccountLogoutPackage::PackageId:
	{
		traderSpi_->OnRspAccountLogout(static_cast<RspAccountLogoutPackage*>(package)->RspAccountLogout, static_cast<RspAccountLogoutPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryHolderAccountPackage::PackageId:
	{
		traderSpi_->OnRspQryHolderAccount(static_cast<RspQryHolderAccountPackage*>(package)->HolderAccount, static_cast<RspQryHolderAccountPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryCapitalPackage::PackageId:
	{
		traderSpi_->OnRspQryCapital(static_cast<RspQryCapitalPackage*>(package)->Capital, static_cast<RspQryCapitalPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryPositionPackage::PackageId:
	{
		traderSpi_->OnRspQryPosition(static_cast<RspQryPositionPackage*>(package)->Position, static_cast<RspQryPositionPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryOrderPackage::PackageId:
	{
		traderSpi_->OnRspQryOrder(static_cast<RspQryOrderPackage*>(package)->Order, static_cast<RspQryOrderPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryTradePackage::PackageId:
	{
		traderSpi_->OnRspQryTrade(static_cast<RspQryTradePackage*>(package)->Trade, static_cast<RspQryTradePackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryInstrumentPackage::PackageId:
	{
		traderSpi_->OnRspQryInstrument(static_cast<RspQryInstrumentPackage*>(package)->Instrument, static_cast<RspQryInstrumentPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryOptionInstrumentPackage::PackageId:
	{
		traderSpi_->OnRspQryOptionInstrument(static_cast<RspQryOptionInstrumentPackage*>(package)->OptionInstrument, static_cast<RspQryOptionInstrumentPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryCommissionRatePackage::PackageId:
	{
		traderSpi_->OnRspQryCommissionRate(static_cast<RspQryCommissionRatePackage*>(package)->CommissionRate, static_cast<RspQryCommissionRatePackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryMoneyTransferPackage::PackageId:
	{
		traderSpi_->OnRspQryMoneyTransfer(static_cast<RspQryMoneyTransferPackage*>(package)->MoneyTransfer, static_cast<RspQryMoneyTransferPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspInsertOrderPackage::PackageId:
	{
		traderSpi_->OnRspInsertOrder(static_cast<RspInsertOrderPackage*>(package)->ReqInsertOrder, static_cast<RspInsertOrderPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspCancelOrderPackage::PackageId:
	{
		traderSpi_->OnRspCancelOrder(static_cast<RspCancelOrderPackage*>(package)->ReqCancelOrder, static_cast<RspCancelOrderPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RtnOrderPackage::PackageId:
	{
		traderSpi_->OnRtnOrder(static_cast<RtnOrderPackage*>(package)->Order);
		break;
	}
	case RtnTradePackage::PackageId:
	{
		traderSpi_->OnRtnTrade(static_cast<RtnTradePackage*>(package)->Trade);
		break;
	}
	case RtnMoneyTransferPackage::PackageId:
	{
		traderSpi_->OnRtnMoneyTransfer(static_cast<RtnMoneyTransferPackage*>(package)->MoneyTransfer);
		break;
	}
	case RtnAccountLogoutPackage::PackageId:
	{
		traderSpi_->OnRtnAccountLogout(static_cast<RtnAccountLogoutPackage*>(package)->AccountLogout);
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
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestId)
{
	ReqAccountLogoutPackage* reqPackage = ReqAccountLogoutPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqAccountLogout = Allocate<ReqAccountLogoutField>();
	memcpy(reqPackage->ReqAccountLogout, reqAccountLogout, sizeof(ReqAccountLogoutField));
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryHolderAccount(const ReqQryHolderAccountField* reqQryHolderAccount, int requestId)
{
	ReqQryHolderAccountPackage* reqPackage = ReqQryHolderAccountPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryHolderAccount = Allocate<ReqQryHolderAccountField>();
	memcpy(reqPackage->ReqQryHolderAccount, reqQryHolderAccount, sizeof(ReqQryHolderAccountField));
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryCapital(const ReqQryCapitalField* reqQryCapital, int requestId)
{
	ReqQryCapitalPackage* reqPackage = ReqQryCapitalPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryCapital = Allocate<ReqQryCapitalField>();
	memcpy(reqPackage->ReqQryCapital, reqQryCapital, sizeof(ReqQryCapitalField));
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryPosition(const ReqQryPositionField* reqQryPosition, int requestId)
{
	ReqQryPositionPackage* reqPackage = ReqQryPositionPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryPosition = Allocate<ReqQryPositionField>();
	memcpy(reqPackage->ReqQryPosition, reqQryPosition, sizeof(ReqQryPositionField));
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestId)
{
	ReqQryOrderPackage* reqPackage = ReqQryOrderPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryOrder = Allocate<ReqQryOrderField>();
	memcpy(reqPackage->ReqQryOrder, reqQryOrder, sizeof(ReqQryOrderField));
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestId)
{
	ReqQryTradePackage* reqPackage = ReqQryTradePackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryTrade = Allocate<ReqQryTradeField>();
	memcpy(reqPackage->ReqQryTrade, reqQryTrade, sizeof(ReqQryTradeField));
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestId)
{
	ReqQryInstrumentPackage* reqPackage = ReqQryInstrumentPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryInstrument = Allocate<ReqQryInstrumentField>();
	memcpy(reqPackage->ReqQryInstrument, reqQryInstrument, sizeof(ReqQryInstrumentField));
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryOptionInstrument(const ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestId)
{
	ReqQryOptionInstrumentPackage* reqPackage = ReqQryOptionInstrumentPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryOptionInstrument = Allocate<ReqQryOptionInstrumentField>();
	memcpy(reqPackage->ReqQryOptionInstrument, reqQryOptionInstrument, sizeof(ReqQryOptionInstrumentField));
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryCommissionRate(const ReqQryCommissionRateField* reqQryCommissionRate, int requestId)
{
	ReqQryCommissionRatePackage* reqPackage = ReqQryCommissionRatePackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryCommissionRate = Allocate<ReqQryCommissionRateField>();
	memcpy(reqPackage->ReqQryCommissionRate, reqQryCommissionRate, sizeof(ReqQryCommissionRateField));
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqQryMoneyTransfer(const ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestId)
{
	ReqQryMoneyTransferPackage* reqPackage = ReqQryMoneyTransferPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryMoneyTransfer = Allocate<ReqQryMoneyTransferField>();
	memcpy(reqPackage->ReqQryMoneyTransfer, reqQryMoneyTransfer, sizeof(ReqQryMoneyTransferField));
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestId)
{
	ReqInsertOrderPackage* reqPackage = ReqInsertOrderPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqInsertOrder = Allocate<ReqInsertOrderField>();
	memcpy(reqPackage->ReqInsertOrder, reqInsertOrder, sizeof(ReqInsertOrderField));
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int TraderApiImpl::ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestId)
{
	ReqCancelOrderPackage* reqPackage = ReqCancelOrderPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqCancelOrder = Allocate<ReqCancelOrderField>();
	memcpy(reqPackage->ReqCancelOrder, reqCancelOrder, sizeof(ReqCancelOrderField));
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
}
