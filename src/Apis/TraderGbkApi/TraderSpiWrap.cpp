#include "TraderSpiWrap.h"


namespace quanttrading
{
void TraderSpiWrap::RegisterSpi(TraderCSpi* spi)
{
	m_TraderCSpi = spi;
}
void TraderSpiWrap::OnConnected()
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnConnected();
	}
}
void TraderSpiWrap::OnDisConnected()
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnDisConnected();
	}
}

void TraderSpiWrap::OnRspAccountLogin(const RspAccountLoginField* rspAccountLogin, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspAccountLogin(rspAccountLogin, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspAccountLogout(const RspAccountLogoutField* rspAccountLogout, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspAccountLogout(rspAccountLogout, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryHolderAccount(const HolderAccountField* holderAccount, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspQryHolderAccount(holderAccount, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryCapital(const CapitalField* capital, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspQryCapital(capital, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryPosition(const PositionField* position, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspQryPosition(position, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryOrder(const OrderField* order, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspQryOrder(order, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryTrade(const TradeField* trade, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspQryTrade(trade, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryInstrument(const InstrumentField* instrument, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspQryInstrument(instrument, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryOptionInstrument(const OptionInstrumentField* optionInstrument, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspQryOptionInstrument(optionInstrument, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryCommissionRate(const CommissionRateField* commissionRate, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspQryCommissionRate(commissionRate, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryMoneyTransfer(const MoneyTransferField* moneyTransfer, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspQryMoneyTransfer(moneyTransfer, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspInsertOrder(reqInsertOrder, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspCancelOrder(reqCancelOrder, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRtnOrder(const OrderField* order)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRtnOrder(order);
	}
}
void TraderSpiWrap::OnRtnTrade(const TradeField* trade)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRtnTrade(trade);
	}
}
void TraderSpiWrap::OnRtnMoneyTransfer(const MoneyTransferField* moneyTransfer)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRtnMoneyTransfer(moneyTransfer);
	}
}
void TraderSpiWrap::OnRtnAccountLogout(const AccountLogoutField* accountLogout)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRtnAccountLogout(accountLogout);
	}
}
}
