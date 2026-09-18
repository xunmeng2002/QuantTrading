// 本文件由 ../Templates/Cpp/Mdb/MdbStructs.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "MdbStructs.h"
#include "MdbIndexes.h"
#include <Spark/TemplateLib/TemplateLib.h>
#include <string>
#include <cstring>

using namespace Spark;
using namespace DbAdapters;
namespace QuantTrading
{
	thread_local char MdbDataStringBuffer[10240];

	static const FieldDescriptor TradingDayFields[] = {
		{"Pk", FieldType::Int32, offsetof(TradingDay, Pk), 0},
		{"CurrTradingDay", FieldType::Char, offsetof(TradingDay, CurrTradingDay), sizeof(TradingDay::CurrTradingDay)},
		{"PreTradingDay", FieldType::Char, offsetof(TradingDay, PreTradingDay), sizeof(TradingDay::PreTradingDay)},
	};
	static const int TradingDayPKIndices[] = { 0 };
	TradingDay* TradingDay::Allocate()
	{
		return ObjectPool<TradingDay>::GetInstance().Allocate();
	}
	void TradingDay::Deallocate()
	{
		ObjectPool<TradingDay>::GetInstance().Deallocate(this);
	}
	const char* TradingDay::GetString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "%d,%s,%s",
			Pk, CurrTradingDay, PreTradingDay);
		return MdbDataStringBuffer;
	}
	const char* TradingDay::GetDebugString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "TradingDay:Pk:[%d], CurrTradingDay:[%s], PreTradingDay:[%s]",
			Pk, CurrTradingDay, PreTradingDay);
		return MdbDataStringBuffer;
	}
	static void DeallocateTradingDay(void* r) { static_cast<TradingDay*>(r)->Deallocate(); }
	const TableSchema& TradingDay::GetSchema()
	{
		static const TableSchema schema = {"TradingDay", TradingDayFields, 3, TradingDayPKIndices, 1, DeallocateTradingDay, nullptr, 0};
		return schema;
	}
	static const FieldDescriptor ExchangeFields[] = {
		{"ExchangeId", FieldType::Char, offsetof(Exchange, ExchangeId), sizeof(Exchange::ExchangeId)},
		{"ExchangeName", FieldType::Char, offsetof(Exchange, ExchangeName), sizeof(Exchange::ExchangeName)},
	};
	static const int ExchangePKIndices[] = { 0 };
	Exchange* Exchange::Allocate()
	{
		return ObjectPool<Exchange>::GetInstance().Allocate();
	}
	void Exchange::Deallocate()
	{
		ObjectPool<Exchange>::GetInstance().Deallocate(this);
	}
	const char* Exchange::GetString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "%s,%s",
			ExchangeId, ExchangeName);
		return MdbDataStringBuffer;
	}
	const char* Exchange::GetDebugString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "Exchange:ExchangeId:[%s], ExchangeName:[%s]",
			ExchangeId, ExchangeName);
		return MdbDataStringBuffer;
	}
	static void DeallocateExchange(void* r) { static_cast<Exchange*>(r)->Deallocate(); }
	const TableSchema& Exchange::GetSchema()
	{
		static const TableSchema schema = {"Exchange", ExchangeFields, 2, ExchangePKIndices, 1, DeallocateExchange, nullptr, 0};
		return schema;
	}
	static const FieldDescriptor ProductFields[] = {
		{"ExchangeId", FieldType::Char, offsetof(Product, ExchangeId), sizeof(Product::ExchangeId)},
		{"ProductId", FieldType::Char, offsetof(Product, ProductId), sizeof(Product::ProductId)},
		{"ProductName", FieldType::Char, offsetof(Product, ProductName), sizeof(Product::ProductName)},
		{"ProductClass", FieldType::Int32, offsetof(Product, ProductClass), 0},
		{"VolumeMultiple", FieldType::Int32, offsetof(Product, VolumeMultiple), 0},
		{"PriceTick", FieldType::Double, offsetof(Product, PriceTick), 0},
		{"MaxMarketOrderVolume", FieldType::Int64, offsetof(Product, MaxMarketOrderVolume), 0},
		{"MinMarketOrderVolume", FieldType::Int64, offsetof(Product, MinMarketOrderVolume), 0},
		{"MaxLimitOrderVolume", FieldType::Int64, offsetof(Product, MaxLimitOrderVolume), 0},
		{"MinLimitOrderVolume", FieldType::Int64, offsetof(Product, MinLimitOrderVolume), 0},
		{"SessionName", FieldType::Char, offsetof(Product, SessionName), sizeof(Product::SessionName)},
	};
	static const int ProductPKIndices[] = { 0, 1 };
	Product* Product::Allocate()
	{
		return ObjectPool<Product>::GetInstance().Allocate();
	}
	void Product::Deallocate()
	{
		ObjectPool<Product>::GetInstance().Deallocate(this);
	}
	const char* Product::GetString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "%s,%s,%s,%d,%d,%f,%lld,%lld,%lld,%lld,%s",
			ExchangeId, ProductId, ProductName, static_cast<int>(ProductClass), VolumeMultiple, PriceTick, MaxMarketOrderVolume, MinMarketOrderVolume, MaxLimitOrderVolume, MinLimitOrderVolume, SessionName);
		return MdbDataStringBuffer;
	}
	const char* Product::GetDebugString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "Product:ExchangeId:[%s], ProductId:[%s], ProductName:[%s], ProductClass:[%d], VolumeMultiple:[%d], PriceTick:[%f], MaxMarketOrderVolume:[%lld], MinMarketOrderVolume:[%lld], MaxLimitOrderVolume:[%lld], MinLimitOrderVolume:[%lld], SessionName:[%s]",
			ExchangeId, ProductId, ProductName, static_cast<int>(ProductClass), VolumeMultiple, PriceTick, MaxMarketOrderVolume, MinMarketOrderVolume, MaxLimitOrderVolume, MinLimitOrderVolume, SessionName);
		return MdbDataStringBuffer;
	}
	static void DeallocateProduct(void* r) { static_cast<Product*>(r)->Deallocate(); }
	const TableSchema& Product::GetSchema()
	{
		static const TableSchema schema = {"Product", ProductFields, 11, ProductPKIndices, 2, DeallocateProduct, nullptr, 0};
		return schema;
	}
	static const FieldDescriptor HotInstrumentFields[] = {
		{"TradingDay", FieldType::Char, offsetof(HotInstrument, TradingDay), sizeof(HotInstrument::TradingDay)},
		{"ExchangeId", FieldType::Char, offsetof(HotInstrument, ExchangeId), sizeof(HotInstrument::ExchangeId)},
		{"ProductId", FieldType::Char, offsetof(HotInstrument, ProductId), sizeof(HotInstrument::ProductId)},
		{"InstrumentId", FieldType::Char, offsetof(HotInstrument, InstrumentId), sizeof(HotInstrument::InstrumentId)},
		{"ProductClass", FieldType::Int32, offsetof(HotInstrument, ProductClass), 0},
		{"Volume", FieldType::Int64, offsetof(HotInstrument, Volume), 0},
		{"MaxVolume", FieldType::Int64, offsetof(HotInstrument, MaxVolume), 0},
		{"Turnover", FieldType::Double, offsetof(HotInstrument, Turnover), 0},
		{"MaxTurnover", FieldType::Double, offsetof(HotInstrument, MaxTurnover), 0},
		{"OpenInterest", FieldType::Double, offsetof(HotInstrument, OpenInterest), 0},
		{"MaxOpenInterest", FieldType::Double, offsetof(HotInstrument, MaxOpenInterest), 0},
		{"Rank", FieldType::Int32, offsetof(HotInstrument, Rank), 0},
	};
	static const int HotInstrumentPKIndices[] = { 0, 1, 2, 11 };
	static const int HotInstrumentIdxTradingDay[] = { 1, 2, 11, 0 };
	static const IndexDefinition HotInstrumentIndices[] = {
		{HotInstrumentIndexTradingDay::IndexID, HotInstrumentIdxTradingDay, 4},
	};
	HotInstrument* HotInstrument::Allocate()
	{
		return ObjectPool<HotInstrument>::GetInstance().Allocate();
	}
	void HotInstrument::Deallocate()
	{
		ObjectPool<HotInstrument>::GetInstance().Deallocate(this);
	}
	const char* HotInstrument::GetString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "%s,%s,%s,%s,%d,%lld,%lld,%f,%f,%f,%f,%d",
			TradingDay, ExchangeId, ProductId, InstrumentId, static_cast<int>(ProductClass), Volume, MaxVolume, Turnover, MaxTurnover, OpenInterest, MaxOpenInterest, Rank);
		return MdbDataStringBuffer;
	}
	const char* HotInstrument::GetDebugString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "HotInstrument:TradingDay:[%s], ExchangeId:[%s], ProductId:[%s], InstrumentId:[%s], ProductClass:[%d], Volume:[%lld], MaxVolume:[%lld], Turnover:[%f], MaxTurnover:[%f], OpenInterest:[%f], MaxOpenInterest:[%f], Rank:[%d]",
			TradingDay, ExchangeId, ProductId, InstrumentId, static_cast<int>(ProductClass), Volume, MaxVolume, Turnover, MaxTurnover, OpenInterest, MaxOpenInterest, Rank);
		return MdbDataStringBuffer;
	}
	static void DeallocateHotInstrument(void* r) { static_cast<HotInstrument*>(r)->Deallocate(); }
	const TableSchema& HotInstrument::GetSchema()
	{
		static const TableSchema schema = {"HotInstrument", HotInstrumentFields, 12, HotInstrumentPKIndices, 4, DeallocateHotInstrument, HotInstrumentIndices, 1};
		return schema;
	}
	static const FieldDescriptor InstrumentFields[] = {
		{"ExchangeId", FieldType::Char, offsetof(Instrument, ExchangeId), sizeof(Instrument::ExchangeId)},
		{"InstrumentId", FieldType::Char, offsetof(Instrument, InstrumentId), sizeof(Instrument::InstrumentId)},
		{"ExchangeInstId", FieldType::Char, offsetof(Instrument, ExchangeInstId), sizeof(Instrument::ExchangeInstId)},
		{"InstrumentName", FieldType::Char, offsetof(Instrument, InstrumentName), sizeof(Instrument::InstrumentName)},
		{"ProductId", FieldType::Char, offsetof(Instrument, ProductId), sizeof(Instrument::ProductId)},
		{"ProductClass", FieldType::Int32, offsetof(Instrument, ProductClass), 0},
		{"InstrumentClass", FieldType::Int32, offsetof(Instrument, InstrumentClass), 0},
		{"Rank", FieldType::Int32, offsetof(Instrument, Rank), 0},
		{"VolumeMultiple", FieldType::Int32, offsetof(Instrument, VolumeMultiple), 0},
		{"PriceTick", FieldType::Double, offsetof(Instrument, PriceTick), 0},
		{"MaxMarketOrderVolume", FieldType::Int64, offsetof(Instrument, MaxMarketOrderVolume), 0},
		{"MinMarketOrderVolume", FieldType::Int64, offsetof(Instrument, MinMarketOrderVolume), 0},
		{"MaxLimitOrderVolume", FieldType::Int64, offsetof(Instrument, MaxLimitOrderVolume), 0},
		{"MinLimitOrderVolume", FieldType::Int64, offsetof(Instrument, MinLimitOrderVolume), 0},
		{"SessionName", FieldType::Char, offsetof(Instrument, SessionName), sizeof(Instrument::SessionName)},
	};
	static const int InstrumentPKIndices[] = { 0, 1 };
	static const int InstrumentIdxExchangeId[] = { 0 };
	static const IndexDefinition InstrumentIndices[] = {
		{InstrumentIndexExchangeId::IndexID, InstrumentIdxExchangeId, 1},
	};
	Instrument* Instrument::Allocate()
	{
		return ObjectPool<Instrument>::GetInstance().Allocate();
	}
	void Instrument::Deallocate()
	{
		ObjectPool<Instrument>::GetInstance().Deallocate(this);
	}
	const char* Instrument::GetString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "%s,%s,%s,%s,%s,%d,%d,%d,%d,%f,%lld,%lld,%lld,%lld,%s",
			ExchangeId, InstrumentId, ExchangeInstId, InstrumentName, ProductId, static_cast<int>(ProductClass), static_cast<int>(InstrumentClass), Rank, VolumeMultiple, PriceTick, MaxMarketOrderVolume, MinMarketOrderVolume, MaxLimitOrderVolume, MinLimitOrderVolume, SessionName);
		return MdbDataStringBuffer;
	}
	const char* Instrument::GetDebugString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "Instrument:ExchangeId:[%s], InstrumentId:[%s], ExchangeInstId:[%s], InstrumentName:[%s], ProductId:[%s], ProductClass:[%d], InstrumentClass:[%d], Rank:[%d], VolumeMultiple:[%d], PriceTick:[%f], MaxMarketOrderVolume:[%lld], MinMarketOrderVolume:[%lld], MaxLimitOrderVolume:[%lld], MinLimitOrderVolume:[%lld], SessionName:[%s]",
			ExchangeId, InstrumentId, ExchangeInstId, InstrumentName, ProductId, static_cast<int>(ProductClass), static_cast<int>(InstrumentClass), Rank, VolumeMultiple, PriceTick, MaxMarketOrderVolume, MinMarketOrderVolume, MaxLimitOrderVolume, MinLimitOrderVolume, SessionName);
		return MdbDataStringBuffer;
	}
	static void DeallocateInstrument(void* r) { static_cast<Instrument*>(r)->Deallocate(); }
	const TableSchema& Instrument::GetSchema()
	{
		static const TableSchema schema = {"Instrument", InstrumentFields, 15, InstrumentPKIndices, 2, DeallocateInstrument, InstrumentIndices, 1};
		return schema;
	}
	static const FieldDescriptor DepthMarketDataFields[] = {
		{"TradingDay", FieldType::Char, offsetof(DepthMarketData, TradingDay), sizeof(DepthMarketData::TradingDay)},
		{"ExchangeId", FieldType::Char, offsetof(DepthMarketData, ExchangeId), sizeof(DepthMarketData::ExchangeId)},
		{"InstrumentId", FieldType::Char, offsetof(DepthMarketData, InstrumentId), sizeof(DepthMarketData::InstrumentId)},
		{"UpdateTs", FieldType::Int64, offsetof(DepthMarketData, UpdateTs), 0},
		{"LastPrice", FieldType::Double, offsetof(DepthMarketData, LastPrice), 0},
		{"PreSettlementPrice", FieldType::Double, offsetof(DepthMarketData, PreSettlementPrice), 0},
		{"PreClosePrice", FieldType::Double, offsetof(DepthMarketData, PreClosePrice), 0},
		{"PreOpenInterest", FieldType::Double, offsetof(DepthMarketData, PreOpenInterest), 0},
		{"OpenPrice", FieldType::Double, offsetof(DepthMarketData, OpenPrice), 0},
		{"HighestPrice", FieldType::Double, offsetof(DepthMarketData, HighestPrice), 0},
		{"LowestPrice", FieldType::Double, offsetof(DepthMarketData, LowestPrice), 0},
		{"ClosePrice", FieldType::Double, offsetof(DepthMarketData, ClosePrice), 0},
		{"CurrVolume", FieldType::Int64, offsetof(DepthMarketData, CurrVolume), 0},
		{"Volume", FieldType::Int64, offsetof(DepthMarketData, Volume), 0},
		{"CurrTurnover", FieldType::Double, offsetof(DepthMarketData, CurrTurnover), 0},
		{"Turnover", FieldType::Double, offsetof(DepthMarketData, Turnover), 0},
		{"OpenInterest", FieldType::Double, offsetof(DepthMarketData, OpenInterest), 0},
		{"SettlementPrice", FieldType::Double, offsetof(DepthMarketData, SettlementPrice), 0},
		{"UpperLimitPrice", FieldType::Double, offsetof(DepthMarketData, UpperLimitPrice), 0},
		{"LowerLimitPrice", FieldType::Double, offsetof(DepthMarketData, LowerLimitPrice), 0},
		{"AveragePrice", FieldType::Double, offsetof(DepthMarketData, AveragePrice), 0},
		{"AskPrice1", FieldType::Double, offsetof(DepthMarketData, AskPrice1), 0},
		{"AskPrice2", FieldType::Double, offsetof(DepthMarketData, AskPrice2), 0},
		{"AskPrice3", FieldType::Double, offsetof(DepthMarketData, AskPrice3), 0},
		{"AskPrice4", FieldType::Double, offsetof(DepthMarketData, AskPrice4), 0},
		{"AskPrice5", FieldType::Double, offsetof(DepthMarketData, AskPrice5), 0},
		{"AskPrice6", FieldType::Double, offsetof(DepthMarketData, AskPrice6), 0},
		{"AskPrice7", FieldType::Double, offsetof(DepthMarketData, AskPrice7), 0},
		{"AskPrice8", FieldType::Double, offsetof(DepthMarketData, AskPrice8), 0},
		{"AskPrice9", FieldType::Double, offsetof(DepthMarketData, AskPrice9), 0},
		{"AskPrice10", FieldType::Double, offsetof(DepthMarketData, AskPrice10), 0},
		{"AskVolume1", FieldType::Int64, offsetof(DepthMarketData, AskVolume1), 0},
		{"AskVolume2", FieldType::Int64, offsetof(DepthMarketData, AskVolume2), 0},
		{"AskVolume3", FieldType::Int64, offsetof(DepthMarketData, AskVolume3), 0},
		{"AskVolume4", FieldType::Int64, offsetof(DepthMarketData, AskVolume4), 0},
		{"AskVolume5", FieldType::Int64, offsetof(DepthMarketData, AskVolume5), 0},
		{"AskVolume6", FieldType::Int64, offsetof(DepthMarketData, AskVolume6), 0},
		{"AskVolume7", FieldType::Int64, offsetof(DepthMarketData, AskVolume7), 0},
		{"AskVolume8", FieldType::Int64, offsetof(DepthMarketData, AskVolume8), 0},
		{"AskVolume9", FieldType::Int64, offsetof(DepthMarketData, AskVolume9), 0},
		{"AskVolume10", FieldType::Int64, offsetof(DepthMarketData, AskVolume10), 0},
		{"BidPrice1", FieldType::Double, offsetof(DepthMarketData, BidPrice1), 0},
		{"BidPrice2", FieldType::Double, offsetof(DepthMarketData, BidPrice2), 0},
		{"BidPrice3", FieldType::Double, offsetof(DepthMarketData, BidPrice3), 0},
		{"BidPrice4", FieldType::Double, offsetof(DepthMarketData, BidPrice4), 0},
		{"BidPrice5", FieldType::Double, offsetof(DepthMarketData, BidPrice5), 0},
		{"BidPrice6", FieldType::Double, offsetof(DepthMarketData, BidPrice6), 0},
		{"BidPrice7", FieldType::Double, offsetof(DepthMarketData, BidPrice7), 0},
		{"BidPrice8", FieldType::Double, offsetof(DepthMarketData, BidPrice8), 0},
		{"BidPrice9", FieldType::Double, offsetof(DepthMarketData, BidPrice9), 0},
		{"BidPrice10", FieldType::Double, offsetof(DepthMarketData, BidPrice10), 0},
		{"BidVolume1", FieldType::Int64, offsetof(DepthMarketData, BidVolume1), 0},
		{"BidVolume2", FieldType::Int64, offsetof(DepthMarketData, BidVolume2), 0},
		{"BidVolume3", FieldType::Int64, offsetof(DepthMarketData, BidVolume3), 0},
		{"BidVolume4", FieldType::Int64, offsetof(DepthMarketData, BidVolume4), 0},
		{"BidVolume5", FieldType::Int64, offsetof(DepthMarketData, BidVolume5), 0},
		{"BidVolume6", FieldType::Int64, offsetof(DepthMarketData, BidVolume6), 0},
		{"BidVolume7", FieldType::Int64, offsetof(DepthMarketData, BidVolume7), 0},
		{"BidVolume8", FieldType::Int64, offsetof(DepthMarketData, BidVolume8), 0},
		{"BidVolume9", FieldType::Int64, offsetof(DepthMarketData, BidVolume9), 0},
		{"BidVolume10", FieldType::Int64, offsetof(DepthMarketData, BidVolume10), 0},
	};
	static const int DepthMarketDataPKIndices[] = { 0, 1, 2 };
	DepthMarketData* DepthMarketData::Allocate()
	{
		return ObjectPool<DepthMarketData>::GetInstance().Allocate();
	}
	void DepthMarketData::Deallocate()
	{
		ObjectPool<DepthMarketData>::GetInstance().Deallocate(this);
	}
	const char* DepthMarketData::GetString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "%s,%s,%s,%lld,%f,%f,%f,%f,%f,%f,%f,%f,%lld,%lld,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld",
			TradingDay, ExchangeId, InstrumentId, UpdateTs, LastPrice, PreSettlementPrice, PreClosePrice, PreOpenInterest, OpenPrice, HighestPrice, LowestPrice, ClosePrice, CurrVolume, Volume, CurrTurnover, Turnover, OpenInterest, SettlementPrice, UpperLimitPrice, LowerLimitPrice, AveragePrice, AskPrice1, AskPrice2, AskPrice3, AskPrice4, AskPrice5, AskPrice6, AskPrice7, AskPrice8, AskPrice9, AskPrice10, AskVolume1, AskVolume2, AskVolume3, AskVolume4, AskVolume5, AskVolume6, AskVolume7, AskVolume8, AskVolume9, AskVolume10, BidPrice1, BidPrice2, BidPrice3, BidPrice4, BidPrice5, BidPrice6, BidPrice7, BidPrice8, BidPrice9, BidPrice10, BidVolume1, BidVolume2, BidVolume3, BidVolume4, BidVolume5, BidVolume6, BidVolume7, BidVolume8, BidVolume9, BidVolume10);
		return MdbDataStringBuffer;
	}
	const char* DepthMarketData::GetDebugString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "DepthMarketData:TradingDay:[%s], ExchangeId:[%s], InstrumentId:[%s], UpdateTs:[%lld], LastPrice:[%f], PreSettlementPrice:[%f], PreClosePrice:[%f], PreOpenInterest:[%f], OpenPrice:[%f], HighestPrice:[%f], LowestPrice:[%f], ClosePrice:[%f], CurrVolume:[%lld], Volume:[%lld], CurrTurnover:[%f], Turnover:[%f], OpenInterest:[%f], SettlementPrice:[%f], UpperLimitPrice:[%f], LowerLimitPrice:[%f], AveragePrice:[%f], AskPrice1:[%f], AskPrice2:[%f], AskPrice3:[%f], AskPrice4:[%f], AskPrice5:[%f], AskPrice6:[%f], AskPrice7:[%f], AskPrice8:[%f], AskPrice9:[%f], AskPrice10:[%f], AskVolume1:[%lld], AskVolume2:[%lld], AskVolume3:[%lld], AskVolume4:[%lld], AskVolume5:[%lld], AskVolume6:[%lld], AskVolume7:[%lld], AskVolume8:[%lld], AskVolume9:[%lld], AskVolume10:[%lld], BidPrice1:[%f], BidPrice2:[%f], BidPrice3:[%f], BidPrice4:[%f], BidPrice5:[%f], BidPrice6:[%f], BidPrice7:[%f], BidPrice8:[%f], BidPrice9:[%f], BidPrice10:[%f], BidVolume1:[%lld], BidVolume2:[%lld], BidVolume3:[%lld], BidVolume4:[%lld], BidVolume5:[%lld], BidVolume6:[%lld], BidVolume7:[%lld], BidVolume8:[%lld], BidVolume9:[%lld], BidVolume10:[%lld]",
			TradingDay, ExchangeId, InstrumentId, UpdateTs, LastPrice, PreSettlementPrice, PreClosePrice, PreOpenInterest, OpenPrice, HighestPrice, LowestPrice, ClosePrice, CurrVolume, Volume, CurrTurnover, Turnover, OpenInterest, SettlementPrice, UpperLimitPrice, LowerLimitPrice, AveragePrice, AskPrice1, AskPrice2, AskPrice3, AskPrice4, AskPrice5, AskPrice6, AskPrice7, AskPrice8, AskPrice9, AskPrice10, AskVolume1, AskVolume2, AskVolume3, AskVolume4, AskVolume5, AskVolume6, AskVolume7, AskVolume8, AskVolume9, AskVolume10, BidPrice1, BidPrice2, BidPrice3, BidPrice4, BidPrice5, BidPrice6, BidPrice7, BidPrice8, BidPrice9, BidPrice10, BidVolume1, BidVolume2, BidVolume3, BidVolume4, BidVolume5, BidVolume6, BidVolume7, BidVolume8, BidVolume9, BidVolume10);
		return MdbDataStringBuffer;
	}
	static void DeallocateDepthMarketData(void* r) { static_cast<DepthMarketData*>(r)->Deallocate(); }
	const TableSchema& DepthMarketData::GetSchema()
	{
		static const TableSchema schema = {"DepthMarketData", DepthMarketDataFields, 61, DepthMarketDataPKIndices, 3, DeallocateDepthMarketData, nullptr, 0};
		return schema;
	}
	static const FieldDescriptor BarMarketDataFields[] = {
		{"TradingDay", FieldType::Char, offsetof(BarMarketData, TradingDay), sizeof(BarMarketData::TradingDay)},
		{"ExchangeId", FieldType::Char, offsetof(BarMarketData, ExchangeId), sizeof(BarMarketData::ExchangeId)},
		{"InstrumentId", FieldType::Char, offsetof(BarMarketData, InstrumentId), sizeof(BarMarketData::InstrumentId)},
		{"BarPreces", FieldType::Int32, offsetof(BarMarketData, BarPreces), 0},
		{"BarPeriod", FieldType::Int32, offsetof(BarMarketData, BarPeriod), 0},
		{"BarTime", FieldType::Int64, offsetof(BarMarketData, BarTime), 0},
		{"UpdateTs", FieldType::Int64, offsetof(BarMarketData, UpdateTs), 0},
		{"PreSettlementPrice", FieldType::Double, offsetof(BarMarketData, PreSettlementPrice), 0},
		{"PreClosePrice", FieldType::Double, offsetof(BarMarketData, PreClosePrice), 0},
		{"HighestPrice", FieldType::Double, offsetof(BarMarketData, HighestPrice), 0},
		{"LowestPrice", FieldType::Double, offsetof(BarMarketData, LowestPrice), 0},
		{"Open", FieldType::Double, offsetof(BarMarketData, Open), 0},
		{"High", FieldType::Double, offsetof(BarMarketData, High), 0},
		{"Low", FieldType::Double, offsetof(BarMarketData, Low), 0},
		{"Close", FieldType::Double, offsetof(BarMarketData, Close), 0},
		{"CurrVolume", FieldType::Int64, offsetof(BarMarketData, CurrVolume), 0},
		{"Volume", FieldType::Int64, offsetof(BarMarketData, Volume), 0},
		{"CurrTurnover", FieldType::Double, offsetof(BarMarketData, CurrTurnover), 0},
		{"Turnover", FieldType::Double, offsetof(BarMarketData, Turnover), 0},
		{"OpenInterest", FieldType::Double, offsetof(BarMarketData, OpenInterest), 0},
	};
	static const int BarMarketDataPKIndices[] = { 0, 1, 2, 3, 4, 5 };
	BarMarketData* BarMarketData::Allocate()
	{
		return ObjectPool<BarMarketData>::GetInstance().Allocate();
	}
	void BarMarketData::Deallocate()
	{
		ObjectPool<BarMarketData>::GetInstance().Deallocate(this);
	}
	const char* BarMarketData::GetString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "%s,%s,%s,%d,%d,%lld,%lld,%f,%f,%f,%f,%f,%f,%f,%f,%lld,%lld,%f,%f,%f",
			TradingDay, ExchangeId, InstrumentId, static_cast<int>(BarPreces), BarPeriod, BarTime, UpdateTs, PreSettlementPrice, PreClosePrice, HighestPrice, LowestPrice, Open, High, Low, Close, CurrVolume, Volume, CurrTurnover, Turnover, OpenInterest);
		return MdbDataStringBuffer;
	}
	const char* BarMarketData::GetDebugString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "BarMarketData:TradingDay:[%s], ExchangeId:[%s], InstrumentId:[%s], BarPreces:[%d], BarPeriod:[%d], BarTime:[%lld], UpdateTs:[%lld], PreSettlementPrice:[%f], PreClosePrice:[%f], HighestPrice:[%f], LowestPrice:[%f], Open:[%f], High:[%f], Low:[%f], Close:[%f], CurrVolume:[%lld], Volume:[%lld], CurrTurnover:[%f], Turnover:[%f], OpenInterest:[%f]",
			TradingDay, ExchangeId, InstrumentId, static_cast<int>(BarPreces), BarPeriod, BarTime, UpdateTs, PreSettlementPrice, PreClosePrice, HighestPrice, LowestPrice, Open, High, Low, Close, CurrVolume, Volume, CurrTurnover, Turnover, OpenInterest);
		return MdbDataStringBuffer;
	}
	static void DeallocateBarMarketData(void* r) { static_cast<BarMarketData*>(r)->Deallocate(); }
	const TableSchema& BarMarketData::GetSchema()
	{
		static const TableSchema schema = {"BarMarketData", BarMarketDataFields, 20, BarMarketDataPKIndices, 6, DeallocateBarMarketData, nullptr, 0};
		return schema;
	}
	static const FieldDescriptor MdSubscribeFields[] = {
		{"ExchangeId", FieldType::Char, offsetof(MdSubscribe, ExchangeId), sizeof(MdSubscribe::ExchangeId)},
		{"InstrumentId", FieldType::Char, offsetof(MdSubscribe, InstrumentId), sizeof(MdSubscribe::InstrumentId)},
		{"RealInstrumentId", FieldType::Char, offsetof(MdSubscribe, RealInstrumentId), sizeof(MdSubscribe::RealInstrumentId)},
		{"ProductId", FieldType::Char, offsetof(MdSubscribe, ProductId), sizeof(MdSubscribe::ProductId)},
		{"ProductClass", FieldType::Int32, offsetof(MdSubscribe, ProductClass), 0},
		{"StartTradingDay", FieldType::Char, offsetof(MdSubscribe, StartTradingDay), sizeof(MdSubscribe::StartTradingDay)},
		{"EndTradingDay", FieldType::Char, offsetof(MdSubscribe, EndTradingDay), sizeof(MdSubscribe::EndTradingDay)},
	};
	static const int MdSubscribePKIndices[] = { 0, 1, 5 };
	MdSubscribe* MdSubscribe::Allocate()
	{
		return ObjectPool<MdSubscribe>::GetInstance().Allocate();
	}
	void MdSubscribe::Deallocate()
	{
		ObjectPool<MdSubscribe>::GetInstance().Deallocate(this);
	}
	const char* MdSubscribe::GetString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "%s,%s,%s,%s,%d,%s,%s",
			ExchangeId, InstrumentId, RealInstrumentId, ProductId, static_cast<int>(ProductClass), StartTradingDay, EndTradingDay);
		return MdbDataStringBuffer;
	}
	const char* MdSubscribe::GetDebugString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "MdSubscribe:ExchangeId:[%s], InstrumentId:[%s], RealInstrumentId:[%s], ProductId:[%s], ProductClass:[%d], StartTradingDay:[%s], EndTradingDay:[%s]",
			ExchangeId, InstrumentId, RealInstrumentId, ProductId, static_cast<int>(ProductClass), StartTradingDay, EndTradingDay);
		return MdbDataStringBuffer;
	}
	static void DeallocateMdSubscribe(void* r) { static_cast<MdSubscribe*>(r)->Deallocate(); }
	const TableSchema& MdSubscribe::GetSchema()
	{
		static const TableSchema schema = {"MdSubscribe", MdSubscribeFields, 7, MdSubscribePKIndices, 3, DeallocateMdSubscribe, nullptr, 0};
		return schema;
	}
	static const FieldDescriptor MdUserFields[] = {
		{"MdUserId", FieldType::Char, offsetof(MdUser, MdUserId), sizeof(MdUser::MdUserId)},
		{"MdUserName", FieldType::Char, offsetof(MdUser, MdUserName), sizeof(MdUser::MdUserName)},
		{"Password", FieldType::Char, offsetof(MdUser, Password), sizeof(MdUser::Password)},
	};
	static const int MdUserPKIndices[] = { 0 };
	MdUser* MdUser::Allocate()
	{
		return ObjectPool<MdUser>::GetInstance().Allocate();
	}
	void MdUser::Deallocate()
	{
		ObjectPool<MdUser>::GetInstance().Deallocate(this);
	}
	const char* MdUser::GetString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "%s,%s,%s",
			MdUserId, MdUserName, Password);
		return MdbDataStringBuffer;
	}
	const char* MdUser::GetDebugString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "MdUser:MdUserId:[%s], MdUserName:[%s], Password:[%s]",
			MdUserId, MdUserName, Password);
		return MdbDataStringBuffer;
	}
	static void DeallocateMdUser(void* r) { static_cast<MdUser*>(r)->Deallocate(); }
	const TableSchema& MdUser::GetSchema()
	{
		static const TableSchema schema = {"MdUser", MdUserFields, 3, MdUserPKIndices, 1, DeallocateMdUser, nullptr, 0};
		return schema;
	}
	static const FieldDescriptor MdUserLoginSessionFields[] = {
		{"MdUserId", FieldType::Char, offsetof(MdUserLoginSession, MdUserId), sizeof(MdUserLoginSession::MdUserId)},
		{"SessionId", FieldType::Int64, offsetof(MdUserLoginSession, SessionId), 0},
		{"IpAddress", FieldType::Char, offsetof(MdUserLoginSession, IpAddress), sizeof(MdUserLoginSession::IpAddress)},
	};
	static const int MdUserLoginSessionPKIndices[] = { 0, 1 };
	static const int MdUserLoginSessionIdxSessionId[] = { 1 };
	static const int MdUserLoginSessionIdxMdUserId[] = { 0 };
	static const IndexDefinition MdUserLoginSessionIndices[] = {
		{MdUserLoginSessionIndexSessionId::IndexID, MdUserLoginSessionIdxSessionId, 1},
		{MdUserLoginSessionIndexMdUserId::IndexID, MdUserLoginSessionIdxMdUserId, 1},
	};
	MdUserLoginSession* MdUserLoginSession::Allocate()
	{
		return ObjectPool<MdUserLoginSession>::GetInstance().Allocate();
	}
	void MdUserLoginSession::Deallocate()
	{
		ObjectPool<MdUserLoginSession>::GetInstance().Deallocate(this);
	}
	const char* MdUserLoginSession::GetString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "%s,%lld,%s",
			MdUserId, SessionId, IpAddress);
		return MdbDataStringBuffer;
	}
	const char* MdUserLoginSession::GetDebugString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "MdUserLoginSession:MdUserId:[%s], SessionId:[%lld], IpAddress:[%s]",
			MdUserId, SessionId, IpAddress);
		return MdbDataStringBuffer;
	}
	static void DeallocateMdUserLoginSession(void* r) { static_cast<MdUserLoginSession*>(r)->Deallocate(); }
	const TableSchema& MdUserLoginSession::GetSchema()
	{
		static const TableSchema schema = {"MdUserLoginSession", MdUserLoginSessionFields, 3, MdUserLoginSessionPKIndices, 2, DeallocateMdUserLoginSession, MdUserLoginSessionIndices, 2};
		return schema;
	}
	static const FieldDescriptor PrimaryAccountFields[] = {
		{"PrimaryAccountId", FieldType::Char, offsetof(PrimaryAccount, PrimaryAccountId), sizeof(PrimaryAccount::PrimaryAccountId)},
		{"PrimaryAccountName", FieldType::Char, offsetof(PrimaryAccount, PrimaryAccountName), sizeof(PrimaryAccount::PrimaryAccountName)},
		{"AccountClass", FieldType::Int32, offsetof(PrimaryAccount, AccountClass), 0},
		{"Password", FieldType::Char, offsetof(PrimaryAccount, Password), sizeof(PrimaryAccount::Password)},
		{"OfferId", FieldType::Int32, offsetof(PrimaryAccount, OfferId), 0},
		{"IsAllowLogin", FieldType::Bool, offsetof(PrimaryAccount, IsAllowLogin), 0},
		{"IsSimulateAccount", FieldType::Bool, offsetof(PrimaryAccount, IsSimulateAccount), 0},
		{"LoginStatus", FieldType::Int32, offsetof(PrimaryAccount, LoginStatus), 0},
		{"InitStatus", FieldType::Int32, offsetof(PrimaryAccount, InitStatus), 0},
	};
	static const int PrimaryAccountPKIndices[] = { 0 };
	static const int PrimaryAccountIdxOfferId[] = { 4 };
	static const IndexDefinition PrimaryAccountIndices[] = {
		{PrimaryAccountIndexOfferId::IndexID, PrimaryAccountIdxOfferId, 1},
	};
	PrimaryAccount* PrimaryAccount::Allocate()
	{
		return ObjectPool<PrimaryAccount>::GetInstance().Allocate();
	}
	void PrimaryAccount::Deallocate()
	{
		ObjectPool<PrimaryAccount>::GetInstance().Deallocate(this);
	}
	const char* PrimaryAccount::GetString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "%s,%s,%d,%s,%d,%d,%d,%d,%d",
			PrimaryAccountId, PrimaryAccountName, static_cast<int>(AccountClass), Password, OfferId, IsAllowLogin, IsSimulateAccount, static_cast<int>(LoginStatus), static_cast<int>(InitStatus));
		return MdbDataStringBuffer;
	}
	const char* PrimaryAccount::GetDebugString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "PrimaryAccount:PrimaryAccountId:[%s], PrimaryAccountName:[%s], AccountClass:[%d], Password:[%s], OfferId:[%d], IsAllowLogin:[%d], IsSimulateAccount:[%d], LoginStatus:[%d], InitStatus:[%d]",
			PrimaryAccountId, PrimaryAccountName, static_cast<int>(AccountClass), Password, OfferId, IsAllowLogin, IsSimulateAccount, static_cast<int>(LoginStatus), static_cast<int>(InitStatus));
		return MdbDataStringBuffer;
	}
	static void DeallocatePrimaryAccount(void* r) { static_cast<PrimaryAccount*>(r)->Deallocate(); }
	const TableSchema& PrimaryAccount::GetSchema()
	{
		static const TableSchema schema = {"PrimaryAccount", PrimaryAccountFields, 9, PrimaryAccountPKIndices, 1, DeallocatePrimaryAccount, PrimaryAccountIndices, 1};
		return schema;
	}
	static const FieldDescriptor AccountFields[] = {
		{"AccountId", FieldType::Char, offsetof(Account, AccountId), sizeof(Account::AccountId)},
		{"AccountName", FieldType::Char, offsetof(Account, AccountName), sizeof(Account::AccountName)},
		{"AccountType", FieldType::Int32, offsetof(Account, AccountType), 0},
		{"AccountStatus", FieldType::Int32, offsetof(Account, AccountStatus), 0},
		{"Password", FieldType::Char, offsetof(Account, Password), sizeof(Account::Password)},
		{"TradeGroupId", FieldType::Int32, offsetof(Account, TradeGroupId), 0},
		{"RiskGroupId", FieldType::Int32, offsetof(Account, RiskGroupId), 0},
		{"CommissionGroupId", FieldType::Int32, offsetof(Account, CommissionGroupId), 0},
	};
	static const int AccountPKIndices[] = { 0 };
	Account* Account::Allocate()
	{
		return ObjectPool<Account>::GetInstance().Allocate();
	}
	void Account::Deallocate()
	{
		ObjectPool<Account>::GetInstance().Deallocate(this);
	}
	const char* Account::GetString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "%s,%s,%d,%d,%s,%d,%d,%d",
			AccountId, AccountName, static_cast<int>(AccountType), static_cast<int>(AccountStatus), Password, TradeGroupId, RiskGroupId, CommissionGroupId);
		return MdbDataStringBuffer;
	}
	const char* Account::GetDebugString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "Account:AccountId:[%s], AccountName:[%s], AccountType:[%d], AccountStatus:[%d], Password:[%s], TradeGroupId:[%d], RiskGroupId:[%d], CommissionGroupId:[%d]",
			AccountId, AccountName, static_cast<int>(AccountType), static_cast<int>(AccountStatus), Password, TradeGroupId, RiskGroupId, CommissionGroupId);
		return MdbDataStringBuffer;
	}
	static void DeallocateAccount(void* r) { static_cast<Account*>(r)->Deallocate(); }
	const TableSchema& Account::GetSchema()
	{
		static const TableSchema schema = {"Account", AccountFields, 8, AccountPKIndices, 1, DeallocateAccount, nullptr, 0};
		return schema;
	}
	static const FieldDescriptor CapitalFields[] = {
		{"TradingDay", FieldType::Char, offsetof(Capital, TradingDay), sizeof(Capital::TradingDay)},
		{"AccountId", FieldType::Char, offsetof(Capital, AccountId), sizeof(Capital::AccountId)},
		{"AccountType", FieldType::Int32, offsetof(Capital, AccountType), 0},
		{"Balance", FieldType::Double, offsetof(Capital, Balance), 0},
		{"PreBalance", FieldType::Double, offsetof(Capital, PreBalance), 0},
		{"Available", FieldType::Double, offsetof(Capital, Available), 0},
		{"MarketValue", FieldType::Double, offsetof(Capital, MarketValue), 0},
		{"CashIn", FieldType::Double, offsetof(Capital, CashIn), 0},
		{"CashOut", FieldType::Double, offsetof(Capital, CashOut), 0},
		{"Margin", FieldType::Double, offsetof(Capital, Margin), 0},
		{"Commission", FieldType::Double, offsetof(Capital, Commission), 0},
		{"FrozenCash", FieldType::Double, offsetof(Capital, FrozenCash), 0},
		{"FrozenMargin", FieldType::Double, offsetof(Capital, FrozenMargin), 0},
		{"FrozenCommission", FieldType::Double, offsetof(Capital, FrozenCommission), 0},
		{"CloseProfitByDate", FieldType::Double, offsetof(Capital, CloseProfitByDate), 0},
		{"CloseProfitByTrade", FieldType::Double, offsetof(Capital, CloseProfitByTrade), 0},
		{"PositionProfitByDate", FieldType::Double, offsetof(Capital, PositionProfitByDate), 0},
		{"PositionProfitByTrade", FieldType::Double, offsetof(Capital, PositionProfitByTrade), 0},
		{"Deposit", FieldType::Double, offsetof(Capital, Deposit), 0},
		{"Withdraw", FieldType::Double, offsetof(Capital, Withdraw), 0},
		{"StampTax", FieldType::Double, offsetof(Capital, StampTax), 0},
		{"TransferFee", FieldType::Double, offsetof(Capital, TransferFee), 0},
	};
	static const int CapitalPKIndices[] = { 0, 1 };
	static const int CapitalIdxTradingDay[] = { 0 };
	static const IndexDefinition CapitalIndices[] = {
		{CapitalIndexTradingDay::IndexID, CapitalIdxTradingDay, 1},
	};
	Capital* Capital::Allocate()
	{
		return ObjectPool<Capital>::GetInstance().Allocate();
	}
	void Capital::Deallocate()
	{
		ObjectPool<Capital>::GetInstance().Deallocate(this);
	}
	const char* Capital::GetString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "%s,%s,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
			TradingDay, AccountId, static_cast<int>(AccountType), Balance, PreBalance, Available, MarketValue, CashIn, CashOut, Margin, Commission, FrozenCash, FrozenMargin, FrozenCommission, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, Deposit, Withdraw, StampTax, TransferFee);
		return MdbDataStringBuffer;
	}
	const char* Capital::GetDebugString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "Capital:TradingDay:[%s], AccountId:[%s], AccountType:[%d], Balance:[%f], PreBalance:[%f], Available:[%f], MarketValue:[%f], CashIn:[%f], CashOut:[%f], Margin:[%f], Commission:[%f], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f], CloseProfitByDate:[%f], CloseProfitByTrade:[%f], PositionProfitByDate:[%f], PositionProfitByTrade:[%f], Deposit:[%f], Withdraw:[%f], StampTax:[%f], TransferFee:[%f]",
			TradingDay, AccountId, static_cast<int>(AccountType), Balance, PreBalance, Available, MarketValue, CashIn, CashOut, Margin, Commission, FrozenCash, FrozenMargin, FrozenCommission, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, Deposit, Withdraw, StampTax, TransferFee);
		return MdbDataStringBuffer;
	}
	static void DeallocateCapital(void* r) { static_cast<Capital*>(r)->Deallocate(); }
	const TableSchema& Capital::GetSchema()
	{
		static const TableSchema schema = {"Capital", CapitalFields, 22, CapitalPKIndices, 2, DeallocateCapital, CapitalIndices, 1};
		return schema;
	}
	static const FieldDescriptor PositionFields[] = {
		{"TradingDay", FieldType::Char, offsetof(Position, TradingDay), sizeof(Position::TradingDay)},
		{"AccountId", FieldType::Char, offsetof(Position, AccountId), sizeof(Position::AccountId)},
		{"AccountType", FieldType::Int32, offsetof(Position, AccountType), 0},
		{"ExchangeId", FieldType::Char, offsetof(Position, ExchangeId), sizeof(Position::ExchangeId)},
		{"InstrumentId", FieldType::Char, offsetof(Position, InstrumentId), sizeof(Position::InstrumentId)},
		{"ProductClass", FieldType::Int32, offsetof(Position, ProductClass), 0},
		{"PosiDirection", FieldType::Int32, offsetof(Position, PosiDirection), 0},
		{"TotalPosition", FieldType::Int64, offsetof(Position, TotalPosition), 0},
		{"PositionFrozen", FieldType::Int64, offsetof(Position, PositionFrozen), 0},
		{"TodayPosition", FieldType::Int64, offsetof(Position, TodayPosition), 0},
		{"MarketValue", FieldType::Double, offsetof(Position, MarketValue), 0},
		{"CashIn", FieldType::Double, offsetof(Position, CashIn), 0},
		{"CashOut", FieldType::Double, offsetof(Position, CashOut), 0},
		{"Margin", FieldType::Double, offsetof(Position, Margin), 0},
		{"Commission", FieldType::Double, offsetof(Position, Commission), 0},
		{"FrozenCash", FieldType::Double, offsetof(Position, FrozenCash), 0},
		{"FrozenMargin", FieldType::Double, offsetof(Position, FrozenMargin), 0},
		{"FrozenCommission", FieldType::Double, offsetof(Position, FrozenCommission), 0},
		{"VolumeMultiple", FieldType::Int32, offsetof(Position, VolumeMultiple), 0},
		{"CloseProfitByDate", FieldType::Double, offsetof(Position, CloseProfitByDate), 0},
		{"CloseProfitByTrade", FieldType::Double, offsetof(Position, CloseProfitByTrade), 0},
		{"PositionProfitByDate", FieldType::Double, offsetof(Position, PositionProfitByDate), 0},
		{"PositionProfitByTrade", FieldType::Double, offsetof(Position, PositionProfitByTrade), 0},
		{"SettlementPrice", FieldType::Double, offsetof(Position, SettlementPrice), 0},
		{"PreSettlementPrice", FieldType::Double, offsetof(Position, PreSettlementPrice), 0},
		{"StampTax", FieldType::Double, offsetof(Position, StampTax), 0},
		{"TransferFee", FieldType::Double, offsetof(Position, TransferFee), 0},
	};
	static const int PositionPKIndices[] = { 0, 1, 3, 4, 6 };
	static const int PositionIdxAccount[] = { 0, 1 };
	static const int PositionIdxTradingDay[] = { 0 };
	static const IndexDefinition PositionIndices[] = {
		{PositionIndexAccount::IndexID, PositionIdxAccount, 2},
		{PositionIndexTradingDay::IndexID, PositionIdxTradingDay, 1},
	};
	Position* Position::Allocate()
	{
		return ObjectPool<Position>::GetInstance().Allocate();
	}
	void Position::Deallocate()
	{
		ObjectPool<Position>::GetInstance().Deallocate(this);
	}
	const char* Position::GetString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "%s,%s,%d,%s,%s,%d,%d,%lld,%lld,%lld,%f,%f,%f,%f,%f,%f,%f,%f,%d,%f,%f,%f,%f,%f,%f,%f,%f",
			TradingDay, AccountId, static_cast<int>(AccountType), ExchangeId, InstrumentId, static_cast<int>(ProductClass), static_cast<int>(PosiDirection), TotalPosition, PositionFrozen, TodayPosition, MarketValue, CashIn, CashOut, Margin, Commission, FrozenCash, FrozenMargin, FrozenCommission, VolumeMultiple, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, SettlementPrice, PreSettlementPrice, StampTax, TransferFee);
		return MdbDataStringBuffer;
	}
	const char* Position::GetDebugString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "Position:TradingDay:[%s], AccountId:[%s], AccountType:[%d], ExchangeId:[%s], InstrumentId:[%s], ProductClass:[%d], PosiDirection:[%d], TotalPosition:[%lld], PositionFrozen:[%lld], TodayPosition:[%lld], MarketValue:[%f], CashIn:[%f], CashOut:[%f], Margin:[%f], Commission:[%f], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f], VolumeMultiple:[%d], CloseProfitByDate:[%f], CloseProfitByTrade:[%f], PositionProfitByDate:[%f], PositionProfitByTrade:[%f], SettlementPrice:[%f], PreSettlementPrice:[%f], StampTax:[%f], TransferFee:[%f]",
			TradingDay, AccountId, static_cast<int>(AccountType), ExchangeId, InstrumentId, static_cast<int>(ProductClass), static_cast<int>(PosiDirection), TotalPosition, PositionFrozen, TodayPosition, MarketValue, CashIn, CashOut, Margin, Commission, FrozenCash, FrozenMargin, FrozenCommission, VolumeMultiple, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, SettlementPrice, PreSettlementPrice, StampTax, TransferFee);
		return MdbDataStringBuffer;
	}
	static void DeallocatePosition(void* r) { static_cast<Position*>(r)->Deallocate(); }
	const TableSchema& Position::GetSchema()
	{
		static const TableSchema schema = {"Position", PositionFields, 27, PositionPKIndices, 5, DeallocatePosition, PositionIndices, 2};
		return schema;
	}
	static const FieldDescriptor PositionDetailFields[] = {
		{"TradingDay", FieldType::Char, offsetof(PositionDetail, TradingDay), sizeof(PositionDetail::TradingDay)},
		{"AccountId", FieldType::Char, offsetof(PositionDetail, AccountId), sizeof(PositionDetail::AccountId)},
		{"AccountType", FieldType::Int32, offsetof(PositionDetail, AccountType), 0},
		{"ExchangeId", FieldType::Char, offsetof(PositionDetail, ExchangeId), sizeof(PositionDetail::ExchangeId)},
		{"InstrumentId", FieldType::Char, offsetof(PositionDetail, InstrumentId), sizeof(PositionDetail::InstrumentId)},
		{"ProductClass", FieldType::Int32, offsetof(PositionDetail, ProductClass), 0},
		{"PosiDirection", FieldType::Int32, offsetof(PositionDetail, PosiDirection), 0},
		{"OpenDate", FieldType::Char, offsetof(PositionDetail, OpenDate), sizeof(PositionDetail::OpenDate)},
		{"TradeId", FieldType::Char, offsetof(PositionDetail, TradeId), sizeof(PositionDetail::TradeId)},
		{"Volume", FieldType::Int64, offsetof(PositionDetail, Volume), 0},
		{"OpenPrice", FieldType::Double, offsetof(PositionDetail, OpenPrice), 0},
		{"MarketValue", FieldType::Double, offsetof(PositionDetail, MarketValue), 0},
		{"CashIn", FieldType::Double, offsetof(PositionDetail, CashIn), 0},
		{"CashOut", FieldType::Double, offsetof(PositionDetail, CashOut), 0},
		{"Margin", FieldType::Double, offsetof(PositionDetail, Margin), 0},
		{"Commission", FieldType::Double, offsetof(PositionDetail, Commission), 0},
		{"VolumeMultiple", FieldType::Int32, offsetof(PositionDetail, VolumeMultiple), 0},
		{"CloseProfitByDate", FieldType::Double, offsetof(PositionDetail, CloseProfitByDate), 0},
		{"CloseProfitByTrade", FieldType::Double, offsetof(PositionDetail, CloseProfitByTrade), 0},
		{"PositionProfitByDate", FieldType::Double, offsetof(PositionDetail, PositionProfitByDate), 0},
		{"PositionProfitByTrade", FieldType::Double, offsetof(PositionDetail, PositionProfitByTrade), 0},
		{"SettlementPrice", FieldType::Double, offsetof(PositionDetail, SettlementPrice), 0},
		{"PreSettlementPrice", FieldType::Double, offsetof(PositionDetail, PreSettlementPrice), 0},
		{"CloseVolume", FieldType::Int64, offsetof(PositionDetail, CloseVolume), 0},
		{"CloseAmount", FieldType::Double, offsetof(PositionDetail, CloseAmount), 0},
		{"StampTax", FieldType::Double, offsetof(PositionDetail, StampTax), 0},
		{"TransferFee", FieldType::Double, offsetof(PositionDetail, TransferFee), 0},
	};
	static const int PositionDetailPKIndices[] = { 0, 1, 3, 4, 6, 7, 8 };
	static const int PositionDetailIdxTradeMatch[] = { 0, 1, 3, 4, 6 };
	static const int PositionDetailIdxTradingDay[] = { 0 };
	static const IndexDefinition PositionDetailIndices[] = {
		{PositionDetailIndexTradeMatch::IndexID, PositionDetailIdxTradeMatch, 5},
		{PositionDetailIndexTradingDay::IndexID, PositionDetailIdxTradingDay, 1},
	};
	PositionDetail* PositionDetail::Allocate()
	{
		return ObjectPool<PositionDetail>::GetInstance().Allocate();
	}
	void PositionDetail::Deallocate()
	{
		ObjectPool<PositionDetail>::GetInstance().Deallocate(this);
	}
	const char* PositionDetail::GetString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "%s,%s,%d,%s,%s,%d,%d,%s,%s,%lld,%f,%f,%f,%f,%f,%f,%d,%f,%f,%f,%f,%f,%f,%lld,%f,%f,%f",
			TradingDay, AccountId, static_cast<int>(AccountType), ExchangeId, InstrumentId, static_cast<int>(ProductClass), static_cast<int>(PosiDirection), OpenDate, TradeId, Volume, OpenPrice, MarketValue, CashIn, CashOut, Margin, Commission, VolumeMultiple, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, SettlementPrice, PreSettlementPrice, CloseVolume, CloseAmount, StampTax, TransferFee);
		return MdbDataStringBuffer;
	}
	const char* PositionDetail::GetDebugString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "PositionDetail:TradingDay:[%s], AccountId:[%s], AccountType:[%d], ExchangeId:[%s], InstrumentId:[%s], ProductClass:[%d], PosiDirection:[%d], OpenDate:[%s], TradeId:[%s], Volume:[%lld], OpenPrice:[%f], MarketValue:[%f], CashIn:[%f], CashOut:[%f], Margin:[%f], Commission:[%f], VolumeMultiple:[%d], CloseProfitByDate:[%f], CloseProfitByTrade:[%f], PositionProfitByDate:[%f], PositionProfitByTrade:[%f], SettlementPrice:[%f], PreSettlementPrice:[%f], CloseVolume:[%lld], CloseAmount:[%f], StampTax:[%f], TransferFee:[%f]",
			TradingDay, AccountId, static_cast<int>(AccountType), ExchangeId, InstrumentId, static_cast<int>(ProductClass), static_cast<int>(PosiDirection), OpenDate, TradeId, Volume, OpenPrice, MarketValue, CashIn, CashOut, Margin, Commission, VolumeMultiple, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, SettlementPrice, PreSettlementPrice, CloseVolume, CloseAmount, StampTax, TransferFee);
		return MdbDataStringBuffer;
	}
	static void DeallocatePositionDetail(void* r) { static_cast<PositionDetail*>(r)->Deallocate(); }
	const TableSchema& PositionDetail::GetSchema()
	{
		static const TableSchema schema = {"PositionDetail", PositionDetailFields, 27, PositionDetailPKIndices, 7, DeallocatePositionDetail, PositionDetailIndices, 2};
		return schema;
	}
	static const FieldDescriptor OrderFields[] = {
		{"TradingDay", FieldType::Char, offsetof(Order, TradingDay), sizeof(Order::TradingDay)},
		{"AccountId", FieldType::Char, offsetof(Order, AccountId), sizeof(Order::AccountId)},
		{"AccountType", FieldType::Int32, offsetof(Order, AccountType), 0},
		{"ExchangeId", FieldType::Char, offsetof(Order, ExchangeId), sizeof(Order::ExchangeId)},
		{"InstrumentId", FieldType::Char, offsetof(Order, InstrumentId), sizeof(Order::InstrumentId)},
		{"ProductClass", FieldType::Int32, offsetof(Order, ProductClass), 0},
		{"OrderId", FieldType::Int32, offsetof(Order, OrderId), 0},
		{"OrderSysId", FieldType::Char, offsetof(Order, OrderSysId), sizeof(Order::OrderSysId)},
		{"Direction", FieldType::Int32, offsetof(Order, Direction), 0},
		{"OffsetFlag", FieldType::Int32, offsetof(Order, OffsetFlag), 0},
		{"OrderPriceType", FieldType::Int32, offsetof(Order, OrderPriceType), 0},
		{"Price", FieldType::Double, offsetof(Order, Price), 0},
		{"Volume", FieldType::Int64, offsetof(Order, Volume), 0},
		{"VolumeTotal", FieldType::Int64, offsetof(Order, VolumeTotal), 0},
		{"VolumeTraded", FieldType::Int64, offsetof(Order, VolumeTraded), 0},
		{"VolumeMultiple", FieldType::Int32, offsetof(Order, VolumeMultiple), 0},
		{"OrderStatus", FieldType::Int32, offsetof(Order, OrderStatus), 0},
		{"OrderDate", FieldType::Char, offsetof(Order, OrderDate), sizeof(Order::OrderDate)},
		{"OrderTime", FieldType::Char, offsetof(Order, OrderTime), sizeof(Order::OrderTime)},
		{"CancelDate", FieldType::Char, offsetof(Order, CancelDate), sizeof(Order::CancelDate)},
		{"CancelTime", FieldType::Char, offsetof(Order, CancelTime), sizeof(Order::CancelTime)},
		{"SessionId", FieldType::Int64, offsetof(Order, SessionId), 0},
		{"ClientOrderId", FieldType::Int32, offsetof(Order, ClientOrderId), 0},
		{"RequestId", FieldType::Int32, offsetof(Order, RequestId), 0},
		{"OfferId", FieldType::Int32, offsetof(Order, OfferId), 0},
		{"TradeGroupId", FieldType::Int32, offsetof(Order, TradeGroupId), 0},
		{"RiskGroupId", FieldType::Int32, offsetof(Order, RiskGroupId), 0},
		{"CommissionGroupId", FieldType::Int32, offsetof(Order, CommissionGroupId), 0},
		{"FrozenCash", FieldType::Double, offsetof(Order, FrozenCash), 0},
		{"FrozenMargin", FieldType::Double, offsetof(Order, FrozenMargin), 0},
		{"FrozenCommission", FieldType::Double, offsetof(Order, FrozenCommission), 0},
		{"RebuildMark", FieldType::Bool, offsetof(Order, RebuildMark), 0},
		{"IsForceClose", FieldType::Bool, offsetof(Order, IsForceClose), 0},
	};
	static const int OrderPKIndices[] = { 0, 1, 3, 4, 6 };
	static const int OrderIdxAccountId[] = { 0, 1 };
	static const IndexDefinition OrderIndices[] = {
		{OrderIndexAccountId::IndexID, OrderIdxAccountId, 2},
	};
	Order* Order::Allocate()
	{
		return ObjectPool<Order>::GetInstance().Allocate();
	}
	void Order::Deallocate()
	{
		ObjectPool<Order>::GetInstance().Deallocate(this);
	}
	const char* Order::GetString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "%s,%s,%d,%s,%s,%d,%d,%s,%d,%d,%d,%f,%lld,%lld,%lld,%d,%d,%s,%s,%s,%s,%lld,%d,%d,%d,%d,%d,%d,%f,%f,%f,%d,%d",
			TradingDay, AccountId, static_cast<int>(AccountType), ExchangeId, InstrumentId, static_cast<int>(ProductClass), OrderId, OrderSysId, static_cast<int>(Direction), static_cast<int>(OffsetFlag), static_cast<int>(OrderPriceType), Price, Volume, VolumeTotal, VolumeTraded, VolumeMultiple, static_cast<int>(OrderStatus), OrderDate, OrderTime, CancelDate, CancelTime, SessionId, ClientOrderId, RequestId, OfferId, TradeGroupId, RiskGroupId, CommissionGroupId, FrozenCash, FrozenMargin, FrozenCommission, RebuildMark, IsForceClose);
		return MdbDataStringBuffer;
	}
	const char* Order::GetDebugString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "Order:TradingDay:[%s], AccountId:[%s], AccountType:[%d], ExchangeId:[%s], InstrumentId:[%s], ProductClass:[%d], OrderId:[%d], OrderSysId:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], VolumeTotal:[%lld], VolumeTraded:[%lld], VolumeMultiple:[%d], OrderStatus:[%d], OrderDate:[%s], OrderTime:[%s], CancelDate:[%s], CancelTime:[%s], SessionId:[%lld], ClientOrderId:[%d], RequestId:[%d], OfferId:[%d], TradeGroupId:[%d], RiskGroupId:[%d], CommissionGroupId:[%d], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f], RebuildMark:[%d], IsForceClose:[%d]",
			TradingDay, AccountId, static_cast<int>(AccountType), ExchangeId, InstrumentId, static_cast<int>(ProductClass), OrderId, OrderSysId, static_cast<int>(Direction), static_cast<int>(OffsetFlag), static_cast<int>(OrderPriceType), Price, Volume, VolumeTotal, VolumeTraded, VolumeMultiple, static_cast<int>(OrderStatus), OrderDate, OrderTime, CancelDate, CancelTime, SessionId, ClientOrderId, RequestId, OfferId, TradeGroupId, RiskGroupId, CommissionGroupId, FrozenCash, FrozenMargin, FrozenCommission, RebuildMark, IsForceClose);
		return MdbDataStringBuffer;
	}
	static void DeallocateOrder(void* r) { static_cast<Order*>(r)->Deallocate(); }
	const TableSchema& Order::GetSchema()
	{
		static const TableSchema schema = {"Order", OrderFields, 33, OrderPKIndices, 5, DeallocateOrder, OrderIndices, 1};
		return schema;
	}
	static const FieldDescriptor TradeFields[] = {
		{"TradingDay", FieldType::Char, offsetof(Trade, TradingDay), sizeof(Trade::TradingDay)},
		{"AccountId", FieldType::Char, offsetof(Trade, AccountId), sizeof(Trade::AccountId)},
		{"AccountType", FieldType::Int32, offsetof(Trade, AccountType), 0},
		{"ExchangeId", FieldType::Char, offsetof(Trade, ExchangeId), sizeof(Trade::ExchangeId)},
		{"InstrumentId", FieldType::Char, offsetof(Trade, InstrumentId), sizeof(Trade::InstrumentId)},
		{"ProductClass", FieldType::Int32, offsetof(Trade, ProductClass), 0},
		{"OrderId", FieldType::Int32, offsetof(Trade, OrderId), 0},
		{"OrderSysId", FieldType::Char, offsetof(Trade, OrderSysId), sizeof(Trade::OrderSysId)},
		{"TradeId", FieldType::Char, offsetof(Trade, TradeId), sizeof(Trade::TradeId)},
		{"Direction", FieldType::Int32, offsetof(Trade, Direction), 0},
		{"OffsetFlag", FieldType::Int32, offsetof(Trade, OffsetFlag), 0},
		{"Price", FieldType::Double, offsetof(Trade, Price), 0},
		{"Volume", FieldType::Int64, offsetof(Trade, Volume), 0},
		{"VolumeMultiple", FieldType::Int32, offsetof(Trade, VolumeMultiple), 0},
		{"TradeAmount", FieldType::Double, offsetof(Trade, TradeAmount), 0},
		{"Commission", FieldType::Double, offsetof(Trade, Commission), 0},
		{"TradeDate", FieldType::Char, offsetof(Trade, TradeDate), sizeof(Trade::TradeDate)},
		{"TradeTime", FieldType::Char, offsetof(Trade, TradeTime), sizeof(Trade::TradeTime)},
		{"StampTax", FieldType::Double, offsetof(Trade, StampTax), 0},
		{"TransferFee", FieldType::Double, offsetof(Trade, TransferFee), 0},
	};
	static const int TradePKIndices[] = { 0, 3, 8, 9 };
	static const int TradeIdxAccountId[] = { 0, 1 };
	static const IndexDefinition TradeIndices[] = {
		{TradeIndexAccountId::IndexID, TradeIdxAccountId, 2},
	};
	Trade* Trade::Allocate()
	{
		return ObjectPool<Trade>::GetInstance().Allocate();
	}
	void Trade::Deallocate()
	{
		ObjectPool<Trade>::GetInstance().Deallocate(this);
	}
	const char* Trade::GetString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "%s,%s,%d,%s,%s,%d,%d,%s,%s,%d,%d,%f,%lld,%d,%f,%f,%s,%s,%f,%f",
			TradingDay, AccountId, static_cast<int>(AccountType), ExchangeId, InstrumentId, static_cast<int>(ProductClass), OrderId, OrderSysId, TradeId, static_cast<int>(Direction), static_cast<int>(OffsetFlag), Price, Volume, VolumeMultiple, TradeAmount, Commission, TradeDate, TradeTime, StampTax, TransferFee);
		return MdbDataStringBuffer;
	}
	const char* Trade::GetDebugString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "Trade:TradingDay:[%s], AccountId:[%s], AccountType:[%d], ExchangeId:[%s], InstrumentId:[%s], ProductClass:[%d], OrderId:[%d], OrderSysId:[%s], TradeId:[%s], Direction:[%d], OffsetFlag:[%d], Price:[%f], Volume:[%lld], VolumeMultiple:[%d], TradeAmount:[%f], Commission:[%f], TradeDate:[%s], TradeTime:[%s], StampTax:[%f], TransferFee:[%f]",
			TradingDay, AccountId, static_cast<int>(AccountType), ExchangeId, InstrumentId, static_cast<int>(ProductClass), OrderId, OrderSysId, TradeId, static_cast<int>(Direction), static_cast<int>(OffsetFlag), Price, Volume, VolumeMultiple, TradeAmount, Commission, TradeDate, TradeTime, StampTax, TransferFee);
		return MdbDataStringBuffer;
	}
	static void DeallocateTrade(void* r) { static_cast<Trade*>(r)->Deallocate(); }
	const TableSchema& Trade::GetSchema()
	{
		static const TableSchema schema = {"Trade", TradeFields, 20, TradePKIndices, 4, DeallocateTrade, TradeIndices, 1};
		return schema;
	}
	static const FieldDescriptor AccountLoginSessionFields[] = {
		{"AccountId", FieldType::Char, offsetof(AccountLoginSession, AccountId), sizeof(AccountLoginSession::AccountId)},
		{"SessionId", FieldType::Int64, offsetof(AccountLoginSession, SessionId), 0},
		{"IpAddress", FieldType::Char, offsetof(AccountLoginSession, IpAddress), sizeof(AccountLoginSession::IpAddress)},
	};
	static const int AccountLoginSessionPKIndices[] = { 0, 1 };
	static const int AccountLoginSessionIdxSessionId[] = { 1 };
	static const int AccountLoginSessionIdxAccountId[] = { 0 };
	static const IndexDefinition AccountLoginSessionIndices[] = {
		{AccountLoginSessionIndexSessionId::IndexID, AccountLoginSessionIdxSessionId, 1},
		{AccountLoginSessionIndexAccountId::IndexID, AccountLoginSessionIdxAccountId, 1},
	};
	AccountLoginSession* AccountLoginSession::Allocate()
	{
		return ObjectPool<AccountLoginSession>::GetInstance().Allocate();
	}
	void AccountLoginSession::Deallocate()
	{
		ObjectPool<AccountLoginSession>::GetInstance().Deallocate(this);
	}
	const char* AccountLoginSession::GetString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "%s,%lld,%s",
			AccountId, SessionId, IpAddress);
		return MdbDataStringBuffer;
	}
	const char* AccountLoginSession::GetDebugString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "AccountLoginSession:AccountId:[%s], SessionId:[%lld], IpAddress:[%s]",
			AccountId, SessionId, IpAddress);
		return MdbDataStringBuffer;
	}
	static void DeallocateAccountLoginSession(void* r) { static_cast<AccountLoginSession*>(r)->Deallocate(); }
	const TableSchema& AccountLoginSession::GetSchema()
	{
		static const TableSchema schema = {"AccountLoginSession", AccountLoginSessionFields, 3, AccountLoginSessionPKIndices, 2, DeallocateAccountLoginSession, AccountLoginSessionIndices, 2};
		return schema;
	}
	static const FieldDescriptor PrimaryAccountLoginSessionFields[] = {
		{"PrimaryAccountId", FieldType::Char, offsetof(PrimaryAccountLoginSession, PrimaryAccountId), sizeof(PrimaryAccountLoginSession::PrimaryAccountId)},
		{"SessionId", FieldType::Int64, offsetof(PrimaryAccountLoginSession, SessionId), 0},
		{"IpAddress", FieldType::Char, offsetof(PrimaryAccountLoginSession, IpAddress), sizeof(PrimaryAccountLoginSession::IpAddress)},
	};
	static const int PrimaryAccountLoginSessionPKIndices[] = { 0, 1 };
	static const int PrimaryAccountLoginSessionIdxSessionId[] = { 1 };
	static const int PrimaryAccountLoginSessionIdxPrimaryAccountId[] = { 0 };
	static const IndexDefinition PrimaryAccountLoginSessionIndices[] = {
		{PrimaryAccountLoginSessionIndexSessionId::IndexID, PrimaryAccountLoginSessionIdxSessionId, 1},
		{PrimaryAccountLoginSessionIndexPrimaryAccountId::IndexID, PrimaryAccountLoginSessionIdxPrimaryAccountId, 1},
	};
	PrimaryAccountLoginSession* PrimaryAccountLoginSession::Allocate()
	{
		return ObjectPool<PrimaryAccountLoginSession>::GetInstance().Allocate();
	}
	void PrimaryAccountLoginSession::Deallocate()
	{
		ObjectPool<PrimaryAccountLoginSession>::GetInstance().Deallocate(this);
	}
	const char* PrimaryAccountLoginSession::GetString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "%s,%lld,%s",
			PrimaryAccountId, SessionId, IpAddress);
		return MdbDataStringBuffer;
	}
	const char* PrimaryAccountLoginSession::GetDebugString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "PrimaryAccountLoginSession:PrimaryAccountId:[%s], SessionId:[%lld], IpAddress:[%s]",
			PrimaryAccountId, SessionId, IpAddress);
		return MdbDataStringBuffer;
	}
	static void DeallocatePrimaryAccountLoginSession(void* r) { static_cast<PrimaryAccountLoginSession*>(r)->Deallocate(); }
	const TableSchema& PrimaryAccountLoginSession::GetSchema()
	{
		static const TableSchema schema = {"PrimaryAccountLoginSession", PrimaryAccountLoginSessionFields, 3, PrimaryAccountLoginSessionPKIndices, 2, DeallocatePrimaryAccountLoginSession, PrimaryAccountLoginSessionIndices, 2};
		return schema;
	}
	static const FieldDescriptor CommissionGroupFields[] = {
		{"CommissionGroupId", FieldType::Int32, offsetof(CommissionGroup, CommissionGroupId), 0},
		{"CommissionGroupName", FieldType::Char, offsetof(CommissionGroup, CommissionGroupName), sizeof(CommissionGroup::CommissionGroupName)},
	};
	static const int CommissionGroupPKIndices[] = { 0 };
	CommissionGroup* CommissionGroup::Allocate()
	{
		return ObjectPool<CommissionGroup>::GetInstance().Allocate();
	}
	void CommissionGroup::Deallocate()
	{
		ObjectPool<CommissionGroup>::GetInstance().Deallocate(this);
	}
	const char* CommissionGroup::GetString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "%d,%s",
			CommissionGroupId, CommissionGroupName);
		return MdbDataStringBuffer;
	}
	const char* CommissionGroup::GetDebugString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "CommissionGroup:CommissionGroupId:[%d], CommissionGroupName:[%s]",
			CommissionGroupId, CommissionGroupName);
		return MdbDataStringBuffer;
	}
	static void DeallocateCommissionGroup(void* r) { static_cast<CommissionGroup*>(r)->Deallocate(); }
	const TableSchema& CommissionGroup::GetSchema()
	{
		static const TableSchema schema = {"CommissionGroup", CommissionGroupFields, 2, CommissionGroupPKIndices, 1, DeallocateCommissionGroup, nullptr, 0};
		return schema;
	}
	static const FieldDescriptor BaseCommissionFields[] = {
		{"CommissionGroupId", FieldType::Int32, offsetof(BaseCommission, CommissionGroupId), 0},
		{"ExchangeId", FieldType::Char, offsetof(BaseCommission, ExchangeId), sizeof(BaseCommission::ExchangeId)},
		{"InstrumentId", FieldType::Char, offsetof(BaseCommission, InstrumentId), sizeof(BaseCommission::InstrumentId)},
		{"Direction", FieldType::Int32, offsetof(BaseCommission, Direction), 0},
		{"OpenByMoney", FieldType::Double, offsetof(BaseCommission, OpenByMoney), 0},
		{"CloseByMoney", FieldType::Double, offsetof(BaseCommission, CloseByMoney), 0},
		{"OpenByVolume", FieldType::Double, offsetof(BaseCommission, OpenByVolume), 0},
		{"CloseByVolume", FieldType::Double, offsetof(BaseCommission, CloseByVolume), 0},
		{"OpenStampTaxByMoney", FieldType::Double, offsetof(BaseCommission, OpenStampTaxByMoney), 0},
		{"CloseStampTaxByMoney", FieldType::Double, offsetof(BaseCommission, CloseStampTaxByMoney), 0},
		{"OpenTransferFeeByMoney", FieldType::Double, offsetof(BaseCommission, OpenTransferFeeByMoney), 0},
		{"CloseTransferFeeByMoney", FieldType::Double, offsetof(BaseCommission, CloseTransferFeeByMoney), 0},
		{"MinCommission", FieldType::Double, offsetof(BaseCommission, MinCommission), 0},
		{"MaxCommission", FieldType::Double, offsetof(BaseCommission, MaxCommission), 0},
	};
	static const int BaseCommissionPKIndices[] = { 0, 1, 2, 3 };
	BaseCommission* BaseCommission::Allocate()
	{
		return ObjectPool<BaseCommission>::GetInstance().Allocate();
	}
	void BaseCommission::Deallocate()
	{
		ObjectPool<BaseCommission>::GetInstance().Deallocate(this);
	}
	const char* BaseCommission::GetString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "%d,%s,%s,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
			CommissionGroupId, ExchangeId, InstrumentId, static_cast<int>(Direction), OpenByMoney, CloseByMoney, OpenByVolume, CloseByVolume, OpenStampTaxByMoney, CloseStampTaxByMoney, OpenTransferFeeByMoney, CloseTransferFeeByMoney, MinCommission, MaxCommission);
		return MdbDataStringBuffer;
	}
	const char* BaseCommission::GetDebugString() const
	{
		snprintf(MdbDataStringBuffer, sizeof(MdbDataStringBuffer), "BaseCommission:CommissionGroupId:[%d], ExchangeId:[%s], InstrumentId:[%s], Direction:[%d], OpenByMoney:[%f], CloseByMoney:[%f], OpenByVolume:[%f], CloseByVolume:[%f], OpenStampTaxByMoney:[%f], CloseStampTaxByMoney:[%f], OpenTransferFeeByMoney:[%f], CloseTransferFeeByMoney:[%f], MinCommission:[%f], MaxCommission:[%f]",
			CommissionGroupId, ExchangeId, InstrumentId, static_cast<int>(Direction), OpenByMoney, CloseByMoney, OpenByVolume, CloseByVolume, OpenStampTaxByMoney, CloseStampTaxByMoney, OpenTransferFeeByMoney, CloseTransferFeeByMoney, MinCommission, MaxCommission);
		return MdbDataStringBuffer;
	}
	static void DeallocateBaseCommission(void* r) { static_cast<BaseCommission*>(r)->Deallocate(); }
	const TableSchema& BaseCommission::GetSchema()
	{
		static const TableSchema schema = {"BaseCommission", BaseCommissionFields, 14, BaseCommissionPKIndices, 4, DeallocateBaseCommission, nullptr, 0};
		return schema;
	}

	thread_local TradingDay CompareTradingDay;
	thread_local Exchange CompareExchange;
	thread_local Product CompareProduct;
	thread_local HotInstrument CompareHotInstrument;
	thread_local Instrument CompareInstrument;
	thread_local DepthMarketData CompareDepthMarketData;
	thread_local BarMarketData CompareBarMarketData;
	thread_local MdSubscribe CompareMdSubscribe;
	thread_local MdUser CompareMdUser;
	thread_local MdUserLoginSession CompareMdUserLoginSession;
	thread_local PrimaryAccount ComparePrimaryAccount;
	thread_local Account CompareAccount;
	thread_local Capital CompareCapital;
	thread_local Position ComparePosition;
	thread_local PositionDetail ComparePositionDetail;
	thread_local Order CompareOrder;
	thread_local Trade CompareTrade;
	thread_local AccountLoginSession CompareAccountLoginSession;
	thread_local PrimaryAccountLoginSession ComparePrimaryAccountLoginSession;
	thread_local CommissionGroup CompareCommissionGroup;
	thread_local BaseCommission CompareBaseCommission;

}
