#pragma once
#include "Error.h"
#include "Packages.h"

#include <Spark/Core/Logger/Logger.h>
#include <Spark/Core/Utility/Utility.h>
#include <Spark/Network/Protocol/Protocol.h>
#include <Spark/TemplateLib/ObjectPool/ObjectPool.h>

namespace quanttrading
{
	// 外部链路收到的请求包若解析不出字段区，必须就地回绝并把原因回给对端：缺字段的包流进
	// Handler，只会逼每个 Handler 各写一遍判空、各挑一个与真实原因不符的域内错误码。
	// 响应包类型随请求包而变（ReqXxx -> RspXxx），故取模板参数而不做重载
	template <typename RspPackageType>
	bool ReplyPackageParseFailed(spark::network::Protocol* front, SessionIDType sessionID, int msgSeqNum)
	{
		RspPackageType* rspPackage = RspPackageType::Allocate();
		rspPackage->Prepare(sessionID, false, msgSeqNum);
		rspPackage->RspInfo = spark::Allocate<RspInfoField>();
		rspPackage->RspInfo->ErrorID = ErrorReqPackageParseFailed;
		spark::core::Utility::Strcpy(rspPackage->RspInfo->ErrorMsg, GetErrorMessage(ErrorReqPackageParseFailed));
		bool isSent = front->Send(rspPackage);
		if (!isSent)
		{
			WriteLog(spark::core::LogLevel::Error, "ReplyPackageParseFailed: Send failed. SessionID:%lld", sessionID);
		}
		rspPackage->Deallocate();
		return isSent;
	}
}
