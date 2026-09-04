#include <QuantTrading/Fields.h>

#include <pybind11/pybind11.h>

#include <string>

namespace
{
namespace py = pybind11;

// char[N] 数组成员不支持 def_readonly，统一以字符串只读属性暴露
template <typename FieldT, typename MemberT>
py::class_<FieldT>& BindStringMember(py::class_<FieldT>& fieldClass, const char* memberName, MemberT FieldT::* member)
{
	return fieldClass.def_property_readonly(memberName, [member](const FieldT& field) { return std::string(field.*member); });
}

void BindEnums(py::module_& module)
{
	py::enum_<DirectionType>(module, "DirectionType")
		.value("Buy", DirectionType::Buy)
		.value("Sell", DirectionType::Sell);

	py::enum_<OffsetFlagType>(module, "OffsetFlagType")
		.value("Open", OffsetFlagType::Open)
		.value("Close", OffsetFlagType::Close)
		.value("CloseToday", OffsetFlagType::CloseToday);

	py::enum_<OrderStatusType>(module, "OrderStatusType")
		.value("Inserting", OrderStatusType::Inserting)
		.value("Inserted", OrderStatusType::Inserted)
		.value("PartTraded", OrderStatusType::PartTraded)
		.value("AllTraded", OrderStatusType::AllTraded)
		.value("Canceled", OrderStatusType::Canceled)
		.value("PartTradedCanceled", OrderStatusType::PartTradedCanceled)
		.value("Auditing", OrderStatusType::Auditing)
		.value("AuditReject", OrderStatusType::AuditReject)
		.value("RiskChecking", OrderStatusType::RiskChecking)
		.value("RiskCheckFailed", OrderStatusType::RiskCheckFailed)
		.value("Error", OrderStatusType::Error)
		.value("NotTouched", OrderStatusType::NotTouched)
		.value("Touched", OrderStatusType::Touched)
		.value("Unknown", OrderStatusType::Unknown);
}

void BindFields(py::module_& module)
{
	py::class_<RspInfoField>(module, "RspInfoField")
		.def_readonly("error_id", &RspInfoField::ErrorID)
		.def_property_readonly("error_msg", [](const RspInfoField& field) { return std::string(field.ErrorMsg); });

	py::class_<SessionBeginField> sessionBeginField(module, "SessionBeginField");
	BindStringMember(sessionBeginField, "trading_day", &SessionBeginField::TradingDay);

	py::class_<SessionEndField> sessionEndField(module, "SessionEndField");
	BindStringMember(sessionEndField, "trading_day", &SessionEndField::TradingDay);

	py::class_<MarketDataEndField> marketDataEndField(module, "MarketDataEndField");
	BindStringMember(marketDataEndField, "trading_day", &MarketDataEndField::TradingDay);

	py::class_<DepthMarketDataField>(module, "DepthMarketDataField")
		.def_property_readonly("trading_day", [](const DepthMarketDataField& field) { return std::string(field.TradingDay); })
		.def_property_readonly("exchange_id", [](const DepthMarketDataField& field) { return std::string(field.ExchangeID); })
		.def_property_readonly("instrument_id", [](const DepthMarketDataField& field) { return std::string(field.InstrumentID); })
		.def_readonly("update_ts", &DepthMarketDataField::UpdateTs)
		.def_readonly("last_price", &DepthMarketDataField::LastPrice)
		.def_readonly("pre_settlement_price", &DepthMarketDataField::PreSettlementPrice)
		.def_readonly("open_price", &DepthMarketDataField::OpenPrice)
		.def_readonly("highest_price", &DepthMarketDataField::HighestPrice)
		.def_readonly("lowest_price", &DepthMarketDataField::LowestPrice)
		.def_readonly("close_price", &DepthMarketDataField::ClosePrice)
		.def_readonly("volume", &DepthMarketDataField::Volume)
		.def_readonly("curr_volume", &DepthMarketDataField::CurrVolume)
		.def_readonly("open_interest", &DepthMarketDataField::OpenInterest)
		.def_readonly("turnover", &DepthMarketDataField::Turnover)
		.def_readonly("curr_turnover", &DepthMarketDataField::CurrTurnover)
		.def_readonly("settlement_price", &DepthMarketDataField::SettlementPrice)
		.def_readonly("upper_limit_price", &DepthMarketDataField::UpperLimitPrice)
		.def_readonly("lower_limit_price", &DepthMarketDataField::LowerLimitPrice)
		.def_readonly("average_price", &DepthMarketDataField::AveragePrice)
		.def_readonly("ask_price_1", &DepthMarketDataField::AskPrice1)
		.def_readonly("ask_volume_1", &DepthMarketDataField::AskVolume1)
		.def_readonly("bid_price_1", &DepthMarketDataField::BidPrice1)
		.def_readonly("bid_volume_1", &DepthMarketDataField::BidVolume1);

	py::class_<BarMarketDataField>(module, "BarMarketDataField")
		.def_property_readonly("trading_day", [](const BarMarketDataField& field) { return std::string(field.TradingDay); })
		.def_property_readonly("exchange_id", [](const BarMarketDataField& field) { return std::string(field.ExchangeID); })
		.def_property_readonly("instrument_id", [](const BarMarketDataField& field) { return std::string(field.InstrumentID); })
		.def_readonly("bar_time", &BarMarketDataField::BarTime)
		.def_readonly("update_ts", &BarMarketDataField::UpdateTs)
		.def_readonly("open", &BarMarketDataField::Open)
		.def_readonly("high", &BarMarketDataField::High)
		.def_readonly("low", &BarMarketDataField::Low)
		.def_readonly("close", &BarMarketDataField::Close)
		.def_readonly("curr_volume", &BarMarketDataField::CurrVolume)
		.def_readonly("volume", &BarMarketDataField::Volume)
		.def_readonly("open_interest", &BarMarketDataField::OpenInterest);

	py::class_<OrderField>(module, "OrderField")
		.def_property_readonly("trading_day", [](const OrderField& field) { return std::string(field.TradingDay); })
		.def_property_readonly("account_id", [](const OrderField& field) { return std::string(field.AccountID); })
		.def_property_readonly("exchange_id", [](const OrderField& field) { return std::string(field.ExchangeID); })
		.def_property_readonly("instrument_id", [](const OrderField& field) { return std::string(field.InstrumentID); })
		.def_readonly("order_id", &OrderField::OrderID)
		.def_readonly("direction", &OrderField::Direction)
		.def_readonly("offset_flag", &OrderField::OffsetFlag)
		.def_readonly("order_price_type", &OrderField::OrderPriceType)
		.def_readonly("price", &OrderField::Price)
		.def_readonly("volume", &OrderField::Volume)
		.def_readonly("volume_total", &OrderField::VolumeTotal)
		.def_readonly("volume_traded", &OrderField::VolumeTraded)
		.def_readonly("volume_multiple", &OrderField::VolumeMultiple)
		.def_readonly("order_status", &OrderField::OrderStatus)
		.def_property_readonly("order_date", [](const OrderField& field) { return std::string(field.OrderDate); })
		.def_property_readonly("order_time", [](const OrderField& field) { return std::string(field.OrderTime); })
		.def_property_readonly("cancel_date", [](const OrderField& field) { return std::string(field.CancelDate); })
		.def_property_readonly("cancel_time", [](const OrderField& field) { return std::string(field.CancelTime); })
		.def_readonly("session_id", &OrderField::SessionID)
		.def_readonly("client_order_id", &OrderField::ClientOrderID)
		.def_readonly("request_id", &OrderField::RequestID);

	py::class_<TradeField>(module, "TradeField")
		.def_property_readonly("trading_day", [](const TradeField& field) { return std::string(field.TradingDay); })
		.def_property_readonly("account_id", [](const TradeField& field) { return std::string(field.AccountID); })
		.def_property_readonly("exchange_id", [](const TradeField& field) { return std::string(field.ExchangeID); })
		.def_property_readonly("instrument_id", [](const TradeField& field) { return std::string(field.InstrumentID); })
		.def_readonly("order_id", &TradeField::OrderID)
		.def_property_readonly("trade_id", [](const TradeField& field) { return std::string(field.TradeID); })
		.def_readonly("direction", &TradeField::Direction)
		.def_readonly("offset_flag", &TradeField::OffsetFlag)
		.def_readonly("price", &TradeField::Price)
		.def_readonly("volume", &TradeField::Volume)
		.def_readonly("volume_multiple", &TradeField::VolumeMultiple)
		.def_readonly("trade_amount", &TradeField::TradeAmount)
		.def_readonly("commission", &TradeField::Commission)
		.def_property_readonly("trade_date", [](const TradeField& field) { return std::string(field.TradeDate); })
		.def_property_readonly("trade_time", [](const TradeField& field) { return std::string(field.TradeTime); });

	py::class_<ReqInsertOrderField>(module, "ReqInsertOrderField")
		.def_property_readonly("account_id", [](const ReqInsertOrderField& field) { return std::string(field.AccountID); })
		.def_property_readonly("exchange_id", [](const ReqInsertOrderField& field) { return std::string(field.ExchangeID); })
		.def_property_readonly("instrument_id", [](const ReqInsertOrderField& field) { return std::string(field.InstrumentID); })
		.def_readonly("direction", &ReqInsertOrderField::Direction)
		.def_readonly("offset_flag", &ReqInsertOrderField::OffsetFlag)
		.def_readonly("order_price_type", &ReqInsertOrderField::OrderPriceType)
		.def_readonly("price", &ReqInsertOrderField::Price)
		.def_readonly("volume", &ReqInsertOrderField::Volume)
		.def_readonly("client_order_id", &ReqInsertOrderField::ClientOrderID);

	py::class_<ReqCancelOrderField>(module, "ReqCancelOrderField")
		.def_property_readonly("account_id", [](const ReqCancelOrderField& field) { return std::string(field.AccountID); })
		.def_property_readonly("exchange_id", [](const ReqCancelOrderField& field) { return std::string(field.ExchangeID); })
		.def_property_readonly("instrument_id", [](const ReqCancelOrderField& field) { return std::string(field.InstrumentID); })
		.def_readonly("client_cancel_order_id", &ReqCancelOrderField::ClientCancelOrderID)
		.def_readonly("order_id", &ReqCancelOrderField::OrderID)
		.def_readonly("session_id", &ReqCancelOrderField::SessionID)
		.def_readonly("client_order_id", &ReqCancelOrderField::ClientOrderID);
}
}

void BindEnumsAndFields(pybind11::module_& module)
{
	BindEnums(module);
	BindFields(module);
}
