#!/usr/bin/env python
"""回测基本数据种子库生成器。

用法：

    python makeseeddb.py bin/Release/BackTestInit.db
    python makeseeddb.py bin/Release/BackTestInit.db <CSV 目录>

第一式写出内置最小种子（A 股三只标的）；第二式额外从给定目录读 <表名>.csv 取行。

**列序即 `src/Mdb/MdbStructs.cpp` 的字段序，改这里之前先核对那边的 GetSchema。**
引擎侧读库走 `SELECT *` 加列下标绑定，列序错会静默错位且不报错。

SQLite 是二进制产物，不进版本库（输出落在 /bin 下即被 .gitignore 覆盖）。
"""

from __future__ import annotations

import csv
import os
import sqlite3
import sys
from contextlib import closing
from dataclasses import dataclass


DIRECTION_BUY = 0
DIRECTION_SELL = 1
PRODUCT_CLASS_STOCK = 6
COMMISSION_GROUP_DEFAULT_ID = 1
DEFAULT_DATABASE_PATH = os.path.join("bin", "Release", "BackTestInit.db")


@dataclass(frozen=True)
class SeedTable:
    """一张种子表：列序、主键与内置行。列序即 C++ 结构体的字段序，是列下标绑定的依据。"""

    table_name: str
    columns: tuple[tuple[str, str], ...]
    primary_key_columns: tuple[str, ...]
    default_rows: tuple[tuple[object, ...], ...]

    def column_names(self) -> tuple[str, ...]:
        return tuple(column_name for column_name, _ in self.columns)


def build_a_share_commission_rows(exchange_id: str, instrument_id: str) -> tuple[tuple[object, ...], ...]:
    """A 股费率两行：卖出单边印花税写在 Sell 行的平仓侧，买卖各自的开平费率分列两行。"""
    return (
        (COMMISSION_GROUP_DEFAULT_ID, exchange_id, instrument_id, DIRECTION_BUY,
         0.00025, 0.0, 0.0, 0.0, 0.0, 0.0, 0.00001, 0.00001, 5.0, 0.0),
        (COMMISSION_GROUP_DEFAULT_ID, exchange_id, instrument_id, DIRECTION_SELL,
         0.0, 0.00025, 0.0, 0.0, 0.0, 0.0005, 0.00001, 0.00001, 5.0, 0.0),
    )


COMMISSION_GROUP_TABLE = SeedTable(
    table_name="CommissionGroup",
    columns=(("CommissionGroupId", "int"), ("CommissionGroupName", "char(64)")),
    primary_key_columns=("CommissionGroupId",),
    default_rows=((COMMISSION_GROUP_DEFAULT_ID, "Default"),),
)

# 品种只登记到三位代码，且 ProductClass 必须是 Stock：InitMainInstrument 只对 Future
# 造 .Hot/.Second/.Third，写成 Future 会凭空多出一批主力合约
PRODUCT_TABLE = SeedTable(
    table_name="Product",
    columns=(
        ("ExchangeId", "char(8)"),
        ("ProductId", "char(32)"),
        ("ProductName", "char(32)"),
        ("ProductClass", "int"),
        ("VolumeMultiple", "int"),
        ("PriceTick", "double"),
        ("MaxMarketOrderVolume", "bigint"),
        ("MinMarketOrderVolume", "bigint"),
        ("MaxLimitOrderVolume", "bigint"),
        ("MinLimitOrderVolume", "bigint"),
        ("SessionName", "char(32)"),
    ),
    primary_key_columns=("ExchangeId", "ProductId"),
    default_rows=(
        ("SSE", "600", "股票", PRODUCT_CLASS_STOCK, 1, 0.01, 0, 0, 0, 0, ""),
        ("SZSE", "000", "股票", PRODUCT_CLASS_STOCK, 1, 0.01, 0, 0, 0, 0, ""),
    ),
)

BASE_COMMISSION_TABLE = SeedTable(
    table_name="BaseCommission",
    columns=(
        ("CommissionGroupId", "int"),
        ("ExchangeId", "char(8)"),
        ("InstrumentId", "char(32)"),
        ("Direction", "int"),
        ("OpenByMoney", "double"),
        ("CloseByMoney", "double"),
        ("OpenByVolume", "double"),
        ("CloseByVolume", "double"),
        ("OpenStampTaxByMoney", "double"),
        ("CloseStampTaxByMoney", "double"),
        ("OpenTransferFeeByMoney", "double"),
        ("CloseTransferFeeByMoney", "double"),
        ("MinCommission", "double"),
        ("MaxCommission", "double"),
    ),
    primary_key_columns=("CommissionGroupId", "ExchangeId", "InstrumentId", "Direction"),
    default_rows=tuple(
        row
        for exchange_id, instrument_id in (("SSE", "600000"), ("SSE", "600519"), ("SZSE", "000001"))
        for row in build_a_share_commission_rows(exchange_id, instrument_id)
    ),
)

SEED_TABLES = (COMMISSION_GROUP_TABLE, PRODUCT_TABLE, BASE_COMMISSION_TABLE)


def convert_csv_cell(column_type: str, raw_value: str) -> object:
    """空数值列按 0 处理：Dump 出来的 CSV 里缺列就是空串，语义上等于不收费/不限制。"""
    if column_type.startswith("char"):
        return raw_value
    if column_type == "double":
        return float(raw_value) if raw_value.strip() else 0.0
    return int(raw_value) if raw_value.strip() else 0


def load_rows_from_csv(csv_dir: str, table: SeedTable) -> tuple[tuple[object, ...], ...]:
    csv_path = os.path.join(csv_dir, f"{table.table_name}.csv")
    # utf-8-sig：本仓的 CSV 多数带 BOM，按 utf-8 读会让首列名多出一个不可见字符
    with open(csv_path, encoding="utf-8-sig", newline="") as csv_file:
        reader = csv.reader(csv_file)
        header = tuple(next(reader))
        if header != table.column_names():
            raise ValueError(f"{csv_path} 表头与 {table.table_name} 的列序不一致：{header} != {table.column_names()}")
        return tuple(
            tuple(convert_csv_cell(column_type, raw_value) for (_, column_type), raw_value in zip(table.columns, raw_row))
            for raw_row in reader
            if raw_row
        )


def create_table(connection: sqlite3.Connection, table: SeedTable) -> None:
    column_definitions = ", ".join(f"{column_name} {column_type}" for column_name, column_type in table.columns)
    primary_key = ", ".join(table.primary_key_columns)
    connection.execute(f'DROP TABLE IF EXISTS "{table.table_name}"')
    connection.execute(f'CREATE TABLE "{table.table_name}"({column_definitions}, PRIMARY KEY({primary_key}))')


def insert_rows(connection: sqlite3.Connection, table: SeedTable, rows: tuple[tuple[object, ...], ...]) -> None:
    placeholders = ", ".join("?" for _ in table.columns)
    connection.executemany(f'INSERT INTO "{table.table_name}" VALUES ({placeholders})', rows)


def write_seed_database(database_path: str, csv_dir: str | None) -> None:
    output_dir = os.path.dirname(database_path)
    if output_dir:
        os.makedirs(output_dir, exist_ok=True)
    # closing 管连接、connection 管事务：sqlite3 的上下文管理器只提交事务，不会关连接
    with closing(sqlite3.connect(database_path)) as connection:
        with connection:
            for table in SEED_TABLES:
                rows = load_rows_from_csv(csv_dir, table) if csv_dir else table.default_rows
                create_table(connection, table)
                insert_rows(connection, table, rows)
                print(f"{table.table_name}: {len(rows)} 行")


def main() -> int:
    if len(sys.argv) > 3:
        print("用法：python makeseeddb.py [输出.db] [CSV 目录]")
        return 1
    database_path = sys.argv[1] if len(sys.argv) > 1 else DEFAULT_DATABASE_PATH
    csv_dir = sys.argv[2] if len(sys.argv) > 2 else None
    try:
        write_seed_database(database_path, csv_dir)
    except (OSError, ValueError, sqlite3.Error) as error:
        print(f"生成种子库失败：{error}")
        return 1
    print(f"已写出种子库：{database_path}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
