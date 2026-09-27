#include "DatabaseAdapterFactory.h"

#include "doctest/doctest.h"

#include <optional>
#include <string>

using namespace QuantTrading;

TEST_SUITE("DatabaseType")
{

TEST_CASE("配置里的DbType整数映射到后端种类")
{
    CHECK(ParseDatabaseType(0) == DbTypeType::DuckDb);
    CHECK(ParseDatabaseType(1) == DbTypeType::SqliteDb);
    CHECK(ParseDatabaseType(2) == DbTypeType::MysqlDb);
    CHECK(ParseDatabaseType(3) == DbTypeType::MariaDb);
}

TEST_CASE("越界的DbType一律解析失败而不静默退化成某个后端")
{
    for (const int outOfRangeDbType : { 4, 5, 99, -1, 100 })
    {
        CHECK_FALSE(ParseDatabaseType(outOfRangeDbType).has_value());
    }

    // 报出的文案要含全部合法取值 —— 配置模型只声明 DbType 是 int, 没有取值域,
    // 故这条文案是唯一一处机器可读的合法取值声明.
    const std::string message = UnknownDatabaseTypeMessage(9);
    CHECK(message.find("9") != std::string::npos);
    for (const int legalDbType : { 0, 1, 2, 3 })
    {
        CHECK(message.find(std::to_string(legalDbType)) != std::string::npos);
    }
    CHECK(message.find("DuckDB") != std::string::npos);
    CHECK(message.find("SQLite") != std::string::npos);
    CHECK(message.find("MySQL") != std::string::npos);
    CHECK(message.find("MariaDB") != std::string::npos);
    CHECK(message.find("缺省") != std::string::npos);
}

// CreateDatabaseAdapter 本身的"失败即返回空指针而不抛"不在此处断言: 该函数体内含
// new DuckdbWrapper/SqliteWrapper, 链接它会逼单测依赖两个 wrapper 的导入库. 这条契约由
// 端到端探针覆盖 —— DbType=9 下宿主退出码为 ExitCodeHostInitFailed, 且日志里有一条
// 列明合法取值的 ERROR.

}
