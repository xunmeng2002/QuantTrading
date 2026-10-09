# QuantTrading
[![Language](https://img.shields.io/badge/Language-C++20+-orange.svg)]()
[![Build](https://img.shields.io/badge/Build-CMake3.20+-green.svg)]()
[![CTP](https://img.shields.io/badge/CTP-v6.7.9_P1-blue.svg)]()

**QuantTrading** 是一套基于 C++20 的 **CTP 期货量化交易系统**，覆盖行情采集（**MdOffer**）、模拟撮合（**SimExchange**）、历史回测（**BackTest**）三条业务链路，对外提供风格统一的 **MdApi / TraderApi / SimExchangeApi / BackTest** 四套客户端接口。系统以 **Spark** 提供线程 / 日志 / 网络基础能力，以 **DbAdapters** 提供 SQLite / DuckDB / MySQL / MariaDB 四库一致性读写，采用"**内存库 Mdb + AsyncDbWriter 异步落库**"的低时延架构。

Created by [xunmeng2002](https://gitee.com/xunmeng2002)

## 一、项目概述

本项目为个人开源项目，聚焦"**一套行情服务 / 撮合引擎 / 回测框架，支撑从行情到回测的完整量化链路**"：实盘行情经 CTP 订阅后写入内存库并异步落盘，同时通过行情服务端广播给交易侧；模拟撮合在本地订单簿 / 最新价 / 对手价 / Bar 四种模式下完成撮合、持仓与结算；回测框架从 Parquet 历史数据重放 tick / Bar，复跑同一套撮合与结算逻辑。

系统基于标准 C++20 开发，采用 CMake 跨平台构建，依赖 [Spark](https://gitee.com/xunmeng2002/Spark.git)（线程、日志、网络、对象池）与 [DbAdapters](https://gitee.com/xunmeng2002/DbAdapters.git)（数据库访问层），第三方驱动（SQLite / MySQL / MariaDB）经 vcpkg 管理，内置 CTP / SimExchange / BackTest 的测试客户端程序。

## 二、核心功能模块

整体分为**业务链路**（MdOffer / SimExchange / BackTest）、**基础设施**（Mdb / OrderMatch / Bar / Packages / Settlement / QuantTradingCommon / Ctp）与**对外接口**（Apis）三部分。

### 1. MdOffer —— 行情服务（可执行程序）

CTP 行情主流程：`ThostFtdcMdSpiImpl`（CTP 回调）→ `MdKernel` 单线程事件循环 → `Mdb` 内存表 → `AsyncDbWriter` 异步落库 → `MdFront` 行情广播。

- 交易日本归属修复：夜盘 `TradingDay` 采用交易所交易日，为空时回退 `ActionDay`
- 订阅字段生命周期重构：全局 `std::set` 值集合持节点，会话集合每会话一份，断线整行 `erase`
- P1-1 重连路径并发修复：回调线程对订阅表反查改同锁 `find()`，重连补订取锁内快照批量下发
- 优雅退出：`ShutdownSignal`（Ctrl+C / SIGTERM）置位后按依赖序有序关停
- 支持 4 种 DB（DuckDB / SQLite / MySQL / MariaDB），按配置分发

### 2. SimExchange —— 模拟撮合服务（可执行程序）

以 `MdApi` 接收行情，`SimExchange` 单线程撮合，`TradeFront` / `MdFront` 分别广播交易与行情回报：

- 四种撮合模式（`MatchMode`）：`OrderBook` 订单簿 / `LastPrice` 最新价 / `OppositePrice` 对手价 / `Bar`
- 撮合引擎 `OrderMatch` 与行情、结算解耦，四模式独立实现
- 结算与交易日切换：模拟盘不做结算与日切（交易日经 `SimExchangeInit` 固化，每日停机后由外部重新初始化并重启）；运行期持仓维护已启用（公共结算库 `src/Settlement` 的 `PositionMaintenance` 实时维护持仓与开仓明细），日结与结转逻辑位于回测引擎（见下节）

### 3. BackTest —— 历史回测（动态库）

`MdReader` 从 parquet 读入 tick / Bar → `SimExchange` 按时间重放撮合 → 结算（公共结算库 `src/Settlement`）→ 落库：

- DuckDB 向量化批量读（`SelectWithSqlVectorized`），NULL 写类型哨兵
- 三种查询（Instrument / Tick / Bar）复用 mdb `GetSchema()`，按 mdb 列序自动装配
- 订阅到"回测结束"（`OnRtnMarketDataEnd`）即可拿到整段结果，`TestBackTest` 已端到端跑通

### 4. Mdb —— 内存数据库（静态库）

- 表结构由 `MdbTables.h` 模板生成，每表继承 `MdbTableBase` 统一接口
- **按需装配**：`Mdb(const TableList&)` 构造时只 `new` 本模块的表，`MdbTableRegistry` 按模块过滤 schema
- `AsyncDbWriter` 只作用于本模块的表，机制上杜绝模块越界访问
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
| `Settlement` | 结算公共库：持仓维护（`PositionMaintenance`，FIFO 先开先平）、日结（`Settle`：明细 → 持仓 → 资金核算）、跨日结转（`RollToNextDay`），结算价经 `SettlementPriceSource` 注入 |
| `Bar` | 分钟 Bar 聚合（`MinuteBar`）、交易时段（`TradeSession`）、Bar 接口（`BarInterface`） |
| `Packages` | 报文与数据结构包（对象池分配 / 释放） |
| `QuantTradingCommon` | 环境配置（`Environment`）、服务端配置（`ServerConfig`）、`ShutdownSignal`、字段比较、错误码 |
| `Ctp` | CTP API 封装：`MdApiMiddle` / `TraderApiMiddle` / `StructLogFunc` |

### 7. 典型场景

```text
CTP 行情 ──► MdOffer（订阅→内存库→异步落库→广播）──► MdFront
                                                      │
                                                      ▼
                     SimExchange（撮合→持仓维护）──► TradeFront / MdFront
                                                      │
                                                      ▼
      BackTest（MdReader 读 parquet ──► 重放 ──► 撮合 ──► 结算 ──► 落库）
```

## 三、项目目录结构

```text
QuantTrading/
├── include/QuantTrading/         # 对外公共头文件（API 定义 + Fields + 版本头模板）
├── src/                          # 源码
│   ├── Apis/                     # 对外接口：ApiBase / MdApi(+Gbk) / TraderApi(+Gbk) / SimExchangeApi(+Gbk)
│   ├── MdOffer/                  # 行情服务应用（Main.cpp + MdKernel + MdFront + ThostFtdcMdSpiImpl）
│   ├── SimExchange/              # 模拟撮合应用（Main.cpp + SimExchange + TradeFront + MdSpiImpl）
│   ├── BackTest/                 # 回测动态库（MdReader + SimExchange + BackTestApiImpl）
│   ├── Strategy/                 # 策略基类（StrategyBase，C++ 与 Python 绑定共用）
│   ├── PythonBindings/           # pybind11 绑定（产出 QuantTrading.pyd，非 Debug 构建）
│   ├── SimExchangeInit/          # 撮合初始化工具（含 Init 库装载）
│   ├── Mdb/                      # 内存数据库（表 / 索引 / 注册表 / 装配）
│   ├── OrderMatch/               # 四模式撮合引擎
│   ├── Settlement/               # 结算公共库（PositionMaintenance 持仓维护 + Settlement 日结/结转 + 结算价源）
│   ├── Bar/                      # Bar 聚合 + 交易时段
│   ├── Packages/                 # 报文 / 数据结构包
│   ├── QuantTradingCommon/       # 公共基础（Environment / ServerConfig / ShutdownSignal / 错误码）
│   └── Ctp/                      # CTP 封装（MdApiMiddle / TraderApiMiddle / StructLogFunc）
├── test/                         # 测试客户端与单元测试
│   ├── ApiMiddles/               # Md / Trader / SimExchange / BackTest 的 ApiMiddle + SpiMiddle 封装
│   ├── TestMdApi/                # CTP 行情客户端测试
│   ├── TestTraderApi/            # 交易客户端测试
│   ├── TestSimExchangeApi/       # 模拟交易所客户端测试
│   ├── TestBackTest/             # 回测端到端测试
│   ├── TestStrategyGrid/         # C++ 网格策略测试宿主
│   ├── PythonStrategyGrid/       # Python 网格策略示例（grid_strategy.py）
│   └── UnitTests/                # doctest 单元测试
├── Configs/                      # 各应用的 JSON 配置（MdOffer / SimExchange / BackTest / ServerConfig / 账户环境等）
├── Model/                        # 表 / 包 / 会话的模型定义（pumplist.xml 登记）
├── docs/                         # 设计文档（回测运行契约等）
├── submodules/CMakeCommon/       # 子模块：公共 CMake 宏
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
| **DbAdapters** | `../Libs/DbAdapters/<triplet>` | 四库统一访问层（`DB::DbInterface` / `AsyncDbWriter` 等） |
| **DuckDB** | `../Libs/duckdb/<triplet>` | `duckdb::duckdb`（向量化读取所需头文件 + 运行时库） |
| **CTP** | `../Libs/Ctp/<triplet>` | `CTP::mdapi` / `CTP::traderapi`（v6.7.9） |

`<triplet>` 在 Windows 下为 `x64-windows`，Linux / WSL 下为 `x64-linux`。

### 单元测试依赖（doctest）

单元测试目标另需 `../Libs/doctest`（doctest 单头，v2.5.3，**无 triplet 子目录**，只落盘不入库）。
放置方法与 `doctestConfig.cmake` 全文见
[DbAdapters 环境准备指南 1.7](../DbAdapters/docs/environment-setup.md#17-doctest单元测试框架)。

### vcpkg 第三方依赖

`vcpkg.json` 声明的依赖（构建时自动解析）：

- `sqlite3` —— SQLite 驱动
- `mysql-connector-cpp` —— MySQL 驱动
- `mariadb-connector-cpp` —— MariaDB 驱动

### vcpkg 环境变量（构建期）

以下变量供 CMake 的 vcpkg toolchain 与二进制缓存使用，**只在构建机需要**；部署二进制时一个都不涉及。

| 变量 | 必需 | 说明 |
| --- | --- | --- |
| `VCPKG_ROOT` | 必需 | vcpkg 根目录，CMake 据此定位 toolchain |
| `VCPKG_DOWNLOADS` | 可选 | 源码包下载缓存，多项目共用可免重复下载 |
| `VCPKG_DEFAULT_BINARY_CACHE` | 可选 | 二进制缓存，命中后跳过重复编译 |

```bash
export VCPKG_ROOT=~/Github/vcpkg
export VCPKG_DOWNLOADS=/mnt/d/Github/vcpkg/downloads
export VCPKG_DEFAULT_BINARY_CACHE=~/Github/vcpkg/archives
export PATH=$VCPKG_ROOT:$PATH
```

> **注意**：写入 `~/.profile` 时只有**登录 shell** 会加载。IDE、构建脚本、`wsl.exe -c` 这类非登录
> shell 都读不到，表现为 vcpkg 落回默认空目录并**重新下载全部源码包**。可改写入 `~/.bashrc`，
> 或显式用登录 shell 启动。

### 运行期环境变量

凭证**不入库**，由系统环境变量提供；只在运行期需要，与构建无关。

**CTP 凭证** —— `Configs/CtpAccountInfo.json` 的 `Password` / `AuthCode` 字段留空，由环境变量补齐。
键名为 `CTP_<环境名大写>_PASSWORD` 与 `CTP_<环境名大写>_AUTHCODE`，非空时覆盖（实现见
`src/QuantTradingCommon/Environment.cpp`）。现有环境名 `SimNow` / `SimNow24`：

```bash
export CTP_SIMNOW_PASSWORD=<密码>
export CTP_SIMNOW_AUTHCODE=<认证码>
export CTP_SIMNOW24_PASSWORD=<密码>
export CTP_SIMNOW24_AUTHCODE=<认证码>
```

> **警告**：本文只文档化**键名**。任何文档、脚本、配置都不得写入真实凭证值。

仅 CTP 客户端需要（`TestMdApi` / `TestTraderApi` / `MdOffer` / `SimExchangeInit`）。回测
`TestBackTest` 走内置 `SimExchange`，不做 CTP 登录，**不需要**这组变量。

### Python 绑定（可选）

`src/PythonBindings/` 产出 `QuantTrading.<abi>.pyd`（WSL / Linux 下为 `.so`），供 Python 侧策略使用。
它**不进 Release 包**：`.pyd` 受 CPython **次版本 ABI 锁定**（3.11 编出的只能被 3.11 导入），
打进通用包会把包锁死在某一个次版本上。按需自建：

1. 给目标解释器安装 pybind11：`pip install pybind11`。缺失时配置阶段直接失败，报错文案以
   `QUANTTRADING_ENABLE_PYTHON=ON requires pybind11` 开头。
2. 构建**非 Debug** 配置。`Debug` 会自动跳过绑定（CPython 官方解释器用 Release CRT），
   故 `bin/Debug` 下没有 `.pyd` 属预期。

产物落在 `bin/<CONFIG>`，可用产物名自检解释器版本是否用对（下表为本仓开发机实测）：

| 平台 | 预期产物名 | 对应解释器 |
| --- | --- | --- |
| Windows | `QuantTrading.cp311-win_amd64.pyd` | CPython 3.11 |
| WSL / Linux | `QuantTrading.cpython-312-x86_64-linux-gnu.so` | CPython 3.12 |

加载路径由 CWD 或宿主注入的 `PYTHONPATH` 解析——本地调试即 `cd bin/<CONFIG> && python grid_strategy.py`；
由调度平台拉起时，平台会把引擎根前置进子进程的 `PYTHONPATH`。**不要**按 `__file__` 反推仓根：
`sys.path[0]` 的优先级高于 `PYTHONPATH`，那条路径一旦存在就会静默盖掉宿主指定的引擎根。

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
# 确保 Spark、DbAdapters、duckdb、CTP 已安装到 ../Libs/ 对应目录（见上文"预编译依赖"）
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

using namespace QuantTrading;
using namespace Spark::Core;

// 策略回调：收到行情后，以"最新价"下单（示意：仅开仓示例）
class DemoBackTestSpi : public BackTestSpi
{
public:
    void OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData) override
    {
        // 收到 tick，按最新价下一手买单（首次时）
        ReqInsertOrderField req;
        std::memset(&req, 0, sizeof(req));
        std::strcpy(req.AccountId, accountId_);
        std::strcpy(req.InstrumentId, depthMarketData->InstrumentId);
        req.Direction = DirectionType::Buy;
        req.OffsetFlag = OffsetFlagType::Open;
        req.Price = depthMarketData->LastPrice;
        req.Volume = 1;
        ReqInsertOrder(&req, 1);
    }
    void OnRtnMarketDataEnd(const MarketDataEndField*) override
    {
        backTestApi_->Release();   // 回测结束，释放
    }
    BackTestApi* backTestApi_;
    char accountId_[32];
};

int main(int argc, char* argv[])
{
    Logger::GetInstance().Init(argv[0]);
    Logger::GetInstance().Start();

    auto api = BackTestApi::CreateBackTestApi();   // 内部读取 BackTest.json
    DemoBackTestSpi spi;
    spi.backTestApi_ = api;
    std::strcpy(spi.accountId_, "test");
    api->RegisterSpi(&spi);
    api->Init();

    ReqSubMarketDataField reqSubMd;
    std::memset(&reqSubMd, 0, sizeof(reqSubMd));
    std::strcpy(reqSubMd.ExchangeId, "CFFEX");
    std::strcpy(reqSubMd.InstrumentId, "IF2503");
    api->ReqSubMarketData(&reqSubMd, 1);

    api->Join();                    // 阻塞至回测数据重放完毕
    Logger::GetInstance().Stop();
    Logger::GetInstance().Join();
    return 0;
}
```

> 运行前提：`BackTest.json` 的 `MdDataPath` 指向含 `Tick/`、`Bar/` 子目录的 parquet 数据根目录。
> 它与其他路径一样相对 CWD（`bin/<Config>`）解析：默认值 `../../MdBaoStock` 即**仓根下的 `MdBaoStock`**，
> 故每个工作副本的仓根都要有一份行情（本仓用 `.gitignore` 的 `/MdBaoStock` 把它挡在版本库外）——
> Windows 侧放一个实体目录即可：VS 编译时的 WSL 源码同步会把 Parquet **增量同步**到副本的同一相对位置，
> WSL 侧不需要手工拷贝；也可直接把 `MdDataPath` 写成绝对路径。
> `StartTradingDay` / `EndTradingDay` 须覆盖所需区间。

### 示例 2：行情客户端（MdApi）

```cpp
#include <QuantTrading/MdApi.h>
#include <Spark/Core/Logger/Logger.h>
#include <cstring>

using namespace QuantTrading;
using namespace Spark::Core;

class DemoMdSpi : public MdSpi
{
public:
    void OnRtnDepthMarketData(const DepthMarketDataField* depthMarketData) override
    {
        WriteLog(LogLevel::Info, "%s last=%.2f", depthMarketData->InstrumentId, depthMarketData->LastPrice);
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
    std::strcpy(reqSubMd.ExchangeId, "CFFEX");
    std::strcpy(reqSubMd.InstrumentId, "IF2503");
    api->ReqSubMarketData(&reqSubMd, 1);

    api->Join();
    api->Release();
    Logger::GetInstance().Stop();
    Logger::GetInstance().Join();
    return 0;
}
```

## 七、集成测试

项目内置以下测试目标（`test/`）：

| 测试程序 | 说明 |
| --- | --- |
| `UnitTests` | 单元测试（doctest 2.5.3，覆盖撮合 / 结算 / 持仓 / Bar 聚合 / 网格策略 / 报文解析等） |
| `TestBackTest` | 回测端到端：MdReader 读 parquet → 撮合 → 结算 → 落库（已跑通） |
| `TestStrategyGrid` | C++ 网格策略宿主：按轮驱动、日切换 |
| `TestMdApi` | CTP 行情客户端：订阅 / 行情回调（需 CTP 或 SimNow 行情前置） |
| `TestTraderApi` | 交易客户端：登录 / 查询 / 下单（需交易前置） |
| `TestSimExchangeApi` | 模拟交易所客户端：登录 / 下单 / 成交回报 |

`test/PythonStrategyGrid/grid_strategy.py` 是对应的 Python 策略示例，直接由解释器运行，无需构建。

### 运行测试

```bash
# Windows
./bin/Debug/UnitTests.exe
./bin/Debug/TestBackTest.exe
./bin/Debug/TestStrategyGrid.exe
./bin/Debug/TestMdApi.exe

# Linux
./bin/Debug/UnitTests
./bin/Debug/TestBackTest
./bin/Debug/TestStrategyGrid
./bin/Debug/TestMdApi
```

> `UnitTests` 未接入 CTest，需手工执行（退出码 0 且 `[doctest] Status: SUCCESS!` 即为通过）。
> `Debug` 配置下不生成 Python 绑定，故 `PythonStrategyGrid` 需用 Release 产物运行。

## 八、许可证 & 声明

- **开源协议**：**MIT License**（全文见仓根 `LICENSE`，Copyright (c) 2026 xunmeng2002）
- **适用范围**：本项目仅供个人学习、研究使用
- **风险提示**：本项目为个人开源项目，涉及真实资金交易前请自行充分测试并评估风险；实盘账户、数据库口令等敏感信息应自行妥善管理

## 九、补充说明

- **包含路径**：头文件统一使用 `#include <QuantTrading/XxxApi.h>` 风格；模块内部使用 `#include <Module/Xxx.h>`
- **命名空间**：公共 API 位于 `QuantTrading`，各模块分别位于 `QuantTrading::MdOffer`、`QuantTrading::SimExchange`、`QuantTrading::BackTest`、`QuantTrading::OrderMatch` 等
- **依赖链**：`Spark`（线程 / 日志 / 网络）→ `DbAdapters`（四库统一访问）→ `QuantTrading`
- **版本**：CTP API v6.7.9（`MdOffer` 启动日志可见 `API Version`）
- **编码变体**：MdApi / TraderApi / SimExchangeApi 各提供 **UTF-8**（`MdApi` 等）与 **GBK**（`MdGbkApi` 等）两套动态库
- **数据源适配**：`BackTest` 的 `MdReader` 当前 SQL 面向旧列名 parquet（如 `LastTraded` / `LastTurnover` / 数组盘口），缺失列以 NULL 占位；数据侧整理对齐 mdb schema 后可删除占位符，使 tick 涨跌停价等列真实可用
- **优雅退出**：MdOffer / SimExchange 支持 Ctrl+C / SIGTERM 按依赖序有序关停（`ShutdownSignal`）
