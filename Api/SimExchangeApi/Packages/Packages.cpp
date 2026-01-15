#include "Packages.h"
#include "Items.h"
#include "StepUtility.h"
#include "Logger.h"
#include "MemCacheTemplateSingleton.h"
#include <cstring>

thread_local char t_DataStringBuffer[10240];



 
ReqAccountLoginPackage* ReqAccountLoginPackage::Allocate()
{
	return ::Allocate<ReqAccountLoginPackage>();
}
void ReqAccountLoginPackage::Free()
{
	Package::Free();
	if (ReqAccountLogin != nullptr)
	{
		::Free<ReqAccountLoginField>(ReqAccountLogin);
		ReqAccountLogin = nullptr;
	}
	MemCacheTemplateSingleton<ReqAccountLoginPackage>::GetInstance().Free(this);
}
void ReqAccountLoginPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqAccountLoginPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqAccountLogin != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqAccountLoginField::FieldID);
		if (strlen(ReqAccountLogin->AccountID) >= sizeof(ReqAccountLogin->AccountID))
		{
			ReqAccountLogin->AccountID[sizeof(ReqAccountLogin->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, ReqAccountLogin->AccountID);
		if (strlen(ReqAccountLogin->Password) >= sizeof(ReqAccountLogin->Password))
		{
			ReqAccountLogin->Password[sizeof(ReqAccountLogin->Password) - 1] = 0;
		}
		WriteString(ppos, Items::Password, ReqAccountLogin->Password);
		WriteHexString(ppos, Items::FieldEnd, ReqAccountLoginField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqAccountLoginPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqAccountLoginField::FieldID:
			{
				ReqAccountLogin = ::Allocate<ReqAccountLoginField>();
				memset(ReqAccountLogin, 0, sizeof(*ReqAccountLogin));
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
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(ReqAccountLogin->AccountID) ? sizeof(ReqAccountLogin->AccountID) - 1 : value.length();
							memcpy(ReqAccountLogin->AccountID, value.c_str(), len);
							break;
						}
						case Items::Password:
						{
							size_t len = value.length() >= sizeof(ReqAccountLogin->Password) ? sizeof(ReqAccountLogin->Password) - 1 : value.length();
							memcpy(ReqAccountLogin->Password, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqAccountLoginField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqAccountLoginPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqAccountLoginPackage");
			return false;
		}
	}
	return true;
}
int ReqAccountLoginPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqAccountLogin != nullptr)
	{
		memcpy(buff + offset, &ReqAccountLoginField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqAccountLogin, sizeof(ReqAccountLoginField));
		offset += sizeof(ReqAccountLoginField);
	}
	return offset;
}
bool ReqAccountLoginPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqAccountLoginField::FieldID:
		{
			ReqAccountLogin = ::Allocate<ReqAccountLoginField>();
			memcpy(ReqAccountLogin, buff + offset, sizeof(ReqAccountLoginField));
			offset += sizeof(ReqAccountLoginField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqAccountLoginPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqAccountLogin != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqAccountLogin:AccountID:[%s], Password:[%s]", ReqAccountLogin->AccountID, ReqAccountLogin->Password);
	}
	return t_DataStringBuffer;
}
 
RspAccountLoginPackage* RspAccountLoginPackage::Allocate()
{
	return ::Allocate<RspAccountLoginPackage>();
}
void RspAccountLoginPackage::Free()
{
	Package::Free();
	if (RspAccountLogin != nullptr)
	{
		::Free<RspAccountLoginField>(RspAccountLogin);
		RspAccountLogin = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspAccountLoginPackage>::GetInstance().Free(this);
}
void RspAccountLoginPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspAccountLoginPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (RspAccountLogin != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, RspAccountLoginField::FieldID);
		if (strlen(RspAccountLogin->AccountID) >= sizeof(RspAccountLogin->AccountID))
		{
			RspAccountLogin->AccountID[sizeof(RspAccountLogin->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, RspAccountLogin->AccountID);
		if (strlen(RspAccountLogin->LoginDate) >= sizeof(RspAccountLogin->LoginDate))
		{
			RspAccountLogin->LoginDate[sizeof(RspAccountLogin->LoginDate) - 1] = 0;
		}
		WriteString(ppos, Items::LoginDate, RspAccountLogin->LoginDate);
		if (strlen(RspAccountLogin->LoginTime) >= sizeof(RspAccountLogin->LoginTime))
		{
			RspAccountLogin->LoginTime[sizeof(RspAccountLogin->LoginTime) - 1] = 0;
		}
		WriteString(ppos, Items::LoginTime, RspAccountLogin->LoginTime);
		WriteString(ppos, Items::SessionID, RspAccountLogin->SessionID);
		WriteHexString(ppos, Items::FieldEnd, RspAccountLoginField::FieldID);
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
bool RspAccountLoginPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case RspAccountLoginField::FieldID:
			{
				RspAccountLogin = ::Allocate<RspAccountLoginField>();
				memset(RspAccountLogin, 0, sizeof(*RspAccountLogin));
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
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(RspAccountLogin->AccountID) ? sizeof(RspAccountLogin->AccountID) - 1 : value.length();
							memcpy(RspAccountLogin->AccountID, value.c_str(), len);
							break;
						}
						case Items::LoginDate:
						{
							size_t len = value.length() >= sizeof(RspAccountLogin->LoginDate) ? sizeof(RspAccountLogin->LoginDate) - 1 : value.length();
							memcpy(RspAccountLogin->LoginDate, value.c_str(), len);
							break;
						}
						case Items::LoginTime:
						{
							size_t len = value.length() >= sizeof(RspAccountLogin->LoginTime) ? sizeof(RspAccountLogin->LoginTime) - 1 : value.length();
							memcpy(RspAccountLogin->LoginTime, value.c_str(), len);
							break;
						}
						case Items::SessionID:
						{
							RspAccountLogin->SessionID = atoll(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for RspAccountLoginField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspAccountLoginPackage FieldID:0x%X", fieldID);
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
						WriteLog(LogLevel::Warning, "GetNext Failed For RspAccountLoginPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspAccountLoginPackage");
			return false;
		}
	}
	return true;
}
int RspAccountLoginPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (RspAccountLogin != nullptr)
	{
		memcpy(buff + offset, &RspAccountLoginField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, RspAccountLogin, sizeof(RspAccountLoginField));
		offset += sizeof(RspAccountLoginField);
	}
	if (RspInfo != nullptr)
	{
		memcpy(buff + offset, &RspInfoField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, RspInfo, sizeof(RspInfoField));
		offset += sizeof(RspInfoField);
	}
	return offset;
}
bool RspAccountLoginPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case RspAccountLoginField::FieldID:
		{
			RspAccountLogin = ::Allocate<RspAccountLoginField>();
			memcpy(RspAccountLogin, buff + offset, sizeof(RspAccountLoginField));
			offset += sizeof(RspAccountLoginField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ::Allocate<RspInfoField>();
			memcpy(RspInfo, buff + offset, sizeof(RspInfoField));
			offset += sizeof(RspInfoField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* RspAccountLoginPackage::GetDebugString() const
{
	int offset = 0;
	if (RspAccountLogin != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspAccountLogin:AccountID:[%s], LoginDate:[%s], LoginTime:[%s], SessionID:[%lld]", RspAccountLogin->AccountID, RspAccountLogin->LoginDate, RspAccountLogin->LoginTime, RspAccountLogin->SessionID);
	}
	if (RspInfo != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
	return t_DataStringBuffer;
}
 
ReqAccountLogoutPackage* ReqAccountLogoutPackage::Allocate()
{
	return ::Allocate<ReqAccountLogoutPackage>();
}
void ReqAccountLogoutPackage::Free()
{
	Package::Free();
	if (ReqAccountLogout != nullptr)
	{
		::Free<ReqAccountLogoutField>(ReqAccountLogout);
		ReqAccountLogout = nullptr;
	}
	MemCacheTemplateSingleton<ReqAccountLogoutPackage>::GetInstance().Free(this);
}
void ReqAccountLogoutPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqAccountLogoutPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqAccountLogout != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqAccountLogoutField::FieldID);
		if (strlen(ReqAccountLogout->AccountID) >= sizeof(ReqAccountLogout->AccountID))
		{
			ReqAccountLogout->AccountID[sizeof(ReqAccountLogout->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, ReqAccountLogout->AccountID);
		WriteHexString(ppos, Items::FieldEnd, ReqAccountLogoutField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqAccountLogoutPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqAccountLogoutField::FieldID:
			{
				ReqAccountLogout = ::Allocate<ReqAccountLogoutField>();
				memset(ReqAccountLogout, 0, sizeof(*ReqAccountLogout));
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
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(ReqAccountLogout->AccountID) ? sizeof(ReqAccountLogout->AccountID) - 1 : value.length();
							memcpy(ReqAccountLogout->AccountID, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqAccountLogoutField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqAccountLogoutPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqAccountLogoutPackage");
			return false;
		}
	}
	return true;
}
int ReqAccountLogoutPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqAccountLogout != nullptr)
	{
		memcpy(buff + offset, &ReqAccountLogoutField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqAccountLogout, sizeof(ReqAccountLogoutField));
		offset += sizeof(ReqAccountLogoutField);
	}
	return offset;
}
bool ReqAccountLogoutPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqAccountLogoutField::FieldID:
		{
			ReqAccountLogout = ::Allocate<ReqAccountLogoutField>();
			memcpy(ReqAccountLogout, buff + offset, sizeof(ReqAccountLogoutField));
			offset += sizeof(ReqAccountLogoutField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqAccountLogoutPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqAccountLogout != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqAccountLogout:AccountID:[%s]", ReqAccountLogout->AccountID);
	}
	return t_DataStringBuffer;
}
 
RspAccountLogoutPackage* RspAccountLogoutPackage::Allocate()
{
	return ::Allocate<RspAccountLogoutPackage>();
}
void RspAccountLogoutPackage::Free()
{
	Package::Free();
	if (RspAccountLogout != nullptr)
	{
		::Free<RspAccountLogoutField>(RspAccountLogout);
		RspAccountLogout = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspAccountLogoutPackage>::GetInstance().Free(this);
}
void RspAccountLogoutPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspAccountLogoutPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (RspAccountLogout != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, RspAccountLogoutField::FieldID);
		if (strlen(RspAccountLogout->AccountID) >= sizeof(RspAccountLogout->AccountID))
		{
			RspAccountLogout->AccountID[sizeof(RspAccountLogout->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, RspAccountLogout->AccountID);
		WriteHexString(ppos, Items::FieldEnd, RspAccountLogoutField::FieldID);
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
bool RspAccountLogoutPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case RspAccountLogoutField::FieldID:
			{
				RspAccountLogout = ::Allocate<RspAccountLogoutField>();
				memset(RspAccountLogout, 0, sizeof(*RspAccountLogout));
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
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(RspAccountLogout->AccountID) ? sizeof(RspAccountLogout->AccountID) - 1 : value.length();
							memcpy(RspAccountLogout->AccountID, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for RspAccountLogoutField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspAccountLogoutPackage FieldID:0x%X", fieldID);
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
						WriteLog(LogLevel::Warning, "GetNext Failed For RspAccountLogoutPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspAccountLogoutPackage");
			return false;
		}
	}
	return true;
}
int RspAccountLogoutPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (RspAccountLogout != nullptr)
	{
		memcpy(buff + offset, &RspAccountLogoutField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, RspAccountLogout, sizeof(RspAccountLogoutField));
		offset += sizeof(RspAccountLogoutField);
	}
	if (RspInfo != nullptr)
	{
		memcpy(buff + offset, &RspInfoField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, RspInfo, sizeof(RspInfoField));
		offset += sizeof(RspInfoField);
	}
	return offset;
}
bool RspAccountLogoutPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case RspAccountLogoutField::FieldID:
		{
			RspAccountLogout = ::Allocate<RspAccountLogoutField>();
			memcpy(RspAccountLogout, buff + offset, sizeof(RspAccountLogoutField));
			offset += sizeof(RspAccountLogoutField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ::Allocate<RspInfoField>();
			memcpy(RspInfo, buff + offset, sizeof(RspInfoField));
			offset += sizeof(RspInfoField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* RspAccountLogoutPackage::GetDebugString() const
{
	int offset = 0;
	if (RspAccountLogout != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspAccountLogout:AccountID:[%s]", RspAccountLogout->AccountID);
	}
	if (RspInfo != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
	return t_DataStringBuffer;
}
 
ReqQryOrderPackage* ReqQryOrderPackage::Allocate()
{
	return ::Allocate<ReqQryOrderPackage>();
}
void ReqQryOrderPackage::Free()
{
	Package::Free();
	if (ReqQryOrder != nullptr)
	{
		::Free<ReqQryOrderField>(ReqQryOrder);
		ReqQryOrder = nullptr;
	}
	MemCacheTemplateSingleton<ReqQryOrderPackage>::GetInstance().Free(this);
}
void ReqQryOrderPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqQryOrderPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqQryOrder != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqQryOrderField::FieldID);
		if (strlen(ReqQryOrder->AccountID) >= sizeof(ReqQryOrder->AccountID))
		{
			ReqQryOrder->AccountID[sizeof(ReqQryOrder->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, ReqQryOrder->AccountID);
		WriteHexString(ppos, Items::FieldEnd, ReqQryOrderField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqQryOrderPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqQryOrderField::FieldID:
			{
				ReqQryOrder = ::Allocate<ReqQryOrderField>();
				memset(ReqQryOrder, 0, sizeof(*ReqQryOrder));
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
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(ReqQryOrder->AccountID) ? sizeof(ReqQryOrder->AccountID) - 1 : value.length();
							memcpy(ReqQryOrder->AccountID, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqQryOrderField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqQryOrderPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqQryOrderPackage");
			return false;
		}
	}
	return true;
}
int ReqQryOrderPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqQryOrder != nullptr)
	{
		memcpy(buff + offset, &ReqQryOrderField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqQryOrder, sizeof(ReqQryOrderField));
		offset += sizeof(ReqQryOrderField);
	}
	return offset;
}
bool ReqQryOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqQryOrderField::FieldID:
		{
			ReqQryOrder = ::Allocate<ReqQryOrderField>();
			memcpy(ReqQryOrder, buff + offset, sizeof(ReqQryOrderField));
			offset += sizeof(ReqQryOrderField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqQryOrderPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqQryOrder != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqQryOrder:AccountID:[%s]", ReqQryOrder->AccountID);
	}
	return t_DataStringBuffer;
}
 
RspQryOrderPackage* RspQryOrderPackage::Allocate()
{
	return ::Allocate<RspQryOrderPackage>();
}
void RspQryOrderPackage::Free()
{
	Package::Free();
	if (Order != nullptr)
	{
		::Free<OrderField>(Order);
		Order = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspQryOrderPackage>::GetInstance().Free(this);
}
void RspQryOrderPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspQryOrderPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (Order != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, OrderField::FieldID);
		if (strlen(Order->TradingDay) >= sizeof(Order->TradingDay))
		{
			Order->TradingDay[sizeof(Order->TradingDay) - 1] = 0;
		}
		WriteString(ppos, Items::TradingDay, Order->TradingDay);
		if (strlen(Order->AccountID) >= sizeof(Order->AccountID))
		{
			Order->AccountID[sizeof(Order->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, Order->AccountID);
		if (strlen(Order->ExchangeID) >= sizeof(Order->ExchangeID))
		{
			Order->ExchangeID[sizeof(Order->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, Order->ExchangeID);
		if (strlen(Order->InstrumentID) >= sizeof(Order->InstrumentID))
		{
			Order->InstrumentID[sizeof(Order->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, Order->InstrumentID);
		WriteString(ppos, Items::ProductClass, (int)Order->ProductClass);
		WriteString(ppos, Items::OrderID, Order->OrderID);
		if (strlen(Order->OrderSysID) >= sizeof(Order->OrderSysID))
		{
			Order->OrderSysID[sizeof(Order->OrderSysID) - 1] = 0;
		}
		WriteString(ppos, Items::OrderSysID, Order->OrderSysID);
		WriteString(ppos, Items::Direction, (int)Order->Direction);
		WriteString(ppos, Items::OffsetFlag, (int)Order->OffsetFlag);
		WriteString(ppos, Items::OrderPriceType, (int)Order->OrderPriceType);
		WriteString(ppos, Items::Price, Order->Price);
		WriteString(ppos, Items::Volume, Order->Volume);
		WriteString(ppos, Items::VolumeTotal, Order->VolumeTotal);
		WriteString(ppos, Items::VolumeTraded, Order->VolumeTraded);
		WriteString(ppos, Items::VolumeMultiple, Order->VolumeMultiple);
		WriteString(ppos, Items::OrderStatus, (int)Order->OrderStatus);
		if (strlen(Order->OrderDate) >= sizeof(Order->OrderDate))
		{
			Order->OrderDate[sizeof(Order->OrderDate) - 1] = 0;
		}
		WriteString(ppos, Items::OrderDate, Order->OrderDate);
		if (strlen(Order->OrderTime) >= sizeof(Order->OrderTime))
		{
			Order->OrderTime[sizeof(Order->OrderTime) - 1] = 0;
		}
		WriteString(ppos, Items::OrderTime, Order->OrderTime);
		if (strlen(Order->CancelDate) >= sizeof(Order->CancelDate))
		{
			Order->CancelDate[sizeof(Order->CancelDate) - 1] = 0;
		}
		WriteString(ppos, Items::CancelDate, Order->CancelDate);
		if (strlen(Order->CancelTime) >= sizeof(Order->CancelTime))
		{
			Order->CancelTime[sizeof(Order->CancelTime) - 1] = 0;
		}
		WriteString(ppos, Items::CancelTime, Order->CancelTime);
		WriteString(ppos, Items::SessionID, Order->SessionID);
		WriteString(ppos, Items::ClientOrderID, Order->ClientOrderID);
		WriteString(ppos, Items::RequestID, Order->RequestID);
		WriteString(ppos, Items::FrozenCash, Order->FrozenCash);
		WriteString(ppos, Items::FrozenMargin, Order->FrozenMargin);
		WriteString(ppos, Items::FrozenCommission, Order->FrozenCommission);
		WriteHexString(ppos, Items::FieldEnd, OrderField::FieldID);
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
bool RspQryOrderPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case OrderField::FieldID:
			{
				Order = ::Allocate<OrderField>();
				memset(Order, 0, sizeof(*Order));
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
							size_t len = value.length() >= sizeof(Order->TradingDay) ? sizeof(Order->TradingDay) - 1 : value.length();
							memcpy(Order->TradingDay, value.c_str(), len);
							break;
						}
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(Order->AccountID) ? sizeof(Order->AccountID) - 1 : value.length();
							memcpy(Order->AccountID, value.c_str(), len);
							break;
						}
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(Order->ExchangeID) ? sizeof(Order->ExchangeID) - 1 : value.length();
							memcpy(Order->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(Order->InstrumentID) ? sizeof(Order->InstrumentID) - 1 : value.length();
							memcpy(Order->InstrumentID, value.c_str(), len);
							break;
						}
						case Items::ProductClass:
						{
							Order->ProductClass = (ProductClassType)(atoi(value.c_str()));
							break;
						}
						case Items::OrderID:
						{
							Order->OrderID = atoi(value.c_str());
							break;
						}
						case Items::OrderSysID:
						{
							size_t len = value.length() >= sizeof(Order->OrderSysID) ? sizeof(Order->OrderSysID) - 1 : value.length();
							memcpy(Order->OrderSysID, value.c_str(), len);
							break;
						}
						case Items::Direction:
						{
							Order->Direction = (DirectionType)(atoi(value.c_str()));
							break;
						}
						case Items::OffsetFlag:
						{
							Order->OffsetFlag = (OffsetFlagType)(atoi(value.c_str()));
							break;
						}
						case Items::OrderPriceType:
						{
							Order->OrderPriceType = (OrderPriceTypeType)(atoi(value.c_str()));
							break;
						}
						case Items::Price:
						{
							Order->Price = atof(value.c_str());
							break;
						}
						case Items::Volume:
						{
							Order->Volume = atoll(value.c_str());
							break;
						}
						case Items::VolumeTotal:
						{
							Order->VolumeTotal = atoll(value.c_str());
							break;
						}
						case Items::VolumeTraded:
						{
							Order->VolumeTraded = atoll(value.c_str());
							break;
						}
						case Items::VolumeMultiple:
						{
							Order->VolumeMultiple = atoi(value.c_str());
							break;
						}
						case Items::OrderStatus:
						{
							Order->OrderStatus = (OrderStatusType)(atoi(value.c_str()));
							break;
						}
						case Items::OrderDate:
						{
							size_t len = value.length() >= sizeof(Order->OrderDate) ? sizeof(Order->OrderDate) - 1 : value.length();
							memcpy(Order->OrderDate, value.c_str(), len);
							break;
						}
						case Items::OrderTime:
						{
							size_t len = value.length() >= sizeof(Order->OrderTime) ? sizeof(Order->OrderTime) - 1 : value.length();
							memcpy(Order->OrderTime, value.c_str(), len);
							break;
						}
						case Items::CancelDate:
						{
							size_t len = value.length() >= sizeof(Order->CancelDate) ? sizeof(Order->CancelDate) - 1 : value.length();
							memcpy(Order->CancelDate, value.c_str(), len);
							break;
						}
						case Items::CancelTime:
						{
							size_t len = value.length() >= sizeof(Order->CancelTime) ? sizeof(Order->CancelTime) - 1 : value.length();
							memcpy(Order->CancelTime, value.c_str(), len);
							break;
						}
						case Items::SessionID:
						{
							Order->SessionID = atoll(value.c_str());
							break;
						}
						case Items::ClientOrderID:
						{
							Order->ClientOrderID = atoi(value.c_str());
							break;
						}
						case Items::RequestID:
						{
							Order->RequestID = atoi(value.c_str());
							break;
						}
						case Items::FrozenCash:
						{
							Order->FrozenCash = atof(value.c_str());
							break;
						}
						case Items::FrozenMargin:
						{
							Order->FrozenMargin = atof(value.c_str());
							break;
						}
						case Items::FrozenCommission:
						{
							Order->FrozenCommission = atof(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for OrderField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryOrderPackage FieldID:0x%X", fieldID);
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
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryOrderPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspQryOrderPackage");
			return false;
		}
	}
	return true;
}
int RspQryOrderPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (Order != nullptr)
	{
		memcpy(buff + offset, &OrderField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, Order, sizeof(OrderField));
		offset += sizeof(OrderField);
	}
	if (RspInfo != nullptr)
	{
		memcpy(buff + offset, &RspInfoField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, RspInfo, sizeof(RspInfoField));
		offset += sizeof(RspInfoField);
	}
	return offset;
}
bool RspQryOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case OrderField::FieldID:
		{
			Order = ::Allocate<OrderField>();
			memcpy(Order, buff + offset, sizeof(OrderField));
			offset += sizeof(OrderField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ::Allocate<RspInfoField>();
			memcpy(RspInfo, buff + offset, sizeof(RspInfoField));
			offset += sizeof(RspInfoField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* RspQryOrderPackage::GetDebugString() const
{
	int offset = 0;
	if (Order != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "Order:TradingDay:[%s], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], OrderSysID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], VolumeTotal:[%lld], VolumeTraded:[%lld], VolumeMultiple:[%d], OrderStatus:[%d], OrderDate:[%s], OrderTime:[%s], CancelDate:[%s], CancelTime:[%s], SessionID:[%lld], ClientOrderID:[%d], RequestID:[%d], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f]", Order->TradingDay, Order->AccountID, Order->ExchangeID, Order->InstrumentID, (int)Order->ProductClass, Order->OrderID, Order->OrderSysID, (int)Order->Direction, (int)Order->OffsetFlag, (int)Order->OrderPriceType, Order->Price, Order->Volume, Order->VolumeTotal, Order->VolumeTraded, Order->VolumeMultiple, (int)Order->OrderStatus, Order->OrderDate, Order->OrderTime, Order->CancelDate, Order->CancelTime, Order->SessionID, Order->ClientOrderID, Order->RequestID, Order->FrozenCash, Order->FrozenMargin, Order->FrozenCommission);
	}
	if (RspInfo != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
	return t_DataStringBuffer;
}
 
ReqQryTradePackage* ReqQryTradePackage::Allocate()
{
	return ::Allocate<ReqQryTradePackage>();
}
void ReqQryTradePackage::Free()
{
	Package::Free();
	if (ReqQryTrade != nullptr)
	{
		::Free<ReqQryTradeField>(ReqQryTrade);
		ReqQryTrade = nullptr;
	}
	MemCacheTemplateSingleton<ReqQryTradePackage>::GetInstance().Free(this);
}
void ReqQryTradePackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqQryTradePackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqQryTrade != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqQryTradeField::FieldID);
		if (strlen(ReqQryTrade->AccountID) >= sizeof(ReqQryTrade->AccountID))
		{
			ReqQryTrade->AccountID[sizeof(ReqQryTrade->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, ReqQryTrade->AccountID);
		WriteHexString(ppos, Items::FieldEnd, ReqQryTradeField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqQryTradePackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqQryTradeField::FieldID:
			{
				ReqQryTrade = ::Allocate<ReqQryTradeField>();
				memset(ReqQryTrade, 0, sizeof(*ReqQryTrade));
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
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(ReqQryTrade->AccountID) ? sizeof(ReqQryTrade->AccountID) - 1 : value.length();
							memcpy(ReqQryTrade->AccountID, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqQryTradeField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqQryTradePackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqQryTradePackage");
			return false;
		}
	}
	return true;
}
int ReqQryTradePackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqQryTrade != nullptr)
	{
		memcpy(buff + offset, &ReqQryTradeField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqQryTrade, sizeof(ReqQryTradeField));
		offset += sizeof(ReqQryTradeField);
	}
	return offset;
}
bool ReqQryTradePackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqQryTradeField::FieldID:
		{
			ReqQryTrade = ::Allocate<ReqQryTradeField>();
			memcpy(ReqQryTrade, buff + offset, sizeof(ReqQryTradeField));
			offset += sizeof(ReqQryTradeField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqQryTradePackage::GetDebugString() const
{
	int offset = 0;
	if (ReqQryTrade != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqQryTrade:AccountID:[%s]", ReqQryTrade->AccountID);
	}
	return t_DataStringBuffer;
}
 
RspQryTradePackage* RspQryTradePackage::Allocate()
{
	return ::Allocate<RspQryTradePackage>();
}
void RspQryTradePackage::Free()
{
	Package::Free();
	if (Trade != nullptr)
	{
		::Free<TradeField>(Trade);
		Trade = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspQryTradePackage>::GetInstance().Free(this);
}
void RspQryTradePackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspQryTradePackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (Trade != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, TradeField::FieldID);
		if (strlen(Trade->TradingDay) >= sizeof(Trade->TradingDay))
		{
			Trade->TradingDay[sizeof(Trade->TradingDay) - 1] = 0;
		}
		WriteString(ppos, Items::TradingDay, Trade->TradingDay);
		if (strlen(Trade->AccountID) >= sizeof(Trade->AccountID))
		{
			Trade->AccountID[sizeof(Trade->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, Trade->AccountID);
		if (strlen(Trade->ExchangeID) >= sizeof(Trade->ExchangeID))
		{
			Trade->ExchangeID[sizeof(Trade->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, Trade->ExchangeID);
		if (strlen(Trade->InstrumentID) >= sizeof(Trade->InstrumentID))
		{
			Trade->InstrumentID[sizeof(Trade->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, Trade->InstrumentID);
		WriteString(ppos, Items::ProductClass, (int)Trade->ProductClass);
		WriteString(ppos, Items::OrderID, Trade->OrderID);
		if (strlen(Trade->OrderSysID) >= sizeof(Trade->OrderSysID))
		{
			Trade->OrderSysID[sizeof(Trade->OrderSysID) - 1] = 0;
		}
		WriteString(ppos, Items::OrderSysID, Trade->OrderSysID);
		if (strlen(Trade->TradeID) >= sizeof(Trade->TradeID))
		{
			Trade->TradeID[sizeof(Trade->TradeID) - 1] = 0;
		}
		WriteString(ppos, Items::TradeID, Trade->TradeID);
		WriteString(ppos, Items::Direction, (int)Trade->Direction);
		WriteString(ppos, Items::OffsetFlag, (int)Trade->OffsetFlag);
		WriteString(ppos, Items::Price, Trade->Price);
		WriteString(ppos, Items::Volume, Trade->Volume);
		WriteString(ppos, Items::VolumeMultiple, Trade->VolumeMultiple);
		WriteString(ppos, Items::TradeAmount, Trade->TradeAmount);
		WriteString(ppos, Items::Commission, Trade->Commission);
		if (strlen(Trade->TradeDate) >= sizeof(Trade->TradeDate))
		{
			Trade->TradeDate[sizeof(Trade->TradeDate) - 1] = 0;
		}
		WriteString(ppos, Items::TradeDate, Trade->TradeDate);
		if (strlen(Trade->TradeTime) >= sizeof(Trade->TradeTime))
		{
			Trade->TradeTime[sizeof(Trade->TradeTime) - 1] = 0;
		}
		WriteString(ppos, Items::TradeTime, Trade->TradeTime);
		WriteHexString(ppos, Items::FieldEnd, TradeField::FieldID);
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
bool RspQryTradePackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case TradeField::FieldID:
			{
				Trade = ::Allocate<TradeField>();
				memset(Trade, 0, sizeof(*Trade));
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
							size_t len = value.length() >= sizeof(Trade->TradingDay) ? sizeof(Trade->TradingDay) - 1 : value.length();
							memcpy(Trade->TradingDay, value.c_str(), len);
							break;
						}
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(Trade->AccountID) ? sizeof(Trade->AccountID) - 1 : value.length();
							memcpy(Trade->AccountID, value.c_str(), len);
							break;
						}
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(Trade->ExchangeID) ? sizeof(Trade->ExchangeID) - 1 : value.length();
							memcpy(Trade->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(Trade->InstrumentID) ? sizeof(Trade->InstrumentID) - 1 : value.length();
							memcpy(Trade->InstrumentID, value.c_str(), len);
							break;
						}
						case Items::ProductClass:
						{
							Trade->ProductClass = (ProductClassType)(atoi(value.c_str()));
							break;
						}
						case Items::OrderID:
						{
							Trade->OrderID = atoi(value.c_str());
							break;
						}
						case Items::OrderSysID:
						{
							size_t len = value.length() >= sizeof(Trade->OrderSysID) ? sizeof(Trade->OrderSysID) - 1 : value.length();
							memcpy(Trade->OrderSysID, value.c_str(), len);
							break;
						}
						case Items::TradeID:
						{
							size_t len = value.length() >= sizeof(Trade->TradeID) ? sizeof(Trade->TradeID) - 1 : value.length();
							memcpy(Trade->TradeID, value.c_str(), len);
							break;
						}
						case Items::Direction:
						{
							Trade->Direction = (DirectionType)(atoi(value.c_str()));
							break;
						}
						case Items::OffsetFlag:
						{
							Trade->OffsetFlag = (OffsetFlagType)(atoi(value.c_str()));
							break;
						}
						case Items::Price:
						{
							Trade->Price = atof(value.c_str());
							break;
						}
						case Items::Volume:
						{
							Trade->Volume = atoll(value.c_str());
							break;
						}
						case Items::VolumeMultiple:
						{
							Trade->VolumeMultiple = atoi(value.c_str());
							break;
						}
						case Items::TradeAmount:
						{
							Trade->TradeAmount = atof(value.c_str());
							break;
						}
						case Items::Commission:
						{
							Trade->Commission = atof(value.c_str());
							break;
						}
						case Items::TradeDate:
						{
							size_t len = value.length() >= sizeof(Trade->TradeDate) ? sizeof(Trade->TradeDate) - 1 : value.length();
							memcpy(Trade->TradeDate, value.c_str(), len);
							break;
						}
						case Items::TradeTime:
						{
							size_t len = value.length() >= sizeof(Trade->TradeTime) ? sizeof(Trade->TradeTime) - 1 : value.length();
							memcpy(Trade->TradeTime, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for TradeField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryTradePackage FieldID:0x%X", fieldID);
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
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryTradePackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspQryTradePackage");
			return false;
		}
	}
	return true;
}
int RspQryTradePackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (Trade != nullptr)
	{
		memcpy(buff + offset, &TradeField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, Trade, sizeof(TradeField));
		offset += sizeof(TradeField);
	}
	if (RspInfo != nullptr)
	{
		memcpy(buff + offset, &RspInfoField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, RspInfo, sizeof(RspInfoField));
		offset += sizeof(RspInfoField);
	}
	return offset;
}
bool RspQryTradePackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case TradeField::FieldID:
		{
			Trade = ::Allocate<TradeField>();
			memcpy(Trade, buff + offset, sizeof(TradeField));
			offset += sizeof(TradeField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ::Allocate<RspInfoField>();
			memcpy(RspInfo, buff + offset, sizeof(RspInfoField));
			offset += sizeof(RspInfoField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* RspQryTradePackage::GetDebugString() const
{
	int offset = 0;
	if (Trade != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "Trade:TradingDay:[%s], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], OrderSysID:[%s], TradeID:[%s], Direction:[%d], OffsetFlag:[%d], Price:[%f], Volume:[%lld], VolumeMultiple:[%d], TradeAmount:[%f], Commission:[%f], TradeDate:[%s], TradeTime:[%s]", Trade->TradingDay, Trade->AccountID, Trade->ExchangeID, Trade->InstrumentID, (int)Trade->ProductClass, Trade->OrderID, Trade->OrderSysID, Trade->TradeID, (int)Trade->Direction, (int)Trade->OffsetFlag, Trade->Price, Trade->Volume, Trade->VolumeMultiple, Trade->TradeAmount, Trade->Commission, Trade->TradeDate, Trade->TradeTime);
	}
	if (RspInfo != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
	return t_DataStringBuffer;
}
 
ReqQryInstrumentPackage* ReqQryInstrumentPackage::Allocate()
{
	return ::Allocate<ReqQryInstrumentPackage>();
}
void ReqQryInstrumentPackage::Free()
{
	Package::Free();
	if (ReqQryInstrument != nullptr)
	{
		::Free<ReqQryInstrumentField>(ReqQryInstrument);
		ReqQryInstrument = nullptr;
	}
	MemCacheTemplateSingleton<ReqQryInstrumentPackage>::GetInstance().Free(this);
}
void ReqQryInstrumentPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqQryInstrumentPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqQryInstrument != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqQryInstrumentField::FieldID);
		if (strlen(ReqQryInstrument->ExchangeID) >= sizeof(ReqQryInstrument->ExchangeID))
		{
			ReqQryInstrument->ExchangeID[sizeof(ReqQryInstrument->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, ReqQryInstrument->ExchangeID);
		if (strlen(ReqQryInstrument->InstrumentID) >= sizeof(ReqQryInstrument->InstrumentID))
		{
			ReqQryInstrument->InstrumentID[sizeof(ReqQryInstrument->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, ReqQryInstrument->InstrumentID);
		WriteHexString(ppos, Items::FieldEnd, ReqQryInstrumentField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqQryInstrumentPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqQryInstrumentField::FieldID:
			{
				ReqQryInstrument = ::Allocate<ReqQryInstrumentField>();
				memset(ReqQryInstrument, 0, sizeof(*ReqQryInstrument));
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
							size_t len = value.length() >= sizeof(ReqQryInstrument->ExchangeID) ? sizeof(ReqQryInstrument->ExchangeID) - 1 : value.length();
							memcpy(ReqQryInstrument->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(ReqQryInstrument->InstrumentID) ? sizeof(ReqQryInstrument->InstrumentID) - 1 : value.length();
							memcpy(ReqQryInstrument->InstrumentID, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqQryInstrumentField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqQryInstrumentPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqQryInstrumentPackage");
			return false;
		}
	}
	return true;
}
int ReqQryInstrumentPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqQryInstrument != nullptr)
	{
		memcpy(buff + offset, &ReqQryInstrumentField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqQryInstrument, sizeof(ReqQryInstrumentField));
		offset += sizeof(ReqQryInstrumentField);
	}
	return offset;
}
bool ReqQryInstrumentPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqQryInstrumentField::FieldID:
		{
			ReqQryInstrument = ::Allocate<ReqQryInstrumentField>();
			memcpy(ReqQryInstrument, buff + offset, sizeof(ReqQryInstrumentField));
			offset += sizeof(ReqQryInstrumentField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqQryInstrumentPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqQryInstrument != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqQryInstrument:ExchangeID:[%s], InstrumentID:[%s]", ReqQryInstrument->ExchangeID, ReqQryInstrument->InstrumentID);
	}
	return t_DataStringBuffer;
}
 
RspQryInstrumentPackage* RspQryInstrumentPackage::Allocate()
{
	return ::Allocate<RspQryInstrumentPackage>();
}
void RspQryInstrumentPackage::Free()
{
	Package::Free();
	if (Instrument != nullptr)
	{
		::Free<InstrumentField>(Instrument);
		Instrument = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspQryInstrumentPackage>::GetInstance().Free(this);
}
void RspQryInstrumentPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspQryInstrumentPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (Instrument != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, InstrumentField::FieldID);
		if (strlen(Instrument->ExchangeID) >= sizeof(Instrument->ExchangeID))
		{
			Instrument->ExchangeID[sizeof(Instrument->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, Instrument->ExchangeID);
		if (strlen(Instrument->InstrumentID) >= sizeof(Instrument->InstrumentID))
		{
			Instrument->InstrumentID[sizeof(Instrument->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, Instrument->InstrumentID);
		if (strlen(Instrument->ExchangeInstID) >= sizeof(Instrument->ExchangeInstID))
		{
			Instrument->ExchangeInstID[sizeof(Instrument->ExchangeInstID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeInstID, Instrument->ExchangeInstID);
		if (strlen(Instrument->InstrumentName) >= sizeof(Instrument->InstrumentName))
		{
			Instrument->InstrumentName[sizeof(Instrument->InstrumentName) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentName, Instrument->InstrumentName);
		if (strlen(Instrument->ProductID) >= sizeof(Instrument->ProductID))
		{
			Instrument->ProductID[sizeof(Instrument->ProductID) - 1] = 0;
		}
		WriteString(ppos, Items::ProductID, Instrument->ProductID);
		WriteString(ppos, Items::ProductClass, (int)Instrument->ProductClass);
		WriteString(ppos, Items::VolumeMultiple, Instrument->VolumeMultiple);
		WriteString(ppos, Items::PriceTick, Instrument->PriceTick);
		WriteString(ppos, Items::MaxMarketOrderVolume, Instrument->MaxMarketOrderVolume);
		WriteString(ppos, Items::MinMarketOrderVolume, Instrument->MinMarketOrderVolume);
		WriteString(ppos, Items::MaxLimitOrderVolume, Instrument->MaxLimitOrderVolume);
		WriteString(ppos, Items::MinLimitOrderVolume, Instrument->MinLimitOrderVolume);
		if (strlen(Instrument->SessionName) >= sizeof(Instrument->SessionName))
		{
			Instrument->SessionName[sizeof(Instrument->SessionName) - 1] = 0;
		}
		WriteString(ppos, Items::SessionName, Instrument->SessionName);
		WriteHexString(ppos, Items::FieldEnd, InstrumentField::FieldID);
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
bool RspQryInstrumentPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case InstrumentField::FieldID:
			{
				Instrument = ::Allocate<InstrumentField>();
				memset(Instrument, 0, sizeof(*Instrument));
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
							size_t len = value.length() >= sizeof(Instrument->ExchangeID) ? sizeof(Instrument->ExchangeID) - 1 : value.length();
							memcpy(Instrument->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(Instrument->InstrumentID) ? sizeof(Instrument->InstrumentID) - 1 : value.length();
							memcpy(Instrument->InstrumentID, value.c_str(), len);
							break;
						}
						case Items::ExchangeInstID:
						{
							size_t len = value.length() >= sizeof(Instrument->ExchangeInstID) ? sizeof(Instrument->ExchangeInstID) - 1 : value.length();
							memcpy(Instrument->ExchangeInstID, value.c_str(), len);
							break;
						}
						case Items::InstrumentName:
						{
							size_t len = value.length() >= sizeof(Instrument->InstrumentName) ? sizeof(Instrument->InstrumentName) - 1 : value.length();
							memcpy(Instrument->InstrumentName, value.c_str(), len);
							break;
						}
						case Items::ProductID:
						{
							size_t len = value.length() >= sizeof(Instrument->ProductID) ? sizeof(Instrument->ProductID) - 1 : value.length();
							memcpy(Instrument->ProductID, value.c_str(), len);
							break;
						}
						case Items::ProductClass:
						{
							Instrument->ProductClass = (ProductClassType)(atoi(value.c_str()));
							break;
						}
						case Items::VolumeMultiple:
						{
							Instrument->VolumeMultiple = atoi(value.c_str());
							break;
						}
						case Items::PriceTick:
						{
							Instrument->PriceTick = atof(value.c_str());
							break;
						}
						case Items::MaxMarketOrderVolume:
						{
							Instrument->MaxMarketOrderVolume = atoll(value.c_str());
							break;
						}
						case Items::MinMarketOrderVolume:
						{
							Instrument->MinMarketOrderVolume = atoll(value.c_str());
							break;
						}
						case Items::MaxLimitOrderVolume:
						{
							Instrument->MaxLimitOrderVolume = atoll(value.c_str());
							break;
						}
						case Items::MinLimitOrderVolume:
						{
							Instrument->MinLimitOrderVolume = atoll(value.c_str());
							break;
						}
						case Items::SessionName:
						{
							size_t len = value.length() >= sizeof(Instrument->SessionName) ? sizeof(Instrument->SessionName) - 1 : value.length();
							memcpy(Instrument->SessionName, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for InstrumentField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryInstrumentPackage FieldID:0x%X", fieldID);
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
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryInstrumentPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspQryInstrumentPackage");
			return false;
		}
	}
	return true;
}
int RspQryInstrumentPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (Instrument != nullptr)
	{
		memcpy(buff + offset, &InstrumentField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, Instrument, sizeof(InstrumentField));
		offset += sizeof(InstrumentField);
	}
	if (RspInfo != nullptr)
	{
		memcpy(buff + offset, &RspInfoField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, RspInfo, sizeof(RspInfoField));
		offset += sizeof(RspInfoField);
	}
	return offset;
}
bool RspQryInstrumentPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case InstrumentField::FieldID:
		{
			Instrument = ::Allocate<InstrumentField>();
			memcpy(Instrument, buff + offset, sizeof(InstrumentField));
			offset += sizeof(InstrumentField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ::Allocate<RspInfoField>();
			memcpy(RspInfo, buff + offset, sizeof(RspInfoField));
			offset += sizeof(RspInfoField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* RspQryInstrumentPackage::GetDebugString() const
{
	int offset = 0;
	if (Instrument != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "Instrument:ExchangeID:[%s], InstrumentID:[%s], ExchangeInstID:[%s], InstrumentName:[%s], ProductID:[%s], ProductClass:[%d], VolumeMultiple:[%d], PriceTick:[%f], MaxMarketOrderVolume:[%lld], MinMarketOrderVolume:[%lld], MaxLimitOrderVolume:[%lld], MinLimitOrderVolume:[%lld], SessionName:[%s]", Instrument->ExchangeID, Instrument->InstrumentID, Instrument->ExchangeInstID, Instrument->InstrumentName, Instrument->ProductID, (int)Instrument->ProductClass, Instrument->VolumeMultiple, Instrument->PriceTick, Instrument->MaxMarketOrderVolume, Instrument->MinMarketOrderVolume, Instrument->MaxLimitOrderVolume, Instrument->MinLimitOrderVolume, Instrument->SessionName);
	}
	if (RspInfo != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
	return t_DataStringBuffer;
}
 
ReqInsertOrderPackage* ReqInsertOrderPackage::Allocate()
{
	return ::Allocate<ReqInsertOrderPackage>();
}
void ReqInsertOrderPackage::Free()
{
	Package::Free();
	if (ReqInsertOrder != nullptr)
	{
		::Free<ReqInsertOrderField>(ReqInsertOrder);
		ReqInsertOrder = nullptr;
	}
	MemCacheTemplateSingleton<ReqInsertOrderPackage>::GetInstance().Free(this);
}
void ReqInsertOrderPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqInsertOrderPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqInsertOrder != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqInsertOrderField::FieldID);
		if (strlen(ReqInsertOrder->AccountID) >= sizeof(ReqInsertOrder->AccountID))
		{
			ReqInsertOrder->AccountID[sizeof(ReqInsertOrder->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, ReqInsertOrder->AccountID);
		if (strlen(ReqInsertOrder->ExchangeID) >= sizeof(ReqInsertOrder->ExchangeID))
		{
			ReqInsertOrder->ExchangeID[sizeof(ReqInsertOrder->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, ReqInsertOrder->ExchangeID);
		if (strlen(ReqInsertOrder->InstrumentID) >= sizeof(ReqInsertOrder->InstrumentID))
		{
			ReqInsertOrder->InstrumentID[sizeof(ReqInsertOrder->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, ReqInsertOrder->InstrumentID);
		WriteString(ppos, Items::Direction, (int)ReqInsertOrder->Direction);
		WriteString(ppos, Items::OffsetFlag, (int)ReqInsertOrder->OffsetFlag);
		WriteString(ppos, Items::OrderPriceType, (int)ReqInsertOrder->OrderPriceType);
		WriteString(ppos, Items::Price, ReqInsertOrder->Price);
		WriteString(ppos, Items::Volume, ReqInsertOrder->Volume);
		WriteString(ppos, Items::ClientOrderID, ReqInsertOrder->ClientOrderID);
		WriteHexString(ppos, Items::FieldEnd, ReqInsertOrderField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqInsertOrderPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqInsertOrderField::FieldID:
			{
				ReqInsertOrder = ::Allocate<ReqInsertOrderField>();
				memset(ReqInsertOrder, 0, sizeof(*ReqInsertOrder));
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
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(ReqInsertOrder->AccountID) ? sizeof(ReqInsertOrder->AccountID) - 1 : value.length();
							memcpy(ReqInsertOrder->AccountID, value.c_str(), len);
							break;
						}
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(ReqInsertOrder->ExchangeID) ? sizeof(ReqInsertOrder->ExchangeID) - 1 : value.length();
							memcpy(ReqInsertOrder->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(ReqInsertOrder->InstrumentID) ? sizeof(ReqInsertOrder->InstrumentID) - 1 : value.length();
							memcpy(ReqInsertOrder->InstrumentID, value.c_str(), len);
							break;
						}
						case Items::Direction:
						{
							ReqInsertOrder->Direction = (DirectionType)(atoi(value.c_str()));
							break;
						}
						case Items::OffsetFlag:
						{
							ReqInsertOrder->OffsetFlag = (OffsetFlagType)(atoi(value.c_str()));
							break;
						}
						case Items::OrderPriceType:
						{
							ReqInsertOrder->OrderPriceType = (OrderPriceTypeType)(atoi(value.c_str()));
							break;
						}
						case Items::Price:
						{
							ReqInsertOrder->Price = atof(value.c_str());
							break;
						}
						case Items::Volume:
						{
							ReqInsertOrder->Volume = atoll(value.c_str());
							break;
						}
						case Items::ClientOrderID:
						{
							ReqInsertOrder->ClientOrderID = atoi(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqInsertOrderField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqInsertOrderPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqInsertOrderPackage");
			return false;
		}
	}
	return true;
}
int ReqInsertOrderPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqInsertOrder != nullptr)
	{
		memcpy(buff + offset, &ReqInsertOrderField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqInsertOrder, sizeof(ReqInsertOrderField));
		offset += sizeof(ReqInsertOrderField);
	}
	return offset;
}
bool ReqInsertOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqInsertOrderField::FieldID:
		{
			ReqInsertOrder = ::Allocate<ReqInsertOrderField>();
			memcpy(ReqInsertOrder, buff + offset, sizeof(ReqInsertOrderField));
			offset += sizeof(ReqInsertOrderField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqInsertOrderPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqInsertOrder != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqInsertOrder:AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], ClientOrderID:[%d]", ReqInsertOrder->AccountID, ReqInsertOrder->ExchangeID, ReqInsertOrder->InstrumentID, (int)ReqInsertOrder->Direction, (int)ReqInsertOrder->OffsetFlag, (int)ReqInsertOrder->OrderPriceType, ReqInsertOrder->Price, ReqInsertOrder->Volume, ReqInsertOrder->ClientOrderID);
	}
	return t_DataStringBuffer;
}
 
RspInsertOrderPackage* RspInsertOrderPackage::Allocate()
{
	return ::Allocate<RspInsertOrderPackage>();
}
void RspInsertOrderPackage::Free()
{
	Package::Free();
	if (ReqInsertOrder != nullptr)
	{
		::Free<ReqInsertOrderField>(ReqInsertOrder);
		ReqInsertOrder = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspInsertOrderPackage>::GetInstance().Free(this);
}
void RspInsertOrderPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspInsertOrderPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqInsertOrder != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqInsertOrderField::FieldID);
		if (strlen(ReqInsertOrder->AccountID) >= sizeof(ReqInsertOrder->AccountID))
		{
			ReqInsertOrder->AccountID[sizeof(ReqInsertOrder->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, ReqInsertOrder->AccountID);
		if (strlen(ReqInsertOrder->ExchangeID) >= sizeof(ReqInsertOrder->ExchangeID))
		{
			ReqInsertOrder->ExchangeID[sizeof(ReqInsertOrder->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, ReqInsertOrder->ExchangeID);
		if (strlen(ReqInsertOrder->InstrumentID) >= sizeof(ReqInsertOrder->InstrumentID))
		{
			ReqInsertOrder->InstrumentID[sizeof(ReqInsertOrder->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, ReqInsertOrder->InstrumentID);
		WriteString(ppos, Items::Direction, (int)ReqInsertOrder->Direction);
		WriteString(ppos, Items::OffsetFlag, (int)ReqInsertOrder->OffsetFlag);
		WriteString(ppos, Items::OrderPriceType, (int)ReqInsertOrder->OrderPriceType);
		WriteString(ppos, Items::Price, ReqInsertOrder->Price);
		WriteString(ppos, Items::Volume, ReqInsertOrder->Volume);
		WriteString(ppos, Items::ClientOrderID, ReqInsertOrder->ClientOrderID);
		WriteHexString(ppos, Items::FieldEnd, ReqInsertOrderField::FieldID);
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
bool RspInsertOrderPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqInsertOrderField::FieldID:
			{
				ReqInsertOrder = ::Allocate<ReqInsertOrderField>();
				memset(ReqInsertOrder, 0, sizeof(*ReqInsertOrder));
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
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(ReqInsertOrder->AccountID) ? sizeof(ReqInsertOrder->AccountID) - 1 : value.length();
							memcpy(ReqInsertOrder->AccountID, value.c_str(), len);
							break;
						}
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(ReqInsertOrder->ExchangeID) ? sizeof(ReqInsertOrder->ExchangeID) - 1 : value.length();
							memcpy(ReqInsertOrder->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(ReqInsertOrder->InstrumentID) ? sizeof(ReqInsertOrder->InstrumentID) - 1 : value.length();
							memcpy(ReqInsertOrder->InstrumentID, value.c_str(), len);
							break;
						}
						case Items::Direction:
						{
							ReqInsertOrder->Direction = (DirectionType)(atoi(value.c_str()));
							break;
						}
						case Items::OffsetFlag:
						{
							ReqInsertOrder->OffsetFlag = (OffsetFlagType)(atoi(value.c_str()));
							break;
						}
						case Items::OrderPriceType:
						{
							ReqInsertOrder->OrderPriceType = (OrderPriceTypeType)(atoi(value.c_str()));
							break;
						}
						case Items::Price:
						{
							ReqInsertOrder->Price = atof(value.c_str());
							break;
						}
						case Items::Volume:
						{
							ReqInsertOrder->Volume = atoll(value.c_str());
							break;
						}
						case Items::ClientOrderID:
						{
							ReqInsertOrder->ClientOrderID = atoi(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqInsertOrderField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspInsertOrderPackage FieldID:0x%X", fieldID);
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
						WriteLog(LogLevel::Warning, "GetNext Failed For RspInsertOrderPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspInsertOrderPackage");
			return false;
		}
	}
	return true;
}
int RspInsertOrderPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqInsertOrder != nullptr)
	{
		memcpy(buff + offset, &ReqInsertOrderField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqInsertOrder, sizeof(ReqInsertOrderField));
		offset += sizeof(ReqInsertOrderField);
	}
	if (RspInfo != nullptr)
	{
		memcpy(buff + offset, &RspInfoField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, RspInfo, sizeof(RspInfoField));
		offset += sizeof(RspInfoField);
	}
	return offset;
}
bool RspInsertOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqInsertOrderField::FieldID:
		{
			ReqInsertOrder = ::Allocate<ReqInsertOrderField>();
			memcpy(ReqInsertOrder, buff + offset, sizeof(ReqInsertOrderField));
			offset += sizeof(ReqInsertOrderField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ::Allocate<RspInfoField>();
			memcpy(RspInfo, buff + offset, sizeof(RspInfoField));
			offset += sizeof(RspInfoField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* RspInsertOrderPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqInsertOrder != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqInsertOrder:AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], ClientOrderID:[%d]", ReqInsertOrder->AccountID, ReqInsertOrder->ExchangeID, ReqInsertOrder->InstrumentID, (int)ReqInsertOrder->Direction, (int)ReqInsertOrder->OffsetFlag, (int)ReqInsertOrder->OrderPriceType, ReqInsertOrder->Price, ReqInsertOrder->Volume, ReqInsertOrder->ClientOrderID);
	}
	if (RspInfo != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
	return t_DataStringBuffer;
}
 
ReqCancelOrderPackage* ReqCancelOrderPackage::Allocate()
{
	return ::Allocate<ReqCancelOrderPackage>();
}
void ReqCancelOrderPackage::Free()
{
	Package::Free();
	if (ReqCancelOrder != nullptr)
	{
		::Free<ReqCancelOrderField>(ReqCancelOrder);
		ReqCancelOrder = nullptr;
	}
	MemCacheTemplateSingleton<ReqCancelOrderPackage>::GetInstance().Free(this);
}
void ReqCancelOrderPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqCancelOrderPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqCancelOrder != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqCancelOrderField::FieldID);
		if (strlen(ReqCancelOrder->AccountID) >= sizeof(ReqCancelOrder->AccountID))
		{
			ReqCancelOrder->AccountID[sizeof(ReqCancelOrder->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, ReqCancelOrder->AccountID);
		if (strlen(ReqCancelOrder->ExchangeID) >= sizeof(ReqCancelOrder->ExchangeID))
		{
			ReqCancelOrder->ExchangeID[sizeof(ReqCancelOrder->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, ReqCancelOrder->ExchangeID);
		if (strlen(ReqCancelOrder->InstrumentID) >= sizeof(ReqCancelOrder->InstrumentID))
		{
			ReqCancelOrder->InstrumentID[sizeof(ReqCancelOrder->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, ReqCancelOrder->InstrumentID);
		WriteString(ppos, Items::ClientCancelOrderID, ReqCancelOrder->ClientCancelOrderID);
		WriteString(ppos, Items::OrderID, ReqCancelOrder->OrderID);
		if (strlen(ReqCancelOrder->OrderSysID) >= sizeof(ReqCancelOrder->OrderSysID))
		{
			ReqCancelOrder->OrderSysID[sizeof(ReqCancelOrder->OrderSysID) - 1] = 0;
		}
		WriteString(ppos, Items::OrderSysID, ReqCancelOrder->OrderSysID);
		WriteString(ppos, Items::SessionID, ReqCancelOrder->SessionID);
		WriteString(ppos, Items::ClientOrderID, ReqCancelOrder->ClientOrderID);
		WriteHexString(ppos, Items::FieldEnd, ReqCancelOrderField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqCancelOrderPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqCancelOrderField::FieldID:
			{
				ReqCancelOrder = ::Allocate<ReqCancelOrderField>();
				memset(ReqCancelOrder, 0, sizeof(*ReqCancelOrder));
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
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(ReqCancelOrder->AccountID) ? sizeof(ReqCancelOrder->AccountID) - 1 : value.length();
							memcpy(ReqCancelOrder->AccountID, value.c_str(), len);
							break;
						}
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(ReqCancelOrder->ExchangeID) ? sizeof(ReqCancelOrder->ExchangeID) - 1 : value.length();
							memcpy(ReqCancelOrder->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(ReqCancelOrder->InstrumentID) ? sizeof(ReqCancelOrder->InstrumentID) - 1 : value.length();
							memcpy(ReqCancelOrder->InstrumentID, value.c_str(), len);
							break;
						}
						case Items::ClientCancelOrderID:
						{
							ReqCancelOrder->ClientCancelOrderID = atoi(value.c_str());
							break;
						}
						case Items::OrderID:
						{
							ReqCancelOrder->OrderID = atoi(value.c_str());
							break;
						}
						case Items::OrderSysID:
						{
							size_t len = value.length() >= sizeof(ReqCancelOrder->OrderSysID) ? sizeof(ReqCancelOrder->OrderSysID) - 1 : value.length();
							memcpy(ReqCancelOrder->OrderSysID, value.c_str(), len);
							break;
						}
						case Items::SessionID:
						{
							ReqCancelOrder->SessionID = atoll(value.c_str());
							break;
						}
						case Items::ClientOrderID:
						{
							ReqCancelOrder->ClientOrderID = atoi(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqCancelOrderField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqCancelOrderPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqCancelOrderPackage");
			return false;
		}
	}
	return true;
}
int ReqCancelOrderPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqCancelOrder != nullptr)
	{
		memcpy(buff + offset, &ReqCancelOrderField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqCancelOrder, sizeof(ReqCancelOrderField));
		offset += sizeof(ReqCancelOrderField);
	}
	return offset;
}
bool ReqCancelOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqCancelOrderField::FieldID:
		{
			ReqCancelOrder = ::Allocate<ReqCancelOrderField>();
			memcpy(ReqCancelOrder, buff + offset, sizeof(ReqCancelOrderField));
			offset += sizeof(ReqCancelOrderField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqCancelOrderPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqCancelOrder != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqCancelOrder:AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ClientCancelOrderID:[%d], OrderID:[%d], OrderSysID:[%s], SessionID:[%lld], ClientOrderID:[%d]", ReqCancelOrder->AccountID, ReqCancelOrder->ExchangeID, ReqCancelOrder->InstrumentID, ReqCancelOrder->ClientCancelOrderID, ReqCancelOrder->OrderID, ReqCancelOrder->OrderSysID, ReqCancelOrder->SessionID, ReqCancelOrder->ClientOrderID);
	}
	return t_DataStringBuffer;
}
 
RspCancelOrderPackage* RspCancelOrderPackage::Allocate()
{
	return ::Allocate<RspCancelOrderPackage>();
}
void RspCancelOrderPackage::Free()
{
	Package::Free();
	if (ReqCancelOrder != nullptr)
	{
		::Free<ReqCancelOrderField>(ReqCancelOrder);
		ReqCancelOrder = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspCancelOrderPackage>::GetInstance().Free(this);
}
void RspCancelOrderPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspCancelOrderPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqCancelOrder != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqCancelOrderField::FieldID);
		if (strlen(ReqCancelOrder->AccountID) >= sizeof(ReqCancelOrder->AccountID))
		{
			ReqCancelOrder->AccountID[sizeof(ReqCancelOrder->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, ReqCancelOrder->AccountID);
		if (strlen(ReqCancelOrder->ExchangeID) >= sizeof(ReqCancelOrder->ExchangeID))
		{
			ReqCancelOrder->ExchangeID[sizeof(ReqCancelOrder->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, ReqCancelOrder->ExchangeID);
		if (strlen(ReqCancelOrder->InstrumentID) >= sizeof(ReqCancelOrder->InstrumentID))
		{
			ReqCancelOrder->InstrumentID[sizeof(ReqCancelOrder->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, ReqCancelOrder->InstrumentID);
		WriteString(ppos, Items::ClientCancelOrderID, ReqCancelOrder->ClientCancelOrderID);
		WriteString(ppos, Items::OrderID, ReqCancelOrder->OrderID);
		if (strlen(ReqCancelOrder->OrderSysID) >= sizeof(ReqCancelOrder->OrderSysID))
		{
			ReqCancelOrder->OrderSysID[sizeof(ReqCancelOrder->OrderSysID) - 1] = 0;
		}
		WriteString(ppos, Items::OrderSysID, ReqCancelOrder->OrderSysID);
		WriteString(ppos, Items::SessionID, ReqCancelOrder->SessionID);
		WriteString(ppos, Items::ClientOrderID, ReqCancelOrder->ClientOrderID);
		WriteHexString(ppos, Items::FieldEnd, ReqCancelOrderField::FieldID);
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
bool RspCancelOrderPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqCancelOrderField::FieldID:
			{
				ReqCancelOrder = ::Allocate<ReqCancelOrderField>();
				memset(ReqCancelOrder, 0, sizeof(*ReqCancelOrder));
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
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(ReqCancelOrder->AccountID) ? sizeof(ReqCancelOrder->AccountID) - 1 : value.length();
							memcpy(ReqCancelOrder->AccountID, value.c_str(), len);
							break;
						}
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(ReqCancelOrder->ExchangeID) ? sizeof(ReqCancelOrder->ExchangeID) - 1 : value.length();
							memcpy(ReqCancelOrder->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(ReqCancelOrder->InstrumentID) ? sizeof(ReqCancelOrder->InstrumentID) - 1 : value.length();
							memcpy(ReqCancelOrder->InstrumentID, value.c_str(), len);
							break;
						}
						case Items::ClientCancelOrderID:
						{
							ReqCancelOrder->ClientCancelOrderID = atoi(value.c_str());
							break;
						}
						case Items::OrderID:
						{
							ReqCancelOrder->OrderID = atoi(value.c_str());
							break;
						}
						case Items::OrderSysID:
						{
							size_t len = value.length() >= sizeof(ReqCancelOrder->OrderSysID) ? sizeof(ReqCancelOrder->OrderSysID) - 1 : value.length();
							memcpy(ReqCancelOrder->OrderSysID, value.c_str(), len);
							break;
						}
						case Items::SessionID:
						{
							ReqCancelOrder->SessionID = atoll(value.c_str());
							break;
						}
						case Items::ClientOrderID:
						{
							ReqCancelOrder->ClientOrderID = atoi(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqCancelOrderField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspCancelOrderPackage FieldID:0x%X", fieldID);
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
						WriteLog(LogLevel::Warning, "GetNext Failed For RspCancelOrderPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspCancelOrderPackage");
			return false;
		}
	}
	return true;
}
int RspCancelOrderPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqCancelOrder != nullptr)
	{
		memcpy(buff + offset, &ReqCancelOrderField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqCancelOrder, sizeof(ReqCancelOrderField));
		offset += sizeof(ReqCancelOrderField);
	}
	if (RspInfo != nullptr)
	{
		memcpy(buff + offset, &RspInfoField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, RspInfo, sizeof(RspInfoField));
		offset += sizeof(RspInfoField);
	}
	return offset;
}
bool RspCancelOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqCancelOrderField::FieldID:
		{
			ReqCancelOrder = ::Allocate<ReqCancelOrderField>();
			memcpy(ReqCancelOrder, buff + offset, sizeof(ReqCancelOrderField));
			offset += sizeof(ReqCancelOrderField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ::Allocate<RspInfoField>();
			memcpy(RspInfo, buff + offset, sizeof(RspInfoField));
			offset += sizeof(RspInfoField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* RspCancelOrderPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqCancelOrder != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqCancelOrder:AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ClientCancelOrderID:[%d], OrderID:[%d], OrderSysID:[%s], SessionID:[%lld], ClientOrderID:[%d]", ReqCancelOrder->AccountID, ReqCancelOrder->ExchangeID, ReqCancelOrder->InstrumentID, ReqCancelOrder->ClientCancelOrderID, ReqCancelOrder->OrderID, ReqCancelOrder->OrderSysID, ReqCancelOrder->SessionID, ReqCancelOrder->ClientOrderID);
	}
	if (RspInfo != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
	return t_DataStringBuffer;
}
 
RtnOrderPackage* RtnOrderPackage::Allocate()
{
	return ::Allocate<RtnOrderPackage>();
}
void RtnOrderPackage::Free()
{
	Package::Free();
	if (Order != nullptr)
	{
		::Free<OrderField>(Order);
		Order = nullptr;
	}
	MemCacheTemplateSingleton<RtnOrderPackage>::GetInstance().Free(this);
}
void RtnOrderPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RtnOrderPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (Order != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, OrderField::FieldID);
		if (strlen(Order->TradingDay) >= sizeof(Order->TradingDay))
		{
			Order->TradingDay[sizeof(Order->TradingDay) - 1] = 0;
		}
		WriteString(ppos, Items::TradingDay, Order->TradingDay);
		if (strlen(Order->AccountID) >= sizeof(Order->AccountID))
		{
			Order->AccountID[sizeof(Order->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, Order->AccountID);
		if (strlen(Order->ExchangeID) >= sizeof(Order->ExchangeID))
		{
			Order->ExchangeID[sizeof(Order->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, Order->ExchangeID);
		if (strlen(Order->InstrumentID) >= sizeof(Order->InstrumentID))
		{
			Order->InstrumentID[sizeof(Order->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, Order->InstrumentID);
		WriteString(ppos, Items::ProductClass, (int)Order->ProductClass);
		WriteString(ppos, Items::OrderID, Order->OrderID);
		if (strlen(Order->OrderSysID) >= sizeof(Order->OrderSysID))
		{
			Order->OrderSysID[sizeof(Order->OrderSysID) - 1] = 0;
		}
		WriteString(ppos, Items::OrderSysID, Order->OrderSysID);
		WriteString(ppos, Items::Direction, (int)Order->Direction);
		WriteString(ppos, Items::OffsetFlag, (int)Order->OffsetFlag);
		WriteString(ppos, Items::OrderPriceType, (int)Order->OrderPriceType);
		WriteString(ppos, Items::Price, Order->Price);
		WriteString(ppos, Items::Volume, Order->Volume);
		WriteString(ppos, Items::VolumeTotal, Order->VolumeTotal);
		WriteString(ppos, Items::VolumeTraded, Order->VolumeTraded);
		WriteString(ppos, Items::VolumeMultiple, Order->VolumeMultiple);
		WriteString(ppos, Items::OrderStatus, (int)Order->OrderStatus);
		if (strlen(Order->OrderDate) >= sizeof(Order->OrderDate))
		{
			Order->OrderDate[sizeof(Order->OrderDate) - 1] = 0;
		}
		WriteString(ppos, Items::OrderDate, Order->OrderDate);
		if (strlen(Order->OrderTime) >= sizeof(Order->OrderTime))
		{
			Order->OrderTime[sizeof(Order->OrderTime) - 1] = 0;
		}
		WriteString(ppos, Items::OrderTime, Order->OrderTime);
		if (strlen(Order->CancelDate) >= sizeof(Order->CancelDate))
		{
			Order->CancelDate[sizeof(Order->CancelDate) - 1] = 0;
		}
		WriteString(ppos, Items::CancelDate, Order->CancelDate);
		if (strlen(Order->CancelTime) >= sizeof(Order->CancelTime))
		{
			Order->CancelTime[sizeof(Order->CancelTime) - 1] = 0;
		}
		WriteString(ppos, Items::CancelTime, Order->CancelTime);
		WriteString(ppos, Items::SessionID, Order->SessionID);
		WriteString(ppos, Items::ClientOrderID, Order->ClientOrderID);
		WriteString(ppos, Items::RequestID, Order->RequestID);
		WriteString(ppos, Items::FrozenCash, Order->FrozenCash);
		WriteString(ppos, Items::FrozenMargin, Order->FrozenMargin);
		WriteString(ppos, Items::FrozenCommission, Order->FrozenCommission);
		WriteHexString(ppos, Items::FieldEnd, OrderField::FieldID);
	}
	return int(ppos - buff);
}
bool RtnOrderPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case OrderField::FieldID:
			{
				Order = ::Allocate<OrderField>();
				memset(Order, 0, sizeof(*Order));
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
							size_t len = value.length() >= sizeof(Order->TradingDay) ? sizeof(Order->TradingDay) - 1 : value.length();
							memcpy(Order->TradingDay, value.c_str(), len);
							break;
						}
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(Order->AccountID) ? sizeof(Order->AccountID) - 1 : value.length();
							memcpy(Order->AccountID, value.c_str(), len);
							break;
						}
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(Order->ExchangeID) ? sizeof(Order->ExchangeID) - 1 : value.length();
							memcpy(Order->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(Order->InstrumentID) ? sizeof(Order->InstrumentID) - 1 : value.length();
							memcpy(Order->InstrumentID, value.c_str(), len);
							break;
						}
						case Items::ProductClass:
						{
							Order->ProductClass = (ProductClassType)(atoi(value.c_str()));
							break;
						}
						case Items::OrderID:
						{
							Order->OrderID = atoi(value.c_str());
							break;
						}
						case Items::OrderSysID:
						{
							size_t len = value.length() >= sizeof(Order->OrderSysID) ? sizeof(Order->OrderSysID) - 1 : value.length();
							memcpy(Order->OrderSysID, value.c_str(), len);
							break;
						}
						case Items::Direction:
						{
							Order->Direction = (DirectionType)(atoi(value.c_str()));
							break;
						}
						case Items::OffsetFlag:
						{
							Order->OffsetFlag = (OffsetFlagType)(atoi(value.c_str()));
							break;
						}
						case Items::OrderPriceType:
						{
							Order->OrderPriceType = (OrderPriceTypeType)(atoi(value.c_str()));
							break;
						}
						case Items::Price:
						{
							Order->Price = atof(value.c_str());
							break;
						}
						case Items::Volume:
						{
							Order->Volume = atoll(value.c_str());
							break;
						}
						case Items::VolumeTotal:
						{
							Order->VolumeTotal = atoll(value.c_str());
							break;
						}
						case Items::VolumeTraded:
						{
							Order->VolumeTraded = atoll(value.c_str());
							break;
						}
						case Items::VolumeMultiple:
						{
							Order->VolumeMultiple = atoi(value.c_str());
							break;
						}
						case Items::OrderStatus:
						{
							Order->OrderStatus = (OrderStatusType)(atoi(value.c_str()));
							break;
						}
						case Items::OrderDate:
						{
							size_t len = value.length() >= sizeof(Order->OrderDate) ? sizeof(Order->OrderDate) - 1 : value.length();
							memcpy(Order->OrderDate, value.c_str(), len);
							break;
						}
						case Items::OrderTime:
						{
							size_t len = value.length() >= sizeof(Order->OrderTime) ? sizeof(Order->OrderTime) - 1 : value.length();
							memcpy(Order->OrderTime, value.c_str(), len);
							break;
						}
						case Items::CancelDate:
						{
							size_t len = value.length() >= sizeof(Order->CancelDate) ? sizeof(Order->CancelDate) - 1 : value.length();
							memcpy(Order->CancelDate, value.c_str(), len);
							break;
						}
						case Items::CancelTime:
						{
							size_t len = value.length() >= sizeof(Order->CancelTime) ? sizeof(Order->CancelTime) - 1 : value.length();
							memcpy(Order->CancelTime, value.c_str(), len);
							break;
						}
						case Items::SessionID:
						{
							Order->SessionID = atoll(value.c_str());
							break;
						}
						case Items::ClientOrderID:
						{
							Order->ClientOrderID = atoi(value.c_str());
							break;
						}
						case Items::RequestID:
						{
							Order->RequestID = atoi(value.c_str());
							break;
						}
						case Items::FrozenCash:
						{
							Order->FrozenCash = atof(value.c_str());
							break;
						}
						case Items::FrozenMargin:
						{
							Order->FrozenMargin = atof(value.c_str());
							break;
						}
						case Items::FrozenCommission:
						{
							Order->FrozenCommission = atof(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for OrderField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RtnOrderPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RtnOrderPackage");
			return false;
		}
	}
	return true;
}
int RtnOrderPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (Order != nullptr)
	{
		memcpy(buff + offset, &OrderField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, Order, sizeof(OrderField));
		offset += sizeof(OrderField);
	}
	return offset;
}
bool RtnOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case OrderField::FieldID:
		{
			Order = ::Allocate<OrderField>();
			memcpy(Order, buff + offset, sizeof(OrderField));
			offset += sizeof(OrderField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* RtnOrderPackage::GetDebugString() const
{
	int offset = 0;
	if (Order != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "Order:TradingDay:[%s], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], OrderSysID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], VolumeTotal:[%lld], VolumeTraded:[%lld], VolumeMultiple:[%d], OrderStatus:[%d], OrderDate:[%s], OrderTime:[%s], CancelDate:[%s], CancelTime:[%s], SessionID:[%lld], ClientOrderID:[%d], RequestID:[%d], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f]", Order->TradingDay, Order->AccountID, Order->ExchangeID, Order->InstrumentID, (int)Order->ProductClass, Order->OrderID, Order->OrderSysID, (int)Order->Direction, (int)Order->OffsetFlag, (int)Order->OrderPriceType, Order->Price, Order->Volume, Order->VolumeTotal, Order->VolumeTraded, Order->VolumeMultiple, (int)Order->OrderStatus, Order->OrderDate, Order->OrderTime, Order->CancelDate, Order->CancelTime, Order->SessionID, Order->ClientOrderID, Order->RequestID, Order->FrozenCash, Order->FrozenMargin, Order->FrozenCommission);
	}
	return t_DataStringBuffer;
}
 
RtnTradePackage* RtnTradePackage::Allocate()
{
	return ::Allocate<RtnTradePackage>();
}
void RtnTradePackage::Free()
{
	Package::Free();
	if (Trade != nullptr)
	{
		::Free<TradeField>(Trade);
		Trade = nullptr;
	}
	MemCacheTemplateSingleton<RtnTradePackage>::GetInstance().Free(this);
}
void RtnTradePackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RtnTradePackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (Trade != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, TradeField::FieldID);
		if (strlen(Trade->TradingDay) >= sizeof(Trade->TradingDay))
		{
			Trade->TradingDay[sizeof(Trade->TradingDay) - 1] = 0;
		}
		WriteString(ppos, Items::TradingDay, Trade->TradingDay);
		if (strlen(Trade->AccountID) >= sizeof(Trade->AccountID))
		{
			Trade->AccountID[sizeof(Trade->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, Trade->AccountID);
		if (strlen(Trade->ExchangeID) >= sizeof(Trade->ExchangeID))
		{
			Trade->ExchangeID[sizeof(Trade->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, Trade->ExchangeID);
		if (strlen(Trade->InstrumentID) >= sizeof(Trade->InstrumentID))
		{
			Trade->InstrumentID[sizeof(Trade->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, Trade->InstrumentID);
		WriteString(ppos, Items::ProductClass, (int)Trade->ProductClass);
		WriteString(ppos, Items::OrderID, Trade->OrderID);
		if (strlen(Trade->OrderSysID) >= sizeof(Trade->OrderSysID))
		{
			Trade->OrderSysID[sizeof(Trade->OrderSysID) - 1] = 0;
		}
		WriteString(ppos, Items::OrderSysID, Trade->OrderSysID);
		if (strlen(Trade->TradeID) >= sizeof(Trade->TradeID))
		{
			Trade->TradeID[sizeof(Trade->TradeID) - 1] = 0;
		}
		WriteString(ppos, Items::TradeID, Trade->TradeID);
		WriteString(ppos, Items::Direction, (int)Trade->Direction);
		WriteString(ppos, Items::OffsetFlag, (int)Trade->OffsetFlag);
		WriteString(ppos, Items::Price, Trade->Price);
		WriteString(ppos, Items::Volume, Trade->Volume);
		WriteString(ppos, Items::VolumeMultiple, Trade->VolumeMultiple);
		WriteString(ppos, Items::TradeAmount, Trade->TradeAmount);
		WriteString(ppos, Items::Commission, Trade->Commission);
		if (strlen(Trade->TradeDate) >= sizeof(Trade->TradeDate))
		{
			Trade->TradeDate[sizeof(Trade->TradeDate) - 1] = 0;
		}
		WriteString(ppos, Items::TradeDate, Trade->TradeDate);
		if (strlen(Trade->TradeTime) >= sizeof(Trade->TradeTime))
		{
			Trade->TradeTime[sizeof(Trade->TradeTime) - 1] = 0;
		}
		WriteString(ppos, Items::TradeTime, Trade->TradeTime);
		WriteHexString(ppos, Items::FieldEnd, TradeField::FieldID);
	}
	return int(ppos - buff);
}
bool RtnTradePackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case TradeField::FieldID:
			{
				Trade = ::Allocate<TradeField>();
				memset(Trade, 0, sizeof(*Trade));
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
							size_t len = value.length() >= sizeof(Trade->TradingDay) ? sizeof(Trade->TradingDay) - 1 : value.length();
							memcpy(Trade->TradingDay, value.c_str(), len);
							break;
						}
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(Trade->AccountID) ? sizeof(Trade->AccountID) - 1 : value.length();
							memcpy(Trade->AccountID, value.c_str(), len);
							break;
						}
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(Trade->ExchangeID) ? sizeof(Trade->ExchangeID) - 1 : value.length();
							memcpy(Trade->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(Trade->InstrumentID) ? sizeof(Trade->InstrumentID) - 1 : value.length();
							memcpy(Trade->InstrumentID, value.c_str(), len);
							break;
						}
						case Items::ProductClass:
						{
							Trade->ProductClass = (ProductClassType)(atoi(value.c_str()));
							break;
						}
						case Items::OrderID:
						{
							Trade->OrderID = atoi(value.c_str());
							break;
						}
						case Items::OrderSysID:
						{
							size_t len = value.length() >= sizeof(Trade->OrderSysID) ? sizeof(Trade->OrderSysID) - 1 : value.length();
							memcpy(Trade->OrderSysID, value.c_str(), len);
							break;
						}
						case Items::TradeID:
						{
							size_t len = value.length() >= sizeof(Trade->TradeID) ? sizeof(Trade->TradeID) - 1 : value.length();
							memcpy(Trade->TradeID, value.c_str(), len);
							break;
						}
						case Items::Direction:
						{
							Trade->Direction = (DirectionType)(atoi(value.c_str()));
							break;
						}
						case Items::OffsetFlag:
						{
							Trade->OffsetFlag = (OffsetFlagType)(atoi(value.c_str()));
							break;
						}
						case Items::Price:
						{
							Trade->Price = atof(value.c_str());
							break;
						}
						case Items::Volume:
						{
							Trade->Volume = atoll(value.c_str());
							break;
						}
						case Items::VolumeMultiple:
						{
							Trade->VolumeMultiple = atoi(value.c_str());
							break;
						}
						case Items::TradeAmount:
						{
							Trade->TradeAmount = atof(value.c_str());
							break;
						}
						case Items::Commission:
						{
							Trade->Commission = atof(value.c_str());
							break;
						}
						case Items::TradeDate:
						{
							size_t len = value.length() >= sizeof(Trade->TradeDate) ? sizeof(Trade->TradeDate) - 1 : value.length();
							memcpy(Trade->TradeDate, value.c_str(), len);
							break;
						}
						case Items::TradeTime:
						{
							size_t len = value.length() >= sizeof(Trade->TradeTime) ? sizeof(Trade->TradeTime) - 1 : value.length();
							memcpy(Trade->TradeTime, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for TradeField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RtnTradePackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RtnTradePackage");
			return false;
		}
	}
	return true;
}
int RtnTradePackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (Trade != nullptr)
	{
		memcpy(buff + offset, &TradeField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, Trade, sizeof(TradeField));
		offset += sizeof(TradeField);
	}
	return offset;
}
bool RtnTradePackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case TradeField::FieldID:
		{
			Trade = ::Allocate<TradeField>();
			memcpy(Trade, buff + offset, sizeof(TradeField));
			offset += sizeof(TradeField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* RtnTradePackage::GetDebugString() const
{
	int offset = 0;
	if (Trade != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "Trade:TradingDay:[%s], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], OrderSysID:[%s], TradeID:[%s], Direction:[%d], OffsetFlag:[%d], Price:[%f], Volume:[%lld], VolumeMultiple:[%d], TradeAmount:[%f], Commission:[%f], TradeDate:[%s], TradeTime:[%s]", Trade->TradingDay, Trade->AccountID, Trade->ExchangeID, Trade->InstrumentID, (int)Trade->ProductClass, Trade->OrderID, Trade->OrderSysID, Trade->TradeID, (int)Trade->Direction, (int)Trade->OffsetFlag, Trade->Price, Trade->Volume, Trade->VolumeMultiple, Trade->TradeAmount, Trade->Commission, Trade->TradeDate, Trade->TradeTime);
	}
	return t_DataStringBuffer;
}
