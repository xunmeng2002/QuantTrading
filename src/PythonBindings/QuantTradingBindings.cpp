#include "StrategyBase.h"

#include "BackTestApiMiddle.h"
#include <Spark/Core/Logger/Logger.h>
#include <pybind11/pybind11.h>

#include <exception>
#include <string>

namespace py = pybind11;
using namespace spark::core;
using quanttrading::strategy::StrategyBase;

void BindEnumsAndFields(pybind11::module_& module);

namespace
{
	// 持有 BackTestApi 裸指针但不拥有：api->Release 由 StrategyBase::OnRtnMarketDataEnd 收口，
	// 与 C++ 宿主进程尾不 delete api 的语义一致
	class BackTestApiHandle
	{
	public:
		explicit BackTestApiHandle(quanttrading::BackTestApi* backTestApi) :m_BackTestApi(backTestApi) {}
		quanttrading::BackTestApi* Get() const { return m_BackTestApi; }

	private:
		quanttrading::BackTestApi* m_BackTestApi = nullptr;
	};

	BackTestApiHandle* CreateBackTestApiHandle()
	{
		return new BackTestApiHandle(quanttrading::BackTestApiMiddle::CreateBackTestApiMiddle());
	}

	// StrategyBase 的 Python 桥接：钩子覆写统一「取得 GIL → 按值拷贝分发 → 吞掉 Python 异常记日志」，
	// Python 侧拿到的字段对象是快照副本，回调结束后仍可安全持有
	class StrategyBasePy : public StrategyBase
	{
	public:
		StrategyBasePy(quanttrading::BackTestApi* backTestApi, const std::string& accountID)
			:StrategyBase(backTestApi, accountID.c_str())
		{
		}

		// 在成员上下文内形成 protected 成员指针并注册绑定（命名空间域无法取 protected 成员指针）
		static void RegisterMethods(py::class_<StrategyBase, StrategyBasePy>& strategyClass)
		{
			strategyClass
				.def("start", &StrategyBasePy::Start, py::call_guard<py::gil_scoped_release>())
				.def("wait_for_end", &StrategyBasePy::WaitForEnd, py::call_guard<py::gil_scoped_release>())
				.def("subscribe_tick", &StrategyBasePy::SubscribeTick)
				.def("subscribe_bar", &StrategyBasePy::SubscribeBar)
				.def("buy_open", &StrategyBasePy::BuyOpen)
				.def("sell_open", &StrategyBasePy::SellOpen)
				.def("buy_close", &StrategyBasePy::BuyClose)
				.def("sell_close", &StrategyBasePy::SellClose)
				.def("cancel_order", &StrategyBasePy::CancelOrder)
				.def("get_long_position", &StrategyBasePy::GetLongPosition)
				.def("get_short_position", &StrategyBasePy::GetShortPosition)
				.def("get_last_price", &StrategyBasePy::GetLastPrice);
		}

	protected:
		void OnStart() override
		{
			RunWithGil([&] { PYBIND11_OVERRIDE_NAME(void, StrategyBase, "on_start", OnStart); });
		}
		void OnTick(const DepthMarketDataField* depthMarketData) override
		{
			if (depthMarketData == nullptr)
			{
				return;
			}
			RunWithGil([&] { PYBIND11_OVERRIDE_NAME(void, StrategyBase, "on_tick", OnTick, *depthMarketData); });
		}
		void OnBar(const BarMarketDataField* barMarketData) override
		{
			if (barMarketData == nullptr)
			{
				return;
			}
			RunWithGil([&] { PYBIND11_OVERRIDE_NAME(void, StrategyBase, "on_bar", OnBar, *barMarketData); });
		}
		void OnTrade(const TradeField* trade, ClientOrderIDType clientOrderID) override
		{
			if (trade == nullptr)
			{
				return;
			}
			RunWithGil([&] { PYBIND11_OVERRIDE_NAME(void, StrategyBase, "on_trade", OnTrade, *trade, clientOrderID); });
		}
		void OnOrder(const OrderField* order) override
		{
			if (order == nullptr)
			{
				return;
			}
			RunWithGil([&] { PYBIND11_OVERRIDE_NAME(void, StrategyBase, "on_order", OnOrder, *order); });
		}
		void OnInsertOrderRsp(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo) override
		{
			if (reqInsertOrder == nullptr || rspInfo == nullptr)
			{
				return;
			}
			RunWithGil([&] { PYBIND11_OVERRIDE_NAME(void, StrategyBase, "on_insert_order_rsp", OnInsertOrderRsp, *reqInsertOrder, *rspInfo); });
		}
		void OnCancelOrderRsp(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo) override
		{
			if (reqCancelOrder == nullptr || rspInfo == nullptr)
			{
				return;
			}
			RunWithGil([&] { PYBIND11_OVERRIDE_NAME(void, StrategyBase, "on_cancel_order_rsp", OnCancelOrderRsp, *reqCancelOrder, *rspInfo); });
		}
		void OnSessionBegin(const SessionBeginField* sessionBegin) override
		{
			if (sessionBegin == nullptr)
			{
				return;
			}
			RunWithGil([&] { PYBIND11_OVERRIDE_NAME(void, StrategyBase, "on_session_begin", OnSessionBegin, *sessionBegin); });
		}
		void OnSessionEnd(const SessionEndField* sessionEnd) override
		{
			if (sessionEnd == nullptr)
			{
				return;
			}
			RunWithGil([&] { PYBIND11_OVERRIDE_NAME(void, StrategyBase, "on_session_end", OnSessionEnd, *sessionEnd); });
		}
		void OnEnd() override
		{
			RunWithGil([&] { PYBIND11_OVERRIDE_NAME(void, StrategyBase, "on_end", OnEnd); });
		}

	private:
		template <typename Dispatch>
		void RunWithGil(Dispatch dispatch)
		{
			py::gil_scoped_acquire acquire;
			try
			{
				dispatch();
			}
			catch (const std::exception& error)
			{
				WriteLog(LogLevel::Error, "Python strategy callback error: %s", error.what());
			}
		}
	};
}

PYBIND11_MODULE(quanttrading, module)
{
	BindEnumsAndFields(module);

	py::class_<BackTestApiHandle>(module, "BackTestApi");
	module.def("create_backtest_api", &CreateBackTestApiHandle, py::return_value_policy::take_ownership);

	py::class_<StrategyBase, StrategyBasePy> strategyClass(module, "StrategyBase");
	strategyClass.def(py::init([](BackTestApiHandle* apiHandle, const std::string& accountID)
	{
		if (apiHandle == nullptr)
		{
			throw py::value_error("backtest_api is required");
		}
		return new StrategyBasePy(apiHandle->Get(), accountID);
	}), py::keep_alive<1, 2>(), py::arg("backtest_api"), py::arg("account_id"));
	StrategyBasePy::RegisterMethods(strategyClass);

	module.def("init_logger", [](const std::string& processName, int logLevel)
	{
		Logger::GetInstance().Init(processName.c_str());
		Logger::GetInstance().SetLogLevel(static_cast<LogLevel>(logLevel), LogLevel::Info);
		Logger::GetInstance().Start();
	}, py::arg("process_name"), py::arg("log_level"));
	module.def("shutdown_logger", []()
	{
		Logger::GetInstance().Stop();
		Logger::GetInstance().Join();
	});
}
