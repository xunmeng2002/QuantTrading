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
#include <mutex>
#include <condition_variable>


class SimExchange : public ThreadBase, public ProtocolSubscriber
{
public:
	SimExchange(const Config& config, TradeFront* tradeFront, MdFront* mdFront);
	~SimExchange();

	void Init();

	virtual void OnProtocolConnect(SessionIDType sessionID, const char* ip, int port) override;
	virtual void OnProtocolDisConnect(SessionIDType sessionID, const char* ip, int port) override;
	virtual void OnMessage(Package* package) override;

protected:
	virtual void Run() override;
	void CheckPackages();
	void HandlePackages();

private:
	void HandleBrokerLogin(ReqSEBrokerLoginPackage* reqPackage);
	void HandleInsertOrder(ReqSEInsertOrderPackage* reqPackage);
	void HandleCancelOrder(ReqSECancelOrderPackage* reqPackage);
	void HandleQryOrder(ReqQrySEOrderPackage* reqPackage);
	void HandleQryTrade(ReqQrySETradePackage* reqPackage);
	void HandleQryInstrument(ReqQrySEInstrumentPackage* reqPackage);


	bool CheckSessionLogin(const SessionIDType& sessionID);
	int CheckForInsertOrder(ReqSEInsertOrderField* reqInsertOrder, mdb::SEInstrument* instrument);
	void CheckMatchForOrderQueue(mdb::SEOrder* order);
	bool CheckMatchForTwoOrder(mdb::SEOrder* order, mdb::SEOrder* queueOrder);
	void Match(mdb::SEOrder* order, const PriceType& price, VolumeType volume, const TradeIDType& tradeID, const TimeType& tradeTime);

	void SendRspBrokerLogin(ReqSEBrokerLoginPackage* reqPackage, mdb::SEBroker* broker, int errorID);
	void SendRspInsertOrder(ReqSEInsertOrderPackage* reqPackage, int errorID);
	void SendRspCancelOrder(ReqSECancelOrderPackage* reqPackage, int errorID);
	void SendRspQryOrder(ReqQrySEOrderPackage* reqPackage, int errorID, bool isLast, mdb::SEOrder* order = nullptr);
	void SendRspQryTrade(ReqQrySETradePackage* reqPackage, int errorID, bool isLast, mdb::SETrade* trade = nullptr);
	void SendRspQryInstrument(ReqQrySEInstrumentPackage* reqPackage, int errorID, bool isLast, mdb::SEInstrument* instrument = nullptr);
	
	void SendRtnOrder(mdb::SEOrder* order);
	void SendRtnTrade(mdb::SETrade* trade);

	Package* GetNextPackage();
	OrderIDType GetNextOrderID();
	void GetNextTradeID(TradeIDType& tradeID);
	void AddOrderToQueue(mdb::SEOrder* order);
	void RemoveOrderFromQueue(mdb::SEOrder* order);

protected:
	MdFront* m_MdFront;
	TradeFront* m_TradeFront;
	mdb::Mdb* m_Mdb;
	std::mutex m_Mutex;
	std::condition_variable m_ConditionVariable;

	DateType m_TradingDay;
	int m_MaxOrderID;
	int m_MaxTradeID;

	std::list<Package*> m_Packages;
	RspSEBrokerLoginPackage* m_RspBrokerLoginPackage;
	RspSEInsertOrderPackage* m_RspInsertOrderPackage;
	RspSECancelOrderPackage* m_RspCancelOrderPackage;
	RspQrySEOrderPackage* m_RspQryOrderPackage;
	RspQrySETradePackage* m_RspQryTradePackage;
	RspQrySEInstrumentPackage* m_RspQryInstrumentPackage;
	RtnSEOrderPackage* m_RtnOrderPackage;
	RtnSETradePackage* m_RtnTradePackage;

	std::map<std::string, std::set<mdb::SEOrder*, OrderGreatForPrice>> m_BuyOrders;
	std::map<std::string, std::set<mdb::SEOrder*, OrderLessForPrice>> m_SellOrders;
	std::map<std::string, std::set<mdb::SEOrder*, OrderGreatForOrderID>> m_MarketBuyOrders;
	std::map<std::string, std::set<mdb::SEOrder*, OrderGreatForOrderID>> m_MarketSellOrders;
};