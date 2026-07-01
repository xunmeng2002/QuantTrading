#include "InnerMdSpiImpl.h"
#include "Logger.h"
#include "Error.h"
#include "Utility.h"
#include "DoubleUtility.h"
#include "SimExchange.h"

using namespace std;

InnerMdSpiImpl::InnerMdSpiImpl(InnerMdApi* mdApi, const std::string& mdUser, const std::string& mdPassword)
	:m_MdApi(mdApi), m_SimExchange(nullptr), m_MdUser(mdUser), m_MdPassword(mdPassword), m_RequestID(0)
{
}
void InnerMdSpiImpl::SetSimExchange(SimExchange* simExchange)
{
	m_SimExchange = simExchange;
}
void InnerMdSpiImpl::OnConnected()
{
	WriteLog(LogLevel::Info, "OnConnected:");
	ReqMdUserLogin();
}
void InnerMdSpiImpl::OnDisConnected()
{
	WriteLog(LogLevel::Info, "OnDisConnected");
}

void InnerMdSpiImpl::OnRspMdUserLogin(RspMdUserLoginField* rspMdUserLogin, RspInfoField* rspInfo, int requestID, bool isLast)
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
void InnerMdSpiImpl::OnRspMdUserLogout(RspMdUserLogoutField* rspMdUserLogout, RspInfoField* rspInfo, int requestID, bool isLast)
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
void InnerMdSpiImpl::OnRspSubMarketData(RspSubMarketDataField* rspSubMarketData, RspInfoField* rspInfo, int requestID, bool isLast)
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
void InnerMdSpiImpl::OnRspUnSubMarketData(RspUnSubMarketDataField* rspUnSubMarketData, RspInfoField* rspInfo, int requestID, bool isLast)
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
void InnerMdSpiImpl::OnRtnDepthMarketData(DepthMarketDataField* depthMarketData)
{
	WriteLog(LogLevel::Info, "OnRtnDepthMarketData");
	if (depthMarketData != nullptr)
	{
		WriteLog(LogLevel::Info, "DepthMarketDataField:TradingDay:[%s], ExchangeID:[%s], InstrumentID:[%s], UpdateTs:[%lld], LastPrice:[%f], PreSettlementPrice:[%f], PreClosePrice:[%f], PreOpenInterest:[%f], OpenPrice:[%f], HighestPrice:[%f], LowestPrice:[%f], ClosePrice:[%f], CurrVolume:[%lld], Volume:[%lld], CurrTurnover:[%f], Turnover:[%f], OpenInterest:[%f], SettlementPrice:[%f], UpperLimitPrice:[%f], LowerLimitPrice:[%f], AveragePrice:[%f], AskPrice1:[%f], AskPrice2:[%f], AskPrice3:[%f], AskPrice4:[%f], AskPrice5:[%f], AskPrice6:[%f], AskPrice7:[%f], AskPrice8:[%f], AskPrice9:[%f], AskPrice10:[%f], AskVolume1:[%lld], AskVolume2:[%lld], AskVolume3:[%lld], AskVolume4:[%lld], AskVolume5:[%lld], AskVolume6:[%lld], AskVolume7:[%lld], AskVolume8:[%lld], AskVolume9:[%lld], AskVolume10:[%lld], BidPrice1:[%f], BidPrice2:[%f], BidPrice3:[%f], BidPrice4:[%f], BidPrice5:[%f], BidPrice6:[%f], BidPrice7:[%f], BidPrice8:[%f], BidPrice9:[%f], BidPrice10:[%f], BidVolume1:[%lld], BidVolume2:[%lld], BidVolume3:[%lld], BidVolume4:[%lld], BidVolume5:[%lld], BidVolume6:[%lld], BidVolume7:[%lld], BidVolume8:[%lld], BidVolume9:[%lld], BidVolume10:[%lld]",
			depthMarketData->TradingDay, depthMarketData->ExchangeID, depthMarketData->InstrumentID, depthMarketData->UpdateTs, GetDoubleValue(depthMarketData->LastPrice), GetDoubleValue(depthMarketData->PreSettlementPrice), GetDoubleValue(depthMarketData->PreClosePrice), GetDoubleValue(depthMarketData->PreOpenInterest), GetDoubleValue(depthMarketData->OpenPrice), GetDoubleValue(depthMarketData->HighestPrice), GetDoubleValue(depthMarketData->LowestPrice), GetDoubleValue(depthMarketData->ClosePrice), depthMarketData->CurrVolume, depthMarketData->Volume, GetDoubleValue(depthMarketData->CurrTurnover), GetDoubleValue(depthMarketData->Turnover), GetDoubleValue(depthMarketData->OpenInterest), GetDoubleValue(depthMarketData->SettlementPrice), GetDoubleValue(depthMarketData->UpperLimitPrice), GetDoubleValue(depthMarketData->LowerLimitPrice), GetDoubleValue(depthMarketData->AveragePrice), GetDoubleValue(depthMarketData->AskPrice1), GetDoubleValue(depthMarketData->AskPrice2), GetDoubleValue(depthMarketData->AskPrice3), GetDoubleValue(depthMarketData->AskPrice4), GetDoubleValue(depthMarketData->AskPrice5), GetDoubleValue(depthMarketData->AskPrice6), GetDoubleValue(depthMarketData->AskPrice7), GetDoubleValue(depthMarketData->AskPrice8), GetDoubleValue(depthMarketData->AskPrice9), GetDoubleValue(depthMarketData->AskPrice10), depthMarketData->AskVolume1, depthMarketData->AskVolume2, depthMarketData->AskVolume3, depthMarketData->AskVolume4, depthMarketData->AskVolume5, depthMarketData->AskVolume6, depthMarketData->AskVolume7, depthMarketData->AskVolume8, depthMarketData->AskVolume9, depthMarketData->AskVolume10, GetDoubleValue(depthMarketData->BidPrice1), GetDoubleValue(depthMarketData->BidPrice2), GetDoubleValue(depthMarketData->BidPrice3), GetDoubleValue(depthMarketData->BidPrice4), GetDoubleValue(depthMarketData->BidPrice5), GetDoubleValue(depthMarketData->BidPrice6), GetDoubleValue(depthMarketData->BidPrice7), GetDoubleValue(depthMarketData->BidPrice8), GetDoubleValue(depthMarketData->BidPrice9), GetDoubleValue(depthMarketData->BidPrice10), depthMarketData->BidVolume1, depthMarketData->BidVolume2, depthMarketData->BidVolume3, depthMarketData->BidVolume4, depthMarketData->BidVolume5, depthMarketData->BidVolume6, depthMarketData->BidVolume7, depthMarketData->BidVolume8, depthMarketData->BidVolume9, depthMarketData->BidVolume10);
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
void InnerMdSpiImpl::OnRtnBarMarketData(BarMarketDataField* barMarketData)
{
	WriteLog(LogLevel::Info, "OnRtnBarMarketData");
	if (barMarketData != nullptr)
	{
		WriteLog(LogLevel::Info, "BarMarketDataField:TradingDay:[%s], ExchangeID:[%s], InstrumentID:[%s], BarPreces:[%d], BarPeriod:[%d], BarTime:[%lld], UpdateTs:[%lld], HighestPrice:[%f], LowestPrice:[%f], Open:[%f], High:[%f], Low:[%f], Close:[%f], CurrVolume:[%lld], Volume:[%lld], CurrTurnover:[%f], Turnover:[%f], OpenInterest:[%f]",
			barMarketData->TradingDay, barMarketData->ExchangeID, barMarketData->InstrumentID, (int)barMarketData->BarPreces, barMarketData->BarPeriod, barMarketData->BarTime, barMarketData->UpdateTs, GetDoubleValue(barMarketData->HighestPrice), GetDoubleValue(barMarketData->LowestPrice), GetDoubleValue(barMarketData->Open), GetDoubleValue(barMarketData->High), GetDoubleValue(barMarketData->Low), GetDoubleValue(barMarketData->Close), barMarketData->CurrVolume, barMarketData->Volume, GetDoubleValue(barMarketData->CurrTurnover), GetDoubleValue(barMarketData->Turnover), GetDoubleValue(barMarketData->OpenInterest));
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

void InnerMdSpiImpl::ReqMdUserLogin()
{
	ReqMdUserLoginField reqMdUserLogin;
	memset(&reqMdUserLogin, 0, sizeof(ReqMdUserLoginField));
	Strcpy(reqMdUserLogin.UserID, m_MdUser.c_str());
	Strcpy(reqMdUserLogin.Password, m_MdPassword.c_str());
	m_MdApi->ReqMdUserLogin(&reqMdUserLogin, ++m_RequestID);
}
void InnerMdSpiImpl::ReqSubMarketData(ReqSubMarketDataField* reqSubMarketData)
{
	m_MdApi->ReqSubMarketData(reqSubMarketData, ++m_RequestID);
}
