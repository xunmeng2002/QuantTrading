#include "StrategyBase.h"

#include "BackTestApiMiddle.h"
#include <Spark/Core/Logger/Logger.h>
#include <pybind11/pybind11.h>

#include <exception>
#include <string>

namespace py = pybind11;
using namespace Spark::Core;
using QuantTrading::strategy::StrategyBase;

void BindEnumsAndFields(pybind11::module_& module);

namespace
{
	// 持有 BackTestApi 裸指针但不拥有：api->Release 由 StrategyBase::OnRtnMarketDataEnd 收口，
	// 与 C++ 宿主进程尾不 delete api 的语义一致
	class BackTestApiHandle
	{
	public:
		explicit BackTestApiHandle(QuantTrading::BackTestApi* backTestApi) :backTestApi_(backTestApi) {}
		QuantTrading::BackTestApi* Get() const { return backTestApi_; }

	private:
		QuantTrading::BackTestApi* backTestApi_ = nullptr;
	};

	BackTestApiHandle* CreateBackTestApiHandle()
	{
		return new BackTestApiHandle(QuantTrading::BackTestApiMiddle::CreateBackTestApiMiddle());
	}

	// StrategyBase 的 Python 桥接：钩子统一「取得 GIL → 存在 Python 覆写按值拷贝分发 / 无覆写走基类 →
	// 吞掉 Python 异常记日志」，Python 侧拿到的字段对象是快照副本，回调结束后仍可安全持有
	class StrategyBasePy : public StrategyBase
	{
	public:
		StrategyBasePy(QuantTrading::BackTestApi* backTestApi, const std::string& accountId)
			:StrategyBase(backTestApi, accountId.c_str())
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
				// 须在 on_start 前或 on_start 内声明；on_start 内抛出会被钩子分发吞为日志，建议构造后立即调用
				.def("declare_bar_period", &StrategyBasePy::DeclareBarPeriod)
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
			DispatchHookWithGil("on_start", [&] { StrategyBase::OnStart(); });
		}
		void OnTick(const DepthMarketDataField* depthMarketData) override
		{
			if (depthMarketData == nullptr)
			{
				return;
			}
			DispatchHookWithGil("on_tick", [&] { StrategyBase::OnTick(depthMarketData); }, *depthMarketData);
		}
		void OnBar(const BarMarketDataField* barMarketData) override
		{
			if (barMarketData == nullptr)
			{
				return;
			}
			DispatchHookWithGil("on_bar", [&] { StrategyBase::OnBar(barMarketData); }, *barMarketData);
		}
		void OnTrade(const TradeField* trade, ClientOrderIdType clientOrderID) override
		{
			if (trade == nullptr)
			{
				return;
			}
			DispatchHookWithGil("on_trade", [&] { StrategyBase::OnTrade(trade, clientOrderID); }, *trade, clientOrderID);
		}
		void OnOrder(const OrderField* order) override
		{
			if (order == nullptr)
			{
				return;
			}
			DispatchHookWithGil("on_order", [&] { StrategyBase::OnOrder(order); }, *order);
		}
		void OnInsertOrderRsp(const ReqInsertOrderField* reqInsertOrder, const RspInfoField* rspInfo) override
		{
			if (reqInsertOrder == nullptr || rspInfo == nullptr)
			{
				return;
			}
			DispatchHookWithGil("on_insert_order_rsp", [&] { StrategyBase::OnInsertOrderRsp(reqInsertOrder, rspInfo); }, *reqInsertOrder, *rspInfo);
		}
		void OnCancelOrderRsp(const ReqCancelOrderField* reqCancelOrder, const RspInfoField* rspInfo) override
		{
			if (reqCancelOrder == nullptr || rspInfo == nullptr)
			{
				return;
			}
			DispatchHookWithGil("on_cancel_order_rsp", [&] { StrategyBase::OnCancelOrderRsp(reqCancelOrder, rspInfo); }, *reqCancelOrder, *rspInfo);
		}
		void OnSessionBegin(const SessionBeginField* sessionBegin) override
		{
			if (sessionBegin == nullptr)
			{
				return;
			}
			DispatchHookWithGil("on_session_begin", [&] { StrategyBase::OnSessionBegin(sessionBegin); }, *sessionBegin);
		}
		void OnSessionEnd(const SessionEndField* sessionEnd) override
		{
			if (sessionEnd == nullptr)
			{
				return;
			}
			DispatchHookWithGil("on_session_end", [&] { StrategyBase::OnSessionEnd(sessionEnd); }, *sessionEnd);
		}
		void OnEnd() override
		{
			DispatchHookWithGil("on_end", [&] { StrategyBase::OnEnd(); });
		}

	private:
		// 钩子统一分发：pybind11 宏无法为回退路径与 Python 路径传不同实参（基类收指针、Python 收拷贝），
		// 故手动 get_overload；存在覆写则按值拷贝转发，否则走基类实现
		template <typename BaseDispatch, typename... PythonArgs>
		void DispatchHookWithGil(const char* hookName, BaseDispatch fallback, PythonArgs&&... pythonArgs)
		{
			RunWithGil([&]
			{
				if (auto hookOverload = py::get_overload(this, hookName))
				{
					hookOverload(pythonArgs...);
				}
				else
				{
					fallback();
				}
			});
		}

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

PYBIND11_MODULE(QuantTrading, module)
{
	BindEnumsAndFields(module);

	py::class_<BackTestApiHandle>(module, "BackTestApi");
	module.def("create_backtest_api", &CreateBackTestApiHandle, py::return_value_policy::take_ownership);

	py::class_<StrategyBase, StrategyBasePy> strategyClass(module, "StrategyBase");
	strategyClass.def(py::init([](BackTestApiHandle* apiHandle, const std::string& accountId)
	{
		if (apiHandle == nullptr)
		{
			throw py::value_error("backtest_api is required");
		}
		return new StrategyBasePy(apiHandle->Get(), accountId);
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
