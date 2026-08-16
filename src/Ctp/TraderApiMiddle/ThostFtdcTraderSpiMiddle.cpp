#include "ThostFtdcTraderSpiMiddle.h"
#include "StructLogFunc.h"
#include <Spark/Core/Logger/Logger.h>



void CThostFtdcTraderSpiMiddle::OnFrontConnected()
{
	WriteLog(LogLevel::Info, "OnFrontConnected:");
}
void CThostFtdcTraderSpiMiddle::OnFrontDisconnected(int nReason)
{
	WriteLog(LogLevel::Info, "OnFrontDisconnected: nReason[%d]", nReason);
}
void CThostFtdcTraderSpiMiddle::OnHeartBeatWarning(int nTimeLapse)
{
	WriteLog(LogLevel::Info, "OnHeartBeatWarning: nTimeLapse[%d]", nTimeLapse);
}
void CThostFtdcTraderSpiMiddle::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspAuthenticate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRspAuthenticate(pRspAuthenticate);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspUserLogin: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRspUserLogin(pRspUserLogin);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspUserLogout: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteUserLogout(pUserLogout);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspUserPasswordUpdate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteUserPasswordUpdate(pUserPasswordUpdate);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField *pTradingAccountPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspTradingAccountPasswordUpdate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteTradingAccountPasswordUpdate(pTradingAccountPasswordUpdate);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspUserAuthMethod(CThostFtdcRspUserAuthMethodField *pRspUserAuthMethod, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspUserAuthMethod: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRspUserAuthMethod(pRspUserAuthMethod);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspGenUserCaptcha(CThostFtdcRspGenUserCaptchaField *pRspGenUserCaptcha, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspGenUserCaptcha: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRspGenUserCaptcha(pRspGenUserCaptcha);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspGenUserText(CThostFtdcRspGenUserTextField *pRspGenUserText, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspGenUserText: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRspGenUserText(pRspGenUserText);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspOrderInsert: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputOrder(pInputOrder);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspParkedOrderInsert(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspParkedOrderInsert: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteParkedOrder(pParkedOrder);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspParkedOrderAction: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteParkedOrderAction(pParkedOrderAction);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspOrderAction: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputOrderAction(pInputOrderAction);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryMaxOrderVolume(CThostFtdcQryMaxOrderVolumeField *pQryMaxOrderVolume, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryMaxOrderVolume: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteQryMaxOrderVolume(pQryMaxOrderVolume);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspSettlementInfoConfirm: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSettlementInfoConfirm(pSettlementInfoConfirm);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspRemoveParkedOrder(CThostFtdcRemoveParkedOrderField *pRemoveParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspRemoveParkedOrder: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRemoveParkedOrder(pRemoveParkedOrder);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField *pRemoveParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspRemoveParkedOrderAction: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRemoveParkedOrderAction(pRemoveParkedOrderAction);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspExecOrderInsert: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputExecOrder(pInputExecOrder);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspExecOrderAction(CThostFtdcInputExecOrderActionField *pInputExecOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspExecOrderAction: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputExecOrderAction(pInputExecOrderAction);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspForQuoteInsert: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputForQuote(pInputForQuote);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQuoteInsert: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputQuote(pInputQuote);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQuoteAction(CThostFtdcInputQuoteActionField *pInputQuoteAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQuoteAction: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputQuoteAction(pInputQuoteAction);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspBatchOrderAction(CThostFtdcInputBatchOrderActionField *pInputBatchOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspBatchOrderAction: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputBatchOrderAction(pInputBatchOrderAction);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspOptionSelfCloseInsert: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputOptionSelfClose(pInputOptionSelfClose);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField *pInputOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspOptionSelfCloseAction: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputOptionSelfCloseAction(pInputOptionSelfCloseAction);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspCombActionInsert: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputCombAction(pInputCombAction);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryOrder: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteOrder(pOrder);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryTrade: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteTrade(pTrade);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryInvestorPosition: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInvestorPosition(pInvestorPosition);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryTradingAccount: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteTradingAccount(pTradingAccount);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryInvestor: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInvestor(pInvestor);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryTradingCode: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteTradingCode(pTradingCode);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryInstrumentMarginRate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInstrumentMarginRate(pInstrumentMarginRate);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryInstrumentCommissionRate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInstrumentCommissionRate(pInstrumentCommissionRate);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryExchange(CThostFtdcExchangeField *pExchange, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryExchange: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteExchange(pExchange);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryProduct(CThostFtdcProductField *pProduct, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryProduct: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteProduct(pProduct);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryInstrument: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInstrument(pInstrument);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryDepthMarketData: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteDepthMarketData(pDepthMarketData);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryTraderOffer(CThostFtdcTraderOfferField *pTraderOffer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryTraderOffer: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteTraderOffer(pTraderOffer);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQrySettlementInfo: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSettlementInfo(pSettlementInfo);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryTransferBank(CThostFtdcTransferBankField *pTransferBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryTransferBank: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteTransferBank(pTransferBank);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryInvestorPositionDetail(CThostFtdcInvestorPositionDetailField *pInvestorPositionDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryInvestorPositionDetail: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInvestorPositionDetail(pInvestorPositionDetail);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryNotice(CThostFtdcNoticeField *pNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryNotice: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteNotice(pNotice);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQrySettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQrySettlementInfoConfirm: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSettlementInfoConfirm(pSettlementInfoConfirm);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField *pInvestorPositionCombineDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryInvestorPositionCombineDetail: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInvestorPositionCombineDetail(pInvestorPositionCombineDetail);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField *pCFMMCTradingAccountKey, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryCFMMCTradingAccountKey: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteCFMMCTradingAccountKey(pCFMMCTradingAccountKey);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryEWarrantOffset(CThostFtdcEWarrantOffsetField *pEWarrantOffset, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryEWarrantOffset: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteEWarrantOffset(pEWarrantOffset);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField *pInvestorProductGroupMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryInvestorProductGroupMargin: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInvestorProductGroupMargin(pInvestorProductGroupMargin);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryExchangeMarginRate(CThostFtdcExchangeMarginRateField *pExchangeMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryExchangeMarginRate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteExchangeMarginRate(pExchangeMarginRate);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField *pExchangeMarginRateAdjust, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryExchangeMarginRateAdjust: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteExchangeMarginRateAdjust(pExchangeMarginRateAdjust);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryExchangeRate(CThostFtdcExchangeRateField *pExchangeRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryExchangeRate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteExchangeRate(pExchangeRate);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQrySecAgentACIDMap(CThostFtdcSecAgentACIDMapField *pSecAgentACIDMap, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQrySecAgentACIDMap: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSecAgentACIDMap(pSecAgentACIDMap);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryProductExchRate(CThostFtdcProductExchRateField *pProductExchRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryProductExchRate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteProductExchRate(pProductExchRate);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryProductGroup(CThostFtdcProductGroupField *pProductGroup, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryProductGroup: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteProductGroup(pProductGroup);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField *pMMInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryMMInstrumentCommissionRate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteMMInstrumentCommissionRate(pMMInstrumentCommissionRate);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField *pMMOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryMMOptionInstrCommRate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteMMOptionInstrCommRate(pMMOptionInstrCommRate);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField *pInstrumentOrderCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryInstrumentOrderCommRate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInstrumentOrderCommRate(pInstrumentOrderCommRate);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQrySecAgentTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQrySecAgentTradingAccount: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteTradingAccount(pTradingAccount);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQrySecAgentCheckMode(CThostFtdcSecAgentCheckModeField *pSecAgentCheckMode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQrySecAgentCheckMode: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSecAgentCheckMode(pSecAgentCheckMode);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQrySecAgentTradeInfo(CThostFtdcSecAgentTradeInfoField *pSecAgentTradeInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQrySecAgentTradeInfo: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSecAgentTradeInfo(pSecAgentTradeInfo);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField *pOptionInstrTradeCost, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryOptionInstrTradeCost: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteOptionInstrTradeCost(pOptionInstrTradeCost);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryOptionInstrCommRate(CThostFtdcOptionInstrCommRateField *pOptionInstrCommRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryOptionInstrCommRate: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteOptionInstrCommRate(pOptionInstrCommRate);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryExecOrder(CThostFtdcExecOrderField *pExecOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryExecOrder: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteExecOrder(pExecOrder);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryForQuote(CThostFtdcForQuoteField *pForQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryForQuote: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteForQuote(pForQuote);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryQuote(CThostFtdcQuoteField *pQuote, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryQuote: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteQuote(pQuote);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryOptionSelfClose: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteOptionSelfClose(pOptionSelfClose);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryInvestUnit(CThostFtdcInvestUnitField *pInvestUnit, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryInvestUnit: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInvestUnit(pInvestUnit);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryCombInstrumentGuard(CThostFtdcCombInstrumentGuardField *pCombInstrumentGuard, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryCombInstrumentGuard: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteCombInstrumentGuard(pCombInstrumentGuard);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryCombAction(CThostFtdcCombActionField *pCombAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryCombAction: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteCombAction(pCombAction);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryTransferSerial(CThostFtdcTransferSerialField *pTransferSerial, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryTransferSerial: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteTransferSerial(pTransferSerial);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryAccountregister(CThostFtdcAccountregisterField *pAccountregister, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryAccountregister: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteAccountregister(pAccountregister);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspError: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
	WriteLog(LogLevel::Info, "OnRtnOrder:");
	WriteOrder(pOrder);
}
void CThostFtdcTraderSpiMiddle::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
	WriteLog(LogLevel::Info, "OnRtnTrade:");
	WriteTrade(pTrade);
}
void CThostFtdcTraderSpiMiddle::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{
	WriteLog(LogLevel::Info, "OnErrRtnOrderInsert:");
	WriteInputOrder(pInputOrder);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
	WriteLog(LogLevel::Info, "OnErrRtnOrderAction:");
	WriteOrderAction(pOrderAction);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus)
{
	WriteLog(LogLevel::Info, "OnRtnInstrumentStatus:");
	WriteInstrumentStatus(pInstrumentStatus);
}
void CThostFtdcTraderSpiMiddle::OnRtnBulletin(CThostFtdcBulletinField *pBulletin)
{
	WriteLog(LogLevel::Info, "OnRtnBulletin:");
	WriteBulletin(pBulletin);
}
void CThostFtdcTraderSpiMiddle::OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo)
{
	WriteLog(LogLevel::Info, "OnRtnTradingNotice:");
	WriteTradingNoticeInfo(pTradingNoticeInfo);
}
void CThostFtdcTraderSpiMiddle::OnRtnErrorConditionalOrder(CThostFtdcErrorConditionalOrderField *pErrorConditionalOrder)
{
	WriteLog(LogLevel::Info, "OnRtnErrorConditionalOrder:");
	WriteErrorConditionalOrder(pErrorConditionalOrder);
}
void CThostFtdcTraderSpiMiddle::OnRtnExecOrder(CThostFtdcExecOrderField *pExecOrder)
{
	WriteLog(LogLevel::Info, "OnRtnExecOrder:");
	WriteExecOrder(pExecOrder);
}
void CThostFtdcTraderSpiMiddle::OnErrRtnExecOrderInsert(CThostFtdcInputExecOrderField *pInputExecOrder, CThostFtdcRspInfoField *pRspInfo)
{
	WriteLog(LogLevel::Info, "OnErrRtnExecOrderInsert:");
	WriteInputExecOrder(pInputExecOrder);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnErrRtnExecOrderAction(CThostFtdcExecOrderActionField *pExecOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
	WriteLog(LogLevel::Info, "OnErrRtnExecOrderAction:");
	WriteExecOrderAction(pExecOrderAction);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnErrRtnForQuoteInsert(CThostFtdcInputForQuoteField *pInputForQuote, CThostFtdcRspInfoField *pRspInfo)
{
	WriteLog(LogLevel::Info, "OnErrRtnForQuoteInsert:");
	WriteInputForQuote(pInputForQuote);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRtnQuote(CThostFtdcQuoteField *pQuote)
{
	WriteLog(LogLevel::Info, "OnRtnQuote:");
	WriteQuote(pQuote);
}
void CThostFtdcTraderSpiMiddle::OnErrRtnQuoteInsert(CThostFtdcInputQuoteField *pInputQuote, CThostFtdcRspInfoField *pRspInfo)
{
	WriteLog(LogLevel::Info, "OnErrRtnQuoteInsert:");
	WriteInputQuote(pInputQuote);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnErrRtnQuoteAction(CThostFtdcQuoteActionField *pQuoteAction, CThostFtdcRspInfoField *pRspInfo)
{
	WriteLog(LogLevel::Info, "OnErrRtnQuoteAction:");
	WriteQuoteAction(pQuoteAction);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{
	WriteLog(LogLevel::Info, "OnRtnForQuoteRsp:");
	WriteForQuoteRsp(pForQuoteRsp);
}
void CThostFtdcTraderSpiMiddle::OnRtnCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField *pCFMMCTradingAccountToken)
{
	WriteLog(LogLevel::Info, "OnRtnCFMMCTradingAccountToken:");
	WriteCFMMCTradingAccountToken(pCFMMCTradingAccountToken);
}
void CThostFtdcTraderSpiMiddle::OnErrRtnBatchOrderAction(CThostFtdcBatchOrderActionField *pBatchOrderAction, CThostFtdcRspInfoField *pRspInfo)
{
	WriteLog(LogLevel::Info, "OnErrRtnBatchOrderAction:");
	WriteBatchOrderAction(pBatchOrderAction);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRtnOptionSelfClose(CThostFtdcOptionSelfCloseField *pOptionSelfClose)
{
	WriteLog(LogLevel::Info, "OnRtnOptionSelfClose:");
	WriteOptionSelfClose(pOptionSelfClose);
}
void CThostFtdcTraderSpiMiddle::OnErrRtnOptionSelfCloseInsert(CThostFtdcInputOptionSelfCloseField *pInputOptionSelfClose, CThostFtdcRspInfoField *pRspInfo)
{
	WriteLog(LogLevel::Info, "OnErrRtnOptionSelfCloseInsert:");
	WriteInputOptionSelfClose(pInputOptionSelfClose);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnErrRtnOptionSelfCloseAction(CThostFtdcOptionSelfCloseActionField *pOptionSelfCloseAction, CThostFtdcRspInfoField *pRspInfo)
{
	WriteLog(LogLevel::Info, "OnErrRtnOptionSelfCloseAction:");
	WriteOptionSelfCloseAction(pOptionSelfCloseAction);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRtnCombAction(CThostFtdcCombActionField *pCombAction)
{
	WriteLog(LogLevel::Info, "OnRtnCombAction:");
	WriteCombAction(pCombAction);
}
void CThostFtdcTraderSpiMiddle::OnErrRtnCombActionInsert(CThostFtdcInputCombActionField *pInputCombAction, CThostFtdcRspInfoField *pRspInfo)
{
	WriteLog(LogLevel::Info, "OnErrRtnCombActionInsert:");
	WriteInputCombAction(pInputCombAction);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryContractBank(CThostFtdcContractBankField *pContractBank, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryContractBank: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteContractBank(pContractBank);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryParkedOrder(CThostFtdcParkedOrderField *pParkedOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryParkedOrder: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteParkedOrder(pParkedOrder);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryParkedOrderAction(CThostFtdcParkedOrderActionField *pParkedOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryParkedOrderAction: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteParkedOrderAction(pParkedOrderAction);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryTradingNotice(CThostFtdcTradingNoticeField *pTradingNotice, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryTradingNotice: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteTradingNotice(pTradingNotice);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryBrokerTradingParams(CThostFtdcBrokerTradingParamsField *pBrokerTradingParams, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryBrokerTradingParams: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteBrokerTradingParams(pBrokerTradingParams);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField *pBrokerTradingAlgos, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryBrokerTradingAlgos: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteBrokerTradingAlgos(pBrokerTradingAlgos);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField *pQueryCFMMCTradingAccountToken, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQueryCFMMCTradingAccountToken: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteQueryCFMMCTradingAccountToken(pQueryCFMMCTradingAccountToken);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRtnFromBankToFutureByBank(CThostFtdcRspTransferField *pRspTransfer)
{
	WriteLog(LogLevel::Info, "OnRtnFromBankToFutureByBank:");
	WriteRspTransfer(pRspTransfer);
}
void CThostFtdcTraderSpiMiddle::OnRtnFromFutureToBankByBank(CThostFtdcRspTransferField *pRspTransfer)
{
	WriteLog(LogLevel::Info, "OnRtnFromFutureToBankByBank:");
	WriteRspTransfer(pRspTransfer);
}
void CThostFtdcTraderSpiMiddle::OnRtnRepealFromBankToFutureByBank(CThostFtdcRspRepealField *pRspRepeal)
{
	WriteLog(LogLevel::Info, "OnRtnRepealFromBankToFutureByBank:");
	WriteRspRepeal(pRspRepeal);
}
void CThostFtdcTraderSpiMiddle::OnRtnRepealFromFutureToBankByBank(CThostFtdcRspRepealField *pRspRepeal)
{
	WriteLog(LogLevel::Info, "OnRtnRepealFromFutureToBankByBank:");
	WriteRspRepeal(pRspRepeal);
}
void CThostFtdcTraderSpiMiddle::OnRtnFromBankToFutureByFuture(CThostFtdcRspTransferField *pRspTransfer)
{
	WriteLog(LogLevel::Info, "OnRtnFromBankToFutureByFuture:");
	WriteRspTransfer(pRspTransfer);
}
void CThostFtdcTraderSpiMiddle::OnRtnFromFutureToBankByFuture(CThostFtdcRspTransferField *pRspTransfer)
{
	WriteLog(LogLevel::Info, "OnRtnFromFutureToBankByFuture:");
	WriteRspTransfer(pRspTransfer);
}
void CThostFtdcTraderSpiMiddle::OnRtnRepealFromBankToFutureByFutureManual(CThostFtdcRspRepealField *pRspRepeal)
{
	WriteLog(LogLevel::Info, "OnRtnRepealFromBankToFutureByFutureManual:");
	WriteRspRepeal(pRspRepeal);
}
void CThostFtdcTraderSpiMiddle::OnRtnRepealFromFutureToBankByFutureManual(CThostFtdcRspRepealField *pRspRepeal)
{
	WriteLog(LogLevel::Info, "OnRtnRepealFromFutureToBankByFutureManual:");
	WriteRspRepeal(pRspRepeal);
}
void CThostFtdcTraderSpiMiddle::OnRtnQueryBankBalanceByFuture(CThostFtdcNotifyQueryAccountField *pNotifyQueryAccount)
{
	WriteLog(LogLevel::Info, "OnRtnQueryBankBalanceByFuture:");
	WriteNotifyQueryAccount(pNotifyQueryAccount);
}
void CThostFtdcTraderSpiMiddle::OnErrRtnBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo)
{
	WriteLog(LogLevel::Info, "OnErrRtnBankToFutureByFuture:");
	WriteReqTransfer(pReqTransfer);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnErrRtnFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo)
{
	WriteLog(LogLevel::Info, "OnErrRtnFutureToBankByFuture:");
	WriteReqTransfer(pReqTransfer);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnErrRtnRepealBankToFutureByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo)
{
	WriteLog(LogLevel::Info, "OnErrRtnRepealBankToFutureByFutureManual:");
	WriteReqRepeal(pReqRepeal);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnErrRtnRepealFutureToBankByFutureManual(CThostFtdcReqRepealField *pReqRepeal, CThostFtdcRspInfoField *pRspInfo)
{
	WriteLog(LogLevel::Info, "OnErrRtnRepealFutureToBankByFutureManual:");
	WriteReqRepeal(pReqRepeal);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnErrRtnQueryBankBalanceByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo)
{
	WriteLog(LogLevel::Info, "OnErrRtnQueryBankBalanceByFuture:");
	WriteReqQueryAccount(pReqQueryAccount);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRtnRepealFromBankToFutureByFuture(CThostFtdcRspRepealField *pRspRepeal)
{
	WriteLog(LogLevel::Info, "OnRtnRepealFromBankToFutureByFuture:");
	WriteRspRepeal(pRspRepeal);
}
void CThostFtdcTraderSpiMiddle::OnRtnRepealFromFutureToBankByFuture(CThostFtdcRspRepealField *pRspRepeal)
{
	WriteLog(LogLevel::Info, "OnRtnRepealFromFutureToBankByFuture:");
	WriteRspRepeal(pRspRepeal);
}
void CThostFtdcTraderSpiMiddle::OnRspFromBankToFutureByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspFromBankToFutureByFuture: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteReqTransfer(pReqTransfer);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspFromFutureToBankByFuture(CThostFtdcReqTransferField *pReqTransfer, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspFromFutureToBankByFuture: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteReqTransfer(pReqTransfer);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQueryBankAccountMoneyByFuture(CThostFtdcReqQueryAccountField *pReqQueryAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQueryBankAccountMoneyByFuture: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteReqQueryAccount(pReqQueryAccount);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRtnOpenAccountByBank(CThostFtdcOpenAccountField *pOpenAccount)
{
	WriteLog(LogLevel::Info, "OnRtnOpenAccountByBank:");
	WriteOpenAccount(pOpenAccount);
}
void CThostFtdcTraderSpiMiddle::OnRtnCancelAccountByBank(CThostFtdcCancelAccountField *pCancelAccount)
{
	WriteLog(LogLevel::Info, "OnRtnCancelAccountByBank:");
	WriteCancelAccount(pCancelAccount);
}
void CThostFtdcTraderSpiMiddle::OnRtnChangeAccountByBank(CThostFtdcChangeAccountField *pChangeAccount)
{
	WriteLog(LogLevel::Info, "OnRtnChangeAccountByBank:");
	WriteChangeAccount(pChangeAccount);
}
void CThostFtdcTraderSpiMiddle::OnRspQryClassifiedInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryClassifiedInstrument: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInstrument(pInstrument);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryCombPromotionParam(CThostFtdcCombPromotionParamField *pCombPromotionParam, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryCombPromotionParam: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteCombPromotionParam(pCombPromotionParam);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryRiskSettleInvstPosition(CThostFtdcRiskSettleInvstPositionField *pRiskSettleInvstPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryRiskSettleInvstPosition: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRiskSettleInvstPosition(pRiskSettleInvstPosition);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryRiskSettleProductStatus(CThostFtdcRiskSettleProductStatusField *pRiskSettleProductStatus, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryRiskSettleProductStatus: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRiskSettleProductStatus(pRiskSettleProductStatus);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQrySPBMFutureParameter(CThostFtdcSPBMFutureParameterField *pSPBMFutureParameter, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQrySPBMFutureParameter: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSPBMFutureParameter(pSPBMFutureParameter);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQrySPBMOptionParameter(CThostFtdcSPBMOptionParameterField *pSPBMOptionParameter, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQrySPBMOptionParameter: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSPBMOptionParameter(pSPBMOptionParameter);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQrySPBMIntraParameter(CThostFtdcSPBMIntraParameterField *pSPBMIntraParameter, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQrySPBMIntraParameter: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSPBMIntraParameter(pSPBMIntraParameter);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQrySPBMInterParameter(CThostFtdcSPBMInterParameterField *pSPBMInterParameter, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQrySPBMInterParameter: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSPBMInterParameter(pSPBMInterParameter);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQrySPBMPortfDefinition(CThostFtdcSPBMPortfDefinitionField *pSPBMPortfDefinition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQrySPBMPortfDefinition: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSPBMPortfDefinition(pSPBMPortfDefinition);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQrySPBMInvestorPortfDef(CThostFtdcSPBMInvestorPortfDefField *pSPBMInvestorPortfDef, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQrySPBMInvestorPortfDef: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSPBMInvestorPortfDef(pSPBMInvestorPortfDef);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryInvestorPortfMarginRatio(CThostFtdcInvestorPortfMarginRatioField *pInvestorPortfMarginRatio, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryInvestorPortfMarginRatio: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInvestorPortfMarginRatio(pInvestorPortfMarginRatio);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryInvestorProdSPBMDetail(CThostFtdcInvestorProdSPBMDetailField *pInvestorProdSPBMDetail, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryInvestorProdSPBMDetail: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInvestorProdSPBMDetail(pInvestorProdSPBMDetail);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryInvestorCommoditySPMMMargin(CThostFtdcInvestorCommoditySPMMMarginField *pInvestorCommoditySPMMMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryInvestorCommoditySPMMMargin: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInvestorCommoditySPMMMargin(pInvestorCommoditySPMMMargin);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryInvestorCommodityGroupSPMMMargin(CThostFtdcInvestorCommodityGroupSPMMMarginField *pInvestorCommodityGroupSPMMMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryInvestorCommodityGroupSPMMMargin: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInvestorCommodityGroupSPMMMargin(pInvestorCommodityGroupSPMMMargin);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQrySPMMInstParam(CThostFtdcSPMMInstParamField *pSPMMInstParam, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQrySPMMInstParam: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSPMMInstParam(pSPMMInstParam);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQrySPMMProductParam(CThostFtdcSPMMProductParamField *pSPMMProductParam, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQrySPMMProductParam: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSPMMProductParam(pSPMMProductParam);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQrySPBMAddOnInterParameter(CThostFtdcSPBMAddOnInterParameterField *pSPBMAddOnInterParameter, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQrySPBMAddOnInterParameter: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSPBMAddOnInterParameter(pSPBMAddOnInterParameter);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryRCAMSCombProductInfo(CThostFtdcRCAMSCombProductInfoField *pRCAMSCombProductInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryRCAMSCombProductInfo: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRCAMSCombProductInfo(pRCAMSCombProductInfo);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryRCAMSInstrParameter(CThostFtdcRCAMSInstrParameterField *pRCAMSInstrParameter, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryRCAMSInstrParameter: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRCAMSInstrParameter(pRCAMSInstrParameter);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryRCAMSIntraParameter(CThostFtdcRCAMSIntraParameterField *pRCAMSIntraParameter, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryRCAMSIntraParameter: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRCAMSIntraParameter(pRCAMSIntraParameter);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryRCAMSInterParameter(CThostFtdcRCAMSInterParameterField *pRCAMSInterParameter, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryRCAMSInterParameter: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRCAMSInterParameter(pRCAMSInterParameter);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryRCAMSShortOptAdjustParam(CThostFtdcRCAMSShortOptAdjustParamField *pRCAMSShortOptAdjustParam, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryRCAMSShortOptAdjustParam: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRCAMSShortOptAdjustParam(pRCAMSShortOptAdjustParam);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryRCAMSInvestorCombPosition(CThostFtdcRCAMSInvestorCombPositionField *pRCAMSInvestorCombPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryRCAMSInvestorCombPosition: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRCAMSInvestorCombPosition(pRCAMSInvestorCombPosition);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryInvestorProdRCAMSMargin(CThostFtdcInvestorProdRCAMSMarginField *pInvestorProdRCAMSMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryInvestorProdRCAMSMargin: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInvestorProdRCAMSMargin(pInvestorProdRCAMSMargin);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryRULEInstrParameter(CThostFtdcRULEInstrParameterField *pRULEInstrParameter, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryRULEInstrParameter: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRULEInstrParameter(pRULEInstrParameter);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryRULEIntraParameter(CThostFtdcRULEIntraParameterField *pRULEIntraParameter, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryRULEIntraParameter: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRULEIntraParameter(pRULEIntraParameter);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryRULEInterParameter(CThostFtdcRULEInterParameterField *pRULEInterParameter, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryRULEInterParameter: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRULEInterParameter(pRULEInterParameter);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryInvestorProdRULEMargin(CThostFtdcInvestorProdRULEMarginField *pInvestorProdRULEMargin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryInvestorProdRULEMargin: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInvestorProdRULEMargin(pInvestorProdRULEMargin);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryInvestorPortfSetting(CThostFtdcInvestorPortfSettingField *pInvestorPortfSetting, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryInvestorPortfSetting: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInvestorPortfSetting(pInvestorPortfSetting);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryInvestorInfoCommRec(CThostFtdcInvestorInfoCommRecField *pInvestorInfoCommRec, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryInvestorInfoCommRec: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInvestorInfoCommRec(pInvestorInfoCommRec);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryCombLeg(CThostFtdcCombLegField *pCombLeg, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryCombLeg: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteCombLeg(pCombLeg);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspOffsetSetting(CThostFtdcInputOffsetSettingField *pInputOffsetSetting, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspOffsetSetting: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputOffsetSetting(pInputOffsetSetting);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspCancelOffsetSetting(CThostFtdcInputOffsetSettingField *pInputOffsetSetting, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspCancelOffsetSetting: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteInputOffsetSetting(pInputOffsetSetting);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRtnOffsetSetting(CThostFtdcOffsetSettingField *pOffsetSetting)
{
	WriteLog(LogLevel::Info, "OnRtnOffsetSetting:");
	WriteOffsetSetting(pOffsetSetting);
}
void CThostFtdcTraderSpiMiddle::OnErrRtnOffsetSetting(CThostFtdcInputOffsetSettingField *pInputOffsetSetting, CThostFtdcRspInfoField *pRspInfo)
{
	WriteLog(LogLevel::Info, "OnErrRtnOffsetSetting:");
	WriteInputOffsetSetting(pInputOffsetSetting);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnErrRtnCancelOffsetSetting(CThostFtdcCancelOffsetSettingField *pCancelOffsetSetting, CThostFtdcRspInfoField *pRspInfo)
{
	WriteLog(LogLevel::Info, "OnErrRtnCancelOffsetSetting:");
	WriteCancelOffsetSetting(pCancelOffsetSetting);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcTraderSpiMiddle::OnRspQryOffsetSetting(CThostFtdcOffsetSettingField *pOffsetSetting, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryOffsetSetting: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteOffsetSetting(pOffsetSetting);
	WriteRspInfo(pRspInfo);
}
