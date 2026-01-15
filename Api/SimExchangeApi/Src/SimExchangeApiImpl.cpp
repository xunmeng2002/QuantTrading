#include "SimExchangeApiImpl.h"
#include "Items.h"
#include "Packages.h"
#include "MemCacheTemplateSingleton.h"
#include "Logger.h"
#include "Error.h"
#include <cstring>


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
		m_SimExchangeSpi->OnRspAccountLogin(((RspAccountLoginPackage*)package)->RspAccountLogin, ((RspAccountLoginPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspAccountLogoutPackage::PackageID:
	{
		m_SimExchangeSpi->OnRspAccountLogout(((RspAccountLogoutPackage*)package)->RspAccountLogout, ((RspAccountLogoutPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryOrderPackage::PackageID:
	{
		m_SimExchangeSpi->OnRspQryOrder(((RspQryOrderPackage*)package)->Order, ((RspQryOrderPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryTradePackage::PackageID:
	{
		m_SimExchangeSpi->OnRspQryTrade(((RspQryTradePackage*)package)->Trade, ((RspQryTradePackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQryInstrumentPackage::PackageID:
	{
		m_SimExchangeSpi->OnRspQryInstrument(((RspQryInstrumentPackage*)package)->Instrument, ((RspQryInstrumentPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspInsertOrderPackage::PackageID:
	{
		m_SimExchangeSpi->OnRspInsertOrder(((RspInsertOrderPackage*)package)->ReqInsertOrder, ((RspInsertOrderPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspCancelOrderPackage::PackageID:
	{
		m_SimExchangeSpi->OnRspCancelOrder(((RspCancelOrderPackage*)package)->ReqCancelOrder, ((RspCancelOrderPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RtnOrderPackage::PackageID:
	{
		m_SimExchangeSpi->OnRtnOrder(((RtnOrderPackage*)package)->Order);
		break;
	}
	case RtnTradePackage::PackageID:
	{
		m_SimExchangeSpi->OnRtnTrade(((RtnTradePackage*)package)->Trade);
		break;
	}
	default:
		break;
	}
	package->Free();
}


int SimExchangeApiImpl::ReqAccountLogin(ReqAccountLoginField* reqAccountLogin, int requestID)
{
	ReqAccountLoginPackage* reqPackage = ReqAccountLoginPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqAccountLogin = Allocate<ReqAccountLoginField>();
	memcpy(reqPackage->ReqAccountLogin, reqAccountLogin, sizeof(ReqAccountLoginField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int SimExchangeApiImpl::ReqAccountLogout(ReqAccountLogoutField* reqAccountLogout, int requestID)
{
	ReqAccountLogoutPackage* reqPackage = ReqAccountLogoutPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqAccountLogout = Allocate<ReqAccountLogoutField>();
	memcpy(reqPackage->ReqAccountLogout, reqAccountLogout, sizeof(ReqAccountLogoutField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int SimExchangeApiImpl::ReqQryOrder(ReqQryOrderField* reqQryOrder, int requestID)
{
	ReqQryOrderPackage* reqPackage = ReqQryOrderPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqQryOrder = Allocate<ReqQryOrderField>();
	memcpy(reqPackage->ReqQryOrder, reqQryOrder, sizeof(ReqQryOrderField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int SimExchangeApiImpl::ReqQryTrade(ReqQryTradeField* reqQryTrade, int requestID)
{
	ReqQryTradePackage* reqPackage = ReqQryTradePackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqQryTrade = Allocate<ReqQryTradeField>();
	memcpy(reqPackage->ReqQryTrade, reqQryTrade, sizeof(ReqQryTradeField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int SimExchangeApiImpl::ReqQryInstrument(ReqQryInstrumentField* reqQryInstrument, int requestID)
{
	ReqQryInstrumentPackage* reqPackage = ReqQryInstrumentPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqQryInstrument = Allocate<ReqQryInstrumentField>();
	memcpy(reqPackage->ReqQryInstrument, reqQryInstrument, sizeof(ReqQryInstrumentField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int SimExchangeApiImpl::ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID)
{
	ReqInsertOrderPackage* reqPackage = ReqInsertOrderPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqInsertOrder = Allocate<ReqInsertOrderField>();
	memcpy(reqPackage->ReqInsertOrder, reqInsertOrder, sizeof(ReqInsertOrderField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int SimExchangeApiImpl::ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID)
{
	ReqCancelOrderPackage* reqPackage = ReqCancelOrderPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqCancelOrder = Allocate<ReqCancelOrderField>();
	memcpy(reqPackage->ReqCancelOrder, reqCancelOrder, sizeof(ReqCancelOrderField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}

