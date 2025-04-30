#include "MdSpiWrap.h"
#include "Encode.h"
#include <cstring>


void MdSpiWrap::RegisterSpi(MdCSpi* spi)
{
	m_MdCSpi = spi;
}
void MdSpiWrap::OnConnected()
{
	if (m_MdCSpi != nullptr)
	{
		m_MdCSpi->OnConnected();
	}
}
void MdSpiWrap::OnDisConnected()
{
	if (m_MdCSpi != nullptr)
	{
		m_MdCSpi->OnDisConnected();
	}
}

void MdSpiWrap::OnRspMdUserLogin(RspMdUserLoginField* rspMdUserLogin, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_MdCSpi != nullptr)
	{
#ifdef WINDOWS
		if (rspMdUserLogin != nullptr)
		{
			TrunsferUtf8ToGbk(rspMdUserLogin->UserID);
			TrunsferUtf8ToGbk(rspMdUserLogin->LoginDate);
			TrunsferUtf8ToGbk(rspMdUserLogin->LoginTime);
		}
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
#endif
		m_MdCSpi->OnRspMdUserLogin(rspMdUserLogin, rspInfo, requestID, isLast);
	}
}
void MdSpiWrap::OnRspMdUserLogout(RspMdUserLogoutField* rspMdUserLogout, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_MdCSpi != nullptr)
	{
#ifdef WINDOWS
		if (rspMdUserLogout != nullptr)
		{
			TrunsferUtf8ToGbk(rspMdUserLogout->UserID);
		}
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
#endif
		m_MdCSpi->OnRspMdUserLogout(rspMdUserLogout, rspInfo, requestID, isLast);
	}
}
void MdSpiWrap::OnRspSubMarketData(RspSubMarketDataField* rspSubMarketData, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_MdCSpi != nullptr)
	{
#ifdef WINDOWS
		if (rspSubMarketData != nullptr)
		{
			TrunsferUtf8ToGbk(rspSubMarketData->ExchangeID);
			TrunsferUtf8ToGbk(rspSubMarketData->InstrumentID);
		}
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
#endif
		m_MdCSpi->OnRspSubMarketData(rspSubMarketData, rspInfo, requestID, isLast);
	}
}
void MdSpiWrap::OnRspUnSubMarketData(RspUnSubMarketDataField* rspUnSubMarketData, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_MdCSpi != nullptr)
	{
#ifdef WINDOWS
		if (rspUnSubMarketData != nullptr)
		{
			TrunsferUtf8ToGbk(rspUnSubMarketData->ExchangeID);
			TrunsferUtf8ToGbk(rspUnSubMarketData->InstrumentID);
		}
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
#endif
		m_MdCSpi->OnRspUnSubMarketData(rspUnSubMarketData, rspInfo, requestID, isLast);
	}
}
void MdSpiWrap::OnRtnDepthMarketData(DepthMarketDataField* depthMarketData)
{
	if (m_MdCSpi != nullptr)
	{
#ifdef WINDOWS
		if (depthMarketData != nullptr)
		{
			TrunsferUtf8ToGbk(depthMarketData->TradingDay);
			TrunsferUtf8ToGbk(depthMarketData->ExchangeID);
			TrunsferUtf8ToGbk(depthMarketData->InstrumentID);
		}
#endif
		m_MdCSpi->OnRtnDepthMarketData(depthMarketData);
	}
}
void MdSpiWrap::OnRtnBarMarketData(BarMarketDataField* barMarketData)
{
	if (m_MdCSpi != nullptr)
	{
#ifdef WINDOWS
		if (barMarketData != nullptr)
		{
			TrunsferUtf8ToGbk(barMarketData->TradingDay);
			TrunsferUtf8ToGbk(barMarketData->ExchangeID);
			TrunsferUtf8ToGbk(barMarketData->InstrumentID);
		}
#endif
		m_MdCSpi->OnRtnBarMarketData(barMarketData);
	}
}
