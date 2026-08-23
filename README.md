# QuantTrading
[![Language](https://img.shields.io/badge/Language-C++20+-orange.svg)]()
[![Build](https://img.shields.io/badge/Build-CMake3.20+-green.svg)]()
[![CTP](https://img.shields.io/badge/CTP-v6.7.9_P1-blue.svg)]()

**QuantTrading** 是一套基于 C++20 的 **CTP 期货量化交易系统**，覆盖行情采集（**MdOffer**）、模拟撮合（**SimExchange**）、历史回测（**BackTest**）三条业务链路，对外提供风格统一的 **MdApi / TraderApi / SimExchangeApi / BackTest** 四套客户端接口。系统以 **Spark** 提供线程 / 日志 / 网络基础能力，以 **DBAdapters** 提供 SQLite / DuckDB / MySQL / MariaDB 四库一致性读写，采用"**内存库 Mdb + AsyncDBWriter 异步落库**"的低时延架构。

Created by [xunmeng2002](https://gitee.com/xunmeng2002)

## 一、项目概述

本项目为个人开源项目，聚焦"**一套行情服务 / 撮合引擎 / 回测框架，支撑从行情到回测的完整量化链路**"：实盘行情经 CTP 订阅后写入内存库并异步落盘，同时通过行情服务端广播给交易侧；模拟撮合在本地订单簿 / 最新价 / 对手价 / Bar 四种模式下完成撮合、持仓与结算；回测框架从 Parquet 历史数据重放 tick / Bar，复跑同一套撮合与结算逻辑。

系统基于标准 C++20 开发，采用 CMake 跨平台构建，依赖 [Spark](https://gitee.com/xunmeng2002/Spark.git)（线程、日志、网络、对象池）与 [DBAdapters](https://gitee.com/xunmeng2002/DBAdapters.git)（数据库访问层），第三方驱动（SQLite / MySQL / MariaDB）经 vcpkg 管理，内置 CTP / SimExchange / BackTest 的测试客户端程序。

## 二、核心功能模块

整体分为**业务链路**（MdOffer / SimExchange / BackTest）、**基础设施**（Mdb / OrderMatch / Bar / Packages / QuantTradingCommon / Ctp）与**对外接口**（Apis）三部分。

### 1. MdOffer —— 行情服务（可执行程序）

CTP 行情主流程：`ThostFtdcMdSpiImpl`（CTP 回调）→ `MdKernel` 单线程事件循环 → `Mdb` 内存表 → `AsyncDBWriter` 异步落库 → `MdFront` 行情广播。

- 交易日本归属修复：夜盘 `TradingDay` 采用交易所交易日，为空时回退 `ActionDay`
- 订阅字段生命周期重构：全局 `std::set` 值集合持节点，会话集合每会话一份，断线整行 `erase`
- P1-1 重连路径并发修复：回调线程对订阅表反查改同锁 `find()`，重连补订取锁内快照批量下发
- 优雅退出：`ShutdownSignal`（Ctrl+C / SIGTERM）置位后按依赖序有序关停
- 支持 4 种 DB（DuckDB / SQLite / MySQL / MariaDB），按配置分发

### 2. SimExchange —— 模拟撮合服务（可执行程序）

以 `MdApi` 接收行情，`SimExchange` 单线程撮合，`TradeFront` / `MdFront` 分别广播交易与行情回报：

- 四种撮合模式（`MatchMode`）：`OrderBook` 订单簿 / `LastPrice` 最新价 / `OppositePrice` 对手价 / `Bar`
- 撮合引擎 `OrderMatch` 与行情、结算解耦，四模式独立实现
- 结算逻辑：持仓浮盈（逐日 / 逐笔）、平仓盈亏、市值、保证金，结算价缺省回退

### 3. BackTest —— 历史回测（动态库）

`MdReader` 从 parquet 读入 tick / Bar → `SimExchange` 按时间重放撮合 → 结算 → 落库：

- DuckDB 向量化批量读（`SelectWithSqlVectorized`），NULL 写类型哨兵
- 三种查询（Instrument / Tick / Bar）复用 mdb `GetSchema()`，按 mdb 列序自动装配
- 订阅到"回测结束"（`OnRtnMarketDataEnd`）即可拿到整段结果，`TestBackTest` 已端到端跑通

### 4. Mdb —— 内存数据库（静态库）

- 表结构由 `MdbTables.h` 模板生成，每表继承 `MdbTableBase` 统一接口
- **按需装配**：`Mdb(const TableList&)` 构造时只 `new` 本模块的表，`MdbTableRegistry` 按模块过滤 schema
- `AsyncDBWriter` 只作用于本模块的表，机制上杜绝模块越界访问
- 变更经 `MdbSubscriber` 广播，供撮合 / 落库 / 快照复用

### 5. Apis —— 对外客户端接口（动态库）

统一"请求 / 回调"风格，分为 **UTF-8** 与 **GBK** 两套编码变体：

| 接口 | 用途 | 关键方法 |
| --- | --- | --- |
| `MdApi` / `MdGbkApi` | 行情客户端 | `ReqMdUserLogin`、`ReqSubMarketData`、`OnRtnDepthMarketData`、`OnRtnBarMarketData` |
| `TraderApi` / `TraderGbkApi` | 交易客户端 | `ReqAccountLogin`、`ReqQryPosition`、`ReqInsertOrder`、`ReqCancelOrder`、`OnRtnOrder`、`OnRtnTrade` |
| `SimExchangeApi` / `SimExchangeGbkApi` | 模拟交易所客户端 | `ReqInsertOrder`、`ReqQryOrder`、`OnRtnOrder`、`OnRtnTrade` |
| `BackTest` | 回测接口 | `ReqSubMarketData`、`ReqInsertOrder`、`OnRtnDepthMarketData`、`OnRtnMarketDataEnd` |

### 6. 基础设施

| 模块 | 说明 |
| --- | --- |
| `OrderMatch` | 四模式撮合引擎：`OrderBookOrderMatch` / `LastPriceOrderMatch` / `OppositePriceOrderMatch` / `BarOrderMatch` |
| `Bar` | 分钟 Bar 聚合（`MinuteBar`）、交易时段（`TradeSession`）、Bar 接口（`BarInterface`） |
| `Packages` | 报文与数据结构包（对象池分配 / 释放） |
| `QuantTradingCommon` | 环境配置（`Environment`）、服务端配置（`ServerConfig`）、`ShutdownSignal`、字段比较、错误码 |
| `Ctp` | CTP API 封装：`MdApiMiddle` / `TraderApiMiddle` / `StructLogFunc` |

### 7. 典型场景

```
CTP 行情 ──► MdOffer（订阅→内存库→异步落库→广播）──► MdFront
                                                      │
                                                      ▼
                     SimExchange（撮合→持仓→结算）──► TradeFront / MdFront
                                                      │
                                                      ▼
      BackTest（MdReader 读 parquet ──► 重放 ──► 撮合 ──► 结算 ──► 落库）
```

## 三、项目目录结构

```
QuantTrading/
├── include/QuantTrading/         # 对外公共头文件（API 定义 + Fields + 版本头模板）
├── src/                          # 源码
│   ├── Apis/                     # 对外接口：ApiBase / MdApi(+Gbk) / TraderApi(+Gbk) / SimExchangeApi(+Gbk)
│   ├── MdOffer/                  # 行情服务应用（Main.cpp + MdKernel + MdFront + ThostFtdcMdSpiImpl）
│   ├── SimExchange/              # 模拟撮合应用（Main.cpp + SimExchange + TradeFront + MdSpiImpl）
│   ├── BackTest/                 # 回测动态库（MdReader + SimExchange + BackTestApiImpl）
│   ├── BackTestInit/             # 回测初始化工具（含 Init 库装载）
│   ├── SimExchangeInit/          # 撮合初始化工具（含 Init 库装载）
│   ├── Mdb/                      # 内存数据库（表 / 索引 / 注册表 / 装配）
│   ├── OrderMatch/               # 四模式撮合引擎
│   ├── Bar/                      # Bar 聚合 + 交易时段
│   ├── Packages/                 # 报文 / 数据结构包
│   ├── QuantTradingCommon/       # 公共基础（Environment / ServerConfig / ShutdownSignal / 错误码）
│   └── Ctp/                      # CTP 封装（MdApiMiddle / TraderApiMiddle / StructLogFunc）
├── test/                         # 测试客户端
│   ├── ApiMiddles/               # Md / Trader / SimExchange / BackTest 的 ApiMiddle + SpiMiddle 封装
│   ├── TestMdApi/                # CTP 行情客户端测试
│   ├── TestTraderApi/            # 交易客户端测试
│   ├── TestSimExchangeApi/       # 模拟交易所客户端测试
│   └── TestBackTest/             # 回测端到端测试
├── Configs/                      # 各应用的 JSON 配置（MdOffer / SimExchange / BackTest / ServerConfig / 账户环境等）
├── Model/                        # 表 / 包 / 会话的模型定义（pumplist.xml 登记）
├── submodules/CMakeCommon/       # 子模块：公共 CMake 宏
├── include/                      # 对外头文件目录（公共 API）
├── bin/                          # 构建产物：可执行文件（按配置分目录）
├── lib/                          # 构建产物：库文件（按配置分目录）
├── out/                          # CMake Presets 构建目录
├── CMakeLists.txt                # CMake 主构建配置
├── CMakePresets.json             # CMake 预设配置（VS / 命令行）
├── vcpkg.json                    # vcpkg 清单（第三方驱动）
├── pump.py / pumpall.py          # 模板代码生成脚本（模型 → 代码）
└── PROGRESS.md                   # 项目进度跟踪
```

## 四、环境依赖

### 基础要求

- C++ 编译器：支持 **C++20 及以上**（GCC、Clang、MSVC）
- 构建工具：**CMake 3.20+**（本项目 Presets 需 3.21+）
- 包管理：**vcpkg**（`VCPKG_ROOT` 环境变量必需，供 CMake 定位 toolchain）
- 平台：Linux、Windows（Windows 推荐搭配 VS2022 / WSL）

### 依赖子模块

- **CMakeCommon**：公共 CMake 宏集合，克隆后需同步拉取子模块。

### 预编译依赖（需手动准备）

构建依赖四个**预编译第三方库**，需先安装到项目父目录的 `Libs/` 下（与 `CMakePresets.json` 的 `CMAKE_INSTALL_PREFIX` 布局一致）：

| 依赖 | 安装位置 | 提供内容 |
| --- | --- | --- |
| **Spark** 基础库 | `../Libs/Spark/<triplet>` | `Spark::Core`（线程 / 日志 / 网络 / 对象池）、`Spark/Types.h` |
| **DBAdapters** | `../Libs/DBAdapters/<triplet>` | 四库统一访问层（`DB::DBInterface` / `AsyncDBWriter` 等） |
| **DuckDB** | `../Libs/duckdb/<triplet>` | `duckdb::duckdb`（向量化读取所需头文件 + 运行时库） |
| **CTP** | `../Libs/Ctp/<triplet>` | `CTP::mdapi` / `CTP::traderapi`（v6.7.9） |

`<triplet>` 在 Windows 下为 `x64-windows`，Linux / WSL 下为 `x64-linux`。

### vcpkg 第三方依赖

`vcpkg.json` 声明的依赖（构建时自动解析）：

- `sqlite3` —— SQLite 驱动
- `mysql-connector-cpp` —— MySQL 驱动
- `mariadb-connector-cpp` —— MariaDB 驱动

## 五、快速构建 & 编译

### 1. 克隆代码（含子模块）

```bash
git clone --recursive https://gitee.com/xunmeng2002/QuantTrading.git
cd QuantTrading
```

### 2. 更新子模块（若未递归克隆）

```bash
# Linux / Mac
sh UpdateSubmodule.sh

# Windows
UpdateSubmodule.bat
```

### 3. 准备依赖

```bash
# 确保 VCPKG_ROOT 已配置（Windows 设为系统环境变量，Linux 写入 ~/.bashrc）
# 确保 Spark、DBAdapters、duckdb、CTP 已安装到 ../Libs/ 对应目录（见上文"预编译依赖"）
```

### 4. CMake 编译（推荐使用 Presets）

```bash
# Windows（MSVC，Ninja）
cmake --preset x64-Debug
cmake --build out/build/x64-Debug

# Linux / WSL（GCC）
cmake --preset WSL-GCC-Debug
cmake --build out/build/WSL-GCC-Debug
```

编译完成后，可执行文件输出至 `bin/<Config>`（如 `bin/Debug/MdOffer.exe`），库文件输出至 `lib/<Config>`。

### 5. 运行测试客户端

```bash
# Windows
./bin/Debug/TestBackTest.exe      # 回测端到端（依赖 BackTest.json 中 MdDataPath 指向的 parquet 历史数据）
./bin/Debug/TestMdApi.exe         # CTP 行情客户端（需可连接的 CTP / SimNow 行情前置）
./bin/Debug/TestTraderApi.exe     # 交易客户端
./bin/Debug/TestSimExchangeApi.exe
```

### 6. 运行应用

```bash
./bin/Debug/MdOffer.exe           # 行情服务（Ctrl+C / SIGTERM 优雅退出）
./bin/Debug/SimExchange.exe       # 模拟撮合服务
```

## 六、基础使用示例

### 示例 1：BackTest 回测（BackTestApi）

```cpp
#include <QuantTrading/BackTestApi.h>
#include <Spark/Core/Logger/Logger.h>
#include <cstring>

using namespace quanttrading;
using namespace spark::core;

// 策略回调：收到行情后，以"最新价"下单（示意：仅开仓示例）
class DemoBackTestSpi : public BackTestSpi
{
public:
    void OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData) override
    {
        // 收到 tick，按最新价下一手买单（首次时）
        ReqInsertOrderField req;
        std::memset(&req, 0, sizeof(req));
        std::strcpy(req.AccountID, m_AccountID);
        std::strcpy(req.InstrumentID, depthMarketData->InstrumentID);
        req.Direction = DirectionType::Buy;
        req.OffsetFlag = OffsetFlagType::Open;
        req.Price = depthMarketData->LastPrice;
        req.Volume = 1;
        ReqInsertOrder(&req, 1);
    }
    void OnRtnMarketDataEnd(const MarketDataEndField*) override
    {
        m_BackTestApi->Release();   // 回测结束，释放
    }
    BackTestApi* m_BackTestApi;
    char m_AccountID[32];
};

int main(int argc, char* argv[])
{
    Logger::GetInstance().Init(argv[0]);
    Logger::GetInstance().Start();

    auto api = BackTestApi::CreateBackTestApi();   // 内部读取 BackTest.json
    DemoBackTestSpi spi;
    spi.m_BackTestApi = api;
    std::strcpy(spi.m_AccountID, "test");
    api->RegisterSpi(&spi);
    api->Init();

    ReqSubMarketDataField reqSubMd;
    std::memset(&reqSubMd, 0, sizeof(reqSubMd));
    std::strcpy(reqSubMd.ExchangeID, "CFFEX");
    std::strcpy(reqSubMd.InstrumentID, "IF2503");
    api->ReqSubMarketData(&reqSubMd, 1);

    api->Join();                    // 阻塞至回测数据重放完毕
    Logger::GetInstance().Stop();
    Logger::GetInstance().Join();
    return 0;
}
```

> 运行前提：`BackTest.json` 的 `MdDataPath` 指向含 `Tick/`、`Bar/` 子目录的 parquet 数据根目录，`StartTradingDay` / `EndTradingDay` 覆盖所需区间。

### 示例 2：行情客户端（MdApi）

```cpp
#include <QuantTrading/MdApi.h>
#include <Spark/Core/Logger/Logger.h>
#include <cstring>

using namespace quanttrading;
using namespace spark::core;

class DemoMdSpi : public MdSpi
{
public:
    void OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData) override
    {
        WriteLog(LogLevel::Info, "%s last=%.2f", depthMarketData->InstrumentID, depthMarketData->LastPrice);
    }
};

int main(int argc, char* argv[])
{
    Logger::GetInstance().Init(argv[0]);
    Logger::GetInstance().Start();

    auto api = MdApi::CreateMdApi();
    DemoMdSpi spi;
    api->RegisterSpi(&spi);
    api->RegisterFront("tcp://182.254.243.31:30011");   // CTP 行情前置
    api->Init();

    ReqSubMarketDataField reqSubMd;
    std::memset(&reqSubMd, 0, sizeof(reqSubMd));
    std::strcpy(reqSubMd.ExchangeID, "CFFEX");
    std::strcpy(reqSubMd.InstrumentID, "IF2503");
    api->ReqSubMarketData(&reqSubMd, 1);

    api->Join();
    api->Release();
    Logger::GetInstance().Stop();
    Logger::GetInstance().Join();
    return 0;
}
```

## 七、集成测试

项目内置四个测试客户端（`test/`）：

| 测试程序 | 说明 |
| --- | --- |
| `TestBackTest` | 回测端到端：MdReader 读 parquet → 撮合 → 结算 → 落库（已跑通） |
| `TestMdApi` | CTP 行情客户端：订阅 / 行情回调（需 CTP 或 SimNow 行情前置） |
| `TestTraderApi` | 交易客户端：登录 / 查询 / 下单（需交易前置） |
| `TestSimExchangeApi` | 模拟交易所客户端：登录 / 下单 / 成交回报 |

### 运行测试

```bash
# Windows
./bin/Debug/TestBackTest.exe
./bin/Debug/TestMdApi.exe

# Linux
./bin/Debug/TestBackTest
./bin/Debug/TestMdApi
```

## 八、许可证 & 声明

- **开源协议**：**待定**（项目暂未添加 LICENSE 文件，发布前需确定协议）
- **适用范围**：本项目仅供个人学习、研究使用
- **风险提示**：本项目为个人开源项目，涉及真实资金交易前请自行充分测试并评估风险；实盘账户、数据库口令等敏感信息应自行妥善管理

## 九、补充说明

- **包含路径**：头文件统一使用 `#include <QuantTrading/XxxApi.h>` 风格；模块内部使用 `#include <Module/Xxx.h>`
- **命名空间**：公共 API 位于 `quanttrading`，各模块分别位于 `quanttrading::mdoffer`、`quanttrading::simexchange`、`quanttrading::backtest`、`quanttrading::ordermatch` 等
- **依赖链**：`Spark`（线程 / 日志 / 网络）→ `DBAdapters`（四库统一访问）→ `QuantTrading`
- **版本**：CTP API v6.7.9（`MdOffer` 启动日志可见 `API Version`）
- **编码变体**：MdApi / TraderApi / SimExchangeApi 各提供 **UTF-8**（`MdApi` 等）与 **GBK**（`MdGbkApi` 等）两套动态库
- **数据源适配**：`BackTest` 的 `MdReader` 当前 SQL 面向旧列名 parquet（如 `LastTraded` / `LastTurnover` / 数组盘口），缺失列以 NULL 占位；数据侧整理对齐 mdb schema 后可删除占位符，使 tick 涨跌停价等列真实可用
- **优雅退出**：MdOffer / SimExchange 支持 Ctrl+C / SIGTERM 按依赖序有序关停（`ShutdownSignal`）
