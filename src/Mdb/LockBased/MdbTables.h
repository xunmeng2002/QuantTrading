// 本文件由 ../Templates/Cpp/Mdb/LockBased/MdbTables.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include "Common/MdbStructs.h"
#include "Common/MdbTableBase.h"
#include <DbAdapters/DbInterface/MdbSubscriber.h>
#include <DbAdapters/DbInterface/RowChangeEvent.h>
#include "MdbPrimaryKeys.h"
#include "MdbIndexes.h"
#include <cstdint>
#include <mutex>
#include <shared_mutex>
#include <vector>

using DbAdapters::MdbSubscriber;
using DbAdapters::MdbReplicaSubscriber;
using DbAdapters::RecordHandle;
using DbAdapters::RowChangeEventPtr;
using DbAdapters::RowChangeType;

namespace QuantTrading
{
	class TradingDayTable : public MdbTableBase
	{
	public:
		TradingDayTable();
		~TradingDayTable() override;
		virtual unsigned int GetTableId() const override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void SubscribeReplica(MdbReplicaSubscriber* replica) override;
		virtual void UnSubscribe() override;
		virtual void InitDb() override;
		template <typename Visitor>
		void ForEach(Visitor&& visitor)
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				if (!visitor(*it))
				{
					break;
				}
			}
		}
		bool Insert(TradingDay* record);
		void BatchInsert(std::vector<TradingDay*>& records);
		// 按主键定位表内活记录删除，record 只提供主键
		bool Erase(const TradingDay& record);
		// 按主键定位表内活记录并整行覆盖，newRecord 只提供新值
		bool Update(const TradingDay& newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		TradingDayTablePrimaryKey* PrimaryKey;
	private:
		bool HasSubscribers() const;
		RowChangeEventPtr MakeInsertEvent(const TradingDay* record);
		// 单写者前提：Build* 在锁内按写入顺序取号，Publish* 在锁外调用订阅者；订阅者不得回写本表
		// BuildRowChangeEvent 接管 record：无订阅者时记录随句柄回池。Build* 调用方必须持有 SharedMutex。
		RowChangeEventPtr BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record);
		RowChangeEventPtr BuildInsertEvent(const TradingDay* record);
		RowChangeEventPtr BuildUpdateEvent(const TradingDay& newRecord, bool updateDB);
		std::vector<RowChangeEventPtr> BuildBatchInsertEvents(const std::vector<TradingDay*>& records);
		void PublishRowChange(const RowChangeEventPtr& event);
		void PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events);
		void EraseUniqueKey(TradingDay* record);
		void EraseIndex(TradingDay* record);

		// 发布屏障：写事务与快照按交付顺序串行，读者不取此锁
		std::mutex publishMutex_;
		// 只在启动期注册，之后列表不可变，热路径无锁读
		std::vector<MdbSubscriber*> subscribers_;
		MdbReplicaSubscriber* replicaSubscriber_ = nullptr;
		// 只在持 publishMutex_ 时递增
		std::uint64_t sequence_ = 0;
	};

	class ExchangeTable : public MdbTableBase
	{
	public:
		ExchangeTable();
		~ExchangeTable() override;
		virtual unsigned int GetTableId() const override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void SubscribeReplica(MdbReplicaSubscriber* replica) override;
		virtual void UnSubscribe() override;
		virtual void InitDb() override;
		template <typename Visitor>
		void ForEach(Visitor&& visitor)
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				if (!visitor(*it))
				{
					break;
				}
			}
		}
		bool Insert(Exchange* record);
		void BatchInsert(std::vector<Exchange*>& records);
		// 按主键定位表内活记录删除，record 只提供主键
		bool Erase(const Exchange& record);
		// 按主键定位表内活记录并整行覆盖，newRecord 只提供新值
		bool Update(const Exchange& newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		ExchangeTablePrimaryKey* PrimaryKey;
	private:
		bool HasSubscribers() const;
		RowChangeEventPtr MakeInsertEvent(const Exchange* record);
		// 单写者前提：Build* 在锁内按写入顺序取号，Publish* 在锁外调用订阅者；订阅者不得回写本表
		// BuildRowChangeEvent 接管 record：无订阅者时记录随句柄回池。Build* 调用方必须持有 SharedMutex。
		RowChangeEventPtr BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record);
		RowChangeEventPtr BuildInsertEvent(const Exchange* record);
		RowChangeEventPtr BuildUpdateEvent(const Exchange& newRecord, bool updateDB);
		std::vector<RowChangeEventPtr> BuildBatchInsertEvents(const std::vector<Exchange*>& records);
		void PublishRowChange(const RowChangeEventPtr& event);
		void PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events);
		void EraseUniqueKey(Exchange* record);
		void EraseIndex(Exchange* record);

		// 发布屏障：写事务与快照按交付顺序串行，读者不取此锁
		std::mutex publishMutex_;
		// 只在启动期注册，之后列表不可变，热路径无锁读
		std::vector<MdbSubscriber*> subscribers_;
		MdbReplicaSubscriber* replicaSubscriber_ = nullptr;
		// 只在持 publishMutex_ 时递增
		std::uint64_t sequence_ = 0;
	};

	class ProductTable : public MdbTableBase
	{
	public:
		ProductTable();
		~ProductTable() override;
		virtual unsigned int GetTableId() const override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void SubscribeReplica(MdbReplicaSubscriber* replica) override;
		virtual void UnSubscribe() override;
		virtual void InitDb() override;
		template <typename Visitor>
		void ForEach(Visitor&& visitor)
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				if (!visitor(*it))
				{
					break;
				}
			}
		}
		bool Insert(Product* record);
		void BatchInsert(std::vector<Product*>& records);
		// 按主键定位表内活记录删除，record 只提供主键
		bool Erase(const Product& record);
		// 按主键定位表内活记录并整行覆盖，newRecord 只提供新值
		bool Update(const Product& newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		ProductTablePrimaryKey* PrimaryKey;
	private:
		bool HasSubscribers() const;
		RowChangeEventPtr MakeInsertEvent(const Product* record);
		// 单写者前提：Build* 在锁内按写入顺序取号，Publish* 在锁外调用订阅者；订阅者不得回写本表
		// BuildRowChangeEvent 接管 record：无订阅者时记录随句柄回池。Build* 调用方必须持有 SharedMutex。
		RowChangeEventPtr BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record);
		RowChangeEventPtr BuildInsertEvent(const Product* record);
		RowChangeEventPtr BuildUpdateEvent(const Product& newRecord, bool updateDB);
		std::vector<RowChangeEventPtr> BuildBatchInsertEvents(const std::vector<Product*>& records);
		void PublishRowChange(const RowChangeEventPtr& event);
		void PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events);
		void EraseUniqueKey(Product* record);
		void EraseIndex(Product* record);

		// 发布屏障：写事务与快照按交付顺序串行，读者不取此锁
		std::mutex publishMutex_;
		// 只在启动期注册，之后列表不可变，热路径无锁读
		std::vector<MdbSubscriber*> subscribers_;
		MdbReplicaSubscriber* replicaSubscriber_ = nullptr;
		// 只在持 publishMutex_ 时递增
		std::uint64_t sequence_ = 0;
	};

	class HotInstrumentTable : public MdbTableBase
	{
	public:
		HotInstrumentTable();
		~HotInstrumentTable() override;
		virtual unsigned int GetTableId() const override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void SubscribeReplica(MdbReplicaSubscriber* replica) override;
		virtual void UnSubscribe() override;
		virtual void InitDb() override;
		template <typename Visitor>
		void ForEach(Visitor&& visitor)
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				if (!visitor(*it))
				{
					break;
				}
			}
		}
		bool Insert(HotInstrument* record);
		void BatchInsert(std::vector<HotInstrument*>& records);
		// 按主键定位表内活记录删除，record 只提供主键
		bool Erase(const HotInstrument& record);
		int EraseByTradingDayIndex(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank, const DateType& TradingDay);
		// 按主键定位表内活记录并整行覆盖，newRecord 只提供新值
		bool Update(const HotInstrument& newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		HotInstrumentTablePrimaryKey* PrimaryKey;
		HotInstrumentTableIndexTradingDay* TradingDayIndex;
	private:
		bool HasSubscribers() const;
		RowChangeEventPtr MakeInsertEvent(const HotInstrument* record);
		// 单写者前提：Build* 在锁内按写入顺序取号，Publish* 在锁外调用订阅者；订阅者不得回写本表
		// BuildRowChangeEvent 接管 record：无订阅者时记录随句柄回池。Build* 调用方必须持有 SharedMutex。
		RowChangeEventPtr BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record);
		RowChangeEventPtr BuildInsertEvent(const HotInstrument* record);
		RowChangeEventPtr BuildUpdateEvent(const HotInstrument& newRecord, bool updateDB);
		std::vector<RowChangeEventPtr> BuildBatchInsertEvents(const std::vector<HotInstrument*>& records);
		void PublishRowChange(const RowChangeEventPtr& event);
		void PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events);
		void EraseUniqueKey(HotInstrument* record);
		void EraseIndex(HotInstrument* record);

		// 发布屏障：写事务与快照按交付顺序串行，读者不取此锁
		std::mutex publishMutex_;
		// 只在启动期注册，之后列表不可变，热路径无锁读
		std::vector<MdbSubscriber*> subscribers_;
		MdbReplicaSubscriber* replicaSubscriber_ = nullptr;
		// 只在持 publishMutex_ 时递增
		std::uint64_t sequence_ = 0;
	};

	class InstrumentTable : public MdbTableBase
	{
	public:
		InstrumentTable();
		~InstrumentTable() override;
		virtual unsigned int GetTableId() const override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void SubscribeReplica(MdbReplicaSubscriber* replica) override;
		virtual void UnSubscribe() override;
		virtual void InitDb() override;
		template <typename Visitor>
		void ForEach(Visitor&& visitor)
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				if (!visitor(*it))
				{
					break;
				}
			}
		}
		bool Insert(Instrument* record);
		void BatchInsert(std::vector<Instrument*>& records);
		// 按主键定位表内活记录删除，record 只提供主键
		bool Erase(const Instrument& record);
		int EraseByExchangeIdIndex(const ExchangeIdType& ExchangeId);
		// 按主键定位表内活记录并整行覆盖，newRecord 只提供新值
		bool Update(const Instrument& newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		InstrumentTablePrimaryKey* PrimaryKey;
		InstrumentTableIndexExchangeId* ExchangeIdIndex;
	private:
		bool HasSubscribers() const;
		RowChangeEventPtr MakeInsertEvent(const Instrument* record);
		// 单写者前提：Build* 在锁内按写入顺序取号，Publish* 在锁外调用订阅者；订阅者不得回写本表
		// BuildRowChangeEvent 接管 record：无订阅者时记录随句柄回池。Build* 调用方必须持有 SharedMutex。
		RowChangeEventPtr BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record);
		RowChangeEventPtr BuildInsertEvent(const Instrument* record);
		RowChangeEventPtr BuildUpdateEvent(const Instrument& newRecord, bool updateDB);
		std::vector<RowChangeEventPtr> BuildBatchInsertEvents(const std::vector<Instrument*>& records);
		void PublishRowChange(const RowChangeEventPtr& event);
		void PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events);
		void EraseUniqueKey(Instrument* record);
		void EraseIndex(Instrument* record);

		// 发布屏障：写事务与快照按交付顺序串行，读者不取此锁
		std::mutex publishMutex_;
		// 只在启动期注册，之后列表不可变，热路径无锁读
		std::vector<MdbSubscriber*> subscribers_;
		MdbReplicaSubscriber* replicaSubscriber_ = nullptr;
		// 只在持 publishMutex_ 时递增
		std::uint64_t sequence_ = 0;
	};

	class DepthMarketDataTable : public MdbTableBase
	{
	public:
		DepthMarketDataTable();
		~DepthMarketDataTable() override;
		virtual unsigned int GetTableId() const override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void SubscribeReplica(MdbReplicaSubscriber* replica) override;
		virtual void UnSubscribe() override;
		virtual void InitDb() override;
		template <typename Visitor>
		void ForEach(Visitor&& visitor)
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				if (!visitor(*it))
				{
					break;
				}
			}
		}
		bool Insert(DepthMarketData* record);
		void BatchInsert(std::vector<DepthMarketData*>& records);
		// 按主键定位表内活记录删除，record 只提供主键
		bool Erase(const DepthMarketData& record);
		// 按主键定位表内活记录并整行覆盖，newRecord 只提供新值
		bool Update(const DepthMarketData& newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		DepthMarketDataTablePrimaryKey* PrimaryKey;
	private:
		bool HasSubscribers() const;
		RowChangeEventPtr MakeInsertEvent(const DepthMarketData* record);
		// 单写者前提：Build* 在锁内按写入顺序取号，Publish* 在锁外调用订阅者；订阅者不得回写本表
		// BuildRowChangeEvent 接管 record：无订阅者时记录随句柄回池。Build* 调用方必须持有 SharedMutex。
		RowChangeEventPtr BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record);
		RowChangeEventPtr BuildInsertEvent(const DepthMarketData* record);
		RowChangeEventPtr BuildUpdateEvent(const DepthMarketData& newRecord, bool updateDB);
		std::vector<RowChangeEventPtr> BuildBatchInsertEvents(const std::vector<DepthMarketData*>& records);
		void PublishRowChange(const RowChangeEventPtr& event);
		void PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events);
		void EraseUniqueKey(DepthMarketData* record);
		void EraseIndex(DepthMarketData* record);

		// 发布屏障：写事务与快照按交付顺序串行，读者不取此锁
		std::mutex publishMutex_;
		// 只在启动期注册，之后列表不可变，热路径无锁读
		std::vector<MdbSubscriber*> subscribers_;
		MdbReplicaSubscriber* replicaSubscriber_ = nullptr;
		// 只在持 publishMutex_ 时递增
		std::uint64_t sequence_ = 0;
	};

	class BarMarketDataTable : public MdbTableBase
	{
	public:
		BarMarketDataTable();
		~BarMarketDataTable() override;
		virtual unsigned int GetTableId() const override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void SubscribeReplica(MdbReplicaSubscriber* replica) override;
		virtual void UnSubscribe() override;
		virtual void InitDb() override;
		template <typename Visitor>
		void ForEach(Visitor&& visitor)
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				if (!visitor(*it))
				{
					break;
				}
			}
		}
		bool Insert(BarMarketData* record);
		void BatchInsert(std::vector<BarMarketData*>& records);
		// 按主键定位表内活记录删除，record 只提供主键
		bool Erase(const BarMarketData& record);
		// 按主键定位表内活记录并整行覆盖，newRecord 只提供新值
		bool Update(const BarMarketData& newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		BarMarketDataTablePrimaryKey* PrimaryKey;
	private:
		bool HasSubscribers() const;
		RowChangeEventPtr MakeInsertEvent(const BarMarketData* record);
		// 单写者前提：Build* 在锁内按写入顺序取号，Publish* 在锁外调用订阅者；订阅者不得回写本表
		// BuildRowChangeEvent 接管 record：无订阅者时记录随句柄回池。Build* 调用方必须持有 SharedMutex。
		RowChangeEventPtr BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record);
		RowChangeEventPtr BuildInsertEvent(const BarMarketData* record);
		RowChangeEventPtr BuildUpdateEvent(const BarMarketData& newRecord, bool updateDB);
		std::vector<RowChangeEventPtr> BuildBatchInsertEvents(const std::vector<BarMarketData*>& records);
		void PublishRowChange(const RowChangeEventPtr& event);
		void PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events);
		void EraseUniqueKey(BarMarketData* record);
		void EraseIndex(BarMarketData* record);

		// 发布屏障：写事务与快照按交付顺序串行，读者不取此锁
		std::mutex publishMutex_;
		// 只在启动期注册，之后列表不可变，热路径无锁读
		std::vector<MdbSubscriber*> subscribers_;
		MdbReplicaSubscriber* replicaSubscriber_ = nullptr;
		// 只在持 publishMutex_ 时递增
		std::uint64_t sequence_ = 0;
	};

	class MdSubscribeTable : public MdbTableBase
	{
	public:
		MdSubscribeTable();
		~MdSubscribeTable() override;
		virtual unsigned int GetTableId() const override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void SubscribeReplica(MdbReplicaSubscriber* replica) override;
		virtual void UnSubscribe() override;
		virtual void InitDb() override;
		template <typename Visitor>
		void ForEach(Visitor&& visitor)
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				if (!visitor(*it))
				{
					break;
				}
			}
		}
		bool Insert(MdSubscribe* record);
		void BatchInsert(std::vector<MdSubscribe*>& records);
		// 按主键定位表内活记录删除，record 只提供主键
		bool Erase(const MdSubscribe& record);
		// 按主键定位表内活记录并整行覆盖，newRecord 只提供新值
		bool Update(const MdSubscribe& newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		MdSubscribeTablePrimaryKey* PrimaryKey;
	private:
		bool HasSubscribers() const;
		RowChangeEventPtr MakeInsertEvent(const MdSubscribe* record);
		// 单写者前提：Build* 在锁内按写入顺序取号，Publish* 在锁外调用订阅者；订阅者不得回写本表
		// BuildRowChangeEvent 接管 record：无订阅者时记录随句柄回池。Build* 调用方必须持有 SharedMutex。
		RowChangeEventPtr BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record);
		RowChangeEventPtr BuildInsertEvent(const MdSubscribe* record);
		RowChangeEventPtr BuildUpdateEvent(const MdSubscribe& newRecord, bool updateDB);
		std::vector<RowChangeEventPtr> BuildBatchInsertEvents(const std::vector<MdSubscribe*>& records);
		void PublishRowChange(const RowChangeEventPtr& event);
		void PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events);
		void EraseUniqueKey(MdSubscribe* record);
		void EraseIndex(MdSubscribe* record);

		// 发布屏障：写事务与快照按交付顺序串行，读者不取此锁
		std::mutex publishMutex_;
		// 只在启动期注册，之后列表不可变，热路径无锁读
		std::vector<MdbSubscriber*> subscribers_;
		MdbReplicaSubscriber* replicaSubscriber_ = nullptr;
		// 只在持 publishMutex_ 时递增
		std::uint64_t sequence_ = 0;
	};

	class MdUserTable : public MdbTableBase
	{
	public:
		MdUserTable();
		~MdUserTable() override;
		virtual unsigned int GetTableId() const override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void SubscribeReplica(MdbReplicaSubscriber* replica) override;
		virtual void UnSubscribe() override;
		virtual void InitDb() override;
		template <typename Visitor>
		void ForEach(Visitor&& visitor)
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				if (!visitor(*it))
				{
					break;
				}
			}
		}
		bool Insert(MdUser* record);
		void BatchInsert(std::vector<MdUser*>& records);
		// 按主键定位表内活记录删除，record 只提供主键
		bool Erase(const MdUser& record);
		// 按主键定位表内活记录并整行覆盖，newRecord 只提供新值
		bool Update(const MdUser& newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		MdUserTablePrimaryKey* PrimaryKey;
	private:
		bool HasSubscribers() const;
		RowChangeEventPtr MakeInsertEvent(const MdUser* record);
		// 单写者前提：Build* 在锁内按写入顺序取号，Publish* 在锁外调用订阅者；订阅者不得回写本表
		// BuildRowChangeEvent 接管 record：无订阅者时记录随句柄回池。Build* 调用方必须持有 SharedMutex。
		RowChangeEventPtr BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record);
		RowChangeEventPtr BuildInsertEvent(const MdUser* record);
		RowChangeEventPtr BuildUpdateEvent(const MdUser& newRecord, bool updateDB);
		std::vector<RowChangeEventPtr> BuildBatchInsertEvents(const std::vector<MdUser*>& records);
		void PublishRowChange(const RowChangeEventPtr& event);
		void PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events);
		void EraseUniqueKey(MdUser* record);
		void EraseIndex(MdUser* record);

		// 发布屏障：写事务与快照按交付顺序串行，读者不取此锁
		std::mutex publishMutex_;
		// 只在启动期注册，之后列表不可变，热路径无锁读
		std::vector<MdbSubscriber*> subscribers_;
		MdbReplicaSubscriber* replicaSubscriber_ = nullptr;
		// 只在持 publishMutex_ 时递增
		std::uint64_t sequence_ = 0;
	};

	class MdUserLoginSessionTable : public MdbTableBase
	{
	public:
		MdUserLoginSessionTable();
		~MdUserLoginSessionTable() override;
		virtual unsigned int GetTableId() const override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void SubscribeReplica(MdbReplicaSubscriber* replica) override;
		virtual void UnSubscribe() override;
		virtual void InitDb() override;
		template <typename Visitor>
		void ForEach(Visitor&& visitor)
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				if (!visitor(*it))
				{
					break;
				}
			}
		}
		bool Insert(MdUserLoginSession* record);
		void BatchInsert(std::vector<MdUserLoginSession*>& records);
		// 按主键定位表内活记录删除，record 只提供主键
		bool Erase(const MdUserLoginSession& record);
		int EraseBySessionIdIndex(const SessionIdType& SessionId);
		int EraseByMdUserIdIndex(const UserIdType& MdUserId);
		// 按主键定位表内活记录并整行覆盖，newRecord 只提供新值
		bool Update(const MdUserLoginSession& newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		MdUserLoginSessionTablePrimaryKey* PrimaryKey;
		MdUserLoginSessionTableIndexSessionId* SessionIdIndex;
		MdUserLoginSessionTableIndexMdUserId* MdUserIdIndex;
	private:
		bool HasSubscribers() const;
		RowChangeEventPtr MakeInsertEvent(const MdUserLoginSession* record);
		// 单写者前提：Build* 在锁内按写入顺序取号，Publish* 在锁外调用订阅者；订阅者不得回写本表
		// BuildRowChangeEvent 接管 record：无订阅者时记录随句柄回池。Build* 调用方必须持有 SharedMutex。
		RowChangeEventPtr BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record);
		RowChangeEventPtr BuildInsertEvent(const MdUserLoginSession* record);
		RowChangeEventPtr BuildUpdateEvent(const MdUserLoginSession& newRecord, bool updateDB);
		std::vector<RowChangeEventPtr> BuildBatchInsertEvents(const std::vector<MdUserLoginSession*>& records);
		void PublishRowChange(const RowChangeEventPtr& event);
		void PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events);
		void EraseUniqueKey(MdUserLoginSession* record);
		void EraseIndex(MdUserLoginSession* record);

		// 发布屏障：写事务与快照按交付顺序串行，读者不取此锁
		std::mutex publishMutex_;
		// 只在启动期注册，之后列表不可变，热路径无锁读
		std::vector<MdbSubscriber*> subscribers_;
		MdbReplicaSubscriber* replicaSubscriber_ = nullptr;
		// 只在持 publishMutex_ 时递增
		std::uint64_t sequence_ = 0;
	};

	class PrimaryAccountTable : public MdbTableBase
	{
	public:
		PrimaryAccountTable();
		~PrimaryAccountTable() override;
		virtual unsigned int GetTableId() const override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void SubscribeReplica(MdbReplicaSubscriber* replica) override;
		virtual void UnSubscribe() override;
		virtual void InitDb() override;
		template <typename Visitor>
		void ForEach(Visitor&& visitor)
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				if (!visitor(*it))
				{
					break;
				}
			}
		}
		bool Insert(PrimaryAccount* record);
		void BatchInsert(std::vector<PrimaryAccount*>& records);
		// 按主键定位表内活记录删除，record 只提供主键
		bool Erase(const PrimaryAccount& record);
		int EraseByOfferIdIndex(const OfferIdType& OfferId);
		// 按主键定位表内活记录并整行覆盖，newRecord 只提供新值
		bool Update(const PrimaryAccount& newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		PrimaryAccountTablePrimaryKey* PrimaryKey;
		PrimaryAccountTableIndexOfferId* OfferIdIndex;
	private:
		bool HasSubscribers() const;
		RowChangeEventPtr MakeInsertEvent(const PrimaryAccount* record);
		// 单写者前提：Build* 在锁内按写入顺序取号，Publish* 在锁外调用订阅者；订阅者不得回写本表
		// BuildRowChangeEvent 接管 record：无订阅者时记录随句柄回池。Build* 调用方必须持有 SharedMutex。
		RowChangeEventPtr BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record);
		RowChangeEventPtr BuildInsertEvent(const PrimaryAccount* record);
		RowChangeEventPtr BuildUpdateEvent(const PrimaryAccount& newRecord, bool updateDB);
		std::vector<RowChangeEventPtr> BuildBatchInsertEvents(const std::vector<PrimaryAccount*>& records);
		void PublishRowChange(const RowChangeEventPtr& event);
		void PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events);
		void EraseUniqueKey(PrimaryAccount* record);
		void EraseIndex(PrimaryAccount* record);

		// 发布屏障：写事务与快照按交付顺序串行，读者不取此锁
		std::mutex publishMutex_;
		// 只在启动期注册，之后列表不可变，热路径无锁读
		std::vector<MdbSubscriber*> subscribers_;
		MdbReplicaSubscriber* replicaSubscriber_ = nullptr;
		// 只在持 publishMutex_ 时递增
		std::uint64_t sequence_ = 0;
	};

	class AccountTable : public MdbTableBase
	{
	public:
		AccountTable();
		~AccountTable() override;
		virtual unsigned int GetTableId() const override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void SubscribeReplica(MdbReplicaSubscriber* replica) override;
		virtual void UnSubscribe() override;
		virtual void InitDb() override;
		template <typename Visitor>
		void ForEach(Visitor&& visitor)
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				if (!visitor(*it))
				{
					break;
				}
			}
		}
		bool Insert(Account* record);
		void BatchInsert(std::vector<Account*>& records);
		// 按主键定位表内活记录删除，record 只提供主键
		bool Erase(const Account& record);
		// 按主键定位表内活记录并整行覆盖，newRecord 只提供新值
		bool Update(const Account& newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		AccountTablePrimaryKey* PrimaryKey;
	private:
		bool HasSubscribers() const;
		RowChangeEventPtr MakeInsertEvent(const Account* record);
		// 单写者前提：Build* 在锁内按写入顺序取号，Publish* 在锁外调用订阅者；订阅者不得回写本表
		// BuildRowChangeEvent 接管 record：无订阅者时记录随句柄回池。Build* 调用方必须持有 SharedMutex。
		RowChangeEventPtr BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record);
		RowChangeEventPtr BuildInsertEvent(const Account* record);
		RowChangeEventPtr BuildUpdateEvent(const Account& newRecord, bool updateDB);
		std::vector<RowChangeEventPtr> BuildBatchInsertEvents(const std::vector<Account*>& records);
		void PublishRowChange(const RowChangeEventPtr& event);
		void PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events);
		void EraseUniqueKey(Account* record);
		void EraseIndex(Account* record);

		// 发布屏障：写事务与快照按交付顺序串行，读者不取此锁
		std::mutex publishMutex_;
		// 只在启动期注册，之后列表不可变，热路径无锁读
		std::vector<MdbSubscriber*> subscribers_;
		MdbReplicaSubscriber* replicaSubscriber_ = nullptr;
		// 只在持 publishMutex_ 时递增
		std::uint64_t sequence_ = 0;
	};

	class CapitalTable : public MdbTableBase
	{
	public:
		CapitalTable();
		~CapitalTable() override;
		virtual unsigned int GetTableId() const override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void SubscribeReplica(MdbReplicaSubscriber* replica) override;
		virtual void UnSubscribe() override;
		virtual void InitDb() override;
		template <typename Visitor>
		void ForEach(Visitor&& visitor)
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				if (!visitor(*it))
				{
					break;
				}
			}
		}
		bool Insert(Capital* record);
		void BatchInsert(std::vector<Capital*>& records);
		// 按主键定位表内活记录删除，record 只提供主键
		bool Erase(const Capital& record);
		int EraseByTradingDayIndex(const DateType& TradingDay);
		// 按主键定位表内活记录并整行覆盖，newRecord 只提供新值
		bool Update(const Capital& newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		CapitalTablePrimaryKey* PrimaryKey;
		CapitalTableIndexTradingDay* TradingDayIndex;
	private:
		bool HasSubscribers() const;
		RowChangeEventPtr MakeInsertEvent(const Capital* record);
		// 单写者前提：Build* 在锁内按写入顺序取号，Publish* 在锁外调用订阅者；订阅者不得回写本表
		// BuildRowChangeEvent 接管 record：无订阅者时记录随句柄回池。Build* 调用方必须持有 SharedMutex。
		RowChangeEventPtr BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record);
		RowChangeEventPtr BuildInsertEvent(const Capital* record);
		RowChangeEventPtr BuildUpdateEvent(const Capital& newRecord, bool updateDB);
		std::vector<RowChangeEventPtr> BuildBatchInsertEvents(const std::vector<Capital*>& records);
		void PublishRowChange(const RowChangeEventPtr& event);
		void PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events);
		void EraseUniqueKey(Capital* record);
		void EraseIndex(Capital* record);

		// 发布屏障：写事务与快照按交付顺序串行，读者不取此锁
		std::mutex publishMutex_;
		// 只在启动期注册，之后列表不可变，热路径无锁读
		std::vector<MdbSubscriber*> subscribers_;
		MdbReplicaSubscriber* replicaSubscriber_ = nullptr;
		// 只在持 publishMutex_ 时递增
		std::uint64_t sequence_ = 0;
	};

	class PositionTable : public MdbTableBase
	{
	public:
		PositionTable();
		~PositionTable() override;
		virtual unsigned int GetTableId() const override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void SubscribeReplica(MdbReplicaSubscriber* replica) override;
		virtual void UnSubscribe() override;
		virtual void InitDb() override;
		template <typename Visitor>
		void ForEach(Visitor&& visitor)
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				if (!visitor(*it))
				{
					break;
				}
			}
		}
		bool Insert(Position* record);
		void BatchInsert(std::vector<Position*>& records);
		// 按主键定位表内活记录删除，record 只提供主键
		bool Erase(const Position& record);
		int EraseByAccountIndex(const DateType& TradingDay, const AccountIdType& AccountId);
		int EraseByTradingDayIndex(const DateType& TradingDay);
		// 按主键定位表内活记录并整行覆盖，newRecord 只提供新值
		bool Update(const Position& newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		PositionTablePrimaryKey* PrimaryKey;
		PositionTableIndexAccount* AccountIndex;
		PositionTableIndexTradingDay* TradingDayIndex;
	private:
		bool HasSubscribers() const;
		RowChangeEventPtr MakeInsertEvent(const Position* record);
		// 单写者前提：Build* 在锁内按写入顺序取号，Publish* 在锁外调用订阅者；订阅者不得回写本表
		// BuildRowChangeEvent 接管 record：无订阅者时记录随句柄回池。Build* 调用方必须持有 SharedMutex。
		RowChangeEventPtr BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record);
		RowChangeEventPtr BuildInsertEvent(const Position* record);
		RowChangeEventPtr BuildUpdateEvent(const Position& newRecord, bool updateDB);
		std::vector<RowChangeEventPtr> BuildBatchInsertEvents(const std::vector<Position*>& records);
		void PublishRowChange(const RowChangeEventPtr& event);
		void PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events);
		void EraseUniqueKey(Position* record);
		void EraseIndex(Position* record);

		// 发布屏障：写事务与快照按交付顺序串行，读者不取此锁
		std::mutex publishMutex_;
		// 只在启动期注册，之后列表不可变，热路径无锁读
		std::vector<MdbSubscriber*> subscribers_;
		MdbReplicaSubscriber* replicaSubscriber_ = nullptr;
		// 只在持 publishMutex_ 时递增
		std::uint64_t sequence_ = 0;
	};

	class PositionDetailTable : public MdbTableBase
	{
	public:
		PositionDetailTable();
		~PositionDetailTable() override;
		virtual unsigned int GetTableId() const override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void SubscribeReplica(MdbReplicaSubscriber* replica) override;
		virtual void UnSubscribe() override;
		virtual void InitDb() override;
		template <typename Visitor>
		void ForEach(Visitor&& visitor)
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				if (!visitor(*it))
				{
					break;
				}
			}
		}
		bool Insert(PositionDetail* record);
		void BatchInsert(std::vector<PositionDetail*>& records);
		// 按主键定位表内活记录删除，record 只提供主键
		bool Erase(const PositionDetail& record);
		int EraseByTradeMatchIndex(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection);
		int EraseByTradingDayIndex(const DateType& TradingDay);
		// 按主键定位表内活记录并整行覆盖，newRecord 只提供新值
		bool Update(const PositionDetail& newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		PositionDetailTablePrimaryKey* PrimaryKey;
		PositionDetailTableIndexTradeMatch* TradeMatchIndex;
		PositionDetailTableIndexTradingDay* TradingDayIndex;
	private:
		bool HasSubscribers() const;
		RowChangeEventPtr MakeInsertEvent(const PositionDetail* record);
		// 单写者前提：Build* 在锁内按写入顺序取号，Publish* 在锁外调用订阅者；订阅者不得回写本表
		// BuildRowChangeEvent 接管 record：无订阅者时记录随句柄回池。Build* 调用方必须持有 SharedMutex。
		RowChangeEventPtr BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record);
		RowChangeEventPtr BuildInsertEvent(const PositionDetail* record);
		RowChangeEventPtr BuildUpdateEvent(const PositionDetail& newRecord, bool updateDB);
		std::vector<RowChangeEventPtr> BuildBatchInsertEvents(const std::vector<PositionDetail*>& records);
		void PublishRowChange(const RowChangeEventPtr& event);
		void PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events);
		void EraseUniqueKey(PositionDetail* record);
		void EraseIndex(PositionDetail* record);

		// 发布屏障：写事务与快照按交付顺序串行，读者不取此锁
		std::mutex publishMutex_;
		// 只在启动期注册，之后列表不可变，热路径无锁读
		std::vector<MdbSubscriber*> subscribers_;
		MdbReplicaSubscriber* replicaSubscriber_ = nullptr;
		// 只在持 publishMutex_ 时递增
		std::uint64_t sequence_ = 0;
	};

	class OrderTable : public MdbTableBase
	{
	public:
		OrderTable();
		~OrderTable() override;
		virtual unsigned int GetTableId() const override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void SubscribeReplica(MdbReplicaSubscriber* replica) override;
		virtual void UnSubscribe() override;
		virtual void InitDb() override;
		template <typename Visitor>
		void ForEach(Visitor&& visitor)
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				if (!visitor(*it))
				{
					break;
				}
			}
		}
		bool Insert(Order* record);
		void BatchInsert(std::vector<Order*>& records);
		// 按主键定位表内活记录删除，record 只提供主键
		bool Erase(const Order& record);
		int EraseByAccountIdIndex(const DateType& TradingDay, const AccountIdType& AccountId);
		// 按主键定位表内活记录并整行覆盖，newRecord 只提供新值
		bool Update(const Order& newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		OrderTablePrimaryKey* PrimaryKey;
		OrderTableUniqueKeyClientOrderId* ClientOrderIdUniqueKey;
		OrderTableIndexAccountId* AccountIdIndex;
	private:
		bool HasSubscribers() const;
		RowChangeEventPtr MakeInsertEvent(const Order* record);
		// 单写者前提：Build* 在锁内按写入顺序取号，Publish* 在锁外调用订阅者；订阅者不得回写本表
		// BuildRowChangeEvent 接管 record：无订阅者时记录随句柄回池。Build* 调用方必须持有 SharedMutex。
		RowChangeEventPtr BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record);
		RowChangeEventPtr BuildInsertEvent(const Order* record);
		RowChangeEventPtr BuildUpdateEvent(const Order& newRecord, bool updateDB);
		std::vector<RowChangeEventPtr> BuildBatchInsertEvents(const std::vector<Order*>& records);
		void PublishRowChange(const RowChangeEventPtr& event);
		void PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events);
		void EraseUniqueKey(Order* record);
		void EraseIndex(Order* record);

		// 发布屏障：写事务与快照按交付顺序串行，读者不取此锁
		std::mutex publishMutex_;
		// 只在启动期注册，之后列表不可变，热路径无锁读
		std::vector<MdbSubscriber*> subscribers_;
		MdbReplicaSubscriber* replicaSubscriber_ = nullptr;
		// 只在持 publishMutex_ 时递增
		std::uint64_t sequence_ = 0;
	};

	class TradeTable : public MdbTableBase
	{
	public:
		TradeTable();
		~TradeTable() override;
		virtual unsigned int GetTableId() const override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void SubscribeReplica(MdbReplicaSubscriber* replica) override;
		virtual void UnSubscribe() override;
		virtual void InitDb() override;
		template <typename Visitor>
		void ForEach(Visitor&& visitor)
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				if (!visitor(*it))
				{
					break;
				}
			}
		}
		bool Insert(Trade* record);
		void BatchInsert(std::vector<Trade*>& records);
		// 按主键定位表内活记录删除，record 只提供主键
		bool Erase(const Trade& record);
		int EraseByAccountIdIndex(const DateType& TradingDay, const AccountIdType& AccountId);
		// 按主键定位表内活记录并整行覆盖，newRecord 只提供新值
		bool Update(const Trade& newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		TradeTablePrimaryKey* PrimaryKey;
		TradeTableIndexAccountId* AccountIdIndex;
	private:
		bool HasSubscribers() const;
		RowChangeEventPtr MakeInsertEvent(const Trade* record);
		// 单写者前提：Build* 在锁内按写入顺序取号，Publish* 在锁外调用订阅者；订阅者不得回写本表
		// BuildRowChangeEvent 接管 record：无订阅者时记录随句柄回池。Build* 调用方必须持有 SharedMutex。
		RowChangeEventPtr BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record);
		RowChangeEventPtr BuildInsertEvent(const Trade* record);
		RowChangeEventPtr BuildUpdateEvent(const Trade& newRecord, bool updateDB);
		std::vector<RowChangeEventPtr> BuildBatchInsertEvents(const std::vector<Trade*>& records);
		void PublishRowChange(const RowChangeEventPtr& event);
		void PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events);
		void EraseUniqueKey(Trade* record);
		void EraseIndex(Trade* record);

		// 发布屏障：写事务与快照按交付顺序串行，读者不取此锁
		std::mutex publishMutex_;
		// 只在启动期注册，之后列表不可变，热路径无锁读
		std::vector<MdbSubscriber*> subscribers_;
		MdbReplicaSubscriber* replicaSubscriber_ = nullptr;
		// 只在持 publishMutex_ 时递增
		std::uint64_t sequence_ = 0;
	};

	class AccountLoginSessionTable : public MdbTableBase
	{
	public:
		AccountLoginSessionTable();
		~AccountLoginSessionTable() override;
		virtual unsigned int GetTableId() const override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void SubscribeReplica(MdbReplicaSubscriber* replica) override;
		virtual void UnSubscribe() override;
		virtual void InitDb() override;
		template <typename Visitor>
		void ForEach(Visitor&& visitor)
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				if (!visitor(*it))
				{
					break;
				}
			}
		}
		bool Insert(AccountLoginSession* record);
		void BatchInsert(std::vector<AccountLoginSession*>& records);
		// 按主键定位表内活记录删除，record 只提供主键
		bool Erase(const AccountLoginSession& record);
		int EraseBySessionIdIndex(const SessionIdType& SessionId);
		int EraseByAccountIdIndex(const AccountIdType& AccountId);
		// 按主键定位表内活记录并整行覆盖，newRecord 只提供新值
		bool Update(const AccountLoginSession& newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		AccountLoginSessionTablePrimaryKey* PrimaryKey;
		AccountLoginSessionTableIndexSessionId* SessionIdIndex;
		AccountLoginSessionTableIndexAccountId* AccountIdIndex;
	private:
		bool HasSubscribers() const;
		RowChangeEventPtr MakeInsertEvent(const AccountLoginSession* record);
		// 单写者前提：Build* 在锁内按写入顺序取号，Publish* 在锁外调用订阅者；订阅者不得回写本表
		// BuildRowChangeEvent 接管 record：无订阅者时记录随句柄回池。Build* 调用方必须持有 SharedMutex。
		RowChangeEventPtr BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record);
		RowChangeEventPtr BuildInsertEvent(const AccountLoginSession* record);
		RowChangeEventPtr BuildUpdateEvent(const AccountLoginSession& newRecord, bool updateDB);
		std::vector<RowChangeEventPtr> BuildBatchInsertEvents(const std::vector<AccountLoginSession*>& records);
		void PublishRowChange(const RowChangeEventPtr& event);
		void PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events);
		void EraseUniqueKey(AccountLoginSession* record);
		void EraseIndex(AccountLoginSession* record);

		// 发布屏障：写事务与快照按交付顺序串行，读者不取此锁
		std::mutex publishMutex_;
		// 只在启动期注册，之后列表不可变，热路径无锁读
		std::vector<MdbSubscriber*> subscribers_;
		MdbReplicaSubscriber* replicaSubscriber_ = nullptr;
		// 只在持 publishMutex_ 时递增
		std::uint64_t sequence_ = 0;
	};

	class PrimaryAccountLoginSessionTable : public MdbTableBase
	{
	public:
		PrimaryAccountLoginSessionTable();
		~PrimaryAccountLoginSessionTable() override;
		virtual unsigned int GetTableId() const override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void SubscribeReplica(MdbReplicaSubscriber* replica) override;
		virtual void UnSubscribe() override;
		virtual void InitDb() override;
		template <typename Visitor>
		void ForEach(Visitor&& visitor)
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				if (!visitor(*it))
				{
					break;
				}
			}
		}
		bool Insert(PrimaryAccountLoginSession* record);
		void BatchInsert(std::vector<PrimaryAccountLoginSession*>& records);
		// 按主键定位表内活记录删除，record 只提供主键
		bool Erase(const PrimaryAccountLoginSession& record);
		int EraseBySessionIdIndex(const SessionIdType& SessionId);
		int EraseByPrimaryAccountIdIndex(const AccountIdType& PrimaryAccountId);
		// 按主键定位表内活记录并整行覆盖，newRecord 只提供新值
		bool Update(const PrimaryAccountLoginSession& newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		PrimaryAccountLoginSessionTablePrimaryKey* PrimaryKey;
		PrimaryAccountLoginSessionTableIndexSessionId* SessionIdIndex;
		PrimaryAccountLoginSessionTableIndexPrimaryAccountId* PrimaryAccountIdIndex;
	private:
		bool HasSubscribers() const;
		RowChangeEventPtr MakeInsertEvent(const PrimaryAccountLoginSession* record);
		// 单写者前提：Build* 在锁内按写入顺序取号，Publish* 在锁外调用订阅者；订阅者不得回写本表
		// BuildRowChangeEvent 接管 record：无订阅者时记录随句柄回池。Build* 调用方必须持有 SharedMutex。
		RowChangeEventPtr BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record);
		RowChangeEventPtr BuildInsertEvent(const PrimaryAccountLoginSession* record);
		RowChangeEventPtr BuildUpdateEvent(const PrimaryAccountLoginSession& newRecord, bool updateDB);
		std::vector<RowChangeEventPtr> BuildBatchInsertEvents(const std::vector<PrimaryAccountLoginSession*>& records);
		void PublishRowChange(const RowChangeEventPtr& event);
		void PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events);
		void EraseUniqueKey(PrimaryAccountLoginSession* record);
		void EraseIndex(PrimaryAccountLoginSession* record);

		// 发布屏障：写事务与快照按交付顺序串行，读者不取此锁
		std::mutex publishMutex_;
		// 只在启动期注册，之后列表不可变，热路径无锁读
		std::vector<MdbSubscriber*> subscribers_;
		MdbReplicaSubscriber* replicaSubscriber_ = nullptr;
		// 只在持 publishMutex_ 时递增
		std::uint64_t sequence_ = 0;
	};

	class CommissionGroupTable : public MdbTableBase
	{
	public:
		CommissionGroupTable();
		~CommissionGroupTable() override;
		virtual unsigned int GetTableId() const override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void SubscribeReplica(MdbReplicaSubscriber* replica) override;
		virtual void UnSubscribe() override;
		virtual void InitDb() override;
		template <typename Visitor>
		void ForEach(Visitor&& visitor)
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				if (!visitor(*it))
				{
					break;
				}
			}
		}
		bool Insert(CommissionGroup* record);
		void BatchInsert(std::vector<CommissionGroup*>& records);
		// 按主键定位表内活记录删除，record 只提供主键
		bool Erase(const CommissionGroup& record);
		// 按主键定位表内活记录并整行覆盖，newRecord 只提供新值
		bool Update(const CommissionGroup& newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		CommissionGroupTablePrimaryKey* PrimaryKey;
	private:
		bool HasSubscribers() const;
		RowChangeEventPtr MakeInsertEvent(const CommissionGroup* record);
		// 单写者前提：Build* 在锁内按写入顺序取号，Publish* 在锁外调用订阅者；订阅者不得回写本表
		// BuildRowChangeEvent 接管 record：无订阅者时记录随句柄回池。Build* 调用方必须持有 SharedMutex。
		RowChangeEventPtr BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record);
		RowChangeEventPtr BuildInsertEvent(const CommissionGroup* record);
		RowChangeEventPtr BuildUpdateEvent(const CommissionGroup& newRecord, bool updateDB);
		std::vector<RowChangeEventPtr> BuildBatchInsertEvents(const std::vector<CommissionGroup*>& records);
		void PublishRowChange(const RowChangeEventPtr& event);
		void PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events);
		void EraseUniqueKey(CommissionGroup* record);
		void EraseIndex(CommissionGroup* record);

		// 发布屏障：写事务与快照按交付顺序串行，读者不取此锁
		std::mutex publishMutex_;
		// 只在启动期注册，之后列表不可变，热路径无锁读
		std::vector<MdbSubscriber*> subscribers_;
		MdbReplicaSubscriber* replicaSubscriber_ = nullptr;
		// 只在持 publishMutex_ 时递增
		std::uint64_t sequence_ = 0;
	};

	class BaseCommissionTable : public MdbTableBase
	{
	public:
		BaseCommissionTable();
		~BaseCommissionTable() override;
		virtual unsigned int GetTableId() const override;
		virtual void Subscribe(MdbSubscriber* subscriber) override;
		virtual void SubscribeReplica(MdbReplicaSubscriber* replica) override;
		virtual void UnSubscribe() override;
		virtual void InitDb() override;
		template <typename Visitor>
		void ForEach(Visitor&& visitor)
		{
			std::shared_lock guard(SharedMutex);
			for (auto it = PrimaryKey->index_.begin(); it != PrimaryKey->index_.end(); ++it)
			{
				if (!visitor(*it))
				{
					break;
				}
			}
		}
		bool Insert(BaseCommission* record);
		void BatchInsert(std::vector<BaseCommission*>& records);
		// 按主键定位表内活记录删除，record 只提供主键
		bool Erase(const BaseCommission& record);
		// 按主键定位表内活记录并整行覆盖，newRecord 只提供新值
		bool Update(const BaseCommission& newRecord, bool updateDB = true);
		virtual void TruncateTables() override;
		void TruncateTable();
		virtual void Dump(const char* dir) override;

		std::shared_mutex SharedMutex;
		BaseCommissionTablePrimaryKey* PrimaryKey;
	private:
		bool HasSubscribers() const;
		RowChangeEventPtr MakeInsertEvent(const BaseCommission* record);
		// 单写者前提：Build* 在锁内按写入顺序取号，Publish* 在锁外调用订阅者；订阅者不得回写本表
		// BuildRowChangeEvent 接管 record：无订阅者时记录随句柄回池。Build* 调用方必须持有 SharedMutex。
		RowChangeEventPtr BuildRowChangeEvent(RowChangeType type, unsigned int indexId, bool persistDatabase, RecordHandle record);
		RowChangeEventPtr BuildInsertEvent(const BaseCommission* record);
		RowChangeEventPtr BuildUpdateEvent(const BaseCommission& newRecord, bool updateDB);
		std::vector<RowChangeEventPtr> BuildBatchInsertEvents(const std::vector<BaseCommission*>& records);
		void PublishRowChange(const RowChangeEventPtr& event);
		void PublishRowBatchChange(const std::vector<RowChangeEventPtr>& events);
		void EraseUniqueKey(BaseCommission* record);
		void EraseIndex(BaseCommission* record);

		// 发布屏障：写事务与快照按交付顺序串行，读者不取此锁
		std::mutex publishMutex_;
		// 只在启动期注册，之后列表不可变，热路径无锁读
		std::vector<MdbSubscriber*> subscribers_;
		MdbReplicaSubscriber* replicaSubscriber_ = nullptr;
		// 只在持 publishMutex_ 时递增
		std::uint64_t sequence_ = 0;
	};

}
