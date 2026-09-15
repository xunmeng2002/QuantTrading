// 本文件由 ../Templates/Cpp/Api/SpiWrap.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "TraderSpiWrap.h"


namespace quanttrading
{
void TraderSpiWrap::RegisterSpi(TraderCSpi* spi)
{
	traderCSpi = spi;
}
void TraderSpiWrap::OnConnected()
{
	if (traderCSpi != nullptr)
	{
		traderCSpi->OnConnected();
	}
}
void TraderSpiWrap::OnDisConnected()
{
	if (traderCSpi != nullptr)
	{
		traderCSpi->OnDisConnected();
	}
}

void TraderSpiWrap::OnRspAccountLogin(const RspAccountLoginField* rspAccountLogin, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (traderCSpi != nullptr)
	{
		traderCSpi->OnRspAccountLogin(rspAccountLogin, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspAccountLogout(const RspAccountLogoutField* rspAccountLogout, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (traderCSpi != nullptr)
	{
		traderCSpi->OnRspAccountLogout(rspAccountLogout, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryHolderAccount(const HolderAccountField* holderAccount, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (traderCSpi != nullptr)
	{
		traderCSpi->OnRspQryHolderAccount(holderAccount, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryCapital(const CapitalField* capital, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (traderCSpi != nullptr)
	{
		traderCSpi->OnRspQryCapital(capital, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryPosition(const PositionField* position, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (traderCSpi != nullptr)
	{
		traderCSpi->OnRspQryPosition(position, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryOrder(const OrderField* order, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (traderCSpi != nullptr)
	{
		traderCSpi->OnRspQryOrder(order, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryTrade(const TradeField* trade, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (traderCSpi != nullptr)
	{
		traderCSpi->OnRspQryTrade(trade, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryInstrument(const InstrumentField* instrument, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (traderCSpi != nullptr)
	{
		traderCSpi->OnRspQryInstrument(instrument, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryOptionInstrument(const OptionInstrumentField* optionInstrument, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (traderCSpi != nullptr)
	{
		traderCSpi->OnRspQryOptionInstrument(optionInstrument, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryCommissionRate(const CommissionRateField* commissionRate, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (traderCSpi != nullptr)
	{
		traderCSpi->OnRspQryCommissionRate(commissionRate, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspQryMoneyTransfer(const MoneyTransferField* moneyTransfer, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (traderCSpi != nullptr)
	{
		traderCSpi->OnRspQryMoneyTransfer(moneyTransfer, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (traderCSpi != nullptr)
	{
		traderCSpi->OnRspInsertOrder(reqInsertOrder, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (traderCSpi != nullptr)
	{
		traderCSpi->OnRspCancelOrder(reqCancelOrder, rspInfo, requestID, isLast);
	}
}
void TraderSpiWrap::OnRtnOrder(const OrderField* order)
{
	if (traderCSpi != nullptr)
	{
		traderCSpi->OnRtnOrder(order);
	}
}
void TraderSpiWrap::OnRtnTrade(const TradeField* trade)
{
	if (traderCSpi != nullptr)
	{
		traderCSpi->OnRtnTrade(trade);
	}
}
void TraderSpiWrap::OnRtnMoneyTransfer(const MoneyTransferField* moneyTransfer)
{
	if (traderCSpi != nullptr)
	{
		traderCSpi->OnRtnMoneyTransfer(moneyTransfer);
	}
}
void TraderSpiWrap::OnRtnAccountLogout(const AccountLogoutField* accountLogout)
{
	if (traderCSpi != nullptr)
	{
		traderCSpi->OnRtnAccountLogout(accountLogout);
	}
}
}
