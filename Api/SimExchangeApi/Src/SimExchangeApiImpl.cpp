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
	case RspQryInstrumentPackage::PackageID:
	{
		m_SimExchangeSpi->OnRspQryInstrument(((RspQryInstrumentPackage*)package)->Instrument, ((RspQryInstrumentPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspSEBrokerLoginPackage::PackageID:
	{
		m_SimExchangeSpi->OnRspSEBrokerLogin(((RspSEBrokerLoginPackage*)package)->RspSEBrokerLogin, ((RspSEBrokerLoginPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspSEInsertOrderPackage::PackageID:
	{
		m_SimExchangeSpi->OnRspSEInsertOrder(((RspSEInsertOrderPackage*)package)->ReqSEInsertOrder, ((RspSEInsertOrderPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspSECancelOrderPackage::PackageID:
	{
		m_SimExchangeSpi->OnRspSECancelOrder(((RspSECancelOrderPackage*)package)->ReqSECancelOrder, ((RspSECancelOrderPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQrySEOrderPackage::PackageID:
	{
		m_SimExchangeSpi->OnRspQrySEOrder(((RspQrySEOrderPackage*)package)->SEOrder, ((RspQrySEOrderPackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspQrySETradePackage::PackageID:
	{
		m_SimExchangeSpi->OnRspQrySETrade(((RspQrySETradePackage*)package)->SETrade, ((RspQrySETradePackage*)package)->RspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RtnSEOrderPackage::PackageID:
	{
		m_SimExchangeSpi->OnRtnSEOrder(((RtnSEOrderPackage*)package)->SEOrder);
		break;
	}
	case RtnSETradePackage::PackageID:
	{
		m_SimExchangeSpi->OnRtnSETrade(((RtnSETradePackage*)package)->SETrade);
		break;
	}
	default:
		break;
	}
	package->Free();
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
int SimExchangeApiImpl::ReqSEBrokerLogin(ReqSEBrokerLoginField* reqSEBrokerLogin, int requestID)
{
	ReqSEBrokerLoginPackage* reqPackage = ReqSEBrokerLoginPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqSEBrokerLogin = Allocate<ReqSEBrokerLoginField>();
	memcpy(reqPackage->ReqSEBrokerLogin, reqSEBrokerLogin, sizeof(ReqSEBrokerLoginField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int SimExchangeApiImpl::ReqSEInsertOrder(ReqSEInsertOrderField* reqSEInsertOrder, int requestID)
{
	ReqSEInsertOrderPackage* reqPackage = ReqSEInsertOrderPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqSEInsertOrder = Allocate<ReqSEInsertOrderField>();
	memcpy(reqPackage->ReqSEInsertOrder, reqSEInsertOrder, sizeof(ReqSEInsertOrderField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int SimExchangeApiImpl::ReqSECancelOrder(ReqSECancelOrderField* reqSECancelOrder, int requestID)
{
	ReqSECancelOrderPackage* reqPackage = ReqSECancelOrderPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqSECancelOrder = Allocate<ReqSECancelOrderField>();
	memcpy(reqPackage->ReqSECancelOrder, reqSECancelOrder, sizeof(ReqSECancelOrderField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int SimExchangeApiImpl::ReqQrySEOrder(ReqQrySEOrderField* reqQrySEOrder, int requestID)
{
	ReqQrySEOrderPackage* reqPackage = ReqQrySEOrderPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqQrySEOrder = Allocate<ReqQrySEOrderField>();
	memcpy(reqPackage->ReqQrySEOrder, reqQrySEOrder, sizeof(ReqQrySEOrderField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}
int SimExchangeApiImpl::ReqQrySETrade(ReqQrySETradeField* reqQrySETrade, int requestID)
{
	ReqQrySETradePackage* reqPackage = ReqQrySETradePackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqQrySETrade = Allocate<ReqQrySETradeField>();
	memcpy(reqPackage->ReqQrySETrade, reqQrySETrade, sizeof(ReqQrySETradeField));
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Free();
	return result;
}

