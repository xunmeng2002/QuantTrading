// 本文件由 ../Templates/Cpp/ApiTest/ApiMiddle.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdApiMiddle.h"
#include <Spark/Core/Logger/Logger.h>

using namespace Spark::Core;


namespace QuantTrading
{
MdApiMiddle* MdApiMiddle::CreateMdApiMiddle()
{
	WriteLog(LogLevel::Info, "CreateMdApi");
	
	auto api = MdApi::CreateMdApi();
	auto apiMiddle = new MdApiMiddle();
	apiMiddle->mdApi_ = api;
	
	return apiMiddle;
}
const char* MdApiMiddle::GetApiVersion()
{
	WriteLog(LogLevel::Info, "GetApiVersion");
	return MdApi::GetApiVersion();
}
bool MdApiMiddle::Init()
{
	WriteLog(LogLevel::Info, "Init");
	return mdApi_->Init();
}
void MdApiMiddle::Join()
{
	WriteLog(LogLevel::Info, "Join");
	mdApi_->Join();
}
void MdApiMiddle::Release()
{
	WriteLog(LogLevel::Info, "Release");
	mdApi_->Release();
}
void MdApiMiddle::RegisterFront(const char* address)
{
	WriteLog(LogLevel::Info, "RegisterFront:%s", address);
	mdApi_->RegisterFront(address);
}
void MdApiMiddle::RegisterSpi(MdSpi* spi)
{
	WriteLog(LogLevel::Info, "RegisterSpi");
	mdApi_->RegisterSpi(spi);
}

int MdApiMiddle::ReqMdUserLogin(const ReqMdUserLoginField* reqMdUserLogin, int requestId)
{
	WriteLog(LogLevel::Info, "ReqMdUserLogin: RequestID:%d", requestId);
	if (reqMdUserLogin != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqMdUserLoginField:UserId:[%s]",
			reqMdUserLogin->UserId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqMdUserLogin is nullptr");
	}
	return mdApi_->ReqMdUserLogin(reqMdUserLogin, requestId);
}
int MdApiMiddle::ReqMdUserLogout(const ReqMdUserLogoutField* reqMdUserLogout, int requestId)
{
	WriteLog(LogLevel::Info, "ReqMdUserLogout: RequestID:%d", requestId);
	if (reqMdUserLogout != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqMdUserLogoutField:UserId:[%s]",
			reqMdUserLogout->UserId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqMdUserLogout is nullptr");
	}
	return mdApi_->ReqMdUserLogout(reqMdUserLogout, requestId);
}
int MdApiMiddle::ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestId)
{
	WriteLog(LogLevel::Info, "ReqSubMarketData: RequestID:%d", requestId);
	if (reqSubMarketData != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqSubMarketDataField:ExchangeId:[%s], InstrumentId:[%s], BarPreces:[%d], BarPeriod:[%d]",
			reqSubMarketData->ExchangeId, reqSubMarketData->InstrumentId, static_cast<int>(reqSubMarketData->BarPreces), reqSubMarketData->BarPeriod);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqSubMarketData is nullptr");
	}
	return mdApi_->ReqSubMarketData(reqSubMarketData, requestId);
}
int MdApiMiddle::ReqUnSubMarketData(const ReqUnSubMarketDataField* reqUnSubMarketData, int requestId)
{
	WriteLog(LogLevel::Info, "ReqUnSubMarketData: RequestID:%d", requestId);
	if (reqUnSubMarketData != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqUnSubMarketDataField:ExchangeId:[%s], InstrumentId:[%s]",
			reqUnSubMarketData->ExchangeId, reqUnSubMarketData->InstrumentId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqUnSubMarketData is nullptr");
	}
	return mdApi_->ReqUnSubMarketData(reqUnSubMarketData, requestId);
}
}
