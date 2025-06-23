#pragma once
#include "Mdb.h"
#include "Packages.h"
#include "Config.h"
#include "ThreadBase.h"
#include "SimExchangeUtility.h"
#include <map>
#include <string>

class SimExchange : public ThreadBase
{
public:
	SimExchange(const Config& config);
	~SimExchange();

	void Init();
	int ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID);
	int ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID);

protected:
	virtual void Run() override;
	void HandlePackages();


protected:
	mdb::Mdb* m_Mdb;

	std::map<std::string, std::set<mdb::Order*, OrderGreatForPrice>> m_BuyOrders;
	std::map<std::string, std::set<mdb::Order*, OrderLessForPrice>> m_SellOrders;
	std::map<std::string, std::set<mdb::Order*, OrderGreatForOrderID>> m_MarketBuyOrders;
	std::map<std::string, std::set<mdb::Order*, OrderGreatForOrderID>> m_MarketSellOrders;
};