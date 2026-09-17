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
using namespace QuantTrading;
using namespace Spark;
using namespace Spark::Core;
using namespace QuantTrading;
using namespace QuantTrading::Bar;

namespace QuantTrading::MdOffer
{
    MdKernel::MdKernel(QuantTrading::Mdb* mdb, const TradeSessions& tradeSessions,
        const std::list<Spark::Core::SubscribeInstrument*>& startupSubscribeInstruments)
        :ThreadBase("MdKernel"), mdb_(mdb), mdFront_(nullptr), mdSpi_(nullptr), startupSubscribeInstruments_(startupSubscribeInstruments)
    {
        minuteBar_ = new MinuteBar(tradeSessions);
        minuteBar_->Subscribe(this);
        // 复用为查询键（仅 ExchangeId/InstrumentId 参与比较），零初始化以免未参与赋值的字段带出随机值
        reqSubMarketData_ = new ReqSubMarketDataField();
        memset(reqSubMarketData_, 0, sizeof(ReqSubMarketDataField));
        barMdPackage_ = new RtnBarMarketDataPackage();
    }
    void MdKernel::SetMdFront(MdFront* mdFront)
    {
        mdFront_ = mdFront;
        mdFront_->Subscribe(this);
    }
    void MdKernel::SetMdSpi(CThostFtdcMdSpiImpl* mdSpi)
    {
        mdSpi_ = mdSpi;
    }
    void MdKernel::OnProtocolConnect(SessionIdType sessionId, const char* ip, int port)
    {
        WriteLog(LogLevel::Info, "MdKernel: OnConnect SessionId:%lld, IP:%s, Port:%d", sessionId, ip, port);
    }
    void MdKernel::OnProtocolDisConnect(SessionIdType sessionId, const char* ip, int port)
    {
        WriteLog(LogLevel::Info, "MdKernel: OnDisConnect SessionId:%lld, IP:%s, Port:%d", sessionId, ip, port);

        NotifyDisConnectPackage* package = NotifyDisConnectPackage::Allocate();
        package->Prepare(0, false, 0);
        package->NotifyDisConnect = ::Allocate<NotifyDisConnectField>();
        package->NotifyDisConnect->SessionId = sessionId;
        Utility::Strcpy(package->NotifyDisConnect->IpAddress, ip);
        package->NotifyDisConnect->Port = port;

        OnMessage(package);
    }
    void MdKernel::OnMessage(Package* package)
    {
        {
            std::lock_guard<std::mutex> guard(mutex_);
            recvPackages_.push_back(package);
        }
        conditionVariable_.notify_one();
    }
    void MdKernel::OnBarMarketData(BarMarketDataField* bar)
    {
        BarMarketData* barMarketData = ::Allocate<BarMarketData>();
        FieldToMdb(bar, barMarketData);
        auto oldBarMarketData = mdb_->BarMarketData->PrimaryKey->Select(barMarketData->TradingDay, barMarketData->ExchangeId, barMarketData->InstrumentId, barMarketData->BarPreces, barMarketData->BarPeriod, barMarketData->BarTime);
        if (oldBarMarketData == nullptr)
        {
            mdb_->BarMarketData->Insert(barMarketData);
        }
        else
        {
            mdb_->BarMarketData->Update(oldBarMarketData, barMarketData);
        }

        barMdPackage_->BarMarketData = bar;

        Utility::Strcpy(reqSubMarketData_->ExchangeId, bar->ExchangeId);
        Utility::Strcpy(reqSubMarketData_->InstrumentId, bar->InstrumentId);
        PushToAllSubscribed(reqSubMarketData_, barMdPackage_);
    }

    void MdKernel::OnDbConnected()
    {
        WriteLog(LogLevel::Info, "MdKernel::OnDbConnected");
        NotifyDbConnectPackage* package = ::Allocate<NotifyDbConnectPackage>();
        package->Prepare(0, false, 0);
        package->NotifyDbConnect = ::Allocate<NotifyDbConnectField>();

        OnMessage(package);
    }
    void MdKernel::OnDbDisConnected()
    {
        WriteLog(LogLevel::Info, "MdKernel::OnDbDisConnected");
        NotifyDbDisConnectPackage* package = ::Allocate<NotifyDbDisConnectPackage>();
        package->Prepare(0, false, 0);
        package->NotifyDbDisConnect = ::Allocate<NotifyDbDisConnectField>();

        OnMessage(package);
    }

    void MdKernel::Run()
    {
        CheckEvent();
        HandlePackage();
    }

    void MdKernel::CheckEvent()
    {
        std::unique_lock<std::mutex> guard(mutex_);
        conditionVariable_.wait_for(guard, timeOut_, [&] {return (!recvPackages_.empty()); });
    }
    int MdKernel::HandlePackage()
    {
        Package* package = nullptr;
        while ((package = GetPackage()) != nullptr)
        {
            if (DispatchPackage(package))
            {
                package->Deallocate();
            }
        }
        return 0;
    }
    int MdKernel::HandleNotifyDisConnect(NotifyDisConnectPackage* package)
    {
        if (package->NotifyDisConnect == nullptr)
        {
            // 字段区缺失时解析层仍返回成功（只拦"多余字段"，不校验"缺失字段"），此处不判空即读空指针；
            // 断开清理以字段内的 SessionId 为键，缺字段则无从清理，直接丢弃
            WriteLog(LogLevel::Warning, "HandleNotifyDisConnect: missing field zone. SessionId:%lld", package->SessionId);
            return 0;
        }
        sessionSubscribeInstruments_.erase(package->NotifyDisConnect->SessionId);

        // 同步清理持久化会话记录，否则同 SessionId 重连会命中 ErrorSessionAlreadyLogin。
        mdb_->MdUserLoginSession->EraseBySessionIdIndex(package->NotifyDisConnect->SessionId);
        return 0;
    }
    int MdKernel::HandleNotifyDbConnect(NotifyDbConnectPackage* package)
    {
        mdb_->InitDb();
        list<const ReqSubMarketDataField*> reqSubMds;
        for (auto startupSubscribeInstrument : startupSubscribeInstruments_)
        {
            // 启动订阅复用全局注册表：重复合约自动去重，且消除此前的裸分配泄漏。
            // 启动订阅不对 bar 周期提要求，BarPreces/BarPeriod 置 0
            ReqSubMarketDataField field;
            memset(&field, 0, sizeof(ReqSubMarketDataField));
            Utility::Strcpy(field.ExchangeId, startupSubscribeInstrument->ExchangeId.c_str());
            Utility::Strcpy(field.InstrumentId, startupSubscribeInstrument->InstrumentId.c_str());
            auto [fieldIt, isNew] = subscribeInstruments_.insert(field);
            if (isNew)
            {
                minuteBar_->ReqSubMarketData(fieldIt->ExchangeId, fieldIt->InstrumentId);
                reqSubMds.push_back(&*fieldIt);
            }
        }
        if (mdSpi_ != nullptr)
        {
            mdSpi_->SubscribeMds(reqSubMds);
        }
        return 0;
    }
    int MdKernel::HandleNotifyDbDisConnect(NotifyDbDisConnectPackage* package)
    {
        mdb_->SetInitStatus(false);
        return 0;
    }
    int MdKernel::HandleReqMdUserLogin(ReqMdUserLoginPackage* package)
    {
        auto reqMdUserLogin = package->ReqMdUserLogin;
        // 登录处理在鉴权之前，字段区缺失时解析层仍返回成功，这里必须先判空：
        // 否则任何能建立连接的客户端发一个"只有包头"的登录包就能打到空指针上
        auto errorId = ErrorUserNotExist;
        if (reqMdUserLogin == nullptr)
        {
            WriteLog(LogLevel::Warning, "HandleReqMdUserLogin: missing field zone. SessionId:%lld", package->SessionId);
        }
        else
        {
            auto mdUser = mdb_->MdUser->PrimaryKey->Select(reqMdUserLogin->UserId);
            if (mdUser == nullptr)
            {
                errorId = ErrorUserNotExist;
            }
            else if (strcmp(reqMdUserLogin->Password, mdUser->Password) != 0)
            {
                errorId = ErrorIncorrectPassword;
            }
            else
            {
                auto mdUserLoginSession = mdb_->MdUserLoginSession->PrimaryKey->Select(mdUser->MdUserId, package->SessionId);
                if (mdUserLoginSession != nullptr)
                {
                    errorId = ErrorSessionAlreadyLogin;
                }
                else
                {
                    mdUserLoginSession = MdUserLoginSession::Allocate();
                    memset(mdUserLoginSession, 0, sizeof(MdUserLoginSession));
                    Utility::Strcpy(mdUserLoginSession->MdUserId, mdUser->MdUserId);
                    mdUserLoginSession->SessionId = package->SessionId;
                    Utility::Strcpy(mdUserLoginSession->IpAddress, package->IpAddress);
                    if (mdb_->MdUserLoginSession->Insert(mdUserLoginSession))
                    {
                        errorId = ErrorNone;
                    }
                    else
                    {
                        errorId = ErrorSessionAlreadyLogin;
                    }
                }
            }
        }

        RspMdUserLoginPackage* rspPackage = RspMdUserLoginPackage::Allocate();
        rspPackage->Prepare(package->SessionId, false, package->Head.MsgSeqNum);

        rspPackage->RspInfo = ::Allocate<RspInfoField>();
        rspPackage->RspInfo->ErrorId = errorId;
        Utility::Strcpy(rspPackage->RspInfo->ErrorMsg, GetErrorMessage(errorId));

        rspPackage->RspMdUserLogin = ::Allocate<RspMdUserLoginField>();
        if (reqMdUserLogin != nullptr)
        {
            Utility::Strcpy(rspPackage->RspMdUserLogin->UserId, reqMdUserLogin->UserId);
        }
        rspPackage->RspMdUserLogin->SessionId = package->SessionId;
        if (errorId == ErrorNone)
        {
            TimeUtility::GetLocalDateTime(rspPackage->RspMdUserLogin->LoginDate, rspPackage->RspMdUserLogin->LoginTime);
        }

        WriteLog(LogLevel::Info, "HandleReqMdUserLogin: ReqMdUserLoginPackage:%s, RspMdUserLoginPackage:%s", package->GetDebugString(), rspPackage->GetDebugString());

        mdFront_->Send(rspPackage);
        rspPackage->Deallocate();
        return 0;
    }
    int MdKernel::HandleReqMdUserLogout(ReqMdUserLogoutPackage* package)
    {
        sessionSubscribeInstruments_.erase(package->SessionId);

        // 同步清理持久化会话记录，否则同 SessionId 重登会命中 ErrorSessionAlreadyLogin。
        mdb_->MdUserLoginSession->EraseBySessionIdIndex(package->SessionId);

        RspMdUserLogoutPackage* rspPackage = RspMdUserLogoutPackage::Allocate();
        rspPackage->Prepare(package->SessionId, false, package->Head.MsgSeqNum);

        rspPackage->RspInfo = ::Allocate<RspInfoField>();
        rspPackage->RspInfo->ErrorId = ErrorNone;
        Utility::Strcpy(rspPackage->RspInfo->ErrorMsg, GetErrorMessage(ErrorNone));

        // 字段区缺失时解析层仍返回成功，此处判空避免读空指针；登出以传输层 SessionId 为准，
        // 响应里的 UserId 只是回显，缺字段时留空即可
        rspPackage->RspMdUserLogout = ::Allocate<RspMdUserLogoutField>();
        if (package->ReqMdUserLogout == nullptr)
        {
            WriteLog(LogLevel::Warning, "HandleReqMdUserLogout: missing field zone. SessionId:%lld", package->SessionId);
        }
        else
        {
            Utility::Strcpy(rspPackage->RspMdUserLogout->UserId, package->ReqMdUserLogout->UserId);
        }



        WriteLog(LogLevel::Info, "HandleReqMdUserLogout: ReqMdUserLogoutPackage:%s, RspMdUserLogoutPackage:%s", package->GetDebugString(), rspPackage->GetDebugString());

        mdFront_->Send(rspPackage);
        rspPackage->Deallocate();
        return 0;
    }
    int MdKernel::HandleReqSubMarketData(ReqSubMarketDataPackage* package)
    {
        WriteLog(LogLevel::Info, "HandleReqSubMarketData: %s", package->GetDebugString());
        auto reqSubMarketData = package->ReqSubMarketData;
        auto errorId = ErrorNone;
        if (!IsSessionLoggedIn(package->SessionId))
        {
            errorId = ErrorUserNotLogin;
        }
        else if (reqSubMarketData == nullptr)
        {
            // 报文体缺整段字段区时解析层仍返回成功（它只拦"多余字段"，不校验"缺失字段"），
            // 这里补判空并按"合约不存在"回复，否则下面每处解引用都会读到空指针
            WriteLog(LogLevel::Warning, "HandleReqSubMarketData: missing field zone. SessionId:%lld", package->SessionId);
            errorId = ErrorInstrumentNotExist;
        }
        else
        {
            // 值语义：集合持有合约键的拷贝，全局注册表负责 CTP 去重（进程级），
            // 会话集合每会话一份、断开即整行移除；包析构释放自己的字段互不影响。
            auto [canonicalIt, isNew] = subscribeInstruments_.insert(*reqSubMarketData);
            if (isNew)
            {
                // set 节点地址在进程生命周期内稳定，MdSpi 以此反查 ExchangeId。
                minuteBar_->ReqSubMarketData(canonicalIt->ExchangeId, canonicalIt->InstrumentId);
                mdSpi_->SubscribeMd(&*canonicalIt);
            }
            sessionSubscribeInstruments_[package->SessionId].insert(*reqSubMarketData);
        }

        RspSubMarketDataPackage* rspPackage = RspSubMarketDataPackage::Allocate();
        rspPackage->Prepare(package->SessionId, false, package->Head.MsgSeqNum);
        rspPackage->RspInfo = ::Allocate<RspInfoField>();
        rspPackage->RspInfo->ErrorId = errorId;
        Utility::Strcpy(rspPackage->RspInfo->ErrorMsg, GetErrorMessage(errorId));
        rspPackage->RspSubMarketData = ::Allocate<RspSubMarketDataField>();
        if (reqSubMarketData != nullptr)
        {
            Utility::Strcpy(rspPackage->RspSubMarketData->ExchangeId, reqSubMarketData->ExchangeId);
            Utility::Strcpy(rspPackage->RspSubMarketData->InstrumentId, reqSubMarketData->InstrumentId);
        }
        mdFront_->Send(rspPackage);
        rspPackage->Deallocate();

        if (reqSubMarketData != nullptr)
        {
            auto rtnDepthMdPackage = MdSnap::GetInstance().GetDepthMd(reqSubMarketData->ExchangeId, reqSubMarketData->InstrumentId);
            if (rtnDepthMdPackage != nullptr)
            {
                rtnDepthMdPackage->Prepare(package->SessionId, false, package->Head.MsgSeqNum);
                mdFront_->Send(rtnDepthMdPackage);
            }
        }
        return 0;
    }
    int MdKernel::HandleRtnDepthMarketData(RtnDepthMarketDataPackage* package)
    {
        if (package->DepthMarketData == nullptr)
        {
            // 字段区缺失时解析层仍返回成功，往下走 MinuteBar 会按空指针取合约会话；
            // 本分支由 DispatchPackage 返回 false（所有权交给 MdSnap），丢弃时须自行归还
            WriteLog(LogLevel::Warning, "HandleRtnDepthMarketData: missing field zone. SessionId:%lld", package->SessionId);
            package->Deallocate();
            return 0;
        }
        minuteBar_->OnDepthMarketData(package->DepthMarketData);

        DepthMarketData* depthMarketData = ::Allocate<DepthMarketData>();
        FieldToMdb(package->DepthMarketData, depthMarketData);
        auto oldDepthMarketData = mdb_->DepthMarketData->PrimaryKey->Select(depthMarketData->TradingDay, depthMarketData->ExchangeId, depthMarketData->InstrumentId);
        if (oldDepthMarketData == nullptr)
        {
            mdb_->DepthMarketData->Insert(depthMarketData);
        }
        else
        {
            mdb_->DepthMarketData->Update(oldDepthMarketData, depthMarketData);
        }

        package = MdSnap::GetInstance().AddDepthMd(package);
        Utility::Strcpy(reqSubMarketData_->ExchangeId, package->DepthMarketData->ExchangeId);
        Utility::Strcpy(reqSubMarketData_->InstrumentId, package->DepthMarketData->InstrumentId);
        PushToAllSubscribed(reqSubMarketData_, package);
        return 0;
    }

    bool MdKernel::IsSessionLoggedIn(const SessionIdType& sessionId)
    {
        auto sessionIDRange = mdb_->MdUserLoginSession->SessionIdIndex->EqualRange(sessionId);
        return sessionIDRange.first != sessionIDRange.second;
    }

    Package* MdKernel::GetPackage()
    {
        std::lock_guard<std::mutex> guard(mutex_);
        if (recvPackages_.empty())
        {
            return nullptr;
        }
        auto package = recvPackages_.front();
        recvPackages_.pop_front();
        return package;
    }
    void MdKernel::PushToAll(Package* package)
    {
        for (auto& item : sessionSubscribeInstruments_)
        {
            package->Prepare(item.first, false, 0);
            if (!mdFront_->Send(package))
            {
                WriteLog(LogLevel::Error, "PushToAll MdFront->Send Failed. SessionId:%lld, Package:%s", item.first, package->GetDebugString());
            }
        }
    }
    void MdKernel::PushToAllSubscribed(ReqSubMarketDataField* reqSubMarketData, Package* package)
    {
        for (auto& item : sessionSubscribeInstruments_)
        {
            auto& instruments = item.second;
            if (instruments.find(*reqSubMarketData) != instruments.end())
            {
                package->Prepare(item.first, false, 0);
                if (!mdFront_->Send(package))
                {
                    WriteLog(LogLevel::Error, "PushToAllSubscribed MdFront->Send Failed. SessionId:%lld, Package:%s", item.first, package->GetDebugString());
                }
            }
        }
    }
}
