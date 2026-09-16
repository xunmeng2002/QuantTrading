// 本文件由 ../Templates/Cpp/ApiTest/SpiMiddle.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
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

void TraderSpiMiddle::OnRspAccountLogin(const RspAccountLoginField* rspAccountLogin, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspAccountLogin: RequestID:%d, IsLast:%d", requestID, isLast);
	if (rspAccountLogin != nullptr)
	{
		WriteLog(LogLevel::Info, "RspAccountLoginField:AccountId:[%s], LoginDate:[%s], LoginTime:[%s], SessionId:[%lld]",
			rspAccountLogin->AccountId, rspAccountLogin->LoginDate, rspAccountLogin->LoginTime, rspAccountLogin->SessionId);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspAccountLogin is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorId:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspAccountLogout(const RspAccountLogoutField* rspAccountLogout, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspAccountLogout: RequestID:%d, IsLast:%d", requestID, isLast);
	if (rspAccountLogout != nullptr)
	{
		WriteLog(LogLevel::Info, "RspAccountLogoutField:AccountId:[%s]",
			rspAccountLogout->AccountId);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspAccountLogout is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorId:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspQryHolderAccount(const HolderAccountField* holderAccount, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryHolderAccount: RequestID:%d, IsLast:%d", requestID, isLast);
	if (holderAccount != nullptr)
	{
		WriteLog(LogLevel::Info, "HolderAccountField:ExchangeId:[%s], HolderAccountId:[%s], PrimaryFlag:[%d]",
			holderAccount->ExchangeId, holderAccount->HolderAccountId, holderAccount->PrimaryFlag);
	}
	else
	{
		WriteLog(LogLevel::Info, "holderAccount is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorId:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspQryCapital(const CapitalField* capital, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryCapital: RequestID:%d, IsLast:%d", requestID, isLast);
	if (capital != nullptr)
	{
		WriteLog(LogLevel::Info, "CapitalField:TradingDay:[%s], AccountId:[%s], AccountType:[%d], Balance:[%f], PreBalance:[%f], Available:[%f], MarketValue:[%f], CashIn:[%f], CashOut:[%f], Margin:[%f], Commission:[%f], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f], CloseProfitByDate:[%f], CloseProfitByTrade:[%f], PositionProfitByDate:[%f], PositionProfitByTrade:[%f], Deposit:[%f], Withdraw:[%f]",
			capital->TradingDay, capital->AccountId, static_cast<int>(capital->AccountType), GetDoubleValue(capital->Balance), GetDoubleValue(capital->PreBalance), GetDoubleValue(capital->Available), GetDoubleValue(capital->MarketValue), GetDoubleValue(capital->CashIn), GetDoubleValue(capital->CashOut), GetDoubleValue(capital->Margin), GetDoubleValue(capital->Commission), GetDoubleValue(capital->FrozenCash), GetDoubleValue(capital->FrozenMargin), GetDoubleValue(capital->FrozenCommission), GetDoubleValue(capital->CloseProfitByDate), GetDoubleValue(capital->CloseProfitByTrade), GetDoubleValue(capital->PositionProfitByDate), GetDoubleValue(capital->PositionProfitByTrade), GetDoubleValue(capital->Deposit), GetDoubleValue(capital->Withdraw));
	}
	else
	{
		WriteLog(LogLevel::Info, "capital is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorId:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspQryPosition(const PositionField* position, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryPosition: RequestID:%d, IsLast:%d", requestID, isLast);
	if (position != nullptr)
	{
		WriteLog(LogLevel::Info, "PositionField:TradingDay:[%s], AccountId:[%s], AccountType:[%d], ExchangeId:[%s], InstrumentId:[%s], ProductClass:[%d], PosiDirection:[%d], TotalPosition:[%lld], PositionFrozen:[%lld], TodayPosition:[%lld], MarketValue:[%f], CashIn:[%f], CashOut:[%f], Margin:[%f], Commission:[%f], VolumeMultiple:[%d], CloseProfitByDate:[%f], CloseProfitByTrade:[%f], PositionProfitByDate:[%f], PositionProfitByTrade:[%f], LastPrice:[%f], PreSettlementPrice:[%f]",
			position->TradingDay, position->AccountId, static_cast<int>(position->AccountType), position->ExchangeId, position->InstrumentId, static_cast<int>(position->ProductClass), static_cast<int>(position->PosiDirection), position->TotalPosition, position->PositionFrozen, position->TodayPosition, GetDoubleValue(position->MarketValue), GetDoubleValue(position->CashIn), GetDoubleValue(position->CashOut), GetDoubleValue(position->Margin), GetDoubleValue(position->Commission), position->VolumeMultiple, GetDoubleValue(position->CloseProfitByDate), GetDoubleValue(position->CloseProfitByTrade), GetDoubleValue(position->PositionProfitByDate), GetDoubleValue(position->PositionProfitByTrade), GetDoubleValue(position->LastPrice), GetDoubleValue(position->PreSettlementPrice));
	}
	else
	{
		WriteLog(LogLevel::Info, "position is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorId:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspQryOrder(const OrderField* order, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryOrder: RequestID:%d, IsLast:%d", requestID, isLast);
	if (order != nullptr)
	{
		WriteLog(LogLevel::Info, "OrderField:TradingDay:[%s], AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], ProductClass:[%d], OrderId:[%d], OrderSysId:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], VolumeTotal:[%lld], VolumeTraded:[%lld], VolumeMultiple:[%d], OrderStatus:[%d], OrderDate:[%s], OrderTime:[%s], CancelDate:[%s], CancelTime:[%s], SessionId:[%lld], ClientOrderId:[%d], RequestId:[%d], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f]",
			order->TradingDay, order->AccountId, order->ExchangeId, order->InstrumentId, static_cast<int>(order->ProductClass), order->OrderId, order->OrderSysId, static_cast<int>(order->Direction), static_cast<int>(order->OffsetFlag), static_cast<int>(order->OrderPriceType), GetDoubleValue(order->Price), order->Volume, order->VolumeTotal, order->VolumeTraded, order->VolumeMultiple, static_cast<int>(order->OrderStatus), order->OrderDate, order->OrderTime, order->CancelDate, order->CancelTime, order->SessionId, order->ClientOrderId, order->RequestId, GetDoubleValue(order->FrozenCash), GetDoubleValue(order->FrozenMargin), GetDoubleValue(order->FrozenCommission));
	}
	else
	{
		WriteLog(LogLevel::Info, "order is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorId:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspQryTrade(const TradeField* trade, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryTrade: RequestID:%d, IsLast:%d", requestID, isLast);
	if (trade != nullptr)
	{
		WriteLog(LogLevel::Info, "TradeField:TradingDay:[%s], AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], ProductClass:[%d], OrderId:[%d], OrderSysId:[%s], TradeId:[%s], Direction:[%d], OffsetFlag:[%d], Price:[%f], Volume:[%lld], VolumeMultiple:[%d], TradeAmount:[%f], Commission:[%f], TradeDate:[%s], TradeTime:[%s]",
			trade->TradingDay, trade->AccountId, trade->ExchangeId, trade->InstrumentId, static_cast<int>(trade->ProductClass), trade->OrderId, trade->OrderSysId, trade->TradeId, static_cast<int>(trade->Direction), static_cast<int>(trade->OffsetFlag), GetDoubleValue(trade->Price), trade->Volume, trade->VolumeMultiple, GetDoubleValue(trade->TradeAmount), GetDoubleValue(trade->Commission), trade->TradeDate, trade->TradeTime);
	}
	else
	{
		WriteLog(LogLevel::Info, "trade is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorId:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspQryInstrument(const InstrumentField* instrument, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryInstrument: RequestID:%d, IsLast:%d", requestID, isLast);
	if (instrument != nullptr)
	{
		WriteLog(LogLevel::Info, "InstrumentField:ExchangeId:[%s], InstrumentId:[%s], ExchangeInstId:[%s], InstrumentName:[%s], ProductId:[%s], ProductClass:[%d], VolumeMultiple:[%d], PriceTick:[%f], MaxMarketOrderVolume:[%lld], MinMarketOrderVolume:[%lld], MaxLimitOrderVolume:[%lld], MinLimitOrderVolume:[%lld], SessionName:[%s]",
			instrument->ExchangeId, instrument->InstrumentId, instrument->ExchangeInstId, instrument->InstrumentName, instrument->ProductId, static_cast<int>(instrument->ProductClass), instrument->VolumeMultiple, GetDoubleValue(instrument->PriceTick), instrument->MaxMarketOrderVolume, instrument->MinMarketOrderVolume, instrument->MaxLimitOrderVolume, instrument->MinLimitOrderVolume, instrument->SessionName);
	}
	else
	{
		WriteLog(LogLevel::Info, "instrument is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorId:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspQryOptionInstrument(const OptionInstrumentField* optionInstrument, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryOptionInstrument: RequestID:%d, IsLast:%d", requestID, isLast);
	if (optionInstrument != nullptr)
	{
		WriteLog(LogLevel::Info, "OptionInstrumentField:ExchangeId:[%s], InstrumentId:[%s], ExchangeInstId:[%s], InstrumentName:[%s], VolumeMultiple:[%d], OptionType:[%d], UnderlyingInstrumentId:[%s], ExecutePrice:[%f], UnitMargin:[%f], PriceTick:[%f], MaxLimitOrderVolume:[%lld], MaxMarketOrderVolume:[%lld], ExpiringDate:[%s]",
			optionInstrument->ExchangeId, optionInstrument->InstrumentId, optionInstrument->ExchangeInstId, optionInstrument->InstrumentName, optionInstrument->VolumeMultiple, static_cast<int>(optionInstrument->OptionType), optionInstrument->UnderlyingInstrumentId, GetDoubleValue(optionInstrument->ExecutePrice), GetDoubleValue(optionInstrument->UnitMargin), GetDoubleValue(optionInstrument->PriceTick), optionInstrument->MaxLimitOrderVolume, optionInstrument->MaxMarketOrderVolume, optionInstrument->ExpiringDate);
	}
	else
	{
		WriteLog(LogLevel::Info, "optionInstrument is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorId:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspQryCommissionRate(const CommissionRateField* commissionRate, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryCommissionRate: RequestID:%d, IsLast:%d", requestID, isLast);
	if (commissionRate != nullptr)
	{
		WriteLog(LogLevel::Info, "CommissionRateField:AccountId:[%s], ExchangeId:[%s], ProductClass:[%d], OpenBuyByMoney:[%f], OpenSellByMoney:[%f], CloseBuyByMoney:[%f], CloseSellByMoney:[%f], OpenBuyByVolume:[%f], OpenSellByVolume:[%f], CloseBuyByVolume:[%f], CloseSellByVolume:[%f], MinCommission:[%f], MaxCommission:[%f]",
			commissionRate->AccountId, commissionRate->ExchangeId, static_cast<int>(commissionRate->ProductClass), GetDoubleValue(commissionRate->OpenBuyByMoney), GetDoubleValue(commissionRate->OpenSellByMoney), GetDoubleValue(commissionRate->CloseBuyByMoney), GetDoubleValue(commissionRate->CloseSellByMoney), GetDoubleValue(commissionRate->OpenBuyByVolume), GetDoubleValue(commissionRate->OpenSellByVolume), GetDoubleValue(commissionRate->CloseBuyByVolume), GetDoubleValue(commissionRate->CloseSellByVolume), GetDoubleValue(commissionRate->MinCommission), GetDoubleValue(commissionRate->MaxCommission));
	}
	else
	{
		WriteLog(LogLevel::Info, "commissionRate is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorId:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspQryMoneyTransfer(const MoneyTransferField* moneyTransfer, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspQryMoneyTransfer: RequestID:%d, IsLast:%d", requestID, isLast);
	if (moneyTransfer != nullptr)
	{
		WriteLog(LogLevel::Info, "MoneyTransferField:TradingDay:[%s], AccountId:[%s], MoneyTransferId:[%d], AccountType:[%d], TransferDirection:[%d], TransferAmount:[%f], InfoMessage:[%s], UserId:[%s], TransferDate:[%s], TransferTime:[%s]",
			moneyTransfer->TradingDay, moneyTransfer->AccountId, moneyTransfer->MoneyTransferId, static_cast<int>(moneyTransfer->AccountType), static_cast<int>(moneyTransfer->TransferDirection), GetDoubleValue(moneyTransfer->TransferAmount), moneyTransfer->InfoMessage, moneyTransfer->UserId, moneyTransfer->TransferDate, moneyTransfer->TransferTime);
	}
	else
	{
		WriteLog(LogLevel::Info, "moneyTransfer is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorId:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspInsertOrder: RequestID:%d, IsLast:%d", requestID, isLast);
	if (reqInsertOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqInsertOrderField:AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], ClientOrderId:[%d]",
			reqInsertOrder->AccountId, reqInsertOrder->ExchangeId, reqInsertOrder->InstrumentId, static_cast<int>(reqInsertOrder->Direction), static_cast<int>(reqInsertOrder->OffsetFlag), static_cast<int>(reqInsertOrder->OrderPriceType), GetDoubleValue(reqInsertOrder->Price), reqInsertOrder->Volume, reqInsertOrder->ClientOrderId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqInsertOrder is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorId:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestID, bool isLast)
{
	WriteLog(LogLevel::Info, "OnRspCancelOrder: RequestID:%d, IsLast:%d", requestID, isLast);
	if (reqCancelOrder != nullptr)
	{
		WriteLog(LogLevel::Info, "ReqCancelOrderField:AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], ClientCancelOrderId:[%d], OrderId:[%d], OrderSysId:[%s], SessionId:[%lld], ClientOrderId:[%d]",
			reqCancelOrder->AccountId, reqCancelOrder->ExchangeId, reqCancelOrder->InstrumentId, reqCancelOrder->ClientCancelOrderId, reqCancelOrder->OrderId, reqCancelOrder->OrderSysId, reqCancelOrder->SessionId, reqCancelOrder->ClientOrderId);
	}
	else
	{
		WriteLog(LogLevel::Info, "reqCancelOrder is nullptr");
	}
	if (rspInfo != nullptr)
	{
		WriteLog(LogLevel::Info, "RspInfoField:ErrorId:[%d], ErrorMsg:[%s]",
			rspInfo->ErrorId, rspInfo->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "rspInfo is nullptr");
	}
}
void TraderSpiMiddle::OnRtnOrder(const OrderField* order)
{
	WriteLog(LogLevel::Info, "OnRtnOrder");
	if (order != nullptr)
	{
		WriteLog(LogLevel::Info, "OrderField:TradingDay:[%s], AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], ProductClass:[%d], OrderId:[%d], OrderSysId:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], VolumeTotal:[%lld], VolumeTraded:[%lld], VolumeMultiple:[%d], OrderStatus:[%d], OrderDate:[%s], OrderTime:[%s], CancelDate:[%s], CancelTime:[%s], SessionId:[%lld], ClientOrderId:[%d], RequestId:[%d], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f]",
			order->TradingDay, order->AccountId, order->ExchangeId, order->InstrumentId, static_cast<int>(order->ProductClass), order->OrderId, order->OrderSysId, static_cast<int>(order->Direction), static_cast<int>(order->OffsetFlag), static_cast<int>(order->OrderPriceType), GetDoubleValue(order->Price), order->Volume, order->VolumeTotal, order->VolumeTraded, order->VolumeMultiple, static_cast<int>(order->OrderStatus), order->OrderDate, order->OrderTime, order->CancelDate, order->CancelTime, order->SessionId, order->ClientOrderId, order->RequestId, GetDoubleValue(order->FrozenCash), GetDoubleValue(order->FrozenMargin), GetDoubleValue(order->FrozenCommission));
	}
	else
	{
		WriteLog(LogLevel::Info, "order is nullptr");
	}
}
void TraderSpiMiddle::OnRtnTrade(const TradeField* trade)
{
	WriteLog(LogLevel::Info, "OnRtnTrade");
	if (trade != nullptr)
	{
		WriteLog(LogLevel::Info, "TradeField:TradingDay:[%s], AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], ProductClass:[%d], OrderId:[%d], OrderSysId:[%s], TradeId:[%s], Direction:[%d], OffsetFlag:[%d], Price:[%f], Volume:[%lld], VolumeMultiple:[%d], TradeAmount:[%f], Commission:[%f], TradeDate:[%s], TradeTime:[%s]",
			trade->TradingDay, trade->AccountId, trade->ExchangeId, trade->InstrumentId, static_cast<int>(trade->ProductClass), trade->OrderId, trade->OrderSysId, trade->TradeId, static_cast<int>(trade->Direction), static_cast<int>(trade->OffsetFlag), GetDoubleValue(trade->Price), trade->Volume, trade->VolumeMultiple, GetDoubleValue(trade->TradeAmount), GetDoubleValue(trade->Commission), trade->TradeDate, trade->TradeTime);
	}
	else
	{
		WriteLog(LogLevel::Info, "trade is nullptr");
	}
}
void TraderSpiMiddle::OnRtnMoneyTransfer(const MoneyTransferField* moneyTransfer)
{
	WriteLog(LogLevel::Info, "OnRtnMoneyTransfer");
	if (moneyTransfer != nullptr)
	{
		WriteLog(LogLevel::Info, "MoneyTransferField:TradingDay:[%s], AccountId:[%s], MoneyTransferId:[%d], AccountType:[%d], TransferDirection:[%d], TransferAmount:[%f], InfoMessage:[%s], UserId:[%s], TransferDate:[%s], TransferTime:[%s]",
			moneyTransfer->TradingDay, moneyTransfer->AccountId, moneyTransfer->MoneyTransferId, static_cast<int>(moneyTransfer->AccountType), static_cast<int>(moneyTransfer->TransferDirection), GetDoubleValue(moneyTransfer->TransferAmount), moneyTransfer->InfoMessage, moneyTransfer->UserId, moneyTransfer->TransferDate, moneyTransfer->TransferTime);
	}
	else
	{
		WriteLog(LogLevel::Info, "moneyTransfer is nullptr");
	}
}
void TraderSpiMiddle::OnRtnAccountLogout(const AccountLogoutField* accountLogout)
{
	WriteLog(LogLevel::Info, "OnRtnAccountLogout");
	if (accountLogout != nullptr)
	{
		WriteLog(LogLevel::Info, "AccountLogoutField:AccountId:[%s], ErrorId:[%d], ErrorMsg:[%s]",
			accountLogout->AccountId, accountLogout->ErrorId, accountLogout->ErrorMsg);
	}
	else
	{
		WriteLog(LogLevel::Info, "accountLogout is nullptr");
	}
}
}
