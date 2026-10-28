// 本文件由 ../Templates/Cpp/Mdb/LockBased/MdbPrimaryKeys.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include <optional>
#include <unordered_set>
#include "Common/MdbStructs.h"
#include "Common/MdbPrimaryKeyComp.h"
#include "Common/MdbReadLease.h"

namespace QuantTrading
{
	class TradingDayTable;
	class TradingDayTablePrimaryKey
	{
	public:
		using iterator = std::unordered_set<TradingDay*, TradingDayHashForTradingDayPrimaryKey, TradingDayEqualForTradingDayPrimaryKey>::iterator;
		TradingDayTablePrimaryKey(TradingDayTable* tableOwner, size_t buckets = 1000);
		std::optional<TradingDay> Select(const Int32Type& Pk);
		TableRangeLease<iterator> SelectAll();

	protected:
		bool Insert(TradingDay* const record);
		void Erase(TradingDay* const record);
		bool CheckInsert(TradingDay* const record);
		// 调用方必须已持有 SharedMutex；返回表内活记录，不存在则为空
		TradingDay* Find(const TradingDay* record);

	private:
		friend class TradingDayTable;
		
		TradingDayTable* table_;
		std::unordered_set<TradingDay*, TradingDayHashForTradingDayPrimaryKey, TradingDayEqualForTradingDayPrimaryKey> index_;
	};
	class ExchangeTable;
	class ExchangeTablePrimaryKey
	{
	public:
		using iterator = std::unordered_set<Exchange*, ExchangeHashForExchangePrimaryKey, ExchangeEqualForExchangePrimaryKey>::iterator;
		ExchangeTablePrimaryKey(ExchangeTable* tableOwner, size_t buckets = 1000);
		std::optional<Exchange> Select(const ExchangeIdType& ExchangeId);
		TableRangeLease<iterator> SelectAll();

	protected:
		bool Insert(Exchange* const record);
		void Erase(Exchange* const record);
		bool CheckInsert(Exchange* const record);
		// 调用方必须已持有 SharedMutex；返回表内活记录，不存在则为空
		Exchange* Find(const Exchange* record);

	private:
		friend class ExchangeTable;
		
		ExchangeTable* table_;
		std::unordered_set<Exchange*, ExchangeHashForExchangePrimaryKey, ExchangeEqualForExchangePrimaryKey> index_;
	};
	class ProductTable;
	class ProductTablePrimaryKey
	{
	public:
		using iterator = std::unordered_set<Product*, ProductHashForProductPrimaryKey, ProductEqualForProductPrimaryKey>::iterator;
		ProductTablePrimaryKey(ProductTable* tableOwner, size_t buckets = 1000);
		std::optional<Product> Select(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId);
		TableRangeLease<iterator> SelectAll();

	protected:
		bool Insert(Product* const record);
		void Erase(Product* const record);
		bool CheckInsert(Product* const record);
		// 调用方必须已持有 SharedMutex；返回表内活记录，不存在则为空
		Product* Find(const Product* record);

	private:
		friend class ProductTable;
		
		ProductTable* table_;
		std::unordered_set<Product*, ProductHashForProductPrimaryKey, ProductEqualForProductPrimaryKey> index_;
	};
	class HotInstrumentTable;
	class HotInstrumentTablePrimaryKey
	{
	public:
		using iterator = std::unordered_set<HotInstrument*, HotInstrumentHashForHotInstrumentPrimaryKey, HotInstrumentEqualForHotInstrumentPrimaryKey>::iterator;
		HotInstrumentTablePrimaryKey(HotInstrumentTable* tableOwner, size_t buckets = 1000);
		std::optional<HotInstrument> Select(const DateType& TradingDay, const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank);
		TableRangeLease<iterator> SelectAll();

	protected:
		bool Insert(HotInstrument* const record);
		void Erase(HotInstrument* const record);
		bool CheckInsert(HotInstrument* const record);
		// 调用方必须已持有 SharedMutex；返回表内活记录，不存在则为空
		HotInstrument* Find(const HotInstrument* record);

	private:
		friend class HotInstrumentTable;
		
		HotInstrumentTable* table_;
		std::unordered_set<HotInstrument*, HotInstrumentHashForHotInstrumentPrimaryKey, HotInstrumentEqualForHotInstrumentPrimaryKey> index_;
	};
	class InstrumentTable;
	class InstrumentTablePrimaryKey
	{
	public:
		using iterator = std::unordered_set<Instrument*, InstrumentHashForInstrumentPrimaryKey, InstrumentEqualForInstrumentPrimaryKey>::iterator;
		InstrumentTablePrimaryKey(InstrumentTable* tableOwner, size_t buckets = 1000);
		std::optional<Instrument> Select(const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId);
		TableRangeLease<iterator> SelectAll();

	protected:
		bool Insert(Instrument* const record);
		void Erase(Instrument* const record);
		bool CheckInsert(Instrument* const record);
		// 调用方必须已持有 SharedMutex；返回表内活记录，不存在则为空
		Instrument* Find(const Instrument* record);

	private:
		friend class InstrumentTable;
		
		InstrumentTable* table_;
		std::unordered_set<Instrument*, InstrumentHashForInstrumentPrimaryKey, InstrumentEqualForInstrumentPrimaryKey> index_;
	};
	class DepthMarketDataTable;
	class DepthMarketDataTablePrimaryKey
	{
	public:
		using iterator = std::unordered_set<DepthMarketData*, DepthMarketDataHashForDepthMarketDataPrimaryKey, DepthMarketDataEqualForDepthMarketDataPrimaryKey>::iterator;
		DepthMarketDataTablePrimaryKey(DepthMarketDataTable* tableOwner, size_t buckets = 1000);
		std::optional<DepthMarketData> Select(const DateType& TradingDay, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId);
		TableRangeLease<iterator> SelectAll();

	protected:
		bool Insert(DepthMarketData* const record);
		void Erase(DepthMarketData* const record);
		bool CheckInsert(DepthMarketData* const record);
		// 调用方必须已持有 SharedMutex；返回表内活记录，不存在则为空
		DepthMarketData* Find(const DepthMarketData* record);

	private:
		friend class DepthMarketDataTable;
		
		DepthMarketDataTable* table_;
		std::unordered_set<DepthMarketData*, DepthMarketDataHashForDepthMarketDataPrimaryKey, DepthMarketDataEqualForDepthMarketDataPrimaryKey> index_;
	};
	class BarMarketDataTable;
	class BarMarketDataTablePrimaryKey
	{
	public:
		using iterator = std::unordered_set<BarMarketData*, BarMarketDataHashForBarMarketDataPrimaryKey, BarMarketDataEqualForBarMarketDataPrimaryKey>::iterator;
		BarMarketDataTablePrimaryKey(BarMarketDataTable* tableOwner, size_t buckets = 1000);
		std::optional<BarMarketData> Select(const DateType& TradingDay, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const BarPrecesType& BarPreces, const Int32Type& BarPeriod, const Int64Type& BarTime);
		TableRangeLease<iterator> SelectAll();

	protected:
		bool Insert(BarMarketData* const record);
		void Erase(BarMarketData* const record);
		bool CheckInsert(BarMarketData* const record);
		// 调用方必须已持有 SharedMutex；返回表内活记录，不存在则为空
		BarMarketData* Find(const BarMarketData* record);

	private:
		friend class BarMarketDataTable;
		
		BarMarketDataTable* table_;
		std::unordered_set<BarMarketData*, BarMarketDataHashForBarMarketDataPrimaryKey, BarMarketDataEqualForBarMarketDataPrimaryKey> index_;
	};
	class MdSubscribeTable;
	class MdSubscribeTablePrimaryKey
	{
	public:
		using iterator = std::unordered_set<MdSubscribe*, MdSubscribeHashForMdSubscribePrimaryKey, MdSubscribeEqualForMdSubscribePrimaryKey>::iterator;
		MdSubscribeTablePrimaryKey(MdSubscribeTable* tableOwner, size_t buckets = 1000);
		std::optional<MdSubscribe> Select(const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const DateType& StartTradingDay);
		TableRangeLease<iterator> SelectAll();

	protected:
		bool Insert(MdSubscribe* const record);
		void Erase(MdSubscribe* const record);
		bool CheckInsert(MdSubscribe* const record);
		// 调用方必须已持有 SharedMutex；返回表内活记录，不存在则为空
		MdSubscribe* Find(const MdSubscribe* record);

	private:
		friend class MdSubscribeTable;
		
		MdSubscribeTable* table_;
		std::unordered_set<MdSubscribe*, MdSubscribeHashForMdSubscribePrimaryKey, MdSubscribeEqualForMdSubscribePrimaryKey> index_;
	};
	class MdUserTable;
	class MdUserTablePrimaryKey
	{
	public:
		using iterator = std::unordered_set<MdUser*, MdUserHashForMdUserPrimaryKey, MdUserEqualForMdUserPrimaryKey>::iterator;
		MdUserTablePrimaryKey(MdUserTable* tableOwner, size_t buckets = 1000);
		std::optional<MdUser> Select(const UserIdType& MdUserId);
		TableRangeLease<iterator> SelectAll();

	protected:
		bool Insert(MdUser* const record);
		void Erase(MdUser* const record);
		bool CheckInsert(MdUser* const record);
		// 调用方必须已持有 SharedMutex；返回表内活记录，不存在则为空
		MdUser* Find(const MdUser* record);

	private:
		friend class MdUserTable;
		
		MdUserTable* table_;
		std::unordered_set<MdUser*, MdUserHashForMdUserPrimaryKey, MdUserEqualForMdUserPrimaryKey> index_;
	};
	class MdUserLoginSessionTable;
	class MdUserLoginSessionTablePrimaryKey
	{
	public:
		using iterator = std::unordered_set<MdUserLoginSession*, MdUserLoginSessionHashForMdUserLoginSessionPrimaryKey, MdUserLoginSessionEqualForMdUserLoginSessionPrimaryKey>::iterator;
		MdUserLoginSessionTablePrimaryKey(MdUserLoginSessionTable* tableOwner, size_t buckets = 1000);
		std::optional<MdUserLoginSession> Select(const UserIdType& MdUserId, const SessionIdType& SessionId);
		TableRangeLease<iterator> SelectAll();

	protected:
		bool Insert(MdUserLoginSession* const record);
		void Erase(MdUserLoginSession* const record);
		bool CheckInsert(MdUserLoginSession* const record);
		// 调用方必须已持有 SharedMutex；返回表内活记录，不存在则为空
		MdUserLoginSession* Find(const MdUserLoginSession* record);

	private:
		friend class MdUserLoginSessionTable;
		
		MdUserLoginSessionTable* table_;
		std::unordered_set<MdUserLoginSession*, MdUserLoginSessionHashForMdUserLoginSessionPrimaryKey, MdUserLoginSessionEqualForMdUserLoginSessionPrimaryKey> index_;
	};
	class PrimaryAccountTable;
	class PrimaryAccountTablePrimaryKey
	{
	public:
		using iterator = std::unordered_set<PrimaryAccount*, PrimaryAccountHashForPrimaryAccountPrimaryKey, PrimaryAccountEqualForPrimaryAccountPrimaryKey>::iterator;
		PrimaryAccountTablePrimaryKey(PrimaryAccountTable* tableOwner, size_t buckets = 1000);
		std::optional<PrimaryAccount> Select(const AccountIdType& PrimaryAccountId);
		TableRangeLease<iterator> SelectAll();

	protected:
		bool Insert(PrimaryAccount* const record);
		void Erase(PrimaryAccount* const record);
		bool CheckInsert(PrimaryAccount* const record);
		// 调用方必须已持有 SharedMutex；返回表内活记录，不存在则为空
		PrimaryAccount* Find(const PrimaryAccount* record);

	private:
		friend class PrimaryAccountTable;
		
		PrimaryAccountTable* table_;
		std::unordered_set<PrimaryAccount*, PrimaryAccountHashForPrimaryAccountPrimaryKey, PrimaryAccountEqualForPrimaryAccountPrimaryKey> index_;
	};
	class AccountTable;
	class AccountTablePrimaryKey
	{
	public:
		using iterator = std::unordered_set<Account*, AccountHashForAccountPrimaryKey, AccountEqualForAccountPrimaryKey>::iterator;
		AccountTablePrimaryKey(AccountTable* tableOwner, size_t buckets = 1000);
		std::optional<Account> Select(const AccountIdType& AccountId);
		TableRangeLease<iterator> SelectAll();

	protected:
		bool Insert(Account* const record);
		void Erase(Account* const record);
		bool CheckInsert(Account* const record);
		// 调用方必须已持有 SharedMutex；返回表内活记录，不存在则为空
		Account* Find(const Account* record);

	private:
		friend class AccountTable;
		
		AccountTable* table_;
		std::unordered_set<Account*, AccountHashForAccountPrimaryKey, AccountEqualForAccountPrimaryKey> index_;
	};
	class CapitalTable;
	class CapitalTablePrimaryKey
	{
	public:
		using iterator = std::unordered_set<Capital*, CapitalHashForCapitalPrimaryKey, CapitalEqualForCapitalPrimaryKey>::iterator;
		CapitalTablePrimaryKey(CapitalTable* tableOwner, size_t buckets = 1000);
		std::optional<Capital> Select(const DateType& TradingDay, const AccountIdType& AccountId);
		TableRangeLease<iterator> SelectAll();

	protected:
		bool Insert(Capital* const record);
		void Erase(Capital* const record);
		bool CheckInsert(Capital* const record);
		// 调用方必须已持有 SharedMutex；返回表内活记录，不存在则为空
		Capital* Find(const Capital* record);

	private:
		friend class CapitalTable;
		
		CapitalTable* table_;
		std::unordered_set<Capital*, CapitalHashForCapitalPrimaryKey, CapitalEqualForCapitalPrimaryKey> index_;
	};
	class PositionTable;
	class PositionTablePrimaryKey
	{
	public:
		using iterator = std::unordered_set<Position*, PositionHashForPositionPrimaryKey, PositionEqualForPositionPrimaryKey>::iterator;
		PositionTablePrimaryKey(PositionTable* tableOwner, size_t buckets = 1000);
		std::optional<Position> Select(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection);
		TableRangeLease<iterator> SelectAll();

	protected:
		bool Insert(Position* const record);
		void Erase(Position* const record);
		bool CheckInsert(Position* const record);
		// 调用方必须已持有 SharedMutex；返回表内活记录，不存在则为空
		Position* Find(const Position* record);

	private:
		friend class PositionTable;
		
		PositionTable* table_;
		std::unordered_set<Position*, PositionHashForPositionPrimaryKey, PositionEqualForPositionPrimaryKey> index_;
	};
	class PositionDetailTable;
	class PositionDetailTablePrimaryKey
	{
	public:
		using iterator = std::unordered_set<PositionDetail*, PositionDetailHashForPositionDetailPrimaryKey, PositionDetailEqualForPositionDetailPrimaryKey>::iterator;
		PositionDetailTablePrimaryKey(PositionDetailTable* tableOwner, size_t buckets = 1000);
		std::optional<PositionDetail> Select(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection, const DateType& OpenDate, const TradeIdType& TradeId);
		TableRangeLease<iterator> SelectAll();

	protected:
		bool Insert(PositionDetail* const record);
		void Erase(PositionDetail* const record);
		bool CheckInsert(PositionDetail* const record);
		// 调用方必须已持有 SharedMutex；返回表内活记录，不存在则为空
		PositionDetail* Find(const PositionDetail* record);

	private:
		friend class PositionDetailTable;
		
		PositionDetailTable* table_;
		std::unordered_set<PositionDetail*, PositionDetailHashForPositionDetailPrimaryKey, PositionDetailEqualForPositionDetailPrimaryKey> index_;
	};
	class OrderTable;
	class OrderTablePrimaryKey
	{
	public:
		using iterator = std::unordered_set<Order*, OrderHashForOrderPrimaryKey, OrderEqualForOrderPrimaryKey>::iterator;
		OrderTablePrimaryKey(OrderTable* tableOwner, size_t buckets = 1000);
		std::optional<Order> Select(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const OrderIdType& OrderId);
		TableRangeLease<iterator> SelectAll();

	protected:
		bool Insert(Order* const record);
		void Erase(Order* const record);
		bool CheckInsert(Order* const record);
		// 调用方必须已持有 SharedMutex；返回表内活记录，不存在则为空
		Order* Find(const Order* record);

	private:
		friend class OrderTable;
		
		OrderTable* table_;
		std::unordered_set<Order*, OrderHashForOrderPrimaryKey, OrderEqualForOrderPrimaryKey> index_;
	};
	class OrderTableUniqueKeyClientOrderId
	{
	public:
		OrderTableUniqueKeyClientOrderId(OrderTable* tableOwner, size_t buckets = 1000);
		std::optional<Order> Select(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const SessionIdType& SessionId, const ClientOrderIdType& ClientOrderId);

	protected:
		bool Insert(Order* const record);
		void Erase(Order* const record);
		bool CheckInsert(Order* const record);
		bool CheckUpdate(const Order* const oldRecord, const Order* const newRecord);

	private:
		friend class OrderTable;
	
		OrderTable* table_;
		std::unordered_set<Order*, OrderHashForClientOrderIdUniqueKey, OrderEqualForClientOrderIdUniqueKey> index_;
	};
	
	class TradeTable;
	class TradeTablePrimaryKey
	{
	public:
		using iterator = std::unordered_set<Trade*, TradeHashForTradePrimaryKey, TradeEqualForTradePrimaryKey>::iterator;
		TradeTablePrimaryKey(TradeTable* tableOwner, size_t buckets = 1000);
		std::optional<Trade> Select(const DateType& TradingDay, const ExchangeIdType& ExchangeId, const TradeIdType& TradeId, const DirectionType& Direction);
		TableRangeLease<iterator> SelectAll();

	protected:
		bool Insert(Trade* const record);
		void Erase(Trade* const record);
		bool CheckInsert(Trade* const record);
		// 调用方必须已持有 SharedMutex；返回表内活记录，不存在则为空
		Trade* Find(const Trade* record);

	private:
		friend class TradeTable;
		
		TradeTable* table_;
		std::unordered_set<Trade*, TradeHashForTradePrimaryKey, TradeEqualForTradePrimaryKey> index_;
	};
	class AccountLoginSessionTable;
	class AccountLoginSessionTablePrimaryKey
	{
	public:
		using iterator = std::unordered_set<AccountLoginSession*, AccountLoginSessionHashForAccountLoginSessionPrimaryKey, AccountLoginSessionEqualForAccountLoginSessionPrimaryKey>::iterator;
		AccountLoginSessionTablePrimaryKey(AccountLoginSessionTable* tableOwner, size_t buckets = 1000);
		std::optional<AccountLoginSession> Select(const AccountIdType& AccountId, const SessionIdType& SessionId);
		TableRangeLease<iterator> SelectAll();

	protected:
		bool Insert(AccountLoginSession* const record);
		void Erase(AccountLoginSession* const record);
		bool CheckInsert(AccountLoginSession* const record);
		// 调用方必须已持有 SharedMutex；返回表内活记录，不存在则为空
		AccountLoginSession* Find(const AccountLoginSession* record);

	private:
		friend class AccountLoginSessionTable;
		
		AccountLoginSessionTable* table_;
		std::unordered_set<AccountLoginSession*, AccountLoginSessionHashForAccountLoginSessionPrimaryKey, AccountLoginSessionEqualForAccountLoginSessionPrimaryKey> index_;
	};
	class PrimaryAccountLoginSessionTable;
	class PrimaryAccountLoginSessionTablePrimaryKey
	{
	public:
		using iterator = std::unordered_set<PrimaryAccountLoginSession*, PrimaryAccountLoginSessionHashForPrimaryAccountLoginSessionPrimaryKey, PrimaryAccountLoginSessionEqualForPrimaryAccountLoginSessionPrimaryKey>::iterator;
		PrimaryAccountLoginSessionTablePrimaryKey(PrimaryAccountLoginSessionTable* tableOwner, size_t buckets = 1000);
		std::optional<PrimaryAccountLoginSession> Select(const AccountIdType& PrimaryAccountId, const SessionIdType& SessionId);
		TableRangeLease<iterator> SelectAll();

	protected:
		bool Insert(PrimaryAccountLoginSession* const record);
		void Erase(PrimaryAccountLoginSession* const record);
		bool CheckInsert(PrimaryAccountLoginSession* const record);
		// 调用方必须已持有 SharedMutex；返回表内活记录，不存在则为空
		PrimaryAccountLoginSession* Find(const PrimaryAccountLoginSession* record);

	private:
		friend class PrimaryAccountLoginSessionTable;
		
		PrimaryAccountLoginSessionTable* table_;
		std::unordered_set<PrimaryAccountLoginSession*, PrimaryAccountLoginSessionHashForPrimaryAccountLoginSessionPrimaryKey, PrimaryAccountLoginSessionEqualForPrimaryAccountLoginSessionPrimaryKey> index_;
	};
	class CommissionGroupTable;
	class CommissionGroupTablePrimaryKey
	{
	public:
		using iterator = std::unordered_set<CommissionGroup*, CommissionGroupHashForCommissionGroupPrimaryKey, CommissionGroupEqualForCommissionGroupPrimaryKey>::iterator;
		CommissionGroupTablePrimaryKey(CommissionGroupTable* tableOwner, size_t buckets = 1000);
		std::optional<CommissionGroup> Select(const GroupIdType& CommissionGroupId);
		TableRangeLease<iterator> SelectAll();

	protected:
		bool Insert(CommissionGroup* const record);
		void Erase(CommissionGroup* const record);
		bool CheckInsert(CommissionGroup* const record);
		// 调用方必须已持有 SharedMutex；返回表内活记录，不存在则为空
		CommissionGroup* Find(const CommissionGroup* record);

	private:
		friend class CommissionGroupTable;
		
		CommissionGroupTable* table_;
		std::unordered_set<CommissionGroup*, CommissionGroupHashForCommissionGroupPrimaryKey, CommissionGroupEqualForCommissionGroupPrimaryKey> index_;
	};
	class BaseCommissionTable;
	class BaseCommissionTablePrimaryKey
	{
	public:
		using iterator = std::unordered_set<BaseCommission*, BaseCommissionHashForBaseCommissionPrimaryKey, BaseCommissionEqualForBaseCommissionPrimaryKey>::iterator;
		BaseCommissionTablePrimaryKey(BaseCommissionTable* tableOwner, size_t buckets = 1000);
		std::optional<BaseCommission> Select(const GroupIdType& CommissionGroupId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const DirectionType& Direction);
		TableRangeLease<iterator> SelectAll();

	protected:
		bool Insert(BaseCommission* const record);
		void Erase(BaseCommission* const record);
		bool CheckInsert(BaseCommission* const record);
		// 调用方必须已持有 SharedMutex；返回表内活记录，不存在则为空
		BaseCommission* Find(const BaseCommission* record);

	private:
		friend class BaseCommissionTable;
		
		BaseCommissionTable* table_;
		std::unordered_set<BaseCommission*, BaseCommissionHashForBaseCommissionPrimaryKey, BaseCommissionEqualForBaseCommissionPrimaryKey> index_;
	};
}
