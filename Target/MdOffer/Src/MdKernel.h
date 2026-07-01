#pragma once
#include "ThreadBase.h"
#include "ProtocolSubscriber.h"
#include "Packages.h"
#include "MdFront.h"
#include "ThostFtdcMdSpiImpl.h"
#include "FieldsCompare.h"
#include "BarInterface.h"
#include "Mdb.h"
#include <map>
#include <set>
#include <list>
#include <mutex>
#include <condition_variable>

class mdb::Mdb;
class MinuteBar;
class MdKernel : public ThreadBase, public ProtocolSubscriber, public BarSubscriber, public DBSubscriber
{
public:
	MdKernel(mdb::Mdb* mdb);
	void SetMdFront(MdFront* mdFront);
	void SetMdSpi(CThostFtdcMdSpiImpl* mdSpi);


	virtual void OnProtocolConnect(SessionIDType sessionID, const char* ip, int port) override;
	virtual void OnProtocolDisConnect(SessionIDType sessionID, const char* ip, int port) override;
	virtual void OnMessage(Package* package) override;

	virtual void OnBarMarketData(BarMarketDataField* bar) override;

	virtual void OnDBConnected() override;
	virtual void OnDBDisConnected() override;
protected:
	virtual void Run() override;
	void CheckEvent();
	int HandlePackage();
	int HandleNotifyDisConnect(NotifyDisConnectPackage* package);
	int HandleNotifyDBConnect(NotifyDBConnectPackage* package);
	int HandleNotifyDBDisConnect(NotifyDBDisConnectPackage* package);
	int HandleReqMdUserLogin(ReqMdUserLoginPackage* package);
	int HandleReqMdUserLogout(ReqMdUserLogoutPackage* package);
	int HandleReqSubMarketData(ReqSubMarketDataPackage* package);
	int HandleRtnDepthMarketData(RtnDepthMarketDataPackage* package);

	Package* GetPackage();
	void PushToAll(Package* package);
	void PushToAllSubscribed(ReqSubMarketDataField* reqSubMarketData, Package* package);

private:
	mdb::Mdb* m_Mdb;
	MdFront* m_MdFront;
	CThostFtdcMdSpiImpl* m_MdSpi;
	MinuteBar* m_MinuteBar;

	std::mutex m_Mutex;
	std::condition_variable m_ConditionVariable;

	std::set<SessionIDType> m_LoggedSessions;
	std::set<ReqSubMarketDataField*, std::less<ReqSubMarketDataField>> m_SubscribeInstruments;
	std::map<SessionIDType, std::set<ReqSubMarketDataField*, std::less<ReqSubMarketDataField>>> m_SessionSubscribeInstruments;
	std::list<Package*> m_RecvPackages;

	ReqSubMarketDataField* m_ReqSubMarketData;
	RtnBarMarketDataPackage* m_BarMdPackage;
};

