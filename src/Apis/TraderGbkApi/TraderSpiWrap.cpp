// 本文件由 ../Templates/Cpp/Api/SpiWrap.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "TraderSpiWrap.h"


namespace QuantTrading
{
void TraderSpiWrap::RegisterSpi(TraderCSpi* spi)
{
	traderCSpi_ = spi;
}
void TraderSpiWrap::OnConnected()
{
	if (traderCSpi_ != nullptr)
	{
		traderCSpi_->OnConnected();
	}
}
void TraderSpiWrap::OnDisConnected()
{
	if (traderCSpi_ != nullptr)
	{
		traderCSpi_->OnDisConnected();
	}
}

void TraderSpiWrap::OnRspAccountLogin(const RspAccountLoginField* rspAccountLogin, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (traderCSpi_ != nullptr)
	{
		traderCSpi_->OnRspAccountLogin(rspAccountLogin, rspInfo, requestId, isLast);
	}
}
void TraderSpiWrap::OnRspAccountLogout(const RspAccountLogoutField* rspAccountLogout, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (traderCSpi_ != nullptr)
	{
		traderCSpi_->OnRspAccountLogout(rspAccountLogout, rspInfo, requestId, isLast);
	}
}
void TraderSpiWrap::OnRspQryHolderAccount(const HolderAccountField* holderAccount, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (traderCSpi_ != nullptr)
	{
		traderCSpi_->OnRspQryHolderAccount(holderAccount, rspInfo, requestId, isLast);
	}
}
void TraderSpiWrap::OnRspQryCapital(const CapitalField* capital, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (traderCSpi_ != nullptr)
	{
		traderCSpi_->OnRspQryCapital(capital, rspInfo, requestId, isLast);
	}
}
void TraderSpiWrap::OnRspQryPosition(const PositionField* position, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (traderCSpi_ != nullptr)
	{
		traderCSpi_->OnRspQryPosition(position, rspInfo, requestId, isLast);
	}
}
void TraderSpiWrap::OnRspQryOrder(const OrderField* order, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (traderCSpi_ != nullptr)
	{
		traderCSpi_->OnRspQryOrder(order, rspInfo, requestId, isLast);
	}
}
void TraderSpiWrap::OnRspQryTrade(const TradeField* trade, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (traderCSpi_ != nullptr)
	{
		traderCSpi_->OnRspQryTrade(trade, rspInfo, requestId, isLast);
	}
}
void TraderSpiWrap::OnRspQryInstrument(const InstrumentField* instrument, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (traderCSpi_ != nullptr)
	{
		traderCSpi_->OnRspQryInstrument(instrument, rspInfo, requestId, isLast);
	}
}
void TraderSpiWrap::OnRspQryOptionInstrument(const OptionInstrumentField* optionInstrument, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (traderCSpi_ != nullptr)
	{
		traderCSpi_->OnRspQryOptionInstrument(optionInstrument, rspInfo, requestId, isLast);
	}
}
void TraderSpiWrap::OnRspQryCommissionRate(const CommissionRateField* commissionRate, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (traderCSpi_ != nullptr)
	{
		traderCSpi_->OnRspQryCommissionRate(commissionRate, rspInfo, requestId, isLast);
	}
}
void TraderSpiWrap::OnRspQryMoneyTransfer(const MoneyTransferField* moneyTransfer, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (traderCSpi_ != nullptr)
	{
		traderCSpi_->OnRspQryMoneyTransfer(moneyTransfer, rspInfo, requestId, isLast);
	}
}
void TraderSpiWrap::OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (traderCSpi_ != nullptr)
	{
		traderCSpi_->OnRspInsertOrder(reqInsertOrder, rspInfo, requestId, isLast);
	}
}
void TraderSpiWrap::OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestId, bool isLast)
{
	if (traderCSpi_ != nullptr)
	{
		traderCSpi_->OnRspCancelOrder(reqCancelOrder, rspInfo, requestId, isLast);
	}
}
void TraderSpiWrap::OnRtnOrder(const OrderField* order)
{
	if (traderCSpi_ != nullptr)
	{
		traderCSpi_->OnRtnOrder(order);
	}
}
void TraderSpiWrap::OnRtnTrade(const TradeField* trade)
{
	if (traderCSpi_ != nullptr)
	{
		traderCSpi_->OnRtnTrade(trade);
	}
}
void TraderSpiWrap::OnRtnMoneyTransfer(const MoneyTransferField* moneyTransfer)
{
	if (traderCSpi_ != nullptr)
	{
		traderCSpi_->OnRtnMoneyTransfer(moneyTransfer);
	}
}
void TraderSpiWrap::OnRtnAccountLogout(const AccountLogoutField* accountLogout)
{
	if (traderCSpi_ != nullptr)
	{
		traderCSpi_->OnRtnAccountLogout(accountLogout);
	}
}
}
