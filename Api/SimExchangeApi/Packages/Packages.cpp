#include "Packages.h"
#include "Items.h"
#include "StepUtility.h"
#include "Logger.h"
#include "MemCacheTemplateSingleton.h"
#include <cstring>

thread_local char t_DataStringBuffer[10240];



 
ReqSEBrokerLoginPackage* ReqSEBrokerLoginPackage::Allocate()
{
	return ::Allocate<ReqSEBrokerLoginPackage>();
}
void ReqSEBrokerLoginPackage::Free()
{
	Package::Free();
	if (ReqSEBrokerLogin != nullptr)
	{
		::Free<ReqSEBrokerLoginField>(ReqSEBrokerLogin);
		ReqSEBrokerLogin = nullptr;
	}
	MemCacheTemplateSingleton<ReqSEBrokerLoginPackage>::GetInstance().Free(this);
}
void ReqSEBrokerLoginPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqSEBrokerLoginPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqSEBrokerLogin != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqSEBrokerLoginField::FieldID);
		WriteString(ppos, Items::BrokerID, ReqSEBrokerLogin->BrokerID);
		if (strlen(ReqSEBrokerLogin->Password) >= sizeof(ReqSEBrokerLogin->Password))
		{
			ReqSEBrokerLogin->Password[sizeof(ReqSEBrokerLogin->Password) - 1] = 0;
		}
		WriteString(ppos, Items::Password, ReqSEBrokerLogin->Password);
		WriteHexString(ppos, Items::FieldEnd, ReqSEBrokerLoginField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqSEBrokerLoginPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqSEBrokerLoginField::FieldID:
			{
				ReqSEBrokerLogin = ::Allocate<ReqSEBrokerLoginField>();
				memset(ReqSEBrokerLogin, 0, sizeof(*ReqSEBrokerLogin));
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
						case Items::BrokerID:
						{
							ReqSEBrokerLogin->BrokerID = atoi(value.c_str());
							break;
						}
						case Items::Password:
						{
							size_t len = value.length() >= sizeof(ReqSEBrokerLogin->Password) ? sizeof(ReqSEBrokerLogin->Password) - 1 : value.length();
							memcpy(ReqSEBrokerLogin->Password, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqSEBrokerLoginField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqSEBrokerLoginPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqSEBrokerLoginPackage");
			return false;
		}
	}
	return true;
}
int ReqSEBrokerLoginPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqSEBrokerLogin != nullptr)
	{
		memcpy(buff + offset, &ReqSEBrokerLoginField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqSEBrokerLogin, sizeof(ReqSEBrokerLoginField));
		offset += sizeof(ReqSEBrokerLoginField);
	}
	return offset;
}
bool ReqSEBrokerLoginPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqSEBrokerLoginField::FieldID:
		{
			ReqSEBrokerLogin = ::Allocate<ReqSEBrokerLoginField>();
			memcpy(ReqSEBrokerLogin, buff + offset, sizeof(ReqSEBrokerLoginField));
			offset += sizeof(ReqSEBrokerLoginField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqSEBrokerLoginPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqSEBrokerLogin != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqSEBrokerLogin:BrokerID:[%d], Password:[%s]", ReqSEBrokerLogin->BrokerID, ReqSEBrokerLogin->Password);
	}
	return t_DataStringBuffer;
}
 
RspSEBrokerLoginPackage* RspSEBrokerLoginPackage::Allocate()
{
	return ::Allocate<RspSEBrokerLoginPackage>();
}
void RspSEBrokerLoginPackage::Free()
{
	Package::Free();
	if (RspSEBrokerLogin != nullptr)
	{
		::Free<RspSEBrokerLoginField>(RspSEBrokerLogin);
		RspSEBrokerLogin = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspSEBrokerLoginPackage>::GetInstance().Free(this);
}
void RspSEBrokerLoginPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspSEBrokerLoginPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (RspSEBrokerLogin != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, RspSEBrokerLoginField::FieldID);
		WriteString(ppos, Items::BrokerID, RspSEBrokerLogin->BrokerID);
		if (strlen(RspSEBrokerLogin->BrokerName) >= sizeof(RspSEBrokerLogin->BrokerName))
		{
			RspSEBrokerLogin->BrokerName[sizeof(RspSEBrokerLogin->BrokerName) - 1] = 0;
		}
		WriteString(ppos, Items::BrokerName, RspSEBrokerLogin->BrokerName);
		WriteString(ppos, Items::SessionID, RspSEBrokerLogin->SessionID);
		if (strlen(RspSEBrokerLogin->IPAddress) >= sizeof(RspSEBrokerLogin->IPAddress))
		{
			RspSEBrokerLogin->IPAddress[sizeof(RspSEBrokerLogin->IPAddress) - 1] = 0;
		}
		WriteString(ppos, Items::IPAddress, RspSEBrokerLogin->IPAddress);
		WriteHexString(ppos, Items::FieldEnd, RspSEBrokerLoginField::FieldID);
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
bool RspSEBrokerLoginPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case RspSEBrokerLoginField::FieldID:
			{
				RspSEBrokerLogin = ::Allocate<RspSEBrokerLoginField>();
				memset(RspSEBrokerLogin, 0, sizeof(*RspSEBrokerLogin));
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
						case Items::BrokerID:
						{
							RspSEBrokerLogin->BrokerID = atoi(value.c_str());
							break;
						}
						case Items::BrokerName:
						{
							size_t len = value.length() >= sizeof(RspSEBrokerLogin->BrokerName) ? sizeof(RspSEBrokerLogin->BrokerName) - 1 : value.length();
							memcpy(RspSEBrokerLogin->BrokerName, value.c_str(), len);
							break;
						}
						case Items::SessionID:
						{
							RspSEBrokerLogin->SessionID = atoll(value.c_str());
							break;
						}
						case Items::IPAddress:
						{
							size_t len = value.length() >= sizeof(RspSEBrokerLogin->IPAddress) ? sizeof(RspSEBrokerLogin->IPAddress) - 1 : value.length();
							memcpy(RspSEBrokerLogin->IPAddress, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for RspSEBrokerLoginField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspSEBrokerLoginPackage FieldID:0x%X", fieldID);
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
						WriteLog(LogLevel::Warning, "GetNext Failed For RspSEBrokerLoginPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspSEBrokerLoginPackage");
			return false;
		}
	}
	return true;
}
int RspSEBrokerLoginPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (RspSEBrokerLogin != nullptr)
	{
		memcpy(buff + offset, &RspSEBrokerLoginField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, RspSEBrokerLogin, sizeof(RspSEBrokerLoginField));
		offset += sizeof(RspSEBrokerLoginField);
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
bool RspSEBrokerLoginPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case RspSEBrokerLoginField::FieldID:
		{
			RspSEBrokerLogin = ::Allocate<RspSEBrokerLoginField>();
			memcpy(RspSEBrokerLogin, buff + offset, sizeof(RspSEBrokerLoginField));
			offset += sizeof(RspSEBrokerLoginField);	
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
const char* RspSEBrokerLoginPackage::GetDebugString() const
{
	int offset = 0;
	if (RspSEBrokerLogin != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspSEBrokerLogin:BrokerID:[%d], BrokerName:[%s], SessionID:[%lld], IPAddress:[%s]", RspSEBrokerLogin->BrokerID, RspSEBrokerLogin->BrokerName, RspSEBrokerLogin->SessionID, RspSEBrokerLogin->IPAddress);
	}
	if (RspInfo != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
	return t_DataStringBuffer;
}
 
ReqSEBrokerLogoutPackage* ReqSEBrokerLogoutPackage::Allocate()
{
	return ::Allocate<ReqSEBrokerLogoutPackage>();
}
void ReqSEBrokerLogoutPackage::Free()
{
	Package::Free();
	if (ReqSEBrokerLogout != nullptr)
	{
		::Free<ReqSEBrokerLogoutField>(ReqSEBrokerLogout);
		ReqSEBrokerLogout = nullptr;
	}
	MemCacheTemplateSingleton<ReqSEBrokerLogoutPackage>::GetInstance().Free(this);
}
void ReqSEBrokerLogoutPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqSEBrokerLogoutPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqSEBrokerLogout != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqSEBrokerLogoutField::FieldID);
		WriteString(ppos, Items::BrokerID, ReqSEBrokerLogout->BrokerID);
		WriteHexString(ppos, Items::FieldEnd, ReqSEBrokerLogoutField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqSEBrokerLogoutPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqSEBrokerLogoutField::FieldID:
			{
				ReqSEBrokerLogout = ::Allocate<ReqSEBrokerLogoutField>();
				memset(ReqSEBrokerLogout, 0, sizeof(*ReqSEBrokerLogout));
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
						case Items::BrokerID:
						{
							ReqSEBrokerLogout->BrokerID = atoi(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqSEBrokerLogoutField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqSEBrokerLogoutPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqSEBrokerLogoutPackage");
			return false;
		}
	}
	return true;
}
int ReqSEBrokerLogoutPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqSEBrokerLogout != nullptr)
	{
		memcpy(buff + offset, &ReqSEBrokerLogoutField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqSEBrokerLogout, sizeof(ReqSEBrokerLogoutField));
		offset += sizeof(ReqSEBrokerLogoutField);
	}
	return offset;
}
bool ReqSEBrokerLogoutPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqSEBrokerLogoutField::FieldID:
		{
			ReqSEBrokerLogout = ::Allocate<ReqSEBrokerLogoutField>();
			memcpy(ReqSEBrokerLogout, buff + offset, sizeof(ReqSEBrokerLogoutField));
			offset += sizeof(ReqSEBrokerLogoutField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqSEBrokerLogoutPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqSEBrokerLogout != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqSEBrokerLogout:BrokerID:[%d]", ReqSEBrokerLogout->BrokerID);
	}
	return t_DataStringBuffer;
}
 
RspSEBrokerLogoutPackage* RspSEBrokerLogoutPackage::Allocate()
{
	return ::Allocate<RspSEBrokerLogoutPackage>();
}
void RspSEBrokerLogoutPackage::Free()
{
	Package::Free();
	if (RspSEBrokerLogout != nullptr)
	{
		::Free<RspSEBrokerLogoutField>(RspSEBrokerLogout);
		RspSEBrokerLogout = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspSEBrokerLogoutPackage>::GetInstance().Free(this);
}
void RspSEBrokerLogoutPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspSEBrokerLogoutPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (RspSEBrokerLogout != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, RspSEBrokerLogoutField::FieldID);
		WriteString(ppos, Items::BrokerID, RspSEBrokerLogout->BrokerID);
		WriteString(ppos, Items::SessionID, RspSEBrokerLogout->SessionID);
		if (strlen(RspSEBrokerLogout->IPAddress) >= sizeof(RspSEBrokerLogout->IPAddress))
		{
			RspSEBrokerLogout->IPAddress[sizeof(RspSEBrokerLogout->IPAddress) - 1] = 0;
		}
		WriteString(ppos, Items::IPAddress, RspSEBrokerLogout->IPAddress);
		WriteHexString(ppos, Items::FieldEnd, RspSEBrokerLogoutField::FieldID);
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
bool RspSEBrokerLogoutPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case RspSEBrokerLogoutField::FieldID:
			{
				RspSEBrokerLogout = ::Allocate<RspSEBrokerLogoutField>();
				memset(RspSEBrokerLogout, 0, sizeof(*RspSEBrokerLogout));
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
						case Items::BrokerID:
						{
							RspSEBrokerLogout->BrokerID = atoi(value.c_str());
							break;
						}
						case Items::SessionID:
						{
							RspSEBrokerLogout->SessionID = atoll(value.c_str());
							break;
						}
						case Items::IPAddress:
						{
							size_t len = value.length() >= sizeof(RspSEBrokerLogout->IPAddress) ? sizeof(RspSEBrokerLogout->IPAddress) - 1 : value.length();
							memcpy(RspSEBrokerLogout->IPAddress, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for RspSEBrokerLogoutField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspSEBrokerLogoutPackage FieldID:0x%X", fieldID);
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
						WriteLog(LogLevel::Warning, "GetNext Failed For RspSEBrokerLogoutPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspSEBrokerLogoutPackage");
			return false;
		}
	}
	return true;
}
int RspSEBrokerLogoutPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (RspSEBrokerLogout != nullptr)
	{
		memcpy(buff + offset, &RspSEBrokerLogoutField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, RspSEBrokerLogout, sizeof(RspSEBrokerLogoutField));
		offset += sizeof(RspSEBrokerLogoutField);
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
bool RspSEBrokerLogoutPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case RspSEBrokerLogoutField::FieldID:
		{
			RspSEBrokerLogout = ::Allocate<RspSEBrokerLogoutField>();
			memcpy(RspSEBrokerLogout, buff + offset, sizeof(RspSEBrokerLogoutField));
			offset += sizeof(RspSEBrokerLogoutField);	
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
const char* RspSEBrokerLogoutPackage::GetDebugString() const
{
	int offset = 0;
	if (RspSEBrokerLogout != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspSEBrokerLogout:BrokerID:[%d], SessionID:[%lld], IPAddress:[%s]", RspSEBrokerLogout->BrokerID, RspSEBrokerLogout->SessionID, RspSEBrokerLogout->IPAddress);
	}
	if (RspInfo != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
	return t_DataStringBuffer;
}
 
ReqSEInsertOrderPackage* ReqSEInsertOrderPackage::Allocate()
{
	return ::Allocate<ReqSEInsertOrderPackage>();
}
void ReqSEInsertOrderPackage::Free()
{
	Package::Free();
	if (ReqSEInsertOrder != nullptr)
	{
		::Free<ReqSEInsertOrderField>(ReqSEInsertOrder);
		ReqSEInsertOrder = nullptr;
	}
	MemCacheTemplateSingleton<ReqSEInsertOrderPackage>::GetInstance().Free(this);
}
void ReqSEInsertOrderPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqSEInsertOrderPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqSEInsertOrder != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqSEInsertOrderField::FieldID);
		WriteString(ppos, Items::BrokerID, ReqSEInsertOrder->BrokerID);
		if (strlen(ReqSEInsertOrder->AccountID) >= sizeof(ReqSEInsertOrder->AccountID))
		{
			ReqSEInsertOrder->AccountID[sizeof(ReqSEInsertOrder->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, ReqSEInsertOrder->AccountID);
		if (strlen(ReqSEInsertOrder->ExchangeID) >= sizeof(ReqSEInsertOrder->ExchangeID))
		{
			ReqSEInsertOrder->ExchangeID[sizeof(ReqSEInsertOrder->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, ReqSEInsertOrder->ExchangeID);
		if (strlen(ReqSEInsertOrder->InstrumentID) >= sizeof(ReqSEInsertOrder->InstrumentID))
		{
			ReqSEInsertOrder->InstrumentID[sizeof(ReqSEInsertOrder->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, ReqSEInsertOrder->InstrumentID);
		WriteString(ppos, Items::Direction, (int)ReqSEInsertOrder->Direction);
		WriteString(ppos, Items::OffsetFlag, (int)ReqSEInsertOrder->OffsetFlag);
		WriteString(ppos, Items::OrderPriceType, (int)ReqSEInsertOrder->OrderPriceType);
		WriteString(ppos, Items::Price, ReqSEInsertOrder->Price);
		WriteString(ppos, Items::Volume, ReqSEInsertOrder->Volume);
		WriteString(ppos, Items::ClientOrderID, ReqSEInsertOrder->ClientOrderID);
		WriteHexString(ppos, Items::FieldEnd, ReqSEInsertOrderField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqSEInsertOrderPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqSEInsertOrderField::FieldID:
			{
				ReqSEInsertOrder = ::Allocate<ReqSEInsertOrderField>();
				memset(ReqSEInsertOrder, 0, sizeof(*ReqSEInsertOrder));
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
						case Items::BrokerID:
						{
							ReqSEInsertOrder->BrokerID = atoi(value.c_str());
							break;
						}
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(ReqSEInsertOrder->AccountID) ? sizeof(ReqSEInsertOrder->AccountID) - 1 : value.length();
							memcpy(ReqSEInsertOrder->AccountID, value.c_str(), len);
							break;
						}
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(ReqSEInsertOrder->ExchangeID) ? sizeof(ReqSEInsertOrder->ExchangeID) - 1 : value.length();
							memcpy(ReqSEInsertOrder->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(ReqSEInsertOrder->InstrumentID) ? sizeof(ReqSEInsertOrder->InstrumentID) - 1 : value.length();
							memcpy(ReqSEInsertOrder->InstrumentID, value.c_str(), len);
							break;
						}
						case Items::Direction:
						{
							ReqSEInsertOrder->Direction = (DirectionType)(atoi(value.c_str()));
							break;
						}
						case Items::OffsetFlag:
						{
							ReqSEInsertOrder->OffsetFlag = (OffsetFlagType)(atoi(value.c_str()));
							break;
						}
						case Items::OrderPriceType:
						{
							ReqSEInsertOrder->OrderPriceType = (OrderPriceTypeType)(atoi(value.c_str()));
							break;
						}
						case Items::Price:
						{
							ReqSEInsertOrder->Price = atof(value.c_str());
							break;
						}
						case Items::Volume:
						{
							ReqSEInsertOrder->Volume = atoll(value.c_str());
							break;
						}
						case Items::ClientOrderID:
						{
							ReqSEInsertOrder->ClientOrderID = atoi(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqSEInsertOrderField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqSEInsertOrderPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqSEInsertOrderPackage");
			return false;
		}
	}
	return true;
}
int ReqSEInsertOrderPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqSEInsertOrder != nullptr)
	{
		memcpy(buff + offset, &ReqSEInsertOrderField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqSEInsertOrder, sizeof(ReqSEInsertOrderField));
		offset += sizeof(ReqSEInsertOrderField);
	}
	return offset;
}
bool ReqSEInsertOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqSEInsertOrderField::FieldID:
		{
			ReqSEInsertOrder = ::Allocate<ReqSEInsertOrderField>();
			memcpy(ReqSEInsertOrder, buff + offset, sizeof(ReqSEInsertOrderField));
			offset += sizeof(ReqSEInsertOrderField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqSEInsertOrderPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqSEInsertOrder != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqSEInsertOrder:BrokerID:[%d], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], ClientOrderID:[%d]", ReqSEInsertOrder->BrokerID, ReqSEInsertOrder->AccountID, ReqSEInsertOrder->ExchangeID, ReqSEInsertOrder->InstrumentID, (int)ReqSEInsertOrder->Direction, (int)ReqSEInsertOrder->OffsetFlag, (int)ReqSEInsertOrder->OrderPriceType, ReqSEInsertOrder->Price, ReqSEInsertOrder->Volume, ReqSEInsertOrder->ClientOrderID);
	}
	return t_DataStringBuffer;
}
 
RspSEInsertOrderPackage* RspSEInsertOrderPackage::Allocate()
{
	return ::Allocate<RspSEInsertOrderPackage>();
}
void RspSEInsertOrderPackage::Free()
{
	Package::Free();
	if (ReqSEInsertOrder != nullptr)
	{
		::Free<ReqSEInsertOrderField>(ReqSEInsertOrder);
		ReqSEInsertOrder = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspSEInsertOrderPackage>::GetInstance().Free(this);
}
void RspSEInsertOrderPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspSEInsertOrderPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqSEInsertOrder != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqSEInsertOrderField::FieldID);
		WriteString(ppos, Items::BrokerID, ReqSEInsertOrder->BrokerID);
		if (strlen(ReqSEInsertOrder->AccountID) >= sizeof(ReqSEInsertOrder->AccountID))
		{
			ReqSEInsertOrder->AccountID[sizeof(ReqSEInsertOrder->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, ReqSEInsertOrder->AccountID);
		if (strlen(ReqSEInsertOrder->ExchangeID) >= sizeof(ReqSEInsertOrder->ExchangeID))
		{
			ReqSEInsertOrder->ExchangeID[sizeof(ReqSEInsertOrder->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, ReqSEInsertOrder->ExchangeID);
		if (strlen(ReqSEInsertOrder->InstrumentID) >= sizeof(ReqSEInsertOrder->InstrumentID))
		{
			ReqSEInsertOrder->InstrumentID[sizeof(ReqSEInsertOrder->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, ReqSEInsertOrder->InstrumentID);
		WriteString(ppos, Items::Direction, (int)ReqSEInsertOrder->Direction);
		WriteString(ppos, Items::OffsetFlag, (int)ReqSEInsertOrder->OffsetFlag);
		WriteString(ppos, Items::OrderPriceType, (int)ReqSEInsertOrder->OrderPriceType);
		WriteString(ppos, Items::Price, ReqSEInsertOrder->Price);
		WriteString(ppos, Items::Volume, ReqSEInsertOrder->Volume);
		WriteString(ppos, Items::ClientOrderID, ReqSEInsertOrder->ClientOrderID);
		WriteHexString(ppos, Items::FieldEnd, ReqSEInsertOrderField::FieldID);
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
bool RspSEInsertOrderPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqSEInsertOrderField::FieldID:
			{
				ReqSEInsertOrder = ::Allocate<ReqSEInsertOrderField>();
				memset(ReqSEInsertOrder, 0, sizeof(*ReqSEInsertOrder));
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
						case Items::BrokerID:
						{
							ReqSEInsertOrder->BrokerID = atoi(value.c_str());
							break;
						}
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(ReqSEInsertOrder->AccountID) ? sizeof(ReqSEInsertOrder->AccountID) - 1 : value.length();
							memcpy(ReqSEInsertOrder->AccountID, value.c_str(), len);
							break;
						}
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(ReqSEInsertOrder->ExchangeID) ? sizeof(ReqSEInsertOrder->ExchangeID) - 1 : value.length();
							memcpy(ReqSEInsertOrder->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(ReqSEInsertOrder->InstrumentID) ? sizeof(ReqSEInsertOrder->InstrumentID) - 1 : value.length();
							memcpy(ReqSEInsertOrder->InstrumentID, value.c_str(), len);
							break;
						}
						case Items::Direction:
						{
							ReqSEInsertOrder->Direction = (DirectionType)(atoi(value.c_str()));
							break;
						}
						case Items::OffsetFlag:
						{
							ReqSEInsertOrder->OffsetFlag = (OffsetFlagType)(atoi(value.c_str()));
							break;
						}
						case Items::OrderPriceType:
						{
							ReqSEInsertOrder->OrderPriceType = (OrderPriceTypeType)(atoi(value.c_str()));
							break;
						}
						case Items::Price:
						{
							ReqSEInsertOrder->Price = atof(value.c_str());
							break;
						}
						case Items::Volume:
						{
							ReqSEInsertOrder->Volume = atoll(value.c_str());
							break;
						}
						case Items::ClientOrderID:
						{
							ReqSEInsertOrder->ClientOrderID = atoi(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqSEInsertOrderField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspSEInsertOrderPackage FieldID:0x%X", fieldID);
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
						WriteLog(LogLevel::Warning, "GetNext Failed For RspSEInsertOrderPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspSEInsertOrderPackage");
			return false;
		}
	}
	return true;
}
int RspSEInsertOrderPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqSEInsertOrder != nullptr)
	{
		memcpy(buff + offset, &ReqSEInsertOrderField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqSEInsertOrder, sizeof(ReqSEInsertOrderField));
		offset += sizeof(ReqSEInsertOrderField);
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
bool RspSEInsertOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqSEInsertOrderField::FieldID:
		{
			ReqSEInsertOrder = ::Allocate<ReqSEInsertOrderField>();
			memcpy(ReqSEInsertOrder, buff + offset, sizeof(ReqSEInsertOrderField));
			offset += sizeof(ReqSEInsertOrderField);	
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
const char* RspSEInsertOrderPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqSEInsertOrder != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqSEInsertOrder:BrokerID:[%d], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], ClientOrderID:[%d]", ReqSEInsertOrder->BrokerID, ReqSEInsertOrder->AccountID, ReqSEInsertOrder->ExchangeID, ReqSEInsertOrder->InstrumentID, (int)ReqSEInsertOrder->Direction, (int)ReqSEInsertOrder->OffsetFlag, (int)ReqSEInsertOrder->OrderPriceType, ReqSEInsertOrder->Price, ReqSEInsertOrder->Volume, ReqSEInsertOrder->ClientOrderID);
	}
	if (RspInfo != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
	return t_DataStringBuffer;
}
 
ReqSECancelOrderPackage* ReqSECancelOrderPackage::Allocate()
{
	return ::Allocate<ReqSECancelOrderPackage>();
}
void ReqSECancelOrderPackage::Free()
{
	Package::Free();
	if (ReqSECancelOrder != nullptr)
	{
		::Free<ReqSECancelOrderField>(ReqSECancelOrder);
		ReqSECancelOrder = nullptr;
	}
	MemCacheTemplateSingleton<ReqSECancelOrderPackage>::GetInstance().Free(this);
}
void ReqSECancelOrderPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqSECancelOrderPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqSECancelOrder != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqSECancelOrderField::FieldID);
		WriteString(ppos, Items::BrokerID, ReqSECancelOrder->BrokerID);
		if (strlen(ReqSECancelOrder->AccountID) >= sizeof(ReqSECancelOrder->AccountID))
		{
			ReqSECancelOrder->AccountID[sizeof(ReqSECancelOrder->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, ReqSECancelOrder->AccountID);
		if (strlen(ReqSECancelOrder->ExchangeID) >= sizeof(ReqSECancelOrder->ExchangeID))
		{
			ReqSECancelOrder->ExchangeID[sizeof(ReqSECancelOrder->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, ReqSECancelOrder->ExchangeID);
		if (strlen(ReqSECancelOrder->InstrumentID) >= sizeof(ReqSECancelOrder->InstrumentID))
		{
			ReqSECancelOrder->InstrumentID[sizeof(ReqSECancelOrder->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, ReqSECancelOrder->InstrumentID);
		WriteString(ppos, Items::CancelOrderID, ReqSECancelOrder->CancelOrderID);
		WriteString(ppos, Items::OrderID, ReqSECancelOrder->OrderID);
		WriteString(ppos, Items::ClientOrderID, ReqSECancelOrder->ClientOrderID);
		WriteString(ppos, Items::SessionID, ReqSECancelOrder->SessionID);
		WriteHexString(ppos, Items::FieldEnd, ReqSECancelOrderField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqSECancelOrderPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqSECancelOrderField::FieldID:
			{
				ReqSECancelOrder = ::Allocate<ReqSECancelOrderField>();
				memset(ReqSECancelOrder, 0, sizeof(*ReqSECancelOrder));
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
						case Items::BrokerID:
						{
							ReqSECancelOrder->BrokerID = atoi(value.c_str());
							break;
						}
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(ReqSECancelOrder->AccountID) ? sizeof(ReqSECancelOrder->AccountID) - 1 : value.length();
							memcpy(ReqSECancelOrder->AccountID, value.c_str(), len);
							break;
						}
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(ReqSECancelOrder->ExchangeID) ? sizeof(ReqSECancelOrder->ExchangeID) - 1 : value.length();
							memcpy(ReqSECancelOrder->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(ReqSECancelOrder->InstrumentID) ? sizeof(ReqSECancelOrder->InstrumentID) - 1 : value.length();
							memcpy(ReqSECancelOrder->InstrumentID, value.c_str(), len);
							break;
						}
						case Items::CancelOrderID:
						{
							ReqSECancelOrder->CancelOrderID = atoi(value.c_str());
							break;
						}
						case Items::OrderID:
						{
							ReqSECancelOrder->OrderID = atoi(value.c_str());
							break;
						}
						case Items::ClientOrderID:
						{
							ReqSECancelOrder->ClientOrderID = atoi(value.c_str());
							break;
						}
						case Items::SessionID:
						{
							ReqSECancelOrder->SessionID = atoll(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqSECancelOrderField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqSECancelOrderPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqSECancelOrderPackage");
			return false;
		}
	}
	return true;
}
int ReqSECancelOrderPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqSECancelOrder != nullptr)
	{
		memcpy(buff + offset, &ReqSECancelOrderField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqSECancelOrder, sizeof(ReqSECancelOrderField));
		offset += sizeof(ReqSECancelOrderField);
	}
	return offset;
}
bool ReqSECancelOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqSECancelOrderField::FieldID:
		{
			ReqSECancelOrder = ::Allocate<ReqSECancelOrderField>();
			memcpy(ReqSECancelOrder, buff + offset, sizeof(ReqSECancelOrderField));
			offset += sizeof(ReqSECancelOrderField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqSECancelOrderPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqSECancelOrder != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqSECancelOrder:BrokerID:[%d], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], CancelOrderID:[%d], OrderID:[%d], ClientOrderID:[%d], SessionID:[%lld]", ReqSECancelOrder->BrokerID, ReqSECancelOrder->AccountID, ReqSECancelOrder->ExchangeID, ReqSECancelOrder->InstrumentID, ReqSECancelOrder->CancelOrderID, ReqSECancelOrder->OrderID, ReqSECancelOrder->ClientOrderID, ReqSECancelOrder->SessionID);
	}
	return t_DataStringBuffer;
}
 
RspSECancelOrderPackage* RspSECancelOrderPackage::Allocate()
{
	return ::Allocate<RspSECancelOrderPackage>();
}
void RspSECancelOrderPackage::Free()
{
	Package::Free();
	if (ReqSECancelOrder != nullptr)
	{
		::Free<ReqSECancelOrderField>(ReqSECancelOrder);
		ReqSECancelOrder = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspSECancelOrderPackage>::GetInstance().Free(this);
}
void RspSECancelOrderPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspSECancelOrderPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqSECancelOrder != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqSECancelOrderField::FieldID);
		WriteString(ppos, Items::BrokerID, ReqSECancelOrder->BrokerID);
		if (strlen(ReqSECancelOrder->AccountID) >= sizeof(ReqSECancelOrder->AccountID))
		{
			ReqSECancelOrder->AccountID[sizeof(ReqSECancelOrder->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, ReqSECancelOrder->AccountID);
		if (strlen(ReqSECancelOrder->ExchangeID) >= sizeof(ReqSECancelOrder->ExchangeID))
		{
			ReqSECancelOrder->ExchangeID[sizeof(ReqSECancelOrder->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, ReqSECancelOrder->ExchangeID);
		if (strlen(ReqSECancelOrder->InstrumentID) >= sizeof(ReqSECancelOrder->InstrumentID))
		{
			ReqSECancelOrder->InstrumentID[sizeof(ReqSECancelOrder->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, ReqSECancelOrder->InstrumentID);
		WriteString(ppos, Items::CancelOrderID, ReqSECancelOrder->CancelOrderID);
		WriteString(ppos, Items::OrderID, ReqSECancelOrder->OrderID);
		WriteString(ppos, Items::ClientOrderID, ReqSECancelOrder->ClientOrderID);
		WriteString(ppos, Items::SessionID, ReqSECancelOrder->SessionID);
		WriteHexString(ppos, Items::FieldEnd, ReqSECancelOrderField::FieldID);
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
bool RspSECancelOrderPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqSECancelOrderField::FieldID:
			{
				ReqSECancelOrder = ::Allocate<ReqSECancelOrderField>();
				memset(ReqSECancelOrder, 0, sizeof(*ReqSECancelOrder));
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
						case Items::BrokerID:
						{
							ReqSECancelOrder->BrokerID = atoi(value.c_str());
							break;
						}
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(ReqSECancelOrder->AccountID) ? sizeof(ReqSECancelOrder->AccountID) - 1 : value.length();
							memcpy(ReqSECancelOrder->AccountID, value.c_str(), len);
							break;
						}
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(ReqSECancelOrder->ExchangeID) ? sizeof(ReqSECancelOrder->ExchangeID) - 1 : value.length();
							memcpy(ReqSECancelOrder->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(ReqSECancelOrder->InstrumentID) ? sizeof(ReqSECancelOrder->InstrumentID) - 1 : value.length();
							memcpy(ReqSECancelOrder->InstrumentID, value.c_str(), len);
							break;
						}
						case Items::CancelOrderID:
						{
							ReqSECancelOrder->CancelOrderID = atoi(value.c_str());
							break;
						}
						case Items::OrderID:
						{
							ReqSECancelOrder->OrderID = atoi(value.c_str());
							break;
						}
						case Items::ClientOrderID:
						{
							ReqSECancelOrder->ClientOrderID = atoi(value.c_str());
							break;
						}
						case Items::SessionID:
						{
							ReqSECancelOrder->SessionID = atoll(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqSECancelOrderField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspSECancelOrderPackage FieldID:0x%X", fieldID);
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
						WriteLog(LogLevel::Warning, "GetNext Failed For RspSECancelOrderPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspSECancelOrderPackage");
			return false;
		}
	}
	return true;
}
int RspSECancelOrderPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqSECancelOrder != nullptr)
	{
		memcpy(buff + offset, &ReqSECancelOrderField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqSECancelOrder, sizeof(ReqSECancelOrderField));
		offset += sizeof(ReqSECancelOrderField);
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
bool RspSECancelOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqSECancelOrderField::FieldID:
		{
			ReqSECancelOrder = ::Allocate<ReqSECancelOrderField>();
			memcpy(ReqSECancelOrder, buff + offset, sizeof(ReqSECancelOrderField));
			offset += sizeof(ReqSECancelOrderField);	
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
const char* RspSECancelOrderPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqSECancelOrder != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqSECancelOrder:BrokerID:[%d], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], CancelOrderID:[%d], OrderID:[%d], ClientOrderID:[%d], SessionID:[%lld]", ReqSECancelOrder->BrokerID, ReqSECancelOrder->AccountID, ReqSECancelOrder->ExchangeID, ReqSECancelOrder->InstrumentID, ReqSECancelOrder->CancelOrderID, ReqSECancelOrder->OrderID, ReqSECancelOrder->ClientOrderID, ReqSECancelOrder->SessionID);
	}
	if (RspInfo != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
	return t_DataStringBuffer;
}
 
ReqQrySEOrderPackage* ReqQrySEOrderPackage::Allocate()
{
	return ::Allocate<ReqQrySEOrderPackage>();
}
void ReqQrySEOrderPackage::Free()
{
	Package::Free();
	if (ReqQrySEOrder != nullptr)
	{
		::Free<ReqQrySEOrderField>(ReqQrySEOrder);
		ReqQrySEOrder = nullptr;
	}
	MemCacheTemplateSingleton<ReqQrySEOrderPackage>::GetInstance().Free(this);
}
void ReqQrySEOrderPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqQrySEOrderPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqQrySEOrder != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqQrySEOrderField::FieldID);
		if (strlen(ReqQrySEOrder->AccountID) >= sizeof(ReqQrySEOrder->AccountID))
		{
			ReqQrySEOrder->AccountID[sizeof(ReqQrySEOrder->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, ReqQrySEOrder->AccountID);
		WriteHexString(ppos, Items::FieldEnd, ReqQrySEOrderField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqQrySEOrderPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqQrySEOrderField::FieldID:
			{
				ReqQrySEOrder = ::Allocate<ReqQrySEOrderField>();
				memset(ReqQrySEOrder, 0, sizeof(*ReqQrySEOrder));
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
							size_t len = value.length() >= sizeof(ReqQrySEOrder->AccountID) ? sizeof(ReqQrySEOrder->AccountID) - 1 : value.length();
							memcpy(ReqQrySEOrder->AccountID, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqQrySEOrderField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqQrySEOrderPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqQrySEOrderPackage");
			return false;
		}
	}
	return true;
}
int ReqQrySEOrderPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqQrySEOrder != nullptr)
	{
		memcpy(buff + offset, &ReqQrySEOrderField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqQrySEOrder, sizeof(ReqQrySEOrderField));
		offset += sizeof(ReqQrySEOrderField);
	}
	return offset;
}
bool ReqQrySEOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqQrySEOrderField::FieldID:
		{
			ReqQrySEOrder = ::Allocate<ReqQrySEOrderField>();
			memcpy(ReqQrySEOrder, buff + offset, sizeof(ReqQrySEOrderField));
			offset += sizeof(ReqQrySEOrderField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqQrySEOrderPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqQrySEOrder != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqQrySEOrder:AccountID:[%s]", ReqQrySEOrder->AccountID);
	}
	return t_DataStringBuffer;
}
 
RspQrySEOrderPackage* RspQrySEOrderPackage::Allocate()
{
	return ::Allocate<RspQrySEOrderPackage>();
}
void RspQrySEOrderPackage::Free()
{
	Package::Free();
	if (SEOrder != nullptr)
	{
		::Free<SEOrderField>(SEOrder);
		SEOrder = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspQrySEOrderPackage>::GetInstance().Free(this);
}
void RspQrySEOrderPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspQrySEOrderPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (SEOrder != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, SEOrderField::FieldID);
		if (strlen(SEOrder->TradingDay) >= sizeof(SEOrder->TradingDay))
		{
			SEOrder->TradingDay[sizeof(SEOrder->TradingDay) - 1] = 0;
		}
		WriteString(ppos, Items::TradingDay, SEOrder->TradingDay);
		WriteString(ppos, Items::BrokerID, SEOrder->BrokerID);
		if (strlen(SEOrder->AccountID) >= sizeof(SEOrder->AccountID))
		{
			SEOrder->AccountID[sizeof(SEOrder->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, SEOrder->AccountID);
		if (strlen(SEOrder->ExchangeID) >= sizeof(SEOrder->ExchangeID))
		{
			SEOrder->ExchangeID[sizeof(SEOrder->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, SEOrder->ExchangeID);
		if (strlen(SEOrder->InstrumentID) >= sizeof(SEOrder->InstrumentID))
		{
			SEOrder->InstrumentID[sizeof(SEOrder->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, SEOrder->InstrumentID);
		WriteString(ppos, Items::ProductClass, (int)SEOrder->ProductClass);
		WriteString(ppos, Items::OrderID, SEOrder->OrderID);
		WriteString(ppos, Items::Direction, (int)SEOrder->Direction);
		WriteString(ppos, Items::OffsetFlag, (int)SEOrder->OffsetFlag);
		WriteString(ppos, Items::OrderPriceType, (int)SEOrder->OrderPriceType);
		WriteString(ppos, Items::Price, SEOrder->Price);
		WriteString(ppos, Items::Volume, SEOrder->Volume);
		WriteString(ppos, Items::VolumeTotal, SEOrder->VolumeTotal);
		WriteString(ppos, Items::VolumeTraded, SEOrder->VolumeTraded);
		WriteString(ppos, Items::VolumeMultiple, SEOrder->VolumeMultiple);
		WriteString(ppos, Items::OrderStatus, (int)SEOrder->OrderStatus);
		if (strlen(SEOrder->OrderDate) >= sizeof(SEOrder->OrderDate))
		{
			SEOrder->OrderDate[sizeof(SEOrder->OrderDate) - 1] = 0;
		}
		WriteString(ppos, Items::OrderDate, SEOrder->OrderDate);
		if (strlen(SEOrder->OrderTime) >= sizeof(SEOrder->OrderTime))
		{
			SEOrder->OrderTime[sizeof(SEOrder->OrderTime) - 1] = 0;
		}
		WriteString(ppos, Items::OrderTime, SEOrder->OrderTime);
		if (strlen(SEOrder->CancelDate) >= sizeof(SEOrder->CancelDate))
		{
			SEOrder->CancelDate[sizeof(SEOrder->CancelDate) - 1] = 0;
		}
		WriteString(ppos, Items::CancelDate, SEOrder->CancelDate);
		if (strlen(SEOrder->CancelTime) >= sizeof(SEOrder->CancelTime))
		{
			SEOrder->CancelTime[sizeof(SEOrder->CancelTime) - 1] = 0;
		}
		WriteString(ppos, Items::CancelTime, SEOrder->CancelTime);
		WriteString(ppos, Items::SessionID, SEOrder->SessionID);
		WriteString(ppos, Items::ClientOrderID, SEOrder->ClientOrderID);
		WriteHexString(ppos, Items::FieldEnd, SEOrderField::FieldID);
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
bool RspQrySEOrderPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case SEOrderField::FieldID:
			{
				SEOrder = ::Allocate<SEOrderField>();
				memset(SEOrder, 0, sizeof(*SEOrder));
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
							size_t len = value.length() >= sizeof(SEOrder->TradingDay) ? sizeof(SEOrder->TradingDay) - 1 : value.length();
							memcpy(SEOrder->TradingDay, value.c_str(), len);
							break;
						}
						case Items::BrokerID:
						{
							SEOrder->BrokerID = atoi(value.c_str());
							break;
						}
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(SEOrder->AccountID) ? sizeof(SEOrder->AccountID) - 1 : value.length();
							memcpy(SEOrder->AccountID, value.c_str(), len);
							break;
						}
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(SEOrder->ExchangeID) ? sizeof(SEOrder->ExchangeID) - 1 : value.length();
							memcpy(SEOrder->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(SEOrder->InstrumentID) ? sizeof(SEOrder->InstrumentID) - 1 : value.length();
							memcpy(SEOrder->InstrumentID, value.c_str(), len);
							break;
						}
						case Items::ProductClass:
						{
							SEOrder->ProductClass = (ProductClassType)(atoi(value.c_str()));
							break;
						}
						case Items::OrderID:
						{
							SEOrder->OrderID = atoi(value.c_str());
							break;
						}
						case Items::Direction:
						{
							SEOrder->Direction = (DirectionType)(atoi(value.c_str()));
							break;
						}
						case Items::OffsetFlag:
						{
							SEOrder->OffsetFlag = (OffsetFlagType)(atoi(value.c_str()));
							break;
						}
						case Items::OrderPriceType:
						{
							SEOrder->OrderPriceType = (OrderPriceTypeType)(atoi(value.c_str()));
							break;
						}
						case Items::Price:
						{
							SEOrder->Price = atof(value.c_str());
							break;
						}
						case Items::Volume:
						{
							SEOrder->Volume = atoll(value.c_str());
							break;
						}
						case Items::VolumeTotal:
						{
							SEOrder->VolumeTotal = atoll(value.c_str());
							break;
						}
						case Items::VolumeTraded:
						{
							SEOrder->VolumeTraded = atoll(value.c_str());
							break;
						}
						case Items::VolumeMultiple:
						{
							SEOrder->VolumeMultiple = atoi(value.c_str());
							break;
						}
						case Items::OrderStatus:
						{
							SEOrder->OrderStatus = (OrderStatusType)(atoi(value.c_str()));
							break;
						}
						case Items::OrderDate:
						{
							size_t len = value.length() >= sizeof(SEOrder->OrderDate) ? sizeof(SEOrder->OrderDate) - 1 : value.length();
							memcpy(SEOrder->OrderDate, value.c_str(), len);
							break;
						}
						case Items::OrderTime:
						{
							size_t len = value.length() >= sizeof(SEOrder->OrderTime) ? sizeof(SEOrder->OrderTime) - 1 : value.length();
							memcpy(SEOrder->OrderTime, value.c_str(), len);
							break;
						}
						case Items::CancelDate:
						{
							size_t len = value.length() >= sizeof(SEOrder->CancelDate) ? sizeof(SEOrder->CancelDate) - 1 : value.length();
							memcpy(SEOrder->CancelDate, value.c_str(), len);
							break;
						}
						case Items::CancelTime:
						{
							size_t len = value.length() >= sizeof(SEOrder->CancelTime) ? sizeof(SEOrder->CancelTime) - 1 : value.length();
							memcpy(SEOrder->CancelTime, value.c_str(), len);
							break;
						}
						case Items::SessionID:
						{
							SEOrder->SessionID = atoll(value.c_str());
							break;
						}
						case Items::ClientOrderID:
						{
							SEOrder->ClientOrderID = atoi(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for SEOrderField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQrySEOrderPackage FieldID:0x%X", fieldID);
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
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQrySEOrderPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspQrySEOrderPackage");
			return false;
		}
	}
	return true;
}
int RspQrySEOrderPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (SEOrder != nullptr)
	{
		memcpy(buff + offset, &SEOrderField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, SEOrder, sizeof(SEOrderField));
		offset += sizeof(SEOrderField);
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
bool RspQrySEOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case SEOrderField::FieldID:
		{
			SEOrder = ::Allocate<SEOrderField>();
			memcpy(SEOrder, buff + offset, sizeof(SEOrderField));
			offset += sizeof(SEOrderField);	
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
const char* RspQrySEOrderPackage::GetDebugString() const
{
	int offset = 0;
	if (SEOrder != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "SEOrder:TradingDay:[%s], BrokerID:[%d], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], VolumeTotal:[%lld], VolumeTraded:[%lld], VolumeMultiple:[%d], OrderStatus:[%d], OrderDate:[%s], OrderTime:[%s], CancelDate:[%s], CancelTime:[%s], SessionID:[%lld], ClientOrderID:[%d]", SEOrder->TradingDay, SEOrder->BrokerID, SEOrder->AccountID, SEOrder->ExchangeID, SEOrder->InstrumentID, (int)SEOrder->ProductClass, SEOrder->OrderID, (int)SEOrder->Direction, (int)SEOrder->OffsetFlag, (int)SEOrder->OrderPriceType, SEOrder->Price, SEOrder->Volume, SEOrder->VolumeTotal, SEOrder->VolumeTraded, SEOrder->VolumeMultiple, (int)SEOrder->OrderStatus, SEOrder->OrderDate, SEOrder->OrderTime, SEOrder->CancelDate, SEOrder->CancelTime, SEOrder->SessionID, SEOrder->ClientOrderID);
	}
	if (RspInfo != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
	return t_DataStringBuffer;
}
 
ReqQrySETradePackage* ReqQrySETradePackage::Allocate()
{
	return ::Allocate<ReqQrySETradePackage>();
}
void ReqQrySETradePackage::Free()
{
	Package::Free();
	if (ReqQrySETrade != nullptr)
	{
		::Free<ReqQrySETradeField>(ReqQrySETrade);
		ReqQrySETrade = nullptr;
	}
	MemCacheTemplateSingleton<ReqQrySETradePackage>::GetInstance().Free(this);
}
void ReqQrySETradePackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqQrySETradePackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqQrySETrade != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqQrySETradeField::FieldID);
		if (strlen(ReqQrySETrade->AccountID) >= sizeof(ReqQrySETrade->AccountID))
		{
			ReqQrySETrade->AccountID[sizeof(ReqQrySETrade->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, ReqQrySETrade->AccountID);
		WriteHexString(ppos, Items::FieldEnd, ReqQrySETradeField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqQrySETradePackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqQrySETradeField::FieldID:
			{
				ReqQrySETrade = ::Allocate<ReqQrySETradeField>();
				memset(ReqQrySETrade, 0, sizeof(*ReqQrySETrade));
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
							size_t len = value.length() >= sizeof(ReqQrySETrade->AccountID) ? sizeof(ReqQrySETrade->AccountID) - 1 : value.length();
							memcpy(ReqQrySETrade->AccountID, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqQrySETradeField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqQrySETradePackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqQrySETradePackage");
			return false;
		}
	}
	return true;
}
int ReqQrySETradePackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqQrySETrade != nullptr)
	{
		memcpy(buff + offset, &ReqQrySETradeField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqQrySETrade, sizeof(ReqQrySETradeField));
		offset += sizeof(ReqQrySETradeField);
	}
	return offset;
}
bool ReqQrySETradePackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqQrySETradeField::FieldID:
		{
			ReqQrySETrade = ::Allocate<ReqQrySETradeField>();
			memcpy(ReqQrySETrade, buff + offset, sizeof(ReqQrySETradeField));
			offset += sizeof(ReqQrySETradeField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqQrySETradePackage::GetDebugString() const
{
	int offset = 0;
	if (ReqQrySETrade != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqQrySETrade:AccountID:[%s]", ReqQrySETrade->AccountID);
	}
	return t_DataStringBuffer;
}
 
RspQrySETradePackage* RspQrySETradePackage::Allocate()
{
	return ::Allocate<RspQrySETradePackage>();
}
void RspQrySETradePackage::Free()
{
	Package::Free();
	if (SETrade != nullptr)
	{
		::Free<SETradeField>(SETrade);
		SETrade = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspQrySETradePackage>::GetInstance().Free(this);
}
void RspQrySETradePackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspQrySETradePackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (SETrade != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, SETradeField::FieldID);
		if (strlen(SETrade->TradingDay) >= sizeof(SETrade->TradingDay))
		{
			SETrade->TradingDay[sizeof(SETrade->TradingDay) - 1] = 0;
		}
		WriteString(ppos, Items::TradingDay, SETrade->TradingDay);
		WriteString(ppos, Items::BrokerID, SETrade->BrokerID);
		if (strlen(SETrade->AccountID) >= sizeof(SETrade->AccountID))
		{
			SETrade->AccountID[sizeof(SETrade->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, SETrade->AccountID);
		if (strlen(SETrade->ExchangeID) >= sizeof(SETrade->ExchangeID))
		{
			SETrade->ExchangeID[sizeof(SETrade->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, SETrade->ExchangeID);
		if (strlen(SETrade->InstrumentID) >= sizeof(SETrade->InstrumentID))
		{
			SETrade->InstrumentID[sizeof(SETrade->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, SETrade->InstrumentID);
		WriteString(ppos, Items::ProductClass, (int)SETrade->ProductClass);
		WriteString(ppos, Items::OrderID, SETrade->OrderID);
		if (strlen(SETrade->TradeID) >= sizeof(SETrade->TradeID))
		{
			SETrade->TradeID[sizeof(SETrade->TradeID) - 1] = 0;
		}
		WriteString(ppos, Items::TradeID, SETrade->TradeID);
		WriteString(ppos, Items::Direction, (int)SETrade->Direction);
		WriteString(ppos, Items::OffsetFlag, (int)SETrade->OffsetFlag);
		WriteString(ppos, Items::Price, SETrade->Price);
		WriteString(ppos, Items::Volume, SETrade->Volume);
		WriteString(ppos, Items::VolumeMultiple, SETrade->VolumeMultiple);
		WriteString(ppos, Items::TradeAmount, SETrade->TradeAmount);
		WriteString(ppos, Items::Commission, SETrade->Commission);
		if (strlen(SETrade->TradeDate) >= sizeof(SETrade->TradeDate))
		{
			SETrade->TradeDate[sizeof(SETrade->TradeDate) - 1] = 0;
		}
		WriteString(ppos, Items::TradeDate, SETrade->TradeDate);
		if (strlen(SETrade->TradeTime) >= sizeof(SETrade->TradeTime))
		{
			SETrade->TradeTime[sizeof(SETrade->TradeTime) - 1] = 0;
		}
		WriteString(ppos, Items::TradeTime, SETrade->TradeTime);
		WriteHexString(ppos, Items::FieldEnd, SETradeField::FieldID);
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
bool RspQrySETradePackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case SETradeField::FieldID:
			{
				SETrade = ::Allocate<SETradeField>();
				memset(SETrade, 0, sizeof(*SETrade));
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
							size_t len = value.length() >= sizeof(SETrade->TradingDay) ? sizeof(SETrade->TradingDay) - 1 : value.length();
							memcpy(SETrade->TradingDay, value.c_str(), len);
							break;
						}
						case Items::BrokerID:
						{
							SETrade->BrokerID = atoi(value.c_str());
							break;
						}
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(SETrade->AccountID) ? sizeof(SETrade->AccountID) - 1 : value.length();
							memcpy(SETrade->AccountID, value.c_str(), len);
							break;
						}
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(SETrade->ExchangeID) ? sizeof(SETrade->ExchangeID) - 1 : value.length();
							memcpy(SETrade->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(SETrade->InstrumentID) ? sizeof(SETrade->InstrumentID) - 1 : value.length();
							memcpy(SETrade->InstrumentID, value.c_str(), len);
							break;
						}
						case Items::ProductClass:
						{
							SETrade->ProductClass = (ProductClassType)(atoi(value.c_str()));
							break;
						}
						case Items::OrderID:
						{
							SETrade->OrderID = atoi(value.c_str());
							break;
						}
						case Items::TradeID:
						{
							size_t len = value.length() >= sizeof(SETrade->TradeID) ? sizeof(SETrade->TradeID) - 1 : value.length();
							memcpy(SETrade->TradeID, value.c_str(), len);
							break;
						}
						case Items::Direction:
						{
							SETrade->Direction = (DirectionType)(atoi(value.c_str()));
							break;
						}
						case Items::OffsetFlag:
						{
							SETrade->OffsetFlag = (OffsetFlagType)(atoi(value.c_str()));
							break;
						}
						case Items::Price:
						{
							SETrade->Price = atof(value.c_str());
							break;
						}
						case Items::Volume:
						{
							SETrade->Volume = atoll(value.c_str());
							break;
						}
						case Items::VolumeMultiple:
						{
							SETrade->VolumeMultiple = atoi(value.c_str());
							break;
						}
						case Items::TradeAmount:
						{
							SETrade->TradeAmount = atof(value.c_str());
							break;
						}
						case Items::Commission:
						{
							SETrade->Commission = atof(value.c_str());
							break;
						}
						case Items::TradeDate:
						{
							size_t len = value.length() >= sizeof(SETrade->TradeDate) ? sizeof(SETrade->TradeDate) - 1 : value.length();
							memcpy(SETrade->TradeDate, value.c_str(), len);
							break;
						}
						case Items::TradeTime:
						{
							size_t len = value.length() >= sizeof(SETrade->TradeTime) ? sizeof(SETrade->TradeTime) - 1 : value.length();
							memcpy(SETrade->TradeTime, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for SETradeField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQrySETradePackage FieldID:0x%X", fieldID);
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
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQrySETradePackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspQrySETradePackage");
			return false;
		}
	}
	return true;
}
int RspQrySETradePackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (SETrade != nullptr)
	{
		memcpy(buff + offset, &SETradeField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, SETrade, sizeof(SETradeField));
		offset += sizeof(SETradeField);
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
bool RspQrySETradePackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case SETradeField::FieldID:
		{
			SETrade = ::Allocate<SETradeField>();
			memcpy(SETrade, buff + offset, sizeof(SETradeField));
			offset += sizeof(SETradeField);	
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
const char* RspQrySETradePackage::GetDebugString() const
{
	int offset = 0;
	if (SETrade != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "SETrade:TradingDay:[%s], BrokerID:[%d], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], TradeID:[%s], Direction:[%d], OffsetFlag:[%d], Price:[%f], Volume:[%lld], VolumeMultiple:[%d], TradeAmount:[%f], Commission:[%f], TradeDate:[%s], TradeTime:[%s]", SETrade->TradingDay, SETrade->BrokerID, SETrade->AccountID, SETrade->ExchangeID, SETrade->InstrumentID, (int)SETrade->ProductClass, SETrade->OrderID, SETrade->TradeID, (int)SETrade->Direction, (int)SETrade->OffsetFlag, SETrade->Price, SETrade->Volume, SETrade->VolumeMultiple, SETrade->TradeAmount, SETrade->Commission, SETrade->TradeDate, SETrade->TradeTime);
	}
	if (RspInfo != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
	return t_DataStringBuffer;
}
 
ReqQrySEInstrumentPackage* ReqQrySEInstrumentPackage::Allocate()
{
	return ::Allocate<ReqQrySEInstrumentPackage>();
}
void ReqQrySEInstrumentPackage::Free()
{
	Package::Free();
	if (ReqQrySEInstrument != nullptr)
	{
		::Free<ReqQrySEInstrumentField>(ReqQrySEInstrument);
		ReqQrySEInstrument = nullptr;
	}
	MemCacheTemplateSingleton<ReqQrySEInstrumentPackage>::GetInstance().Free(this);
}
void ReqQrySEInstrumentPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqQrySEInstrumentPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqQrySEInstrument != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqQrySEInstrumentField::FieldID);
		if (strlen(ReqQrySEInstrument->ExchangeID) >= sizeof(ReqQrySEInstrument->ExchangeID))
		{
			ReqQrySEInstrument->ExchangeID[sizeof(ReqQrySEInstrument->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, ReqQrySEInstrument->ExchangeID);
		if (strlen(ReqQrySEInstrument->InstrumentID) >= sizeof(ReqQrySEInstrument->InstrumentID))
		{
			ReqQrySEInstrument->InstrumentID[sizeof(ReqQrySEInstrument->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, ReqQrySEInstrument->InstrumentID);
		WriteHexString(ppos, Items::FieldEnd, ReqQrySEInstrumentField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqQrySEInstrumentPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqQrySEInstrumentField::FieldID:
			{
				ReqQrySEInstrument = ::Allocate<ReqQrySEInstrumentField>();
				memset(ReqQrySEInstrument, 0, sizeof(*ReqQrySEInstrument));
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
							size_t len = value.length() >= sizeof(ReqQrySEInstrument->ExchangeID) ? sizeof(ReqQrySEInstrument->ExchangeID) - 1 : value.length();
							memcpy(ReqQrySEInstrument->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(ReqQrySEInstrument->InstrumentID) ? sizeof(ReqQrySEInstrument->InstrumentID) - 1 : value.length();
							memcpy(ReqQrySEInstrument->InstrumentID, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqQrySEInstrumentField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqQrySEInstrumentPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqQrySEInstrumentPackage");
			return false;
		}
	}
	return true;
}
int ReqQrySEInstrumentPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqQrySEInstrument != nullptr)
	{
		memcpy(buff + offset, &ReqQrySEInstrumentField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqQrySEInstrument, sizeof(ReqQrySEInstrumentField));
		offset += sizeof(ReqQrySEInstrumentField);
	}
	return offset;
}
bool ReqQrySEInstrumentPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqQrySEInstrumentField::FieldID:
		{
			ReqQrySEInstrument = ::Allocate<ReqQrySEInstrumentField>();
			memcpy(ReqQrySEInstrument, buff + offset, sizeof(ReqQrySEInstrumentField));
			offset += sizeof(ReqQrySEInstrumentField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqQrySEInstrumentPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqQrySEInstrument != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqQrySEInstrument:ExchangeID:[%s], InstrumentID:[%s]", ReqQrySEInstrument->ExchangeID, ReqQrySEInstrument->InstrumentID);
	}
	return t_DataStringBuffer;
}
 
RspQrySEInstrumentPackage* RspQrySEInstrumentPackage::Allocate()
{
	return ::Allocate<RspQrySEInstrumentPackage>();
}
void RspQrySEInstrumentPackage::Free()
{
	Package::Free();
	if (SEInstrument != nullptr)
	{
		::Free<SEInstrumentField>(SEInstrument);
		SEInstrument = nullptr;
	}
	if (RspInfo != nullptr)
	{
		::Free<RspInfoField>(RspInfo);
		RspInfo = nullptr;
	}
	MemCacheTemplateSingleton<RspQrySEInstrumentPackage>::GetInstance().Free(this);
}
void RspQrySEInstrumentPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspQrySEInstrumentPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (SEInstrument != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, SEInstrumentField::FieldID);
		if (strlen(SEInstrument->ExchangeID) >= sizeof(SEInstrument->ExchangeID))
		{
			SEInstrument->ExchangeID[sizeof(SEInstrument->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, SEInstrument->ExchangeID);
		if (strlen(SEInstrument->InstrumentID) >= sizeof(SEInstrument->InstrumentID))
		{
			SEInstrument->InstrumentID[sizeof(SEInstrument->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, SEInstrument->InstrumentID);
		if (strlen(SEInstrument->ExchangeInstID) >= sizeof(SEInstrument->ExchangeInstID))
		{
			SEInstrument->ExchangeInstID[sizeof(SEInstrument->ExchangeInstID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeInstID, SEInstrument->ExchangeInstID);
		if (strlen(SEInstrument->InstrumentName) >= sizeof(SEInstrument->InstrumentName))
		{
			SEInstrument->InstrumentName[sizeof(SEInstrument->InstrumentName) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentName, SEInstrument->InstrumentName);
		if (strlen(SEInstrument->ProductID) >= sizeof(SEInstrument->ProductID))
		{
			SEInstrument->ProductID[sizeof(SEInstrument->ProductID) - 1] = 0;
		}
		WriteString(ppos, Items::ProductID, SEInstrument->ProductID);
		WriteString(ppos, Items::ProductClass, (int)SEInstrument->ProductClass);
		WriteString(ppos, Items::MaxMarketOrderVolume, SEInstrument->MaxMarketOrderVolume);
		WriteString(ppos, Items::MinMarketOrderVolume, SEInstrument->MinMarketOrderVolume);
		WriteString(ppos, Items::MaxLimitOrderVolume, SEInstrument->MaxLimitOrderVolume);
		WriteString(ppos, Items::MinLimitOrderVolume, SEInstrument->MinLimitOrderVolume);
		WriteString(ppos, Items::VolumeMultiple, SEInstrument->VolumeMultiple);
		WriteString(ppos, Items::PriceTick, SEInstrument->PriceTick);
		WriteString(ppos, Items::UpperLimitPrice, SEInstrument->UpperLimitPrice);
		WriteString(ppos, Items::LowerLimitPrice, SEInstrument->LowerLimitPrice);
		WriteHexString(ppos, Items::FieldEnd, SEInstrumentField::FieldID);
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
bool RspQrySEInstrumentPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case SEInstrumentField::FieldID:
			{
				SEInstrument = ::Allocate<SEInstrumentField>();
				memset(SEInstrument, 0, sizeof(*SEInstrument));
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
							size_t len = value.length() >= sizeof(SEInstrument->ExchangeID) ? sizeof(SEInstrument->ExchangeID) - 1 : value.length();
							memcpy(SEInstrument->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(SEInstrument->InstrumentID) ? sizeof(SEInstrument->InstrumentID) - 1 : value.length();
							memcpy(SEInstrument->InstrumentID, value.c_str(), len);
							break;
						}
						case Items::ExchangeInstID:
						{
							size_t len = value.length() >= sizeof(SEInstrument->ExchangeInstID) ? sizeof(SEInstrument->ExchangeInstID) - 1 : value.length();
							memcpy(SEInstrument->ExchangeInstID, value.c_str(), len);
							break;
						}
						case Items::InstrumentName:
						{
							size_t len = value.length() >= sizeof(SEInstrument->InstrumentName) ? sizeof(SEInstrument->InstrumentName) - 1 : value.length();
							memcpy(SEInstrument->InstrumentName, value.c_str(), len);
							break;
						}
						case Items::ProductID:
						{
							size_t len = value.length() >= sizeof(SEInstrument->ProductID) ? sizeof(SEInstrument->ProductID) - 1 : value.length();
							memcpy(SEInstrument->ProductID, value.c_str(), len);
							break;
						}
						case Items::ProductClass:
						{
							SEInstrument->ProductClass = (ProductClassType)(atoi(value.c_str()));
							break;
						}
						case Items::MaxMarketOrderVolume:
						{
							SEInstrument->MaxMarketOrderVolume = atoll(value.c_str());
							break;
						}
						case Items::MinMarketOrderVolume:
						{
							SEInstrument->MinMarketOrderVolume = atoll(value.c_str());
							break;
						}
						case Items::MaxLimitOrderVolume:
						{
							SEInstrument->MaxLimitOrderVolume = atoll(value.c_str());
							break;
						}
						case Items::MinLimitOrderVolume:
						{
							SEInstrument->MinLimitOrderVolume = atoll(value.c_str());
							break;
						}
						case Items::VolumeMultiple:
						{
							SEInstrument->VolumeMultiple = atoi(value.c_str());
							break;
						}
						case Items::PriceTick:
						{
							SEInstrument->PriceTick = atof(value.c_str());
							break;
						}
						case Items::UpperLimitPrice:
						{
							SEInstrument->UpperLimitPrice = atof(value.c_str());
							break;
						}
						case Items::LowerLimitPrice:
						{
							SEInstrument->LowerLimitPrice = atof(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for SEInstrumentField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQrySEInstrumentPackage FieldID:0x%X", fieldID);
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
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQrySEInstrumentPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspQrySEInstrumentPackage");
			return false;
		}
	}
	return true;
}
int RspQrySEInstrumentPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (SEInstrument != nullptr)
	{
		memcpy(buff + offset, &SEInstrumentField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, SEInstrument, sizeof(SEInstrumentField));
		offset += sizeof(SEInstrumentField);
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
bool RspQrySEInstrumentPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case SEInstrumentField::FieldID:
		{
			SEInstrument = ::Allocate<SEInstrumentField>();
			memcpy(SEInstrument, buff + offset, sizeof(SEInstrumentField));
			offset += sizeof(SEInstrumentField);	
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
const char* RspQrySEInstrumentPackage::GetDebugString() const
{
	int offset = 0;
	if (SEInstrument != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "SEInstrument:ExchangeID:[%s], InstrumentID:[%s], ExchangeInstID:[%s], InstrumentName:[%s], ProductID:[%s], ProductClass:[%d], MaxMarketOrderVolume:[%lld], MinMarketOrderVolume:[%lld], MaxLimitOrderVolume:[%lld], MinLimitOrderVolume:[%lld], VolumeMultiple:[%d], PriceTick:[%f], UpperLimitPrice:[%f], LowerLimitPrice:[%f]", SEInstrument->ExchangeID, SEInstrument->InstrumentID, SEInstrument->ExchangeInstID, SEInstrument->InstrumentName, SEInstrument->ProductID, (int)SEInstrument->ProductClass, SEInstrument->MaxMarketOrderVolume, SEInstrument->MinMarketOrderVolume, SEInstrument->MaxLimitOrderVolume, SEInstrument->MinLimitOrderVolume, SEInstrument->VolumeMultiple, SEInstrument->PriceTick, SEInstrument->UpperLimitPrice, SEInstrument->LowerLimitPrice);
	}
	if (RspInfo != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
	return t_DataStringBuffer;
}
 
RtnSEOrderPackage* RtnSEOrderPackage::Allocate()
{
	return ::Allocate<RtnSEOrderPackage>();
}
void RtnSEOrderPackage::Free()
{
	Package::Free();
	if (SEOrder != nullptr)
	{
		::Free<SEOrderField>(SEOrder);
		SEOrder = nullptr;
	}
	MemCacheTemplateSingleton<RtnSEOrderPackage>::GetInstance().Free(this);
}
void RtnSEOrderPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RtnSEOrderPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (SEOrder != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, SEOrderField::FieldID);
		if (strlen(SEOrder->TradingDay) >= sizeof(SEOrder->TradingDay))
		{
			SEOrder->TradingDay[sizeof(SEOrder->TradingDay) - 1] = 0;
		}
		WriteString(ppos, Items::TradingDay, SEOrder->TradingDay);
		WriteString(ppos, Items::BrokerID, SEOrder->BrokerID);
		if (strlen(SEOrder->AccountID) >= sizeof(SEOrder->AccountID))
		{
			SEOrder->AccountID[sizeof(SEOrder->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, SEOrder->AccountID);
		if (strlen(SEOrder->ExchangeID) >= sizeof(SEOrder->ExchangeID))
		{
			SEOrder->ExchangeID[sizeof(SEOrder->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, SEOrder->ExchangeID);
		if (strlen(SEOrder->InstrumentID) >= sizeof(SEOrder->InstrumentID))
		{
			SEOrder->InstrumentID[sizeof(SEOrder->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, SEOrder->InstrumentID);
		WriteString(ppos, Items::ProductClass, (int)SEOrder->ProductClass);
		WriteString(ppos, Items::OrderID, SEOrder->OrderID);
		WriteString(ppos, Items::Direction, (int)SEOrder->Direction);
		WriteString(ppos, Items::OffsetFlag, (int)SEOrder->OffsetFlag);
		WriteString(ppos, Items::OrderPriceType, (int)SEOrder->OrderPriceType);
		WriteString(ppos, Items::Price, SEOrder->Price);
		WriteString(ppos, Items::Volume, SEOrder->Volume);
		WriteString(ppos, Items::VolumeTotal, SEOrder->VolumeTotal);
		WriteString(ppos, Items::VolumeTraded, SEOrder->VolumeTraded);
		WriteString(ppos, Items::VolumeMultiple, SEOrder->VolumeMultiple);
		WriteString(ppos, Items::OrderStatus, (int)SEOrder->OrderStatus);
		if (strlen(SEOrder->OrderDate) >= sizeof(SEOrder->OrderDate))
		{
			SEOrder->OrderDate[sizeof(SEOrder->OrderDate) - 1] = 0;
		}
		WriteString(ppos, Items::OrderDate, SEOrder->OrderDate);
		if (strlen(SEOrder->OrderTime) >= sizeof(SEOrder->OrderTime))
		{
			SEOrder->OrderTime[sizeof(SEOrder->OrderTime) - 1] = 0;
		}
		WriteString(ppos, Items::OrderTime, SEOrder->OrderTime);
		if (strlen(SEOrder->CancelDate) >= sizeof(SEOrder->CancelDate))
		{
			SEOrder->CancelDate[sizeof(SEOrder->CancelDate) - 1] = 0;
		}
		WriteString(ppos, Items::CancelDate, SEOrder->CancelDate);
		if (strlen(SEOrder->CancelTime) >= sizeof(SEOrder->CancelTime))
		{
			SEOrder->CancelTime[sizeof(SEOrder->CancelTime) - 1] = 0;
		}
		WriteString(ppos, Items::CancelTime, SEOrder->CancelTime);
		WriteString(ppos, Items::SessionID, SEOrder->SessionID);
		WriteString(ppos, Items::ClientOrderID, SEOrder->ClientOrderID);
		WriteHexString(ppos, Items::FieldEnd, SEOrderField::FieldID);
	}
	return int(ppos - buff);
}
bool RtnSEOrderPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case SEOrderField::FieldID:
			{
				SEOrder = ::Allocate<SEOrderField>();
				memset(SEOrder, 0, sizeof(*SEOrder));
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
							size_t len = value.length() >= sizeof(SEOrder->TradingDay) ? sizeof(SEOrder->TradingDay) - 1 : value.length();
							memcpy(SEOrder->TradingDay, value.c_str(), len);
							break;
						}
						case Items::BrokerID:
						{
							SEOrder->BrokerID = atoi(value.c_str());
							break;
						}
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(SEOrder->AccountID) ? sizeof(SEOrder->AccountID) - 1 : value.length();
							memcpy(SEOrder->AccountID, value.c_str(), len);
							break;
						}
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(SEOrder->ExchangeID) ? sizeof(SEOrder->ExchangeID) - 1 : value.length();
							memcpy(SEOrder->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(SEOrder->InstrumentID) ? sizeof(SEOrder->InstrumentID) - 1 : value.length();
							memcpy(SEOrder->InstrumentID, value.c_str(), len);
							break;
						}
						case Items::ProductClass:
						{
							SEOrder->ProductClass = (ProductClassType)(atoi(value.c_str()));
							break;
						}
						case Items::OrderID:
						{
							SEOrder->OrderID = atoi(value.c_str());
							break;
						}
						case Items::Direction:
						{
							SEOrder->Direction = (DirectionType)(atoi(value.c_str()));
							break;
						}
						case Items::OffsetFlag:
						{
							SEOrder->OffsetFlag = (OffsetFlagType)(atoi(value.c_str()));
							break;
						}
						case Items::OrderPriceType:
						{
							SEOrder->OrderPriceType = (OrderPriceTypeType)(atoi(value.c_str()));
							break;
						}
						case Items::Price:
						{
							SEOrder->Price = atof(value.c_str());
							break;
						}
						case Items::Volume:
						{
							SEOrder->Volume = atoll(value.c_str());
							break;
						}
						case Items::VolumeTotal:
						{
							SEOrder->VolumeTotal = atoll(value.c_str());
							break;
						}
						case Items::VolumeTraded:
						{
							SEOrder->VolumeTraded = atoll(value.c_str());
							break;
						}
						case Items::VolumeMultiple:
						{
							SEOrder->VolumeMultiple = atoi(value.c_str());
							break;
						}
						case Items::OrderStatus:
						{
							SEOrder->OrderStatus = (OrderStatusType)(atoi(value.c_str()));
							break;
						}
						case Items::OrderDate:
						{
							size_t len = value.length() >= sizeof(SEOrder->OrderDate) ? sizeof(SEOrder->OrderDate) - 1 : value.length();
							memcpy(SEOrder->OrderDate, value.c_str(), len);
							break;
						}
						case Items::OrderTime:
						{
							size_t len = value.length() >= sizeof(SEOrder->OrderTime) ? sizeof(SEOrder->OrderTime) - 1 : value.length();
							memcpy(SEOrder->OrderTime, value.c_str(), len);
							break;
						}
						case Items::CancelDate:
						{
							size_t len = value.length() >= sizeof(SEOrder->CancelDate) ? sizeof(SEOrder->CancelDate) - 1 : value.length();
							memcpy(SEOrder->CancelDate, value.c_str(), len);
							break;
						}
						case Items::CancelTime:
						{
							size_t len = value.length() >= sizeof(SEOrder->CancelTime) ? sizeof(SEOrder->CancelTime) - 1 : value.length();
							memcpy(SEOrder->CancelTime, value.c_str(), len);
							break;
						}
						case Items::SessionID:
						{
							SEOrder->SessionID = atoll(value.c_str());
							break;
						}
						case Items::ClientOrderID:
						{
							SEOrder->ClientOrderID = atoi(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for SEOrderField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RtnSEOrderPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RtnSEOrderPackage");
			return false;
		}
	}
	return true;
}
int RtnSEOrderPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (SEOrder != nullptr)
	{
		memcpy(buff + offset, &SEOrderField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, SEOrder, sizeof(SEOrderField));
		offset += sizeof(SEOrderField);
	}
	return offset;
}
bool RtnSEOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case SEOrderField::FieldID:
		{
			SEOrder = ::Allocate<SEOrderField>();
			memcpy(SEOrder, buff + offset, sizeof(SEOrderField));
			offset += sizeof(SEOrderField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* RtnSEOrderPackage::GetDebugString() const
{
	int offset = 0;
	if (SEOrder != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "SEOrder:TradingDay:[%s], BrokerID:[%d], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], VolumeTotal:[%lld], VolumeTraded:[%lld], VolumeMultiple:[%d], OrderStatus:[%d], OrderDate:[%s], OrderTime:[%s], CancelDate:[%s], CancelTime:[%s], SessionID:[%lld], ClientOrderID:[%d]", SEOrder->TradingDay, SEOrder->BrokerID, SEOrder->AccountID, SEOrder->ExchangeID, SEOrder->InstrumentID, (int)SEOrder->ProductClass, SEOrder->OrderID, (int)SEOrder->Direction, (int)SEOrder->OffsetFlag, (int)SEOrder->OrderPriceType, SEOrder->Price, SEOrder->Volume, SEOrder->VolumeTotal, SEOrder->VolumeTraded, SEOrder->VolumeMultiple, (int)SEOrder->OrderStatus, SEOrder->OrderDate, SEOrder->OrderTime, SEOrder->CancelDate, SEOrder->CancelTime, SEOrder->SessionID, SEOrder->ClientOrderID);
	}
	return t_DataStringBuffer;
}
 
RtnSETradePackage* RtnSETradePackage::Allocate()
{
	return ::Allocate<RtnSETradePackage>();
}
void RtnSETradePackage::Free()
{
	Package::Free();
	if (SETrade != nullptr)
	{
		::Free<SETradeField>(SETrade);
		SETrade = nullptr;
	}
	MemCacheTemplateSingleton<RtnSETradePackage>::GetInstance().Free(this);
}
void RtnSETradePackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RtnSETradePackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (SETrade != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, SETradeField::FieldID);
		if (strlen(SETrade->TradingDay) >= sizeof(SETrade->TradingDay))
		{
			SETrade->TradingDay[sizeof(SETrade->TradingDay) - 1] = 0;
		}
		WriteString(ppos, Items::TradingDay, SETrade->TradingDay);
		WriteString(ppos, Items::BrokerID, SETrade->BrokerID);
		if (strlen(SETrade->AccountID) >= sizeof(SETrade->AccountID))
		{
			SETrade->AccountID[sizeof(SETrade->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, SETrade->AccountID);
		if (strlen(SETrade->ExchangeID) >= sizeof(SETrade->ExchangeID))
		{
			SETrade->ExchangeID[sizeof(SETrade->ExchangeID) - 1] = 0;
		}
		WriteString(ppos, Items::ExchangeID, SETrade->ExchangeID);
		if (strlen(SETrade->InstrumentID) >= sizeof(SETrade->InstrumentID))
		{
			SETrade->InstrumentID[sizeof(SETrade->InstrumentID) - 1] = 0;
		}
		WriteString(ppos, Items::InstrumentID, SETrade->InstrumentID);
		WriteString(ppos, Items::ProductClass, (int)SETrade->ProductClass);
		WriteString(ppos, Items::OrderID, SETrade->OrderID);
		if (strlen(SETrade->TradeID) >= sizeof(SETrade->TradeID))
		{
			SETrade->TradeID[sizeof(SETrade->TradeID) - 1] = 0;
		}
		WriteString(ppos, Items::TradeID, SETrade->TradeID);
		WriteString(ppos, Items::Direction, (int)SETrade->Direction);
		WriteString(ppos, Items::OffsetFlag, (int)SETrade->OffsetFlag);
		WriteString(ppos, Items::Price, SETrade->Price);
		WriteString(ppos, Items::Volume, SETrade->Volume);
		WriteString(ppos, Items::VolumeMultiple, SETrade->VolumeMultiple);
		WriteString(ppos, Items::TradeAmount, SETrade->TradeAmount);
		WriteString(ppos, Items::Commission, SETrade->Commission);
		if (strlen(SETrade->TradeDate) >= sizeof(SETrade->TradeDate))
		{
			SETrade->TradeDate[sizeof(SETrade->TradeDate) - 1] = 0;
		}
		WriteString(ppos, Items::TradeDate, SETrade->TradeDate);
		if (strlen(SETrade->TradeTime) >= sizeof(SETrade->TradeTime))
		{
			SETrade->TradeTime[sizeof(SETrade->TradeTime) - 1] = 0;
		}
		WriteString(ppos, Items::TradeTime, SETrade->TradeTime);
		WriteHexString(ppos, Items::FieldEnd, SETradeField::FieldID);
	}
	return int(ppos - buff);
}
bool RtnSETradePackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case SETradeField::FieldID:
			{
				SETrade = ::Allocate<SETradeField>();
				memset(SETrade, 0, sizeof(*SETrade));
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
							size_t len = value.length() >= sizeof(SETrade->TradingDay) ? sizeof(SETrade->TradingDay) - 1 : value.length();
							memcpy(SETrade->TradingDay, value.c_str(), len);
							break;
						}
						case Items::BrokerID:
						{
							SETrade->BrokerID = atoi(value.c_str());
							break;
						}
						case Items::AccountID:
						{
							size_t len = value.length() >= sizeof(SETrade->AccountID) ? sizeof(SETrade->AccountID) - 1 : value.length();
							memcpy(SETrade->AccountID, value.c_str(), len);
							break;
						}
						case Items::ExchangeID:
						{
							size_t len = value.length() >= sizeof(SETrade->ExchangeID) ? sizeof(SETrade->ExchangeID) - 1 : value.length();
							memcpy(SETrade->ExchangeID, value.c_str(), len);
							break;
						}
						case Items::InstrumentID:
						{
							size_t len = value.length() >= sizeof(SETrade->InstrumentID) ? sizeof(SETrade->InstrumentID) - 1 : value.length();
							memcpy(SETrade->InstrumentID, value.c_str(), len);
							break;
						}
						case Items::ProductClass:
						{
							SETrade->ProductClass = (ProductClassType)(atoi(value.c_str()));
							break;
						}
						case Items::OrderID:
						{
							SETrade->OrderID = atoi(value.c_str());
							break;
						}
						case Items::TradeID:
						{
							size_t len = value.length() >= sizeof(SETrade->TradeID) ? sizeof(SETrade->TradeID) - 1 : value.length();
							memcpy(SETrade->TradeID, value.c_str(), len);
							break;
						}
						case Items::Direction:
						{
							SETrade->Direction = (DirectionType)(atoi(value.c_str()));
							break;
						}
						case Items::OffsetFlag:
						{
							SETrade->OffsetFlag = (OffsetFlagType)(atoi(value.c_str()));
							break;
						}
						case Items::Price:
						{
							SETrade->Price = atof(value.c_str());
							break;
						}
						case Items::Volume:
						{
							SETrade->Volume = atoll(value.c_str());
							break;
						}
						case Items::VolumeMultiple:
						{
							SETrade->VolumeMultiple = atoi(value.c_str());
							break;
						}
						case Items::TradeAmount:
						{
							SETrade->TradeAmount = atof(value.c_str());
							break;
						}
						case Items::Commission:
						{
							SETrade->Commission = atof(value.c_str());
							break;
						}
						case Items::TradeDate:
						{
							size_t len = value.length() >= sizeof(SETrade->TradeDate) ? sizeof(SETrade->TradeDate) - 1 : value.length();
							memcpy(SETrade->TradeDate, value.c_str(), len);
							break;
						}
						case Items::TradeTime:
						{
							size_t len = value.length() >= sizeof(SETrade->TradeTime) ? sizeof(SETrade->TradeTime) - 1 : value.length();
							memcpy(SETrade->TradeTime, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for SETradeField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RtnSETradePackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RtnSETradePackage");
			return false;
		}
	}
	return true;
}
int RtnSETradePackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (SETrade != nullptr)
	{
		memcpy(buff + offset, &SETradeField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, SETrade, sizeof(SETradeField));
		offset += sizeof(SETradeField);
	}
	return offset;
}
bool RtnSETradePackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case SETradeField::FieldID:
		{
			SETrade = ::Allocate<SETradeField>();
			memcpy(SETrade, buff + offset, sizeof(SETradeField));
			offset += sizeof(SETradeField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* RtnSETradePackage::GetDebugString() const
{
	int offset = 0;
	if (SETrade != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "SETrade:TradingDay:[%s], BrokerID:[%d], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], TradeID:[%s], Direction:[%d], OffsetFlag:[%d], Price:[%f], Volume:[%lld], VolumeMultiple:[%d], TradeAmount:[%f], Commission:[%f], TradeDate:[%s], TradeTime:[%s]", SETrade->TradingDay, SETrade->BrokerID, SETrade->AccountID, SETrade->ExchangeID, SETrade->InstrumentID, (int)SETrade->ProductClass, SETrade->OrderID, SETrade->TradeID, (int)SETrade->Direction, (int)SETrade->OffsetFlag, SETrade->Price, SETrade->Volume, SETrade->VolumeMultiple, SETrade->TradeAmount, SETrade->Commission, SETrade->TradeDate, SETrade->TradeTime);
	}
	return t_DataStringBuffer;
}
