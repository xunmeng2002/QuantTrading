#pragma once
#include "MdbStructs.h"
#include <cstddef>
#include <set>
#include <string>
#include <vector>

namespace QuantTrading
{
	class Mdb;
}

namespace QuantTrading::Settlement
{
	// 一笔成交的三项费用。分三列入库：Commission 忠实只装佣金，印花税与过户费各归各列。
	struct TradeFee
	{
		MoneyType Commission = 0;
		MoneyType StampTax = 0;
		MoneyType TransferFee = 0;
	};

	TradeFee AddTradeFee(const TradeFee& left, const TradeFee& right);
	TradeFee SubtractTradeFee(const TradeFee& left, const TradeFee& right);
	TradeFee ScaleTradeFee(const TradeFee& tradeFee, double ratio);

	// 按 (手续费组, 交易所, 合约, 方向) 取费率行，算三项费用写回 Trade 的三列。
	// 费率行缺失或费率表未注册时按 0 计费、按键去重告警并计数，不阻断成交、不抛异常。
	class CommissionCalculator
	{
	public:
		explicit CommissionCalculator(QuantTrading::Mdb* mdb);

		void Apply(QuantTrading::Trade* trade);

		// 未命中费率的成交笔数：每笔缺费率的成交计 1，是「费率种子是否补齐」的端到端判据
		long long GetMissingRateCount() const;
		// 未命中费率的去重键数：同一 (组, 交易所, 合约, 方向) 无论成交多少笔只计 1
		long long GetZeroRateKeyCount() const;
		// 去重后的未命中费率键，供 result.json 直接抄出缺口去补种子
		const std::vector<std::string>& GetMissingRateKeys() const;

	private:
		static constexpr std::size_t MaxMissingRateKeyCount = 200;

		static bool IsOpenLeg(OffsetFlagType offsetFlag);
		static std::string MakeRateKey(GroupIdType commissionGroupId, const char* exchangeId, const char* instrumentId, DirectionType direction);
		static TradeFee CalcTradeFee(const QuantTrading::BaseCommission* rate, const QuantTrading::Trade* trade);

		GroupIdType SelectCommissionGroupId(const AccountIdType& accountId) const;
		void RecordMissingRate(GroupIdType commissionGroupId, const QuantTrading::Trade* trade);

		QuantTrading::Mdb* mdb_;
		std::set<std::string> warnedRateKeys_;
		std::vector<std::string> missingRateKeys_;
		long long missingRateCount_ = 0;
		long long zeroRateKeyCount_ = 0;
	};
}
