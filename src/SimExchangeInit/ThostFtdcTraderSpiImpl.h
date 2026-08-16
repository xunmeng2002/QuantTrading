#pragma once

#include "ThostFtdcTraderSpiMiddle.h"
#include "Environment.h"
#include "Mdb.h"
#include "MdbStructs.h"
#include <atomic>
#include <vector>

class CThostFtdcTraderSpiImpl : public CThostFtdcTraderSpiMiddle
{
public:
	CThostFtdcTraderSpiImpl(CThostFtdcTraderApi* traderApi, mdb::Mdb* mdb);

	virtual void OnFrontConnected() override;
	virtual void OnFrontDisconnected(int nReason) override;
	virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField* pRspAuthenticateField, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) override;
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) override;
	virtual void OnRspQryExchange(CThostFtdcExchangeField* pExchange, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) override;
	virtual void OnRspQryProduct(CThostFtdcProductField* pProduct, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) override;
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField* pInstrument, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) override;
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField* pTradingAccount, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) override;
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField* pInvestorPosition, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) override;
	virtual void OnRspQryOrder(CThostFtdcOrderField* pOrder, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) override;
	virtual void OnRspQryTrade(CThostFtdcTradeField* pTrade, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) override;

public:
	void SetAccountInfo(AccountInfo* accountInfo);
	void SetNewPassword(const std::string& newPassword);

private:
	void ReqAuthenticate();
	void ReqUserLogin();
	void ReqUserPasswordUpdate();
	void ReqQryExchange();
	void ReqQryProduct();
	void ReqQryInstrument();
	void ReqQryTradingAccount();
	void ReqQryInvestorPosition();
	void ReqQryOrder();
	void ReqQryTrade();

public:
	std::atomic<bool> m_QryFinished;
private:
	CThostFtdcTraderApi* m_TraderApi;
	mdb::Mdb* m_Mdb;
	int m_RequestID;

	AccountInfo* m_AccountInfo;
	std::string m_NewPassword;

	std::vector<mdb::Exchange*>* m_Exchanges;
	std::vector<mdb::Product*>* m_Products;
	std::vector<mdb::Instrument*>* m_Instruments;
};
