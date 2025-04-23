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
		m_MdCSpi->OnRspMdUserLogin(rspInfo, rspMdUserLogin, requestID, isLast);
	}
}
void MdSpiWrap::OnRspSubMarketData(RspInfoField* rspInfo, RspSubMarketDataField* rspSubMarketData, int requestID, bool isLast)
{
	if (m_MdCSpi != nullptr)
	{
		m_MdCSpi->OnRspSubMarketData(rspInfo, rspSubMarketData, requestID, isLast);
	}
}
void MdSpiWrap::OnRspUnSubMarketData(RspInfoField* rspInfo, RspUnSubMarketDataField* rspUnSubMarketData, int requestID, bool isLast)
{
	if (m_MdCSpi != nullptr)
	{
		m_MdCSpi->OnRspUnSubMarketData(rspInfo, rspUnSubMarketData, requestID, isLast);
	}
}
void MdSpiWrap::OnRtnDepthMarketData(DepthMarketDataField* depthMarketData)
{
	if (m_MdCSpi != nullptr)
	{
		m_MdCSpi->OnRtnDepthMarketData(depthMarketData);
	}
}
void MdSpiWrap::OnRtnBarMarketData(BarMarketDataField* barMarketData)
{
	if (m_MdCSpi != nullptr)
	{
		m_MdCSpi->OnRtnBarMarketData(barMarketData);
	}
}
