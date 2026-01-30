#pragma once
#include "Mdb.h"
#include "Packages.h"
#include "Config.h"
#include "ThreadBase.h"
#include "MdFront.h"
#include "TradeFront.h"
#include "OrderMatch.h"
#include "FieldsCompare.h"
#include "InnerMdSpiImpl.h"
#include <list>
#include <map>
#include <string>
#include <mutex>
#include <condition_variable>


class SimExchange : public ThreadBase, public ProtocolSubscriber, public OrderMatchSubscriber
{
public:
	SimExchange(mdb::Mdb* mdb, TradeFront* tradeFront, MdFront* mdFront, InnerMdSpiImpl* innerMdSpi, const std::string& matchMode);
	~SimExchange();

	void Init();

	virtual void OnProtocolConnect(SessionIDType sessionID, const char* ip, int port) override;
	virtual void OnProtocolDisConnect(SessionIDType sessionID, const char* ip, int port) override;
	virtual void OnMessage(Package* package) override;


	virtual void OnOrder(mdb::Order* order) override;
	virtual void OnTrade(mdb::Trade* trade) override;
protected:
	virtual void Run() override;
	void CheckPackages();
	void HandlePackages();

private:
	void HandleRspMdUserLogin(RspMdUserLoginPackage* package);
	void HandleRspMdUserLogout(RspMdUserLogoutPackage* package);
	void HandleDepthMarketData(RtnDepthMarketDataPackage* rtnPackage);
	void HandleBarMarketData(RtnBarMarketDataPackage* rtnPackage);

	void HandleNotifyDisConnect(NotifyDisConnectPackage* notifyPackage);
	void HandleAccountLogin(ReqAccountLoginPackage* reqPackage);
	void HandleAccountLogout(ReqAccountLogoutPackage* reqPackage);
	
	void HandleInsertOrder(ReqInsertOrderPackage* reqPackage);
	void HandleCancelOrder(ReqCancelOrderPackage* reqPackage);
	void HandleQryOrder(ReqQryOrderPackage* reqPackage);
	void HandleQryTrade(ReqQryTradePackage* reqPackage);
	void HandleQryInstrument(ReqQryInstrumentPackage* reqPackage);


	bool CheckSessionLogin(const SessionIDType& sessionID);
	
	void SendRspAccountLogin(ReqAccountLoginPackage* reqPackage, mdb::PrimaryAccount* primaryAccount, int errorID);
	void SendRspInsertOrder(ReqInsertOrderPackage* reqPackage, int errorID);
	void SendRspCancelOrder(ReqCancelOrderPackage* reqPackage, int errorID);
	void SendRspQryOrder(ReqQryOrderPackage* reqPackage, int errorID, bool isLast, mdb::Order* order = nullptr);
	void SendRspQryTrade(ReqQryTradePackage* reqPackage, int errorID, bool isLast, mdb::Trade* trade = nullptr);
	void SendRspQryInstrument(ReqQryInstrumentPackage* reqPackage, int errorID, bool isLast, mdb::Instrument* instrument = nullptr);
	
	void SendRtnOrder(mdb::Order* order);
	void SendRtnTrade(mdb::Trade* trade);

	Package* GetNextPackage();
	void ReqSubMarketData(const ExchangeIDType& exchangeID, const InstrumentIDType& instrumentID);

protected:
	MdFront* m_MdFront;
	TradeFront* m_TradeFront;
	InnerMdSpiImpl* m_MdSpi;
	mdb::Mdb* m_Mdb;
	OrderMatch* m_OrderMatch;
	std::mutex m_Mutex;
	std::condition_variable m_ConditionVariable;

	DateType m_TradingDay;
	DateType m_CurrDate;
	TimeType m_CurrTime;

	std::set<ReqSubMarketDataField*> m_ReqSubMarketDatas;
	bool m_IsMdLogged;

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
};