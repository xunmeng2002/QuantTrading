// 本文件由 ../Templates/Cpp/Mdb/MdbPrimaryKeys.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdbPrimaryKeys.h"
#include "MdbTables.h"
#include <Spark/Core/Utility/Utility.h>
#include <string.h>

using std::unordered_set;
using namespace Spark::Core;


namespace QuantTrading
{
	TradingDayTablePrimaryKey::TradingDayTablePrimaryKey(TradingDayTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	TradingDay* TradingDayTablePrimaryKey::Select(const Int32Type& Pk)
	{
		CompareTradingDay.Pk = Pk;
		
		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareTradingDay);
		if (it == index_.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<TradingDayTablePrimaryKey::iterator, TradingDayTablePrimaryKey::iterator> TradingDayTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return std::pair<iterator, iterator>(index_.begin(), index_.end());
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
	bool TradingDayTablePrimaryKey::CheckUpdate(const TradingDay* const oldRecord, const TradingDay* const newRecord)
	{
		return TradingDayEqualForTradingDayPrimaryKey()(oldRecord, newRecord);
	}
	ExchangeTablePrimaryKey::ExchangeTablePrimaryKey(ExchangeTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	Exchange* ExchangeTablePrimaryKey::Select(const ExchangeIdType& ExchangeId)
	{
		Utility::Strcpy(CompareExchange.ExchangeId, ExchangeId);
		
		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareExchange);
		if (it == index_.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<ExchangeTablePrimaryKey::iterator, ExchangeTablePrimaryKey::iterator> ExchangeTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return std::pair<iterator, iterator>(index_.begin(), index_.end());
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
	bool ExchangeTablePrimaryKey::CheckUpdate(const Exchange* const oldRecord, const Exchange* const newRecord)
	{
		return ExchangeEqualForExchangePrimaryKey()(oldRecord, newRecord);
	}
	ProductTablePrimaryKey::ProductTablePrimaryKey(ProductTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	Product* ProductTablePrimaryKey::Select(const ExchangeIdType& ExchangeId, const ProductIdType& ProductId)
	{
		Utility::Strcpy(CompareProduct.ExchangeId, ExchangeId);
		Utility::Strcpy(CompareProduct.ProductId, ProductId);
		
		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareProduct);
		if (it == index_.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<ProductTablePrimaryKey::iterator, ProductTablePrimaryKey::iterator> ProductTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return std::pair<iterator, iterator>(index_.begin(), index_.end());
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
	bool ProductTablePrimaryKey::CheckUpdate(const Product* const oldRecord, const Product* const newRecord)
	{
		return ProductEqualForProductPrimaryKey()(oldRecord, newRecord);
	}
	HotInstrumentTablePrimaryKey::HotInstrumentTablePrimaryKey(HotInstrumentTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	HotInstrument* HotInstrumentTablePrimaryKey::Select(const DateType& TradingDay, const ExchangeIdType& ExchangeId, const ProductIdType& ProductId, const Int32Type& Rank)
	{
		Utility::Strcpy(CompareHotInstrument.TradingDay, TradingDay);
		Utility::Strcpy(CompareHotInstrument.ExchangeId, ExchangeId);
		Utility::Strcpy(CompareHotInstrument.ProductId, ProductId);
		CompareHotInstrument.Rank = Rank;
		
		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareHotInstrument);
		if (it == index_.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<HotInstrumentTablePrimaryKey::iterator, HotInstrumentTablePrimaryKey::iterator> HotInstrumentTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return std::pair<iterator, iterator>(index_.begin(), index_.end());
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
	bool HotInstrumentTablePrimaryKey::CheckUpdate(const HotInstrument* const oldRecord, const HotInstrument* const newRecord)
	{
		return HotInstrumentEqualForHotInstrumentPrimaryKey()(oldRecord, newRecord);
	}
	InstrumentTablePrimaryKey::InstrumentTablePrimaryKey(InstrumentTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	Instrument* InstrumentTablePrimaryKey::Select(const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId)
	{
		Utility::Strcpy(CompareInstrument.ExchangeId, ExchangeId);
		Utility::Strcpy(CompareInstrument.InstrumentId, InstrumentId);
		
		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareInstrument);
		if (it == index_.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<InstrumentTablePrimaryKey::iterator, InstrumentTablePrimaryKey::iterator> InstrumentTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return std::pair<iterator, iterator>(index_.begin(), index_.end());
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
	bool InstrumentTablePrimaryKey::CheckUpdate(const Instrument* const oldRecord, const Instrument* const newRecord)
	{
		return InstrumentEqualForInstrumentPrimaryKey()(oldRecord, newRecord);
	}
	DepthMarketDataTablePrimaryKey::DepthMarketDataTablePrimaryKey(DepthMarketDataTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	DepthMarketData* DepthMarketDataTablePrimaryKey::Select(const DateType& TradingDay, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId)
	{
		Utility::Strcpy(CompareDepthMarketData.TradingDay, TradingDay);
		Utility::Strcpy(CompareDepthMarketData.ExchangeId, ExchangeId);
		Utility::Strcpy(CompareDepthMarketData.InstrumentId, InstrumentId);
		
		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareDepthMarketData);
		if (it == index_.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<DepthMarketDataTablePrimaryKey::iterator, DepthMarketDataTablePrimaryKey::iterator> DepthMarketDataTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return std::pair<iterator, iterator>(index_.begin(), index_.end());
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
	bool DepthMarketDataTablePrimaryKey::CheckUpdate(const DepthMarketData* const oldRecord, const DepthMarketData* const newRecord)
	{
		return DepthMarketDataEqualForDepthMarketDataPrimaryKey()(oldRecord, newRecord);
	}
	BarMarketDataTablePrimaryKey::BarMarketDataTablePrimaryKey(BarMarketDataTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	BarMarketData* BarMarketDataTablePrimaryKey::Select(const DateType& TradingDay, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const BarPrecesType& BarPreces, const Int32Type& BarPeriod, const Int64Type& BarTime)
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
			return nullptr;
		}
		return *it;
	}
	std::pair<BarMarketDataTablePrimaryKey::iterator, BarMarketDataTablePrimaryKey::iterator> BarMarketDataTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return std::pair<iterator, iterator>(index_.begin(), index_.end());
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
	bool BarMarketDataTablePrimaryKey::CheckUpdate(const BarMarketData* const oldRecord, const BarMarketData* const newRecord)
	{
		return BarMarketDataEqualForBarMarketDataPrimaryKey()(oldRecord, newRecord);
	}
	MdSubscribeTablePrimaryKey::MdSubscribeTablePrimaryKey(MdSubscribeTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	MdSubscribe* MdSubscribeTablePrimaryKey::Select(const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const DateType& StartTradingDay)
	{
		Utility::Strcpy(CompareMdSubscribe.ExchangeId, ExchangeId);
		Utility::Strcpy(CompareMdSubscribe.InstrumentId, InstrumentId);
		Utility::Strcpy(CompareMdSubscribe.StartTradingDay, StartTradingDay);
		
		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareMdSubscribe);
		if (it == index_.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<MdSubscribeTablePrimaryKey::iterator, MdSubscribeTablePrimaryKey::iterator> MdSubscribeTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return std::pair<iterator, iterator>(index_.begin(), index_.end());
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
	bool MdSubscribeTablePrimaryKey::CheckUpdate(const MdSubscribe* const oldRecord, const MdSubscribe* const newRecord)
	{
		return MdSubscribeEqualForMdSubscribePrimaryKey()(oldRecord, newRecord);
	}
	MdUserTablePrimaryKey::MdUserTablePrimaryKey(MdUserTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	MdUser* MdUserTablePrimaryKey::Select(const UserIdType& MdUserId)
	{
		Utility::Strcpy(CompareMdUser.MdUserId, MdUserId);
		
		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareMdUser);
		if (it == index_.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<MdUserTablePrimaryKey::iterator, MdUserTablePrimaryKey::iterator> MdUserTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return std::pair<iterator, iterator>(index_.begin(), index_.end());
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
	bool MdUserTablePrimaryKey::CheckUpdate(const MdUser* const oldRecord, const MdUser* const newRecord)
	{
		return MdUserEqualForMdUserPrimaryKey()(oldRecord, newRecord);
	}
	MdUserLoginSessionTablePrimaryKey::MdUserLoginSessionTablePrimaryKey(MdUserLoginSessionTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	MdUserLoginSession* MdUserLoginSessionTablePrimaryKey::Select(const UserIdType& MdUserId, const SessionIdType& SessionId)
	{
		Utility::Strcpy(CompareMdUserLoginSession.MdUserId, MdUserId);
		CompareMdUserLoginSession.SessionId = SessionId;
		
		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareMdUserLoginSession);
		if (it == index_.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<MdUserLoginSessionTablePrimaryKey::iterator, MdUserLoginSessionTablePrimaryKey::iterator> MdUserLoginSessionTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return std::pair<iterator, iterator>(index_.begin(), index_.end());
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
	bool MdUserLoginSessionTablePrimaryKey::CheckUpdate(const MdUserLoginSession* const oldRecord, const MdUserLoginSession* const newRecord)
	{
		return MdUserLoginSessionEqualForMdUserLoginSessionPrimaryKey()(oldRecord, newRecord);
	}
	PrimaryAccountTablePrimaryKey::PrimaryAccountTablePrimaryKey(PrimaryAccountTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	PrimaryAccount* PrimaryAccountTablePrimaryKey::Select(const AccountIdType& PrimaryAccountId)
	{
		Utility::Strcpy(ComparePrimaryAccount.PrimaryAccountId, PrimaryAccountId);
		
		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&ComparePrimaryAccount);
		if (it == index_.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<PrimaryAccountTablePrimaryKey::iterator, PrimaryAccountTablePrimaryKey::iterator> PrimaryAccountTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return std::pair<iterator, iterator>(index_.begin(), index_.end());
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
	bool PrimaryAccountTablePrimaryKey::CheckUpdate(const PrimaryAccount* const oldRecord, const PrimaryAccount* const newRecord)
	{
		return PrimaryAccountEqualForPrimaryAccountPrimaryKey()(oldRecord, newRecord);
	}
	AccountTablePrimaryKey::AccountTablePrimaryKey(AccountTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	Account* AccountTablePrimaryKey::Select(const AccountIdType& AccountId)
	{
		Utility::Strcpy(CompareAccount.AccountId, AccountId);
		
		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareAccount);
		if (it == index_.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<AccountTablePrimaryKey::iterator, AccountTablePrimaryKey::iterator> AccountTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return std::pair<iterator, iterator>(index_.begin(), index_.end());
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
	bool AccountTablePrimaryKey::CheckUpdate(const Account* const oldRecord, const Account* const newRecord)
	{
		return AccountEqualForAccountPrimaryKey()(oldRecord, newRecord);
	}
	CapitalTablePrimaryKey::CapitalTablePrimaryKey(CapitalTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	Capital* CapitalTablePrimaryKey::Select(const DateType& TradingDay, const AccountIdType& AccountId)
	{
		Utility::Strcpy(CompareCapital.TradingDay, TradingDay);
		Utility::Strcpy(CompareCapital.AccountId, AccountId);
		
		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareCapital);
		if (it == index_.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<CapitalTablePrimaryKey::iterator, CapitalTablePrimaryKey::iterator> CapitalTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return std::pair<iterator, iterator>(index_.begin(), index_.end());
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
	bool CapitalTablePrimaryKey::CheckUpdate(const Capital* const oldRecord, const Capital* const newRecord)
	{
		return CapitalEqualForCapitalPrimaryKey()(oldRecord, newRecord);
	}
	PositionTablePrimaryKey::PositionTablePrimaryKey(PositionTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	Position* PositionTablePrimaryKey::Select(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection)
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
			return nullptr;
		}
		return *it;
	}
	std::pair<PositionTablePrimaryKey::iterator, PositionTablePrimaryKey::iterator> PositionTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return std::pair<iterator, iterator>(index_.begin(), index_.end());
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
	bool PositionTablePrimaryKey::CheckUpdate(const Position* const oldRecord, const Position* const newRecord)
	{
		return PositionEqualForPositionPrimaryKey()(oldRecord, newRecord);
	}
	PositionDetailTablePrimaryKey::PositionDetailTablePrimaryKey(PositionDetailTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	PositionDetail* PositionDetailTablePrimaryKey::Select(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const PosiDirectionType& PosiDirection, const DateType& OpenDate, const TradeIdType& TradeId)
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
			return nullptr;
		}
		return *it;
	}
	std::pair<PositionDetailTablePrimaryKey::iterator, PositionDetailTablePrimaryKey::iterator> PositionDetailTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return std::pair<iterator, iterator>(index_.begin(), index_.end());
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
	bool PositionDetailTablePrimaryKey::CheckUpdate(const PositionDetail* const oldRecord, const PositionDetail* const newRecord)
	{
		return PositionDetailEqualForPositionDetailPrimaryKey()(oldRecord, newRecord);
	}
	OrderTablePrimaryKey::OrderTablePrimaryKey(OrderTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	Order* OrderTablePrimaryKey::Select(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const OrderIdType& OrderId)
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
			return nullptr;
		}
		return *it;
	}
	std::pair<OrderTablePrimaryKey::iterator, OrderTablePrimaryKey::iterator> OrderTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return std::pair<iterator, iterator>(index_.begin(), index_.end());
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
	bool OrderTablePrimaryKey::CheckUpdate(const Order* const oldRecord, const Order* const newRecord)
	{
		return OrderEqualForOrderPrimaryKey()(oldRecord, newRecord);
	}
	OrderTableUniqueKeyClientOrderId::OrderTableUniqueKeyClientOrderId(OrderTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	Order* OrderTableUniqueKeyClientOrderId::Select(const DateType& TradingDay, const AccountIdType& AccountId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const SessionIdType& SessionId, const ClientOrderIdType& ClientOrderId)
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
			return nullptr;
		}
		return *it;
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
	Trade* TradeTablePrimaryKey::Select(const DateType& TradingDay, const ExchangeIdType& ExchangeId, const TradeIdType& TradeId, const DirectionType& Direction)
	{
		Utility::Strcpy(CompareTrade.TradingDay, TradingDay);
		Utility::Strcpy(CompareTrade.ExchangeId, ExchangeId);
		Utility::Strcpy(CompareTrade.TradeId, TradeId);
		CompareTrade.Direction = Direction;
		
		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareTrade);
		if (it == index_.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<TradeTablePrimaryKey::iterator, TradeTablePrimaryKey::iterator> TradeTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return std::pair<iterator, iterator>(index_.begin(), index_.end());
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
	bool TradeTablePrimaryKey::CheckUpdate(const Trade* const oldRecord, const Trade* const newRecord)
	{
		return TradeEqualForTradePrimaryKey()(oldRecord, newRecord);
	}
	AccountLoginSessionTablePrimaryKey::AccountLoginSessionTablePrimaryKey(AccountLoginSessionTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	AccountLoginSession* AccountLoginSessionTablePrimaryKey::Select(const AccountIdType& AccountId, const SessionIdType& SessionId)
	{
		Utility::Strcpy(CompareAccountLoginSession.AccountId, AccountId);
		CompareAccountLoginSession.SessionId = SessionId;
		
		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareAccountLoginSession);
		if (it == index_.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<AccountLoginSessionTablePrimaryKey::iterator, AccountLoginSessionTablePrimaryKey::iterator> AccountLoginSessionTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return std::pair<iterator, iterator>(index_.begin(), index_.end());
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
	bool AccountLoginSessionTablePrimaryKey::CheckUpdate(const AccountLoginSession* const oldRecord, const AccountLoginSession* const newRecord)
	{
		return AccountLoginSessionEqualForAccountLoginSessionPrimaryKey()(oldRecord, newRecord);
	}
	PrimaryAccountLoginSessionTablePrimaryKey::PrimaryAccountLoginSessionTablePrimaryKey(PrimaryAccountLoginSessionTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	PrimaryAccountLoginSession* PrimaryAccountLoginSessionTablePrimaryKey::Select(const AccountIdType& PrimaryAccountId, const SessionIdType& SessionId)
	{
		Utility::Strcpy(ComparePrimaryAccountLoginSession.PrimaryAccountId, PrimaryAccountId);
		ComparePrimaryAccountLoginSession.SessionId = SessionId;
		
		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&ComparePrimaryAccountLoginSession);
		if (it == index_.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<PrimaryAccountLoginSessionTablePrimaryKey::iterator, PrimaryAccountLoginSessionTablePrimaryKey::iterator> PrimaryAccountLoginSessionTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return std::pair<iterator, iterator>(index_.begin(), index_.end());
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
	bool PrimaryAccountLoginSessionTablePrimaryKey::CheckUpdate(const PrimaryAccountLoginSession* const oldRecord, const PrimaryAccountLoginSession* const newRecord)
	{
		return PrimaryAccountLoginSessionEqualForPrimaryAccountLoginSessionPrimaryKey()(oldRecord, newRecord);
	}
	CommissionGroupTablePrimaryKey::CommissionGroupTablePrimaryKey(CommissionGroupTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	CommissionGroup* CommissionGroupTablePrimaryKey::Select(const GroupIdType& CommissionGroupId)
	{
		CompareCommissionGroup.CommissionGroupId = CommissionGroupId;
		
		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareCommissionGroup);
		if (it == index_.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<CommissionGroupTablePrimaryKey::iterator, CommissionGroupTablePrimaryKey::iterator> CommissionGroupTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return std::pair<iterator, iterator>(index_.begin(), index_.end());
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
	bool CommissionGroupTablePrimaryKey::CheckUpdate(const CommissionGroup* const oldRecord, const CommissionGroup* const newRecord)
	{
		return CommissionGroupEqualForCommissionGroupPrimaryKey()(oldRecord, newRecord);
	}
	BaseCommissionTablePrimaryKey::BaseCommissionTablePrimaryKey(BaseCommissionTable* tableOwner, size_t buckets)
		:table_(tableOwner), index_(buckets)
	{
	}
	BaseCommission* BaseCommissionTablePrimaryKey::Select(const GroupIdType& CommissionGroupId, const ExchangeIdType& ExchangeId, const InstrumentIdType& InstrumentId, const DirectionType& Direction)
	{
		CompareBaseCommission.CommissionGroupId = CommissionGroupId;
		Utility::Strcpy(CompareBaseCommission.ExchangeId, ExchangeId);
		Utility::Strcpy(CompareBaseCommission.InstrumentId, InstrumentId);
		CompareBaseCommission.Direction = Direction;
		
		std::shared_lock guard(table_->SharedMutex);
		auto it = index_.find(&CompareBaseCommission);
		if (it == index_.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<BaseCommissionTablePrimaryKey::iterator, BaseCommissionTablePrimaryKey::iterator> BaseCommissionTablePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table_->SharedMutex);
		return std::pair<iterator, iterator>(index_.begin(), index_.end());
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
	bool BaseCommissionTablePrimaryKey::CheckUpdate(const BaseCommission* const oldRecord, const BaseCommission* const newRecord)
	{
		return BaseCommissionEqualForBaseCommissionPrimaryKey()(oldRecord, newRecord);
	}
}
