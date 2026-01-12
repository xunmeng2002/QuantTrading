#include "ThostFtdcTraderSpiImpl.h"
#include "Logger.h"
#include "MdbStructs.h"
#include "Utility.h"
#include <string.h>

using namespace std;
using namespace mdb;

CThostFtdcTraderSpiImpl::CThostFtdcTraderSpiImpl(CThostFtdcTraderApi* traderApi, mdb::Mdb* mdb)
	:m_TraderApi(traderApi), m_Mdb(mdb), m_RequestID(0), m_AccountInfo(nullptr), m_QryFinished(false)
{
	m_Exchanges = new list<Exchange*>();
	m_Products = new list< Product*>();
	m_Instruments = new list<Instrument*>();
}
void CThostFtdcTraderSpiImpl::OnFrontConnected()
{
	CThostFtdcTraderSpiMiddle::OnFrontConnected();
	ReqAuthenticate();
}
void CThostFtdcTraderSpiImpl::OnFrontDisconnected(int nReason)
{
	CThostFtdcTraderSpiMiddle::OnFrontDisconnected(nReason);
}
void CThostFtdcTraderSpiImpl::OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	CThostFtdcTraderSpiMiddle::OnRspAuthenticate(pRspAuthenticateField, pRspInfo, nRequestID, bIsLast);
	ReqUserLogin();
}
void CThostFtdcTraderSpiImpl::OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	CThostFtdcTraderSpiMiddle::OnRspUserLogin(pRspUserLogin, pRspInfo, nRequestID, bIsLast);
	if (pRspInfo != nullptr && pRspInfo->ErrorID == 141)	//PWD_OUT_OF_DATE
	{
		ReqUserPasswordUpdate();
	}
	else
	{
		ReqQryExchange();
	}
}
void CThostFtdcTraderSpiImpl::OnRspQryExchange(CThostFtdcExchangeField* pExchange, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	CThostFtdcTraderSpiMiddle::OnRspQryExchange(pExchange, pRspInfo, nRequestID, bIsLast);
	Exchange* exchange = Exchange::Allocate();
	Strcpy(exchange->ExchangeID, pExchange->ExchangeID);
	Strcpy(exchange->ExchangeName, pExchange->ExchangeName);
	m_Exchanges->push_back(exchange);
	if (bIsLast)
	{
		m_Mdb->t_Exchange->BatchInsert(m_Exchanges);
		ReqQryProduct();
	}
}
void CThostFtdcTraderSpiImpl::OnRspQryProduct(CThostFtdcProductField* pProduct, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	CThostFtdcTraderSpiMiddle::OnRspQryProduct(pProduct, pRspInfo, nRequestID, bIsLast);
	Product* product = Product::Allocate();
	Strcpy(product->ExchangeID, pProduct->ExchangeID);
	Strcpy(product->ProductID, pProduct->ProductID);
	Strcpy(product->ProductName, pProduct->ProductName);
	switch (pProduct->ProductClass)
	{
	case THOST_FTDC_PC_Futures:
		product->ProductClass = ProductClassType::Future;
		break;
	case THOST_FTDC_PC_Options:
		product->ProductClass = ProductClassType::FutureOption;
		break;
	case THOST_FTDC_PC_Combination:
		product->ProductClass = ProductClassType::Combination;
		break;
	case THOST_FTDC_PC_Spot:
		product->ProductClass = ProductClassType::Spot;
		break;
	case THOST_FTDC_PC_EFP:
		product->ProductClass = ProductClassType::EFP;
		break;
	case THOST_FTDC_PC_SpotOption:
		product->ProductClass = ProductClassType::StockOption;
		break;
	case THOST_FTDC_PC_TAS:
		product->ProductClass = ProductClassType::Future;
		break;
	case THOST_FTDC_PC_MI:
		product->ProductClass = ProductClassType::Index;
		break;
	default:
		product->ProductClass = ProductClassType::Future;
		break;
	}
	product->VolumeMultiple = pProduct->VolumeMultiple;
	product->PriceTick = pProduct->PriceTick;
	product->MaxMarketOrderVolume = pProduct->MaxMarketOrderVolume;
	product->MinMarketOrderVolume = pProduct->MinMarketOrderVolume;
	product->MaxLimitOrderVolume = pProduct->MaxLimitOrderVolume;
	product->MinLimitOrderVolume = pProduct->MinLimitOrderVolume;
	memset(product->SessionName, 0, sizeof(product->SessionName));
	m_Products->push_back(product);
	if (bIsLast)
	{
		m_Mdb->t_Product->BatchInsert(m_Products);
		ReqQryInstrument();
	}
}
void CThostFtdcTraderSpiImpl::OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	CThostFtdcTraderSpiMiddle::OnRspQryInstrument(pInstrument, pRspInfo, nRequestID, bIsLast);
	Instrument* instrument = Instrument::Allocate();
	Strcpy(instrument->ExchangeID, pInstrument->ExchangeID);
	Strcpy(instrument->InstrumentID, pInstrument->InstrumentID);
	Strcpy(instrument->ExchangeInstID, pInstrument->ExchangeInstID);
	Strcpy(instrument->InstrumentName, pInstrument->InstrumentName);
	Strcpy(instrument->ProductID, pInstrument->ProductID);
	switch (pInstrument->ProductClass)
	{
	case THOST_FTDC_PC_Futures:
		instrument->ProductClass = ProductClassType::Future;
		break;
	case THOST_FTDC_PC_Options:
		instrument->ProductClass = ProductClassType::FutureOption;
		break;
	case THOST_FTDC_PC_Combination:
		instrument->ProductClass = ProductClassType::Combination;
		break;
	case THOST_FTDC_PC_Spot:
		instrument->ProductClass = ProductClassType::Spot;
		break;
	case THOST_FTDC_PC_EFP:
		instrument->ProductClass = ProductClassType::EFP;
		break;
	case THOST_FTDC_PC_SpotOption:
		instrument->ProductClass = ProductClassType::StockOption;
		break;
	case THOST_FTDC_PC_TAS:
		instrument->ProductClass = ProductClassType::Future;
		break;
	case THOST_FTDC_PC_MI:
		instrument->ProductClass = ProductClassType::Index;
		break;
	default:
		instrument->ProductClass = ProductClassType::Future;
		break;
	}
	
	instrument->InstrumentClass = InstrumentClassType::Normal;
	instrument->Rank = 0;
	instrument->VolumeMultiple = pInstrument->VolumeMultiple;
	instrument->PriceTick = pInstrument->PriceTick;
	instrument->MaxMarketOrderVolume = pInstrument->MaxMarketOrderVolume;
	instrument->MinMarketOrderVolume = pInstrument->MinMarketOrderVolume;
	instrument->MaxLimitOrderVolume = pInstrument->MaxLimitOrderVolume;
	instrument->MinLimitOrderVolume = pInstrument->MinLimitOrderVolume;
	memset(instrument->SessionName, 0, sizeof(instrument->SessionName));
	m_Instruments->push_back(instrument);
	if (bIsLast)
	{
		m_Mdb->t_Instrument->BatchInsert(m_Instruments);
		ReqQryTradingAccount();
	}
}
void CThostFtdcTraderSpiImpl::OnRspQryTradingAccount(CThostFtdcTradingAccountField* pTradingAccount, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	CThostFtdcTraderSpiMiddle::OnRspQryTradingAccount(pTradingAccount, pRspInfo, nRequestID, bIsLast);
	ReqQryInvestorPosition();
}
void CThostFtdcTraderSpiImpl::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField* pInvestorPosition, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	CThostFtdcTraderSpiMiddle::OnRspQryInvestorPosition(pInvestorPosition, pRspInfo, nRequestID, bIsLast);
	if (bIsLast)
	{
		ReqQryOrder();
	}
}
void CThostFtdcTraderSpiImpl::OnRspQryOrder(CThostFtdcOrderField* pOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	CThostFtdcTraderSpiMiddle::OnRspQryOrder(pOrder, pRspInfo, nRequestID, bIsLast);
	if (bIsLast)
	{
		ReqQryTrade();
	}
}
void CThostFtdcTraderSpiImpl::OnRspQryTrade(CThostFtdcTradeField* pTrade, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	CThostFtdcTraderSpiMiddle::OnRspQryTrade(pTrade, pRspInfo, nRequestID, bIsLast);
	if (bIsLast)
	{
		
	}
}

void CThostFtdcTraderSpiImpl::SetAccountInfo(AccountInfo* accountInfo)
{
	m_AccountInfo = accountInfo;
}
void CThostFtdcTraderSpiImpl::SetNewPassword(const std::string& newPassword)
{
	m_NewPassword = newPassword;
}

void CThostFtdcTraderSpiImpl::ReqAuthenticate()
{
	CThostFtdcReqAuthenticateField authenticate;
	::memset(&authenticate, 0, sizeof(authenticate));
	strcpy(authenticate.BrokerID, m_AccountInfo->BrokerID);
	strcpy(authenticate.UserID, m_AccountInfo->InvestorID);
	strcpy(authenticate.UserProductInfo, m_AccountInfo->UserProductInfo);
	strcpy(authenticate.AuthCode, m_AccountInfo->AuthCode);
	strcpy(authenticate.AppID, m_AccountInfo->AppID);

	int ret = m_TraderApi->ReqAuthenticate(&authenticate, m_RequestID++);
	WriteLog(LogLevel::Info, "ReqAuthenticate: ret[%d]", ret);
}
void CThostFtdcTraderSpiImpl::ReqUserLogin()
{
	CThostFtdcReqUserLoginField userLogin;
	::memset(&userLogin, 0, sizeof(userLogin));
	strcpy(userLogin.TradingDay, "");
	strcpy(userLogin.BrokerID, m_AccountInfo->BrokerID);
	strcpy(userLogin.UserID, m_AccountInfo->InvestorID);
	strcpy(userLogin.Password, m_AccountInfo->Password);
	strcpy(userLogin.UserProductInfo, m_AccountInfo->UserProductInfo);

	int ret = m_TraderApi->ReqUserLogin(&userLogin, m_RequestID++);
	WriteLog(LogLevel::Info, "ReqUserLogin: ret[%d]", ret);
}
void CThostFtdcTraderSpiImpl::ReqUserPasswordUpdate()
{
	CThostFtdcUserPasswordUpdateField userPasswordUpdate;
	::memset(&userPasswordUpdate, 0, sizeof(userPasswordUpdate));
	strcpy(userPasswordUpdate.BrokerID, m_AccountInfo->BrokerID);
	strcpy(userPasswordUpdate.UserID, m_AccountInfo->InvestorID);
	strcpy(userPasswordUpdate.OldPassword, m_AccountInfo->Password);
	strcpy(userPasswordUpdate.NewPassword, m_NewPassword.c_str());

	int ret = m_TraderApi->ReqUserPasswordUpdate(&userPasswordUpdate, m_RequestID++);
	WriteLog(LogLevel::Info, "ReqUserPasswordUpdate: ret[%d]", ret);
}
void CThostFtdcTraderSpiImpl::ReqQryExchange()
{
	CThostFtdcQryExchangeField qryExchange;
	::memset(&qryExchange, 0, sizeof(qryExchange));
	int ret = m_TraderApi->ReqQryExchange(&qryExchange, m_RequestID++);
	WriteLog(LogLevel::Info, "ReqQryExchange: ret[%d]", ret);
}void CThostFtdcTraderSpiImpl::ReqQryProduct()
{
	CThostFtdcQryProductField qryProduct;
	::memset(&qryProduct, 0, sizeof(qryProduct));
	int ret = m_TraderApi->ReqQryProduct(&qryProduct, m_RequestID++);
	WriteLog(LogLevel::Info, "ReqQryProduct: ret[%d]", ret);
}
void CThostFtdcTraderSpiImpl::ReqQryInstrument()
{
	CThostFtdcQryInstrumentField qryInstrument;
	::memset(&qryInstrument, 0, sizeof(qryInstrument));
	int ret = m_TraderApi->ReqQryInstrument(&qryInstrument, m_RequestID++);
	WriteLog(LogLevel::Info, "ReqQryInstrument: ret[%d]", ret);
}
void CThostFtdcTraderSpiImpl::ReqQryTradingAccount()
{
	CThostFtdcQryTradingAccountField qryTradingAccount;
	::memset(&qryTradingAccount, 0, sizeof(qryTradingAccount));
	int ret = m_TraderApi->ReqQryTradingAccount(&qryTradingAccount, m_RequestID++);
	WriteLog(LogLevel::Info, "ReqQryTradingAccount: ret[%d]", ret);
}
void CThostFtdcTraderSpiImpl::ReqQryInvestorPosition()
{
	CThostFtdcQryInvestorPositionField qryInvestorPosition;
	::memset(&qryInvestorPosition, 0, sizeof(qryInvestorPosition));
	int ret = m_TraderApi->ReqQryInvestorPosition(&qryInvestorPosition, m_RequestID++);
	WriteLog(LogLevel::Info, "ReqQryInvestorPosition: ret[%d]", ret);
}
void CThostFtdcTraderSpiImpl::ReqQryOrder()
{
	CThostFtdcQryOrderField qryOrder;
	::memset(&qryOrder, 0, sizeof(qryOrder));
	int ret = m_TraderApi->ReqQryOrder(&qryOrder, m_RequestID++);
	WriteLog(LogLevel::Info, "ReqQryOrder: ret[%d]", ret);
}
void CThostFtdcTraderSpiImpl::ReqQryTrade()
{
	CThostFtdcQryTradeField qryTrade;
	::memset(&qryTrade, 0, sizeof(qryTrade));
	int ret = m_TraderApi->ReqQryTrade(&qryTrade, m_RequestID++);
	WriteLog(LogLevel::Info, "ReqQryTrade: ret[%d]", ret);
}
