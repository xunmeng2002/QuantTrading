#pragma once
#include "Types.h"

namespace mdb
{
	class TradingDay
	{
	public:
		static constexpr unsigned int TableID = 0x0001;
		//主键
		IntType PK;
		//当前交易日
		DateType CurrTradingDay;
		//昨交易日
		DateType PreTradingDay;
		
		static TradingDay* Allocate();
		void Free();
		const char* GetString() const;
		int GetSqlString(char* buff) const;
		const char* GetDebugString() const;
	};
	class Exchange
	{
	public:
		static constexpr unsigned int TableID = 0x0002;
		//交易所代码
		ExchangeIDType ExchangeID;
		//交易所名称
		ExchangeNameType ExchangeName;
		
		static Exchange* Allocate();
		void Free();
		const char* GetString() const;
		int GetSqlString(char* buff) const;
		const char* GetDebugString() const;
	};
	class Product
	{
	public:
		static constexpr unsigned int TableID = 0x0003;
		//交易所代码
		ExchangeIDType ExchangeID;
		//品种代码
		ProductIDType ProductID;
		//品种名称
		ProductNameType ProductName;
		//品种类型
		ProductClassType ProductClass;
		//合约乘数
		VolumeMultipleType VolumeMultiple;
		//最小变动价位
		PriceType PriceTick;
		//市价最大下单量
		VolumeType MaxMarketOrderVolume;
		//市价最小下单量
		VolumeType MinMarketOrderVolume;
		//限价最大下单量
		VolumeType MaxLimitOrderVolume;
		//限价最小下单量
		VolumeType MinLimitOrderVolume;
		//交易节名称
		SessionNameType SessionName;
		
		static Product* Allocate();
		void Free();
		const char* GetString() const;
		int GetSqlString(char* buff) const;
		const char* GetDebugString() const;
	};
	class HotInstrument
	{
	public:
		static constexpr unsigned int TableID = 0x0004;
		//交易日
		DateType TradingDay;
		//交易所代码
		ExchangeIDType ExchangeID;
		//品种代码
		ProductIDType ProductID;
		//合约代码
		InstrumentIDType InstrumentID;
		//品种类型
		ProductClassType ProductClass;
		//委托数量
		VolumeType Volume;
		//最大数量
		VolumeType MaxVolume;
		//成交金额
		MoneyType Turnover;
		//最大成交金额
		MoneyType MaxTurnover;
		//持仓量
		LargeVolumeType OpenInterest;
		//最大持仓量
		LargeVolumeType MaxOpenInterest;
		//级别
		IntType Rank;
		
		static HotInstrument* Allocate();
		void Free();
		const char* GetString() const;
		int GetSqlString(char* buff) const;
		const char* GetDebugString() const;
	};
	class Instrument
	{
	public:
		static constexpr unsigned int TableID = 0x0005;
		//交易所代码
		ExchangeIDType ExchangeID;
		//合约代码
		InstrumentIDType InstrumentID;
		//交易所合约代码
		InstrumentIDType ExchangeInstID;
		//合约名称
		InstrumentNameType InstrumentName;
		//品种代码
		ProductIDType ProductID;
		//品种类型
		ProductClassType ProductClass;
		//合约类别
		InstrumentClassType InstrumentClass;
		//级别
		IntType Rank;
		//合约乘数
		VolumeMultipleType VolumeMultiple;
		//最小变动价位
		PriceType PriceTick;
		//市价最大下单量
		VolumeType MaxMarketOrderVolume;
		//市价最小下单量
		VolumeType MinMarketOrderVolume;
		//限价最大下单量
		VolumeType MaxLimitOrderVolume;
		//限价最小下单量
		VolumeType MinLimitOrderVolume;
		//交易节名称
		SessionNameType SessionName;
		
		static Instrument* Allocate();
		void Free();
		const char* GetString() const;
		int GetSqlString(char* buff) const;
		const char* GetDebugString() const;
	};
	class Account
	{
	public:
		static constexpr unsigned int TableID = 0x3002;
		//账户代码
		AccountIDType AccountID;
		//账户名称
		AccountNameType AccountName;
		//账户类型
		AccountTypeType AccountType;
		//账户状态
		AccountStatusType AccountStatus;
		//密码
		PasswordType Password;
		//交易组代码
		GroupIDType TradeGroupID;
		//交易组代码
		GroupIDType RiskGroupID;
		//交易组代码
		GroupIDType CommissionGroupID;
		
		static Account* Allocate();
		void Free();
		const char* GetString() const;
		int GetSqlString(char* buff) const;
		const char* GetDebugString() const;
	};

	extern thread_local TradingDay t_CompareTradingDay;
	extern thread_local Exchange t_CompareExchange;
	extern thread_local Product t_CompareProduct;
	extern thread_local HotInstrument t_CompareHotInstrument;
	extern thread_local Instrument t_CompareInstrument;
	extern thread_local Account t_CompareAccount;

}

