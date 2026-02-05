#pragma once
#include "Types.h"

#pragma pack(push, 1)
class ReqSubMarketDataField
{
public:
	static constexpr UShortType FieldID = 0x1005;
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
};

class RspSubMarketDataField
{
public:
	static constexpr UShortType FieldID = 0x1006;
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
};

class RspInfoField
{
public:
	static constexpr UShortType FieldID = 0x0001;
	ErrorIDType ErrorID;		//错误代码
	MessageType ErrorMsg;		//错误信息
};

class ReqSubMarketDataFinishedField
{
public:
	static constexpr UShortType FieldID = 0x1009;
	SessionIDType SessionID;		//会话编号
};

class DepthMarketDataField
{
public:
	static constexpr UShortType FieldID = 0x100A;
	DateType TradingDay;		//交易日
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	Int64Type UpdateTs;		//更新时间戳
	PriceType LastPrice;		//最新价
	PriceType PreSettlementPrice;		//昨结算价
	PriceType PreClosePrice;		//昨收盘价
	LargeVolumeType PreOpenInterest;		//上日持仓量
	PriceType OpenPrice;		//开盘价
	PriceType HighestPrice;		//最高价
	PriceType LowestPrice;		//最低价
	PriceType ClosePrice;		//收盘价
	VolumeType CurrVolume;		//当前数量
	VolumeType Volume;		//委托数量
	MoneyType CurrTurnover;		//当前成交金额
	MoneyType Turnover;		//成交金额
	LargeVolumeType OpenInterest;		//持仓量
	PriceType SettlementPrice;		//结算价
	PriceType UpperLimitPrice;		//涨停板价
	PriceType LowerLimitPrice;		//跌停板价
	PriceType AveragePrice;		//当日均价
	PriceType AskPrice1;		//申卖价一
	PriceType AskPrice2;		//申卖价二
	PriceType AskPrice3;		//申卖价三
	PriceType AskPrice4;		//申卖价四
	PriceType AskPrice5;		//申卖价五
	PriceType AskPrice6;		//申卖价六
	PriceType AskPrice7;		//申卖价七
	PriceType AskPrice8;		//申卖价八
	PriceType AskPrice9;		//申卖价九
	PriceType AskPrice10;		//申卖价十
	VolumeType AskVolume1;		//申卖量一
	VolumeType AskVolume2;		//申卖量二
	VolumeType AskVolume3;		//申卖量三
	VolumeType AskVolume4;		//申卖量四
	VolumeType AskVolume5;		//申卖量五
	VolumeType AskVolume6;		//申卖量六
	VolumeType AskVolume7;		//申卖量七
	VolumeType AskVolume8;		//申卖量八
	VolumeType AskVolume9;		//申卖量九
	VolumeType AskVolume10;		//申卖量十
	PriceType BidPrice1;		//申买价一
	PriceType BidPrice2;		//申买价二
	PriceType BidPrice3;		//申买价三
	PriceType BidPrice4;		//申买价四
	PriceType BidPrice5;		//申买价五
	PriceType BidPrice6;		//申买价六
	PriceType BidPrice7;		//申买价七
	PriceType BidPrice8;		//申买价八
	PriceType BidPrice9;		//申买价九
	PriceType BidPrice10;		//申买价十
	VolumeType BidVolume1;		//申买量一
	VolumeType BidVolume2;		//申买量二
	VolumeType BidVolume3;		//申买量三
	VolumeType BidVolume4;		//申买量四
	VolumeType BidVolume5;		//申买量五
	VolumeType BidVolume6;		//申买量六
	VolumeType BidVolume7;		//申买量七
	VolumeType BidVolume8;		//申买量八
	VolumeType BidVolume9;		//申买量九
	VolumeType BidVolume10;		//申买量十
};

class BarMarketDataField
{
public:
	static constexpr UShortType FieldID = 0x100B;
	DateType TradingDay;		//交易日
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	BarPrecesType BarPreces;		//Bar精度
	IntType BarPeriod;		//Bar周期
	Int64Type BarTime;		//Bar时间
	Int64Type UpdateTs;		//更新时间戳
	PriceType PreSettlementPrice;		//昨结算价
	PriceType PreClosePrice;		//昨收盘价
	PriceType HighestPrice;		//最高价
	PriceType LowestPrice;		//最低价
	PriceType Open;		//开盘价
	PriceType High;		//最高价
	PriceType Low;		//最低价
	PriceType Close;		//收盘价
	VolumeType CurrVolume;		//当前数量
	VolumeType Volume;		//委托数量
	MoneyType CurrTurnover;		//当前成交金额
	MoneyType Turnover;		//成交金额
	LargeVolumeType OpenInterest;		//持仓量
};

class SessionBeginField
{
public:
	static constexpr UShortType FieldID = 0x100C;
	DateType TradingDay;		//交易日
};

class SessionEndField
{
public:
	static constexpr UShortType FieldID = 0x100D;
	DateType TradingDay;		//交易日
};

class MarketDataEndField
{
public:
	static constexpr UShortType FieldID = 0x100E;
	DateType TradingDay;		//交易日
};

class ReqInsertOrderField
{
public:
	static constexpr UShortType FieldID = 0x201A;
	AccountIDType AccountID;		//账户代码
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	DirectionType Direction;		//买卖方向
	OffsetFlagType OffsetFlag;		//开平标志
	OrderPriceTypeType OrderPriceType;		//委托价格类型
	PriceType Price;		//委托价格
	VolumeType Volume;		//委托数量
	ClientOrderIDType ClientOrderID;		//客户端委托编号
};

class ReqCancelOrderField
{
public:
	static constexpr UShortType FieldID = 0x201B;
	AccountIDType AccountID;		//账户代码
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	ClientOrderIDType ClientCancelOrderID;		//客户端撤单委托编号
	OrderIDType OrderID;		//委托编号
	OrderSysIDType OrderSysID;		//系统委托编号
	SessionIDType SessionID;		//会话编号
	ClientOrderIDType ClientOrderID;		//客户端委托编号
};

class OrderField
{
public:
	static constexpr UShortType FieldID = 0x200F;
	DateType TradingDay;		//交易日
	AccountIDType AccountID;		//账户代码
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	ProductClassType ProductClass;		//品种类型
	OrderIDType OrderID;		//委托编号
	OrderSysIDType OrderSysID;		//系统委托编号
	DirectionType Direction;		//买卖方向
	OffsetFlagType OffsetFlag;		//开平标志
	OrderPriceTypeType OrderPriceType;		//委托价格类型
	PriceType Price;		//委托价格
	VolumeType Volume;		//委托数量
	VolumeType VolumeTotal;		//剩余数量
	VolumeType VolumeTraded;		//成交数量
	VolumeMultipleType VolumeMultiple;		//合约乘数
	OrderStatusType OrderStatus;		//委托状态
	DateType OrderDate;		//委托日期
	TimeType OrderTime;		//委托时间
	DateType CancelDate;		//撤单日期
	TimeType CancelTime;		//撤单时间
	SessionIDType SessionID;		//会话编号
	ClientOrderIDType ClientOrderID;		//客户端委托编号
	RequestIDType RequestID;		//客户端请求编号
	MoneyType FrozenCash;		//冻结资金
	MoneyType FrozenMargin;		//冻结保证金
	MoneyType FrozenCommission;		//冻结手续费
};

class TradeField
{
public:
	static constexpr UShortType FieldID = 0x2011;
	DateType TradingDay;		//交易日
	AccountIDType AccountID;		//账户代码
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	ProductClassType ProductClass;		//品种类型
	OrderIDType OrderID;		//委托编号
	OrderSysIDType OrderSysID;		//系统委托编号
	TradeIDType TradeID;		//成交编号
	DirectionType Direction;		//买卖方向
	OffsetFlagType OffsetFlag;		//开平标志
	PriceType Price;		//委托价格
	VolumeType Volume;		//委托数量
	VolumeMultipleType VolumeMultiple;		//合约乘数
	MoneyType TradeAmount;		//成交金额
	MoneyType Commission;		//手续费
	DateType TradeDate;		//成交日期
	TimeType TradeTime;		//成交时间
};

#pragma pack(pop)