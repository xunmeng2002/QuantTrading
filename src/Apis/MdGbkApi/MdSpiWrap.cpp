#include "MdSpiWrap.h"


namespace quanttrading
{
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
		m_MdCSpi->OnRspMdUserLogin(rspMdUserLogin, rspInfo, requestID, isLast);
	}
}
void MdSpiWrap::OnRspMdUserLogout(RspMdUserLogoutField* rspMdUserLogout, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_MdCSpi != nullptr)
	{
		m_MdCSpi->OnRspMdUserLogout(rspMdUserLogout, rspInfo, requestID, isLast);
	}
}
void MdSpiWrap::OnRspSubMarketData(RspSubMarketDataField* rspSubMarketData, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_MdCSpi != nullptr)
	{
		m_MdCSpi->OnRspSubMarketData(rspSubMarketData, rspInfo, requestID, isLast);
	}
}
void MdSpiWrap::OnRspUnSubMarketData(RspUnSubMarketDataField* rspUnSubMarketData, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_MdCSpi != nullptr)
	{
		m_MdCSpi->OnRspUnSubMarketData(rspUnSubMarketData, rspInfo, requestID, isLast);
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
}
