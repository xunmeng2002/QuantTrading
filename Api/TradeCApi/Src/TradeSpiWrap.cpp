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
#ifdef WINDOWS
		if (rspAccountLogin != nullptr)
		{
			TrunsferUtf8ToGbk(rspAccountLogin->AccountID);
			TrunsferUtf8ToGbk(rspAccountLogin->LoginDate);
			TrunsferUtf8ToGbk(rspAccountLogin->LoginTime);
		}
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
#endif
		m_TradeCSpi->OnRspAccountLogin(rspAccountLogin, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspAccountLogout(RspAccountLogoutField* rspAccountLogout, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
#ifdef WINDOWS
		if (rspAccountLogout != nullptr)
		{
			TrunsferUtf8ToGbk(rspAccountLogout->AccountID);
		}
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
#endif
		m_TradeCSpi->OnRspAccountLogout(rspAccountLogout, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspQryHolderAccount(HolderAccountField* holderAccount, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
#ifdef WINDOWS
		if (holderAccount != nullptr)
		{
			TrunsferUtf8ToGbk(holderAccount->ExchangeID);
			TrunsferUtf8ToGbk(holderAccount->HolderAccountID);
		}
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
#endif
		m_TradeCSpi->OnRspQryHolderAccount(holderAccount, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspQryCapital(CapitalField* capital, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
#ifdef WINDOWS
		if (capital != nullptr)
		{
			TrunsferUtf8ToGbk(capital->TradingDay);
			TrunsferUtf8ToGbk(capital->AccountID);
		}
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
#endif
		m_TradeCSpi->OnRspQryCapital(capital, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspQryPosition(PositionField* position, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
#ifdef WINDOWS
		if (position != nullptr)
		{
			TrunsferUtf8ToGbk(position->TradingDay);
			TrunsferUtf8ToGbk(position->AccountID);
			TrunsferUtf8ToGbk(position->ExchangeID);
			TrunsferUtf8ToGbk(position->InstrumentID);
		}
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
#endif
		m_TradeCSpi->OnRspQryPosition(position, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspQryOrder(OrderField* order, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
#ifdef WINDOWS
		if (order != nullptr)
		{
			TrunsferUtf8ToGbk(order->TradingDay);
			TrunsferUtf8ToGbk(order->AccountID);
			TrunsferUtf8ToGbk(order->ExchangeID);
			TrunsferUtf8ToGbk(order->InstrumentID);
			TrunsferUtf8ToGbk(order->OrderSysID);
			TrunsferUtf8ToGbk(order->StatusMsg);
			TrunsferUtf8ToGbk(order->OrderDate);
			TrunsferUtf8ToGbk(order->OrderTime);
			TrunsferUtf8ToGbk(order->CancelDate);
			TrunsferUtf8ToGbk(order->CancelTime);
		}
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
#endif
		m_TradeCSpi->OnRspQryOrder(order, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspQryTrade(TradeField* trade, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
#ifdef WINDOWS
		if (trade != nullptr)
		{
			TrunsferUtf8ToGbk(trade->TradingDay);
			TrunsferUtf8ToGbk(trade->AccountID);
			TrunsferUtf8ToGbk(trade->ExchangeID);
			TrunsferUtf8ToGbk(trade->InstrumentID);
			TrunsferUtf8ToGbk(trade->OrderSysID);
			TrunsferUtf8ToGbk(trade->TradeID);
			TrunsferUtf8ToGbk(trade->TradeDate);
			TrunsferUtf8ToGbk(trade->TradeTime);
		}
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
#endif
		m_TradeCSpi->OnRspQryTrade(trade, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspQryInstrument(InstrumentField* instrument, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
#ifdef WINDOWS
		if (instrument != nullptr)
		{
			TrunsferUtf8ToGbk(instrument->ExchangeID);
			TrunsferUtf8ToGbk(instrument->InstrumentID);
			TrunsferUtf8ToGbk(instrument->ExchangeInstID);
			TrunsferUtf8ToGbk(instrument->InstrumentName);
		}
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
#endif
		m_TradeCSpi->OnRspQryInstrument(instrument, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspQryOptionInstrument(OptionInstrumentField* optionInstrument, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
#ifdef WINDOWS
		if (optionInstrument != nullptr)
		{
			TrunsferUtf8ToGbk(optionInstrument->ExchangeID);
			TrunsferUtf8ToGbk(optionInstrument->InstrumentID);
			TrunsferUtf8ToGbk(optionInstrument->ExchangeInstID);
			TrunsferUtf8ToGbk(optionInstrument->InstrumentName);
			TrunsferUtf8ToGbk(optionInstrument->UnderlyingInstrumentID);
			TrunsferUtf8ToGbk(optionInstrument->ExpiringDate);
		}
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
#endif
		m_TradeCSpi->OnRspQryOptionInstrument(optionInstrument, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspQryCommissionRate(CommissionRateField* commissionRate, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
#ifdef WINDOWS
		if (commissionRate != nullptr)
		{
			TrunsferUtf8ToGbk(commissionRate->AccountID);
			TrunsferUtf8ToGbk(commissionRate->ExchangeID);
		}
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
#endif
		m_TradeCSpi->OnRspQryCommissionRate(commissionRate, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspQryMoneyTransfer(MoneyTransferField* moneyTransfer, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
#ifdef WINDOWS
		if (moneyTransfer != nullptr)
		{
			TrunsferUtf8ToGbk(moneyTransfer->TradingDay);
			TrunsferUtf8ToGbk(moneyTransfer->AccountID);
			TrunsferUtf8ToGbk(moneyTransfer->InfoMessage);
			TrunsferUtf8ToGbk(moneyTransfer->UserID);
			TrunsferUtf8ToGbk(moneyTransfer->TransferDate);
			TrunsferUtf8ToGbk(moneyTransfer->TransferTime);
		}
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
#endif
		m_TradeCSpi->OnRspQryMoneyTransfer(moneyTransfer, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspInsertOrder(OrderField* order, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
#ifdef WINDOWS
		if (order != nullptr)
		{
			TrunsferUtf8ToGbk(order->TradingDay);
			TrunsferUtf8ToGbk(order->AccountID);
			TrunsferUtf8ToGbk(order->ExchangeID);
			TrunsferUtf8ToGbk(order->InstrumentID);
			TrunsferUtf8ToGbk(order->OrderSysID);
			TrunsferUtf8ToGbk(order->StatusMsg);
			TrunsferUtf8ToGbk(order->OrderDate);
			TrunsferUtf8ToGbk(order->OrderTime);
			TrunsferUtf8ToGbk(order->CancelDate);
			TrunsferUtf8ToGbk(order->CancelTime);
		}
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
#endif
		m_TradeCSpi->OnRspInsertOrder(order, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRspCancelOrder(CancelOrderField* cancelOrder, RspInfoField* rspInfo, int requestID, bool isLast)
{
	if (m_TradeCSpi != nullptr)
	{
#ifdef WINDOWS
		if (cancelOrder != nullptr)
		{
			TrunsferUtf8ToGbk(cancelOrder->AccountID);
			TrunsferUtf8ToGbk(cancelOrder->ExchangeID);
			TrunsferUtf8ToGbk(cancelOrder->InstrumentID);
			TrunsferUtf8ToGbk(cancelOrder->OrderSysID);
		}
		if (rspInfo != nullptr)
		{
			TrunsferUtf8ToGbk(rspInfo->ErrorMsg);
		}
#endif
		m_TradeCSpi->OnRspCancelOrder(cancelOrder, rspInfo, requestID, isLast);
	}
}
void TradeSpiWrap::OnRtnOrder(OrderField* order)
{
	if (m_TradeCSpi != nullptr)
	{
#ifdef WINDOWS
		if (order != nullptr)
		{
			TrunsferUtf8ToGbk(order->TradingDay);
			TrunsferUtf8ToGbk(order->AccountID);
			TrunsferUtf8ToGbk(order->ExchangeID);
			TrunsferUtf8ToGbk(order->InstrumentID);
			TrunsferUtf8ToGbk(order->OrderSysID);
			TrunsferUtf8ToGbk(order->StatusMsg);
			TrunsferUtf8ToGbk(order->OrderDate);
			TrunsferUtf8ToGbk(order->OrderTime);
			TrunsferUtf8ToGbk(order->CancelDate);
			TrunsferUtf8ToGbk(order->CancelTime);
		}
#endif
		m_TradeCSpi->OnRtnOrder(order);
	}
}
void TradeSpiWrap::OnRtnTrade(TradeField* trade)
{
	if (m_TradeCSpi != nullptr)
	{
#ifdef WINDOWS
		if (trade != nullptr)
		{
			TrunsferUtf8ToGbk(trade->TradingDay);
			TrunsferUtf8ToGbk(trade->AccountID);
			TrunsferUtf8ToGbk(trade->ExchangeID);
			TrunsferUtf8ToGbk(trade->InstrumentID);
			TrunsferUtf8ToGbk(trade->OrderSysID);
			TrunsferUtf8ToGbk(trade->TradeID);
			TrunsferUtf8ToGbk(trade->TradeDate);
			TrunsferUtf8ToGbk(trade->TradeTime);
		}
#endif
		m_TradeCSpi->OnRtnTrade(trade);
	}
}
void TradeSpiWrap::OnRtnMoneyTransfer(MoneyTransferField* moneyTransfer)
{
	if (m_TradeCSpi != nullptr)
	{
#ifdef WINDOWS
		if (moneyTransfer != nullptr)
		{
			TrunsferUtf8ToGbk(moneyTransfer->TradingDay);
			TrunsferUtf8ToGbk(moneyTransfer->AccountID);
			TrunsferUtf8ToGbk(moneyTransfer->InfoMessage);
			TrunsferUtf8ToGbk(moneyTransfer->UserID);
			TrunsferUtf8ToGbk(moneyTransfer->TransferDate);
			TrunsferUtf8ToGbk(moneyTransfer->TransferTime);
		}
#endif
		m_TradeCSpi->OnRtnMoneyTransfer(moneyTransfer);
	}
}
void TradeSpiWrap::OnRtnAccountLogout(AccountLogoutField* accountLogout)
{
	if (m_TradeCSpi != nullptr)
	{
#ifdef WINDOWS
		if (accountLogout != nullptr)
		{
			TrunsferUtf8ToGbk(accountLogout->AccountID);
			TrunsferUtf8ToGbk(accountLogout->ErrorMsg);
		}
#endif
		m_TradeCSpi->OnRtnAccountLogout(accountLogout);
	}
}
