// 本文件由 ../Templates/Cpp/Api/SpiWrap.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdSpiWrap.h"


namespace quanttrading
{
void MdSpiWrap::RegisterSpi(MdCSpi* spi)
{
	mdCSpi = spi;
}
void MdSpiWrap::OnConnected()
{
	if (mdCSpi != nullptr)
	{
		mdCSpi->OnConnected();
	}
}
void MdSpiWrap::OnDisConnected()
{
	if (mdCSpi != nullptr)
	{
		mdCSpi->OnDisConnected();
	}
}

void MdSpiWrap::OnRspMdUserLogin(const RspMdUserLoginField* rspMdUserLogin, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (mdCSpi != nullptr)
	{
		mdCSpi->OnRspMdUserLogin(rspMdUserLogin, rspInfo, requestID, isLast);
	}
}
void MdSpiWrap::OnRspMdUserLogout(const RspMdUserLogoutField* rspMdUserLogout, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (mdCSpi != nullptr)
	{
		mdCSpi->OnRspMdUserLogout(rspMdUserLogout, rspInfo, requestID, isLast);
	}
}
void MdSpiWrap::OnRspSubMarketData(const RspSubMarketDataField* rspSubMarketData, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (mdCSpi != nullptr)
	{
		mdCSpi->OnRspSubMarketData(rspSubMarketData, rspInfo, requestID, isLast);
	}
}
void MdSpiWrap::OnRspUnSubMarketData(const RspUnSubMarketDataField* rspUnSubMarketData, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (mdCSpi != nullptr)
	{
		mdCSpi->OnRspUnSubMarketData(rspUnSubMarketData, rspInfo, requestID, isLast);
	}
}
void MdSpiWrap::OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData)
{
	if (mdCSpi != nullptr)
	{
		mdCSpi->OnRtnDepthMarketData(depthMarketData);
	}
}
void MdSpiWrap::OnRtnBarMarketData(const BarMarketDataField* barMarketData)
{
	if (mdCSpi != nullptr)
	{
		mdCSpi->OnRtnBarMarketData(barMarketData);
	}
}
}
