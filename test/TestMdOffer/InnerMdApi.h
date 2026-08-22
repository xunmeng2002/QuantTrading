#pragma once
#include <Spark/Core/Thread/ThreadBase.h>
#include <Spark/Network/Protocol/Protocol.h>
#include <QuantTrading/Fields.h>

using namespace spark::network;
namespace quanttrading::testmdoffer
{
class MdSpi
{
public:
	virtual void OnConnected() {}
	virtual void OnDisConnected() {}
	virtual void OnRspMdUserLogin(RspMdUserLoginField* rspMdUserLogin, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspMdUserLogout(RspMdUserLogoutField* rspMdUserLogout, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspSubMarketData(RspSubMarketDataField* rspSubMarketData, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRspUnSubMarketData(RspUnSubMarketDataField* rspUnSubMarketData, RspInfoField* rspInfo, int requestID, bool isLast) {}
	virtual void OnRtnDepthMarketData(DepthMarketDataField* depthMarketData) {}
	virtual void OnRtnBarMarketData(BarMarketDataField* barMarketData) {}
};

class InnerMdApi : public ProtocolSubscriber
{
public:
	InnerMdApi(const char* name = "InnerMdApi");
	virtual void OnProtocolConnect(SessionIDType sessionID, const char* ip, int port) override;
	virtual void OnProtocolDisConnect(SessionIDType sessionID, const char* ip, int port) override;
	virtual void OnMessage(Package* package) override;

	virtual bool Init();
	virtual void Join();
	virtual void Release();
	virtual void RegisterFront(const char* address);
	virtual void RegisterSpi(MdSpi* spi);

	virtual int ReqMdUserLogin(ReqMdUserLoginField* reqMdUserLogin, int requestID);
	virtual int ReqMdUserLogout(ReqMdUserLogoutField* reqMdUserLogout, int requestID);
	virtual int ReqSubMarketData(ReqSubMarketDataField* reqSubMarketData, int requestID);
	virtual int ReqUnSubMarketData(ReqUnSubMarketDataField* reqUnSubMarketData, int requestID);

protected:
	ProtocolTypeType m_ProtocolType;
	IOThread* m_IOThread;
	Protocol* m_Protocol;

	MdSpi* m_MdSpi;
	SessionIDType m_SessionID;
};
}
