// 本文件由 ../Templates/Cpp/Api/SpiWrap.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdSpiWrap.h"


namespace QuantTrading
{
void MdSpiWrap::RegisterSpi(MdCSpi* spi)
{
	mdCSpi_ = spi;
}
void MdSpiWrap::OnConnected()
{
	if (mdCSpi_ != nullptr)
	{
		mdCSpi_->OnConnected();
	}
}
void MdSpiWrap::OnDisConnected()
{
	if (mdCSpi_ != nullptr)
	{
		mdCSpi_->OnDisConnected();
	}
}

void MdSpiWrap::OnRspMdUserLogin(const RspMdUserLoginField* rspMdUserLogin, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (mdCSpi_ != nullptr)
	{
		mdCSpi_->OnRspMdUserLogin(rspMdUserLogin, rspInfo, requestId, isLast);
	}
}
void MdSpiWrap::OnRspMdUserLogout(const RspMdUserLogoutField* rspMdUserLogout, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (mdCSpi_ != nullptr)
	{
		mdCSpi_->OnRspMdUserLogout(rspMdUserLogout, rspInfo, requestId, isLast);
	}
}
void MdSpiWrap::OnRspSubMarketData(const RspSubMarketDataField* rspSubMarketData, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (mdCSpi_ != nullptr)
	{
		mdCSpi_->OnRspSubMarketData(rspSubMarketData, rspInfo, requestId, isLast);
	}
}
void MdSpiWrap::OnRspUnSubMarketData(const RspUnSubMarketDataField* rspUnSubMarketData, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (mdCSpi_ != nullptr)
	{
		mdCSpi_->OnRspUnSubMarketData(rspUnSubMarketData, rspInfo, requestId, isLast);
	}
}
void MdSpiWrap::OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData)
{
	if (mdCSpi_ != nullptr)
	{
		mdCSpi_->OnRtnDepthMarketData(depthMarketData);
	}
}
void MdSpiWrap::OnRtnBarMarketData(const BarMarketDataField* barMarketData)
{
	if (mdCSpi_ != nullptr)
	{
		mdCSpi_->OnRtnBarMarketData(barMarketData);
	}
}
}
