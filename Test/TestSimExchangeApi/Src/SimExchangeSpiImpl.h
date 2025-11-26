#pragma once
#include "SimExchangeSpiMiddle.h"
#include <string>
#include <chrono>
#include <vector>
#include <map>

class SimExchangeSpiImpl : public SimExchangeSpiMiddle
{
public:
	SimExchangeSpiImpl(SimExchangeApi* api);
	~SimExchangeSpiImpl();

	virtual void OnConnected() override;
	virtual void OnRspSEBrokerLogin(RspSEBrokerLoginField* rspSEBrokerLogin, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspSEBrokerLogout(RspSEBrokerLogoutField* rspSEBrokerLogout, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspSEInsertOrder(ReqSEInsertOrderField* reqSEInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQrySEInstrument(SEInstrumentField* sEInstrument, RspInfoField* rspInfo, int requestID, bool isLast) override;

	virtual void OnRtnSEOrder(SEOrderField* sEOrder) override;

	void ReqQryOrder();
	void ReqInsertOrders();
private:
	void ReqBrokerLogin();
	void ReqQryInstrument();
	void ReqInsertOrder(DirectionType direction, OffsetFlagType offsetFlag, OrderPriceTypeType orderPriceType, PriceType price, VolumeType volume);
	void ReqCancelOrder(SEOrderField* order);

public:
	bool m_InitStatus;
	bool m_Finished;
private:
	SimExchangeApi* m_SimExchangeApi;
	int m_MaxRequestID;
	int m_MaxClientOrderID;
	BrokerIDType m_BrokerID = 9999;
	AccountIDType m_AccountID;
	SEInstrumentField* m_SEInstrument;

	int m_OrderCount;
};
