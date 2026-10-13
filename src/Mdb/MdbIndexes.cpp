// 本文件由 ../Templates/Cpp/Mdb/MdbIndexes.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdbIndexes.h"
#include "MdbTables.h"
#include <Spark/Core/Utility/Utility.h>
#include <string.h>


using namespace Spark::Core;
namespace QuantTrading
{
	HotInstrumentTableIndexTradingDay::HotInstrumentTableIndexTradingDay(HotInstrumentTable* tableOwner)
		:table_(tableOwner)
	{
	}
	HotInstrumentTableIndexTradingDay::iterator HotInstrumentTableIndexTradingDay::LowerBound(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank, const DateType& TradingDay)
	{
		FillCompareRecord(ExchangeId, ProductId, Rank, TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&CompareHotInstrument);
	}
	HotInstrumentTableIndexTradingDay::iterator HotInstrumentTableIndexTradingDay::UpperBound(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank, const DateType& TradingDay)
	{
		FillCompareRecord(ExchangeId, ProductId, Rank, TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&CompareHotInstrument);
	}
	std::pair<HotInstrumentTableIndexTradingDay::iterator, HotInstrumentTableIndexTradingDay::iterator> HotInstrumentTableIndexTradingDay::EqualRange(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank, const DateType& TradingDay)
	{
		FillCompareRecord(ExchangeId, ProductId, Rank, TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&CompareHotInstrument);
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
	InstrumentTableIndexExchangeId::iterator InstrumentTableIndexExchangeId::LowerBound(const ExchangeIdType& ExchangeId)
	{
		FillCompareRecord(ExchangeId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&CompareInstrument);
	}
	InstrumentTableIndexExchangeId::iterator InstrumentTableIndexExchangeId::UpperBound(const ExchangeIdType& ExchangeId)
	{
		FillCompareRecord(ExchangeId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&CompareInstrument);
	}
	std::pair<InstrumentTableIndexExchangeId::iterator, InstrumentTableIndexExchangeId::iterator> InstrumentTableIndexExchangeId::EqualRange(const ExchangeIdType& ExchangeId)
	{
		FillCompareRecord(ExchangeId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&CompareInstrument);
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
	MdUserLoginSessionTableIndexSessionId::iterator MdUserLoginSessionTableIndexSessionId::LowerBound(const SessionIdType& SessionId)
	{
		FillCompareRecord(SessionId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&CompareMdUserLoginSession);
	}
	MdUserLoginSessionTableIndexSessionId::iterator MdUserLoginSessionTableIndexSessionId::UpperBound(const SessionIdType& SessionId)
	{
		FillCompareRecord(SessionId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&CompareMdUserLoginSession);
	}
	std::pair<MdUserLoginSessionTableIndexSessionId::iterator, MdUserLoginSessionTableIndexSessionId::iterator> MdUserLoginSessionTableIndexSessionId::EqualRange(const SessionIdType& SessionId)
	{
		FillCompareRecord(SessionId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&CompareMdUserLoginSession);
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
	MdUserLoginSessionTableIndexMdUserId::iterator MdUserLoginSessionTableIndexMdUserId::LowerBound(const UserIdType& MdUserId)
	{
		FillCompareRecord(MdUserId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&CompareMdUserLoginSession);
	}
	MdUserLoginSessionTableIndexMdUserId::iterator MdUserLoginSessionTableIndexMdUserId::UpperBound(const UserIdType& MdUserId)
	{
		FillCompareRecord(MdUserId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&CompareMdUserLoginSession);
	}
	std::pair<MdUserLoginSessionTableIndexMdUserId::iterator, MdUserLoginSessionTableIndexMdUserId::iterator> MdUserLoginSessionTableIndexMdUserId::EqualRange(const UserIdType& MdUserId)
	{
		FillCompareRecord(MdUserId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&CompareMdUserLoginSession);
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
	PrimaryAccountTableIndexOfferId::iterator PrimaryAccountTableIndexOfferId::LowerBound(const OfferIdType& OfferId)
	{
		FillCompareRecord(OfferId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&ComparePrimaryAccount);
	}
	PrimaryAccountTableIndexOfferId::iterator PrimaryAccountTableIndexOfferId::UpperBound(const OfferIdType& OfferId)
	{
		FillCompareRecord(OfferId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&ComparePrimaryAccount);
	}
	std::pair<PrimaryAccountTableIndexOfferId::iterator, PrimaryAccountTableIndexOfferId::iterator> PrimaryAccountTableIndexOfferId::EqualRange(const OfferIdType& OfferId)
	{
		FillCompareRecord(OfferId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&ComparePrimaryAccount);
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
	CapitalTableIndexTradingDay::iterator CapitalTableIndexTradingDay::LowerBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&CompareCapital);
	}
	CapitalTableIndexTradingDay::iterator CapitalTableIndexTradingDay::UpperBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&CompareCapital);
	}
	std::pair<CapitalTableIndexTradingDay::iterator, CapitalTableIndexTradingDay::iterator> CapitalTableIndexTradingDay::EqualRange(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&CompareCapital);
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
	PositionTableIndexAccount::iterator PositionTableIndexAccount::LowerBound(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		FillCompareRecord(TradingDay, AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&ComparePosition);
	}
	PositionTableIndexAccount::iterator PositionTableIndexAccount::UpperBound(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		FillCompareRecord(TradingDay, AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&ComparePosition);
	}
	std::pair<PositionTableIndexAccount::iterator, PositionTableIndexAccount::iterator> PositionTableIndexAccount::EqualRange(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		FillCompareRecord(TradingDay, AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&ComparePosition);
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
	PositionTableIndexTradingDay::iterator PositionTableIndexTradingDay::LowerBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&ComparePosition);
	}
	PositionTableIndexTradingDay::iterator PositionTableIndexTradingDay::UpperBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&ComparePosition);
	}
	std::pair<PositionTableIndexTradingDay::iterator, PositionTableIndexTradingDay::iterator> PositionTableIndexTradingDay::EqualRange(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&ComparePosition);
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
	PositionDetailTableIndexTradeMatch::iterator PositionDetailTableIndexTradeMatch::LowerBound(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection)
	{
		FillCompareRecord(TradingDay, AccountId, ExchangeId, InstrumentId, PosiDirection);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&ComparePositionDetail);
	}
	PositionDetailTableIndexTradeMatch::iterator PositionDetailTableIndexTradeMatch::UpperBound(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection)
	{
		FillCompareRecord(TradingDay, AccountId, ExchangeId, InstrumentId, PosiDirection);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&ComparePositionDetail);
	}
	std::pair<PositionDetailTableIndexTradeMatch::iterator, PositionDetailTableIndexTradeMatch::iterator> PositionDetailTableIndexTradeMatch::EqualRange(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection)
	{
		FillCompareRecord(TradingDay, AccountId, ExchangeId, InstrumentId, PosiDirection);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&ComparePositionDetail);
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
	PositionDetailTableIndexTradingDay::iterator PositionDetailTableIndexTradingDay::LowerBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&ComparePositionDetail);
	}
	PositionDetailTableIndexTradingDay::iterator PositionDetailTableIndexTradingDay::UpperBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&ComparePositionDetail);
	}
	std::pair<PositionDetailTableIndexTradingDay::iterator, PositionDetailTableIndexTradingDay::iterator> PositionDetailTableIndexTradingDay::EqualRange(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&ComparePositionDetail);
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
	OrderTableIndexAccountId::iterator OrderTableIndexAccountId::LowerBound(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		FillCompareRecord(TradingDay, AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&CompareOrder);
	}
	OrderTableIndexAccountId::iterator OrderTableIndexAccountId::UpperBound(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		FillCompareRecord(TradingDay, AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&CompareOrder);
	}
	std::pair<OrderTableIndexAccountId::iterator, OrderTableIndexAccountId::iterator> OrderTableIndexAccountId::EqualRange(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		FillCompareRecord(TradingDay, AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&CompareOrder);
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
	TradeTableIndexAccountId::iterator TradeTableIndexAccountId::LowerBound(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		FillCompareRecord(TradingDay, AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&CompareTrade);
	}
	TradeTableIndexAccountId::iterator TradeTableIndexAccountId::UpperBound(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		FillCompareRecord(TradingDay, AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&CompareTrade);
	}
	std::pair<TradeTableIndexAccountId::iterator, TradeTableIndexAccountId::iterator> TradeTableIndexAccountId::EqualRange(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		FillCompareRecord(TradingDay, AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&CompareTrade);
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
	AccountLoginSessionTableIndexSessionId::iterator AccountLoginSessionTableIndexSessionId::LowerBound(const SessionIdType& SessionId)
	{
		FillCompareRecord(SessionId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&CompareAccountLoginSession);
	}
	AccountLoginSessionTableIndexSessionId::iterator AccountLoginSessionTableIndexSessionId::UpperBound(const SessionIdType& SessionId)
	{
		FillCompareRecord(SessionId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&CompareAccountLoginSession);
	}
	std::pair<AccountLoginSessionTableIndexSessionId::iterator, AccountLoginSessionTableIndexSessionId::iterator> AccountLoginSessionTableIndexSessionId::EqualRange(const SessionIdType& SessionId)
	{
		FillCompareRecord(SessionId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&CompareAccountLoginSession);
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
	AccountLoginSessionTableIndexAccountId::iterator AccountLoginSessionTableIndexAccountId::LowerBound(const AccountIdType& AccountId)
	{
		FillCompareRecord(AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&CompareAccountLoginSession);
	}
	AccountLoginSessionTableIndexAccountId::iterator AccountLoginSessionTableIndexAccountId::UpperBound(const AccountIdType& AccountId)
	{
		FillCompareRecord(AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&CompareAccountLoginSession);
	}
	std::pair<AccountLoginSessionTableIndexAccountId::iterator, AccountLoginSessionTableIndexAccountId::iterator> AccountLoginSessionTableIndexAccountId::EqualRange(const AccountIdType& AccountId)
	{
		FillCompareRecord(AccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&CompareAccountLoginSession);
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
	PrimaryAccountLoginSessionTableIndexSessionId::iterator PrimaryAccountLoginSessionTableIndexSessionId::LowerBound(const SessionIdType& SessionId)
	{
		FillCompareRecord(SessionId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&ComparePrimaryAccountLoginSession);
	}
	PrimaryAccountLoginSessionTableIndexSessionId::iterator PrimaryAccountLoginSessionTableIndexSessionId::UpperBound(const SessionIdType& SessionId)
	{
		FillCompareRecord(SessionId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&ComparePrimaryAccountLoginSession);
	}
	std::pair<PrimaryAccountLoginSessionTableIndexSessionId::iterator, PrimaryAccountLoginSessionTableIndexSessionId::iterator> PrimaryAccountLoginSessionTableIndexSessionId::EqualRange(const SessionIdType& SessionId)
	{
		FillCompareRecord(SessionId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&ComparePrimaryAccountLoginSession);
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
	PrimaryAccountLoginSessionTableIndexPrimaryAccountId::iterator PrimaryAccountLoginSessionTableIndexPrimaryAccountId::LowerBound(const AccountIdType& PrimaryAccountId)
	{
		FillCompareRecord(PrimaryAccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.lower_bound(&ComparePrimaryAccountLoginSession);
	}
	PrimaryAccountLoginSessionTableIndexPrimaryAccountId::iterator PrimaryAccountLoginSessionTableIndexPrimaryAccountId::UpperBound(const AccountIdType& PrimaryAccountId)
	{
		FillCompareRecord(PrimaryAccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.upper_bound(&ComparePrimaryAccountLoginSession);
	}
	std::pair<PrimaryAccountLoginSessionTableIndexPrimaryAccountId::iterator, PrimaryAccountLoginSessionTableIndexPrimaryAccountId::iterator> PrimaryAccountLoginSessionTableIndexPrimaryAccountId::EqualRange(const AccountIdType& PrimaryAccountId)
	{
		FillCompareRecord(PrimaryAccountId);
		std::shared_lock guard(table_->SharedMutex);
		return index_.equal_range(&ComparePrimaryAccountLoginSession);
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
