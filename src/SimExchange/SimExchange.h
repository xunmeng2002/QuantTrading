#pragma once
#include "Mdb.h"
#include "Packages.h"
#include "Config/Config.h"
#include "MdFront.h"
#include "TradeFront.h"
#include "OrderMatch.h"
#include "PositionMaintenance.h"
#include "FieldsCompare.h"
#include "MdSpiImpl.h"
#include <Spark/Core/Thread/ThreadBase.h>
#include <atomic>
#include <list>
#include <map>
#include <string>
#include <mutex>
#include <condition_variable>

using namespace QuantTrading::Packages;

namespace QuantTrading::SimExchange
{
class SimExchange : public Spark::Core::ThreadBase, public Spark::Network::ProtocolSubscriber, public QuantTrading::ordermatch::OrderMatchSubscriber
{
public:
	SimExchange(QuantTrading::Mdb* mdb, TradeFront* tradeFront, MdFront* mdFront, MdSpiImpl* mdSpi, MatchModeType matchMode);
	~SimExchange();

	void Init();

	void OnMdDisConnected();

	virtual void OnProtocolConnect(SessionIdType sessionId, const char* ip, int port) override;
	virtual void OnProtocolDisConnect(SessionIdType sessionId, const char* ip, int port) override;
	virtual void OnMessage(Package* package) override;


	virtual void OnOrder(QuantTrading::Order* order) override;
    virtual void OnOrderUpdate(QuantTrading::Order* order, QuantTrading::Order* newOrder) override;
	virtual void OnTrade(QuantTrading::Trade* trade) override;
protected:
	virtual void Run() override;
	void CheckPackages();
	void HandlePackages();
	// 返回 true 表示包已用完可回收，false 表示 Handler 接管了所有权
	bool DispatchPackage(Package* package);

private:
	void HandleRspMdUserLogin(RspMdUserLoginPackage* package);
	void HandleRspMdUserLogout(RspMdUserLogoutPackage* package);
	void HandleRtnDepthMarketData(RtnDepthMarketDataPackage* rtnPackage);
	void HandleRtnBarMarketData(RtnBarMarketDataPackage* rtnPackage);

	void HandleNotifyDisConnect(NotifyDisConnectPackage* notifyPackage);
	void HandleReqAccountLogin(ReqAccountLoginPackage* reqPackage);
	void HandleReqAccountLogout(ReqAccountLogoutPackage* reqPackage);
	
	void HandleReqInsertOrder(ReqInsertOrderPackage* reqPackage);
	void HandleReqCancelOrder(ReqCancelOrderPackage* reqPackage);
	void HandleReqQryOrder(ReqQryOrderPackage* reqPackage);
	void HandleReqQryTrade(ReqQryTradePackage* reqPackage);
	void HandleReqQryInstrument(ReqQryInstrumentPackage* reqPackage);


	int CheckSessionLogin(const SessionIdType& sessionId);
	int CheckSessionLogin(const AccountIdType& primaryAccountID, const SessionIdType& sessionId);
	
	void SendRspAccountLogin(ReqAccountLoginPackage* reqPackage, QuantTrading::PrimaryAccount* primaryAccount, int errorId);
	void SendRspInsertOrder(ReqInsertOrderPackage* reqPackage, int errorId);
	void SendRspCancelOrder(ReqCancelOrderPackage* reqPackage, int errorId);
	void SendRspQryOrder(ReqQryOrderPackage* reqPackage, int errorId, bool isLast, QuantTrading::Order* order = nullptr);
	void SendRspQryTrade(ReqQryTradePackage* reqPackage, int errorId, bool isLast, QuantTrading::Trade* trade = nullptr);
	void SendRspQryInstrument(ReqQryInstrumentPackage* reqPackage, int errorId, bool isLast, QuantTrading::Instrument* instrument = nullptr);
	
	void SendRtnOrder(QuantTrading::Order* order);
	void SendRtnTrade(QuantTrading::Trade* trade);

	Package* GetNextPackage();
	void ReqSubMarketData(const ExchangeIdType& exchangeId, const InstrumentIdType& instrumentId);

protected:
	MdFront* m_MdFront;
	TradeFront* m_TradeFront;
	MdSpiImpl* m_MdSpi;
	QuantTrading::Mdb* mdb_;
    QuantTrading::ordermatch::OrderMatch* orderMatch_;
	QuantTrading::Settlement::PositionMaintenance* positionMaintenance_;
	std::mutex m_Mutex;
	std::condition_variable m_ConditionVariable;

	DateType tradingDay_;
	DateType currDate_;
	TimeType currTime_;

	std::set<ReqSubMarketDataField> m_SubscribeInstruments;
	std::atomic<bool> m_IsMdLogged;

	std::list<Package*> packages_;
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
}
