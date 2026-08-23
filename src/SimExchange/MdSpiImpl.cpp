#include "MdSpiImpl.h"
#include "Error.h"
#include "SimExchange.h"
#include <Spark/Core/Logger/Logger.h>
#include <Spark/Core/Utility/Utility.h>
#include <Spark/Core/Utility/DoubleUtility.h>

using namespace std;
using namespace spark;
using namespace spark::core;


namespace quanttrading::simexchange
{
MdSpiImpl::MdSpiImpl(MdApi* mdApi, const std::string& mdUser, const std::string& mdPassword)
	:m_MdApi(mdApi), m_SimExchange(nullptr), m_MdUser(mdUser), m_MdPassword(mdPassword), m_RequestID(0)
{
}
void MdSpiImpl::SetSimExchange(SimExchange* simExchange)
{
	m_SimExchange = simExchange;
}
void MdSpiImpl::OnConnected()
{
	WriteLog(LogLevel::Info, "OnConnected:");
	ReqMdUserLogin();
}
void MdSpiImpl::OnDisConnected()
{
	WriteLog(LogLevel::Info, "OnDisConnected");
}

void MdSpiImpl::OnRspMdUserLogin(const RspMdUserLoginField* rspMdUserLogin, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspMdUserLogin: RequestID:%d, IsLast:%d", requestID, isLast);
	if (rspMdUserLogin != nullptr)
	{
		WriteLog(LogLevel::Info, "RspMdUserLoginField:UserID:[%s], LoginDate:[%s], LoginTime:[%s], SessionID:[%lld]",
			rspMdUserLogin->UserID, rspMdUserLogin->LoginDate, rspMdUserLogin->LoginTime, rspMdUserLogin->SessionID);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspMdUserLogin is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]", rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
	RspMdUserLoginPackage* package = RspMdUserLoginPackage::Allocate();
	package->Prepare(0, false, 0);
	package->RspMdUserLogin = Allocate<RspMdUserLoginField>();
	package->RspInfo = Allocate<RspInfoField>();
	if (rspMdUserLogin != nullptr)
	{
		memcpy(package->RspMdUserLogin, rspMdUserLogin, sizeof(RspMdUserLoginField));
	}
	if (rspInfo != nullptr)
	{
		memcpy(package->RspInfo, rspInfo, sizeof(RspInfoField));
	}
	m_SimExchange->OnMessage(package);
}
void MdSpiImpl::OnRspMdUserLogout(const RspMdUserLogoutField* rspMdUserLogout, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspMdUserLogout: RequestID:%d, IsLast:%d", requestID, isLast);
	if (rspMdUserLogout != nullptr)
	{
		WriteLog(LogLevel::Info, "RspMdUserLogoutField:UserID:[%s]",
			rspMdUserLogout->UserID);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspMdUserLogout is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
	RspMdUserLogoutPackage* package = RspMdUserLogoutPackage::Allocate();
	package->Prepare(0, false, 0);
	package->RspMdUserLogout = Allocate<RspMdUserLogoutField>();
	package->RspInfo = Allocate<RspInfoField>();
	if (rspMdUserLogout != nullptr)
	{
		memcpy(package->RspMdUserLogout, rspMdUserLogout, sizeof(RspMdUserLogoutField));
	}
	if (rspInfo != nullptr)
	{
		memcpy(package->RspInfo, rspInfo, sizeof(RspInfoField));
	}
	m_SimExchange->OnMessage(package);
}
void MdSpiImpl::OnRspSubMarketData(const RspSubMarketDataField* rspSubMarketData, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspSubMarketData: RequestID:%d, IsLast:%d", requestID, isLast);
	if (rspSubMarketData != nullptr)
	{
		WriteLog(LogLevel::Info, "RspSubMarketDataField:ExchangeID:[%s], InstrumentID:[%s]",
			rspSubMarketData->ExchangeID, rspSubMarketData->InstrumentID);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspSubMarketData is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void MdSpiImpl::OnRspUnSubMarketData(const RspUnSubMarketDataField* rspUnSubMarketData, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspUnSubMarketData: RequestID:%d, IsLast:%d", requestID, isLast);
	if (rspUnSubMarketData != nullptr)
	{
		WriteLog(LogLevel::Info, "RspUnSubMarketDataField:ExchangeID:[%s], InstrumentID:[%s]",
			rspUnSubMarketData->ExchangeID, rspUnSubMarketData->InstrumentID);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspUnSubMarketData is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void MdSpiImpl::OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData)
{
	WriteLog(LogLevel::Info, "OnRtnDepthMarketData");
	if (depthMarketData != nullptr)
	{
		WriteLog(LogLevel::Info, "DepthMarketDataField:TradingDay:[%s], ExchangeID:[%s], InstrumentID:[%s], UpdateTs:[%lld], LastPrice:[%f], PreSettlementPrice:[%f], PreClosePrice:[%f], PreOpenInterest:[%f], OpenPrice:[%f], HighestPrice:[%f], LowestPrice:[%f], ClosePrice:[%f], CurrVolume:[%lld], Volume:[%lld], CurrTurnover:[%f], Turnover:[%f], OpenInterest:[%f], SettlementPrice:[%f], UpperLimitPrice:[%f], LowerLimitPrice:[%f], AveragePrice:[%f], AskPrice1:[%f], AskPrice2:[%f], AskPrice3:[%f], AskPrice4:[%f], AskPrice5:[%f], AskPrice6:[%f], AskPrice7:[%f], AskPrice8:[%f], AskPrice9:[%f], AskPrice10:[%f], AskVolume1:[%lld], AskVolume2:[%lld], AskVolume3:[%lld], AskVolume4:[%lld], AskVolume5:[%lld], AskVolume6:[%lld], AskVolume7:[%lld], AskVolume8:[%lld], AskVolume9:[%lld], AskVolume10:[%lld], BidPrice1:[%f], BidPrice2:[%f], BidPrice3:[%f], BidPrice4:[%f], BidPrice5:[%f], BidPrice6:[%f], BidPrice7:[%f], BidPrice8:[%f], BidPrice9:[%f], BidPrice10:[%f], BidVolume1:[%lld], BidVolume2:[%lld], BidVolume3:[%lld], BidVolume4:[%lld], BidVolume5:[%lld], BidVolume6:[%lld], BidVolume7:[%lld], BidVolume8:[%lld], BidVolume9:[%lld], BidVolume10:[%lld]",
			depthMarketData->TradingDay, depthMarketData->ExchangeID, depthMarketData->InstrumentID, depthMarketData->UpdateTs, DoubleUtility::GetDoubleValue(depthMarketData->LastPrice), DoubleUtility::GetDoubleValue(depthMarketData->PreSettlementPrice), DoubleUtility::GetDoubleValue(depthMarketData->PreClosePrice), DoubleUtility::GetDoubleValue(depthMarketData->PreOpenInterest), DoubleUtility::GetDoubleValue(depthMarketData->OpenPrice), DoubleUtility::GetDoubleValue(depthMarketData->HighestPrice), DoubleUtility::GetDoubleValue(depthMarketData->LowestPrice), DoubleUtility::GetDoubleValue(depthMarketData->ClosePrice), depthMarketData->CurrVolume, depthMarketData->Volume, DoubleUtility::GetDoubleValue(depthMarketData->CurrTurnover), DoubleUtility::GetDoubleValue(depthMarketData->Turnover), DoubleUtility::GetDoubleValue(depthMarketData->OpenInterest), DoubleUtility::GetDoubleValue(depthMarketData->SettlementPrice), DoubleUtility::GetDoubleValue(depthMarketData->UpperLimitPrice), DoubleUtility::GetDoubleValue(depthMarketData->LowerLimitPrice), DoubleUtility::GetDoubleValue(depthMarketData->AveragePrice), DoubleUtility::GetDoubleValue(depthMarketData->AskPrice1), DoubleUtility::GetDoubleValue(depthMarketData->AskPrice2), DoubleUtility::GetDoubleValue(depthMarketData->AskPrice3), DoubleUtility::GetDoubleValue(depthMarketData->AskPrice4), DoubleUtility::GetDoubleValue(depthMarketData->AskPrice5), DoubleUtility::GetDoubleValue(depthMarketData->AskPrice6), DoubleUtility::GetDoubleValue(depthMarketData->AskPrice7), DoubleUtility::GetDoubleValue(depthMarketData->AskPrice8), DoubleUtility::GetDoubleValue(depthMarketData->AskPrice9), DoubleUtility::GetDoubleValue(depthMarketData->AskPrice10), depthMarketData->AskVolume1, depthMarketData->AskVolume2, depthMarketData->AskVolume3, depthMarketData->AskVolume4, depthMarketData->AskVolume5, depthMarketData->AskVolume6, depthMarketData->AskVolume7, depthMarketData->AskVolume8, depthMarketData->AskVolume9, depthMarketData->AskVolume10, DoubleUtility::GetDoubleValue(depthMarketData->BidPrice1), DoubleUtility::GetDoubleValue(depthMarketData->BidPrice2), DoubleUtility::GetDoubleValue(depthMarketData->BidPrice3), DoubleUtility::GetDoubleValue(depthMarketData->BidPrice4), DoubleUtility::GetDoubleValue(depthMarketData->BidPrice5), DoubleUtility::GetDoubleValue(depthMarketData->BidPrice6), DoubleUtility::GetDoubleValue(depthMarketData->BidPrice7), DoubleUtility::GetDoubleValue(depthMarketData->BidPrice8), DoubleUtility::GetDoubleValue(depthMarketData->BidPrice9), DoubleUtility::GetDoubleValue(depthMarketData->BidPrice10), depthMarketData->BidVolume1, depthMarketData->BidVolume2, depthMarketData->BidVolume3, depthMarketData->BidVolume4, depthMarketData->BidVolume5, depthMarketData->BidVolume6, depthMarketData->BidVolume7, depthMarketData->BidVolume8, depthMarketData->BidVolume9, depthMarketData->BidVolume10);
	}
	else
	{
		WriteLog(LogLevel::Info, "depthMarketData is nullptr");
		return;
	}

	RtnDepthMarketDataPackage* package = RtnDepthMarketDataPackage::Allocate();
	package->Prepare(0, false, 0);
	package->DepthMarketData = ::Allocate<DepthMarketDataField>();
	memcpy(package->DepthMarketData, depthMarketData, sizeof(DepthMarketDataField));
	m_SimExchange->OnMessage(package);
}
void MdSpiImpl::OnRtnBarMarketData(const BarMarketDataField* barMarketData)
{
	WriteLog(LogLevel::Info, "OnRtnBarMarketData");
	if (barMarketData != nullptr)
	{
		WriteLog(LogLevel::Info, "BarMarketDataField:TradingDay:[%s], ExchangeID:[%s], InstrumentID:[%s], BarPreces:[%d], BarPeriod:[%d], BarTime:[%lld], UpdateTs:[%lld], HighestPrice:[%f], LowestPrice:[%f], Open:[%f], High:[%f], Low:[%f], Close:[%f], CurrVolume:[%lld], Volume:[%lld], CurrTurnover:[%f], Turnover:[%f], OpenInterest:[%f]",
			barMarketData->TradingDay, barMarketData->ExchangeID, barMarketData->InstrumentID, (int)barMarketData->BarPreces, barMarketData->BarPeriod, barMarketData->BarTime, barMarketData->UpdateTs, DoubleUtility::GetDoubleValue(barMarketData->HighestPrice), DoubleUtility::GetDoubleValue(barMarketData->LowestPrice), DoubleUtility::GetDoubleValue(barMarketData->Open), DoubleUtility::GetDoubleValue(barMarketData->High), DoubleUtility::GetDoubleValue(barMarketData->Low), DoubleUtility::GetDoubleValue(barMarketData->Close), barMarketData->CurrVolume, barMarketData->Volume, DoubleUtility::GetDoubleValue(barMarketData->CurrTurnover), DoubleUtility::GetDoubleValue(barMarketData->Turnover), DoubleUtility::GetDoubleValue(barMarketData->OpenInterest));
	}
	else
	{
		WriteLog(LogLevel::Info, "barMarketData is nullptr");
		return;
	}

	RtnBarMarketDataPackage* package = RtnBarMarketDataPackage::Allocate();
	package->Prepare(0, false, 0);
	package->BarMarketData = ::Allocate<BarMarketDataField>();
	memcpy(package->BarMarketData, barMarketData, sizeof(BarMarketDataField));
	m_SimExchange->OnMessage(package);
}

void MdSpiImpl::ReqMdUserLogin()
{
	ReqMdUserLoginField reqMdUserLogin;
	memset(&reqMdUserLogin, 0, sizeof(ReqMdUserLoginField));
    Utility::Strcpy(reqMdUserLogin.UserID, m_MdUser.c_str());
    Utility::Strcpy(reqMdUserLogin.Password, m_MdPassword.c_str());
	m_MdApi->ReqMdUserLogin(&reqMdUserLogin, ++m_RequestID);
}
void MdSpiImpl::ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData)
{
	m_MdApi->ReqSubMarketData(reqSubMarketData, ++m_RequestID);
}
}
