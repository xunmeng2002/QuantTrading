#include "TradeSpiWrap.h"
#include "Encode.h"
#include <cstring>


void TradeSpiWrap::RegisterSpi(TradeCSpi* spi)
{
	m_TradeCSpi = spi;
}
void TradeSpiWrap::OnConnected()
{
	if (m_TradeCSpi != nullptr)
	{
		m_TradeCSpi->OnConnected();
	}
}
void TradeSpiWrap::OnDisConnected()
{
	if (m_TradeCSpi != nullptr)
	{
		m_TradeCSpi->OnDisConnected();
	}
}

void TradeSpiWrap::OnRspAccountLogin(RspAccountLoginField* rspAccountLogin, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
		m_TradeCSpi->OnRspAccountLogin(rspAccountLogin, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspAccountLogout(RspAccountLogoutField* rspAccountLogout, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
		m_TradeCSpi->OnRspAccountLogout(rspAccountLogout, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspQryHolderAccount(HolderAccountField* holderAccount, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
		m_TradeCSpi->OnRspQryHolderAccount(holderAccount, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspQryCapital(CapitalField* capital, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
		m_TradeCSpi->OnRspQryCapital(capital, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspQryPosition(PositionField* position, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
		m_TradeCSpi->OnRspQryPosition(position, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspQryOrder(OrderField* order, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
		m_TradeCSpi->OnRspQryOrder(order, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspQryTrade(TradeField* trade, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
		m_TradeCSpi->OnRspQryTrade(trade, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspQryInstrument(InstrumentField* instrument, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
		m_TradeCSpi->OnRspQryInstrument(instrument, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspQryOptionInstrument(OptionInstrumentField* optionInstrument, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
		m_TradeCSpi->OnRspQryOptionInstrument(optionInstrument, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspQryCommissionRate(CommissionRateField* commissionRate, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
		m_TradeCSpi->OnRspQryCommissionRate(commissionRate, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspQryMoneyTransfer(MoneyTransferField* moneyTransfer, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
		m_TradeCSpi->OnRspQryMoneyTransfer(moneyTransfer, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspInsertOrder(OrderField* order, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
		m_TradeCSpi->OnRspInsertOrder(order, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspCancelOrder(CancelOrderField* cancelOrder, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
		m_TradeCSpi->OnRspCancelOrder(cancelOrder, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRtnOrder(OrderField* order)
{
	if (m_TradeCSpi != nullptr)
	{
		m_TradeCSpi->OnRtnOrder(order);
	}
}
void TradeSpiWrap::OnRtnTrade(TradeField* trade)
{
	if (m_TradeCSpi != nullptr)
	{
		m_TradeCSpi->OnRtnTrade(trade);
	}
}
void TradeSpiWrap::OnRtnMoneyTransfer(MoneyTransferField* moneyTransfer)
{
	if (m_TradeCSpi != nullptr)
	{
		m_TradeCSpi->OnRtnMoneyTransfer(moneyTransfer);
	}
}
void TradeSpiWrap::OnRtnAccountLogout(AccountLogoutField* accountLogout)
{
	if (m_TradeCSpi != nullptr)
	{
		m_TradeCSpi->OnRtnAccountLogout(accountLogout);
	}
}
