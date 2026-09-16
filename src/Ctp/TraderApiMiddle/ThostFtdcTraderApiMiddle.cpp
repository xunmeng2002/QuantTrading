// 本文件由 ../Templates/Cpp/LibTest/CtpWrapper/ApiMiddle.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "ThostFtdcTraderApiMiddle.h"
#include "StructLogFunc.h"
#include <Spark/Core/Logger/Logger.h>

using namespace Spark::Core;


CThostFtdcTraderApi *CThostFtdcTraderApiMiddle::CreateFtdcTraderApi(const char *pszFlowPath)
{
	WriteLog(LogLevel::Info, "CreateFtdcTraderApi: pszFlowPath[%s]", pszFlowPath);
	
	auto api = CThostFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath);
	auto apiMiddle = new CThostFtdcTraderApiMiddle();
	apiMiddle->traderApi_ = api;
	
	return apiMiddle;
}

const char *CThostFtdcTraderApiMiddle::GetApiVersion()
{
	WriteLog(LogLevel::Info, "GetApiVersion:");
	
	return CThostFtdcTraderApi::GetApiVersion();
}

void CThostFtdcTraderApiMiddle::Release()
{
	WriteLog(LogLevel::Info, "Release:");

	return traderApi_->Release();
}
void CThostFtdcTraderApiMiddle::Init()
{
	WriteLog(LogLevel::Info, "Init:");

	return traderApi_->Init();
}
int CThostFtdcTraderApiMiddle::Join()
{
	WriteLog(LogLevel::Info, "Join:");

	return traderApi_->Join();
}
const char * CThostFtdcTraderApiMiddle::GetTradingDay()
{
	WriteLog(LogLevel::Info, "GetTradingDay:");

	return traderApi_->GetTradingDay();
}
void CThostFtdcTraderApiMiddle::GetFrontInfo(CThostFtdcFrontInfoField *pFrontInfo)
{
	WriteLog(LogLevel::Info, "GetFrontInfo:");
	WriteFrontInfo(pFrontInfo);

	return traderApi_->GetFrontInfo(pFrontInfo);
}
void CThostFtdcTraderApiMiddle::RegisterFront(char * pszFrontAddress)
{
	WriteLog(LogLevel::Info, "RegisterFront: pszFrontAddress[%s]", pszFrontAddress);

	return traderApi_->RegisterFront(pszFrontAddress);
}
void CThostFtdcTraderApiMiddle::RegisterNameServer(char * pszNsAddress)
{
	WriteLog(LogLevel::Info, "RegisterNameServer: pszNsAddress[%s]", pszNsAddress);

	return traderApi_->RegisterNameServer(pszNsAddress);
}
void CThostFtdcTraderApiMiddle::RegisterFensUserInfo(CThostFtdcFensUserInfoField *pFensUserInfo)
{
	WriteLog(LogLevel::Info, "RegisterFensUserInfo:");
	WriteFensUserInfo(pFensUserInfo);

	return traderApi_->RegisterFensUserInfo(pFensUserInfo);
}
void CThostFtdcTraderApiMiddle::RegisterSpi(CThostFtdcTraderSpi *pTraderSpi)
{
	WriteLog(LogLevel::Info, "RegisterSpi:");

	return traderApi_->RegisterSpi(pTraderSpi);
}
void CThostFtdcTraderApiMiddle::SubscribePrivateTopic(THOST_TE_RESUME_TYPE nResumeType)
{
	WriteLog(LogLevel::Info, "SubscribePrivateTopic: nResumeType[%d]", nResumeType);

	return traderApi_->SubscribePrivateTopic(nResumeType);
}
void CThostFtdcTraderApiMiddle::SubscribePublicTopic(THOST_TE_RESUME_TYPE nResumeType)
{
	WriteLog(LogLevel::Info, "SubscribePublicTopic: nResumeType[%d]", nResumeType);

	return traderApi_->SubscribePublicTopic(nResumeType);
}
int CThostFtdcTraderApiMiddle::ReqAuthenticate(CThostFtdcReqAuthenticateField *pReqAuthenticate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqAuthenticate: nRequestID[%d]", nRequestID);
	WriteReqAuthenticate(pReqAuthenticate);

	return traderApi_->ReqAuthenticate(pReqAuthenticate, nRequestID);
}
int CThostFtdcTraderApiMiddle::RegisterUserSystemInfo(CThostFtdcUserSystemInfoField *pUserSystemInfo)
{
	WriteLog(LogLevel::Info, "RegisterUserSystemInfo:");
	WriteUserSystemInfo(pUserSystemInfo);

	return traderApi_->RegisterUserSystemInfo(pUserSystemInfo);
}
int CThostFtdcTraderApiMiddle::SubmitUserSystemInfo(CThostFtdcUserSystemInfoField *pUserSystemInfo)
{
	WriteLog(LogLevel::Info, "SubmitUserSystemInfo:");
	WriteUserSystemInfo(pUserSystemInfo);

	return traderApi_->SubmitUserSystemInfo(pUserSystemInfo);
}
int CThostFtdcTraderApiMiddle::ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLogin, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqUserLogin: nRequestID[%d]", nRequestID);
	WriteReqUserLogin(pReqUserLogin);

	return traderApi_->ReqUserLogin(pReqUserLogin, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqUserLogout: nRequestID[%d]", nRequestID);
	WriteUserLogout(pUserLogout);

	return traderApi_->ReqUserLogout(pUserLogout, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqUserPasswordUpdate: nRequestID[%d]", nRequestID);
	WriteUserPasswordUpdate(pUserPasswordUpdate);

	return traderApi_->ReqUserPasswordUpdate(pUserPasswordUpdate, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqTradingAccountPasswordUpdate: nRequestID[%d]", nRequestID);
	WriteTradingAccountPasswordUpdate(pTradingAccountPasswordUpdate);

	return traderApi_->ReqTradingAccountPasswordUpdate(pTradingAccountPasswordUpdate, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqUserAuthMethod(CThostFtdcReqUserAuthMethodField *pReqUserAuthMethod, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqUserAuthMethod: nRequestID[%d]", nRequestID);
	WriteReqUserAuthMethod(pReqUserAuthMethod);

	return traderApi_->ReqUserAuthMethod(pReqUserAuthMethod, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqGenUserCaptcha(CThostFtdcReqGenUserCaptchaField *pReqGenUserCaptcha, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqGenUserCaptcha: nRequestID[%d]", nRequestID);
	WriteReqGenUserCaptcha(pReqGenUserCaptcha);

	return traderApi_->ReqGenUserCaptcha(pReqGenUserCaptcha, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqGenUserText(CThostFtdcReqGenUserTextField *pReqGenUserText, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqGenUserText: nRequestID[%d]", nRequestID);
	WriteReqGenUserText(pReqGenUserText);

	return traderApi_->ReqGenUserText(pReqGenUserText, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqUserLoginWithCaptcha(CThostFtdcReqUserLoginWithCaptchaField *pReqUserLoginWithCaptcha, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqUserLoginWithCaptcha: nRequestID[%d]", nRequestID);
	WriteReqUserLoginWithCaptcha(pReqUserLoginWithCaptcha);

	return traderApi_->ReqUserLoginWithCaptcha(pReqUserLoginWithCaptcha, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqUserLoginWithText(CThostFtdcReqUserLoginWithTextField *pReqUserLoginWithText, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqUserLoginWithText: nRequestID[%d]", nRequestID);
	WriteReqUserLoginWithText(pReqUserLoginWithText);

	return traderApi_->ReqUserLoginWithText(pReqUserLoginWithText, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqUserLoginWithOTP(CThostFtdcReqUserLoginWithOTPField *pReqUserLoginWithOTP, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqUserLoginWithOTP: nRequestID[%d]", nRequestID);
	WriteReqUserLoginWithOTP(pReqUserLoginWithOTP);

	return traderApi_->ReqUserLoginWithOTP(pReqUserLoginWithOTP, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqOrderInsert: nRequestID[%d]", nRequestID);
	WriteInputOrder(pInputOrder);

	return traderApi_->ReqOrderInsert(pInputOrder, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqParkedOrderInsert: nRequestID[%d]", nRequestID);
	WriteParkedOrder(pParkedOrder);

	return traderApi_->ReqParkedOrderInsert(pParkedOrder, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqParkedOrderAction: nRequestID[%d]", nRequestID);
	WriteParkedOrderAction(pParkedOrderAction);

	return traderApi_->ReqParkedOrderAction(pParkedOrderAction, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqOrderAction: nRequestID[%d]", nRequestID);
	WriteInputOrderAction(pInputOrderAction);

	return traderApi_->ReqOrderAction(pInputOrderAction, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryMaxOrderVolume(CThostFtdcQryMaxOrderVolumeField *pQryMaxOrderVolume, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryMaxOrderVolume: nRequestID[%d]", nRequestID);
	WriteQryMaxOrderVolume(pQryMaxOrderVolume);

	return traderApi_->ReqQryMaxOrderVolume(pQryMaxOrderVolume, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqSettlementInfoConfirm: nRequestID[%d]", nRequestID);
	WriteSettlementInfoConfirm(pSettlementInfoConfirm);

	return traderApi_->ReqSettlementInfoConfirm(pSettlementInfoConfirm, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqRemoveParkedOrder: nRequestID[%d]", nRequestID);
	WriteRemoveParkedOrder(pRemoveParkedOrder);

	return traderApi_->ReqRemoveParkedOrder(pRemoveParkedOrder, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqRemoveParkedOrderAction: nRequestID[%d]", nRequestID);
	WriteRemoveParkedOrderAction(pRemoveParkedOrderAction);

	return traderApi_->ReqRemoveParkedOrderAction(pRemoveParkedOrderAction, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqExecOrderInsert: nRequestID[%d]", nRequestID);
	WriteInputExecOrder(pInputExecOrder);

	return traderApi_->ReqExecOrderInsert(pInputExecOrder, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqExecOrderAction: nRequestID[%d]", nRequestID);
	WriteInputExecOrderAction(pInputExecOrderAction);

	return traderApi_->ReqExecOrderAction(pInputExecOrderAction, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqForQuoteInsert: nRequestID[%d]", nRequestID);
	WriteInputForQuote(pInputForQuote);

	return traderApi_->ReqForQuoteInsert(pInputForQuote, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQuoteInsert: nRequestID[%d]", nRequestID);
	WriteInputQuote(pInputQuote);

	return traderApi_->ReqQuoteInsert(pInputQuote, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQuoteAction: nRequestID[%d]", nRequestID);
	WriteInputQuoteAction(pInputQuoteAction);

	return traderApi_->ReqQuoteAction(pInputQuoteAction, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqBatchOrderAction: nRequestID[%d]", nRequestID);
	WriteInputBatchOrderAction(pInputBatchOrderAction);

	return traderApi_->ReqBatchOrderAction(pInputBatchOrderAction, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqOptionSelfCloseInsert: nRequestID[%d]", nRequestID);
	WriteInputOptionSelfClose(pInputOptionSelfClose);

	return traderApi_->ReqOptionSelfCloseInsert(pInputOptionSelfClose, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqOptionSelfCloseAction: nRequestID[%d]", nRequestID);
	WriteInputOptionSelfCloseAction(pInputOptionSelfCloseAction);

	return traderApi_->ReqOptionSelfCloseAction(pInputOptionSelfCloseAction, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqCombActionInsert: nRequestID[%d]", nRequestID);
	WriteInputCombAction(pInputCombAction);

	return traderApi_->ReqCombActionInsert(pInputCombAction, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryOrder(CThostFtdcQryOrderField *pQryOrder, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryOrder: nRequestID[%d]", nRequestID);
	WriteQryOrder(pQryOrder);

	return traderApi_->ReqQryOrder(pQryOrder, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryTrade(CThostFtdcQryTradeField *pQryTrade, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryTrade: nRequestID[%d]", nRequestID);
	WriteQryTrade(pQryTrade);

	return traderApi_->ReqQryTrade(pQryTrade, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorPosition: nRequestID[%d]", nRequestID);
	WriteQryInvestorPosition(pQryInvestorPosition);

	return traderApi_->ReqQryInvestorPosition(pQryInvestorPosition, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryTradingAccount: nRequestID[%d]", nRequestID);
	WriteQryTradingAccount(pQryTradingAccount);

	return traderApi_->ReqQryTradingAccount(pQryTradingAccount, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestor(CThostFtdcQryInvestorField *pQryInvestor, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestor: nRequestID[%d]", nRequestID);
	WriteQryInvestor(pQryInvestor);

	return traderApi_->ReqQryInvestor(pQryInvestor, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryTradingCode(CThostFtdcQryTradingCodeField *pQryTradingCode, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryTradingCode: nRequestID[%d]", nRequestID);
	WriteQryTradingCode(pQryTradingCode);

	return traderApi_->ReqQryTradingCode(pQryTradingCode, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInstrumentMarginRate(CThostFtdcQryInstrumentMarginRateField *pQryInstrumentMarginRate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInstrumentMarginRate: nRequestID[%d]", nRequestID);
	WriteQryInstrumentMarginRate(pQryInstrumentMarginRate);

	return traderApi_->ReqQryInstrumentMarginRate(pQryInstrumentMarginRate, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInstrumentCommissionRate(CThostFtdcQryInstrumentCommissionRateField *pQryInstrumentCommissionRate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInstrumentCommissionRate: nRequestID[%d]", nRequestID);
	WriteQryInstrumentCommissionRate(pQryInstrumentCommissionRate);

	return traderApi_->ReqQryInstrumentCommissionRate(pQryInstrumentCommissionRate, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryExchange(CThostFtdcQryExchangeField *pQryExchange, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryExchange: nRequestID[%d]", nRequestID);
	WriteQryExchange(pQryExchange);

	return traderApi_->ReqQryExchange(pQryExchange, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryProduct(CThostFtdcQryProductField *pQryProduct, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryProduct: nRequestID[%d]", nRequestID);
	WriteQryProduct(pQryProduct);

	return traderApi_->ReqQryProduct(pQryProduct, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInstrument: nRequestID[%d]", nRequestID);
	WriteQryInstrument(pQryInstrument);

	return traderApi_->ReqQryInstrument(pQryInstrument, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryDepthMarketData(CThostFtdcQryDepthMarketDataField *pQryDepthMarketData, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryDepthMarketData: nRequestID[%d]", nRequestID);
	WriteQryDepthMarketData(pQryDepthMarketData);

	return traderApi_->ReqQryDepthMarketData(pQryDepthMarketData, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryTraderOffer(CThostFtdcQryTraderOfferField *pQryTraderOffer, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryTraderOffer: nRequestID[%d]", nRequestID);
	WriteQryTraderOffer(pQryTraderOffer);

	return traderApi_->ReqQryTraderOffer(pQryTraderOffer, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySettlementInfo(CThostFtdcQrySettlementInfoField *pQrySettlementInfo, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySettlementInfo: nRequestID[%d]", nRequestID);
	WriteQrySettlementInfo(pQrySettlementInfo);

	return traderApi_->ReqQrySettlementInfo(pQrySettlementInfo, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryTransferBank(CThostFtdcQryTransferBankField *pQryTransferBank, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryTransferBank: nRequestID[%d]", nRequestID);
	WriteQryTransferBank(pQryTransferBank);

	return traderApi_->ReqQryTransferBank(pQryTransferBank, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorPositionDetail(CThostFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorPositionDetail: nRequestID[%d]", nRequestID);
	WriteQryInvestorPositionDetail(pQryInvestorPositionDetail);

	return traderApi_->ReqQryInvestorPositionDetail(pQryInvestorPositionDetail, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryNotice(CThostFtdcQryNoticeField *pQryNotice, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryNotice: nRequestID[%d]", nRequestID);
	WriteQryNotice(pQryNotice);

	return traderApi_->ReqQryNotice(pQryNotice, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySettlementInfoConfirm(CThostFtdcQrySettlementInfoConfirmField *pQrySettlementInfoConfirm, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySettlementInfoConfirm: nRequestID[%d]", nRequestID);
	WriteQrySettlementInfoConfirm(pQrySettlementInfoConfirm);

	return traderApi_->ReqQrySettlementInfoConfirm(pQrySettlementInfoConfirm, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorPositionCombineDetail(CThostFtdcQryInvestorPositionCombineDetailField *pQryInvestorPositionCombineDetail, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorPositionCombineDetail: nRequestID[%d]", nRequestID);
	WriteQryInvestorPositionCombineDetail(pQryInvestorPositionCombineDetail);

	return traderApi_->ReqQryInvestorPositionCombineDetail(pQryInvestorPositionCombineDetail, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryCFMMCTradingAccountKey(CThostFtdcQryCFMMCTradingAccountKeyField *pQryCFMMCTradingAccountKey, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryCFMMCTradingAccountKey: nRequestID[%d]", nRequestID);
	WriteQryCFMMCTradingAccountKey(pQryCFMMCTradingAccountKey);

	return traderApi_->ReqQryCFMMCTradingAccountKey(pQryCFMMCTradingAccountKey, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryEWarrantOffset(CThostFtdcQryEWarrantOffsetField *pQryEWarrantOffset, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryEWarrantOffset: nRequestID[%d]", nRequestID);
	WriteQryEWarrantOffset(pQryEWarrantOffset);

	return traderApi_->ReqQryEWarrantOffset(pQryEWarrantOffset, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorProductGroupMargin(CThostFtdcQryInvestorProductGroupMarginField *pQryInvestorProductGroupMargin, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorProductGroupMargin: nRequestID[%d]", nRequestID);
	WriteQryInvestorProductGroupMargin(pQryInvestorProductGroupMargin);

	return traderApi_->ReqQryInvestorProductGroupMargin(pQryInvestorProductGroupMargin, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryExchangeMarginRate(CThostFtdcQryExchangeMarginRateField *pQryExchangeMarginRate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryExchangeMarginRate: nRequestID[%d]", nRequestID);
	WriteQryExchangeMarginRate(pQryExchangeMarginRate);

	return traderApi_->ReqQryExchangeMarginRate(pQryExchangeMarginRate, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryExchangeMarginRateAdjust(CThostFtdcQryExchangeMarginRateAdjustField *pQryExchangeMarginRateAdjust, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryExchangeMarginRateAdjust: nRequestID[%d]", nRequestID);
	WriteQryExchangeMarginRateAdjust(pQryExchangeMarginRateAdjust);

	return traderApi_->ReqQryExchangeMarginRateAdjust(pQryExchangeMarginRateAdjust, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryExchangeRate(CThostFtdcQryExchangeRateField *pQryExchangeRate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryExchangeRate: nRequestID[%d]", nRequestID);
	WriteQryExchangeRate(pQryExchangeRate);

	return traderApi_->ReqQryExchangeRate(pQryExchangeRate, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySecAgentACIDMap(CThostFtdcQrySecAgentACIDMapField *pQrySecAgentACIDMap, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySecAgentACIDMap: nRequestID[%d]", nRequestID);
	WriteQrySecAgentACIDMap(pQrySecAgentACIDMap);

	return traderApi_->ReqQrySecAgentACIDMap(pQrySecAgentACIDMap, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryProductExchRate(CThostFtdcQryProductExchRateField *pQryProductExchRate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryProductExchRate: nRequestID[%d]", nRequestID);
	WriteQryProductExchRate(pQryProductExchRate);

	return traderApi_->ReqQryProductExchRate(pQryProductExchRate, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryProductGroup(CThostFtdcQryProductGroupField *pQryProductGroup, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryProductGroup: nRequestID[%d]", nRequestID);
	WriteQryProductGroup(pQryProductGroup);

	return traderApi_->ReqQryProductGroup(pQryProductGroup, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryMMInstrumentCommissionRate(CThostFtdcQryMMInstrumentCommissionRateField *pQryMMInstrumentCommissionRate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryMMInstrumentCommissionRate: nRequestID[%d]", nRequestID);
	WriteQryMMInstrumentCommissionRate(pQryMMInstrumentCommissionRate);

	return traderApi_->ReqQryMMInstrumentCommissionRate(pQryMMInstrumentCommissionRate, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryMMOptionInstrCommRate(CThostFtdcQryMMOptionInstrCommRateField *pQryMMOptionInstrCommRate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryMMOptionInstrCommRate: nRequestID[%d]", nRequestID);
	WriteQryMMOptionInstrCommRate(pQryMMOptionInstrCommRate);

	return traderApi_->ReqQryMMOptionInstrCommRate(pQryMMOptionInstrCommRate, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInstrumentOrderCommRate(CThostFtdcQryInstrumentOrderCommRateField *pQryInstrumentOrderCommRate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInstrumentOrderCommRate: nRequestID[%d]", nRequestID);
	WriteQryInstrumentOrderCommRate(pQryInstrumentOrderCommRate);

	return traderApi_->ReqQryInstrumentOrderCommRate(pQryInstrumentOrderCommRate, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySecAgentTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySecAgentTradingAccount: nRequestID[%d]", nRequestID);
	WriteQryTradingAccount(pQryTradingAccount);

	return traderApi_->ReqQrySecAgentTradingAccount(pQryTradingAccount, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySecAgentCheckMode(CThostFtdcQrySecAgentCheckModeField *pQrySecAgentCheckMode, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySecAgentCheckMode: nRequestID[%d]", nRequestID);
	WriteQrySecAgentCheckMode(pQrySecAgentCheckMode);

	return traderApi_->ReqQrySecAgentCheckMode(pQrySecAgentCheckMode, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySecAgentTradeInfo(CThostFtdcQrySecAgentTradeInfoField *pQrySecAgentTradeInfo, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySecAgentTradeInfo: nRequestID[%d]", nRequestID);
	WriteQrySecAgentTradeInfo(pQrySecAgentTradeInfo);

	return traderApi_->ReqQrySecAgentTradeInfo(pQrySecAgentTradeInfo, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryOptionInstrTradeCost(CThostFtdcQryOptionInstrTradeCostField *pQryOptionInstrTradeCost, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryOptionInstrTradeCost: nRequestID[%d]", nRequestID);
	WriteQryOptionInstrTradeCost(pQryOptionInstrTradeCost);

	return traderApi_->ReqQryOptionInstrTradeCost(pQryOptionInstrTradeCost, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryOptionInstrCommRate(CThostFtdcQryOptionInstrCommRateField *pQryOptionInstrCommRate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryOptionInstrCommRate: nRequestID[%d]", nRequestID);
	WriteQryOptionInstrCommRate(pQryOptionInstrCommRate);

	return traderApi_->ReqQryOptionInstrCommRate(pQryOptionInstrCommRate, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryExecOrder(CThostFtdcQryExecOrderField *pQryExecOrder, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryExecOrder: nRequestID[%d]", nRequestID);
	WriteQryExecOrder(pQryExecOrder);

	return traderApi_->ReqQryExecOrder(pQryExecOrder, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryForQuote(CThostFtdcQryForQuoteField *pQryForQuote, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryForQuote: nRequestID[%d]", nRequestID);
	WriteQryForQuote(pQryForQuote);

	return traderApi_->ReqQryForQuote(pQryForQuote, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryQuote(CThostFtdcQryQuoteField *pQryQuote, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryQuote: nRequestID[%d]", nRequestID);
	WriteQryQuote(pQryQuote);

	return traderApi_->ReqQryQuote(pQryQuote, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryOptionSelfClose(CThostFtdcQryOptionSelfCloseField *pQryOptionSelfClose, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryOptionSelfClose: nRequestID[%d]", nRequestID);
	WriteQryOptionSelfClose(pQryOptionSelfClose);

	return traderApi_->ReqQryOptionSelfClose(pQryOptionSelfClose, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestUnit(CThostFtdcQryInvestUnitField *pQryInvestUnit, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestUnit: nRequestID[%d]", nRequestID);
	WriteQryInvestUnit(pQryInvestUnit);

	return traderApi_->ReqQryInvestUnit(pQryInvestUnit, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryCombInstrumentGuard(CThostFtdcQryCombInstrumentGuardField *pQryCombInstrumentGuard, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryCombInstrumentGuard: nRequestID[%d]", nRequestID);
	WriteQryCombInstrumentGuard(pQryCombInstrumentGuard);

	return traderApi_->ReqQryCombInstrumentGuard(pQryCombInstrumentGuard, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryCombAction(CThostFtdcQryCombActionField *pQryCombAction, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryCombAction: nRequestID[%d]", nRequestID);
	WriteQryCombAction(pQryCombAction);

	return traderApi_->ReqQryCombAction(pQryCombAction, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryTransferSerial(CThostFtdcQryTransferSerialField *pQryTransferSerial, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryTransferSerial: nRequestID[%d]", nRequestID);
	WriteQryTransferSerial(pQryTransferSerial);

	return traderApi_->ReqQryTransferSerial(pQryTransferSerial, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryAccountregister(CThostFtdcQryAccountregisterField *pQryAccountregister, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryAccountregister: nRequestID[%d]", nRequestID);
	WriteQryAccountregister(pQryAccountregister);

	return traderApi_->ReqQryAccountregister(pQryAccountregister, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryContractBank(CThostFtdcQryContractBankField *pQryContractBank, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryContractBank: nRequestID[%d]", nRequestID);
	WriteQryContractBank(pQryContractBank);

	return traderApi_->ReqQryContractBank(pQryContractBank, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryParkedOrder(CThostFtdcQryParkedOrderField *pQryParkedOrder, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryParkedOrder: nRequestID[%d]", nRequestID);
	WriteQryParkedOrder(pQryParkedOrder);

	return traderApi_->ReqQryParkedOrder(pQryParkedOrder, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryParkedOrderAction(CThostFtdcQryParkedOrderActionField *pQryParkedOrderAction, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryParkedOrderAction: nRequestID[%d]", nRequestID);
	WriteQryParkedOrderAction(pQryParkedOrderAction);

	return traderApi_->ReqQryParkedOrderAction(pQryParkedOrderAction, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryTradingNotice(CThostFtdcQryTradingNoticeField *pQryTradingNotice, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryTradingNotice: nRequestID[%d]", nRequestID);
	WriteQryTradingNotice(pQryTradingNotice);

	return traderApi_->ReqQryTradingNotice(pQryTradingNotice, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryBrokerTradingParams(CThostFtdcQryBrokerTradingParamsField *pQryBrokerTradingParams, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryBrokerTradingParams: nRequestID[%d]", nRequestID);
	WriteQryBrokerTradingParams(pQryBrokerTradingParams);

	return traderApi_->ReqQryBrokerTradingParams(pQryBrokerTradingParams, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryBrokerTradingAlgos(CThostFtdcQryBrokerTradingAlgosField *pQryBrokerTradingAlgos, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryBrokerTradingAlgos: nRequestID[%d]", nRequestID);
	WriteQryBrokerTradingAlgos(pQryBrokerTradingAlgos);

	return traderApi_->ReqQryBrokerTradingAlgos(pQryBrokerTradingAlgos, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQueryCFMMCTradingAccountToken: nRequestID[%d]", nRequestID);
	WriteQueryCFMMCTradingAccountToken(pQueryCFMMCTradingAccountToken);

	return traderApi_->ReqQueryCFMMCTradingAccountToken(pQueryCFMMCTradingAccountToken, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqFromBankToFutureByFuture: nRequestID[%d]", nRequestID);
	WriteReqTransfer(pReqTransfer);

	return traderApi_->ReqFromBankToFutureByFuture(pReqTransfer, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqFromFutureToBankByFuture: nRequestID[%d]", nRequestID);
	WriteReqTransfer(pReqTransfer);

	return traderApi_->ReqFromFutureToBankByFuture(pReqTransfer, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQueryBankAccountMoneyByFuture: nRequestID[%d]", nRequestID);
	WriteReqQueryAccount(pReqQueryAccount);

	return traderApi_->ReqQueryBankAccountMoneyByFuture(pReqQueryAccount, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryClassifiedInstrument(CThostFtdcQryClassifiedInstrumentField *pQryClassifiedInstrument, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryClassifiedInstrument: nRequestID[%d]", nRequestID);
	WriteQryClassifiedInstrument(pQryClassifiedInstrument);

	return traderApi_->ReqQryClassifiedInstrument(pQryClassifiedInstrument, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryCombPromotionParam(CThostFtdcQryCombPromotionParamField *pQryCombPromotionParam, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryCombPromotionParam: nRequestID[%d]", nRequestID);
	WriteQryCombPromotionParam(pQryCombPromotionParam);

	return traderApi_->ReqQryCombPromotionParam(pQryCombPromotionParam, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryRiskSettleInvstPosition(CThostFtdcQryRiskSettleInvstPositionField *pQryRiskSettleInvstPosition, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryRiskSettleInvstPosition: nRequestID[%d]", nRequestID);
	WriteQryRiskSettleInvstPosition(pQryRiskSettleInvstPosition);

	return traderApi_->ReqQryRiskSettleInvstPosition(pQryRiskSettleInvstPosition, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryRiskSettleProductStatus(CThostFtdcQryRiskSettleProductStatusField *pQryRiskSettleProductStatus, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryRiskSettleProductStatus: nRequestID[%d]", nRequestID);
	WriteQryRiskSettleProductStatus(pQryRiskSettleProductStatus);

	return traderApi_->ReqQryRiskSettleProductStatus(pQryRiskSettleProductStatus, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySPBMFutureParameter(CThostFtdcQrySPBMFutureParameterField *pQrySPBMFutureParameter, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySPBMFutureParameter: nRequestID[%d]", nRequestID);
	WriteQrySPBMFutureParameter(pQrySPBMFutureParameter);

	return traderApi_->ReqQrySPBMFutureParameter(pQrySPBMFutureParameter, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySPBMOptionParameter(CThostFtdcQrySPBMOptionParameterField *pQrySPBMOptionParameter, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySPBMOptionParameter: nRequestID[%d]", nRequestID);
	WriteQrySPBMOptionParameter(pQrySPBMOptionParameter);

	return traderApi_->ReqQrySPBMOptionParameter(pQrySPBMOptionParameter, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySPBMIntraParameter(CThostFtdcQrySPBMIntraParameterField *pQrySPBMIntraParameter, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySPBMIntraParameter: nRequestID[%d]", nRequestID);
	WriteQrySPBMIntraParameter(pQrySPBMIntraParameter);

	return traderApi_->ReqQrySPBMIntraParameter(pQrySPBMIntraParameter, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySPBMInterParameter(CThostFtdcQrySPBMInterParameterField *pQrySPBMInterParameter, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySPBMInterParameter: nRequestID[%d]", nRequestID);
	WriteQrySPBMInterParameter(pQrySPBMInterParameter);

	return traderApi_->ReqQrySPBMInterParameter(pQrySPBMInterParameter, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySPBMPortfDefinition(CThostFtdcQrySPBMPortfDefinitionField *pQrySPBMPortfDefinition, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySPBMPortfDefinition: nRequestID[%d]", nRequestID);
	WriteQrySPBMPortfDefinition(pQrySPBMPortfDefinition);

	return traderApi_->ReqQrySPBMPortfDefinition(pQrySPBMPortfDefinition, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySPBMInvestorPortfDef(CThostFtdcQrySPBMInvestorPortfDefField *pQrySPBMInvestorPortfDef, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySPBMInvestorPortfDef: nRequestID[%d]", nRequestID);
	WriteQrySPBMInvestorPortfDef(pQrySPBMInvestorPortfDef);

	return traderApi_->ReqQrySPBMInvestorPortfDef(pQrySPBMInvestorPortfDef, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorPortfMarginRatio(CThostFtdcQryInvestorPortfMarginRatioField *pQryInvestorPortfMarginRatio, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorPortfMarginRatio: nRequestID[%d]", nRequestID);
	WriteQryInvestorPortfMarginRatio(pQryInvestorPortfMarginRatio);

	return traderApi_->ReqQryInvestorPortfMarginRatio(pQryInvestorPortfMarginRatio, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorProdSPBMDetail(CThostFtdcQryInvestorProdSPBMDetailField *pQryInvestorProdSPBMDetail, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorProdSPBMDetail: nRequestID[%d]", nRequestID);
	WriteQryInvestorProdSPBMDetail(pQryInvestorProdSPBMDetail);

	return traderApi_->ReqQryInvestorProdSPBMDetail(pQryInvestorProdSPBMDetail, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorCommoditySPMMMargin(CThostFtdcQryInvestorCommoditySPMMMarginField *pQryInvestorCommoditySPMMMargin, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorCommoditySPMMMargin: nRequestID[%d]", nRequestID);
	WriteQryInvestorCommoditySPMMMargin(pQryInvestorCommoditySPMMMargin);

	return traderApi_->ReqQryInvestorCommoditySPMMMargin(pQryInvestorCommoditySPMMMargin, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorCommodityGroupSPMMMargin(CThostFtdcQryInvestorCommodityGroupSPMMMarginField *pQryInvestorCommodityGroupSPMMMargin, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorCommodityGroupSPMMMargin: nRequestID[%d]", nRequestID);
	WriteQryInvestorCommodityGroupSPMMMargin(pQryInvestorCommodityGroupSPMMMargin);

	return traderApi_->ReqQryInvestorCommodityGroupSPMMMargin(pQryInvestorCommodityGroupSPMMMargin, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySPMMInstParam(CThostFtdcQrySPMMInstParamField *pQrySPMMInstParam, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySPMMInstParam: nRequestID[%d]", nRequestID);
	WriteQrySPMMInstParam(pQrySPMMInstParam);

	return traderApi_->ReqQrySPMMInstParam(pQrySPMMInstParam, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySPMMProductParam(CThostFtdcQrySPMMProductParamField *pQrySPMMProductParam, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySPMMProductParam: nRequestID[%d]", nRequestID);
	WriteQrySPMMProductParam(pQrySPMMProductParam);

	return traderApi_->ReqQrySPMMProductParam(pQrySPMMProductParam, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySPBMAddOnInterParameter(CThostFtdcQrySPBMAddOnInterParameterField *pQrySPBMAddOnInterParameter, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySPBMAddOnInterParameter: nRequestID[%d]", nRequestID);
	WriteQrySPBMAddOnInterParameter(pQrySPBMAddOnInterParameter);

	return traderApi_->ReqQrySPBMAddOnInterParameter(pQrySPBMAddOnInterParameter, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryRCAMSCombProductInfo(CThostFtdcQryRCAMSCombProductInfoField *pQryRCAMSCombProductInfo, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryRCAMSCombProductInfo: nRequestID[%d]", nRequestID);
	WriteQryRCAMSCombProductInfo(pQryRCAMSCombProductInfo);

	return traderApi_->ReqQryRCAMSCombProductInfo(pQryRCAMSCombProductInfo, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryRCAMSInstrParameter(CThostFtdcQryRCAMSInstrParameterField *pQryRCAMSInstrParameter, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryRCAMSInstrParameter: nRequestID[%d]", nRequestID);
	WriteQryRCAMSInstrParameter(pQryRCAMSInstrParameter);

	return traderApi_->ReqQryRCAMSInstrParameter(pQryRCAMSInstrParameter, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryRCAMSIntraParameter(CThostFtdcQryRCAMSIntraParameterField *pQryRCAMSIntraParameter, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryRCAMSIntraParameter: nRequestID[%d]", nRequestID);
	WriteQryRCAMSIntraParameter(pQryRCAMSIntraParameter);

	return traderApi_->ReqQryRCAMSIntraParameter(pQryRCAMSIntraParameter, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryRCAMSInterParameter(CThostFtdcQryRCAMSInterParameterField *pQryRCAMSInterParameter, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryRCAMSInterParameter: nRequestID[%d]", nRequestID);
	WriteQryRCAMSInterParameter(pQryRCAMSInterParameter);

	return traderApi_->ReqQryRCAMSInterParameter(pQryRCAMSInterParameter, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryRCAMSShortOptAdjustParam(CThostFtdcQryRCAMSShortOptAdjustParamField *pQryRCAMSShortOptAdjustParam, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryRCAMSShortOptAdjustParam: nRequestID[%d]", nRequestID);
	WriteQryRCAMSShortOptAdjustParam(pQryRCAMSShortOptAdjustParam);

	return traderApi_->ReqQryRCAMSShortOptAdjustParam(pQryRCAMSShortOptAdjustParam, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryRCAMSInvestorCombPosition(CThostFtdcQryRCAMSInvestorCombPositionField *pQryRCAMSInvestorCombPosition, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryRCAMSInvestorCombPosition: nRequestID[%d]", nRequestID);
	WriteQryRCAMSInvestorCombPosition(pQryRCAMSInvestorCombPosition);

	return traderApi_->ReqQryRCAMSInvestorCombPosition(pQryRCAMSInvestorCombPosition, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorProdRCAMSMargin(CThostFtdcQryInvestorProdRCAMSMarginField *pQryInvestorProdRCAMSMargin, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorProdRCAMSMargin: nRequestID[%d]", nRequestID);
	WriteQryInvestorProdRCAMSMargin(pQryInvestorProdRCAMSMargin);

	return traderApi_->ReqQryInvestorProdRCAMSMargin(pQryInvestorProdRCAMSMargin, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryRULEInstrParameter(CThostFtdcQryRULEInstrParameterField *pQryRULEInstrParameter, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryRULEInstrParameter: nRequestID[%d]", nRequestID);
	WriteQryRULEInstrParameter(pQryRULEInstrParameter);

	return traderApi_->ReqQryRULEInstrParameter(pQryRULEInstrParameter, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryRULEIntraParameter(CThostFtdcQryRULEIntraParameterField *pQryRULEIntraParameter, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryRULEIntraParameter: nRequestID[%d]", nRequestID);
	WriteQryRULEIntraParameter(pQryRULEIntraParameter);

	return traderApi_->ReqQryRULEIntraParameter(pQryRULEIntraParameter, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryRULEInterParameter(CThostFtdcQryRULEInterParameterField *pQryRULEInterParameter, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryRULEInterParameter: nRequestID[%d]", nRequestID);
	WriteQryRULEInterParameter(pQryRULEInterParameter);

	return traderApi_->ReqQryRULEInterParameter(pQryRULEInterParameter, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorProdRULEMargin(CThostFtdcQryInvestorProdRULEMarginField *pQryInvestorProdRULEMargin, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorProdRULEMargin: nRequestID[%d]", nRequestID);
	WriteQryInvestorProdRULEMargin(pQryInvestorProdRULEMargin);

	return traderApi_->ReqQryInvestorProdRULEMargin(pQryInvestorProdRULEMargin, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorPortfSetting(CThostFtdcQryInvestorPortfSettingField *pQryInvestorPortfSetting, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorPortfSetting: nRequestID[%d]", nRequestID);
	WriteQryInvestorPortfSetting(pQryInvestorPortfSetting);

	return traderApi_->ReqQryInvestorPortfSetting(pQryInvestorPortfSetting, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorInfoCommRec(CThostFtdcQryInvestorInfoCommRecField *pQryInvestorInfoCommRec, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorInfoCommRec: nRequestID[%d]", nRequestID);
	WriteQryInvestorInfoCommRec(pQryInvestorInfoCommRec);

	return traderApi_->ReqQryInvestorInfoCommRec(pQryInvestorInfoCommRec, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryCombLeg(CThostFtdcQryCombLegField *pQryCombLeg, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryCombLeg: nRequestID[%d]", nRequestID);
	WriteQryCombLeg(pQryCombLeg);

	return traderApi_->ReqQryCombLeg(pQryCombLeg, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqOffsetSetting(CThostFtdcInputOffsetSettingField *pInputOffsetSetting, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqOffsetSetting: nRequestID[%d]", nRequestID);
	WriteInputOffsetSetting(pInputOffsetSetting);

	return traderApi_->ReqOffsetSetting(pInputOffsetSetting, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqCancelOffsetSetting(CThostFtdcInputOffsetSettingField *pInputOffsetSetting, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqCancelOffsetSetting: nRequestID[%d]", nRequestID);
	WriteInputOffsetSetting(pInputOffsetSetting);

	return traderApi_->ReqCancelOffsetSetting(pInputOffsetSetting, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryOffsetSetting(CThostFtdcQryOffsetSettingField *pQryOffsetSetting, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryOffsetSetting: nRequestID[%d]", nRequestID);
	WriteQryOffsetSetting(pQryOffsetSetting);

	return traderApi_->ReqQryOffsetSetting(pQryOffsetSetting, nRequestID);
}
