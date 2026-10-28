// 本文件由 ../Templates/Cpp/Mdb/LockBased/MdbIndexes.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdbIndexes.h"
#include "MdbTables.h"
#include <Spark/Core/Utility/Utility.h>
#include <string.h>
#include <utility>


using namespace Spark::Core;
namespace QuantTrading
{
	HotInstrumentTableIndexTradingDay::HotInstrumentTableIndexTradingDay(HotInstrumentTable* tableOwner)
		:table_(tableOwner)
	{
	}
	TableRangeLease<HotInstrumentTableIndexTradingDay::iterator> HotInstrumentTableIndexTradingDay::Range(const ExchangeIdType& lowerExchangeId, const ProductIdType& lowerProductId, const Int32Type& lowerRank, const DateType& lowerTradingDay, const ExchangeIdType& upperExchangeId, const ProductIdType& upperProductId, const Int32Type& upperRank, const DateType& upperTradingDay)
	{
		FillCompareRecord(lowerExchangeId, lowerProductId, lowerRank, lowerTradingDay);
		std::shared_lock guard(table_->SharedMutex);
		auto first = index_.lower_bound(&CompareHotInstrument);
		FillCompareRecord(upperExchangeId, upperProductId, upperRank, upperTradingDay);
		auto last = index_.upper_bound(&CompareHotInstrument);
		return TableRangeLease<iterator>(std::move(guard), first, last);
	}
	TableRangeLease<HotInstrumentTableIndexTradingDay::iterator> HotInstrumentTableIndexTradingDay::EqualRange(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank, const DateType& TradingDay)
	{
		FillCompareRecord(ExchangeId, ProductId, Rank, TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		auto range = index_.equal_range(&CompareHotInstrument);
		return TableRangeLease<iterator>(std::move(guard), range.first, range.second);
	}
	void HotInstrumentTableIndexTradingDay::Insert(HotInstrument* const record)
	{
		index_.insert(record);
	}
	void HotInstrumentTableIndexTradingDay::Erase(HotInstrument* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void HotInstrumentTableIndexTradingDay::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool HotInstrumentTableIndexTradingDay::NeedUpdate(const HotInstrument* const oldRecord, const HotInstrument* const newRecord)
	{
		return !(HotInstrumentEqualForTradingDayIndex()(oldRecord, newRecord));
	}
	HotInstrumentTableIndexTradingDay::iterator HotInstrumentTableIndexTradingDay::FindNode(HotInstrument* const record)
	{
		auto p = index_.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index_.end();
	}
	void HotInstrumentTableIndexTradingDay::FillCompareRecord(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank, const DateType& TradingDay)
	{
		Utility::Strcpy(CompareHotInstrument.ExchangeId, ExchangeId);
		Utility::Strcpy(CompareHotInstrument.ProductId, ProductId);
		CompareHotInstrument.Rank = Rank;
		Utility::Strcpy(CompareHotInstrument.TradingDay, TradingDay);
	}
	
	InstrumentTableIndexExchangeId::InstrumentTableIndexExchangeId(InstrumentTable* tableOwner)
		:table_(tableOwner)
	{
	}
	TableRangeLease<InstrumentTableIndexExchangeId::iterator> InstrumentTableIndexExchangeId::Range(const ExchangeIdType& lowerExchangeId, const ExchangeIdType& upperExchangeId)
	{
		FillCompareRecord(lowerExchangeId);
		std::shared_lock guard(table_->SharedMutex);
		auto first = index_.lower_bound(&CompareInstrument);
		FillCompareRecord(upperExchangeId);
		auto last = index_.upper_bound(&CompareInstrument);
		return TableRangeLease<iterator>(std::move(guard), first, last);
	}
	TableRangeLease<InstrumentTableIndexExchangeId::iterator> InstrumentTableIndexExchangeId::EqualRange(const ExchangeIdType& ExchangeId)
	{
		FillCompareRecord(ExchangeId);
		std::shared_lock guard(table_->SharedMutex);
		auto range = index_.equal_range(&CompareInstrument);
		return TableRangeLease<iterator>(std::move(guard), range.first, range.second);
	}
	void InstrumentTableIndexExchangeId::Insert(Instrument* const record)
	{
		index_.insert(record);
	}
	void InstrumentTableIndexExchangeId::Erase(Instrument* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void InstrumentTableIndexExchangeId::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool InstrumentTableIndexExchangeId::NeedUpdate(const Instrument* const oldRecord, const Instrument* const newRecord)
	{
		return !(InstrumentEqualForExchangeIdIndex()(oldRecord, newRecord));
	}
	InstrumentTableIndexExchangeId::iterator InstrumentTableIndexExchangeId::FindNode(Instrument* const record)
	{
		auto p = index_.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index_.end();
	}
	void InstrumentTableIndexExchangeId::FillCompareRecord(const ExchangeIdType& ExchangeId)
	{
		Utility::Strcpy(CompareInstrument.ExchangeId, ExchangeId);
	}
	
	MdUserLoginSessionTableIndexSessionId::MdUserLoginSessionTableIndexSessionId(MdUserLoginSessionTable* tableOwner)
		:table_(tableOwner)
	{
	}
	TableRangeLease<MdUserLoginSessionTableIndexSessionId::iterator> MdUserLoginSessionTableIndexSessionId::Range(const SessionIdType& lowerSessionId, const SessionIdType& upperSessionId)
	{
		FillCompareRecord(lowerSessionId);
		std::shared_lock guard(table_->SharedMutex);
		auto first = index_.lower_bound(&CompareMdUserLoginSession);
		FillCompareRecord(upperSessionId);
		auto last = index_.upper_bound(&CompareMdUserLoginSession);
		return TableRangeLease<iterator>(std::move(guard), first, last);
	}
	TableRangeLease<MdUserLoginSessionTableIndexSessionId::iterator> MdUserLoginSessionTableIndexSessionId::EqualRange(const SessionIdType& SessionId)
	{
		FillCompareRecord(SessionId);
		std::shared_lock guard(table_->SharedMutex);
		auto range = index_.equal_range(&CompareMdUserLoginSession);
		return TableRangeLease<iterator>(std::move(guard), range.first, range.second);
	}
	void MdUserLoginSessionTableIndexSessionId::Insert(MdUserLoginSession* const record)
	{
		index_.insert(record);
	}
	void MdUserLoginSessionTableIndexSessionId::Erase(MdUserLoginSession* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void MdUserLoginSessionTableIndexSessionId::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool MdUserLoginSessionTableIndexSessionId::NeedUpdate(const MdUserLoginSession* const oldRecord, const MdUserLoginSession* const newRecord)
	{
		return !(MdUserLoginSessionEqualForSessionIdIndex()(oldRecord, newRecord));
	}
	MdUserLoginSessionTableIndexSessionId::iterator MdUserLoginSessionTableIndexSessionId::FindNode(MdUserLoginSession* const record)
	{
		auto p = index_.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index_.end();
	}
	void MdUserLoginSessionTableIndexSessionId::FillCompareRecord(const SessionIdType& SessionId)
	{
		CompareMdUserLoginSession.SessionId = SessionId;
	}
	
	MdUserLoginSessionTableIndexMdUserId::MdUserLoginSessionTableIndexMdUserId(MdUserLoginSessionTable* tableOwner)
		:table_(tableOwner)
	{
	}
	TableRangeLease<MdUserLoginSessionTableIndexMdUserId::iterator> MdUserLoginSessionTableIndexMdUserId::Range(const UserIdType& lowerMdUserId, const UserIdType& upperMdUserId)
	{
		FillCompareRecord(lowerMdUserId);
		std::shared_lock guard(table_->SharedMutex);
		auto first = index_.lower_bound(&CompareMdUserLoginSession);
		FillCompareRecord(upperMdUserId);
		auto last = index_.upper_bound(&CompareMdUserLoginSession);
		return TableRangeLease<iterator>(std::move(guard), first, last);
	}
	TableRangeLease<MdUserLoginSessionTableIndexMdUserId::iterator> MdUserLoginSessionTableIndexMdUserId::EqualRange(const UserIdType& MdUserId)
	{
		FillCompareRecord(MdUserId);
		std::shared_lock guard(table_->SharedMutex);
		auto range = index_.equal_range(&CompareMdUserLoginSession);
		return TableRangeLease<iterator>(std::move(guard), range.first, range.second);
	}
	void MdUserLoginSessionTableIndexMdUserId::Insert(MdUserLoginSession* const record)
	{
		index_.insert(record);
	}
	void MdUserLoginSessionTableIndexMdUserId::Erase(MdUserLoginSession* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void MdUserLoginSessionTableIndexMdUserId::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool MdUserLoginSessionTableIndexMdUserId::NeedUpdate(const MdUserLoginSession* const oldRecord, const MdUserLoginSession* const newRecord)
	{
		return !(MdUserLoginSessionEqualForMdUserIdIndex()(oldRecord, newRecord));
	}
	MdUserLoginSessionTableIndexMdUserId::iterator MdUserLoginSessionTableIndexMdUserId::FindNode(MdUserLoginSession* const record)
	{
		auto p = index_.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index_.end();
	}
	void MdUserLoginSessionTableIndexMdUserId::FillCompareRecord(const UserIdType& MdUserId)
	{
		Utility::Strcpy(CompareMdUserLoginSession.MdUserId, MdUserId);
	}
	
	PrimaryAccountTableIndexOfferId::PrimaryAccountTableIndexOfferId(PrimaryAccountTable* tableOwner)
		:table_(tableOwner)
	{
	}
	TableRangeLease<PrimaryAccountTableIndexOfferId::iterator> PrimaryAccountTableIndexOfferId::Range(const OfferIdType& lowerOfferId, const OfferIdType& upperOfferId)
	{
		FillCompareRecord(lowerOfferId);
		std::shared_lock guard(table_->SharedMutex);
		auto first = index_.lower_bound(&ComparePrimaryAccount);
		FillCompareRecord(upperOfferId);
		auto last = index_.upper_bound(&ComparePrimaryAccount);
		return TableRangeLease<iterator>(std::move(guard), first, last);
	}
	TableRangeLease<PrimaryAccountTableIndexOfferId::iterator> PrimaryAccountTableIndexOfferId::EqualRange(const OfferIdType& OfferId)
	{
		FillCompareRecord(OfferId);
		std::shared_lock guard(table_->SharedMutex);
		auto range = index_.equal_range(&ComparePrimaryAccount);
		return TableRangeLease<iterator>(std::move(guard), range.first, range.second);
	}
	void PrimaryAccountTableIndexOfferId::Insert(PrimaryAccount* const record)
	{
		index_.insert(record);
	}
	void PrimaryAccountTableIndexOfferId::Erase(PrimaryAccount* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void PrimaryAccountTableIndexOfferId::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool PrimaryAccountTableIndexOfferId::NeedUpdate(const PrimaryAccount* const oldRecord, const PrimaryAccount* const newRecord)
	{
		return !(PrimaryAccountEqualForOfferIdIndex()(oldRecord, newRecord));
	}
	PrimaryAccountTableIndexOfferId::iterator PrimaryAccountTableIndexOfferId::FindNode(PrimaryAccount* const record)
	{
		auto p = index_.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index_.end();
	}
	void PrimaryAccountTableIndexOfferId::FillCompareRecord(const OfferIdType& OfferId)
	{
		ComparePrimaryAccount.OfferId = OfferId;
	}
	
	CapitalTableIndexTradingDay::CapitalTableIndexTradingDay(CapitalTable* tableOwner)
		:table_(tableOwner)
	{
	}
	TableRangeLease<CapitalTableIndexTradingDay::iterator> CapitalTableIndexTradingDay::Range(const DateType& lowerTradingDay, const DateType& upperTradingDay)
	{
		FillCompareRecord(lowerTradingDay);
		std::shared_lock guard(table_->SharedMutex);
		auto first = index_.lower_bound(&CompareCapital);
		FillCompareRecord(upperTradingDay);
		auto last = index_.upper_bound(&CompareCapital);
		return TableRangeLease<iterator>(std::move(guard), first, last);
	}
	TableRangeLease<CapitalTableIndexTradingDay::iterator> CapitalTableIndexTradingDay::EqualRange(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		auto range = index_.equal_range(&CompareCapital);
		return TableRangeLease<iterator>(std::move(guard), range.first, range.second);
	}
	void CapitalTableIndexTradingDay::Insert(Capital* const record)
	{
		index_.insert(record);
	}
	void CapitalTableIndexTradingDay::Erase(Capital* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void CapitalTableIndexTradingDay::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool CapitalTableIndexTradingDay::NeedUpdate(const Capital* const oldRecord, const Capital* const newRecord)
	{
		return !(CapitalEqualForTradingDayIndex()(oldRecord, newRecord));
	}
	CapitalTableIndexTradingDay::iterator CapitalTableIndexTradingDay::FindNode(Capital* const record)
	{
		auto p = index_.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index_.end();
	}
	void CapitalTableIndexTradingDay::FillCompareRecord(const DateType& TradingDay)
	{
		Utility::Strcpy(CompareCapital.TradingDay, TradingDay);
	}
	
	PositionTableIndexAccount::PositionTableIndexAccount(PositionTable* tableOwner)
		:table_(tableOwner)
	{
	}
	TableRangeLease<PositionTableIndexAccount::iterator> PositionTableIndexAccount::Range(const DateType& lowerTradingDay, const AccountIdType& lowerAccountId, const DateType& upperTradingDay, const AccountIdType& upperAccountId)
	{
		FillCompareRecord(lowerTradingDay, lowerAccountId);
		std::shared_lock guard(table_->SharedMutex);
		auto first = index_.lower_bound(&ComparePosition);
		FillCompareRecord(upperTradingDay, upperAccountId);
		auto last = index_.upper_bound(&ComparePosition);
		return TableRangeLease<iterator>(std::move(guard), first, last);
	}
	TableRangeLease<PositionTableIndexAccount::iterator> PositionTableIndexAccount::EqualRange(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		FillCompareRecord(TradingDay, AccountId);
		std::shared_lock guard(table_->SharedMutex);
		auto range = index_.equal_range(&ComparePosition);
		return TableRangeLease<iterator>(std::move(guard), range.first, range.second);
	}
	void PositionTableIndexAccount::Insert(Position* const record)
	{
		index_.insert(record);
	}
	void PositionTableIndexAccount::Erase(Position* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void PositionTableIndexAccount::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool PositionTableIndexAccount::NeedUpdate(const Position* const oldRecord, const Position* const newRecord)
	{
		return !(PositionEqualForAccountIndex()(oldRecord, newRecord));
	}
	PositionTableIndexAccount::iterator PositionTableIndexAccount::FindNode(Position* const record)
	{
		auto p = index_.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index_.end();
	}
	void PositionTableIndexAccount::FillCompareRecord(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		Utility::Strcpy(ComparePosition.TradingDay, TradingDay);
		Utility::Strcpy(ComparePosition.AccountId, AccountId);
	}
	
	PositionTableIndexTradingDay::PositionTableIndexTradingDay(PositionTable* tableOwner)
		:table_(tableOwner)
	{
	}
	TableRangeLease<PositionTableIndexTradingDay::iterator> PositionTableIndexTradingDay::Range(const DateType& lowerTradingDay, const DateType& upperTradingDay)
	{
		FillCompareRecord(lowerTradingDay);
		std::shared_lock guard(table_->SharedMutex);
		auto first = index_.lower_bound(&ComparePosition);
		FillCompareRecord(upperTradingDay);
		auto last = index_.upper_bound(&ComparePosition);
		return TableRangeLease<iterator>(std::move(guard), first, last);
	}
	TableRangeLease<PositionTableIndexTradingDay::iterator> PositionTableIndexTradingDay::EqualRange(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		auto range = index_.equal_range(&ComparePosition);
		return TableRangeLease<iterator>(std::move(guard), range.first, range.second);
	}
	void PositionTableIndexTradingDay::Insert(Position* const record)
	{
		index_.insert(record);
	}
	void PositionTableIndexTradingDay::Erase(Position* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void PositionTableIndexTradingDay::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool PositionTableIndexTradingDay::NeedUpdate(const Position* const oldRecord, const Position* const newRecord)
	{
		return !(PositionEqualForTradingDayIndex()(oldRecord, newRecord));
	}
	PositionTableIndexTradingDay::iterator PositionTableIndexTradingDay::FindNode(Position* const record)
	{
		auto p = index_.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index_.end();
	}
	void PositionTableIndexTradingDay::FillCompareRecord(const DateType& TradingDay)
	{
		Utility::Strcpy(ComparePosition.TradingDay, TradingDay);
	}
	
	PositionDetailTableIndexTradeMatch::PositionDetailTableIndexTradeMatch(PositionDetailTable* tableOwner)
		:table_(tableOwner)
	{
	}
	TableRangeLease<PositionDetailTableIndexTradeMatch::iterator> PositionDetailTableIndexTradeMatch::Range(const DateType& lowerTradingDay, const AccountIdType& lowerAccountId, const ExchangeIdType& lowerExchangeId, const InstrumentIdType& lowerInstrumentId, const PosiDirectionType& lowerPosiDirection, const DateType& upperTradingDay, const AccountIdType& upperAccountId, const ExchangeIdType& upperExchangeId, const InstrumentIdType& upperInstrumentId, const PosiDirectionType& upperPosiDirection)
	{
		FillCompareRecord(lowerTradingDay, lowerAccountId, lowerExchangeId, lowerInstrumentId, lowerPosiDirection);
		std::shared_lock guard(table_->SharedMutex);
		auto first = index_.lower_bound(&ComparePositionDetail);
		FillCompareRecord(upperTradingDay, upperAccountId, upperExchangeId, upperInstrumentId, upperPosiDirection);
		auto last = index_.upper_bound(&ComparePositionDetail);
		return TableRangeLease<iterator>(std::move(guard), first, last);
	}
	TableRangeLease<PositionDetailTableIndexTradeMatch::iterator> PositionDetailTableIndexTradeMatch::EqualRange(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection)
	{
		FillCompareRecord(TradingDay, AccountId, ExchangeId, InstrumentId, PosiDirection);
		std::shared_lock guard(table_->SharedMutex);
		auto range = index_.equal_range(&ComparePositionDetail);
		return TableRangeLease<iterator>(std::move(guard), range.first, range.second);
	}
	void PositionDetailTableIndexTradeMatch::Insert(PositionDetail* const record)
	{
		index_.insert(record);
	}
	void PositionDetailTableIndexTradeMatch::Erase(PositionDetail* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void PositionDetailTableIndexTradeMatch::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool PositionDetailTableIndexTradeMatch::NeedUpdate(const PositionDetail* const oldRecord, const PositionDetail* const newRecord)
	{
		return !(PositionDetailEqualForTradeMatchIndex()(oldRecord, newRecord));
	}
	PositionDetailTableIndexTradeMatch::iterator PositionDetailTableIndexTradeMatch::FindNode(PositionDetail* const record)
	{
		auto p = index_.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index_.end();
	}
	void PositionDetailTableIndexTradeMatch::FillCompareRecord(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection)
	{
		Utility::Strcpy(ComparePositionDetail.TradingDay, TradingDay);
		Utility::Strcpy(ComparePositionDetail.AccountId, AccountId);
		Utility::Strcpy(ComparePositionDetail.ExchangeId, ExchangeId);
		Utility::Strcpy(ComparePositionDetail.InstrumentId, InstrumentId);
		ComparePositionDetail.PosiDirection = PosiDirection;
	}
	
	PositionDetailTableIndexTradingDay::PositionDetailTableIndexTradingDay(PositionDetailTable* tableOwner)
		:table_(tableOwner)
	{
	}
	TableRangeLease<PositionDetailTableIndexTradingDay::iterator> PositionDetailTableIndexTradingDay::Range(const DateType& lowerTradingDay, const DateType& upperTradingDay)
	{
		FillCompareRecord(lowerTradingDay);
		std::shared_lock guard(table_->SharedMutex);
		auto first = index_.lower_bound(&ComparePositionDetail);
		FillCompareRecord(upperTradingDay);
		auto last = index_.upper_bound(&ComparePositionDetail);
		return TableRangeLease<iterator>(std::move(guard), first, last);
	}
	TableRangeLease<PositionDetailTableIndexTradingDay::iterator> PositionDetailTableIndexTradingDay::EqualRange(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		auto range = index_.equal_range(&ComparePositionDetail);
		return TableRangeLease<iterator>(std::move(guard), range.first, range.second);
	}
	void PositionDetailTableIndexTradingDay::Insert(PositionDetail* const record)
	{
		index_.insert(record);
	}
	void PositionDetailTableIndexTradingDay::Erase(PositionDetail* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void PositionDetailTableIndexTradingDay::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool PositionDetailTableIndexTradingDay::NeedUpdate(const PositionDetail* const oldRecord, const PositionDetail* const newRecord)
	{
		return !(PositionDetailEqualForTradingDayIndex()(oldRecord, newRecord));
	}
	PositionDetailTableIndexTradingDay::iterator PositionDetailTableIndexTradingDay::FindNode(PositionDetail* const record)
	{
		auto p = index_.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index_.end();
	}
	void PositionDetailTableIndexTradingDay::FillCompareRecord(const DateType& TradingDay)
	{
		Utility::Strcpy(ComparePositionDetail.TradingDay, TradingDay);
	}
	
	OrderTableIndexAccountId::OrderTableIndexAccountId(OrderTable* tableOwner)
		:table_(tableOwner)
	{
	}
	TableRangeLease<OrderTableIndexAccountId::iterator> OrderTableIndexAccountId::Range(const DateType& lowerTradingDay, const AccountIdType& lowerAccountId, const DateType& upperTradingDay, const AccountIdType& upperAccountId)
	{
		FillCompareRecord(lowerTradingDay, lowerAccountId);
		std::shared_lock guard(table_->SharedMutex);
		auto first = index_.lower_bound(&CompareOrder);
		FillCompareRecord(upperTradingDay, upperAccountId);
		auto last = index_.upper_bound(&CompareOrder);
		return TableRangeLease<iterator>(std::move(guard), first, last);
	}
	TableRangeLease<OrderTableIndexAccountId::iterator> OrderTableIndexAccountId::EqualRange(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		FillCompareRecord(TradingDay, AccountId);
		std::shared_lock guard(table_->SharedMutex);
		auto range = index_.equal_range(&CompareOrder);
		return TableRangeLease<iterator>(std::move(guard), range.first, range.second);
	}
	void OrderTableIndexAccountId::Insert(Order* const record)
	{
		index_.insert(record);
	}
	void OrderTableIndexAccountId::Erase(Order* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void OrderTableIndexAccountId::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool OrderTableIndexAccountId::NeedUpdate(const Order* const oldRecord, const Order* const newRecord)
	{
		return !(OrderEqualForAccountIdIndex()(oldRecord, newRecord));
	}
	OrderTableIndexAccountId::iterator OrderTableIndexAccountId::FindNode(Order* const record)
	{
		auto p = index_.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index_.end();
	}
	void OrderTableIndexAccountId::FillCompareRecord(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		Utility::Strcpy(CompareOrder.TradingDay, TradingDay);
		Utility::Strcpy(CompareOrder.AccountId, AccountId);
	}
	
	TradeTableIndexAccountId::TradeTableIndexAccountId(TradeTable* tableOwner)
		:table_(tableOwner)
	{
	}
	TableRangeLease<TradeTableIndexAccountId::iterator> TradeTableIndexAccountId::Range(const DateType& lowerTradingDay, const AccountIdType& lowerAccountId, const DateType& upperTradingDay, const AccountIdType& upperAccountId)
	{
		FillCompareRecord(lowerTradingDay, lowerAccountId);
		std::shared_lock guard(table_->SharedMutex);
		auto first = index_.lower_bound(&CompareTrade);
		FillCompareRecord(upperTradingDay, upperAccountId);
		auto last = index_.upper_bound(&CompareTrade);
		return TableRangeLease<iterator>(std::move(guard), first, last);
	}
	TableRangeLease<TradeTableIndexAccountId::iterator> TradeTableIndexAccountId::EqualRange(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		FillCompareRecord(TradingDay, AccountId);
		std::shared_lock guard(table_->SharedMutex);
		auto range = index_.equal_range(&CompareTrade);
		return TableRangeLease<iterator>(std::move(guard), range.first, range.second);
	}
	void TradeTableIndexAccountId::Insert(Trade* const record)
	{
		index_.insert(record);
	}
	void TradeTableIndexAccountId::Erase(Trade* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void TradeTableIndexAccountId::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool TradeTableIndexAccountId::NeedUpdate(const Trade* const oldRecord, const Trade* const newRecord)
	{
		return !(TradeEqualForAccountIdIndex()(oldRecord, newRecord));
	}
	TradeTableIndexAccountId::iterator TradeTableIndexAccountId::FindNode(Trade* const record)
	{
		auto p = index_.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index_.end();
	}
	void TradeTableIndexAccountId::FillCompareRecord(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		Utility::Strcpy(CompareTrade.TradingDay, TradingDay);
		Utility::Strcpy(CompareTrade.AccountId, AccountId);
	}
	
	AccountLoginSessionTableIndexSessionId::AccountLoginSessionTableIndexSessionId(AccountLoginSessionTable* tableOwner)
		:table_(tableOwner)
	{
	}
	TableRangeLease<AccountLoginSessionTableIndexSessionId::iterator> AccountLoginSessionTableIndexSessionId::Range(const SessionIdType& lowerSessionId, const SessionIdType& upperSessionId)
	{
		FillCompareRecord(lowerSessionId);
		std::shared_lock guard(table_->SharedMutex);
		auto first = index_.lower_bound(&CompareAccountLoginSession);
		FillCompareRecord(upperSessionId);
		auto last = index_.upper_bound(&CompareAccountLoginSession);
		return TableRangeLease<iterator>(std::move(guard), first, last);
	}
	TableRangeLease<AccountLoginSessionTableIndexSessionId::iterator> AccountLoginSessionTableIndexSessionId::EqualRange(const SessionIdType& SessionId)
	{
		FillCompareRecord(SessionId);
		std::shared_lock guard(table_->SharedMutex);
		auto range = index_.equal_range(&CompareAccountLoginSession);
		return TableRangeLease<iterator>(std::move(guard), range.first, range.second);
	}
	void AccountLoginSessionTableIndexSessionId::Insert(AccountLoginSession* const record)
	{
		index_.insert(record);
	}
	void AccountLoginSessionTableIndexSessionId::Erase(AccountLoginSession* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void AccountLoginSessionTableIndexSessionId::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool AccountLoginSessionTableIndexSessionId::NeedUpdate(const AccountLoginSession* const oldRecord, const AccountLoginSession* const newRecord)
	{
		return !(AccountLoginSessionEqualForSessionIdIndex()(oldRecord, newRecord));
	}
	AccountLoginSessionTableIndexSessionId::iterator AccountLoginSessionTableIndexSessionId::FindNode(AccountLoginSession* const record)
	{
		auto p = index_.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index_.end();
	}
	void AccountLoginSessionTableIndexSessionId::FillCompareRecord(const SessionIdType& SessionId)
	{
		CompareAccountLoginSession.SessionId = SessionId;
	}
	
	AccountLoginSessionTableIndexAccountId::AccountLoginSessionTableIndexAccountId(AccountLoginSessionTable* tableOwner)
		:table_(tableOwner)
	{
	}
	TableRangeLease<AccountLoginSessionTableIndexAccountId::iterator> AccountLoginSessionTableIndexAccountId::Range(const AccountIdType& lowerAccountId, const AccountIdType& upperAccountId)
	{
		FillCompareRecord(lowerAccountId);
		std::shared_lock guard(table_->SharedMutex);
		auto first = index_.lower_bound(&CompareAccountLoginSession);
		FillCompareRecord(upperAccountId);
		auto last = index_.upper_bound(&CompareAccountLoginSession);
		return TableRangeLease<iterator>(std::move(guard), first, last);
	}
	TableRangeLease<AccountLoginSessionTableIndexAccountId::iterator> AccountLoginSessionTableIndexAccountId::EqualRange(const AccountIdType& AccountId)
	{
		FillCompareRecord(AccountId);
		std::shared_lock guard(table_->SharedMutex);
		auto range = index_.equal_range(&CompareAccountLoginSession);
		return TableRangeLease<iterator>(std::move(guard), range.first, range.second);
	}
	void AccountLoginSessionTableIndexAccountId::Insert(AccountLoginSession* const record)
	{
		index_.insert(record);
	}
	void AccountLoginSessionTableIndexAccountId::Erase(AccountLoginSession* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void AccountLoginSessionTableIndexAccountId::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool AccountLoginSessionTableIndexAccountId::NeedUpdate(const AccountLoginSession* const oldRecord, const AccountLoginSession* const newRecord)
	{
		return !(AccountLoginSessionEqualForAccountIdIndex()(oldRecord, newRecord));
	}
	AccountLoginSessionTableIndexAccountId::iterator AccountLoginSessionTableIndexAccountId::FindNode(AccountLoginSession* const record)
	{
		auto p = index_.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index_.end();
	}
	void AccountLoginSessionTableIndexAccountId::FillCompareRecord(const AccountIdType& AccountId)
	{
		Utility::Strcpy(CompareAccountLoginSession.AccountId, AccountId);
	}
	
	PrimaryAccountLoginSessionTableIndexSessionId::PrimaryAccountLoginSessionTableIndexSessionId(PrimaryAccountLoginSessionTable* tableOwner)
		:table_(tableOwner)
	{
	}
	TableRangeLease<PrimaryAccountLoginSessionTableIndexSessionId::iterator> PrimaryAccountLoginSessionTableIndexSessionId::Range(const SessionIdType& lowerSessionId, const SessionIdType& upperSessionId)
	{
		FillCompareRecord(lowerSessionId);
		std::shared_lock guard(table_->SharedMutex);
		auto first = index_.lower_bound(&ComparePrimaryAccountLoginSession);
		FillCompareRecord(upperSessionId);
		auto last = index_.upper_bound(&ComparePrimaryAccountLoginSession);
		return TableRangeLease<iterator>(std::move(guard), first, last);
	}
	TableRangeLease<PrimaryAccountLoginSessionTableIndexSessionId::iterator> PrimaryAccountLoginSessionTableIndexSessionId::EqualRange(const SessionIdType& SessionId)
	{
		FillCompareRecord(SessionId);
		std::shared_lock guard(table_->SharedMutex);
		auto range = index_.equal_range(&ComparePrimaryAccountLoginSession);
		return TableRangeLease<iterator>(std::move(guard), range.first, range.second);
	}
	void PrimaryAccountLoginSessionTableIndexSessionId::Insert(PrimaryAccountLoginSession* const record)
	{
		index_.insert(record);
	}
	void PrimaryAccountLoginSessionTableIndexSessionId::Erase(PrimaryAccountLoginSession* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void PrimaryAccountLoginSessionTableIndexSessionId::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool PrimaryAccountLoginSessionTableIndexSessionId::NeedUpdate(const PrimaryAccountLoginSession* const oldRecord, const PrimaryAccountLoginSession* const newRecord)
	{
		return !(PrimaryAccountLoginSessionEqualForSessionIdIndex()(oldRecord, newRecord));
	}
	PrimaryAccountLoginSessionTableIndexSessionId::iterator PrimaryAccountLoginSessionTableIndexSessionId::FindNode(PrimaryAccountLoginSession* const record)
	{
		auto p = index_.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index_.end();
	}
	void PrimaryAccountLoginSessionTableIndexSessionId::FillCompareRecord(const SessionIdType& SessionId)
	{
		ComparePrimaryAccountLoginSession.SessionId = SessionId;
	}
	
	PrimaryAccountLoginSessionTableIndexPrimaryAccountId::PrimaryAccountLoginSessionTableIndexPrimaryAccountId(PrimaryAccountLoginSessionTable* tableOwner)
		:table_(tableOwner)
	{
	}
	TableRangeLease<PrimaryAccountLoginSessionTableIndexPrimaryAccountId::iterator> PrimaryAccountLoginSessionTableIndexPrimaryAccountId::Range(const AccountIdType& lowerPrimaryAccountId, const AccountIdType& upperPrimaryAccountId)
	{
		FillCompareRecord(lowerPrimaryAccountId);
		std::shared_lock guard(table_->SharedMutex);
		auto first = index_.lower_bound(&ComparePrimaryAccountLoginSession);
		FillCompareRecord(upperPrimaryAccountId);
		auto last = index_.upper_bound(&ComparePrimaryAccountLoginSession);
		return TableRangeLease<iterator>(std::move(guard), first, last);
	}
	TableRangeLease<PrimaryAccountLoginSessionTableIndexPrimaryAccountId::iterator> PrimaryAccountLoginSessionTableIndexPrimaryAccountId::EqualRange(const AccountIdType& PrimaryAccountId)
	{
		FillCompareRecord(PrimaryAccountId);
		std::shared_lock guard(table_->SharedMutex);
		auto range = index_.equal_range(&ComparePrimaryAccountLoginSession);
		return TableRangeLease<iterator>(std::move(guard), range.first, range.second);
	}
	void PrimaryAccountLoginSessionTableIndexPrimaryAccountId::Insert(PrimaryAccountLoginSession* const record)
	{
		index_.insert(record);
	}
	void PrimaryAccountLoginSessionTableIndexPrimaryAccountId::Erase(PrimaryAccountLoginSession* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void PrimaryAccountLoginSessionTableIndexPrimaryAccountId::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool PrimaryAccountLoginSessionTableIndexPrimaryAccountId::NeedUpdate(const PrimaryAccountLoginSession* const oldRecord, const PrimaryAccountLoginSession* const newRecord)
	{
		return !(PrimaryAccountLoginSessionEqualForPrimaryAccountIdIndex()(oldRecord, newRecord));
	}
	PrimaryAccountLoginSessionTableIndexPrimaryAccountId::iterator PrimaryAccountLoginSessionTableIndexPrimaryAccountId::FindNode(PrimaryAccountLoginSession* const record)
	{
		auto p = index_.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index_.end();
	}
	void PrimaryAccountLoginSessionTableIndexPrimaryAccountId::FillCompareRecord(const AccountIdType& PrimaryAccountId)
	{
		Utility::Strcpy(ComparePrimaryAccountLoginSession.PrimaryAccountId, PrimaryAccountId);
	}
	
}
