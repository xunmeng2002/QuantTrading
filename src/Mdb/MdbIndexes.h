// 本文件由 ../Templates/Cpp/Mdb/MdbIndexes.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include "MdbStructs.h"
#include "MdbIndexComp.h"
#include <set>

using std::multiset;

namespace mdb
{
	class HotInstrumentTable;
	class HotInstrumentIndexTradingDay
	{
		using iterator = std::multiset<HotInstrument*, HotInstrumentLessForTradingDayIndex>::iterator;
		friend class HotInstrumentTable;
	public:
		HotInstrumentIndexTradingDay(HotInstrumentTable* tableOwner);
		iterator LowerBound(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const Int32Type& Rank, const DateType& TradingDay);
		iterator UpperBound(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const Int32Type& Rank, const DateType& TradingDay);
		std::pair<iterator, iterator> EqualRange(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const Int32Type& Rank, const DateType& TradingDay);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(HotInstrument* const record);
		void Erase(HotInstrument* const record);
		void Update(iterator it);
		bool NeedUpdate(const HotInstrument* const oldRecord, const HotInstrument* const newRecord);
		iterator FindNode(HotInstrument* const record);
		void FillCompareRecord(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const Int32Type& Rank, const DateType& TradingDay);

	private:
		HotInstrumentTable* table;
		multiset<HotInstrument*, HotInstrumentLessForTradingDayIndex> index;
	};
	
	class InstrumentTable;
	class InstrumentIndexExchangeID
	{
		using iterator = std::multiset<Instrument*, InstrumentLessForExchangeIDIndex>::iterator;
		friend class InstrumentTable;
	public:
		InstrumentIndexExchangeID(InstrumentTable* tableOwner);
		iterator LowerBound(const ExchangeIDType& ExchangeID);
		iterator UpperBound(const ExchangeIDType& ExchangeID);
		std::pair<iterator, iterator> EqualRange(const ExchangeIDType& ExchangeID);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(Instrument* const record);
		void Erase(Instrument* const record);
		void Update(iterator it);
		bool NeedUpdate(const Instrument* const oldRecord, const Instrument* const newRecord);
		iterator FindNode(Instrument* const record);
		void FillCompareRecord(const ExchangeIDType& ExchangeID);

	private:
		InstrumentTable* table;
		multiset<Instrument*, InstrumentLessForExchangeIDIndex> index;
	};
	
	class MdUserLoginSessionTable;
	class MdUserLoginSessionIndexSessionID
	{
		using iterator = std::multiset<MdUserLoginSession*, MdUserLoginSessionLessForSessionIDIndex>::iterator;
		friend class MdUserLoginSessionTable;
	public:
		MdUserLoginSessionIndexSessionID(MdUserLoginSessionTable* tableOwner);
		iterator LowerBound(const SessionIDType& SessionID);
		iterator UpperBound(const SessionIDType& SessionID);
		std::pair<iterator, iterator> EqualRange(const SessionIDType& SessionID);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(MdUserLoginSession* const record);
		void Erase(MdUserLoginSession* const record);
		void Update(iterator it);
		bool NeedUpdate(const MdUserLoginSession* const oldRecord, const MdUserLoginSession* const newRecord);
		iterator FindNode(MdUserLoginSession* const record);
		void FillCompareRecord(const SessionIDType& SessionID);

	private:
		MdUserLoginSessionTable* table;
		multiset<MdUserLoginSession*, MdUserLoginSessionLessForSessionIDIndex> index;
	};
	
	class MdUserLoginSessionIndexMdUserID
	{
		using iterator = std::multiset<MdUserLoginSession*, MdUserLoginSessionLessForMdUserIDIndex>::iterator;
		friend class MdUserLoginSessionTable;
	public:
		MdUserLoginSessionIndexMdUserID(MdUserLoginSessionTable* tableOwner);
		iterator LowerBound(const UserIDType& MdUserID);
		iterator UpperBound(const UserIDType& MdUserID);
		std::pair<iterator, iterator> EqualRange(const UserIDType& MdUserID);
	public:
		static constexpr unsigned int IndexID = 0x0001;
	protected:
		void Insert(MdUserLoginSession* const record);
		void Erase(MdUserLoginSession* const record);
		void Update(iterator it);
		bool NeedUpdate(const MdUserLoginSession* const oldRecord, const MdUserLoginSession* const newRecord);
		iterator FindNode(MdUserLoginSession* const record);
		void FillCompareRecord(const UserIDType& MdUserID);

	private:
		MdUserLoginSessionTable* table;
		multiset<MdUserLoginSession*, MdUserLoginSessionLessForMdUserIDIndex> index;
	};
	
	class PrimaryAccountTable;
	class PrimaryAccountIndexOfferID
	{
		using iterator = std::multiset<PrimaryAccount*, PrimaryAccountLessForOfferIDIndex>::iterator;
		friend class PrimaryAccountTable;
	public:
		PrimaryAccountIndexOfferID(PrimaryAccountTable* tableOwner);
		iterator LowerBound(const OfferIDType& OfferID);
		iterator UpperBound(const OfferIDType& OfferID);
		std::pair<iterator, iterator> EqualRange(const OfferIDType& OfferID);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(PrimaryAccount* const record);
		void Erase(PrimaryAccount* const record);
		void Update(iterator it);
		bool NeedUpdate(const PrimaryAccount* const oldRecord, const PrimaryAccount* const newRecord);
		iterator FindNode(PrimaryAccount* const record);
		void FillCompareRecord(const OfferIDType& OfferID);

	private:
		PrimaryAccountTable* table;
		multiset<PrimaryAccount*, PrimaryAccountLessForOfferIDIndex> index;
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
		CapitalTable* table;
		multiset<Capital*, CapitalLessForTradingDayIndex> index;
	};
	
	class PositionTable;
	class PositionIndexAccount
	{
		using iterator = std::multiset<Position*, PositionLessForAccountIndex>::iterator;
		friend class PositionTable;
	public:
		PositionIndexAccount(PositionTable* tableOwner);
		iterator LowerBound(const DateType& TradingDay, const AccountIDType& AccountID);
		iterator UpperBound(const DateType& TradingDay, const AccountIDType& AccountID);
		std::pair<iterator, iterator> EqualRange(const DateType& TradingDay, const AccountIDType& AccountID);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(Position* const record);
		void Erase(Position* const record);
		void Update(iterator it);
		bool NeedUpdate(const Position* const oldRecord, const Position* const newRecord);
		iterator FindNode(Position* const record);
		void FillCompareRecord(const DateType& TradingDay, const AccountIDType& AccountID);

	private:
		PositionTable* table;
		multiset<Position*, PositionLessForAccountIndex> index;
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
		PositionTable* table;
		multiset<Position*, PositionLessForTradingDayIndex> index;
	};
	
	class PositionDetailTable;
	class PositionDetailIndexTradeMatch
	{
		using iterator = std::multiset<PositionDetail*, PositionDetailLessForTradeMatchIndex>::iterator;
		friend class PositionDetailTable;
	public:
		PositionDetailIndexTradeMatch(PositionDetailTable* tableOwner);
		iterator LowerBound(const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const PosiDirectionType& PosiDirection);
		iterator UpperBound(const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const PosiDirectionType& PosiDirection);
		std::pair<iterator, iterator> EqualRange(const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const PosiDirectionType& PosiDirection);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(PositionDetail* const record);
		void Erase(PositionDetail* const record);
		void Update(iterator it);
		bool NeedUpdate(const PositionDetail* const oldRecord, const PositionDetail* const newRecord);
		iterator FindNode(PositionDetail* const record);
		void FillCompareRecord(const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const PosiDirectionType& PosiDirection);

	private:
		PositionDetailTable* table;
		multiset<PositionDetail*, PositionDetailLessForTradeMatchIndex> index;
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
		PositionDetailTable* table;
		multiset<PositionDetail*, PositionDetailLessForTradingDayIndex> index;
	};
	
	class OrderTable;
	class OrderIndexAccountID
	{
		using iterator = std::multiset<Order*, OrderLessForAccountIDIndex>::iterator;
		friend class OrderTable;
	public:
		OrderIndexAccountID(OrderTable* tableOwner);
		iterator LowerBound(const DateType& TradingDay, const AccountIDType& AccountID);
		iterator UpperBound(const DateType& TradingDay, const AccountIDType& AccountID);
		std::pair<iterator, iterator> EqualRange(const DateType& TradingDay, const AccountIDType& AccountID);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(Order* const record);
		void Erase(Order* const record);
		void Update(iterator it);
		bool NeedUpdate(const Order* const oldRecord, const Order* const newRecord);
		iterator FindNode(Order* const record);
		void FillCompareRecord(const DateType& TradingDay, const AccountIDType& AccountID);

	private:
		OrderTable* table;
		multiset<Order*, OrderLessForAccountIDIndex> index;
	};
	
	class TradeTable;
	class TradeIndexAccountID
	{
		using iterator = std::multiset<Trade*, TradeLessForAccountIDIndex>::iterator;
		friend class TradeTable;
	public:
		TradeIndexAccountID(TradeTable* tableOwner);
		iterator LowerBound(const DateType& TradingDay, const AccountIDType& AccountID);
		iterator UpperBound(const DateType& TradingDay, const AccountIDType& AccountID);
		std::pair<iterator, iterator> EqualRange(const DateType& TradingDay, const AccountIDType& AccountID);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(Trade* const record);
		void Erase(Trade* const record);
		void Update(iterator it);
		bool NeedUpdate(const Trade* const oldRecord, const Trade* const newRecord);
		iterator FindNode(Trade* const record);
		void FillCompareRecord(const DateType& TradingDay, const AccountIDType& AccountID);

	private:
		TradeTable* table;
		multiset<Trade*, TradeLessForAccountIDIndex> index;
	};
	
	class AccountLoginSessionTable;
	class AccountLoginSessionIndexSessionID
	{
		using iterator = std::multiset<AccountLoginSession*, AccountLoginSessionLessForSessionIDIndex>::iterator;
		friend class AccountLoginSessionTable;
	public:
		AccountLoginSessionIndexSessionID(AccountLoginSessionTable* tableOwner);
		iterator LowerBound(const SessionIDType& SessionID);
		iterator UpperBound(const SessionIDType& SessionID);
		std::pair<iterator, iterator> EqualRange(const SessionIDType& SessionID);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(AccountLoginSession* const record);
		void Erase(AccountLoginSession* const record);
		void Update(iterator it);
		bool NeedUpdate(const AccountLoginSession* const oldRecord, const AccountLoginSession* const newRecord);
		iterator FindNode(AccountLoginSession* const record);
		void FillCompareRecord(const SessionIDType& SessionID);

	private:
		AccountLoginSessionTable* table;
		multiset<AccountLoginSession*, AccountLoginSessionLessForSessionIDIndex> index;
	};
	
	class AccountLoginSessionIndexAccountID
	{
		using iterator = std::multiset<AccountLoginSession*, AccountLoginSessionLessForAccountIDIndex>::iterator;
		friend class AccountLoginSessionTable;
	public:
		AccountLoginSessionIndexAccountID(AccountLoginSessionTable* tableOwner);
		iterator LowerBound(const AccountIDType& AccountID);
		iterator UpperBound(const AccountIDType& AccountID);
		std::pair<iterator, iterator> EqualRange(const AccountIDType& AccountID);
	public:
		static constexpr unsigned int IndexID = 0x0001;
	protected:
		void Insert(AccountLoginSession* const record);
		void Erase(AccountLoginSession* const record);
		void Update(iterator it);
		bool NeedUpdate(const AccountLoginSession* const oldRecord, const AccountLoginSession* const newRecord);
		iterator FindNode(AccountLoginSession* const record);
		void FillCompareRecord(const AccountIDType& AccountID);

	private:
		AccountLoginSessionTable* table;
		multiset<AccountLoginSession*, AccountLoginSessionLessForAccountIDIndex> index;
	};
	
	class PrimaryAccountLoginSessionTable;
	class PrimaryAccountLoginSessionIndexSessionID
	{
		using iterator = std::multiset<PrimaryAccountLoginSession*, PrimaryAccountLoginSessionLessForSessionIDIndex>::iterator;
		friend class PrimaryAccountLoginSessionTable;
	public:
		PrimaryAccountLoginSessionIndexSessionID(PrimaryAccountLoginSessionTable* tableOwner);
		iterator LowerBound(const SessionIDType& SessionID);
		iterator UpperBound(const SessionIDType& SessionID);
		std::pair<iterator, iterator> EqualRange(const SessionIDType& SessionID);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(PrimaryAccountLoginSession* const record);
		void Erase(PrimaryAccountLoginSession* const record);
		void Update(iterator it);
		bool NeedUpdate(const PrimaryAccountLoginSession* const oldRecord, const PrimaryAccountLoginSession* const newRecord);
		iterator FindNode(PrimaryAccountLoginSession* const record);
		void FillCompareRecord(const SessionIDType& SessionID);

	private:
		PrimaryAccountLoginSessionTable* table;
		multiset<PrimaryAccountLoginSession*, PrimaryAccountLoginSessionLessForSessionIDIndex> index;
	};
	
	class PrimaryAccountLoginSessionIndexPrimaryAccountID
	{
		using iterator = std::multiset<PrimaryAccountLoginSession*, PrimaryAccountLoginSessionLessForPrimaryAccountIDIndex>::iterator;
		friend class PrimaryAccountLoginSessionTable;
	public:
		PrimaryAccountLoginSessionIndexPrimaryAccountID(PrimaryAccountLoginSessionTable* tableOwner);
		iterator LowerBound(const AccountIDType& PrimaryAccountID);
		iterator UpperBound(const AccountIDType& PrimaryAccountID);
		std::pair<iterator, iterator> EqualRange(const AccountIDType& PrimaryAccountID);
	public:
		static constexpr unsigned int IndexID = 0x0001;
	protected:
		void Insert(PrimaryAccountLoginSession* const record);
		void Erase(PrimaryAccountLoginSession* const record);
		void Update(iterator it);
		bool NeedUpdate(const PrimaryAccountLoginSession* const oldRecord, const PrimaryAccountLoginSession* const newRecord);
		iterator FindNode(PrimaryAccountLoginSession* const record);
		void FillCompareRecord(const AccountIDType& PrimaryAccountID);

	private:
		PrimaryAccountLoginSessionTable* table;
		multiset<PrimaryAccountLoginSession*, PrimaryAccountLoginSessionLessForPrimaryAccountIDIndex> index;
	};
	
}
