// 本文件由 ../Templates/Cpp/Api/SpiWrap.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include <QuantTrading/SimExchangeCApi.h>
#include <QuantTrading/SimExchangeApi.h>


namespace QuantTrading
{
class SimExchangeSpiWrap : public SimExchangeSpi
{
public:
	void RegisterSpi(SimExchangeCSpi* spi);
	virtual void OnConnected() override;
	virtual void OnDisConnected() override;
	
	virtual void OnRspAccountLogin(const RspAccountLoginField* rspAccountLogin, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspAccountLogout(const RspAccountLogoutField* rspAccountLogout, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryOrder(const OrderField* order, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryTrade(const TradeField* trade, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspQryInstrument(const InstrumentField* instrument, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspInsertOrder(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRspCancelOrder(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo, int requestID, bool isLast) override;
	virtual void OnRtnOrder(const OrderField* order) override;
	virtual void OnRtnTrade(const TradeField* trade) override;

private:
	SimExchangeCSpi* simExchangeCSpi = nullptr;
};
}
