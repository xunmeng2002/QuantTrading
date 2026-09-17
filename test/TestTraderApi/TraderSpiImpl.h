#pragma once
#include "TraderSpiMiddle.h"
#include "Environment.h"
#include <string>
#include <chrono>
#include <vector>
#include <map>

using QuantTrading::AccountInfo;
namespace QuantTrading::TestTraderApi
{
class TraderSpiImpl : public TraderSpiMiddle
{
public:
	TraderSpiImpl(TraderApi* api);
	~TraderSpiImpl();
	void SetAccountInfo(AccountInfo* accountInfo);

	virtual void OnConnected() override;
	virtual void OnRspAccountLogin(const RspAccountLoginField* rspAccountLogin, const RspInfoField* rspInfo, int requestId, bool isLast) override;
	virtual void OnRspAccountLogout(const RspAccountLogoutField* rspAccountLogout, const RspInfoField* rspInfo, int requestId, bool isLast) override;
	virtual void OnRspInsertOrder(const ReqInsertOrderField* reqSEInsertOrder, const RspInfoField* rspInfo, int requestId, bool isLast) override;
	virtual void OnRspQryInstrument(const InstrumentField* sEInstrument, const RspInfoField* rspInfo, int requestId, bool isLast) override;

	virtual void OnRtnOrder(const OrderField* order) override;

	void ReqQryOrder();
	void ReqInsertOrders();

    bool InitStatus;
    bool Finished;
private:
	void ReqAccountLogin();
	void ReqQryInstrument();
	void ReqInsertOrder(DirectionType direction, OffsetFlagType offsetFlag, OrderPriceTypeType orderPriceType, PriceType price, VolumeType volume);
	void ReqCancelOrder(const OrderField* order);

private:
	TraderApi* traderApi_;
	AccountInfo* accountInfo_;
	InstrumentField instrument_;
	bool hasInstrument_;
	int maxRequestId_;
	int maxClientOrderId_;
	int orderCount_;
};
}
