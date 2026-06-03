#include "Packages.h"
#include "Protocol/Items.h"
#include "Protocol/StepUtility.h"
#include "Logger/Logger.h"
#include "ObjectPool/ObjectPool.h"
#include <cstring>

thread_local char t_DataStringBuffer[10240];



 
NotifyConnectPackage::NotifyConnectPackage()
	:NotifyConnect(nullptr)
{
}
NotifyConnectPackage::~NotifyConnectPackage()
{
	if (NotifyConnect != nullptr)
	{
		ObjectPool<NotifyConnectField>::GetInstance().Deallocate(NotifyConnect);
		NotifyConnect = nullptr;
	}
}
NotifyConnectPackage* NotifyConnectPackage::Allocate()
{
	return ObjectPool<NotifyConnectPackage>::GetInstance().Allocate();
}
void NotifyConnectPackage::Deallocate()
{
	ObjectPool<NotifyConnectPackage>::GetInstance().Deallocate(this);
}
void NotifyConnectPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int NotifyConnectPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (NotifyConnect != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, NotifyConnectField::FieldID);
		WriteString(ppos, Items::SessionID, NotifyConnect->SessionID);
		if (strlen(NotifyConnect->IPAddress) >= sizeof(NotifyConnect->IPAddress))
		{
			NotifyConnect->IPAddress[sizeof(NotifyConnect->IPAddress) - 1] = 0;
		}
		WriteString(ppos, Items::IPAddress, NotifyConnect->IPAddress);
		WriteString(ppos, Items::Port, NotifyConnect->Port);
		WriteHexString(ppos, Items::FieldEnd, NotifyConnectField::FieldID);
	}
	return int(ppos - buff);
}
bool NotifyConnectPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case NotifyConnectField::FieldID:
			{
				NotifyConnect = ObjectPool<NotifyConnectField>::GetInstance().Allocate();
				memset(NotifyConnect, 0, sizeof(*NotifyConnect));
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
						case Items::SessionID:
						{
							NotifyConnect->SessionID = atoll(value.c_str());
							break;
						}
						case Items::IPAddress:
						{
							size_t len = value.length() >= sizeof(NotifyConnect->IPAddress) ? sizeof(NotifyConnect->IPAddress) - 1 : value.length();
							memcpy(NotifyConnect->IPAddress, value.c_str(), len);
							break;
						}
						case Items::Port:
						{
							NotifyConnect->Port = atoi(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for NotifyConnectField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For NotifyConnectPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For NotifyConnectPackage");
			return false;
		}
	}
	return true;
}
int NotifyConnectPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (NotifyConnect != nullptr)
	{
		memcpy(buff + offset, &NotifyConnectField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, NotifyConnect, sizeof(NotifyConnectField));
		offset += sizeof(NotifyConnectField);
	}
	return offset;
}
bool NotifyConnectPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case NotifyConnectField::FieldID:
		{
			NotifyConnect = ObjectPool<NotifyConnectField>::GetInstance().Allocate();
			memcpy(NotifyConnect, buff + offset, sizeof(NotifyConnectField));
			offset += sizeof(NotifyConnectField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* NotifyConnectPackage::GetDebugString() const
{
	int offset = 0;
	if (NotifyConnect != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "NotifyConnect:SessionID:[%lld], IPAddress:[%s], Port:[%d]", NotifyConnect->SessionID, NotifyConnect->IPAddress, NotifyConnect->Port);
	}
	return t_DataStringBuffer;
}
 
NotifyDisConnectPackage::NotifyDisConnectPackage()
	:NotifyDisConnect(nullptr)
{
}
NotifyDisConnectPackage::~NotifyDisConnectPackage()
{
	if (NotifyDisConnect != nullptr)
	{
		ObjectPool<NotifyDisConnectField>::GetInstance().Deallocate(NotifyDisConnect);
		NotifyDisConnect = nullptr;
	}
}
NotifyDisConnectPackage* NotifyDisConnectPackage::Allocate()
{
	return ObjectPool<NotifyDisConnectPackage>::GetInstance().Allocate();
}
void NotifyDisConnectPackage::Deallocate()
{
	ObjectPool<NotifyDisConnectPackage>::GetInstance().Deallocate(this);
}
void NotifyDisConnectPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int NotifyDisConnectPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (NotifyDisConnect != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, NotifyDisConnectField::FieldID);
		WriteString(ppos, Items::SessionID, NotifyDisConnect->SessionID);
		if (strlen(NotifyDisConnect->IPAddress) >= sizeof(NotifyDisConnect->IPAddress))
		{
			NotifyDisConnect->IPAddress[sizeof(NotifyDisConnect->IPAddress) - 1] = 0;
		}
		WriteString(ppos, Items::IPAddress, NotifyDisConnect->IPAddress);
		WriteString(ppos, Items::Port, NotifyDisConnect->Port);
		WriteHexString(ppos, Items::FieldEnd, NotifyDisConnectField::FieldID);
	}
	return int(ppos - buff);
}
bool NotifyDisConnectPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case NotifyDisConnectField::FieldID:
			{
				NotifyDisConnect = ObjectPool<NotifyDisConnectField>::GetInstance().Allocate();
				memset(NotifyDisConnect, 0, sizeof(*NotifyDisConnect));
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
						case Items::SessionID:
						{
							NotifyDisConnect->SessionID = atoll(value.c_str());
							break;
						}
						case Items::IPAddress:
						{
							size_t len = value.length() >= sizeof(NotifyDisConnect->IPAddress) ? sizeof(NotifyDisConnect->IPAddress) - 1 : value.length();
							memcpy(NotifyDisConnect->IPAddress, value.c_str(), len);
							break;
						}
						case Items::Port:
						{
							NotifyDisConnect->Port = atoi(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for NotifyDisConnectField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For NotifyDisConnectPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For NotifyDisConnectPackage");
			return false;
		}
	}
	return true;
}
int NotifyDisConnectPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (NotifyDisConnect != nullptr)
	{
		memcpy(buff + offset, &NotifyDisConnectField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, NotifyDisConnect, sizeof(NotifyDisConnectField));
		offset += sizeof(NotifyDisConnectField);
	}
	return offset;
}
bool NotifyDisConnectPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case NotifyDisConnectField::FieldID:
		{
			NotifyDisConnect = ObjectPool<NotifyDisConnectField>::GetInstance().Allocate();
			memcpy(NotifyDisConnect, buff + offset, sizeof(NotifyDisConnectField));
			offset += sizeof(NotifyDisConnectField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* NotifyDisConnectPackage::GetDebugString() const
{
	int offset = 0;
	if (NotifyDisConnect != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "NotifyDisConnect:SessionID:[%lld], IPAddress:[%s], Port:[%d]", NotifyDisConnect->SessionID, NotifyDisConnect->IPAddress, NotifyDisConnect->Port);
	}
	return t_DataStringBuffer;
}
 
NotifyDBConnectPackage::NotifyDBConnectPackage()
	:NotifyDBConnect(nullptr)
{
}
NotifyDBConnectPackage::~NotifyDBConnectPackage()
{
	if (NotifyDBConnect != nullptr)
	{
		ObjectPool<NotifyDBConnectField>::GetInstance().Deallocate(NotifyDBConnect);
		NotifyDBConnect = nullptr;
	}
}
NotifyDBConnectPackage* NotifyDBConnectPackage::Allocate()
{
	return ObjectPool<NotifyDBConnectPackage>::GetInstance().Allocate();
}
void NotifyDBConnectPackage::Deallocate()
{
	ObjectPool<NotifyDBConnectPackage>::GetInstance().Deallocate(this);
}
void NotifyDBConnectPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int NotifyDBConnectPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (NotifyDBConnect != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, NotifyDBConnectField::FieldID);
		if (strlen(NotifyDBConnect->DBName) >= sizeof(NotifyDBConnect->DBName))
		{
			NotifyDBConnect->DBName[sizeof(NotifyDBConnect->DBName) - 1] = 0;
		}
		WriteString(ppos, Items::DBName, NotifyDBConnect->DBName);
		WriteHexString(ppos, Items::FieldEnd, NotifyDBConnectField::FieldID);
	}
	return int(ppos - buff);
}
bool NotifyDBConnectPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case NotifyDBConnectField::FieldID:
			{
				NotifyDBConnect = ObjectPool<NotifyDBConnectField>::GetInstance().Allocate();
				memset(NotifyDBConnect, 0, sizeof(*NotifyDBConnect));
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
						case Items::DBName:
						{
							size_t len = value.length() >= sizeof(NotifyDBConnect->DBName) ? sizeof(NotifyDBConnect->DBName) - 1 : value.length();
							memcpy(NotifyDBConnect->DBName, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for NotifyDBConnectField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For NotifyDBConnectPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For NotifyDBConnectPackage");
			return false;
		}
	}
	return true;
}
int NotifyDBConnectPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (NotifyDBConnect != nullptr)
	{
		memcpy(buff + offset, &NotifyDBConnectField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, NotifyDBConnect, sizeof(NotifyDBConnectField));
		offset += sizeof(NotifyDBConnectField);
	}
	return offset;
}
bool NotifyDBConnectPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case NotifyDBConnectField::FieldID:
		{
			NotifyDBConnect = ObjectPool<NotifyDBConnectField>::GetInstance().Allocate();
			memcpy(NotifyDBConnect, buff + offset, sizeof(NotifyDBConnectField));
			offset += sizeof(NotifyDBConnectField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* NotifyDBConnectPackage::GetDebugString() const
{
	int offset = 0;
	if (NotifyDBConnect != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "NotifyDBConnect:DBName:[%s]", NotifyDBConnect->DBName);
	}
	return t_DataStringBuffer;
}
 
NotifyDBDisConnectPackage::NotifyDBDisConnectPackage()
	:NotifyDBDisConnect(nullptr)
{
}
NotifyDBDisConnectPackage::~NotifyDBDisConnectPackage()
{
	if (NotifyDBDisConnect != nullptr)
	{
		ObjectPool<NotifyDBDisConnectField>::GetInstance().Deallocate(NotifyDBDisConnect);
		NotifyDBDisConnect = nullptr;
	}
}
NotifyDBDisConnectPackage* NotifyDBDisConnectPackage::Allocate()
{
	return ObjectPool<NotifyDBDisConnectPackage>::GetInstance().Allocate();
}
void NotifyDBDisConnectPackage::Deallocate()
{
	ObjectPool<NotifyDBDisConnectPackage>::GetInstance().Deallocate(this);
}
void NotifyDBDisConnectPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int NotifyDBDisConnectPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (NotifyDBDisConnect != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, NotifyDBDisConnectField::FieldID);
		if (strlen(NotifyDBDisConnect->DBName) >= sizeof(NotifyDBDisConnect->DBName))
		{
			NotifyDBDisConnect->DBName[sizeof(NotifyDBDisConnect->DBName) - 1] = 0;
		}
		WriteString(ppos, Items::DBName, NotifyDBDisConnect->DBName);
		WriteHexString(ppos, Items::FieldEnd, NotifyDBDisConnectField::FieldID);
	}
	return int(ppos - buff);
}
bool NotifyDBDisConnectPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case NotifyDBDisConnectField::FieldID:
			{
				NotifyDBDisConnect = ObjectPool<NotifyDBDisConnectField>::GetInstance().Allocate();
				memset(NotifyDBDisConnect, 0, sizeof(*NotifyDBDisConnect));
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
						case Items::DBName:
						{
							size_t len = value.length() >= sizeof(NotifyDBDisConnect->DBName) ? sizeof(NotifyDBDisConnect->DBName) - 1 : value.length();
							memcpy(NotifyDBDisConnect->DBName, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for NotifyDBDisConnectField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For NotifyDBDisConnectPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For NotifyDBDisConnectPackage");
			return false;
		}
	}
	return true;
}
int NotifyDBDisConnectPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (NotifyDBDisConnect != nullptr)
	{
		memcpy(buff + offset, &NotifyDBDisConnectField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, NotifyDBDisConnect, sizeof(NotifyDBDisConnectField));
		offset += sizeof(NotifyDBDisConnectField);
	}
	return offset;
}
bool NotifyDBDisConnectPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case NotifyDBDisConnectField::FieldID:
		{
			NotifyDBDisConnect = ObjectPool<NotifyDBDisConnectField>::GetInstance().Allocate();
			memcpy(NotifyDBDisConnect, buff + offset, sizeof(NotifyDBDisConnectField));
			offset += sizeof(NotifyDBDisConnectField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* NotifyDBDisConnectPackage::GetDebugString() const
{
	int offset = 0;
	if (NotifyDBDisConnect != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "NotifyDBDisConnect:DBName:[%s]", NotifyDBDisConnect->DBName);
	}
	return t_DataStringBuffer;
}
 
ReqMdUserLoginPackage::ReqMdUserLoginPackage()
	:ReqMdUserLogin(nullptr)
{
}
ReqMdUserLoginPackage::~ReqMdUserLoginPackage()
{
	if (ReqMdUserLogin != nullptr)
	{
		ObjectPool<ReqMdUserLoginField>::GetInstance().Deallocate(ReqMdUserLogin);
		ReqMdUserLogin = nullptr;
	}
}
ReqMdUserLoginPackage* ReqMdUserLoginPackage::Allocate()
{
	return ObjectPool<ReqMdUserLoginPackage>::GetInstance().Allocate();
}
void ReqMdUserLoginPackage::Deallocate()
{
	ObjectPool<ReqMdUserLoginPackage>::GetInstance().Deallocate(this);
}
void ReqMdUserLoginPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				ReqMdUserLogin = ObjectPool<ReqMdUserLoginField>::GetInstance().Allocate();
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
	if (ReqMdUserLogin != nullptr)
	{
		memcpy(buff + offset, &ReqMdUserLoginField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqMdUserLogin, sizeof(ReqMdUserLoginField));
		offset += sizeof(ReqMdUserLoginField);
	}
	return offset;
}
bool ReqMdUserLoginPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqMdUserLoginField::FieldID:
		{
			ReqMdUserLogin = ObjectPool<ReqMdUserLoginField>::GetInstance().Allocate();
			memcpy(ReqMdUserLogin, buff + offset, sizeof(ReqMdUserLoginField));
			offset += sizeof(ReqMdUserLoginField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqMdUserLoginPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqMdUserLogin != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqMdUserLogin:UserID:[%s], Password:[%s]", ReqMdUserLogin->UserID, ReqMdUserLogin->Password);
	}
	return t_DataStringBuffer;
}
 
RspMdUserLoginPackage::RspMdUserLoginPackage()
	:RspMdUserLogin(nullptr), RspInfo(nullptr)
{
}
RspMdUserLoginPackage::~RspMdUserLoginPackage()
{
	if (RspMdUserLogin != nullptr)
	{
		ObjectPool<RspMdUserLoginField>::GetInstance().Deallocate(RspMdUserLogin);
		RspMdUserLogin = nullptr;
	}
	if (RspInfo != nullptr)
	{
		ObjectPool<RspInfoField>::GetInstance().Deallocate(RspInfo);
		RspInfo = nullptr;
	}
}
RspMdUserLoginPackage* RspMdUserLoginPackage::Allocate()
{
	return ObjectPool<RspMdUserLoginPackage>::GetInstance().Allocate();
}
void RspMdUserLoginPackage::Deallocate()
{
	ObjectPool<RspMdUserLoginPackage>::GetInstance().Deallocate(this);
}
void RspMdUserLoginPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				RspMdUserLogin = ObjectPool<RspMdUserLoginField>::GetInstance().Allocate();
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
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
	if (RspMdUserLogin != nullptr)
	{
		memcpy(buff + offset, &RspMdUserLoginField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, RspMdUserLogin, sizeof(RspMdUserLoginField));
		offset += sizeof(RspMdUserLoginField);
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
bool RspMdUserLoginPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case RspMdUserLoginField::FieldID:
		{
			RspMdUserLogin = ObjectPool<RspMdUserLoginField>::GetInstance().Allocate();
			memcpy(RspMdUserLogin, buff + offset, sizeof(RspMdUserLoginField));
			offset += sizeof(RspMdUserLoginField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
const char* RspMdUserLoginPackage::GetDebugString() const
{
	int offset = 0;
	if (RspMdUserLogin != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspMdUserLogin:UserID:[%s], LoginDate:[%s], LoginTime:[%s], SessionID:[%lld]", RspMdUserLogin->UserID, RspMdUserLogin->LoginDate, RspMdUserLogin->LoginTime, RspMdUserLogin->SessionID);
	}
	if (RspInfo != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
	return t_DataStringBuffer;
}
 
ReqMdUserLogoutPackage::ReqMdUserLogoutPackage()
	:ReqMdUserLogout(nullptr)
{
}
ReqMdUserLogoutPackage::~ReqMdUserLogoutPackage()
{
	if (ReqMdUserLogout != nullptr)
	{
		ObjectPool<ReqMdUserLogoutField>::GetInstance().Deallocate(ReqMdUserLogout);
		ReqMdUserLogout = nullptr;
	}
}
ReqMdUserLogoutPackage* ReqMdUserLogoutPackage::Allocate()
{
	return ObjectPool<ReqMdUserLogoutPackage>::GetInstance().Allocate();
}
void ReqMdUserLogoutPackage::Deallocate()
{
	ObjectPool<ReqMdUserLogoutPackage>::GetInstance().Deallocate(this);
}
void ReqMdUserLogoutPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				ReqMdUserLogout = ObjectPool<ReqMdUserLogoutField>::GetInstance().Allocate();
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
	if (ReqMdUserLogout != nullptr)
	{
		memcpy(buff + offset, &ReqMdUserLogoutField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqMdUserLogout, sizeof(ReqMdUserLogoutField));
		offset += sizeof(ReqMdUserLogoutField);
	}
	return offset;
}
bool ReqMdUserLogoutPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqMdUserLogoutField::FieldID:
		{
			ReqMdUserLogout = ObjectPool<ReqMdUserLogoutField>::GetInstance().Allocate();
			memcpy(ReqMdUserLogout, buff + offset, sizeof(ReqMdUserLogoutField));
			offset += sizeof(ReqMdUserLogoutField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqMdUserLogoutPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqMdUserLogout != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqMdUserLogout:UserID:[%s]", ReqMdUserLogout->UserID);
	}
	return t_DataStringBuffer;
}
 
RspMdUserLogoutPackage::RspMdUserLogoutPackage()
	:RspMdUserLogout(nullptr), RspInfo(nullptr)
{
}
RspMdUserLogoutPackage::~RspMdUserLogoutPackage()
{
	if (RspMdUserLogout != nullptr)
	{
		ObjectPool<RspMdUserLogoutField>::GetInstance().Deallocate(RspMdUserLogout);
		RspMdUserLogout = nullptr;
	}
	if (RspInfo != nullptr)
	{
		ObjectPool<RspInfoField>::GetInstance().Deallocate(RspInfo);
		RspInfo = nullptr;
	}
}
RspMdUserLogoutPackage* RspMdUserLogoutPackage::Allocate()
{
	return ObjectPool<RspMdUserLogoutPackage>::GetInstance().Allocate();
}
void RspMdUserLogoutPackage::Deallocate()
{
	ObjectPool<RspMdUserLogoutPackage>::GetInstance().Deallocate(this);
}
void RspMdUserLogoutPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				RspMdUserLogout = ObjectPool<RspMdUserLogoutField>::GetInstance().Allocate();
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
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
	if (RspMdUserLogout != nullptr)
	{
		memcpy(buff + offset, &RspMdUserLogoutField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, RspMdUserLogout, sizeof(RspMdUserLogoutField));
		offset += sizeof(RspMdUserLogoutField);
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
bool RspMdUserLogoutPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case RspMdUserLogoutField::FieldID:
		{
			RspMdUserLogout = ObjectPool<RspMdUserLogoutField>::GetInstance().Allocate();
			memcpy(RspMdUserLogout, buff + offset, sizeof(RspMdUserLogoutField));
			offset += sizeof(RspMdUserLogoutField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
const char* RspMdUserLogoutPackage::GetDebugString() const
{
	int offset = 0;
	if (RspMdUserLogout != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspMdUserLogout:UserID:[%s]", RspMdUserLogout->UserID);
	}
	if (RspInfo != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
	return t_DataStringBuffer;
}
 
ReqSubMarketDataPackage::ReqSubMarketDataPackage()
	:ReqSubMarketData(nullptr)
{
}
ReqSubMarketDataPackage::~ReqSubMarketDataPackage()
{
	if (ReqSubMarketData != nullptr)
	{
		ObjectPool<ReqSubMarketDataField>::GetInstance().Deallocate(ReqSubMarketData);
		ReqSubMarketData = nullptr;
	}
}
ReqSubMarketDataPackage* ReqSubMarketDataPackage::Allocate()
{
	return ObjectPool<ReqSubMarketDataPackage>::GetInstance().Allocate();
}
void ReqSubMarketDataPackage::Deallocate()
{
	ObjectPool<ReqSubMarketDataPackage>::GetInstance().Deallocate(this);
}
void ReqSubMarketDataPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				ReqSubMarketData = ObjectPool<ReqSubMarketDataField>::GetInstance().Allocate();
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
	if (ReqSubMarketData != nullptr)
	{
		memcpy(buff + offset, &ReqSubMarketDataField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqSubMarketData, sizeof(ReqSubMarketDataField));
		offset += sizeof(ReqSubMarketDataField);
	}
	return offset;
}
bool ReqSubMarketDataPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqSubMarketDataField::FieldID:
		{
			ReqSubMarketData = ObjectPool<ReqSubMarketDataField>::GetInstance().Allocate();
			memcpy(ReqSubMarketData, buff + offset, sizeof(ReqSubMarketDataField));
			offset += sizeof(ReqSubMarketDataField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqSubMarketDataPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqSubMarketData != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqSubMarketData:ExchangeID:[%s], InstrumentID:[%s]", ReqSubMarketData->ExchangeID, ReqSubMarketData->InstrumentID);
	}
	return t_DataStringBuffer;
}
 
RspSubMarketDataPackage::RspSubMarketDataPackage()
	:RspSubMarketData(nullptr), RspInfo(nullptr)
{
}
RspSubMarketDataPackage::~RspSubMarketDataPackage()
{
	if (RspSubMarketData != nullptr)
	{
		ObjectPool<RspSubMarketDataField>::GetInstance().Deallocate(RspSubMarketData);
		RspSubMarketData = nullptr;
	}
	if (RspInfo != nullptr)
	{
		ObjectPool<RspInfoField>::GetInstance().Deallocate(RspInfo);
		RspInfo = nullptr;
	}
}
RspSubMarketDataPackage* RspSubMarketDataPackage::Allocate()
{
	return ObjectPool<RspSubMarketDataPackage>::GetInstance().Allocate();
}
void RspSubMarketDataPackage::Deallocate()
{
	ObjectPool<RspSubMarketDataPackage>::GetInstance().Deallocate(this);
}
void RspSubMarketDataPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				RspSubMarketData = ObjectPool<RspSubMarketDataField>::GetInstance().Allocate();
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
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
	if (RspSubMarketData != nullptr)
	{
		memcpy(buff + offset, &RspSubMarketDataField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, RspSubMarketData, sizeof(RspSubMarketDataField));
		offset += sizeof(RspSubMarketDataField);
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
bool RspSubMarketDataPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case RspSubMarketDataField::FieldID:
		{
			RspSubMarketData = ObjectPool<RspSubMarketDataField>::GetInstance().Allocate();
			memcpy(RspSubMarketData, buff + offset, sizeof(RspSubMarketDataField));
			offset += sizeof(RspSubMarketDataField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
const char* RspSubMarketDataPackage::GetDebugString() const
{
	int offset = 0;
	if (RspSubMarketData != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspSubMarketData:ExchangeID:[%s], InstrumentID:[%s]", RspSubMarketData->ExchangeID, RspSubMarketData->InstrumentID);
	}
	if (RspInfo != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
	return t_DataStringBuffer;
}
 
ReqUnSubMarketDataPackage::ReqUnSubMarketDataPackage()
	:ReqUnSubMarketData(nullptr)
{
}
ReqUnSubMarketDataPackage::~ReqUnSubMarketDataPackage()
{
	if (ReqUnSubMarketData != nullptr)
	{
		ObjectPool<ReqUnSubMarketDataField>::GetInstance().Deallocate(ReqUnSubMarketData);
		ReqUnSubMarketData = nullptr;
	}
}
ReqUnSubMarketDataPackage* ReqUnSubMarketDataPackage::Allocate()
{
	return ObjectPool<ReqUnSubMarketDataPackage>::GetInstance().Allocate();
}
void ReqUnSubMarketDataPackage::Deallocate()
{
	ObjectPool<ReqUnSubMarketDataPackage>::GetInstance().Deallocate(this);
}
void ReqUnSubMarketDataPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				ReqUnSubMarketData = ObjectPool<ReqUnSubMarketDataField>::GetInstance().Allocate();
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
	if (ReqUnSubMarketData != nullptr)
	{
		memcpy(buff + offset, &ReqUnSubMarketDataField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqUnSubMarketData, sizeof(ReqUnSubMarketDataField));
		offset += sizeof(ReqUnSubMarketDataField);
	}
	return offset;
}
bool ReqUnSubMarketDataPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqUnSubMarketDataField::FieldID:
		{
			ReqUnSubMarketData = ObjectPool<ReqUnSubMarketDataField>::GetInstance().Allocate();
			memcpy(ReqUnSubMarketData, buff + offset, sizeof(ReqUnSubMarketDataField));
			offset += sizeof(ReqUnSubMarketDataField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqUnSubMarketDataPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqUnSubMarketData != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqUnSubMarketData:ExchangeID:[%s], InstrumentID:[%s]", ReqUnSubMarketData->ExchangeID, ReqUnSubMarketData->InstrumentID);
	}
	return t_DataStringBuffer;
}
 
RspUnSubMarketDataPackage::RspUnSubMarketDataPackage()
	:RspUnSubMarketData(nullptr), RspInfo(nullptr)
{
}
RspUnSubMarketDataPackage::~RspUnSubMarketDataPackage()
{
	if (RspUnSubMarketData != nullptr)
	{
		ObjectPool<RspUnSubMarketDataField>::GetInstance().Deallocate(RspUnSubMarketData);
		RspUnSubMarketData = nullptr;
	}
	if (RspInfo != nullptr)
	{
		ObjectPool<RspInfoField>::GetInstance().Deallocate(RspInfo);
		RspInfo = nullptr;
	}
}
RspUnSubMarketDataPackage* RspUnSubMarketDataPackage::Allocate()
{
	return ObjectPool<RspUnSubMarketDataPackage>::GetInstance().Allocate();
}
void RspUnSubMarketDataPackage::Deallocate()
{
	ObjectPool<RspUnSubMarketDataPackage>::GetInstance().Deallocate(this);
}
void RspUnSubMarketDataPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				RspUnSubMarketData = ObjectPool<RspUnSubMarketDataField>::GetInstance().Allocate();
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
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
	if (RspUnSubMarketData != nullptr)
	{
		memcpy(buff + offset, &RspUnSubMarketDataField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, RspUnSubMarketData, sizeof(RspUnSubMarketDataField));
		offset += sizeof(RspUnSubMarketDataField);
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
bool RspUnSubMarketDataPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case RspUnSubMarketDataField::FieldID:
		{
			RspUnSubMarketData = ObjectPool<RspUnSubMarketDataField>::GetInstance().Allocate();
			memcpy(RspUnSubMarketData, buff + offset, sizeof(RspUnSubMarketDataField));
			offset += sizeof(RspUnSubMarketDataField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
const char* RspUnSubMarketDataPackage::GetDebugString() const
{
	int offset = 0;
	if (RspUnSubMarketData != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspUnSubMarketData:ExchangeID:[%s], InstrumentID:[%s]", RspUnSubMarketData->ExchangeID, RspUnSubMarketData->InstrumentID);
	}
	if (RspInfo != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
	return t_DataStringBuffer;
}
 
ReqSubMarketDataFinishedPackage::ReqSubMarketDataFinishedPackage()
	:ReqSubMarketDataFinished(nullptr)
{
}
ReqSubMarketDataFinishedPackage::~ReqSubMarketDataFinishedPackage()
{
	if (ReqSubMarketDataFinished != nullptr)
	{
		ObjectPool<ReqSubMarketDataFinishedField>::GetInstance().Deallocate(ReqSubMarketDataFinished);
		ReqSubMarketDataFinished = nullptr;
	}
}
ReqSubMarketDataFinishedPackage* ReqSubMarketDataFinishedPackage::Allocate()
{
	return ObjectPool<ReqSubMarketDataFinishedPackage>::GetInstance().Allocate();
}
void ReqSubMarketDataFinishedPackage::Deallocate()
{
	ObjectPool<ReqSubMarketDataFinishedPackage>::GetInstance().Deallocate(this);
}
void ReqSubMarketDataFinishedPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqSubMarketDataFinishedPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqSubMarketDataFinished != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqSubMarketDataFinishedField::FieldID);
		WriteString(ppos, Items::SessionID, ReqSubMarketDataFinished->SessionID);
		WriteHexString(ppos, Items::FieldEnd, ReqSubMarketDataFinishedField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqSubMarketDataFinishedPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqSubMarketDataFinishedField::FieldID:
			{
				ReqSubMarketDataFinished = ObjectPool<ReqSubMarketDataFinishedField>::GetInstance().Allocate();
				memset(ReqSubMarketDataFinished, 0, sizeof(*ReqSubMarketDataFinished));
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
						case Items::SessionID:
						{
							ReqSubMarketDataFinished->SessionID = atoll(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqSubMarketDataFinishedField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqSubMarketDataFinishedPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqSubMarketDataFinishedPackage");
			return false;
		}
	}
	return true;
}
int ReqSubMarketDataFinishedPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqSubMarketDataFinished != nullptr)
	{
		memcpy(buff + offset, &ReqSubMarketDataFinishedField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqSubMarketDataFinished, sizeof(ReqSubMarketDataFinishedField));
		offset += sizeof(ReqSubMarketDataFinishedField);
	}
	return offset;
}
bool ReqSubMarketDataFinishedPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqSubMarketDataFinishedField::FieldID:
		{
			ReqSubMarketDataFinished = ObjectPool<ReqSubMarketDataFinishedField>::GetInstance().Allocate();
			memcpy(ReqSubMarketDataFinished, buff + offset, sizeof(ReqSubMarketDataFinishedField));
			offset += sizeof(ReqSubMarketDataFinishedField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqSubMarketDataFinishedPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqSubMarketDataFinished != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqSubMarketDataFinished:SessionID:[%lld]", ReqSubMarketDataFinished->SessionID);
	}
	return t_DataStringBuffer;
}
 
RtnDepthMarketDataPackage::RtnDepthMarketDataPackage()
	:DepthMarketData(nullptr)
{
}
RtnDepthMarketDataPackage::~RtnDepthMarketDataPackage()
{
	if (DepthMarketData != nullptr)
	{
		ObjectPool<DepthMarketDataField>::GetInstance().Deallocate(DepthMarketData);
		DepthMarketData = nullptr;
	}
}
RtnDepthMarketDataPackage* RtnDepthMarketDataPackage::Allocate()
{
	return ObjectPool<RtnDepthMarketDataPackage>::GetInstance().Allocate();
}
void RtnDepthMarketDataPackage::Deallocate()
{
	ObjectPool<RtnDepthMarketDataPackage>::GetInstance().Deallocate(this);
}
void RtnDepthMarketDataPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
		WriteString(ppos, Items::UpdateTs, DepthMarketData->UpdateTs);
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
				DepthMarketData = ObjectPool<DepthMarketDataField>::GetInstance().Allocate();
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
						case Items::UpdateTs:
						{
							DepthMarketData->UpdateTs = atoll(value.c_str());
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
							DepthMarketData->PreOpenInterest = atof(value.c_str());
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
							DepthMarketData->OpenInterest = atof(value.c_str());
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
	if (DepthMarketData != nullptr)
	{
		memcpy(buff + offset, &DepthMarketDataField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, DepthMarketData, sizeof(DepthMarketDataField));
		offset += sizeof(DepthMarketDataField);
	}
	return offset;
}
bool RtnDepthMarketDataPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case DepthMarketDataField::FieldID:
		{
			DepthMarketData = ObjectPool<DepthMarketDataField>::GetInstance().Allocate();
			memcpy(DepthMarketData, buff + offset, sizeof(DepthMarketDataField));
			offset += sizeof(DepthMarketDataField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* RtnDepthMarketDataPackage::GetDebugString() const
{
	int offset = 0;
	if (DepthMarketData != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "DepthMarketData:TradingDay:[%s], ExchangeID:[%s], InstrumentID:[%s], UpdateTs:[%lld], LastPrice:[%f], PreSettlementPrice:[%f], PreClosePrice:[%f], PreOpenInterest:[%f], OpenPrice:[%f], HighestPrice:[%f], LowestPrice:[%f], ClosePrice:[%f], CurrVolume:[%lld], Volume:[%lld], CurrTurnover:[%f], Turnover:[%f], OpenInterest:[%f], SettlementPrice:[%f], UpperLimitPrice:[%f], LowerLimitPrice:[%f], AveragePrice:[%f], AskPrice1:[%f], AskPrice2:[%f], AskPrice3:[%f], AskPrice4:[%f], AskPrice5:[%f], AskPrice6:[%f], AskPrice7:[%f], AskPrice8:[%f], AskPrice9:[%f], AskPrice10:[%f], AskVolume1:[%lld], AskVolume2:[%lld], AskVolume3:[%lld], AskVolume4:[%lld], AskVolume5:[%lld], AskVolume6:[%lld], AskVolume7:[%lld], AskVolume8:[%lld], AskVolume9:[%lld], AskVolume10:[%lld], BidPrice1:[%f], BidPrice2:[%f], BidPrice3:[%f], BidPrice4:[%f], BidPrice5:[%f], BidPrice6:[%f], BidPrice7:[%f], BidPrice8:[%f], BidPrice9:[%f], BidPrice10:[%f], BidVolume1:[%lld], BidVolume2:[%lld], BidVolume3:[%lld], BidVolume4:[%lld], BidVolume5:[%lld], BidVolume6:[%lld], BidVolume7:[%lld], BidVolume8:[%lld], BidVolume9:[%lld], BidVolume10:[%lld]", DepthMarketData->TradingDay, DepthMarketData->ExchangeID, DepthMarketData->InstrumentID, DepthMarketData->UpdateTs, DepthMarketData->LastPrice, DepthMarketData->PreSettlementPrice, DepthMarketData->PreClosePrice, DepthMarketData->PreOpenInterest, DepthMarketData->OpenPrice, DepthMarketData->HighestPrice, DepthMarketData->LowestPrice, DepthMarketData->ClosePrice, DepthMarketData->CurrVolume, DepthMarketData->Volume, DepthMarketData->CurrTurnover, DepthMarketData->Turnover, DepthMarketData->OpenInterest, DepthMarketData->SettlementPrice, DepthMarketData->UpperLimitPrice, DepthMarketData->LowerLimitPrice, DepthMarketData->AveragePrice, DepthMarketData->AskPrice1, DepthMarketData->AskPrice2, DepthMarketData->AskPrice3, DepthMarketData->AskPrice4, DepthMarketData->AskPrice5, DepthMarketData->AskPrice6, DepthMarketData->AskPrice7, DepthMarketData->AskPrice8, DepthMarketData->AskPrice9, DepthMarketData->AskPrice10, DepthMarketData->AskVolume1, DepthMarketData->AskVolume2, DepthMarketData->AskVolume3, DepthMarketData->AskVolume4, DepthMarketData->AskVolume5, DepthMarketData->AskVolume6, DepthMarketData->AskVolume7, DepthMarketData->AskVolume8, DepthMarketData->AskVolume9, DepthMarketData->AskVolume10, DepthMarketData->BidPrice1, DepthMarketData->BidPrice2, DepthMarketData->BidPrice3, DepthMarketData->BidPrice4, DepthMarketData->BidPrice5, DepthMarketData->BidPrice6, DepthMarketData->BidPrice7, DepthMarketData->BidPrice8, DepthMarketData->BidPrice9, DepthMarketData->BidPrice10, DepthMarketData->BidVolume1, DepthMarketData->BidVolume2, DepthMarketData->BidVolume3, DepthMarketData->BidVolume4, DepthMarketData->BidVolume5, DepthMarketData->BidVolume6, DepthMarketData->BidVolume7, DepthMarketData->BidVolume8, DepthMarketData->BidVolume9, DepthMarketData->BidVolume10);
	}
	return t_DataStringBuffer;
}
 
RtnBarMarketDataPackage::RtnBarMarketDataPackage()
	:BarMarketData(nullptr)
{
}
RtnBarMarketDataPackage::~RtnBarMarketDataPackage()
{
	if (BarMarketData != nullptr)
	{
		ObjectPool<BarMarketDataField>::GetInstance().Deallocate(BarMarketData);
		BarMarketData = nullptr;
	}
}
RtnBarMarketDataPackage* RtnBarMarketDataPackage::Allocate()
{
	return ObjectPool<RtnBarMarketDataPackage>::GetInstance().Allocate();
}
void RtnBarMarketDataPackage::Deallocate()
{
	ObjectPool<RtnBarMarketDataPackage>::GetInstance().Deallocate(this);
}
void RtnBarMarketDataPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
		WriteString(ppos, Items::PreSettlementPrice, BarMarketData->PreSettlementPrice);
		WriteString(ppos, Items::PreClosePrice, BarMarketData->PreClosePrice);
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
				BarMarketData = ObjectPool<BarMarketDataField>::GetInstance().Allocate();
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
						case Items::PreSettlementPrice:
						{
							BarMarketData->PreSettlementPrice = atof(value.c_str());
							break;
						}
						case Items::PreClosePrice:
						{
							BarMarketData->PreClosePrice = atof(value.c_str());
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
							BarMarketData->OpenInterest = atof(value.c_str());
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
	if (BarMarketData != nullptr)
	{
		memcpy(buff + offset, &BarMarketDataField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, BarMarketData, sizeof(BarMarketDataField));
		offset += sizeof(BarMarketDataField);
	}
	return offset;
}
bool RtnBarMarketDataPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case BarMarketDataField::FieldID:
		{
			BarMarketData = ObjectPool<BarMarketDataField>::GetInstance().Allocate();
			memcpy(BarMarketData, buff + offset, sizeof(BarMarketDataField));
			offset += sizeof(BarMarketDataField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* RtnBarMarketDataPackage::GetDebugString() const
{
	int offset = 0;
	if (BarMarketData != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "BarMarketData:TradingDay:[%s], ExchangeID:[%s], InstrumentID:[%s], BarPreces:[%d], BarPeriod:[%d], BarTime:[%lld], UpdateTs:[%lld], PreSettlementPrice:[%f], PreClosePrice:[%f], HighestPrice:[%f], LowestPrice:[%f], Open:[%f], High:[%f], Low:[%f], Close:[%f], CurrVolume:[%lld], Volume:[%lld], CurrTurnover:[%f], Turnover:[%f], OpenInterest:[%f]", BarMarketData->TradingDay, BarMarketData->ExchangeID, BarMarketData->InstrumentID, (int)BarMarketData->BarPreces, BarMarketData->BarPeriod, BarMarketData->BarTime, BarMarketData->UpdateTs, BarMarketData->PreSettlementPrice, BarMarketData->PreClosePrice, BarMarketData->HighestPrice, BarMarketData->LowestPrice, BarMarketData->Open, BarMarketData->High, BarMarketData->Low, BarMarketData->Close, BarMarketData->CurrVolume, BarMarketData->Volume, BarMarketData->CurrTurnover, BarMarketData->Turnover, BarMarketData->OpenInterest);
	}
	return t_DataStringBuffer;
}
 
RtnSessionBeginPackage::RtnSessionBeginPackage()
	:SessionBegin(nullptr)
{
}
RtnSessionBeginPackage::~RtnSessionBeginPackage()
{
	if (SessionBegin != nullptr)
	{
		ObjectPool<SessionBeginField>::GetInstance().Deallocate(SessionBegin);
		SessionBegin = nullptr;
	}
}
RtnSessionBeginPackage* RtnSessionBeginPackage::Allocate()
{
	return ObjectPool<RtnSessionBeginPackage>::GetInstance().Allocate();
}
void RtnSessionBeginPackage::Deallocate()
{
	ObjectPool<RtnSessionBeginPackage>::GetInstance().Deallocate(this);
}
void RtnSessionBeginPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RtnSessionBeginPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (SessionBegin != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, SessionBeginField::FieldID);
		if (strlen(SessionBegin->TradingDay) >= sizeof(SessionBegin->TradingDay))
		{
			SessionBegin->TradingDay[sizeof(SessionBegin->TradingDay) - 1] = 0;
		}
		WriteString(ppos, Items::TradingDay, SessionBegin->TradingDay);
		WriteHexString(ppos, Items::FieldEnd, SessionBeginField::FieldID);
	}
	return int(ppos - buff);
}
bool RtnSessionBeginPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case SessionBeginField::FieldID:
			{
				SessionBegin = ObjectPool<SessionBeginField>::GetInstance().Allocate();
				memset(SessionBegin, 0, sizeof(*SessionBegin));
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
							size_t len = value.length() >= sizeof(SessionBegin->TradingDay) ? sizeof(SessionBegin->TradingDay) - 1 : value.length();
							memcpy(SessionBegin->TradingDay, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for SessionBeginField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RtnSessionBeginPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RtnSessionBeginPackage");
			return false;
		}
	}
	return true;
}
int RtnSessionBeginPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (SessionBegin != nullptr)
	{
		memcpy(buff + offset, &SessionBeginField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, SessionBegin, sizeof(SessionBeginField));
		offset += sizeof(SessionBeginField);
	}
	return offset;
}
bool RtnSessionBeginPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case SessionBeginField::FieldID:
		{
			SessionBegin = ObjectPool<SessionBeginField>::GetInstance().Allocate();
			memcpy(SessionBegin, buff + offset, sizeof(SessionBeginField));
			offset += sizeof(SessionBeginField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* RtnSessionBeginPackage::GetDebugString() const
{
	int offset = 0;
	if (SessionBegin != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "SessionBegin:TradingDay:[%s]", SessionBegin->TradingDay);
	}
	return t_DataStringBuffer;
}
 
RtnSessionEndPackage::RtnSessionEndPackage()
	:SessionEnd(nullptr)
{
}
RtnSessionEndPackage::~RtnSessionEndPackage()
{
	if (SessionEnd != nullptr)
	{
		ObjectPool<SessionEndField>::GetInstance().Deallocate(SessionEnd);
		SessionEnd = nullptr;
	}
}
RtnSessionEndPackage* RtnSessionEndPackage::Allocate()
{
	return ObjectPool<RtnSessionEndPackage>::GetInstance().Allocate();
}
void RtnSessionEndPackage::Deallocate()
{
	ObjectPool<RtnSessionEndPackage>::GetInstance().Deallocate(this);
}
void RtnSessionEndPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RtnSessionEndPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (SessionEnd != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, SessionEndField::FieldID);
		if (strlen(SessionEnd->TradingDay) >= sizeof(SessionEnd->TradingDay))
		{
			SessionEnd->TradingDay[sizeof(SessionEnd->TradingDay) - 1] = 0;
		}
		WriteString(ppos, Items::TradingDay, SessionEnd->TradingDay);
		WriteHexString(ppos, Items::FieldEnd, SessionEndField::FieldID);
	}
	return int(ppos - buff);
}
bool RtnSessionEndPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case SessionEndField::FieldID:
			{
				SessionEnd = ObjectPool<SessionEndField>::GetInstance().Allocate();
				memset(SessionEnd, 0, sizeof(*SessionEnd));
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
							size_t len = value.length() >= sizeof(SessionEnd->TradingDay) ? sizeof(SessionEnd->TradingDay) - 1 : value.length();
							memcpy(SessionEnd->TradingDay, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for SessionEndField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RtnSessionEndPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RtnSessionEndPackage");
			return false;
		}
	}
	return true;
}
int RtnSessionEndPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (SessionEnd != nullptr)
	{
		memcpy(buff + offset, &SessionEndField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, SessionEnd, sizeof(SessionEndField));
		offset += sizeof(SessionEndField);
	}
	return offset;
}
bool RtnSessionEndPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case SessionEndField::FieldID:
		{
			SessionEnd = ObjectPool<SessionEndField>::GetInstance().Allocate();
			memcpy(SessionEnd, buff + offset, sizeof(SessionEndField));
			offset += sizeof(SessionEndField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* RtnSessionEndPackage::GetDebugString() const
{
	int offset = 0;
	if (SessionEnd != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "SessionEnd:TradingDay:[%s]", SessionEnd->TradingDay);
	}
	return t_DataStringBuffer;
}
 
RtnMarketDataEndPackage::RtnMarketDataEndPackage()
	:MarketDataEnd(nullptr)
{
}
RtnMarketDataEndPackage::~RtnMarketDataEndPackage()
{
	if (MarketDataEnd != nullptr)
	{
		ObjectPool<MarketDataEndField>::GetInstance().Deallocate(MarketDataEnd);
		MarketDataEnd = nullptr;
	}
}
RtnMarketDataEndPackage* RtnMarketDataEndPackage::Allocate()
{
	return ObjectPool<RtnMarketDataEndPackage>::GetInstance().Allocate();
}
void RtnMarketDataEndPackage::Deallocate()
{
	ObjectPool<RtnMarketDataEndPackage>::GetInstance().Deallocate(this);
}
void RtnMarketDataEndPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RtnMarketDataEndPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (MarketDataEnd != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, MarketDataEndField::FieldID);
		if (strlen(MarketDataEnd->TradingDay) >= sizeof(MarketDataEnd->TradingDay))
		{
			MarketDataEnd->TradingDay[sizeof(MarketDataEnd->TradingDay) - 1] = 0;
		}
		WriteString(ppos, Items::TradingDay, MarketDataEnd->TradingDay);
		WriteHexString(ppos, Items::FieldEnd, MarketDataEndField::FieldID);
	}
	return int(ppos - buff);
}
bool RtnMarketDataEndPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case MarketDataEndField::FieldID:
			{
				MarketDataEnd = ObjectPool<MarketDataEndField>::GetInstance().Allocate();
				memset(MarketDataEnd, 0, sizeof(*MarketDataEnd));
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
							size_t len = value.length() >= sizeof(MarketDataEnd->TradingDay) ? sizeof(MarketDataEnd->TradingDay) - 1 : value.length();
							memcpy(MarketDataEnd->TradingDay, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for MarketDataEndField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RtnMarketDataEndPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RtnMarketDataEndPackage");
			return false;
		}
	}
	return true;
}
int RtnMarketDataEndPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (MarketDataEnd != nullptr)
	{
		memcpy(buff + offset, &MarketDataEndField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, MarketDataEnd, sizeof(MarketDataEndField));
		offset += sizeof(MarketDataEndField);
	}
	return offset;
}
bool RtnMarketDataEndPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case MarketDataEndField::FieldID:
		{
			MarketDataEnd = ObjectPool<MarketDataEndField>::GetInstance().Allocate();
			memcpy(MarketDataEnd, buff + offset, sizeof(MarketDataEndField));
			offset += sizeof(MarketDataEndField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* RtnMarketDataEndPackage::GetDebugString() const
{
	int offset = 0;
	if (MarketDataEnd != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "MarketDataEnd:TradingDay:[%s]", MarketDataEnd->TradingDay);
	}
	return t_DataStringBuffer;
}
 
ReqAccountLoginPackage::ReqAccountLoginPackage()
	:ReqAccountLogin(nullptr)
{
}
ReqAccountLoginPackage::~ReqAccountLoginPackage()
{
	if (ReqAccountLogin != nullptr)
	{
		ObjectPool<ReqAccountLoginField>::GetInstance().Deallocate(ReqAccountLogin);
		ReqAccountLogin = nullptr;
	}
}
ReqAccountLoginPackage* ReqAccountLoginPackage::Allocate()
{
	return ObjectPool<ReqAccountLoginPackage>::GetInstance().Allocate();
}
void ReqAccountLoginPackage::Deallocate()
{
	ObjectPool<ReqAccountLoginPackage>::GetInstance().Deallocate(this);
}
void ReqAccountLoginPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				ReqAccountLogin = ObjectPool<ReqAccountLoginField>::GetInstance().Allocate();
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
			ReqAccountLogin = ObjectPool<ReqAccountLoginField>::GetInstance().Allocate();
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
 
RspAccountLoginPackage::RspAccountLoginPackage()
	:RspAccountLogin(nullptr), RspInfo(nullptr)
{
}
RspAccountLoginPackage::~RspAccountLoginPackage()
{
	if (RspAccountLogin != nullptr)
	{
		ObjectPool<RspAccountLoginField>::GetInstance().Deallocate(RspAccountLogin);
		RspAccountLogin = nullptr;
	}
	if (RspInfo != nullptr)
	{
		ObjectPool<RspInfoField>::GetInstance().Deallocate(RspInfo);
		RspInfo = nullptr;
	}
}
RspAccountLoginPackage* RspAccountLoginPackage::Allocate()
{
	return ObjectPool<RspAccountLoginPackage>::GetInstance().Allocate();
}
void RspAccountLoginPackage::Deallocate()
{
	ObjectPool<RspAccountLoginPackage>::GetInstance().Deallocate(this);
}
void RspAccountLoginPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				RspAccountLogin = ObjectPool<RspAccountLoginField>::GetInstance().Allocate();
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
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
			RspAccountLogin = ObjectPool<RspAccountLoginField>::GetInstance().Allocate();
			memcpy(RspAccountLogin, buff + offset, sizeof(RspAccountLoginField));
			offset += sizeof(RspAccountLoginField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
 
ReqAccountLogoutPackage::ReqAccountLogoutPackage()
	:ReqAccountLogout(nullptr)
{
}
ReqAccountLogoutPackage::~ReqAccountLogoutPackage()
{
	if (ReqAccountLogout != nullptr)
	{
		ObjectPool<ReqAccountLogoutField>::GetInstance().Deallocate(ReqAccountLogout);
		ReqAccountLogout = nullptr;
	}
}
ReqAccountLogoutPackage* ReqAccountLogoutPackage::Allocate()
{
	return ObjectPool<ReqAccountLogoutPackage>::GetInstance().Allocate();
}
void ReqAccountLogoutPackage::Deallocate()
{
	ObjectPool<ReqAccountLogoutPackage>::GetInstance().Deallocate(this);
}
void ReqAccountLogoutPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				ReqAccountLogout = ObjectPool<ReqAccountLogoutField>::GetInstance().Allocate();
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
			ReqAccountLogout = ObjectPool<ReqAccountLogoutField>::GetInstance().Allocate();
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
 
RspAccountLogoutPackage::RspAccountLogoutPackage()
	:RspAccountLogout(nullptr), RspInfo(nullptr)
{
}
RspAccountLogoutPackage::~RspAccountLogoutPackage()
{
	if (RspAccountLogout != nullptr)
	{
		ObjectPool<RspAccountLogoutField>::GetInstance().Deallocate(RspAccountLogout);
		RspAccountLogout = nullptr;
	}
	if (RspInfo != nullptr)
	{
		ObjectPool<RspInfoField>::GetInstance().Deallocate(RspInfo);
		RspInfo = nullptr;
	}
}
RspAccountLogoutPackage* RspAccountLogoutPackage::Allocate()
{
	return ObjectPool<RspAccountLogoutPackage>::GetInstance().Allocate();
}
void RspAccountLogoutPackage::Deallocate()
{
	ObjectPool<RspAccountLogoutPackage>::GetInstance().Deallocate(this);
}
void RspAccountLogoutPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				RspAccountLogout = ObjectPool<RspAccountLogoutField>::GetInstance().Allocate();
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
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
			RspAccountLogout = ObjectPool<RspAccountLogoutField>::GetInstance().Allocate();
			memcpy(RspAccountLogout, buff + offset, sizeof(RspAccountLogoutField));
			offset += sizeof(RspAccountLogoutField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
 
ReqQryAccountPackage::ReqQryAccountPackage()
	:ReqQryAccount(nullptr)
{
}
ReqQryAccountPackage::~ReqQryAccountPackage()
{
	if (ReqQryAccount != nullptr)
	{
		ObjectPool<ReqQryAccountField>::GetInstance().Deallocate(ReqQryAccount);
		ReqQryAccount = nullptr;
	}
}
ReqQryAccountPackage* ReqQryAccountPackage::Allocate()
{
	return ObjectPool<ReqQryAccountPackage>::GetInstance().Allocate();
}
void ReqQryAccountPackage::Deallocate()
{
	ObjectPool<ReqQryAccountPackage>::GetInstance().Deallocate(this);
}
void ReqQryAccountPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int ReqQryAccountPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (ReqQryAccount != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, ReqQryAccountField::FieldID);
		if (strlen(ReqQryAccount->AccountID) >= sizeof(ReqQryAccount->AccountID))
		{
			ReqQryAccount->AccountID[sizeof(ReqQryAccount->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, ReqQryAccount->AccountID);
		WriteHexString(ppos, Items::FieldEnd, ReqQryAccountField::FieldID);
	}
	return int(ppos - buff);
}
bool ReqQryAccountPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case ReqQryAccountField::FieldID:
			{
				ReqQryAccount = ObjectPool<ReqQryAccountField>::GetInstance().Allocate();
				memset(ReqQryAccount, 0, sizeof(*ReqQryAccount));
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
							size_t len = value.length() >= sizeof(ReqQryAccount->AccountID) ? sizeof(ReqQryAccount->AccountID) - 1 : value.length();
							memcpy(ReqQryAccount->AccountID, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for ReqQryAccountField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqQryAccountPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqQryAccountPackage");
			return false;
		}
	}
	return true;
}
int ReqQryAccountPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqQryAccount != nullptr)
	{
		memcpy(buff + offset, &ReqQryAccountField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, ReqQryAccount, sizeof(ReqQryAccountField));
		offset += sizeof(ReqQryAccountField);
	}
	return offset;
}
bool ReqQryAccountPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case ReqQryAccountField::FieldID:
		{
			ReqQryAccount = ObjectPool<ReqQryAccountField>::GetInstance().Allocate();
			memcpy(ReqQryAccount, buff + offset, sizeof(ReqQryAccountField));
			offset += sizeof(ReqQryAccountField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqQryAccountPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqQryAccount != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "ReqQryAccount:AccountID:[%s]", ReqQryAccount->AccountID);
	}
	return t_DataStringBuffer;
}
 
RspQryAccountPackage::RspQryAccountPackage()
	:Account(nullptr), RspInfo(nullptr)
{
}
RspQryAccountPackage::~RspQryAccountPackage()
{
	if (Account != nullptr)
	{
		ObjectPool<AccountField>::GetInstance().Deallocate(Account);
		Account = nullptr;
	}
	if (RspInfo != nullptr)
	{
		ObjectPool<RspInfoField>::GetInstance().Deallocate(RspInfo);
		RspInfo = nullptr;
	}
}
RspQryAccountPackage* RspQryAccountPackage::Allocate()
{
	return ObjectPool<RspQryAccountPackage>::GetInstance().Allocate();
}
void RspQryAccountPackage::Deallocate()
{
	ObjectPool<RspQryAccountPackage>::GetInstance().Deallocate(this);
}
void RspQryAccountPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionID, messageChain, msgSeqNum);
	Head.PackageID = PackageID;
}
int RspQryAccountPackage::ToStepStream(char* buff, int size) const
{
	char* ppos = buff;
	if (Account != nullptr)
	{
		WriteHexString(ppos, Items::FieldStart, AccountField::FieldID);
		if (strlen(Account->AccountID) >= sizeof(Account->AccountID))
		{
			Account->AccountID[sizeof(Account->AccountID) - 1] = 0;
		}
		WriteString(ppos, Items::AccountID, Account->AccountID);
		WriteString(ppos, Items::AccountType, (int)Account->AccountType);
		WriteString(ppos, Items::AccountStatus, (int)Account->AccountStatus);
		WriteString(ppos, Items::TradeGroupID, Account->TradeGroupID);
		WriteString(ppos, Items::RiskGroupID, Account->RiskGroupID);
		WriteString(ppos, Items::CommissionGroupID, Account->CommissionGroupID);
		WriteHexString(ppos, Items::FieldEnd, AccountField::FieldID);
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
bool RspQryAccountPackage::FromStepStream(char* buff, int startIndex, int endIndex)
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
			case AccountField::FieldID:
			{
				Account = ObjectPool<AccountField>::GetInstance().Allocate();
				memset(Account, 0, sizeof(*Account));
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
							size_t len = value.length() >= sizeof(Account->AccountID) ? sizeof(Account->AccountID) - 1 : value.length();
							memcpy(Account->AccountID, value.c_str(), len);
							break;
						}
						case Items::AccountType:
						{
							Account->AccountType = (AccountTypeType)(atoi(value.c_str()));
							break;
						}
						case Items::AccountStatus:
						{
							Account->AccountStatus = (AccountStatusType)(atoi(value.c_str()));
							break;
						}
						case Items::TradeGroupID:
						{
							Account->TradeGroupID = atoi(value.c_str());
							break;
						}
						case Items::RiskGroupID:
						{
							Account->RiskGroupID = atoi(value.c_str());
							break;
						}
						case Items::CommissionGroupID:
						{
							Account->CommissionGroupID = atoi(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemID:0x%X for AccountField FieldID:0x%X, Please Check ApiVersion.", itemID, fieldID);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryAccountPackage FieldID:0x%X", fieldID);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldID:
			{
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryAccountPackage FieldID:0x%X", fieldID);
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
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspQryAccountPackage");
			return false;
		}
	}
	return true;
}
int RspQryAccountPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (Account != nullptr)
	{
		memcpy(buff + offset, &AccountField::FieldID, sizeof(UShortType));
		offset += sizeof(UShortType);
		memcpy(buff + offset, Account, sizeof(AccountField));
		offset += sizeof(AccountField);
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
bool RspQryAccountPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		auto fieldID = *(UShortType*)(buff + offset);
		offset += sizeof(UShortType);
		switch (fieldID)
		{
		case AccountField::FieldID:
		{
			Account = ObjectPool<AccountField>::GetInstance().Allocate();
			memcpy(Account, buff + offset, sizeof(AccountField));
			offset += sizeof(AccountField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
const char* RspQryAccountPackage::GetDebugString() const
{
	int offset = 0;
	if (Account != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "Account:AccountID:[%s], AccountType:[%d], AccountStatus:[%d], TradeGroupID:[%d], RiskGroupID:[%d], CommissionGroupID:[%d]", Account->AccountID, (int)Account->AccountType, (int)Account->AccountStatus, Account->TradeGroupID, Account->RiskGroupID, Account->CommissionGroupID);
	}
	if (RspInfo != nullptr)
	{
		offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
	return t_DataStringBuffer;
}
 
ReqQryHolderAccountPackage::ReqQryHolderAccountPackage()
	:ReqQryHolderAccount(nullptr)
{
}
ReqQryHolderAccountPackage::~ReqQryHolderAccountPackage()
{
	if (ReqQryHolderAccount != nullptr)
	{
		ObjectPool<ReqQryHolderAccountField>::GetInstance().Deallocate(ReqQryHolderAccount);
		ReqQryHolderAccount = nullptr;
	}
}
ReqQryHolderAccountPackage* ReqQryHolderAccountPackage::Allocate()
{
	return ObjectPool<ReqQryHolderAccountPackage>::GetInstance().Allocate();
}
void ReqQryHolderAccountPackage::Deallocate()
{
	ObjectPool<ReqQryHolderAccountPackage>::GetInstance().Deallocate(this);
}
void ReqQryHolderAccountPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				ReqQryHolderAccount = ObjectPool<ReqQryHolderAccountField>::GetInstance().Allocate();
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
			ReqQryHolderAccount = ObjectPool<ReqQryHolderAccountField>::GetInstance().Allocate();
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
 
RspQryHolderAccountPackage::RspQryHolderAccountPackage()
	:HolderAccount(nullptr), RspInfo(nullptr)
{
}
RspQryHolderAccountPackage::~RspQryHolderAccountPackage()
{
	if (HolderAccount != nullptr)
	{
		ObjectPool<HolderAccountField>::GetInstance().Deallocate(HolderAccount);
		HolderAccount = nullptr;
	}
	if (RspInfo != nullptr)
	{
		ObjectPool<RspInfoField>::GetInstance().Deallocate(RspInfo);
		RspInfo = nullptr;
	}
}
RspQryHolderAccountPackage* RspQryHolderAccountPackage::Allocate()
{
	return ObjectPool<RspQryHolderAccountPackage>::GetInstance().Allocate();
}
void RspQryHolderAccountPackage::Deallocate()
{
	ObjectPool<RspQryHolderAccountPackage>::GetInstance().Deallocate(this);
}
void RspQryHolderAccountPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				HolderAccount = ObjectPool<HolderAccountField>::GetInstance().Allocate();
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
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
			HolderAccount = ObjectPool<HolderAccountField>::GetInstance().Allocate();
			memcpy(HolderAccount, buff + offset, sizeof(HolderAccountField));
			offset += sizeof(HolderAccountField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
 
ReqQryCapitalPackage::ReqQryCapitalPackage()
	:ReqQryCapital(nullptr)
{
}
ReqQryCapitalPackage::~ReqQryCapitalPackage()
{
	if (ReqQryCapital != nullptr)
	{
		ObjectPool<ReqQryCapitalField>::GetInstance().Deallocate(ReqQryCapital);
		ReqQryCapital = nullptr;
	}
}
ReqQryCapitalPackage* ReqQryCapitalPackage::Allocate()
{
	return ObjectPool<ReqQryCapitalPackage>::GetInstance().Allocate();
}
void ReqQryCapitalPackage::Deallocate()
{
	ObjectPool<ReqQryCapitalPackage>::GetInstance().Deallocate(this);
}
void ReqQryCapitalPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				ReqQryCapital = ObjectPool<ReqQryCapitalField>::GetInstance().Allocate();
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
			ReqQryCapital = ObjectPool<ReqQryCapitalField>::GetInstance().Allocate();
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
 
RspQryCapitalPackage::RspQryCapitalPackage()
	:Capital(nullptr), RspInfo(nullptr)
{
}
RspQryCapitalPackage::~RspQryCapitalPackage()
{
	if (Capital != nullptr)
	{
		ObjectPool<CapitalField>::GetInstance().Deallocate(Capital);
		Capital = nullptr;
	}
	if (RspInfo != nullptr)
	{
		ObjectPool<RspInfoField>::GetInstance().Deallocate(RspInfo);
		RspInfo = nullptr;
	}
}
RspQryCapitalPackage* RspQryCapitalPackage::Allocate()
{
	return ObjectPool<RspQryCapitalPackage>::GetInstance().Allocate();
}
void RspQryCapitalPackage::Deallocate()
{
	ObjectPool<RspQryCapitalPackage>::GetInstance().Deallocate(this);
}
void RspQryCapitalPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				Capital = ObjectPool<CapitalField>::GetInstance().Allocate();
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
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
			Capital = ObjectPool<CapitalField>::GetInstance().Allocate();
			memcpy(Capital, buff + offset, sizeof(CapitalField));
			offset += sizeof(CapitalField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
 
ReqQryPositionPackage::ReqQryPositionPackage()
	:ReqQryPosition(nullptr)
{
}
ReqQryPositionPackage::~ReqQryPositionPackage()
{
	if (ReqQryPosition != nullptr)
	{
		ObjectPool<ReqQryPositionField>::GetInstance().Deallocate(ReqQryPosition);
		ReqQryPosition = nullptr;
	}
}
ReqQryPositionPackage* ReqQryPositionPackage::Allocate()
{
	return ObjectPool<ReqQryPositionPackage>::GetInstance().Allocate();
}
void ReqQryPositionPackage::Deallocate()
{
	ObjectPool<ReqQryPositionPackage>::GetInstance().Deallocate(this);
}
void ReqQryPositionPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				ReqQryPosition = ObjectPool<ReqQryPositionField>::GetInstance().Allocate();
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
			ReqQryPosition = ObjectPool<ReqQryPositionField>::GetInstance().Allocate();
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
 
RspQryPositionPackage::RspQryPositionPackage()
	:Position(nullptr), RspInfo(nullptr)
{
}
RspQryPositionPackage::~RspQryPositionPackage()
{
	if (Position != nullptr)
	{
		ObjectPool<PositionField>::GetInstance().Deallocate(Position);
		Position = nullptr;
	}
	if (RspInfo != nullptr)
	{
		ObjectPool<RspInfoField>::GetInstance().Deallocate(RspInfo);
		RspInfo = nullptr;
	}
}
RspQryPositionPackage* RspQryPositionPackage::Allocate()
{
	return ObjectPool<RspQryPositionPackage>::GetInstance().Allocate();
}
void RspQryPositionPackage::Deallocate()
{
	ObjectPool<RspQryPositionPackage>::GetInstance().Deallocate(this);
}
void RspQryPositionPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				Position = ObjectPool<PositionField>::GetInstance().Allocate();
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
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
			Position = ObjectPool<PositionField>::GetInstance().Allocate();
			memcpy(Position, buff + offset, sizeof(PositionField));
			offset += sizeof(PositionField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
 
ReqQryOrderPackage::ReqQryOrderPackage()
	:ReqQryOrder(nullptr)
{
}
ReqQryOrderPackage::~ReqQryOrderPackage()
{
	if (ReqQryOrder != nullptr)
	{
		ObjectPool<ReqQryOrderField>::GetInstance().Deallocate(ReqQryOrder);
		ReqQryOrder = nullptr;
	}
}
ReqQryOrderPackage* ReqQryOrderPackage::Allocate()
{
	return ObjectPool<ReqQryOrderPackage>::GetInstance().Allocate();
}
void ReqQryOrderPackage::Deallocate()
{
	ObjectPool<ReqQryOrderPackage>::GetInstance().Deallocate(this);
}
void ReqQryOrderPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				ReqQryOrder = ObjectPool<ReqQryOrderField>::GetInstance().Allocate();
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
			ReqQryOrder = ObjectPool<ReqQryOrderField>::GetInstance().Allocate();
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
 
RspQryOrderPackage::RspQryOrderPackage()
	:Order(nullptr), RspInfo(nullptr)
{
}
RspQryOrderPackage::~RspQryOrderPackage()
{
	if (Order != nullptr)
	{
		ObjectPool<OrderField>::GetInstance().Deallocate(Order);
		Order = nullptr;
	}
	if (RspInfo != nullptr)
	{
		ObjectPool<RspInfoField>::GetInstance().Deallocate(RspInfo);
		RspInfo = nullptr;
	}
}
RspQryOrderPackage* RspQryOrderPackage::Allocate()
{
	return ObjectPool<RspQryOrderPackage>::GetInstance().Allocate();
}
void RspQryOrderPackage::Deallocate()
{
	ObjectPool<RspQryOrderPackage>::GetInstance().Deallocate(this);
}
void RspQryOrderPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				Order = ObjectPool<OrderField>::GetInstance().Allocate();
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
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
			Order = ObjectPool<OrderField>::GetInstance().Allocate();
			memcpy(Order, buff + offset, sizeof(OrderField));
			offset += sizeof(OrderField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
 
ReqQryTradePackage::ReqQryTradePackage()
	:ReqQryTrade(nullptr)
{
}
ReqQryTradePackage::~ReqQryTradePackage()
{
	if (ReqQryTrade != nullptr)
	{
		ObjectPool<ReqQryTradeField>::GetInstance().Deallocate(ReqQryTrade);
		ReqQryTrade = nullptr;
	}
}
ReqQryTradePackage* ReqQryTradePackage::Allocate()
{
	return ObjectPool<ReqQryTradePackage>::GetInstance().Allocate();
}
void ReqQryTradePackage::Deallocate()
{
	ObjectPool<ReqQryTradePackage>::GetInstance().Deallocate(this);
}
void ReqQryTradePackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				ReqQryTrade = ObjectPool<ReqQryTradeField>::GetInstance().Allocate();
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
			ReqQryTrade = ObjectPool<ReqQryTradeField>::GetInstance().Allocate();
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
 
RspQryTradePackage::RspQryTradePackage()
	:Trade(nullptr), RspInfo(nullptr)
{
}
RspQryTradePackage::~RspQryTradePackage()
{
	if (Trade != nullptr)
	{
		ObjectPool<TradeField>::GetInstance().Deallocate(Trade);
		Trade = nullptr;
	}
	if (RspInfo != nullptr)
	{
		ObjectPool<RspInfoField>::GetInstance().Deallocate(RspInfo);
		RspInfo = nullptr;
	}
}
RspQryTradePackage* RspQryTradePackage::Allocate()
{
	return ObjectPool<RspQryTradePackage>::GetInstance().Allocate();
}
void RspQryTradePackage::Deallocate()
{
	ObjectPool<RspQryTradePackage>::GetInstance().Deallocate(this);
}
void RspQryTradePackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				Trade = ObjectPool<TradeField>::GetInstance().Allocate();
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
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
			Trade = ObjectPool<TradeField>::GetInstance().Allocate();
			memcpy(Trade, buff + offset, sizeof(TradeField));
			offset += sizeof(TradeField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
 
ReqQryInstrumentPackage::ReqQryInstrumentPackage()
	:ReqQryInstrument(nullptr)
{
}
ReqQryInstrumentPackage::~ReqQryInstrumentPackage()
{
	if (ReqQryInstrument != nullptr)
	{
		ObjectPool<ReqQryInstrumentField>::GetInstance().Deallocate(ReqQryInstrument);
		ReqQryInstrument = nullptr;
	}
}
ReqQryInstrumentPackage* ReqQryInstrumentPackage::Allocate()
{
	return ObjectPool<ReqQryInstrumentPackage>::GetInstance().Allocate();
}
void ReqQryInstrumentPackage::Deallocate()
{
	ObjectPool<ReqQryInstrumentPackage>::GetInstance().Deallocate(this);
}
void ReqQryInstrumentPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				ReqQryInstrument = ObjectPool<ReqQryInstrumentField>::GetInstance().Allocate();
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
			ReqQryInstrument = ObjectPool<ReqQryInstrumentField>::GetInstance().Allocate();
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
 
RspQryInstrumentPackage::RspQryInstrumentPackage()
	:Instrument(nullptr), RspInfo(nullptr)
{
}
RspQryInstrumentPackage::~RspQryInstrumentPackage()
{
	if (Instrument != nullptr)
	{
		ObjectPool<InstrumentField>::GetInstance().Deallocate(Instrument);
		Instrument = nullptr;
	}
	if (RspInfo != nullptr)
	{
		ObjectPool<RspInfoField>::GetInstance().Deallocate(RspInfo);
		RspInfo = nullptr;
	}
}
RspQryInstrumentPackage* RspQryInstrumentPackage::Allocate()
{
	return ObjectPool<RspQryInstrumentPackage>::GetInstance().Allocate();
}
void RspQryInstrumentPackage::Deallocate()
{
	ObjectPool<RspQryInstrumentPackage>::GetInstance().Deallocate(this);
}
void RspQryInstrumentPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				Instrument = ObjectPool<InstrumentField>::GetInstance().Allocate();
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
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
			Instrument = ObjectPool<InstrumentField>::GetInstance().Allocate();
			memcpy(Instrument, buff + offset, sizeof(InstrumentField));
			offset += sizeof(InstrumentField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
 
ReqQryOptionInstrumentPackage::ReqQryOptionInstrumentPackage()
	:ReqQryOptionInstrument(nullptr)
{
}
ReqQryOptionInstrumentPackage::~ReqQryOptionInstrumentPackage()
{
	if (ReqQryOptionInstrument != nullptr)
	{
		ObjectPool<ReqQryOptionInstrumentField>::GetInstance().Deallocate(ReqQryOptionInstrument);
		ReqQryOptionInstrument = nullptr;
	}
}
ReqQryOptionInstrumentPackage* ReqQryOptionInstrumentPackage::Allocate()
{
	return ObjectPool<ReqQryOptionInstrumentPackage>::GetInstance().Allocate();
}
void ReqQryOptionInstrumentPackage::Deallocate()
{
	ObjectPool<ReqQryOptionInstrumentPackage>::GetInstance().Deallocate(this);
}
void ReqQryOptionInstrumentPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				ReqQryOptionInstrument = ObjectPool<ReqQryOptionInstrumentField>::GetInstance().Allocate();
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
			ReqQryOptionInstrument = ObjectPool<ReqQryOptionInstrumentField>::GetInstance().Allocate();
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
 
RspQryOptionInstrumentPackage::RspQryOptionInstrumentPackage()
	:OptionInstrument(nullptr), RspInfo(nullptr)
{
}
RspQryOptionInstrumentPackage::~RspQryOptionInstrumentPackage()
{
	if (OptionInstrument != nullptr)
	{
		ObjectPool<OptionInstrumentField>::GetInstance().Deallocate(OptionInstrument);
		OptionInstrument = nullptr;
	}
	if (RspInfo != nullptr)
	{
		ObjectPool<RspInfoField>::GetInstance().Deallocate(RspInfo);
		RspInfo = nullptr;
	}
}
RspQryOptionInstrumentPackage* RspQryOptionInstrumentPackage::Allocate()
{
	return ObjectPool<RspQryOptionInstrumentPackage>::GetInstance().Allocate();
}
void RspQryOptionInstrumentPackage::Deallocate()
{
	ObjectPool<RspQryOptionInstrumentPackage>::GetInstance().Deallocate(this);
}
void RspQryOptionInstrumentPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				OptionInstrument = ObjectPool<OptionInstrumentField>::GetInstance().Allocate();
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
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
			OptionInstrument = ObjectPool<OptionInstrumentField>::GetInstance().Allocate();
			memcpy(OptionInstrument, buff + offset, sizeof(OptionInstrumentField));
			offset += sizeof(OptionInstrumentField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
 
ReqQryCommissionRatePackage::ReqQryCommissionRatePackage()
	:ReqQryCommissionRate(nullptr)
{
}
ReqQryCommissionRatePackage::~ReqQryCommissionRatePackage()
{
	if (ReqQryCommissionRate != nullptr)
	{
		ObjectPool<ReqQryCommissionRateField>::GetInstance().Deallocate(ReqQryCommissionRate);
		ReqQryCommissionRate = nullptr;
	}
}
ReqQryCommissionRatePackage* ReqQryCommissionRatePackage::Allocate()
{
	return ObjectPool<ReqQryCommissionRatePackage>::GetInstance().Allocate();
}
void ReqQryCommissionRatePackage::Deallocate()
{
	ObjectPool<ReqQryCommissionRatePackage>::GetInstance().Deallocate(this);
}
void ReqQryCommissionRatePackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				ReqQryCommissionRate = ObjectPool<ReqQryCommissionRateField>::GetInstance().Allocate();
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
			ReqQryCommissionRate = ObjectPool<ReqQryCommissionRateField>::GetInstance().Allocate();
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
 
RspQryCommissionRatePackage::RspQryCommissionRatePackage()
	:CommissionRate(nullptr), RspInfo(nullptr)
{
}
RspQryCommissionRatePackage::~RspQryCommissionRatePackage()
{
	if (CommissionRate != nullptr)
	{
		ObjectPool<CommissionRateField>::GetInstance().Deallocate(CommissionRate);
		CommissionRate = nullptr;
	}
	if (RspInfo != nullptr)
	{
		ObjectPool<RspInfoField>::GetInstance().Deallocate(RspInfo);
		RspInfo = nullptr;
	}
}
RspQryCommissionRatePackage* RspQryCommissionRatePackage::Allocate()
{
	return ObjectPool<RspQryCommissionRatePackage>::GetInstance().Allocate();
}
void RspQryCommissionRatePackage::Deallocate()
{
	ObjectPool<RspQryCommissionRatePackage>::GetInstance().Deallocate(this);
}
void RspQryCommissionRatePackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				CommissionRate = ObjectPool<CommissionRateField>::GetInstance().Allocate();
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
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
			CommissionRate = ObjectPool<CommissionRateField>::GetInstance().Allocate();
			memcpy(CommissionRate, buff + offset, sizeof(CommissionRateField));
			offset += sizeof(CommissionRateField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
 
ReqQryMoneyTransferPackage::ReqQryMoneyTransferPackage()
	:ReqQryMoneyTransfer(nullptr)
{
}
ReqQryMoneyTransferPackage::~ReqQryMoneyTransferPackage()
{
	if (ReqQryMoneyTransfer != nullptr)
	{
		ObjectPool<ReqQryMoneyTransferField>::GetInstance().Deallocate(ReqQryMoneyTransfer);
		ReqQryMoneyTransfer = nullptr;
	}
}
ReqQryMoneyTransferPackage* ReqQryMoneyTransferPackage::Allocate()
{
	return ObjectPool<ReqQryMoneyTransferPackage>::GetInstance().Allocate();
}
void ReqQryMoneyTransferPackage::Deallocate()
{
	ObjectPool<ReqQryMoneyTransferPackage>::GetInstance().Deallocate(this);
}
void ReqQryMoneyTransferPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				ReqQryMoneyTransfer = ObjectPool<ReqQryMoneyTransferField>::GetInstance().Allocate();
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
			ReqQryMoneyTransfer = ObjectPool<ReqQryMoneyTransferField>::GetInstance().Allocate();
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
 
RspQryMoneyTransferPackage::RspQryMoneyTransferPackage()
	:MoneyTransfer(nullptr), RspInfo(nullptr)
{
}
RspQryMoneyTransferPackage::~RspQryMoneyTransferPackage()
{
	if (MoneyTransfer != nullptr)
	{
		ObjectPool<MoneyTransferField>::GetInstance().Deallocate(MoneyTransfer);
		MoneyTransfer = nullptr;
	}
	if (RspInfo != nullptr)
	{
		ObjectPool<RspInfoField>::GetInstance().Deallocate(RspInfo);
		RspInfo = nullptr;
	}
}
RspQryMoneyTransferPackage* RspQryMoneyTransferPackage::Allocate()
{
	return ObjectPool<RspQryMoneyTransferPackage>::GetInstance().Allocate();
}
void RspQryMoneyTransferPackage::Deallocate()
{
	ObjectPool<RspQryMoneyTransferPackage>::GetInstance().Deallocate(this);
}
void RspQryMoneyTransferPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				MoneyTransfer = ObjectPool<MoneyTransferField>::GetInstance().Allocate();
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
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
			MoneyTransfer = ObjectPool<MoneyTransferField>::GetInstance().Allocate();
			memcpy(MoneyTransfer, buff + offset, sizeof(MoneyTransferField));
			offset += sizeof(MoneyTransferField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
 
ReqInsertOrderPackage::ReqInsertOrderPackage()
	:ReqInsertOrder(nullptr)
{
}
ReqInsertOrderPackage::~ReqInsertOrderPackage()
{
	if (ReqInsertOrder != nullptr)
	{
		ObjectPool<ReqInsertOrderField>::GetInstance().Deallocate(ReqInsertOrder);
		ReqInsertOrder = nullptr;
	}
}
ReqInsertOrderPackage* ReqInsertOrderPackage::Allocate()
{
	return ObjectPool<ReqInsertOrderPackage>::GetInstance().Allocate();
}
void ReqInsertOrderPackage::Deallocate()
{
	ObjectPool<ReqInsertOrderPackage>::GetInstance().Deallocate(this);
}
void ReqInsertOrderPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				ReqInsertOrder = ObjectPool<ReqInsertOrderField>::GetInstance().Allocate();
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
			ReqInsertOrder = ObjectPool<ReqInsertOrderField>::GetInstance().Allocate();
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
 
RspInsertOrderPackage::RspInsertOrderPackage()
	:ReqInsertOrder(nullptr), RspInfo(nullptr)
{
}
RspInsertOrderPackage::~RspInsertOrderPackage()
{
	if (ReqInsertOrder != nullptr)
	{
		ObjectPool<ReqInsertOrderField>::GetInstance().Deallocate(ReqInsertOrder);
		ReqInsertOrder = nullptr;
	}
	if (RspInfo != nullptr)
	{
		ObjectPool<RspInfoField>::GetInstance().Deallocate(RspInfo);
		RspInfo = nullptr;
	}
}
RspInsertOrderPackage* RspInsertOrderPackage::Allocate()
{
	return ObjectPool<RspInsertOrderPackage>::GetInstance().Allocate();
}
void RspInsertOrderPackage::Deallocate()
{
	ObjectPool<RspInsertOrderPackage>::GetInstance().Deallocate(this);
}
void RspInsertOrderPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				ReqInsertOrder = ObjectPool<ReqInsertOrderField>::GetInstance().Allocate();
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
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
			ReqInsertOrder = ObjectPool<ReqInsertOrderField>::GetInstance().Allocate();
			memcpy(ReqInsertOrder, buff + offset, sizeof(ReqInsertOrderField));
			offset += sizeof(ReqInsertOrderField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
 
ReqCancelOrderPackage::ReqCancelOrderPackage()
	:ReqCancelOrder(nullptr)
{
}
ReqCancelOrderPackage::~ReqCancelOrderPackage()
{
	if (ReqCancelOrder != nullptr)
	{
		ObjectPool<ReqCancelOrderField>::GetInstance().Deallocate(ReqCancelOrder);
		ReqCancelOrder = nullptr;
	}
}
ReqCancelOrderPackage* ReqCancelOrderPackage::Allocate()
{
	return ObjectPool<ReqCancelOrderPackage>::GetInstance().Allocate();
}
void ReqCancelOrderPackage::Deallocate()
{
	ObjectPool<ReqCancelOrderPackage>::GetInstance().Deallocate(this);
}
void ReqCancelOrderPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				ReqCancelOrder = ObjectPool<ReqCancelOrderField>::GetInstance().Allocate();
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
			ReqCancelOrder = ObjectPool<ReqCancelOrderField>::GetInstance().Allocate();
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
 
RspCancelOrderPackage::RspCancelOrderPackage()
	:ReqCancelOrder(nullptr), RspInfo(nullptr)
{
}
RspCancelOrderPackage::~RspCancelOrderPackage()
{
	if (ReqCancelOrder != nullptr)
	{
		ObjectPool<ReqCancelOrderField>::GetInstance().Deallocate(ReqCancelOrder);
		ReqCancelOrder = nullptr;
	}
	if (RspInfo != nullptr)
	{
		ObjectPool<RspInfoField>::GetInstance().Deallocate(RspInfo);
		RspInfo = nullptr;
	}
}
RspCancelOrderPackage* RspCancelOrderPackage::Allocate()
{
	return ObjectPool<RspCancelOrderPackage>::GetInstance().Allocate();
}
void RspCancelOrderPackage::Deallocate()
{
	ObjectPool<RspCancelOrderPackage>::GetInstance().Deallocate(this);
}
void RspCancelOrderPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				ReqCancelOrder = ObjectPool<ReqCancelOrderField>::GetInstance().Allocate();
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
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
			ReqCancelOrder = ObjectPool<ReqCancelOrderField>::GetInstance().Allocate();
			memcpy(ReqCancelOrder, buff + offset, sizeof(ReqCancelOrderField));
			offset += sizeof(ReqCancelOrderField);	
			break;
		}
		case RspInfoField::FieldID:
		{
			RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
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
 
RtnOrderPackage::RtnOrderPackage()
	:Order(nullptr)
{
}
RtnOrderPackage::~RtnOrderPackage()
{
	if (Order != nullptr)
	{
		ObjectPool<OrderField>::GetInstance().Deallocate(Order);
		Order = nullptr;
	}
}
RtnOrderPackage* RtnOrderPackage::Allocate()
{
	return ObjectPool<RtnOrderPackage>::GetInstance().Allocate();
}
void RtnOrderPackage::Deallocate()
{
	ObjectPool<RtnOrderPackage>::GetInstance().Deallocate(this);
}
void RtnOrderPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				Order = ObjectPool<OrderField>::GetInstance().Allocate();
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
			Order = ObjectPool<OrderField>::GetInstance().Allocate();
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
 
RtnTradePackage::RtnTradePackage()
	:Trade(nullptr)
{
}
RtnTradePackage::~RtnTradePackage()
{
	if (Trade != nullptr)
	{
		ObjectPool<TradeField>::GetInstance().Deallocate(Trade);
		Trade = nullptr;
	}
}
RtnTradePackage* RtnTradePackage::Allocate()
{
	return ObjectPool<RtnTradePackage>::GetInstance().Allocate();
}
void RtnTradePackage::Deallocate()
{
	ObjectPool<RtnTradePackage>::GetInstance().Deallocate(this);
}
void RtnTradePackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				Trade = ObjectPool<TradeField>::GetInstance().Allocate();
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
			Trade = ObjectPool<TradeField>::GetInstance().Allocate();
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
 
RtnMoneyTransferPackage::RtnMoneyTransferPackage()
	:MoneyTransfer(nullptr)
{
}
RtnMoneyTransferPackage::~RtnMoneyTransferPackage()
{
	if (MoneyTransfer != nullptr)
	{
		ObjectPool<MoneyTransferField>::GetInstance().Deallocate(MoneyTransfer);
		MoneyTransfer = nullptr;
	}
}
RtnMoneyTransferPackage* RtnMoneyTransferPackage::Allocate()
{
	return ObjectPool<RtnMoneyTransferPackage>::GetInstance().Allocate();
}
void RtnMoneyTransferPackage::Deallocate()
{
	ObjectPool<RtnMoneyTransferPackage>::GetInstance().Deallocate(this);
}
void RtnMoneyTransferPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				MoneyTransfer = ObjectPool<MoneyTransferField>::GetInstance().Allocate();
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
			MoneyTransfer = ObjectPool<MoneyTransferField>::GetInstance().Allocate();
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
 
RtnAccountLogoutPackage::RtnAccountLogoutPackage()
	:AccountLogout(nullptr)
{
}
RtnAccountLogoutPackage::~RtnAccountLogoutPackage()
{
	if (AccountLogout != nullptr)
	{
		ObjectPool<AccountLogoutField>::GetInstance().Deallocate(AccountLogout);
		AccountLogout = nullptr;
	}
}
RtnAccountLogoutPackage* RtnAccountLogoutPackage::Allocate()
{
	return ObjectPool<RtnAccountLogoutPackage>::GetInstance().Allocate();
}
void RtnAccountLogoutPackage::Deallocate()
{
	ObjectPool<RtnAccountLogoutPackage>::GetInstance().Deallocate(this);
}
void RtnAccountLogoutPackage::Prepare(SessionIDType sessionID, int messageChain, int msgSeqNum)
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
				AccountLogout = ObjectPool<AccountLogoutField>::GetInstance().Allocate();
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
			AccountLogout = ObjectPool<AccountLogoutField>::GetInstance().Allocate();
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
