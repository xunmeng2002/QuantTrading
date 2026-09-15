// 本文件由 ../Templates/Cpp/Api/SpiWrap.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "SimExchangeSpiWrap.h"


namespace quanttrading
{
void SimExchangeSpiWrap::RegisterSpi(SimExchangeCSpi* spi)
{
	simExchangeCSpi = spi;
}
void SimExchangeSpiWrap::OnConnected()
{
	if (simExchangeCSpi != nullptr)
	{
		simExchangeCSpi->OnConnected();
	}
}
void SimExchangeSpiWrap::OnDisConnected()
{
	if (simExchangeCSpi != nullptr)
	{
		simExchangeCSpi->OnDisConnected();
	}
}

void SimExchangeSpiWrap::OnRspAccountLogin(const RspAccountLoginField* rspAccountLogin, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (simExchangeCSpi != nullptr)
	{
		simExchangeCSpi->OnRspAccountLogin(rspAccountLogin, rspInfo, requestID, isLast);
	}
}
void SimExchangeSpiWrap::OnRspAccountLogout(const RspAccountLogoutField* rspAccountLogout, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (simExchangeCSpi != nullptr)
	{
		simExchangeCSpi->OnRspAccountLogout(rspAccountLogout, rspInfo, requestID, isLast);
	}
}
void SimExchangeSpiWrap::OnRspQryOrder(const OrderField* order, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (simExchangeCSpi != nullptr)
	{
		simExchangeCSpi->OnRspQryOrder(order, rspInfo, requestID, isLast);
	}
}
void SimExchangeSpiWrap::OnRspQryTrade(const TradeField* trade, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (simExchangeCSpi != nullptr)
	{
		simExchangeCSpi->OnRspQryTrade(trade, rspInfo, requestID, isLast);
	}
}
void SimExchangeSpiWrap::OnRspQryInstrument(const InstrumentField* instrument, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (simExchangeCSpi != nullptr)
	{
		simExchangeCSpi->OnRspQryInstrument(instrument, rspInfo, requestID, isLast);
	}
}
void SimExchangeSpiWrap::OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (simExchangeCSpi != nullptr)
	{
		simExchangeCSpi->OnRspInsertOrder(reqInsertOrder, rspInfo, requestID, isLast);
	}
}
void SimExchangeSpiWrap::OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (simExchangeCSpi != nullptr)
	{
		simExchangeCSpi->OnRspCancelOrder(reqCancelOrder, rspInfo, requestID, isLast);
	}
}
void SimExchangeSpiWrap::OnRtnOrder(const OrderField* order)
{
	if (simExchangeCSpi != nullptr)
	{
		simExchangeCSpi->OnRtnOrder(order);
	}
}
void SimExchangeSpiWrap::OnRtnTrade(const TradeField* trade)
{
	if (simExchangeCSpi != nullptr)
	{
		simExchangeCSpi->OnRtnTrade(trade);
	}
}
}
