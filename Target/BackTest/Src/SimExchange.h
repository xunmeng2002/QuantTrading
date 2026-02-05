#pragma once
#include "ThreadBase.h"
#include "Fields.h"
#include "Packages.h"
#include "Mdb.h"
#include "BackTestApi.h"
#include "BackTestUtility.h"
#include "MdReader.h"
#include "DBWriter.h"
#include "Config.h"
#include "OrderUtility.h"
#include "OrderMatch.h"
#include <list>
#include <map>

class SimExchange : public ThreadBase, public DBSubscriber, public OrderMatchSubscriber
{
public:
	SimExchange(const Config& config);
	~SimExchange();
	bool Init();

	virtual bool Start() override;
	virtual void Stop() override;
	virtual void Join() override;

	virtual void OnDBConnected() override;
	virtual void OnDBDisConnected() override;

	virtual void OnOrder(mdb::Order* order) override;
	virtual void OnTrade(mdb::Trade* trade) override;

	void RegisterSpi(BackTestSpi* pSpi);
	int ReqSubMarketData(ReqSubMarketDataField* reqSubMarketData, int requestID);
	int ReqSubMarketDataFinished(ReqSubMarketDataFinishedField* reqSubMarketDataFinished, int requestID);
	int ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID);
	int ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID);

protected:
	virtual void Run() override;
	void HandlePackages();
	void PushNextMd();
	void OnMdEnd();

private:
	void PushNextTick(mdb::DepthMarketData* mdTick);
	void PushNextBar(mdb::BarMarketData* mdBar);

	void HandleSubMarketDataFinished(ReqSubMarketDataFinishedPackage* reqPackage);
	void HandleInsertOrder(ReqInsertOrderPackage* reqPackage);
	void HandleCancelOrder(ReqCancelOrderPackage* reqPackage);

	void InitMdInstrument();
	void InitMainInstrument();
	void ChangeTradingDay(const DateType& nextTradingDay);
	void Settlement();
	void SettlementAccount(); 
	void SettlementPosition();
	void SettlementPositionDetail();
	void Init(const DateType& nextTradingDay);
	void InitAccount(const DateType& nextTradingDay);
	void InitPosition(const DateType& nextTradingDay);
	void InitPositionDetail(const DateType& nextTradingDay);
	

	PriceType GetSettlementPrice(mdb::PositionDetail* positionDetail);
	void CalcCapital(mdb::Capital* capital);

	void SendRspOrderInsert(ReqInsertOrderPackage* reqPackage, int errorID);
	void SendRspCancelOrder(ReqCancelOrderPackage* reqPackage, int errorID);
	void SendRtnOrder(mdb::Order* order);
	void SendRtnTrade(mdb::Trade* trade);
	void SendRtnDepthMarketData(mdb::DepthMarketData* mdTick);
	void SendRtnBarMarketData(mdb::BarMarketData* mdBar);
	void SendRtnSessionBegin(const DateType& tradingDay);
	void SendRtnSessionEnd(const DateType& tradingDay);

private:
	std::list<ReqSubMarketDataField*> m_ReqSubMds;
	std::list<Package*> m_Packages;
	BackTestSpi* m_BackTestSpi;
	OrderMatch* m_OrderMatch;
	mdb::Mdb* m_Mdb;
	DB* m_DB;
	DB* m_InitDB;
	DBWriter* m_DBWriter;
	bool m_HasSubMd;
	DateType m_TradingDay;
	DateType m_StartTradingDay;
	DateType m_EndTradingDay;
	bool m_IsMdEnd;
	DateType m_CurrDate;
	TimeType m_CurrTime;
	
	MarketDataTypeType m_MarketDataType;
	std::string m_DumpPath;

	MdReader* m_MdReader;
	std::list<mdb::DepthMarketData*> m_MdTicks;
	std::list<mdb::BarMarketData*> m_MdBars;
	std::map<std::string, mdb::BarMarketData*> m_LastMdBars;
	DepthMarketDataField m_PushMdTick;
	BarMarketDataField m_PushMdBar;
};