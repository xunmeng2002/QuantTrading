#pragma once
#include "Types.h"


class ReqSEBrokerLoginField
{
public:
	static constexpr UShortType FieldID = 0x3001;
	BrokerIDType BrokerID;		//经纪公司代码
	PasswordType Password;		//密码
};

class RspSEBrokerLoginField
{
public:
	static constexpr UShortType FieldID = 0x3002;
	BrokerIDType BrokerID;		//经纪公司代码
	BrokerNameType BrokerName;		//经纪公司名称
	SessionIDType SessionID;		//会话编号
	IPAddressType IPAddress;		//IP地址
};

class RspInfoField
{
public:
	static constexpr UShortType FieldID = 0x0001;
	ErrorIDType ErrorID;		//错误代码
	MessageType ErrorMsg;		//错误信息
};

class ReqSEInsertOrderField
{
public:
	static constexpr UShortType FieldID = 0x3005;
	BrokerIDType BrokerID;		//经纪公司代码
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

class ReqSECancelOrderField
{
public:
	static constexpr UShortType FieldID = 0x3006;
	BrokerIDType BrokerID;		//经纪公司代码
	AccountIDType AccountID;		//账户代码
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	OrderIDType CancelOrderID;		//本地撤单编号
	OrderIDType OrderID;		//委托编号
	ClientOrderIDType ClientOrderID;		//客户端委托编号
	SessionIDType SessionID;		//会话编号
};

class ReqQrySEOrderField
{
public:
	static constexpr UShortType FieldID = 0x3007;
	AccountIDType AccountID;		//账户代码
};

class SEOrderField
{
public:
	static constexpr UShortType FieldID = 0x3008;
	DateType TradingDay;		//交易日
	BrokerIDType BrokerID;		//经纪公司代码
	AccountIDType AccountID;		//账户代码
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	ProductClassType ProductClass;		//品种类型
	OrderIDType OrderID;		//委托编号
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
};

class ReqQrySETradeField
{
public:
	static constexpr UShortType FieldID = 0x3009;
	AccountIDType AccountID;		//账户代码
};

class SETradeField
{
public:
	static constexpr UShortType FieldID = 0x300A;
	DateType TradingDay;		//交易日
	BrokerIDType BrokerID;		//经纪公司代码
	AccountIDType AccountID;		//账户代码
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	ProductClassType ProductClass;		//品种类型
	OrderIDType OrderID;		//委托编号
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

class ReqQrySEInstrumentField
{
public:
	static constexpr UShortType FieldID = 0x300B;
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
};

class SEInstrumentField
{
public:
	static constexpr UShortType FieldID = 0x300C;
	ExchangeIDType ExchangeID;		//交易所代码
	InstrumentIDType InstrumentID;		//合约代码
	InstrumentIDType ExchangeInstID;		//交易所合约代码
	InstrumentNameType InstrumentName;		//合约名称
	ProductIDType ProductID;		//品种代码
	ProductClassType ProductClass;		//品种类型
	VolumeType MaxMarketOrderVolume;		//市价最大下单量
	VolumeType MinMarketOrderVolume;		//市价最小下单量
	VolumeType MaxLimitOrderVolume;		//限价最大下单量
	VolumeType MinLimitOrderVolume;		//限价最小下单量
	VolumeMultipleType VolumeMultiple;		//合约乘数
	PriceType PriceTick;		//最小变动价位
	PriceType UpperLimitPrice;		//涨停板价
	PriceType LowerLimitPrice;		//跌停板价
};

