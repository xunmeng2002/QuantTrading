// 本文件由 ../Templates/Cpp/Mdb/MdbTables.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include "MdbStructs.h"
#include "MdbTableBase.h"
#include <DbAdapters/DbInterface/MdbSubscriber.h>
#include "MdbPrimaryKeys.h"
#include "MdbIndexes.h"
#include <shared_mutex>
#include <atomic>
#include <vector>

using DbAdapters::MdbSubscriber;

namespace QuantTrading
{
	class TradingDayTable : public MdbTableBase
	{
	public:
		TradingDayTable();
		~TradingDayTable() override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDb() override;
		bool Insert(TradingDay* record);
		void BatchInsert(std::vector<TradingDay*>* records);
		void Erase(TradingDay* record);
		bool Update(TradingDay* const oldRecord, TradingDay* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		TradingDayPrimaryKey* PrimaryKey;
	protected:
		MdbSubscriber* mdbSubscriber_;

	private:
		void EraseUniqueKey(TradingDay* record);
		void EraseIndex(TradingDay* record);
	};

	class ExchangeTable : public MdbTableBase
	{
	public:
		ExchangeTable();
		~ExchangeTable() override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDb() override;
		bool Insert(Exchange* record);
		void BatchInsert(std::vector<Exchange*>* records);
		void Erase(Exchange* record);
		bool Update(Exchange* const oldRecord, Exchange* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		ExchangePrimaryKey* PrimaryKey;
	protected:
		MdbSubscriber* mdbSubscriber_;

	private:
		void EraseUniqueKey(Exchange* record);
		void EraseIndex(Exchange* record);
	};

	class ProductTable : public MdbTableBase
	{
	public:
		ProductTable();
		~ProductTable() override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDb() override;
		bool Insert(Product* record);
		void BatchInsert(std::vector<Product*>* records);
		void Erase(Product* record);
		bool Update(Product* const oldRecord, Product* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		ProductPrimaryKey* PrimaryKey;
	protected:
		MdbSubscriber* mdbSubscriber_;

	private:
		void EraseUniqueKey(Product* record);
		void EraseIndex(Product* record);
	};

	class HotInstrumentTable : public MdbTableBase
	{
	public:
		HotInstrumentTable();
		~HotInstrumentTable() override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDb() override;
		bool Insert(HotInstrument* record);
		void BatchInsert(std::vector<HotInstrument*>* records);
		void Erase(HotInstrument* record);
		int EraseByTradingDayIndex(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank, const DateType& TradingDay);
		bool Update(HotInstrument* const oldRecord, HotInstrument* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		HotInstrumentPrimaryKey* PrimaryKey;
		HotInstrumentIndexTradingDay* TradingDayIndex;
	protected:
		MdbSubscriber* mdbSubscriber_;

	private:
		void EraseUniqueKey(HotInstrument* record);
		void EraseIndex(HotInstrument* record);
	};

	class InstrumentTable : public MdbTableBase
	{
	public:
		InstrumentTable();
		~InstrumentTable() override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDb() override;
		bool Insert(Instrument* record);
		void BatchInsert(std::vector<Instrument*>* records);
		void Erase(Instrument* record);
		int EraseByExchangeIdIndex(const ExchangeIdType& ExchangeId);
		bool Update(Instrument* const oldRecord, Instrument* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		InstrumentPrimaryKey* PrimaryKey;
		InstrumentIndexExchangeId* ExchangeIdIndex;
	protected:
		MdbSubscriber* mdbSubscriber_;

	private:
		void EraseUniqueKey(Instrument* record);
		void EraseIndex(Instrument* record);
	};

	class DepthMarketDataTable : public MdbTableBase
	{
	public:
		DepthMarketDataTable();
		~DepthMarketDataTable() override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDb() override;
		bool Insert(DepthMarketData* record);
		void BatchInsert(std::vector<DepthMarketData*>* records);
		void Erase(DepthMarketData* record);
		bool Update(DepthMarketData* const oldRecord, DepthMarketData* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		DepthMarketDataPrimaryKey* PrimaryKey;
	protected:
		MdbSubscriber* mdbSubscriber_;

	private:
		void EraseUniqueKey(DepthMarketData* record);
		void EraseIndex(DepthMarketData* record);
	};

	class BarMarketDataTable : public MdbTableBase
	{
	public:
		BarMarketDataTable();
		~BarMarketDataTable() override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDb() override;
		bool Insert(BarMarketData* record);
		void BatchInsert(std::vector<BarMarketData*>* records);
		void Erase(BarMarketData* record);
		bool Update(BarMarketData* const oldRecord, BarMarketData* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		BarMarketDataPrimaryKey* PrimaryKey;
	protected:
		MdbSubscriber* mdbSubscriber_;

	private:
		void EraseUniqueKey(BarMarketData* record);
		void EraseIndex(BarMarketData* record);
	};

	class MdSubscribeTable : public MdbTableBase
	{
	public:
		MdSubscribeTable();
		~MdSubscribeTable() override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDb() override;
		bool Insert(MdSubscribe* record);
		void BatchInsert(std::vector<MdSubscribe*>* records);
		void Erase(MdSubscribe* record);
		bool Update(MdSubscribe* const oldRecord, MdSubscribe* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		MdSubscribePrimaryKey* PrimaryKey;
	protected:
		MdbSubscriber* mdbSubscriber_;

	private:
		void EraseUniqueKey(MdSubscribe* record);
		void EraseIndex(MdSubscribe* record);
	};

	class MdUserTable : public MdbTableBase
	{
	public:
		MdUserTable();
		~MdUserTable() override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDb() override;
		bool Insert(MdUser* record);
		void BatchInsert(std::vector<MdUser*>* records);
		void Erase(MdUser* record);
		bool Update(MdUser* const oldRecord, MdUser* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		MdUserPrimaryKey* PrimaryKey;
	protected:
		MdbSubscriber* mdbSubscriber_;

	private:
		void EraseUniqueKey(MdUser* record);
		void EraseIndex(MdUser* record);
	};

	class MdUserLoginSessionTable : public MdbTableBase
	{
	public:
		MdUserLoginSessionTable();
		~MdUserLoginSessionTable() override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDb() override;
		bool Insert(MdUserLoginSession* record);
		void BatchInsert(std::vector<MdUserLoginSession*>* records);
		void Erase(MdUserLoginSession* record);
		int EraseBySessionIdIndex(const SessionIdType& SessionId);
		int EraseByMdUserIdIndex(const UserIdType& MdUserId);
		bool Update(MdUserLoginSession* const oldRecord, MdUserLoginSession* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		MdUserLoginSessionPrimaryKey* PrimaryKey;
		MdUserLoginSessionIndexSessionId* SessionIdIndex;
		MdUserLoginSessionIndexMdUserId* MdUserIdIndex;
	protected:
		MdbSubscriber* mdbSubscriber_;

	private:
		void EraseUniqueKey(MdUserLoginSession* record);
		void EraseIndex(MdUserLoginSession* record);
	};

	class PrimaryAccountTable : public MdbTableBase
	{
	public:
		PrimaryAccountTable();
		~PrimaryAccountTable() override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDb() override;
		bool Insert(PrimaryAccount* record);
		void BatchInsert(std::vector<PrimaryAccount*>* records);
		void Erase(PrimaryAccount* record);
		int EraseByOfferIdIndex(const OfferIdType& OfferId);
		bool Update(PrimaryAccount* const oldRecord, PrimaryAccount* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		PrimaryAccountPrimaryKey* PrimaryKey;
		PrimaryAccountIndexOfferId* OfferIdIndex;
	protected:
		MdbSubscriber* mdbSubscriber_;

	private:
		void EraseUniqueKey(PrimaryAccount* record);
		void EraseIndex(PrimaryAccount* record);
	};

	class AccountTable : public MdbTableBase
	{
	public:
		AccountTable();
		~AccountTable() override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDb() override;
		bool Insert(Account* record);
		void BatchInsert(std::vector<Account*>* records);
		void Erase(Account* record);
		bool Update(Account* const oldRecord, Account* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		AccountPrimaryKey* PrimaryKey;
	protected:
		MdbSubscriber* mdbSubscriber_;

	private:
		void EraseUniqueKey(Account* record);
		void EraseIndex(Account* record);
	};

	class CapitalTable : public MdbTableBase
	{
	public:
		CapitalTable();
		~CapitalTable() override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDb() override;
		bool Insert(Capital* record);
		void BatchInsert(std::vector<Capital*>* records);
		void Erase(Capital* record);
		int EraseByTradingDayIndex(const DateType& TradingDay);
		bool Update(Capital* const oldRecord, Capital* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		CapitalPrimaryKey* PrimaryKey;
		CapitalIndexTradingDay* TradingDayIndex;
	protected:
		MdbSubscriber* mdbSubscriber_;

	private:
		void EraseUniqueKey(Capital* record);
		void EraseIndex(Capital* record);
	};

	class PositionTable : public MdbTableBase
	{
	public:
		PositionTable();
		~PositionTable() override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDb() override;
		bool Insert(Position* record);
		void BatchInsert(std::vector<Position*>* records);
		void Erase(Position* record);
		int EraseByAccountIndex(const DateType& TradingDay, const AccountIdType& AccountId);
		int EraseByTradingDayIndex(const DateType& TradingDay);
		bool Update(Position* const oldRecord, Position* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		PositionPrimaryKey* PrimaryKey;
		PositionIndexAccount* AccountIndex;
		PositionIndexTradingDay* TradingDayIndex;
	protected:
		MdbSubscriber* mdbSubscriber_;

	private:
		void EraseUniqueKey(Position* record);
		void EraseIndex(Position* record);
	};

	class PositionDetailTable : public MdbTableBase
	{
	public:
		PositionDetailTable();
		~PositionDetailTable() override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDb() override;
		bool Insert(PositionDetail* record);
		void BatchInsert(std::vector<PositionDetail*>* records);
		void Erase(PositionDetail* record);
		int EraseByTradeMatchIndex(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection);
		int EraseByTradingDayIndex(const DateType& TradingDay);
		bool Update(PositionDetail* const oldRecord, PositionDetail* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		PositionDetailPrimaryKey* PrimaryKey;
		PositionDetailIndexTradeMatch* TradeMatchIndex;
		PositionDetailIndexTradingDay* TradingDayIndex;
	protected:
		MdbSubscriber* mdbSubscriber_;

	private:
		void EraseUniqueKey(PositionDetail* record);
		void EraseIndex(PositionDetail* record);
	};

	class OrderTable : public MdbTableBase
	{
	public:
		OrderTable();
		~OrderTable() override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDb() override;
		bool Insert(Order* record);
		void BatchInsert(std::vector<Order*>* records);
		void Erase(Order* record);
		int EraseByAccountIdIndex(const DateType& TradingDay, const AccountIdType& AccountId);
		bool Update(Order* const oldRecord, Order* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		OrderPrimaryKey* PrimaryKey;
		OrderUniqueKeyClientOrderId* ClientOrderIdUniqueKey;
		OrderIndexAccountId* AccountIdIndex;
	protected:
		MdbSubscriber* mdbSubscriber_;

	private:
		void EraseUniqueKey(Order* record);
		void EraseIndex(Order* record);
	};

	class TradeTable : public MdbTableBase
	{
	public:
		TradeTable();
		~TradeTable() override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDb() override;
		bool Insert(Trade* record);
		void BatchInsert(std::vector<Trade*>* records);
		void Erase(Trade* record);
		int EraseByAccountIdIndex(const DateType& TradingDay, const AccountIdType& AccountId);
		bool Update(Trade* const oldRecord, Trade* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		TradePrimaryKey* PrimaryKey;
		TradeIndexAccountId* AccountIdIndex;
	protected:
		MdbSubscriber* mdbSubscriber_;

	private:
		void EraseUniqueKey(Trade* record);
		void EraseIndex(Trade* record);
	};

	class AccountLoginSessionTable : public MdbTableBase
	{
	public:
		AccountLoginSessionTable();
		~AccountLoginSessionTable() override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDb() override;
		bool Insert(AccountLoginSession* record);
		void BatchInsert(std::vector<AccountLoginSession*>* records);
		void Erase(AccountLoginSession* record);
		int EraseBySessionIdIndex(const SessionIdType& SessionId);
		int EraseByAccountIdIndex(const AccountIdType& AccountId);
		bool Update(AccountLoginSession* const oldRecord, AccountLoginSession* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		AccountLoginSessionPrimaryKey* PrimaryKey;
		AccountLoginSessionIndexSessionId* SessionIdIndex;
		AccountLoginSessionIndexAccountId* AccountIdIndex;
	protected:
		MdbSubscriber* mdbSubscriber_;

	private:
		void EraseUniqueKey(AccountLoginSession* record);
		void EraseIndex(AccountLoginSession* record);
	};

	class PrimaryAccountLoginSessionTable : public MdbTableBase
	{
	public:
		PrimaryAccountLoginSessionTable();
		~PrimaryAccountLoginSessionTable() override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDb() override;
		bool Insert(PrimaryAccountLoginSession* record);
		void BatchInsert(std::vector<PrimaryAccountLoginSession*>* records);
		void Erase(PrimaryAccountLoginSession* record);
		int EraseBySessionIdIndex(const SessionIdType& SessionId);
		int EraseByPrimaryAccountIdIndex(const AccountIdType& PrimaryAccountId);
		bool Update(PrimaryAccountLoginSession* const oldRecord, PrimaryAccountLoginSession* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		PrimaryAccountLoginSessionPrimaryKey* PrimaryKey;
		PrimaryAccountLoginSessionIndexSessionId* SessionIdIndex;
		PrimaryAccountLoginSessionIndexPrimaryAccountId* PrimaryAccountIdIndex;
	protected:
		MdbSubscriber* mdbSubscriber_;

	private:
		void EraseUniqueKey(PrimaryAccountLoginSession* record);
		void EraseIndex(PrimaryAccountLoginSession* record);
	};

	class CommissionGroupTable : public MdbTableBase
	{
	public:
		CommissionGroupTable();
		~CommissionGroupTable() override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDb() override;
		bool Insert(CommissionGroup* record);
		void BatchInsert(std::vector<CommissionGroup*>* records);
		void Erase(CommissionGroup* record);
		bool Update(CommissionGroup* const oldRecord, CommissionGroup* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		CommissionGroupPrimaryKey* PrimaryKey;
	protected:
		MdbSubscriber* mdbSubscriber_;

	private:
		void EraseUniqueKey(CommissionGroup* record);
		void EraseIndex(CommissionGroup* record);
	};

	class BaseCommissionTable : public MdbTableBase
	{
	public:
		BaseCommissionTable();
		~BaseCommissionTable() override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void UnSubscribe() override;
		void LockShared();
		void UnlockShared();
		virtual void InitDb() override;
		bool Insert(BaseCommission* record);
		void BatchInsert(std::vector<BaseCommission*>* records);
		void Erase(BaseCommission* record);
		bool Update(BaseCommission* const oldRecord, BaseCommission* const newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		BaseCommissionPrimaryKey* PrimaryKey;
	protected:
		MdbSubscriber* mdbSubscriber_;

	private:
		void EraseUniqueKey(BaseCommission* record);
		void EraseIndex(BaseCommission* record);
	};

}
