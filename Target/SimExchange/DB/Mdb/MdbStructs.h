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
	class SEBroker
	{
	public:
		static constexpr unsigned int TableID = 0x1001;
		//经纪公司代码
		BrokerIDType BrokerID;
		//经纪公司名称
		BrokerNameType BrokerName;
		//密码
		PasswordType Password;
		
		static SEBroker* Allocate();
		void Free();
		const char* GetString() const;
		int GetSqlString(char* buff) const;
		const char* GetDebugString() const;
	};
	class SEInstrument
	{
	public:
		static constexpr unsigned int TableID = 0x1002;
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
		//市价最大下单量
		VolumeType MaxMarketOrderVolume;
		//市价最小下单量
		VolumeType MinMarketOrderVolume;
		//限价最大下单量
		VolumeType MaxLimitOrderVolume;
		//限价最小下单量
		VolumeType MinLimitOrderVolume;
		//合约乘数
		VolumeMultipleType VolumeMultiple;
		//最小变动价位
		PriceType PriceTick;
		//涨停板价
		PriceType UpperLimitPrice;
		//跌停板价
		PriceType LowerLimitPrice;
		//交易节名称
		SessionNameType SessionName;
		
		static SEInstrument* Allocate();
		void Free();
		const char* GetString() const;
		int GetSqlString(char* buff) const;
		const char* GetDebugString() const;
	};
	class SEOrder
	{
	public:
		static constexpr unsigned int TableID = 0x1003;
		//交易日
		DateType TradingDay;
		//经纪公司代码
		BrokerIDType BrokerID;
		//账户代码
		AccountIDType AccountID;
		//交易所代码
		ExchangeIDType ExchangeID;
		//合约代码
		InstrumentIDType InstrumentID;
		//品种类型
		ProductClassType ProductClass;
		//委托编号
		OrderIDType OrderID;
		//买卖方向
		DirectionType Direction;
		//开平标志
		OffsetFlagType OffsetFlag;
		//委托价格类型
		OrderPriceTypeType OrderPriceType;
		//委托价格
		PriceType Price;
		//委托数量
		VolumeType Volume;
		//剩余数量
		VolumeType VolumeTotal;
		//成交数量
		VolumeType VolumeTraded;
		//合约乘数
		VolumeMultipleType VolumeMultiple;
		//委托状态
		OrderStatusType OrderStatus;
		//委托日期
		DateType OrderDate;
		//委托时间
		TimeType OrderTime;
		//撤单日期
		DateType CancelDate;
		//撤单时间
		TimeType CancelTime;
		//会话编号
		SessionIDType SessionID;
		//客户端委托编号
		ClientOrderIDType ClientOrderID;
		
		static SEOrder* Allocate();
		void Free();
		const char* GetString() const;
		int GetSqlString(char* buff) const;
		const char* GetDebugString() const;
	};
	class SETrade
	{
	public:
		static constexpr unsigned int TableID = 0x1004;
		//交易日
		DateType TradingDay;
		//经纪公司代码
		BrokerIDType BrokerID;
		//账户代码
		AccountIDType AccountID;
		//交易所代码
		ExchangeIDType ExchangeID;
		//合约代码
		InstrumentIDType InstrumentID;
		//品种类型
		ProductClassType ProductClass;
		//委托编号
		OrderIDType OrderID;
		//成交编号
		TradeIDType TradeID;
		//买卖方向
		DirectionType Direction;
		//开平标志
		OffsetFlagType OffsetFlag;
		//委托价格
		PriceType Price;
		//委托数量
		VolumeType Volume;
		//合约乘数
		VolumeMultipleType VolumeMultiple;
		//成交金额
		MoneyType TradeAmount;
		//手续费
		MoneyType Commission;
		//成交日期
		DateType TradeDate;
		//成交时间
		TimeType TradeTime;
		
		static SETrade* Allocate();
		void Free();
		const char* GetString() const;
		int GetSqlString(char* buff) const;
		const char* GetDebugString() const;
	};
	class SEBrokerLoginSession
	{
	public:
		static constexpr unsigned int TableID = 0x1005;
		//经纪公司代码
		BrokerIDType BrokerID;
		//会话编号
		SessionIDType SessionID;
		//IP地址
		IPAddressType IPAddress;
		
		static SEBrokerLoginSession* Allocate();
		void Free();
		const char* GetString() const;
		int GetSqlString(char* buff) const;
		const char* GetDebugString() const;
	};
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

	extern thread_local TradingDay t_CompareTradingDay;
	extern thread_local Exchange t_CompareExchange;
	extern thread_local Product t_CompareProduct;
	extern thread_local SEBroker t_CompareSEBroker;
	extern thread_local SEInstrument t_CompareSEInstrument;
	extern thread_local SEOrder t_CompareSEOrder;
	extern thread_local SETrade t_CompareSETrade;
	extern thread_local SEBrokerLoginSession t_CompareSEBrokerLoginSession;
	extern thread_local DepthMarketData t_CompareDepthMarketData;

}

