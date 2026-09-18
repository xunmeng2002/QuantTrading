#pragma once
#include <Spark/Serialization/json/json.h>

#include <fstream>
#include <memory>
#include <string>
#include <vector>

// 回测结果契约：引擎收尾把 RunResult 写成 <cwd>/result.json，宿主读它决定退出码。
// 契约只在这里定义一次——键名即 RunResult 的成员名，加字段只改这一个结构体。
// 放在 src/BackTest/ 而非 include/QuantTrading/（后者是生成的 DLL 导出面），也不放 test/（会让 src/ 反向依赖 test/）。
namespace QuantTrading::BackTest
{
	inline constexpr const char* ResultFileName = "result.json";
	inline constexpr int ResultSchemaVersion = 1;

	// 退出码契约。已知歧义：MSVC 下 abort()/未捕获异常也返回 3，与「引擎报告失败」同码，
	// 消歧只能靠文件——码 3 且有可解析的 result.json 即引擎报告失败，码 3 且无文件即崩溃。
	inline constexpr int ExitCodeSuccess = 0;
	inline constexpr int ExitCodeHostInitFailed = 1;
	inline constexpr int ExitCodeResultFileUnreadable = 2;
	inline constexpr int ExitCodeEngineFailed = 3;

	struct RunResult
	{
		int SchemaVersion = ResultSchemaVersion;
		std::string RunId;
		bool Success = false;
		int ErrorId = 0;
		std::string ErrorMsg;
		std::string DumpPath;
		std::string DbPath;
		std::string StartTradingDay;
		std::string EndTradingDay;
		std::string LastTradingDay;
		std::string AccountId;
		bool BasicDataLoaded = false;
		int MdSubscribeCount = 0;
		int BarMarketDataCount = 0;
		int DepthMarketDataCount = 0;
		int InstrumentCount = 0;
		int OrderCount = 0;
		int TradeCount = 0;
		bool HasCapital = false;
		double Balance = 0;
		double Available = 0;
		double Commission = 0;
		double StampTax = 0;
		double TransferFee = 0;
		int CommissionMissingCount = 0;
		int CommissionZeroRateKeyCount = 0;
		std::vector<std::string> MissingRateKeys;
		int VolumeMultipleFallbackProductCount = 0;
	};

	// 键名一律 PascalCase：本项目跨语言面（Fields.h 经 pybind11 暴露的 Python 属性、所有 JSON 配置）都是 PascalCase
	inline Json::Value ToJsonValue(const RunResult& runResult)
	{
		Json::Value root;
		root["SchemaVersion"] = runResult.SchemaVersion;
		root["RunId"] = runResult.RunId;
		root["Success"] = runResult.Success;
		root["ErrorId"] = runResult.ErrorId;
		root["ErrorMsg"] = runResult.ErrorMsg;
		root["DumpPath"] = runResult.DumpPath;
		root["DbPath"] = runResult.DbPath;
		root["StartTradingDay"] = runResult.StartTradingDay;
		root["EndTradingDay"] = runResult.EndTradingDay;
		root["LastTradingDay"] = runResult.LastTradingDay;
		root["AccountId"] = runResult.AccountId;
		root["BasicDataLoaded"] = runResult.BasicDataLoaded;
		root["MdSubscribeCount"] = runResult.MdSubscribeCount;
		root["BarMarketDataCount"] = runResult.BarMarketDataCount;
		root["DepthMarketDataCount"] = runResult.DepthMarketDataCount;
		root["InstrumentCount"] = runResult.InstrumentCount;
		root["OrderCount"] = runResult.OrderCount;
		root["TradeCount"] = runResult.TradeCount;
		root["HasCapital"] = runResult.HasCapital;
		root["Balance"] = runResult.Balance;
		root["Available"] = runResult.Available;
		root["Commission"] = runResult.Commission;
		root["StampTax"] = runResult.StampTax;
		root["TransferFee"] = runResult.TransferFee;
		root["CommissionMissingCount"] = runResult.CommissionMissingCount;
		root["CommissionZeroRateKeyCount"] = runResult.CommissionZeroRateKeyCount;
		root["VolumeMultipleFallbackProductCount"] = runResult.VolumeMultipleFallbackProductCount;
		Json::Value missingRateKeys(Json::arrayValue);
		for (const auto& rateKey : runResult.MissingRateKeys)
		{
			missingRateKeys.append(rateKey);
		}
		root["MissingRateKeys"] = missingRateKeys;
		return root;
	}

	inline bool WriteRunResultFile(const char* filePath, const RunResult& runResult)
	{
		std::ofstream outFile(filePath, std::ios::binary | std::ios::trunc);
		if (!outFile.is_open())
		{
			return false;
		}
		Json::StreamWriterBuilder builder;
		builder["indentation"] = "  ";
		std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
		writer->write(ToJsonValue(runResult), &outFile);
		outFile.flush();
		return outFile.good();
	}

	// 文件打不开或解析失败一律返回「缺失或不可解析」，让「没走完收尾」与「引擎报告失败」在宿主侧可区分
	inline int ExitCodeFromRunResultFile(const char* filePath)
	{
		std::ifstream inFile(filePath, std::ios::binary);
		if (!inFile.is_open())
		{
			return ExitCodeResultFileUnreadable;
		}
		Json::Value root;
		Json::Reader reader;
		if (!reader.parse(inFile, root) || !root.isObject())
		{
			return ExitCodeResultFileUnreadable;
		}
		return root.get("Success", false).asBool() ? ExitCodeSuccess : ExitCodeEngineFailed;
	}
}
