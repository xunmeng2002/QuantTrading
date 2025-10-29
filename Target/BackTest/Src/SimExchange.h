#pragma once
#include "ThreadBase.h"
#include "BackTestFields.h"
#include "Packages.h"
#include "Mdb.h"
#include "BackTestApi.h"
#include "BackTestUtility.h"
#include "MdReader.h"
#include "Config.h"
#include <list>
#include <map>

class SimExchange : public ThreadBase
{
public:
	SimExchange(const Config& config);
	~SimExchange();
	void Init();

	void RegisterSpi(BackTestSpi* pSpi);
	int ReqSubMarketData(ReqSubMarketDataField* reqSubMarketData, int requestID);
	int ReqSubMarketDataFinished(ReqSubMarketDataFinishedField* reqSubMarketDataFinished, int requestID);
	int ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID);
	int ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID);

protected:
	virtual void Run() override;
	void HandlePackages();
	void PushNextMd();
	void UpdateOrderQueue();
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
	void UpdateLastMdTick(mdb::DepthMarketData* mdTick);
	void UpdateLastMdBar(mdb::BarMarketData* mdBar);
	
	mdb::Position* InitPosition(ReqInsertOrderField* reqInsertOrder, mdb::Account* account, mdb::Instrument* instrument, const PosiDirectionType& posiDirection, const PriceType& preSettlementPrice);
	mdb::Position* GetPosition(ReqInsertOrderField* reqInsertOrder, mdb::Account* account, mdb::Instrument* instrument, const PriceType& preSettlementPrice);
	mdb::Position* GetPosition(mdb::Order* order);
	int CheckForInputOrder(ReqInsertOrderField* reqInsertOrder, mdb::Position* position);
	mdb::Order* InitOrder(ReqInsertOrderPackage* reqPackage, mdb::Account* account, mdb::Position* postion, const Int64Type& insertTime);
	void AddOrderToQueue(mdb::Order* order);
	void UpdateMarketOrderAfterMd(const InstrumentIDType& instrumentID);
	int CheckForCancelOrder(mdb::Order* order);

	void CheckMatchForMdTick(mdb::Order* order, mdb::DepthMarketData* mdTick);
	void CheckMatchForMdBar(mdb::Order* order, mdb::BarMarketData* mdBar);
	void CheckMatchForOnePrice(mdb::Order* order, const Int64Type& updateTs, PriceType lastPrice, PriceType oppoPrice, VolumeType& oppoVolume);
	void CheckMatchForOrderQueue(mdb::Order* order);
	bool CheckMatchForTwoOrder(mdb::Order* order, mdb::Order* queueOrder);
	void Match(mdb::Order* order, const PriceType& price, VolumeType volume, const TradeIDType& tradeID, const TimeType& tradeTime);

	void UpdateAllQueueOrder(const std::string& instrumentID);

	OrderIDType GetNextOrderID();
	void GetNextTradeID(TradeIDType& tradeID);
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
	mdb::Mdb* m_Mdb;
	bool m_HasSubMd;
	DateType m_TradingDay;
	DateType m_StartTradingDay;
	DateType m_EndTradingDay;
	
	int m_MaxOrderID;
	int m_MaxTradeID;
	MarketDataTypeType m_MarketDataType;
	std::string m_DumpPath;

	MdReader* m_MdReader;
	std::list<mdb::DepthMarketData*> m_MdTicks;
	std::list<mdb::BarMarketData*> m_MdBars;
	std::map<std::string, mdb::DepthMarketData*> m_LastMdTicks;
	std::map<std::string, mdb::BarMarketData*> m_LastMdBars;
	DepthMarketDataField m_PushMdTick;
	BarMarketDataField m_PushMdBar;

	std::map<std::string, std::set<mdb::Order*, OrderLessForPriceOpposite>> m_BuyOrders;
	std::map<std::string, std::set<mdb::Order*, OrderLessForPrice>> m_SellOrders;
	std::map<std::string, std::set<mdb::Order*, OrderLessForOrderID>> m_MarketBuyOrders;
	std::map<std::string, std::set<mdb::Order*, OrderLessForOrderID>> m_MarketSellOrders;

	std::map<std::string, bool> m_InstrumentsHasMatched;
};