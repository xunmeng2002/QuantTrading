#pragma once
#include "OrderUtility.h"
#include "MdbStructs.h"
#include "Mdb.h"
#include <string>
#include <map>
#include <set>


class OrderMatchSubscriber
{
public:
	virtual void OnOrder(mdb::Order* order) = 0;
	virtual void OnTrade(mdb::Trade* trade) = 0;
};

class OrderMatch
{
public:
	static OrderMatch* CreateOrderMatch(const MatchModeType& matchMode, mdb::Mdb* mdb, const DateType& tradingDay, int maxTradeID = 0);
	OrderMatch(mdb::Mdb* mdb, const DateType& tradingDay, int maxTradeID = 0);
	virtual ~OrderMatch();
	void Subscribe(OrderMatchSubscriber* orderMatchSubscriber);

	virtual void OnTick(mdb::DepthMarketData* mdTick) = 0;
	virtual void OnBar(mdb::BarMarketData* mdBar) = 0;
	virtual void InsertOrder(mdb::Order* order) = 0;
	virtual void CancelOrder(mdb::Order* order);

protected:
	void Match(mdb::Order* order, const PriceType& price, const VolumeType& volume, const TradeIDType& tradeID);
	void AddOrderToQueue(mdb::Order* order);
	void GetNextTradeID(TradeIDType& tradeID);
	void UpdateDateTime();
	void UpdateDateTime(const Int64Type& updateTs);

protected:
	mdb::Mdb* m_Mdb;
	OrderMatchSubscriber* m_OrderMatchSubscriber;

	DateType m_TradingDay;
	int m_MaxTradeID;
	TradeIDType m_TradeID;
	DateType m_CurrDate;
	TimeType m_CurrTime;
	std::map<std::string, std::set<mdb::Order*, OrderLessForPriceOpposite>> m_BuyOrders;
	std::map<std::string, std::set<mdb::Order*, OrderLessForPrice>> m_SellOrders;
	std::map<std::string, std::set<mdb::Order*, OrderLessForOrderID>> m_MarketBuyOrders;
	std::map<std::string, std::set<mdb::Order*, OrderLessForOrderID>> m_MarketSellOrders;
};
