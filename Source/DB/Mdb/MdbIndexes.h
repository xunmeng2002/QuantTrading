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
		HotInstrumentIndexTradingDay(HotInstrumentTable* table);
		iterator LowerBound(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank, const DateType& TradingDay);
		iterator UpperBound(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank, const DateType& TradingDay);
		std::pair<iterator, iterator> EqualRange(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank, const DateType& TradingDay);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(HotInstrument* const record);
		void Erase(HotInstrument* const record);
		void Update(iterator it);
		bool NeedUpdate(const HotInstrument* const oldRecord, const HotInstrument* const newRecord);
		iterator FindNode(HotInstrument* const record);
		void FillCompareRecord(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank, const DateType& TradingDay);

	private:
		HotInstrumentTable* m_Table;
		multiset<HotInstrument*, HotInstrumentLessForTradingDayIndex> m_Index;
	};
	
	class PrimaryAccountTable;
	class PrimaryAccountIndexOfferID
	{
		using iterator = std::multiset<PrimaryAccount*, PrimaryAccountLessForOfferIDIndex>::iterator;
		friend class PrimaryAccountTable;
	public:
		PrimaryAccountIndexOfferID(PrimaryAccountTable* table);
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
		PrimaryAccountTable* m_Table;
		multiset<PrimaryAccount*, PrimaryAccountLessForOfferIDIndex> m_Index;
	};
	
	class CapitalTable;
	class CapitalIndexTradingDay
	{
		using iterator = std::multiset<Capital*, CapitalLessForTradingDayIndex>::iterator;
		friend class CapitalTable;
	public:
		CapitalIndexTradingDay(CapitalTable* table);
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
		CapitalTable* m_Table;
		multiset<Capital*, CapitalLessForTradingDayIndex> m_Index;
	};
	
	class PositionTable;
	class PositionIndexAccount
	{
		using iterator = std::multiset<Position*, PositionLessForAccountIndex>::iterator;
		friend class PositionTable;
	public:
		PositionIndexAccount(PositionTable* table);
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
		PositionTable* m_Table;
		multiset<Position*, PositionLessForAccountIndex> m_Index;
	};
	
	class PositionIndexTradingDay
	{
		using iterator = std::multiset<Position*, PositionLessForTradingDayIndex>::iterator;
		friend class PositionTable;
	public:
		PositionIndexTradingDay(PositionTable* table);
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
		PositionTable* m_Table;
		multiset<Position*, PositionLessForTradingDayIndex> m_Index;
	};
	
	class PositionDetailTable;
	class PositionDetailIndexTradeMatch
	{
		using iterator = std::multiset<PositionDetail*, PositionDetailLessForTradeMatchIndex>::iterator;
		friend class PositionDetailTable;
	public:
		PositionDetailIndexTradeMatch(PositionDetailTable* table);
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
		PositionDetailTable* m_Table;
		multiset<PositionDetail*, PositionDetailLessForTradeMatchIndex> m_Index;
	};
	
	class PositionDetailIndexTradingDay
	{
		using iterator = std::multiset<PositionDetail*, PositionDetailLessForTradingDayIndex>::iterator;
		friend class PositionDetailTable;
	public:
		PositionDetailIndexTradingDay(PositionDetailTable* table);
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
		PositionDetailTable* m_Table;
		multiset<PositionDetail*, PositionDetailLessForTradingDayIndex> m_Index;
	};
	
	class SEInstrumentTable;
	class SEInstrumentIndexExchangeID
	{
		using iterator = std::multiset<SEInstrument*, SEInstrumentLessForExchangeIDIndex>::iterator;
		friend class SEInstrumentTable;
	public:
		SEInstrumentIndexExchangeID(SEInstrumentTable* table);
		iterator LowerBound(const ExchangeIDType& ExchangeID);
		iterator UpperBound(const ExchangeIDType& ExchangeID);
		std::pair<iterator, iterator> EqualRange(const ExchangeIDType& ExchangeID);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(SEInstrument* const record);
		void Erase(SEInstrument* const record);
		void Update(iterator it);
		bool NeedUpdate(const SEInstrument* const oldRecord, const SEInstrument* const newRecord);
		iterator FindNode(SEInstrument* const record);
		void FillCompareRecord(const ExchangeIDType& ExchangeID);

	private:
		SEInstrumentTable* m_Table;
		multiset<SEInstrument*, SEInstrumentLessForExchangeIDIndex> m_Index;
	};
	
	class SEOrderTable;
	class SEOrderIndexAccountID
	{
		using iterator = std::multiset<SEOrder*, SEOrderLessForAccountIDIndex>::iterator;
		friend class SEOrderTable;
	public:
		SEOrderIndexAccountID(SEOrderTable* table);
		iterator LowerBound(const DateType& TradingDay, const AccountIDType& AccountID);
		iterator UpperBound(const DateType& TradingDay, const AccountIDType& AccountID);
		std::pair<iterator, iterator> EqualRange(const DateType& TradingDay, const AccountIDType& AccountID);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(SEOrder* const record);
		void Erase(SEOrder* const record);
		void Update(iterator it);
		bool NeedUpdate(const SEOrder* const oldRecord, const SEOrder* const newRecord);
		iterator FindNode(SEOrder* const record);
		void FillCompareRecord(const DateType& TradingDay, const AccountIDType& AccountID);

	private:
		SEOrderTable* m_Table;
		multiset<SEOrder*, SEOrderLessForAccountIDIndex> m_Index;
	};
	
	class SETradeTable;
	class SETradeIndexAccountID
	{
		using iterator = std::multiset<SETrade*, SETradeLessForAccountIDIndex>::iterator;
		friend class SETradeTable;
	public:
		SETradeIndexAccountID(SETradeTable* table);
		iterator LowerBound(const DateType& TradingDay, const AccountIDType& AccountID);
		iterator UpperBound(const DateType& TradingDay, const AccountIDType& AccountID);
		std::pair<iterator, iterator> EqualRange(const DateType& TradingDay, const AccountIDType& AccountID);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(SETrade* const record);
		void Erase(SETrade* const record);
		void Update(iterator it);
		bool NeedUpdate(const SETrade* const oldRecord, const SETrade* const newRecord);
		iterator FindNode(SETrade* const record);
		void FillCompareRecord(const DateType& TradingDay, const AccountIDType& AccountID);

	private:
		SETradeTable* m_Table;
		multiset<SETrade*, SETradeLessForAccountIDIndex> m_Index;
	};
	
	class SEBrokerLoginSessionTable;
	class SEBrokerLoginSessionIndexBrokerID
	{
		using iterator = std::multiset<SEBrokerLoginSession*, SEBrokerLoginSessionLessForBrokerIDIndex>::iterator;
		friend class SEBrokerLoginSessionTable;
	public:
		SEBrokerLoginSessionIndexBrokerID(SEBrokerLoginSessionTable* table);
		iterator LowerBound(const BrokerIDType& BrokerID);
		iterator UpperBound(const BrokerIDType& BrokerID);
		std::pair<iterator, iterator> EqualRange(const BrokerIDType& BrokerID);
	public:
		static constexpr unsigned int IndexID = 0x0000;
	protected:
		void Insert(SEBrokerLoginSession* const record);
		void Erase(SEBrokerLoginSession* const record);
		void Update(iterator it);
		bool NeedUpdate(const SEBrokerLoginSession* const oldRecord, const SEBrokerLoginSession* const newRecord);
		iterator FindNode(SEBrokerLoginSession* const record);
		void FillCompareRecord(const BrokerIDType& BrokerID);

	private:
		SEBrokerLoginSessionTable* m_Table;
		multiset<SEBrokerLoginSession*, SEBrokerLoginSessionLessForBrokerIDIndex> m_Index;
	};
	
}
