// 本文件由 ../Templates/Cpp/Api/SpiWrap.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "SimExchangeSpiWrap.h"


namespace QuantTrading
{
void SimExchangeSpiWrap::RegisterSpi(SimExchangeCSpi* spi)
{
	simExchangeCSpi_ = spi;
}
void SimExchangeSpiWrap::OnConnected()
{
	if (simExchangeCSpi_ != nullptr)
	{
		simExchangeCSpi_->OnConnected();
	}
}
void SimExchangeSpiWrap::OnDisConnected()
{
	if (simExchangeCSpi_ != nullptr)
	{
		simExchangeCSpi_->OnDisConnected();
	}
}

void SimExchangeSpiWrap::OnRspAccountLogin(const RspAccountLoginField* rspAccountLogin, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (simExchangeCSpi_ != nullptr)
	{
		simExchangeCSpi_->OnRspAccountLogin(rspAccountLogin, rspInfo, requestId, isLast);
	}
}
void SimExchangeSpiWrap::OnRspAccountLogout(const RspAccountLogoutField* rspAccountLogout, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (simExchangeCSpi_ != nullptr)
	{
		simExchangeCSpi_->OnRspAccountLogout(rspAccountLogout, rspInfo, requestId, isLast);
	}
}
void SimExchangeSpiWrap::OnRspQryOrder(const OrderField* order, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (simExchangeCSpi_ != nullptr)
	{
		simExchangeCSpi_->OnRspQryOrder(order, rspInfo, requestId, isLast);
	}
}
void SimExchangeSpiWrap::OnRspQryTrade(const TradeField* trade, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (simExchangeCSpi_ != nullptr)
	{
		simExchangeCSpi_->OnRspQryTrade(trade, rspInfo, requestId, isLast);
	}
}
void SimExchangeSpiWrap::OnRspQryInstrument(const InstrumentField* instrument, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (simExchangeCSpi_ != nullptr)
	{
		simExchangeCSpi_->OnRspQryInstrument(instrument, rspInfo, requestId, isLast);
	}
}
void SimExchangeSpiWrap::OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (simExchangeCSpi_ != nullptr)
	{
		simExchangeCSpi_->OnRspInsertOrder(reqInsertOrder, rspInfo, requestId, isLast);
	}
}
void SimExchangeSpiWrap::OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (simExchangeCSpi_ != nullptr)
	{
		simExchangeCSpi_->OnRspCancelOrder(reqCancelOrder, rspInfo, requestId, isLast);
	}
}
void SimExchangeSpiWrap::OnRtnOrder(const OrderField* order)
{
	if (simExchangeCSpi_ != nullptr)
	{
		simExchangeCSpi_->OnRtnOrder(order);
	}
}
void SimExchangeSpiWrap::OnRtnTrade(const TradeField* trade)
{
	if (simExchangeCSpi_ != nullptr)
	{
		simExchangeCSpi_->OnRtnTrade(trade);
	}
}
}
