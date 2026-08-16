#include "ThostFtdcMdSpiMiddle.h"
#include "StructLogFunc.h"
#include <Spark/Core/Logger/Logger.h>



void CThostFtdcMdSpiMiddle::OnFrontConnected()
{
	WriteLog(LogLevel::Info, "OnFrontConnected:");
}
void CThostFtdcMdSpiMiddle::OnFrontDisconnected(int nReason)
{
	WriteLog(LogLevel::Info, "OnFrontDisconnected: nReason[%d]", nReason);
}
void CThostFtdcMdSpiMiddle::OnHeartBeatWarning(int nTimeLapse)
{
	WriteLog(LogLevel::Info, "OnHeartBeatWarning: nTimeLapse[%d]", nTimeLapse);
}
void CThostFtdcMdSpiMiddle::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspUserLogin: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRspUserLogin(pRspUserLogin);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcMdSpiMiddle::OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspUserLogout: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteUserLogout(pUserLogout);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcMdSpiMiddle::OnRspQryMulticastInstrument(CThostFtdcMulticastInstrumentField *pMulticastInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspQryMulticastInstrument: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteMulticastInstrument(pMulticastInstrument);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcMdSpiMiddle::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspError: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcMdSpiMiddle::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspSubMarketData: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSpecificInstrument(pSpecificInstrument);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcMdSpiMiddle::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspUnSubMarketData: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSpecificInstrument(pSpecificInstrument);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcMdSpiMiddle::OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspSubForQuoteRsp: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSpecificInstrument(pSpecificInstrument);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcMdSpiMiddle::OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	WriteLog(LogLevel::Info, "OnRspUnSubForQuoteRsp: nRequestID[%d] bIsLast[%d]", nRequestID, bIsLast);
	WriteSpecificInstrument(pSpecificInstrument);
	WriteRspInfo(pRspInfo);
}
void CThostFtdcMdSpiMiddle::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	WriteLog(LogLevel::Info, "OnRtnDepthMarketData:");
	WriteDepthMarketData(pDepthMarketData);
}
void CThostFtdcMdSpiMiddle::OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp)
{
	WriteLog(LogLevel::Info, "OnRtnForQuoteRsp:");
	WriteForQuoteRsp(pForQuoteRsp);
}
