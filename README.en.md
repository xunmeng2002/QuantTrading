# QuantTrading - Quantitative Trading System

## Project Overview

QuantTrading is a professional quantitative trading system developed in C++, supporting a multi-market, multi-strategy trading framework. The system integrates market data reception, order management, trade execution, backtesting, and other functionalities, and provides rich API interfaces for strategy development.

## Key Features

### Market Data Interface (MdApi)
- Supports real-time market data subscription
- Supports depth market data
- Supports minute-level K-line data generation
- Provides API interfaces in C/C++ with UTF-8 encoding

### Trading Interface (TradeApi)
- Supports account login and authentication
- Supports order management (buy, sell, cancel)
- Supports position inquiry
- Supports fund transfer
- Supports multiple query functions (position, trade, order, etc.)

### Simulation Trading Interface (SimExchangeApi)
- Supports simulation trading environment
- Supports exchange order matching
- Provides complete simulation trading functionality

### CTP Integration
- Supports CTP versions 6.7.2 and 6.7.9
- Provides complete market and trading middleware
- Supports structured logging

### K-Line Generation
- Automatically generates minute-level K-lines
- Supports data recovery after disconnection and reconnection
- Provides comprehensive Bar data processing tools

## Project Structure

```
QuantTrading/
├── Api/                    # API Layer
│   ├── ApiBase/            # Base API Framework
│   ├── MdApi/              # Market Data API (C++ Interface)
│   ├── MdCApi/             # Market Data API (C Interface)
│   ├── MdUtf8CApi/         # Market Data API (UTF-8 C Interface)
│   ├── TradeApi/           # Trading API (C++ Interface)
│   ├── TradeCApi/          # Trading API (C Interface)
│   ├── TradeUtf8CApi/      # Trading API (UTF-8 C Interface)
│   └── SimExchangeApi/     # Simulation Trading API
├── Source/                 # Core Implementation
│   ├── Bar/                # K-Line Data Processing
│   └── Ctp/                # CTP Interface Implementation
├── Configs/                # Configuration Files
│   ├── BackTest.json       # Backtesting Configuration
│   ├── CtpAccountInfo.json # CTP Account Configuration
│   ├── Init.json           # Initialization Configuration
│   ├── MdOffer.json        # Market Data Service Configuration
│   └── ServerConfig.json   # Server Configuration
├── Model/                  # Data Model Definitions
│   ├── Api/                # API Data Packet Definitions
│   ├── Configs/            # Configuration File Models
│   ├── Error/              # Error Code Definitions
│   ├── Packages/           # Data Packet Models
│   └── Tables/             # Database Table Models
└── CMakeLists.txt          # Build Configuration
```

## Build Requirements

- CMake 3.10+
- C++17 Compatible Compiler
- CTP Dynamic Library (version 6.7.2 or 6.7.9)

## Usage Instructions

### 1. Environment Configuration

Modify the configuration files under the `Configs/` directory:
- `CtpAccountInfo.json`: Configure CTP account information
- `MdOffer.json`: Configure market data server address
- `Init.json`: Configure initialization parameters

### 2. Build the Project

```bash
mkdir build
cd build
cmake ..
make
```

### 3. Run the Program

After compilation, choose the appropriate mode based on your strategy needs:
- Real-time Trading Mode
- Backtesting Mode
- Simulation Trading Mode

## API Usage Examples

### Market Data API

```cpp
// Create market data API
MdApi* mdApi = MdApi::CreateMdApi();

// Register callback
mdApi->RegisterSpi(new MyMdSpi());
mdApi->RegisterFront("tcp://127.0.0.1:7777");

// Login
ReqMdUserLoginField loginReq;
mdApi->ReqMdUserLogin(&loginReq, 0);

// Subscribe to market data
ReqSubMarketDataField subReq;
strcpy(subReq.Ticker, "IF2106");
mdApi->ReqSubMarketData(&subReq, 0);
```

### Trading API

```cpp
// Create trading API
TradeApi* tradeApi = TradeApi::CreateTradeApi();

// Register callback
tradeApi->RegisterSpi(new MyTradeSpi());
tradeApi->RegisterFront("tcp://127.0.0.1:7788");

// Login
ReqAccountLoginField loginReq;
tradeApi->ReqAccountLogin(&loginReq, 0);

// Place order
ReqInsertOrderField orderReq;
strcpy(orderReq.Ticker, "IF2106");
orderReq.Direction = '0';
orderReq.VolumeTotalOriginal = 1;
tradeApi->ReqInsertOrder(&orderReq, 0);
```

## Configuration Details

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

## Notes

1. Ensure the corresponding version of the CTP dynamic library is installed before use.
2. Safeguard your account credentials.
3. Thoroughly test in a simulation environment before deploying to live trading.
4. Comply with exchange rules and risk management requirements.

## License

This project follows relevant open-source licenses. See the LICENSE file for details.

## Contribution Guidelines

Issues and pull requests are welcome to help improve this project.