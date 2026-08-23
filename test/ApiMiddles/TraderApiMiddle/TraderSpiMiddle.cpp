#include "TraderSpiMiddle.h"
#include <Spark/Core/Logger/Logger.h>

using namespace spark::core;

namespace quanttrading
{
double GetDoubleValue(const double& value)
{
    if (value == std::numeric_limits<double>::max())
    {
        return 0.0;
    }
    return value;
}


void TraderSpiMiddle::OnConnected()
{
	WriteLog(LogLevel::Info, "OnConnected:");
}
void TraderSpiMiddle::OnDisConnected()
{
	WriteLog(LogLevel::Info, "OnDisConnected");
}

void TraderSpiMiddle::OnRspAccountLogin(RspAccountLoginField* rspAccountLogin, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspAccountLogin: RequestID:%d, IsLast:%d", requestID, isLast);
	if (rspAccountLogin != nullptr)
	{
		WriteLog(LogLevel::Info, "RspAccountLoginField:AccountID:[%s], LoginDate:[%s], LoginTime:[%s], SessionID:[%lld]",
			rspAccountLogin->AccountID, rspAccountLogin->LoginDate, rspAccountLogin->LoginTime, rspAccountLogin->SessionID);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspAccountLogin is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspAccountLogout(RspAccountLogoutField* rspAccountLogout, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspAccountLogout: RequestID:%d, IsLast:%d", requestID, isLast);
	if (rspAccountLogout != nullptr)
	{
		WriteLog(LogLevel::Info, "RspAccountLogoutField:AccountID:[%s]",
			rspAccountLogout->AccountID);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspAccountLogout is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspQryHolderAccount(HolderAccountField* holderAccount, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryHolderAccount: RequestID:%d, IsLast:%d", requestID, isLast);
	if (holderAccount != nullptr)
	{
		WriteLog(LogLevel::Info, "HolderAccountField:ExchangeID:[%s], HolderAccountID:[%s], PrimaryFlag:[%d]",
			holderAccount->ExchangeID, holderAccount->HolderAccountID, holderAccount->PrimaryFlag);
	}
	else
	{
		WriteLog(LogLevel::Info, "holderAccount is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspQryCapital(CapitalField* capital, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryCapital: RequestID:%d, IsLast:%d", requestID, isLast);
	if (capital != nullptr)
	{
		WriteLog(LogLevel::Info, "CapitalField:TradingDay:[%s], AccountID:[%s], AccountType:[%d], Balance:[%f], PreBalance:[%f], Available:[%f], MarketValue:[%f], CashIn:[%f], CashOut:[%f], Margin:[%f], Commission:[%f], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f], CloseProfitByDate:[%f], CloseProfitByTrade:[%f], PositionProfitByDate:[%f], PositionProfitByTrade:[%f], Deposit:[%f], Withdraw:[%f]",
			capital->TradingDay, capital->AccountID, (int)capital->AccountType, GetDoubleValue(capital->Balance), GetDoubleValue(capital->PreBalance), GetDoubleValue(capital->Available), GetDoubleValue(capital->MarketValue), GetDoubleValue(capital->CashIn), GetDoubleValue(capital->CashOut), GetDoubleValue(capital->Margin), GetDoubleValue(capital->Commission), GetDoubleValue(capital->FrozenCash), GetDoubleValue(capital->FrozenMargin), GetDoubleValue(capital->FrozenCommission), GetDoubleValue(capital->CloseProfitByDate), GetDoubleValue(capital->CloseProfitByTrade), GetDoubleValue(capital->PositionProfitByDate), GetDoubleValue(capital->PositionProfitByTrade), GetDoubleValue(capital->Deposit), GetDoubleValue(capital->Withdraw));
	}
	else
	{
		WriteLog(LogLevel::Info, "capital is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspQryPosition(PositionField* position, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryPosition: RequestID:%d, IsLast:%d", requestID, isLast);
	if (position != nullptr)
	{
		WriteLog(LogLevel::Info, "PositionField:TradingDay:[%s], AccountID:[%s], AccountType:[%d], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], PosiDirection:[%d], TotalPosition:[%lld], PositionFrozen:[%lld], TodayPosition:[%lld], MarketValue:[%f], CashIn:[%f], CashOut:[%f], Margin:[%f], Commission:[%f], VolumeMultiple:[%d], CloseProfitByDate:[%f], CloseProfitByTrade:[%f], PositionProfitByDate:[%f], PositionProfitByTrade:[%f], LastPrice:[%f], PreSettlementPrice:[%f]",
			position->TradingDay, position->AccountID, (int)position->AccountType, position->ExchangeID, position->InstrumentID, (int)position->ProductClass, (int)position->PosiDirection, position->TotalPosition, position->PositionFrozen, position->TodayPosition, GetDoubleValue(position->MarketValue), GetDoubleValue(position->CashIn), GetDoubleValue(position->CashOut), GetDoubleValue(position->Margin), GetDoubleValue(position->Commission), position->VolumeMultiple, GetDoubleValue(position->CloseProfitByDate), GetDoubleValue(position->CloseProfitByTrade), GetDoubleValue(position->PositionProfitByDate), GetDoubleValue(position->PositionProfitByTrade), GetDoubleValue(position->LastPrice), GetDoubleValue(position->PreSettlementPrice));
	}
	else
	{
		WriteLog(LogLevel::Info, "position is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspQryOrder(OrderField* order, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryOrder: RequestID:%d, IsLast:%d", requestID, isLast);
	if (order != nullptr)
	{
		WriteLog(LogLevel::Info, "OrderField:TradingDay:[%s], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], OrderSysID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], VolumeTotal:[%lld], VolumeTraded:[%lld], VolumeMultiple:[%d], OrderStatus:[%d], OrderDate:[%s], OrderTime:[%s], CancelDate:[%s], CancelTime:[%s], SessionID:[%lld], ClientOrderID:[%d], RequestID:[%d], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f]",
			order->TradingDay, order->AccountID, order->ExchangeID, order->InstrumentID, (int)order->ProductClass, order->OrderID, order->OrderSysID, (int)order->Direction, (int)order->OffsetFlag, (int)order->OrderPriceType, GetDoubleValue(order->Price), order->Volume, order->VolumeTotal, order->VolumeTraded, order->VolumeMultiple, (int)order->OrderStatus, order->OrderDate, order->OrderTime, order->CancelDate, order->CancelTime, order->SessionID, order->ClientOrderID, order->RequestID, GetDoubleValue(order->FrozenCash), GetDoubleValue(order->FrozenMargin), GetDoubleValue(order->FrozenCommission));
	}
	else
	{
		WriteLog(LogLevel::Info, "order is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspQryTrade(TradeField* trade, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryTrade: RequestID:%d, IsLast:%d", requestID, isLast);
	if (trade != nullptr)
	{
		WriteLog(LogLevel::Info, "TradeField:TradingDay:[%s], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], OrderSysID:[%s], TradeID:[%s], Direction:[%d], OffsetFlag:[%d], Price:[%f], Volume:[%lld], VolumeMultiple:[%d], TradeAmount:[%f], Commission:[%f], TradeDate:[%s], TradeTime:[%s]",
			trade->TradingDay, trade->AccountID, trade->ExchangeID, trade->InstrumentID, (int)trade->ProductClass, trade->OrderID, trade->OrderSysID, trade->TradeID, (int)trade->Direction, (int)trade->OffsetFlag, GetDoubleValue(trade->Price), trade->Volume, trade->VolumeMultiple, GetDoubleValue(trade->TradeAmount), GetDoubleValue(trade->Commission), trade->TradeDate, trade->TradeTime);
	}
	else
	{
		WriteLog(LogLevel::Info, "trade is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspQryInstrument(InstrumentField* instrument, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryInstrument: RequestID:%d, IsLast:%d", requestID, isLast);
	if (instrument != nullptr)
	{
		WriteLog(LogLevel::Info, "InstrumentField:ExchangeID:[%s], InstrumentID:[%s], ExchangeInstID:[%s], InstrumentName:[%s], ProductID:[%s], ProductClass:[%d], VolumeMultiple:[%d], PriceTick:[%f], MaxMarketOrderVolume:[%lld], MinMarketOrderVolume:[%lld], MaxLimitOrderVolume:[%lld], MinLimitOrderVolume:[%lld], SessionName:[%s]",
			instrument->ExchangeID, instrument->InstrumentID, instrument->ExchangeInstID, instrument->InstrumentName, instrument->ProductID, (int)instrument->ProductClass, instrument->VolumeMultiple, GetDoubleValue(instrument->PriceTick), instrument->MaxMarketOrderVolume, instrument->MinMarketOrderVolume, instrument->MaxLimitOrderVolume, instrument->MinLimitOrderVolume, instrument->SessionName);
	}
	else
	{
		WriteLog(LogLevel::Info, "instrument is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspQryOptionInstrument(OptionInstrumentField* optionInstrument, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryOptionInstrument: RequestID:%d, IsLast:%d", requestID, isLast);
	if (optionInstrument != nullptr)
	{
		WriteLog(LogLevel::Info, "OptionInstrumentField:ExchangeID:[%s], InstrumentID:[%s], ExchangeInstID:[%s], InstrumentName:[%s], VolumeMultiple:[%d], OptionType:[%d], UnderlyingInstrumentID:[%s], ExecutePrice:[%f], UnitMargin:[%f], PriceTick:[%f], MaxLimitOrderVolume:[%lld], MaxMarketOrderVolume:[%lld], ExpiringDate:[%s]",
			optionInstrument->ExchangeID, optionInstrument->InstrumentID, optionInstrument->ExchangeInstID, optionInstrument->InstrumentName, optionInstrument->VolumeMultiple, (int)optionInstrument->OptionType, optionInstrument->UnderlyingInstrumentID, GetDoubleValue(optionInstrument->ExecutePrice), GetDoubleValue(optionInstrument->UnitMargin), GetDoubleValue(optionInstrument->PriceTick), optionInstrument->MaxLimitOrderVolume, optionInstrument->MaxMarketOrderVolume, optionInstrument->ExpiringDate);
	}
	else
	{
		WriteLog(LogLevel::Info, "optionInstrument is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspQryCommissionRate(CommissionRateField* commissionRate, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryCommissionRate: RequestID:%d, IsLast:%d", requestID, isLast);
	if (commissionRate != nullptr)
	{
		WriteLog(LogLevel::Info, "CommissionRateField:AccountID:[%s], ExchangeID:[%s], ProductClass:[%d], OpenBuyByMoney:[%f], OpenSellByMoney:[%f], CloseBuyByMoney:[%f], CloseSellByMoney:[%f], OpenBuyByVolume:[%f], OpenSellByVolume:[%f], CloseBuyByVolume:[%f], CloseSellByVolume:[%f], MinCommission:[%f], MaxCommission:[%f]",
			commissionRate->AccountID, commissionRate->ExchangeID, (int)commissionRate->ProductClass, GetDoubleValue(commissionRate->OpenBuyByMoney), GetDoubleValue(commissionRate->OpenSellByMoney), GetDoubleValue(commissionRate->CloseBuyByMoney), GetDoubleValue(commissionRate->CloseSellByMoney), GetDoubleValue(commissionRate->OpenBuyByVolume), GetDoubleValue(commissionRate->OpenSellByVolume), GetDoubleValue(commissionRate->CloseBuyByVolume), GetDoubleValue(commissionRate->CloseSellByVolume), GetDoubleValue(commissionRate->MinCommission), GetDoubleValue(commissionRate->MaxCommission));
	}
	else
	{
		WriteLog(LogLevel::Info, "commissionRate is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspQryMoneyTransfer(MoneyTransferField* moneyTransfer, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryMoneyTransfer: RequestID:%d, IsLast:%d", requestID, isLast);
	if (moneyTransfer != nullptr)
	{
		WriteLog(LogLevel::Info, "MoneyTransferField:TradingDay:[%s], AccountID:[%s], MoneyTransferID:[%d], AccountType:[%d], TransferDirection:[%d], TransferAmount:[%f], InfoMessage:[%s], UserID:[%s], TransferDate:[%s], TransferTime:[%s]",
			moneyTransfer->TradingDay, moneyTransfer->AccountID, moneyTransfer->MoneyTransferID, (int)moneyTransfer->AccountType, (int)moneyTransfer->TransferDirection, GetDoubleValue(moneyTransfer->TransferAmount), moneyTransfer->InfoMessage, moneyTransfer->UserID, moneyTransfer->TransferDate, moneyTransfer->TransferTime);
	}
	else
	{
		WriteLog(LogLevel::Info, "moneyTransfer is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspInsertOrder(ReqInsertOrderField* reqInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspInsertOrder: RequestID:%d, IsLast:%d", requestID, isLast);
	if (reqInsertOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqInsertOrderField:AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], ClientOrderID:[%d]",
			reqInsertOrder->AccountID, reqInsertOrder->ExchangeID, reqInsertOrder->InstrumentID, (int)reqInsertOrder->Direction, (int)reqInsertOrder->OffsetFlag, (int)reqInsertOrder->OrderPriceType, GetDoubleValue(reqInsertOrder->Price), reqInsertOrder->Volume, reqInsertOrder->ClientOrderID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqInsertOrder is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspCancelOrder(ReqCancelOrderField* reqCancelOrder, RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspCancelOrder: RequestID:%d, IsLast:%d", requestID, isLast);
	if (reqCancelOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqCancelOrderField:AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ClientCancelOrderID:[%d], OrderID:[%d], OrderSysID:[%s], SessionID:[%lld], ClientOrderID:[%d]",
			reqCancelOrder->AccountID, reqCancelOrder->ExchangeID, reqCancelOrder->InstrumentID, reqCancelOrder->ClientCancelOrderID, reqCancelOrder->OrderID, reqCancelOrder->OrderSysID, reqCancelOrder->SessionID, reqCancelOrder->ClientOrderID);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqCancelOrder is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorID:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorID, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRtnOrder(OrderField* order)
{
	WriteLog(LogLevel::Info, "OnRtnOrder");
	if (order != nullptr)
	{
		WriteLog(LogLevel::Info, "OrderField:TradingDay:[%s], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], OrderSysID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], VolumeTotal:[%lld], VolumeTraded:[%lld], VolumeMultiple:[%d], OrderStatus:[%d], OrderDate:[%s], OrderTime:[%s], CancelDate:[%s], CancelTime:[%s], SessionID:[%lld], ClientOrderID:[%d], RequestID:[%d], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f]",
			order->TradingDay, order->AccountID, order->ExchangeID, order->InstrumentID, (int)order->ProductClass, order->OrderID, order->OrderSysID, (int)order->Direction, (int)order->OffsetFlag, (int)order->OrderPriceType, GetDoubleValue(order->Price), order->Volume, order->VolumeTotal, order->VolumeTraded, order->VolumeMultiple, (int)order->OrderStatus, order->OrderDate, order->OrderTime, order->CancelDate, order->CancelTime, order->SessionID, order->ClientOrderID, order->RequestID, GetDoubleValue(order->FrozenCash), GetDoubleValue(order->FrozenMargin), GetDoubleValue(order->FrozenCommission));
	}
	else
	{
		WriteLog(LogLevel::Info, "order is nullptr");
	}
}
void TraderSpiMiddle::OnRtnTrade(TradeField* trade)
{
	WriteLog(LogLevel::Info, "OnRtnTrade");
	if (trade != nullptr)
	{
		WriteLog(LogLevel::Info, "TradeField:TradingDay:[%s], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], OrderSysID:[%s], TradeID:[%s], Direction:[%d], OffsetFlag:[%d], Price:[%f], Volume:[%lld], VolumeMultiple:[%d], TradeAmount:[%f], Commission:[%f], TradeDate:[%s], TradeTime:[%s]",
			trade->TradingDay, trade->AccountID, trade->ExchangeID, trade->InstrumentID, (int)trade->ProductClass, trade->OrderID, trade->OrderSysID, trade->TradeID, (int)trade->Direction, (int)trade->OffsetFlag, GetDoubleValue(trade->Price), trade->Volume, trade->VolumeMultiple, GetDoubleValue(trade->TradeAmount), GetDoubleValue(trade->Commission), trade->TradeDate, trade->TradeTime);
	}
	else
	{
		WriteLog(LogLevel::Info, "trade is nullptr");
	}
}
void TraderSpiMiddle::OnRtnMoneyTransfer(MoneyTransferField* moneyTransfer)
{
	WriteLog(LogLevel::Info, "OnRtnMoneyTransfer");
	if (moneyTransfer != nullptr)
	{
		WriteLog(LogLevel::Info, "MoneyTransferField:TradingDay:[%s], AccountID:[%s], MoneyTransferID:[%d], AccountType:[%d], TransferDirection:[%d], TransferAmount:[%f], InfoMessage:[%s], UserID:[%s], TransferDate:[%s], TransferTime:[%s]",
			moneyTransfer->TradingDay, moneyTransfer->AccountID, moneyTransfer->MoneyTransferID, (int)moneyTransfer->AccountType, (int)moneyTransfer->TransferDirection, GetDoubleValue(moneyTransfer->TransferAmount), moneyTransfer->InfoMessage, moneyTransfer->UserID, moneyTransfer->TransferDate, moneyTransfer->TransferTime);
	}
	else
	{
		WriteLog(LogLevel::Info, "moneyTransfer is nullptr");
	}
}
void TraderSpiMiddle::OnRtnAccountLogout(AccountLogoutField* accountLogout)
{
	WriteLog(LogLevel::Info, "OnRtnAccountLogout");
	if (accountLogout != nullptr)
	{
		WriteLog(LogLevel::Info, "AccountLogoutField:AccountID:[%s], ErrorID:[%d], ErrorMsg:[%s]",
			accountLogout->AccountID, accountLogout->ErrorID, accountLogout->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "accountLogout is nullptr");
	}
}
}
