# 回测运行契约

本文落定回测引擎与调度侧之间的接口：工作目录假设、结果文件 `result.json` 的字段与语义、宿主退出码，
以及基本数据种子库的生成方式。调度器、宿主与产物消费者都以本文为准。

---

## 1. 工作目录假设

**引擎的全部输入路径与产物路径都是相对当前工作目录（CWD）解析的。**

- `BackTest.json` 由引擎从 CWD 读取。
- `SessionFile`、`DumpPath`、`DbHost`、`DbInitHost` 同理。
- 结果文件固定在 `<CWD>/result.json`。

> **这条假设是「每 job 独立工作目录」隔离的全部依据。** 谁把 `BackTest.json` 里任一路径写成绝对路径，
> 或把引擎改成绝对路径，隔离就会**静默失效**——两个并发 job 会写同一个库且不报错。
> 调度侧必须为每个 job 分配独立的工作目录，并在其中放入 `BackTest.json` 与 `Sessions.json`。

---

## 2. 结果文件 `result.json`

引擎在收尾阶段（结算与 Dump 完成之后、行情结束通知之前）把它写到 `<CWD>/result.json`。
**行数一律取自内存表**，不是输出库——输出库由异步写线程落盘，收尾时并不完整。

键名一律 PascalCase，与 `src/BackTest/RunResult.h` 的 `RunResult` 成员名一一对应。
契约只在该结构体里定义一次。`SchemaVersion` 目前为 `1`。

| 键 | 类型 | 说明 |
| ---- | ---- | ---- |
| `SchemaVersion` | int | 契约版本 |
| `RunId` | string | 本次运行标识 |
| `Success` | bool | `ErrorId == 0` 即为 true |
| `ErrorId` | int | 首个错误码，0 表示无错 |
| `ErrorMsg` | string | 错误码对应的成因说明 |
| `DumpPath` | string | 产物目录 |
| `DbPath` | string | 输出库实际路径 |
| `StartTradingDay` | string | 配置的起始交易日 |
| `EndTradingDay` | string | 配置的结束交易日 |
| `LastTradingDay` | string | 实际走到的最后交易日 |
| `AccountId` | string | 注册的账户 |
| `BasicDataLoaded` | bool | 种子库是否装载成功 |
| `MdSubscribeCount` | int | 行情订阅表行数 |
| `BarMarketDataCount` | int | bar 行情表行数 |
| `DepthMarketDataCount` | int | tick 行情表行数 |
| `InstrumentCount` | int | 合约表行数 |
| `OrderCount` | int | 委托表行数 |
| `TradeCount` | int | 成交表行数 |
| `HasCapital` | bool | 是否取到资金行 |
| `Balance` | double | 权益 |
| `Available` | double | 可用资金 |
| `Commission` | double | 佣金合计 |
| `StampTax` | double | 印花税合计 |
| `TransferFee` | double | 过户费合计 |
| `CommissionMissingCount` | int | 未命中费率的成交笔数 |
| `CommissionZeroRateKeyCount` | int | 未命中费率的去重键数 |
| `MissingRateKeys` | string[] | 缺失的费率键，上限 200 条 |
| `VolumeMultipleFallbackProductCount` | int | 乘数兜底为 1 的品种数 |

### 2.1 `ErrorId` 取值

目前只有一条会让整轮判定为失败：

| 错误码 | 触发条件 |
| ---- | ---- |
| `0x100F` | 无任何有效订阅、bar 周期无法聚合、或行情零行 |

以下情形属**部分降级**，只记日志与计数，**不置错误**：部分订阅被丢弃、部分合约查不到、
tick 早于当前交易日、费率行缺失（后者由 `CommissionMissingCount` 体现）。

### 2.2 `MissingRateKeys` 的键格式

```text
<手续费组>|<交易所>|<合约>|<方向>
```

`方向` 取 `DirectionType` 的数值（`Buy=0`、`Sell=1`），可直接抄进种子库的 `Direction` 列。

---

## 3. 退出码契约

| 码 | 含义 | 判定方式 |
| ---- | ---- | ---- |
| `0` | 成功 | 文件存在、可解析、`Success` 为 true |
| `1` | 宿主启动失败 | `api->Init()` 或 `strategy.start()` 返回 false |
| `2` | 结果文件缺失或不可解析 | 打不开或解析失败 |
| `3` | 引擎明确报告失败 | 文件可解析且 `Success` 为 false |

**陈旧结果防护**：三个宿主都在启动策略**之前**删除 `<CWD>/result.json`。
这样「文件不存在」就等价于「本轮没走完收尾」，调度器复用工作目录也不会读到上一轮残留。

> **已知歧义**：MSVC 下 `abort()` 与未捕获异常同样返回 3，与「引擎报告失败」同码。
> 消歧只能靠文件：码 3 且存在可解析的 `result.json` 即引擎报告失败；码 3 且无文件即崩溃。

---

## 4. 基本数据种子库

`Product`、`CommissionGroup`、`BaseCommission` 三张表由种子库提供，其余表由引擎自建。
种子库缺失**不会**让回测失败，只会让费率全部按 0 计费并把缺口写进 `result.json`。

### 4.1 生成

种子库是 SQLite 二进制产物，不进版本库（`/bin` 已被 `.gitignore` 覆盖）。按各配置手工执行一次：

```text
python makeseeddb.py bin/Release/BackTestInit.db
```

脚本只依赖标准库 `sqlite3`，写出内置最小种子（A 股三只标的）。要换一批标的时再给一个 CSV 目录：

```text
python makeseeddb.py bin/Release/BackTestInit.db Configs/SeedCsv
```

此时三张表的行取自 `<CSV 目录>/<表名>.csv`，**表头即列序**，与预期列序不符会被拒绝而不是静默错位。
两种方式都只重建 `CommissionGroup` / `Product` / `BaseCommission` 三张表，其余表不受影响。

**表名与列序必须严格对齐 `MdbStructs.cpp` 的字段序**——
SQLite 读取是 `SELECT *` 加按列下标绑定，列序错会静默错位。

### 4.2 首轮发现式播种

不另开 CSV 通道，费率行的落点就是种子库本身：

1. 直接跑一轮，不看日志。
2. 从 `result.json` 的 `MissingRateKeys` 与 `VolumeMultipleFallbackProductCount` 抄出缺口。
3. 补齐种子后重新导出种子库。
4. 再跑一轮，`CommissionMissingCount == 0` 即为验收通过。

---

## 5. 费用口径

`Trade`、`Position`、`PositionDetail`、`Capital` 四张表各带三列费用，**互不合并**：
`Commission` 只装佣金，`StampTax` 与 `TransferFee` 各归各列。

```text
佣金   = 成交金额 × 金额侧费率 + 手数 × 手数侧费率
佣金   = Clamp(佣金, MinCommission, MaxCommission)
印花税 = 成交金额 × 印花税费率
过户费 = 成交金额 × 过户费率
```

- 费率按 `(手续费组, 交易所, 合约, 方向)` 取行，**方向不参与取列**。
- 买卖差异由**数据**表达：A 股在 `Buy` 行填开仓侧、`Sell` 行填平仓侧与印花税；港股两行都填印花税。
- `MinCommission` 与 `MaxCommission` 为 0 或负值表示不设限，且**只封佣金**。
- 封底封顶**按每笔成交**执行，故 N 笔部分成交最多产生 `N × MinCommission`。
