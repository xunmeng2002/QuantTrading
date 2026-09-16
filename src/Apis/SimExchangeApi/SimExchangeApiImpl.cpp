// 本文件由 ../Templates/Cpp/Api/ApiImpl.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "SimExchangeApiImpl.h"
#include "Error.h"
#include "Packages.h"
#include <Spark/Network/Protocol/Items.h>

using namespace Spark;
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
		simExchangeSpi->OnRspAccountLogin(static_cast<RspAccountLoginPackage*>(package)->RspAccountLogin, static_cast<RspAccountLoginPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspAccountLogoutPackage::PackageId:
	{
		simExchangeSpi->OnRspAccountLogout(static_cast<RspAccountLogoutPackage*>(package)->RspAccountLogout, static_cast<RspAccountLogoutPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryOrderPackage::PackageId:
	{
		simExchangeSpi->OnRspQryOrder(static_cast<RspQryOrderPackage*>(package)->Order, static_cast<RspQryOrderPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryTradePackage::PackageId:
	{
		simExchangeSpi->OnRspQryTrade(static_cast<RspQryTradePackage*>(package)->Trade, static_cast<RspQryTradePackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryInstrumentPackage::PackageId:
	{
		simExchangeSpi->OnRspQryInstrument(static_cast<RspQryInstrumentPackage*>(package)->Instrument, static_cast<RspQryInstrumentPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspInsertOrderPackage::PackageId:
	{
		simExchangeSpi->OnRspInsertOrder(static_cast<RspInsertOrderPackage*>(package)->ReqInsertOrder, static_cast<RspInsertOrderPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspCancelOrderPackage::PackageId:
	{
		simExchangeSpi->OnRspCancelOrder(static_cast<RspCancelOrderPackage*>(package)->ReqCancelOrder, static_cast<RspCancelOrderPackage*>(package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RtnOrderPackage::PackageId:
	{
		simExchangeSpi->OnRtnOrder(static_cast<RtnOrderPackage*>(package)->Order);
		break;
	}
	case RtnTradePackage::PackageId:
	{
		simExchangeSpi->OnRtnTrade(static_cast<RtnTradePackage*>(package)->Trade);
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
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int SimExchangeApiImpl::ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestId)
{
	ReqAccountLogoutPackage* reqPackage = ReqAccountLogoutPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqAccountLogout = Allocate<ReqAccountLogoutField>();
	memcpy(reqPackage->ReqAccountLogout, reqAccountLogout, sizeof(ReqAccountLogoutField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int SimExchangeApiImpl::ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestId)
{
	ReqQryOrderPackage* reqPackage = ReqQryOrderPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryOrder = Allocate<ReqQryOrderField>();
	memcpy(reqPackage->ReqQryOrder, reqQryOrder, sizeof(ReqQryOrderField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int SimExchangeApiImpl::ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestId)
{
	ReqQryTradePackage* reqPackage = ReqQryTradePackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryTrade = Allocate<ReqQryTradeField>();
	memcpy(reqPackage->ReqQryTrade, reqQryTrade, sizeof(ReqQryTradeField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int SimExchangeApiImpl::ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestId)
{
	ReqQryInstrumentPackage* reqPackage = ReqQryInstrumentPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqQryInstrument = Allocate<ReqQryInstrumentField>();
	memcpy(reqPackage->ReqQryInstrument, reqQryInstrument, sizeof(ReqQryInstrumentField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int SimExchangeApiImpl::ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestId)
{
	ReqInsertOrderPackage* reqPackage = ReqInsertOrderPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqInsertOrder = Allocate<ReqInsertOrderField>();
	memcpy(reqPackage->ReqInsertOrder, reqInsertOrder, sizeof(ReqInsertOrderField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int SimExchangeApiImpl::ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestId)
{
	ReqCancelOrderPackage* reqPackage = ReqCancelOrderPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqCancelOrder = Allocate<ReqCancelOrderField>();
	memcpy(reqPackage->ReqCancelOrder, reqCancelOrder, sizeof(ReqCancelOrderField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
}
