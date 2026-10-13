// 本文件由 ../Templates/Cpp/Mdb/MdbIndexes.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include "MdbStructs.h"
#include "MdbIndexComp.h"
#include <set>

using std::multiset;

namespace QuantTrading
{
	class HotInstrumentTable;
	class HotInstrumentTableIndexTradingDay
	{
	public:
		using iterator = std::multiset<HotInstrument*, HotInstrumentLessForTradingDayIndex>::iterator;
		static constexpr unsigned int IndexID = 0x0000;
	
		HotInstrumentTableIndexTradingDay(HotInstrumentTable* tableOwner);
		iterator LowerBound(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank, const DateType& TradingDay);
		iterator UpperBound(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank, const DateType& TradingDay);
		std::pair<iterator, iterator> EqualRange(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank, const DateType& TradingDay);
	
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
		static constexpr unsigned int IndexID = 0x0000;
	
		InstrumentTableIndexExchangeId(InstrumentTable* tableOwner);
		iterator LowerBound(const ExchangeIdType& ExchangeId);
		iterator UpperBound(const ExchangeIdType& ExchangeId);
		std::pair<iterator, iterator> EqualRange(const ExchangeIdType& ExchangeId);
	
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
		static constexpr unsigned int IndexID = 0x0000;
	
		MdUserLoginSessionTableIndexSessionId(MdUserLoginSessionTable* tableOwner);
		iterator LowerBound(const SessionIdType& SessionId);
		iterator UpperBound(const SessionIdType& SessionId);
		std::pair<iterator, iterator> EqualRange(const SessionIdType& SessionId);
	
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
		static constexpr unsigned int IndexID = 0x0001;
	
		MdUserLoginSessionTableIndexMdUserId(MdUserLoginSessionTable* tableOwner);
		iterator LowerBound(const UserIdType& MdUserId);
		iterator UpperBound(const UserIdType& MdUserId);
		std::pair<iterator, iterator> EqualRange(const UserIdType& MdUserId);
	
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
		static constexpr unsigned int IndexID = 0x0000;
	
		PrimaryAccountTableIndexOfferId(PrimaryAccountTable* tableOwner);
		iterator LowerBound(const OfferIdType& OfferId);
		iterator UpperBound(const OfferIdType& OfferId);
		std::pair<iterator, iterator> EqualRange(const OfferIdType& OfferId);
	
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
		static constexpr unsigned int IndexID = 0x0000;
	
		CapitalTableIndexTradingDay(CapitalTable* tableOwner);
		iterator LowerBound(const DateType& TradingDay);
		iterator UpperBound(const DateType& TradingDay);
		std::pair<iterator, iterator> EqualRange(const DateType& TradingDay);
	
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
		static constexpr unsigned int IndexID = 0x0000;
	
		PositionTableIndexAccount(PositionTable* tableOwner);
		iterator LowerBound(const DateType& TradingDay, const AccountIdType& AccountId);
		iterator UpperBound(const DateType& TradingDay, const AccountIdType& AccountId);
		std::pair<iterator, iterator> EqualRange(const DateType& TradingDay, const AccountIdType& AccountId);
	
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
		static constexpr unsigned int IndexID = 0x0001;
	
		PositionTableIndexTradingDay(PositionTable* tableOwner);
		iterator LowerBound(const DateType& TradingDay);
		iterator UpperBound(const DateType& TradingDay);
		std::pair<iterator, iterator> EqualRange(const DateType& TradingDay);
	
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
		static constexpr unsigned int IndexID = 0x0000;
	
		PositionDetailTableIndexTradeMatch(PositionDetailTable* tableOwner);
		iterator LowerBound(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection);
		iterator UpperBound(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection);
		std::pair<iterator, iterator> EqualRange(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection);
	
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
		static constexpr unsigned int IndexID = 0x0001;
	
		PositionDetailTableIndexTradingDay(PositionDetailTable* tableOwner);
		iterator LowerBound(const DateType& TradingDay);
		iterator UpperBound(const DateType& TradingDay);
		std::pair<iterator, iterator> EqualRange(const DateType& TradingDay);
	
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
		static constexpr unsigned int IndexID = 0x0000;
	
		OrderTableIndexAccountId(OrderTable* tableOwner);
		iterator LowerBound(const DateType& TradingDay, const AccountIdType& AccountId);
		iterator UpperBound(const DateType& TradingDay, const AccountIdType& AccountId);
		std::pair<iterator, iterator> EqualRange(const DateType& TradingDay, const AccountIdType& AccountId);
	
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
		static constexpr unsigned int IndexID = 0x0000;
	
		TradeTableIndexAccountId(TradeTable* tableOwner);
		iterator LowerBound(const DateType& TradingDay, const AccountIdType& AccountId);
		iterator UpperBound(const DateType& TradingDay, const AccountIdType& AccountId);
		std::pair<iterator, iterator> EqualRange(const DateType& TradingDay, const AccountIdType& AccountId);
	
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
		static constexpr unsigned int IndexID = 0x0000;
	
		AccountLoginSessionTableIndexSessionId(AccountLoginSessionTable* tableOwner);
		iterator LowerBound(const SessionIdType& SessionId);
		iterator UpperBound(const SessionIdType& SessionId);
		std::pair<iterator, iterator> EqualRange(const SessionIdType& SessionId);
	
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
		static constexpr unsigned int IndexID = 0x0001;
	
		AccountLoginSessionTableIndexAccountId(AccountLoginSessionTable* tableOwner);
		iterator LowerBound(const AccountIdType& AccountId);
		iterator UpperBound(const AccountIdType& AccountId);
		std::pair<iterator, iterator> EqualRange(const AccountIdType& AccountId);
	
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
		static constexpr unsigned int IndexID = 0x0000;
	
		PrimaryAccountLoginSessionTableIndexSessionId(PrimaryAccountLoginSessionTable* tableOwner);
		iterator LowerBound(const SessionIdType& SessionId);
		iterator UpperBound(const SessionIdType& SessionId);
		std::pair<iterator, iterator> EqualRange(const SessionIdType& SessionId);
	
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
		static constexpr unsigned int IndexID = 0x0001;
	
		PrimaryAccountLoginSessionTableIndexPrimaryAccountId(PrimaryAccountLoginSessionTable* tableOwner);
		iterator LowerBound(const AccountIdType& PrimaryAccountId);
		iterator UpperBound(const AccountIdType& PrimaryAccountId);
		std::pair<iterator, iterator> EqualRange(const AccountIdType& PrimaryAccountId);
	
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
