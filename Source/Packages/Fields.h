#pragma once
#include "Types.h"

class RspInfoField
{
public:
	static constexpr UShortType FieldID = 0x0001;
	ErrorIDType ErrorID;		//错误代码
	MessageType ErrorMsg;		//错误信息
};
class NotifyConnectField
{
public:
	static constexpr UShortType FieldID = 0x0002;
	SessionIDType SessionID;		//会话编号
	IPAddressType IPAddress;		//IP地址
	IntType Port;		//端口
};
class NotifyDisConnectField
{
public:
	static constexpr UShortType FieldID = 0x0003;
	SessionIDType SessionID;		//会话编号
	IPAddressType IPAddress;		//IP地址
	IntType Port;		//端口
};
class ReqMdUserLoginField
{
public:
	static constexpr UShortType FieldID = 0x1001;
	UserIDType UserID;		//用户代码
	PasswordType Password;		//密码
};
class RspMdUserLoginField
{
public:
	static constexpr UShortType FieldID = 0x1002;
	UserIDType UserID;		//用户代码
	DateType LoginDate;		//登录日期
	TimeType LoginTime;		//登录时间
	SessionIDType SessionID;		//会话编号
};
class ReqSubMarketDataField
{
public:
	static constexpr UShortType FieldID = 0x1003;
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
};
class RspSubMarketDataField
{
public:
	static constexpr UShortType FieldID = 0x1004;
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
};
class ReqUnSubMarketDataField
{
public:
	static constexpr UShortType FieldID = 0x1005;
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
};
class RspUnSubMarketDataField
{
public:
	static constexpr UShortType FieldID = 0x1006;
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
};
class DepthMarketDataField
{
public:
	static constexpr UShortType FieldID = 0x1007;
	DateType TradingDay;		//交易日
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	PriceType LastPrice;		//最新价
	PriceType PreSettlementPrice;		//昨结算价
	PriceType PreClosePrice;		//昨收盘价
	VolumeType PreOpenInterest;		//上日持仓量
	PriceType OpenPrice;		//开盘价
	PriceType HighestPrice;		//最高价
	PriceType LowestPrice;		//最低价
	PriceType ClosePrice;		//收盘价
	VolumeType CurrVolume;		//当前数量
	VolumeType Volume;		//委托数量
	MoneyType CurrTurnover;		//当前成交金额
	MoneyType Turnover;		//成交金额
	VolumeType OpenInterest;		//持仓量
	PriceType SettlementPrice;		//结算价
	PriceType UpperLimitPrice;		//涨停板价
	PriceType LowerLimitPrice;		//跌停板价
	PriceType AveragePrice;		//当日均价
	Int64Type UpdateTs;		//更新时间戳
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
	static constexpr UShortType FieldID = 0x1008;
	DateType TradingDay;		//交易日
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	BarPrecesType BarPreces;		//Bar精度
	IntType BarPeriod;		//Bar周期
	Int64Type BarTime;		//Bar时间
	Int64Type UpdateTs;		//更新时间戳
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
	VolumeType OpenInterest;		//持仓量
};
