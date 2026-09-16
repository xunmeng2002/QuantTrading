#pragma once
#include "Packages.h"
#include "MdFront.h"
#include "ThostFtdcMdSpiImpl.h"
#include "FieldsCompare.h"
#include "BarInterface.h"
#include "MinuteBar.h"
#include "Mdb.h"
#include <Spark/Core/Thread/ThreadBase.h>
#include <Spark/Core/ConfigStructs/ConfigStructs.h>
#include <Spark/Network/Protocol/ProtocolSubscriber.h>
#include <Spark/Network/Protocol/Package.h>
#include <map>
#include <set>
#include <list>
#include <mutex>
#include <condition_variable>

using namespace QuantTrading::Packages;
using QuantTrading::bar::MinuteBar;
using QuantTrading::bar::TradeSessions;

namespace QuantTrading::mdoffer
{
    class MdKernel : public Spark::core::ThreadBase, public Spark::Network::ProtocolSubscriber, public QuantTrading::bar::BarSubscriber, public dbadapters::DBSubscriber
    {
    public:
        // tradeSessions 须长于本对象（转交 MinuteBar 持有），且须在首个订阅到达前装载完成；
        // 启动订阅清单项指向配置单例，生命周期同进程
        MdKernel(QuantTrading::Mdb* mdb, const TradeSessions& tradeSessions,
            const std::list<Spark::core::SubscribeInstrument*>& startupSubscribeInstruments);
        void SetMdFront(MdFront* mdFront);
        void SetMdSpi(CThostFtdcMdSpiImpl* mdSpi);


        virtual void OnProtocolConnect(SessionIdType sessionId, const char* ip, int port) override;
        virtual void OnProtocolDisConnect(SessionIdType sessionId, const char* ip, int port) override;
        virtual void OnMessage(Package* package) override;

        virtual void OnBarMarketData(BarMarketDataField* bar) override;

        virtual void OnDBConnected() override;
        virtual void OnDBDisConnected() override;
    protected:
        virtual void Run() override;
        void CheckEvent();
        int HandlePackage();
        // 返回 true 表示包已用完可回收，false 表示 Handler 接管了所有权
        bool DispatchPackage(Package* package);
        int HandleNotifyDisConnect(NotifyDisConnectPackage* package);
        int HandleNotifyDBConnect(NotifyDBConnectPackage* package);
        int HandleNotifyDBDisConnect(NotifyDBDisConnectPackage* package);
        int HandleReqMdUserLogin(ReqMdUserLoginPackage* package);
        int HandleReqMdUserLogout(ReqMdUserLogoutPackage* package);
        int HandleReqSubMarketData(ReqSubMarketDataPackage* package);
        int HandleRtnDepthMarketData(RtnDepthMarketDataPackage* package);

        Package* GetPackage();
        void PushToAll(Package* package);
        void PushToAllSubscribed(ReqSubMarketDataField* reqSubMarketData, Package* package);
        bool IsSessionLoggedIn(const SessionIdType& sessionId);

    private:
        QuantTrading::Mdb* m_Mdb;
        MdFront* m_MdFront;
        CThostFtdcMdSpiImpl* m_MdSpi;
        MinuteBar* m_MinuteBar;
        std::list<Spark::core::SubscribeInstrument*> m_StartupSubscribeInstruments;

        std::mutex m_Mutex;
        std::condition_variable m_ConditionVariable;

        std::set<ReqSubMarketDataField> m_SubscribeInstruments;
        std::map<SessionIdType, std::set<ReqSubMarketDataField>> m_SessionSubscribeInstruments;
        std::list<Package*> m_RecvPackages;

        ReqSubMarketDataField* m_ReqSubMarketData;
        RtnBarMarketDataPackage* m_BarMdPackage;
    };
}
