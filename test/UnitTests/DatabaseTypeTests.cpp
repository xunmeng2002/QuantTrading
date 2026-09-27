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

TEST_CASE("越界取值下工厂交出空指针而不是抛异常")
{
    // 越界在这条路上是确定性的: 查表那一步就挡下了, 一个模块都不会碰, 故不依赖 bin 下
    // 摆了哪些适配器. WriteLog 是宏, 未设外部日志器时是空操作, 故也不依赖日志器已启动.
    CHECK(CreateDatabaseAdapter(9, "", "", "") == nullptr);
    CHECK(CreateDatabaseAdapter(-1, ":memory:", "", "") == nullptr);
}

// "装不到模块时交出空指针"那条同样只由端到端探针覆盖 —— 它取决于引擎目录里摆了哪些适配器,
// 且要把两次尝试的原因都报出来, 不是单测该模拟的东西.

}
