

# QuantTrading - 量化交易系统

## 项目简介

QuantTrading 是一个专业的量化交易系统,采用 C++ 开发,支持多市场、多策略的交易框架。该系统集成了市场数据接收、订单管理、交易执行、回测等功能,并提供了丰富的 API 接口供策略开发使用。

## 主要特性

### 市场数据接口 (MdApi)
- 支持实时行情订阅
- 支持深度行情数据
- 支持分钟级 K 线数据生成
- 提供 C/C++ 和 UTF-8 编码的 API 接口

### 交易接口 (TradeApi)
- 支持账户登录认证
- 支持订单管理(买入、卖出、撤单)
- 支持持仓查询
- 支持资金划转
- 支持多种查询功能(持仓、成交、委托等)

### 模拟交易接口 (SimExchangeApi)
- 支持模拟交易环境
- 支持交易所订单撮合
- 提供完整的模拟交易功能

### CTP 集成
- 支持 CTP 6.7.2 和 6.7.9 版本
- 提供完整的行情和交易中间件
- 支持结构化日志记录

### K 线生成
- 自动生成分钟级 K 线
- 支持断线重连后的数据补全
- 提供完整的 Bar 数据处理工具

## 项目结构

```
QuantTrading/
├── Api/                    # API 接口层
│   ├── ApiBase/            # 基础 API 框架
│   ├── MdApi/              # 行情 API (C++ 接口)
│   ├── MdCApi/             # 行情 API (C 接口)
│   ├── MdUtf8CApi/         # 行情 API (UTF-8 C 接口)
│   ├── TradeApi/           # 交易 API (C++ 接口)
│   ├── TradeCApi/          # 交易 API (C 接口)
│   ├── TradeUtf8CApi/      # 交易 API (UTF-8 C 接口)
│   └── SimExchangeApi/     # 模拟交易 API
├── Source/                 # 核心实现
│   ├── Bar/                # K 线数据处理
│   └── Ctp/                # CTP 接口实现
├── Configs/                # 配置文件
│   ├── BackTest.json       # 回测配置
│   ├── CtpAccountInfo.json # CTP 账户配置
│   ├── Init.json           # 初始化配置
│   ├── MdOffer.json        # 行情服务配置
│   └── ServerConfig.json   # 服务器配置
├── Model/                  # 数据模型定义
│   ├── Api/                # API 数据包定义
│   ├── Configs/            # 配置文件模型
│   ├── Error/              # 错误码定义
│   ├── Packages/           # 数据包模型
│   └── Tables/             # 数据库表模型
└── CMakeLists.txt          # 构建配置
```

## 编译要求

- CMake 3.10+
- C++17 编译器
- CTP 动态库 (6.7.2 或 6.7.9)

## 使用说明

### 1. 环境配置

修改 `Configs/` 目录下的配置文件:
- `CtpAccountInfo.json`: 配置 CTP 账户信息
- `MdOffer.json`: 配置行情服务器地址
- `Init.json`: 配置初始化参数

### 2. 编译项目

```bash
mkdir build
cd build
cmake ..
make
```

### 3. 运行程序

编译完成后,根据策略需求选择:
- 实时交易模式
- 回测模式
- 模拟交易模式

## API 使用示例

### 行情 API

```cpp
// 创建行情 API
MdApi* mdApi = MdApi::CreateMdApi();

// 注册回调
mdApi->RegisterSpi(new MyMdSpi());
mdApi->RegisterFront("tcp://127.0.0.1:7777");

// 登录
ReqMdUserLoginField loginReq;
mdApi->ReqMdUserLogin(&loginReq, 0);

// 订阅行情
ReqSubMarketDataField subReq;
strcpy(subReq.Ticker, "IF2106");
mdApi->ReqSubMarketData(&subReq, 0);
```

### 交易 API

```cpp
// 创建交易 API
TradeApi* tradeApi = TradeApi::CreateTradeApi();

// 注册回调
tradeApi->RegisterSpi(new MyTradeSpi());
tradeApi->RegisterFront("tcp://127.0.0.1:7788");

// 登录
ReqAccountLoginField loginReq;
tradeApi->ReqAccountLogin(&loginReq, 0);

// 下单
ReqInsertOrderField orderReq;
strcpy(orderReq.Ticker, "IF2106");
orderReq.Direction = '0';
orderReq.VolumeTotalOriginal = 1;
tradeApi->ReqInsertOrder(&orderReq, 0);
```

## 配置说明

### CtpAccountInfo.json
```json
{
  "brokerId": "9999",
  "userId": "your_user_id",
  "password": "your_password",
  "mdAddress": "tcp://127.0.0.1:7777",
  "tradeAddress": "tcp://127.0.0.1:7788"
}
```

## 注意事项

1. 使用前请确保已安装相应版本的 CTP 动态库
2. 请妥善保管账户密码信息
3. 建议在模拟环境充分测试后再投入实盘
4. 请遵守交易所规则和风险管理要求

## 许可证

本项目遵循相关开源协议,详情请查看 LICENSE 文件。

## 贡献指南

欢迎提交 Issue 和 Pull Request,共同完善本项目。