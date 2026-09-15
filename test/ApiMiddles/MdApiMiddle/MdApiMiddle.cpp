// 本文件由 ../Templates/Cpp/ApiTest/ApiMiddle.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdApiMiddle.h"
#include <Spark/Core/Logger/Logger.h>

using namespace spark::core;


namespace quanttrading
{
MdApiMiddle* MdApiMiddle::CreateMdApiMiddle()
{
	WriteLog(LogLevel::Info, "CreateMdApi");
	
	auto api = MdApi::CreateMdApi();
	auto apiMiddle = new MdApiMiddle();
	apiMiddle->mdApi = api;
	
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
	return mdApi->Init();
}
void MdApiMiddle::Join()
{
	WriteLog(LogLevel::Info, "Join");
	mdApi->Join();
}
void MdApiMiddle::Release()
{
	WriteLog(LogLevel::Info, "Release");
	mdApi->Release();
}
void MdApiMiddle::RegisterFront(const char* address)
{
	WriteLog(LogLevel::Info, "RegisterFront:%s", address);
	mdApi->RegisterFront(address);
}
void MdApiMiddle::RegisterSpi(MdSpi* pSpi)
{
	WriteLog(LogLevel::Info, "RegisterSpi");
	mdApi->RegisterSpi(pSpi);
}

int MdApiMiddle::ReqMdUserLogin(const ReqMdUserLoginField* reqMdUserLogin, int requestID)
{
	WriteLog(LogLevel::Info, "ReqMdUserLogin: RequestID:%d", requestID);
	if (reqMdUserLogin != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqMdUserLoginField:UserID:[%s]",
			reqMdUserLogin->UserID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqMdUserLogin is nullptr");
	}
	return mdApi->ReqMdUserLogin(reqMdUserLogin, requestID);
}
int MdApiMiddle::ReqMdUserLogout(const ReqMdUserLogoutField* reqMdUserLogout, int requestID)
{
	WriteLog(LogLevel::Info, "ReqMdUserLogout: RequestID:%d", requestID);
	if (reqMdUserLogout != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqMdUserLogoutField:UserID:[%s]",
			reqMdUserLogout->UserID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqMdUserLogout is nullptr");
	}
	return mdApi->ReqMdUserLogout(reqMdUserLogout, requestID);
}
int MdApiMiddle::ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestID)
{
	WriteLog(LogLevel::Info, "ReqSubMarketData: RequestID:%d", requestID);
	if (reqSubMarketData != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqSubMarketDataField:ExchangeID:[%s], InstrumentID:[%s], BarPreces:[%d], BarPeriod:[%d]",
			reqSubMarketData->ExchangeID, reqSubMarketData->InstrumentID, static_cast<int>(reqSubMarketData->BarPreces), reqSubMarketData->BarPeriod);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqSubMarketData is nullptr");
	}
	return mdApi->ReqSubMarketData(reqSubMarketData, requestID);
}
int MdApiMiddle::ReqUnSubMarketData(const ReqUnSubMarketDataField* reqUnSubMarketData, int requestID)
{
	WriteLog(LogLevel::Info, "ReqUnSubMarketData: RequestID:%d", requestID);
	if (reqUnSubMarketData != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqUnSubMarketDataField:ExchangeID:[%s], InstrumentID:[%s]",
			reqUnSubMarketData->ExchangeID, reqUnSubMarketData->InstrumentID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqUnSubMarketData is nullptr");
	}
	return mdApi->ReqUnSubMarketData(reqUnSubMarketData, requestID);
}
}
