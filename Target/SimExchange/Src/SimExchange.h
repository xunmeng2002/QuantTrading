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
	SimExchange(mdb::Mdb* mdb, TradeFront* tradeFront, MdFront* mdFront);
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
	void HandleNotifyDisConnect(NotifyDisConnectPackage* notifyPackage);
	void HandleAccountLogin(ReqAccountLoginPackage* reqPackage);
	void HandleAccountLogout(ReqAccountLogoutPackage* reqPackage);
	
	void HandleInsertOrder(ReqInsertOrderPackage* reqPackage);
	void HandleCancelOrder(ReqCancelOrderPackage* reqPackage);
	void HandleQryOrder(ReqQryOrderPackage* reqPackage);
	void HandleQryTrade(ReqQryTradePackage* reqPackage);
	void HandleQryInstrument(ReqQryInstrumentPackage* reqPackage);


	bool CheckSessionLogin(const SessionIDType& sessionID);
	int CheckForInsertOrder(ReqInsertOrderField* reqInsertOrder, mdb::Instrument* instrument);
	void CheckMatchForOrderQueue(mdb::Order* order);
	bool CheckMatchForTwoOrder(mdb::Order* order, mdb::Order* queueOrder);
	void Match(mdb::Order* order, const PriceType& price, VolumeType volume, const TradeIDType& tradeID, const TimeType& tradeTime);

	void SendRspAccountLogin(ReqAccountLoginPackage* reqPackage, mdb::PrimaryAccount* primaryAccount, int errorID);
	void SendRspInsertOrder(ReqInsertOrderPackage* reqPackage, int errorID);
	void SendRspCancelOrder(ReqCancelOrderPackage* reqPackage, int errorID);
	void SendRspQryOrder(ReqQryOrderPackage* reqPackage, int errorID, bool isLast, mdb::Order* order = nullptr);
	void SendRspQryTrade(ReqQryTradePackage* reqPackage, int errorID, bool isLast, mdb::Trade* trade = nullptr);
	void SendRspQryInstrument(ReqQryInstrumentPackage* reqPackage, int errorID, bool isLast, mdb::Instrument* instrument = nullptr);
	
	void SendRtnOrder(mdb::Order* order);
	void SendRtnTrade(mdb::Trade* trade);

	Package* GetNextPackage();
	OrderIDType GetNextOrderID();
	void GetNextTradeID(TradeIDType& tradeID);
	void AddOrderToQueue(mdb::Order* order);
	void RemoveOrderFromQueue(mdb::Order* order);

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
	RspAccountLoginPackage* m_RspAccountLoginPackage;
	RspAccountLogoutPackage* m_RspAccountLogoutPackage;
	RspInsertOrderPackage* m_RspInsertOrderPackage;
	RspCancelOrderPackage* m_RspCancelOrderPackage;
	RspQryOrderPackage* m_RspQryOrderPackage;
	RspQryTradePackage* m_RspQryTradePackage;
	RspQryInstrumentPackage* m_RspQryInstrumentPackage;
	RtnOrderPackage* m_RtnOrderPackage;
	RtnTradePackage* m_RtnTradePackage;

	std::map<std::string, std::set<mdb::Order*, OrderLessForPriceOpposite>> m_BuyOrders;
	std::map<std::string, std::set<mdb::Order*, OrderLessForPrice>> m_SellOrders;
	std::map<std::string, std::set<mdb::Order*, OrderLessForOrderID>> m_MarketBuyOrders;
	std::map<std::string, std::set<mdb::Order*, OrderLessForOrderID>> m_MarketSellOrders;
};