// 本文件由 ../Templates/Cpp/Api/GbkApiImpl.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdApiImpl.h"
#include "Error.h"
#include "Packages.h"
#include <Spark/Network/Protocol/Items.h>
#include <Spark/Serialization/Encode/Encode.h>

using namespace spark;
using namespace spark::serialization;
using namespace quanttrading::packages;

namespace quanttrading
{
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
		auto rspMdUserLogin = static_cast<RspMdUserLoginPackage*>(package)->RspMdUserLogin;
		if (rspMdUserLogin != nullptr)
		{
			TrunsferUtf8ToGbk(rspMdUserLogin->UserID);
			TrunsferUtf8ToGbk(rspMdUserLogin->LoginDate);
			TrunsferUtf8ToGbk(rspMdUserLogin->LoginTime);
		}
		auto rspInfo = static_cast<RspMdUserLoginPackage*>(package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		mdSpi->OnRspMdUserLogin(rspMdUserLogin, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspMdUserLogoutPackage::PackageID:
	{
		auto rspMdUserLogout = static_cast<RspMdUserLogoutPackage*>(package)->RspMdUserLogout;
		if (rspMdUserLogout != nullptr)
		{
			TrunsferUtf8ToGbk(rspMdUserLogout->UserID);
		}
		auto rspInfo = static_cast<RspMdUserLogoutPackage*>(package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		mdSpi->OnRspMdUserLogout(rspMdUserLogout, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspSubMarketDataPackage::PackageID:
	{
		auto rspSubMarketData = static_cast<RspSubMarketDataPackage*>(package)->RspSubMarketData;
		if (rspSubMarketData != nullptr)
		{
			TrunsferUtf8ToGbk(rspSubMarketData->ExchangeID);
			TrunsferUtf8ToGbk(rspSubMarketData->InstrumentID);
		}
		auto rspInfo = static_cast<RspSubMarketDataPackage*>(package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		mdSpi->OnRspSubMarketData(rspSubMarketData, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspUnSubMarketDataPackage::PackageID:
	{
		auto rspUnSubMarketData = static_cast<RspUnSubMarketDataPackage*>(package)->RspUnSubMarketData;
		if (rspUnSubMarketData != nullptr)
		{
			TrunsferUtf8ToGbk(rspUnSubMarketData->ExchangeID);
			TrunsferUtf8ToGbk(rspUnSubMarketData->InstrumentID);
		}
		auto rspInfo = static_cast<RspUnSubMarketDataPackage*>(package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		mdSpi->OnRspUnSubMarketData(rspUnSubMarketData, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RtnDepthMarketDataPackage::PackageID:
	{
		auto depthMarketData = static_cast<RtnDepthMarketDataPackage*>(package)->DepthMarketData;
		if (depthMarketData != nullptr)
		{
			TrunsferUtf8ToGbk(depthMarketData->TradingDay);
			TrunsferUtf8ToGbk(depthMarketData->ExchangeID);
			TrunsferUtf8ToGbk(depthMarketData->InstrumentID);
		}
		mdSpi->OnRtnDepthMarketData(depthMarketData);
		break;
	}
	case RtnBarMarketDataPackage::PackageID:
	{
		auto barMarketData = static_cast<RtnBarMarketDataPackage*>(package)->BarMarketData;
		if (barMarketData != nullptr)
		{
			TrunsferUtf8ToGbk(barMarketData->TradingDay);
			TrunsferUtf8ToGbk(barMarketData->ExchangeID);
			TrunsferUtf8ToGbk(barMarketData->InstrumentID);
		}
		mdSpi->OnRtnBarMarketData(barMarketData);
		break;
	}
	default:
		break;
	}
	package->Deallocate();
}


int MdApiImpl::ReqMdUserLogin(const ReqMdUserLoginField* reqMdUserLogin, int requestID)
{
	ReqMdUserLoginPackage* reqPackage = ReqMdUserLoginPackage::Allocate();
	reqPackage->Prepare(sessionID, false, requestID);
	reqPackage->ReqMdUserLogin = Allocate<ReqMdUserLoginField>();
	memcpy(reqPackage->ReqMdUserLogin, reqMdUserLogin, sizeof(ReqMdUserLoginField));
	TrunsferGbkToUtf8(reqPackage->ReqMdUserLogin->UserID);
	TrunsferGbkToUtf8(reqPackage->ReqMdUserLogin->Password);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int MdApiImpl::ReqMdUserLogout(const ReqMdUserLogoutField* reqMdUserLogout, int requestID)
{
	ReqMdUserLogoutPackage* reqPackage = ReqMdUserLogoutPackage::Allocate();
	reqPackage->Prepare(sessionID, false, requestID);
	reqPackage->ReqMdUserLogout = Allocate<ReqMdUserLogoutField>();
	memcpy(reqPackage->ReqMdUserLogout, reqMdUserLogout, sizeof(ReqMdUserLogoutField));
	TrunsferGbkToUtf8(reqPackage->ReqMdUserLogout->UserID);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int MdApiImpl::ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestID)
{
	ReqSubMarketDataPackage* reqPackage = ReqSubMarketDataPackage::Allocate();
	reqPackage->Prepare(sessionID, false, requestID);
	reqPackage->ReqSubMarketData = Allocate<ReqSubMarketDataField>();
	memcpy(reqPackage->ReqSubMarketData, reqSubMarketData, sizeof(ReqSubMarketDataField));
	TrunsferGbkToUtf8(reqPackage->ReqSubMarketData->ExchangeID);
	TrunsferGbkToUtf8(reqPackage->ReqSubMarketData->InstrumentID);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int MdApiImpl::ReqUnSubMarketData(const ReqUnSubMarketDataField* reqUnSubMarketData, int requestID)
{
	ReqUnSubMarketDataPackage* reqPackage = ReqUnSubMarketDataPackage::Allocate();
	reqPackage->Prepare(sessionID, false, requestID);
	reqPackage->ReqUnSubMarketData = Allocate<ReqUnSubMarketDataField>();
	memcpy(reqPackage->ReqUnSubMarketData, reqUnSubMarketData, sizeof(ReqUnSubMarketDataField));
	TrunsferGbkToUtf8(reqPackage->ReqUnSubMarketData->ExchangeID);
	TrunsferGbkToUtf8(reqPackage->ReqUnSubMarketData->InstrumentID);
	
	
	int result = (m_Protocol->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
}
