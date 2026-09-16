// 本文件由 ../Templates/Cpp/Api/ApiBase.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include "ApiBase.h"
#include <QuantTrading/MdApi.h>
#include <Spark/Network/Protocol/Protocol.h>


namespace QuantTrading
{
class MdApiBase : public ApiBase, public MdApi
{
public:
	MdApiBase();
	virtual ~MdApiBase();

	//override for ProtocolSubscriber
	virtual void OnProtocolConnect(SessionIdType sessionId, const char* ip, int port) override;
	virtual void OnProtocolDisConnect(SessionIdType sessionId, const char* ip, int port) override;

	//override for MdApi
	virtual bool Init() override;
	virtual void Join() override;
	virtual void Release() override;
	virtual void RegisterFront(const char* address) override;
	virtual void RegisterSpi(MdSpi* spi) override;


protected:
	MdSpi* mdSpi_;
	SessionIdType sessionId_;
};
}


