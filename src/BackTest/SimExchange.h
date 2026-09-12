#pragma once
#include "Packages.h"
#include "Config/Config.h"
#include "OrderUtility.h"
#include "OrderMatch.h"
#include "PositionMaintenance.h"
#include "Settlement.h"
#include "SettlementPriceSource.h"
#include "MdReader.h"
#include "Mdb.h"
#include "MdbTableRegistry.h"
#include "BarAggregator.h"
#include "TradeSession.h"
#include <QuantTrading/Fields.h>
#include <QuantTrading/BackTestApi.h>
#include <Spark/Core/Thread/ThreadBase.h>
#include <DBAdapters/DBInterface/DB.h>
#include <DBAdapters/AsyncDBWriter/AsyncDBWriter.h>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <utility>


namespace quanttrading::backtest
{
class SimExchange : public spark::core::ThreadBase, public dbadapters::DBSubscriber, public quanttrading::ordermatch::OrderMatchSubscriber, private quanttrading::bar::BarSubscriber
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
    virtual void OnOrderUpdate(mdb::Order* order, mdb::Order* newOrder) override;
	virtual void OnTrade(mdb::Trade* trade) override;

	// bar::BarSubscriber 桥：聚合器闭桶回调 → 推送目标周期 bar（指针仅在本次回调内有效）
	void OnBarMarketData(BarMarketDataField* bar) override;

	void RegisterSpi(BackTestSpi* pSpi);
	int ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestID);
	int ReqSubMarketDataFinished(const ReqSubMarketDataFinishedField* reqSubMarketDataFinished, int requestID);
	int ReqRegisterAccount(const ReqRegisterAccountField* reqRegisterAccount, int requestID);
	int ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestID);
	int ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestID);

protected:
	virtual void Run() override;
	void HandlePackages();
	void PushNextMd();
	void OnMdEnd();

private:
	void PushNextTick(mdb::DepthMarketData* mdTick);
	void PushNextBar(mdb::BarMarketData* mdBar);
	// bar 出口：该合约声明了目标周期则送入聚合器（闭桶时经 OnBarMarketData 推送），否则透传数据集精度 bar
	void PushBarMarketData(mdb::BarMarketData* mdBar);
	// 按订阅声明的目标周期登记合约的聚合器（同周期合约共用一个）；周期非法或无法由数据集精度聚合时记日志并返回 false
	bool BindBarAggregator(const char* exchangeID, const char* instrumentID, BarPrecesType barPreces, int barPeriod);
	// 闭合全部未闭合桶并按序推送：换交易日与行情收尾时调用，保证不满一桶的尾桶落在其所属交易日内
	void FlushBarAggregators();

	void HandleRegisterAccount(quanttrading::packages::ReqRegisterAccountPackage* reqPackage);
	void HandleSubMarketDataFinished(quanttrading::packages::ReqSubMarketDataFinishedPackage* reqPackage);
	void HandleInsertOrder(quanttrading::packages::ReqInsertOrderPackage* reqPackage);
	void HandleCancelOrder(quanttrading::packages::ReqCancelOrderPackage* reqPackage);

	void InitMdInstrument();
	void InitMainInstrument();
	void ChangeTradingDay(const DateType& nextTradingDay);
	void Settlement();
	void Init(const DateType& nextTradingDay);

	// Bar 撮合模式无逐笔行情表，结算价取各合约当日末根 bar 收盘价（嵌套类不持有外围实例，经指针访问引擎末根 bar 表）
	struct BarSettlementPriceSource : quanttrading::settlement::SettlementPriceSource
	{
		std::map<std::string, mdb::BarMarketData*>* m_LastMdBars;
		PriceType GetSettlementPrice(const mdb::PositionDetail* positionDetail) override;
	};

	void SendRspRegisterAccount(quanttrading::packages::ReqRegisterAccountPackage* reqPackage, int errorID);
	void SendRspOrderInsert(quanttrading::packages::ReqInsertOrderPackage* reqPackage, int errorID);
	void SendRspCancelOrder(quanttrading::packages::ReqCancelOrderPackage* reqPackage, int errorID);
	void SendRtnOrder(mdb::Order* order);
	void SendRtnTrade(mdb::Trade* trade);
	void SendRtnDepthMarketData(mdb::DepthMarketData* mdTick);
    void SendRtnMarketDataEnd();
	void SendRtnSessionBegin(const DateType& tradingDay);
	void SendRtnSessionEnd(const DateType& tradingDay);

private:
	std::mutex m_QueueMutex;
	std::list<ReqSubMarketDataField*> m_ReqSubMds;
	std::list<Package*> m_Packages;
	BackTestSpi* m_BackTestSpi;
    quanttrading::ordermatch::OrderMatch* m_OrderMatch;
	quanttrading::settlement::PositionMaintenance* m_PositionMaintenance;
	quanttrading::settlement::Settlement* m_Settlement;
	quanttrading::settlement::SettlementPriceSource* m_SettlementPriceSource;
	BarSettlementPriceSource m_BarSettlementPriceSource;
	mdb::Mdb* m_Mdb;
    dbadapters::DB* m_DB;
	mdb::MdbTableRegistry m_Registry;
    dbadapters::AsyncDBWriter* m_DBWriter;
	bool m_HasSubMd;
	DateType m_TradingDay;
	DateType m_StartTradingDay;
	DateType m_EndTradingDay;
	bool m_IsMdEnd;
	DateType m_CurrDate;
	TimeType m_CurrTime;
	
	MarketDataTypeType m_MarketDataType;
	std::string m_RunID;
	std::string m_DumpPath;

	MdReader* m_MdReader;
	std::list<mdb::DepthMarketData*> m_MdTicks;
	std::list<mdb::BarMarketData*> m_MdBars;
	std::map<std::string, mdb::BarMarketData*> m_LastMdBars;
	DepthMarketDataField m_PushMdTick;
	BarMarketDataField m_PushMdBar;

	// 交易节由引擎自己持有并装载（BackTest.json 的 SessionFile）：聚合器的桶边界锚定在交易节段首。
	// 持有期长于全部聚合器，装载完成后内容不再变化，聚合器缓存的 TradeSession* 因此长期有效。
	std::string m_SessionFile;
	quanttrading::bar::TradeSessions m_TradeSessions;
	// 目标周期 → 聚合器（同周期合约共用一个实例，实例内部按合约分桶）；唯一持有者
	std::map<std::pair<BarPrecesType, int>, std::unique_ptr<quanttrading::bar::BarAggregator>> m_BarAggregators;
	// 合约 → 其目标周期聚合器；未声明周期的合约不在表中，走透传。裸指针指向 m_BarAggregators 的 value
	std::map<std::string, quanttrading::bar::BarAggregator*> m_InstrumentBarAggregators;
};
}
