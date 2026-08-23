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
	
	virtual int ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestID) override;
	virtual int ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestID) override;
	virtual int ReqQryHolderAccount(const ReqQryHolderAccountField* reqQryHolderAccount, int requestID) override;
	virtual int ReqQryCapital(const ReqQryCapitalField* reqQryCapital, int requestID) override;
	virtual int ReqQryPosition(const ReqQryPositionField* reqQryPosition, int requestID) override;
	virtual int ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestID) override;
	virtual int ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestID) override;
	virtual int ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestID) override;
	virtual int ReqQryOptionInstrument(const ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestID) override;
	virtual int ReqQryCommissionRate(const ReqQryCommissionRateField* reqQryCommissionRate, int requestID) override;
	virtual int ReqQryMoneyTransfer(const ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestID) override;
	virtual int ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestID) override;
	virtual int ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestID) override;

private:
	TraderApi* m_TraderApi;
};
}
