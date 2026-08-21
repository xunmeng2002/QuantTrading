#include "MdbStructs.h"
#include "MdbIndexes.h"
#include <Spark/TemplateLib/TemplateLib.h>
#include <string>
#include <cstring>

using namespace spark;
using namespace dbadapters;
namespace mdb
{
	thread_local char t_MdbDataStringBuffer[10240];

	static const FieldDescriptor TradingDayFields[] = {
		{"PK", FieldType::Int, offsetof(TradingDay, PK), 0},
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
		sprintf(t_MdbDataStringBuffer, "%d,%s,%s",
			PK, CurrTradingDay, PreTradingDay);
		return t_MdbDataStringBuffer;
	}
	int TradingDay::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%d','%s','%s'),",
			PK, CurrTradingDay, PreTradingDay);
	}
	const char* TradingDay::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "TradingDay:PK:[%d], CurrTradingDay:[%s], PreTradingDay:[%s]",
			PK, CurrTradingDay, PreTradingDay);
		return t_MdbDataStringBuffer;
	}
	static void DeallocateTradingDay(void* r) { static_cast<TradingDay*>(r)->Deallocate(); }
	const TableSchema& TradingDay::GetSchema()
	{
		static const TableSchema schema = {"t_TradingDay", TradingDayFields, 3, TradingDayPKIndices, 1, DeallocateTradingDay, nullptr, 0};
		return schema;
	}
	static const FieldDescriptor ExchangeFields[] = {
		{"ExchangeID", FieldType::Char, offsetof(Exchange, ExchangeID), sizeof(Exchange::ExchangeID)},
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
		sprintf(t_MdbDataStringBuffer, "%s,%s",
			ExchangeID, ExchangeName);
		return t_MdbDataStringBuffer;
	}
	int Exchange::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s'),",
			ExchangeID, ExchangeName);
	}
	const char* Exchange::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "Exchange:ExchangeID:[%s], ExchangeName:[%s]",
			ExchangeID, ExchangeName);
		return t_MdbDataStringBuffer;
	}
	static void DeallocateExchange(void* r) { static_cast<Exchange*>(r)->Deallocate(); }
	const TableSchema& Exchange::GetSchema()
	{
		static const TableSchema schema = {"t_Exchange", ExchangeFields, 2, ExchangePKIndices, 1, DeallocateExchange, nullptr, 0};
		return schema;
	}
	static const FieldDescriptor ProductFields[] = {
		{"ExchangeID", FieldType::Char, offsetof(Product, ExchangeID), sizeof(Product::ExchangeID)},
		{"ProductID", FieldType::Char, offsetof(Product, ProductID), sizeof(Product::ProductID)},
		{"ProductName", FieldType::Char, offsetof(Product, ProductName), sizeof(Product::ProductName)},
		{"ProductClass", FieldType::Int, offsetof(Product, ProductClass), 0},
		{"VolumeMultiple", FieldType::Int, offsetof(Product, VolumeMultiple), 0},
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
		sprintf(t_MdbDataStringBuffer, "%s,%s,%s,%d,%d,%f,%lld,%lld,%lld,%lld,%s",
			ExchangeID, ProductID, ProductName, (int)ProductClass, VolumeMultiple, PriceTick, MaxMarketOrderVolume, MinMarketOrderVolume, MaxLimitOrderVolume, MinLimitOrderVolume, SessionName);
		return t_MdbDataStringBuffer;
	}
	int Product::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%s','%d','%d','%f','%lld','%lld','%lld','%lld','%s'),",
			ExchangeID, ProductID, ProductName, (int)ProductClass, VolumeMultiple, PriceTick, MaxMarketOrderVolume, MinMarketOrderVolume, MaxLimitOrderVolume, MinLimitOrderVolume, SessionName);
	}
	const char* Product::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "Product:ExchangeID:[%s], ProductID:[%s], ProductName:[%s], ProductClass:[%d], VolumeMultiple:[%d], PriceTick:[%f], MaxMarketOrderVolume:[%lld], MinMarketOrderVolume:[%lld], MaxLimitOrderVolume:[%lld], MinLimitOrderVolume:[%lld], SessionName:[%s]",
			ExchangeID, ProductID, ProductName, (int)ProductClass, VolumeMultiple, PriceTick, MaxMarketOrderVolume, MinMarketOrderVolume, MaxLimitOrderVolume, MinLimitOrderVolume, SessionName);
		return t_MdbDataStringBuffer;
	}
	static void DeallocateProduct(void* r) { static_cast<Product*>(r)->Deallocate(); }
	const TableSchema& Product::GetSchema()
	{
		static const TableSchema schema = {"t_Product", ProductFields, 11, ProductPKIndices, 2, DeallocateProduct, nullptr, 0};
		return schema;
	}
	static const FieldDescriptor HotInstrumentFields[] = {
		{"TradingDay", FieldType::Char, offsetof(HotInstrument, TradingDay), sizeof(HotInstrument::TradingDay)},
		{"ExchangeID", FieldType::Char, offsetof(HotInstrument, ExchangeID), sizeof(HotInstrument::ExchangeID)},
		{"ProductID", FieldType::Char, offsetof(HotInstrument, ProductID), sizeof(HotInstrument::ProductID)},
		{"InstrumentID", FieldType::Char, offsetof(HotInstrument, InstrumentID), sizeof(HotInstrument::InstrumentID)},
		{"ProductClass", FieldType::Int, offsetof(HotInstrument, ProductClass), 0},
		{"Volume", FieldType::Int64, offsetof(HotInstrument, Volume), 0},
		{"MaxVolume", FieldType::Int64, offsetof(HotInstrument, MaxVolume), 0},
		{"Turnover", FieldType::Double, offsetof(HotInstrument, Turnover), 0},
		{"MaxTurnover", FieldType::Double, offsetof(HotInstrument, MaxTurnover), 0},
		{"OpenInterest", FieldType::Double, offsetof(HotInstrument, OpenInterest), 0},
		{"MaxOpenInterest", FieldType::Double, offsetof(HotInstrument, MaxOpenInterest), 0},
		{"Rank", FieldType::Int, offsetof(HotInstrument, Rank), 0},
	};
	static const int HotInstrumentPKIndices[] = { 0, 1, 2, 11 };
	static const int kHotInstrumentIdxTradingDay[] = { 1, 2, 11, 0 };
	static const IndexDefinition HotInstrumentIndices[] = {
		{HotInstrumentIndexTradingDay::IndexID, kHotInstrumentIdxTradingDay, 4},
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
		sprintf(t_MdbDataStringBuffer, "%s,%s,%s,%s,%d,%lld,%lld,%f,%f,%f,%f,%d",
			TradingDay, ExchangeID, ProductID, InstrumentID, (int)ProductClass, Volume, MaxVolume, Turnover, MaxTurnover, OpenInterest, MaxOpenInterest, Rank);
		return t_MdbDataStringBuffer;
	}
	int HotInstrument::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%s','%s','%d','%lld','%lld','%f','%f','%f','%f','%d'),",
			TradingDay, ExchangeID, ProductID, InstrumentID, (int)ProductClass, Volume, MaxVolume, Turnover, MaxTurnover, OpenInterest, MaxOpenInterest, Rank);
	}
	const char* HotInstrument::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "HotInstrument:TradingDay:[%s], ExchangeID:[%s], ProductID:[%s], InstrumentID:[%s], ProductClass:[%d], Volume:[%lld], MaxVolume:[%lld], Turnover:[%f], MaxTurnover:[%f], OpenInterest:[%f], MaxOpenInterest:[%f], Rank:[%d]",
			TradingDay, ExchangeID, ProductID, InstrumentID, (int)ProductClass, Volume, MaxVolume, Turnover, MaxTurnover, OpenInterest, MaxOpenInterest, Rank);
		return t_MdbDataStringBuffer;
	}
	static void DeallocateHotInstrument(void* r) { static_cast<HotInstrument*>(r)->Deallocate(); }
	const TableSchema& HotInstrument::GetSchema()
	{
		static const TableSchema schema = {"t_HotInstrument", HotInstrumentFields, 12, HotInstrumentPKIndices, 4, DeallocateHotInstrument, HotInstrumentIndices, 1};
		return schema;
	}
	static const FieldDescriptor InstrumentFields[] = {
		{"ExchangeID", FieldType::Char, offsetof(Instrument, ExchangeID), sizeof(Instrument::ExchangeID)},
		{"InstrumentID", FieldType::Char, offsetof(Instrument, InstrumentID), sizeof(Instrument::InstrumentID)},
		{"ExchangeInstID", FieldType::Char, offsetof(Instrument, ExchangeInstID), sizeof(Instrument::ExchangeInstID)},
		{"InstrumentName", FieldType::Char, offsetof(Instrument, InstrumentName), sizeof(Instrument::InstrumentName)},
		{"ProductID", FieldType::Char, offsetof(Instrument, ProductID), sizeof(Instrument::ProductID)},
		{"ProductClass", FieldType::Int, offsetof(Instrument, ProductClass), 0},
		{"InstrumentClass", FieldType::Int, offsetof(Instrument, InstrumentClass), 0},
		{"Rank", FieldType::Int, offsetof(Instrument, Rank), 0},
		{"VolumeMultiple", FieldType::Int, offsetof(Instrument, VolumeMultiple), 0},
		{"PriceTick", FieldType::Double, offsetof(Instrument, PriceTick), 0},
		{"MaxMarketOrderVolume", FieldType::Int64, offsetof(Instrument, MaxMarketOrderVolume), 0},
		{"MinMarketOrderVolume", FieldType::Int64, offsetof(Instrument, MinMarketOrderVolume), 0},
		{"MaxLimitOrderVolume", FieldType::Int64, offsetof(Instrument, MaxLimitOrderVolume), 0},
		{"MinLimitOrderVolume", FieldType::Int64, offsetof(Instrument, MinLimitOrderVolume), 0},
		{"SessionName", FieldType::Char, offsetof(Instrument, SessionName), sizeof(Instrument::SessionName)},
	};
	static const int InstrumentPKIndices[] = { 0, 1 };
	static const int kInstrumentIdxExchangeID[] = { 0 };
	static const IndexDefinition InstrumentIndices[] = {
		{InstrumentIndexExchangeID::IndexID, kInstrumentIdxExchangeID, 1},
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
		sprintf(t_MdbDataStringBuffer, "%s,%s,%s,%s,%s,%d,%d,%d,%d,%f,%lld,%lld,%lld,%lld,%s",
			ExchangeID, InstrumentID, ExchangeInstID, InstrumentName, ProductID, (int)ProductClass, (int)InstrumentClass, Rank, VolumeMultiple, PriceTick, MaxMarketOrderVolume, MinMarketOrderVolume, MaxLimitOrderVolume, MinLimitOrderVolume, SessionName);
		return t_MdbDataStringBuffer;
	}
	int Instrument::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%s','%s','%s','%d','%d','%d','%d','%f','%lld','%lld','%lld','%lld','%s'),",
			ExchangeID, InstrumentID, ExchangeInstID, InstrumentName, ProductID, (int)ProductClass, (int)InstrumentClass, Rank, VolumeMultiple, PriceTick, MaxMarketOrderVolume, MinMarketOrderVolume, MaxLimitOrderVolume, MinLimitOrderVolume, SessionName);
	}
	const char* Instrument::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "Instrument:ExchangeID:[%s], InstrumentID:[%s], ExchangeInstID:[%s], InstrumentName:[%s], ProductID:[%s], ProductClass:[%d], InstrumentClass:[%d], Rank:[%d], VolumeMultiple:[%d], PriceTick:[%f], MaxMarketOrderVolume:[%lld], MinMarketOrderVolume:[%lld], MaxLimitOrderVolume:[%lld], MinLimitOrderVolume:[%lld], SessionName:[%s]",
			ExchangeID, InstrumentID, ExchangeInstID, InstrumentName, ProductID, (int)ProductClass, (int)InstrumentClass, Rank, VolumeMultiple, PriceTick, MaxMarketOrderVolume, MinMarketOrderVolume, MaxLimitOrderVolume, MinLimitOrderVolume, SessionName);
		return t_MdbDataStringBuffer;
	}
	static void DeallocateInstrument(void* r) { static_cast<Instrument*>(r)->Deallocate(); }
	const TableSchema& Instrument::GetSchema()
	{
		static const TableSchema schema = {"t_Instrument", InstrumentFields, 15, InstrumentPKIndices, 2, DeallocateInstrument, InstrumentIndices, 1};
		return schema;
	}
	static const FieldDescriptor DepthMarketDataFields[] = {
		{"TradingDay", FieldType::Char, offsetof(DepthMarketData, TradingDay), sizeof(DepthMarketData::TradingDay)},
		{"ExchangeID", FieldType::Char, offsetof(DepthMarketData, ExchangeID), sizeof(DepthMarketData::ExchangeID)},
		{"InstrumentID", FieldType::Char, offsetof(DepthMarketData, InstrumentID), sizeof(DepthMarketData::InstrumentID)},
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
		sprintf(t_MdbDataStringBuffer, "%s,%s,%s,%lld,%f,%f,%f,%f,%f,%f,%f,%f,%lld,%lld,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld",
			TradingDay, ExchangeID, InstrumentID, UpdateTs, LastPrice, PreSettlementPrice, PreClosePrice, PreOpenInterest, OpenPrice, HighestPrice, LowestPrice, ClosePrice, CurrVolume, Volume, CurrTurnover, Turnover, OpenInterest, SettlementPrice, UpperLimitPrice, LowerLimitPrice, AveragePrice, AskPrice1, AskPrice2, AskPrice3, AskPrice4, AskPrice5, AskPrice6, AskPrice7, AskPrice8, AskPrice9, AskPrice10, AskVolume1, AskVolume2, AskVolume3, AskVolume4, AskVolume5, AskVolume6, AskVolume7, AskVolume8, AskVolume9, AskVolume10, BidPrice1, BidPrice2, BidPrice3, BidPrice4, BidPrice5, BidPrice6, BidPrice7, BidPrice8, BidPrice9, BidPrice10, BidVolume1, BidVolume2, BidVolume3, BidVolume4, BidVolume5, BidVolume6, BidVolume7, BidVolume8, BidVolume9, BidVolume10);
		return t_MdbDataStringBuffer;
	}
	int DepthMarketData::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%s','%lld','%f','%f','%f','%f','%f','%f','%f','%f','%lld','%lld','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%lld','%lld','%lld','%lld','%lld','%lld','%lld','%lld','%lld','%lld','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%lld','%lld','%lld','%lld','%lld','%lld','%lld','%lld','%lld','%lld'),",
			TradingDay, ExchangeID, InstrumentID, UpdateTs, LastPrice, PreSettlementPrice, PreClosePrice, PreOpenInterest, OpenPrice, HighestPrice, LowestPrice, ClosePrice, CurrVolume, Volume, CurrTurnover, Turnover, OpenInterest, SettlementPrice, UpperLimitPrice, LowerLimitPrice, AveragePrice, AskPrice1, AskPrice2, AskPrice3, AskPrice4, AskPrice5, AskPrice6, AskPrice7, AskPrice8, AskPrice9, AskPrice10, AskVolume1, AskVolume2, AskVolume3, AskVolume4, AskVolume5, AskVolume6, AskVolume7, AskVolume8, AskVolume9, AskVolume10, BidPrice1, BidPrice2, BidPrice3, BidPrice4, BidPrice5, BidPrice6, BidPrice7, BidPrice8, BidPrice9, BidPrice10, BidVolume1, BidVolume2, BidVolume3, BidVolume4, BidVolume5, BidVolume6, BidVolume7, BidVolume8, BidVolume9, BidVolume10);
	}
	const char* DepthMarketData::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "DepthMarketData:TradingDay:[%s], ExchangeID:[%s], InstrumentID:[%s], UpdateTs:[%lld], LastPrice:[%f], PreSettlementPrice:[%f], PreClosePrice:[%f], PreOpenInterest:[%f], OpenPrice:[%f], HighestPrice:[%f], LowestPrice:[%f], ClosePrice:[%f], CurrVolume:[%lld], Volume:[%lld], CurrTurnover:[%f], Turnover:[%f], OpenInterest:[%f], SettlementPrice:[%f], UpperLimitPrice:[%f], LowerLimitPrice:[%f], AveragePrice:[%f], AskPrice1:[%f], AskPrice2:[%f], AskPrice3:[%f], AskPrice4:[%f], AskPrice5:[%f], AskPrice6:[%f], AskPrice7:[%f], AskPrice8:[%f], AskPrice9:[%f], AskPrice10:[%f], AskVolume1:[%lld], AskVolume2:[%lld], AskVolume3:[%lld], AskVolume4:[%lld], AskVolume5:[%lld], AskVolume6:[%lld], AskVolume7:[%lld], AskVolume8:[%lld], AskVolume9:[%lld], AskVolume10:[%lld], BidPrice1:[%f], BidPrice2:[%f], BidPrice3:[%f], BidPrice4:[%f], BidPrice5:[%f], BidPrice6:[%f], BidPrice7:[%f], BidPrice8:[%f], BidPrice9:[%f], BidPrice10:[%f], BidVolume1:[%lld], BidVolume2:[%lld], BidVolume3:[%lld], BidVolume4:[%lld], BidVolume5:[%lld], BidVolume6:[%lld], BidVolume7:[%lld], BidVolume8:[%lld], BidVolume9:[%lld], BidVolume10:[%lld]",
			TradingDay, ExchangeID, InstrumentID, UpdateTs, LastPrice, PreSettlementPrice, PreClosePrice, PreOpenInterest, OpenPrice, HighestPrice, LowestPrice, ClosePrice, CurrVolume, Volume, CurrTurnover, Turnover, OpenInterest, SettlementPrice, UpperLimitPrice, LowerLimitPrice, AveragePrice, AskPrice1, AskPrice2, AskPrice3, AskPrice4, AskPrice5, AskPrice6, AskPrice7, AskPrice8, AskPrice9, AskPrice10, AskVolume1, AskVolume2, AskVolume3, AskVolume4, AskVolume5, AskVolume6, AskVolume7, AskVolume8, AskVolume9, AskVolume10, BidPrice1, BidPrice2, BidPrice3, BidPrice4, BidPrice5, BidPrice6, BidPrice7, BidPrice8, BidPrice9, BidPrice10, BidVolume1, BidVolume2, BidVolume3, BidVolume4, BidVolume5, BidVolume6, BidVolume7, BidVolume8, BidVolume9, BidVolume10);
		return t_MdbDataStringBuffer;
	}
	static void DeallocateDepthMarketData(void* r) { static_cast<DepthMarketData*>(r)->Deallocate(); }
	const TableSchema& DepthMarketData::GetSchema()
	{
		static const TableSchema schema = {"t_DepthMarketData", DepthMarketDataFields, 61, DepthMarketDataPKIndices, 3, DeallocateDepthMarketData, nullptr, 0};
		return schema;
	}
	static const FieldDescriptor BarMarketDataFields[] = {
		{"TradingDay", FieldType::Char, offsetof(BarMarketData, TradingDay), sizeof(BarMarketData::TradingDay)},
		{"ExchangeID", FieldType::Char, offsetof(BarMarketData, ExchangeID), sizeof(BarMarketData::ExchangeID)},
		{"InstrumentID", FieldType::Char, offsetof(BarMarketData, InstrumentID), sizeof(BarMarketData::InstrumentID)},
		{"BarPreces", FieldType::Int, offsetof(BarMarketData, BarPreces), 0},
		{"BarPeriod", FieldType::Int, offsetof(BarMarketData, BarPeriod), 0},
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
		sprintf(t_MdbDataStringBuffer, "%s,%s,%s,%d,%d,%lld,%lld,%f,%f,%f,%f,%f,%f,%f,%f,%lld,%lld,%f,%f,%f",
			TradingDay, ExchangeID, InstrumentID, (int)BarPreces, BarPeriod, BarTime, UpdateTs, PreSettlementPrice, PreClosePrice, HighestPrice, LowestPrice, Open, High, Low, Close, CurrVolume, Volume, CurrTurnover, Turnover, OpenInterest);
		return t_MdbDataStringBuffer;
	}
	int BarMarketData::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%s','%d','%d','%lld','%lld','%f','%f','%f','%f','%f','%f','%f','%f','%lld','%lld','%f','%f','%f'),",
			TradingDay, ExchangeID, InstrumentID, (int)BarPreces, BarPeriod, BarTime, UpdateTs, PreSettlementPrice, PreClosePrice, HighestPrice, LowestPrice, Open, High, Low, Close, CurrVolume, Volume, CurrTurnover, Turnover, OpenInterest);
	}
	const char* BarMarketData::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "BarMarketData:TradingDay:[%s], ExchangeID:[%s], InstrumentID:[%s], BarPreces:[%d], BarPeriod:[%d], BarTime:[%lld], UpdateTs:[%lld], PreSettlementPrice:[%f], PreClosePrice:[%f], HighestPrice:[%f], LowestPrice:[%f], Open:[%f], High:[%f], Low:[%f], Close:[%f], CurrVolume:[%lld], Volume:[%lld], CurrTurnover:[%f], Turnover:[%f], OpenInterest:[%f]",
			TradingDay, ExchangeID, InstrumentID, (int)BarPreces, BarPeriod, BarTime, UpdateTs, PreSettlementPrice, PreClosePrice, HighestPrice, LowestPrice, Open, High, Low, Close, CurrVolume, Volume, CurrTurnover, Turnover, OpenInterest);
		return t_MdbDataStringBuffer;
	}
	static void DeallocateBarMarketData(void* r) { static_cast<BarMarketData*>(r)->Deallocate(); }
	const TableSchema& BarMarketData::GetSchema()
	{
		static const TableSchema schema = {"t_BarMarketData", BarMarketDataFields, 20, BarMarketDataPKIndices, 6, DeallocateBarMarketData, nullptr, 0};
		return schema;
	}
	static const FieldDescriptor MdSubscribeFields[] = {
		{"ExchangeID", FieldType::Char, offsetof(MdSubscribe, ExchangeID), sizeof(MdSubscribe::ExchangeID)},
		{"InstrumentID", FieldType::Char, offsetof(MdSubscribe, InstrumentID), sizeof(MdSubscribe::InstrumentID)},
		{"RealInstrumentID", FieldType::Char, offsetof(MdSubscribe, RealInstrumentID), sizeof(MdSubscribe::RealInstrumentID)},
		{"ProductID", FieldType::Char, offsetof(MdSubscribe, ProductID), sizeof(MdSubscribe::ProductID)},
		{"ProductClass", FieldType::Int, offsetof(MdSubscribe, ProductClass), 0},
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
		sprintf(t_MdbDataStringBuffer, "%s,%s,%s,%s,%d,%s,%s",
			ExchangeID, InstrumentID, RealInstrumentID, ProductID, (int)ProductClass, StartTradingDay, EndTradingDay);
		return t_MdbDataStringBuffer;
	}
	int MdSubscribe::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%s','%s','%d','%s','%s'),",
			ExchangeID, InstrumentID, RealInstrumentID, ProductID, (int)ProductClass, StartTradingDay, EndTradingDay);
	}
	const char* MdSubscribe::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "MdSubscribe:ExchangeID:[%s], InstrumentID:[%s], RealInstrumentID:[%s], ProductID:[%s], ProductClass:[%d], StartTradingDay:[%s], EndTradingDay:[%s]",
			ExchangeID, InstrumentID, RealInstrumentID, ProductID, (int)ProductClass, StartTradingDay, EndTradingDay);
		return t_MdbDataStringBuffer;
	}
	static void DeallocateMdSubscribe(void* r) { static_cast<MdSubscribe*>(r)->Deallocate(); }
	const TableSchema& MdSubscribe::GetSchema()
	{
		static const TableSchema schema = {"t_MdSubscribe", MdSubscribeFields, 7, MdSubscribePKIndices, 3, DeallocateMdSubscribe, nullptr, 0};
		return schema;
	}
	static const FieldDescriptor MdUserFields[] = {
		{"MdUserID", FieldType::Char, offsetof(MdUser, MdUserID), sizeof(MdUser::MdUserID)},
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
		sprintf(t_MdbDataStringBuffer, "%s,%s,%s",
			MdUserID, MdUserName, Password);
		return t_MdbDataStringBuffer;
	}
	int MdUser::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%s'),",
			MdUserID, MdUserName, Password);
	}
	const char* MdUser::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "MdUser:MdUserID:[%s], MdUserName:[%s], Password:[%s]",
			MdUserID, MdUserName, Password);
		return t_MdbDataStringBuffer;
	}
	static void DeallocateMdUser(void* r) { static_cast<MdUser*>(r)->Deallocate(); }
	const TableSchema& MdUser::GetSchema()
	{
		static const TableSchema schema = {"t_MdUser", MdUserFields, 3, MdUserPKIndices, 1, DeallocateMdUser, nullptr, 0};
		return schema;
	}
	static const FieldDescriptor MdUserLoginSessionFields[] = {
		{"MdUserID", FieldType::Char, offsetof(MdUserLoginSession, MdUserID), sizeof(MdUserLoginSession::MdUserID)},
		{"SessionID", FieldType::Int64, offsetof(MdUserLoginSession, SessionID), 0},
		{"IPAddress", FieldType::Char, offsetof(MdUserLoginSession, IPAddress), sizeof(MdUserLoginSession::IPAddress)},
	};
	static const int MdUserLoginSessionPKIndices[] = { 1 };
	static const int kMdUserLoginSessionIdxMdUserID[] = { 0 };
	static const IndexDefinition MdUserLoginSessionIndices[] = {
		{MdUserLoginSessionIndexMdUserID::IndexID, kMdUserLoginSessionIdxMdUserID, 1},
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
		sprintf(t_MdbDataStringBuffer, "%s,%lld,%s",
			MdUserID, SessionID, IPAddress);
		return t_MdbDataStringBuffer;
	}
	int MdUserLoginSession::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%lld','%s'),",
			MdUserID, SessionID, IPAddress);
	}
	const char* MdUserLoginSession::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "MdUserLoginSession:MdUserID:[%s], SessionID:[%lld], IPAddress:[%s]",
			MdUserID, SessionID, IPAddress);
		return t_MdbDataStringBuffer;
	}
	static void DeallocateMdUserLoginSession(void* r) { static_cast<MdUserLoginSession*>(r)->Deallocate(); }
	const TableSchema& MdUserLoginSession::GetSchema()
	{
		static const TableSchema schema = {"t_MdUserLoginSession", MdUserLoginSessionFields, 3, MdUserLoginSessionPKIndices, 1, DeallocateMdUserLoginSession, MdUserLoginSessionIndices, 1};
		return schema;
	}
	static const FieldDescriptor PrimaryAccountFields[] = {
		{"PrimaryAccountID", FieldType::Char, offsetof(PrimaryAccount, PrimaryAccountID), sizeof(PrimaryAccount::PrimaryAccountID)},
		{"PrimaryAccountName", FieldType::Char, offsetof(PrimaryAccount, PrimaryAccountName), sizeof(PrimaryAccount::PrimaryAccountName)},
		{"AccountClass", FieldType::Int, offsetof(PrimaryAccount, AccountClass), 0},
		{"Password", FieldType::Char, offsetof(PrimaryAccount, Password), sizeof(PrimaryAccount::Password)},
		{"OfferID", FieldType::Int, offsetof(PrimaryAccount, OfferID), 0},
		{"IsAllowLogin", FieldType::Bool, offsetof(PrimaryAccount, IsAllowLogin), 0},
		{"IsSimulateAccount", FieldType::Bool, offsetof(PrimaryAccount, IsSimulateAccount), 0},
		{"LoginStatus", FieldType::Int, offsetof(PrimaryAccount, LoginStatus), 0},
		{"InitStatus", FieldType::Int, offsetof(PrimaryAccount, InitStatus), 0},
	};
	static const int PrimaryAccountPKIndices[] = { 0 };
	static const int kPrimaryAccountIdxOfferID[] = { 4 };
	static const IndexDefinition PrimaryAccountIndices[] = {
		{PrimaryAccountIndexOfferID::IndexID, kPrimaryAccountIdxOfferID, 1},
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
		sprintf(t_MdbDataStringBuffer, "%s,%s,%d,%s,%d,%d,%d,%d,%d",
			PrimaryAccountID, PrimaryAccountName, (int)AccountClass, Password, OfferID, IsAllowLogin, IsSimulateAccount, (int)LoginStatus, (int)InitStatus);
		return t_MdbDataStringBuffer;
	}
	int PrimaryAccount::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%d','%s','%d','%d','%d','%d','%d'),",
			PrimaryAccountID, PrimaryAccountName, (int)AccountClass, Password, OfferID, IsAllowLogin, IsSimulateAccount, (int)LoginStatus, (int)InitStatus);
	}
	const char* PrimaryAccount::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "PrimaryAccount:PrimaryAccountID:[%s], PrimaryAccountName:[%s], AccountClass:[%d], Password:[%s], OfferID:[%d], IsAllowLogin:[%d], IsSimulateAccount:[%d], LoginStatus:[%d], InitStatus:[%d]",
			PrimaryAccountID, PrimaryAccountName, (int)AccountClass, Password, OfferID, IsAllowLogin, IsSimulateAccount, (int)LoginStatus, (int)InitStatus);
		return t_MdbDataStringBuffer;
	}
	static void DeallocatePrimaryAccount(void* r) { static_cast<PrimaryAccount*>(r)->Deallocate(); }
	const TableSchema& PrimaryAccount::GetSchema()
	{
		static const TableSchema schema = {"t_PrimaryAccount", PrimaryAccountFields, 9, PrimaryAccountPKIndices, 1, DeallocatePrimaryAccount, PrimaryAccountIndices, 1};
		return schema;
	}
	static const FieldDescriptor AccountFields[] = {
		{"AccountID", FieldType::Char, offsetof(Account, AccountID), sizeof(Account::AccountID)},
		{"AccountName", FieldType::Char, offsetof(Account, AccountName), sizeof(Account::AccountName)},
		{"AccountType", FieldType::Int, offsetof(Account, AccountType), 0},
		{"AccountStatus", FieldType::Int, offsetof(Account, AccountStatus), 0},
		{"Password", FieldType::Char, offsetof(Account, Password), sizeof(Account::Password)},
		{"TradeGroupID", FieldType::Int, offsetof(Account, TradeGroupID), 0},
		{"RiskGroupID", FieldType::Int, offsetof(Account, RiskGroupID), 0},
		{"CommissionGroupID", FieldType::Int, offsetof(Account, CommissionGroupID), 0},
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
		sprintf(t_MdbDataStringBuffer, "%s,%s,%d,%d,%s,%d,%d,%d",
			AccountID, AccountName, (int)AccountType, (int)AccountStatus, Password, TradeGroupID, RiskGroupID, CommissionGroupID);
		return t_MdbDataStringBuffer;
	}
	int Account::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%d','%d','%s','%d','%d','%d'),",
			AccountID, AccountName, (int)AccountType, (int)AccountStatus, Password, TradeGroupID, RiskGroupID, CommissionGroupID);
	}
	const char* Account::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "Account:AccountID:[%s], AccountName:[%s], AccountType:[%d], AccountStatus:[%d], Password:[%s], TradeGroupID:[%d], RiskGroupID:[%d], CommissionGroupID:[%d]",
			AccountID, AccountName, (int)AccountType, (int)AccountStatus, Password, TradeGroupID, RiskGroupID, CommissionGroupID);
		return t_MdbDataStringBuffer;
	}
	static void DeallocateAccount(void* r) { static_cast<Account*>(r)->Deallocate(); }
	const TableSchema& Account::GetSchema()
	{
		static const TableSchema schema = {"t_Account", AccountFields, 8, AccountPKIndices, 1, DeallocateAccount, nullptr, 0};
		return schema;
	}
	static const FieldDescriptor CapitalFields[] = {
		{"TradingDay", FieldType::Char, offsetof(Capital, TradingDay), sizeof(Capital::TradingDay)},
		{"AccountID", FieldType::Char, offsetof(Capital, AccountID), sizeof(Capital::AccountID)},
		{"AccountType", FieldType::Int, offsetof(Capital, AccountType), 0},
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
	};
	static const int CapitalPKIndices[] = { 0, 1 };
	static const int kCapitalIdxTradingDay[] = { 0 };
	static const IndexDefinition CapitalIndices[] = {
		{CapitalIndexTradingDay::IndexID, kCapitalIdxTradingDay, 1},
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
		sprintf(t_MdbDataStringBuffer, "%s,%s,%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f",
			TradingDay, AccountID, (int)AccountType, Balance, PreBalance, Available, MarketValue, CashIn, CashOut, Margin, Commission, FrozenCash, FrozenMargin, FrozenCommission, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, Deposit, Withdraw);
		return t_MdbDataStringBuffer;
	}
	int Capital::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%d','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f','%f'),",
			TradingDay, AccountID, (int)AccountType, Balance, PreBalance, Available, MarketValue, CashIn, CashOut, Margin, Commission, FrozenCash, FrozenMargin, FrozenCommission, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, Deposit, Withdraw);
	}
	const char* Capital::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "Capital:TradingDay:[%s], AccountID:[%s], AccountType:[%d], Balance:[%f], PreBalance:[%f], Available:[%f], MarketValue:[%f], CashIn:[%f], CashOut:[%f], Margin:[%f], Commission:[%f], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f], CloseProfitByDate:[%f], CloseProfitByTrade:[%f], PositionProfitByDate:[%f], PositionProfitByTrade:[%f], Deposit:[%f], Withdraw:[%f]",
			TradingDay, AccountID, (int)AccountType, Balance, PreBalance, Available, MarketValue, CashIn, CashOut, Margin, Commission, FrozenCash, FrozenMargin, FrozenCommission, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, Deposit, Withdraw);
		return t_MdbDataStringBuffer;
	}
	static void DeallocateCapital(void* r) { static_cast<Capital*>(r)->Deallocate(); }
	const TableSchema& Capital::GetSchema()
	{
		static const TableSchema schema = {"t_Capital", CapitalFields, 20, CapitalPKIndices, 2, DeallocateCapital, CapitalIndices, 1};
		return schema;
	}
	static const FieldDescriptor PositionFields[] = {
		{"TradingDay", FieldType::Char, offsetof(Position, TradingDay), sizeof(Position::TradingDay)},
		{"AccountID", FieldType::Char, offsetof(Position, AccountID), sizeof(Position::AccountID)},
		{"AccountType", FieldType::Int, offsetof(Position, AccountType), 0},
		{"ExchangeID", FieldType::Char, offsetof(Position, ExchangeID), sizeof(Position::ExchangeID)},
		{"InstrumentID", FieldType::Char, offsetof(Position, InstrumentID), sizeof(Position::InstrumentID)},
		{"ProductClass", FieldType::Int, offsetof(Position, ProductClass), 0},
		{"PosiDirection", FieldType::Int, offsetof(Position, PosiDirection), 0},
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
		{"VolumeMultiple", FieldType::Int, offsetof(Position, VolumeMultiple), 0},
		{"CloseProfitByDate", FieldType::Double, offsetof(Position, CloseProfitByDate), 0},
		{"CloseProfitByTrade", FieldType::Double, offsetof(Position, CloseProfitByTrade), 0},
		{"PositionProfitByDate", FieldType::Double, offsetof(Position, PositionProfitByDate), 0},
		{"PositionProfitByTrade", FieldType::Double, offsetof(Position, PositionProfitByTrade), 0},
		{"SettlementPrice", FieldType::Double, offsetof(Position, SettlementPrice), 0},
		{"PreSettlementPrice", FieldType::Double, offsetof(Position, PreSettlementPrice), 0},
	};
	static const int PositionPKIndices[] = { 0, 1, 3, 4, 6 };
	static const int kPositionIdxAccount[] = { 0, 1 };
	static const int kPositionIdxTradingDay[] = { 0 };
	static const IndexDefinition PositionIndices[] = {
		{PositionIndexAccount::IndexID, kPositionIdxAccount, 2},
		{PositionIndexTradingDay::IndexID, kPositionIdxTradingDay, 1},
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
		sprintf(t_MdbDataStringBuffer, "%s,%s,%d,%s,%s,%d,%d,%lld,%lld,%lld,%f,%f,%f,%f,%f,%f,%f,%f,%d,%f,%f,%f,%f,%f,%f",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, (int)PosiDirection, TotalPosition, PositionFrozen, TodayPosition, MarketValue, CashIn, CashOut, Margin, Commission, FrozenCash, FrozenMargin, FrozenCommission, VolumeMultiple, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, SettlementPrice, PreSettlementPrice);
		return t_MdbDataStringBuffer;
	}
	int Position::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%d','%s','%s','%d','%d','%lld','%lld','%lld','%f','%f','%f','%f','%f','%f','%f','%f','%d','%f','%f','%f','%f','%f','%f'),",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, (int)PosiDirection, TotalPosition, PositionFrozen, TodayPosition, MarketValue, CashIn, CashOut, Margin, Commission, FrozenCash, FrozenMargin, FrozenCommission, VolumeMultiple, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, SettlementPrice, PreSettlementPrice);
	}
	const char* Position::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "Position:TradingDay:[%s], AccountID:[%s], AccountType:[%d], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], PosiDirection:[%d], TotalPosition:[%lld], PositionFrozen:[%lld], TodayPosition:[%lld], MarketValue:[%f], CashIn:[%f], CashOut:[%f], Margin:[%f], Commission:[%f], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f], VolumeMultiple:[%d], CloseProfitByDate:[%f], CloseProfitByTrade:[%f], PositionProfitByDate:[%f], PositionProfitByTrade:[%f], SettlementPrice:[%f], PreSettlementPrice:[%f]",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, (int)PosiDirection, TotalPosition, PositionFrozen, TodayPosition, MarketValue, CashIn, CashOut, Margin, Commission, FrozenCash, FrozenMargin, FrozenCommission, VolumeMultiple, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, SettlementPrice, PreSettlementPrice);
		return t_MdbDataStringBuffer;
	}
	static void DeallocatePosition(void* r) { static_cast<Position*>(r)->Deallocate(); }
	const TableSchema& Position::GetSchema()
	{
		static const TableSchema schema = {"t_Position", PositionFields, 25, PositionPKIndices, 5, DeallocatePosition, PositionIndices, 2};
		return schema;
	}
	static const FieldDescriptor PositionDetailFields[] = {
		{"TradingDay", FieldType::Char, offsetof(PositionDetail, TradingDay), sizeof(PositionDetail::TradingDay)},
		{"AccountID", FieldType::Char, offsetof(PositionDetail, AccountID), sizeof(PositionDetail::AccountID)},
		{"AccountType", FieldType::Int, offsetof(PositionDetail, AccountType), 0},
		{"ExchangeID", FieldType::Char, offsetof(PositionDetail, ExchangeID), sizeof(PositionDetail::ExchangeID)},
		{"InstrumentID", FieldType::Char, offsetof(PositionDetail, InstrumentID), sizeof(PositionDetail::InstrumentID)},
		{"ProductClass", FieldType::Int, offsetof(PositionDetail, ProductClass), 0},
		{"PosiDirection", FieldType::Int, offsetof(PositionDetail, PosiDirection), 0},
		{"OpenDate", FieldType::Char, offsetof(PositionDetail, OpenDate), sizeof(PositionDetail::OpenDate)},
		{"TradeID", FieldType::Char, offsetof(PositionDetail, TradeID), sizeof(PositionDetail::TradeID)},
		{"Volume", FieldType::Int64, offsetof(PositionDetail, Volume), 0},
		{"OpenPrice", FieldType::Double, offsetof(PositionDetail, OpenPrice), 0},
		{"MarketValue", FieldType::Double, offsetof(PositionDetail, MarketValue), 0},
		{"CashIn", FieldType::Double, offsetof(PositionDetail, CashIn), 0},
		{"CashOut", FieldType::Double, offsetof(PositionDetail, CashOut), 0},
		{"Margin", FieldType::Double, offsetof(PositionDetail, Margin), 0},
		{"Commission", FieldType::Double, offsetof(PositionDetail, Commission), 0},
		{"VolumeMultiple", FieldType::Int, offsetof(PositionDetail, VolumeMultiple), 0},
		{"CloseProfitByDate", FieldType::Double, offsetof(PositionDetail, CloseProfitByDate), 0},
		{"CloseProfitByTrade", FieldType::Double, offsetof(PositionDetail, CloseProfitByTrade), 0},
		{"PositionProfitByDate", FieldType::Double, offsetof(PositionDetail, PositionProfitByDate), 0},
		{"PositionProfitByTrade", FieldType::Double, offsetof(PositionDetail, PositionProfitByTrade), 0},
		{"SettlementPrice", FieldType::Double, offsetof(PositionDetail, SettlementPrice), 0},
		{"PreSettlementPrice", FieldType::Double, offsetof(PositionDetail, PreSettlementPrice), 0},
		{"CloseVolume", FieldType::Int64, offsetof(PositionDetail, CloseVolume), 0},
		{"CloseAmount", FieldType::Double, offsetof(PositionDetail, CloseAmount), 0},
	};
	static const int PositionDetailPKIndices[] = { 0, 1, 3, 4, 6, 7, 8 };
	static const int kPositionDetailIdxTradeMatch[] = { 0, 1, 3, 4, 6 };
	static const int kPositionDetailIdxTradingDay[] = { 0 };
	static const IndexDefinition PositionDetailIndices[] = {
		{PositionDetailIndexTradeMatch::IndexID, kPositionDetailIdxTradeMatch, 5},
		{PositionDetailIndexTradingDay::IndexID, kPositionDetailIdxTradingDay, 1},
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
		sprintf(t_MdbDataStringBuffer, "%s,%s,%d,%s,%s,%d,%d,%s,%s,%lld,%f,%f,%f,%f,%f,%f,%d,%f,%f,%f,%f,%f,%f,%lld,%f",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, (int)PosiDirection, OpenDate, TradeID, Volume, OpenPrice, MarketValue, CashIn, CashOut, Margin, Commission, VolumeMultiple, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, SettlementPrice, PreSettlementPrice, CloseVolume, CloseAmount);
		return t_MdbDataStringBuffer;
	}
	int PositionDetail::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%d','%s','%s','%d','%d','%s','%s','%lld','%f','%f','%f','%f','%f','%f','%d','%f','%f','%f','%f','%f','%f','%lld','%f'),",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, (int)PosiDirection, OpenDate, TradeID, Volume, OpenPrice, MarketValue, CashIn, CashOut, Margin, Commission, VolumeMultiple, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, SettlementPrice, PreSettlementPrice, CloseVolume, CloseAmount);
	}
	const char* PositionDetail::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "PositionDetail:TradingDay:[%s], AccountID:[%s], AccountType:[%d], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], PosiDirection:[%d], OpenDate:[%s], TradeID:[%s], Volume:[%lld], OpenPrice:[%f], MarketValue:[%f], CashIn:[%f], CashOut:[%f], Margin:[%f], Commission:[%f], VolumeMultiple:[%d], CloseProfitByDate:[%f], CloseProfitByTrade:[%f], PositionProfitByDate:[%f], PositionProfitByTrade:[%f], SettlementPrice:[%f], PreSettlementPrice:[%f], CloseVolume:[%lld], CloseAmount:[%f]",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, (int)PosiDirection, OpenDate, TradeID, Volume, OpenPrice, MarketValue, CashIn, CashOut, Margin, Commission, VolumeMultiple, CloseProfitByDate, CloseProfitByTrade, PositionProfitByDate, PositionProfitByTrade, SettlementPrice, PreSettlementPrice, CloseVolume, CloseAmount);
		return t_MdbDataStringBuffer;
	}
	static void DeallocatePositionDetail(void* r) { static_cast<PositionDetail*>(r)->Deallocate(); }
	const TableSchema& PositionDetail::GetSchema()
	{
		static const TableSchema schema = {"t_PositionDetail", PositionDetailFields, 25, PositionDetailPKIndices, 7, DeallocatePositionDetail, PositionDetailIndices, 2};
		return schema;
	}
	static const FieldDescriptor OrderFields[] = {
		{"TradingDay", FieldType::Char, offsetof(Order, TradingDay), sizeof(Order::TradingDay)},
		{"AccountID", FieldType::Char, offsetof(Order, AccountID), sizeof(Order::AccountID)},
		{"AccountType", FieldType::Int, offsetof(Order, AccountType), 0},
		{"ExchangeID", FieldType::Char, offsetof(Order, ExchangeID), sizeof(Order::ExchangeID)},
		{"InstrumentID", FieldType::Char, offsetof(Order, InstrumentID), sizeof(Order::InstrumentID)},
		{"ProductClass", FieldType::Int, offsetof(Order, ProductClass), 0},
		{"OrderID", FieldType::Int, offsetof(Order, OrderID), 0},
		{"OrderSysID", FieldType::Char, offsetof(Order, OrderSysID), sizeof(Order::OrderSysID)},
		{"Direction", FieldType::Int, offsetof(Order, Direction), 0},
		{"OffsetFlag", FieldType::Int, offsetof(Order, OffsetFlag), 0},
		{"OrderPriceType", FieldType::Int, offsetof(Order, OrderPriceType), 0},
		{"Price", FieldType::Double, offsetof(Order, Price), 0},
		{"Volume", FieldType::Int64, offsetof(Order, Volume), 0},
		{"VolumeTotal", FieldType::Int64, offsetof(Order, VolumeTotal), 0},
		{"VolumeTraded", FieldType::Int64, offsetof(Order, VolumeTraded), 0},
		{"VolumeMultiple", FieldType::Int, offsetof(Order, VolumeMultiple), 0},
		{"OrderStatus", FieldType::Int, offsetof(Order, OrderStatus), 0},
		{"OrderDate", FieldType::Char, offsetof(Order, OrderDate), sizeof(Order::OrderDate)},
		{"OrderTime", FieldType::Char, offsetof(Order, OrderTime), sizeof(Order::OrderTime)},
		{"CancelDate", FieldType::Char, offsetof(Order, CancelDate), sizeof(Order::CancelDate)},
		{"CancelTime", FieldType::Char, offsetof(Order, CancelTime), sizeof(Order::CancelTime)},
		{"SessionID", FieldType::Int64, offsetof(Order, SessionID), 0},
		{"ClientOrderID", FieldType::Int, offsetof(Order, ClientOrderID), 0},
		{"RequestID", FieldType::Int, offsetof(Order, RequestID), 0},
		{"OfferID", FieldType::Int, offsetof(Order, OfferID), 0},
		{"TradeGroupID", FieldType::Int, offsetof(Order, TradeGroupID), 0},
		{"RiskGroupID", FieldType::Int, offsetof(Order, RiskGroupID), 0},
		{"CommissionGroupID", FieldType::Int, offsetof(Order, CommissionGroupID), 0},
		{"FrozenCash", FieldType::Double, offsetof(Order, FrozenCash), 0},
		{"FrozenMargin", FieldType::Double, offsetof(Order, FrozenMargin), 0},
		{"FrozenCommission", FieldType::Double, offsetof(Order, FrozenCommission), 0},
		{"RebuildMark", FieldType::Bool, offsetof(Order, RebuildMark), 0},
		{"IsForceClose", FieldType::Bool, offsetof(Order, IsForceClose), 0},
	};
	static const int OrderPKIndices[] = { 0, 1, 3, 4, 6 };
	static const int kOrderIdxAccountID[] = { 0, 1 };
	static const IndexDefinition OrderIndices[] = {
		{OrderIndexAccountID::IndexID, kOrderIdxAccountID, 2},
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
		sprintf(t_MdbDataStringBuffer, "%s,%s,%d,%s,%s,%d,%d,%s,%d,%d,%d,%f,%lld,%lld,%lld,%d,%d,%s,%s,%s,%s,%lld,%d,%d,%d,%d,%d,%d,%f,%f,%f,%d,%d",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, OrderID, OrderSysID, (int)Direction, (int)OffsetFlag, (int)OrderPriceType, Price, Volume, VolumeTotal, VolumeTraded, VolumeMultiple, (int)OrderStatus, OrderDate, OrderTime, CancelDate, CancelTime, SessionID, ClientOrderID, RequestID, OfferID, TradeGroupID, RiskGroupID, CommissionGroupID, FrozenCash, FrozenMargin, FrozenCommission, RebuildMark, IsForceClose);
		return t_MdbDataStringBuffer;
	}
	int Order::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%d','%s','%s','%d','%d','%s','%d','%d','%d','%f','%lld','%lld','%lld','%d','%d','%s','%s','%s','%s','%lld','%d','%d','%d','%d','%d','%d','%f','%f','%f','%d','%d'),",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, OrderID, OrderSysID, (int)Direction, (int)OffsetFlag, (int)OrderPriceType, Price, Volume, VolumeTotal, VolumeTraded, VolumeMultiple, (int)OrderStatus, OrderDate, OrderTime, CancelDate, CancelTime, SessionID, ClientOrderID, RequestID, OfferID, TradeGroupID, RiskGroupID, CommissionGroupID, FrozenCash, FrozenMargin, FrozenCommission, RebuildMark, IsForceClose);
	}
	const char* Order::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "Order:TradingDay:[%s], AccountID:[%s], AccountType:[%d], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], OrderSysID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], VolumeTotal:[%lld], VolumeTraded:[%lld], VolumeMultiple:[%d], OrderStatus:[%d], OrderDate:[%s], OrderTime:[%s], CancelDate:[%s], CancelTime:[%s], SessionID:[%lld], ClientOrderID:[%d], RequestID:[%d], OfferID:[%d], TradeGroupID:[%d], RiskGroupID:[%d], CommissionGroupID:[%d], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f], RebuildMark:[%d], IsForceClose:[%d]",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, OrderID, OrderSysID, (int)Direction, (int)OffsetFlag, (int)OrderPriceType, Price, Volume, VolumeTotal, VolumeTraded, VolumeMultiple, (int)OrderStatus, OrderDate, OrderTime, CancelDate, CancelTime, SessionID, ClientOrderID, RequestID, OfferID, TradeGroupID, RiskGroupID, CommissionGroupID, FrozenCash, FrozenMargin, FrozenCommission, RebuildMark, IsForceClose);
		return t_MdbDataStringBuffer;
	}
	static void DeallocateOrder(void* r) { static_cast<Order*>(r)->Deallocate(); }
	const TableSchema& Order::GetSchema()
	{
		static const TableSchema schema = {"t_Order", OrderFields, 33, OrderPKIndices, 5, DeallocateOrder, OrderIndices, 1};
		return schema;
	}
	static const FieldDescriptor TradeFields[] = {
		{"TradingDay", FieldType::Char, offsetof(Trade, TradingDay), sizeof(Trade::TradingDay)},
		{"AccountID", FieldType::Char, offsetof(Trade, AccountID), sizeof(Trade::AccountID)},
		{"AccountType", FieldType::Int, offsetof(Trade, AccountType), 0},
		{"ExchangeID", FieldType::Char, offsetof(Trade, ExchangeID), sizeof(Trade::ExchangeID)},
		{"InstrumentID", FieldType::Char, offsetof(Trade, InstrumentID), sizeof(Trade::InstrumentID)},
		{"ProductClass", FieldType::Int, offsetof(Trade, ProductClass), 0},
		{"OrderID", FieldType::Int, offsetof(Trade, OrderID), 0},
		{"OrderSysID", FieldType::Char, offsetof(Trade, OrderSysID), sizeof(Trade::OrderSysID)},
		{"TradeID", FieldType::Char, offsetof(Trade, TradeID), sizeof(Trade::TradeID)},
		{"Direction", FieldType::Int, offsetof(Trade, Direction), 0},
		{"OffsetFlag", FieldType::Int, offsetof(Trade, OffsetFlag), 0},
		{"Price", FieldType::Double, offsetof(Trade, Price), 0},
		{"Volume", FieldType::Int64, offsetof(Trade, Volume), 0},
		{"VolumeMultiple", FieldType::Int, offsetof(Trade, VolumeMultiple), 0},
		{"TradeAmount", FieldType::Double, offsetof(Trade, TradeAmount), 0},
		{"Commission", FieldType::Double, offsetof(Trade, Commission), 0},
		{"TradeDate", FieldType::Char, offsetof(Trade, TradeDate), sizeof(Trade::TradeDate)},
		{"TradeTime", FieldType::Char, offsetof(Trade, TradeTime), sizeof(Trade::TradeTime)},
	};
	static const int TradePKIndices[] = { 0, 3, 8, 9 };
	static const int kTradeIdxAccountID[] = { 0, 1 };
	static const IndexDefinition TradeIndices[] = {
		{TradeIndexAccountID::IndexID, kTradeIdxAccountID, 2},
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
		sprintf(t_MdbDataStringBuffer, "%s,%s,%d,%s,%s,%d,%d,%s,%s,%d,%d,%f,%lld,%d,%f,%f,%s,%s",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, OrderID, OrderSysID, TradeID, (int)Direction, (int)OffsetFlag, Price, Volume, VolumeMultiple, TradeAmount, Commission, TradeDate, TradeTime);
		return t_MdbDataStringBuffer;
	}
	int Trade::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%d','%s','%s','%d','%d','%s','%s','%d','%d','%f','%lld','%d','%f','%f','%s','%s'),",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, OrderID, OrderSysID, TradeID, (int)Direction, (int)OffsetFlag, Price, Volume, VolumeMultiple, TradeAmount, Commission, TradeDate, TradeTime);
	}
	const char* Trade::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "Trade:TradingDay:[%s], AccountID:[%s], AccountType:[%d], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], OrderSysID:[%s], TradeID:[%s], Direction:[%d], OffsetFlag:[%d], Price:[%f], Volume:[%lld], VolumeMultiple:[%d], TradeAmount:[%f], Commission:[%f], TradeDate:[%s], TradeTime:[%s]",
			TradingDay, AccountID, (int)AccountType, ExchangeID, InstrumentID, (int)ProductClass, OrderID, OrderSysID, TradeID, (int)Direction, (int)OffsetFlag, Price, Volume, VolumeMultiple, TradeAmount, Commission, TradeDate, TradeTime);
		return t_MdbDataStringBuffer;
	}
	static void DeallocateTrade(void* r) { static_cast<Trade*>(r)->Deallocate(); }
	const TableSchema& Trade::GetSchema()
	{
		static const TableSchema schema = {"t_Trade", TradeFields, 18, TradePKIndices, 4, DeallocateTrade, TradeIndices, 1};
		return schema;
	}
	static const FieldDescriptor AccountLoginSessionFields[] = {
		{"AccountID", FieldType::Char, offsetof(AccountLoginSession, AccountID), sizeof(AccountLoginSession::AccountID)},
		{"SessionID", FieldType::Int64, offsetof(AccountLoginSession, SessionID), 0},
		{"IPAddress", FieldType::Char, offsetof(AccountLoginSession, IPAddress), sizeof(AccountLoginSession::IPAddress)},
	};
	static const int AccountLoginSessionPKIndices[] = { 1 };
	static const int kAccountLoginSessionIdxAccountID[] = { 0 };
	static const IndexDefinition AccountLoginSessionIndices[] = {
		{AccountLoginSessionIndexAccountID::IndexID, kAccountLoginSessionIdxAccountID, 1},
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
		sprintf(t_MdbDataStringBuffer, "%s,%lld,%s",
			AccountID, SessionID, IPAddress);
		return t_MdbDataStringBuffer;
	}
	int AccountLoginSession::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%lld','%s'),",
			AccountID, SessionID, IPAddress);
	}
	const char* AccountLoginSession::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "AccountLoginSession:AccountID:[%s], SessionID:[%lld], IPAddress:[%s]",
			AccountID, SessionID, IPAddress);
		return t_MdbDataStringBuffer;
	}
	static void DeallocateAccountLoginSession(void* r) { static_cast<AccountLoginSession*>(r)->Deallocate(); }
	const TableSchema& AccountLoginSession::GetSchema()
	{
		static const TableSchema schema = {"t_AccountLoginSession", AccountLoginSessionFields, 3, AccountLoginSessionPKIndices, 1, DeallocateAccountLoginSession, AccountLoginSessionIndices, 1};
		return schema;
	}

	thread_local TradingDay t_CompareTradingDay;
	thread_local Exchange t_CompareExchange;
	thread_local Product t_CompareProduct;
	thread_local HotInstrument t_CompareHotInstrument;
	thread_local Instrument t_CompareInstrument;
	thread_local DepthMarketData t_CompareDepthMarketData;
	thread_local BarMarketData t_CompareBarMarketData;
	thread_local MdSubscribe t_CompareMdSubscribe;
	thread_local MdUser t_CompareMdUser;
	thread_local MdUserLoginSession t_CompareMdUserLoginSession;
	thread_local PrimaryAccount t_ComparePrimaryAccount;
	thread_local Account t_CompareAccount;
	thread_local Capital t_CompareCapital;
	thread_local Position t_ComparePosition;
	thread_local PositionDetail t_ComparePositionDetail;
	thread_local Order t_CompareOrder;
	thread_local Trade t_CompareTrade;
	thread_local AccountLoginSession t_CompareAccountLoginSession;

}
