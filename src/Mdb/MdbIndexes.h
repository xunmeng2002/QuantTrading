// 本文件由 ../Templates/Cpp/Mdb/MdbIndexes.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include "MdbStructs.h"
#include "MdbIndexComp.h"
#include <set>

using std::multiset;

namespace QuantTrading
{
	class HotInstrumentTable;
	class HotInstrumentIndexTradingDay
	{
		using iterator = std::multiset<HotInstrument*, HotInstrumentLessForTradingDayIndex>::iterator;
		friend class HotInstrumentTable;
	public:
		HotInstrumentIndexTradingDay(HotInstrumentTable* tableOwner);
		iterator LowerBound(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank, const DateType& TradingDay);
		iterator UpperBound(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank, const DateType& TradingDay);
		std::pair<iterator, iterator> EqualRange(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank, const DateType& TradingDay);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(HotInstrument* const record);
		void Erase(HotInstrument* const record);
		void Update(iterator it);
		bool NeedUpdate(const HotInstrument* const oldRecord, const HotInstrument* const newRecord);
		iterator FindNode(HotInstrument* const record);
		void FillCompareRecord(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank, const DateType& TradingDay);

	private:
		HotInstrumentTable* table_;
		multiset<HotInstrument*, HotInstrumentLessForTradingDayIndex> index_;
	};
	
	class InstrumentTable;
	class InstrumentIndexExchangeId
	{
		using iterator = std::multiset<Instrument*, InstrumentLessForExchangeIdIndex>::iterator;
		friend class InstrumentTable;
	public:
		InstrumentIndexExchangeId(InstrumentTable* tableOwner);
		iterator LowerBound(const ExchangeIdType& ExchangeId);
		iterator UpperBound(const ExchangeIdType& ExchangeId);
		std::pair<iterator, iterator> EqualRange(const ExchangeIdType& ExchangeId);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(Instrument* const record);
		void Erase(Instrument* const record);
		void Update(iterator it);
		bool NeedUpdate(const Instrument* const oldRecord, const Instrument* const newRecord);
		iterator FindNode(Instrument* const record);
		void FillCompareRecord(const ExchangeIdType& ExchangeId);

	private:
		InstrumentTable* table_;
		multiset<Instrument*, InstrumentLessForExchangeIdIndex> index_;
	};
	
	class MdUserLoginSessionTable;
	class MdUserLoginSessionIndexSessionId
	{
		using iterator = std::multiset<MdUserLoginSession*, MdUserLoginSessionLessForSessionIdIndex>::iterator;
		friend class MdUserLoginSessionTable;
	public:
		MdUserLoginSessionIndexSessionId(MdUserLoginSessionTable* tableOwner);
		iterator LowerBound(const SessionIdType& SessionId);
		iterator UpperBound(const SessionIdType& SessionId);
		std::pair<iterator, iterator> EqualRange(const SessionIdType& SessionId);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(MdUserLoginSession* const record);
		void Erase(MdUserLoginSession* const record);
		void Update(iterator it);
		bool NeedUpdate(const MdUserLoginSession* const oldRecord, const MdUserLoginSession* const newRecord);
		iterator FindNode(MdUserLoginSession* const record);
		void FillCompareRecord(const SessionIdType& SessionId);

	private:
		MdUserLoginSessionTable* table_;
		multiset<MdUserLoginSession*, MdUserLoginSessionLessForSessionIdIndex> index_;
	};
	
	class MdUserLoginSessionIndexMdUserId
	{
		using iterator = std::multiset<MdUserLoginSession*, MdUserLoginSessionLessForMdUserIdIndex>::iterator;
		friend class MdUserLoginSessionTable;
	public:
		MdUserLoginSessionIndexMdUserId(MdUserLoginSessionTable* tableOwner);
		iterator LowerBound(const UserIdType& MdUserId);
		iterator UpperBound(const UserIdType& MdUserId);
		std::pair<iterator, iterator> EqualRange(const UserIdType& MdUserId);
	public:
		static constexpr unsigned int IndexID = 0x0001;
	protected:
		void Insert(MdUserLoginSession* const record);
		void Erase(MdUserLoginSession* const record);
		void Update(iterator it);
		bool NeedUpdate(const MdUserLoginSession* const oldRecord, const MdUserLoginSession* const newRecord);
		iterator FindNode(MdUserLoginSession* const record);
		void FillCompareRecord(const UserIdType& MdUserId);

	private:
		MdUserLoginSessionTable* table_;
		multiset<MdUserLoginSession*, MdUserLoginSessionLessForMdUserIdIndex> index_;
	};
	
	class PrimaryAccountTable;
	class PrimaryAccountIndexOfferId
	{
		using iterator = std::multiset<PrimaryAccount*, PrimaryAccountLessForOfferIdIndex>::iterator;
		friend class PrimaryAccountTable;
	public:
		PrimaryAccountIndexOfferId(PrimaryAccountTable* tableOwner);
		iterator LowerBound(const OfferIdType& OfferId);
		iterator UpperBound(const OfferIdType& OfferId);
		std::pair<iterator, iterator> EqualRange(const OfferIdType& OfferId);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(PrimaryAccount* const record);
		void Erase(PrimaryAccount* const record);
		void Update(iterator it);
		bool NeedUpdate(const PrimaryAccount* const oldRecord, const PrimaryAccount* const newRecord);
		iterator FindNode(PrimaryAccount* const record);
		void FillCompareRecord(const OfferIdType& OfferId);

	private:
		PrimaryAccountTable* table_;
		multiset<PrimaryAccount*, PrimaryAccountLessForOfferIdIndex> index_;
	};
	
	class CapitalTable;
	class CapitalIndexTradingDay
	{
		using iterator = std::multiset<Capital*, CapitalLessForTradingDayIndex>::iterator;
		friend class CapitalTable;
	public:
		CapitalIndexTradingDay(CapitalTable* tableOwner);
		iterator LowerBound(const DateType& TradingDay);
		iterator UpperBound(const DateType& TradingDay);
		std::pair<iterator, iterator> EqualRange(const DateType& TradingDay);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(Capital* const record);
		void Erase(Capital* const record);
		void Update(iterator it);
		bool NeedUpdate(const Capital* const oldRecord, const Capital* const newRecord);
		iterator FindNode(Capital* const record);
		void FillCompareRecord(const DateType& TradingDay);

	private:
		CapitalTable* table_;
		multiset<Capital*, CapitalLessForTradingDayIndex> index_;
	};
	
	class PositionTable;
	class PositionIndexAccount
	{
		using iterator = std::multiset<Position*, PositionLessForAccountIndex>::iterator;
		friend class PositionTable;
	public:
		PositionIndexAccount(PositionTable* tableOwner);
		iterator LowerBound(const DateType& TradingDay, const AccountIdType& AccountId);
		iterator UpperBound(const DateType& TradingDay, const AccountIdType& AccountId);
		std::pair<iterator, iterator> EqualRange(const DateType& TradingDay, const AccountIdType& AccountId);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(Position* const record);
		void Erase(Position* const record);
		void Update(iterator it);
		bool NeedUpdate(const Position* const oldRecord, const Position* const newRecord);
		iterator FindNode(Position* const record);
		void FillCompareRecord(const DateType& TradingDay, const AccountIdType& AccountId);

	private:
		PositionTable* table_;
		multiset<Position*, PositionLessForAccountIndex> index_;
	};
	
	class PositionIndexTradingDay
	{
		using iterator = std::multiset<Position*, PositionLessForTradingDayIndex>::iterator;
		friend class PositionTable;
	public:
		PositionIndexTradingDay(PositionTable* tableOwner);
		iterator LowerBound(const DateType& TradingDay);
		iterator UpperBound(const DateType& TradingDay);
		std::pair<iterator, iterator> EqualRange(const DateType& TradingDay);
	public:
		static constexpr unsigned int IndexID = 0x0001;
	protected:
		void Insert(Position* const record);
		void Erase(Position* const record);
		void Update(iterator it);
		bool NeedUpdate(const Position* const oldRecord, const Position* const newRecord);
		iterator FindNode(Position* const record);
		void FillCompareRecord(const DateType& TradingDay);

	private:
		PositionTable* table_;
		multiset<Position*, PositionLessForTradingDayIndex> index_;
	};
	
	class PositionDetailTable;
	class PositionDetailIndexTradeMatch
	{
		using iterator = std::multiset<PositionDetail*, PositionDetailLessForTradeMatchIndex>::iterator;
		friend class PositionDetailTable;
	public:
		PositionDetailIndexTradeMatch(PositionDetailTable* tableOwner);
		iterator LowerBound(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection);
		iterator UpperBound(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection);
		std::pair<iterator, iterator> EqualRange(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(PositionDetail* const record);
		void Erase(PositionDetail* const record);
		void Update(iterator it);
		bool NeedUpdate(const PositionDetail* const oldRecord, const PositionDetail* const newRecord);
		iterator FindNode(PositionDetail* const record);
		void FillCompareRecord(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection);

	private:
		PositionDetailTable* table_;
		multiset<PositionDetail*, PositionDetailLessForTradeMatchIndex> index_;
	};
	
	class PositionDetailIndexTradingDay
	{
		using iterator = std::multiset<PositionDetail*, PositionDetailLessForTradingDayIndex>::iterator;
		friend class PositionDetailTable;
	public:
		PositionDetailIndexTradingDay(PositionDetailTable* tableOwner);
		iterator LowerBound(const DateType& TradingDay);
		iterator UpperBound(const DateType& TradingDay);
		std::pair<iterator, iterator> EqualRange(const DateType& TradingDay);
	public:
		static constexpr unsigned int IndexID = 0x0001;
	protected:
		void Insert(PositionDetail* const record);
		void Erase(PositionDetail* const record);
		void Update(iterator it);
		bool NeedUpdate(const PositionDetail* const oldRecord, const PositionDetail* const newRecord);
		iterator FindNode(PositionDetail* const record);
		void FillCompareRecord(const DateType& TradingDay);

	private:
		PositionDetailTable* table_;
		multiset<PositionDetail*, PositionDetailLessForTradingDayIndex> index_;
	};
	
	class OrderTable;
	class OrderIndexAccountId
	{
		using iterator = std::multiset<Order*, OrderLessForAccountIdIndex>::iterator;
		friend class OrderTable;
	public:
		OrderIndexAccountId(OrderTable* tableOwner);
		iterator LowerBound(const DateType& TradingDay, const AccountIdType& AccountId);
		iterator UpperBound(const DateType& TradingDay, const AccountIdType& AccountId);
		std::pair<iterator, iterator> EqualRange(const DateType& TradingDay, const AccountIdType& AccountId);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(Order* const record);
		void Erase(Order* const record);
		void Update(iterator it);
		bool NeedUpdate(const Order* const oldRecord, const Order* const newRecord);
		iterator FindNode(Order* const record);
		void FillCompareRecord(const DateType& TradingDay, const AccountIdType& AccountId);

	private:
		OrderTable* table_;
		multiset<Order*, OrderLessForAccountIdIndex> index_;
	};
	
	class TradeTable;
	class TradeIndexAccountId
	{
		using iterator = std::multiset<Trade*, TradeLessForAccountIdIndex>::iterator;
		friend class TradeTable;
	public:
		TradeIndexAccountId(TradeTable* tableOwner);
		iterator LowerBound(const DateType& TradingDay, const AccountIdType& AccountId);
		iterator UpperBound(const DateType& TradingDay, const AccountIdType& AccountId);
		std::pair<iterator, iterator> EqualRange(const DateType& TradingDay, const AccountIdType& AccountId);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(Trade* const record);
		void Erase(Trade* const record);
		void Update(iterator it);
		bool NeedUpdate(const Trade* const oldRecord, const Trade* const newRecord);
		iterator FindNode(Trade* const record);
		void FillCompareRecord(const DateType& TradingDay, const AccountIdType& AccountId);

	private:
		TradeTable* table_;
		multiset<Trade*, TradeLessForAccountIdIndex> index_;
	};
	
	class AccountLoginSessionTable;
	class AccountLoginSessionIndexSessionId
	{
		using iterator = std::multiset<AccountLoginSession*, AccountLoginSessionLessForSessionIdIndex>::iterator;
		friend class AccountLoginSessionTable;
	public:
		AccountLoginSessionIndexSessionId(AccountLoginSessionTable* tableOwner);
		iterator LowerBound(const SessionIdType& SessionId);
		iterator UpperBound(const SessionIdType& SessionId);
		std::pair<iterator, iterator> EqualRange(const SessionIdType& SessionId);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(AccountLoginSession* const record);
		void Erase(AccountLoginSession* const record);
		void Update(iterator it);
		bool NeedUpdate(const AccountLoginSession* const oldRecord, const AccountLoginSession* const newRecord);
		iterator FindNode(AccountLoginSession* const record);
		void FillCompareRecord(const SessionIdType& SessionId);

	private:
		AccountLoginSessionTable* table_;
		multiset<AccountLoginSession*, AccountLoginSessionLessForSessionIdIndex> index_;
	};
	
	class AccountLoginSessionIndexAccountId
	{
		using iterator = std::multiset<AccountLoginSession*, AccountLoginSessionLessForAccountIdIndex>::iterator;
		friend class AccountLoginSessionTable;
	public:
		AccountLoginSessionIndexAccountId(AccountLoginSessionTable* tableOwner);
		iterator LowerBound(const AccountIdType& AccountId);
		iterator UpperBound(const AccountIdType& AccountId);
		std::pair<iterator, iterator> EqualRange(const AccountIdType& AccountId);
	public:
		static constexpr unsigned int IndexID = 0x0001;
	protected:
		void Insert(AccountLoginSession* const record);
		void Erase(AccountLoginSession* const record);
		void Update(iterator it);
		bool NeedUpdate(const AccountLoginSession* const oldRecord, const AccountLoginSession* const newRecord);
		iterator FindNode(AccountLoginSession* const record);
		void FillCompareRecord(const AccountIdType& AccountId);

	private:
		AccountLoginSessionTable* table_;
		multiset<AccountLoginSession*, AccountLoginSessionLessForAccountIdIndex> index_;
	};
	
	class PrimaryAccountLoginSessionTable;
	class PrimaryAccountLoginSessionIndexSessionId
	{
		using iterator = std::multiset<PrimaryAccountLoginSession*, PrimaryAccountLoginSessionLessForSessionIdIndex>::iterator;
		friend class PrimaryAccountLoginSessionTable;
	public:
		PrimaryAccountLoginSessionIndexSessionId(PrimaryAccountLoginSessionTable* tableOwner);
		iterator LowerBound(const SessionIdType& SessionId);
		iterator UpperBound(const SessionIdType& SessionId);
		std::pair<iterator, iterator> EqualRange(const SessionIdType& SessionId);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(PrimaryAccountLoginSession* const record);
		void Erase(PrimaryAccountLoginSession* const record);
		void Update(iterator it);
		bool NeedUpdate(const PrimaryAccountLoginSession* const oldRecord, const PrimaryAccountLoginSession* const newRecord);
		iterator FindNode(PrimaryAccountLoginSession* const record);
		void FillCompareRecord(const SessionIdType& SessionId);

	private:
		PrimaryAccountLoginSessionTable* table_;
		multiset<PrimaryAccountLoginSession*, PrimaryAccountLoginSessionLessForSessionIdIndex> index_;
	};
	
	class PrimaryAccountLoginSessionIndexPrimaryAccountId
	{
		using iterator = std::multiset<PrimaryAccountLoginSession*, PrimaryAccountLoginSessionLessForPrimaryAccountIdIndex>::iterator;
		friend class PrimaryAccountLoginSessionTable;
	public:
		PrimaryAccountLoginSessionIndexPrimaryAccountId(PrimaryAccountLoginSessionTable* tableOwner);
		iterator LowerBound(const AccountIdType& PrimaryAccountId);
		iterator UpperBound(const AccountIdType& PrimaryAccountId);
		std::pair<iterator, iterator> EqualRange(const AccountIdType& PrimaryAccountId);
	public:
		static constexpr unsigned int IndexID = 0x0001;
	protected:
		void Insert(PrimaryAccountLoginSession* const record);
		void Erase(PrimaryAccountLoginSession* const record);
		void Update(iterator it);
		bool NeedUpdate(const PrimaryAccountLoginSession* const oldRecord, const PrimaryAccountLoginSession* const newRecord);
		iterator FindNode(PrimaryAccountLoginSession* const record);
		void FillCompareRecord(const AccountIdType& PrimaryAccountId);

	private:
		PrimaryAccountLoginSessionTable* table_;
		multiset<PrimaryAccountLoginSession*, PrimaryAccountLoginSessionLessForPrimaryAccountIdIndex> index_;
	};
	
}
