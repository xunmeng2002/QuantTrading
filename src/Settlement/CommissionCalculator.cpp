#include "CommissionCalculator.h"
#include "Mdb.h"

#include <Spark/Core/Logger/Logger.h>
#include <Spark/Core/Utility/DoubleUtility.h>

#include <string>

using namespace QuantTrading;
using namespace Spark;
using namespace Spark::Core;

namespace QuantTrading::Settlement
{
	namespace
	{
		// MinCommission/MaxCommission 为 0 或负值表示该侧不设限，只有正值才参与封底封顶。
		// 封顶只作用于佣金：印花税与过户费按法定费率实收，不受券商最低收费约束。
		MoneyType ClampCommission(const MoneyType commission, const MoneyType minCommission, const MoneyType maxCommission)
		{
			if (minCommission > 0 && DoubleUtility::DoubleLess(commission, minCommission))
			{
				return minCommission;
			}
			if (maxCommission > 0 && DoubleUtility::DoubleGreat(commission, maxCommission))
			{
				return maxCommission;
			}
			return commission;
		}
	}

	TradeFee AddTradeFee(const TradeFee& left, const TradeFee& right)
	{
		return TradeFee{ left.Commission + right.Commission, left.StampTax + right.StampTax, left.TransferFee + right.TransferFee };
	}

	TradeFee SubtractTradeFee(const TradeFee& left, const TradeFee& right)
	{
		return TradeFee{ left.Commission - right.Commission, left.StampTax - right.StampTax, left.TransferFee - right.TransferFee };
	}

	TradeFee ScaleTradeFee(const TradeFee& tradeFee, const double ratio)
	{
		return TradeFee{ tradeFee.Commission * ratio, tradeFee.StampTax * ratio, tradeFee.TransferFee * ratio };
	}

	CommissionCalculator::CommissionCalculator(QuantTrading::Mdb* mdb)
		:mdb_(mdb)
	{
	}

	void CommissionCalculator::Apply(QuantTrading::Trade* trade)
	{
		if (mdb_ == nullptr || trade == nullptr)
		{
			return;
		}
		// 实盘安装包未注册 BaseCommission（SimExchangeTableNames.xml 刻意不含费率表），此处即空守卫，
		// 成交三列保持调用方置好的 0，实盘行为不因本类引入而改变。
		if (mdb_->BaseCommission == nullptr)
		{
			return;
		}
		const auto commissionGroupId = SelectCommissionGroupId(trade->AccountId);
		auto rate = mdb_->BaseCommission->PrimaryKey->Select(commissionGroupId, trade->ExchangeId, trade->InstrumentId, trade->Direction);
		if (rate == nullptr)
		{
			RecordMissingRate(commissionGroupId, trade);
			return;
		}
		const auto tradeFee = CalcTradeFee(rate, trade);
		trade->Commission = tradeFee.Commission;
		trade->StampTax = tradeFee.StampTax;
		trade->TransferFee = tradeFee.TransferFee;
	}

	long long CommissionCalculator::GetMissingRateCount() const
	{
		return missingRateCount_;
	}

	long long CommissionCalculator::GetZeroRateKeyCount() const
	{
		return zeroRateKeyCount_;
	}

	const std::vector<std::string>& CommissionCalculator::GetMissingRateKeys() const
	{
		return missingRateKeys_;
	}

	bool CommissionCalculator::IsOpenLeg(const OffsetFlagType offsetFlag)
	{
		return offsetFlag == OffsetFlagType::Open;
	}

	std::string CommissionCalculator::MakeRateKey(const GroupIdType commissionGroupId, const char* exchangeId, const char* instrumentId, const DirectionType direction)
	{
		return std::to_string(commissionGroupId) + "|" + exchangeId + "|" + instrumentId + "|" + std::to_string(static_cast<int>(direction));
	}

	TradeFee CommissionCalculator::CalcTradeFee(const QuantTrading::BaseCommission* rate, const QuantTrading::Trade* trade)
	{
		// 方向不参与取列：买卖差异由费率行的数据表达（A 股卖出单边、港股双边都写在费率里）。
		// 金额侧与手数侧是相加的两项，不是相乘：一份按成交金额收，一份按成交手数收。
		const auto isOpenLeg = IsOpenLeg(trade->OffsetFlag);
		const auto commission = trade->TradeAmount * (isOpenLeg ? rate->OpenByMoney : rate->CloseByMoney)
			+ static_cast<MoneyType>(trade->Volume) * (isOpenLeg ? rate->OpenByVolume : rate->CloseByVolume);
		TradeFee tradeFee;
		tradeFee.Commission = ClampCommission(commission, rate->MinCommission, rate->MaxCommission);
		tradeFee.StampTax = trade->TradeAmount * (isOpenLeg ? rate->OpenStampTaxByMoney : rate->CloseStampTaxByMoney);
		tradeFee.TransferFee = trade->TradeAmount * (isOpenLeg ? rate->OpenTransferFeeByMoney : rate->CloseTransferFeeByMoney);
		return tradeFee;
	}

	GroupIdType CommissionCalculator::SelectCommissionGroupId(const AccountIdType& accountId) const
	{
		if (mdb_->Account == nullptr)
		{
			return 0;
		}
		auto account = mdb_->Account->PrimaryKey->Select(accountId);
		return account == nullptr ? 0 : account->CommissionGroupId;
	}

	void CommissionCalculator::RecordMissingRate(const GroupIdType commissionGroupId, const QuantTrading::Trade* trade)
	{
		++missingRateCount_;
		const auto rateKey = MakeRateKey(commissionGroupId, trade->ExchangeId, trade->InstrumentId, trade->Direction);
		if (!warnedRateKeys_.insert(rateKey).second)
		{
			return;
		}
		++zeroRateKeyCount_;
		WriteLog(LogLevel::Warning, "BaseCommission Not Exist, RateKey:%s, Trade:%s", rateKey.c_str(), trade->GetDebugString());
		if (missingRateKeys_.size() < MaxMissingRateKeyCount)
		{
			missingRateKeys_.push_back(rateKey);
		}
	}
}
