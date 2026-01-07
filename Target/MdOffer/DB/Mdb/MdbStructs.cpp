#include "MdbStructs.h"
#include "MemCacheTemplateSingleton.h"
#include <string>
#include <cstring>

namespace mdb
{
	thread_local char t_MdbDataStringBuffer[10240];

	DepthMarketData* DepthMarketData::Allocate()
	{
		return ::Allocate<DepthMarketData>();
	}
	void DepthMarketData::Free()
	{
		::Free<DepthMarketData>(this);
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

	BarMarketData* BarMarketData::Allocate()
	{
		return ::Allocate<BarMarketData>();
	}
	void BarMarketData::Free()
	{
		::Free<BarMarketData>(this);
	}
	const char* BarMarketData::GetString() const
	{
		sprintf(t_MdbDataStringBuffer, "%s,%s,%s,%d,%d,%lld,%lld,%f,%f,%f,%f,%f,%f,%lld,%lld,%f,%f,%f",
			TradingDay, ExchangeID, InstrumentID, (int)BarPreces, BarPeriod, BarTime, UpdateTs, PreSettlementPrice, PreClosePrice, Open, High, Low, Close, CurrVolume, Volume, CurrTurnover, Turnover, OpenInterest);
		return t_MdbDataStringBuffer;
	}
	int BarMarketData::GetSqlString(char* buff) const
	{
		return sprintf(buff, "\n('%s','%s','%s','%d','%d','%lld','%lld','%f','%f','%f','%f','%f','%f','%lld','%lld','%f','%f','%f'),",
			TradingDay, ExchangeID, InstrumentID, (int)BarPreces, BarPeriod, BarTime, UpdateTs, PreSettlementPrice, PreClosePrice, Open, High, Low, Close, CurrVolume, Volume, CurrTurnover, Turnover, OpenInterest);
	}
	const char* BarMarketData::GetDebugString() const
	{
		sprintf(t_MdbDataStringBuffer, "BarMarketData:TradingDay:[%s], ExchangeID:[%s], InstrumentID:[%s], BarPreces:[%d], BarPeriod:[%d], BarTime:[%lld], UpdateTs:[%lld], PreSettlementPrice:[%f], PreClosePrice:[%f], Open:[%f], High:[%f], Low:[%f], Close:[%f], CurrVolume:[%lld], Volume:[%lld], CurrTurnover:[%f], Turnover:[%f], OpenInterest:[%f]",
			TradingDay, ExchangeID, InstrumentID, (int)BarPreces, BarPeriod, BarTime, UpdateTs, PreSettlementPrice, PreClosePrice, Open, High, Low, Close, CurrVolume, Volume, CurrTurnover, Turnover, OpenInterest);
		return t_MdbDataStringBuffer;
	}


	thread_local DepthMarketData t_CompareDepthMarketData;
	thread_local BarMarketData t_CompareBarMarketData;

}
