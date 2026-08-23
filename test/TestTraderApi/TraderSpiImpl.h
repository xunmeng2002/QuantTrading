#pragma once
#include "TraderSpiMiddle.h"
#include "Environment.h"
#include <string>
#include <chrono>
#include <vector>
#include <map>

using quanttrading::quanttradingcommon::AccountInfo;
namespace quanttrading::testtraderapi
{
class TraderSpiImpl : public TraderSpiMiddle
{
public:
	TraderSpiImpl(TraderApi* api);
	~TraderSpiImpl();
	void SetAccountInfo(AccountInfo* accountInfo);

	virtual void OnConnected() override;
	virtual void OnRspAccountLogin(RspAccountLoginField* rspAccountLogin, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspAccountLogout(RspAccountLogoutField* rspAccountLogout, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspInsertOrder(ReqInsertOrderField* reqSEInsertOrder, RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryInstrument(InstrumentField* sEInstrument, RspInfoField* rspInfo, int requestID, bool isLast) override;

	virtual void OnRtnOrder(OrderField* order) override;

	void ReqQryOrder();
	void ReqInsertOrders();
private:
	void ReqAccountLogin();
	void ReqQryInstrument();
	void ReqInsertOrder(DirectionType direction, OffsetFlagType offsetFlag, OrderPriceTypeType orderPriceType, PriceType price, VolumeType volume);
	void ReqCancelOrder(OrderField* order);

public:
	bool m_InitStatus;
	bool m_Finished;
private:
	TraderApi* m_TraderApi;
	AccountInfo* m_AccountInfo;
	InstrumentField m_Instrument;
	bool m_HasInstrument;
	int m_MaxRequestID;
	int m_MaxClientOrderID;
	int m_OrderCount;
};
}
