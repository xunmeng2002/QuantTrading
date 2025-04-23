#pragma once
#include "ThreadBase.h"
#include "ProtocolSubscriber.h"
#include "Packages.h"
#include "MdFront.h"
#include "ThostFtdcMdSpiImpl.h"
#include "FieldsCompare.h"
#include "BarInterface.h"
#include <map>
#include <set>
#include <list>


class MdKernel : public ThreadBase, public ProtocolSubscriber, public BarSubscriber
{
public:
	MdKernel(const char* mdUser, const char* password);
	void SetMdFront(MdFront* mdFront);
	void SetMdSpi(CThostFtdcMdSpiImpl* mdSpi);


	virtual void OnProtocolConnect(SessionIDType sessionID, const char* ip, int port) override;
	virtual void OnProtocolDisConnect(SessionIDType sessionID, const char* ip, int port) override;
	virtual void OnMessage(Package* package) override;

	virtual void OnBarMarketData(BarMarketDataField* bar) override;

protected:
	virtual void Run() override;
	void CheckEvent();
	int HandlePackage();
	int HandleNotifyDisConnect(NotifyDisConnectPackage* package);
	int HandleReqMdUserLogin(ReqMdUserLoginPackage* package);
	int HandleReqSubMarketData(ReqSubMarketDataPackage* package);
	int HandleRtnDepthMarketData(RtnDepthMarketDataPackage* package);

	Package* GetPackage();
	void PushToAll(Package* package);
	void PushToAllSubscribed(ReqSubMarketDataField* reqSubMarketData, Package* package);

private:
	MdFront* m_MdFront;
	CThostFtdcMdSpiImpl* m_MdSpi;

	std::set<ReqSubMarketDataField*, std::less<ReqSubMarketDataField>> m_SubscribeInstruments;
	std::map<SessionIDType, std::set<ReqSubMarketDataField*, std::less<ReqSubMarketDataField>>> m_SessionSubscribeInstruments;
	std::list<Package*> m_RecvPackages;

	RtnBarMarketDataPackage* m_BarMdPackage;

	UserIDType m_MdUser;
	PasswordType m_MdPassword;
};

