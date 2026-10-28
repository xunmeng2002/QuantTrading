// 本文件由 ../Templates/Cpp/Mdb/LockBased/MdbIndexes.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include "Common/MdbStructs.h"
#include "Common/MdbIndexComp.h"
#include "Common/MdbReadLease.h"
#include <set>

using std::multiset;

namespace QuantTrading
{
	class HotInstrumentTable;
	class HotInstrumentTableIndexTradingDay
	{
	public:
		using iterator = std::multiset<HotInstrument*, HotInstrumentLessForTradingDayIndex>::iterator;
		static constexpr unsigned int IndexID = HotInstrument::IndexTradingDayId;
	
		HotInstrumentTableIndexTradingDay(HotInstrumentTable* tableOwner);
		TableRangeLease<iterator> Range(const ExchangeIdType& lowerExchangeId, const ProductIdType& lowerProductId, const Int32Type& lowerRank, const DateType& lowerTradingDay, const ExchangeIdType& upperExchangeId, const ProductIdType& upperProductId, const Int32Type& upperRank, const DateType& upperTradingDay);
		TableRangeLease<iterator> EqualRange(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank, const DateType& TradingDay);
	
	protected:
		void Insert(HotInstrument* const record);
		void Erase(HotInstrument* const record);
		void Update(iterator it);
		bool NeedUpdate(const HotInstrument* const oldRecord, const HotInstrument* const newRecord);
		iterator FindNode(HotInstrument* const record);
		void FillCompareRecord(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank, const DateType& TradingDay);

	private:
		friend class HotInstrumentTable;
	
		HotInstrumentTable* table_;
		multiset<HotInstrument*, HotInstrumentLessForTradingDayIndex> index_;
	};
	
	class InstrumentTable;
	class InstrumentTableIndexExchangeId
	{
	public:
		using iterator = std::multiset<Instrument*, InstrumentLessForExchangeIdIndex>::iterator;
		static constexpr unsigned int IndexID = Instrument::IndexExchangeIdId;
	
		InstrumentTableIndexExchangeId(InstrumentTable* tableOwner);
		TableRangeLease<iterator> Range(const ExchangeIdType& lowerExchangeId, const ExchangeIdType& upperExchangeId);
		TableRangeLease<iterator> EqualRange(const ExchangeIdType& ExchangeId);
	
	protected:
		void Insert(Instrument* const record);
		void Erase(Instrument* const record);
		void Update(iterator it);
		bool NeedUpdate(const Instrument* const oldRecord, const Instrument* const newRecord);
		iterator FindNode(Instrument* const record);
		void FillCompareRecord(const ExchangeIdType& ExchangeId);

	private:
		friend class InstrumentTable;
	
		InstrumentTable* table_;
		multiset<Instrument*, InstrumentLessForExchangeIdIndex> index_;
	};
	
	class MdUserLoginSessionTable;
	class MdUserLoginSessionTableIndexSessionId
	{
	public:
		using iterator = std::multiset<MdUserLoginSession*, MdUserLoginSessionLessForSessionIdIndex>::iterator;
		static constexpr unsigned int IndexID = MdUserLoginSession::IndexSessionIdId;
	
		MdUserLoginSessionTableIndexSessionId(MdUserLoginSessionTable* tableOwner);
		TableRangeLease<iterator> Range(const SessionIdType& lowerSessionId, const SessionIdType& upperSessionId);
		TableRangeLease<iterator> EqualRange(const SessionIdType& SessionId);
	
	protected:
		void Insert(MdUserLoginSession* const record);
		void Erase(MdUserLoginSession* const record);
		void Update(iterator it);
		bool NeedUpdate(const MdUserLoginSession* const oldRecord, const MdUserLoginSession* const newRecord);
		iterator FindNode(MdUserLoginSession* const record);
		void FillCompareRecord(const SessionIdType& SessionId);

	private:
		friend class MdUserLoginSessionTable;
	
		MdUserLoginSessionTable* table_;
		multiset<MdUserLoginSession*, MdUserLoginSessionLessForSessionIdIndex> index_;
	};
	
	class MdUserLoginSessionTableIndexMdUserId
	{
	public:
		using iterator = std::multiset<MdUserLoginSession*, MdUserLoginSessionLessForMdUserIdIndex>::iterator;
		static constexpr unsigned int IndexID = MdUserLoginSession::IndexMdUserIdId;
	
		MdUserLoginSessionTableIndexMdUserId(MdUserLoginSessionTable* tableOwner);
		TableRangeLease<iterator> Range(const UserIdType& lowerMdUserId, const UserIdType& upperMdUserId);
		TableRangeLease<iterator> EqualRange(const UserIdType& MdUserId);
	
	protected:
		void Insert(MdUserLoginSession* const record);
		void Erase(MdUserLoginSession* const record);
		void Update(iterator it);
		bool NeedUpdate(const MdUserLoginSession* const oldRecord, const MdUserLoginSession* const newRecord);
		iterator FindNode(MdUserLoginSession* const record);
		void FillCompareRecord(const UserIdType& MdUserId);

	private:
		friend class MdUserLoginSessionTable;
	
		MdUserLoginSessionTable* table_;
		multiset<MdUserLoginSession*, MdUserLoginSessionLessForMdUserIdIndex> index_;
	};
	
	class PrimaryAccountTable;
	class PrimaryAccountTableIndexOfferId
	{
	public:
		using iterator = std::multiset<PrimaryAccount*, PrimaryAccountLessForOfferIdIndex>::iterator;
		static constexpr unsigned int IndexID = PrimaryAccount::IndexOfferIdId;
	
		PrimaryAccountTableIndexOfferId(PrimaryAccountTable* tableOwner);
		TableRangeLease<iterator> Range(const OfferIdType& lowerOfferId, const OfferIdType& upperOfferId);
		TableRangeLease<iterator> EqualRange(const OfferIdType& OfferId);
	
	protected:
		void Insert(PrimaryAccount* const record);
		void Erase(PrimaryAccount* const record);
		void Update(iterator it);
		bool NeedUpdate(const PrimaryAccount* const oldRecord, const PrimaryAccount* const newRecord);
		iterator FindNode(PrimaryAccount* const record);
		void FillCompareRecord(const OfferIdType& OfferId);

	private:
		friend class PrimaryAccountTable;
	
		PrimaryAccountTable* table_;
		multiset<PrimaryAccount*, PrimaryAccountLessForOfferIdIndex> index_;
	};
	
	class CapitalTable;
	class CapitalTableIndexTradingDay
	{
	public:
		using iterator = std::multiset<Capital*, CapitalLessForTradingDayIndex>::iterator;
		static constexpr unsigned int IndexID = Capital::IndexTradingDayId;
	
		CapitalTableIndexTradingDay(CapitalTable* tableOwner);
		TableRangeLease<iterator> Range(const DateType& lowerTradingDay, const DateType& upperTradingDay);
		TableRangeLease<iterator> EqualRange(const DateType& TradingDay);
	
	protected:
		void Insert(Capital* const record);
		void Erase(Capital* const record);
		void Update(iterator it);
		bool NeedUpdate(const Capital* const oldRecord, const Capital* const newRecord);
		iterator FindNode(Capital* const record);
		void FillCompareRecord(const DateType& TradingDay);

	private:
		friend class CapitalTable;
	
		CapitalTable* table_;
		multiset<Capital*, CapitalLessForTradingDayIndex> index_;
	};
	
	class PositionTable;
	class PositionTableIndexAccount
	{
	public:
		using iterator = std::multiset<Position*, PositionLessForAccountIndex>::iterator;
		static constexpr unsigned int IndexID = Position::IndexAccountId;
	
		PositionTableIndexAccount(PositionTable* tableOwner);
		TableRangeLease<iterator> Range(const DateType& lowerTradingDay, const AccountIdType& lowerAccountId, const DateType& upperTradingDay, const AccountIdType& upperAccountId);
		TableRangeLease<iterator> EqualRange(const DateType& TradingDay, const AccountIdType& AccountId);
	
	protected:
		void Insert(Position* const record);
		void Erase(Position* const record);
		void Update(iterator it);
		bool NeedUpdate(const Position* const oldRecord, const Position* const newRecord);
		iterator FindNode(Position* const record);
		void FillCompareRecord(const DateType& TradingDay, const AccountIdType& AccountId);

	private:
		friend class PositionTable;
	
		PositionTable* table_;
		multiset<Position*, PositionLessForAccountIndex> index_;
	};
	
	class PositionTableIndexTradingDay
	{
	public:
		using iterator = std::multiset<Position*, PositionLessForTradingDayIndex>::iterator;
		static constexpr unsigned int IndexID = Position::IndexTradingDayId;
	
		PositionTableIndexTradingDay(PositionTable* tableOwner);
		TableRangeLease<iterator> Range(const DateType& lowerTradingDay, const DateType& upperTradingDay);
		TableRangeLease<iterator> EqualRange(const DateType& TradingDay);
	
	protected:
		void Insert(Position* const record);
		void Erase(Position* const record);
		void Update(iterator it);
		bool NeedUpdate(const Position* const oldRecord, const Position* const newRecord);
		iterator FindNode(Position* const record);
		void FillCompareRecord(const DateType& TradingDay);

	private:
		friend class PositionTable;
	
		PositionTable* table_;
		multiset<Position*, PositionLessForTradingDayIndex> index_;
	};
	
	class PositionDetailTable;
	class PositionDetailTableIndexTradeMatch
	{
	public:
		using iterator = std::multiset<PositionDetail*, PositionDetailLessForTradeMatchIndex>::iterator;
		static constexpr unsigned int IndexID = PositionDetail::IndexTradeMatchId;
	
		PositionDetailTableIndexTradeMatch(PositionDetailTable* tableOwner);
		TableRangeLease<iterator> Range(const DateType& lowerTradingDay, const AccountIdType& lowerAccountId, const ExchangeIdType& lowerExchangeId, const InstrumentIdType& lowerInstrumentId, const PosiDirectionType& lowerPosiDirection, const DateType& upperTradingDay, const AccountIdType& upperAccountId, const ExchangeIdType& upperExchangeId, const InstrumentIdType& upperInstrumentId, const PosiDirectionType& upperPosiDirection);
		TableRangeLease<iterator> EqualRange(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection);
	
	protected:
		void Insert(PositionDetail* const record);
		void Erase(PositionDetail* const record);
		void Update(iterator it);
		bool NeedUpdate(const PositionDetail* const oldRecord, const PositionDetail* const newRecord);
		iterator FindNode(PositionDetail* const record);
		void FillCompareRecord(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection);

	private:
		friend class PositionDetailTable;
	
		PositionDetailTable* table_;
		multiset<PositionDetail*, PositionDetailLessForTradeMatchIndex> index_;
	};
	
	class PositionDetailTableIndexTradingDay
	{
	public:
		using iterator = std::multiset<PositionDetail*, PositionDetailLessForTradingDayIndex>::iterator;
		static constexpr unsigned int IndexID = PositionDetail::IndexTradingDayId;
	
		PositionDetailTableIndexTradingDay(PositionDetailTable* tableOwner);
		TableRangeLease<iterator> Range(const DateType& lowerTradingDay, const DateType& upperTradingDay);
		TableRangeLease<iterator> EqualRange(const DateType& TradingDay);
	
	protected:
		void Insert(PositionDetail* const record);
		void Erase(PositionDetail* const record);
		void Update(iterator it);
		bool NeedUpdate(const PositionDetail* const oldRecord, const PositionDetail* const newRecord);
		iterator FindNode(PositionDetail* const record);
		void FillCompareRecord(const DateType& TradingDay);

	private:
		friend class PositionDetailTable;
	
		PositionDetailTable* table_;
		multiset<PositionDetail*, PositionDetailLessForTradingDayIndex> index_;
	};
	
	class OrderTable;
	class OrderTableIndexAccountId
	{
	public:
		using iterator = std::multiset<Order*, OrderLessForAccountIdIndex>::iterator;
		static constexpr unsigned int IndexID = Order::IndexAccountIdId;
	
		OrderTableIndexAccountId(OrderTable* tableOwner);
		TableRangeLease<iterator> Range(const DateType& lowerTradingDay, const AccountIdType& lowerAccountId, const DateType& upperTradingDay, const AccountIdType& upperAccountId);
		TableRangeLease<iterator> EqualRange(const DateType& TradingDay, const AccountIdType& AccountId);
	
	protected:
		void Insert(Order* const record);
		void Erase(Order* const record);
		void Update(iterator it);
		bool NeedUpdate(const Order* const oldRecord, const Order* const newRecord);
		iterator FindNode(Order* const record);
		void FillCompareRecord(const DateType& TradingDay, const AccountIdType& AccountId);

	private:
		friend class OrderTable;
	
		OrderTable* table_;
		multiset<Order*, OrderLessForAccountIdIndex> index_;
	};
	
	class TradeTable;
	class TradeTableIndexAccountId
	{
	public:
		using iterator = std::multiset<Trade*, TradeLessForAccountIdIndex>::iterator;
		static constexpr unsigned int IndexID = Trade::IndexAccountIdId;
	
		TradeTableIndexAccountId(TradeTable* tableOwner);
		TableRangeLease<iterator> Range(const DateType& lowerTradingDay, const AccountIdType& lowerAccountId, const DateType& upperTradingDay, const AccountIdType& upperAccountId);
		TableRangeLease<iterator> EqualRange(const DateType& TradingDay, const AccountIdType& AccountId);
	
	protected:
		void Insert(Trade* const record);
		void Erase(Trade* const record);
		void Update(iterator it);
		bool NeedUpdate(const Trade* const oldRecord, const Trade* const newRecord);
		iterator FindNode(Trade* const record);
		void FillCompareRecord(const DateType& TradingDay, const AccountIdType& AccountId);

	private:
		friend class TradeTable;
	
		TradeTable* table_;
		multiset<Trade*, TradeLessForAccountIdIndex> index_;
	};
	
	class AccountLoginSessionTable;
	class AccountLoginSessionTableIndexSessionId
	{
	public:
		using iterator = std::multiset<AccountLoginSession*, AccountLoginSessionLessForSessionIdIndex>::iterator;
		static constexpr unsigned int IndexID = AccountLoginSession::IndexSessionIdId;
	
		AccountLoginSessionTableIndexSessionId(AccountLoginSessionTable* tableOwner);
		TableRangeLease<iterator> Range(const SessionIdType& lowerSessionId, const SessionIdType& upperSessionId);
		TableRangeLease<iterator> EqualRange(const SessionIdType& SessionId);
	
	protected:
		void Insert(AccountLoginSession* const record);
		void Erase(AccountLoginSession* const record);
		void Update(iterator it);
		bool NeedUpdate(const AccountLoginSession* const oldRecord, const AccountLoginSession* const newRecord);
		iterator FindNode(AccountLoginSession* const record);
		void FillCompareRecord(const SessionIdType& SessionId);

	private:
		friend class AccountLoginSessionTable;
	
		AccountLoginSessionTable* table_;
		multiset<AccountLoginSession*, AccountLoginSessionLessForSessionIdIndex> index_;
	};
	
	class AccountLoginSessionTableIndexAccountId
	{
	public:
		using iterator = std::multiset<AccountLoginSession*, AccountLoginSessionLessForAccountIdIndex>::iterator;
		static constexpr unsigned int IndexID = AccountLoginSession::IndexAccountIdId;
	
		AccountLoginSessionTableIndexAccountId(AccountLoginSessionTable* tableOwner);
		TableRangeLease<iterator> Range(const AccountIdType& lowerAccountId, const AccountIdType& upperAccountId);
		TableRangeLease<iterator> EqualRange(const AccountIdType& AccountId);
	
	protected:
		void Insert(AccountLoginSession* const record);
		void Erase(AccountLoginSession* const record);
		void Update(iterator it);
		bool NeedUpdate(const AccountLoginSession* const oldRecord, const AccountLoginSession* const newRecord);
		iterator FindNode(AccountLoginSession* const record);
		void FillCompareRecord(const AccountIdType& AccountId);

	private:
		friend class AccountLoginSessionTable;
	
		AccountLoginSessionTable* table_;
		multiset<AccountLoginSession*, AccountLoginSessionLessForAccountIdIndex> index_;
	};
	
	class PrimaryAccountLoginSessionTable;
	class PrimaryAccountLoginSessionTableIndexSessionId
	{
	public:
		using iterator = std::multiset<PrimaryAccountLoginSession*, PrimaryAccountLoginSessionLessForSessionIdIndex>::iterator;
		static constexpr unsigned int IndexID = PrimaryAccountLoginSession::IndexSessionIdId;
	
		PrimaryAccountLoginSessionTableIndexSessionId(PrimaryAccountLoginSessionTable* tableOwner);
		TableRangeLease<iterator> Range(const SessionIdType& lowerSessionId, const SessionIdType& upperSessionId);
		TableRangeLease<iterator> EqualRange(const SessionIdType& SessionId);
	
	protected:
		void Insert(PrimaryAccountLoginSession* const record);
		void Erase(PrimaryAccountLoginSession* const record);
		void Update(iterator it);
		bool NeedUpdate(const PrimaryAccountLoginSession* const oldRecord, const PrimaryAccountLoginSession* const newRecord);
		iterator FindNode(PrimaryAccountLoginSession* const record);
		void FillCompareRecord(const SessionIdType& SessionId);

	private:
		friend class PrimaryAccountLoginSessionTable;
	
		PrimaryAccountLoginSessionTable* table_;
		multiset<PrimaryAccountLoginSession*, PrimaryAccountLoginSessionLessForSessionIdIndex> index_;
	};
	
	class PrimaryAccountLoginSessionTableIndexPrimaryAccountId
	{
	public:
		using iterator = std::multiset<PrimaryAccountLoginSession*, PrimaryAccountLoginSessionLessForPrimaryAccountIdIndex>::iterator;
		static constexpr unsigned int IndexID = PrimaryAccountLoginSession::IndexPrimaryAccountIdId;
	
		PrimaryAccountLoginSessionTableIndexPrimaryAccountId(PrimaryAccountLoginSessionTable* tableOwner);
		TableRangeLease<iterator> Range(const AccountIdType& lowerPrimaryAccountId, const AccountIdType& upperPrimaryAccountId);
		TableRangeLease<iterator> EqualRange(const AccountIdType& PrimaryAccountId);
	
	protected:
		void Insert(PrimaryAccountLoginSession* const record);
		void Erase(PrimaryAccountLoginSession* const record);
		void Update(iterator it);
		bool NeedUpdate(const PrimaryAccountLoginSession* const oldRecord, const PrimaryAccountLoginSession* const newRecord);
		iterator FindNode(PrimaryAccountLoginSession* const record);
		void FillCompareRecord(const AccountIdType& PrimaryAccountId);

	private:
		friend class PrimaryAccountLoginSessionTable;
	
		PrimaryAccountLoginSessionTable* table_;
		multiset<PrimaryAccountLoginSession*, PrimaryAccountLoginSessionLessForPrimaryAccountIdIndex> index_;
	};
	
}
