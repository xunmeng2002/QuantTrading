#pragma once

// 配置 DbType → 适配器实例. 四个后端走**同一条路** (DbAdapters::LoadDatabaseBackend), 本函数不写
// "哪个后端怎么建"的知识 —— 哪个种类对应哪个模块、模块名的平台前后缀与调试后缀怎么拼, 都是
// DbAdapters 的内部知识. 本仓某个模块与适配器有编译期依赖时, 那条依赖写在 CMakeLists 的链接行上,
// 不写在这里 —— 依赖变了不必回来改这个函数.
// 失败一律 "写日志 + 返回 nullptr", 不抛: 适配器是在 SimExchange 构造函数里建的, 抛出点不在宿主
// 的 try 作用域内, 异常会以 std::terminate 收场 —— 而 abort 既不 flush stdio 缓冲也不走日志器的
// ThreadExit, 日志器那条后台线程缓冲的文案随之消失, 留下的是一份 0 字节日志 (实测 DbType="9":
// 退出码 0xC0000409, 日志 0 字节). 返回 nullptr 则走引擎既有的判空通路, 进程正常退出, 文案落进日志.
// 装载机制、查找次序与"模块缺了怎么办"见 DbAdapters 仓的 docs/backend-runtime-loading.md.

#include <DbAdapters/BackendLoader/DbBackendLoader.h>
#include <DbAdapters/DbInterface/Db.h>
#include <Spark/Core/Logger/Logger.h>
#include <Spark/Types.h>

#include <optional>
#include <string>

namespace QuantTrading
{
    // 配置 DbType → 后端种类. 配置取值就是 DbTypeType 的枚举值 (Model/Configs/*.xml 把 DbType
    // 声明成 int, 生成的 Config 逐字读它), 故这里只剩"校验 + 恒等转换", 没有自己的字面量表.
    // 越界一律返回空 optional —— 若静默退化成缺省, 一个写错的 DbType 会跑出一份看着正常的回测
    // 结果, 那是查不出来的.
    inline std::optional<DbTypeType> ParseDatabaseType(int dbType)
    {
        switch (dbType)
        {
        case static_cast<int>(DbTypeType::DuckDb):   return DbTypeType::DuckDb;
        case static_cast<int>(DbTypeType::SqliteDb): return DbTypeType::SqliteDb;
        case static_cast<int>(DbTypeType::MysqlDb):  return DbTypeType::MysqlDb;
        case static_cast<int>(DbTypeType::MariaDb):  return DbTypeType::MariaDb;
        default: return std::nullopt;
        }
    }

    // 这条文案是唯一一处机器可读的合法取值声明 —— 配置模型只声明 DbType 是 int, 没有取值域.
    // 数值全部取自枚举, 人读的名字是展示用, 只在这条文案里出现.
    inline std::string UnknownDatabaseTypeMessage(int dbType)
    {
        return "配置 DbType = " + std::to_string(dbType) + " 不是已知的后端: 合法取值为 "
            + std::to_string(static_cast<int>(DbTypeType::DuckDb)) + " (DuckDB) / "
            + std::to_string(static_cast<int>(DbTypeType::SqliteDb)) + " (SQLite, 缺省) / "
            + std::to_string(static_cast<int>(DbTypeType::MysqlDb)) + " (MySQL) / "
            + std::to_string(static_cast<int>(DbTypeType::MariaDb)) + " (MariaDB).";
    }

    // 失败出口: 文案落日志并交出空指针. 两件事绑在一处, 免得某个失败分支只记不发或只发不记.
    [[nodiscard]] inline DbAdapters::Db* ReportDatabaseAdapterFailure(const std::string& failureMessage)
    {
        WriteLog(Spark::Core::LogLevel::Error, "%s", failureMessage.c_str());
        return nullptr;
    }

    // 越界取值在这里就挡下 (这条文案列明四个合法取值), 不交给装载器 —— 后者只知道"种类越界",
    // 说不出合法取值是哪几个.
    inline DbAdapters::Db* CreateDatabaseAdapter(
        int dbType,
        const std::string& dbHost,
        const std::string& dbUser,
        const std::string& dbPassword)
    {
        const std::optional<DbTypeType> databaseType = ParseDatabaseType(dbType);
        if (!databaseType.has_value())
        {
            return ReportDatabaseAdapterFailure(UnknownDatabaseTypeMessage(dbType));
        }

        try
        {
            return DbAdapters::LoadDatabaseBackend(*databaseType, dbHost, dbUser, dbPassword);
        }
        catch (const std::exception& loadFailure)
        {
            return ReportDatabaseAdapterFailure(
                std::string("数据库适配器加载失败: 该后端由配置 DbType = ") + std::to_string(dbType)
                + " 选中, 但未能取到它 —— " + loadFailure.what()
                + "; 请补齐该模块, 或把 DbType 改回 " + std::to_string(static_cast<int>(DbTypeType::SqliteDb)) + ".");
        }
    }
}
