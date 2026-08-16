#include "MdbFieldConverter.h"

#include <cstring>
#include <type_traits>

namespace detail
{
	// 两结构布局一致时整块拷贝；否则返回 false 走逐字段映射
	template <typename SrcT, typename DstT>
	bool TryBulkCopy(const SrcT& src, DstT& dst)
	{
		if constexpr (sizeof(SrcT) == sizeof(DstT))
		{
			memcpy(&dst, &src, sizeof(SrcT));
			return true;
		}
		return false;
	}

	// Depth 逐字段映射：字段在两个结构里同名同型，一个函数两方向通用
	template <typename SrcT, typename DstT>
	void CopyDepthFields(const SrcT& src, DstT& dst)
	{
		static_assert((std::is_same_v<SrcT, DepthMarketDataField> && std::is_same_v<DstT, mdb::DepthMarketData>)
			|| (std::is_same_v<SrcT, mdb::DepthMarketData> && std::is_same_v<DstT, DepthMarketDataField>));

		memcpy(dst.TradingDay, src.TradingDay, sizeof(DateType));
		memcpy(dst.ExchangeID, src.ExchangeID, sizeof(ExchangeIDType));
		memcpy(dst.InstrumentID, src.InstrumentID, sizeof(InstrumentIDType));
		dst.UpdateTs = src.UpdateTs;
		dst.LastPrice = src.LastPrice;
		dst.PreSettlementPrice = src.PreSettlementPrice;
		dst.PreClosePrice = src.PreClosePrice;
		dst.PreOpenInterest = src.PreOpenInterest;
		dst.OpenPrice = src.OpenPrice;
		dst.HighestPrice = src.HighestPrice;
		dst.LowestPrice = src.LowestPrice;
		dst.ClosePrice = src.ClosePrice;
		dst.CurrVolume = src.CurrVolume;
		dst.Volume = src.Volume;
		dst.CurrTurnover = src.CurrTurnover;
		dst.Turnover = src.Turnover;
		dst.OpenInterest = src.OpenInterest;
		dst.SettlementPrice = src.SettlementPrice;
		dst.UpperLimitPrice = src.UpperLimitPrice;
		dst.LowerLimitPrice = src.LowerLimitPrice;
		dst.AveragePrice = src.AveragePrice;
		dst.AskPrice1 = src.AskPrice1;
		dst.AskPrice2 = src.AskPrice2;
		dst.AskPrice3 = src.AskPrice3;
		dst.AskPrice4 = src.AskPrice4;
		dst.AskPrice5 = src.AskPrice5;
		dst.AskPrice6 = src.AskPrice6;
		dst.AskPrice7 = src.AskPrice7;
		dst.AskPrice8 = src.AskPrice8;
		dst.AskPrice9 = src.AskPrice9;
		dst.AskPrice10 = src.AskPrice10;
		dst.AskVolume1 = src.AskVolume1;
		dst.AskVolume2 = src.AskVolume2;
		dst.AskVolume3 = src.AskVolume3;
		dst.AskVolume4 = src.AskVolume4;
		dst.AskVolume5 = src.AskVolume5;
		dst.AskVolume6 = src.AskVolume6;
		dst.AskVolume7 = src.AskVolume7;
		dst.AskVolume8 = src.AskVolume8;
		dst.AskVolume9 = src.AskVolume9;
		dst.AskVolume10 = src.AskVolume10;
		dst.BidPrice1 = src.BidPrice1;
		dst.BidPrice2 = src.BidPrice2;
		dst.BidPrice3 = src.BidPrice3;
		dst.BidPrice4 = src.BidPrice4;
		dst.BidPrice5 = src.BidPrice5;
		dst.BidPrice6 = src.BidPrice6;
		dst.BidPrice7 = src.BidPrice7;
		dst.BidPrice8 = src.BidPrice8;
		dst.BidPrice9 = src.BidPrice9;
		dst.BidPrice10 = src.BidPrice10;
		dst.BidVolume1 = src.BidVolume1;
		dst.BidVolume2 = src.BidVolume2;
		dst.BidVolume3 = src.BidVolume3;
		dst.BidVolume4 = src.BidVolume4;
		dst.BidVolume5 = src.BidVolume5;
		dst.BidVolume6 = src.BidVolume6;
		dst.BidVolume7 = src.BidVolume7;
		dst.BidVolume8 = src.BidVolume8;
		dst.BidVolume9 = src.BidVolume9;
		dst.BidVolume10 = src.BidVolume10;
	}

	// Bar 逐字段映射：同上，一函数两方向通用
	template <typename SrcT, typename DstT>
	void CopyBarFields(const SrcT& src, DstT& dst)
	{
		static_assert((std::is_same_v<SrcT, BarMarketDataField> && std::is_same_v<DstT, mdb::BarMarketData>)
			|| (std::is_same_v<SrcT, mdb::BarMarketData> && std::is_same_v<DstT, BarMarketDataField>));

		memcpy(dst.TradingDay, src.TradingDay, sizeof(DateType));
		memcpy(dst.ExchangeID, src.ExchangeID, sizeof(ExchangeIDType));
		memcpy(dst.InstrumentID, src.InstrumentID, sizeof(InstrumentIDType));
		dst.BarPreces = src.BarPreces;
		dst.BarPeriod = src.BarPeriod;
		dst.BarTime = src.BarTime;
		dst.UpdateTs = src.UpdateTs;
		dst.PreSettlementPrice = src.PreSettlementPrice;
		dst.PreClosePrice = src.PreClosePrice;
		dst.HighestPrice = src.HighestPrice;
		dst.LowestPrice = src.LowestPrice;
		dst.Open = src.Open;
		dst.High = src.High;
		dst.Low = src.Low;
		dst.Close = src.Close;
		dst.CurrVolume = src.CurrVolume;
		dst.Volume = src.Volume;
		dst.CurrTurnover = src.CurrTurnover;
		dst.Turnover = src.Turnover;
		dst.OpenInterest = src.OpenInterest;
	}
}

void FieldToMdb(const DepthMarketDataField* field, mdb::DepthMarketData* dbStruct)
{
	if (detail::TryBulkCopy(*field, *dbStruct))
	{
		return;
	}
	detail::CopyDepthFields(*field, *dbStruct);
}
void MdbToField(const mdb::DepthMarketData* dbStruct, DepthMarketDataField* field)
{
	if (detail::TryBulkCopy(*dbStruct, *field))
	{
		return;
	}
	detail::CopyDepthFields(*dbStruct, *field);
}

void FieldToMdb(const BarMarketDataField* field, mdb::BarMarketData* dbStruct)
{
	if (detail::TryBulkCopy(*field, *dbStruct))
	{
		return;
	}
	detail::CopyBarFields(*field, *dbStruct);
}
void MdbToField(const mdb::BarMarketData* dbStruct, BarMarketDataField* field)
{
	if (detail::TryBulkCopy(*dbStruct, *field))
	{
		return;
	}
	detail::CopyBarFields(*dbStruct, *field);
}
