// 本文件由 ../Templates/Cpp/Api/GbkApiImpl.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdApiImpl.h"
#include "Error.h"
#include "Packages.h"
#include <Spark/Network/Protocol/Items.h>
#include <Spark/Serialization/Encode/Encode.h>

using namespace Spark;
using namespace Spark::Serialization;
using namespace QuantTrading::Packages;

namespace QuantTrading
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
	switch (package->Head.PackageId)
	{
	case RspMdUserLoginPackage::PackageId:
	{
		auto rspMdUserLogin = static_cast<RspMdUserLoginPackage*>(package)->RspMdUserLogin;
		if (rspMdUserLogin != nullptr)
		{
			TrunsferUtf8ToGbk(rspMdUserLogin->UserId);
			TrunsferUtf8ToGbk(rspMdUserLogin->LoginDate);
			TrunsferUtf8ToGbk(rspMdUserLogin->LoginTime);
		}
		auto rspInfo = static_cast<RspMdUserLoginPackage*>(package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		mdSpi_->OnRspMdUserLogin(rspMdUserLogin, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspMdUserLogoutPackage::PackageId:
	{
		auto rspMdUserLogout = static_cast<RspMdUserLogoutPackage*>(package)->RspMdUserLogout;
		if (rspMdUserLogout != nullptr)
		{
			TrunsferUtf8ToGbk(rspMdUserLogout->UserId);
		}
		auto rspInfo = static_cast<RspMdUserLogoutPackage*>(package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		mdSpi_->OnRspMdUserLogout(rspMdUserLogout, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspSubMarketDataPackage::PackageId:
	{
		auto rspSubMarketData = static_cast<RspSubMarketDataPackage*>(package)->RspSubMarketData;
		if (rspSubMarketData != nullptr)
		{
			TrunsferUtf8ToGbk(rspSubMarketData->ExchangeId);
			TrunsferUtf8ToGbk(rspSubMarketData->InstrumentId);
		}
		auto rspInfo = static_cast<RspSubMarketDataPackage*>(package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		mdSpi_->OnRspSubMarketData(rspSubMarketData, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RspUnSubMarketDataPackage::PackageId:
	{
		auto rspUnSubMarketData = static_cast<RspUnSubMarketDataPackage*>(package)->RspUnSubMarketData;
		if (rspUnSubMarketData != nullptr)
		{
			TrunsferUtf8ToGbk(rspUnSubMarketData->ExchangeId);
			TrunsferUtf8ToGbk(rspUnSubMarketData->InstrumentId);
		}
		auto rspInfo = static_cast<RspUnSubMarketDataPackage*>(package)->RspInfo;
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		mdSpi_->OnRspUnSubMarketData(rspUnSubMarketData, rspInfo, package->Head.MsgSeqNum, !package->Head.MessageChain);
		break;
	}
	case RtnDepthMarketDataPackage::PackageId:
	{
		auto depthMarketData = static_cast<RtnDepthMarketDataPackage*>(package)->DepthMarketData;
		if (depthMarketData != nullptr)
		{
			TrunsferUtf8ToGbk(depthMarketData->TradingDay);
			TrunsferUtf8ToGbk(depthMarketData->ExchangeId);
			TrunsferUtf8ToGbk(depthMarketData->InstrumentId);
		}
		mdSpi_->OnRtnDepthMarketData(depthMarketData);
		break;
	}
	case RtnBarMarketDataPackage::PackageId:
	{
		auto barMarketData = static_cast<RtnBarMarketDataPackage*>(package)->BarMarketData;
		if (barMarketData != nullptr)
		{
			TrunsferUtf8ToGbk(barMarketData->TradingDay);
			TrunsferUtf8ToGbk(barMarketData->ExchangeId);
			TrunsferUtf8ToGbk(barMarketData->InstrumentId);
		}
		mdSpi_->OnRtnBarMarketData(barMarketData);
		break;
	}
	default:
		break;
	}
	package->Deallocate();
}


int MdApiImpl::ReqMdUserLogin(const ReqMdUserLoginField* reqMdUserLogin, int requestId)
{
	ReqMdUserLoginPackage* reqPackage = ReqMdUserLoginPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqMdUserLogin = Allocate<ReqMdUserLoginField>();
	memcpy(reqPackage->ReqMdUserLogin, reqMdUserLogin, sizeof(ReqMdUserLoginField));
	TrunsferGbkToUtf8(reqPackage->ReqMdUserLogin->UserId);
	TrunsferGbkToUtf8(reqPackage->ReqMdUserLogin->Password);
	
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int MdApiImpl::ReqMdUserLogout(const ReqMdUserLogoutField* reqMdUserLogout, int requestId)
{
	ReqMdUserLogoutPackage* reqPackage = ReqMdUserLogoutPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqMdUserLogout = Allocate<ReqMdUserLogoutField>();
	memcpy(reqPackage->ReqMdUserLogout, reqMdUserLogout, sizeof(ReqMdUserLogoutField));
	TrunsferGbkToUtf8(reqPackage->ReqMdUserLogout->UserId);
	
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int MdApiImpl::ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestId)
{
	ReqSubMarketDataPackage* reqPackage = ReqSubMarketDataPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqSubMarketData = Allocate<ReqSubMarketDataField>();
	memcpy(reqPackage->ReqSubMarketData, reqSubMarketData, sizeof(ReqSubMarketDataField));
	TrunsferGbkToUtf8(reqPackage->ReqSubMarketData->ExchangeId);
	TrunsferGbkToUtf8(reqPackage->ReqSubMarketData->InstrumentId);
	
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
int MdApiImpl::ReqUnSubMarketData(const ReqUnSubMarketDataField* reqUnSubMarketData, int requestId)
{
	ReqUnSubMarketDataPackage* reqPackage = ReqUnSubMarketDataPackage::Allocate();
	reqPackage->Prepare(sessionId_, false, requestId);
	reqPackage->ReqUnSubMarketData = Allocate<ReqUnSubMarketDataField>();
	memcpy(reqPackage->ReqUnSubMarketData, reqUnSubMarketData, sizeof(ReqUnSubMarketDataField));
	TrunsferGbkToUtf8(reqPackage->ReqUnSubMarketData->ExchangeId);
	TrunsferGbkToUtf8(reqPackage->ReqUnSubMarketData->InstrumentId);
	
	
	int result = (protocol_->Send(reqPackage))? ErrorNone : ErrorNetwork;
	reqPackage->Deallocate();
	return result;
}
}
