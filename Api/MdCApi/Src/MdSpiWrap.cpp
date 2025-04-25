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

void MdSpiWrap::OnRspMdUserLogin(RspInfoField* rspInfo, RspMdUserLoginField* rspMdUserLogin, int requestID, bool isLast)
{
	if (m_MdCSpi != nullptr)
	{
#ifdef WINDOWS
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		if (rspMdUserLogin != nullptr)
		{
			TrunsferUtf8ToGbk(rspMdUserLogin->UserID);
			TrunsferUtf8ToGbk(rspMdUserLogin->LoginDate);
			TrunsferUtf8ToGbk(rspMdUserLogin->LoginTime);
		}
#endif
		m_MdCSpi->OnRspMdUserLogin(rspInfo, rspMdUserLogin, requestID, isLast);
	}
}
void MdSpiWrap::OnRspMdUserLogout(RspInfoField* rspInfo, RspMdUserLogoutField* rspMdUserLogout, int requestID, bool isLast)
{
	if (m_MdCSpi != nullptr)
	{
#ifdef WINDOWS
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		if (rspMdUserLogout != nullptr)
		{
			TrunsferUtf8ToGbk(rspMdUserLogout->UserID);
		}
#endif
		m_MdCSpi->OnRspMdUserLogout(rspInfo, rspMdUserLogout, requestID, isLast);
	}
}
void MdSpiWrap::OnRspSubMarketData(RspInfoField* rspInfo, RspSubMarketDataField* rspSubMarketData, int requestID, bool isLast)
{
	if (m_MdCSpi != nullptr)
	{
#ifdef WINDOWS
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		if (rspSubMarketData != nullptr)
		{
			TrunsferUtf8ToGbk(rspSubMarketData->ExchangeID);
			TrunsferUtf8ToGbk(rspSubMarketData->InstrumentID);
		}
#endif
		m_MdCSpi->OnRspSubMarketData(rspInfo, rspSubMarketData, requestID, isLast);
	}
}
void MdSpiWrap::OnRspUnSubMarketData(RspInfoField* rspInfo, RspUnSubMarketDataField* rspUnSubMarketData, int requestID, bool isLast)
{
	if (m_MdCSpi != nullptr)
	{
#ifdef WINDOWS
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
		if (rspUnSubMarketData != nullptr)
		{
			TrunsferUtf8ToGbk(rspUnSubMarketData->ExchangeID);
			TrunsferUtf8ToGbk(rspUnSubMarketData->InstrumentID);
		}
#endif
		m_MdCSpi->OnRspUnSubMarketData(rspInfo, rspUnSubMarketData, requestID, isLast);
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
