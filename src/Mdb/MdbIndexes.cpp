// 本文件由 ../Templates/Cpp/Mdb/MdbIndexes.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdbIndexes.h"
#include "MdbTables.h"
#include <Spark/Core/Utility/Utility.h>
#include <string.h>


using namespace spark::core;
namespace mdb
{
	HotInstrumentIndexTradingDay::HotInstrumentIndexTradingDay(HotInstrumentTable* tableOwner)
		:table(tableOwner)
	{
	}
	HotInstrumentIndexTradingDay::iterator HotInstrumentIndexTradingDay::LowerBound(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const Int32Type& Rank, const DateType& TradingDay)
	{
		FillCompareRecord(ExchangeID, ProductID, Rank, TradingDay);
		std::shared_lock guard(table->sharedMutex);
		return index.lower_bound(&CompareHotInstrument);
	}
	HotInstrumentIndexTradingDay::iterator HotInstrumentIndexTradingDay::UpperBound(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const Int32Type& Rank, const DateType& TradingDay)
	{
		FillCompareRecord(ExchangeID, ProductID, Rank, TradingDay);
		std::shared_lock guard(table->sharedMutex);
		return index.upper_bound(&CompareHotInstrument);
	}
	std::pair<HotInstrumentIndexTradingDay::iterator, HotInstrumentIndexTradingDay::iterator> HotInstrumentIndexTradingDay::EqualRange(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const Int32Type& Rank, const DateType& TradingDay)
	{
		FillCompareRecord(ExchangeID, ProductID, Rank, TradingDay);
		std::shared_lock guard(table->sharedMutex);
		return index.equal_range(&CompareHotInstrument);
	}
	void HotInstrumentIndexTradingDay::Insert(HotInstrument* const record)
	{
		index.insert(record);
	}
	void HotInstrumentIndexTradingDay::Erase(HotInstrument* const record)
	{
		auto it = FindNode(record);
		index.erase(it);
	}
	void HotInstrumentIndexTradingDay::Update(iterator it)
	{
		auto record = *it;
		index.erase(it);
		index.insert(record);
	}
	bool HotInstrumentIndexTradingDay::NeedUpdate(const HotInstrument* const oldRecord, const HotInstrument* const newRecord)
	{
		return !(HotInstrumentEqualForTradingDayIndex()(oldRecord, newRecord));
	}
	HotInstrumentIndexTradingDay::iterator HotInstrumentIndexTradingDay::FindNode(HotInstrument* const record)
	{
		auto p = index.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index.end();
	}
	void HotInstrumentIndexTradingDay::FillCompareRecord(const ExchangeIDType& ExchangeID, const ProductIDType& ProductID, const Int32Type& Rank, const DateType& TradingDay)
	{
		Utility::Strcpy(CompareHotInstrument.ExchangeID, ExchangeID);
		Utility::Strcpy(CompareHotInstrument.ProductID, ProductID);
		CompareHotInstrument.Rank = Rank;
		Utility::Strcpy(CompareHotInstrument.TradingDay, TradingDay);
	}
	
	InstrumentIndexExchangeID::InstrumentIndexExchangeID(InstrumentTable* tableOwner)
		:table(tableOwner)
	{
	}
	InstrumentIndexExchangeID::iterator InstrumentIndexExchangeID::LowerBound(const ExchangeIDType& ExchangeID)
	{
		FillCompareRecord(ExchangeID);
		std::shared_lock guard(table->sharedMutex);
		return index.lower_bound(&CompareInstrument);
	}
	InstrumentIndexExchangeID::iterator InstrumentIndexExchangeID::UpperBound(const ExchangeIDType& ExchangeID)
	{
		FillCompareRecord(ExchangeID);
		std::shared_lock guard(table->sharedMutex);
		return index.upper_bound(&CompareInstrument);
	}
	std::pair<InstrumentIndexExchangeID::iterator, InstrumentIndexExchangeID::iterator> InstrumentIndexExchangeID::EqualRange(const ExchangeIDType& ExchangeID)
	{
		FillCompareRecord(ExchangeID);
		std::shared_lock guard(table->sharedMutex);
		return index.equal_range(&CompareInstrument);
	}
	void InstrumentIndexExchangeID::Insert(Instrument* const record)
	{
		index.insert(record);
	}
	void InstrumentIndexExchangeID::Erase(Instrument* const record)
	{
		auto it = FindNode(record);
		index.erase(it);
	}
	void InstrumentIndexExchangeID::Update(iterator it)
	{
		auto record = *it;
		index.erase(it);
		index.insert(record);
	}
	bool InstrumentIndexExchangeID::NeedUpdate(const Instrument* const oldRecord, const Instrument* const newRecord)
	{
		return !(InstrumentEqualForExchangeIDIndex()(oldRecord, newRecord));
	}
	InstrumentIndexExchangeID::iterator InstrumentIndexExchangeID::FindNode(Instrument* const record)
	{
		auto p = index.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index.end();
	}
	void InstrumentIndexExchangeID::FillCompareRecord(const ExchangeIDType& ExchangeID)
	{
		Utility::Strcpy(CompareInstrument.ExchangeID, ExchangeID);
	}
	
	MdUserLoginSessionIndexSessionID::MdUserLoginSessionIndexSessionID(MdUserLoginSessionTable* tableOwner)
		:table(tableOwner)
	{
	}
	MdUserLoginSessionIndexSessionID::iterator MdUserLoginSessionIndexSessionID::LowerBound(const SessionIDType& SessionID)
	{
		FillCompareRecord(SessionID);
		std::shared_lock guard(table->sharedMutex);
		return index.lower_bound(&CompareMdUserLoginSession);
	}
	MdUserLoginSessionIndexSessionID::iterator MdUserLoginSessionIndexSessionID::UpperBound(const SessionIDType& SessionID)
	{
		FillCompareRecord(SessionID);
		std::shared_lock guard(table->sharedMutex);
		return index.upper_bound(&CompareMdUserLoginSession);
	}
	std::pair<MdUserLoginSessionIndexSessionID::iterator, MdUserLoginSessionIndexSessionID::iterator> MdUserLoginSessionIndexSessionID::EqualRange(const SessionIDType& SessionID)
	{
		FillCompareRecord(SessionID);
		std::shared_lock guard(table->sharedMutex);
		return index.equal_range(&CompareMdUserLoginSession);
	}
	void MdUserLoginSessionIndexSessionID::Insert(MdUserLoginSession* const record)
	{
		index.insert(record);
	}
	void MdUserLoginSessionIndexSessionID::Erase(MdUserLoginSession* const record)
	{
		auto it = FindNode(record);
		index.erase(it);
	}
	void MdUserLoginSessionIndexSessionID::Update(iterator it)
	{
		auto record = *it;
		index.erase(it);
		index.insert(record);
	}
	bool MdUserLoginSessionIndexSessionID::NeedUpdate(const MdUserLoginSession* const oldRecord, const MdUserLoginSession* const newRecord)
	{
		return !(MdUserLoginSessionEqualForSessionIDIndex()(oldRecord, newRecord));
	}
	MdUserLoginSessionIndexSessionID::iterator MdUserLoginSessionIndexSessionID::FindNode(MdUserLoginSession* const record)
	{
		auto p = index.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index.end();
	}
	void MdUserLoginSessionIndexSessionID::FillCompareRecord(const SessionIDType& SessionID)
	{
		CompareMdUserLoginSession.SessionID = SessionID;
	}
	
	MdUserLoginSessionIndexMdUserID::MdUserLoginSessionIndexMdUserID(MdUserLoginSessionTable* tableOwner)
		:table(tableOwner)
	{
	}
	MdUserLoginSessionIndexMdUserID::iterator MdUserLoginSessionIndexMdUserID::LowerBound(const UserIDType& MdUserID)
	{
		FillCompareRecord(MdUserID);
		std::shared_lock guard(table->sharedMutex);
		return index.lower_bound(&CompareMdUserLoginSession);
	}
	MdUserLoginSessionIndexMdUserID::iterator MdUserLoginSessionIndexMdUserID::UpperBound(const UserIDType& MdUserID)
	{
		FillCompareRecord(MdUserID);
		std::shared_lock guard(table->sharedMutex);
		return index.upper_bound(&CompareMdUserLoginSession);
	}
	std::pair<MdUserLoginSessionIndexMdUserID::iterator, MdUserLoginSessionIndexMdUserID::iterator> MdUserLoginSessionIndexMdUserID::EqualRange(const UserIDType& MdUserID)
	{
		FillCompareRecord(MdUserID);
		std::shared_lock guard(table->sharedMutex);
		return index.equal_range(&CompareMdUserLoginSession);
	}
	void MdUserLoginSessionIndexMdUserID::Insert(MdUserLoginSession* const record)
	{
		index.insert(record);
	}
	void MdUserLoginSessionIndexMdUserID::Erase(MdUserLoginSession* const record)
	{
		auto it = FindNode(record);
		index.erase(it);
	}
	void MdUserLoginSessionIndexMdUserID::Update(iterator it)
	{
		auto record = *it;
		index.erase(it);
		index.insert(record);
	}
	bool MdUserLoginSessionIndexMdUserID::NeedUpdate(const MdUserLoginSession* const oldRecord, const MdUserLoginSession* const newRecord)
	{
		return !(MdUserLoginSessionEqualForMdUserIDIndex()(oldRecord, newRecord));
	}
	MdUserLoginSessionIndexMdUserID::iterator MdUserLoginSessionIndexMdUserID::FindNode(MdUserLoginSession* const record)
	{
		auto p = index.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index.end();
	}
	void MdUserLoginSessionIndexMdUserID::FillCompareRecord(const UserIDType& MdUserID)
	{
		Utility::Strcpy(CompareMdUserLoginSession.MdUserID, MdUserID);
	}
	
	PrimaryAccountIndexOfferID::PrimaryAccountIndexOfferID(PrimaryAccountTable* tableOwner)
		:table(tableOwner)
	{
	}
	PrimaryAccountIndexOfferID::iterator PrimaryAccountIndexOfferID::LowerBound(const OfferIDType& OfferID)
	{
		FillCompareRecord(OfferID);
		std::shared_lock guard(table->sharedMutex);
		return index.lower_bound(&ComparePrimaryAccount);
	}
	PrimaryAccountIndexOfferID::iterator PrimaryAccountIndexOfferID::UpperBound(const OfferIDType& OfferID)
	{
		FillCompareRecord(OfferID);
		std::shared_lock guard(table->sharedMutex);
		return index.upper_bound(&ComparePrimaryAccount);
	}
	std::pair<PrimaryAccountIndexOfferID::iterator, PrimaryAccountIndexOfferID::iterator> PrimaryAccountIndexOfferID::EqualRange(const OfferIDType& OfferID)
	{
		FillCompareRecord(OfferID);
		std::shared_lock guard(table->sharedMutex);
		return index.equal_range(&ComparePrimaryAccount);
	}
	void PrimaryAccountIndexOfferID::Insert(PrimaryAccount* const record)
	{
		index.insert(record);
	}
	void PrimaryAccountIndexOfferID::Erase(PrimaryAccount* const record)
	{
		auto it = FindNode(record);
		index.erase(it);
	}
	void PrimaryAccountIndexOfferID::Update(iterator it)
	{
		auto record = *it;
		index.erase(it);
		index.insert(record);
	}
	bool PrimaryAccountIndexOfferID::NeedUpdate(const PrimaryAccount* const oldRecord, const PrimaryAccount* const newRecord)
	{
		return !(PrimaryAccountEqualForOfferIDIndex()(oldRecord, newRecord));
	}
	PrimaryAccountIndexOfferID::iterator PrimaryAccountIndexOfferID::FindNode(PrimaryAccount* const record)
	{
		auto p = index.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index.end();
	}
	void PrimaryAccountIndexOfferID::FillCompareRecord(const OfferIDType& OfferID)
	{
		ComparePrimaryAccount.OfferID = OfferID;
	}
	
	CapitalIndexTradingDay::CapitalIndexTradingDay(CapitalTable* tableOwner)
		:table(tableOwner)
	{
	}
	CapitalIndexTradingDay::iterator CapitalIndexTradingDay::LowerBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table->sharedMutex);
		return index.lower_bound(&CompareCapital);
	}
	CapitalIndexTradingDay::iterator CapitalIndexTradingDay::UpperBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table->sharedMutex);
		return index.upper_bound(&CompareCapital);
	}
	std::pair<CapitalIndexTradingDay::iterator, CapitalIndexTradingDay::iterator> CapitalIndexTradingDay::EqualRange(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table->sharedMutex);
		return index.equal_range(&CompareCapital);
	}
	void CapitalIndexTradingDay::Insert(Capital* const record)
	{
		index.insert(record);
	}
	void CapitalIndexTradingDay::Erase(Capital* const record)
	{
		auto it = FindNode(record);
		index.erase(it);
	}
	void CapitalIndexTradingDay::Update(iterator it)
	{
		auto record = *it;
		index.erase(it);
		index.insert(record);
	}
	bool CapitalIndexTradingDay::NeedUpdate(const Capital* const oldRecord, const Capital* const newRecord)
	{
		return !(CapitalEqualForTradingDayIndex()(oldRecord, newRecord));
	}
	CapitalIndexTradingDay::iterator CapitalIndexTradingDay::FindNode(Capital* const record)
	{
		auto p = index.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index.end();
	}
	void CapitalIndexTradingDay::FillCompareRecord(const DateType& TradingDay)
	{
		Utility::Strcpy(CompareCapital.TradingDay, TradingDay);
	}
	
	PositionIndexAccount::PositionIndexAccount(PositionTable* tableOwner)
		:table(tableOwner)
	{
	}
	PositionIndexAccount::iterator PositionIndexAccount::LowerBound(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(table->sharedMutex);
		return index.lower_bound(&ComparePosition);
	}
	PositionIndexAccount::iterator PositionIndexAccount::UpperBound(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(table->sharedMutex);
		return index.upper_bound(&ComparePosition);
	}
	std::pair<PositionIndexAccount::iterator, PositionIndexAccount::iterator> PositionIndexAccount::EqualRange(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(table->sharedMutex);
		return index.equal_range(&ComparePosition);
	}
	void PositionIndexAccount::Insert(Position* const record)
	{
		index.insert(record);
	}
	void PositionIndexAccount::Erase(Position* const record)
	{
		auto it = FindNode(record);
		index.erase(it);
	}
	void PositionIndexAccount::Update(iterator it)
	{
		auto record = *it;
		index.erase(it);
		index.insert(record);
	}
	bool PositionIndexAccount::NeedUpdate(const Position* const oldRecord, const Position* const newRecord)
	{
		return !(PositionEqualForAccountIndex()(oldRecord, newRecord));
	}
	PositionIndexAccount::iterator PositionIndexAccount::FindNode(Position* const record)
	{
		auto p = index.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index.end();
	}
	void PositionIndexAccount::FillCompareRecord(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		Utility::Strcpy(ComparePosition.TradingDay, TradingDay);
		Utility::Strcpy(ComparePosition.AccountID, AccountID);
	}
	
	PositionIndexTradingDay::PositionIndexTradingDay(PositionTable* tableOwner)
		:table(tableOwner)
	{
	}
	PositionIndexTradingDay::iterator PositionIndexTradingDay::LowerBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table->sharedMutex);
		return index.lower_bound(&ComparePosition);
	}
	PositionIndexTradingDay::iterator PositionIndexTradingDay::UpperBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table->sharedMutex);
		return index.upper_bound(&ComparePosition);
	}
	std::pair<PositionIndexTradingDay::iterator, PositionIndexTradingDay::iterator> PositionIndexTradingDay::EqualRange(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table->sharedMutex);
		return index.equal_range(&ComparePosition);
	}
	void PositionIndexTradingDay::Insert(Position* const record)
	{
		index.insert(record);
	}
	void PositionIndexTradingDay::Erase(Position* const record)
	{
		auto it = FindNode(record);
		index.erase(it);
	}
	void PositionIndexTradingDay::Update(iterator it)
	{
		auto record = *it;
		index.erase(it);
		index.insert(record);
	}
	bool PositionIndexTradingDay::NeedUpdate(const Position* const oldRecord, const Position* const newRecord)
	{
		return !(PositionEqualForTradingDayIndex()(oldRecord, newRecord));
	}
	PositionIndexTradingDay::iterator PositionIndexTradingDay::FindNode(Position* const record)
	{
		auto p = index.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index.end();
	}
	void PositionIndexTradingDay::FillCompareRecord(const DateType& TradingDay)
	{
		Utility::Strcpy(ComparePosition.TradingDay, TradingDay);
	}
	
	PositionDetailIndexTradeMatch::PositionDetailIndexTradeMatch(PositionDetailTable* tableOwner)
		:table(tableOwner)
	{
	}
	PositionDetailIndexTradeMatch::iterator PositionDetailIndexTradeMatch::LowerBound(const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const PosiDirectionType& PosiDirection)
	{
		FillCompareRecord(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection);
		std::shared_lock guard(table->sharedMutex);
		return index.lower_bound(&ComparePositionDetail);
	}
	PositionDetailIndexTradeMatch::iterator PositionDetailIndexTradeMatch::UpperBound(const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const PosiDirectionType& PosiDirection)
	{
		FillCompareRecord(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection);
		std::shared_lock guard(table->sharedMutex);
		return index.upper_bound(&ComparePositionDetail);
	}
	std::pair<PositionDetailIndexTradeMatch::iterator, PositionDetailIndexTradeMatch::iterator> PositionDetailIndexTradeMatch::EqualRange(const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const PosiDirectionType& PosiDirection)
	{
		FillCompareRecord(TradingDay, AccountID, ExchangeID, InstrumentID, PosiDirection);
		std::shared_lock guard(table->sharedMutex);
		return index.equal_range(&ComparePositionDetail);
	}
	void PositionDetailIndexTradeMatch::Insert(PositionDetail* const record)
	{
		index.insert(record);
	}
	void PositionDetailIndexTradeMatch::Erase(PositionDetail* const record)
	{
		auto it = FindNode(record);
		index.erase(it);
	}
	void PositionDetailIndexTradeMatch::Update(iterator it)
	{
		auto record = *it;
		index.erase(it);
		index.insert(record);
	}
	bool PositionDetailIndexTradeMatch::NeedUpdate(const PositionDetail* const oldRecord, const PositionDetail* const newRecord)
	{
		return !(PositionDetailEqualForTradeMatchIndex()(oldRecord, newRecord));
	}
	PositionDetailIndexTradeMatch::iterator PositionDetailIndexTradeMatch::FindNode(PositionDetail* const record)
	{
		auto p = index.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index.end();
	}
	void PositionDetailIndexTradeMatch::FillCompareRecord(const DateType& TradingDay, const AccountIDType& AccountID, const ExchangeIDType& ExchangeID, const InstrumentIDType& InstrumentID, const PosiDirectionType& PosiDirection)
	{
		Utility::Strcpy(ComparePositionDetail.TradingDay, TradingDay);
		Utility::Strcpy(ComparePositionDetail.AccountID, AccountID);
		Utility::Strcpy(ComparePositionDetail.ExchangeID, ExchangeID);
		Utility::Strcpy(ComparePositionDetail.InstrumentID, InstrumentID);
		ComparePositionDetail.PosiDirection = PosiDirection;
	}
	
	PositionDetailIndexTradingDay::PositionDetailIndexTradingDay(PositionDetailTable* tableOwner)
		:table(tableOwner)
	{
	}
	PositionDetailIndexTradingDay::iterator PositionDetailIndexTradingDay::LowerBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table->sharedMutex);
		return index.lower_bound(&ComparePositionDetail);
	}
	PositionDetailIndexTradingDay::iterator PositionDetailIndexTradingDay::UpperBound(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table->sharedMutex);
		return index.upper_bound(&ComparePositionDetail);
	}
	std::pair<PositionDetailIndexTradingDay::iterator, PositionDetailIndexTradingDay::iterator> PositionDetailIndexTradingDay::EqualRange(const DateType& TradingDay)
	{
		FillCompareRecord(TradingDay);
		std::shared_lock guard(table->sharedMutex);
		return index.equal_range(&ComparePositionDetail);
	}
	void PositionDetailIndexTradingDay::Insert(PositionDetail* const record)
	{
		index.insert(record);
	}
	void PositionDetailIndexTradingDay::Erase(PositionDetail* const record)
	{
		auto it = FindNode(record);
		index.erase(it);
	}
	void PositionDetailIndexTradingDay::Update(iterator it)
	{
		auto record = *it;
		index.erase(it);
		index.insert(record);
	}
	bool PositionDetailIndexTradingDay::NeedUpdate(const PositionDetail* const oldRecord, const PositionDetail* const newRecord)
	{
		return !(PositionDetailEqualForTradingDayIndex()(oldRecord, newRecord));
	}
	PositionDetailIndexTradingDay::iterator PositionDetailIndexTradingDay::FindNode(PositionDetail* const record)
	{
		auto p = index.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index.end();
	}
	void PositionDetailIndexTradingDay::FillCompareRecord(const DateType& TradingDay)
	{
		Utility::Strcpy(ComparePositionDetail.TradingDay, TradingDay);
	}
	
	OrderIndexAccountID::OrderIndexAccountID(OrderTable* tableOwner)
		:table(tableOwner)
	{
	}
	OrderIndexAccountID::iterator OrderIndexAccountID::LowerBound(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(table->sharedMutex);
		return index.lower_bound(&CompareOrder);
	}
	OrderIndexAccountID::iterator OrderIndexAccountID::UpperBound(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(table->sharedMutex);
		return index.upper_bound(&CompareOrder);
	}
	std::pair<OrderIndexAccountID::iterator, OrderIndexAccountID::iterator> OrderIndexAccountID::EqualRange(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(table->sharedMutex);
		return index.equal_range(&CompareOrder);
	}
	void OrderIndexAccountID::Insert(Order* const record)
	{
		index.insert(record);
	}
	void OrderIndexAccountID::Erase(Order* const record)
	{
		auto it = FindNode(record);
		index.erase(it);
	}
	void OrderIndexAccountID::Update(iterator it)
	{
		auto record = *it;
		index.erase(it);
		index.insert(record);
	}
	bool OrderIndexAccountID::NeedUpdate(const Order* const oldRecord, const Order* const newRecord)
	{
		return !(OrderEqualForAccountIDIndex()(oldRecord, newRecord));
	}
	OrderIndexAccountID::iterator OrderIndexAccountID::FindNode(Order* const record)
	{
		auto p = index.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index.end();
	}
	void OrderIndexAccountID::FillCompareRecord(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		Utility::Strcpy(CompareOrder.TradingDay, TradingDay);
		Utility::Strcpy(CompareOrder.AccountID, AccountID);
	}
	
	TradeIndexAccountID::TradeIndexAccountID(TradeTable* tableOwner)
		:table(tableOwner)
	{
	}
	TradeIndexAccountID::iterator TradeIndexAccountID::LowerBound(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(table->sharedMutex);
		return index.lower_bound(&CompareTrade);
	}
	TradeIndexAccountID::iterator TradeIndexAccountID::UpperBound(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(table->sharedMutex);
		return index.upper_bound(&CompareTrade);
	}
	std::pair<TradeIndexAccountID::iterator, TradeIndexAccountID::iterator> TradeIndexAccountID::EqualRange(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		FillCompareRecord(TradingDay, AccountID);
		std::shared_lock guard(table->sharedMutex);
		return index.equal_range(&CompareTrade);
	}
	void TradeIndexAccountID::Insert(Trade* const record)
	{
		index.insert(record);
	}
	void TradeIndexAccountID::Erase(Trade* const record)
	{
		auto it = FindNode(record);
		index.erase(it);
	}
	void TradeIndexAccountID::Update(iterator it)
	{
		auto record = *it;
		index.erase(it);
		index.insert(record);
	}
	bool TradeIndexAccountID::NeedUpdate(const Trade* const oldRecord, const Trade* const newRecord)
	{
		return !(TradeEqualForAccountIDIndex()(oldRecord, newRecord));
	}
	TradeIndexAccountID::iterator TradeIndexAccountID::FindNode(Trade* const record)
	{
		auto p = index.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index.end();
	}
	void TradeIndexAccountID::FillCompareRecord(const DateType& TradingDay, const AccountIDType& AccountID)
	{
		Utility::Strcpy(CompareTrade.TradingDay, TradingDay);
		Utility::Strcpy(CompareTrade.AccountID, AccountID);
	}
	
	AccountLoginSessionIndexSessionID::AccountLoginSessionIndexSessionID(AccountLoginSessionTable* tableOwner)
		:table(tableOwner)
	{
	}
	AccountLoginSessionIndexSessionID::iterator AccountLoginSessionIndexSessionID::LowerBound(const SessionIDType& SessionID)
	{
		FillCompareRecord(SessionID);
		std::shared_lock guard(table->sharedMutex);
		return index.lower_bound(&CompareAccountLoginSession);
	}
	AccountLoginSessionIndexSessionID::iterator AccountLoginSessionIndexSessionID::UpperBound(const SessionIDType& SessionID)
	{
		FillCompareRecord(SessionID);
		std::shared_lock guard(table->sharedMutex);
		return index.upper_bound(&CompareAccountLoginSession);
	}
	std::pair<AccountLoginSessionIndexSessionID::iterator, AccountLoginSessionIndexSessionID::iterator> AccountLoginSessionIndexSessionID::EqualRange(const SessionIDType& SessionID)
	{
		FillCompareRecord(SessionID);
		std::shared_lock guard(table->sharedMutex);
		return index.equal_range(&CompareAccountLoginSession);
	}
	void AccountLoginSessionIndexSessionID::Insert(AccountLoginSession* const record)
	{
		index.insert(record);
	}
	void AccountLoginSessionIndexSessionID::Erase(AccountLoginSession* const record)
	{
		auto it = FindNode(record);
		index.erase(it);
	}
	void AccountLoginSessionIndexSessionID::Update(iterator it)
	{
		auto record = *it;
		index.erase(it);
		index.insert(record);
	}
	bool AccountLoginSessionIndexSessionID::NeedUpdate(const AccountLoginSession* const oldRecord, const AccountLoginSession* const newRecord)
	{
		return !(AccountLoginSessionEqualForSessionIDIndex()(oldRecord, newRecord));
	}
	AccountLoginSessionIndexSessionID::iterator AccountLoginSessionIndexSessionID::FindNode(AccountLoginSession* const record)
	{
		auto p = index.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index.end();
	}
	void AccountLoginSessionIndexSessionID::FillCompareRecord(const SessionIDType& SessionID)
	{
		CompareAccountLoginSession.SessionID = SessionID;
	}
	
	AccountLoginSessionIndexAccountID::AccountLoginSessionIndexAccountID(AccountLoginSessionTable* tableOwner)
		:table(tableOwner)
	{
	}
	AccountLoginSessionIndexAccountID::iterator AccountLoginSessionIndexAccountID::LowerBound(const AccountIDType& AccountID)
	{
		FillCompareRecord(AccountID);
		std::shared_lock guard(table->sharedMutex);
		return index.lower_bound(&CompareAccountLoginSession);
	}
	AccountLoginSessionIndexAccountID::iterator AccountLoginSessionIndexAccountID::UpperBound(const AccountIDType& AccountID)
	{
		FillCompareRecord(AccountID);
		std::shared_lock guard(table->sharedMutex);
		return index.upper_bound(&CompareAccountLoginSession);
	}
	std::pair<AccountLoginSessionIndexAccountID::iterator, AccountLoginSessionIndexAccountID::iterator> AccountLoginSessionIndexAccountID::EqualRange(const AccountIDType& AccountID)
	{
		FillCompareRecord(AccountID);
		std::shared_lock guard(table->sharedMutex);
		return index.equal_range(&CompareAccountLoginSession);
	}
	void AccountLoginSessionIndexAccountID::Insert(AccountLoginSession* const record)
	{
		index.insert(record);
	}
	void AccountLoginSessionIndexAccountID::Erase(AccountLoginSession* const record)
	{
		auto it = FindNode(record);
		index.erase(it);
	}
	void AccountLoginSessionIndexAccountID::Update(iterator it)
	{
		auto record = *it;
		index.erase(it);
		index.insert(record);
	}
	bool AccountLoginSessionIndexAccountID::NeedUpdate(const AccountLoginSession* const oldRecord, const AccountLoginSession* const newRecord)
	{
		return !(AccountLoginSessionEqualForAccountIDIndex()(oldRecord, newRecord));
	}
	AccountLoginSessionIndexAccountID::iterator AccountLoginSessionIndexAccountID::FindNode(AccountLoginSession* const record)
	{
		auto p = index.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index.end();
	}
	void AccountLoginSessionIndexAccountID::FillCompareRecord(const AccountIDType& AccountID)
	{
		Utility::Strcpy(CompareAccountLoginSession.AccountID, AccountID);
	}
	
	PrimaryAccountLoginSessionIndexSessionID::PrimaryAccountLoginSessionIndexSessionID(PrimaryAccountLoginSessionTable* tableOwner)
		:table(tableOwner)
	{
	}
	PrimaryAccountLoginSessionIndexSessionID::iterator PrimaryAccountLoginSessionIndexSessionID::LowerBound(const SessionIDType& SessionID)
	{
		FillCompareRecord(SessionID);
		std::shared_lock guard(table->sharedMutex);
		return index.lower_bound(&ComparePrimaryAccountLoginSession);
	}
	PrimaryAccountLoginSessionIndexSessionID::iterator PrimaryAccountLoginSessionIndexSessionID::UpperBound(const SessionIDType& SessionID)
	{
		FillCompareRecord(SessionID);
		std::shared_lock guard(table->sharedMutex);
		return index.upper_bound(&ComparePrimaryAccountLoginSession);
	}
	std::pair<PrimaryAccountLoginSessionIndexSessionID::iterator, PrimaryAccountLoginSessionIndexSessionID::iterator> PrimaryAccountLoginSessionIndexSessionID::EqualRange(const SessionIDType& SessionID)
	{
		FillCompareRecord(SessionID);
		std::shared_lock guard(table->sharedMutex);
		return index.equal_range(&ComparePrimaryAccountLoginSession);
	}
	void PrimaryAccountLoginSessionIndexSessionID::Insert(PrimaryAccountLoginSession* const record)
	{
		index.insert(record);
	}
	void PrimaryAccountLoginSessionIndexSessionID::Erase(PrimaryAccountLoginSession* const record)
	{
		auto it = FindNode(record);
		index.erase(it);
	}
	void PrimaryAccountLoginSessionIndexSessionID::Update(iterator it)
	{
		auto record = *it;
		index.erase(it);
		index.insert(record);
	}
	bool PrimaryAccountLoginSessionIndexSessionID::NeedUpdate(const PrimaryAccountLoginSession* const oldRecord, const PrimaryAccountLoginSession* const newRecord)
	{
		return !(PrimaryAccountLoginSessionEqualForSessionIDIndex()(oldRecord, newRecord));
	}
	PrimaryAccountLoginSessionIndexSessionID::iterator PrimaryAccountLoginSessionIndexSessionID::FindNode(PrimaryAccountLoginSession* const record)
	{
		auto p = index.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index.end();
	}
	void PrimaryAccountLoginSessionIndexSessionID::FillCompareRecord(const SessionIDType& SessionID)
	{
		ComparePrimaryAccountLoginSession.SessionID = SessionID;
	}
	
	PrimaryAccountLoginSessionIndexPrimaryAccountID::PrimaryAccountLoginSessionIndexPrimaryAccountID(PrimaryAccountLoginSessionTable* tableOwner)
		:table(tableOwner)
	{
	}
	PrimaryAccountLoginSessionIndexPrimaryAccountID::iterator PrimaryAccountLoginSessionIndexPrimaryAccountID::LowerBound(const AccountIDType& PrimaryAccountID)
	{
		FillCompareRecord(PrimaryAccountID);
		std::shared_lock guard(table->sharedMutex);
		return index.lower_bound(&ComparePrimaryAccountLoginSession);
	}
	PrimaryAccountLoginSessionIndexPrimaryAccountID::iterator PrimaryAccountLoginSessionIndexPrimaryAccountID::UpperBound(const AccountIDType& PrimaryAccountID)
	{
		FillCompareRecord(PrimaryAccountID);
		std::shared_lock guard(table->sharedMutex);
		return index.upper_bound(&ComparePrimaryAccountLoginSession);
	}
	std::pair<PrimaryAccountLoginSessionIndexPrimaryAccountID::iterator, PrimaryAccountLoginSessionIndexPrimaryAccountID::iterator> PrimaryAccountLoginSessionIndexPrimaryAccountID::EqualRange(const AccountIDType& PrimaryAccountID)
	{
		FillCompareRecord(PrimaryAccountID);
		std::shared_lock guard(table->sharedMutex);
		return index.equal_range(&ComparePrimaryAccountLoginSession);
	}
	void PrimaryAccountLoginSessionIndexPrimaryAccountID::Insert(PrimaryAccountLoginSession* const record)
	{
		index.insert(record);
	}
	void PrimaryAccountLoginSessionIndexPrimaryAccountID::Erase(PrimaryAccountLoginSession* const record)
	{
		auto it = FindNode(record);
		index.erase(it);
	}
	void PrimaryAccountLoginSessionIndexPrimaryAccountID::Update(iterator it)
	{
		auto record = *it;
		index.erase(it);
		index.insert(record);
	}
	bool PrimaryAccountLoginSessionIndexPrimaryAccountID::NeedUpdate(const PrimaryAccountLoginSession* const oldRecord, const PrimaryAccountLoginSession* const newRecord)
	{
		return !(PrimaryAccountLoginSessionEqualForPrimaryAccountIDIndex()(oldRecord, newRecord));
	}
	PrimaryAccountLoginSessionIndexPrimaryAccountID::iterator PrimaryAccountLoginSessionIndexPrimaryAccountID::FindNode(PrimaryAccountLoginSession* const record)
	{
		auto p = index.equal_range(record);
		for (auto it = p.first; it != p.second; ++it)
		{
			if (*it == record)
			{
				return it;
			}
		}
		return index.end();
	}
	void PrimaryAccountLoginSessionIndexPrimaryAccountID::FillCompareRecord(const AccountIDType& PrimaryAccountID)
	{
		Utility::Strcpy(ComparePrimaryAccountLoginSession.PrimaryAccountID, PrimaryAccountID);
	}
	
}
