#pragma once
#include "SimExchangeFields.h"
#include "Package.h"


class ReqAccountLoginPackage : public Package
{
public:
	static ReqAccountLoginPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
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
	static RspAccountLoginPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
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
	static ReqAccountLogoutPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
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
	static RspAccountLogoutPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
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
class ReqQryOrderPackage : public Package
{
public:
	static ReqQryOrderPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
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
	static RspQryOrderPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
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
	static ReqQryTradePackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
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
	static RspQryTradePackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
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
	static ReqQryInstrumentPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
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
	static RspQryInstrumentPackage* Allocate();
	virtual void Free() override;
	virtual void Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum) override;
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
