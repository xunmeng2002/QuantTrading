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

void SimExchangeSpiWrap::OnRspAccountLogin(const RspAccountLoginField* rspAccountLogin, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_SimExchangeCSpi != nullptr)
	{
		m_SimExchangeCSpi->OnRspAccountLogin(rspAccountLogin, rspInfo, requestID, isLast);
	}
}
void SimExchangeSpiWrap::OnRspAccountLogout(const RspAccountLogoutField* rspAccountLogout, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_SimExchangeCSpi != nullptr)
	{
		m_SimExchangeCSpi->OnRspAccountLogout(rspAccountLogout, rspInfo, requestID, isLast);
	}
}
void SimExchangeSpiWrap::OnRspQryOrder(const OrderField* order, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_SimExchangeCSpi != nullptr)
	{
		m_SimExchangeCSpi->OnRspQryOrder(order, rspInfo, requestID, isLast);
	}
}
void SimExchangeSpiWrap::OnRspQryTrade(const TradeField* trade, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_SimExchangeCSpi != nullptr)
	{
		m_SimExchangeCSpi->OnRspQryTrade(trade, rspInfo, requestID, isLast);
	}
}
void SimExchangeSpiWrap::OnRspQryInstrument(const InstrumentField* instrument, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_SimExchangeCSpi != nullptr)
	{
		m_SimExchangeCSpi->OnRspQryInstrument(instrument, rspInfo, requestID, isLast);
	}
}
void SimExchangeSpiWrap::OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_SimExchangeCSpi != nullptr)
	{
		m_SimExchangeCSpi->OnRspInsertOrder(reqInsertOrder, rspInfo, requestID, isLast);
	}
}
void SimExchangeSpiWrap::OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_SimExchangeCSpi != nullptr)
	{
		m_SimExchangeCSpi->OnRspCancelOrder(reqCancelOrder, rspInfo, requestID, isLast);
	}
}
void SimExchangeSpiWrap::OnRtnOrder(const OrderField* order)
{
	if (m_SimExchangeCSpi != nullptr)
	{
		m_SimExchangeCSpi->OnRtnOrder(order);
	}
}
void SimExchangeSpiWrap::OnRtnTrade(const TradeField* trade)
{
	if (m_SimExchangeCSpi != nullptr)
	{
		m_SimExchangeCSpi->OnRtnTrade(trade);
	}
}
}
