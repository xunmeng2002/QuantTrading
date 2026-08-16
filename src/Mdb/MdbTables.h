#pragma once
#include "MdbStructs.h"
#include "MdbTableBase.h"
#include <DBAdapters/DBInterface/MdbSubscriber.h>
#include "MdbPrimaryKeys.h"
#include "MdbIndexes.h"
#include <shared_mutex>
#include <atomic>
#include <vector>


namespace mdb
{
	class TradingDayTable : public MdbTableBase
	{
	public:
		TradingDayTable();
		~TradingDayTable() override;
		virtual void Subscribe(MdbSubscriber* mdbSubscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDB() override;
		bool Insert(TradingDay* record);
		void BatchInsert(std::vector<mdb::TradingDay*>* records);
		void Erase(TradingDay* record);
		bool Update(TradingDay* const oldRecord, TradingDay* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

	private:
		void EraseUniqueKey(TradingDay* record);
		void EraseIndex(TradingDay* record);

	public:
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		TradingDayPrimaryKey* m_PrimaryKey;
	};

	class ExchangeTable : public MdbTableBase
	{
	public:
		ExchangeTable();
		~ExchangeTable() override;
		virtual void Subscribe(MdbSubscriber* mdbSubscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDB() override;
		bool Insert(Exchange* record);
		void BatchInsert(std::vector<mdb::Exchange*>* records);
		void Erase(Exchange* record);
		bool Update(Exchange* const oldRecord, Exchange* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

	private:
		void EraseUniqueKey(Exchange* record);
		void EraseIndex(Exchange* record);

	public:
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		ExchangePrimaryKey* m_PrimaryKey;
	};

	class ProductTable : public MdbTableBase
	{
	public:
		ProductTable();
		~ProductTable() override;
		virtual void Subscribe(MdbSubscriber* mdbSubscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDB() override;
		bool Insert(Product* record);
		void BatchInsert(std::vector<mdb::Product*>* records);
		void Erase(Product* record);
		bool Update(Product* const oldRecord, Product* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

	private:
		void EraseUniqueKey(Product* record);
		void EraseIndex(Product* record);

	public:
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		ProductPrimaryKey* m_PrimaryKey;
	};

	class HotInstrumentTable : public MdbTableBase
	{
	public:
		HotInstrumentTable();
		~HotInstrumentTable() override;
		virtual void Subscribe(MdbSubscriber* mdbSubscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDB() override;
		bool Insert(HotInstrument* record);
		void BatchInsert(std::vector<mdb::HotInstrument*>* records);
		void Erase(HotInstrument* record);
		int EraseByTradingDayIndex(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const IntType& Rank, const DateType& TradingDay);
		bool Update(HotInstrument* const oldRecord, HotInstrument* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

	private:
		void EraseUniqueKey(HotInstrument* record);
		void EraseIndex(HotInstrument* record);

	public:
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		HotInstrumentPrimaryKey* m_PrimaryKey;
		HotInstrumentIndexTradingDay* m_TradingDayIndex;
	};

	class InstrumentTable : public MdbTableBase
	{
	public:
		InstrumentTable();
		~InstrumentTable() override;
		virtual void Subscribe(MdbSubscriber* mdbSubscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDB() override;
		bool Insert(Instrument* record);
		void BatchInsert(std::vector<mdb::Instrument*>* records);
		void Erase(Instrument* record);
		int EraseByExchangeIDIndex(const ExchangeIDType& ExchangeID);
		bool Update(Instrument* const oldRecord, Instrument* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

	private:
		void EraseUniqueKey(Instrument* record);
		void EraseIndex(Instrument* record);

	public:
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		InstrumentPrimaryKey* m_PrimaryKey;
		InstrumentIndexExchangeID* m_ExchangeIDIndex;
	};

	class DepthMarketDataTable : public MdbTableBase
	{
	public:
		DepthMarketDataTable();
		~DepthMarketDataTable() override;
		virtual void Subscribe(MdbSubscriber* mdbSubscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDB() override;
		bool Insert(DepthMarketData* record);
		void BatchInsert(std::vector<mdb::DepthMarketData*>* records);
		void Erase(DepthMarketData* record);
		bool Update(DepthMarketData* const oldRecord, DepthMarketData* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

	private:
		void EraseUniqueKey(DepthMarketData* record);
		void EraseIndex(DepthMarketData* record);

	public:
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		DepthMarketDataPrimaryKey* m_PrimaryKey;
	};

	class BarMarketDataTable : public MdbTableBase
	{
	public:
		BarMarketDataTable();
		~BarMarketDataTable() override;
		virtual void Subscribe(MdbSubscriber* mdbSubscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDB() override;
		bool Insert(BarMarketData* record);
		void BatchInsert(std::vector<mdb::BarMarketData*>* records);
		void Erase(BarMarketData* record);
		bool Update(BarMarketData* const oldRecord, BarMarketData* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

	private:
		void EraseUniqueKey(BarMarketData* record);
		void EraseIndex(BarMarketData* record);

	public:
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		BarMarketDataPrimaryKey* m_PrimaryKey;
	};

	class MdSubscribeTable : public MdbTableBase
	{
	public:
		MdSubscribeTable();
		~MdSubscribeTable() override;
		virtual void Subscribe(MdbSubscriber* mdbSubscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDB() override;
		bool Insert(MdSubscribe* record);
		void BatchInsert(std::vector<mdb::MdSubscribe*>* records);
		void Erase(MdSubscribe* record);
		bool Update(MdSubscribe* const oldRecord, MdSubscribe* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

	private:
		void EraseUniqueKey(MdSubscribe* record);
		void EraseIndex(MdSubscribe* record);

	public:
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		MdSubscribePrimaryKey* m_PrimaryKey;
	};

	class MdUserTable : public MdbTableBase
	{
	public:
		MdUserTable();
		~MdUserTable() override;
		virtual void Subscribe(MdbSubscriber* mdbSubscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDB() override;
		bool Insert(MdUser* record);
		void BatchInsert(std::vector<mdb::MdUser*>* records);
		void Erase(MdUser* record);
		bool Update(MdUser* const oldRecord, MdUser* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

	private:
		void EraseUniqueKey(MdUser* record);
		void EraseIndex(MdUser* record);

	public:
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		MdUserPrimaryKey* m_PrimaryKey;
	};

	class MdUserLoginSessionTable : public MdbTableBase
	{
	public:
		MdUserLoginSessionTable();
		~MdUserLoginSessionTable() override;
		virtual void Subscribe(MdbSubscriber* mdbSubscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDB() override;
		bool Insert(MdUserLoginSession* record);
		void BatchInsert(std::vector<mdb::MdUserLoginSession*>* records);
		void Erase(MdUserLoginSession* record);
		int EraseByMdUserIDIndex(const UserIDType& MdUserID);
		bool Update(MdUserLoginSession* const oldRecord, MdUserLoginSession* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

	private:
		void EraseUniqueKey(MdUserLoginSession* record);
		void EraseIndex(MdUserLoginSession* record);

	public:
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		MdUserLoginSessionPrimaryKey* m_PrimaryKey;
		MdUserLoginSessionIndexMdUserID* m_MdUserIDIndex;
	};

	class PrimaryAccountTable : public MdbTableBase
	{
	public:
		PrimaryAccountTable();
		~PrimaryAccountTable() override;
		virtual void Subscribe(MdbSubscriber* mdbSubscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDB() override;
		bool Insert(PrimaryAccount* record);
		void BatchInsert(std::vector<mdb::PrimaryAccount*>* records);
		void Erase(PrimaryAccount* record);
		int EraseByOfferIDIndex(const OfferIDType& OfferID);
		bool Update(PrimaryAccount* const oldRecord, PrimaryAccount* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

	private:
		void EraseUniqueKey(PrimaryAccount* record);
		void EraseIndex(PrimaryAccount* record);

	public:
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		PrimaryAccountPrimaryKey* m_PrimaryKey;
		PrimaryAccountIndexOfferID* m_OfferIDIndex;
	};

	class AccountTable : public MdbTableBase
	{
	public:
		AccountTable();
		~AccountTable() override;
		virtual void Subscribe(MdbSubscriber* mdbSubscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDB() override;
		bool Insert(Account* record);
		void BatchInsert(std::vector<mdb::Account*>* records);
		void Erase(Account* record);
		bool Update(Account* const oldRecord, Account* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

	private:
		void EraseUniqueKey(Account* record);
		void EraseIndex(Account* record);

	public:
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		AccountPrimaryKey* m_PrimaryKey;
	};

	class CapitalTable : public MdbTableBase
	{
	public:
		CapitalTable();
		~CapitalTable() override;
		virtual void Subscribe(MdbSubscriber* mdbSubscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDB() override;
		bool Insert(Capital* record);
		void BatchInsert(std::vector<mdb::Capital*>* records);
		void Erase(Capital* record);
		int EraseByTradingDayIndex(const DateType& TradingDay);
		bool Update(Capital* const oldRecord, Capital* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

	private:
		void EraseUniqueKey(Capital* record);
		void EraseIndex(Capital* record);

	public:
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		CapitalPrimaryKey* m_PrimaryKey;
		CapitalIndexTradingDay* m_TradingDayIndex;
	};

	class PositionTable : public MdbTableBase
	{
	public:
		PositionTable();
		~PositionTable() override;
		virtual void Subscribe(MdbSubscriber* mdbSubscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDB() override;
		bool Insert(Position* record);
		void BatchInsert(std::vector<mdb::Position*>* records);
		void Erase(Position* record);
		int EraseByAccountIndex(const DateType& TradingDay, const AccountIDType& AccountID);
		int EraseByTradingDayIndex(const DateType& TradingDay);
		bool Update(Position* const oldRecord, Position* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

	private:
		void EraseUniqueKey(Position* record);
		void EraseIndex(Position* record);

	public:
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		PositionPrimaryKey* m_PrimaryKey;
		PositionIndexAccount* m_AccountIndex;
		PositionIndexTradingDay* m_TradingDayIndex;
	};

	class PositionDetailTable : public MdbTableBase
	{
	public:
		PositionDetailTable();
		~PositionDetailTable() override;
		virtual void Subscribe(MdbSubscriber* mdbSubscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDB() override;
		bool Insert(PositionDetail* record);
		void BatchInsert(std::vector<mdb::PositionDetail*>* records);
		void Erase(PositionDetail* record);
		int EraseByTradeMatchIndex(const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const PosiDirectionType& PosiDirection);
		int EraseByTradingDayIndex(const DateType& TradingDay);
		bool Update(PositionDetail* const oldRecord, PositionDetail* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

	private:
		void EraseUniqueKey(PositionDetail* record);
		void EraseIndex(PositionDetail* record);

	public:
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		PositionDetailPrimaryKey* m_PrimaryKey;
		PositionDetailIndexTradeMatch* m_TradeMatchIndex;
		PositionDetailIndexTradingDay* m_TradingDayIndex;
	};

	class OrderTable : public MdbTableBase
	{
	public:
		OrderTable();
		~OrderTable() override;
		virtual void Subscribe(MdbSubscriber* mdbSubscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDB() override;
		bool Insert(Order* record);
		void BatchInsert(std::vector<mdb::Order*>* records);
		void Erase(Order* record);
		int EraseByAccountIDIndex(const DateType& TradingDay, const AccountIDType& AccountID);
		bool Update(Order* const oldRecord, Order* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

	private:
		void EraseUniqueKey(Order* record);
		void EraseIndex(Order* record);

	public:
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		OrderPrimaryKey* m_PrimaryKey;
		OrderUniqueKeyClientOrderID* m_ClientOrderIDUniqueKey;
		OrderIndexAccountID* m_AccountIDIndex;
	};

	class TradeTable : public MdbTableBase
	{
	public:
		TradeTable();
		~TradeTable() override;
		virtual void Subscribe(MdbSubscriber* mdbSubscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDB() override;
		bool Insert(Trade* record);
		void BatchInsert(std::vector<mdb::Trade*>* records);
		void Erase(Trade* record);
		int EraseByAccountIDIndex(const DateType& TradingDay, const AccountIDType& AccountID);
		bool Update(Trade* const oldRecord, Trade* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

	private:
		void EraseUniqueKey(Trade* record);
		void EraseIndex(Trade* record);

	public:
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		TradePrimaryKey* m_PrimaryKey;
		TradeIndexAccountID* m_AccountIDIndex;
	};

	class AccountLoginSessionTable : public MdbTableBase
	{
	public:
		AccountLoginSessionTable();
		~AccountLoginSessionTable() override;
		virtual void Subscribe(MdbSubscriber* mdbSubscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDB() override;
		bool Insert(AccountLoginSession* record);
		void BatchInsert(std::vector<mdb::AccountLoginSession*>* records);
		void Erase(AccountLoginSession* record);
		int EraseByAccountIDIndex(const AccountIDType& AccountID);
		bool Update(AccountLoginSession* const oldRecord, AccountLoginSession* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

	private:
		void EraseUniqueKey(AccountLoginSession* record);
		void EraseIndex(AccountLoginSession* record);

	public:
		MdbSubscriber* m_MdbSubscriber;
		std::shared_mutex m_SharedMutex;
		AccountLoginSessionPrimaryKey* m_PrimaryKey;
		AccountLoginSessionIndexAccountID* m_AccountIDIndex;
	};

}
