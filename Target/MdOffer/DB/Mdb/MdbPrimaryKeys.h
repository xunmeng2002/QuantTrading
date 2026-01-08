#pragma once
#include <unordered_set>
#include "MdbStructs.h"
#include "MdbPrimaryKeyComp.h"

namespace mdb
{
	class ExchangeTable;
	class ExchangePrimaryKey
	{
		using iterator = std::unordered_set<Exchange*, ExchangeHashForExchangePrimaryKey, ExchangeEqualForExchangePrimaryKey>::iterator;
		friend class ExchangeTable;
	public:
		ExchangePrimaryKey(ExchangeTable* table, size_t buckets = 1000);
		Exchange* Select(const ExchangeIDType& ExchangeID);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(Exchange* const record);
		void Erase(Exchange* const record);
		bool CheckInsert(Exchange* const record);
		bool CheckUpdate(const Exchange* const oldRecord, const Exchange* const newRecord);

	private:
		ExchangeTable* m_Table;
		std::unordered_set<Exchange*, ExchangeHashForExchangePrimaryKey, ExchangeEqualForExchangePrimaryKey> m_Index;
	};
	class InstrumentTable;
	class InstrumentPrimaryKey
	{
		using iterator = std::unordered_set<Instrument*, InstrumentHashForInstrumentPrimaryKey, InstrumentEqualForInstrumentPrimaryKey>::iterator;
		friend class InstrumentTable;
	public:
		InstrumentPrimaryKey(InstrumentTable* table, size_t buckets = 1000);
		Instrument* Select(const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(Instrument* const record);
		void Erase(Instrument* const record);
		bool CheckInsert(Instrument* const record);
		bool CheckUpdate(const Instrument* const oldRecord, const Instrument* const newRecord);

	private:
		InstrumentTable* m_Table;
		std::unordered_set<Instrument*, InstrumentHashForInstrumentPrimaryKey, InstrumentEqualForInstrumentPrimaryKey> m_Index;
	};
	class DepthMarketDataTable;
	class DepthMarketDataPrimaryKey
	{
		using iterator = std::unordered_set<DepthMarketData*, DepthMarketDataHashForDepthMarketDataPrimaryKey, DepthMarketDataEqualForDepthMarketDataPrimaryKey>::iterator;
		friend class DepthMarketDataTable;
	public:
		DepthMarketDataPrimaryKey(DepthMarketDataTable* table, size_t buckets = 1000);
		DepthMarketData* Select(const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(DepthMarketData* const record);
		void Erase(DepthMarketData* const record);
		bool CheckInsert(DepthMarketData* const record);
		bool CheckUpdate(const DepthMarketData* const oldRecord, const DepthMarketData* const newRecord);

	private:
		DepthMarketDataTable* m_Table;
		std::unordered_set<DepthMarketData*, DepthMarketDataHashForDepthMarketDataPrimaryKey, DepthMarketDataEqualForDepthMarketDataPrimaryKey> m_Index;
	};
	class BarMarketDataTable;
	class BarMarketDataPrimaryKey
	{
		using iterator = std::unordered_set<BarMarketData*, BarMarketDataHashForBarMarketDataPrimaryKey, BarMarketDataEqualForBarMarketDataPrimaryKey>::iterator;
		friend class BarMarketDataTable;
	public:
		BarMarketDataPrimaryKey(BarMarketDataTable* table, size_t buckets = 1000);
		BarMarketData* Select(const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const BarPrecesType& BarPreces, const IntType& BarPeriod, const Int64Type& BarTime);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(BarMarketData* const record);
		void Erase(BarMarketData* const record);
		bool CheckInsert(BarMarketData* const record);
		bool CheckUpdate(const BarMarketData* const oldRecord, const BarMarketData* const newRecord);

	private:
		BarMarketDataTable* m_Table;
		std::unordered_set<BarMarketData*, BarMarketDataHashForBarMarketDataPrimaryKey, BarMarketDataEqualForBarMarketDataPrimaryKey> m_Index;
	};
	class MdSubscribeTable;
	class MdSubscribePrimaryKey
	{
		using iterator = std::unordered_set<MdSubscribe*, MdSubscribeHashForMdSubscribePrimaryKey, MdSubscribeEqualForMdSubscribePrimaryKey>::iterator;
		friend class MdSubscribeTable;
	public:
		MdSubscribePrimaryKey(MdSubscribeTable* table, size_t buckets = 1000);
		MdSubscribe* Select(const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const DateType& StartTradingDay);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(MdSubscribe* const record);
		void Erase(MdSubscribe* const record);
		bool CheckInsert(MdSubscribe* const record);
		bool CheckUpdate(const MdSubscribe* const oldRecord, const MdSubscribe* const newRecord);

	private:
		MdSubscribeTable* m_Table;
		std::unordered_set<MdSubscribe*, MdSubscribeHashForMdSubscribePrimaryKey, MdSubscribeEqualForMdSubscribePrimaryKey> m_Index;
	};
	class MdUserTable;
	class MdUserPrimaryKey
	{
		using iterator = std::unordered_set<MdUser*, MdUserHashForMdUserPrimaryKey, MdUserEqualForMdUserPrimaryKey>::iterator;
		friend class MdUserTable;
	public:
		MdUserPrimaryKey(MdUserTable* table, size_t buckets = 1000);
		MdUser* Select(const UserIDType& MdUserID);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(MdUser* const record);
		void Erase(MdUser* const record);
		bool CheckInsert(MdUser* const record);
		bool CheckUpdate(const MdUser* const oldRecord, const MdUser* const newRecord);

	private:
		MdUserTable* m_Table;
		std::unordered_set<MdUser*, MdUserHashForMdUserPrimaryKey, MdUserEqualForMdUserPrimaryKey> m_Index;
	};
	class MdUserLoginSessionTable;
	class MdUserLoginSessionPrimaryKey
	{
		using iterator = std::unordered_set<MdUserLoginSession*, MdUserLoginSessionHashForMdUserLoginSessionPrimaryKey, MdUserLoginSessionEqualForMdUserLoginSessionPrimaryKey>::iterator;
		friend class MdUserLoginSessionTable;
	public:
		MdUserLoginSessionPrimaryKey(MdUserLoginSessionTable* table, size_t buckets = 1000);
		MdUserLoginSession* Select(const SessionIDType& SessionID);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(MdUserLoginSession* const record);
		void Erase(MdUserLoginSession* const record);
		bool CheckInsert(MdUserLoginSession* const record);
		bool CheckUpdate(const MdUserLoginSession* const oldRecord, const MdUserLoginSession* const newRecord);

	private:
		MdUserLoginSessionTable* m_Table;
		std::unordered_set<MdUserLoginSession*, MdUserLoginSessionHashForMdUserLoginSessionPrimaryKey, MdUserLoginSessionEqualForMdUserLoginSessionPrimaryKey> m_Index;
	};
}
