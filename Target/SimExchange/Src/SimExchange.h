#pragma once
#include "Mdb.h"
#include "Packages.h"
#include "Config.h"
#include "ThreadBase.h"
#include "SimExchangeUtility.h"
#include "MdFront.h"
#include "TradeFront.h"
#include <list>
#include <map>
#include <string>

class SimExchange : public ThreadBase
{
public:
	SimExchange(const Config& config);
	~SimExchange();

	void Init();
	int ReqSEInsertOrder(ReqSEInsertOrderField* reqInsertOrder, int requestID);
	int ReqSECancelOrder(ReqSECancelOrderField* reqCancelOrder, int requestID);

protected:
	virtual void Run() override;
	void HandlePackages();

private:
	void HandleBrokerLogin(ReqSEBrokerLoginPackage* reqPackage);
	void HandleInsertOrder(ReqSEInsertOrderPackage* reqPackage);
	void HandleCancelOrder(ReqSECancelOrderPackage* reqPackage);
	void HandleQryOrder(ReqQrySEOrderPackage* reqPackage);
	void HandleQryTrade(ReqQrySETradePackage* reqPackage);
	void HandleQryInstrument(ReqQryInstrumentPackage* reqPackage);


	int CheckForInsertOrder(ReqSEInsertOrderField* reqInsertOrder, mdb::SEInstrument* instrument);
	void CheckMatchForOrderQueue(mdb::SEOrder* order);
	bool CheckMatchForTwoOrder(mdb::SEOrder* order, mdb::SEOrder* queueOrder);
	void Match(mdb::SEOrder* order, const PriceType& price, VolumeType volume, const TradeIDType& tradeID, const TimeType& tradeTime);

	void SendRspBrokerLogin(ReqSEBrokerLoginPackage* reqPackage, mdb::SEBroker* broker, int errorID);
	void SendRspInsertOrder(ReqSEInsertOrderPackage* reqPackage, int errorID);
	void SendRspCancelOrder(ReqSECancelOrderPackage* reqPackage, int errorID);
	void SendRtnOrder(mdb::SEOrder* order);
	void SendRtnTrade(mdb::SETrade* trade);

	OrderIDType GetNextOrderID();
	void GetNextTradeID(TradeIDType& tradeID);
	void AddOrderToQueue(mdb::SEOrder* order);

protected:
	MdFront* m_MdFront;
	TradeFront* m_TradeFront;
	mdb::Mdb* m_Mdb;

	DateType m_TradingDay;
	int m_MaxOrderID;
	int m_MaxTradeID;

	std::list<Package*> m_Packages;
	RspSEBrokerLoginPackage* m_RspBrokerLoginPackage;
	RspSEInsertOrderPackage* m_RspInsertOrderPackage;
	RspSECancelOrderPackage* m_RspCancelOrderPackage;
	RtnSEOrderPackage* m_RtnOrderPackage;
	RtnSETradePackage* m_RtnTradePackage;

	std::map<std::string, std::set<mdb::SEOrder*, OrderGreatForPrice>> m_BuyOrders;
	std::map<std::string, std::set<mdb::SEOrder*, OrderLessForPrice>> m_SellOrders;
	std::map<std::string, std::set<mdb::SEOrder*, OrderGreatForOrderID>> m_MarketBuyOrders;
	std::map<std::string, std::set<mdb::SEOrder*, OrderGreatForOrderID>> m_MarketSellOrders;
};