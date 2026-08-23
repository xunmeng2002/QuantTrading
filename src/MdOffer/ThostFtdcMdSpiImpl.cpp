#include "ThostFtdcMdSpiImpl.h"
#include <Spark/Core/Logger/Logger.h>
#include "MdKernel.h"
#include <Spark/Core/Utility/Utility.h>
#include <Spark/Core/Utility/TimeUtility.h>
#include <string.h>
#include <vector>

using namespace std;
using namespace spark;
using namespace spark::core;
using namespace quanttrading::packages;

namespace quanttrading::mdoffer
{
    CThostFtdcMdSpiImpl::CThostFtdcMdSpiImpl(CThostFtdcMdApi* MdApi, MdKernel* mdKernel)
        :m_MdApi(MdApi), m_MdKernel(mdKernel), m_IsLogged(false), m_RequestID(0), m_AccountInfo(nullptr)
    {}
    void CThostFtdcMdSpiImpl::OnFrontConnected()
    {
        CThostFtdcMdSpiMiddle::OnFrontConnected();
        ReqUserLogin();
    }
    void CThostFtdcMdSpiImpl::OnFrontDisconnected(int nReason)
    {
        CThostFtdcMdSpiMiddle::OnFrontDisconnected(nReason);
        m_IsLogged = false;
    }
    void CThostFtdcMdSpiImpl::OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast)
    {
        CThostFtdcMdSpiMiddle::OnRspUserLogin(pRspUserLogin, pRspInfo, nRequestID, bIsLast);
        m_IsLogged = true;
        std::vector<const char*> reqSubInstruments;
        {
            std::lock_guard<std::mutex> guard(m_Mutex);
            reqSubInstruments = m_ReqSubInstruments;
        }
        if (!reqSubInstruments.empty())
        {
            m_MdApi->SubscribeMarketData(const_cast<char**>(reqSubInstruments.data()), (int)reqSubInstruments.size());
        }
    }
    void CThostFtdcMdSpiImpl::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData)
    {
        CThostFtdcMdSpiMiddle::OnRtnDepthMarketData(pDepthMarketData);
        RtnDepthMarketDataPackage* package = RtnDepthMarketDataPackage::Allocate();
        package->Prepare(0, false, 0);
        package->DepthMarketData = ::Allocate<DepthMarketDataField>();
        memset(package->DepthMarketData, 0, sizeof(DepthMarketDataField));
        // 交易日归属必须用交易所 TradingDay：夜盘时 ActionDay 是自然日（如周五），TradingDay 才是下一交易日（如周一）。
        // CTP 部分行情可能不填充 TradingDay，此时回退到 ActionDay。
        if (strlen(pDepthMarketData->TradingDay) != 0)
        {
            Utility::Strcpy(package->DepthMarketData->TradingDay, pDepthMarketData->TradingDay);
        }
        else
        {
            Utility::Strcpy(package->DepthMarketData->TradingDay, pDepthMarketData->ActionDay);
        }
        Utility::Strcpy(package->DepthMarketData->InstrumentID, pDepthMarketData->InstrumentID);
        if (strlen(pDepthMarketData->ExchangeID) != 0)
        {
            Utility::Strcpy(package->DepthMarketData->ExchangeID, pDepthMarketData->ExchangeID);
        }
        else
        {
            std::lock_guard<std::mutex> guard(m_Mutex);
            auto reqSubMdIt = m_ReqSubMds.find(package->DepthMarketData->InstrumentID);
            if (reqSubMdIt != m_ReqSubMds.end())
            {
                Utility::Strcpy(package->DepthMarketData->ExchangeID, reqSubMdIt->second->ExchangeID);
            }
        }
        package->DepthMarketData->LastPrice = pDepthMarketData->LastPrice;
        package->DepthMarketData->PreSettlementPrice = pDepthMarketData->PreSettlementPrice;
        package->DepthMarketData->PreClosePrice = pDepthMarketData->PreClosePrice;
        package->DepthMarketData->PreOpenInterest = pDepthMarketData->PreOpenInterest;
        package->DepthMarketData->OpenPrice = pDepthMarketData->OpenPrice;
        package->DepthMarketData->HighestPrice = pDepthMarketData->HighestPrice;
        package->DepthMarketData->LowestPrice = pDepthMarketData->LowestPrice;
        package->DepthMarketData->ClosePrice = pDepthMarketData->ClosePrice;
        package->DepthMarketData->CurrVolume = 0;
        package->DepthMarketData->Volume = pDepthMarketData->Volume;
        package->DepthMarketData->CurrTurnover = 0;
        package->DepthMarketData->Turnover = pDepthMarketData->Turnover;
        package->DepthMarketData->OpenInterest = pDepthMarketData->OpenInterest;
        package->DepthMarketData->SettlementPrice = pDepthMarketData->SettlementPrice;
        package->DepthMarketData->UpperLimitPrice = pDepthMarketData->UpperLimitPrice;
        package->DepthMarketData->LowerLimitPrice = pDepthMarketData->LowerLimitPrice;
        package->DepthMarketData->AveragePrice = pDepthMarketData->AveragePrice;
        package->DepthMarketData->UpdateTs = atoll(pDepthMarketData->ActionDay) * 1000000000LL + TimeUtility::GetTimeFromTimeString(pDepthMarketData->UpdateTime) * 1000LL + pDepthMarketData->UpdateMillisec;

        package->DepthMarketData->AskPrice1 = pDepthMarketData->AskPrice1;
        package->DepthMarketData->AskPrice2 = pDepthMarketData->AskPrice2;
        package->DepthMarketData->AskPrice3 = pDepthMarketData->AskPrice3;
        package->DepthMarketData->AskPrice4 = pDepthMarketData->AskPrice4;
        package->DepthMarketData->AskPrice5 = pDepthMarketData->AskPrice5;
        package->DepthMarketData->AskVolume1 = pDepthMarketData->AskVolume1;
        package->DepthMarketData->AskVolume2 = pDepthMarketData->AskVolume2;
        package->DepthMarketData->AskVolume3 = pDepthMarketData->AskVolume3;
        package->DepthMarketData->AskVolume4 = pDepthMarketData->AskVolume4;
        package->DepthMarketData->AskVolume5 = pDepthMarketData->AskVolume5;

        package->DepthMarketData->BidPrice1 = pDepthMarketData->BidPrice1;
        package->DepthMarketData->BidPrice2 = pDepthMarketData->BidPrice2;
        package->DepthMarketData->BidPrice3 = pDepthMarketData->BidPrice3;
        package->DepthMarketData->BidPrice4 = pDepthMarketData->BidPrice4;
        package->DepthMarketData->BidPrice5 = pDepthMarketData->BidPrice5;
        package->DepthMarketData->BidVolume1 = pDepthMarketData->BidVolume1;
        package->DepthMarketData->BidVolume2 = pDepthMarketData->BidVolume2;
        package->DepthMarketData->BidVolume3 = pDepthMarketData->BidVolume3;
        package->DepthMarketData->BidVolume4 = pDepthMarketData->BidVolume4;
        package->DepthMarketData->BidVolume5 = pDepthMarketData->BidVolume5;

        m_MdKernel->OnMessage(package);
    }

    void CThostFtdcMdSpiImpl::SetAccountInfo(AccountInfo* accountInfo)
    {
        m_AccountInfo = accountInfo;
    }
    void CThostFtdcMdSpiImpl::SubscribeMd(const ReqSubMarketDataField* reqSubMd)
    {
        WriteLog(LogLevel::Info, "SubscribeMd: ExchangeID:%s, InstrumentID:%s", reqSubMd->ExchangeID, reqSubMd->InstrumentID);
        lock_guard<mutex> gurad(m_Mutex);
        if (!m_ReqSubMds.try_emplace(reqSubMd->InstrumentID, reqSubMd).second)
        {
            return;
        }
        m_ReqSubInstruments.push_back(reqSubMd->InstrumentID);
        if (m_IsLogged)
        {
            char* instrument[1] = { const_cast<char*>(reqSubMd->InstrumentID) };
            m_MdApi->SubscribeMarketData(instrument, 1);
        }
    }
    void CThostFtdcMdSpiImpl::SubscribeMds(const std::list<const ReqSubMarketDataField*>& reqSubMds)
    {
        WriteLog(LogLevel::Info, "SubscribeMds: Size:%d", reqSubMds.size());
        lock_guard<mutex> gurad(m_Mutex);
        // 本次新增合约，已登录时增量发送；累积清单仅用于重连全量补订。
        std::vector<const char*> newInstruments;
        for (auto reqSubMd : reqSubMds)
        {
            if (!m_ReqSubMds.try_emplace(reqSubMd->InstrumentID, reqSubMd).second)
            {
                continue;
            }
            m_ReqSubInstruments.push_back(reqSubMd->InstrumentID);
            newInstruments.push_back(reqSubMd->InstrumentID);
        }
        if (m_IsLogged && !newInstruments.empty())
        {
            m_MdApi->SubscribeMarketData(const_cast<char**>(newInstruments.data()), (int)newInstruments.size());
        }
    }

    void CThostFtdcMdSpiImpl::ReqUserLogin()
    {
        CThostFtdcReqUserLoginField userLogin;
        ::memset(&userLogin, 0, sizeof(userLogin));
        Utility::Strcpy(userLogin.TradingDay, "");
        Utility::Strcpy(userLogin.BrokerID, m_AccountInfo->BrokerID);
        Utility::Strcpy(userLogin.UserID, m_AccountInfo->InvestorID);
        Utility::Strcpy(userLogin.Password, m_AccountInfo->Password);
        Utility::Strcpy(userLogin.UserProductInfo, m_AccountInfo->UserProductInfo);

        int ret = m_MdApi->ReqUserLogin(&userLogin, m_RequestID++);
        WriteLog(LogLevel::Info, "ReqUserLogin: ret[%d]", ret);
    }
}
