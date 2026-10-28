// 本文件由 ../Templates/Cpp/Mdb/LockBased/MdbPrimaryKeys.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdbPrimaryKeys.h"
#include "MdbTables.h"
#include <Spark/Core/Utility/Utility.h>
#include <string.h>
#include <utility>

using std::unordered_set;
using namespace Spark::Core;


namespace QuantTrading
{
	TradingDayTablePrimaryKey::TradingDayTablePrimaryKey(TradingDayTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	std::optional<TradingDay> TradingDayTablePrimaryKey::Select(const Int32Type& Pk)
	{
		CompareTradingDay.Pk = Pk;

		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareTradingDay);
		if (it == index_.end())
		{
			return std::nullopt;
		}
		return **it;
	}
	TableRangeLease<TradingDayTablePrimaryKey::iterator> TradingDayTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return TableRangeLease<iterator>(std::move(guard), index_.begin(), index_.end());
	}
	bool TradingDayTablePrimaryKey::Insert(TradingDay* const record)
	{
		return index_.insert(record).second;
	}
	void TradingDayTablePrimaryKey::Erase(TradingDay* const  record)
	{
		index_.erase(record);
	}
	bool TradingDayTablePrimaryKey::CheckInsert(TradingDay* const record)
	{
		return index_.find(record) == index_.end();
	}
	TradingDay* TradingDayTablePrimaryKey::Find(const TradingDay* record)
	{
		auto it = index_.find(const_cast<TradingDay*>(record));
		return it == index_.end() ? nullptr : *it;
	}
	ExchangeTablePrimaryKey::ExchangeTablePrimaryKey(ExchangeTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	std::optional<Exchange> ExchangeTablePrimaryKey::Select(const ExchangeIdType& ExchangeId)
	{
		Utility::Strcpy(CompareExchange.ExchangeId, ExchangeId);

		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareExchange);
		if (it == index_.end())
		{
			return std::nullopt;
		}
		return **it;
	}
	TableRangeLease<ExchangeTablePrimaryKey::iterator> ExchangeTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return TableRangeLease<iterator>(std::move(guard), index_.begin(), index_.end());
	}
	bool ExchangeTablePrimaryKey::Insert(Exchange* const record)
	{
		return index_.insert(record).second;
	}
	void ExchangeTablePrimaryKey::Erase(Exchange* const  record)
	{
		index_.erase(record);
	}
	bool ExchangeTablePrimaryKey::CheckInsert(Exchange* const record)
	{
		return index_.find(record) == index_.end();
	}
	Exchange* ExchangeTablePrimaryKey::Find(const Exchange* record)
	{
		auto it = index_.find(const_cast<Exchange*>(record));
		return it == index_.end() ? nullptr : *it;
	}
	ProductTablePrimaryKey::ProductTablePrimaryKey(ProductTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	std::optional<Product> ProductTablePrimaryKey::Select(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId)
	{
		Utility::Strcpy(CompareProduct.ExchangeId, ExchangeId);
		Utility::Strcpy(CompareProduct.ProductId, ProductId);

		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareProduct);
		if (it == index_.end())
		{
			return std::nullopt;
		}
		return **it;
	}
	TableRangeLease<ProductTablePrimaryKey::iterator> ProductTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return TableRangeLease<iterator>(std::move(guard), index_.begin(), index_.end());
	}
	bool ProductTablePrimaryKey::Insert(Product* const record)
	{
		return index_.insert(record).second;
	}
	void ProductTablePrimaryKey::Erase(Product* const  record)
	{
		index_.erase(record);
	}
	bool ProductTablePrimaryKey::CheckInsert(Product* const record)
	{
		return index_.find(record) == index_.end();
	}
	Product* ProductTablePrimaryKey::Find(const Product* record)
	{
		auto it = index_.find(const_cast<Product*>(record));
		return it == index_.end() ? nullptr : *it;
	}
	HotInstrumentTablePrimaryKey::HotInstrumentTablePrimaryKey(HotInstrumentTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	std::optional<HotInstrument> HotInstrumentTablePrimaryKey::Select(const DateType& TradingDay, const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank)
	{
		Utility::Strcpy(CompareHotInstrument.TradingDay, TradingDay);
		Utility::Strcpy(CompareHotInstrument.ExchangeId, ExchangeId);
		Utility::Strcpy(CompareHotInstrument.ProductId, ProductId);
		CompareHotInstrument.Rank = Rank;

		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareHotInstrument);
		if (it == index_.end())
		{
			return std::nullopt;
		}
		return **it;
	}
	TableRangeLease<HotInstrumentTablePrimaryKey::iterator> HotInstrumentTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return TableRangeLease<iterator>(std::move(guard), index_.begin(), index_.end());
	}
	bool HotInstrumentTablePrimaryKey::Insert(HotInstrument* const record)
	{
		return index_.insert(record).second;
	}
	void HotInstrumentTablePrimaryKey::Erase(HotInstrument* const  record)
	{
		index_.erase(record);
	}
	bool HotInstrumentTablePrimaryKey::CheckInsert(HotInstrument* const record)
	{
		return index_.find(record) == index_.end();
	}
	HotInstrument* HotInstrumentTablePrimaryKey::Find(const HotInstrument* record)
	{
		auto it = index_.find(const_cast<HotInstrument*>(record));
		return it == index_.end() ? nullptr : *it;
	}
	InstrumentTablePrimaryKey::InstrumentTablePrimaryKey(InstrumentTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	std::optional<Instrument> InstrumentTablePrimaryKey::Select(const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId)
	{
		Utility::Strcpy(CompareInstrument.ExchangeId, ExchangeId);
		Utility::Strcpy(CompareInstrument.InstrumentId, InstrumentId);

		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareInstrument);
		if (it == index_.end())
		{
			return std::nullopt;
		}
		return **it;
	}
	TableRangeLease<InstrumentTablePrimaryKey::iterator> InstrumentTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return TableRangeLease<iterator>(std::move(guard), index_.begin(), index_.end());
	}
	bool InstrumentTablePrimaryKey::Insert(Instrument* const record)
	{
		return index_.insert(record).second;
	}
	void InstrumentTablePrimaryKey::Erase(Instrument* const  record)
	{
		index_.erase(record);
	}
	bool InstrumentTablePrimaryKey::CheckInsert(Instrument* const record)
	{
		return index_.find(record) == index_.end();
	}
	Instrument* InstrumentTablePrimaryKey::Find(const Instrument* record)
	{
		auto it = index_.find(const_cast<Instrument*>(record));
		return it == index_.end() ? nullptr : *it;
	}
	DepthMarketDataTablePrimaryKey::DepthMarketDataTablePrimaryKey(DepthMarketDataTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	std::optional<DepthMarketData> DepthMarketDataTablePrimaryKey::Select(const DateType& TradingDay, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId)
	{
		Utility::Strcpy(CompareDepthMarketData.TradingDay, TradingDay);
		Utility::Strcpy(CompareDepthMarketData.ExchangeId, ExchangeId);
		Utility::Strcpy(CompareDepthMarketData.InstrumentId, InstrumentId);

		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareDepthMarketData);
		if (it == index_.end())
		{
			return std::nullopt;
		}
		return **it;
	}
	TableRangeLease<DepthMarketDataTablePrimaryKey::iterator> DepthMarketDataTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return TableRangeLease<iterator>(std::move(guard), index_.begin(), index_.end());
	}
	bool DepthMarketDataTablePrimaryKey::Insert(DepthMarketData* const record)
	{
		return index_.insert(record).second;
	}
	void DepthMarketDataTablePrimaryKey::Erase(DepthMarketData* const  record)
	{
		index_.erase(record);
	}
	bool DepthMarketDataTablePrimaryKey::CheckInsert(DepthMarketData* const record)
	{
		return index_.find(record) == index_.end();
	}
	DepthMarketData* DepthMarketDataTablePrimaryKey::Find(const DepthMarketData* record)
	{
		auto it = index_.find(const_cast<DepthMarketData*>(record));
		return it == index_.end() ? nullptr : *it;
	}
	BarMarketDataTablePrimaryKey::BarMarketDataTablePrimaryKey(BarMarketDataTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	std::optional<BarMarketData> BarMarketDataTablePrimaryKey::Select(const DateType& TradingDay, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const BarPrecesType& BarPreces, const Int32Type& BarPeriod, const Int64Type& BarTime)
	{
		Utility::Strcpy(CompareBarMarketData.TradingDay, TradingDay);
		Utility::Strcpy(CompareBarMarketData.ExchangeId, ExchangeId);
		Utility::Strcpy(CompareBarMarketData.InstrumentId, InstrumentId);
		CompareBarMarketData.BarPreces = BarPreces;
		CompareBarMarketData.BarPeriod = BarPeriod;
		CompareBarMarketData.BarTime = BarTime;

		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareBarMarketData);
		if (it == index_.end())
		{
			return std::nullopt;
		}
		return **it;
	}
	TableRangeLease<BarMarketDataTablePrimaryKey::iterator> BarMarketDataTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return TableRangeLease<iterator>(std::move(guard), index_.begin(), index_.end());
	}
	bool BarMarketDataTablePrimaryKey::Insert(BarMarketData* const record)
	{
		return index_.insert(record).second;
	}
	void BarMarketDataTablePrimaryKey::Erase(BarMarketData* const  record)
	{
		index_.erase(record);
	}
	bool BarMarketDataTablePrimaryKey::CheckInsert(BarMarketData* const record)
	{
		return index_.find(record) == index_.end();
	}
	BarMarketData* BarMarketDataTablePrimaryKey::Find(const BarMarketData* record)
	{
		auto it = index_.find(const_cast<BarMarketData*>(record));
		return it == index_.end() ? nullptr : *it;
	}
	MdSubscribeTablePrimaryKey::MdSubscribeTablePrimaryKey(MdSubscribeTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	std::optional<MdSubscribe> MdSubscribeTablePrimaryKey::Select(const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const DateType& StartTradingDay)
	{
		Utility::Strcpy(CompareMdSubscribe.ExchangeId, ExchangeId);
		Utility::Strcpy(CompareMdSubscribe.InstrumentId, InstrumentId);
		Utility::Strcpy(CompareMdSubscribe.StartTradingDay, StartTradingDay);

		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareMdSubscribe);
		if (it == index_.end())
		{
			return std::nullopt;
		}
		return **it;
	}
	TableRangeLease<MdSubscribeTablePrimaryKey::iterator> MdSubscribeTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return TableRangeLease<iterator>(std::move(guard), index_.begin(), index_.end());
	}
	bool MdSubscribeTablePrimaryKey::Insert(MdSubscribe* const record)
	{
		return index_.insert(record).second;
	}
	void MdSubscribeTablePrimaryKey::Erase(MdSubscribe* const  record)
	{
		index_.erase(record);
	}
	bool MdSubscribeTablePrimaryKey::CheckInsert(MdSubscribe* const record)
	{
		return index_.find(record) == index_.end();
	}
	MdSubscribe* MdSubscribeTablePrimaryKey::Find(const MdSubscribe* record)
	{
		auto it = index_.find(const_cast<MdSubscribe*>(record));
		return it == index_.end() ? nullptr : *it;
	}
	MdUserTablePrimaryKey::MdUserTablePrimaryKey(MdUserTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	std::optional<MdUser> MdUserTablePrimaryKey::Select(const UserIdType& MdUserId)
	{
		Utility::Strcpy(CompareMdUser.MdUserId, MdUserId);

		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareMdUser);
		if (it == index_.end())
		{
			return std::nullopt;
		}
		return **it;
	}
	TableRangeLease<MdUserTablePrimaryKey::iterator> MdUserTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return TableRangeLease<iterator>(std::move(guard), index_.begin(), index_.end());
	}
	bool MdUserTablePrimaryKey::Insert(MdUser* const record)
	{
		return index_.insert(record).second;
	}
	void MdUserTablePrimaryKey::Erase(MdUser* const  record)
	{
		index_.erase(record);
	}
	bool MdUserTablePrimaryKey::CheckInsert(MdUser* const record)
	{
		return index_.find(record) == index_.end();
	}
	MdUser* MdUserTablePrimaryKey::Find(const MdUser* record)
	{
		auto it = index_.find(const_cast<MdUser*>(record));
		return it == index_.end() ? nullptr : *it;
	}
	MdUserLoginSessionTablePrimaryKey::MdUserLoginSessionTablePrimaryKey(MdUserLoginSessionTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	std::optional<MdUserLoginSession> MdUserLoginSessionTablePrimaryKey::Select(const UserIdType& MdUserId, const SessionIdType& SessionId)
	{
		Utility::Strcpy(CompareMdUserLoginSession.MdUserId, MdUserId);
		CompareMdUserLoginSession.SessionId = SessionId;

		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareMdUserLoginSession);
		if (it == index_.end())
		{
			return std::nullopt;
		}
		return **it;
	}
	TableRangeLease<MdUserLoginSessionTablePrimaryKey::iterator> MdUserLoginSessionTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return TableRangeLease<iterator>(std::move(guard), index_.begin(), index_.end());
	}
	bool MdUserLoginSessionTablePrimaryKey::Insert(MdUserLoginSession* const record)
	{
		return index_.insert(record).second;
	}
	void MdUserLoginSessionTablePrimaryKey::Erase(MdUserLoginSession* const  record)
	{
		index_.erase(record);
	}
	bool MdUserLoginSessionTablePrimaryKey::CheckInsert(MdUserLoginSession* const record)
	{
		return index_.find(record) == index_.end();
	}
	MdUserLoginSession* MdUserLoginSessionTablePrimaryKey::Find(const MdUserLoginSession* record)
	{
		auto it = index_.find(const_cast<MdUserLoginSession*>(record));
		return it == index_.end() ? nullptr : *it;
	}
	PrimaryAccountTablePrimaryKey::PrimaryAccountTablePrimaryKey(PrimaryAccountTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	std::optional<PrimaryAccount> PrimaryAccountTablePrimaryKey::Select(const AccountIdType& PrimaryAccountId)
	{
		Utility::Strcpy(ComparePrimaryAccount.PrimaryAccountId, PrimaryAccountId);

		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&ComparePrimaryAccount);
		if (it == index_.end())
		{
			return std::nullopt;
		}
		return **it;
	}
	TableRangeLease<PrimaryAccountTablePrimaryKey::iterator> PrimaryAccountTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return TableRangeLease<iterator>(std::move(guard), index_.begin(), index_.end());
	}
	bool PrimaryAccountTablePrimaryKey::Insert(PrimaryAccount* const record)
	{
		return index_.insert(record).second;
	}
	void PrimaryAccountTablePrimaryKey::Erase(PrimaryAccount* const  record)
	{
		index_.erase(record);
	}
	bool PrimaryAccountTablePrimaryKey::CheckInsert(PrimaryAccount* const record)
	{
		return index_.find(record) == index_.end();
	}
	PrimaryAccount* PrimaryAccountTablePrimaryKey::Find(const PrimaryAccount* record)
	{
		auto it = index_.find(const_cast<PrimaryAccount*>(record));
		return it == index_.end() ? nullptr : *it;
	}
	AccountTablePrimaryKey::AccountTablePrimaryKey(AccountTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	std::optional<Account> AccountTablePrimaryKey::Select(const AccountIdType& AccountId)
	{
		Utility::Strcpy(CompareAccount.AccountId, AccountId);

		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareAccount);
		if (it == index_.end())
		{
			return std::nullopt;
		}
		return **it;
	}
	TableRangeLease<AccountTablePrimaryKey::iterator> AccountTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return TableRangeLease<iterator>(std::move(guard), index_.begin(), index_.end());
	}
	bool AccountTablePrimaryKey::Insert(Account* const record)
	{
		return index_.insert(record).second;
	}
	void AccountTablePrimaryKey::Erase(Account* const  record)
	{
		index_.erase(record);
	}
	bool AccountTablePrimaryKey::CheckInsert(Account* const record)
	{
		return index_.find(record) == index_.end();
	}
	Account* AccountTablePrimaryKey::Find(const Account* record)
	{
		auto it = index_.find(const_cast<Account*>(record));
		return it == index_.end() ? nullptr : *it;
	}
	CapitalTablePrimaryKey::CapitalTablePrimaryKey(CapitalTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	std::optional<Capital> CapitalTablePrimaryKey::Select(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		Utility::Strcpy(CompareCapital.TradingDay, TradingDay);
		Utility::Strcpy(CompareCapital.AccountId, AccountId);

		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareCapital);
		if (it == index_.end())
		{
			return std::nullopt;
		}
		return **it;
	}
	TableRangeLease<CapitalTablePrimaryKey::iterator> CapitalTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return TableRangeLease<iterator>(std::move(guard), index_.begin(), index_.end());
	}
	bool CapitalTablePrimaryKey::Insert(Capital* const record)
	{
		return index_.insert(record).second;
	}
	void CapitalTablePrimaryKey::Erase(Capital* const  record)
	{
		index_.erase(record);
	}
	bool CapitalTablePrimaryKey::CheckInsert(Capital* const record)
	{
		return index_.find(record) == index_.end();
	}
	Capital* CapitalTablePrimaryKey::Find(const Capital* record)
	{
		auto it = index_.find(const_cast<Capital*>(record));
		return it == index_.end() ? nullptr : *it;
	}
	PositionTablePrimaryKey::PositionTablePrimaryKey(PositionTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	std::optional<Position> PositionTablePrimaryKey::Select(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection)
	{
		Utility::Strcpy(ComparePosition.TradingDay, TradingDay);
		Utility::Strcpy(ComparePosition.AccountId, AccountId);
		Utility::Strcpy(ComparePosition.ExchangeId, ExchangeId);
		Utility::Strcpy(ComparePosition.InstrumentId, InstrumentId);
		ComparePosition.PosiDirection = PosiDirection;

		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&ComparePosition);
		if (it == index_.end())
		{
			return std::nullopt;
		}
		return **it;
	}
	TableRangeLease<PositionTablePrimaryKey::iterator> PositionTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return TableRangeLease<iterator>(std::move(guard), index_.begin(), index_.end());
	}
	bool PositionTablePrimaryKey::Insert(Position* const record)
	{
		return index_.insert(record).second;
	}
	void PositionTablePrimaryKey::Erase(Position* const  record)
	{
		index_.erase(record);
	}
	bool PositionTablePrimaryKey::CheckInsert(Position* const record)
	{
		return index_.find(record) == index_.end();
	}
	Position* PositionTablePrimaryKey::Find(const Position* record)
	{
		auto it = index_.find(const_cast<Position*>(record));
		return it == index_.end() ? nullptr : *it;
	}
	PositionDetailTablePrimaryKey::PositionDetailTablePrimaryKey(PositionDetailTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	std::optional<PositionDetail> PositionDetailTablePrimaryKey::Select(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection, const DateType& OpenDate, const TradeIdType& TradeId)
	{
		Utility::Strcpy(ComparePositionDetail.TradingDay, TradingDay);
		Utility::Strcpy(ComparePositionDetail.AccountId, AccountId);
		Utility::Strcpy(ComparePositionDetail.ExchangeId, ExchangeId);
		Utility::Strcpy(ComparePositionDetail.InstrumentId, InstrumentId);
		ComparePositionDetail.PosiDirection = PosiDirection;
		Utility::Strcpy(ComparePositionDetail.OpenDate, OpenDate);
		Utility::Strcpy(ComparePositionDetail.TradeId, TradeId);

		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&ComparePositionDetail);
		if (it == index_.end())
		{
			return std::nullopt;
		}
		return **it;
	}
	TableRangeLease<PositionDetailTablePrimaryKey::iterator> PositionDetailTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return TableRangeLease<iterator>(std::move(guard), index_.begin(), index_.end());
	}
	bool PositionDetailTablePrimaryKey::Insert(PositionDetail* const record)
	{
		return index_.insert(record).second;
	}
	void PositionDetailTablePrimaryKey::Erase(PositionDetail* const  record)
	{
		index_.erase(record);
	}
	bool PositionDetailTablePrimaryKey::CheckInsert(PositionDetail* const record)
	{
		return index_.find(record) == index_.end();
	}
	PositionDetail* PositionDetailTablePrimaryKey::Find(const PositionDetail* record)
	{
		auto it = index_.find(const_cast<PositionDetail*>(record));
		return it == index_.end() ? nullptr : *it;
	}
	OrderTablePrimaryKey::OrderTablePrimaryKey(OrderTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	std::optional<Order> OrderTablePrimaryKey::Select(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const OrderIdType& OrderId)
	{
		Utility::Strcpy(CompareOrder.TradingDay, TradingDay);
		Utility::Strcpy(CompareOrder.AccountId, AccountId);
		Utility::Strcpy(CompareOrder.ExchangeId, ExchangeId);
		Utility::Strcpy(CompareOrder.InstrumentId, InstrumentId);
		CompareOrder.OrderId = OrderId;

		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareOrder);
		if (it == index_.end())
		{
			return std::nullopt;
		}
		return **it;
	}
	TableRangeLease<OrderTablePrimaryKey::iterator> OrderTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return TableRangeLease<iterator>(std::move(guard), index_.begin(), index_.end());
	}
	bool OrderTablePrimaryKey::Insert(Order* const record)
	{
		return index_.insert(record).second;
	}
	void OrderTablePrimaryKey::Erase(Order* const  record)
	{
		index_.erase(record);
	}
	bool OrderTablePrimaryKey::CheckInsert(Order* const record)
	{
		return index_.find(record) == index_.end();
	}
	Order* OrderTablePrimaryKey::Find(const Order* record)
	{
		auto it = index_.find(const_cast<Order*>(record));
		return it == index_.end() ? nullptr : *it;
	}
	OrderTableUniqueKeyClientOrderId::OrderTableUniqueKeyClientOrderId(OrderTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	std::optional<Order> OrderTableUniqueKeyClientOrderId::Select(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const SessionIdType& SessionId, const ClientOrderIdType& ClientOrderId)
	{
		Utility::Strcpy(CompareOrder.TradingDay, TradingDay);
		Utility::Strcpy(CompareOrder.AccountId, AccountId);
		Utility::Strcpy(CompareOrder.ExchangeId, ExchangeId);
		Utility::Strcpy(CompareOrder.InstrumentId, InstrumentId);
		CompareOrder.SessionId = SessionId;
		CompareOrder.ClientOrderId = ClientOrderId;
		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareOrder);
		if (it == index_.end())
		{
			return std::nullopt;
		}
		return **it;
	}
	bool OrderTableUniqueKeyClientOrderId::Insert(Order* const record)
	{
		return index_.insert(record).second;
	}
	void OrderTableUniqueKeyClientOrderId::Erase(Order* const  record)
	{
		index_.erase(record);
	}
	bool OrderTableUniqueKeyClientOrderId::CheckInsert(Order* const record)
	{
		return index_.find(record) == index_.end();
	}
	bool OrderTableUniqueKeyClientOrderId::CheckUpdate(const Order* const oldRecord, const Order* const newRecord)
	{
		return OrderEqualForClientOrderIdUniqueKey()(oldRecord, newRecord);
	}
	
	TradeTablePrimaryKey::TradeTablePrimaryKey(TradeTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	std::optional<Trade> TradeTablePrimaryKey::Select(const DateType& TradingDay, const ExchangeIdType& ExchangeId, const TradeIdType& TradeId, const DirectionType& Direction)
	{
		Utility::Strcpy(CompareTrade.TradingDay, TradingDay);
		Utility::Strcpy(CompareTrade.ExchangeId, ExchangeId);
		Utility::Strcpy(CompareTrade.TradeId, TradeId);
		CompareTrade.Direction = Direction;

		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareTrade);
		if (it == index_.end())
		{
			return std::nullopt;
		}
		return **it;
	}
	TableRangeLease<TradeTablePrimaryKey::iterator> TradeTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return TableRangeLease<iterator>(std::move(guard), index_.begin(), index_.end());
	}
	bool TradeTablePrimaryKey::Insert(Trade* const record)
	{
		return index_.insert(record).second;
	}
	void TradeTablePrimaryKey::Erase(Trade* const  record)
	{
		index_.erase(record);
	}
	bool TradeTablePrimaryKey::CheckInsert(Trade* const record)
	{
		return index_.find(record) == index_.end();
	}
	Trade* TradeTablePrimaryKey::Find(const Trade* record)
	{
		auto it = index_.find(const_cast<Trade*>(record));
		return it == index_.end() ? nullptr : *it;
	}
	AccountLoginSessionTablePrimaryKey::AccountLoginSessionTablePrimaryKey(AccountLoginSessionTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	std::optional<AccountLoginSession> AccountLoginSessionTablePrimaryKey::Select(const AccountIdType& AccountId, const SessionIdType& SessionId)
	{
		Utility::Strcpy(CompareAccountLoginSession.AccountId, AccountId);
		CompareAccountLoginSession.SessionId = SessionId;

		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareAccountLoginSession);
		if (it == index_.end())
		{
			return std::nullopt;
		}
		return **it;
	}
	TableRangeLease<AccountLoginSessionTablePrimaryKey::iterator> AccountLoginSessionTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return TableRangeLease<iterator>(std::move(guard), index_.begin(), index_.end());
	}
	bool AccountLoginSessionTablePrimaryKey::Insert(AccountLoginSession* const record)
	{
		return index_.insert(record).second;
	}
	void AccountLoginSessionTablePrimaryKey::Erase(AccountLoginSession* const  record)
	{
		index_.erase(record);
	}
	bool AccountLoginSessionTablePrimaryKey::CheckInsert(AccountLoginSession* const record)
	{
		return index_.find(record) == index_.end();
	}
	AccountLoginSession* AccountLoginSessionTablePrimaryKey::Find(const AccountLoginSession* record)
	{
		auto it = index_.find(const_cast<AccountLoginSession*>(record));
		return it == index_.end() ? nullptr : *it;
	}
	PrimaryAccountLoginSessionTablePrimaryKey::PrimaryAccountLoginSessionTablePrimaryKey(PrimaryAccountLoginSessionTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	std::optional<PrimaryAccountLoginSession> PrimaryAccountLoginSessionTablePrimaryKey::Select(const AccountIdType& PrimaryAccountId, const SessionIdType& SessionId)
	{
		Utility::Strcpy(ComparePrimaryAccountLoginSession.PrimaryAccountId, PrimaryAccountId);
		ComparePrimaryAccountLoginSession.SessionId = SessionId;

		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&ComparePrimaryAccountLoginSession);
		if (it == index_.end())
		{
			return std::nullopt;
		}
		return **it;
	}
	TableRangeLease<PrimaryAccountLoginSessionTablePrimaryKey::iterator> PrimaryAccountLoginSessionTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return TableRangeLease<iterator>(std::move(guard), index_.begin(), index_.end());
	}
	bool PrimaryAccountLoginSessionTablePrimaryKey::Insert(PrimaryAccountLoginSession* const record)
	{
		return index_.insert(record).second;
	}
	void PrimaryAccountLoginSessionTablePrimaryKey::Erase(PrimaryAccountLoginSession* const  record)
	{
		index_.erase(record);
	}
	bool PrimaryAccountLoginSessionTablePrimaryKey::CheckInsert(PrimaryAccountLoginSession* const record)
	{
		return index_.find(record) == index_.end();
	}
	PrimaryAccountLoginSession* PrimaryAccountLoginSessionTablePrimaryKey::Find(const PrimaryAccountLoginSession* record)
	{
		auto it = index_.find(const_cast<PrimaryAccountLoginSession*>(record));
		return it == index_.end() ? nullptr : *it;
	}
	CommissionGroupTablePrimaryKey::CommissionGroupTablePrimaryKey(CommissionGroupTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	std::optional<CommissionGroup> CommissionGroupTablePrimaryKey::Select(const GroupIdType& CommissionGroupId)
	{
		CompareCommissionGroup.CommissionGroupId = CommissionGroupId;

		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareCommissionGroup);
		if (it == index_.end())
		{
			return std::nullopt;
		}
		return **it;
	}
	TableRangeLease<CommissionGroupTablePrimaryKey::iterator> CommissionGroupTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return TableRangeLease<iterator>(std::move(guard), index_.begin(), index_.end());
	}
	bool CommissionGroupTablePrimaryKey::Insert(CommissionGroup* const record)
	{
		return index_.insert(record).second;
	}
	void CommissionGroupTablePrimaryKey::Erase(CommissionGroup* const  record)
	{
		index_.erase(record);
	}
	bool CommissionGroupTablePrimaryKey::CheckInsert(CommissionGroup* const record)
	{
		return index_.find(record) == index_.end();
	}
	CommissionGroup* CommissionGroupTablePrimaryKey::Find(const CommissionGroup* record)
	{
		auto it = index_.find(const_cast<CommissionGroup*>(record));
		return it == index_.end() ? nullptr : *it;
	}
	BaseCommissionTablePrimaryKey::BaseCommissionTablePrimaryKey(BaseCommissionTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	std::optional<BaseCommission> BaseCommissionTablePrimaryKey::Select(const GroupIdType& CommissionGroupId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const DirectionType& Direction)
	{
		CompareBaseCommission.CommissionGroupId = CommissionGroupId;
		Utility::Strcpy(CompareBaseCommission.ExchangeId, ExchangeId);
		Utility::Strcpy(CompareBaseCommission.InstrumentId, InstrumentId);
		CompareBaseCommission.Direction = Direction;

		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareBaseCommission);
		if (it == index_.end())
		{
			return std::nullopt;
		}
		return **it;
	}
	TableRangeLease<BaseCommissionTablePrimaryKey::iterator> BaseCommissionTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return TableRangeLease<iterator>(std::move(guard), index_.begin(), index_.end());
	}
	bool BaseCommissionTablePrimaryKey::Insert(BaseCommission* const record)
	{
		return index_.insert(record).second;
	}
	void BaseCommissionTablePrimaryKey::Erase(BaseCommission* const  record)
	{
		index_.erase(record);
	}
	bool BaseCommissionTablePrimaryKey::CheckInsert(BaseCommission* const record)
	{
		return index_.find(record) == index_.end();
	}
	BaseCommission* BaseCommissionTablePrimaryKey::Find(const BaseCommission* record)
	{
		auto it = index_.find(const_cast<BaseCommission*>(record));
		return it == index_.end() ? nullptr : *it;
	}
}
