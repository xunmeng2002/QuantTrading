#include "OrderUtility.h"
#include "TestHelpers.h"

#include "MdbTables.h"

#include "doctest/doctest.h"

using namespace quanttrading::ordermatch;
using namespace quanttrading::unittest;

TEST_SUITE("OrderIDSeed")
{

TEST_CASE("SeedNextOrderIDFromMaxOrderID只上移计数器(H17回归)")
{
    SeedNextOrderIDFromMaxOrderID(900000);
    auto first_id = GetNextOrderID();
    CHECK(first_id >= 900001);
    CHECK(GetNextOrderID() == first_id + 1);

    // 更小的种子不得把计数器拉低
    SeedNextOrderIDFromMaxOrderID(899999);
    CHECK(GetNextOrderID() == first_id + 2);
}

TEST_CASE("SeedNextOrderIDFromOrders从订单表最大OrderID续接(H17回归)")
{
    mdb::OrderTable order_table;
    PoolRecordGuard<mdb::Order> order_pool;
    for (int order_id : {7, 3, 9999999})
    {
        auto* order = order_pool.Create();
        order->OrderID = order_id;
        order->ClientOrderID = order_id;
        REQUIRE(order_table.Insert(order));
    }

    SeedNextOrderIDFromOrders(&order_table);
    CHECK(GetNextOrderID() == 10000000);
}

}
