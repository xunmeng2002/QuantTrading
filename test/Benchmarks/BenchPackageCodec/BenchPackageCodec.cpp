#include "Packages.h"

#include <Spark/Network/Protocol/StepUtility.h>
#include <Spark/TemplateLib/Benchmark/BenchmarkRunner.h>
#include <Spark/TemplateLib/ObjectPool/ObjectPool.h>

#include <cstdio>
#include <cstring>
#include <vector>

using namespace QuantTrading;
using namespace QuantTrading::Packages;
using Spark::ObjectPool;
namespace Benchmark = Spark::Benchmark;

namespace
{
    // 填一份典型深度行情：十档都带价量，字段串长度与实盘同量级，
    // 免得空串或零值把 WriteString 的成本测低
    void FillDepthMarketData(DepthMarketDataField& depthMarketData)
    {
        std::snprintf(depthMarketData.TradingDay, sizeof(depthMarketData.TradingDay), "%s", "20261030");
        std::snprintf(depthMarketData.ExchangeId, sizeof(depthMarketData.ExchangeId), "%s", "SHFE");
        std::snprintf(depthMarketData.InstrumentId, sizeof(depthMarketData.InstrumentId), "%s", "cu2512");
        depthMarketData.UpdateTs = 20261030103045123LL;
        depthMarketData.LastPrice = 78230.5;
        depthMarketData.PreSettlementPrice = 78150.0;
        depthMarketData.PreClosePrice = 78140.0;
        depthMarketData.PreOpenInterest = 123456.0;
        depthMarketData.OpenPrice = 78100.0;
        depthMarketData.HighestPrice = 78400.0;
        depthMarketData.LowestPrice = 77900.0;
        depthMarketData.ClosePrice = 78230.5;
        depthMarketData.CurrVolume = 120;
        depthMarketData.Volume = 345678;
        depthMarketData.CurrTurnover = 9387660.0;
        depthMarketData.Turnover = 27012345678.0;
        depthMarketData.OpenInterest = 234567.0;
        depthMarketData.SettlementPrice = 78150.0;
        depthMarketData.UpperLimitPrice = 83400.0;
        depthMarketData.LowerLimitPrice = 72900.0;
        depthMarketData.AveragePrice = 78166.0;

        PriceType askPrices[10] = {78231.0, 78232.0, 78233.0, 78234.0, 78235.0, 78236.0, 78237.0, 78238.0, 78239.0, 78240.0};
        VolumeType askVolumes[10] = {12, 34, 56, 78, 90, 11, 22, 33, 44, 55};
        PriceType bidPrices[10] = {78230.0, 78229.0, 78228.0, 78227.0, 78226.0, 78225.0, 78224.0, 78223.0, 78222.0, 78221.0};
        VolumeType bidVolumes[10] = {21, 43, 65, 87, 9, 10, 32, 54, 76, 98};

        PriceType* askPriceLevels[10] = {&depthMarketData.AskPrice1, &depthMarketData.AskPrice2, &depthMarketData.AskPrice3,
            &depthMarketData.AskPrice4, &depthMarketData.AskPrice5, &depthMarketData.AskPrice6, &depthMarketData.AskPrice7,
            &depthMarketData.AskPrice8, &depthMarketData.AskPrice9, &depthMarketData.AskPrice10};
        VolumeType* askVolumeLevels[10] = {&depthMarketData.AskVolume1, &depthMarketData.AskVolume2, &depthMarketData.AskVolume3,
            &depthMarketData.AskVolume4, &depthMarketData.AskVolume5, &depthMarketData.AskVolume6, &depthMarketData.AskVolume7,
            &depthMarketData.AskVolume8, &depthMarketData.AskVolume9, &depthMarketData.AskVolume10};
        PriceType* bidPriceLevels[10] = {&depthMarketData.BidPrice1, &depthMarketData.BidPrice2, &depthMarketData.BidPrice3,
            &depthMarketData.BidPrice4, &depthMarketData.BidPrice5, &depthMarketData.BidPrice6, &depthMarketData.BidPrice7,
            &depthMarketData.BidPrice8, &depthMarketData.BidPrice9, &depthMarketData.BidPrice10};
        VolumeType* bidVolumeLevels[10] = {&depthMarketData.BidVolume1, &depthMarketData.BidVolume2, &depthMarketData.BidVolume3,
            &depthMarketData.BidVolume4, &depthMarketData.BidVolume5, &depthMarketData.BidVolume6, &depthMarketData.BidVolume7,
            &depthMarketData.BidVolume8, &depthMarketData.BidVolume9, &depthMarketData.BidVolume10};

        for (int level = 0; level < 10; ++level)
        {
            *askPriceLevels[level] = askPrices[level];
            *askVolumeLevels[level] = askVolumes[level];
            *bidPriceLevels[level] = bidPrices[level];
            *bidVolumeLevels[level] = bidVolumes[level];
        }
    }
}

int main()
{
    Benchmark::PrintHeader();

    RtnDepthMarketDataPackage* package = RtnDepthMarketDataPackage::Allocate();
    package->Prepare(1, 0, 0);
    package->DepthMarketData = ObjectPool<DepthMarketDataField>::GetInstance().Allocate();
    std::memset(package->DepthMarketData, 0, sizeof(*package->DepthMarketData));
    FillDepthMarketData(*package->DepthMarketData);

    // 包与字段都取自对象池，归还也得分开做：Package::Deallocate 只管包本身
    auto releaseDepthMarketData = [&]()
    {
        if (package->DepthMarketData != nullptr)
        {
            ObjectPool<DepthMarketDataField>::GetInstance().Deallocate(package->DepthMarketData);
            package->DepthMarketData = nullptr;
        }
    };
    auto releasePackage = [&]()
    {
        releaseDepthMarketData();
        package->Deallocate();
    };

    // 正文前留一格 SOH：真实接收路径里正文紧跟报文头，字段标记形如「SOH + 键 + '='」，
    // 缺了前导 SOH 第一个字段认不出来（见 StepUtility::LocateFieldMarker）
    std::vector<char> stepBuffer(MaxPackageSize + 1);
    stepBuffer[0] = ::SOH;
    const int stepLength = package->ToStepStream(stepBuffer.data() + 1, MaxPackageSize);
    if (stepLength <= 0)
    {
        std::fprintf(stderr, "ToStepStream failed, length=%d\n", stepLength);
        releasePackage();
        return 1;
    }
    std::printf("# step_bytes,%d\n", stepLength);

    Benchmark::Measure("RtnDepthMarketDataPackage.ToStepStream",
        [&]() -> std::size_t
        {
            return static_cast<std::size_t>(package->ToStepStream(stepBuffer.data() + 1, MaxPackageSize));
        });

    // FromStepStream 每轮都会新分配一个字段对象，先收回上一轮的，否则基准自己泄漏
    auto parseDepthMarketData = [&]() -> std::size_t
    {
        releaseDepthMarketData();
        const bool parsed = package->FromStepStream(stepBuffer.data(), 1, stepLength + 1);
        return parsed && package->DepthMarketData != nullptr ? 1u : 0u;
    };

    // 解析出的合约必须与原值一致，读回空壳或错位字段都当场失败
    if (parseDepthMarketData() != 1 || std::strcmp(package->DepthMarketData->InstrumentId, "cu2512") != 0)
    {
        std::fprintf(stderr, "FromStepStream did not decode the depth market data field\n");
        releasePackage();
        return 1;
    }
    Benchmark::Measure("RtnDepthMarketDataPackage.FromStepStream", parseDepthMarketData);

    releasePackage();
    return 0;
}
