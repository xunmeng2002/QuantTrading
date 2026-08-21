#pragma once
#include "QuantTrading/Fields.h"
#include <Spark/Network/Protocol/Package.h>

using spark::network::Package;

class NotifyConnectPackage : public Package
{
public:
	NotifyConnectPackage();
	~NotifyConnectPackage();
	static NotifyConnectPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
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
	NotifyDisConnectPackage();
	~NotifyDisConnectPackage();
	static NotifyDisConnectPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x0002;
	NotifyDisConnectField* NotifyDisConnect = nullptr;
};
class NotifyDBConnectPackage : public Package
{
public:
	NotifyDBConnectPackage();
	~NotifyDBConnectPackage();
	static NotifyDBConnectPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x0003;
	NotifyDBConnectField* NotifyDBConnect = nullptr;
};
class NotifyDBDisConnectPackage : public Package
{
public:
	NotifyDBDisConnectPackage();
	~NotifyDBDisConnectPackage();
	static NotifyDBDisConnectPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x0004;
	NotifyDBDisConnectField* NotifyDBDisConnect = nullptr;
};
class ReqMdUserLoginPackage : public Package
{
public:
	ReqMdUserLoginPackage();
	~ReqMdUserLoginPackage();
	static ReqMdUserLoginPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
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
	RspMdUserLoginPackage();
	~RspMdUserLoginPackage();
	static RspMdUserLoginPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x1002;
	RspMdUserLoginField* RspMdUserLogin = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqMdUserLogoutPackage : public Package
{
public:
	ReqMdUserLogoutPackage();
	~ReqMdUserLogoutPackage();
	static ReqMdUserLogoutPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x1003;
	ReqMdUserLogoutField* ReqMdUserLogout = nullptr;
};
class RspMdUserLogoutPackage : public Package
{
public:
	RspMdUserLogoutPackage();
	~RspMdUserLogoutPackage();
	static RspMdUserLogoutPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x1004;
	RspMdUserLogoutField* RspMdUserLogout = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqSubMarketDataPackage : public Package
{
public:
	ReqSubMarketDataPackage();
	~ReqSubMarketDataPackage();
	static ReqSubMarketDataPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x1005;
	ReqSubMarketDataField* ReqSubMarketData = nullptr;
};
class RspSubMarketDataPackage : public Package
{
public:
	RspSubMarketDataPackage();
	~RspSubMarketDataPackage();
	static RspSubMarketDataPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x1006;
	RspSubMarketDataField* RspSubMarketData = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqUnSubMarketDataPackage : public Package
{
public:
	ReqUnSubMarketDataPackage();
	~ReqUnSubMarketDataPackage();
	static ReqUnSubMarketDataPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x1007;
	ReqUnSubMarketDataField* ReqUnSubMarketData = nullptr;
};
class RspUnSubMarketDataPackage : public Package
{
public:
	RspUnSubMarketDataPackage();
	~RspUnSubMarketDataPackage();
	static RspUnSubMarketDataPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x1008;
	RspUnSubMarketDataField* RspUnSubMarketData = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqSubMarketDataFinishedPackage : public Package
{
public:
	ReqSubMarketDataFinishedPackage();
	~ReqSubMarketDataFinishedPackage();
	static ReqSubMarketDataFinishedPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x1009;
	ReqSubMarketDataFinishedField* ReqSubMarketDataFinished = nullptr;
};
class RtnDepthMarketDataPackage : public Package
{
public:
	RtnDepthMarketDataPackage();
	~RtnDepthMarketDataPackage();
	static RtnDepthMarketDataPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x100A;
	DepthMarketDataField* DepthMarketData = nullptr;
};
class RtnBarMarketDataPackage : public Package
{
public:
	RtnBarMarketDataPackage();
	~RtnBarMarketDataPackage();
	static RtnBarMarketDataPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x100B;
	BarMarketDataField* BarMarketData = nullptr;
};
class RtnSessionBeginPackage : public Package
{
public:
	RtnSessionBeginPackage();
	~RtnSessionBeginPackage();
	static RtnSessionBeginPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x100C;
	SessionBeginField* SessionBegin = nullptr;
};
class RtnSessionEndPackage : public Package
{
public:
	RtnSessionEndPackage();
	~RtnSessionEndPackage();
	static RtnSessionEndPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x100D;
	SessionEndField* SessionEnd = nullptr;
};
class RtnMarketDataEndPackage : public Package
{
public:
	RtnMarketDataEndPackage();
	~RtnMarketDataEndPackage();
	static RtnMarketDataEndPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x100E;
	MarketDataEndField* MarketDataEnd = nullptr;
};
class ReqAccountLoginPackage : public Package
{
public:
	ReqAccountLoginPackage();
	~ReqAccountLoginPackage();
	static ReqAccountLoginPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x2001;
	ReqAccountLoginField* ReqAccountLogin = nullptr;
};
class RspAccountLoginPackage : public Package
{
public:
	RspAccountLoginPackage();
	~RspAccountLoginPackage();
	static RspAccountLoginPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x2002;
	RspAccountLoginField* RspAccountLogin = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqAccountLogoutPackage : public Package
{
public:
	ReqAccountLogoutPackage();
	~ReqAccountLogoutPackage();
	static ReqAccountLogoutPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x2003;
	ReqAccountLogoutField* ReqAccountLogout = nullptr;
};
class RspAccountLogoutPackage : public Package
{
public:
	RspAccountLogoutPackage();
	~RspAccountLogoutPackage();
	static RspAccountLogoutPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x2004;
	RspAccountLogoutField* RspAccountLogout = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqQryAccountPackage : public Package
{
public:
	ReqQryAccountPackage();
	~ReqQryAccountPackage();
	static ReqQryAccountPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x2005;
	ReqQryAccountField* ReqQryAccount = nullptr;
};
class RspQryAccountPackage : public Package
{
public:
	RspQryAccountPackage();
	~RspQryAccountPackage();
	static RspQryAccountPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x2006;
	AccountField* Account = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqQryHolderAccountPackage : public Package
{
public:
	ReqQryHolderAccountPackage();
	~ReqQryHolderAccountPackage();
	static ReqQryHolderAccountPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x2007;
	ReqQryHolderAccountField* ReqQryHolderAccount = nullptr;
};
class RspQryHolderAccountPackage : public Package
{
public:
	RspQryHolderAccountPackage();
	~RspQryHolderAccountPackage();
	static RspQryHolderAccountPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x2008;
	HolderAccountField* HolderAccount = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqQryCapitalPackage : public Package
{
public:
	ReqQryCapitalPackage();
	~ReqQryCapitalPackage();
	static ReqQryCapitalPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x2009;
	ReqQryCapitalField* ReqQryCapital = nullptr;
};
class RspQryCapitalPackage : public Package
{
public:
	RspQryCapitalPackage();
	~RspQryCapitalPackage();
	static RspQryCapitalPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x200A;
	CapitalField* Capital = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqQryPositionPackage : public Package
{
public:
	ReqQryPositionPackage();
	~ReqQryPositionPackage();
	static ReqQryPositionPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x200B;
	ReqQryPositionField* ReqQryPosition = nullptr;
};
class RspQryPositionPackage : public Package
{
public:
	RspQryPositionPackage();
	~RspQryPositionPackage();
	static RspQryPositionPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x200C;
	PositionField* Position = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqQryOrderPackage : public Package
{
public:
	ReqQryOrderPackage();
	~ReqQryOrderPackage();
	static ReqQryOrderPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x200D;
	ReqQryOrderField* ReqQryOrder = nullptr;
};
class RspQryOrderPackage : public Package
{
public:
	RspQryOrderPackage();
	~RspQryOrderPackage();
	static RspQryOrderPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x200E;
	OrderField* Order = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqQryTradePackage : public Package
{
public:
	ReqQryTradePackage();
	~ReqQryTradePackage();
	static ReqQryTradePackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x200F;
	ReqQryTradeField* ReqQryTrade = nullptr;
};
class RspQryTradePackage : public Package
{
public:
	RspQryTradePackage();
	~RspQryTradePackage();
	static RspQryTradePackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x2010;
	TradeField* Trade = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqQryInstrumentPackage : public Package
{
public:
	ReqQryInstrumentPackage();
	~ReqQryInstrumentPackage();
	static ReqQryInstrumentPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x2011;
	ReqQryInstrumentField* ReqQryInstrument = nullptr;
};
class RspQryInstrumentPackage : public Package
{
public:
	RspQryInstrumentPackage();
	~RspQryInstrumentPackage();
	static RspQryInstrumentPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x2012;
	InstrumentField* Instrument = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqQryOptionInstrumentPackage : public Package
{
public:
	ReqQryOptionInstrumentPackage();
	~ReqQryOptionInstrumentPackage();
	static ReqQryOptionInstrumentPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x2013;
	ReqQryOptionInstrumentField* ReqQryOptionInstrument = nullptr;
};
class RspQryOptionInstrumentPackage : public Package
{
public:
	RspQryOptionInstrumentPackage();
	~RspQryOptionInstrumentPackage();
	static RspQryOptionInstrumentPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x2014;
	OptionInstrumentField* OptionInstrument = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqQryCommissionRatePackage : public Package
{
public:
	ReqQryCommissionRatePackage();
	~ReqQryCommissionRatePackage();
	static ReqQryCommissionRatePackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x2015;
	ReqQryCommissionRateField* ReqQryCommissionRate = nullptr;
};
class RspQryCommissionRatePackage : public Package
{
public:
	RspQryCommissionRatePackage();
	~RspQryCommissionRatePackage();
	static RspQryCommissionRatePackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x2016;
	CommissionRateField* CommissionRate = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqQryMoneyTransferPackage : public Package
{
public:
	ReqQryMoneyTransferPackage();
	~ReqQryMoneyTransferPackage();
	static ReqQryMoneyTransferPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x2017;
	ReqQryMoneyTransferField* ReqQryMoneyTransfer = nullptr;
};
class RspQryMoneyTransferPackage : public Package
{
public:
	RspQryMoneyTransferPackage();
	~RspQryMoneyTransferPackage();
	static RspQryMoneyTransferPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x2018;
	MoneyTransferField* MoneyTransfer = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqInsertOrderPackage : public Package
{
public:
	ReqInsertOrderPackage();
	~ReqInsertOrderPackage();
	static ReqInsertOrderPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x2019;
	ReqInsertOrderField* ReqInsertOrder = nullptr;
};
class RspInsertOrderPackage : public Package
{
public:
	RspInsertOrderPackage();
	~RspInsertOrderPackage();
	static RspInsertOrderPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x201A;
	ReqInsertOrderField* ReqInsertOrder = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqCancelOrderPackage : public Package
{
public:
	ReqCancelOrderPackage();
	~ReqCancelOrderPackage();
	static ReqCancelOrderPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x201B;
	ReqCancelOrderField* ReqCancelOrder = nullptr;
};
class RspCancelOrderPackage : public Package
{
public:
	RspCancelOrderPackage();
	~RspCancelOrderPackage();
	static RspCancelOrderPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x201C;
	ReqCancelOrderField* ReqCancelOrder = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class RtnOrderPackage : public Package
{
public:
	RtnOrderPackage();
	~RtnOrderPackage();
	static RtnOrderPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x201D;
	OrderField* Order = nullptr;
};
class RtnTradePackage : public Package
{
public:
	RtnTradePackage();
	~RtnTradePackage();
	static RtnTradePackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x201E;
	TradeField* Trade = nullptr;
};
class RtnMoneyTransferPackage : public Package
{
public:
	RtnMoneyTransferPackage();
	~RtnMoneyTransferPackage();
	static RtnMoneyTransferPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x201F;
	MoneyTransferField* MoneyTransfer = nullptr;
};
class RtnAccountLogoutPackage : public Package
{
public:
	RtnAccountLogoutPackage();
	~RtnAccountLogoutPackage();
	static RtnAccountLogoutPackage* Allocate();
	virtual void Deallocate() override;
	virtual void Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x2020;
	AccountLogoutField* AccountLogout = nullptr;
};
