#include "ThostFtdcTraderApiMiddle.h"
#include "StructLogFunc.h"
#include <Spark/Core/Logger/Logger.h>

using namespace spark::core;


CThostFtdcTraderApi *CThostFtdcTraderApiMiddle::CreateFtdcTraderApi(const char *pszFlowPath)
{
	WriteLog(LogLevel::Info, "CreateFtdcTraderApi: pszFlowPath[%s]", pszFlowPath);
	
	auto api = CThostFtdcTraderApi::CreateFtdcTraderApi(pszFlowPath);
	auto apiMiddle = new CThostFtdcTraderApiMiddle();
	apiMiddle->m_TraderApi = api;
	
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

	return m_TraderApi->Release();
}
void CThostFtdcTraderApiMiddle::Init()
{
	WriteLog(LogLevel::Info, "Init:");

	return m_TraderApi->Init();
}
int CThostFtdcTraderApiMiddle::Join()
{
	WriteLog(LogLevel::Info, "Join:");

	return m_TraderApi->Join();
}
const char * CThostFtdcTraderApiMiddle::GetTradingDay()
{
	WriteLog(LogLevel::Info, "GetTradingDay:");

	return m_TraderApi->GetTradingDay();
}
void CThostFtdcTraderApiMiddle::GetFrontInfo(CThostFtdcFrontInfoField *pFrontInfo)
{
	WriteLog(LogLevel::Info, "GetFrontInfo:");
	WriteFrontInfo(pFrontInfo);

	return m_TraderApi->GetFrontInfo(pFrontInfo);
}
void CThostFtdcTraderApiMiddle::RegisterFront(char * pszFrontAddress)
{
	WriteLog(LogLevel::Info, "RegisterFront: pszFrontAddress[%s]", pszFrontAddress);

	return m_TraderApi->RegisterFront(pszFrontAddress);
}
void CThostFtdcTraderApiMiddle::RegisterNameServer(char * pszNsAddress)
{
	WriteLog(LogLevel::Info, "RegisterNameServer: pszNsAddress[%s]", pszNsAddress);

	return m_TraderApi->RegisterNameServer(pszNsAddress);
}
void CThostFtdcTraderApiMiddle::RegisterFensUserInfo(CThostFtdcFensUserInfoField *pFensUserInfo)
{
	WriteLog(LogLevel::Info, "RegisterFensUserInfo:");
	WriteFensUserInfo(pFensUserInfo);

	return m_TraderApi->RegisterFensUserInfo(pFensUserInfo);
}
void CThostFtdcTraderApiMiddle::RegisterSpi(CThostFtdcTraderSpi *pTraderSpi)
{
	WriteLog(LogLevel::Info, "RegisterSpi:");

	return m_TraderApi->RegisterSpi(pTraderSpi);
}
void CThostFtdcTraderApiMiddle::SubscribePrivateTopic(THOST_TE_RESUME_TYPE nResumeType)
{
	WriteLog(LogLevel::Info, "SubscribePrivateTopic: nResumeType[%d]", nResumeType);

	return m_TraderApi->SubscribePrivateTopic(nResumeType);
}
void CThostFtdcTraderApiMiddle::SubscribePublicTopic(THOST_TE_RESUME_TYPE nResumeType)
{
	WriteLog(LogLevel::Info, "SubscribePublicTopic: nResumeType[%d]", nResumeType);

	return m_TraderApi->SubscribePublicTopic(nResumeType);
}
int CThostFtdcTraderApiMiddle::ReqAuthenticate(CThostFtdcReqAuthenticateField *pReqAuthenticate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqAuthenticate: nRequestID[%d]", nRequestID);
	WriteReqAuthenticate(pReqAuthenticate);

	return m_TraderApi->ReqAuthenticate(pReqAuthenticate, nRequestID);
}
int CThostFtdcTraderApiMiddle::RegisterUserSystemInfo(CThostFtdcUserSystemInfoField *pUserSystemInfo)
{
	WriteLog(LogLevel::Info, "RegisterUserSystemInfo:");
	WriteUserSystemInfo(pUserSystemInfo);

	return m_TraderApi->RegisterUserSystemInfo(pUserSystemInfo);
}
int CThostFtdcTraderApiMiddle::SubmitUserSystemInfo(CThostFtdcUserSystemInfoField *pUserSystemInfo)
{
	WriteLog(LogLevel::Info, "SubmitUserSystemInfo:");
	WriteUserSystemInfo(pUserSystemInfo);

	return m_TraderApi->SubmitUserSystemInfo(pUserSystemInfo);
}
int CThostFtdcTraderApiMiddle::ReqUserLogin(CThostFtdcReqUserLoginField *pReqUserLogin, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqUserLogin: nRequestID[%d]", nRequestID);
	WriteReqUserLogin(pReqUserLogin);

	return m_TraderApi->ReqUserLogin(pReqUserLogin, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqUserLogout(CThostFtdcUserLogoutField *pUserLogout, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqUserLogout: nRequestID[%d]", nRequestID);
	WriteUserLogout(pUserLogout);

	return m_TraderApi->ReqUserLogout(pUserLogout, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqUserPasswordUpdate: nRequestID[%d]", nRequestID);
	WriteUserPasswordUpdate(pUserPasswordUpdate);

	return m_TraderApi->ReqUserPasswordUpdate(pUserPasswordUpdate, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqTradingAccountPasswordUpdate: nRequestID[%d]", nRequestID);
	WriteTradingAccountPasswordUpdate(pTradingAccountPasswordUpdate);

	return m_TraderApi->ReqTradingAccountPasswordUpdate(pTradingAccountPasswordUpdate, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqUserAuthMethod(CThostFtdcReqUserAuthMethodField *pReqUserAuthMethod, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqUserAuthMethod: nRequestID[%d]", nRequestID);
	WriteReqUserAuthMethod(pReqUserAuthMethod);

	return m_TraderApi->ReqUserAuthMethod(pReqUserAuthMethod, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqGenUserCaptcha(CThostFtdcReqGenUserCaptchaField *pReqGenUserCaptcha, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqGenUserCaptcha: nRequestID[%d]", nRequestID);
	WriteReqGenUserCaptcha(pReqGenUserCaptcha);

	return m_TraderApi->ReqGenUserCaptcha(pReqGenUserCaptcha, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqGenUserText(CThostFtdcReqGenUserTextField *pReqGenUserText, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqGenUserText: nRequestID[%d]", nRequestID);
	WriteReqGenUserText(pReqGenUserText);

	return m_TraderApi->ReqGenUserText(pReqGenUserText, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqUserLoginWithCaptcha(CThostFtdcReqUserLoginWithCaptchaField *pReqUserLoginWithCaptcha, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqUserLoginWithCaptcha: nRequestID[%d]", nRequestID);
	WriteReqUserLoginWithCaptcha(pReqUserLoginWithCaptcha);

	return m_TraderApi->ReqUserLoginWithCaptcha(pReqUserLoginWithCaptcha, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqUserLoginWithText(CThostFtdcReqUserLoginWithTextField *pReqUserLoginWithText, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqUserLoginWithText: nRequestID[%d]", nRequestID);
	WriteReqUserLoginWithText(pReqUserLoginWithText);

	return m_TraderApi->ReqUserLoginWithText(pReqUserLoginWithText, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqUserLoginWithOTP(CThostFtdcReqUserLoginWithOTPField *pReqUserLoginWithOTP, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqUserLoginWithOTP: nRequestID[%d]", nRequestID);
	WriteReqUserLoginWithOTP(pReqUserLoginWithOTP);

	return m_TraderApi->ReqUserLoginWithOTP(pReqUserLoginWithOTP, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqOrderInsert(CThostFtdcInputOrderField *pInputOrder, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqOrderInsert: nRequestID[%d]", nRequestID);
	WriteInputOrder(pInputOrder);

	return m_TraderApi->ReqOrderInsert(pInputOrder, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqParkedOrderInsert: nRequestID[%d]", nRequestID);
	WriteParkedOrder(pParkedOrder);

	return m_TraderApi->ReqParkedOrderInsert(pParkedOrder, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqParkedOrderAction: nRequestID[%d]", nRequestID);
	WriteParkedOrderAction(pParkedOrderAction);

	return m_TraderApi->ReqParkedOrderAction(pParkedOrderAction, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqOrderAction: nRequestID[%d]", nRequestID);
	WriteInputOrderAction(pInputOrderAction);

	return m_TraderApi->ReqOrderAction(pInputOrderAction, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryMaxOrderVolume(CThostFtdcQryMaxOrderVolumeField *pQryMaxOrderVolume, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryMaxOrderVolume: nRequestID[%d]", nRequestID);
	WriteQryMaxOrderVolume(pQryMaxOrderVolume);

	return m_TraderApi->ReqQryMaxOrderVolume(pQryMaxOrderVolume, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqSettlementInfoConfirm: nRequestID[%d]", nRequestID);
	WriteSettlementInfoConfirm(pSettlementInfoConfirm);

	return m_TraderApi->ReqSettlementInfoConfirm(pSettlementInfoConfirm, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqRemoveParkedOrder: nRequestID[%d]", nRequestID);
	WriteRemoveParkedOrder(pRemoveParkedOrder);

	return m_TraderApi->ReqRemoveParkedOrder(pRemoveParkedOrder, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqRemoveParkedOrderAction: nRequestID[%d]", nRequestID);
	WriteRemoveParkedOrderAction(pRemoveParkedOrderAction);

	return m_TraderApi->ReqRemoveParkedOrderAction(pRemoveParkedOrderAction, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqExecOrderInsert: nRequestID[%d]", nRequestID);
	WriteInputExecOrder(pInputExecOrder);

	return m_TraderApi->ReqExecOrderInsert(pInputExecOrder, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqExecOrderAction: nRequestID[%d]", nRequestID);
	WriteInputExecOrderAction(pInputExecOrderAction);

	return m_TraderApi->ReqExecOrderAction(pInputExecOrderAction, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqForQuoteInsert: nRequestID[%d]", nRequestID);
	WriteInputForQuote(pInputForQuote);

	return m_TraderApi->ReqForQuoteInsert(pInputForQuote, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQuoteInsert: nRequestID[%d]", nRequestID);
	WriteInputQuote(pInputQuote);

	return m_TraderApi->ReqQuoteInsert(pInputQuote, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQuoteAction: nRequestID[%d]", nRequestID);
	WriteInputQuoteAction(pInputQuoteAction);

	return m_TraderApi->ReqQuoteAction(pInputQuoteAction, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqBatchOrderAction: nRequestID[%d]", nRequestID);
	WriteInputBatchOrderAction(pInputBatchOrderAction);

	return m_TraderApi->ReqBatchOrderAction(pInputBatchOrderAction, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqOptionSelfCloseInsert: nRequestID[%d]", nRequestID);
	WriteInputOptionSelfClose(pInputOptionSelfClose);

	return m_TraderApi->ReqOptionSelfCloseInsert(pInputOptionSelfClose, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqOptionSelfCloseAction: nRequestID[%d]", nRequestID);
	WriteInputOptionSelfCloseAction(pInputOptionSelfCloseAction);

	return m_TraderApi->ReqOptionSelfCloseAction(pInputOptionSelfCloseAction, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqCombActionInsert: nRequestID[%d]", nRequestID);
	WriteInputCombAction(pInputCombAction);

	return m_TraderApi->ReqCombActionInsert(pInputCombAction, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryOrder(CThostFtdcQryOrderField *pQryOrder, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryOrder: nRequestID[%d]", nRequestID);
	WriteQryOrder(pQryOrder);

	return m_TraderApi->ReqQryOrder(pQryOrder, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryTrade(CThostFtdcQryTradeField *pQryTrade, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryTrade: nRequestID[%d]", nRequestID);
	WriteQryTrade(pQryTrade);

	return m_TraderApi->ReqQryTrade(pQryTrade, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorPosition(CThostFtdcQryInvestorPositionField *pQryInvestorPosition, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorPosition: nRequestID[%d]", nRequestID);
	WriteQryInvestorPosition(pQryInvestorPosition);

	return m_TraderApi->ReqQryInvestorPosition(pQryInvestorPosition, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryTradingAccount: nRequestID[%d]", nRequestID);
	WriteQryTradingAccount(pQryTradingAccount);

	return m_TraderApi->ReqQryTradingAccount(pQryTradingAccount, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestor(CThostFtdcQryInvestorField *pQryInvestor, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestor: nRequestID[%d]", nRequestID);
	WriteQryInvestor(pQryInvestor);

	return m_TraderApi->ReqQryInvestor(pQryInvestor, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryTradingCode(CThostFtdcQryTradingCodeField *pQryTradingCode, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryTradingCode: nRequestID[%d]", nRequestID);
	WriteQryTradingCode(pQryTradingCode);

	return m_TraderApi->ReqQryTradingCode(pQryTradingCode, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInstrumentMarginRate(CThostFtdcQryInstrumentMarginRateField *pQryInstrumentMarginRate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInstrumentMarginRate: nRequestID[%d]", nRequestID);
	WriteQryInstrumentMarginRate(pQryInstrumentMarginRate);

	return m_TraderApi->ReqQryInstrumentMarginRate(pQryInstrumentMarginRate, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInstrumentCommissionRate(CThostFtdcQryInstrumentCommissionRateField *pQryInstrumentCommissionRate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInstrumentCommissionRate: nRequestID[%d]", nRequestID);
	WriteQryInstrumentCommissionRate(pQryInstrumentCommissionRate);

	return m_TraderApi->ReqQryInstrumentCommissionRate(pQryInstrumentCommissionRate, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryExchange(CThostFtdcQryExchangeField *pQryExchange, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryExchange: nRequestID[%d]", nRequestID);
	WriteQryExchange(pQryExchange);

	return m_TraderApi->ReqQryExchange(pQryExchange, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryProduct(CThostFtdcQryProductField *pQryProduct, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryProduct: nRequestID[%d]", nRequestID);
	WriteQryProduct(pQryProduct);

	return m_TraderApi->ReqQryProduct(pQryProduct, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInstrument(CThostFtdcQryInstrumentField *pQryInstrument, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInstrument: nRequestID[%d]", nRequestID);
	WriteQryInstrument(pQryInstrument);

	return m_TraderApi->ReqQryInstrument(pQryInstrument, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryDepthMarketData(CThostFtdcQryDepthMarketDataField *pQryDepthMarketData, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryDepthMarketData: nRequestID[%d]", nRequestID);
	WriteQryDepthMarketData(pQryDepthMarketData);

	return m_TraderApi->ReqQryDepthMarketData(pQryDepthMarketData, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryTraderOffer(CThostFtdcQryTraderOfferField *pQryTraderOffer, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryTraderOffer: nRequestID[%d]", nRequestID);
	WriteQryTraderOffer(pQryTraderOffer);

	return m_TraderApi->ReqQryTraderOffer(pQryTraderOffer, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySettlementInfo(CThostFtdcQrySettlementInfoField *pQrySettlementInfo, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySettlementInfo: nRequestID[%d]", nRequestID);
	WriteQrySettlementInfo(pQrySettlementInfo);

	return m_TraderApi->ReqQrySettlementInfo(pQrySettlementInfo, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryTransferBank(CThostFtdcQryTransferBankField *pQryTransferBank, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryTransferBank: nRequestID[%d]", nRequestID);
	WriteQryTransferBank(pQryTransferBank);

	return m_TraderApi->ReqQryTransferBank(pQryTransferBank, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorPositionDetail(CThostFtdcQryInvestorPositionDetailField *pQryInvestorPositionDetail, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorPositionDetail: nRequestID[%d]", nRequestID);
	WriteQryInvestorPositionDetail(pQryInvestorPositionDetail);

	return m_TraderApi->ReqQryInvestorPositionDetail(pQryInvestorPositionDetail, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryNotice(CThostFtdcQryNoticeField *pQryNotice, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryNotice: nRequestID[%d]", nRequestID);
	WriteQryNotice(pQryNotice);

	return m_TraderApi->ReqQryNotice(pQryNotice, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySettlementInfoConfirm(CThostFtdcQrySettlementInfoConfirmField *pQrySettlementInfoConfirm, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySettlementInfoConfirm: nRequestID[%d]", nRequestID);
	WriteQrySettlementInfoConfirm(pQrySettlementInfoConfirm);

	return m_TraderApi->ReqQrySettlementInfoConfirm(pQrySettlementInfoConfirm, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorPositionCombineDetail(CThostFtdcQryInvestorPositionCombineDetailField *pQryInvestorPositionCombineDetail, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorPositionCombineDetail: nRequestID[%d]", nRequestID);
	WriteQryInvestorPositionCombineDetail(pQryInvestorPositionCombineDetail);

	return m_TraderApi->ReqQryInvestorPositionCombineDetail(pQryInvestorPositionCombineDetail, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryCFMMCTradingAccountKey(CThostFtdcQryCFMMCTradingAccountKeyField *pQryCFMMCTradingAccountKey, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryCFMMCTradingAccountKey: nRequestID[%d]", nRequestID);
	WriteQryCFMMCTradingAccountKey(pQryCFMMCTradingAccountKey);

	return m_TraderApi->ReqQryCFMMCTradingAccountKey(pQryCFMMCTradingAccountKey, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryEWarrantOffset(CThostFtdcQryEWarrantOffsetField *pQryEWarrantOffset, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryEWarrantOffset: nRequestID[%d]", nRequestID);
	WriteQryEWarrantOffset(pQryEWarrantOffset);

	return m_TraderApi->ReqQryEWarrantOffset(pQryEWarrantOffset, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorProductGroupMargin(CThostFtdcQryInvestorProductGroupMarginField *pQryInvestorProductGroupMargin, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorProductGroupMargin: nRequestID[%d]", nRequestID);
	WriteQryInvestorProductGroupMargin(pQryInvestorProductGroupMargin);

	return m_TraderApi->ReqQryInvestorProductGroupMargin(pQryInvestorProductGroupMargin, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryExchangeMarginRate(CThostFtdcQryExchangeMarginRateField *pQryExchangeMarginRate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryExchangeMarginRate: nRequestID[%d]", nRequestID);
	WriteQryExchangeMarginRate(pQryExchangeMarginRate);

	return m_TraderApi->ReqQryExchangeMarginRate(pQryExchangeMarginRate, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryExchangeMarginRateAdjust(CThostFtdcQryExchangeMarginRateAdjustField *pQryExchangeMarginRateAdjust, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryExchangeMarginRateAdjust: nRequestID[%d]", nRequestID);
	WriteQryExchangeMarginRateAdjust(pQryExchangeMarginRateAdjust);

	return m_TraderApi->ReqQryExchangeMarginRateAdjust(pQryExchangeMarginRateAdjust, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryExchangeRate(CThostFtdcQryExchangeRateField *pQryExchangeRate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryExchangeRate: nRequestID[%d]", nRequestID);
	WriteQryExchangeRate(pQryExchangeRate);

	return m_TraderApi->ReqQryExchangeRate(pQryExchangeRate, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySecAgentACIDMap(CThostFtdcQrySecAgentACIDMapField *pQrySecAgentACIDMap, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySecAgentACIDMap: nRequestID[%d]", nRequestID);
	WriteQrySecAgentACIDMap(pQrySecAgentACIDMap);

	return m_TraderApi->ReqQrySecAgentACIDMap(pQrySecAgentACIDMap, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryProductExchRate(CThostFtdcQryProductExchRateField *pQryProductExchRate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryProductExchRate: nRequestID[%d]", nRequestID);
	WriteQryProductExchRate(pQryProductExchRate);

	return m_TraderApi->ReqQryProductExchRate(pQryProductExchRate, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryProductGroup(CThostFtdcQryProductGroupField *pQryProductGroup, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryProductGroup: nRequestID[%d]", nRequestID);
	WriteQryProductGroup(pQryProductGroup);

	return m_TraderApi->ReqQryProductGroup(pQryProductGroup, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryMMInstrumentCommissionRate(CThostFtdcQryMMInstrumentCommissionRateField *pQryMMInstrumentCommissionRate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryMMInstrumentCommissionRate: nRequestID[%d]", nRequestID);
	WriteQryMMInstrumentCommissionRate(pQryMMInstrumentCommissionRate);

	return m_TraderApi->ReqQryMMInstrumentCommissionRate(pQryMMInstrumentCommissionRate, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryMMOptionInstrCommRate(CThostFtdcQryMMOptionInstrCommRateField *pQryMMOptionInstrCommRate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryMMOptionInstrCommRate: nRequestID[%d]", nRequestID);
	WriteQryMMOptionInstrCommRate(pQryMMOptionInstrCommRate);

	return m_TraderApi->ReqQryMMOptionInstrCommRate(pQryMMOptionInstrCommRate, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInstrumentOrderCommRate(CThostFtdcQryInstrumentOrderCommRateField *pQryInstrumentOrderCommRate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInstrumentOrderCommRate: nRequestID[%d]", nRequestID);
	WriteQryInstrumentOrderCommRate(pQryInstrumentOrderCommRate);

	return m_TraderApi->ReqQryInstrumentOrderCommRate(pQryInstrumentOrderCommRate, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySecAgentTradingAccount(CThostFtdcQryTradingAccountField *pQryTradingAccount, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySecAgentTradingAccount: nRequestID[%d]", nRequestID);
	WriteQryTradingAccount(pQryTradingAccount);

	return m_TraderApi->ReqQrySecAgentTradingAccount(pQryTradingAccount, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySecAgentCheckMode(CThostFtdcQrySecAgentCheckModeField *pQrySecAgentCheckMode, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySecAgentCheckMode: nRequestID[%d]", nRequestID);
	WriteQrySecAgentCheckMode(pQrySecAgentCheckMode);

	return m_TraderApi->ReqQrySecAgentCheckMode(pQrySecAgentCheckMode, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySecAgentTradeInfo(CThostFtdcQrySecAgentTradeInfoField *pQrySecAgentTradeInfo, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySecAgentTradeInfo: nRequestID[%d]", nRequestID);
	WriteQrySecAgentTradeInfo(pQrySecAgentTradeInfo);

	return m_TraderApi->ReqQrySecAgentTradeInfo(pQrySecAgentTradeInfo, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryOptionInstrTradeCost(CThostFtdcQryOptionInstrTradeCostField *pQryOptionInstrTradeCost, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryOptionInstrTradeCost: nRequestID[%d]", nRequestID);
	WriteQryOptionInstrTradeCost(pQryOptionInstrTradeCost);

	return m_TraderApi->ReqQryOptionInstrTradeCost(pQryOptionInstrTradeCost, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryOptionInstrCommRate(CThostFtdcQryOptionInstrCommRateField *pQryOptionInstrCommRate, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryOptionInstrCommRate: nRequestID[%d]", nRequestID);
	WriteQryOptionInstrCommRate(pQryOptionInstrCommRate);

	return m_TraderApi->ReqQryOptionInstrCommRate(pQryOptionInstrCommRate, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryExecOrder(CThostFtdcQryExecOrderField *pQryExecOrder, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryExecOrder: nRequestID[%d]", nRequestID);
	WriteQryExecOrder(pQryExecOrder);

	return m_TraderApi->ReqQryExecOrder(pQryExecOrder, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryForQuote(CThostFtdcQryForQuoteField *pQryForQuote, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryForQuote: nRequestID[%d]", nRequestID);
	WriteQryForQuote(pQryForQuote);

	return m_TraderApi->ReqQryForQuote(pQryForQuote, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryQuote(CThostFtdcQryQuoteField *pQryQuote, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryQuote: nRequestID[%d]", nRequestID);
	WriteQryQuote(pQryQuote);

	return m_TraderApi->ReqQryQuote(pQryQuote, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryOptionSelfClose(CThostFtdcQryOptionSelfCloseField *pQryOptionSelfClose, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryOptionSelfClose: nRequestID[%d]", nRequestID);
	WriteQryOptionSelfClose(pQryOptionSelfClose);

	return m_TraderApi->ReqQryOptionSelfClose(pQryOptionSelfClose, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestUnit(CThostFtdcQryInvestUnitField *pQryInvestUnit, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestUnit: nRequestID[%d]", nRequestID);
	WriteQryInvestUnit(pQryInvestUnit);

	return m_TraderApi->ReqQryInvestUnit(pQryInvestUnit, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryCombInstrumentGuard(CThostFtdcQryCombInstrumentGuardField *pQryCombInstrumentGuard, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryCombInstrumentGuard: nRequestID[%d]", nRequestID);
	WriteQryCombInstrumentGuard(pQryCombInstrumentGuard);

	return m_TraderApi->ReqQryCombInstrumentGuard(pQryCombInstrumentGuard, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryCombAction(CThostFtdcQryCombActionField *pQryCombAction, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryCombAction: nRequestID[%d]", nRequestID);
	WriteQryCombAction(pQryCombAction);

	return m_TraderApi->ReqQryCombAction(pQryCombAction, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryTransferSerial(CThostFtdcQryTransferSerialField *pQryTransferSerial, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryTransferSerial: nRequestID[%d]", nRequestID);
	WriteQryTransferSerial(pQryTransferSerial);

	return m_TraderApi->ReqQryTransferSerial(pQryTransferSerial, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryAccountregister(CThostFtdcQryAccountregisterField *pQryAccountregister, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryAccountregister: nRequestID[%d]", nRequestID);
	WriteQryAccountregister(pQryAccountregister);

	return m_TraderApi->ReqQryAccountregister(pQryAccountregister, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryContractBank(CThostFtdcQryContractBankField *pQryContractBank, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryContractBank: nRequestID[%d]", nRequestID);
	WriteQryContractBank(pQryContractBank);

	return m_TraderApi->ReqQryContractBank(pQryContractBank, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryParkedOrder(CThostFtdcQryParkedOrderField *pQryParkedOrder, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryParkedOrder: nRequestID[%d]", nRequestID);
	WriteQryParkedOrder(pQryParkedOrder);

	return m_TraderApi->ReqQryParkedOrder(pQryParkedOrder, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryParkedOrderAction(CThostFtdcQryParkedOrderActionField *pQryParkedOrderAction, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryParkedOrderAction: nRequestID[%d]", nRequestID);
	WriteQryParkedOrderAction(pQryParkedOrderAction);

	return m_TraderApi->ReqQryParkedOrderAction(pQryParkedOrderAction, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryTradingNotice(CThostFtdcQryTradingNoticeField *pQryTradingNotice, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryTradingNotice: nRequestID[%d]", nRequestID);
	WriteQryTradingNotice(pQryTradingNotice);

	return m_TraderApi->ReqQryTradingNotice(pQryTradingNotice, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryBrokerTradingParams(CThostFtdcQryBrokerTradingParamsField *pQryBrokerTradingParams, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryBrokerTradingParams: nRequestID[%d]", nRequestID);
	WriteQryBrokerTradingParams(pQryBrokerTradingParams);

	return m_TraderApi->ReqQryBrokerTradingParams(pQryBrokerTradingParams, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryBrokerTradingAlgos(CThostFtdcQryBrokerTradingAlgosField *pQryBrokerTradingAlgos, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryBrokerTradingAlgos: nRequestID[%d]", nRequestID);
	WriteQryBrokerTradingAlgos(pQryBrokerTradingAlgos);

	return m_TraderApi->ReqQryBrokerTradingAlgos(pQryBrokerTradingAlgos, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQueryCFMMCTradingAccountToken: nRequestID[%d]", nRequestID);
	WriteQueryCFMMCTradingAccountToken(pQueryCFMMCTradingAccountToken);

	return m_TraderApi->ReqQueryCFMMCTradingAccountToken(pQueryCFMMCTradingAccountToken, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqFromBankToFutureByFuture: nRequestID[%d]", nRequestID);
	WriteReqTransfer(pReqTransfer);

	return m_TraderApi->ReqFromBankToFutureByFuture(pReqTransfer, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqFromFutureToBankByFuture: nRequestID[%d]", nRequestID);
	WriteReqTransfer(pReqTransfer);

	return m_TraderApi->ReqFromFutureToBankByFuture(pReqTransfer, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQueryBankAccountMoneyByFuture: nRequestID[%d]", nRequestID);
	WriteReqQueryAccount(pReqQueryAccount);

	return m_TraderApi->ReqQueryBankAccountMoneyByFuture(pReqQueryAccount, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryClassifiedInstrument(CThostFtdcQryClassifiedInstrumentField *pQryClassifiedInstrument, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryClassifiedInstrument: nRequestID[%d]", nRequestID);
	WriteQryClassifiedInstrument(pQryClassifiedInstrument);

	return m_TraderApi->ReqQryClassifiedInstrument(pQryClassifiedInstrument, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryCombPromotionParam(CThostFtdcQryCombPromotionParamField *pQryCombPromotionParam, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryCombPromotionParam: nRequestID[%d]", nRequestID);
	WriteQryCombPromotionParam(pQryCombPromotionParam);

	return m_TraderApi->ReqQryCombPromotionParam(pQryCombPromotionParam, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryRiskSettleInvstPosition(CThostFtdcQryRiskSettleInvstPositionField *pQryRiskSettleInvstPosition, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryRiskSettleInvstPosition: nRequestID[%d]", nRequestID);
	WriteQryRiskSettleInvstPosition(pQryRiskSettleInvstPosition);

	return m_TraderApi->ReqQryRiskSettleInvstPosition(pQryRiskSettleInvstPosition, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryRiskSettleProductStatus(CThostFtdcQryRiskSettleProductStatusField *pQryRiskSettleProductStatus, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryRiskSettleProductStatus: nRequestID[%d]", nRequestID);
	WriteQryRiskSettleProductStatus(pQryRiskSettleProductStatus);

	return m_TraderApi->ReqQryRiskSettleProductStatus(pQryRiskSettleProductStatus, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySPBMFutureParameter(CThostFtdcQrySPBMFutureParameterField *pQrySPBMFutureParameter, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySPBMFutureParameter: nRequestID[%d]", nRequestID);
	WriteQrySPBMFutureParameter(pQrySPBMFutureParameter);

	return m_TraderApi->ReqQrySPBMFutureParameter(pQrySPBMFutureParameter, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySPBMOptionParameter(CThostFtdcQrySPBMOptionParameterField *pQrySPBMOptionParameter, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySPBMOptionParameter: nRequestID[%d]", nRequestID);
	WriteQrySPBMOptionParameter(pQrySPBMOptionParameter);

	return m_TraderApi->ReqQrySPBMOptionParameter(pQrySPBMOptionParameter, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySPBMIntraParameter(CThostFtdcQrySPBMIntraParameterField *pQrySPBMIntraParameter, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySPBMIntraParameter: nRequestID[%d]", nRequestID);
	WriteQrySPBMIntraParameter(pQrySPBMIntraParameter);

	return m_TraderApi->ReqQrySPBMIntraParameter(pQrySPBMIntraParameter, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySPBMInterParameter(CThostFtdcQrySPBMInterParameterField *pQrySPBMInterParameter, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySPBMInterParameter: nRequestID[%d]", nRequestID);
	WriteQrySPBMInterParameter(pQrySPBMInterParameter);

	return m_TraderApi->ReqQrySPBMInterParameter(pQrySPBMInterParameter, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySPBMPortfDefinition(CThostFtdcQrySPBMPortfDefinitionField *pQrySPBMPortfDefinition, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySPBMPortfDefinition: nRequestID[%d]", nRequestID);
	WriteQrySPBMPortfDefinition(pQrySPBMPortfDefinition);

	return m_TraderApi->ReqQrySPBMPortfDefinition(pQrySPBMPortfDefinition, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySPBMInvestorPortfDef(CThostFtdcQrySPBMInvestorPortfDefField *pQrySPBMInvestorPortfDef, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySPBMInvestorPortfDef: nRequestID[%d]", nRequestID);
	WriteQrySPBMInvestorPortfDef(pQrySPBMInvestorPortfDef);

	return m_TraderApi->ReqQrySPBMInvestorPortfDef(pQrySPBMInvestorPortfDef, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorPortfMarginRatio(CThostFtdcQryInvestorPortfMarginRatioField *pQryInvestorPortfMarginRatio, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorPortfMarginRatio: nRequestID[%d]", nRequestID);
	WriteQryInvestorPortfMarginRatio(pQryInvestorPortfMarginRatio);

	return m_TraderApi->ReqQryInvestorPortfMarginRatio(pQryInvestorPortfMarginRatio, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorProdSPBMDetail(CThostFtdcQryInvestorProdSPBMDetailField *pQryInvestorProdSPBMDetail, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorProdSPBMDetail: nRequestID[%d]", nRequestID);
	WriteQryInvestorProdSPBMDetail(pQryInvestorProdSPBMDetail);

	return m_TraderApi->ReqQryInvestorProdSPBMDetail(pQryInvestorProdSPBMDetail, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorCommoditySPMMMargin(CThostFtdcQryInvestorCommoditySPMMMarginField *pQryInvestorCommoditySPMMMargin, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorCommoditySPMMMargin: nRequestID[%d]", nRequestID);
	WriteQryInvestorCommoditySPMMMargin(pQryInvestorCommoditySPMMMargin);

	return m_TraderApi->ReqQryInvestorCommoditySPMMMargin(pQryInvestorCommoditySPMMMargin, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorCommodityGroupSPMMMargin(CThostFtdcQryInvestorCommodityGroupSPMMMarginField *pQryInvestorCommodityGroupSPMMMargin, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorCommodityGroupSPMMMargin: nRequestID[%d]", nRequestID);
	WriteQryInvestorCommodityGroupSPMMMargin(pQryInvestorCommodityGroupSPMMMargin);

	return m_TraderApi->ReqQryInvestorCommodityGroupSPMMMargin(pQryInvestorCommodityGroupSPMMMargin, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySPMMInstParam(CThostFtdcQrySPMMInstParamField *pQrySPMMInstParam, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySPMMInstParam: nRequestID[%d]", nRequestID);
	WriteQrySPMMInstParam(pQrySPMMInstParam);

	return m_TraderApi->ReqQrySPMMInstParam(pQrySPMMInstParam, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySPMMProductParam(CThostFtdcQrySPMMProductParamField *pQrySPMMProductParam, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySPMMProductParam: nRequestID[%d]", nRequestID);
	WriteQrySPMMProductParam(pQrySPMMProductParam);

	return m_TraderApi->ReqQrySPMMProductParam(pQrySPMMProductParam, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQrySPBMAddOnInterParameter(CThostFtdcQrySPBMAddOnInterParameterField *pQrySPBMAddOnInterParameter, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQrySPBMAddOnInterParameter: nRequestID[%d]", nRequestID);
	WriteQrySPBMAddOnInterParameter(pQrySPBMAddOnInterParameter);

	return m_TraderApi->ReqQrySPBMAddOnInterParameter(pQrySPBMAddOnInterParameter, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryRCAMSCombProductInfo(CThostFtdcQryRCAMSCombProductInfoField *pQryRCAMSCombProductInfo, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryRCAMSCombProductInfo: nRequestID[%d]", nRequestID);
	WriteQryRCAMSCombProductInfo(pQryRCAMSCombProductInfo);

	return m_TraderApi->ReqQryRCAMSCombProductInfo(pQryRCAMSCombProductInfo, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryRCAMSInstrParameter(CThostFtdcQryRCAMSInstrParameterField *pQryRCAMSInstrParameter, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryRCAMSInstrParameter: nRequestID[%d]", nRequestID);
	WriteQryRCAMSInstrParameter(pQryRCAMSInstrParameter);

	return m_TraderApi->ReqQryRCAMSInstrParameter(pQryRCAMSInstrParameter, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryRCAMSIntraParameter(CThostFtdcQryRCAMSIntraParameterField *pQryRCAMSIntraParameter, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryRCAMSIntraParameter: nRequestID[%d]", nRequestID);
	WriteQryRCAMSIntraParameter(pQryRCAMSIntraParameter);

	return m_TraderApi->ReqQryRCAMSIntraParameter(pQryRCAMSIntraParameter, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryRCAMSInterParameter(CThostFtdcQryRCAMSInterParameterField *pQryRCAMSInterParameter, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryRCAMSInterParameter: nRequestID[%d]", nRequestID);
	WriteQryRCAMSInterParameter(pQryRCAMSInterParameter);

	return m_TraderApi->ReqQryRCAMSInterParameter(pQryRCAMSInterParameter, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryRCAMSShortOptAdjustParam(CThostFtdcQryRCAMSShortOptAdjustParamField *pQryRCAMSShortOptAdjustParam, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryRCAMSShortOptAdjustParam: nRequestID[%d]", nRequestID);
	WriteQryRCAMSShortOptAdjustParam(pQryRCAMSShortOptAdjustParam);

	return m_TraderApi->ReqQryRCAMSShortOptAdjustParam(pQryRCAMSShortOptAdjustParam, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryRCAMSInvestorCombPosition(CThostFtdcQryRCAMSInvestorCombPositionField *pQryRCAMSInvestorCombPosition, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryRCAMSInvestorCombPosition: nRequestID[%d]", nRequestID);
	WriteQryRCAMSInvestorCombPosition(pQryRCAMSInvestorCombPosition);

	return m_TraderApi->ReqQryRCAMSInvestorCombPosition(pQryRCAMSInvestorCombPosition, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorProdRCAMSMargin(CThostFtdcQryInvestorProdRCAMSMarginField *pQryInvestorProdRCAMSMargin, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorProdRCAMSMargin: nRequestID[%d]", nRequestID);
	WriteQryInvestorProdRCAMSMargin(pQryInvestorProdRCAMSMargin);

	return m_TraderApi->ReqQryInvestorProdRCAMSMargin(pQryInvestorProdRCAMSMargin, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryRULEInstrParameter(CThostFtdcQryRULEInstrParameterField *pQryRULEInstrParameter, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryRULEInstrParameter: nRequestID[%d]", nRequestID);
	WriteQryRULEInstrParameter(pQryRULEInstrParameter);

	return m_TraderApi->ReqQryRULEInstrParameter(pQryRULEInstrParameter, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryRULEIntraParameter(CThostFtdcQryRULEIntraParameterField *pQryRULEIntraParameter, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryRULEIntraParameter: nRequestID[%d]", nRequestID);
	WriteQryRULEIntraParameter(pQryRULEIntraParameter);

	return m_TraderApi->ReqQryRULEIntraParameter(pQryRULEIntraParameter, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryRULEInterParameter(CThostFtdcQryRULEInterParameterField *pQryRULEInterParameter, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryRULEInterParameter: nRequestID[%d]", nRequestID);
	WriteQryRULEInterParameter(pQryRULEInterParameter);

	return m_TraderApi->ReqQryRULEInterParameter(pQryRULEInterParameter, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorProdRULEMargin(CThostFtdcQryInvestorProdRULEMarginField *pQryInvestorProdRULEMargin, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorProdRULEMargin: nRequestID[%d]", nRequestID);
	WriteQryInvestorProdRULEMargin(pQryInvestorProdRULEMargin);

	return m_TraderApi->ReqQryInvestorProdRULEMargin(pQryInvestorProdRULEMargin, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorPortfSetting(CThostFtdcQryInvestorPortfSettingField *pQryInvestorPortfSetting, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorPortfSetting: nRequestID[%d]", nRequestID);
	WriteQryInvestorPortfSetting(pQryInvestorPortfSetting);

	return m_TraderApi->ReqQryInvestorPortfSetting(pQryInvestorPortfSetting, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryInvestorInfoCommRec(CThostFtdcQryInvestorInfoCommRecField *pQryInvestorInfoCommRec, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryInvestorInfoCommRec: nRequestID[%d]", nRequestID);
	WriteQryInvestorInfoCommRec(pQryInvestorInfoCommRec);

	return m_TraderApi->ReqQryInvestorInfoCommRec(pQryInvestorInfoCommRec, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryCombLeg(CThostFtdcQryCombLegField *pQryCombLeg, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryCombLeg: nRequestID[%d]", nRequestID);
	WriteQryCombLeg(pQryCombLeg);

	return m_TraderApi->ReqQryCombLeg(pQryCombLeg, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqOffsetSetting(CThostFtdcInputOffsetSettingField *pInputOffsetSetting, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqOffsetSetting: nRequestID[%d]", nRequestID);
	WriteInputOffsetSetting(pInputOffsetSetting);

	return m_TraderApi->ReqOffsetSetting(pInputOffsetSetting, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqCancelOffsetSetting(CThostFtdcInputOffsetSettingField *pInputOffsetSetting, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqCancelOffsetSetting: nRequestID[%d]", nRequestID);
	WriteInputOffsetSetting(pInputOffsetSetting);

	return m_TraderApi->ReqCancelOffsetSetting(pInputOffsetSetting, nRequestID);
}
int CThostFtdcTraderApiMiddle::ReqQryOffsetSetting(CThostFtdcQryOffsetSettingField *pQryOffsetSetting, int nRequestID)
{
	WriteLog(LogLevel::Info, "ReqQryOffsetSetting: nRequestID[%d]", nRequestID);
	WriteQryOffsetSetting(pQryOffsetSetting);

	return m_TraderApi->ReqQryOffsetSetting(pQryOffsetSetting, nRequestID);
}
