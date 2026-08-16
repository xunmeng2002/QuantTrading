#include "TraderSpiWrap.h"


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

void TraderSpiWrap::OnRspAccountLogin(RspAccountLoginField* rspAccountLogin, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspAccountLogin(rspAccountLogin, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspAccountLogout(RspAccountLogoutField* rspAccountLogout, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspAccountLogout(rspAccountLogout, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryHolderAccount(HolderAccountField* holderAccount, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspQryHolderAccount(holderAccount, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryCapital(CapitalField* capital, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspQryCapital(capital, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryPosition(PositionField* position, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspQryPosition(position, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryOrder(OrderField* order, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspQryOrder(order, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryTrade(TradeField* trade, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspQryTrade(trade, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryInstrument(InstrumentField* instrument, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspQryInstrument(instrument, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryOptionInstrument(OptionInstrumentField* optionInstrument, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspQryOptionInstrument(optionInstrument, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryCommissionRate(CommissionRateField* commissionRate, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspQryCommissionRate(commissionRate, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryMoneyTransfer(MoneyTransferField* moneyTransfer, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspQryMoneyTransfer(moneyTransfer, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspInsertOrder(ReqInsertOrderField* reqInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspInsertOrder(reqInsertOrder, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspCancelOrder(ReqCancelOrderField* reqCancelOrder, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRspCancelOrder(reqCancelOrder, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRtnOrder(OrderField* order)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRtnOrder(order);
	}
}
void TraderSpiWrap::OnRtnTrade(TradeField* trade)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRtnTrade(trade);
	}
}
void TraderSpiWrap::OnRtnMoneyTransfer(MoneyTransferField* moneyTransfer)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRtnMoneyTransfer(moneyTransfer);
	}
}
void TraderSpiWrap::OnRtnAccountLogout(AccountLogoutField* accountLogout)
{
	if (m_TraderCSpi != nullptr)
	{
		m_TraderCSpi->OnRtnAccountLogout(accountLogout);
	}
}
