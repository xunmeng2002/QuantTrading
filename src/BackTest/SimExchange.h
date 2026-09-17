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
#include <DbAdapters/DbInterface/Db.h>
#include <DbAdapters/AsyncDbWriter/AsyncDbWriter.h>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <utility>


namespace QuantTrading::BackTest
{
class SimExchange : public Spark::Core::ThreadBase, public DbAdapters::DbSubscriber, public QuantTrading::ordermatch::OrderMatchSubscriber, private QuantTrading::Bar::BarSubscriber
{
public:
	SimExchange(const Config& config);
	~SimExchange();
	bool Init();

	virtual bool Start() override;
	virtual void Stop() override;
	virtual void Join() override;

	virtual void OnDbConnected() override;
	virtual void OnDbDisConnected() override;

	virtual void OnOrder(QuantTrading::Order* order) override;
    virtual void OnOrderUpdate(QuantTrading::Order* order, QuantTrading::Order* newOrder) override;
	virtual void OnTrade(QuantTrading::Trade* trade) override;

	// Bar::BarSubscriber 桥：聚合器闭桶回调 → 推送目标周期 bar（指针仅在本次回调内有效）
	void OnBarMarketData(BarMarketDataField* bar) override;

	void RegisterSpi(BackTestSpi* pSpi);
	int ReqSubMarketData(const ReqSubMarketDataField* reqSubMarketData, int requestId);
	int ReqSubMarketDataFinished(const ReqSubMarketDataFinishedField* reqSubMarketDataFinished, int requestId);
	int ReqRegisterAccount(const ReqRegisterAccountField* reqRegisterAccount, int requestId);
	int ReqInsertOrder(const ReqInsertOrderField* reqInsertOrder, int requestId);
	int ReqCancelOrder(const ReqCancelOrderField* reqCancelOrder, int requestId);

protected:
	virtual void Run() override;
	void HandlePackages();
	void PushNextMd();
	void OnMdEnd();

private:
    // Bar 撮合模式无逐笔行情表，结算价取各合约当日末根 bar 收盘价（嵌套类不持有外围实例，经指针访问引擎末根 bar 表）
    struct BarSettlementPriceSource : QuantTrading::Settlement::SettlementPriceSource
    {
        std::map<std::string, QuantTrading::BarMarketData*>* lastMdBars_;
        PriceType GetSettlementPrice(const QuantTrading::PositionDetail* positionDetail) override;
    };

	void PushNextTick(QuantTrading::DepthMarketData* mdTick);
	void PushNextBar(QuantTrading::BarMarketData* mdBar);
	// bar 出口：该合约声明了目标周期则送入聚合器（闭桶时经 OnBarMarketData 推送），否则透传数据集精度 bar
	void PushBarMarketData(QuantTrading::BarMarketData* mdBar);
	// 按订阅声明的目标周期登记合约的聚合器（同周期合约共用一个）；周期非法或无法由数据集精度聚合时记日志并返回 false
	bool BindBarAggregator(const char* exchangeId, const char* instrumentId, BarPrecesType barPreces, int barPeriod);
	// 闭合全部未闭合桶并按序推送：换交易日与行情收尾时调用，保证不满一桶的尾桶落在其所属交易日内
	void FlushBarAggregators();

	void HandleRegisterAccount(QuantTrading::Packages::ReqRegisterAccountPackage* reqPackage);
	void HandleSubMarketDataFinished(QuantTrading::Packages::ReqSubMarketDataFinishedPackage* reqPackage);
	void HandleInsertOrder(QuantTrading::Packages::ReqInsertOrderPackage* reqPackage);
	void HandleCancelOrder(QuantTrading::Packages::ReqCancelOrderPackage* reqPackage);

	void InitMdInstrument();
	void InitMainInstrument();
	void ChangeTradingDay(const DateType& nextTradingDay);
	void Settlement();
	void Init(const DateType& nextTradingDay);



	void SendRspRegisterAccount(QuantTrading::Packages::ReqRegisterAccountPackage* reqPackage, int errorId);
	void SendRspOrderInsert(QuantTrading::Packages::ReqInsertOrderPackage* reqPackage, int errorId);
	void SendRspCancelOrder(QuantTrading::Packages::ReqCancelOrderPackage* reqPackage, int errorId);
	void SendRtnOrder(QuantTrading::Order* order);
	void SendRtnTrade(QuantTrading::Trade* trade);
	void SendRtnDepthMarketData(QuantTrading::DepthMarketData* mdTick);
    void SendRtnMarketDataEnd();
	void SendRtnSessionBegin(const DateType& tradingDay);
	void SendRtnSessionEnd(const DateType& tradingDay);


    std::mutex queueMutex_;
	std::list<ReqSubMarketDataField*> reqSubMds_;
	std::list<Package*> packages_;
	BackTestSpi* backTestSpi_;
    QuantTrading::ordermatch::OrderMatch* orderMatch_;
	QuantTrading::Settlement::PositionMaintenance* positionMaintenance_;
	QuantTrading::Settlement::Settlement* settlement_;
	QuantTrading::Settlement::SettlementPriceSource* settlementPriceSource_;
	BarSettlementPriceSource barSettlementPriceSource_;
	QuantTrading::Mdb* mdb_;
    DbAdapters::Db* db_;
	QuantTrading::MdbTableRegistry registry_;
    DbAdapters::AsyncDbWriter* dbWriter_;
	bool hasSubMd_;
	DateType tradingDay_;
	DateType startTradingDay_;
	DateType endTradingDay_;
	bool isMdEnd_;
	DateType currDate_;
	TimeType currTime_;
	
	MarketDataTypeType marketDataType_;
	std::string runId_;
	std::string dumpPath_;

	MdReader* mdReader_;
	std::list<QuantTrading::DepthMarketData*> mdTicks_;
	std::list<QuantTrading::BarMarketData*> mdBars_;
	std::map<std::string, QuantTrading::BarMarketData*> lastMdBars_;
	DepthMarketDataField pushMdTick_;
	BarMarketDataField pushMdBar_;

	// 交易节由引擎自己持有并装载（BackTest.json 的 SessionFile）：聚合器的桶边界锚定在交易节段首。
	// 持有期长于全部聚合器，装载完成后内容不再变化，聚合器缓存的 TradeSession* 因此长期有效。
	std::string sessionFile_;
	QuantTrading::Bar::TradeSessions tradeSessions_;
	// 目标周期 → 聚合器（同周期合约共用一个实例，实例内部按合约分桶）；唯一持有者
	std::map<std::pair<BarPrecesType, int>, std::unique_ptr<QuantTrading::Bar::BarAggregator>> barAggregators_;
	// 合约 → 其目标周期聚合器；未声明周期的合约不在表中，走透传。裸指针指向 barAggregators_ 的 value
	std::map<std::string, QuantTrading::Bar::BarAggregator*> instrumentBarAggregators_;
};
}
