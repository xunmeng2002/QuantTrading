// 本文件由 ../Templates/Cpp/Mdb/MdbPrimaryKeyComp.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdbPrimaryKeyComp.h"
#include <string.h>
#include <string>
#include <functional>

using std::string;


namespace QuantTrading
{
	bool TradingDayEqualForTradingDayPrimaryKey::operator()(const TradingDay* const left, const TradingDay* const right) const
	{
		return left->Pk == right->Pk;
	}
	bool TradingDayLessForTradingDayPrimaryKey::operator()(const TradingDay* const left, const TradingDay* const right) const
	{
		if (left->Pk < right->Pk)
			return true;
		else if (left->Pk > right->Pk)
			return false;
		return false;
	}
	size_t TradingDayHashForTradingDayPrimaryKey::operator()(const TradingDay* const record) const
	{
		return std::hash<Int32Type>()(record->Pk);
	}
	bool ExchangeEqualForExchangePrimaryKey::operator()(const Exchange* const left, const Exchange* const right) const
	{
		return strcmp(left->ExchangeId, right->ExchangeId) == 0;
	}
	bool ExchangeLessForExchangePrimaryKey::operator()(const Exchange* const left, const Exchange* const right) const
	{
		if (strcmp(left->ExchangeId, right->ExchangeId) < 0)
			return true;
		else if (strcmp(left->ExchangeId, right->ExchangeId) > 0)
			return false;
		return false;
	}
	size_t ExchangeHashForExchangePrimaryKey::operator()(const Exchange* const record) const
	{
		return std::hash<string>()(record->ExchangeId);
	}
	bool ProductEqualForProductPrimaryKey::operator()(const Product* const left, const Product* const right) const
	{
		return strcmp(left->ExchangeId, right->ExchangeId) == 0 && strcmp(left->ProductId, right->ProductId) == 0;
	}
	bool ProductLessForProductPrimaryKey::operator()(const Product* const left, const Product* const right) const
	{
		if (strcmp(left->ExchangeId, right->ExchangeId) < 0)
			return true;
		else if (strcmp(left->ExchangeId, right->ExchangeId) > 0)
			return false;
		if (strcmp(left->ProductId, right->ProductId) < 0)
			return true;
		else if (strcmp(left->ProductId, right->ProductId) > 0)
			return false;
		return false;
	}
	size_t ProductHashForProductPrimaryKey::operator()(const Product* const record) const
	{
		return std::hash<string>()(record->ExchangeId) + std::hash<string>()(record->ProductId);
	}
	bool HotInstrumentEqualForHotInstrumentPrimaryKey::operator()(const HotInstrument* const left, const HotInstrument* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0 && strcmp(left->ExchangeId, right->ExchangeId) == 0 && strcmp(left->ProductId, right->ProductId) == 0 && left->Rank == right->Rank;
	}
	bool HotInstrumentLessForHotInstrumentPrimaryKey::operator()(const HotInstrument* const left, const HotInstrument* const right) const
	{
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		if (strcmp(left->ExchangeId, right->ExchangeId) < 0)
			return true;
		else if (strcmp(left->ExchangeId, right->ExchangeId) > 0)
			return false;
		if (strcmp(left->ProductId, right->ProductId) < 0)
			return true;
		else if (strcmp(left->ProductId, right->ProductId) > 0)
			return false;
		if (left->Rank < right->Rank)
			return true;
		else if (left->Rank > right->Rank)
			return false;
		return false;
	}
	size_t HotInstrumentHashForHotInstrumentPrimaryKey::operator()(const HotInstrument* const record) const
	{
		return std::hash<string>()(record->TradingDay) + std::hash<string>()(record->ExchangeId) + std::hash<string>()(record->ProductId) + std::hash<Int32Type>()(record->Rank);
	}
	bool InstrumentEqualForInstrumentPrimaryKey::operator()(const Instrument* const left, const Instrument* const right) const
	{
		return strcmp(left->ExchangeId, right->ExchangeId) == 0 && strcmp(left->InstrumentId, right->InstrumentId) == 0;
	}
	bool InstrumentLessForInstrumentPrimaryKey::operator()(const Instrument* const left, const Instrument* const right) const
	{
		if (strcmp(left->ExchangeId, right->ExchangeId) < 0)
			return true;
		else if (strcmp(left->ExchangeId, right->ExchangeId) > 0)
			return false;
		if (strcmp(left->InstrumentId, right->InstrumentId) < 0)
			return true;
		else if (strcmp(left->InstrumentId, right->InstrumentId) > 0)
			return false;
		return false;
	}
	size_t InstrumentHashForInstrumentPrimaryKey::operator()(const Instrument* const record) const
	{
		return std::hash<string>()(record->ExchangeId) + std::hash<string>()(record->InstrumentId);
	}
	bool DepthMarketDataEqualForDepthMarketDataPrimaryKey::operator()(const DepthMarketData* const left, const DepthMarketData* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0 && strcmp(left->ExchangeId, right->ExchangeId) == 0 && strcmp(left->InstrumentId, right->InstrumentId) == 0;
	}
	bool DepthMarketDataLessForDepthMarketDataPrimaryKey::operator()(const DepthMarketData* const left, const DepthMarketData* const right) const
	{
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		if (strcmp(left->ExchangeId, right->ExchangeId) < 0)
			return true;
		else if (strcmp(left->ExchangeId, right->ExchangeId) > 0)
			return false;
		if (strcmp(left->InstrumentId, right->InstrumentId) < 0)
			return true;
		else if (strcmp(left->InstrumentId, right->InstrumentId) > 0)
			return false;
		return false;
	}
	size_t DepthMarketDataHashForDepthMarketDataPrimaryKey::operator()(const DepthMarketData* const record) const
	{
		return std::hash<string>()(record->TradingDay) + std::hash<string>()(record->ExchangeId) + std::hash<string>()(record->InstrumentId);
	}
	bool BarMarketDataEqualForBarMarketDataPrimaryKey::operator()(const BarMarketData* const left, const BarMarketData* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0 && strcmp(left->ExchangeId, right->ExchangeId) == 0 && strcmp(left->InstrumentId, right->InstrumentId) == 0 && left->BarPreces == right->BarPreces && left->BarPeriod == right->BarPeriod && left->BarTime == right->BarTime;
	}
	bool BarMarketDataLessForBarMarketDataPrimaryKey::operator()(const BarMarketData* const left, const BarMarketData* const right) const
	{
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		if (strcmp(left->ExchangeId, right->ExchangeId) < 0)
			return true;
		else if (strcmp(left->ExchangeId, right->ExchangeId) > 0)
			return false;
		if (strcmp(left->InstrumentId, right->InstrumentId) < 0)
			return true;
		else if (strcmp(left->InstrumentId, right->InstrumentId) > 0)
			return false;
		if (left->BarPreces < right->BarPreces)
			return true;
		else if (left->BarPreces > right->BarPreces)
			return false;
		if (left->BarPeriod < right->BarPeriod)
			return true;
		else if (left->BarPeriod > right->BarPeriod)
			return false;
		if (left->BarTime < right->BarTime)
			return true;
		else if (left->BarTime > right->BarTime)
			return false;
		return false;
	}
	size_t BarMarketDataHashForBarMarketDataPrimaryKey::operator()(const BarMarketData* const record) const
	{
		return std::hash<string>()(record->TradingDay) + std::hash<string>()(record->ExchangeId) + std::hash<string>()(record->InstrumentId) + std::hash<BarPrecesType>()(record->BarPreces) + std::hash<Int32Type>()(record->BarPeriod) + std::hash<Int64Type>()(record->BarTime);
	}
	bool MdSubscribeEqualForMdSubscribePrimaryKey::operator()(const MdSubscribe* const left, const MdSubscribe* const right) const
	{
		return strcmp(left->ExchangeId, right->ExchangeId) == 0 && strcmp(left->InstrumentId, right->InstrumentId) == 0 && strcmp(left->StartTradingDay, right->StartTradingDay) == 0;
	}
	bool MdSubscribeLessForMdSubscribePrimaryKey::operator()(const MdSubscribe* const left, const MdSubscribe* const right) const
	{
		if (strcmp(left->ExchangeId, right->ExchangeId) < 0)
			return true;
		else if (strcmp(left->ExchangeId, right->ExchangeId) > 0)
			return false;
		if (strcmp(left->InstrumentId, right->InstrumentId) < 0)
			return true;
		else if (strcmp(left->InstrumentId, right->InstrumentId) > 0)
			return false;
		if (strcmp(left->StartTradingDay, right->StartTradingDay) < 0)
			return true;
		else if (strcmp(left->StartTradingDay, right->StartTradingDay) > 0)
			return false;
		return false;
	}
	size_t MdSubscribeHashForMdSubscribePrimaryKey::operator()(const MdSubscribe* const record) const
	{
		return std::hash<string>()(record->ExchangeId) + std::hash<string>()(record->InstrumentId) + std::hash<string>()(record->StartTradingDay);
	}
	bool MdUserEqualForMdUserPrimaryKey::operator()(const MdUser* const left, const MdUser* const right) const
	{
		return strcmp(left->MdUserId, right->MdUserId) == 0;
	}
	bool MdUserLessForMdUserPrimaryKey::operator()(const MdUser* const left, const MdUser* const right) const
	{
		if (strcmp(left->MdUserId, right->MdUserId) < 0)
			return true;
		else if (strcmp(left->MdUserId, right->MdUserId) > 0)
			return false;
		return false;
	}
	size_t MdUserHashForMdUserPrimaryKey::operator()(const MdUser* const record) const
	{
		return std::hash<string>()(record->MdUserId);
	}
	bool MdUserLoginSessionEqualForMdUserLoginSessionPrimaryKey::operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const
	{
		return strcmp(left->MdUserId, right->MdUserId) == 0 && left->SessionId == right->SessionId;
	}
	bool MdUserLoginSessionLessForMdUserLoginSessionPrimaryKey::operator()(const MdUserLoginSession* const left, const MdUserLoginSession* const right) const
	{
		if (strcmp(left->MdUserId, right->MdUserId) < 0)
			return true;
		else if (strcmp(left->MdUserId, right->MdUserId) > 0)
			return false;
		if (left->SessionId < right->SessionId)
			return true;
		else if (left->SessionId > right->SessionId)
			return false;
		return false;
	}
	size_t MdUserLoginSessionHashForMdUserLoginSessionPrimaryKey::operator()(const MdUserLoginSession* const record) const
	{
		return std::hash<string>()(record->MdUserId) + std::hash<SessionIdType>()(record->SessionId);
	}
	bool PrimaryAccountEqualForPrimaryAccountPrimaryKey::operator()(const PrimaryAccount* const left, const PrimaryAccount* const right) const
	{
		return strcmp(left->PrimaryAccountId, right->PrimaryAccountId) == 0;
	}
	bool PrimaryAccountLessForPrimaryAccountPrimaryKey::operator()(const PrimaryAccount* const left, const PrimaryAccount* const right) const
	{
		if (strcmp(left->PrimaryAccountId, right->PrimaryAccountId) < 0)
			return true;
		else if (strcmp(left->PrimaryAccountId, right->PrimaryAccountId) > 0)
			return false;
		return false;
	}
	size_t PrimaryAccountHashForPrimaryAccountPrimaryKey::operator()(const PrimaryAccount* const record) const
	{
		return std::hash<string>()(record->PrimaryAccountId);
	}
	bool AccountEqualForAccountPrimaryKey::operator()(const Account* const left, const Account* const right) const
	{
		return strcmp(left->AccountId, right->AccountId) == 0;
	}
	bool AccountLessForAccountPrimaryKey::operator()(const Account* const left, const Account* const right) const
	{
		if (strcmp(left->AccountId, right->AccountId) < 0)
			return true;
		else if (strcmp(left->AccountId, right->AccountId) > 0)
			return false;
		return false;
	}
	size_t AccountHashForAccountPrimaryKey::operator()(const Account* const record) const
	{
		return std::hash<string>()(record->AccountId);
	}
	bool CapitalEqualForCapitalPrimaryKey::operator()(const Capital* const left, const Capital* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0 && strcmp(left->AccountId, right->AccountId) == 0;
	}
	bool CapitalLessForCapitalPrimaryKey::operator()(const Capital* const left, const Capital* const right) const
	{
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		if (strcmp(left->AccountId, right->AccountId) < 0)
			return true;
		else if (strcmp(left->AccountId, right->AccountId) > 0)
			return false;
		return false;
	}
	size_t CapitalHashForCapitalPrimaryKey::operator()(const Capital* const record) const
	{
		return std::hash<string>()(record->TradingDay) + std::hash<string>()(record->AccountId);
	}
	bool PositionEqualForPositionPrimaryKey::operator()(const Position* const left, const Position* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0 && strcmp(left->AccountId, right->AccountId) == 0 && strcmp(left->ExchangeId, right->ExchangeId) == 0 && strcmp(left->InstrumentId, right->InstrumentId) == 0 && left->PosiDirection == right->PosiDirection;
	}
	bool PositionLessForPositionPrimaryKey::operator()(const Position* const left, const Position* const right) const
	{
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		if (strcmp(left->AccountId, right->AccountId) < 0)
			return true;
		else if (strcmp(left->AccountId, right->AccountId) > 0)
			return false;
		if (strcmp(left->ExchangeId, right->ExchangeId) < 0)
			return true;
		else if (strcmp(left->ExchangeId, right->ExchangeId) > 0)
			return false;
		if (strcmp(left->InstrumentId, right->InstrumentId) < 0)
			return true;
		else if (strcmp(left->InstrumentId, right->InstrumentId) > 0)
			return false;
		if (left->PosiDirection < right->PosiDirection)
			return true;
		else if (left->PosiDirection > right->PosiDirection)
			return false;
		return false;
	}
	size_t PositionHashForPositionPrimaryKey::operator()(const Position* const record) const
	{
		return std::hash<string>()(record->TradingDay) + std::hash<string>()(record->AccountId) + std::hash<string>()(record->ExchangeId) + std::hash<string>()(record->InstrumentId) + std::hash<PosiDirectionType>()(record->PosiDirection);
	}
	bool PositionDetailEqualForPositionDetailPrimaryKey::operator()(const PositionDetail* const left, const PositionDetail* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0 && strcmp(left->AccountId, right->AccountId) == 0 && strcmp(left->ExchangeId, right->ExchangeId) == 0 && strcmp(left->InstrumentId, right->InstrumentId) == 0 && left->PosiDirection == right->PosiDirection && strcmp(left->OpenDate, right->OpenDate) == 0 && strcmp(left->TradeId, right->TradeId) == 0;
	}
	bool PositionDetailLessForPositionDetailPrimaryKey::operator()(const PositionDetail* const left, const PositionDetail* const right) const
	{
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		if (strcmp(left->AccountId, right->AccountId) < 0)
			return true;
		else if (strcmp(left->AccountId, right->AccountId) > 0)
			return false;
		if (strcmp(left->ExchangeId, right->ExchangeId) < 0)
			return true;
		else if (strcmp(left->ExchangeId, right->ExchangeId) > 0)
			return false;
		if (strcmp(left->InstrumentId, right->InstrumentId) < 0)
			return true;
		else if (strcmp(left->InstrumentId, right->InstrumentId) > 0)
			return false;
		if (left->PosiDirection < right->PosiDirection)
			return true;
		else if (left->PosiDirection > right->PosiDirection)
			return false;
		if (strcmp(left->OpenDate, right->OpenDate) < 0)
			return true;
		else if (strcmp(left->OpenDate, right->OpenDate) > 0)
			return false;
		if (strcmp(left->TradeId, right->TradeId) < 0)
			return true;
		else if (strcmp(left->TradeId, right->TradeId) > 0)
			return false;
		return false;
	}
	size_t PositionDetailHashForPositionDetailPrimaryKey::operator()(const PositionDetail* const record) const
	{
		return std::hash<string>()(record->TradingDay) + std::hash<string>()(record->AccountId) + std::hash<string>()(record->ExchangeId) + std::hash<string>()(record->InstrumentId) + std::hash<PosiDirectionType>()(record->PosiDirection) + std::hash<string>()(record->OpenDate) + std::hash<string>()(record->TradeId);
	}
	bool OrderEqualForOrderPrimaryKey::operator()(const Order* const left, const Order* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0 && strcmp(left->AccountId, right->AccountId) == 0 && strcmp(left->ExchangeId, right->ExchangeId) == 0 && strcmp(left->InstrumentId, right->InstrumentId) == 0 && left->OrderId == right->OrderId;
	}
	bool OrderLessForOrderPrimaryKey::operator()(const Order* const left, const Order* const right) const
	{
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		if (strcmp(left->AccountId, right->AccountId) < 0)
			return true;
		else if (strcmp(left->AccountId, right->AccountId) > 0)
			return false;
		if (strcmp(left->ExchangeId, right->ExchangeId) < 0)
			return true;
		else if (strcmp(left->ExchangeId, right->ExchangeId) > 0)
			return false;
		if (strcmp(left->InstrumentId, right->InstrumentId) < 0)
			return true;
		else if (strcmp(left->InstrumentId, right->InstrumentId) > 0)
			return false;
		if (left->OrderId < right->OrderId)
			return true;
		else if (left->OrderId > right->OrderId)
			return false;
		return false;
	}
	size_t OrderHashForOrderPrimaryKey::operator()(const Order* const record) const
	{
		return std::hash<string>()(record->TradingDay) + std::hash<string>()(record->AccountId) + std::hash<string>()(record->ExchangeId) + std::hash<string>()(record->InstrumentId) + std::hash<OrderIdType>()(record->OrderId);
	}
	bool OrderEqualForClientOrderIdUniqueKey::operator()(const Order* const left, const Order* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0 && strcmp(left->AccountId, right->AccountId) == 0 && strcmp(left->ExchangeId, right->ExchangeId) == 0 && strcmp(left->InstrumentId, right->InstrumentId) == 0 && left->SessionId == right->SessionId && left->ClientOrderId == right->ClientOrderId;
	}
	bool OrderLessForClientOrderIdUniqueKey::operator()(const Order* const left, const Order* const right) const
	{
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		if (strcmp(left->AccountId, right->AccountId) < 0)
			return true;
		else if (strcmp(left->AccountId, right->AccountId) > 0)
			return false;
		if (strcmp(left->ExchangeId, right->ExchangeId) < 0)
			return true;
		else if (strcmp(left->ExchangeId, right->ExchangeId) > 0)
			return false;
		if (strcmp(left->InstrumentId, right->InstrumentId) < 0)
			return true;
		else if (strcmp(left->InstrumentId, right->InstrumentId) > 0)
			return false;
		if (left->SessionId < right->SessionId)
			return true;
		else if (left->SessionId > right->SessionId)
			return false;
		if (left->ClientOrderId < right->ClientOrderId)
			return true;
		else if (left->ClientOrderId > right->ClientOrderId)
			return false;
		return false;
	}
	size_t OrderHashForClientOrderIdUniqueKey::operator()(const Order* const record) const
	{
		return std::hash<string>()(record->TradingDay) + std::hash<string>()(record->AccountId) + std::hash<string>()(record->ExchangeId) + std::hash<string>()(record->InstrumentId) + std::hash<SessionIdType>()(record->SessionId) + std::hash<ClientOrderIdType>()(record->ClientOrderId);
	}
	
	bool TradeEqualForTradePrimaryKey::operator()(const Trade* const left, const Trade* const right) const
	{
		return strcmp(left->TradingDay, right->TradingDay) == 0 && strcmp(left->ExchangeId, right->ExchangeId) == 0 && strcmp(left->TradeId, right->TradeId) == 0 && left->Direction == right->Direction;
	}
	bool TradeLessForTradePrimaryKey::operator()(const Trade* const left, const Trade* const right) const
	{
		if (strcmp(left->TradingDay, right->TradingDay) < 0)
			return true;
		else if (strcmp(left->TradingDay, right->TradingDay) > 0)
			return false;
		if (strcmp(left->ExchangeId, right->ExchangeId) < 0)
			return true;
		else if (strcmp(left->ExchangeId, right->ExchangeId) > 0)
			return false;
		if (strcmp(left->TradeId, right->TradeId) < 0)
			return true;
		else if (strcmp(left->TradeId, right->TradeId) > 0)
			return false;
		if (left->Direction < right->Direction)
			return true;
		else if (left->Direction > right->Direction)
			return false;
		return false;
	}
	size_t TradeHashForTradePrimaryKey::operator()(const Trade* const record) const
	{
		return std::hash<string>()(record->TradingDay) + std::hash<string>()(record->ExchangeId) + std::hash<string>()(record->TradeId) + std::hash<DirectionType>()(record->Direction);
	}
	bool AccountLoginSessionEqualForAccountLoginSessionPrimaryKey::operator()(const AccountLoginSession* const left, const AccountLoginSession* const right) const
	{
		return strcmp(left->AccountId, right->AccountId) == 0 && left->SessionId == right->SessionId;
	}
	bool AccountLoginSessionLessForAccountLoginSessionPrimaryKey::operator()(const AccountLoginSession* const left, const AccountLoginSession* const right) const
	{
		if (strcmp(left->AccountId, right->AccountId) < 0)
			return true;
		else if (strcmp(left->AccountId, right->AccountId) > 0)
			return false;
		if (left->SessionId < right->SessionId)
			return true;
		else if (left->SessionId > right->SessionId)
			return false;
		return false;
	}
	size_t AccountLoginSessionHashForAccountLoginSessionPrimaryKey::operator()(const AccountLoginSession* const record) const
	{
		return std::hash<string>()(record->AccountId) + std::hash<SessionIdType>()(record->SessionId);
	}
	bool PrimaryAccountLoginSessionEqualForPrimaryAccountLoginSessionPrimaryKey::operator()(const PrimaryAccountLoginSession* const left, const PrimaryAccountLoginSession* const right) const
	{
		return strcmp(left->PrimaryAccountId, right->PrimaryAccountId) == 0 && left->SessionId == right->SessionId;
	}
	bool PrimaryAccountLoginSessionLessForPrimaryAccountLoginSessionPrimaryKey::operator()(const PrimaryAccountLoginSession* const left, const PrimaryAccountLoginSession* const right) const
	{
		if (strcmp(left->PrimaryAccountId, right->PrimaryAccountId) < 0)
			return true;
		else if (strcmp(left->PrimaryAccountId, right->PrimaryAccountId) > 0)
			return false;
		if (left->SessionId < right->SessionId)
			return true;
		else if (left->SessionId > right->SessionId)
			return false;
		return false;
	}
	size_t PrimaryAccountLoginSessionHashForPrimaryAccountLoginSessionPrimaryKey::operator()(const PrimaryAccountLoginSession* const record) const
	{
		return std::hash<string>()(record->PrimaryAccountId) + std::hash<SessionIdType>()(record->SessionId);
	}
	bool CommissionGroupEqualForCommissionGroupPrimaryKey::operator()(const CommissionGroup* const left, const CommissionGroup* const right) const
	{
		return left->CommissionGroupId == right->CommissionGroupId;
	}
	bool CommissionGroupLessForCommissionGroupPrimaryKey::operator()(const CommissionGroup* const left, const CommissionGroup* const right) const
	{
		if (left->CommissionGroupId < right->CommissionGroupId)
			return true;
		else if (left->CommissionGroupId > right->CommissionGroupId)
			return false;
		return false;
	}
	size_t CommissionGroupHashForCommissionGroupPrimaryKey::operator()(const CommissionGroup* const record) const
	{
		return std::hash<GroupIdType>()(record->CommissionGroupId);
	}
	bool BaseCommissionEqualForBaseCommissionPrimaryKey::operator()(const BaseCommission* const left, const BaseCommission* const right) const
	{
		return left->CommissionGroupId == right->CommissionGroupId && strcmp(left->ExchangeId, right->ExchangeId) == 0 && strcmp(left->InstrumentId, right->InstrumentId) == 0 && left->Direction == right->Direction;
	}
	bool BaseCommissionLessForBaseCommissionPrimaryKey::operator()(const BaseCommission* const left, const BaseCommission* const right) const
	{
		if (left->CommissionGroupId < right->CommissionGroupId)
			return true;
		else if (left->CommissionGroupId > right->CommissionGroupId)
			return false;
		if (strcmp(left->ExchangeId, right->ExchangeId) < 0)
			return true;
		else if (strcmp(left->ExchangeId, right->ExchangeId) > 0)
			return false;
		if (strcmp(left->InstrumentId, right->InstrumentId) < 0)
			return true;
		else if (strcmp(left->InstrumentId, right->InstrumentId) > 0)
			return false;
		if (left->Direction < right->Direction)
			return true;
		else if (left->Direction > right->Direction)
			return false;
		return false;
	}
	size_t BaseCommissionHashForBaseCommissionPrimaryKey::operator()(const BaseCommission* const record) const
	{
		return std::hash<GroupIdType>()(record->CommissionGroupId) + std::hash<string>()(record->ExchangeId) + std::hash<string>()(record->InstrumentId) + std::hash<DirectionType>()(record->Direction);
	}
}
