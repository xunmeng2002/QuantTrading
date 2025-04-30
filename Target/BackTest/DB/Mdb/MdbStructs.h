#pragma once
#include "Types.h"

namespace mdb
{
	class TradingDay
	{
	public:
		static constexpr unsigned int TableID = 0x0001;
		//主键
		UserIDType PK;
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
		//证券类别
		SecurityTypeType SecurityType;
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
	class Instrument
	{
	public:
		static constexpr unsigned int TableID = 0x0004;
		//交易日
		DateType TradingDay;
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
		//证券类别
		SecurityTypeType SecurityType;
		//证券细分类别
		SecurityDetailTypeType SecurityDetailType;
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
	class PrimaryAccount
	{
	public:
		static constexpr unsigned int TableID = 0x0005;
		//交易日
		DateType TradingDay;
		//主账户代码
		AccountIDType PrimaryAccountID;
		//主账户名称
		AccountNameType PrimaryAccountName;
		//账户类别
		AccountClassType AccountClass;
		//经纪公司密码
		PasswordType BrokerPassword;
		//报盘代码
		OfferIDType OfferID;
		//是否允许登陆
		BoolType IsAllowLogin;
		//是否模拟账号
		BoolType IsSimulateAccount;
		//登录状态
		LoginStatusType LoginStatus;
		//初始化状态
		InitStatusType InitStatus;
		
		static PrimaryAccount* Allocate();
		void Free();
		const char* GetString() const;
		int GetSqlString(char* buff) const;
		const char* GetDebugString() const;
	};
	class Account
	{
	public:
		static constexpr unsigned int TableID = 0x0006;
		//交易日
		DateType TradingDay;
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
	class Capital
	{
	public:
		static constexpr unsigned int TableID = 0x0007;
		//交易日
		DateType TradingDay;
		//账户代码
		AccountIDType AccountID;
		//账户类型
		AccountTypeType AccountType;
		//总资产
		MoneyType Asset;
		//上日总资产
		MoneyType PreAsset;
		//现金资产
		MoneyType CashAsset;
		//上日现金资产
		MoneyType PreCashAsset;
		//可用资金
		MoneyType Available;
		//现金收入
		MoneyType CashIn;
		//现金支出
		MoneyType CashOut;
		//保证金
		MoneyType Margin;
		//手续费
		MoneyType Commission;
		//印花税
		MoneyType StampTax;
		//过户费
		MoneyType TransferFee;
		//冻结资金
		MoneyType FrozenCash;
		//冻结保证金
		MoneyType FrozenMargin;
		//冻结手续费
		MoneyType FrozenCommission;
		//冻结印花税
		MoneyType FrozenStampTax;
		//冻结过户费
		MoneyType FrozenTransferFee;
		//市值
		MoneyType MarketValue;
		//总盈亏
		MoneyType TotalProfit;
		//当日盈亏
		MoneyType TodayProfit;
		//入金
		MoneyType Deposit;
		//出金
		MoneyType Withdraw;
		
		static Capital* Allocate();
		void Free();
		const char* GetString() const;
		int GetSqlString(char* buff) const;
		const char* GetDebugString() const;
	};
	class Position
	{
	public:
		static constexpr unsigned int TableID = 0x0008;
		//交易日
		DateType TradingDay;
		//账户代码
		AccountIDType AccountID;
		//账户类型
		AccountTypeType AccountType;
		//交易所代码
		ExchangeIDType ExchangeID;
		//合约代码
		InstrumentIDType InstrumentID;
		//证券类别
		SecurityTypeType SecurityType;
		//持仓方向
		PosiDirectionType PosiDirection;
		//持仓数量
		VolumeType TotalPosition;
		//冻结持仓
		VolumeType PositionFrozen;
		//今日持仓
		VolumeType TodayPosition;
		//现金收入
		MoneyType CashIn;
		//现金支出
		MoneyType CashOut;
		//保证金
		MoneyType Margin;
		//手续费
		MoneyType Commission;
		//印花税
		MoneyType StampTax;
		//过户费
		MoneyType TransferFee;
		//冻结资金
		MoneyType FrozenCash;
		//冻结保证金
		MoneyType FrozenMargin;
		//冻结手续费
		MoneyType FrozenCommission;
		//冻结印花税
		MoneyType FrozenStampTax;
		//冻结过户费
		MoneyType FrozenTransferFee;
		//市值
		MoneyType MarketValue;
		//合约乘数
		VolumeMultipleType VolumeMultiple;
		//逐日平仓盈亏
		MoneyType CloseProfit;
		//逐笔平仓盈亏
		MoneyType CloseProfitFloat;
		//逐日持仓盈亏
		MoneyType PositionProfit;
		//逐笔持仓盈亏
		MoneyType PositionProfitFloat;
		//最新价
		PriceType LastPrice;
		//昨收盘价或昨结算价
		PriceType PrePrice;
		
		static Position* Allocate();
		void Free();
		const char* GetString() const;
		int GetSqlString(char* buff) const;
		const char* GetDebugString() const;
	};
	class Order
	{
	public:
		static constexpr unsigned int TableID = 0x0009;
		//交易日
		DateType TradingDay;
		//账户代码
		AccountIDType AccountID;
		//主账户代码
		AccountIDType PrimaryAccountID;
		//账户类型
		AccountTypeType AccountType;
		//交易所代码
		ExchangeIDType ExchangeID;
		//合约代码
		InstrumentIDType InstrumentID;
		//证券类别
		SecurityTypeType SecurityType;
		//委托编号
		OrderIDType OrderID;
		//系统委托编号
		OrderSysIDType OrderSysID;
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
		//客户端请求编号
		RequestIDType RequestID;
		//报盘代码
		OfferIDType OfferID;
		//交易组代码
		GroupIDType TradeGroupID;
		//交易组代码
		GroupIDType RiskGroupID;
		//交易组代码
		GroupIDType CommissionGroupID;
		//冻结资金
		MoneyType FrozenCash;
		//冻结保证金
		MoneyType FrozenMargin;
		//冻结手续费
		MoneyType FrozenCommission;
		//冻结印花税
		MoneyType FrozenStampTax;
		//冻结过户费
		MoneyType FrozenTransferFee;
		//重建标志
		BoolType RebuildMark;
		//是否强平单
		BoolType IsForceClose;
		
		static Order* Allocate();
		void Free();
		const char* GetString() const;
		int GetSqlString(char* buff) const;
		const char* GetDebugString() const;
	};
	class Trade
	{
	public:
		static constexpr unsigned int TableID = 0x000A;
		//交易日
		DateType TradingDay;
		//账户代码
		AccountIDType AccountID;
		//主账户代码
		AccountIDType PrimaryAccountID;
		//账户类型
		AccountTypeType AccountType;
		//交易所代码
		ExchangeIDType ExchangeID;
		//合约代码
		InstrumentIDType InstrumentID;
		//证券类别
		SecurityTypeType SecurityType;
		//委托编号
		OrderIDType OrderID;
		//系统委托编号
		OrderSysIDType OrderSysID;
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
		//印花税
		MoneyType StampTax;
		//过户费
		MoneyType TransferFee;
		//成交日期
		DateType TradeDate;
		//成交时间
		TimeType TradeTime;
		
		static Trade* Allocate();
		void Free();
		const char* GetString() const;
		int GetSqlString(char* buff) const;
		const char* GetDebugString() const;
	};
	class DepthMarketData
	{
	public:
		static constexpr unsigned int TableID = 0x000B;
		//交易日
		DateType TradingDay;
		//交易所代码
		ExchangeIDType ExchangeID;
		//合约代码
		InstrumentIDType InstrumentID;
		//最新价
		PriceType LastPrice;
		//昨结算价
		PriceType PreSettlementPrice;
		//昨收盘价
		PriceType PreClosePrice;
		//上日持仓量
		VolumeType PreOpenInterest;
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
		VolumeType OpenInterest;
		//结算价
		PriceType SettlementPrice;
		//涨停板价
		PriceType UpperLimitPrice;
		//跌停板价
		PriceType LowerLimitPrice;
		//当日均价
		PriceType AveragePrice;
		//更新时间戳
		Int64Type UpdateTs;
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
	extern thread_local Instrument t_CompareInstrument;
	extern thread_local PrimaryAccount t_ComparePrimaryAccount;
	extern thread_local Account t_CompareAccount;
	extern thread_local Capital t_CompareCapital;
	extern thread_local Position t_ComparePosition;
	extern thread_local Order t_CompareOrder;
	extern thread_local Trade t_CompareTrade;
	extern thread_local DepthMarketData t_CompareDepthMarketData;

}

