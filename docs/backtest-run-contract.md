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

**唯一的例外是 `MdDataPath`。** 历史行情是**只读输入**，多个 job 共享同一份 parquet 是预期用法，
不参与隔离：调度侧可以把它写成指向共享行情根的**绝对路径**，也可留成相对 CWD 的路径（本仓开发用的
`BackTest.json` 就是后者：`../../MdBaoStock` 即仓根下的 `MdBaoStock`，要求每个工作副本的仓根各备一份；
VS WSL 源码副本的那一份由其源码同步带来）。引擎不为此做任何特殊处理，一律按 CWD 解析。

> **豁免的边界**：本条**只**适用于只读输入。`DbHost`、`DbInitHost`、`DumpPath`、`result.json`
> 等**产物**路径必须留在 CWD，任何绝对化都会让隔离静默失效。

**引擎根与工作目录是两回事。** 扩展模块（Windows `QuantTrading.cp314-win_amd64.pyd`）、
`BackTest.dll` 及其运行时 DLL 住在**引擎根**（本仓的 `bin/<CONFIG>`），由调度侧经 `PYTHONPATH`
指向，**不**拷进 job 工作目录。引擎根里另有一份构建期生成的 `engine-version.txt`（首行即版本号，
与 `CMakeLists.txt` 的 `project() VERSION` 同源），供调度侧记录「这一轮跑的是哪个引擎构建」。

---

## 2. 结果文件 `result.json`

引擎在收尾阶段（结算与 Dump 完成之后、行情结束通知之前）把它写到 `<CWD>/result.json`。
**行数一律取自内存表**，不是输出库——输出库由异步写线程落盘，收尾时并不完整。

键名一律 PascalCase，与 `src/BackTest/RunResult.h` 的 `RunResult` 成员名一一对应。
契约只在该结构体里定义一次。`SchemaVersion` 目前为 `2`（`1` 里三项费用读的是最后一日，已废弃）。

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
| `MarketDataType` | string | 消费的行情类型：`Bar` / `Tick` |
| `MdSubscribeCount` | int | 行情订阅表行数 |
| `BarMarketDataCount` | int | bar 行情表行数 |
| `DepthMarketDataCount` | int | tick 快照表行数（见注二） |
| `InstrumentCount` | int | 合约表行数 |
| `OrderCount` | int | 委托表行数 |
| `TradeCount` | int | 成交表行数 |
| `HasCapital` | bool | 是否取到资金行 |
| `Balance` | double | 期末权益 |
| `Available` | double | 期末可用资金 |
| `TotalCommission` | double | 整轮佣金累计 |
| `TotalStampTax` | double | 整轮印花税累计 |
| `TotalTransferFee` | double | 整轮过户费累计 |
| `CommissionMissingCount` | int | 未命中费率的成交笔数（见注三） |
| `CommissionZeroRateKeyCount` | int | 未命中费率的去重键数 |
| `MissingRateKeys` | string[] | 缺失的费率键，上限 200 条 |
| `VolumeMultipleFallbackProductCount` | int | 乘数兜底为 1 的品种数 |

> **注一（口径）**：`Balance` / `Available` 是**状态值**，取 `LastTradingDay` 当日的资金行；
> `Total*` 与各 `*Count` 是**整轮累计值**。资金表本身是**逐日流量**——引擎每天把它清零后只装当日数，
> 所以整轮费用必须跨行相加，**不能读最后一行**（那不是缺陷，是结算表的设计）。

> **注二（两个行情计数互斥非零）**：引擎按 `MatchMode` 只消费一种行情，由 `MarketDataType` 指明是哪种。
> `Bar` 模式下引擎不写 tick 表，故 `DepthMarketDataCount` 恒为 0；`Tick` 模式下 `BarMarketDataCount` 为 0。
> 另注意 tick 表按 `(交易日, 交易所, 合约)` 主键就地更新，它是**每日每合约一条快照**，不是 tick 条数。

> **注三（零成交时费率缺口是真空的）**：`CommissionMissingCount` 与 `MissingRateKeys` 只在
> `TradeCount > 0` 时有意义——零成交时它们为 0 与空数组，**不代表费率齐全**，只代表一笔都没查过。

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

`方向` 取 `DirectionType` 的数值（`Buy=0`、`Sell=1`），可直接抄进种子库的 `Direction` 列。**这里只会
出现 0 与 1 两值**：平台侧那档"双向"（`-1`）在写种子库之前就被摊成了买、卖两行，引擎看不到它 ——
于是缺费率时报出的也是具体方向，而不是"两侧都缺"这种含糊说法。

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

> ⚠️ **2026-10-07 起：种子库由 QuantPlatform 按轮生成，本节的手工路径退化为历史遗留**
> （`makeseeddb.py` 与 `Configs/SeedCsv/` 文件保留、不再执行）。平台在**每一轮开始前**从它自己的
> catalog 现造一份 `BackTestInit.db`，落在**该轮作业目录里**（与引擎同机，路径由该轮 `BackTest.json`
> 的 `DbInitHost` 指向），且**只含该轮用到的合约**的行。费率的**合约 / 品种 / 交易所三级**规则、
> 以及平台侧的**买卖双向**那一档（`Direction = -1`，"买卖共用这一套费率"）都在生成时被摊成具体
> 合约 × 具体方向的行，故**引擎只看得到 `(ExchangeId, InstrumentId)` 两格、`Direction` 只有
> 0 与 1**，下文那次精确查找无需任何改动。本机 `bin/*/BackTestInit.db` **从此无人维护**——在 WSL 里手工跑
> `TestBackTest` 时要它的场合得自己补一份。
> 契约不变——引擎侧零改动，本节以下的**列序与列名要求、以及缺失时的降级行为**仍然逐字适用，
> 它们现在也是核对平台那份实现的依据。详见 QuantPlatform 仓的 `docs/platform-plan.md` §14 与
> `docs/acceptance-checklist.md` §16。

种子库是 SQLite 二进制产物，不进版本库（`/bin` 已被 `.gitignore` 覆盖）。按各配置手工执行一次（**仅供手工补种，见上框**）：

```text
python makeseeddb.py bin/Release/BackTestInit.db
```

脚本只依赖标准库 `sqlite3`，写出**内置**最小种子（A 股三只标的：品种 2 行、费率组 1 行、费率 6 行）。要换一批标的时再给一个 CSV 目录：

```text
python makeseeddb.py bin/Release/BackTestInit.db Configs/SeedCsv
```

> ⚠️ **上面这第二式是「取代」而非「叠加」，而这条命令本身会毁掉内置费率——别照抄。**
> 给了目录就逐表读 `<CSV 目录>/<表名>.csv`，**内置行一行不留**；该目录还须**三张表齐备**，缺文件即报错退出。
> 本仓 `Configs/SeedCsv/` 里 `Product.csv` 有 2 行，而 `CommissionGroup.csv` 与 `BaseCommission.csv`
> **只有表头**（空表只能用有表头无数据行表达），故照抄这条会把内置的 1 行组与 6 行费率**清成 0 行**，
> 费率随即全按 0 计（`result.json` 的 `CommissionMissingCount` 会当场报出来）。要换标的时，
> 须自己准备一个**三表齐备**的目录再跑第二式。

写入的行**表头即列序**，与预期列序不符会被拒绝而不是静默错位。两种方式都只重建
`CommissionGroup` / `Product` / `BaseCommission` 三张表，其余表不受影响。

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
- **手续费组号来自该轮的 `BackTest.json`**（`CommissionGroupId`），**引擎侧无需任何改动**：这个键本来
  就由 `Config` 解析（`src/BackTest/Config/Config.cpp:53`）、由 `SimExchange` 记下
  （`src/BackTest/SimExchange.cpp:106`）并在建账号时带上（`src/BackTest/SimExchange.cpp:786`）。
  2026-10-07 起 QuantPlatform 把它当**运行级字段**逐轮写入（从前那里写死常量 `1`），于是"这一轮用
  哪一套费率"与该轮的其它取值一样，在提交那一刻就冻结了。
- 买卖差异由**数据**表达：A 股在 `Buy` 行填开仓侧、`Sell` 行填平仓侧与印花税；港股两行都填印花税。
- `MinCommission` 与 `MaxCommission` 为 0 或负值表示不设限，且**只封佣金**。
- 封底封顶**按每笔成交**执行，故 N 笔部分成交最多产生 `N × MinCommission`。
