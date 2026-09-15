// 本文件由 ../Templates/Cpp/Mdb/MdbPrimaryKeys.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdbPrimaryKeys.h"
#include "MdbTables.h"
#include <Spark/Core/Utility/Utility.h>
#include <string.h>

using std::unordered_set;
using namespace spark::core;


namespace mdb
{
	TradingDayPrimaryKey::TradingDayPrimaryKey(TradingDayTable* tableOwner, size_t buckets)
		:table(tableOwner), index(buckets)
	{
	}
	TradingDay* TradingDayPrimaryKey::Select(const Int32Type& PK)
	{
		CompareTradingDay.PK = PK;
		
		std::shared_lock guard(table->sharedMutex);
		auto it = index.find(&CompareTradingDay);
		if (it == index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<TradingDayPrimaryKey::iterator, TradingDayPrimaryKey::iterator> TradingDayPrimaryKey::SelectAll()
	{
		std::shared_lock guard(table->sharedMutex);
		return std::pair<iterator, iterator>(index.begin(), index.end());
	}
	bool TradingDayPrimaryKey::Insert(TradingDay* const record)
	{
		return index.insert(record).second;
	}
	void TradingDayPrimaryKey::Erase(TradingDay* const  record)
	{
		index.erase(record);
	}
	bool TradingDayPrimaryKey::CheckInsert(TradingDay* const record)
	{
		return index.find(record) == index.end();
	}
	bool TradingDayPrimaryKey::CheckUpdate(const TradingDay* const oldRecord, const TradingDay* const newRecord)
	{
		return TradingDayEqualForTradingDayPrimaryKey()(oldRecord, newRecord);
	}
	ExchangePrimaryKey::ExchangePrimaryKey(ExchangeTable* tableOwner, size_t buckets)
		:table(tableOwner), index(buckets)
	{
	}
	Exchange* ExchangePrimaryKey::Select(const ExchangeIDType& ExchangeID)
	{
		Utility::Strcpy(CompareExchange.ExchangeID, ExchangeID);
		
		std::shared_lock guard(table->sharedMutex);
		auto it = index.find(&CompareExchange);
		if (it == index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<ExchangePrimaryKey::iterator, ExchangePrimaryKey::iterator> ExchangePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table->sharedMutex);
		return std::pair<iterator, iterator>(index.begin(), index.end());
	}
	bool ExchangePrimaryKey::Insert(Exchange* const record)
	{
		return index.insert(record).second;
	}
	void ExchangePrimaryKey::Erase(Exchange* const  record)
	{
		index.erase(record);
	}
	bool ExchangePrimaryKey::CheckInsert(Exchange* const record)
	{
		return index.find(record) == index.end();
	}
	bool ExchangePrimaryKey::CheckUpdate(const Exchange* const oldRecord, const Exchange* const newRecord)
	{
		return ExchangeEqualForExchangePrimaryKey()(oldRecord, newRecord);
	}
	ProductPrimaryKey::ProductPrimaryKey(ProductTable* tableOwner, size_t buckets)
		:table(tableOwner), index(buckets)
	{
	}
	Product* ProductPrimaryKey::Select(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID)
	{
		Utility::Strcpy(CompareProduct.ExchangeID, ExchangeID);
		Utility::Strcpy(CompareProduct.ProductID, ProductID);
		
		std::shared_lock guard(table->sharedMutex);
		auto it = index.find(&CompareProduct);
		if (it == index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<ProductPrimaryKey::iterator, ProductPrimaryKey::iterator> ProductPrimaryKey::SelectAll()
	{
		std::shared_lock guard(table->sharedMutex);
		return std::pair<iterator, iterator>(index.begin(), index.end());
	}
	bool ProductPrimaryKey::Insert(Product* const record)
	{
		return index.insert(record).second;
	}
	void ProductPrimaryKey::Erase(Product* const  record)
	{
		index.erase(record);
	}
	bool ProductPrimaryKey::CheckInsert(Product* const record)
	{
		return index.find(record) == index.end();
	}
	bool ProductPrimaryKey::CheckUpdate(const Product* const oldRecord, const Product* const newRecord)
	{
		return ProductEqualForProductPrimaryKey()(oldRecord, newRecord);
	}
	HotInstrumentPrimaryKey::HotInstrumentPrimaryKey(HotInstrumentTable* tableOwner, size_t buckets)
		:table(tableOwner), index(buckets)
	{
	}
	HotInstrument* HotInstrumentPrimaryKey::Select(const DateType& TradingDay, const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const Int32Type& Rank)
	{
		Utility::Strcpy(CompareHotInstrument.TradingDay, TradingDay);
		Utility::Strcpy(CompareHotInstrument.ExchangeID, ExchangeID);
		Utility::Strcpy(CompareHotInstrument.ProductID, ProductID);
		CompareHotInstrument.Rank = Rank;
		
		std::shared_lock guard(table->sharedMutex);
		auto it = index.find(&CompareHotInstrument);
		if (it == index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<HotInstrumentPrimaryKey::iterator, HotInstrumentPrimaryKey::iterator> HotInstrumentPrimaryKey::SelectAll()
	{
		std::shared_lock guard(table->sharedMutex);
		return std::pair<iterator, iterator>(index.begin(), index.end());
	}
	bool HotInstrumentPrimaryKey::Insert(HotInstrument* const record)
	{
		return index.insert(record).second;
	}
	void HotInstrumentPrimaryKey::Erase(HotInstrument* const  record)
	{
		index.erase(record);
	}
	bool HotInstrumentPrimaryKey::CheckInsert(HotInstrument* const record)
	{
		return index.find(record) == index.end();
	}
	bool HotInstrumentPrimaryKey::CheckUpdate(const HotInstrument* const oldRecord, const HotInstrument* const newRecord)
	{
		return HotInstrumentEqualForHotInstrumentPrimaryKey()(oldRecord, newRecord);
	}
	InstrumentPrimaryKey::InstrumentPrimaryKey(InstrumentTable* tableOwner, size_t buckets)
		:table(tableOwner), index(buckets)
	{
	}
	Instrument* InstrumentPrimaryKey::Select(const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID)
	{
		Utility::Strcpy(CompareInstrument.ExchangeID, ExchangeID);
		Utility::Strcpy(CompareInstrument.InstrumentID, InstrumentID);
		
		std::shared_lock guard(table->sharedMutex);
		auto it = index.find(&CompareInstrument);
		if (it == index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<InstrumentPrimaryKey::iterator, InstrumentPrimaryKey::iterator> InstrumentPrimaryKey::SelectAll()
	{
		std::shared_lock guard(table->sharedMutex);
		return std::pair<iterator, iterator>(index.begin(), index.end());
	}
	bool InstrumentPrimaryKey::Insert(Instrument* const record)
	{
		return index.insert(record).second;
	}
	void InstrumentPrimaryKey::Erase(Instrument* const  record)
	{
		index.erase(record);
	}
	bool InstrumentPrimaryKey::CheckInsert(Instrument* const record)
	{
		return index.find(record) == index.end();
	}
	bool InstrumentPrimaryKey::CheckUpdate(const Instrument* const oldRecord, const Instrument* const newRecord)
	{
		return InstrumentEqualForInstrumentPrimaryKey()(oldRecord, newRecord);
	}
	DepthMarketDataPrimaryKey::DepthMarketDataPrimaryKey(DepthMarketDataTable* tableOwner, size_t buckets)
		:table(tableOwner), index(buckets)
	{
	}
	DepthMarketData* DepthMarketDataPrimaryKey::Select(const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID)
	{
		Utility::Strcpy(CompareDepthMarketData.TradingDay, TradingDay);
		Utility::Strcpy(CompareDepthMarketData.ExchangeID, ExchangeID);
		Utility::Strcpy(CompareDepthMarketData.InstrumentID, InstrumentID);
		
		std::shared_lock guard(table->sharedMutex);
		auto it = index.find(&CompareDepthMarketData);
		if (it == index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<DepthMarketDataPrimaryKey::iterator, DepthMarketDataPrimaryKey::iterator> DepthMarketDataPrimaryKey::SelectAll()
	{
		std::shared_lock guard(table->sharedMutex);
		return std::pair<iterator, iterator>(index.begin(), index.end());
	}
	bool DepthMarketDataPrimaryKey::Insert(DepthMarketData* const record)
	{
		return index.insert(record).second;
	}
	void DepthMarketDataPrimaryKey::Erase(DepthMarketData* const  record)
	{
		index.erase(record);
	}
	bool DepthMarketDataPrimaryKey::CheckInsert(DepthMarketData* const record)
	{
		return index.find(record) == index.end();
	}
	bool DepthMarketDataPrimaryKey::CheckUpdate(const DepthMarketData* const oldRecord, const DepthMarketData* const newRecord)
	{
		return DepthMarketDataEqualForDepthMarketDataPrimaryKey()(oldRecord, newRecord);
	}
	BarMarketDataPrimaryKey::BarMarketDataPrimaryKey(BarMarketDataTable* tableOwner, size_t buckets)
		:table(tableOwner), index(buckets)
	{
	}
	BarMarketData* BarMarketDataPrimaryKey::Select(const DateType& TradingDay, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const BarPrecesType& BarPreces, const Int32Type& BarPeriod, const Int64Type& BarTime)
	{
		Utility::Strcpy(CompareBarMarketData.TradingDay, TradingDay);
		Utility::Strcpy(CompareBarMarketData.ExchangeID, ExchangeID);
		Utility::Strcpy(CompareBarMarketData.InstrumentID, InstrumentID);
		CompareBarMarketData.BarPreces = BarPreces;
		CompareBarMarketData.BarPeriod = BarPeriod;
		CompareBarMarketData.BarTime = BarTime;
		
		std::shared_lock guard(table->sharedMutex);
		auto it = index.find(&CompareBarMarketData);
		if (it == index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<BarMarketDataPrimaryKey::iterator, BarMarketDataPrimaryKey::iterator> BarMarketDataPrimaryKey::SelectAll()
	{
		std::shared_lock guard(table->sharedMutex);
		return std::pair<iterator, iterator>(index.begin(), index.end());
	}
	bool BarMarketDataPrimaryKey::Insert(BarMarketData* const record)
	{
		return index.insert(record).second;
	}
	void BarMarketDataPrimaryKey::Erase(BarMarketData* const  record)
	{
		index.erase(record);
	}
	bool BarMarketDataPrimaryKey::CheckInsert(BarMarketData* const record)
	{
		return index.find(record) == index.end();
	}
	bool BarMarketDataPrimaryKey::CheckUpdate(const BarMarketData* const oldRecord, const BarMarketData* const newRecord)
	{
		return BarMarketDataEqualForBarMarketDataPrimaryKey()(oldRecord, newRecord);
	}
	MdSubscribePrimaryKey::MdSubscribePrimaryKey(MdSubscribeTable* tableOwner, size_t buckets)
		:table(tableOwner), index(buckets)
	{
	}
	MdSubscribe* MdSubscribePrimaryKey::Select(const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const DateType& StartTradingDay)
	{
		Utility::Strcpy(CompareMdSubscribe.ExchangeID, ExchangeID);
		Utility::Strcpy(CompareMdSubscribe.InstrumentID, InstrumentID);
		Utility::Strcpy(CompareMdSubscribe.StartTradingDay, StartTradingDay);
		
		std::shared_lock guard(table->sharedMutex);
		auto it = index.find(&CompareMdSubscribe);
		if (it == index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<MdSubscribePrimaryKey::iterator, MdSubscribePrimaryKey::iterator> MdSubscribePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table->sharedMutex);
		return std::pair<iterator, iterator>(index.begin(), index.end());
	}
	bool MdSubscribePrimaryKey::Insert(MdSubscribe* const record)
	{
		return index.insert(record).second;
	}
	void MdSubscribePrimaryKey::Erase(MdSubscribe* const  record)
	{
		index.erase(record);
	}
	bool MdSubscribePrimaryKey::CheckInsert(MdSubscribe* const record)
	{
		return index.find(record) == index.end();
	}
	bool MdSubscribePrimaryKey::CheckUpdate(const MdSubscribe* const oldRecord, const MdSubscribe* const newRecord)
	{
		return MdSubscribeEqualForMdSubscribePrimaryKey()(oldRecord, newRecord);
	}
	MdUserPrimaryKey::MdUserPrimaryKey(MdUserTable* tableOwner, size_t buckets)
		:table(tableOwner), index(buckets)
	{
	}
	MdUser* MdUserPrimaryKey::Select(const UserIDType& MdUserID)
	{
		Utility::Strcpy(CompareMdUser.MdUserID, MdUserID);
		
		std::shared_lock guard(table->sharedMutex);
		auto it = index.find(&CompareMdUser);
		if (it == index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<MdUserPrimaryKey::iterator, MdUserPrimaryKey::iterator> MdUserPrimaryKey::SelectAll()
	{
		std::shared_lock guard(table->sharedMutex);
		return std::pair<iterator, iterator>(index.begin(), index.end());
	}
	bool MdUserPrimaryKey::Insert(MdUser* const record)
	{
		return index.insert(record).second;
	}
	void MdUserPrimaryKey::Erase(MdUser* const  record)
	{
		index.erase(record);
	}
	bool MdUserPrimaryKey::CheckInsert(MdUser* const record)
	{
		return index.find(record) == index.end();
	}
	bool MdUserPrimaryKey::CheckUpdate(const MdUser* const oldRecord, const MdUser* const newRecord)
	{
		return MdUserEqualForMdUserPrimaryKey()(oldRecord, newRecord);
	}
	MdUserLoginSessionPrimaryKey::MdUserLoginSessionPrimaryKey(MdUserLoginSessionTable* tableOwner, size_t buckets)
		:table(tableOwner), index(buckets)
	{
	}
	MdUserLoginSession* MdUserLoginSessionPrimaryKey::Select(const UserIDType& MdUserID, const SessionIDType& SessionID)
	{
		Utility::Strcpy(CompareMdUserLoginSession.MdUserID, MdUserID);
		CompareMdUserLoginSession.SessionID = SessionID;
		
		std::shared_lock guard(table->sharedMutex);
		auto it = index.find(&CompareMdUserLoginSession);
		if (it == index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<MdUserLoginSessionPrimaryKey::iterator, MdUserLoginSessionPrimaryKey::iterator> MdUserLoginSessionPrimaryKey::SelectAll()
	{
		std::shared_lock guard(table->sharedMutex);
		return std::pair<iterator, iterator>(index.begin(), index.end());
	}
	bool MdUserLoginSessionPrimaryKey::Insert(MdUserLoginSession* const record)
	{
		return index.insert(record).second;
	}
	void MdUserLoginSessionPrimaryKey::Erase(MdUserLoginSession* const  record)
	{
		index.erase(record);
	}
	bool MdUserLoginSessionPrimaryKey::CheckInsert(MdUserLoginSession* const record)
	{
		return index.find(record) == index.end();
	}
	bool MdUserLoginSessionPrimaryKey::CheckUpdate(const MdUserLoginSession* const oldRecord, const MdUserLoginSession* const newRecord)
	{
		return MdUserLoginSessionEqualForMdUserLoginSessionPrimaryKey()(oldRecord, newRecord);
	}
	PrimaryAccountPrimaryKey::PrimaryAccountPrimaryKey(PrimaryAccountTable* tableOwner, size_t buckets)
		:table(tableOwner), index(buckets)
	{
	}
	PrimaryAccount* PrimaryAccountPrimaryKey::Select(const AccountIDType& PrimaryAccountID)
	{
		Utility::Strcpy(ComparePrimaryAccount.PrimaryAccountID, PrimaryAccountID);
		
		std::shared_lock guard(table->sharedMutex);
		auto it = index.find(&ComparePrimaryAccount);
		if (it == index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<PrimaryAccountPrimaryKey::iterator, PrimaryAccountPrimaryKey::iterator> PrimaryAccountPrimaryKey::SelectAll()
	{
		std::shared_lock guard(table->sharedMutex);
		return std::pair<iterator, iterator>(index.begin(), index.end());
	}
	bool PrimaryAccountPrimaryKey::Insert(PrimaryAccount* const record)
	{
		return index.insert(record).second;
	}
	void PrimaryAccountPrimaryKey::Erase(PrimaryAccount* const  record)
	{
		index.erase(record);
	}
	bool PrimaryAccountPrimaryKey::CheckInsert(PrimaryAccount* const record)
	{
		return index.find(record) == index.end();
	}
	bool PrimaryAccountPrimaryKey::CheckUpdate(const PrimaryAccount* const oldRecord, const PrimaryAccount* const newRecord)
	{
		return PrimaryAccountEqualForPrimaryAccountPrimaryKey()(oldRecord, newRecord);
	}
	AccountPrimaryKey::AccountPrimaryKey(AccountTable* tableOwner, size_t buckets)
		:table(tableOwner), index(buckets)
	{
	}
	Account* AccountPrimaryKey::Select(const AccountIDType& AccountID)
	{
		Utility::Strcpy(CompareAccount.AccountID, AccountID);
		
		std::shared_lock guard(table->sharedMutex);
		auto it = index.find(&CompareAccount);
		if (it == index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<AccountPrimaryKey::iterator, AccountPrimaryKey::iterator> AccountPrimaryKey::SelectAll()
	{
		std::shared_lock guard(table->sharedMutex);
		return std::pair<iterator, iterator>(index.begin(), index.end());
	}
	bool AccountPrimaryKey::Insert(Account* const record)
	{
		return index.insert(record).second;
	}
	void AccountPrimaryKey::Erase(Account* const  record)
	{
		index.erase(record);
	}
	bool AccountPrimaryKey::CheckInsert(Account* const record)
	{
		return index.find(record) == index.end();
	}
	bool AccountPrimaryKey::CheckUpdate(const Account* const oldRecord, const Account* const newRecord)
	{
		return AccountEqualForAccountPrimaryKey()(oldRecord, newRecord);
	}
	CapitalPrimaryKey::CapitalPrimaryKey(CapitalTable* tableOwner, size_t buckets)
		:table(tableOwner), index(buckets)
	{
	}
	Capital* CapitalPrimaryKey::Select(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		Utility::Strcpy(CompareCapital.TradingDay, TradingDay);
		Utility::Strcpy(CompareCapital.AccountID, AccountID);
		
		std::shared_lock guard(table->sharedMutex);
		auto it = index.find(&CompareCapital);
		if (it == index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<CapitalPrimaryKey::iterator, CapitalPrimaryKey::iterator> CapitalPrimaryKey::SelectAll()
	{
		std::shared_lock guard(table->sharedMutex);
		return std::pair<iterator, iterator>(index.begin(), index.end());
	}
	bool CapitalPrimaryKey::Insert(Capital* const record)
	{
		return index.insert(record).second;
	}
	void CapitalPrimaryKey::Erase(Capital* const  record)
	{
		index.erase(record);
	}
	bool CapitalPrimaryKey::CheckInsert(Capital* const record)
	{
		return index.find(record) == index.end();
	}
	bool CapitalPrimaryKey::CheckUpdate(const Capital* const oldRecord, const Capital* const newRecord)
	{
		return CapitalEqualForCapitalPrimaryKey()(oldRecord, newRecord);
	}
	PositionPrimaryKey::PositionPrimaryKey(PositionTable* tableOwner, size_t buckets)
		:table(tableOwner), index(buckets)
	{
	}
	Position* PositionPrimaryKey::Select(const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const PosiDirectionType& PosiDirection)
	{
		Utility::Strcpy(ComparePosition.TradingDay, TradingDay);
		Utility::Strcpy(ComparePosition.AccountID, AccountID);
		Utility::Strcpy(ComparePosition.ExchangeID, ExchangeID);
		Utility::Strcpy(ComparePosition.InstrumentID, InstrumentID);
		ComparePosition.PosiDirection = PosiDirection;
		
		std::shared_lock guard(table->sharedMutex);
		auto it = index.find(&ComparePosition);
		if (it == index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<PositionPrimaryKey::iterator, PositionPrimaryKey::iterator> PositionPrimaryKey::SelectAll()
	{
		std::shared_lock guard(table->sharedMutex);
		return std::pair<iterator, iterator>(index.begin(), index.end());
	}
	bool PositionPrimaryKey::Insert(Position* const record)
	{
		return index.insert(record).second;
	}
	void PositionPrimaryKey::Erase(Position* const  record)
	{
		index.erase(record);
	}
	bool PositionPrimaryKey::CheckInsert(Position* const record)
	{
		return index.find(record) == index.end();
	}
	bool PositionPrimaryKey::CheckUpdate(const Position* const oldRecord, const Position* const newRecord)
	{
		return PositionEqualForPositionPrimaryKey()(oldRecord, newRecord);
	}
	PositionDetailPrimaryKey::PositionDetailPrimaryKey(PositionDetailTable* tableOwner, size_t buckets)
		:table(tableOwner), index(buckets)
	{
	}
	PositionDetail* PositionDetailPrimaryKey::Select(const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const PosiDirectionType& PosiDirection, const DateType& OpenDate, const TradeIDType& TradeID)
	{
		Utility::Strcpy(ComparePositionDetail.TradingDay, TradingDay);
		Utility::Strcpy(ComparePositionDetail.AccountID, AccountID);
		Utility::Strcpy(ComparePositionDetail.ExchangeID, ExchangeID);
		Utility::Strcpy(ComparePositionDetail.InstrumentID, InstrumentID);
		ComparePositionDetail.PosiDirection = PosiDirection;
		Utility::Strcpy(ComparePositionDetail.OpenDate, OpenDate);
		Utility::Strcpy(ComparePositionDetail.TradeID, TradeID);
		
		std::shared_lock guard(table->sharedMutex);
		auto it = index.find(&ComparePositionDetail);
		if (it == index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<PositionDetailPrimaryKey::iterator, PositionDetailPrimaryKey::iterator> PositionDetailPrimaryKey::SelectAll()
	{
		std::shared_lock guard(table->sharedMutex);
		return std::pair<iterator, iterator>(index.begin(), index.end());
	}
	bool PositionDetailPrimaryKey::Insert(PositionDetail* const record)
	{
		return index.insert(record).second;
	}
	void PositionDetailPrimaryKey::Erase(PositionDetail* const  record)
	{
		index.erase(record);
	}
	bool PositionDetailPrimaryKey::CheckInsert(PositionDetail* const record)
	{
		return index.find(record) == index.end();
	}
	bool PositionDetailPrimaryKey::CheckUpdate(const PositionDetail* const oldRecord, const PositionDetail* const newRecord)
	{
		return PositionDetailEqualForPositionDetailPrimaryKey()(oldRecord, newRecord);
	}
	OrderPrimaryKey::OrderPrimaryKey(OrderTable* tableOwner, size_t buckets)
		:table(tableOwner), index(buckets)
	{
	}
	Order* OrderPrimaryKey::Select(const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const OrderIDType& OrderID)
	{
		Utility::Strcpy(CompareOrder.TradingDay, TradingDay);
		Utility::Strcpy(CompareOrder.AccountID, AccountID);
		Utility::Strcpy(CompareOrder.ExchangeID, ExchangeID);
		Utility::Strcpy(CompareOrder.InstrumentID, InstrumentID);
		CompareOrder.OrderID = OrderID;
		
		std::shared_lock guard(table->sharedMutex);
		auto it = index.find(&CompareOrder);
		if (it == index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<OrderPrimaryKey::iterator, OrderPrimaryKey::iterator> OrderPrimaryKey::SelectAll()
	{
		std::shared_lock guard(table->sharedMutex);
		return std::pair<iterator, iterator>(index.begin(), index.end());
	}
	bool OrderPrimaryKey::Insert(Order* const record)
	{
		return index.insert(record).second;
	}
	void OrderPrimaryKey::Erase(Order* const  record)
	{
		index.erase(record);
	}
	bool OrderPrimaryKey::CheckInsert(Order* const record)
	{
		return index.find(record) == index.end();
	}
	bool OrderPrimaryKey::CheckUpdate(const Order* const oldRecord, const Order* const newRecord)
	{
		return OrderEqualForOrderPrimaryKey()(oldRecord, newRecord);
	}
	OrderUniqueKeyClientOrderID::OrderUniqueKeyClientOrderID(OrderTable* tableOwner, size_t buckets)
		:table(tableOwner), index(buckets)
	{
	}
	Order* OrderUniqueKeyClientOrderID::Select(const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const SessionIDType& SessionID, const ClientOrderIDType& ClientOrderID)
	{
		Utility::Strcpy(CompareOrder.TradingDay, TradingDay);
		Utility::Strcpy(CompareOrder.AccountID, AccountID);
		Utility::Strcpy(CompareOrder.ExchangeID, ExchangeID);
		Utility::Strcpy(CompareOrder.InstrumentID, InstrumentID);
		CompareOrder.SessionID = SessionID;
		CompareOrder.ClientOrderID = ClientOrderID;
		std::shared_lock guard(table->sharedMutex);
		auto it = index.find(&CompareOrder);
		if (it == index.end())
		{
			return nullptr;
		}
		return *it;
	}
	bool OrderUniqueKeyClientOrderID::Insert(Order* const record)
	{
		return index.insert(record).second;
	}
	void OrderUniqueKeyClientOrderID::Erase(Order* const  record)
	{
		index.erase(record);
	}
	bool OrderUniqueKeyClientOrderID::CheckInsert(Order* const record)
	{
		return index.find(record) == index.end();
	}
	bool OrderUniqueKeyClientOrderID::CheckUpdate(const Order* const oldRecord, const Order* const newRecord)
	{
		return OrderEqualForClientOrderIDUniqueKey()(oldRecord, newRecord);
	}
	
	TradePrimaryKey::TradePrimaryKey(TradeTable* tableOwner, size_t buckets)
		:table(tableOwner), index(buckets)
	{
	}
	Trade* TradePrimaryKey::Select(const DateType& TradingDay, const ExchangeIDType& ExchangeID, const TradeIDType& TradeID, const DirectionType& Direction)
	{
		Utility::Strcpy(CompareTrade.TradingDay, TradingDay);
		Utility::Strcpy(CompareTrade.ExchangeID, ExchangeID);
		Utility::Strcpy(CompareTrade.TradeID, TradeID);
		CompareTrade.Direction = Direction;
		
		std::shared_lock guard(table->sharedMutex);
		auto it = index.find(&CompareTrade);
		if (it == index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<TradePrimaryKey::iterator, TradePrimaryKey::iterator> TradePrimaryKey::SelectAll()
	{
		std::shared_lock guard(table->sharedMutex);
		return std::pair<iterator, iterator>(index.begin(), index.end());
	}
	bool TradePrimaryKey::Insert(Trade* const record)
	{
		return index.insert(record).second;
	}
	void TradePrimaryKey::Erase(Trade* const  record)
	{
		index.erase(record);
	}
	bool TradePrimaryKey::CheckInsert(Trade* const record)
	{
		return index.find(record) == index.end();
	}
	bool TradePrimaryKey::CheckUpdate(const Trade* const oldRecord, const Trade* const newRecord)
	{
		return TradeEqualForTradePrimaryKey()(oldRecord, newRecord);
	}
	AccountLoginSessionPrimaryKey::AccountLoginSessionPrimaryKey(AccountLoginSessionTable* tableOwner, size_t buckets)
		:table(tableOwner), index(buckets)
	{
	}
	AccountLoginSession* AccountLoginSessionPrimaryKey::Select(const AccountIDType& AccountID, const SessionIDType& SessionID)
	{
		Utility::Strcpy(CompareAccountLoginSession.AccountID, AccountID);
		CompareAccountLoginSession.SessionID = SessionID;
		
		std::shared_lock guard(table->sharedMutex);
		auto it = index.find(&CompareAccountLoginSession);
		if (it == index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<AccountLoginSessionPrimaryKey::iterator, AccountLoginSessionPrimaryKey::iterator> AccountLoginSessionPrimaryKey::SelectAll()
	{
		std::shared_lock guard(table->sharedMutex);
		return std::pair<iterator, iterator>(index.begin(), index.end());
	}
	bool AccountLoginSessionPrimaryKey::Insert(AccountLoginSession* const record)
	{
		return index.insert(record).second;
	}
	void AccountLoginSessionPrimaryKey::Erase(AccountLoginSession* const  record)
	{
		index.erase(record);
	}
	bool AccountLoginSessionPrimaryKey::CheckInsert(AccountLoginSession* const record)
	{
		return index.find(record) == index.end();
	}
	bool AccountLoginSessionPrimaryKey::CheckUpdate(const AccountLoginSession* const oldRecord, const AccountLoginSession* const newRecord)
	{
		return AccountLoginSessionEqualForAccountLoginSessionPrimaryKey()(oldRecord, newRecord);
	}
	PrimaryAccountLoginSessionPrimaryKey::PrimaryAccountLoginSessionPrimaryKey(PrimaryAccountLoginSessionTable* tableOwner, size_t buckets)
		:table(tableOwner), index(buckets)
	{
	}
	PrimaryAccountLoginSession* PrimaryAccountLoginSessionPrimaryKey::Select(const AccountIDType& PrimaryAccountID, const SessionIDType& SessionID)
	{
		Utility::Strcpy(ComparePrimaryAccountLoginSession.PrimaryAccountID, PrimaryAccountID);
		ComparePrimaryAccountLoginSession.SessionID = SessionID;
		
		std::shared_lock guard(table->sharedMutex);
		auto it = index.find(&ComparePrimaryAccountLoginSession);
		if (it == index.end())
		{
			return nullptr;
		}
		return *it;
	}
	std::pair<PrimaryAccountLoginSessionPrimaryKey::iterator, PrimaryAccountLoginSessionPrimaryKey::iterator> PrimaryAccountLoginSessionPrimaryKey::SelectAll()
	{
		std::shared_lock guard(table->sharedMutex);
		return std::pair<iterator, iterator>(index.begin(), index.end());
	}
	bool PrimaryAccountLoginSessionPrimaryKey::Insert(PrimaryAccountLoginSession* const record)
	{
		return index.insert(record).second;
	}
	void PrimaryAccountLoginSessionPrimaryKey::Erase(PrimaryAccountLoginSession* const  record)
	{
		index.erase(record);
	}
	bool PrimaryAccountLoginSessionPrimaryKey::CheckInsert(PrimaryAccountLoginSession* const record)
	{
		return index.find(record) == index.end();
	}
	bool PrimaryAccountLoginSessionPrimaryKey::CheckUpdate(const PrimaryAccountLoginSession* const oldRecord, const PrimaryAccountLoginSession* const newRecord)
	{
		return PrimaryAccountLoginSessionEqualForPrimaryAccountLoginSessionPrimaryKey()(oldRecord, newRecord);
	}
}
