#pragma once
#include "Types.h"

namespace mdb
{
	class DepthMarketData
	{
	public:
		static constexpr unsigned int TableID = 0x2001;
		//交易日
		DateType TradingDay;
		//交易所代码
		ExchangeIDType ExchangeID;
		//合约代码
		InstrumentIDType InstrumentID;
		//更新时间戳
		Int64Type UpdateTs;
		//最新价
		PriceType LastPrice;
		//昨结算价
		PriceType PreSettlementPrice;
		//昨收盘价
		PriceType PreClosePrice;
		//上日持仓量
		LargeVolumeType PreOpenInterest;
		//开盘价
		PriceType OpenPrice;
		//最高价
		PriceType HighestPrice;
		//最低价
		PriceType LowestPrice;
		//收盘价
		PriceType ClosePrice;
		//当前数量
		VolumeType CurrVolume;
		//委托数量
		VolumeType Volume;
		//当前成交金额
		MoneyType CurrTurnover;
		//成交金额
		MoneyType Turnover;
		//持仓量
		LargeVolumeType OpenInterest;
		//结算价
		PriceType SettlementPrice;
		//涨停板价
		PriceType UpperLimitPrice;
		//跌停板价
		PriceType LowerLimitPrice;
		//当日均价
		PriceType AveragePrice;
		//申卖价一
		PriceType AskPrice1;
		//申卖价二
		PriceType AskPrice2;
		//申卖价三
		PriceType AskPrice3;
		//申卖价四
		PriceType AskPrice4;
		//申卖价五
		PriceType AskPrice5;
		//申卖价六
		PriceType AskPrice6;
		//申卖价七
		PriceType AskPrice7;
		//申卖价八
		PriceType AskPrice8;
		//申卖价九
		PriceType AskPrice9;
		//申卖价十
		PriceType AskPrice10;
		//申卖量一
		VolumeType AskVolume1;
		//申卖量二
		VolumeType AskVolume2;
		//申卖量三
		VolumeType AskVolume3;
		//申卖量四
		VolumeType AskVolume4;
		//申卖量五
		VolumeType AskVolume5;
		//申卖量六
		VolumeType AskVolume6;
		//申卖量七
		VolumeType AskVolume7;
		//申卖量八
		VolumeType AskVolume8;
		//申卖量九
		VolumeType AskVolume9;
		//申卖量十
		VolumeType AskVolume10;
		//申买价一
		PriceType BidPrice1;
		//申买价二
		PriceType BidPrice2;
		//申买价三
		PriceType BidPrice3;
		//申买价四
		PriceType BidPrice4;
		//申买价五
		PriceType BidPrice5;
		//申买价六
		PriceType BidPrice6;
		//申买价七
		PriceType BidPrice7;
		//申买价八
		PriceType BidPrice8;
		//申买价九
		PriceType BidPrice9;
		//申买价十
		PriceType BidPrice10;
		//申买量一
		VolumeType BidVolume1;
		//申买量二
		VolumeType BidVolume2;
		//申买量三
		VolumeType BidVolume3;
		//申买量四
		VolumeType BidVolume4;
		//申买量五
		VolumeType BidVolume5;
		//申买量六
		VolumeType BidVolume6;
		//申买量七
		VolumeType BidVolume7;
		//申买量八
		VolumeType BidVolume8;
		//申买量九
		VolumeType BidVolume9;
		//申买量十
		VolumeType BidVolume10;
		
		static DepthMarketData* Allocate();
		void Free();
		const char* GetString() const;
		int GetSqlString(char* buff) const;
		const char* GetDebugString() const;
	};
	class BarMarketData
	{
	public:
		static constexpr unsigned int TableID = 0x2002;
		//交易日
		DateType TradingDay;
		//交易所代码
		ExchangeIDType ExchangeID;
		//合约代码
		InstrumentIDType InstrumentID;
		//Bar精度
		BarPrecesType BarPreces;
		//Bar周期
		IntType BarPeriod;
		//Bar时间
		Int64Type BarTime;
		//更新时间戳
		Int64Type UpdateTs;
		//昨结算价
		PriceType PreSettlementPrice;
		//昨收盘价
		PriceType PreClosePrice;
		//开盘价
		PriceType Open;
		//最高价
		PriceType High;
		//最低价
		PriceType Low;
		//收盘价
		PriceType Close;
		//当前数量
		VolumeType CurrVolume;
		//委托数量
		VolumeType Volume;
		//当前成交金额
		MoneyType CurrTurnover;
		//成交金额
		MoneyType Turnover;
		//持仓量
		LargeVolumeType OpenInterest;
		
		static BarMarketData* Allocate();
		void Free();
		const char* GetString() const;
		int GetSqlString(char* buff) const;
		const char* GetDebugString() const;
	};
	class MdSubscribe
	{
	public:
		static constexpr unsigned int TableID = 0x2003;
		//交易所代码
		ExchangeIDType ExchangeID;
		//合约代码
		InstrumentIDType InstrumentID;
		//真实合约代码
		InstrumentIDType RealInstrumentID;
		//品种代码
		ProductIDType ProductID;
		//品种类型
		ProductClassType ProductClass;
		//开始交易日
		DateType StartTradingDay;
		//结束交易日
		DateType EndTradingDay;
		
		static MdSubscribe* Allocate();
		void Free();
		const char* GetString() const;
		int GetSqlString(char* buff) const;
		const char* GetDebugString() const;
	};
	class MdUser
	{
	public:
		static constexpr unsigned int TableID = 0x2004;
		//行情用户代码
		UserIDType MdUserID;
		//行情用户名称
		UserNameType MdUserName;
		//密码
		PasswordType Password;
		
		static MdUser* Allocate();
		void Free();
		const char* GetString() const;
		int GetSqlString(char* buff) const;
		const char* GetDebugString() const;
	};
	class MdUserLoginSession
	{
	public:
		static constexpr unsigned int TableID = 0x2005;
		//行情用户代码
		UserIDType MdUserID;
		//会话编号
		SessionIDType SessionID;
		//IP地址
		IPAddressType IPAddress;
		
		static MdUserLoginSession* Allocate();
		void Free();
		const char* GetString() const;
		int GetSqlString(char* buff) const;
		const char* GetDebugString() const;
	};

	extern thread_local DepthMarketData t_CompareDepthMarketData;
	extern thread_local BarMarketData t_CompareBarMarketData;
	extern thread_local MdSubscribe t_CompareMdSubscribe;
	extern thread_local MdUser t_CompareMdUser;
	extern thread_local MdUserLoginSession t_CompareMdUserLoginSession;

}

