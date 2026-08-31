# 项目进度跟踪

> 按 Harness 规则 8 维护：每次会话结束更新。新会话开始先读本文件。

## 项目定位

CTP 期货量化交易系统（C++20），当前处于**前期整理阶段**，已实现行情服务 **MdOffer**，交易链路（TraderApiMiddle）已封装但未接入应用。

## ✅ 已完成

- **MdOffer 行情主流程**：CTP 订阅 → MdKernel 单线程事件循环 → Mdb 内存表 + AsyncDBWriter 异步落库 → MdFront 广播；支持 4 种 DB（DuckDB/SQLite/MySQL/MariaDB）。
- **2026-08-08 设计分析 + P0/P1 修复**：
  - P0-1 夜盘 `TradingDay` 归属修复（改用 CTP `TradingDay`，空时回退 `ActionDay`）— `src/MdOffer/ThostFtdcMdSpiImpl.cpp`
  - P0-2 订阅字段生命周期重构（**值集合**：全局 `std::set<ReqSubMarketDataField>` 去重并持进程级节点，会话集合每会话一份、断开整行 `erase`；消除对象池手动分配/释放、canonical 拷贝、`IsGlobalCanonical`；`SubscribeMd/SubscribeMds` 接口 const 化）— `src/MdOffer/MdKernel.{h,cpp}`、`src/MdOffer/FieldsCompare.{h,cpp}`、`src/MdOffer/ThostFtdcMdSpiImpl.{h,cpp}`
  - P1-1 CTP 断线重置登录态（`OnFrontDisconnected` 置 `m_IsLogged=false`）— `src/MdOffer/ThostFtdcMdSpiImpl.cpp`
  - P1-2 按配置 `DbType` 分发数据库（替代硬编码 SqliteWrapper）— `src/MdOffer/Main.cpp`
  - 全部通过 x64-Debug 编译验证（MdOffer.exe 链接成功）。
- **2026-08-09 DBAdapters 向量化批量读扩展**（`D:\Gitee\DBAdapters`，独立仓库）：
  - `DuckdbWrapper` 新增 `SelectWithSqlVectorized`（chunk 向量逐列绑定，DECIMAL 经 `duckdb_decimal_to_double` 精确转换，NULL 写入类型哨兵：Double→+inf、Int/Int64→0、Char→空串、Bool→false；错误透出 duckdb 错误信息）。
  - `TestDB` 新增 `TestDuckdbVectorized` 用例并通过（DECIMAL(24,8)→double、NULL→+inf、错误传播均 PASS），x64-Debug 编译 + 运行验证完成。
  - 为 MdReader 由逐行 `duckdb_value_*` 迁移到向量化读预留接口（SQL 列序须与 schema 字段序对应）。
- **2026-08-09 MdReader 迁移向量化读**（`src/BackTest/MdReader.{h,cpp}`）：
  - 迁移到 `DuckdbWrapper::SelectWithSqlVectorized`，消除手写逐列绑定的 DRY 违规；MdReader.cpp.obj TU 级编译通过。
  - **附带修复 DBAdapters 真实 bug**：`duckdb_value_*` 访问器在流式（`duckdb_fetch_chunk`）结果上失效，导致向量化读值全部为空——所有类型转换改为仅从 chunk 向量 raw data 推导；`TestDB` 新增 `TestDuckdbVectorizedMultiChunk`（6000 行 / 3 chunk 跨边界回归）并通过，修复后的 DLL 已 `cmake --install` 至 `D:\Gitee\Libs\DBAdapters\x64-windows`。
- **2026-08-10 MdReader 复用 mdb `GetSchema()`**（按用户决策，数据源将统一到 mdb 表结构）：
  - 删除本地投影 schema（`InstrumentReadFields`/`TickReadFields`/`TickReadSchema`/`InstrumentReadSchema`）与三个 factory，统一复用 `Instrument::GetSchema()` / `DepthMarketData::GetSchema()` / `BarMarketData::GetSchema()`；分配/追加回调收敛为通用模板 `MakeVectorizedRecordFactory<T>()`。
  - SQL 按 mdb 字段序 + mdb 列名重写（含 61 列 tick 全字段、15 列 instrument 全字段；Bar 也由 `LastTraded/LastTurnover` 改为 `CurrVolume/CurrTurnover`）。
  - **数据源依赖**：当前 parquet 缺 tick 的 6 列（OpenPrice/ClosePrice/SettlementPrice/Upper/LowerLimitPrice/AveragePrice）与 instrument 元数据列，且列名为 `AskPrices[1]`/`LastTraded` 等旧名——需数据源整理对齐 mdb 后 SQL 才可执行。旧 `PreOpenInterest`↔`OpenInterest` 交换在新序下自然消除，若旧数据该两列值本身是交换写入的，整理时需一并修正。
- **2026-08-13 Mdb 表类基类重构 + 表清单生成**：
  - 新增 `MdbTableBase`（`src/Mdb/MdbTableBase.h`），上收各表重复的 `m_DBInited` 及 Subscribe/UnSubscribe/InitDB/TruncateTables/Dump 公共接口；`src/Mdb/MdbTables.h` 由模板重新生成（全部表类改为 `public MdbTableBase` 并加 `override`）。
  - 新增 `src/Mdb/TableLists.h`：按 MdOffer / SimExchange / BackTest 分组输出表 ID 清单（`TableList` 结构 + `TableLists::MdOffer/SimExchange/BackTest`），`pumplist.xml` 已登记生成条目；当前尚无消费方，为后续统一 Mdb 管理预留。
  - 模板侧改动位于独立仓库 `D:\Gitee\Templates`（`Cpp/Mdb/MdbTables.h.tpl` 已改、`Cpp/Mdb/TableLists.h.tpl` 新建，未提交）。
  - x64-Debug 全量编译链接验证通过（2026-08-13）：MdbStatic、MdOffer.exe、SimExchange.exe、BackTestd.dll 均成功重建。
- **2026-08-13 Mdb 按需装配（on-demand assembly）**：Mdb 运行时从"全量 18 表"改为"按各模块 TableList 装配自己的表"：
  - `Mdb` 构造改为 `explicit Mdb(const TableList&)`，构造时按 `TableList.TableIDs` 只 `new` 本模块的表并存入 `m_Tables`（`std::vector<MdbTableBase*>`）；未装配表成员初始化为 `nullptr`，各 bulk 方法（Subscribe/UnSubscribe/InitDB/SetInitStatus/Dump/TruncateTables/OnDBDisConnected）统一遍历 `m_Tables`。
  - `MdbTableRegistry` 删除全量单例 `Instance()` 与默认构造，改为 `MdbTableRegistry(const TableList&)` 按模块过滤 schema（`m_TableIDs`/`m_Schemas`）。`AsyncDBWriter` 经 `GetAllSchemas()`/`GetTableCount()`/`GetSchema()` 取本模块 schema，故 **CreateTables / DropTables / TruncateTables 及所有写入只作用于本模块的表**；越界表 `GetSchema` 返回 `nullptr` 被跳过，机制上杜绝模块访问非本模块表。
  - `InitMdbFromDB` 删除 `LoadTablesWith/WithoutTradingDay`，统一为 `LoadTables(Mdb*, DB*, const TableList&)` 调度器；`InitMdbFromCsv` 的 `LoadTables` 改为 TableList 门控（`LoadTables(Mdb*, const char*, const TableList&)`）。
  - 装配点：`MdOffer/Main.cpp`、`SimExchange/Main.cpp` 用 `Mdb(MdOfferTableList)` / `Mdb(SimExchangeTableList)` + 局部 `MdbTableRegistry` 传 `AsyncDBWriter`；`BackTest/SimExchange.{h,cpp}` 新增成员 `m_Registry(BackTestTableList)` 并将 writer/Mdb 改用之。
  - 8 个模板同步（独立仓库 `D:\Gitee\Templates`：`Cpp/Mdb/Mdb.*.tpl`、`MdbTableRegistry.*.tpl`、`InitMdbFromDB.*.tpl`、`InitMdbFromCsv.*.tpl`），重新 pump 生成 `src/Mdb` 对应 8 文件并核对。
  - x64-Debug 编译链接验证通过（2026-08-13）：MdbStatic、MdOffer.exe、SimExchange.exe、BackTestd.dll 均成功重建（BackTest 阻断已随此前提交消除）。
- **2026-08-13 TableList 按模块落地（从共享核心拆分）**：
  - 共享类型：`src/Mdb/TableList.h`（`struct mdb::TableList`，去掉复数 `s`）；旧 `src/Mdb/TableLists.h` 删除，共享核心不再包含任何应用专属表集合，依赖方向修正（核心不感知消费者）。
  - 各模块清单落各自目录：`src/MdOffer/MdOfferTableList.h`（7 表）→ `mdb::MdOfferTableList`、`src/SimExchange/SimExchangeTableList.h`（14 表）→ `mdb::SimExchangeTableList`、`src/BackTest/BackTestTableList.h`（15 表）→ `mdb::BackTestTableList`。
  - 去掉 `TableLists::` 复数命名空间，调用点直呼变量名（`Mdb(MdOfferTableList)` 等）；文件按"模块名 + TableList"命名，避免与共享 `TableList.h` 同名 basename 冲突。
  - 模板：`TableLists.h.tpl` → `TableList.h.tpl`（纯类型）+ 新建 `ModuleTableList.h.tpl`（模型仍为各 `Model/TableNames/XxxTableNames.xml`）；`pumplist.xml` 拆为 1 条核心条目 + 3 条模块条目。
  - x64-Debug 编译链接验证通过（2026-08-13）：MdbStatic、MdOffer.exe、SimExchange.exe、BackTestd.dll 均成功重建。
- **2026-08-13 放弃按 TradingDay 单日导入，数据初始化改走专用 Init 库**：
  - 决策背景：原计划按表支持 `withtradingday` 导入某一天历史数据，但该属性是表级全局的，无法表达"同一表在 A 模块按日导入、B 模块全量导入"的按（模块 × 表）差异，且 `TypedTable` 仅提供 `SelectAll`，无法扩展按日查询。故整个功能废弃。
  - 数据初始化输入改为各应用已有的专用 Init 库（`DbInitHost` → `initDB` → `LoadTables` 全量 `SelectAll`），按日过滤职责从加载层前移到数据准备层，天然支持按模块差异。
  - 清理：`InitMdbFromDB.{h,cpp}.tpl` 移除 `!!if @withtradingday == 'true':!!` 条件段，加载器统一固定 2 参 `(Mdb*, DB*)`；`Model/Tables/ShortTables.xml` 中 `DepthMarketData` / `BarMarketData` 的 `withtradingday="true"` 属性移除。重新 pump 后生成文件无内容变化（本就为 2 参），x64-Debug 编译链接通过。
- **2026-08-13 API 测试客户端**（`test/`）：
  - ApiMiddle/SpiMiddle 封装由新模板 `Templates/Cpp/ApiTest/*.tpl` + `Model/Packages/Packages.xml` 生成（`test/ApiMiddles/{Md,Trader,SimExchange}ApiMiddle`），注册为 3 个静态库；`TestMdApi`/`TestTraderApi`/`TestSimExchangeApi` 三个测试 exe 均编译链接通过。
  - **安全修复**：`ApiMiddle.cpp.tpl` 生成日志时排除 `Password` 字段（逗号与字段均受 `@name != 'Password'` 保护），三个封装登录不再打印明文密码（原打印 UserID/AccountID + Password）。
  - **健壮性修复**（TestTraderApi/TestSimExchangeApi）：`m_Instrument` 裸指针 + `new` 泄漏 → 值成员 + `m_HasInstrument` 标志（消除泄漏与空指针解引用，查询无 CFFEX 合约时不再发单）；`ReqQryOrder`/`ReqAccountLogin` 补 `memset` 清零脏字节；`Main.cpp` 的 `while (!m_Finished)` 死等加 120s 超时兜底。
  - 遗留：`TestMdApi` 仍硬编码 `sleep(120s)`；C# 模板 `TableViews.razor.cs.tpl` 仍引用 `@withtradingday`（C# 侧计划整体重写，暂缓）。
- **2026-08-24 P1-1 重连路径并发修复 + 优雅退出**：
  - **并发修复**（`src/MdOffer/ThostFtdcMdSpiImpl.cpp`）：`OnRtnDepthMarketData` 反查 `m_ReqSubMds` 改同锁 `find()`（消除 `operator[]` 键缺失插入副作用）；`OnRspUserLogin` 重连补订改锁内取 `m_ReqSubInstruments` 快照后批量订阅。
  - **优雅退出**（新增 `src/QuantTradingCommon/ShutdownSignal.{h,cpp}`，改 `src/MdOffer/Main.cpp`、`src/SimExchange/Main.cpp`）：Windows `SetConsoleCtrlHandler` / Linux `signal(SIGINT/SIGTERM)` 仅置位原子标志；main 尾部由阻塞 Join 链改为「轮询退出标志 → 按依赖序 Stop/Join」。MdOffer 顺序：mdApi Release → mdKernel → mdFront → dbWriter → Logger；SimExchange：mdApi Release → simExchange → tradeFront → mdFront → dbWriter → Logger。
  - 依据库源码核实：所有 ThreadBase 派生线程 `Run()` 均以 `wait_for`/`select` 超时兜底，`Stop()` 后 ≤100ms 退出；`AsyncDBWriter` 退出前刷完剩余 `m_DBOperates`。全量 x64-Debug 编译链接通过，MdOffer.exe 启动冒烟通过；Ctrl+C 交互验证待真实控制台执行。
- **2026-08-24 BackTest 端到端验证**（TestBackTest，`D:\Md` 旧格式 parquet）：MdReader 读 tick/bar → OrderMatch 撮合（IF2503，20241001-20241231，61 根日 Bar、10 月 45 万+ tick）→ 结算 → 落库全链路跑通。注意：数据为旧列名格式，MdReader SQL 的 NULL 占位符与 `AskPrices[1]` 等旧列名兜底正是为此而设；撮合/结算正确性由 `GetSettlementPrice` 对 +inf 回退 + OrderMatch 涨跌停校验注释保证，数据真正对齐 mdb 前该回退不可移除。
- **2026-08-27 安全修复 S1–S4**（先修安全问题，按类型/名称过滤 + 配置驱动）：
  - **S1 行情日志脱敏**（模板 `Templates/Cpp/LibTest/CtpWrapper/StructLogFunc.cpp.tpl`，重新 pump `src/Ctp/StructLogFunc/StructLogFunc.cpp`）：定义 15 个 CTP 敏感类型集合（`TThostFtdcPasswordType`/`*KeyType`/`*AuthKeyType`/`*AuthenticDataType` 等），日志生成按类型过滤 Password/Key/Token 字段，逗号与字段均受保护；497 处 WriteLog 格式串/实参 0 失配，无敏感字段名残留。`WriteReqUserLogin` 不再打印 Password/OneTimePassword。
  - **S2 Environment 输出修复**（`src/QuantTradingCommon/Environment.cpp`）：`PrintEnvironment` 不再打印账户 `Password`/`AuthCode`（只输出 BrokerID/InvestorID/Phone/UserProductInfo/AppID）；`ReadEnvironment` 解析失败路径不再 `in_file >> s; std::cout << s;` 倾倒配置文件内容；输出全部改走 `WriteLog`（4 个调用点均在 Logger 启动后）。
  - **S3 Config 模板密码过滤**（`Templates/Cpp/Config/Config.cpp.tpl`，重新 pump 9 个 `src/*/Config/Config.cpp`）：`Print()` 顶层/记录字段/子记录三处统一按 `@name.lower().endswith('password')` 过滤（配置模型为扁平 string/int，无法按类型过滤）；9 个模块的配置文件打印不再输出 `DbPassword`/`MdPassword`。
  - **S4 MdOffer 种子用户配置化**（`Model/Configs/MdOffer.xml` + `Configs/MdOffer.json` + `src/MdOffer/Main.cpp`）：删除 `Main.cpp` 6 个死常量（sqliteDBName/duckdbDBName/mysqlHost/mariadbHost/mariadbUser/mariadbPassword）；`t_MdUser` 种子记录改由 `MdUserID`/`MdPassword` 配置驱动，`MdUserID` 为空时跳过插入（杜绝空凭证记录，防"空 UserID+空密码"登录）；默认值 `MdUser`/`123456` 与 `TestMdApi.json` 一致，测试登录不受影响。重新 pump 后 `Config.h` 新增两字段，`Print()` 按 S3 过滤不打印 `MdPassword`。**记录用 `MdUser::Allocate()` + `Utility::Strcpy` 逐字段填充**（MSVC 的 C++20 括号聚合初始化无法用字符串字面量初始化 `char[N]` 数组成员，初版 `new MdUser(...)` 触发 C2440；改用对象池分配，与 `Insert` 失败时表调用 `Deallocate()` 回池的契约一致）。x64-Debug 编译链接通过（MdOffer.exe）。
- **2026-08-27 评审修复 H10/H12（Mdb 模板）**：
  - **H10 对象池分配器不匹配**：`Templates/Cpp/Mdb/InitMdbFromCsv.cpp.tpl` 的 `new !!@name!!()` → `!!@name!!::Allocate()`；`MdbTables.cpp.tpl` 的 `InitDB` 内 `new !!$structName!!(**it)` → `!!$structName!!::Allocate()` + `memcpy`（与 `BatchInsert` 既有模式一致）。此前 `new` 分配的对象被 DB 订阅者经池 `Deallocate()` 回收 → 分配器不匹配/堆损坏；`ObjectPool<T>::Allocate()` 无参 placement-new `T()` 值初始化，与 `new X()` 零初始化语义完全一致，行为保持。重新 pump 生成 `src/Mdb/MdbTables.cpp`、`src/Mdb/InitMdbFromCsv.cpp`。
  - **H12 InitDB 空守卫**：`InitDB()` 无 `m_MdbSubscriber` 守卫，`OnRecordTruncate`/`OnRecordBatchInsert` 直接解引用 → 无订阅者时空指针崩溃；改为无订阅者提前返回（置 `m_DBInited=true`），并将锁作用域收敛到拷贝循环（对齐 `BatchInsert`，避免持共享锁调用订阅者回调）。重新 pump 后 x64-Debug 编译链接通过（MdOffer.exe）。
  - **H11 读方法锁契约（用户决策：仅记录文档，代码零改动）**：`Select`/`SelectAll`（主键）与 `LowerBound`/`UpperBound`/`EqualRange`（索引）内部 `std::shared_lock` 只保护查找本身，返回的裸指针/迭代器在锁释放后被使用。核查结论：全库无 `LockShared()` 调用者（无嵌套加锁死锁），表访问按模块串行化（MdKernel 单线程、SimExchange 各自 `m_Mutex`），**当前无活跃 bug，属潜在设计缺陷**。经用户确认不做代码改动，契约仅记录于此：**返回的指针/迭代器仅在调用方间串行访问表（无并发 Erase/Update/Truncate）时有效**。未来交易链路接入时若需跨线程改表，须在调用方持锁或改返回语义。x64-Debug 编译链接通过（MdOffer.exe）。
- **2026-08-27 评审修复 H13–H19（OrderMatch / SimExchange / Bar）**：
  - **H13 BackTest 包队列数据竞争**（`src/BackTest/SimExchange.{h,cpp}`）：测试线程 `ReqXxx` 对 `m_ReqSubMds`/`m_Packages` push、SimExchange 线程 `HandlePackages`/`HandleSubMarketDataFinished` pop/读/清均无锁 → 数据竞争。新增 `m_QueueMutex`（`#include <mutex>`），4 处 push 上锁；`HandlePackages` 锁内 `swap` 出队、`HandleSubMarketDataFinished` 锁内 `swap m_ReqSubMds` 后处理，对齐实盘 `OnMessage`/`GetNextPackage` 既有模式。**附带修复同函数池泄漏**：重复订阅/找不到合约两条 `continue` 路径跳过 `::Deallocate(reqSubMd)`，补回池。
  - **H14 买盘同价 LIFO 违反 FIFO**（`src/OrderMatch/OrderUtility.cpp`）：`OrderLessForPriceOpposite` 同价 tiebreak `OrderID >` 使最新单先成交（LIFO）；改 `<`，与卖盘 `OrderLessForPrice`（`OrderID <`）一致，同价转最早单优先（价格-时间优先）。
  - **H15 OrderBook 市价单（用户决策：仅文档化，代码零改动）**：`CheckMatch` 只遍历对手限价队列，`m_MarketBuy/SellOrders` 滞留无消费；且 `OnTick/OnBar` 为空实现，该模式本就无价格驱动撮合，属整条路径缺口而非单点 bug。经用户确认不修代码，列入待办（见 ❓）。
  - **H16 实盘 `OnTick(mdTick)` 悬垂**（`src/SimExchange/SimExchange.cpp`）：`InitMdbFromDB::LoadTables` 不调 `InitDB()` → `m_DBInited==false`；实盘 `Update(oldMdTick, mdTick)` 走 `else→Deallocate()` 释放 `mdTick`，随后 `OnTick(mdTick)` 悬垂（回测 `PushNextTick` 顺序正确，先 OnTick 后落库）。改为 `OnTick` 移至 `Insert/Update` 之前；`HandleBarMarketData` 同理（`OnBar` 提前于 `Insert`）。
  - **H17 OrderID 计数器无种子**（`src/OrderMatch/OrderUtility.{h,cpp}`）：`GetNextOrderID()` 静态从 0 起，而实盘/回测均从 init DB 装载 t_Order，重复回测或装载历史单时主键冲突。计数器改文件级静态 `g_MaxOrderID`，新增 `SeedNextOrderIDFromMaxOrderID`/`SeedNextOrderIDFromOrders`；回测 `SimExchange::Init`、实盘 `SimExchange::Init` 在 `LoadTables` 后从 t_Order 最大 OrderID 续接。
  - **H18 BackTest `new`→池不匹配**（`src/BackTest/SimExchange.cpp`）：`new MdSubscribe/Capital/Position/PositionDetail` 后被 `Mdb.Insert` 池回收 → 分配器不匹配/堆损坏；改 `X::Allocate()`（与 `CreateOrder`/`CreatePosition` 模式一致，`Allocate()` 值初始化 + `memcpy` 覆盖）。
  - **H19 `GetFirstBarTime` 空指针解引用**（`src/Bar/TradeSession.cpp` + `src/Bar/MinuteBar.cpp`）：无 `Section` 段时 `GetFirstTradeSection()` 返回 `nullptr`，`tradeSection->From` 崩溃；加空守卫返回 0，`CheckHasLostBar` 调用侧对 `lostBarMinuteTime <= 0` 直接返回，避免合成 0 时伪造丢失 bar。
  - x64-Debug 编译链接验证通过（2026-08-27）：OrderMatchStatic/BarStatic 重建，MdOffer.exe、SimExchange.exe、BackTestd.dll 均成功（TestBackTest 动态加载新 BackTestd.dll）。
- **2026-08-31 CMake 全局标志整改**（`CMakeLists.txt`）：
  - 删除 `set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /bigobj /utf-8")` 全局变异与按 config 重复的 `add_compile_options`/`add_compile_definitions`（`/Od /Zi /O2 /O1`、`-O0/-O3/-O2/-Os`、`NDEBUG` 均与 CMake 默认值逐项等价，`/EHsc` 本就在 MSVC 默认标志内，曾致 `/EHsc /EHsc` 重复）。
  - 改为平台分支：`if(WIN32)` 内 `add_compile_definitions(UNICODE _UNICODE _CRT_SECURE_NO_WARNINGS _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING)` + `add_compile_options(/utf-8 /bigobj)`（不设 `MSVC` 子门，按用户约定分流；`/bigobj` 供 Packages.cpp 等超段上限的生成文件）。WSL 实测（g++，即 WSL-GCC-* preset 环境）：`MSVC` 为空、`UNIX=1`——撤 `MSVC` 门对 Linux 构建无影响，Windows 构建 FLAGS 与改前逐字节一致。
  - **`WINDOWS`/`LINUX` 平台 define 删除**（当日二次评估）：C++ 侧平台判断统一为编译器内置宏（`ShutdownSignal.cpp` 改 `_WIN32`）。Spark 源码虽 15+ 文件使用 `WINDOWS`/`LINUX`，但由 **Spark 自身构建**的 CMake 定义解析，与其消费者无关；消费者侧核查为零引用——QuantTrading 全目录零引用，Spark 公共头仅 `Platform.h:3` 一处 `#ifdef LINUX`（经 `Core.h` 传递包含，仅声明 `spark::core::GetLastError`/`WSAGetLastError`，QuantTrading 零调用，声明消失无影响），DBAdapters/Templates 零引用。`elseif(UNIX)` 空分支一并移除。
  - 生效核对（build.ninja FLAGS）：Debug `/DWIN32 /D_WINDOWS /EHsc /Zi /Ob0 /Od /RTC1 -std:c++20 -MDd /utf-8 /bigobj`（重复 `/Od /Zi` 消除）；Release `/DWIN32 /D_WINDOWS /EHsc /O2 /Ob2 /DNDEBUG -std:c++20 -MD /utf-8 /bigobj`（`/O2`、`NDEBUG` 由默认提供）。Linux Debug 的 `-ggdb` 与 `_DEBUG` 因全库（含 Spark/DBAdapters 头）零引用而删。
  - x64-Debug / x64-Release 全量编译链接验证通过（各 131/131 步；删除两个平台 define 后 x64-Debug 再次全量重建通过，DEFINES 已无 `-DWINDOWS`）。本机 shell 无 ninja，验证经 VS 2022 Enterprise 自带 ninja + vcvars64 执行；x64-Debug 缓存 `CMAKE_MAKE_PROGRAM` 已固化为该 ninja 路径（与 VS 所用一致，无副作用）。

- **2026-08-31 WSL-GCC 构建打通（缺 `<string>` 自包含修复 ×8）**：
  - 现象：WSL-GCC-Debug 全量重编时 `MdSpiImpl.h:14` 报 `'string' in namespace 'std' does not name a type`。
  - **与同日 CMake 改动无关（实验证明）**：用旧 Linux Debug 标志（`-DLINUX -D_DEBUG -O0 -g -ggdb`）编译同一 TU，报一模一样的错。根因是 `MdSpiImpl.h` 于 2026-08-24（`2bab7a2`）引入 `std::string` 成员后从未在 GCC 下编译过（MSVC 的 `<cstring>` 传递包含 `<string>`，libstdc++ 没有）；当日 CMake flag 变更触发全量重编才第一次在 GCC 踩到。
  - 修复：8 个"用 `std::string` 但未含 `<string>`"的头文件补 `#include <string>`（`SimExchange/MdSpiImpl.h`、`SimExchangeInit/{ThostFtdcTraderSpiImpl.h,Init.h}`、`Bar/{TradeSession.h,MinuteBar.h}`、`MdOffer/MdFront.h`、`BackTestInit/Init.h`、`BackTest/SimExchange.h`）；预扫 `std::vector`/`std::shared_ptr` 无同类缺口。
  - 验证：WSL-GCC-Debug 28/28 全绿（MdOffer/SimExchange/SimExchangeInit/BackTestInit/TestBackTest + `libBackTestd.so`），**真实 Linux/GCC 环境验证了 `LINUX` define 删除的正确性**（编译行已无 `-DLINUX`）；Windows x64-Debug 131/131 重建通过。修复文件经 cp 同步至 VS 远程副本 `~/.vs/QuantTrading` 后在 WSL 内 ninja 执行，VS 下次同步自动覆盖为相同内容。

## 🔄 进行中

- 无。

## ❓ 待讨论 / 待决策

- **平台宏统一（WINDOWS→_WIN32、LINUX→__linux__）**（2026-08-31 评估）：`_WIN32`/`__linux__` 为编译器内置宏，可替代 CMake 注入的 `WINDOWS`/`LINUX` 家族约定。使用面：Spark 15+ 文件（Logger、Network/Tcp Iocp/Epoll/Select、Shm 等），DBAdapters/Templates 零使用。QuantTrading 侧已完成：`ShutdownSignal.cpp` 3 处 `#ifdef WIN32` 改 `_WIN32`（裸 cl 对照实验证实 `WIN32` 非编译器内置、依赖 CMake 注入 `/DWIN32`，离开构建系统即走错平台分支——且 MSVC CRT 也有 signal.h/signal，属静默劣化而非编译错误）。CMakeLists 的 `WINDOWS`/`LINUX` define 已于当日删除（消费面核查为零引用）；剩余待决策：Spark 仓库源码内部迁移 `WINDOWS→_WIN32`、`LINUX→__linux__`（属 Spark 自身构建范围，不影响 QuantTrading；迁移前 Spark 自己的 CMake 需继续定义这两个宏）。
- **H15 OrderBook 市价撮合缺口**（2026-08-27 用户决策：先文档化，代码不动）：`OrderBookOrderMatch::CheckMatch` 只遍历对手限价队列，`m_MarketBuy/SellOrders`（`OrderMatch.h:48-49`）滞留无消费；`OnTick`/`OnBar`（`OrderBookOrderMatch.cpp:19-26`）为空实现，整条路径无价格驱动撮合。待 OrderBook 引擎设计（OnTick 驱动撮合 + 市价队列语义）时一并处理。
- **BackTest `yearMdSubscribes` 局部 list 泄漏**（2026-08-27 复查发现）：`HandleSubMarketDataFinished` 中 `new list<MdSubscribe*>()`（按年建组）随函数返回永不释放，每次订阅结束泄漏少量 list 容器对象（元素已入 `t_MdSubscribe` 表，不属池对象）；低频小泄漏，待与订阅生命周期重构一并处理。
- **数据源整理对齐 mdb**（用户负责）：TestBackTest 已能在旧格式 parquet（`LastTraded`/`LastTurnover`/数组盘口，缺 OpenPrice/ClosePrice/Upper/LowerLimitPrice/AveragePrice 5 列）上端到端跑通，**靠 MdReader SQL 的 NULL 占位 + 旧列名兜底**；数据侧未真正对齐 mdb schema。真正对齐后 SQL 可删掉占位符，且 tick 的涨跌停价列才真实可用（当前 OrderMatch 的涨跌停校验处于注释状态，`GetSettlementPrice` 对 +inf 有回退，故暂不影响撮合/结算正确性）。
- **P1-1 完整重连**：当前仅重置登录态，CTP 断线自动重连/退避策略未实现。需确认所用 CTP 版本的 `Reconnect()`/自动重连行为后设计。
- **P2-1 MdKernel 职责拆分**：`HandleRtnDepthMarketData` 同时做 bar 聚合/Mdb 更新/快照/广播，建议预留 tick 处理管线。
- **P2-2 Bar 内存策略**：`MinuteBar` 用裸 `new` 且 `m_TodayBars` 无日界清理，考虑改对象池 + 日界重置。
- **P2-3 Bar 算法单测**：补 bar / 交易时段 / 集合竞价逻辑无测试覆盖。
- **P2-4 订阅范围配置化**：当前 `HandleNotifyDBConnect` 遍历 `t_Instrument` 全市场订阅，应改为按交易所/产品/合约配置。
- **配置明文凭证（源码硬编码已消除，S4 完成）**：`Main.cpp` 的 MdOffer 种子用户与死常量已迁移到配置（S4），但配置文件本身仍明文存储密码——`CtpAccountInfo.json`（SimNow 账户 Password/AuthCode）、各 `Configs/*.json`（`DbPassword`/`MdPassword`）、`TestMdApi.json`（`MdPassword`）。接真实环境前需迁移到密钥管理/环境变量；`MdPassword` 测试值 `123456` 仅限开发。
- **优雅退出 Ctrl+C 交互验证**：MdOffer / SimExchange 的有序关停逻辑已就绪，但 shell 无法模拟 Ctrl+C，需在真实控制台运行并确认退出顺序与日志。
- **TestMdApi 遗留**：仍硬编码 `sleep(120s)` 等待行情，应改为条件变量/超时轮询。
- **LICENSE 缺失**：项目无 LICENSE 文件，发布前需确定开源协议（README 中已标注待定）。

## 备注

- 提交信息历史多为 `1`，建议后续写描述性提交信息。
- `D:\Gitee\Templates` 仓库的模板改动（S1/S3/H10/H12 对应 `.tpl`）已提交（`6d12e3d`）。
- `rules/cpp-style.md` 成员命名要求 snake_case，现有代码为 `m_` + PascalCase，项目自洽但与规范不一致（待统一）。
