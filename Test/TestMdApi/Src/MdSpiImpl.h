#pragma once
#include "MdSpiMiddle.h"
#include <string>
#include <chrono>
#include <vector>
#include <map>

class MdSpiImpl : public MdSpiMiddle
{
public:
	MdSpiImpl(MdApi* mdApi);

	virtual void OnConnected() override;
	virtual void OnDisConnected() override;
	virtual void OnRspMdUserLogin(RspInfoField* rspInfo, RspMdUserLoginField* rspMdUserLogin, int requestID, bool isLast) override;

private:
	void ReqUserLogin();
	void ReqSubscribeMd();

private:
	MdApi* m_MdApi;
	int m_RequestID;
};
