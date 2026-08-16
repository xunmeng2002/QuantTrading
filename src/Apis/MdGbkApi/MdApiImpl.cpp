#include "MdApiImpl.h"
#include "Error.h"
#include "Packages.h"
#include <Spark/Network/Protocol/Items.h>
#include <Spark/Serialization/Encode/Encode.h>


MdApi* MdApi::CreateMdApi()
{
	return new MdApiImpl();
}
MdApiImpl::MdApiImpl()
{
}

void MdApiImpl::OnMessage(Package* package)
{
	switch (package->Head.PackageID)
	{
	case RspMdUserLoginPackage::PackageID:
	{
		auto rspMdUserLogin = ((RspMdUserLoginPackage*)package)->RspMdUserLogin;
		if (rspMdUserLogin != nullptr)
		{
			TrunsferUtf8ToGbk(rspMdUserLogin->UserID);
			TrunsferUtf8ToGbk(rspMdUserLogin->LoginDate);
			TrunsferUtf8ToGbk(rspMdUserLogin->LoginTime);
		}
		auto rspInfo = ((RspMdUserLoginPackage*)package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		m_MdSpi->OnRspMdUserLogin(rspMdUserLogin, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspMdUserLogoutPackage::PackageID:
	{
		auto rspMdUserLogout = ((RspMdUserLogoutPackage*)package)->RspMdUserLogout;
		if (rspMdUserLogout != nullptr)
		{
			TrunsferUtf8ToGbk(rspMdUserLogout->UserID);
		}
		auto rspInfo = ((RspMdUserLogoutPackage*)package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		m_MdSpi->OnRspMdUserLogout(rspMdUserLogout, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspSubMarketDataPackage::PackageID:
	{
		auto rspSubMarketData = ((RspSubMarketDataPackage*)package)->RspSubMarketData;
		if (rspSubMarketData != nullptr)
		{
			TrunsferUtf8ToGbk(rspSubMarketData->ExchangeID);
			TrunsferUtf8ToGbk(rspSubMarketData->InstrumentID);
		}
		auto rspInfo = ((RspSubMarketDataPackage*)package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		m_MdSpi->OnRspSubMarketData(rspSubMarketData, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspUnSubMarketDataPackage::PackageID:
	{
		auto rspUnSubMarketData = ((RspUnSubMarketDataPackage*)package)->RspUnSubMarketData;
		if (rspUnSubMarketData != nullptr)
		{
			TrunsferUtf8ToGbk(rspUnSubMarketData->ExchangeID);
			TrunsferUtf8ToGbk(rspUnSubMarketData->InstrumentID);
		}
		auto rspInfo = ((RspUnSubMarketDataPackage*)package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		m_MdSpi->OnRspUnSubMarketData(rspUnSubMarketData, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RtnDepthMarketDataPackage::PackageID:
	{
		auto depthMarketData = ((RtnDepthMarketDataPackage*)package)->DepthMarketData;
		if (depthMarketData != nullptr)
		{
			TrunsferUtf8ToGbk(depthMarketData->TradingDay);
			TrunsferUtf8ToGbk(depthMarketData->ExchangeID);
			TrunsferUtf8ToGbk(depthMarketData->InstrumentID);
		}
		m_MdSpi->OnRtnDepthMarketData(depthMarketData);
		break;
	}
	case RtnBarMarketDataPackage::PackageID:
	{
		auto barMarketData = ((RtnBarMarketDataPackage*)package)->BarMarketData;
		if (barMarketData != nullptr)
		{
			TrunsferUtf8ToGbk(barMarketData->TradingDay);
			TrunsferUtf8ToGbk(barMarketData->ExchangeID);
			TrunsferUtf8ToGbk(barMarketData->InstrumentID);
		}
		m_MdSpi->OnRtnBarMarketData(barMarketData);
		break;
	}
	default:
		break;
	}
	package->Deallocate();
}


int MdApiImpl::ReqMdUserLogin(ReqMdUserLoginField* reqMdUserLogin, int requestID)
{
	ReqMdUserLoginPackage* reqPackage = ReqMdUserLoginPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqMdUserLogin = Allocate<ReqMdUserLoginField>();
	memcpy(reqPackage->ReqMdUserLogin, reqMdUserLogin, sizeof(ReqMdUserLoginField));
	TrunsferGbkToUtf8(reqPackage->ReqMdUserLogin->UserID);
	TrunsferGbkToUtf8(reqPackage->ReqMdUserLogin->Password);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int MdApiImpl::ReqMdUserLogout(ReqMdUserLogoutField* reqMdUserLogout, int requestID)
{
	ReqMdUserLogoutPackage* reqPackage = ReqMdUserLogoutPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqMdUserLogout = Allocate<ReqMdUserLogoutField>();
	memcpy(reqPackage->ReqMdUserLogout, reqMdUserLogout, sizeof(ReqMdUserLogoutField));
	TrunsferGbkToUtf8(reqPackage->ReqMdUserLogout->UserID);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int MdApiImpl::ReqSubMarketData(ReqSubMarketDataField* reqSubMarketData, int requestID)
{
	ReqSubMarketDataPackage* reqPackage = ReqSubMarketDataPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqSubMarketData = Allocate<ReqSubMarketDataField>();
	memcpy(reqPackage->ReqSubMarketData, reqSubMarketData, sizeof(ReqSubMarketDataField));
	TrunsferGbkToUtf8(reqPackage->ReqSubMarketData->ExchangeID);
	TrunsferGbkToUtf8(reqPackage->ReqSubMarketData->InstrumentID);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int MdApiImpl::ReqUnSubMarketData(ReqUnSubMarketDataField* reqUnSubMarketData, int requestID)
{
	ReqUnSubMarketDataPackage* reqPackage = ReqUnSubMarketDataPackage::Allocate();
	reqPackage->Prepare(m_SessionID, false, requestID);
	reqPackage->ReqUnSubMarketData = Allocate<ReqUnSubMarketDataField>();
	memcpy(reqPackage->ReqUnSubMarketData, reqUnSubMarketData, sizeof(ReqUnSubMarketDataField));
	TrunsferGbkToUtf8(reqPackage->ReqUnSubMarketData->ExchangeID);
	TrunsferGbkToUtf8(reqPackage->ReqUnSubMarketData->InstrumentID);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}

