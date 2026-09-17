// 本文件由 ../Templates/Cpp/Protocol/Packages/Packages.h.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#pragma once
#include <QuantTrading/Fields.h>
#include <Spark/Network/Protocol/Package.h>

using Spark::Network::Package;

namespace QuantTrading::Packages
{
class NotifyConnectPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x0001;
	NotifyConnectPackage();
	~NotifyConnectPackage();
	static NotifyConnectPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	NotifyConnectField* NotifyConnect = nullptr;
};
class NotifyDisConnectPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x0002;
	NotifyDisConnectPackage();
	~NotifyDisConnectPackage();
	static NotifyDisConnectPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	NotifyDisConnectField* NotifyDisConnect = nullptr;
};
class NotifyDbConnectPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x0003;
	NotifyDbConnectPackage();
	~NotifyDbConnectPackage();
	static NotifyDbConnectPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	NotifyDbConnectField* NotifyDbConnect = nullptr;
};
class NotifyDbDisConnectPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x0004;
	NotifyDbDisConnectPackage();
	~NotifyDbDisConnectPackage();
	static NotifyDbDisConnectPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	NotifyDbDisConnectField* NotifyDbDisConnect = nullptr;
};
class ReqMdUserLoginPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x1001;
	ReqMdUserLoginPackage();
	~ReqMdUserLoginPackage();
	static ReqMdUserLoginPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	ReqMdUserLoginField* ReqMdUserLogin = nullptr;
};
class RspMdUserLoginPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x1002;
	RspMdUserLoginPackage();
	~RspMdUserLoginPackage();
	static RspMdUserLoginPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	RspMdUserLoginField* RspMdUserLogin = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqMdUserLogoutPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x1003;
	ReqMdUserLogoutPackage();
	~ReqMdUserLogoutPackage();
	static ReqMdUserLogoutPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	ReqMdUserLogoutField* ReqMdUserLogout = nullptr;
};
class RspMdUserLogoutPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x1004;
	RspMdUserLogoutPackage();
	~RspMdUserLogoutPackage();
	static RspMdUserLogoutPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	RspMdUserLogoutField* RspMdUserLogout = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqSubMarketDataPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x1005;
	ReqSubMarketDataPackage();
	~ReqSubMarketDataPackage();
	static ReqSubMarketDataPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	ReqSubMarketDataField* ReqSubMarketData = nullptr;
};
class RspSubMarketDataPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x1006;
	RspSubMarketDataPackage();
	~RspSubMarketDataPackage();
	static RspSubMarketDataPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	RspSubMarketDataField* RspSubMarketData = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqUnSubMarketDataPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x1007;
	ReqUnSubMarketDataPackage();
	~ReqUnSubMarketDataPackage();
	static ReqUnSubMarketDataPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	ReqUnSubMarketDataField* ReqUnSubMarketData = nullptr;
};
class RspUnSubMarketDataPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x1008;
	RspUnSubMarketDataPackage();
	~RspUnSubMarketDataPackage();
	static RspUnSubMarketDataPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	RspUnSubMarketDataField* RspUnSubMarketData = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqSubMarketDataFinishedPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x1009;
	ReqSubMarketDataFinishedPackage();
	~ReqSubMarketDataFinishedPackage();
	static ReqSubMarketDataFinishedPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	ReqSubMarketDataFinishedField* ReqSubMarketDataFinished = nullptr;
};
class RtnDepthMarketDataPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x100A;
	RtnDepthMarketDataPackage();
	~RtnDepthMarketDataPackage();
	static RtnDepthMarketDataPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	DepthMarketDataField* DepthMarketData = nullptr;
};
class RtnBarMarketDataPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x100B;
	RtnBarMarketDataPackage();
	~RtnBarMarketDataPackage();
	static RtnBarMarketDataPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	BarMarketDataField* BarMarketData = nullptr;
};
class RtnSessionBeginPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x100C;
	RtnSessionBeginPackage();
	~RtnSessionBeginPackage();
	static RtnSessionBeginPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	SessionBeginField* SessionBegin = nullptr;
};
class RtnSessionEndPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x100D;
	RtnSessionEndPackage();
	~RtnSessionEndPackage();
	static RtnSessionEndPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	SessionEndField* SessionEnd = nullptr;
};
class RtnMarketDataEndPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x100E;
	RtnMarketDataEndPackage();
	~RtnMarketDataEndPackage();
	static RtnMarketDataEndPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	MarketDataEndField* MarketDataEnd = nullptr;
};
class ReqRegisterAccountPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x2001;
	ReqRegisterAccountPackage();
	~ReqRegisterAccountPackage();
	static ReqRegisterAccountPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	ReqRegisterAccountField* ReqRegisterAccount = nullptr;
};
class RspRegisterAccountPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x2002;
	RspRegisterAccountPackage();
	~RspRegisterAccountPackage();
	static RspRegisterAccountPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	RspRegisterAccountField* RspRegisterAccount = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqAccountLoginPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x2003;
	ReqAccountLoginPackage();
	~ReqAccountLoginPackage();
	static ReqAccountLoginPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	ReqAccountLoginField* ReqAccountLogin = nullptr;
};
class RspAccountLoginPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x2004;
	RspAccountLoginPackage();
	~RspAccountLoginPackage();
	static RspAccountLoginPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	RspAccountLoginField* RspAccountLogin = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqAccountLogoutPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x2005;
	ReqAccountLogoutPackage();
	~ReqAccountLogoutPackage();
	static ReqAccountLogoutPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	ReqAccountLogoutField* ReqAccountLogout = nullptr;
};
class RspAccountLogoutPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x2006;
	RspAccountLogoutPackage();
	~RspAccountLogoutPackage();
	static RspAccountLogoutPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	RspAccountLogoutField* RspAccountLogout = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqQryAccountPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x2007;
	ReqQryAccountPackage();
	~ReqQryAccountPackage();
	static ReqQryAccountPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	ReqQryAccountField* ReqQryAccount = nullptr;
};
class RspQryAccountPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x2008;
	RspQryAccountPackage();
	~RspQryAccountPackage();
	static RspQryAccountPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	AccountField* Account = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqQryHolderAccountPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x2009;
	ReqQryHolderAccountPackage();
	~ReqQryHolderAccountPackage();
	static ReqQryHolderAccountPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	ReqQryHolderAccountField* ReqQryHolderAccount = nullptr;
};
class RspQryHolderAccountPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x200A;
	RspQryHolderAccountPackage();
	~RspQryHolderAccountPackage();
	static RspQryHolderAccountPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	HolderAccountField* HolderAccount = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqQryCapitalPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x200B;
	ReqQryCapitalPackage();
	~ReqQryCapitalPackage();
	static ReqQryCapitalPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	ReqQryCapitalField* ReqQryCapital = nullptr;
};
class RspQryCapitalPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x200C;
	RspQryCapitalPackage();
	~RspQryCapitalPackage();
	static RspQryCapitalPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	CapitalField* Capital = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqQryPositionPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x200D;
	ReqQryPositionPackage();
	~ReqQryPositionPackage();
	static ReqQryPositionPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	ReqQryPositionField* ReqQryPosition = nullptr;
};
class RspQryPositionPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x200E;
	RspQryPositionPackage();
	~RspQryPositionPackage();
	static RspQryPositionPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	PositionField* Position = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqQryOrderPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x200F;
	ReqQryOrderPackage();
	~ReqQryOrderPackage();
	static ReqQryOrderPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	ReqQryOrderField* ReqQryOrder = nullptr;
};
class RspQryOrderPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x2010;
	RspQryOrderPackage();
	~RspQryOrderPackage();
	static RspQryOrderPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	OrderField* Order = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqQryTradePackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x2011;
	ReqQryTradePackage();
	~ReqQryTradePackage();
	static ReqQryTradePackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	ReqQryTradeField* ReqQryTrade = nullptr;
};
class RspQryTradePackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x2012;
	RspQryTradePackage();
	~RspQryTradePackage();
	static RspQryTradePackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	TradeField* Trade = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqQryInstrumentPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x2013;
	ReqQryInstrumentPackage();
	~ReqQryInstrumentPackage();
	static ReqQryInstrumentPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	ReqQryInstrumentField* ReqQryInstrument = nullptr;
};
class RspQryInstrumentPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x2014;
	RspQryInstrumentPackage();
	~RspQryInstrumentPackage();
	static RspQryInstrumentPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	InstrumentField* Instrument = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqQryOptionInstrumentPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x2015;
	ReqQryOptionInstrumentPackage();
	~ReqQryOptionInstrumentPackage();
	static ReqQryOptionInstrumentPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	ReqQryOptionInstrumentField* ReqQryOptionInstrument = nullptr;
};
class RspQryOptionInstrumentPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x2016;
	RspQryOptionInstrumentPackage();
	~RspQryOptionInstrumentPackage();
	static RspQryOptionInstrumentPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	OptionInstrumentField* OptionInstrument = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqQryCommissionRatePackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x2017;
	ReqQryCommissionRatePackage();
	~ReqQryCommissionRatePackage();
	static ReqQryCommissionRatePackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	ReqQryCommissionRateField* ReqQryCommissionRate = nullptr;
};
class RspQryCommissionRatePackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x2018;
	RspQryCommissionRatePackage();
	~RspQryCommissionRatePackage();
	static RspQryCommissionRatePackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	CommissionRateField* CommissionRate = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqQryMoneyTransferPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x2019;
	ReqQryMoneyTransferPackage();
	~ReqQryMoneyTransferPackage();
	static ReqQryMoneyTransferPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	ReqQryMoneyTransferField* ReqQryMoneyTransfer = nullptr;
};
class RspQryMoneyTransferPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x201A;
	RspQryMoneyTransferPackage();
	~RspQryMoneyTransferPackage();
	static RspQryMoneyTransferPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	MoneyTransferField* MoneyTransfer = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqInsertOrderPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x201B;
	ReqInsertOrderPackage();
	~ReqInsertOrderPackage();
	static ReqInsertOrderPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	ReqInsertOrderField* ReqInsertOrder = nullptr;
};
class RspInsertOrderPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x201C;
	RspInsertOrderPackage();
	~RspInsertOrderPackage();
	static RspInsertOrderPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	ReqInsertOrderField* ReqInsertOrder = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqCancelOrderPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x201D;
	ReqCancelOrderPackage();
	~ReqCancelOrderPackage();
	static ReqCancelOrderPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	ReqCancelOrderField* ReqCancelOrder = nullptr;
};
class RspCancelOrderPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x201E;
	RspCancelOrderPackage();
	~RspCancelOrderPackage();
	static RspCancelOrderPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	ReqCancelOrderField* ReqCancelOrder = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class RtnOrderPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x201F;
	RtnOrderPackage();
	~RtnOrderPackage();
	static RtnOrderPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	OrderField* Order = nullptr;
};
class RtnTradePackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x2020;
	RtnTradePackage();
	~RtnTradePackage();
	static RtnTradePackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	TradeField* Trade = nullptr;
};
class RtnMoneyTransferPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x2021;
	RtnMoneyTransferPackage();
	~RtnMoneyTransferPackage();
	static RtnMoneyTransferPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	MoneyTransferField* MoneyTransfer = nullptr;
};
class RtnAccountLogoutPackage : public Package
{
public:
	static constexpr UInt16Type PackageId = 0x2022;
	RtnAccountLogoutPackage();
	~RtnAccountLogoutPackage();
	static RtnAccountLogoutPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;

	AccountLogoutField* AccountLogout = nullptr;
};
}
