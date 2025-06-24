#pragma once
#include "MdbStructs.h"
#include "MdbIndexComp.h"
#include <set>

using std::multiset;

namespace mdb
{
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
