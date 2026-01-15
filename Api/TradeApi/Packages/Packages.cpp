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
 
ReqQryHolderAccountPackage* ReqQryHolderAccountPackage::Allocate()
{
	return ::Allocate<ReqQryHolderAccountPackage>();
}
void ReqQryHolderAccountPackage::Free()
{
	Package::Free();
	if (ReqQryHolderAccount != nullptr)
	{
		::Free<ReqQryHolderAccountField>(ReqQryHolderAccount);
		ReqQryHolderAccount = nullptr;
	}
	MemCacheTemplateSingleton<ReqQryHolderAccountPackage>::GetInstance().Free(this);
}
void ReqQryHolderAccountPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqQryHolderAccountPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqQryHolderAccount != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqQryHolderAccountField::FieldID);
		if (strlen(ReqQryHolderAccount->AccountID) >= sizeof(ReqQryHolderAccount->AccountID))
		{
			ReqQryHolderAccount->AccountID[sizeof(ReqQryHolderAccount->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, ReqQryHolderAccount->AccountID);
		WriteHexString(ppos, Items::FieldEnd, ReqQryHolderAccountField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqQryHolderAccountPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqQryHolderAccountField::FieldID:
			{
				ReqQryHolderAccount = ::Allocate<ReqQryHolderAccountField>();
				memset(ReqQryHolderAccount, 0, sizeof(*ReqQryHolderAccount));
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
							size_t len = value.length() >= sizeof(ReqQryHolderAccount->AccountID) ? sizeof(ReqQryHolderAccount->AccountID) - 1 : value.length();
							memcpy(ReqQryHolderAccount->AccountID, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqQryHolderAccountField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqQryHolderAccountPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqQryHolderAccountPackage");
			return false;
		}
	}
	return true;
}
int ReqQryHolderAccountPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqQryHolderAccount != nullptr)
	{
		memcpy(buff + offset, &ReqQryHolderAccountField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqQryHolderAccount, sizeof(ReqQryHolderAccountField));
		offset += sizeof(ReqQryHolderAccountField);
	}
	return offset;
}
bool ReqQryHolderAccountPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqQryHolderAccountField::FieldID:
		{
			ReqQryHolderAccount = ::Allocate<ReqQryHolderAccountField>();
			memcpy(ReqQryHolderAccount, buff + offset, sizeof(ReqQryHolderAccountField));
			offset += sizeof(ReqQryHolderAccountField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqQryHolderAccountPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqQryHolderAccount != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqQryHolderAccount:AccountID:[%s]", ReqQryHolderAccount->AccountID);
	}
	return t_DataStringBuffer;
}
 
RspQryHolderAccountPackage* RspQryHolderAccountPackage::Allocate()
{
	return ::Allocate<RspQryHolderAccountPackage>();
}
void RspQryHolderAccountPackage::Free()
{
	Package::Free();
	if (HolderAccount != nullptr)
	{
		::Free<HolderAccountField>(HolderAccount);
		HolderAccount = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspQryHolderAccountPackage>::GetInstance().Free(this);
}
void RspQryHolderAccountPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspQryHolderAccountPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (HolderAccount != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, HolderAccountField::FieldID);
		if (strlen(HolderAccount->ExchangeID) >= sizeof(HolderAccount->ExchangeID))
		{
			HolderAccount->ExchangeID[sizeof(HolderAccount->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, HolderAccount->ExchangeID);
		if (strlen(HolderAccount->HolderAccountID) >= sizeof(HolderAccount->HolderAccountID))
		{
			HolderAccount->HolderAccountID[sizeof(HolderAccount->HolderAccountID) - 1] = 0;
		}
		WriteString(ppos, Items::HolderAccountID, HolderAccount->HolderAccountID);
		WriteString(ppos, Items::PrimaryFlag, HolderAccount->PrimaryFlag);
		WriteHexString(ppos, Items::FieldEnd, HolderAccountField::FieldID);
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
bool RspQryHolderAccountPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case HolderAccountField::FieldID:
			{
				HolderAccount = ::Allocate<HolderAccountField>();
				memset(HolderAccount, 0, sizeof(*HolderAccount));
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
							size_t len = value.length() >= sizeof(HolderAccount->ExchangeID) ? sizeof(HolderAccount->ExchangeID) - 1 : value.length();
							memcpy(HolderAccount->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::HolderAccountID:
						{
							size_t len = value.length() >= sizeof(HolderAccount->HolderAccountID) ? sizeof(HolderAccount->HolderAccountID) - 1 : value.length();
							memcpy(HolderAccount->HolderAccountID, value.c_str(), len);
							break;
						}
						case Items::PrimaryFlag:
						{
							HolderAccount->PrimaryFlag = atoi(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for HolderAccountField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryHolderAccountPackage FieldID:0x%X", fieldID);
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
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryHolderAccountPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspQryHolderAccountPackage");
			return false;
		}
	}
	return true;
}
int RspQryHolderAccountPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (HolderAccount != nullptr)
	{
		memcpy(buff + offset, &HolderAccountField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, HolderAccount, sizeof(HolderAccountField));
		offset += sizeof(HolderAccountField);
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
bool RspQryHolderAccountPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case HolderAccountField::FieldID:
		{
			HolderAccount = ::Allocate<HolderAccountField>();
			memcpy(HolderAccount, buff + offset, sizeof(HolderAccountField));
			offset += sizeof(HolderAccountField);	
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
const char* RspQryHolderAccountPackage::GetDebugString() const
{
	int offset = 0;
	if (HolderAccount != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "HolderAccount:ExchangeID:[%s], HolderAccountID:[%s], PrimaryFlag:[%d]", HolderAccount->ExchangeID, HolderAccount->HolderAccountID, HolderAccount->PrimaryFlag);
	}
	if (RspInfo != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
	return t_DataStringBuffer;
}
 
ReqQryCapitalPackage* ReqQryCapitalPackage::Allocate()
{
	return ::Allocate<ReqQryCapitalPackage>();
}
void ReqQryCapitalPackage::Free()
{
	Package::Free();
	if (ReqQryCapital != nullptr)
	{
		::Free<ReqQryCapitalField>(ReqQryCapital);
		ReqQryCapital = nullptr;
	}
	MemCacheTemplateSingleton<ReqQryCapitalPackage>::GetInstance().Free(this);
}
void ReqQryCapitalPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqQryCapitalPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqQryCapital != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqQryCapitalField::FieldID);
		if (strlen(ReqQryCapital->AccountID) >= sizeof(ReqQryCapital->AccountID))
		{
			ReqQryCapital->AccountID[sizeof(ReqQryCapital->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, ReqQryCapital->AccountID);
		WriteHexString(ppos, Items::FieldEnd, ReqQryCapitalField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqQryCapitalPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqQryCapitalField::FieldID:
			{
				ReqQryCapital = ::Allocate<ReqQryCapitalField>();
				memset(ReqQryCapital, 0, sizeof(*ReqQryCapital));
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
							size_t len = value.length() >= sizeof(ReqQryCapital->AccountID) ? sizeof(ReqQryCapital->AccountID) - 1 : value.length();
							memcpy(ReqQryCapital->AccountID, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqQryCapitalField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqQryCapitalPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqQryCapitalPackage");
			return false;
		}
	}
	return true;
}
int ReqQryCapitalPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqQryCapital != nullptr)
	{
		memcpy(buff + offset, &ReqQryCapitalField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqQryCapital, sizeof(ReqQryCapitalField));
		offset += sizeof(ReqQryCapitalField);
	}
	return offset;
}
bool ReqQryCapitalPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqQryCapitalField::FieldID:
		{
			ReqQryCapital = ::Allocate<ReqQryCapitalField>();
			memcpy(ReqQryCapital, buff + offset, sizeof(ReqQryCapitalField));
			offset += sizeof(ReqQryCapitalField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqQryCapitalPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqQryCapital != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqQryCapital:AccountID:[%s]", ReqQryCapital->AccountID);
	}
	return t_DataStringBuffer;
}
 
RspQryCapitalPackage* RspQryCapitalPackage::Allocate()
{
	return ::Allocate<RspQryCapitalPackage>();
}
void RspQryCapitalPackage::Free()
{
	Package::Free();
	if (Capital != nullptr)
	{
		::Free<CapitalField>(Capital);
		Capital = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspQryCapitalPackage>::GetInstance().Free(this);
}
void RspQryCapitalPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspQryCapitalPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (Capital != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, CapitalField::FieldID);
		if (strlen(Capital->TradingDay) >= sizeof(Capital->TradingDay))
		{
			Capital->TradingDay[sizeof(Capital->TradingDay) - 1] = 0;
		}
		WriteString(ppos, Items::TradingDay, Capital->TradingDay);
		if (strlen(Capital->AccountID) >= sizeof(Capital->AccountID))
		{
			Capital->AccountID[sizeof(Capital->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, Capital->AccountID);
		WriteString(ppos, Items::AccountType, (int)Capital->AccountType);
		WriteString(ppos, Items::Balance, Capital->Balance);
		WriteString(ppos, Items::PreBalance, Capital->PreBalance);
		WriteString(ppos, Items::Available, Capital->Available);
		WriteString(ppos, Items::MarketValue, Capital->MarketValue);
		WriteString(ppos, Items::CashIn, Capital->CashIn);
		WriteString(ppos, Items::CashOut, Capital->CashOut);
		WriteString(ppos, Items::Margin, Capital->Margin);
		WriteString(ppos, Items::Commission, Capital->Commission);
		WriteString(ppos, Items::FrozenCash, Capital->FrozenCash);
		WriteString(ppos, Items::FrozenMargin, Capital->FrozenMargin);
		WriteString(ppos, Items::FrozenCommission, Capital->FrozenCommission);
		WriteString(ppos, Items::CloseProfitByDate, Capital->CloseProfitByDate);
		WriteString(ppos, Items::CloseProfitByTrade, Capital->CloseProfitByTrade);
		WriteString(ppos, Items::PositionProfitByDate, Capital->PositionProfitByDate);
		WriteString(ppos, Items::PositionProfitByTrade, Capital->PositionProfitByTrade);
		WriteString(ppos, Items::Deposit, Capital->Deposit);
		WriteString(ppos, Items::Withdraw, Capital->Withdraw);
		WriteHexString(ppos, Items::FieldEnd, CapitalField::FieldID);
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
bool RspQryCapitalPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case CapitalField::FieldID:
			{
				Capital = ::Allocate<CapitalField>();
				memset(Capital, 0, sizeof(*Capital));
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
							size_t len = value.length() >= sizeof(Capital->TradingDay) ? sizeof(Capital->TradingDay) - 1 : value.length();
							memcpy(Capital->TradingDay, value.c_str(), len);
							break;
						}
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(Capital->AccountID) ? sizeof(Capital->AccountID) - 1 : value.length();
							memcpy(Capital->AccountID, value.c_str(), len);
							break;
						}
						case Items::AccountType:
						{
							Capital->AccountType = (AccountTypeType)(atoi(value.c_str()));
							break;
						}
						case Items::Balance:
						{
							Capital->Balance = atof(value.c_str());
							break;
						}
						case Items::PreBalance:
						{
							Capital->PreBalance = atof(value.c_str());
							break;
						}
						case Items::Available:
						{
							Capital->Available = atof(value.c_str());
							break;
						}
						case Items::MarketValue:
						{
							Capital->MarketValue = atof(value.c_str());
							break;
						}
						case Items::CashIn:
						{
							Capital->CashIn = atof(value.c_str());
							break;
						}
						case Items::CashOut:
						{
							Capital->CashOut = atof(value.c_str());
							break;
						}
						case Items::Margin:
						{
							Capital->Margin = atof(value.c_str());
							break;
						}
						case Items::Commission:
						{
							Capital->Commission = atof(value.c_str());
							break;
						}
						case Items::FrozenCash:
						{
							Capital->FrozenCash = atof(value.c_str());
							break;
						}
						case Items::FrozenMargin:
						{
							Capital->FrozenMargin = atof(value.c_str());
							break;
						}
						case Items::FrozenCommission:
						{
							Capital->FrozenCommission = atof(value.c_str());
							break;
						}
						case Items::CloseProfitByDate:
						{
							Capital->CloseProfitByDate = atof(value.c_str());
							break;
						}
						case Items::CloseProfitByTrade:
						{
							Capital->CloseProfitByTrade = atof(value.c_str());
							break;
						}
						case Items::PositionProfitByDate:
						{
							Capital->PositionProfitByDate = atof(value.c_str());
							break;
						}
						case Items::PositionProfitByTrade:
						{
							Capital->PositionProfitByTrade = atof(value.c_str());
							break;
						}
						case Items::Deposit:
						{
							Capital->Deposit = atof(value.c_str());
							break;
						}
						case Items::Withdraw:
						{
							Capital->Withdraw = atof(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for CapitalField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryCapitalPackage FieldID:0x%X", fieldID);
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
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryCapitalPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspQryCapitalPackage");
			return false;
		}
	}
	return true;
}
int RspQryCapitalPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (Capital != nullptr)
	{
		memcpy(buff + offset, &CapitalField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, Capital, sizeof(CapitalField));
		offset += sizeof(CapitalField);
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
bool RspQryCapitalPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case CapitalField::FieldID:
		{
			Capital = ::Allocate<CapitalField>();
			memcpy(Capital, buff + offset, sizeof(CapitalField));
			offset += sizeof(CapitalField);	
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
const char* RspQryCapitalPackage::GetDebugString() const
{
	int offset = 0;
	if (Capital != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "Capital:TradingDay:[%s], AccountID:[%s], AccountType:[%d], Balance:[%f], PreBalance:[%f], Available:[%f], MarketValue:[%f], CashIn:[%f], CashOut:[%f], Margin:[%f], Commission:[%f], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f], CloseProfitByDate:[%f], CloseProfitByTrade:[%f], PositionProfitByDate:[%f], PositionProfitByTrade:[%f], Deposit:[%f], Withdraw:[%f]", Capital->TradingDay, Capital->AccountID, (int)Capital->AccountType, Capital->Balance, Capital->PreBalance, Capital->Available, Capital->MarketValue, Capital->CashIn, Capital->CashOut, Capital->Margin, Capital->Commission, Capital->FrozenCash, Capital->FrozenMargin, Capital->FrozenCommission, Capital->CloseProfitByDate, Capital->CloseProfitByTrade, Capital->PositionProfitByDate, Capital->PositionProfitByTrade, Capital->Deposit, Capital->Withdraw);
	}
	if (RspInfo != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
	return t_DataStringBuffer;
}
 
ReqQryPositionPackage* ReqQryPositionPackage::Allocate()
{
	return ::Allocate<ReqQryPositionPackage>();
}
void ReqQryPositionPackage::Free()
{
	Package::Free();
	if (ReqQryPosition != nullptr)
	{
		::Free<ReqQryPositionField>(ReqQryPosition);
		ReqQryPosition = nullptr;
	}
	MemCacheTemplateSingleton<ReqQryPositionPackage>::GetInstance().Free(this);
}
void ReqQryPositionPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqQryPositionPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqQryPosition != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqQryPositionField::FieldID);
		if (strlen(ReqQryPosition->AccountID) >= sizeof(ReqQryPosition->AccountID))
		{
			ReqQryPosition->AccountID[sizeof(ReqQryPosition->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, ReqQryPosition->AccountID);
		WriteHexString(ppos, Items::FieldEnd, ReqQryPositionField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqQryPositionPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqQryPositionField::FieldID:
			{
				ReqQryPosition = ::Allocate<ReqQryPositionField>();
				memset(ReqQryPosition, 0, sizeof(*ReqQryPosition));
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
							size_t len = value.length() >= sizeof(ReqQryPosition->AccountID) ? sizeof(ReqQryPosition->AccountID) - 1 : value.length();
							memcpy(ReqQryPosition->AccountID, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqQryPositionField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqQryPositionPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqQryPositionPackage");
			return false;
		}
	}
	return true;
}
int ReqQryPositionPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqQryPosition != nullptr)
	{
		memcpy(buff + offset, &ReqQryPositionField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqQryPosition, sizeof(ReqQryPositionField));
		offset += sizeof(ReqQryPositionField);
	}
	return offset;
}
bool ReqQryPositionPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqQryPositionField::FieldID:
		{
			ReqQryPosition = ::Allocate<ReqQryPositionField>();
			memcpy(ReqQryPosition, buff + offset, sizeof(ReqQryPositionField));
			offset += sizeof(ReqQryPositionField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqQryPositionPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqQryPosition != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqQryPosition:AccountID:[%s]", ReqQryPosition->AccountID);
	}
	return t_DataStringBuffer;
}
 
RspQryPositionPackage* RspQryPositionPackage::Allocate()
{
	return ::Allocate<RspQryPositionPackage>();
}
void RspQryPositionPackage::Free()
{
	Package::Free();
	if (Position != nullptr)
	{
		::Free<PositionField>(Position);
		Position = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspQryPositionPackage>::GetInstance().Free(this);
}
void RspQryPositionPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspQryPositionPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (Position != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, PositionField::FieldID);
		if (strlen(Position->TradingDay) >= sizeof(Position->TradingDay))
		{
			Position->TradingDay[sizeof(Position->TradingDay) - 1] = 0;
		}
		WriteString(ppos, Items::TradingDay, Position->TradingDay);
		if (strlen(Position->AccountID) >= sizeof(Position->AccountID))
		{
			Position->AccountID[sizeof(Position->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, Position->AccountID);
		WriteString(ppos, Items::AccountType, (int)Position->AccountType);
		if (strlen(Position->ExchangeID) >= sizeof(Position->ExchangeID))
		{
			Position->ExchangeID[sizeof(Position->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, Position->ExchangeID);
		if (strlen(Position->InstrumentID) >= sizeof(Position->InstrumentID))
		{
			Position->InstrumentID[sizeof(Position->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, Position->InstrumentID);
		WriteString(ppos, Items::ProductClass, (int)Position->ProductClass);
		WriteString(ppos, Items::PosiDirection, (int)Position->PosiDirection);
		WriteString(ppos, Items::TotalPosition, Position->TotalPosition);
		WriteString(ppos, Items::PositionFrozen, Position->PositionFrozen);
		WriteString(ppos, Items::TodayPosition, Position->TodayPosition);
		WriteString(ppos, Items::MarketValue, Position->MarketValue);
		WriteString(ppos, Items::CashIn, Position->CashIn);
		WriteString(ppos, Items::CashOut, Position->CashOut);
		WriteString(ppos, Items::Margin, Position->Margin);
		WriteString(ppos, Items::Commission, Position->Commission);
		WriteString(ppos, Items::VolumeMultiple, Position->VolumeMultiple);
		WriteString(ppos, Items::CloseProfitByDate, Position->CloseProfitByDate);
		WriteString(ppos, Items::CloseProfitByTrade, Position->CloseProfitByTrade);
		WriteString(ppos, Items::PositionProfitByDate, Position->PositionProfitByDate);
		WriteString(ppos, Items::PositionProfitByTrade, Position->PositionProfitByTrade);
		WriteString(ppos, Items::LastPrice, Position->LastPrice);
		WriteString(ppos, Items::PreSettlementPrice, Position->PreSettlementPrice);
		WriteHexString(ppos, Items::FieldEnd, PositionField::FieldID);
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
bool RspQryPositionPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case PositionField::FieldID:
			{
				Position = ::Allocate<PositionField>();
				memset(Position, 0, sizeof(*Position));
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
							size_t len = value.length() >= sizeof(Position->TradingDay) ? sizeof(Position->TradingDay) - 1 : value.length();
							memcpy(Position->TradingDay, value.c_str(), len);
							break;
						}
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(Position->AccountID) ? sizeof(Position->AccountID) - 1 : value.length();
							memcpy(Position->AccountID, value.c_str(), len);
							break;
						}
						case Items::AccountType:
						{
							Position->AccountType = (AccountTypeType)(atoi(value.c_str()));
							break;
						}
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(Position->ExchangeID) ? sizeof(Position->ExchangeID) - 1 : value.length();
							memcpy(Position->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(Position->InstrumentID) ? sizeof(Position->InstrumentID) - 1 : value.length();
							memcpy(Position->InstrumentID, value.c_str(), len);
							break;
						}
						case Items::ProductClass:
						{
							Position->ProductClass = (ProductClassType)(atoi(value.c_str()));
							break;
						}
						case Items::PosiDirection:
						{
							Position->PosiDirection = (PosiDirectionType)(atoi(value.c_str()));
							break;
						}
						case Items::TotalPosition:
						{
							Position->TotalPosition = atoll(value.c_str());
							break;
						}
						case Items::PositionFrozen:
						{
							Position->PositionFrozen = atoll(value.c_str());
							break;
						}
						case Items::TodayPosition:
						{
							Position->TodayPosition = atoll(value.c_str());
							break;
						}
						case Items::MarketValue:
						{
							Position->MarketValue = atof(value.c_str());
							break;
						}
						case Items::CashIn:
						{
							Position->CashIn = atof(value.c_str());
							break;
						}
						case Items::CashOut:
						{
							Position->CashOut = atof(value.c_str());
							break;
						}
						case Items::Margin:
						{
							Position->Margin = atof(value.c_str());
							break;
						}
						case Items::Commission:
						{
							Position->Commission = atof(value.c_str());
							break;
						}
						case Items::VolumeMultiple:
						{
							Position->VolumeMultiple = atoi(value.c_str());
							break;
						}
						case Items::CloseProfitByDate:
						{
							Position->CloseProfitByDate = atof(value.c_str());
							break;
						}
						case Items::CloseProfitByTrade:
						{
							Position->CloseProfitByTrade = atof(value.c_str());
							break;
						}
						case Items::PositionProfitByDate:
						{
							Position->PositionProfitByDate = atof(value.c_str());
							break;
						}
						case Items::PositionProfitByTrade:
						{
							Position->PositionProfitByTrade = atof(value.c_str());
							break;
						}
						case Items::LastPrice:
						{
							Position->LastPrice = atof(value.c_str());
							break;
						}
						case Items::PreSettlementPrice:
						{
							Position->PreSettlementPrice = atof(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for PositionField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryPositionPackage FieldID:0x%X", fieldID);
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
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryPositionPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspQryPositionPackage");
			return false;
		}
	}
	return true;
}
int RspQryPositionPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (Position != nullptr)
	{
		memcpy(buff + offset, &PositionField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, Position, sizeof(PositionField));
		offset += sizeof(PositionField);
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
bool RspQryPositionPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case PositionField::FieldID:
		{
			Position = ::Allocate<PositionField>();
			memcpy(Position, buff + offset, sizeof(PositionField));
			offset += sizeof(PositionField);	
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
const char* RspQryPositionPackage::GetDebugString() const
{
	int offset = 0;
	if (Position != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "Position:TradingDay:[%s], AccountID:[%s], AccountType:[%d], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], PosiDirection:[%d], TotalPosition:[%lld], PositionFrozen:[%lld], TodayPosition:[%lld], MarketValue:[%f], CashIn:[%f], CashOut:[%f], Margin:[%f], Commission:[%f], VolumeMultiple:[%d], CloseProfitByDate:[%f], CloseProfitByTrade:[%f], PositionProfitByDate:[%f], PositionProfitByTrade:[%f], LastPrice:[%f], PreSettlementPrice:[%f]", Position->TradingDay, Position->AccountID, (int)Position->AccountType, Position->ExchangeID, Position->InstrumentID, (int)Position->ProductClass, (int)Position->PosiDirection, Position->TotalPosition, Position->PositionFrozen, Position->TodayPosition, Position->MarketValue, Position->CashIn, Position->CashOut, Position->Margin, Position->Commission, Position->VolumeMultiple, Position->CloseProfitByDate, Position->CloseProfitByTrade, Position->PositionProfitByDate, Position->PositionProfitByTrade, Position->LastPrice, Position->PreSettlementPrice);
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
 
ReqQryOptionInstrumentPackage* ReqQryOptionInstrumentPackage::Allocate()
{
	return ::Allocate<ReqQryOptionInstrumentPackage>();
}
void ReqQryOptionInstrumentPackage::Free()
{
	Package::Free();
	if (ReqQryOptionInstrument != nullptr)
	{
		::Free<ReqQryOptionInstrumentField>(ReqQryOptionInstrument);
		ReqQryOptionInstrument = nullptr;
	}
	MemCacheTemplateSingleton<ReqQryOptionInstrumentPackage>::GetInstance().Free(this);
}
void ReqQryOptionInstrumentPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqQryOptionInstrumentPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqQryOptionInstrument != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqQryOptionInstrumentField::FieldID);
		if (strlen(ReqQryOptionInstrument->ExchangeID) >= sizeof(ReqQryOptionInstrument->ExchangeID))
		{
			ReqQryOptionInstrument->ExchangeID[sizeof(ReqQryOptionInstrument->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, ReqQryOptionInstrument->ExchangeID);
		if (strlen(ReqQryOptionInstrument->InstrumentID) >= sizeof(ReqQryOptionInstrument->InstrumentID))
		{
			ReqQryOptionInstrument->InstrumentID[sizeof(ReqQryOptionInstrument->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, ReqQryOptionInstrument->InstrumentID);
		WriteHexString(ppos, Items::FieldEnd, ReqQryOptionInstrumentField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqQryOptionInstrumentPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqQryOptionInstrumentField::FieldID:
			{
				ReqQryOptionInstrument = ::Allocate<ReqQryOptionInstrumentField>();
				memset(ReqQryOptionInstrument, 0, sizeof(*ReqQryOptionInstrument));
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
							size_t len = value.length() >= sizeof(ReqQryOptionInstrument->ExchangeID) ? sizeof(ReqQryOptionInstrument->ExchangeID) - 1 : value.length();
							memcpy(ReqQryOptionInstrument->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(ReqQryOptionInstrument->InstrumentID) ? sizeof(ReqQryOptionInstrument->InstrumentID) - 1 : value.length();
							memcpy(ReqQryOptionInstrument->InstrumentID, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqQryOptionInstrumentField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqQryOptionInstrumentPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqQryOptionInstrumentPackage");
			return false;
		}
	}
	return true;
}
int ReqQryOptionInstrumentPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqQryOptionInstrument != nullptr)
	{
		memcpy(buff + offset, &ReqQryOptionInstrumentField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqQryOptionInstrument, sizeof(ReqQryOptionInstrumentField));
		offset += sizeof(ReqQryOptionInstrumentField);
	}
	return offset;
}
bool ReqQryOptionInstrumentPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqQryOptionInstrumentField::FieldID:
		{
			ReqQryOptionInstrument = ::Allocate<ReqQryOptionInstrumentField>();
			memcpy(ReqQryOptionInstrument, buff + offset, sizeof(ReqQryOptionInstrumentField));
			offset += sizeof(ReqQryOptionInstrumentField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqQryOptionInstrumentPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqQryOptionInstrument != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqQryOptionInstrument:ExchangeID:[%s], InstrumentID:[%s]", ReqQryOptionInstrument->ExchangeID, ReqQryOptionInstrument->InstrumentID);
	}
	return t_DataStringBuffer;
}
 
RspQryOptionInstrumentPackage* RspQryOptionInstrumentPackage::Allocate()
{
	return ::Allocate<RspQryOptionInstrumentPackage>();
}
void RspQryOptionInstrumentPackage::Free()
{
	Package::Free();
	if (OptionInstrument != nullptr)
	{
		::Free<OptionInstrumentField>(OptionInstrument);
		OptionInstrument = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspQryOptionInstrumentPackage>::GetInstance().Free(this);
}
void RspQryOptionInstrumentPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspQryOptionInstrumentPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (OptionInstrument != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, OptionInstrumentField::FieldID);
		if (strlen(OptionInstrument->ExchangeID) >= sizeof(OptionInstrument->ExchangeID))
		{
			OptionInstrument->ExchangeID[sizeof(OptionInstrument->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, OptionInstrument->ExchangeID);
		if (strlen(OptionInstrument->InstrumentID) >= sizeof(OptionInstrument->InstrumentID))
		{
			OptionInstrument->InstrumentID[sizeof(OptionInstrument->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, OptionInstrument->InstrumentID);
		if (strlen(OptionInstrument->ExchangeInstID) >= sizeof(OptionInstrument->ExchangeInstID))
		{
			OptionInstrument->ExchangeInstID[sizeof(OptionInstrument->ExchangeInstID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeInstID, OptionInstrument->ExchangeInstID);
		if (strlen(OptionInstrument->InstrumentName) >= sizeof(OptionInstrument->InstrumentName))
		{
			OptionInstrument->InstrumentName[sizeof(OptionInstrument->InstrumentName) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentName, OptionInstrument->InstrumentName);
		WriteString(ppos, Items::VolumeMultiple, OptionInstrument->VolumeMultiple);
		WriteString(ppos, Items::OptionType, (int)OptionInstrument->OptionType);
		if (strlen(OptionInstrument->UnderlyingInstrumentID) >= sizeof(OptionInstrument->UnderlyingInstrumentID))
		{
			OptionInstrument->UnderlyingInstrumentID[sizeof(OptionInstrument->UnderlyingInstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::UnderlyingInstrumentID, OptionInstrument->UnderlyingInstrumentID);
		WriteString(ppos, Items::ExecutePrice, OptionInstrument->ExecutePrice);
		WriteString(ppos, Items::UnitMargin, OptionInstrument->UnitMargin);
		WriteString(ppos, Items::PriceTick, OptionInstrument->PriceTick);
		WriteString(ppos, Items::MaxLimitOrderVolume, OptionInstrument->MaxLimitOrderVolume);
		WriteString(ppos, Items::MaxMarketOrderVolume, OptionInstrument->MaxMarketOrderVolume);
		if (strlen(OptionInstrument->ExpiringDate) >= sizeof(OptionInstrument->ExpiringDate))
		{
			OptionInstrument->ExpiringDate[sizeof(OptionInstrument->ExpiringDate) - 1] = 0;
		}
		WriteString(ppos, Items::ExpiringDate, OptionInstrument->ExpiringDate);
		WriteHexString(ppos, Items::FieldEnd, OptionInstrumentField::FieldID);
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
bool RspQryOptionInstrumentPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case OptionInstrumentField::FieldID:
			{
				OptionInstrument = ::Allocate<OptionInstrumentField>();
				memset(OptionInstrument, 0, sizeof(*OptionInstrument));
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
							size_t len = value.length() >= sizeof(OptionInstrument->ExchangeID) ? sizeof(OptionInstrument->ExchangeID) - 1 : value.length();
							memcpy(OptionInstrument->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(OptionInstrument->InstrumentID) ? sizeof(OptionInstrument->InstrumentID) - 1 : value.length();
							memcpy(OptionInstrument->InstrumentID, value.c_str(), len);
							break;
						}
						case Items::ExchangeInstID:
						{
							size_t len = value.length() >= sizeof(OptionInstrument->ExchangeInstID) ? sizeof(OptionInstrument->ExchangeInstID) - 1 : value.length();
							memcpy(OptionInstrument->ExchangeInstID, value.c_str(), len);
							break;
						}
						case Items::InstrumentName:
						{
							size_t len = value.length() >= sizeof(OptionInstrument->InstrumentName) ? sizeof(OptionInstrument->InstrumentName) - 1 : value.length();
							memcpy(OptionInstrument->InstrumentName, value.c_str(), len);
							break;
						}
						case Items::VolumeMultiple:
						{
							OptionInstrument->VolumeMultiple = atoi(value.c_str());
							break;
						}
						case Items::OptionType:
						{
							OptionInstrument->OptionType = (OptionTypeType)(atoi(value.c_str()));
							break;
						}
						case Items::UnderlyingInstrumentID:
						{
							size_t len = value.length() >= sizeof(OptionInstrument->UnderlyingInstrumentID) ? sizeof(OptionInstrument->UnderlyingInstrumentID) - 1 : value.length();
							memcpy(OptionInstrument->UnderlyingInstrumentID, value.c_str(), len);
							break;
						}
						case Items::ExecutePrice:
						{
							OptionInstrument->ExecutePrice = atof(value.c_str());
							break;
						}
						case Items::UnitMargin:
						{
							OptionInstrument->UnitMargin = atof(value.c_str());
							break;
						}
						case Items::PriceTick:
						{
							OptionInstrument->PriceTick = atof(value.c_str());
							break;
						}
						case Items::MaxLimitOrderVolume:
						{
							OptionInstrument->MaxLimitOrderVolume = atoll(value.c_str());
							break;
						}
						case Items::MaxMarketOrderVolume:
						{
							OptionInstrument->MaxMarketOrderVolume = atoll(value.c_str());
							break;
						}
						case Items::ExpiringDate:
						{
							size_t len = value.length() >= sizeof(OptionInstrument->ExpiringDate) ? sizeof(OptionInstrument->ExpiringDate) - 1 : value.length();
							memcpy(OptionInstrument->ExpiringDate, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for OptionInstrumentField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryOptionInstrumentPackage FieldID:0x%X", fieldID);
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
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryOptionInstrumentPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspQryOptionInstrumentPackage");
			return false;
		}
	}
	return true;
}
int RspQryOptionInstrumentPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (OptionInstrument != nullptr)
	{
		memcpy(buff + offset, &OptionInstrumentField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, OptionInstrument, sizeof(OptionInstrumentField));
		offset += sizeof(OptionInstrumentField);
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
bool RspQryOptionInstrumentPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case OptionInstrumentField::FieldID:
		{
			OptionInstrument = ::Allocate<OptionInstrumentField>();
			memcpy(OptionInstrument, buff + offset, sizeof(OptionInstrumentField));
			offset += sizeof(OptionInstrumentField);	
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
const char* RspQryOptionInstrumentPackage::GetDebugString() const
{
	int offset = 0;
	if (OptionInstrument != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "OptionInstrument:ExchangeID:[%s], InstrumentID:[%s], ExchangeInstID:[%s], InstrumentName:[%s], VolumeMultiple:[%d], OptionType:[%d], UnderlyingInstrumentID:[%s], ExecutePrice:[%f], UnitMargin:[%f], PriceTick:[%f], MaxLimitOrderVolume:[%lld], MaxMarketOrderVolume:[%lld], ExpiringDate:[%s]", OptionInstrument->ExchangeID, OptionInstrument->InstrumentID, OptionInstrument->ExchangeInstID, OptionInstrument->InstrumentName, OptionInstrument->VolumeMultiple, (int)OptionInstrument->OptionType, OptionInstrument->UnderlyingInstrumentID, OptionInstrument->ExecutePrice, OptionInstrument->UnitMargin, OptionInstrument->PriceTick, OptionInstrument->MaxLimitOrderVolume, OptionInstrument->MaxMarketOrderVolume, OptionInstrument->ExpiringDate);
	}
	if (RspInfo != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
	return t_DataStringBuffer;
}
 
ReqQryCommissionRatePackage* ReqQryCommissionRatePackage::Allocate()
{
	return ::Allocate<ReqQryCommissionRatePackage>();
}
void ReqQryCommissionRatePackage::Free()
{
	Package::Free();
	if (ReqQryCommissionRate != nullptr)
	{
		::Free<ReqQryCommissionRateField>(ReqQryCommissionRate);
		ReqQryCommissionRate = nullptr;
	}
	MemCacheTemplateSingleton<ReqQryCommissionRatePackage>::GetInstance().Free(this);
}
void ReqQryCommissionRatePackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqQryCommissionRatePackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqQryCommissionRate != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqQryCommissionRateField::FieldID);
		if (strlen(ReqQryCommissionRate->AccountID) >= sizeof(ReqQryCommissionRate->AccountID))
		{
			ReqQryCommissionRate->AccountID[sizeof(ReqQryCommissionRate->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, ReqQryCommissionRate->AccountID);
		if (strlen(ReqQryCommissionRate->ExchangeID) >= sizeof(ReqQryCommissionRate->ExchangeID))
		{
			ReqQryCommissionRate->ExchangeID[sizeof(ReqQryCommissionRate->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, ReqQryCommissionRate->ExchangeID);
		WriteString(ppos, Items::ProductClass, (int)ReqQryCommissionRate->ProductClass);
		WriteHexString(ppos, Items::FieldEnd, ReqQryCommissionRateField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqQryCommissionRatePackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqQryCommissionRateField::FieldID:
			{
				ReqQryCommissionRate = ::Allocate<ReqQryCommissionRateField>();
				memset(ReqQryCommissionRate, 0, sizeof(*ReqQryCommissionRate));
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
							size_t len = value.length() >= sizeof(ReqQryCommissionRate->AccountID) ? sizeof(ReqQryCommissionRate->AccountID) - 1 : value.length();
							memcpy(ReqQryCommissionRate->AccountID, value.c_str(), len);
							break;
						}
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(ReqQryCommissionRate->ExchangeID) ? sizeof(ReqQryCommissionRate->ExchangeID) - 1 : value.length();
							memcpy(ReqQryCommissionRate->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::ProductClass:
						{
							ReqQryCommissionRate->ProductClass = (ProductClassType)(atoi(value.c_str()));
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqQryCommissionRateField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqQryCommissionRatePackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqQryCommissionRatePackage");
			return false;
		}
	}
	return true;
}
int ReqQryCommissionRatePackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqQryCommissionRate != nullptr)
	{
		memcpy(buff + offset, &ReqQryCommissionRateField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqQryCommissionRate, sizeof(ReqQryCommissionRateField));
		offset += sizeof(ReqQryCommissionRateField);
	}
	return offset;
}
bool ReqQryCommissionRatePackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqQryCommissionRateField::FieldID:
		{
			ReqQryCommissionRate = ::Allocate<ReqQryCommissionRateField>();
			memcpy(ReqQryCommissionRate, buff + offset, sizeof(ReqQryCommissionRateField));
			offset += sizeof(ReqQryCommissionRateField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqQryCommissionRatePackage::GetDebugString() const
{
	int offset = 0;
	if (ReqQryCommissionRate != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqQryCommissionRate:AccountID:[%s], ExchangeID:[%s], ProductClass:[%d]", ReqQryCommissionRate->AccountID, ReqQryCommissionRate->ExchangeID, (int)ReqQryCommissionRate->ProductClass);
	}
	return t_DataStringBuffer;
}
 
RspQryCommissionRatePackage* RspQryCommissionRatePackage::Allocate()
{
	return ::Allocate<RspQryCommissionRatePackage>();
}
void RspQryCommissionRatePackage::Free()
{
	Package::Free();
	if (CommissionRate != nullptr)
	{
		::Free<CommissionRateField>(CommissionRate);
		CommissionRate = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspQryCommissionRatePackage>::GetInstance().Free(this);
}
void RspQryCommissionRatePackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspQryCommissionRatePackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (CommissionRate != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, CommissionRateField::FieldID);
		if (strlen(CommissionRate->AccountID) >= sizeof(CommissionRate->AccountID))
		{
			CommissionRate->AccountID[sizeof(CommissionRate->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, CommissionRate->AccountID);
		if (strlen(CommissionRate->ExchangeID) >= sizeof(CommissionRate->ExchangeID))
		{
			CommissionRate->ExchangeID[sizeof(CommissionRate->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, CommissionRate->ExchangeID);
		WriteString(ppos, Items::ProductClass, (int)CommissionRate->ProductClass);
		WriteString(ppos, Items::OpenBuyByMoney, CommissionRate->OpenBuyByMoney);
		WriteString(ppos, Items::OpenSellByMoney, CommissionRate->OpenSellByMoney);
		WriteString(ppos, Items::CloseBuyByMoney, CommissionRate->CloseBuyByMoney);
		WriteString(ppos, Items::CloseSellByMoney, CommissionRate->CloseSellByMoney);
		WriteString(ppos, Items::OpenBuyByVolume, CommissionRate->OpenBuyByVolume);
		WriteString(ppos, Items::OpenSellByVolume, CommissionRate->OpenSellByVolume);
		WriteString(ppos, Items::CloseBuyByVolume, CommissionRate->CloseBuyByVolume);
		WriteString(ppos, Items::CloseSellByVolume, CommissionRate->CloseSellByVolume);
		WriteString(ppos, Items::MinCommission, CommissionRate->MinCommission);
		WriteString(ppos, Items::MaxCommission, CommissionRate->MaxCommission);
		WriteHexString(ppos, Items::FieldEnd, CommissionRateField::FieldID);
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
bool RspQryCommissionRatePackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case CommissionRateField::FieldID:
			{
				CommissionRate = ::Allocate<CommissionRateField>();
				memset(CommissionRate, 0, sizeof(*CommissionRate));
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
							size_t len = value.length() >= sizeof(CommissionRate->AccountID) ? sizeof(CommissionRate->AccountID) - 1 : value.length();
							memcpy(CommissionRate->AccountID, value.c_str(), len);
							break;
						}
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(CommissionRate->ExchangeID) ? sizeof(CommissionRate->ExchangeID) - 1 : value.length();
							memcpy(CommissionRate->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::ProductClass:
						{
							CommissionRate->ProductClass = (ProductClassType)(atoi(value.c_str()));
							break;
						}
						case Items::OpenBuyByMoney:
						{
							CommissionRate->OpenBuyByMoney = atof(value.c_str());
							break;
						}
						case Items::OpenSellByMoney:
						{
							CommissionRate->OpenSellByMoney = atof(value.c_str());
							break;
						}
						case Items::CloseBuyByMoney:
						{
							CommissionRate->CloseBuyByMoney = atof(value.c_str());
							break;
						}
						case Items::CloseSellByMoney:
						{
							CommissionRate->CloseSellByMoney = atof(value.c_str());
							break;
						}
						case Items::OpenBuyByVolume:
						{
							CommissionRate->OpenBuyByVolume = atof(value.c_str());
							break;
						}
						case Items::OpenSellByVolume:
						{
							CommissionRate->OpenSellByVolume = atof(value.c_str());
							break;
						}
						case Items::CloseBuyByVolume:
						{
							CommissionRate->CloseBuyByVolume = atof(value.c_str());
							break;
						}
						case Items::CloseSellByVolume:
						{
							CommissionRate->CloseSellByVolume = atof(value.c_str());
							break;
						}
						case Items::MinCommission:
						{
							CommissionRate->MinCommission = atof(value.c_str());
							break;
						}
						case Items::MaxCommission:
						{
							CommissionRate->MaxCommission = atof(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for CommissionRateField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryCommissionRatePackage FieldID:0x%X", fieldID);
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
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryCommissionRatePackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspQryCommissionRatePackage");
			return false;
		}
	}
	return true;
}
int RspQryCommissionRatePackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (CommissionRate != nullptr)
	{
		memcpy(buff + offset, &CommissionRateField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, CommissionRate, sizeof(CommissionRateField));
		offset += sizeof(CommissionRateField);
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
bool RspQryCommissionRatePackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case CommissionRateField::FieldID:
		{
			CommissionRate = ::Allocate<CommissionRateField>();
			memcpy(CommissionRate, buff + offset, sizeof(CommissionRateField));
			offset += sizeof(CommissionRateField);	
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
const char* RspQryCommissionRatePackage::GetDebugString() const
{
	int offset = 0;
	if (CommissionRate != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "CommissionRate:AccountID:[%s], ExchangeID:[%s], ProductClass:[%d], OpenBuyByMoney:[%f], OpenSellByMoney:[%f], CloseBuyByMoney:[%f], CloseSellByMoney:[%f], OpenBuyByVolume:[%f], OpenSellByVolume:[%f], CloseBuyByVolume:[%f], CloseSellByVolume:[%f], MinCommission:[%f], MaxCommission:[%f]", CommissionRate->AccountID, CommissionRate->ExchangeID, (int)CommissionRate->ProductClass, CommissionRate->OpenBuyByMoney, CommissionRate->OpenSellByMoney, CommissionRate->CloseBuyByMoney, CommissionRate->CloseSellByMoney, CommissionRate->OpenBuyByVolume, CommissionRate->OpenSellByVolume, CommissionRate->CloseBuyByVolume, CommissionRate->CloseSellByVolume, CommissionRate->MinCommission, CommissionRate->MaxCommission);
	}
	if (RspInfo != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
	return t_DataStringBuffer;
}
 
ReqQryMoneyTransferPackage* ReqQryMoneyTransferPackage::Allocate()
{
	return ::Allocate<ReqQryMoneyTransferPackage>();
}
void ReqQryMoneyTransferPackage::Free()
{
	Package::Free();
	if (ReqQryMoneyTransfer != nullptr)
	{
		::Free<ReqQryMoneyTransferField>(ReqQryMoneyTransfer);
		ReqQryMoneyTransfer = nullptr;
	}
	MemCacheTemplateSingleton<ReqQryMoneyTransferPackage>::GetInstance().Free(this);
}
void ReqQryMoneyTransferPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqQryMoneyTransferPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqQryMoneyTransfer != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqQryMoneyTransferField::FieldID);
		if (strlen(ReqQryMoneyTransfer->AccountID) >= sizeof(ReqQryMoneyTransfer->AccountID))
		{
			ReqQryMoneyTransfer->AccountID[sizeof(ReqQryMoneyTransfer->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, ReqQryMoneyTransfer->AccountID);
		WriteHexString(ppos, Items::FieldEnd, ReqQryMoneyTransferField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqQryMoneyTransferPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqQryMoneyTransferField::FieldID:
			{
				ReqQryMoneyTransfer = ::Allocate<ReqQryMoneyTransferField>();
				memset(ReqQryMoneyTransfer, 0, sizeof(*ReqQryMoneyTransfer));
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
							size_t len = value.length() >= sizeof(ReqQryMoneyTransfer->AccountID) ? sizeof(ReqQryMoneyTransfer->AccountID) - 1 : value.length();
							memcpy(ReqQryMoneyTransfer->AccountID, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqQryMoneyTransferField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqQryMoneyTransferPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqQryMoneyTransferPackage");
			return false;
		}
	}
	return true;
}
int ReqQryMoneyTransferPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqQryMoneyTransfer != nullptr)
	{
		memcpy(buff + offset, &ReqQryMoneyTransferField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqQryMoneyTransfer, sizeof(ReqQryMoneyTransferField));
		offset += sizeof(ReqQryMoneyTransferField);
	}
	return offset;
}
bool ReqQryMoneyTransferPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqQryMoneyTransferField::FieldID:
		{
			ReqQryMoneyTransfer = ::Allocate<ReqQryMoneyTransferField>();
			memcpy(ReqQryMoneyTransfer, buff + offset, sizeof(ReqQryMoneyTransferField));
			offset += sizeof(ReqQryMoneyTransferField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqQryMoneyTransferPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqQryMoneyTransfer != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqQryMoneyTransfer:AccountID:[%s]", ReqQryMoneyTransfer->AccountID);
	}
	return t_DataStringBuffer;
}
 
RspQryMoneyTransferPackage* RspQryMoneyTransferPackage::Allocate()
{
	return ::Allocate<RspQryMoneyTransferPackage>();
}
void RspQryMoneyTransferPackage::Free()
{
	Package::Free();
	if (MoneyTransfer != nullptr)
	{
		::Free<MoneyTransferField>(MoneyTransfer);
		MoneyTransfer = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspQryMoneyTransferPackage>::GetInstance().Free(this);
}
void RspQryMoneyTransferPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspQryMoneyTransferPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (MoneyTransfer != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, MoneyTransferField::FieldID);
		if (strlen(MoneyTransfer->TradingDay) >= sizeof(MoneyTransfer->TradingDay))
		{
			MoneyTransfer->TradingDay[sizeof(MoneyTransfer->TradingDay) - 1] = 0;
		}
		WriteString(ppos, Items::TradingDay, MoneyTransfer->TradingDay);
		if (strlen(MoneyTransfer->AccountID) >= sizeof(MoneyTransfer->AccountID))
		{
			MoneyTransfer->AccountID[sizeof(MoneyTransfer->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, MoneyTransfer->AccountID);
		WriteString(ppos, Items::MoneyTransferID, MoneyTransfer->MoneyTransferID);
		WriteString(ppos, Items::AccountType, (int)MoneyTransfer->AccountType);
		WriteString(ppos, Items::TransferDirection, (int)MoneyTransfer->TransferDirection);
		WriteString(ppos, Items::TransferAmount, MoneyTransfer->TransferAmount);
		if (strlen(MoneyTransfer->InfoMessage) >= sizeof(MoneyTransfer->InfoMessage))
		{
			MoneyTransfer->InfoMessage[sizeof(MoneyTransfer->InfoMessage) - 1] = 0;
		}
		WriteString(ppos, Items::InfoMessage, MoneyTransfer->InfoMessage);
		if (strlen(MoneyTransfer->UserID) >= sizeof(MoneyTransfer->UserID))
		{
			MoneyTransfer->UserID[sizeof(MoneyTransfer->UserID) - 1] = 0;
		}
		WriteString(ppos, Items::UserID, MoneyTransfer->UserID);
		if (strlen(MoneyTransfer->TransferDate) >= sizeof(MoneyTransfer->TransferDate))
		{
			MoneyTransfer->TransferDate[sizeof(MoneyTransfer->TransferDate) - 1] = 0;
		}
		WriteString(ppos, Items::TransferDate, MoneyTransfer->TransferDate);
		if (strlen(MoneyTransfer->TransferTime) >= sizeof(MoneyTransfer->TransferTime))
		{
			MoneyTransfer->TransferTime[sizeof(MoneyTransfer->TransferTime) - 1] = 0;
		}
		WriteString(ppos, Items::TransferTime, MoneyTransfer->TransferTime);
		WriteHexString(ppos, Items::FieldEnd, MoneyTransferField::FieldID);
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
bool RspQryMoneyTransferPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case MoneyTransferField::FieldID:
			{
				MoneyTransfer = ::Allocate<MoneyTransferField>();
				memset(MoneyTransfer, 0, sizeof(*MoneyTransfer));
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
							size_t len = value.length() >= sizeof(MoneyTransfer->TradingDay) ? sizeof(MoneyTransfer->TradingDay) - 1 : value.length();
							memcpy(MoneyTransfer->TradingDay, value.c_str(), len);
							break;
						}
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(MoneyTransfer->AccountID) ? sizeof(MoneyTransfer->AccountID) - 1 : value.length();
							memcpy(MoneyTransfer->AccountID, value.c_str(), len);
							break;
						}
						case Items::MoneyTransferID:
						{
							MoneyTransfer->MoneyTransferID = atoi(value.c_str());
							break;
						}
						case Items::AccountType:
						{
							MoneyTransfer->AccountType = (AccountTypeType)(atoi(value.c_str()));
							break;
						}
						case Items::TransferDirection:
						{
							MoneyTransfer->TransferDirection = (TransferDirectionType)(atoi(value.c_str()));
							break;
						}
						case Items::TransferAmount:
						{
							MoneyTransfer->TransferAmount = atof(value.c_str());
							break;
						}
						case Items::InfoMessage:
						{
							size_t len = value.length() >= sizeof(MoneyTransfer->InfoMessage) ? sizeof(MoneyTransfer->InfoMessage) - 1 : value.length();
							memcpy(MoneyTransfer->InfoMessage, value.c_str(), len);
							break;
						}
						case Items::UserID:
						{
							size_t len = value.length() >= sizeof(MoneyTransfer->UserID) ? sizeof(MoneyTransfer->UserID) - 1 : value.length();
							memcpy(MoneyTransfer->UserID, value.c_str(), len);
							break;
						}
						case Items::TransferDate:
						{
							size_t len = value.length() >= sizeof(MoneyTransfer->TransferDate) ? sizeof(MoneyTransfer->TransferDate) - 1 : value.length();
							memcpy(MoneyTransfer->TransferDate, value.c_str(), len);
							break;
						}
						case Items::TransferTime:
						{
							size_t len = value.length() >= sizeof(MoneyTransfer->TransferTime) ? sizeof(MoneyTransfer->TransferTime) - 1 : value.length();
							memcpy(MoneyTransfer->TransferTime, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for MoneyTransferField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryMoneyTransferPackage FieldID:0x%X", fieldID);
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
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryMoneyTransferPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspQryMoneyTransferPackage");
			return false;
		}
	}
	return true;
}
int RspQryMoneyTransferPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (MoneyTransfer != nullptr)
	{
		memcpy(buff + offset, &MoneyTransferField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, MoneyTransfer, sizeof(MoneyTransferField));
		offset += sizeof(MoneyTransferField);
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
bool RspQryMoneyTransferPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case MoneyTransferField::FieldID:
		{
			MoneyTransfer = ::Allocate<MoneyTransferField>();
			memcpy(MoneyTransfer, buff + offset, sizeof(MoneyTransferField));
			offset += sizeof(MoneyTransferField);	
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
const char* RspQryMoneyTransferPackage::GetDebugString() const
{
	int offset = 0;
	if (MoneyTransfer != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "MoneyTransfer:TradingDay:[%s], AccountID:[%s], MoneyTransferID:[%d], AccountType:[%d], TransferDirection:[%d], TransferAmount:[%f], InfoMessage:[%s], UserID:[%s], TransferDate:[%s], TransferTime:[%s]", MoneyTransfer->TradingDay, MoneyTransfer->AccountID, MoneyTransfer->MoneyTransferID, (int)MoneyTransfer->AccountType, (int)MoneyTransfer->TransferDirection, MoneyTransfer->TransferAmount, MoneyTransfer->InfoMessage, MoneyTransfer->UserID, MoneyTransfer->TransferDate, MoneyTransfer->TransferTime);
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
 
RtnMoneyTransferPackage* RtnMoneyTransferPackage::Allocate()
{
	return ::Allocate<RtnMoneyTransferPackage>();
}
void RtnMoneyTransferPackage::Free()
{
	Package::Free();
	if (MoneyTransfer != nullptr)
	{
		::Free<MoneyTransferField>(MoneyTransfer);
		MoneyTransfer = nullptr;
	}
	MemCacheTemplateSingleton<RtnMoneyTransferPackage>::GetInstance().Free(this);
}
void RtnMoneyTransferPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RtnMoneyTransferPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (MoneyTransfer != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, MoneyTransferField::FieldID);
		if (strlen(MoneyTransfer->TradingDay) >= sizeof(MoneyTransfer->TradingDay))
		{
			MoneyTransfer->TradingDay[sizeof(MoneyTransfer->TradingDay) - 1] = 0;
		}
		WriteString(ppos, Items::TradingDay, MoneyTransfer->TradingDay);
		if (strlen(MoneyTransfer->AccountID) >= sizeof(MoneyTransfer->AccountID))
		{
			MoneyTransfer->AccountID[sizeof(MoneyTransfer->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, MoneyTransfer->AccountID);
		WriteString(ppos, Items::MoneyTransferID, MoneyTransfer->MoneyTransferID);
		WriteString(ppos, Items::AccountType, (int)MoneyTransfer->AccountType);
		WriteString(ppos, Items::TransferDirection, (int)MoneyTransfer->TransferDirection);
		WriteString(ppos, Items::TransferAmount, MoneyTransfer->TransferAmount);
		if (strlen(MoneyTransfer->InfoMessage) >= sizeof(MoneyTransfer->InfoMessage))
		{
			MoneyTransfer->InfoMessage[sizeof(MoneyTransfer->InfoMessage) - 1] = 0;
		}
		WriteString(ppos, Items::InfoMessage, MoneyTransfer->InfoMessage);
		if (strlen(MoneyTransfer->UserID) >= sizeof(MoneyTransfer->UserID))
		{
			MoneyTransfer->UserID[sizeof(MoneyTransfer->UserID) - 1] = 0;
		}
		WriteString(ppos, Items::UserID, MoneyTransfer->UserID);
		if (strlen(MoneyTransfer->TransferDate) >= sizeof(MoneyTransfer->TransferDate))
		{
			MoneyTransfer->TransferDate[sizeof(MoneyTransfer->TransferDate) - 1] = 0;
		}
		WriteString(ppos, Items::TransferDate, MoneyTransfer->TransferDate);
		if (strlen(MoneyTransfer->TransferTime) >= sizeof(MoneyTransfer->TransferTime))
		{
			MoneyTransfer->TransferTime[sizeof(MoneyTransfer->TransferTime) - 1] = 0;
		}
		WriteString(ppos, Items::TransferTime, MoneyTransfer->TransferTime);
		WriteHexString(ppos, Items::FieldEnd, MoneyTransferField::FieldID);
	}
	return int(ppos - buff);
}
bool RtnMoneyTransferPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case MoneyTransferField::FieldID:
			{
				MoneyTransfer = ::Allocate<MoneyTransferField>();
				memset(MoneyTransfer, 0, sizeof(*MoneyTransfer));
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
							size_t len = value.length() >= sizeof(MoneyTransfer->TradingDay) ? sizeof(MoneyTransfer->TradingDay) - 1 : value.length();
							memcpy(MoneyTransfer->TradingDay, value.c_str(), len);
							break;
						}
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(MoneyTransfer->AccountID) ? sizeof(MoneyTransfer->AccountID) - 1 : value.length();
							memcpy(MoneyTransfer->AccountID, value.c_str(), len);
							break;
						}
						case Items::MoneyTransferID:
						{
							MoneyTransfer->MoneyTransferID = atoi(value.c_str());
							break;
						}
						case Items::AccountType:
						{
							MoneyTransfer->AccountType = (AccountTypeType)(atoi(value.c_str()));
							break;
						}
						case Items::TransferDirection:
						{
							MoneyTransfer->TransferDirection = (TransferDirectionType)(atoi(value.c_str()));
							break;
						}
						case Items::TransferAmount:
						{
							MoneyTransfer->TransferAmount = atof(value.c_str());
							break;
						}
						case Items::InfoMessage:
						{
							size_t len = value.length() >= sizeof(MoneyTransfer->InfoMessage) ? sizeof(MoneyTransfer->InfoMessage) - 1 : value.length();
							memcpy(MoneyTransfer->InfoMessage, value.c_str(), len);
							break;
						}
						case Items::UserID:
						{
							size_t len = value.length() >= sizeof(MoneyTransfer->UserID) ? sizeof(MoneyTransfer->UserID) - 1 : value.length();
							memcpy(MoneyTransfer->UserID, value.c_str(), len);
							break;
						}
						case Items::TransferDate:
						{
							size_t len = value.length() >= sizeof(MoneyTransfer->TransferDate) ? sizeof(MoneyTransfer->TransferDate) - 1 : value.length();
							memcpy(MoneyTransfer->TransferDate, value.c_str(), len);
							break;
						}
						case Items::TransferTime:
						{
							size_t len = value.length() >= sizeof(MoneyTransfer->TransferTime) ? sizeof(MoneyTransfer->TransferTime) - 1 : value.length();
							memcpy(MoneyTransfer->TransferTime, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for MoneyTransferField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RtnMoneyTransferPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RtnMoneyTransferPackage");
			return false;
		}
	}
	return true;
}
int RtnMoneyTransferPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (MoneyTransfer != nullptr)
	{
		memcpy(buff + offset, &MoneyTransferField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, MoneyTransfer, sizeof(MoneyTransferField));
		offset += sizeof(MoneyTransferField);
	}
	return offset;
}
bool RtnMoneyTransferPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case MoneyTransferField::FieldID:
		{
			MoneyTransfer = ::Allocate<MoneyTransferField>();
			memcpy(MoneyTransfer, buff + offset, sizeof(MoneyTransferField));
			offset += sizeof(MoneyTransferField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* RtnMoneyTransferPackage::GetDebugString() const
{
	int offset = 0;
	if (MoneyTransfer != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "MoneyTransfer:TradingDay:[%s], AccountID:[%s], MoneyTransferID:[%d], AccountType:[%d], TransferDirection:[%d], TransferAmount:[%f], InfoMessage:[%s], UserID:[%s], TransferDate:[%s], TransferTime:[%s]", MoneyTransfer->TradingDay, MoneyTransfer->AccountID, MoneyTransfer->MoneyTransferID, (int)MoneyTransfer->AccountType, (int)MoneyTransfer->TransferDirection, MoneyTransfer->TransferAmount, MoneyTransfer->InfoMessage, MoneyTransfer->UserID, MoneyTransfer->TransferDate, MoneyTransfer->TransferTime);
	}
	return t_DataStringBuffer;
}
 
RtnAccountLogoutPackage* RtnAccountLogoutPackage::Allocate()
{
	return ::Allocate<RtnAccountLogoutPackage>();
}
void RtnAccountLogoutPackage::Free()
{
	Package::Free();
	if (AccountLogout != nullptr)
	{
		::Free<AccountLogoutField>(AccountLogout);
		AccountLogout = nullptr;
	}
	MemCacheTemplateSingleton<RtnAccountLogoutPackage>::GetInstance().Free(this);
}
void RtnAccountLogoutPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RtnAccountLogoutPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (AccountLogout != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, AccountLogoutField::FieldID);
		if (strlen(AccountLogout->AccountID) >= sizeof(AccountLogout->AccountID))
		{
			AccountLogout->AccountID[sizeof(AccountLogout->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, AccountLogout->AccountID);
		WriteString(ppos, Items::ErrorID, AccountLogout->ErrorID);
		if (strlen(AccountLogout->ErrorMsg) >= sizeof(AccountLogout->ErrorMsg))
		{
			AccountLogout->ErrorMsg[sizeof(AccountLogout->ErrorMsg) - 1] = 0;
		}
		WriteString(ppos, Items::ErrorMsg, AccountLogout->ErrorMsg);
		WriteHexString(ppos, Items::FieldEnd, AccountLogoutField::FieldID);
	}
	return int(ppos - buff);
}
bool RtnAccountLogoutPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case AccountLogoutField::FieldID:
			{
				AccountLogout = ::Allocate<AccountLogoutField>();
				memset(AccountLogout, 0, sizeof(*AccountLogout));
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
							size_t len = value.length() >= sizeof(AccountLogout->AccountID) ? sizeof(AccountLogout->AccountID) - 1 : value.length();
							memcpy(AccountLogout->AccountID, value.c_str(), len);
							break;
						}
						case Items::ErrorID:
						{
							AccountLogout->ErrorID = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(AccountLogout->ErrorMsg) ? sizeof(AccountLogout->ErrorMsg) - 1 : value.length();
							memcpy(AccountLogout->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for AccountLogoutField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RtnAccountLogoutPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RtnAccountLogoutPackage");
			return false;
		}
	}
	return true;
}
int RtnAccountLogoutPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (AccountLogout != nullptr)
	{
		memcpy(buff + offset, &AccountLogoutField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, AccountLogout, sizeof(AccountLogoutField));
		offset += sizeof(AccountLogoutField);
	}
	return offset;
}
bool RtnAccountLogoutPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case AccountLogoutField::FieldID:
		{
			AccountLogout = ::Allocate<AccountLogoutField>();
			memcpy(AccountLogout, buff + offset, sizeof(AccountLogoutField));
			offset += sizeof(AccountLogoutField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* RtnAccountLogoutPackage::GetDebugString() const
{
	int offset = 0;
	if (AccountLogout != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "AccountLogout:AccountID:[%s], ErrorID:[%d], ErrorMsg:[%s]", AccountLogout->AccountID, AccountLogout->ErrorID, AccountLogout->ErrorMsg);
	}
	return t_DataStringBuffer;
}
