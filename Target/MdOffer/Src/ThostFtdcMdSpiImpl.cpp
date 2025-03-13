#include "ThostFtdcMdSpiImpl.h"
#include "Logger.h"
#include <string.h>


CThostFtdcMdSpiImpl::CThostFtdcMdSpiImpl(CThostFtdcMdApi* MdApi)
	:m_MdApi(MdApi), m_RequestID(0), m_AccountInfo(nullptr)
{
}
void CThostFtdcMdSpiImpl::OnFrontConnected()
{
	CThostFtdcMdSpiMiddle::OnFrontConnected();
	ReqUserLogin();
}
void CThostFtdcMdSpiImpl::OnFrontDisconnected(int nReason)
{
	CThostFtdcMdSpiMiddle::OnFrontDisconnected(nReason);
}
void CThostFtdcMdSpiImpl::OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	CThostFtdcMdSpiMiddle::OnRspUserLogin(pRspUserLogin, pRspInfo, nRequestID, bIsLast);
	ReqSubscribeMd();
}

void CThostFtdcMdSpiImpl::SetAccountInfo(AccountInfo* accountInfo)
{
	m_AccountInfo = accountInfo;
}

void CThostFtdcMdSpiImpl::ReqUserLogin()
{
	CThostFtdcReqUserLoginField userLogin;
	::memset(&userLogin, 0, sizeof(userLogin));
	strcpy(userLogin.TradingDay, "");
	strcpy(userLogin.BrokerID, m_AccountInfo->BrokerID);
	strcpy(userLogin.UserID, m_AccountInfo->InvestorID);
	strcpy(userLogin.Password, m_AccountInfo->Password);
	strcpy(userLogin.UserProductInfo, m_AccountInfo->UserProductInfo);

	int ret = m_MdApi->ReqUserLogin(&userLogin, m_RequestID++);
	WriteLog(LogLevel::Info, "ReqUserLogin: ret[%d]", ret);
}
void CThostFtdcMdSpiImpl::ReqSubscribeMd()
{
	char* instrumentID[4];
	instrumentID[0] = new char[81];
	instrumentID[1] = new char[81];
	instrumentID[2] = new char[81];
	instrumentID[3] = new char[81];
	strcpy(instrumentID[0], "rb2503");
	strcpy(instrumentID[1], "rb2506");
	strcpy(instrumentID[2], "rb2509");
	strcpy(instrumentID[3], "rb2510");

	int ret = m_MdApi->SubscribeMarketData(instrumentID, 4);
	WriteLog(LogLevel::Info, "SubscribeMarketData: ret[%d]", ret);
}
