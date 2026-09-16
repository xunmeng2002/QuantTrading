// 本文件由 ../Templates/Cpp/Mdb/MdbIndexes.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdbIndexes.h"
#include "MdbTables.h"
#include <Spark/Core/Utility/Utility.h>
#include <string.h>


using namespace Spark::Core;
namespace QuantTrading
{
	HotInstrumentIndexTradingDay::HotInstrumentIndexTradingDay(HotInstrumentTable* tableOwner)
		:table_(tableOwner)
	{
	}
	HotInstrumentIndexTradingDay::iterator HotInstrumentIndexTradingDay::LowerBound(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank, const DateType& TradingDay)
	{
		FillCompareRecord(ExchangeId, ProductId, Rank, TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&CompareHotInstrument);
	}
	HotInstrumentIndexTradingDay::iterator HotInstrumentIndexTradingDay::UpperBound(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank, const DateType& TradingDay)
	{
		FillCompareRecord(ExchangeId, ProductId, Rank, TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&CompareHotInstrument);
	}
	std::pair<HotInstrumentIndexTradingDay::iterator, HotInstrumentIndexTradingDay::iterator> HotInstrumentIndexTradingDay::EqualRange(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank, const DateType& TradingDay)
	{
		FillCompareRecord(ExchangeId, ProductId, Rank, TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&CompareHotInstrument);
	}
	void HotInstrumentIndexTradingDay::Insert(HotInstrument* const record)
	{
		index_.insert(record);
	}
	void HotInstrumentIndexTradingDay::Erase(HotInstrument* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void HotInstrumentIndexTradingDay::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool HotInstrumentIndexTradingDay::NeedUpdate(const HotInstrument* const oldRecord, const HotInstrument* const newRecord)
	{
		return !(HotInstrumentEqualForTradingDayIndex()(oldRecord, newRecord));
	}
	HotInstrumentIndexTradingDay::iterator HotInstrumentIndexTradingDay::FindNode(HotInstrument* const record)
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
	void HotInstrumentIndexTradingDay::FillCompareRecord(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank, const DateType& TradingDay)
	{
		Utility::Strcpy(CompareHotInstrument.ExchangeId, ExchangeId);
		Utility::Strcpy(CompareHotInstrument.ProductId, ProductId);
		CompareHotInstrument.Rank = Rank;
		Utility::Strcpy(CompareHotInstrument.TradingDay, TradingDay);
	}
	
	InstrumentIndexExchangeId::InstrumentIndexExchangeId(InstrumentTable* tableOwner)
		:table_(tableOwner)
	{
	}
	InstrumentIndexExchangeId::iterator InstrumentIndexExchangeId::LowerBound(const ExchangeIdType& ExchangeId)
	{
		FillCompareRecord(ExchangeId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&CompareInstrument);
	}
	InstrumentIndexExchangeId::iterator InstrumentIndexExchangeId::UpperBound(const ExchangeIdType& ExchangeId)
	{
		FillCompareRecord(ExchangeId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&CompareInstrument);
	}
	std::pair<InstrumentIndexExchangeId::iterator, InstrumentIndexExchangeId::iterator> InstrumentIndexExchangeId::EqualRange(const ExchangeIdType& ExchangeId)
	{
		FillCompareRecord(ExchangeId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&CompareInstrument);
	}
	void InstrumentIndexExchangeId::Insert(Instrument* const record)
	{
		index_.insert(record);
	}
	void InstrumentIndexExchangeId::Erase(Instrument* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void InstrumentIndexExchangeId::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool InstrumentIndexExchangeId::NeedUpdate(const Instrument* const oldRecord, const Instrument* const newRecord)
	{
		return !(InstrumentEqualForExchangeIdIndex()(oldRecord, newRecord));
	}
	InstrumentIndexExchangeId::iterator InstrumentIndexExchangeId::FindNode(Instrument* const record)
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
	void InstrumentIndexExchangeId::FillCompareRecord(const ExchangeIdType& ExchangeId)
	{
		Utility::Strcpy(CompareInstrument.ExchangeId, ExchangeId);
	}
	
	MdUserLoginSessionIndexSessionId::MdUserLoginSessionIndexSessionId(MdUserLoginSessionTable* tableOwner)
		:table_(tableOwner)
	{
	}
	MdUserLoginSessionIndexSessionId::iterator MdUserLoginSessionIndexSessionId::LowerBound(const SessionIdType& SessionId)
	{
		FillCompareRecord(SessionId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&CompareMdUserLoginSession);
	}
	MdUserLoginSessionIndexSessionId::iterator MdUserLoginSessionIndexSessionId::UpperBound(const SessionIdType& SessionId)
	{
		FillCompareRecord(SessionId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&CompareMdUserLoginSession);
	}
	std::pair<MdUserLoginSessionIndexSessionId::iterator, MdUserLoginSessionIndexSessionId::iterator> MdUserLoginSessionIndexSessionId::EqualRange(const SessionIdType& SessionId)
	{
		FillCompareRecord(SessionId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&CompareMdUserLoginSession);
	}
	void MdUserLoginSessionIndexSessionId::Insert(MdUserLoginSession* const record)
	{
		index_.insert(record);
	}
	void MdUserLoginSessionIndexSessionId::Erase(MdUserLoginSession* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void MdUserLoginSessionIndexSessionId::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool MdUserLoginSessionIndexSessionId::NeedUpdate(const MdUserLoginSession* const oldRecord, const MdUserLoginSession* const newRecord)
	{
		return !(MdUserLoginSessionEqualForSessionIdIndex()(oldRecord, newRecord));
	}
	MdUserLoginSessionIndexSessionId::iterator MdUserLoginSessionIndexSessionId::FindNode(MdUserLoginSession* const record)
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
	void MdUserLoginSessionIndexSessionId::FillCompareRecord(const SessionIdType& SessionId)
	{
		CompareMdUserLoginSession.SessionId = SessionId;
	}
	
	MdUserLoginSessionIndexMdUserId::MdUserLoginSessionIndexMdUserId(MdUserLoginSessionTable* tableOwner)
		:table_(tableOwner)
	{
	}
	MdUserLoginSessionIndexMdUserId::iterator MdUserLoginSessionIndexMdUserId::LowerBound(const UserIdType& MdUserId)
	{
		FillCompareRecord(MdUserId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&CompareMdUserLoginSession);
	}
	MdUserLoginSessionIndexMdUserId::iterator MdUserLoginSessionIndexMdUserId::UpperBound(const UserIdType& MdUserId)
	{
		FillCompareRecord(MdUserId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&CompareMdUserLoginSession);
	}
	std::pair<MdUserLoginSessionIndexMdUserId::iterator, MdUserLoginSessionIndexMdUserId::iterator> MdUserLoginSessionIndexMdUserId::EqualRange(const UserIdType& MdUserId)
	{
		FillCompareRecord(MdUserId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&CompareMdUserLoginSession);
	}
	void MdUserLoginSessionIndexMdUserId::Insert(MdUserLoginSession* const record)
	{
		index_.insert(record);
	}
	void MdUserLoginSessionIndexMdUserId::Erase(MdUserLoginSession* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void MdUserLoginSessionIndexMdUserId::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool MdUserLoginSessionIndexMdUserId::NeedUpdate(const MdUserLoginSession* const oldRecord, const MdUserLoginSession* const newRecord)
	{
		return !(MdUserLoginSessionEqualForMdUserIdIndex()(oldRecord, newRecord));
	}
	MdUserLoginSessionIndexMdUserId::iterator MdUserLoginSessionIndexMdUserId::FindNode(MdUserLoginSession* const record)
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
	void MdUserLoginSessionIndexMdUserId::FillCompareRecord(const UserIdType& MdUserId)
	{
		Utility::Strcpy(CompareMdUserLoginSession.MdUserId, MdUserId);
	}
	
	PrimaryAccountIndexOfferId::PrimaryAccountIndexOfferId(PrimaryAccountTable* tableOwner)
		:table_(tableOwner)
	{
	}
	PrimaryAccountIndexOfferId::iterator PrimaryAccountIndexOfferId::LowerBound(const OfferIdType& OfferId)
	{
		FillCompareRecord(OfferId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&ComparePrimaryAccount);
	}
	PrimaryAccountIndexOfferId::iterator PrimaryAccountIndexOfferId::UpperBound(const OfferIdType& OfferId)
	{
		FillCompareRecord(OfferId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&ComparePrimaryAccount);
	}
	std::pair<PrimaryAccountIndexOfferId::iterator, PrimaryAccountIndexOfferId::iterator> PrimaryAccountIndexOfferId::EqualRange(const OfferIdType& OfferId)
	{
		FillCompareRecord(OfferId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&ComparePrimaryAccount);
	}
	void PrimaryAccountIndexOfferId::Insert(PrimaryAccount* const record)
	{
		index_.insert(record);
	}
	void PrimaryAccountIndexOfferId::Erase(PrimaryAccount* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void PrimaryAccountIndexOfferId::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool PrimaryAccountIndexOfferId::NeedUpdate(const PrimaryAccount* const oldRecord, const PrimaryAccount* const newRecord)
	{
		return !(PrimaryAccountEqualForOfferIdIndex()(oldRecord, newRecord));
	}
	PrimaryAccountIndexOfferId::iterator PrimaryAccountIndexOfferId::FindNode(PrimaryAccount* const record)
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
	void PrimaryAccountIndexOfferId::FillCompareRecord(const OfferIdType& OfferId)
	{
		ComparePrimaryAccount.OfferId = OfferId;
	}
	
	CapitalIndexTradingDay::CapitalIndexTradingDay(CapitalTable* tableOwner)
		:table_(tableOwner)
	{
	}
	CapitalIndexTradingDay::iterator CapitalIndexTradingDay::LowerBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&CompareCapital);
	}
	CapitalIndexTradingDay::iterator CapitalIndexTradingDay::UpperBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&CompareCapital);
	}
	std::pair<CapitalIndexTradingDay::iterator, CapitalIndexTradingDay::iterator> CapitalIndexTradingDay::EqualRange(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&CompareCapital);
	}
	void CapitalIndexTradingDay::Insert(Capital* const record)
	{
		index_.insert(record);
	}
	void CapitalIndexTradingDay::Erase(Capital* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void CapitalIndexTradingDay::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool CapitalIndexTradingDay::NeedUpdate(const Capital* const oldRecord, const Capital* const newRecord)
	{
		return !(CapitalEqualForTradingDayIndex()(oldRecord, newRecord));
	}
	CapitalIndexTradingDay::iterator CapitalIndexTradingDay::FindNode(Capital* const record)
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
	void CapitalIndexTradingDay::FillCompareRecord(const DateType& TradingDay)
	{
		Utility::Strcpy(CompareCapital.TradingDay, TradingDay);
	}
	
	PositionIndexAccount::PositionIndexAccount(PositionTable* tableOwner)
		:table_(tableOwner)
	{
	}
	PositionIndexAccount::iterator PositionIndexAccount::LowerBound(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		FillCompareRecord(TradingDay, AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&ComparePosition);
	}
	PositionIndexAccount::iterator PositionIndexAccount::UpperBound(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		FillCompareRecord(TradingDay, AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&ComparePosition);
	}
	std::pair<PositionIndexAccount::iterator, PositionIndexAccount::iterator> PositionIndexAccount::EqualRange(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		FillCompareRecord(TradingDay, AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&ComparePosition);
	}
	void PositionIndexAccount::Insert(Position* const record)
	{
		index_.insert(record);
	}
	void PositionIndexAccount::Erase(Position* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void PositionIndexAccount::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool PositionIndexAccount::NeedUpdate(const Position* const oldRecord, const Position* const newRecord)
	{
		return !(PositionEqualForAccountIndex()(oldRecord, newRecord));
	}
	PositionIndexAccount::iterator PositionIndexAccount::FindNode(Position* const record)
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
	void PositionIndexAccount::FillCompareRecord(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		Utility::Strcpy(ComparePosition.TradingDay, TradingDay);
		Utility::Strcpy(ComparePosition.AccountId, AccountId);
	}
	
	PositionIndexTradingDay::PositionIndexTradingDay(PositionTable* tableOwner)
		:table_(tableOwner)
	{
	}
	PositionIndexTradingDay::iterator PositionIndexTradingDay::LowerBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&ComparePosition);
	}
	PositionIndexTradingDay::iterator PositionIndexTradingDay::UpperBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&ComparePosition);
	}
	std::pair<PositionIndexTradingDay::iterator, PositionIndexTradingDay::iterator> PositionIndexTradingDay::EqualRange(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&ComparePosition);
	}
	void PositionIndexTradingDay::Insert(Position* const record)
	{
		index_.insert(record);
	}
	void PositionIndexTradingDay::Erase(Position* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void PositionIndexTradingDay::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool PositionIndexTradingDay::NeedUpdate(const Position* const oldRecord, const Position* const newRecord)
	{
		return !(PositionEqualForTradingDayIndex()(oldRecord, newRecord));
	}
	PositionIndexTradingDay::iterator PositionIndexTradingDay::FindNode(Position* const record)
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
	void PositionIndexTradingDay::FillCompareRecord(const DateType& TradingDay)
	{
		Utility::Strcpy(ComparePosition.TradingDay, TradingDay);
	}
	
	PositionDetailIndexTradeMatch::PositionDetailIndexTradeMatch(PositionDetailTable* tableOwner)
		:table_(tableOwner)
	{
	}
	PositionDetailIndexTradeMatch::iterator PositionDetailIndexTradeMatch::LowerBound(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection)
	{
		FillCompareRecord(TradingDay, AccountId, ExchangeId, InstrumentId, PosiDirection);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&ComparePositionDetail);
	}
	PositionDetailIndexTradeMatch::iterator PositionDetailIndexTradeMatch::UpperBound(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection)
	{
		FillCompareRecord(TradingDay, AccountId, ExchangeId, InstrumentId, PosiDirection);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&ComparePositionDetail);
	}
	std::pair<PositionDetailIndexTradeMatch::iterator, PositionDetailIndexTradeMatch::iterator> PositionDetailIndexTradeMatch::EqualRange(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection)
	{
		FillCompareRecord(TradingDay, AccountId, ExchangeId, InstrumentId, PosiDirection);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&ComparePositionDetail);
	}
	void PositionDetailIndexTradeMatch::Insert(PositionDetail* const record)
	{
		index_.insert(record);
	}
	void PositionDetailIndexTradeMatch::Erase(PositionDetail* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void PositionDetailIndexTradeMatch::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool PositionDetailIndexTradeMatch::NeedUpdate(const PositionDetail* const oldRecord, const PositionDetail* const newRecord)
	{
		return !(PositionDetailEqualForTradeMatchIndex()(oldRecord, newRecord));
	}
	PositionDetailIndexTradeMatch::iterator PositionDetailIndexTradeMatch::FindNode(PositionDetail* const record)
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
	void PositionDetailIndexTradeMatch::FillCompareRecord(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection)
	{
		Utility::Strcpy(ComparePositionDetail.TradingDay, TradingDay);
		Utility::Strcpy(ComparePositionDetail.AccountId, AccountId);
		Utility::Strcpy(ComparePositionDetail.ExchangeId, ExchangeId);
		Utility::Strcpy(ComparePositionDetail.InstrumentId, InstrumentId);
		ComparePositionDetail.PosiDirection = PosiDirection;
	}
	
	PositionDetailIndexTradingDay::PositionDetailIndexTradingDay(PositionDetailTable* tableOwner)
		:table_(tableOwner)
	{
	}
	PositionDetailIndexTradingDay::iterator PositionDetailIndexTradingDay::LowerBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&ComparePositionDetail);
	}
	PositionDetailIndexTradingDay::iterator PositionDetailIndexTradingDay::UpperBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&ComparePositionDetail);
	}
	std::pair<PositionDetailIndexTradingDay::iterator, PositionDetailIndexTradingDay::iterator> PositionDetailIndexTradingDay::EqualRange(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&ComparePositionDetail);
	}
	void PositionDetailIndexTradingDay::Insert(PositionDetail* const record)
	{
		index_.insert(record);
	}
	void PositionDetailIndexTradingDay::Erase(PositionDetail* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void PositionDetailIndexTradingDay::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool PositionDetailIndexTradingDay::NeedUpdate(const PositionDetail* const oldRecord, const PositionDetail* const newRecord)
	{
		return !(PositionDetailEqualForTradingDayIndex()(oldRecord, newRecord));
	}
	PositionDetailIndexTradingDay::iterator PositionDetailIndexTradingDay::FindNode(PositionDetail* const record)
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
	void PositionDetailIndexTradingDay::FillCompareRecord(const DateType& TradingDay)
	{
		Utility::Strcpy(ComparePositionDetail.TradingDay, TradingDay);
	}
	
	OrderIndexAccountId::OrderIndexAccountId(OrderTable* tableOwner)
		:table_(tableOwner)
	{
	}
	OrderIndexAccountId::iterator OrderIndexAccountId::LowerBound(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		FillCompareRecord(TradingDay, AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&CompareOrder);
	}
	OrderIndexAccountId::iterator OrderIndexAccountId::UpperBound(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		FillCompareRecord(TradingDay, AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&CompareOrder);
	}
	std::pair<OrderIndexAccountId::iterator, OrderIndexAccountId::iterator> OrderIndexAccountId::EqualRange(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		FillCompareRecord(TradingDay, AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&CompareOrder);
	}
	void OrderIndexAccountId::Insert(Order* const record)
	{
		index_.insert(record);
	}
	void OrderIndexAccountId::Erase(Order* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void OrderIndexAccountId::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool OrderIndexAccountId::NeedUpdate(const Order* const oldRecord, const Order* const newRecord)
	{
		return !(OrderEqualForAccountIdIndex()(oldRecord, newRecord));
	}
	OrderIndexAccountId::iterator OrderIndexAccountId::FindNode(Order* const record)
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
	void OrderIndexAccountId::FillCompareRecord(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		Utility::Strcpy(CompareOrder.TradingDay, TradingDay);
		Utility::Strcpy(CompareOrder.AccountId, AccountId);
	}
	
	TradeIndexAccountId::TradeIndexAccountId(TradeTable* tableOwner)
		:table_(tableOwner)
	{
	}
	TradeIndexAccountId::iterator TradeIndexAccountId::LowerBound(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		FillCompareRecord(TradingDay, AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&CompareTrade);
	}
	TradeIndexAccountId::iterator TradeIndexAccountId::UpperBound(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		FillCompareRecord(TradingDay, AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&CompareTrade);
	}
	std::pair<TradeIndexAccountId::iterator, TradeIndexAccountId::iterator> TradeIndexAccountId::EqualRange(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		FillCompareRecord(TradingDay, AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&CompareTrade);
	}
	void TradeIndexAccountId::Insert(Trade* const record)
	{
		index_.insert(record);
	}
	void TradeIndexAccountId::Erase(Trade* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void TradeIndexAccountId::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool TradeIndexAccountId::NeedUpdate(const Trade* const oldRecord, const Trade* const newRecord)
	{
		return !(TradeEqualForAccountIdIndex()(oldRecord, newRecord));
	}
	TradeIndexAccountId::iterator TradeIndexAccountId::FindNode(Trade* const record)
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
	void TradeIndexAccountId::FillCompareRecord(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		Utility::Strcpy(CompareTrade.TradingDay, TradingDay);
		Utility::Strcpy(CompareTrade.AccountId, AccountId);
	}
	
	AccountLoginSessionIndexSessionId::AccountLoginSessionIndexSessionId(AccountLoginSessionTable* tableOwner)
		:table_(tableOwner)
	{
	}
	AccountLoginSessionIndexSessionId::iterator AccountLoginSessionIndexSessionId::LowerBound(const SessionIdType& SessionId)
	{
		FillCompareRecord(SessionId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&CompareAccountLoginSession);
	}
	AccountLoginSessionIndexSessionId::iterator AccountLoginSessionIndexSessionId::UpperBound(const SessionIdType& SessionId)
	{
		FillCompareRecord(SessionId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&CompareAccountLoginSession);
	}
	std::pair<AccountLoginSessionIndexSessionId::iterator, AccountLoginSessionIndexSessionId::iterator> AccountLoginSessionIndexSessionId::EqualRange(const SessionIdType& SessionId)
	{
		FillCompareRecord(SessionId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&CompareAccountLoginSession);
	}
	void AccountLoginSessionIndexSessionId::Insert(AccountLoginSession* const record)
	{
		index_.insert(record);
	}
	void AccountLoginSessionIndexSessionId::Erase(AccountLoginSession* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void AccountLoginSessionIndexSessionId::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool AccountLoginSessionIndexSessionId::NeedUpdate(const AccountLoginSession* const oldRecord, const AccountLoginSession* const newRecord)
	{
		return !(AccountLoginSessionEqualForSessionIdIndex()(oldRecord, newRecord));
	}
	AccountLoginSessionIndexSessionId::iterator AccountLoginSessionIndexSessionId::FindNode(AccountLoginSession* const record)
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
	void AccountLoginSessionIndexSessionId::FillCompareRecord(const SessionIdType& SessionId)
	{
		CompareAccountLoginSession.SessionId = SessionId;
	}
	
	AccountLoginSessionIndexAccountId::AccountLoginSessionIndexAccountId(AccountLoginSessionTable* tableOwner)
		:table_(tableOwner)
	{
	}
	AccountLoginSessionIndexAccountId::iterator AccountLoginSessionIndexAccountId::LowerBound(const AccountIdType& AccountId)
	{
		FillCompareRecord(AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&CompareAccountLoginSession);
	}
	AccountLoginSessionIndexAccountId::iterator AccountLoginSessionIndexAccountId::UpperBound(const AccountIdType& AccountId)
	{
		FillCompareRecord(AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&CompareAccountLoginSession);
	}
	std::pair<AccountLoginSessionIndexAccountId::iterator, AccountLoginSessionIndexAccountId::iterator> AccountLoginSessionIndexAccountId::EqualRange(const AccountIdType& AccountId)
	{
		FillCompareRecord(AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&CompareAccountLoginSession);
	}
	void AccountLoginSessionIndexAccountId::Insert(AccountLoginSession* const record)
	{
		index_.insert(record);
	}
	void AccountLoginSessionIndexAccountId::Erase(AccountLoginSession* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void AccountLoginSessionIndexAccountId::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool AccountLoginSessionIndexAccountId::NeedUpdate(const AccountLoginSession* const oldRecord, const AccountLoginSession* const newRecord)
	{
		return !(AccountLoginSessionEqualForAccountIdIndex()(oldRecord, newRecord));
	}
	AccountLoginSessionIndexAccountId::iterator AccountLoginSessionIndexAccountId::FindNode(AccountLoginSession* const record)
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
	void AccountLoginSessionIndexAccountId::FillCompareRecord(const AccountIdType& AccountId)
	{
		Utility::Strcpy(CompareAccountLoginSession.AccountId, AccountId);
	}
	
	PrimaryAccountLoginSessionIndexSessionId::PrimaryAccountLoginSessionIndexSessionId(PrimaryAccountLoginSessionTable* tableOwner)
		:table_(tableOwner)
	{
	}
	PrimaryAccountLoginSessionIndexSessionId::iterator PrimaryAccountLoginSessionIndexSessionId::LowerBound(const SessionIdType& SessionId)
	{
		FillCompareRecord(SessionId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&ComparePrimaryAccountLoginSession);
	}
	PrimaryAccountLoginSessionIndexSessionId::iterator PrimaryAccountLoginSessionIndexSessionId::UpperBound(const SessionIdType& SessionId)
	{
		FillCompareRecord(SessionId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&ComparePrimaryAccountLoginSession);
	}
	std::pair<PrimaryAccountLoginSessionIndexSessionId::iterator, PrimaryAccountLoginSessionIndexSessionId::iterator> PrimaryAccountLoginSessionIndexSessionId::EqualRange(const SessionIdType& SessionId)
	{
		FillCompareRecord(SessionId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&ComparePrimaryAccountLoginSession);
	}
	void PrimaryAccountLoginSessionIndexSessionId::Insert(PrimaryAccountLoginSession* const record)
	{
		index_.insert(record);
	}
	void PrimaryAccountLoginSessionIndexSessionId::Erase(PrimaryAccountLoginSession* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void PrimaryAccountLoginSessionIndexSessionId::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool PrimaryAccountLoginSessionIndexSessionId::NeedUpdate(const PrimaryAccountLoginSession* const oldRecord, const PrimaryAccountLoginSession* const newRecord)
	{
		return !(PrimaryAccountLoginSessionEqualForSessionIdIndex()(oldRecord, newRecord));
	}
	PrimaryAccountLoginSessionIndexSessionId::iterator PrimaryAccountLoginSessionIndexSessionId::FindNode(PrimaryAccountLoginSession* const record)
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
	void PrimaryAccountLoginSessionIndexSessionId::FillCompareRecord(const SessionIdType& SessionId)
	{
		ComparePrimaryAccountLoginSession.SessionId = SessionId;
	}
	
	PrimaryAccountLoginSessionIndexPrimaryAccountId::PrimaryAccountLoginSessionIndexPrimaryAccountId(PrimaryAccountLoginSessionTable* tableOwner)
		:table_(tableOwner)
	{
	}
	PrimaryAccountLoginSessionIndexPrimaryAccountId::iterator PrimaryAccountLoginSessionIndexPrimaryAccountId::LowerBound(const AccountIdType& PrimaryAccountId)
	{
		FillCompareRecord(PrimaryAccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&ComparePrimaryAccountLoginSession);
	}
	PrimaryAccountLoginSessionIndexPrimaryAccountId::iterator PrimaryAccountLoginSessionIndexPrimaryAccountId::UpperBound(const AccountIdType& PrimaryAccountId)
	{
		FillCompareRecord(PrimaryAccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&ComparePrimaryAccountLoginSession);
	}
	std::pair<PrimaryAccountLoginSessionIndexPrimaryAccountId::iterator, PrimaryAccountLoginSessionIndexPrimaryAccountId::iterator> PrimaryAccountLoginSessionIndexPrimaryAccountId::EqualRange(const AccountIdType& PrimaryAccountId)
	{
		FillCompareRecord(PrimaryAccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&ComparePrimaryAccountLoginSession);
	}
	void PrimaryAccountLoginSessionIndexPrimaryAccountId::Insert(PrimaryAccountLoginSession* const record)
	{
		index_.insert(record);
	}
	void PrimaryAccountLoginSessionIndexPrimaryAccountId::Erase(PrimaryAccountLoginSession* const record)
	{
		auto it = FindNode(record);
		index_.erase(it);
	}
	void PrimaryAccountLoginSessionIndexPrimaryAccountId::Update(iterator it)
	{
		auto record = *it;
		index_.erase(it);
		index_.insert(record);
	}
	bool PrimaryAccountLoginSessionIndexPrimaryAccountId::NeedUpdate(const PrimaryAccountLoginSession* const oldRecord, const PrimaryAccountLoginSession* const newRecord)
	{
		return !(PrimaryAccountLoginSessionEqualForPrimaryAccountIdIndex()(oldRecord, newRecord));
	}
	PrimaryAccountLoginSessionIndexPrimaryAccountId::iterator PrimaryAccountLoginSessionIndexPrimaryAccountId::FindNode(PrimaryAccountLoginSession* const record)
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
	void PrimaryAccountLoginSessionIndexPrimaryAccountId::FillCompareRecord(const AccountIdType& PrimaryAccountId)
	{
		Utility::Strcpy(ComparePrimaryAccountLoginSession.PrimaryAccountId, PrimaryAccountId);
	}
	
}
