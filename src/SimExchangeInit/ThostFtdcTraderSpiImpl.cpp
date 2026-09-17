#include "ThostFtdcTraderSpiImpl.h"
#include "MdbStructs.h"
#include <Spark/Core/Logger/Logger.h>
#include <Spark/Core/Utility/Utility.h>
#include <Spark/Serialization/Encode/Encode.h>
#include <string.h>

using namespace std;
using namespace QuantTrading;
using namespace Spark::Core;
using namespace Spark::Serialization;


namespace QuantTrading::SimExchangeInit
{
CThostFtdcTraderSpiImpl::CThostFtdcTraderSpiImpl(CThostFtdcTraderApi* traderApi, QuantTrading::Mdb* mdb)
	:traderApi_(traderApi), mdb_(mdb), requestId_(0), accountInfo_(nullptr), qryFinished_(false)
{
	exchanges_ = new vector<Exchange*>();
	products_ = new vector< Product*>();
	instruments_ = new vector<Instrument*>();
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
	if (newPassword_.length() > 0)
	{
		ReqUserPasswordUpdate();
	}
	else
	{
		ReqUserLogin();
	}
}
void CThostFtdcTraderSpiImpl::OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	CThostFtdcTraderSpiMiddle::OnRspUserLogin(pRspUserLogin, pRspInfo, nRequestID, bIsLast);
	//if (pRspInfo != nullptr && pRspInfo->ErrorId == 141)	//PWD_OUT_OF_DATE
	//{
	//	ReqUserPasswordUpdate();
	//}
	ReqQryExchange();
}
void CThostFtdcTraderSpiImpl::OnRspQryExchange(CThostFtdcExchangeField* pExchange, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	CThostFtdcTraderSpiMiddle::OnRspQryExchange(pExchange, pRspInfo, nRequestID, bIsLast);
	Exchange* exchange = Exchange::Allocate();
	Utility::Strcpy(exchange->ExchangeId, pExchange->ExchangeID);
    Utility::Strcpy(exchange->ExchangeName, GbkToUtf8(pExchange->ExchangeName).c_str());
	exchanges_->push_back(exchange);
	if (bIsLast)
	{
		mdb_->Exchange->BatchInsert(exchanges_);
		ReqQryProduct();
	}
}
void CThostFtdcTraderSpiImpl::OnRspQryProduct(CThostFtdcProductField* pProduct, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	CThostFtdcTraderSpiMiddle::OnRspQryProduct(pProduct, pRspInfo, nRequestID, bIsLast);
	Product* product = Product::Allocate();
    Utility::Strcpy(product->ExchangeId, pProduct->ExchangeID);
    Utility::Strcpy(product->ProductId, pProduct->ProductID);
    Utility::Strcpy(product->ProductName, GbkToUtf8(pProduct->ProductName).c_str());
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
	products_->push_back(product);
	if (bIsLast)
	{
		mdb_->Product->BatchInsert(products_);
		ReqQryInstrument();
	}
}
void CThostFtdcTraderSpiImpl::OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
{
	CThostFtdcTraderSpiMiddle::OnRspQryInstrument(pInstrument, pRspInfo, nRequestID, bIsLast);
	Instrument* instrument = Instrument::Allocate();
    Utility::Strcpy(instrument->ExchangeId, pInstrument->ExchangeID);
    Utility::Strcpy(instrument->InstrumentId, pInstrument->InstrumentID);
    Utility::Strcpy(instrument->ExchangeInstId, pInstrument->ExchangeInstID);
    Utility::Strcpy(instrument->InstrumentName, GbkToUtf8(pInstrument->InstrumentName).c_str());
    Utility::Strcpy(instrument->ProductId, pInstrument->ProductID);
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
	instruments_->push_back(instrument);
	if (bIsLast)
	{
		mdb_->Instrument->BatchInsert(instruments_);
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
        qryFinished_ = true;
	}
}

void CThostFtdcTraderSpiImpl::SetAccountInfo(AccountInfo* accountInfo)
{
	accountInfo_ = accountInfo;
}
void CThostFtdcTraderSpiImpl::SetNewPassword(const std::string& newPassword)
{
	newPassword_ = newPassword;
}

void CThostFtdcTraderSpiImpl::ReqAuthenticate()
{
	CThostFtdcReqAuthenticateField authenticate;
	::memset(&authenticate, 0, sizeof(authenticate));
	Utility::Strcpy(authenticate.BrokerID, accountInfo_->BrokerId);
	Utility::Strcpy(authenticate.UserID, accountInfo_->InvestorId);
	Utility::Strcpy(authenticate.UserProductInfo, accountInfo_->UserProductInfo);
	Utility::Strcpy(authenticate.AuthCode, accountInfo_->AuthCode);
	Utility::Strcpy(authenticate.AppID, accountInfo_->AppId);

	int ret = traderApi_->ReqAuthenticate(&authenticate, requestId_++);
	WriteLog(LogLevel::Info, "ReqAuthenticate: ret[%d]", ret);
}
void CThostFtdcTraderSpiImpl::ReqUserLogin()
{
	CThostFtdcReqUserLoginField userLogin;
	::memset(&userLogin, 0, sizeof(userLogin));
	Utility::Strcpy(userLogin.TradingDay, "");
	Utility::Strcpy(userLogin.BrokerID, accountInfo_->BrokerId);
	Utility::Strcpy(userLogin.UserID, accountInfo_->InvestorId);
	Utility::Strcpy(userLogin.Password, accountInfo_->Password);
	Utility::Strcpy(userLogin.UserProductInfo, accountInfo_->UserProductInfo);

	int ret = traderApi_->ReqUserLogin(&userLogin, requestId_++);
	WriteLog(LogLevel::Info, "ReqUserLogin: ret[%d]", ret);
}
void CThostFtdcTraderSpiImpl::ReqUserPasswordUpdate()
{
	CThostFtdcUserPasswordUpdateField userPasswordUpdate;
	::memset(&userPasswordUpdate, 0, sizeof(userPasswordUpdate));
	Utility::Strcpy(userPasswordUpdate.BrokerID, accountInfo_->BrokerId);
	Utility::Strcpy(userPasswordUpdate.UserID, accountInfo_->InvestorId);
	Utility::Strcpy(userPasswordUpdate.OldPassword, accountInfo_->Password);
	Utility::Strcpy(userPasswordUpdate.NewPassword, newPassword_.c_str());

	int ret = traderApi_->ReqUserPasswordUpdate(&userPasswordUpdate, requestId_++);
	WriteLog(LogLevel::Info, "ReqUserPasswordUpdate: ret[%d]", ret);
}
void CThostFtdcTraderSpiImpl::ReqQryExchange()
{
	CThostFtdcQryExchangeField qryExchange;
	::memset(&qryExchange, 0, sizeof(qryExchange));
	int ret = traderApi_->ReqQryExchange(&qryExchange, requestId_++);
	WriteLog(LogLevel::Info, "ReqQryExchange: ret[%d]", ret);
}void CThostFtdcTraderSpiImpl::ReqQryProduct()
{
	CThostFtdcQryProductField qryProduct;
	::memset(&qryProduct, 0, sizeof(qryProduct));
	int ret = traderApi_->ReqQryProduct(&qryProduct, requestId_++);
	WriteLog(LogLevel::Info, "ReqQryProduct: ret[%d]", ret);
}
void CThostFtdcTraderSpiImpl::ReqQryInstrument()
{
	CThostFtdcQryInstrumentField qryInstrument;
	::memset(&qryInstrument, 0, sizeof(qryInstrument));
	int ret = traderApi_->ReqQryInstrument(&qryInstrument, requestId_++);
	WriteLog(LogLevel::Info, "ReqQryInstrument: ret[%d]", ret);
}
void CThostFtdcTraderSpiImpl::ReqQryTradingAccount()
{
	CThostFtdcQryTradingAccountField qryTradingAccount;
	::memset(&qryTradingAccount, 0, sizeof(qryTradingAccount));
	int ret = traderApi_->ReqQryTradingAccount(&qryTradingAccount, requestId_++);
	WriteLog(LogLevel::Info, "ReqQryTradingAccount: ret[%d]", ret);
}
void CThostFtdcTraderSpiImpl::ReqQryInvestorPosition()
{
	CThostFtdcQryInvestorPositionField qryInvestorPosition;
	::memset(&qryInvestorPosition, 0, sizeof(qryInvestorPosition));
	int ret = traderApi_->ReqQryInvestorPosition(&qryInvestorPosition, requestId_++);
	WriteLog(LogLevel::Info, "ReqQryInvestorPosition: ret[%d]", ret);
}
void CThostFtdcTraderSpiImpl::ReqQryOrder()
{
	CThostFtdcQryOrderField qryOrder;
	::memset(&qryOrder, 0, sizeof(qryOrder));
	int ret = traderApi_->ReqQryOrder(&qryOrder, requestId_++);
	WriteLog(LogLevel::Info, "ReqQryOrder: ret[%d]", ret);
}
void CThostFtdcTraderSpiImpl::ReqQryTrade()
{
	CThostFtdcQryTradeField qryTrade;
	::memset(&qryTrade, 0, sizeof(qryTrade));
	int ret = traderApi_->ReqQryTrade(&qryTrade, requestId_++);
	WriteLog(LogLevel::Info, "ReqQryTrade: ret[%d]", ret);
}
}
