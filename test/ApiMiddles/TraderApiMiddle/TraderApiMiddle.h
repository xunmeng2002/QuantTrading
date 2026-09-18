// 本文件由 ../Templates/Cpp/ApiTest/ApiMiddle.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include <QuantTrading/TraderApi.h>


namespace QuantTrading
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
	virtual void RegisterSpi(TraderSpi* spi) override;
	
	virtual int ReqAccountLogin(const ReqAccountLoginField* reqAccountLogin, int requestId) override;
	virtual int ReqAccountLogout(const ReqAccountLogoutField* reqAccountLogout, int requestId) override;
	virtual int ReqQryHolderAccount(const ReqQryHolderAccountField* reqQryHolderAccount, int requestId) override;
	virtual int ReqQryCapital(const ReqQryCapitalField* reqQryCapital, int requestId) override;
	virtual int ReqQryPosition(const ReqQryPositionField* reqQryPosition, int requestId) override;
	virtual int ReqQryOrder(const ReqQryOrderField* reqQryOrder, int requestId) override;
	virtual int ReqQryTrade(const ReqQryTradeField* reqQryTrade, int requestId) override;
	virtual int ReqQryInstrument(const ReqQryInstrumentField* reqQryInstrument, int requestId) override;
	virtual int ReqQryOptionInstrument(const ReqQryOptionInstrumentField* reqQryOptionInstrument, int requestId) override;
	virtual int ReqQryCommissionRate(const ReqQryCommissionRateField* reqQryCommissionRate, int requestId) override;
	virtual int ReqQryMoneyTransfer(const ReqQryMoneyTransferField* reqQryMoneyTransfer, int requestId) override;
	virtual int ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestId) override;
	virtual int ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestId) override;

private:
	TraderApi* traderApi_;
};
}
