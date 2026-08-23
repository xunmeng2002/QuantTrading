#include "MdKernel.h"
#include "Error.h"
#include "MdSnap.h"
#include "MinuteBar.h"
#include "MdbFieldConverter.h"
#include <Spark/Core/Utility/Utility.h>
#include <Spark/Core/Utility/TimeUtility.h>
#include <Spark/Core/Logger/Logger.h>
#include <Spark/TemplateLib/ObjectPool/ObjectPool.h>

using namespace std;
using namespace mdb;
using namespace spark;
using namespace spark::core;
using namespace quanttrading;
using namespace quanttrading::bar;

namespace quanttrading::mdoffer
{
    MdKernel::MdKernel(mdb::Mdb* mdb)
        :ThreadBase("MdKernel"), m_Mdb(mdb), m_MdFront(nullptr), m_MdSpi(nullptr)
    {
        m_MinuteBar = new MinuteBar();
        m_MinuteBar->Subscribe(this);
        m_ReqSubMarketData = new ReqSubMarketDataField();
        m_BarMdPackage = new RtnBarMarketDataPackage();
    }
    void MdKernel::SetMdFront(MdFront* mdFront)
    {
        m_MdFront = mdFront;
        m_MdFront->Subscribe(this);
    }
    void MdKernel::SetMdSpi(CThostFtdcMdSpiImpl* mdSpi)
    {
        m_MdSpi = mdSpi;
    }
    void MdKernel::OnProtocolConnect(SessionIDType sessionID, const char* ip, int port)
    {
        WriteLog(LogLevel::Info, "MdKernel: OnConnect SessionID:%lld, IP:%s, Port:%d", sessionID, ip, port);
    }
    void MdKernel::OnProtocolDisConnect(SessionIDType sessionID, const char* ip, int port)
    {
        WriteLog(LogLevel::Info, "MdKernel: OnDisConnect SessionID:%lld, IP:%s, Port:%d", sessionID, ip, port);

        NotifyDisConnectPackage* package = NotifyDisConnectPackage::Allocate();
        package->Prepare(0, false, 0);
        package->NotifyDisConnect = ::Allocate<NotifyDisConnectField>();
        package->NotifyDisConnect->SessionID = sessionID;
        Utility::Strcpy(package->NotifyDisConnect->IPAddress, ip);
        package->NotifyDisConnect->Port = port;

        OnMessage(package);
    }
    void MdKernel::OnMessage(Package* package)
    {
        {
            std::lock_guard<std::mutex> guard(m_Mutex);
            m_RecvPackages.push_back(package);
        }
        m_ConditionVariable.notify_one();
    }
    void MdKernel::OnBarMarketData(BarMarketDataField* bar)
    {
        BarMarketData* barMarketData = ::Allocate<BarMarketData>();
        FieldToMdb(bar, barMarketData);
        auto oldBarMarketData = m_Mdb->t_BarMarketData->m_PrimaryKey->Select(barMarketData->TradingDay, barMarketData->ExchangeID, barMarketData->InstrumentID, barMarketData->BarPreces, barMarketData->BarPeriod, barMarketData->BarTime);
        if (oldBarMarketData == nullptr)
        {
            m_Mdb->t_BarMarketData->Insert(barMarketData);
        }
        else
        {
            m_Mdb->t_BarMarketData->Update(oldBarMarketData, barMarketData);
        }

        m_BarMdPackage->BarMarketData = bar;

        Utility::Strcpy(m_ReqSubMarketData->ExchangeID, bar->ExchangeID);
        Utility::Strcpy(m_ReqSubMarketData->InstrumentID, bar->InstrumentID);
        PushToAllSubscribed(m_ReqSubMarketData, m_BarMdPackage);
    }

    void MdKernel::OnDBConnected()
    {
        WriteLog(LogLevel::Info, "MdKernel::OnDBConnected");
        NotifyDBConnectPackage* package = ::Allocate<NotifyDBConnectPackage>();
        package->Prepare(0, false, 0);
        package->NotifyDBConnect = ::Allocate<NotifyDBConnectField>();

        OnMessage(package);
    }
    void MdKernel::OnDBDisConnected()
    {
        WriteLog(LogLevel::Info, "MdKernel::OnDBDisConnected");
        NotifyDBDisConnectPackage* package = ::Allocate<NotifyDBDisConnectPackage>();
        package->Prepare(0, false, 0);
        package->NotifyDBDisConnect = ::Allocate<NotifyDBDisConnectField>();

        OnMessage(package);
    }

    void MdKernel::Run()
    {
        CheckEvent();
        HandlePackage();
    }

    void MdKernel::CheckEvent()
    {
        std::unique_lock<std::mutex> guard(m_Mutex);
        m_ConditionVariable.wait_for(guard, m_TimeOut, [&] {return (!m_RecvPackages.empty()); });
    }
    int MdKernel::HandlePackage()
    {
        Package* package = nullptr;
        while ((package = GetPackage()) != nullptr)
        {
            bool needFree = true;
            switch (package->Head.PackageID)
            {
            case NotifyDisConnectPackage::PackageID:
            {
                HandleNotifyDisConnect((NotifyDisConnectPackage*)package);
                break;
            }
            case NotifyDBConnectPackage::PackageID:
            {
                HandleNotifyDBConnect((NotifyDBConnectPackage*)package);
                break;
            }
            case NotifyDBDisConnectPackage::PackageID:
            {
                HandleNotifyDBDisConnect((NotifyDBDisConnectPackage*)package);
                break;
            }
            case ReqMdUserLoginPackage::PackageID:
            {
                HandleReqMdUserLogin((ReqMdUserLoginPackage*)package);
                break;
            }
            case ReqSubMarketDataPackage::PackageID:
            {
                HandleReqSubMarketData((ReqSubMarketDataPackage*)package);
                break;
            }
            case RtnDepthMarketDataPackage::PackageID:
            {
                needFree = false;
                HandleRtnDepthMarketData((RtnDepthMarketDataPackage*)package);
                break;
            }
            default:
                WriteLog(LogLevel::Warning, "UnExpected PackageID:%d", package->Head.PackageID);
                break;
            }
            if (needFree)
            {
                package->Deallocate();
            }
        }
        return 0;
    }
    int MdKernel::HandleNotifyDisConnect(NotifyDisConnectPackage* package)
    {
        m_LoggedSessions.erase(package->NotifyDisConnect->SessionID);
        m_SessionSubscribeInstruments.erase(package->NotifyDisConnect->SessionID);
        return 0;
    }
    int MdKernel::HandleNotifyDBConnect(NotifyDBConnectPackage* package)
    {
        m_Mdb->InitDB();
        list<const ReqSubMarketDataField*> reqSubMds;
        ExchangeIDType exchangeID = "SHFE";
        auto instrumentItPair = m_Mdb->t_Instrument->m_PrimaryKey->SelectAll();
        for (auto& it = instrumentItPair.first; it != instrumentItPair.second; ++it)
        {
            // 全市场订阅复用全局注册表：重复合约自动去重，且消除此前的裸分配泄漏。
            ReqSubMarketDataField field;
            Utility::Strcpy(field.ExchangeID, (*it)->ExchangeID);
            Utility::Strcpy(field.InstrumentID, (*it)->InstrumentID);
            auto [fieldIt, isNew] = m_SubscribeInstruments.insert(field);
            if (isNew)
            {
                m_MinuteBar->ReqSubMarketData(fieldIt->ExchangeID, fieldIt->InstrumentID);
                reqSubMds.push_back(&*fieldIt);
            }
        }
        m_MdSpi->SubscribeMds(reqSubMds);
        return 0;
    }
    int MdKernel::HandleNotifyDBDisConnect(NotifyDBDisConnectPackage* package)
    {
        m_Mdb->SetInitStatus(false);
        return 0;
    }
    int MdKernel::HandleReqMdUserLogin(ReqMdUserLoginPackage* package)
    {
        auto errorID = ErrorNone;
        auto mdUser = m_Mdb->t_MdUser->m_PrimaryKey->Select(package->ReqMdUserLogin->UserID);
        if (mdUser == nullptr)
        {
            errorID = ErrorUserNotExist;
        }
        else if (strcmp(package->ReqMdUserLogin->Password, mdUser->Password) != 0)
        {
            errorID = ErrorIncorrectPassword;
        }
        else
        {
            auto mdUserLoginSession = m_Mdb->t_MdUserLoginSession->m_PrimaryKey->Select(package->SessionID);
            if (mdUserLoginSession != nullptr)
            {
                errorID = ErrorSessionAlreadyLogin;
            }
            else
            {
                mdUserLoginSession = MdUserLoginSession::Allocate();
                memset(mdUserLoginSession, 0, sizeof(MdUserLoginSession));
                Utility::Strcpy(mdUserLoginSession->MdUserID, mdUser->MdUserID);
                mdUserLoginSession->SessionID = package->SessionID;
                Utility::Strcpy(mdUserLoginSession->IPAddress, package->IPAddress);
                m_Mdb->t_MdUserLoginSession->Insert(mdUserLoginSession);

                m_LoggedSessions.insert(package->SessionID);
            }
        }

        RspMdUserLoginPackage* rspPackage = RspMdUserLoginPackage::Allocate();
        rspPackage->Prepare(package->SessionID, false, package->Head.MsgSeqNum);

        rspPackage->RspInfo = ::Allocate<RspInfoField>();
        rspPackage->RspInfo->ErrorID = errorID;
        Utility::Strcpy(rspPackage->RspInfo->ErrorMsg, GetErrorMessage(errorID));

        rspPackage->RspMdUserLogin = ::Allocate<RspMdUserLoginField>();
        Utility::Strcpy(rspPackage->RspMdUserLogin->UserID, package->ReqMdUserLogin->UserID);
        rspPackage->RspMdUserLogin->SessionID = package->SessionID;
        if (errorID == ErrorNone)
        {
            TimeUtility::GetLocalDateTime(rspPackage->RspMdUserLogin->LoginDate, rspPackage->RspMdUserLogin->LoginTime);
        }

        WriteLog(LogLevel::Info, "HandleReqMdUserLogin: ReqMdUserLoginPackage:%s, RspMdUserLoginPackage:%s", package->GetDebugString(), rspPackage->GetDebugString());

        m_MdFront->Send(rspPackage);
        rspPackage->Deallocate();
        return 0;
    }
    int MdKernel::HandleReqMdUserLogout(ReqMdUserLogoutPackage* package)
    {
        m_LoggedSessions.erase(package->SessionID);
        m_SessionSubscribeInstruments.erase(package->SessionID);

        RspMdUserLogoutPackage* rspPackage = RspMdUserLogoutPackage::Allocate();
        rspPackage->Prepare(package->SessionID, false, package->Head.MsgSeqNum);

        rspPackage->RspInfo = ::Allocate<RspInfoField>();
        rspPackage->RspInfo->ErrorID = ErrorNone;
        Utility::Strcpy(rspPackage->RspInfo->ErrorMsg, GetErrorMessage(ErrorNone));

        rspPackage->RspMdUserLogout = ::Allocate<RspMdUserLogoutField>();
        Utility::Strcpy(rspPackage->RspMdUserLogout->UserID, package->ReqMdUserLogout->UserID);



        WriteLog(LogLevel::Info, "HandleReqMdUserLogout: ReqMdUserLogoutPackage:%s, RspMdUserLogoutPackage:%s", package->GetDebugString(), rspPackage->GetDebugString());

        m_MdFront->Send(rspPackage);
        rspPackage->Deallocate();
        return 0;
    }
    int MdKernel::HandleReqSubMarketData(ReqSubMarketDataPackage* package)
    {
        WriteLog(LogLevel::Info, "HandleReqSubMarketData: %s", package->GetDebugString());
        auto reqSubMarketData = package->ReqSubMarketData;
        auto errorID = ErrorNone;
        auto loggedSessionIt = m_LoggedSessions.find(package->SessionID);
        if (loggedSessionIt == m_LoggedSessions.end())
        {
            errorID = ErrorUserNotLogin;
        }
        else
        {
            // 值语义：集合持有合约键的拷贝，全局注册表负责 CTP 去重（进程级），
            // 会话集合每会话一份、断开即整行移除；包析构释放自己的字段互不影响。
            auto [canonicalIt, isNew] = m_SubscribeInstruments.insert(*reqSubMarketData);
            if (isNew)
            {
                // set 节点地址在进程生命周期内稳定，MdSpi 以此反查 ExchangeID。
                m_MinuteBar->ReqSubMarketData(canonicalIt->ExchangeID, canonicalIt->InstrumentID);
                m_MdSpi->SubscribeMd(&*canonicalIt);
            }
            m_SessionSubscribeInstruments[package->SessionID].insert(*reqSubMarketData);
        }

        RspSubMarketDataPackage* rspPackage = RspSubMarketDataPackage::Allocate();
        rspPackage->Prepare(package->SessionID, false, package->Head.MsgSeqNum);
        rspPackage->RspInfo = ::Allocate<RspInfoField>();
        rspPackage->RspInfo->ErrorID = errorID;
        Utility::Strcpy(rspPackage->RspInfo->ErrorMsg, GetErrorMessage(errorID));
        rspPackage->RspSubMarketData = ::Allocate<RspSubMarketDataField>();
        Utility::Strcpy(rspPackage->RspSubMarketData->ExchangeID, reqSubMarketData->ExchangeID);
        Utility::Strcpy(rspPackage->RspSubMarketData->InstrumentID, reqSubMarketData->InstrumentID);
        m_MdFront->Send(rspPackage);
        rspPackage->Deallocate();

        auto rtnDepthMdPackage = MdSnap::GetInstance().GetDepthMd(reqSubMarketData->ExchangeID, reqSubMarketData->InstrumentID);
        if (rtnDepthMdPackage != nullptr)
        {
            rtnDepthMdPackage->Prepare(package->SessionID, false, package->Head.MsgSeqNum);
            m_MdFront->Send(rtnDepthMdPackage);
        }
        return 0;
    }
    int MdKernel::HandleRtnDepthMarketData(RtnDepthMarketDataPackage* package)
    {
        m_MinuteBar->OnDepthMarketData(package->DepthMarketData);

        DepthMarketData* depthMarketData = ::Allocate<DepthMarketData>();
        FieldToMdb(package->DepthMarketData, depthMarketData);
        auto oldDepthMarketData = m_Mdb->t_DepthMarketData->m_PrimaryKey->Select(depthMarketData->TradingDay, depthMarketData->ExchangeID, depthMarketData->InstrumentID);
        if (oldDepthMarketData == nullptr)
        {
            m_Mdb->t_DepthMarketData->Insert(depthMarketData);
        }
        else
        {
            m_Mdb->t_DepthMarketData->Update(oldDepthMarketData, depthMarketData);
        }

        package = MdSnap::GetInstance().AddDepthMd(package);
        Utility::Strcpy(m_ReqSubMarketData->ExchangeID, package->DepthMarketData->ExchangeID);
        Utility::Strcpy(m_ReqSubMarketData->InstrumentID, package->DepthMarketData->InstrumentID);
        PushToAllSubscribed(m_ReqSubMarketData, package);
        return 0;
    }

    Package* MdKernel::GetPackage()
    {
        std::lock_guard<std::mutex> guard(m_Mutex);
        if (m_RecvPackages.empty())
        {
            return nullptr;
        }
        auto package = m_RecvPackages.front();
        m_RecvPackages.pop_front();
        return package;
    }
    void MdKernel::PushToAll(Package* package)
    {
        for (auto& item : m_SessionSubscribeInstruments)
        {
            package->Prepare(item.first, false, 0);
            if (!m_MdFront->Send(package))
            {
                WriteLog(LogLevel::Error, "PushToAll MdFront->Send Failed. SessionID:%lld, Package:%s", item.first, package->GetDebugString());
            }
        }
    }
    void MdKernel::PushToAllSubscribed(ReqSubMarketDataField* reqSubMarketData, Package* package)
    {
        for (auto& item : m_SessionSubscribeInstruments)
        {
            auto& instruments = item.second;
            if (instruments.find(*reqSubMarketData) != instruments.end())
            {
                package->Prepare(item.first, false, 0);
                if (!m_MdFront->Send(package))
                {
                    WriteLog(LogLevel::Error, "PushToAllSubscribed MdFront->Send Failed. SessionID:%lld, Package:%s", item.first, package->GetDebugString());
                }
            }
        }
    }
}
