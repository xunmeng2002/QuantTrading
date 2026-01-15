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
	virtual void OnRspAccountLogin(RspAccountLoginField* rspAccountLogin, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspAccountLogout(RspAccountLogoutField* rspAccountLogout, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspInsertOrder(ReqInsertOrderField* reqSEInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryInstrument(InstrumentField* sEInstrument, RspInfoField* rspInfo, int requestID, bool isLast) override;

	virtual void OnRtnOrder(OrderField* order) override;

	void ReqQryOrder();
	void ReqInsertOrders();
private:
	void ReqBrokerLogin();
	void ReqQryInstrument();
	void ReqInsertOrder(DirectionType direction, OffsetFlagType offsetFlag, OrderPriceTypeType orderPriceType, PriceType price, VolumeType volume);
	void ReqCancelOrder(OrderField* order);

public:
	bool m_InitStatus;
	bool m_Finished;
private:
	SimExchangeApi* m_SimExchangeApi;
	int m_MaxRequestID;
	int m_MaxClientOrderID;
	BrokerIDType m_BrokerID = 9999;
	AccountIDType m_AccountID;
	InstrumentField* m_Instrument;

	int m_OrderCount;
};
