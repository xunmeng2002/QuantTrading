#pragma once
#include <QuantTrading/TraderApi.h>


namespace quanttrading
{
class TraderApiMiddle : public TraderApi
{
public:
	static TraderApiMiddle* CreateTraderApiMiddle();
	static const char* GetApiVersion();
	virtual bool Init() override;
	virtual void Join() override;
	virtual void Release() override;
	virtual void RegisterFront(const char* address) override;
	virtual void RegisterSpi(TraderSpi* pSpi) override;
	
	virtual int ReqAccountLogin(ReqAccountLoginField* reqAccountLogin, int requestID) override;
	virtual int ReqAccountLogout(ReqAccountLogoutField* reqAccountLogout, int requestID) override;
	virtual int ReqQryHolderAccount(ReqQryHolderAccountField* reqQryHolderAccount, int requestID) override;
	virtual int ReqQryCapital(ReqQryCapitalField* reqQryCapital, int requestID) override;
	virtual int ReqQryPosition(ReqQryPositionField* reqQryPosition, int requestID) override;
	virtual int ReqQryOrder(ReqQryOrderField* reqQryOrder, int requestID) override;
	virtual int ReqQryTrade(ReqQryTradeField* reqQryTrade, int requestID) override;
	virtual int ReqQryInstrument(ReqQryInstrumentField* reqQryInstrument, int requestID) override;
	virtual int ReqQryOptionInstrument(ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestID) override;
	virtual int ReqQryCommissionRate(ReqQryCommissionRateField* reqQryCommissionRate, int requestID) override;
	virtual int ReqQryMoneyTransfer(ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestID) override;
	virtual int ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID) override;
	virtual int ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID) override;

private:
	TraderApi* m_TraderApi;
};
}
