#pragma once
#include "ThostFtdcMdSpiMiddle.h"
#include "Environment.h"
#include <QuantTrading/Fields.h>
#include <atomic>
#include <mutex>
#include <list>
#include <set>
#include <map>
#include <vector>
#include <string>


using QuantTrading::AccountInfo;
namespace QuantTrading::MdOffer
{
    class MdKernel;
    class CThostFtdcMdSpiImpl : public CThostFtdcMdSpiMiddle
    {
    public:
        CThostFtdcMdSpiImpl(CThostFtdcMdApi* MdApi, MdKernel* mdKernel);

        virtual void OnFrontConnected() override;
        virtual void OnFrontDisconnected(int nReason) override;
        virtual void OnRspUserLogin(CThostFtdcRspUserLoginField* pRspUserLogin, CThostFtdcRspInfoField* pRspInfo, int nRequestID, bool bIsLast) override;
        virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField* pDepthMarketData) override;

        void SetAccountInfo(AccountInfo* accountInfo);
        void SubscribeMd(const ReqSubMarketDataField* reqSubMd);
        void SubscribeMds(const std::list<const ReqSubMarketDataField*>& reqSubMds);
    private:
        void ReqUserLogin();

        CThostFtdcMdApi* mdApi_;
        MdKernel* mdKernel_;
        std::atomic<bool> isLogged_;
        int requestId_;
        AccountInfo* accountInfo_;
        std::map<std::string, const ReqSubMarketDataField*> reqSubMds_;
        std::vector<const char*> reqSubInstruments_;
        std::mutex mutex_;
    };
}
