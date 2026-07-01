#include "QuantUtility.h"
#include <memory>


DirectionType GetOppoDirection(const DirectionType& direction)
{
	if (direction == DirectionType::Buy)
		return DirectionType::Sell;
	return DirectionType::Buy;
}
PosiDirectionType GetPosiDirection(const OffsetFlagType& offsetFlag, const DirectionType& direction)
{
	if (offsetFlag == OffsetFlagType::Open)
	{
		if (direction == DirectionType::Buy)
			return PosiDirectionType::Long;
		return PosiDirectionType::Short;
	}
	else
	{
		if (direction == DirectionType::Buy)
			return PosiDirectionType::Short;
		return PosiDirectionType::Long;
	}
}

void PackageToMdb(DepthMarketDataField* field, mdb::DepthMarketData* dbStruct)
{
	if (sizeof(DepthMarketDataField) == sizeof(mdb::DepthMarketData))
	{
		memcpy(dbStruct, field, sizeof(DepthMarketDataField));
	}
	else
	{
		memcpy(dbStruct->TradingDay, field->TradingDay, sizeof(DateType));
		memcpy(dbStruct->ExchangeID, field->ExchangeID, sizeof(ExchangeIDType));
		memcpy(dbStruct->InstrumentID, field->InstrumentID, sizeof(InstrumentIDType));
		dbStruct->UpdateTs = field->UpdateTs;
		dbStruct->LastPrice = field->LastPrice;
		dbStruct->PreSettlementPrice = field->PreSettlementPrice;
		dbStruct->PreClosePrice = field->PreClosePrice;
		dbStruct->PreOpenInterest = field->PreOpenInterest;
		dbStruct->OpenPrice = field->OpenPrice;
		dbStruct->HighestPrice = field->HighestPrice;
		dbStruct->LowestPrice = field->LowestPrice;
		dbStruct->ClosePrice = field->ClosePrice;
		dbStruct->CurrVolume = field->CurrVolume;
		dbStruct->Volume = field->Volume;
		dbStruct->CurrTurnover = field->CurrTurnover;
		dbStruct->Turnover = field->Turnover;
		dbStruct->OpenInterest = field->OpenInterest;
		dbStruct->SettlementPrice = field->SettlementPrice;
		dbStruct->UpperLimitPrice = field->UpperLimitPrice;
		dbStruct->LowerLimitPrice = field->LowerLimitPrice;
		dbStruct->AveragePrice = field->AveragePrice;
		dbStruct->AskPrice1 = field->AskPrice1;
		dbStruct->AskPrice2 = field->AskPrice2;
		dbStruct->AskPrice3 = field->AskPrice3;
		dbStruct->AskPrice4 = field->AskPrice4;
		dbStruct->AskPrice5 = field->AskPrice5;
		dbStruct->AskPrice6 = field->AskPrice6;
		dbStruct->AskPrice7 = field->AskPrice7;
		dbStruct->AskPrice8 = field->AskPrice8;
		dbStruct->AskPrice9 = field->AskPrice9;
		dbStruct->AskPrice10 = field->AskPrice10;
		dbStruct->AskVolume1 = field->AskVolume1;
		dbStruct->AskVolume2 = field->AskVolume2;
		dbStruct->AskVolume3 = field->AskVolume3;
		dbStruct->AskVolume4 = field->AskVolume4;
		dbStruct->AskVolume5 = field->AskVolume5;
		dbStruct->AskVolume6 = field->AskVolume6;
		dbStruct->AskVolume7 = field->AskVolume7;
		dbStruct->AskVolume8 = field->AskVolume8;
		dbStruct->AskVolume9 = field->AskVolume9;
		dbStruct->AskVolume10 = field->AskVolume10;
		dbStruct->BidPrice1 = field->BidPrice1;
		dbStruct->BidPrice2 = field->BidPrice2;
		dbStruct->BidPrice3 = field->BidPrice3;
		dbStruct->BidPrice4 = field->BidPrice4;
		dbStruct->BidPrice5 = field->BidPrice5;
		dbStruct->BidPrice6 = field->BidPrice6;
		dbStruct->BidPrice7 = field->BidPrice7;
		dbStruct->BidPrice8 = field->BidPrice8;
		dbStruct->BidPrice9 = field->BidPrice9;
		dbStruct->BidPrice10 = field->BidPrice10;
		dbStruct->BidVolume1 = field->BidVolume1;
		dbStruct->BidVolume2 = field->BidVolume2;
		dbStruct->BidVolume3 = field->BidVolume3;
		dbStruct->BidVolume4 = field->BidVolume4;
		dbStruct->BidVolume5 = field->BidVolume5;
		dbStruct->BidVolume6 = field->BidVolume6;
		dbStruct->BidVolume7 = field->BidVolume7;
		dbStruct->BidVolume8 = field->BidVolume8;
		dbStruct->BidVolume9 = field->BidVolume9;
		dbStruct->BidVolume10 = field->BidVolume10;
	}
}
void MdbToPackage(mdb::DepthMarketData* dbStruct, DepthMarketDataField* field)
{
	if (sizeof(DepthMarketDataField) == sizeof(mdb::DepthMarketData))
	{
		memcpy(field, dbStruct, sizeof(DepthMarketDataField));
	}
	else
	{
		memcpy(field->TradingDay, dbStruct->TradingDay, sizeof(DateType));
		memcpy(field->ExchangeID, dbStruct->ExchangeID, sizeof(ExchangeIDType));
		memcpy(field->InstrumentID, dbStruct->InstrumentID, sizeof(InstrumentIDType));
		field->UpdateTs = dbStruct->UpdateTs;
		field->LastPrice = dbStruct->LastPrice;
		field->PreSettlementPrice = dbStruct->PreSettlementPrice;
		field->PreClosePrice = dbStruct->PreClosePrice;
		field->PreOpenInterest = dbStruct->PreOpenInterest;
		field->OpenPrice = dbStruct->OpenPrice;
		field->HighestPrice = dbStruct->HighestPrice;
		field->LowestPrice = dbStruct->LowestPrice;
		field->ClosePrice = dbStruct->ClosePrice;
		field->CurrVolume = dbStruct->CurrVolume;
		field->Volume = dbStruct->Volume;
		field->CurrTurnover = dbStruct->CurrTurnover;
		field->Turnover = dbStruct->Turnover;
		field->OpenInterest = dbStruct->OpenInterest;
		field->SettlementPrice = dbStruct->SettlementPrice;
		field->UpperLimitPrice = dbStruct->UpperLimitPrice;
		field->LowerLimitPrice = dbStruct->LowerLimitPrice;
		field->AveragePrice = dbStruct->AveragePrice;
		field->AskPrice1 = dbStruct->AskPrice1;
		field->AskPrice2 = dbStruct->AskPrice2;
		field->AskPrice3 = dbStruct->AskPrice3;
		field->AskPrice4 = dbStruct->AskPrice4;
		field->AskPrice5 = dbStruct->AskPrice5;
		field->AskPrice6 = dbStruct->AskPrice6;
		field->AskPrice7 = dbStruct->AskPrice7;
		field->AskPrice8 = dbStruct->AskPrice8;
		field->AskPrice9 = dbStruct->AskPrice9;
		field->AskPrice10 = dbStruct->AskPrice10;
		field->AskVolume1 = dbStruct->AskVolume1;
		field->AskVolume2 = dbStruct->AskVolume2;
		field->AskVolume3 = dbStruct->AskVolume3;
		field->AskVolume4 = dbStruct->AskVolume4;
		field->AskVolume5 = dbStruct->AskVolume5;
		field->AskVolume6 = dbStruct->AskVolume6;
		field->AskVolume7 = dbStruct->AskVolume7;
		field->AskVolume8 = dbStruct->AskVolume8;
		field->AskVolume9 = dbStruct->AskVolume9;
		field->AskVolume10 = dbStruct->AskVolume10;
		field->BidPrice1 = dbStruct->BidPrice1;
		field->BidPrice2 = dbStruct->BidPrice2;
		field->BidPrice3 = dbStruct->BidPrice3;
		field->BidPrice4 = dbStruct->BidPrice4;
		field->BidPrice5 = dbStruct->BidPrice5;
		field->BidPrice6 = dbStruct->BidPrice6;
		field->BidPrice7 = dbStruct->BidPrice7;
		field->BidPrice8 = dbStruct->BidPrice8;
		field->BidPrice9 = dbStruct->BidPrice9;
		field->BidPrice10 = dbStruct->BidPrice10;
		field->BidVolume1 = dbStruct->BidVolume1;
		field->BidVolume2 = dbStruct->BidVolume2;
		field->BidVolume3 = dbStruct->BidVolume3;
		field->BidVolume4 = dbStruct->BidVolume4;
		field->BidVolume5 = dbStruct->BidVolume5;
		field->BidVolume6 = dbStruct->BidVolume6;
		field->BidVolume7 = dbStruct->BidVolume7;
		field->BidVolume8 = dbStruct->BidVolume8;
		field->BidVolume9 = dbStruct->BidVolume9;
		field->BidVolume10 = dbStruct->BidVolume10;
	}
}

void PackageToMdb(BarMarketDataField* field, mdb::BarMarketData* dbStruct)
{
	if (sizeof(BarMarketDataField) == sizeof(mdb::BarMarketData))
	{
		memcpy(dbStruct, field, sizeof(BarMarketDataField));
	}
	else
	{
		memcpy(dbStruct->TradingDay, field->TradingDay, sizeof(DateType));
		memcpy(dbStruct->ExchangeID, field->ExchangeID, sizeof(ExchangeIDType));
		memcpy(dbStruct->InstrumentID, field->InstrumentID, sizeof(InstrumentIDType));
		dbStruct->BarPreces = field->BarPreces;
		dbStruct->BarPeriod = field->BarPeriod;
		dbStruct->BarTime = field->BarTime;
		dbStruct->UpdateTs = field->UpdateTs;
		dbStruct->PreSettlementPrice = field->PreSettlementPrice;
		dbStruct->PreClosePrice = field->PreClosePrice;
		dbStruct->HighestPrice = field->HighestPrice;
		dbStruct->LowestPrice = field->LowestPrice;
		dbStruct->Open = field->Open;
		dbStruct->High = field->High;
		dbStruct->Low = field->Low;
		dbStruct->Close = field->Close;
		dbStruct->CurrVolume = field->CurrVolume;
		dbStruct->Volume = field->Volume;
		dbStruct->CurrTurnover = field->CurrTurnover;
		dbStruct->Turnover = field->Turnover;
		dbStruct->OpenInterest = field->OpenInterest;
	}
}
void MdbToPackage(mdb::BarMarketData* dbStruct, BarMarketDataField* field)
{
	if (sizeof(BarMarketDataField) == sizeof(mdb::BarMarketData))
	{
		memcpy(field, dbStruct, sizeof(BarMarketDataField));
	}
	else
	{
		memcpy(field->TradingDay, dbStruct->TradingDay, sizeof(DateType));
		memcpy(field->ExchangeID, dbStruct->ExchangeID, sizeof(ExchangeIDType));
		memcpy(field->InstrumentID, dbStruct->InstrumentID, sizeof(InstrumentIDType));
		field->BarPreces = dbStruct->BarPreces;
		field->BarPeriod = dbStruct->BarPeriod;
		field->BarTime = dbStruct->BarTime;
		field->UpdateTs = dbStruct->UpdateTs;
		field->PreSettlementPrice = dbStruct->PreSettlementPrice;
		field->PreClosePrice = dbStruct->PreClosePrice;
		field->HighestPrice = dbStruct->HighestPrice;
		field->LowestPrice = dbStruct->LowestPrice;
		field->Open = dbStruct->Open;
		field->High = dbStruct->High;
		field->Low = dbStruct->Low;
		field->Close = dbStruct->Close;
		field->CurrVolume = dbStruct->CurrVolume;
		field->Volume = dbStruct->Volume;
		field->CurrTurnover = dbStruct->CurrTurnover;
		field->Turnover = dbStruct->Turnover;
		field->OpenInterest = dbStruct->OpenInterest;
	}
}
