#include "Packages.h"
#include "Items.h"
#include "StepUtility.h"
#include "Logger.h"
#include "MemCacheTemplateSingleton.h"
#include <cstring>

thread_local char t_DataStringBuffer[10240];



 
ReqMdUserLoginPackage* ReqMdUserLoginPackage::Allocate()
{
	return ::Allocate<ReqMdUserLoginPackage>();
}
void ReqMdUserLoginPackage::Free()
{
	Package::Free();
	if (ReqMdUserLogin != nullptr)
	{
		::Free<ReqMdUserLoginField>(ReqMdUserLogin);
		ReqMdUserLogin = nullptr;
	}
	MemCacheTemplateSingleton<ReqMdUserLoginPackage>::GetInstance().Free(this);
}
void ReqMdUserLoginPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqMdUserLoginPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqMdUserLogin != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqMdUserLoginField::FieldID);
		if (strlen(ReqMdUserLogin->UserID) >= sizeof(ReqMdUserLogin->UserID))
		{
			ReqMdUserLogin->UserID[sizeof(ReqMdUserLogin->UserID) - 1] = 0;
		}
		WriteString(ppos, Items::UserID, ReqMdUserLogin->UserID);
		if (strlen(ReqMdUserLogin->Password) >= sizeof(ReqMdUserLogin->Password))
		{
			ReqMdUserLogin->Password[sizeof(ReqMdUserLogin->Password) - 1] = 0;
		}
		WriteString(ppos, Items::Password, ReqMdUserLogin->Password);
		WriteHexString(ppos, Items::FieldEnd, ReqMdUserLoginField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqMdUserLoginPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldID;
		int fieldStartIndex;
		int fieldEndIndex;
		if (GetNextFieldZone(buff, startIndex, endIndex, fieldID, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldID)
			{
			case ReqMdUserLoginField::FieldID:
			{
				ReqMdUserLogin = ::Allocate<ReqMdUserLoginField>();
				memset(ReqMdUserLogin, 0, sizeof(*ReqMdUserLogin));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemID;
					std::string value;
					int sohIndex;
					if (GetNext(buff, itemStartIndex, fieldEndIndex, itemID, value, sohIndex))
					{
						switch (itemID)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::UserID:
						{
							size_t len = value.length() >= sizeof(ReqMdUserLogin->UserID) ? sizeof(ReqMdUserLogin->UserID) - 1 : value.length();
							memcpy(ReqMdUserLogin->UserID, value.c_str(), len);
							break;
						}
						case Items::Password:
						{
							size_t len = value.length() >= sizeof(ReqMdUserLogin->Password) ? sizeof(ReqMdUserLogin->Password) - 1 : value.length();
							memcpy(ReqMdUserLogin->Password, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqMdUserLoginField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqMdUserLoginPackage FieldID:0x%X", fieldID);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldID:0x%X, Please Check Api Version.", fieldID);
				return false;
			}
			startIndex = fieldEndIndex;
		}
		else
		{
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqMdUserLoginPackage");
			return false;
		}
	}
	return true;
}
int ReqMdUserLoginPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	memcpy(buff + offset, ReqMdUserLogin, sizeof(ReqMdUserLoginField));
	offset += sizeof(ReqMdUserLoginField);
	return offset;
}
bool ReqMdUserLoginPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	ReqMdUserLogin = ::Allocate<ReqMdUserLoginField>();
	memcpy(ReqMdUserLogin, buff + offset, sizeof(ReqMdUserLoginField));
	offset += sizeof(ReqMdUserLoginField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* ReqMdUserLoginPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "ReqMdUserLogin:UserID:[%s], Password:[%s]",
		ReqMdUserLogin->UserID, ReqMdUserLogin->Password);
	return t_DataStringBuffer;
}
 
RspMdUserLoginPackage* RspMdUserLoginPackage::Allocate()
{
	return ::Allocate<RspMdUserLoginPackage>();
}
void RspMdUserLoginPackage::Free()
{
	Package::Free();
	if (RspMdUserLogin != nullptr)
	{
		::Free<RspMdUserLoginField>(RspMdUserLogin);
		RspMdUserLogin = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspMdUserLoginPackage>::GetInstance().Free(this);
}
void RspMdUserLoginPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspMdUserLoginPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (RspMdUserLogin != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, RspMdUserLoginField::FieldID);
		if (strlen(RspMdUserLogin->UserID) >= sizeof(RspMdUserLogin->UserID))
		{
			RspMdUserLogin->UserID[sizeof(RspMdUserLogin->UserID) - 1] = 0;
		}
		WriteString(ppos, Items::UserID, RspMdUserLogin->UserID);
		if (strlen(RspMdUserLogin->LoginDate) >= sizeof(RspMdUserLogin->LoginDate))
		{
			RspMdUserLogin->LoginDate[sizeof(RspMdUserLogin->LoginDate) - 1] = 0;
		}
		WriteString(ppos, Items::LoginDate, RspMdUserLogin->LoginDate);
		if (strlen(RspMdUserLogin->LoginTime) >= sizeof(RspMdUserLogin->LoginTime))
		{
			RspMdUserLogin->LoginTime[sizeof(RspMdUserLogin->LoginTime) - 1] = 0;
		}
		WriteString(ppos, Items::LoginTime, RspMdUserLogin->LoginTime);
		WriteString(ppos, Items::SessionID, RspMdUserLogin->SessionID);
		WriteHexString(ppos, Items::FieldEnd, RspMdUserLoginField::FieldID);
	}
	if (RspInfo != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, RspInfoField::FieldID);
		WriteString(ppos, Items::ErrorID, RspInfo->ErrorID);
		if (strlen(RspInfo->ErrorMsg) >= sizeof(RspInfo->ErrorMsg))
		{
			RspInfo->ErrorMsg[sizeof(RspInfo->ErrorMsg) - 1] = 0;
		}
		WriteString(ppos, Items::ErrorMsg, RspInfo->ErrorMsg);
		WriteHexString(ppos, Items::FieldEnd, RspInfoField::FieldID);
	}
	return int(ppos - buff);
}
bool RspMdUserLoginPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldID;
		int fieldStartIndex;
		int fieldEndIndex;
		if (GetNextFieldZone(buff, startIndex, endIndex, fieldID, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldID)
			{
			case RspMdUserLoginField::FieldID:
			{
				RspMdUserLogin = ::Allocate<RspMdUserLoginField>();
				memset(RspMdUserLogin, 0, sizeof(*RspMdUserLogin));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemID;
					std::string value;
					int sohIndex;
					if (GetNext(buff, itemStartIndex, fieldEndIndex, itemID, value, sohIndex))
					{
						switch (itemID)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::UserID:
						{
							size_t len = value.length() >= sizeof(RspMdUserLogin->UserID) ? sizeof(RspMdUserLogin->UserID) - 1 : value.length();
							memcpy(RspMdUserLogin->UserID, value.c_str(), len);
							break;
						}
						case Items::LoginDate:
						{
							size_t len = value.length() >= sizeof(RspMdUserLogin->LoginDate) ? sizeof(RspMdUserLogin->LoginDate) - 1 : value.length();
							memcpy(RspMdUserLogin->LoginDate, value.c_str(), len);
							break;
						}
						case Items::LoginTime:
						{
							size_t len = value.length() >= sizeof(RspMdUserLogin->LoginTime) ? sizeof(RspMdUserLogin->LoginTime) - 1 : value.length();
							memcpy(RspMdUserLogin->LoginTime, value.c_str(), len);
							break;
						}
						case Items::SessionID:
						{
							RspMdUserLogin->SessionID = atoll(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for RspMdUserLoginField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspMdUserLoginPackage FieldID:0x%X", fieldID);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldID:
			{
				RspInfo = ::Allocate<RspInfoField>();
				memset(RspInfo, 0, sizeof(*RspInfo));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemID;
					std::string value;
					int sohIndex;
					if (GetNext(buff, itemStartIndex, fieldEndIndex, itemID, value, sohIndex))
					{
						switch (itemID)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ErrorID:
						{
							RspInfo->ErrorID = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(RspInfo->ErrorMsg) ? sizeof(RspInfo->ErrorMsg) - 1 : value.length();
							memcpy(RspInfo->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for RspInfoField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspMdUserLoginPackage FieldID:0x%X", fieldID);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldID:0x%X, Please Check Api Version.", fieldID);
				return false;
			}
			startIndex = fieldEndIndex;
		}
		else
		{
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspMdUserLoginPackage");
			return false;
		}
	}
	return true;
}
int RspMdUserLoginPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	memcpy(buff + offset, RspMdUserLogin, sizeof(RspMdUserLoginField));
	offset += sizeof(RspMdUserLoginField);
	memcpy(buff + offset, RspInfo, sizeof(RspInfoField));
	offset += sizeof(RspInfoField);
	return offset;
}
bool RspMdUserLoginPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	RspMdUserLogin = ::Allocate<RspMdUserLoginField>();
	memcpy(RspMdUserLogin, buff + offset, sizeof(RspMdUserLoginField));
	offset += sizeof(RspMdUserLoginField);
	RspInfo = ::Allocate<RspInfoField>();
	memcpy(RspInfo, buff + offset, sizeof(RspInfoField));
	offset += sizeof(RspInfoField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* RspMdUserLoginPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "RspMdUserLogin:UserID:[%s], LoginDate:[%s], LoginTime:[%s], SessionID:[%lld]",
		RspMdUserLogin->UserID, RspMdUserLogin->LoginDate, RspMdUserLogin->LoginTime, RspMdUserLogin->SessionID);
	offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]",
		RspInfo->ErrorID, RspInfo->ErrorMsg);
	return t_DataStringBuffer;
}
 
ReqMdUserLogoutPackage* ReqMdUserLogoutPackage::Allocate()
{
	return ::Allocate<ReqMdUserLogoutPackage>();
}
void ReqMdUserLogoutPackage::Free()
{
	Package::Free();
	if (ReqMdUserLogout != nullptr)
	{
		::Free<ReqMdUserLogoutField>(ReqMdUserLogout);
		ReqMdUserLogout = nullptr;
	}
	MemCacheTemplateSingleton<ReqMdUserLogoutPackage>::GetInstance().Free(this);
}
void ReqMdUserLogoutPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqMdUserLogoutPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqMdUserLogout != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqMdUserLogoutField::FieldID);
		if (strlen(ReqMdUserLogout->UserID) >= sizeof(ReqMdUserLogout->UserID))
		{
			ReqMdUserLogout->UserID[sizeof(ReqMdUserLogout->UserID) - 1] = 0;
		}
		WriteString(ppos, Items::UserID, ReqMdUserLogout->UserID);
		WriteHexString(ppos, Items::FieldEnd, ReqMdUserLogoutField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqMdUserLogoutPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldID;
		int fieldStartIndex;
		int fieldEndIndex;
		if (GetNextFieldZone(buff, startIndex, endIndex, fieldID, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldID)
			{
			case ReqMdUserLogoutField::FieldID:
			{
				ReqMdUserLogout = ::Allocate<ReqMdUserLogoutField>();
				memset(ReqMdUserLogout, 0, sizeof(*ReqMdUserLogout));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemID;
					std::string value;
					int sohIndex;
					if (GetNext(buff, itemStartIndex, fieldEndIndex, itemID, value, sohIndex))
					{
						switch (itemID)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::UserID:
						{
							size_t len = value.length() >= sizeof(ReqMdUserLogout->UserID) ? sizeof(ReqMdUserLogout->UserID) - 1 : value.length();
							memcpy(ReqMdUserLogout->UserID, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqMdUserLogoutField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqMdUserLogoutPackage FieldID:0x%X", fieldID);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldID:0x%X, Please Check Api Version.", fieldID);
				return false;
			}
			startIndex = fieldEndIndex;
		}
		else
		{
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqMdUserLogoutPackage");
			return false;
		}
	}
	return true;
}
int ReqMdUserLogoutPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	memcpy(buff + offset, ReqMdUserLogout, sizeof(ReqMdUserLogoutField));
	offset += sizeof(ReqMdUserLogoutField);
	return offset;
}
bool ReqMdUserLogoutPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	ReqMdUserLogout = ::Allocate<ReqMdUserLogoutField>();
	memcpy(ReqMdUserLogout, buff + offset, sizeof(ReqMdUserLogoutField));
	offset += sizeof(ReqMdUserLogoutField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* ReqMdUserLogoutPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "ReqMdUserLogout:UserID:[%s]",
		ReqMdUserLogout->UserID);
	return t_DataStringBuffer;
}
 
RspMdUserLogoutPackage* RspMdUserLogoutPackage::Allocate()
{
	return ::Allocate<RspMdUserLogoutPackage>();
}
void RspMdUserLogoutPackage::Free()
{
	Package::Free();
	if (RspMdUserLogout != nullptr)
	{
		::Free<RspMdUserLogoutField>(RspMdUserLogout);
		RspMdUserLogout = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspMdUserLogoutPackage>::GetInstance().Free(this);
}
void RspMdUserLogoutPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspMdUserLogoutPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (RspMdUserLogout != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, RspMdUserLogoutField::FieldID);
		if (strlen(RspMdUserLogout->UserID) >= sizeof(RspMdUserLogout->UserID))
		{
			RspMdUserLogout->UserID[sizeof(RspMdUserLogout->UserID) - 1] = 0;
		}
		WriteString(ppos, Items::UserID, RspMdUserLogout->UserID);
		WriteHexString(ppos, Items::FieldEnd, RspMdUserLogoutField::FieldID);
	}
	if (RspInfo != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, RspInfoField::FieldID);
		WriteString(ppos, Items::ErrorID, RspInfo->ErrorID);
		if (strlen(RspInfo->ErrorMsg) >= sizeof(RspInfo->ErrorMsg))
		{
			RspInfo->ErrorMsg[sizeof(RspInfo->ErrorMsg) - 1] = 0;
		}
		WriteString(ppos, Items::ErrorMsg, RspInfo->ErrorMsg);
		WriteHexString(ppos, Items::FieldEnd, RspInfoField::FieldID);
	}
	return int(ppos - buff);
}
bool RspMdUserLogoutPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldID;
		int fieldStartIndex;
		int fieldEndIndex;
		if (GetNextFieldZone(buff, startIndex, endIndex, fieldID, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldID)
			{
			case RspMdUserLogoutField::FieldID:
			{
				RspMdUserLogout = ::Allocate<RspMdUserLogoutField>();
				memset(RspMdUserLogout, 0, sizeof(*RspMdUserLogout));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemID;
					std::string value;
					int sohIndex;
					if (GetNext(buff, itemStartIndex, fieldEndIndex, itemID, value, sohIndex))
					{
						switch (itemID)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::UserID:
						{
							size_t len = value.length() >= sizeof(RspMdUserLogout->UserID) ? sizeof(RspMdUserLogout->UserID) - 1 : value.length();
							memcpy(RspMdUserLogout->UserID, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for RspMdUserLogoutField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspMdUserLogoutPackage FieldID:0x%X", fieldID);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldID:
			{
				RspInfo = ::Allocate<RspInfoField>();
				memset(RspInfo, 0, sizeof(*RspInfo));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemID;
					std::string value;
					int sohIndex;
					if (GetNext(buff, itemStartIndex, fieldEndIndex, itemID, value, sohIndex))
					{
						switch (itemID)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ErrorID:
						{
							RspInfo->ErrorID = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(RspInfo->ErrorMsg) ? sizeof(RspInfo->ErrorMsg) - 1 : value.length();
							memcpy(RspInfo->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for RspInfoField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspMdUserLogoutPackage FieldID:0x%X", fieldID);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldID:0x%X, Please Check Api Version.", fieldID);
				return false;
			}
			startIndex = fieldEndIndex;
		}
		else
		{
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspMdUserLogoutPackage");
			return false;
		}
	}
	return true;
}
int RspMdUserLogoutPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	memcpy(buff + offset, RspMdUserLogout, sizeof(RspMdUserLogoutField));
	offset += sizeof(RspMdUserLogoutField);
	memcpy(buff + offset, RspInfo, sizeof(RspInfoField));
	offset += sizeof(RspInfoField);
	return offset;
}
bool RspMdUserLogoutPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	RspMdUserLogout = ::Allocate<RspMdUserLogoutField>();
	memcpy(RspMdUserLogout, buff + offset, sizeof(RspMdUserLogoutField));
	offset += sizeof(RspMdUserLogoutField);
	RspInfo = ::Allocate<RspInfoField>();
	memcpy(RspInfo, buff + offset, sizeof(RspInfoField));
	offset += sizeof(RspInfoField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* RspMdUserLogoutPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "RspMdUserLogout:UserID:[%s]",
		RspMdUserLogout->UserID);
	offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]",
		RspInfo->ErrorID, RspInfo->ErrorMsg);
	return t_DataStringBuffer;
}
 
ReqSubMarketDataPackage* ReqSubMarketDataPackage::Allocate()
{
	return ::Allocate<ReqSubMarketDataPackage>();
}
void ReqSubMarketDataPackage::Free()
{
	Package::Free();
	if (ReqSubMarketData != nullptr)
	{
		::Free<ReqSubMarketDataField>(ReqSubMarketData);
		ReqSubMarketData = nullptr;
	}
	MemCacheTemplateSingleton<ReqSubMarketDataPackage>::GetInstance().Free(this);
}
void ReqSubMarketDataPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqSubMarketDataPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqSubMarketData != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqSubMarketDataField::FieldID);
		if (strlen(ReqSubMarketData->ExchangeID) >= sizeof(ReqSubMarketData->ExchangeID))
		{
			ReqSubMarketData->ExchangeID[sizeof(ReqSubMarketData->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, ReqSubMarketData->ExchangeID);
		if (strlen(ReqSubMarketData->InstrumentID) >= sizeof(ReqSubMarketData->InstrumentID))
		{
			ReqSubMarketData->InstrumentID[sizeof(ReqSubMarketData->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, ReqSubMarketData->InstrumentID);
		WriteHexString(ppos, Items::FieldEnd, ReqSubMarketDataField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqSubMarketDataPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldID;
		int fieldStartIndex;
		int fieldEndIndex;
		if (GetNextFieldZone(buff, startIndex, endIndex, fieldID, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldID)
			{
			case ReqSubMarketDataField::FieldID:
			{
				ReqSubMarketData = ::Allocate<ReqSubMarketDataField>();
				memset(ReqSubMarketData, 0, sizeof(*ReqSubMarketData));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemID;
					std::string value;
					int sohIndex;
					if (GetNext(buff, itemStartIndex, fieldEndIndex, itemID, value, sohIndex))
					{
						switch (itemID)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(ReqSubMarketData->ExchangeID) ? sizeof(ReqSubMarketData->ExchangeID) - 1 : value.length();
							memcpy(ReqSubMarketData->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(ReqSubMarketData->InstrumentID) ? sizeof(ReqSubMarketData->InstrumentID) - 1 : value.length();
							memcpy(ReqSubMarketData->InstrumentID, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqSubMarketDataField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqSubMarketDataPackage FieldID:0x%X", fieldID);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldID:0x%X, Please Check Api Version.", fieldID);
				return false;
			}
			startIndex = fieldEndIndex;
		}
		else
		{
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqSubMarketDataPackage");
			return false;
		}
	}
	return true;
}
int ReqSubMarketDataPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	memcpy(buff + offset, ReqSubMarketData, sizeof(ReqSubMarketDataField));
	offset += sizeof(ReqSubMarketDataField);
	return offset;
}
bool ReqSubMarketDataPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	ReqSubMarketData = ::Allocate<ReqSubMarketDataField>();
	memcpy(ReqSubMarketData, buff + offset, sizeof(ReqSubMarketDataField));
	offset += sizeof(ReqSubMarketDataField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* ReqSubMarketDataPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "ReqSubMarketData:ExchangeID:[%s], InstrumentID:[%s]",
		ReqSubMarketData->ExchangeID, ReqSubMarketData->InstrumentID);
	return t_DataStringBuffer;
}
 
RspSubMarketDataPackage* RspSubMarketDataPackage::Allocate()
{
	return ::Allocate<RspSubMarketDataPackage>();
}
void RspSubMarketDataPackage::Free()
{
	Package::Free();
	if (RspSubMarketData != nullptr)
	{
		::Free<RspSubMarketDataField>(RspSubMarketData);
		RspSubMarketData = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspSubMarketDataPackage>::GetInstance().Free(this);
}
void RspSubMarketDataPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspSubMarketDataPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (RspSubMarketData != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, RspSubMarketDataField::FieldID);
		if (strlen(RspSubMarketData->ExchangeID) >= sizeof(RspSubMarketData->ExchangeID))
		{
			RspSubMarketData->ExchangeID[sizeof(RspSubMarketData->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, RspSubMarketData->ExchangeID);
		if (strlen(RspSubMarketData->InstrumentID) >= sizeof(RspSubMarketData->InstrumentID))
		{
			RspSubMarketData->InstrumentID[sizeof(RspSubMarketData->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, RspSubMarketData->InstrumentID);
		WriteHexString(ppos, Items::FieldEnd, RspSubMarketDataField::FieldID);
	}
	if (RspInfo != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, RspInfoField::FieldID);
		WriteString(ppos, Items::ErrorID, RspInfo->ErrorID);
		if (strlen(RspInfo->ErrorMsg) >= sizeof(RspInfo->ErrorMsg))
		{
			RspInfo->ErrorMsg[sizeof(RspInfo->ErrorMsg) - 1] = 0;
		}
		WriteString(ppos, Items::ErrorMsg, RspInfo->ErrorMsg);
		WriteHexString(ppos, Items::FieldEnd, RspInfoField::FieldID);
	}
	return int(ppos - buff);
}
bool RspSubMarketDataPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldID;
		int fieldStartIndex;
		int fieldEndIndex;
		if (GetNextFieldZone(buff, startIndex, endIndex, fieldID, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldID)
			{
			case RspSubMarketDataField::FieldID:
			{
				RspSubMarketData = ::Allocate<RspSubMarketDataField>();
				memset(RspSubMarketData, 0, sizeof(*RspSubMarketData));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemID;
					std::string value;
					int sohIndex;
					if (GetNext(buff, itemStartIndex, fieldEndIndex, itemID, value, sohIndex))
					{
						switch (itemID)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(RspSubMarketData->ExchangeID) ? sizeof(RspSubMarketData->ExchangeID) - 1 : value.length();
							memcpy(RspSubMarketData->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(RspSubMarketData->InstrumentID) ? sizeof(RspSubMarketData->InstrumentID) - 1 : value.length();
							memcpy(RspSubMarketData->InstrumentID, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for RspSubMarketDataField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspSubMarketDataPackage FieldID:0x%X", fieldID);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldID:
			{
				RspInfo = ::Allocate<RspInfoField>();
				memset(RspInfo, 0, sizeof(*RspInfo));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemID;
					std::string value;
					int sohIndex;
					if (GetNext(buff, itemStartIndex, fieldEndIndex, itemID, value, sohIndex))
					{
						switch (itemID)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ErrorID:
						{
							RspInfo->ErrorID = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(RspInfo->ErrorMsg) ? sizeof(RspInfo->ErrorMsg) - 1 : value.length();
							memcpy(RspInfo->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for RspInfoField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspSubMarketDataPackage FieldID:0x%X", fieldID);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldID:0x%X, Please Check Api Version.", fieldID);
				return false;
			}
			startIndex = fieldEndIndex;
		}
		else
		{
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspSubMarketDataPackage");
			return false;
		}
	}
	return true;
}
int RspSubMarketDataPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	memcpy(buff + offset, RspSubMarketData, sizeof(RspSubMarketDataField));
	offset += sizeof(RspSubMarketDataField);
	memcpy(buff + offset, RspInfo, sizeof(RspInfoField));
	offset += sizeof(RspInfoField);
	return offset;
}
bool RspSubMarketDataPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	RspSubMarketData = ::Allocate<RspSubMarketDataField>();
	memcpy(RspSubMarketData, buff + offset, sizeof(RspSubMarketDataField));
	offset += sizeof(RspSubMarketDataField);
	RspInfo = ::Allocate<RspInfoField>();
	memcpy(RspInfo, buff + offset, sizeof(RspInfoField));
	offset += sizeof(RspInfoField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* RspSubMarketDataPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "RspSubMarketData:ExchangeID:[%s], InstrumentID:[%s]",
		RspSubMarketData->ExchangeID, RspSubMarketData->InstrumentID);
	offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]",
		RspInfo->ErrorID, RspInfo->ErrorMsg);
	return t_DataStringBuffer;
}
 
ReqUnSubMarketDataPackage* ReqUnSubMarketDataPackage::Allocate()
{
	return ::Allocate<ReqUnSubMarketDataPackage>();
}
void ReqUnSubMarketDataPackage::Free()
{
	Package::Free();
	if (ReqUnSubMarketData != nullptr)
	{
		::Free<ReqUnSubMarketDataField>(ReqUnSubMarketData);
		ReqUnSubMarketData = nullptr;
	}
	MemCacheTemplateSingleton<ReqUnSubMarketDataPackage>::GetInstance().Free(this);
}
void ReqUnSubMarketDataPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqUnSubMarketDataPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqUnSubMarketData != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqUnSubMarketDataField::FieldID);
		if (strlen(ReqUnSubMarketData->ExchangeID) >= sizeof(ReqUnSubMarketData->ExchangeID))
		{
			ReqUnSubMarketData->ExchangeID[sizeof(ReqUnSubMarketData->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, ReqUnSubMarketData->ExchangeID);
		if (strlen(ReqUnSubMarketData->InstrumentID) >= sizeof(ReqUnSubMarketData->InstrumentID))
		{
			ReqUnSubMarketData->InstrumentID[sizeof(ReqUnSubMarketData->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, ReqUnSubMarketData->InstrumentID);
		WriteHexString(ppos, Items::FieldEnd, ReqUnSubMarketDataField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqUnSubMarketDataPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldID;
		int fieldStartIndex;
		int fieldEndIndex;
		if (GetNextFieldZone(buff, startIndex, endIndex, fieldID, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldID)
			{
			case ReqUnSubMarketDataField::FieldID:
			{
				ReqUnSubMarketData = ::Allocate<ReqUnSubMarketDataField>();
				memset(ReqUnSubMarketData, 0, sizeof(*ReqUnSubMarketData));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemID;
					std::string value;
					int sohIndex;
					if (GetNext(buff, itemStartIndex, fieldEndIndex, itemID, value, sohIndex))
					{
						switch (itemID)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(ReqUnSubMarketData->ExchangeID) ? sizeof(ReqUnSubMarketData->ExchangeID) - 1 : value.length();
							memcpy(ReqUnSubMarketData->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(ReqUnSubMarketData->InstrumentID) ? sizeof(ReqUnSubMarketData->InstrumentID) - 1 : value.length();
							memcpy(ReqUnSubMarketData->InstrumentID, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqUnSubMarketDataField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqUnSubMarketDataPackage FieldID:0x%X", fieldID);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldID:0x%X, Please Check Api Version.", fieldID);
				return false;
			}
			startIndex = fieldEndIndex;
		}
		else
		{
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqUnSubMarketDataPackage");
			return false;
		}
	}
	return true;
}
int ReqUnSubMarketDataPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	memcpy(buff + offset, ReqUnSubMarketData, sizeof(ReqUnSubMarketDataField));
	offset += sizeof(ReqUnSubMarketDataField);
	return offset;
}
bool ReqUnSubMarketDataPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	ReqUnSubMarketData = ::Allocate<ReqUnSubMarketDataField>();
	memcpy(ReqUnSubMarketData, buff + offset, sizeof(ReqUnSubMarketDataField));
	offset += sizeof(ReqUnSubMarketDataField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* ReqUnSubMarketDataPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "ReqUnSubMarketData:ExchangeID:[%s], InstrumentID:[%s]",
		ReqUnSubMarketData->ExchangeID, ReqUnSubMarketData->InstrumentID);
	return t_DataStringBuffer;
}
 
RspUnSubMarketDataPackage* RspUnSubMarketDataPackage::Allocate()
{
	return ::Allocate<RspUnSubMarketDataPackage>();
}
void RspUnSubMarketDataPackage::Free()
{
	Package::Free();
	if (RspUnSubMarketData != nullptr)
	{
		::Free<RspUnSubMarketDataField>(RspUnSubMarketData);
		RspUnSubMarketData = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspUnSubMarketDataPackage>::GetInstance().Free(this);
}
void RspUnSubMarketDataPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspUnSubMarketDataPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (RspUnSubMarketData != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, RspUnSubMarketDataField::FieldID);
		if (strlen(RspUnSubMarketData->ExchangeID) >= sizeof(RspUnSubMarketData->ExchangeID))
		{
			RspUnSubMarketData->ExchangeID[sizeof(RspUnSubMarketData->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, RspUnSubMarketData->ExchangeID);
		if (strlen(RspUnSubMarketData->InstrumentID) >= sizeof(RspUnSubMarketData->InstrumentID))
		{
			RspUnSubMarketData->InstrumentID[sizeof(RspUnSubMarketData->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, RspUnSubMarketData->InstrumentID);
		WriteHexString(ppos, Items::FieldEnd, RspUnSubMarketDataField::FieldID);
	}
	if (RspInfo != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, RspInfoField::FieldID);
		WriteString(ppos, Items::ErrorID, RspInfo->ErrorID);
		if (strlen(RspInfo->ErrorMsg) >= sizeof(RspInfo->ErrorMsg))
		{
			RspInfo->ErrorMsg[sizeof(RspInfo->ErrorMsg) - 1] = 0;
		}
		WriteString(ppos, Items::ErrorMsg, RspInfo->ErrorMsg);
		WriteHexString(ppos, Items::FieldEnd, RspInfoField::FieldID);
	}
	return int(ppos - buff);
}
bool RspUnSubMarketDataPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldID;
		int fieldStartIndex;
		int fieldEndIndex;
		if (GetNextFieldZone(buff, startIndex, endIndex, fieldID, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldID)
			{
			case RspUnSubMarketDataField::FieldID:
			{
				RspUnSubMarketData = ::Allocate<RspUnSubMarketDataField>();
				memset(RspUnSubMarketData, 0, sizeof(*RspUnSubMarketData));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemID;
					std::string value;
					int sohIndex;
					if (GetNext(buff, itemStartIndex, fieldEndIndex, itemID, value, sohIndex))
					{
						switch (itemID)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(RspUnSubMarketData->ExchangeID) ? sizeof(RspUnSubMarketData->ExchangeID) - 1 : value.length();
							memcpy(RspUnSubMarketData->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(RspUnSubMarketData->InstrumentID) ? sizeof(RspUnSubMarketData->InstrumentID) - 1 : value.length();
							memcpy(RspUnSubMarketData->InstrumentID, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for RspUnSubMarketDataField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspUnSubMarketDataPackage FieldID:0x%X", fieldID);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldID:
			{
				RspInfo = ::Allocate<RspInfoField>();
				memset(RspInfo, 0, sizeof(*RspInfo));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemID;
					std::string value;
					int sohIndex;
					if (GetNext(buff, itemStartIndex, fieldEndIndex, itemID, value, sohIndex))
					{
						switch (itemID)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ErrorID:
						{
							RspInfo->ErrorID = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(RspInfo->ErrorMsg) ? sizeof(RspInfo->ErrorMsg) - 1 : value.length();
							memcpy(RspInfo->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for RspInfoField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspUnSubMarketDataPackage FieldID:0x%X", fieldID);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldID:0x%X, Please Check Api Version.", fieldID);
				return false;
			}
			startIndex = fieldEndIndex;
		}
		else
		{
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspUnSubMarketDataPackage");
			return false;
		}
	}
	return true;
}
int RspUnSubMarketDataPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	memcpy(buff + offset, RspUnSubMarketData, sizeof(RspUnSubMarketDataField));
	offset += sizeof(RspUnSubMarketDataField);
	memcpy(buff + offset, RspInfo, sizeof(RspInfoField));
	offset += sizeof(RspInfoField);
	return offset;
}
bool RspUnSubMarketDataPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	RspUnSubMarketData = ::Allocate<RspUnSubMarketDataField>();
	memcpy(RspUnSubMarketData, buff + offset, sizeof(RspUnSubMarketDataField));
	offset += sizeof(RspUnSubMarketDataField);
	RspInfo = ::Allocate<RspInfoField>();
	memcpy(RspInfo, buff + offset, sizeof(RspInfoField));
	offset += sizeof(RspInfoField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* RspUnSubMarketDataPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "RspUnSubMarketData:ExchangeID:[%s], InstrumentID:[%s]",
		RspUnSubMarketData->ExchangeID, RspUnSubMarketData->InstrumentID);
	offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]",
		RspInfo->ErrorID, RspInfo->ErrorMsg);
	return t_DataStringBuffer;
}
 
RtnDepthMarketDataPackage* RtnDepthMarketDataPackage::Allocate()
{
	return ::Allocate<RtnDepthMarketDataPackage>();
}
void RtnDepthMarketDataPackage::Free()
{
	Package::Free();
	if (DepthMarketData != nullptr)
	{
		::Free<DepthMarketDataField>(DepthMarketData);
		DepthMarketData = nullptr;
	}
	MemCacheTemplateSingleton<RtnDepthMarketDataPackage>::GetInstance().Free(this);
}
void RtnDepthMarketDataPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RtnDepthMarketDataPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (DepthMarketData != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, DepthMarketDataField::FieldID);
		if (strlen(DepthMarketData->TradingDay) >= sizeof(DepthMarketData->TradingDay))
		{
			DepthMarketData->TradingDay[sizeof(DepthMarketData->TradingDay) - 1] = 0;
		}
		WriteString(ppos, Items::TradingDay, DepthMarketData->TradingDay);
		if (strlen(DepthMarketData->ExchangeID) >= sizeof(DepthMarketData->ExchangeID))
		{
			DepthMarketData->ExchangeID[sizeof(DepthMarketData->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, DepthMarketData->ExchangeID);
		if (strlen(DepthMarketData->InstrumentID) >= sizeof(DepthMarketData->InstrumentID))
		{
			DepthMarketData->InstrumentID[sizeof(DepthMarketData->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, DepthMarketData->InstrumentID);
		WriteString(ppos, Items::LastPrice, DepthMarketData->LastPrice);
		WriteString(ppos, Items::PreSettlementPrice, DepthMarketData->PreSettlementPrice);
		WriteString(ppos, Items::PreClosePrice, DepthMarketData->PreClosePrice);
		WriteString(ppos, Items::PreOpenInterest, DepthMarketData->PreOpenInterest);
		WriteString(ppos, Items::OpenPrice, DepthMarketData->OpenPrice);
		WriteString(ppos, Items::HighestPrice, DepthMarketData->HighestPrice);
		WriteString(ppos, Items::LowestPrice, DepthMarketData->LowestPrice);
		WriteString(ppos, Items::ClosePrice, DepthMarketData->ClosePrice);
		WriteString(ppos, Items::CurrVolume, DepthMarketData->CurrVolume);
		WriteString(ppos, Items::Volume, DepthMarketData->Volume);
		WriteString(ppos, Items::CurrTurnover, DepthMarketData->CurrTurnover);
		WriteString(ppos, Items::Turnover, DepthMarketData->Turnover);
		WriteString(ppos, Items::OpenInterest, DepthMarketData->OpenInterest);
		WriteString(ppos, Items::SettlementPrice, DepthMarketData->SettlementPrice);
		WriteString(ppos, Items::UpperLimitPrice, DepthMarketData->UpperLimitPrice);
		WriteString(ppos, Items::LowerLimitPrice, DepthMarketData->LowerLimitPrice);
		WriteString(ppos, Items::AveragePrice, DepthMarketData->AveragePrice);
		WriteString(ppos, Items::UpdateTs, DepthMarketData->UpdateTs);
		WriteString(ppos, Items::AskPrice1, DepthMarketData->AskPrice1);
		WriteString(ppos, Items::AskPrice2, DepthMarketData->AskPrice2);
		WriteString(ppos, Items::AskPrice3, DepthMarketData->AskPrice3);
		WriteString(ppos, Items::AskPrice4, DepthMarketData->AskPrice4);
		WriteString(ppos, Items::AskPrice5, DepthMarketData->AskPrice5);
		WriteString(ppos, Items::AskPrice6, DepthMarketData->AskPrice6);
		WriteString(ppos, Items::AskPrice7, DepthMarketData->AskPrice7);
		WriteString(ppos, Items::AskPrice8, DepthMarketData->AskPrice8);
		WriteString(ppos, Items::AskPrice9, DepthMarketData->AskPrice9);
		WriteString(ppos, Items::AskPrice10, DepthMarketData->AskPrice10);
		WriteString(ppos, Items::AskVolume1, DepthMarketData->AskVolume1);
		WriteString(ppos, Items::AskVolume2, DepthMarketData->AskVolume2);
		WriteString(ppos, Items::AskVolume3, DepthMarketData->AskVolume3);
		WriteString(ppos, Items::AskVolume4, DepthMarketData->AskVolume4);
		WriteString(ppos, Items::AskVolume5, DepthMarketData->AskVolume5);
		WriteString(ppos, Items::AskVolume6, DepthMarketData->AskVolume6);
		WriteString(ppos, Items::AskVolume7, DepthMarketData->AskVolume7);
		WriteString(ppos, Items::AskVolume8, DepthMarketData->AskVolume8);
		WriteString(ppos, Items::AskVolume9, DepthMarketData->AskVolume9);
		WriteString(ppos, Items::AskVolume10, DepthMarketData->AskVolume10);
		WriteString(ppos, Items::BidPrice1, DepthMarketData->BidPrice1);
		WriteString(ppos, Items::BidPrice2, DepthMarketData->BidPrice2);
		WriteString(ppos, Items::BidPrice3, DepthMarketData->BidPrice3);
		WriteString(ppos, Items::BidPrice4, DepthMarketData->BidPrice4);
		WriteString(ppos, Items::BidPrice5, DepthMarketData->BidPrice5);
		WriteString(ppos, Items::BidPrice6, DepthMarketData->BidPrice6);
		WriteString(ppos, Items::BidPrice7, DepthMarketData->BidPrice7);
		WriteString(ppos, Items::BidPrice8, DepthMarketData->BidPrice8);
		WriteString(ppos, Items::BidPrice9, DepthMarketData->BidPrice9);
		WriteString(ppos, Items::BidPrice10, DepthMarketData->BidPrice10);
		WriteString(ppos, Items::BidVolume1, DepthMarketData->BidVolume1);
		WriteString(ppos, Items::BidVolume2, DepthMarketData->BidVolume2);
		WriteString(ppos, Items::BidVolume3, DepthMarketData->BidVolume3);
		WriteString(ppos, Items::BidVolume4, DepthMarketData->BidVolume4);
		WriteString(ppos, Items::BidVolume5, DepthMarketData->BidVolume5);
		WriteString(ppos, Items::BidVolume6, DepthMarketData->BidVolume6);
		WriteString(ppos, Items::BidVolume7, DepthMarketData->BidVolume7);
		WriteString(ppos, Items::BidVolume8, DepthMarketData->BidVolume8);
		WriteString(ppos, Items::BidVolume9, DepthMarketData->BidVolume9);
		WriteString(ppos, Items::BidVolume10, DepthMarketData->BidVolume10);
		WriteHexString(ppos, Items::FieldEnd, DepthMarketDataField::FieldID);
	}
	return int(ppos - buff);
}
bool RtnDepthMarketDataPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldID;
		int fieldStartIndex;
		int fieldEndIndex;
		if (GetNextFieldZone(buff, startIndex, endIndex, fieldID, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldID)
			{
			case DepthMarketDataField::FieldID:
			{
				DepthMarketData = ::Allocate<DepthMarketDataField>();
				memset(DepthMarketData, 0, sizeof(*DepthMarketData));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemID;
					std::string value;
					int sohIndex;
					if (GetNext(buff, itemStartIndex, fieldEndIndex, itemID, value, sohIndex))
					{
						switch (itemID)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::TradingDay:
						{
							size_t len = value.length() >= sizeof(DepthMarketData->TradingDay) ? sizeof(DepthMarketData->TradingDay) - 1 : value.length();
							memcpy(DepthMarketData->TradingDay, value.c_str(), len);
							break;
						}
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(DepthMarketData->ExchangeID) ? sizeof(DepthMarketData->ExchangeID) - 1 : value.length();
							memcpy(DepthMarketData->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(DepthMarketData->InstrumentID) ? sizeof(DepthMarketData->InstrumentID) - 1 : value.length();
							memcpy(DepthMarketData->InstrumentID, value.c_str(), len);
							break;
						}
						case Items::LastPrice:
						{
							DepthMarketData->LastPrice = atof(value.c_str());
							break;
						}
						case Items::PreSettlementPrice:
						{
							DepthMarketData->PreSettlementPrice = atof(value.c_str());
							break;
						}
						case Items::PreClosePrice:
						{
							DepthMarketData->PreClosePrice = atof(value.c_str());
							break;
						}
						case Items::PreOpenInterest:
						{
							DepthMarketData->PreOpenInterest = atoll(value.c_str());
							break;
						}
						case Items::OpenPrice:
						{
							DepthMarketData->OpenPrice = atof(value.c_str());
							break;
						}
						case Items::HighestPrice:
						{
							DepthMarketData->HighestPrice = atof(value.c_str());
							break;
						}
						case Items::LowestPrice:
						{
							DepthMarketData->LowestPrice = atof(value.c_str());
							break;
						}
						case Items::ClosePrice:
						{
							DepthMarketData->ClosePrice = atof(value.c_str());
							break;
						}
						case Items::CurrVolume:
						{
							DepthMarketData->CurrVolume = atoll(value.c_str());
							break;
						}
						case Items::Volume:
						{
							DepthMarketData->Volume = atoll(value.c_str());
							break;
						}
						case Items::CurrTurnover:
						{
							DepthMarketData->CurrTurnover = atof(value.c_str());
							break;
						}
						case Items::Turnover:
						{
							DepthMarketData->Turnover = atof(value.c_str());
							break;
						}
						case Items::OpenInterest:
						{
							DepthMarketData->OpenInterest = atoll(value.c_str());
							break;
						}
						case Items::SettlementPrice:
						{
							DepthMarketData->SettlementPrice = atof(value.c_str());
							break;
						}
						case Items::UpperLimitPrice:
						{
							DepthMarketData->UpperLimitPrice = atof(value.c_str());
							break;
						}
						case Items::LowerLimitPrice:
						{
							DepthMarketData->LowerLimitPrice = atof(value.c_str());
							break;
						}
						case Items::AveragePrice:
						{
							DepthMarketData->AveragePrice = atof(value.c_str());
							break;
						}
						case Items::UpdateTs:
						{
							DepthMarketData->UpdateTs = atoll(value.c_str());
							break;
						}
						case Items::AskPrice1:
						{
							DepthMarketData->AskPrice1 = atof(value.c_str());
							break;
						}
						case Items::AskPrice2:
						{
							DepthMarketData->AskPrice2 = atof(value.c_str());
							break;
						}
						case Items::AskPrice3:
						{
							DepthMarketData->AskPrice3 = atof(value.c_str());
							break;
						}
						case Items::AskPrice4:
						{
							DepthMarketData->AskPrice4 = atof(value.c_str());
							break;
						}
						case Items::AskPrice5:
						{
							DepthMarketData->AskPrice5 = atof(value.c_str());
							break;
						}
						case Items::AskPrice6:
						{
							DepthMarketData->AskPrice6 = atof(value.c_str());
							break;
						}
						case Items::AskPrice7:
						{
							DepthMarketData->AskPrice7 = atof(value.c_str());
							break;
						}
						case Items::AskPrice8:
						{
							DepthMarketData->AskPrice8 = atof(value.c_str());
							break;
						}
						case Items::AskPrice9:
						{
							DepthMarketData->AskPrice9 = atof(value.c_str());
							break;
						}
						case Items::AskPrice10:
						{
							DepthMarketData->AskPrice10 = atof(value.c_str());
							break;
						}
						case Items::AskVolume1:
						{
							DepthMarketData->AskVolume1 = atoll(value.c_str());
							break;
						}
						case Items::AskVolume2:
						{
							DepthMarketData->AskVolume2 = atoll(value.c_str());
							break;
						}
						case Items::AskVolume3:
						{
							DepthMarketData->AskVolume3 = atoll(value.c_str());
							break;
						}
						case Items::AskVolume4:
						{
							DepthMarketData->AskVolume4 = atoll(value.c_str());
							break;
						}
						case Items::AskVolume5:
						{
							DepthMarketData->AskVolume5 = atoll(value.c_str());
							break;
						}
						case Items::AskVolume6:
						{
							DepthMarketData->AskVolume6 = atoll(value.c_str());
							break;
						}
						case Items::AskVolume7:
						{
							DepthMarketData->AskVolume7 = atoll(value.c_str());
							break;
						}
						case Items::AskVolume8:
						{
							DepthMarketData->AskVolume8 = atoll(value.c_str());
							break;
						}
						case Items::AskVolume9:
						{
							DepthMarketData->AskVolume9 = atoll(value.c_str());
							break;
						}
						case Items::AskVolume10:
						{
							DepthMarketData->AskVolume10 = atoll(value.c_str());
							break;
						}
						case Items::BidPrice1:
						{
							DepthMarketData->BidPrice1 = atof(value.c_str());
							break;
						}
						case Items::BidPrice2:
						{
							DepthMarketData->BidPrice2 = atof(value.c_str());
							break;
						}
						case Items::BidPrice3:
						{
							DepthMarketData->BidPrice3 = atof(value.c_str());
							break;
						}
						case Items::BidPrice4:
						{
							DepthMarketData->BidPrice4 = atof(value.c_str());
							break;
						}
						case Items::BidPrice5:
						{
							DepthMarketData->BidPrice5 = atof(value.c_str());
							break;
						}
						case Items::BidPrice6:
						{
							DepthMarketData->BidPrice6 = atof(value.c_str());
							break;
						}
						case Items::BidPrice7:
						{
							DepthMarketData->BidPrice7 = atof(value.c_str());
							break;
						}
						case Items::BidPrice8:
						{
							DepthMarketData->BidPrice8 = atof(value.c_str());
							break;
						}
						case Items::BidPrice9:
						{
							DepthMarketData->BidPrice9 = atof(value.c_str());
							break;
						}
						case Items::BidPrice10:
						{
							DepthMarketData->BidPrice10 = atof(value.c_str());
							break;
						}
						case Items::BidVolume1:
						{
							DepthMarketData->BidVolume1 = atoll(value.c_str());
							break;
						}
						case Items::BidVolume2:
						{
							DepthMarketData->BidVolume2 = atoll(value.c_str());
							break;
						}
						case Items::BidVolume3:
						{
							DepthMarketData->BidVolume3 = atoll(value.c_str());
							break;
						}
						case Items::BidVolume4:
						{
							DepthMarketData->BidVolume4 = atoll(value.c_str());
							break;
						}
						case Items::BidVolume5:
						{
							DepthMarketData->BidVolume5 = atoll(value.c_str());
							break;
						}
						case Items::BidVolume6:
						{
							DepthMarketData->BidVolume6 = atoll(value.c_str());
							break;
						}
						case Items::BidVolume7:
						{
							DepthMarketData->BidVolume7 = atoll(value.c_str());
							break;
						}
						case Items::BidVolume8:
						{
							DepthMarketData->BidVolume8 = atoll(value.c_str());
							break;
						}
						case Items::BidVolume9:
						{
							DepthMarketData->BidVolume9 = atoll(value.c_str());
							break;
						}
						case Items::BidVolume10:
						{
							DepthMarketData->BidVolume10 = atoll(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for DepthMarketDataField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RtnDepthMarketDataPackage FieldID:0x%X", fieldID);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldID:0x%X, Please Check Api Version.", fieldID);
				return false;
			}
			startIndex = fieldEndIndex;
		}
		else
		{
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RtnDepthMarketDataPackage");
			return false;
		}
	}
	return true;
}
int RtnDepthMarketDataPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	memcpy(buff + offset, DepthMarketData, sizeof(DepthMarketDataField));
	offset += sizeof(DepthMarketDataField);
	return offset;
}
bool RtnDepthMarketDataPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	DepthMarketData = ::Allocate<DepthMarketDataField>();
	memcpy(DepthMarketData, buff + offset, sizeof(DepthMarketDataField));
	offset += sizeof(DepthMarketDataField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* RtnDepthMarketDataPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "DepthMarketData:TradingDay:[%s], ExchangeID:[%s], InstrumentID:[%s], LastPrice:[%f], PreSettlementPrice:[%f], PreClosePrice:[%f], PreOpenInterest:[%lld], OpenPrice:[%f], HighestPrice:[%f], LowestPrice:[%f], ClosePrice:[%f], CurrVolume:[%lld], Volume:[%lld], CurrTurnover:[%f], Turnover:[%f], OpenInterest:[%lld], SettlementPrice:[%f], UpperLimitPrice:[%f], LowerLimitPrice:[%f], AveragePrice:[%f], UpdateTs:[%lld], AskPrice1:[%f], AskPrice2:[%f], AskPrice3:[%f], AskPrice4:[%f], AskPrice5:[%f], AskPrice6:[%f], AskPrice7:[%f], AskPrice8:[%f], AskPrice9:[%f], AskPrice10:[%f], AskVolume1:[%lld], AskVolume2:[%lld], AskVolume3:[%lld], AskVolume4:[%lld], AskVolume5:[%lld], AskVolume6:[%lld], AskVolume7:[%lld], AskVolume8:[%lld], AskVolume9:[%lld], AskVolume10:[%lld], BidPrice1:[%f], BidPrice2:[%f], BidPrice3:[%f], BidPrice4:[%f], BidPrice5:[%f], BidPrice6:[%f], BidPrice7:[%f], BidPrice8:[%f], BidPrice9:[%f], BidPrice10:[%f], BidVolume1:[%lld], BidVolume2:[%lld], BidVolume3:[%lld], BidVolume4:[%lld], BidVolume5:[%lld], BidVolume6:[%lld], BidVolume7:[%lld], BidVolume8:[%lld], BidVolume9:[%lld], BidVolume10:[%lld]",
		DepthMarketData->TradingDay, DepthMarketData->ExchangeID, DepthMarketData->InstrumentID, DepthMarketData->LastPrice, DepthMarketData->PreSettlementPrice, DepthMarketData->PreClosePrice, DepthMarketData->PreOpenInterest, DepthMarketData->OpenPrice, DepthMarketData->HighestPrice, DepthMarketData->LowestPrice, DepthMarketData->ClosePrice, DepthMarketData->CurrVolume, DepthMarketData->Volume, DepthMarketData->CurrTurnover, DepthMarketData->Turnover, DepthMarketData->OpenInterest, DepthMarketData->SettlementPrice, DepthMarketData->UpperLimitPrice, DepthMarketData->LowerLimitPrice, DepthMarketData->AveragePrice, DepthMarketData->UpdateTs, DepthMarketData->AskPrice1, DepthMarketData->AskPrice2, DepthMarketData->AskPrice3, DepthMarketData->AskPrice4, DepthMarketData->AskPrice5, DepthMarketData->AskPrice6, DepthMarketData->AskPrice7, DepthMarketData->AskPrice8, DepthMarketData->AskPrice9, DepthMarketData->AskPrice10, DepthMarketData->AskVolume1, DepthMarketData->AskVolume2, DepthMarketData->AskVolume3, DepthMarketData->AskVolume4, DepthMarketData->AskVolume5, DepthMarketData->AskVolume6, DepthMarketData->AskVolume7, DepthMarketData->AskVolume8, DepthMarketData->AskVolume9, DepthMarketData->AskVolume10, DepthMarketData->BidPrice1, DepthMarketData->BidPrice2, DepthMarketData->BidPrice3, DepthMarketData->BidPrice4, DepthMarketData->BidPrice5, DepthMarketData->BidPrice6, DepthMarketData->BidPrice7, DepthMarketData->BidPrice8, DepthMarketData->BidPrice9, DepthMarketData->BidPrice10, DepthMarketData->BidVolume1, DepthMarketData->BidVolume2, DepthMarketData->BidVolume3, DepthMarketData->BidVolume4, DepthMarketData->BidVolume5, DepthMarketData->BidVolume6, DepthMarketData->BidVolume7, DepthMarketData->BidVolume8, DepthMarketData->BidVolume9, DepthMarketData->BidVolume10);
	return t_DataStringBuffer;
}
 
RtnBarMarketDataPackage* RtnBarMarketDataPackage::Allocate()
{
	return ::Allocate<RtnBarMarketDataPackage>();
}
void RtnBarMarketDataPackage::Free()
{
	Package::Free();
	if (BarMarketData != nullptr)
	{
		::Free<BarMarketDataField>(BarMarketData);
		BarMarketData = nullptr;
	}
	MemCacheTemplateSingleton<RtnBarMarketDataPackage>::GetInstance().Free(this);
}
void RtnBarMarketDataPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RtnBarMarketDataPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (BarMarketData != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, BarMarketDataField::FieldID);
		if (strlen(BarMarketData->TradingDay) >= sizeof(BarMarketData->TradingDay))
		{
			BarMarketData->TradingDay[sizeof(BarMarketData->TradingDay) - 1] = 0;
		}
		WriteString(ppos, Items::TradingDay, BarMarketData->TradingDay);
		if (strlen(BarMarketData->ExchangeID) >= sizeof(BarMarketData->ExchangeID))
		{
			BarMarketData->ExchangeID[sizeof(BarMarketData->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, BarMarketData->ExchangeID);
		if (strlen(BarMarketData->InstrumentID) >= sizeof(BarMarketData->InstrumentID))
		{
			BarMarketData->InstrumentID[sizeof(BarMarketData->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, BarMarketData->InstrumentID);
		WriteString(ppos, Items::BarPreces, (int)BarMarketData->BarPreces);
		WriteString(ppos, Items::BarPeriod, BarMarketData->BarPeriod);
		WriteString(ppos, Items::BarTime, BarMarketData->BarTime);
		WriteString(ppos, Items::UpdateTs, BarMarketData->UpdateTs);
		WriteString(ppos, Items::HighestPrice, BarMarketData->HighestPrice);
		WriteString(ppos, Items::LowestPrice, BarMarketData->LowestPrice);
		WriteString(ppos, Items::Open, BarMarketData->Open);
		WriteString(ppos, Items::High, BarMarketData->High);
		WriteString(ppos, Items::Low, BarMarketData->Low);
		WriteString(ppos, Items::Close, BarMarketData->Close);
		WriteString(ppos, Items::CurrVolume, BarMarketData->CurrVolume);
		WriteString(ppos, Items::Volume, BarMarketData->Volume);
		WriteString(ppos, Items::CurrTurnover, BarMarketData->CurrTurnover);
		WriteString(ppos, Items::Turnover, BarMarketData->Turnover);
		WriteString(ppos, Items::OpenInterest, BarMarketData->OpenInterest);
		WriteHexString(ppos, Items::FieldEnd, BarMarketDataField::FieldID);
	}
	return int(ppos - buff);
}
bool RtnBarMarketDataPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldID;
		int fieldStartIndex;
		int fieldEndIndex;
		if (GetNextFieldZone(buff, startIndex, endIndex, fieldID, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldID)
			{
			case BarMarketDataField::FieldID:
			{
				BarMarketData = ::Allocate<BarMarketDataField>();
				memset(BarMarketData, 0, sizeof(*BarMarketData));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemID;
					std::string value;
					int sohIndex;
					if (GetNext(buff, itemStartIndex, fieldEndIndex, itemID, value, sohIndex))
					{
						switch (itemID)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::TradingDay:
						{
							size_t len = value.length() >= sizeof(BarMarketData->TradingDay) ? sizeof(BarMarketData->TradingDay) - 1 : value.length();
							memcpy(BarMarketData->TradingDay, value.c_str(), len);
							break;
						}
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(BarMarketData->ExchangeID) ? sizeof(BarMarketData->ExchangeID) - 1 : value.length();
							memcpy(BarMarketData->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(BarMarketData->InstrumentID) ? sizeof(BarMarketData->InstrumentID) - 1 : value.length();
							memcpy(BarMarketData->InstrumentID, value.c_str(), len);
							break;
						}
						case Items::BarPreces:
						{
							BarMarketData->BarPreces = (BarPrecesType)(atoi(value.c_str()));
							break;
						}
						case Items::BarPeriod:
						{
							BarMarketData->BarPeriod = atoi(value.c_str());
							break;
						}
						case Items::BarTime:
						{
							BarMarketData->BarTime = atoll(value.c_str());
							break;
						}
						case Items::UpdateTs:
						{
							BarMarketData->UpdateTs = atoll(value.c_str());
							break;
						}
						case Items::HighestPrice:
						{
							BarMarketData->HighestPrice = atof(value.c_str());
							break;
						}
						case Items::LowestPrice:
						{
							BarMarketData->LowestPrice = atof(value.c_str());
							break;
						}
						case Items::Open:
						{
							BarMarketData->Open = atof(value.c_str());
							break;
						}
						case Items::High:
						{
							BarMarketData->High = atof(value.c_str());
							break;
						}
						case Items::Low:
						{
							BarMarketData->Low = atof(value.c_str());
							break;
						}
						case Items::Close:
						{
							BarMarketData->Close = atof(value.c_str());
							break;
						}
						case Items::CurrVolume:
						{
							BarMarketData->CurrVolume = atoll(value.c_str());
							break;
						}
						case Items::Volume:
						{
							BarMarketData->Volume = atoll(value.c_str());
							break;
						}
						case Items::CurrTurnover:
						{
							BarMarketData->CurrTurnover = atof(value.c_str());
							break;
						}
						case Items::Turnover:
						{
							BarMarketData->Turnover = atof(value.c_str());
							break;
						}
						case Items::OpenInterest:
						{
							BarMarketData->OpenInterest = atoll(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for BarMarketDataField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RtnBarMarketDataPackage FieldID:0x%X", fieldID);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldID:0x%X, Please Check Api Version.", fieldID);
				return false;
			}
			startIndex = fieldEndIndex;
		}
		else
		{
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RtnBarMarketDataPackage");
			return false;
		}
	}
	return true;
}
int RtnBarMarketDataPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	memcpy(buff + offset, BarMarketData, sizeof(BarMarketDataField));
	offset += sizeof(BarMarketDataField);
	return offset;
}
bool RtnBarMarketDataPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	BarMarketData = ::Allocate<BarMarketDataField>();
	memcpy(BarMarketData, buff + offset, sizeof(BarMarketDataField));
	offset += sizeof(BarMarketDataField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* RtnBarMarketDataPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "BarMarketData:TradingDay:[%s], ExchangeID:[%s], InstrumentID:[%s], BarPreces:[%d], BarPeriod:[%d], BarTime:[%lld], UpdateTs:[%lld], HighestPrice:[%f], LowestPrice:[%f], Open:[%f], High:[%f], Low:[%f], Close:[%f], CurrVolume:[%lld], Volume:[%lld], CurrTurnover:[%f], Turnover:[%f], OpenInterest:[%lld]",
		BarMarketData->TradingDay, BarMarketData->ExchangeID, BarMarketData->InstrumentID, (int)BarMarketData->BarPreces, BarMarketData->BarPeriod, BarMarketData->BarTime, BarMarketData->UpdateTs, BarMarketData->HighestPrice, BarMarketData->LowestPrice, BarMarketData->Open, BarMarketData->High, BarMarketData->Low, BarMarketData->Close, BarMarketData->CurrVolume, BarMarketData->Volume, BarMarketData->CurrTurnover, BarMarketData->Turnover, BarMarketData->OpenInterest);
	return t_DataStringBuffer;
}
