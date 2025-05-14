#pragma once
#include "BackTestFields.h"
#include "Package.h"


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
	static constexpr UShortType PackageID = 0x1005;
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
	static constexpr UShortType PackageID = 0x1006;
	RspSubMarketDataField* RspSubMarketData = nullptr;
	RspInfoField* RspInfo = nullptr;
};
class ReqSubMarketDataFinishedPackage : public Package
{
public:
	static ReqSubMarketDataFinishedPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
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
	static RtnDepthMarketDataPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
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
	static RtnBarMarketDataPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
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
	static RtnSessionBeginPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
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
	static RtnSessionEndPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x100D;
	SessionEndField* SessionEnd = nullptr;
};
class ReqInsertOrderPackage : public Package
{
public:
	static ReqInsertOrderPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
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
	static RspInsertOrderPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
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
	static ReqCancelOrderPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
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
	static RspCancelOrderPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
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
	static RtnOrderPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
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
	static RtnTradePackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
	virtual int ToStepStream(char* buff, int size) const override;
	virtual bool FromStepStream(char* buff, int startIndex, int endIndex) override;
	virtual int ToXtpStream(char* buff, int size) const override;
	virtual bool FromXtpStream(char* buff, int startIndex, int endIndex) override;
	virtual const char* GetDebugString() const override;
public:
	static constexpr UShortType PackageID = 0x201E;
	TradeField* Trade = nullptr;
};
