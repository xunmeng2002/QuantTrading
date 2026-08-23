#include "SimExchangeSpiWrap.h"


namespace quanttrading
{
void SimExchangeSpiWrap::RegisterSpi(SimExchangeCSpi* spi)
{
	m_SimExchangeCSpi = spi;
}
void SimExchangeSpiWrap::OnConnected()
{
	if (m_SimExchangeCSpi != nullptr)
	{
		m_SimExchangeCSpi->OnConnected();
	}
}
void SimExchangeSpiWrap::OnDisConnected()
{
	if (m_SimExchangeCSpi != nullptr)
	{
		m_SimExchangeCSpi->OnDisConnected();
	}
}

void SimExchangeSpiWrap::OnRspAccountLogin(RspAccountLoginField* rspAccountLogin, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_SimExchangeCSpi != nullptr)
	{
		m_SimExchangeCSpi->OnRspAccountLogin(rspAccountLogin, rspInfo, requestID, isLast);
	}
}
void SimExchangeSpiWrap::OnRspAccountLogout(RspAccountLogoutField* rspAccountLogout, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_SimExchangeCSpi != nullptr)
	{
		m_SimExchangeCSpi->OnRspAccountLogout(rspAccountLogout, rspInfo, requestID, isLast);
	}
}
void SimExchangeSpiWrap::OnRspQryOrder(OrderField* order, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_SimExchangeCSpi != nullptr)
	{
		m_SimExchangeCSpi->OnRspQryOrder(order, rspInfo, requestID, isLast);
	}
}
void SimExchangeSpiWrap::OnRspQryTrade(TradeField* trade, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_SimExchangeCSpi != nullptr)
	{
		m_SimExchangeCSpi->OnRspQryTrade(trade, rspInfo, requestID, isLast);
	}
}
void SimExchangeSpiWrap::OnRspQryInstrument(InstrumentField* instrument, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_SimExchangeCSpi != nullptr)
	{
		m_SimExchangeCSpi->OnRspQryInstrument(instrument, rspInfo, requestID, isLast);
	}
}
void SimExchangeSpiWrap::OnRspInsertOrder(ReqInsertOrderField* reqInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_SimExchangeCSpi != nullptr)
	{
		m_SimExchangeCSpi->OnRspInsertOrder(reqInsertOrder, rspInfo, requestID, isLast);
	}
}
void SimExchangeSpiWrap::OnRspCancelOrder(ReqCancelOrderField* reqCancelOrder, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_SimExchangeCSpi != nullptr)
	{
		m_SimExchangeCSpi->OnRspCancelOrder(reqCancelOrder, rspInfo, requestID, isLast);
	}
}
void SimExchangeSpiWrap::OnRtnOrder(OrderField* order)
{
	if (m_SimExchangeCSpi != nullptr)
	{
		m_SimExchangeCSpi->OnRtnOrder(order);
	}
}
void SimExchangeSpiWrap::OnRtnTrade(TradeField* trade)
{
	if (m_SimExchangeCSpi != nullptr)
	{
		m_SimExchangeCSpi->OnRtnTrade(trade);
	}
}
}
