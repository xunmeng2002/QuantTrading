// 本文件由 ../Templates/Cpp/Mdb/MdbPrimaryKeys.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include <unordered_set>
#include "MdbStructs.h"
#include "MdbPrimaryKeyComp.h"

namespace QuantTrading
{
	class TradingDayTable;
	class TradingDayPrimaryKey
	{
	public:
		using iterator = std::unordered_set<TradingDay*, TradingDayHashForTradingDayPrimaryKey, TradingDayEqualForTradingDayPrimaryKey>::iterator;
		TradingDayPrimaryKey(TradingDayTable* tableOwner, size_t buckets = 1000);
		TradingDay* Select(const Int32Type& Pk);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(TradingDay* const record);
		void Erase(TradingDay* const record);
		bool CheckInsert(TradingDay* const record);
		bool CheckUpdate(const TradingDay* const oldRecord, const TradingDay* const newRecord);

	private:
		friend class TradingDayTable;
		
		TradingDayTable* table_;
		std::unordered_set<TradingDay*, TradingDayHashForTradingDayPrimaryKey, TradingDayEqualForTradingDayPrimaryKey> index_;
	};
	class ExchangeTable;
	class ExchangePrimaryKey
	{
	public:
		using iterator = std::unordered_set<Exchange*, ExchangeHashForExchangePrimaryKey, ExchangeEqualForExchangePrimaryKey>::iterator;
		ExchangePrimaryKey(ExchangeTable* tableOwner, size_t buckets = 1000);
		Exchange* Select(const ExchangeIdType& ExchangeId);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(Exchange* const record);
		void Erase(Exchange* const record);
		bool CheckInsert(Exchange* const record);
		bool CheckUpdate(const Exchange* const oldRecord, const Exchange* const newRecord);

	private:
		friend class ExchangeTable;
		
		ExchangeTable* table_;
		std::unordered_set<Exchange*, ExchangeHashForExchangePrimaryKey, ExchangeEqualForExchangePrimaryKey> index_;
	};
	class ProductTable;
	class ProductPrimaryKey
	{
	public:
		using iterator = std::unordered_set<Product*, ProductHashForProductPrimaryKey, ProductEqualForProductPrimaryKey>::iterator;
		ProductPrimaryKey(ProductTable* tableOwner, size_t buckets = 1000);
		Product* Select(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(Product* const record);
		void Erase(Product* const record);
		bool CheckInsert(Product* const record);
		bool CheckUpdate(const Product* const oldRecord, const Product* const newRecord);

	private:
		friend class ProductTable;
		
		ProductTable* table_;
		std::unordered_set<Product*, ProductHashForProductPrimaryKey, ProductEqualForProductPrimaryKey> index_;
	};
	class HotInstrumentTable;
	class HotInstrumentPrimaryKey
	{
	public:
		using iterator = std::unordered_set<HotInstrument*, HotInstrumentHashForHotInstrumentPrimaryKey, HotInstrumentEqualForHotInstrumentPrimaryKey>::iterator;
		HotInstrumentPrimaryKey(HotInstrumentTable* tableOwner, size_t buckets = 1000);
		HotInstrument* Select(const DateType& TradingDay, const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(HotInstrument* const record);
		void Erase(HotInstrument* const record);
		bool CheckInsert(HotInstrument* const record);
		bool CheckUpdate(const HotInstrument* const oldRecord, const HotInstrument* const newRecord);

	private:
		friend class HotInstrumentTable;
		
		HotInstrumentTable* table_;
		std::unordered_set<HotInstrument*, HotInstrumentHashForHotInstrumentPrimaryKey, HotInstrumentEqualForHotInstrumentPrimaryKey> index_;
	};
	class InstrumentTable;
	class InstrumentPrimaryKey
	{
	public:
		using iterator = std::unordered_set<Instrument*, InstrumentHashForInstrumentPrimaryKey, InstrumentEqualForInstrumentPrimaryKey>::iterator;
		InstrumentPrimaryKey(InstrumentTable* tableOwner, size_t buckets = 1000);
		Instrument* Select(const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(Instrument* const record);
		void Erase(Instrument* const record);
		bool CheckInsert(Instrument* const record);
		bool CheckUpdate(const Instrument* const oldRecord, const Instrument* const newRecord);

	private:
		friend class InstrumentTable;
		
		InstrumentTable* table_;
		std::unordered_set<Instrument*, InstrumentHashForInstrumentPrimaryKey, InstrumentEqualForInstrumentPrimaryKey> index_;
	};
	class DepthMarketDataTable;
	class DepthMarketDataPrimaryKey
	{
	public:
		using iterator = std::unordered_set<DepthMarketData*, DepthMarketDataHashForDepthMarketDataPrimaryKey, DepthMarketDataEqualForDepthMarketDataPrimaryKey>::iterator;
		DepthMarketDataPrimaryKey(DepthMarketDataTable* tableOwner, size_t buckets = 1000);
		DepthMarketData* Select(const DateType& TradingDay, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(DepthMarketData* const record);
		void Erase(DepthMarketData* const record);
		bool CheckInsert(DepthMarketData* const record);
		bool CheckUpdate(const DepthMarketData* const oldRecord, const DepthMarketData* const newRecord);

	private:
		friend class DepthMarketDataTable;
		
		DepthMarketDataTable* table_;
		std::unordered_set<DepthMarketData*, DepthMarketDataHashForDepthMarketDataPrimaryKey, DepthMarketDataEqualForDepthMarketDataPrimaryKey> index_;
	};
	class BarMarketDataTable;
	class BarMarketDataPrimaryKey
	{
	public:
		using iterator = std::unordered_set<BarMarketData*, BarMarketDataHashForBarMarketDataPrimaryKey, BarMarketDataEqualForBarMarketDataPrimaryKey>::iterator;
		BarMarketDataPrimaryKey(BarMarketDataTable* tableOwner, size_t buckets = 1000);
		BarMarketData* Select(const DateType& TradingDay, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const BarPrecesType& BarPreces, const Int32Type& BarPeriod, const Int64Type& BarTime);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(BarMarketData* const record);
		void Erase(BarMarketData* const record);
		bool CheckInsert(BarMarketData* const record);
		bool CheckUpdate(const BarMarketData* const oldRecord, const BarMarketData* const newRecord);

	private:
		friend class BarMarketDataTable;
		
		BarMarketDataTable* table_;
		std::unordered_set<BarMarketData*, BarMarketDataHashForBarMarketDataPrimaryKey, BarMarketDataEqualForBarMarketDataPrimaryKey> index_;
	};
	class MdSubscribeTable;
	class MdSubscribePrimaryKey
	{
	public:
		using iterator = std::unordered_set<MdSubscribe*, MdSubscribeHashForMdSubscribePrimaryKey, MdSubscribeEqualForMdSubscribePrimaryKey>::iterator;
		MdSubscribePrimaryKey(MdSubscribeTable* tableOwner, size_t buckets = 1000);
		MdSubscribe* Select(const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const DateType& StartTradingDay);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(MdSubscribe* const record);
		void Erase(MdSubscribe* const record);
		bool CheckInsert(MdSubscribe* const record);
		bool CheckUpdate(const MdSubscribe* const oldRecord, const MdSubscribe* const newRecord);

	private:
		friend class MdSubscribeTable;
		
		MdSubscribeTable* table_;
		std::unordered_set<MdSubscribe*, MdSubscribeHashForMdSubscribePrimaryKey, MdSubscribeEqualForMdSubscribePrimaryKey> index_;
	};
	class MdUserTable;
	class MdUserPrimaryKey
	{
	public:
		using iterator = std::unordered_set<MdUser*, MdUserHashForMdUserPrimaryKey, MdUserEqualForMdUserPrimaryKey>::iterator;
		MdUserPrimaryKey(MdUserTable* tableOwner, size_t buckets = 1000);
		MdUser* Select(const UserIdType& MdUserId);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(MdUser* const record);
		void Erase(MdUser* const record);
		bool CheckInsert(MdUser* const record);
		bool CheckUpdate(const MdUser* const oldRecord, const MdUser* const newRecord);

	private:
		friend class MdUserTable;
		
		MdUserTable* table_;
		std::unordered_set<MdUser*, MdUserHashForMdUserPrimaryKey, MdUserEqualForMdUserPrimaryKey> index_;
	};
	class MdUserLoginSessionTable;
	class MdUserLoginSessionPrimaryKey
	{
	public:
		using iterator = std::unordered_set<MdUserLoginSession*, MdUserLoginSessionHashForMdUserLoginSessionPrimaryKey, MdUserLoginSessionEqualForMdUserLoginSessionPrimaryKey>::iterator;
		MdUserLoginSessionPrimaryKey(MdUserLoginSessionTable* tableOwner, size_t buckets = 1000);
		MdUserLoginSession* Select(const UserIdType& MdUserId, const SessionIdType& SessionId);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(MdUserLoginSession* const record);
		void Erase(MdUserLoginSession* const record);
		bool CheckInsert(MdUserLoginSession* const record);
		bool CheckUpdate(const MdUserLoginSession* const oldRecord, const MdUserLoginSession* const newRecord);

	private:
		friend class MdUserLoginSessionTable;
		
		MdUserLoginSessionTable* table_;
		std::unordered_set<MdUserLoginSession*, MdUserLoginSessionHashForMdUserLoginSessionPrimaryKey, MdUserLoginSessionEqualForMdUserLoginSessionPrimaryKey> index_;
	};
	class PrimaryAccountTable;
	class PrimaryAccountPrimaryKey
	{
	public:
		using iterator = std::unordered_set<PrimaryAccount*, PrimaryAccountHashForPrimaryAccountPrimaryKey, PrimaryAccountEqualForPrimaryAccountPrimaryKey>::iterator;
		PrimaryAccountPrimaryKey(PrimaryAccountTable* tableOwner, size_t buckets = 1000);
		PrimaryAccount* Select(const AccountIdType& PrimaryAccountId);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(PrimaryAccount* const record);
		void Erase(PrimaryAccount* const record);
		bool CheckInsert(PrimaryAccount* const record);
		bool CheckUpdate(const PrimaryAccount* const oldRecord, const PrimaryAccount* const newRecord);

	private:
		friend class PrimaryAccountTable;
		
		PrimaryAccountTable* table_;
		std::unordered_set<PrimaryAccount*, PrimaryAccountHashForPrimaryAccountPrimaryKey, PrimaryAccountEqualForPrimaryAccountPrimaryKey> index_;
	};
	class AccountTable;
	class AccountPrimaryKey
	{
	public:
		using iterator = std::unordered_set<Account*, AccountHashForAccountPrimaryKey, AccountEqualForAccountPrimaryKey>::iterator;
		AccountPrimaryKey(AccountTable* tableOwner, size_t buckets = 1000);
		Account* Select(const AccountIdType& AccountId);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(Account* const record);
		void Erase(Account* const record);
		bool CheckInsert(Account* const record);
		bool CheckUpdate(const Account* const oldRecord, const Account* const newRecord);

	private:
		friend class AccountTable;
		
		AccountTable* table_;
		std::unordered_set<Account*, AccountHashForAccountPrimaryKey, AccountEqualForAccountPrimaryKey> index_;
	};
	class CapitalTable;
	class CapitalPrimaryKey
	{
	public:
		using iterator = std::unordered_set<Capital*, CapitalHashForCapitalPrimaryKey, CapitalEqualForCapitalPrimaryKey>::iterator;
		CapitalPrimaryKey(CapitalTable* tableOwner, size_t buckets = 1000);
		Capital* Select(const DateType& TradingDay, const AccountIdType& AccountId);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(Capital* const record);
		void Erase(Capital* const record);
		bool CheckInsert(Capital* const record);
		bool CheckUpdate(const Capital* const oldRecord, const Capital* const newRecord);

	private:
		friend class CapitalTable;
		
		CapitalTable* table_;
		std::unordered_set<Capital*, CapitalHashForCapitalPrimaryKey, CapitalEqualForCapitalPrimaryKey> index_;
	};
	class PositionTable;
	class PositionPrimaryKey
	{
	public:
		using iterator = std::unordered_set<Position*, PositionHashForPositionPrimaryKey, PositionEqualForPositionPrimaryKey>::iterator;
		PositionPrimaryKey(PositionTable* tableOwner, size_t buckets = 1000);
		Position* Select(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(Position* const record);
		void Erase(Position* const record);
		bool CheckInsert(Position* const record);
		bool CheckUpdate(const Position* const oldRecord, const Position* const newRecord);

	private:
		friend class PositionTable;
		
		PositionTable* table_;
		std::unordered_set<Position*, PositionHashForPositionPrimaryKey, PositionEqualForPositionPrimaryKey> index_;
	};
	class PositionDetailTable;
	class PositionDetailPrimaryKey
	{
	public:
		using iterator = std::unordered_set<PositionDetail*, PositionDetailHashForPositionDetailPrimaryKey, PositionDetailEqualForPositionDetailPrimaryKey>::iterator;
		PositionDetailPrimaryKey(PositionDetailTable* tableOwner, size_t buckets = 1000);
		PositionDetail* Select(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection, const DateType& OpenDate, const TradeIdType& TradeId);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(PositionDetail* const record);
		void Erase(PositionDetail* const record);
		bool CheckInsert(PositionDetail* const record);
		bool CheckUpdate(const PositionDetail* const oldRecord, const PositionDetail* const newRecord);

	private:
		friend class PositionDetailTable;
		
		PositionDetailTable* table_;
		std::unordered_set<PositionDetail*, PositionDetailHashForPositionDetailPrimaryKey, PositionDetailEqualForPositionDetailPrimaryKey> index_;
	};
	class OrderTable;
	class OrderPrimaryKey
	{
	public:
		using iterator = std::unordered_set<Order*, OrderHashForOrderPrimaryKey, OrderEqualForOrderPrimaryKey>::iterator;
		OrderPrimaryKey(OrderTable* tableOwner, size_t buckets = 1000);
		Order* Select(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const OrderIdType& OrderId);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(Order* const record);
		void Erase(Order* const record);
		bool CheckInsert(Order* const record);
		bool CheckUpdate(const Order* const oldRecord, const Order* const newRecord);

	private:
		friend class OrderTable;
		
		OrderTable* table_;
		std::unordered_set<Order*, OrderHashForOrderPrimaryKey, OrderEqualForOrderPrimaryKey> index_;
	};
	class OrderUniqueKeyClientOrderId
	{
	public:
		OrderUniqueKeyClientOrderId(OrderTable* tableOwner, size_t buckets = 1000);
		Order* Select(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const SessionIdType& SessionId, const ClientOrderIdType& ClientOrderId);
		
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
	class TradePrimaryKey
	{
	public:
		using iterator = std::unordered_set<Trade*, TradeHashForTradePrimaryKey, TradeEqualForTradePrimaryKey>::iterator;
		TradePrimaryKey(TradeTable* tableOwner, size_t buckets = 1000);
		Trade* Select(const DateType& TradingDay, const ExchangeIdType& ExchangeId, const TradeIdType& TradeId, const DirectionType& Direction);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(Trade* const record);
		void Erase(Trade* const record);
		bool CheckInsert(Trade* const record);
		bool CheckUpdate(const Trade* const oldRecord, const Trade* const newRecord);

	private:
		friend class TradeTable;
		
		TradeTable* table_;
		std::unordered_set<Trade*, TradeHashForTradePrimaryKey, TradeEqualForTradePrimaryKey> index_;
	};
	class AccountLoginSessionTable;
	class AccountLoginSessionPrimaryKey
	{
	public:
		using iterator = std::unordered_set<AccountLoginSession*, AccountLoginSessionHashForAccountLoginSessionPrimaryKey, AccountLoginSessionEqualForAccountLoginSessionPrimaryKey>::iterator;
		AccountLoginSessionPrimaryKey(AccountLoginSessionTable* tableOwner, size_t buckets = 1000);
		AccountLoginSession* Select(const AccountIdType& AccountId, const SessionIdType& SessionId);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(AccountLoginSession* const record);
		void Erase(AccountLoginSession* const record);
		bool CheckInsert(AccountLoginSession* const record);
		bool CheckUpdate(const AccountLoginSession* const oldRecord, const AccountLoginSession* const newRecord);

	private:
		friend class AccountLoginSessionTable;
		
		AccountLoginSessionTable* table_;
		std::unordered_set<AccountLoginSession*, AccountLoginSessionHashForAccountLoginSessionPrimaryKey, AccountLoginSessionEqualForAccountLoginSessionPrimaryKey> index_;
	};
	class PrimaryAccountLoginSessionTable;
	class PrimaryAccountLoginSessionPrimaryKey
	{
	public:
		using iterator = std::unordered_set<PrimaryAccountLoginSession*, PrimaryAccountLoginSessionHashForPrimaryAccountLoginSessionPrimaryKey, PrimaryAccountLoginSessionEqualForPrimaryAccountLoginSessionPrimaryKey>::iterator;
		PrimaryAccountLoginSessionPrimaryKey(PrimaryAccountLoginSessionTable* tableOwner, size_t buckets = 1000);
		PrimaryAccountLoginSession* Select(const AccountIdType& PrimaryAccountId, const SessionIdType& SessionId);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(PrimaryAccountLoginSession* const record);
		void Erase(PrimaryAccountLoginSession* const record);
		bool CheckInsert(PrimaryAccountLoginSession* const record);
		bool CheckUpdate(const PrimaryAccountLoginSession* const oldRecord, const PrimaryAccountLoginSession* const newRecord);

	private:
		friend class PrimaryAccountLoginSessionTable;
		
		PrimaryAccountLoginSessionTable* table_;
		std::unordered_set<PrimaryAccountLoginSession*, PrimaryAccountLoginSessionHashForPrimaryAccountLoginSessionPrimaryKey, PrimaryAccountLoginSessionEqualForPrimaryAccountLoginSessionPrimaryKey> index_;
	};
	class CommissionGroupTable;
	class CommissionGroupPrimaryKey
	{
	public:
		using iterator = std::unordered_set<CommissionGroup*, CommissionGroupHashForCommissionGroupPrimaryKey, CommissionGroupEqualForCommissionGroupPrimaryKey>::iterator;
		CommissionGroupPrimaryKey(CommissionGroupTable* tableOwner, size_t buckets = 1000);
		CommissionGroup* Select(const GroupIdType& CommissionGroupId);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(CommissionGroup* const record);
		void Erase(CommissionGroup* const record);
		bool CheckInsert(CommissionGroup* const record);
		bool CheckUpdate(const CommissionGroup* const oldRecord, const CommissionGroup* const newRecord);

	private:
		friend class CommissionGroupTable;
		
		CommissionGroupTable* table_;
		std::unordered_set<CommissionGroup*, CommissionGroupHashForCommissionGroupPrimaryKey, CommissionGroupEqualForCommissionGroupPrimaryKey> index_;
	};
	class BaseCommissionTable;
	class BaseCommissionPrimaryKey
	{
	public:
		using iterator = std::unordered_set<BaseCommission*, BaseCommissionHashForBaseCommissionPrimaryKey, BaseCommissionEqualForBaseCommissionPrimaryKey>::iterator;
		BaseCommissionPrimaryKey(BaseCommissionTable* tableOwner, size_t buckets = 1000);
		BaseCommission* Select(const GroupIdType& CommissionGroupId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const DirectionType& Direction);
		std::pair<iterator, iterator> SelectAll();
		
	protected:
		bool Insert(BaseCommission* const record);
		void Erase(BaseCommission* const record);
		bool CheckInsert(BaseCommission* const record);
		bool CheckUpdate(const BaseCommission* const oldRecord, const BaseCommission* const newRecord);

	private:
		friend class BaseCommissionTable;
		
		BaseCommissionTable* table_;
		std::unordered_set<BaseCommission*, BaseCommissionHashForBaseCommissionPrimaryKey, BaseCommissionEqualForBaseCommissionPrimaryKey> index_;
	};
}
