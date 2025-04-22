#pragma once
#include "Fields.h"
#include "Package.h"


class NotifyConnectPackage : public Package
{
public:
	static NotifyConnectPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x0001;
	NotifyConnectField* NotifyConnect = nullptr;
};
class NotifyDisConnectPackage : public Package
{
public:
	static NotifyDisConnectPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x0002;
	NotifyDisConnectField* NotifyDisConnect = nullptr;
};
class ReqMdUserLoginPackage : public Package
{
public:
	static ReqMdUserLoginPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x1001;
	ReqMdUserLoginField* ReqMdUserLogin = nullptr;
};
class RspMdUserLoginPackage : public Package
{
public:
	static RspMdUserLoginPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x1002;
	RspInfoField* RspInfo = nullptr;
	RspMdUserLoginField* RspMdUserLogin = nullptr;
};
class ReqSubMarketDataPackage : public Package
{
public:
	static ReqSubMarketDataPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x1003;
	ReqSubMarketDataField* ReqSubMarketData = nullptr;
};
class RspSubMarketDataPackage : public Package
{
public:
	static RspSubMarketDataPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x1004;
	RspInfoField* RspInfo = nullptr;
	RspSubMarketDataField* RspSubMarketData = nullptr;
};
class ReqUnSubMarketDataPackage : public Package
{
public:
	static ReqUnSubMarketDataPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x1005;
	ReqUnSubMarketDataField* ReqUnSubMarketData = nullptr;
};
class RspUnSubMarketDataPackage : public Package
{
public:
	static RspUnSubMarketDataPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x1006;
	RspInfoField* RspInfo = nullptr;
	RspUnSubMarketDataField* RspUnSubMarketData = nullptr;
};
class RtnDepthMarketDataPackage : public Package
{
public:
	static RtnDepthMarketDataPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x1007;
	DepthMarketDataField* DepthMarketData = nullptr;
};
class RtnBarMarketDataPackage : public Package
{
public:
	static RtnBarMarketDataPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x1008;
	BarMarketDataField* BarMarketData = nullptr;
};
