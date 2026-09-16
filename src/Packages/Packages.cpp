// 本文件由 ../Templates/Cpp/Protocol/Packages/Packages.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "Packages.h"
#include <Spark/Network/Protocol/Items.h>
#include <Spark/Network/Protocol/StepUtility.h>
#include <Spark/Core/Logger/Logger.h>
#include <Spark/TemplateLib/ObjectPool/ObjectPool.h>
#include <cstdarg>
#include <cstdio>
#include <cstring>

using namespace Spark;
using namespace Spark::Core;
using namespace Spark::Network;

namespace QuantTrading::Packages
{
thread_local char DataStringBuffer[10240];

[[maybe_unused]] static int AppendDebugString(int offset, const char* format, ...)
{
	const int bufferSize = static_cast<int>(sizeof(DataStringBuffer));
	if (offset < 0)
	{
		offset = 0;
	}
	if (offset >= bufferSize - 1)
	{
		return bufferSize - 1;
	}
	va_list args;
	va_start(args, format);
	const int written = vsnprintf(DataStringBuffer + offset,
		static_cast<size_t>(bufferSize - offset), format, args);
	va_end(args);
	if (written < 0)
	{
		return offset;
	}
	const int next = offset + written;
	return next < bufferSize ? next : bufferSize - 1;
}
 
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
void NotifyConnectPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int NotifyConnectPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (NotifyConnect != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, NotifyConnectField::FieldId);
		StepUtility::WriteString(cursor, Items::SessionId, NotifyConnect->SessionId);
		if (strlen(NotifyConnect->IpAddress) >= sizeof(NotifyConnect->IpAddress))
		{
			NotifyConnect->IpAddress[sizeof(NotifyConnect->IpAddress) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::IpAddress, NotifyConnect->IpAddress);
		StepUtility::WriteString(cursor, Items::Port, NotifyConnect->Port);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, NotifyConnectField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool NotifyConnectPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case NotifyConnectField::FieldId:
			{
				NotifyConnect = ObjectPool<NotifyConnectField>::GetInstance().Allocate();
				memset(NotifyConnect, 0, sizeof(*NotifyConnect));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::SessionId:
						{
							NotifyConnect->SessionId = atoll(value.c_str());
							break;
						}
						case Items::IpAddress:
						{
							size_t len = value.length() >= sizeof(NotifyConnect->IpAddress) ? sizeof(NotifyConnect->IpAddress) - 1 : value.length();
							memcpy(NotifyConnect->IpAddress, value.c_str(), len);
							break;
						}
						case Items::Port:
						{
							NotifyConnect->Port = atoi(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for NotifyConnectField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For NotifyConnectPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(NotifyConnectField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &NotifyConnectField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case NotifyConnectField::FieldId:
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
		offset = AppendDebugString(offset, "NotifyConnect:SessionId:[%lld], IpAddress:[%s], Port:[%d]", NotifyConnect->SessionId, NotifyConnect->IpAddress, NotifyConnect->Port);
	}
	return DataStringBuffer;
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
void NotifyDisConnectPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int NotifyDisConnectPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (NotifyDisConnect != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, NotifyDisConnectField::FieldId);
		StepUtility::WriteString(cursor, Items::SessionId, NotifyDisConnect->SessionId);
		if (strlen(NotifyDisConnect->IpAddress) >= sizeof(NotifyDisConnect->IpAddress))
		{
			NotifyDisConnect->IpAddress[sizeof(NotifyDisConnect->IpAddress) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::IpAddress, NotifyDisConnect->IpAddress);
		StepUtility::WriteString(cursor, Items::Port, NotifyDisConnect->Port);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, NotifyDisConnectField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool NotifyDisConnectPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case NotifyDisConnectField::FieldId:
			{
				NotifyDisConnect = ObjectPool<NotifyDisConnectField>::GetInstance().Allocate();
				memset(NotifyDisConnect, 0, sizeof(*NotifyDisConnect));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::SessionId:
						{
							NotifyDisConnect->SessionId = atoll(value.c_str());
							break;
						}
						case Items::IpAddress:
						{
							size_t len = value.length() >= sizeof(NotifyDisConnect->IpAddress) ? sizeof(NotifyDisConnect->IpAddress) - 1 : value.length();
							memcpy(NotifyDisConnect->IpAddress, value.c_str(), len);
							break;
						}
						case Items::Port:
						{
							NotifyDisConnect->Port = atoi(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for NotifyDisConnectField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For NotifyDisConnectPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(NotifyDisConnectField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &NotifyDisConnectField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case NotifyDisConnectField::FieldId:
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
		offset = AppendDebugString(offset, "NotifyDisConnect:SessionId:[%lld], IpAddress:[%s], Port:[%d]", NotifyDisConnect->SessionId, NotifyDisConnect->IpAddress, NotifyDisConnect->Port);
	}
	return DataStringBuffer;
}
 
NotifyDbConnectPackage::NotifyDbConnectPackage()
	:NotifyDbConnect(nullptr)
{
}
NotifyDbConnectPackage::~NotifyDbConnectPackage()
{
	if (NotifyDbConnect != nullptr)
	{
		ObjectPool<NotifyDbConnectField>::GetInstance().Deallocate(NotifyDbConnect);
		NotifyDbConnect = nullptr;
	}
}
NotifyDbConnectPackage* NotifyDbConnectPackage::Allocate()
{
	return ObjectPool<NotifyDbConnectPackage>::GetInstance().Allocate();
}
void NotifyDbConnectPackage::Deallocate()
{
	ObjectPool<NotifyDbConnectPackage>::GetInstance().Deallocate(this);
}
void NotifyDbConnectPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int NotifyDbConnectPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (NotifyDbConnect != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, NotifyDbConnectField::FieldId);
		if (strlen(NotifyDbConnect->DbName) >= sizeof(NotifyDbConnect->DbName))
		{
			NotifyDbConnect->DbName[sizeof(NotifyDbConnect->DbName) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::DbName, NotifyDbConnect->DbName);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, NotifyDbConnectField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool NotifyDbConnectPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case NotifyDbConnectField::FieldId:
			{
				NotifyDbConnect = ObjectPool<NotifyDbConnectField>::GetInstance().Allocate();
				memset(NotifyDbConnect, 0, sizeof(*NotifyDbConnect));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::DbName:
						{
							size_t len = value.length() >= sizeof(NotifyDbConnect->DbName) ? sizeof(NotifyDbConnect->DbName) - 1 : value.length();
							memcpy(NotifyDbConnect->DbName, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for NotifyDbConnectField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For NotifyDbConnectPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
				return false;
			}
			startIndex = fieldEndIndex;
		}
		else
		{
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For NotifyDbConnectPackage");
			return false;
		}
	}
	return true;
}
int NotifyDbConnectPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (NotifyDbConnect != nullptr)
	{
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(NotifyDbConnectField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &NotifyDbConnectField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		memcpy(buff + offset, NotifyDbConnect, sizeof(NotifyDbConnectField));
		offset += sizeof(NotifyDbConnectField);
	}
	return offset;
}
bool NotifyDbConnectPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case NotifyDbConnectField::FieldId:
		{
			NotifyDbConnect = ObjectPool<NotifyDbConnectField>::GetInstance().Allocate();
			memcpy(NotifyDbConnect, buff + offset, sizeof(NotifyDbConnectField));
			offset += sizeof(NotifyDbConnectField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* NotifyDbConnectPackage::GetDebugString() const
{
	int offset = 0;
	if (NotifyDbConnect != nullptr)
	{
		offset = AppendDebugString(offset, "NotifyDbConnect:DbName:[%s]", NotifyDbConnect->DbName);
	}
	return DataStringBuffer;
}
 
NotifyDbDisConnectPackage::NotifyDbDisConnectPackage()
	:NotifyDbDisConnect(nullptr)
{
}
NotifyDbDisConnectPackage::~NotifyDbDisConnectPackage()
{
	if (NotifyDbDisConnect != nullptr)
	{
		ObjectPool<NotifyDbDisConnectField>::GetInstance().Deallocate(NotifyDbDisConnect);
		NotifyDbDisConnect = nullptr;
	}
}
NotifyDbDisConnectPackage* NotifyDbDisConnectPackage::Allocate()
{
	return ObjectPool<NotifyDbDisConnectPackage>::GetInstance().Allocate();
}
void NotifyDbDisConnectPackage::Deallocate()
{
	ObjectPool<NotifyDbDisConnectPackage>::GetInstance().Deallocate(this);
}
void NotifyDbDisConnectPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int NotifyDbDisConnectPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (NotifyDbDisConnect != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, NotifyDbDisConnectField::FieldId);
		if (strlen(NotifyDbDisConnect->DbName) >= sizeof(NotifyDbDisConnect->DbName))
		{
			NotifyDbDisConnect->DbName[sizeof(NotifyDbDisConnect->DbName) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::DbName, NotifyDbDisConnect->DbName);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, NotifyDbDisConnectField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool NotifyDbDisConnectPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case NotifyDbDisConnectField::FieldId:
			{
				NotifyDbDisConnect = ObjectPool<NotifyDbDisConnectField>::GetInstance().Allocate();
				memset(NotifyDbDisConnect, 0, sizeof(*NotifyDbDisConnect));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::DbName:
						{
							size_t len = value.length() >= sizeof(NotifyDbDisConnect->DbName) ? sizeof(NotifyDbDisConnect->DbName) - 1 : value.length();
							memcpy(NotifyDbDisConnect->DbName, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for NotifyDbDisConnectField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For NotifyDbDisConnectPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
				return false;
			}
			startIndex = fieldEndIndex;
		}
		else
		{
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For NotifyDbDisConnectPackage");
			return false;
		}
	}
	return true;
}
int NotifyDbDisConnectPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (NotifyDbDisConnect != nullptr)
	{
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(NotifyDbDisConnectField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &NotifyDbDisConnectField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		memcpy(buff + offset, NotifyDbDisConnect, sizeof(NotifyDbDisConnectField));
		offset += sizeof(NotifyDbDisConnectField);
	}
	return offset;
}
bool NotifyDbDisConnectPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case NotifyDbDisConnectField::FieldId:
		{
			NotifyDbDisConnect = ObjectPool<NotifyDbDisConnectField>::GetInstance().Allocate();
			memcpy(NotifyDbDisConnect, buff + offset, sizeof(NotifyDbDisConnectField));
			offset += sizeof(NotifyDbDisConnectField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* NotifyDbDisConnectPackage::GetDebugString() const
{
	int offset = 0;
	if (NotifyDbDisConnect != nullptr)
	{
		offset = AppendDebugString(offset, "NotifyDbDisConnect:DbName:[%s]", NotifyDbDisConnect->DbName);
	}
	return DataStringBuffer;
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
void ReqMdUserLoginPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int ReqMdUserLoginPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (ReqMdUserLogin != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, ReqMdUserLoginField::FieldId);
		if (strlen(ReqMdUserLogin->UserId) >= sizeof(ReqMdUserLogin->UserId))
		{
			ReqMdUserLogin->UserId[sizeof(ReqMdUserLogin->UserId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::UserId, ReqMdUserLogin->UserId);
		if (strlen(ReqMdUserLogin->Password) >= sizeof(ReqMdUserLogin->Password))
		{
			ReqMdUserLogin->Password[sizeof(ReqMdUserLogin->Password) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::Password, ReqMdUserLogin->Password);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, ReqMdUserLoginField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool ReqMdUserLoginPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case ReqMdUserLoginField::FieldId:
			{
				ReqMdUserLogin = ObjectPool<ReqMdUserLoginField>::GetInstance().Allocate();
				memset(ReqMdUserLogin, 0, sizeof(*ReqMdUserLogin));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::UserId:
						{
							size_t len = value.length() >= sizeof(ReqMdUserLogin->UserId) ? sizeof(ReqMdUserLogin->UserId) - 1 : value.length();
							memcpy(ReqMdUserLogin->UserId, value.c_str(), len);
							break;
						}
						case Items::Password:
						{
							size_t len = value.length() >= sizeof(ReqMdUserLogin->Password) ? sizeof(ReqMdUserLogin->Password) - 1 : value.length();
							memcpy(ReqMdUserLogin->Password, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for ReqMdUserLoginField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqMdUserLoginPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(ReqMdUserLoginField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &ReqMdUserLoginField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case ReqMdUserLoginField::FieldId:
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
		offset = AppendDebugString(offset, "ReqMdUserLogin:UserId:[%s], Password:[%s]", ReqMdUserLogin->UserId, ReqMdUserLogin->Password);
	}
	return DataStringBuffer;
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
void RspMdUserLoginPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RspMdUserLoginPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (RspMdUserLogin != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspMdUserLoginField::FieldId);
		if (strlen(RspMdUserLogin->UserId) >= sizeof(RspMdUserLogin->UserId))
		{
			RspMdUserLogin->UserId[sizeof(RspMdUserLogin->UserId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::UserId, RspMdUserLogin->UserId);
		if (strlen(RspMdUserLogin->LoginDate) >= sizeof(RspMdUserLogin->LoginDate))
		{
			RspMdUserLogin->LoginDate[sizeof(RspMdUserLogin->LoginDate) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::LoginDate, RspMdUserLogin->LoginDate);
		if (strlen(RspMdUserLogin->LoginTime) >= sizeof(RspMdUserLogin->LoginTime))
		{
			RspMdUserLogin->LoginTime[sizeof(RspMdUserLogin->LoginTime) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::LoginTime, RspMdUserLogin->LoginTime);
		StepUtility::WriteString(cursor, Items::SessionId, RspMdUserLogin->SessionId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspMdUserLoginField::FieldId);
	}
	if (RspInfo != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspInfoField::FieldId);
		StepUtility::WriteString(cursor, Items::ErrorId, RspInfo->ErrorId);
		if (strlen(RspInfo->ErrorMsg) >= sizeof(RspInfo->ErrorMsg))
		{
			RspInfo->ErrorMsg[sizeof(RspInfo->ErrorMsg) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ErrorMsg, RspInfo->ErrorMsg);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspInfoField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RspMdUserLoginPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case RspMdUserLoginField::FieldId:
			{
				RspMdUserLogin = ObjectPool<RspMdUserLoginField>::GetInstance().Allocate();
				memset(RspMdUserLogin, 0, sizeof(*RspMdUserLogin));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::UserId:
						{
							size_t len = value.length() >= sizeof(RspMdUserLogin->UserId) ? sizeof(RspMdUserLogin->UserId) - 1 : value.length();
							memcpy(RspMdUserLogin->UserId, value.c_str(), len);
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
						case Items::SessionId:
						{
							RspMdUserLogin->SessionId = atoll(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspMdUserLoginField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspMdUserLoginPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldId:
			{
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
				memset(RspInfo, 0, sizeof(*RspInfo));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ErrorId:
						{
							RspInfo->ErrorId = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(RspInfo->ErrorMsg) ? sizeof(RspInfo->ErrorMsg) - 1 : value.length();
							memcpy(RspInfo->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspInfoField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspMdUserLoginPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspMdUserLoginField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspMdUserLoginField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		memcpy(buff + offset, RspMdUserLogin, sizeof(RspMdUserLoginField));
		offset += sizeof(RspMdUserLoginField);
	}
	if (RspInfo != nullptr)
	{
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspInfoField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspInfoField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case RspMdUserLoginField::FieldId:
		{
			RspMdUserLogin = ObjectPool<RspMdUserLoginField>::GetInstance().Allocate();
			memcpy(RspMdUserLogin, buff + offset, sizeof(RspMdUserLoginField));
			offset += sizeof(RspMdUserLoginField);	
			break;
		}
		case RspInfoField::FieldId:
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
		offset = AppendDebugString(offset, "RspMdUserLogin:UserId:[%s], LoginDate:[%s], LoginTime:[%s], SessionId:[%lld]", RspMdUserLogin->UserId, RspMdUserLogin->LoginDate, RspMdUserLogin->LoginTime, RspMdUserLogin->SessionId);
	}
	if (RspInfo != nullptr)
	{
		offset = AppendDebugString(offset, "RspInfo:ErrorId:[%d], ErrorMsg:[%s]", RspInfo->ErrorId, RspInfo->ErrorMsg);
	}
	return DataStringBuffer;
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
void ReqMdUserLogoutPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int ReqMdUserLogoutPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (ReqMdUserLogout != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, ReqMdUserLogoutField::FieldId);
		if (strlen(ReqMdUserLogout->UserId) >= sizeof(ReqMdUserLogout->UserId))
		{
			ReqMdUserLogout->UserId[sizeof(ReqMdUserLogout->UserId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::UserId, ReqMdUserLogout->UserId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, ReqMdUserLogoutField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool ReqMdUserLogoutPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case ReqMdUserLogoutField::FieldId:
			{
				ReqMdUserLogout = ObjectPool<ReqMdUserLogoutField>::GetInstance().Allocate();
				memset(ReqMdUserLogout, 0, sizeof(*ReqMdUserLogout));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::UserId:
						{
							size_t len = value.length() >= sizeof(ReqMdUserLogout->UserId) ? sizeof(ReqMdUserLogout->UserId) - 1 : value.length();
							memcpy(ReqMdUserLogout->UserId, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for ReqMdUserLogoutField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqMdUserLogoutPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(ReqMdUserLogoutField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &ReqMdUserLogoutField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case ReqMdUserLogoutField::FieldId:
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
		offset = AppendDebugString(offset, "ReqMdUserLogout:UserId:[%s]", ReqMdUserLogout->UserId);
	}
	return DataStringBuffer;
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
void RspMdUserLogoutPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RspMdUserLogoutPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (RspMdUserLogout != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspMdUserLogoutField::FieldId);
		if (strlen(RspMdUserLogout->UserId) >= sizeof(RspMdUserLogout->UserId))
		{
			RspMdUserLogout->UserId[sizeof(RspMdUserLogout->UserId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::UserId, RspMdUserLogout->UserId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspMdUserLogoutField::FieldId);
	}
	if (RspInfo != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspInfoField::FieldId);
		StepUtility::WriteString(cursor, Items::ErrorId, RspInfo->ErrorId);
		if (strlen(RspInfo->ErrorMsg) >= sizeof(RspInfo->ErrorMsg))
		{
			RspInfo->ErrorMsg[sizeof(RspInfo->ErrorMsg) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ErrorMsg, RspInfo->ErrorMsg);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspInfoField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RspMdUserLogoutPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case RspMdUserLogoutField::FieldId:
			{
				RspMdUserLogout = ObjectPool<RspMdUserLogoutField>::GetInstance().Allocate();
				memset(RspMdUserLogout, 0, sizeof(*RspMdUserLogout));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::UserId:
						{
							size_t len = value.length() >= sizeof(RspMdUserLogout->UserId) ? sizeof(RspMdUserLogout->UserId) - 1 : value.length();
							memcpy(RspMdUserLogout->UserId, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspMdUserLogoutField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspMdUserLogoutPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldId:
			{
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
				memset(RspInfo, 0, sizeof(*RspInfo));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ErrorId:
						{
							RspInfo->ErrorId = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(RspInfo->ErrorMsg) ? sizeof(RspInfo->ErrorMsg) - 1 : value.length();
							memcpy(RspInfo->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspInfoField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspMdUserLogoutPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspMdUserLogoutField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspMdUserLogoutField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		memcpy(buff + offset, RspMdUserLogout, sizeof(RspMdUserLogoutField));
		offset += sizeof(RspMdUserLogoutField);
	}
	if (RspInfo != nullptr)
	{
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspInfoField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspInfoField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case RspMdUserLogoutField::FieldId:
		{
			RspMdUserLogout = ObjectPool<RspMdUserLogoutField>::GetInstance().Allocate();
			memcpy(RspMdUserLogout, buff + offset, sizeof(RspMdUserLogoutField));
			offset += sizeof(RspMdUserLogoutField);	
			break;
		}
		case RspInfoField::FieldId:
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
		offset = AppendDebugString(offset, "RspMdUserLogout:UserId:[%s]", RspMdUserLogout->UserId);
	}
	if (RspInfo != nullptr)
	{
		offset = AppendDebugString(offset, "RspInfo:ErrorId:[%d], ErrorMsg:[%s]", RspInfo->ErrorId, RspInfo->ErrorMsg);
	}
	return DataStringBuffer;
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
void ReqSubMarketDataPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int ReqSubMarketDataPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (ReqSubMarketData != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, ReqSubMarketDataField::FieldId);
		if (strlen(ReqSubMarketData->ExchangeId) >= sizeof(ReqSubMarketData->ExchangeId))
		{
			ReqSubMarketData->ExchangeId[sizeof(ReqSubMarketData->ExchangeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeId, ReqSubMarketData->ExchangeId);
		if (strlen(ReqSubMarketData->InstrumentId) >= sizeof(ReqSubMarketData->InstrumentId))
		{
			ReqSubMarketData->InstrumentId[sizeof(ReqSubMarketData->InstrumentId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::InstrumentId, ReqSubMarketData->InstrumentId);
		StepUtility::WriteString(cursor, Items::BarPreces, static_cast<int>(ReqSubMarketData->BarPreces));
		StepUtility::WriteString(cursor, Items::BarPeriod, ReqSubMarketData->BarPeriod);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, ReqSubMarketDataField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool ReqSubMarketDataPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case ReqSubMarketDataField::FieldId:
			{
				ReqSubMarketData = ObjectPool<ReqSubMarketDataField>::GetInstance().Allocate();
				memset(ReqSubMarketData, 0, sizeof(*ReqSubMarketData));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ExchangeId:
						{
							size_t len = value.length() >= sizeof(ReqSubMarketData->ExchangeId) ? sizeof(ReqSubMarketData->ExchangeId) - 1 : value.length();
							memcpy(ReqSubMarketData->ExchangeId, value.c_str(), len);
							break;
						}
						case Items::InstrumentId:
						{
							size_t len = value.length() >= sizeof(ReqSubMarketData->InstrumentId) ? sizeof(ReqSubMarketData->InstrumentId) - 1 : value.length();
							memcpy(ReqSubMarketData->InstrumentId, value.c_str(), len);
							break;
						}
						case Items::BarPreces:
						{
							ReqSubMarketData->BarPreces = static_cast<BarPrecesType>(atoi(value.c_str()));
							break;
						}
						case Items::BarPeriod:
						{
							ReqSubMarketData->BarPeriod = atoi(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for ReqSubMarketDataField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqSubMarketDataPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(ReqSubMarketDataField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &ReqSubMarketDataField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case ReqSubMarketDataField::FieldId:
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
		offset = AppendDebugString(offset, "ReqSubMarketData:ExchangeId:[%s], InstrumentId:[%s], BarPreces:[%d], BarPeriod:[%d]", ReqSubMarketData->ExchangeId, ReqSubMarketData->InstrumentId, static_cast<int>(ReqSubMarketData->BarPreces), ReqSubMarketData->BarPeriod);
	}
	return DataStringBuffer;
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
void RspSubMarketDataPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RspSubMarketDataPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (RspSubMarketData != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspSubMarketDataField::FieldId);
		if (strlen(RspSubMarketData->ExchangeId) >= sizeof(RspSubMarketData->ExchangeId))
		{
			RspSubMarketData->ExchangeId[sizeof(RspSubMarketData->ExchangeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeId, RspSubMarketData->ExchangeId);
		if (strlen(RspSubMarketData->InstrumentId) >= sizeof(RspSubMarketData->InstrumentId))
		{
			RspSubMarketData->InstrumentId[sizeof(RspSubMarketData->InstrumentId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::InstrumentId, RspSubMarketData->InstrumentId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspSubMarketDataField::FieldId);
	}
	if (RspInfo != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspInfoField::FieldId);
		StepUtility::WriteString(cursor, Items::ErrorId, RspInfo->ErrorId);
		if (strlen(RspInfo->ErrorMsg) >= sizeof(RspInfo->ErrorMsg))
		{
			RspInfo->ErrorMsg[sizeof(RspInfo->ErrorMsg) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ErrorMsg, RspInfo->ErrorMsg);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspInfoField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RspSubMarketDataPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case RspSubMarketDataField::FieldId:
			{
				RspSubMarketData = ObjectPool<RspSubMarketDataField>::GetInstance().Allocate();
				memset(RspSubMarketData, 0, sizeof(*RspSubMarketData));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ExchangeId:
						{
							size_t len = value.length() >= sizeof(RspSubMarketData->ExchangeId) ? sizeof(RspSubMarketData->ExchangeId) - 1 : value.length();
							memcpy(RspSubMarketData->ExchangeId, value.c_str(), len);
							break;
						}
						case Items::InstrumentId:
						{
							size_t len = value.length() >= sizeof(RspSubMarketData->InstrumentId) ? sizeof(RspSubMarketData->InstrumentId) - 1 : value.length();
							memcpy(RspSubMarketData->InstrumentId, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspSubMarketDataField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspSubMarketDataPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldId:
			{
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
				memset(RspInfo, 0, sizeof(*RspInfo));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ErrorId:
						{
							RspInfo->ErrorId = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(RspInfo->ErrorMsg) ? sizeof(RspInfo->ErrorMsg) - 1 : value.length();
							memcpy(RspInfo->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspInfoField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspSubMarketDataPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspSubMarketDataField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspSubMarketDataField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		memcpy(buff + offset, RspSubMarketData, sizeof(RspSubMarketDataField));
		offset += sizeof(RspSubMarketDataField);
	}
	if (RspInfo != nullptr)
	{
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspInfoField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspInfoField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case RspSubMarketDataField::FieldId:
		{
			RspSubMarketData = ObjectPool<RspSubMarketDataField>::GetInstance().Allocate();
			memcpy(RspSubMarketData, buff + offset, sizeof(RspSubMarketDataField));
			offset += sizeof(RspSubMarketDataField);	
			break;
		}
		case RspInfoField::FieldId:
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
		offset = AppendDebugString(offset, "RspSubMarketData:ExchangeId:[%s], InstrumentId:[%s]", RspSubMarketData->ExchangeId, RspSubMarketData->InstrumentId);
	}
	if (RspInfo != nullptr)
	{
		offset = AppendDebugString(offset, "RspInfo:ErrorId:[%d], ErrorMsg:[%s]", RspInfo->ErrorId, RspInfo->ErrorMsg);
	}
	return DataStringBuffer;
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
void ReqUnSubMarketDataPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int ReqUnSubMarketDataPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (ReqUnSubMarketData != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, ReqUnSubMarketDataField::FieldId);
		if (strlen(ReqUnSubMarketData->ExchangeId) >= sizeof(ReqUnSubMarketData->ExchangeId))
		{
			ReqUnSubMarketData->ExchangeId[sizeof(ReqUnSubMarketData->ExchangeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeId, ReqUnSubMarketData->ExchangeId);
		if (strlen(ReqUnSubMarketData->InstrumentId) >= sizeof(ReqUnSubMarketData->InstrumentId))
		{
			ReqUnSubMarketData->InstrumentId[sizeof(ReqUnSubMarketData->InstrumentId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::InstrumentId, ReqUnSubMarketData->InstrumentId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, ReqUnSubMarketDataField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool ReqUnSubMarketDataPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case ReqUnSubMarketDataField::FieldId:
			{
				ReqUnSubMarketData = ObjectPool<ReqUnSubMarketDataField>::GetInstance().Allocate();
				memset(ReqUnSubMarketData, 0, sizeof(*ReqUnSubMarketData));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ExchangeId:
						{
							size_t len = value.length() >= sizeof(ReqUnSubMarketData->ExchangeId) ? sizeof(ReqUnSubMarketData->ExchangeId) - 1 : value.length();
							memcpy(ReqUnSubMarketData->ExchangeId, value.c_str(), len);
							break;
						}
						case Items::InstrumentId:
						{
							size_t len = value.length() >= sizeof(ReqUnSubMarketData->InstrumentId) ? sizeof(ReqUnSubMarketData->InstrumentId) - 1 : value.length();
							memcpy(ReqUnSubMarketData->InstrumentId, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for ReqUnSubMarketDataField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqUnSubMarketDataPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(ReqUnSubMarketDataField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &ReqUnSubMarketDataField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case ReqUnSubMarketDataField::FieldId:
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
		offset = AppendDebugString(offset, "ReqUnSubMarketData:ExchangeId:[%s], InstrumentId:[%s]", ReqUnSubMarketData->ExchangeId, ReqUnSubMarketData->InstrumentId);
	}
	return DataStringBuffer;
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
void RspUnSubMarketDataPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RspUnSubMarketDataPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (RspUnSubMarketData != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspUnSubMarketDataField::FieldId);
		if (strlen(RspUnSubMarketData->ExchangeId) >= sizeof(RspUnSubMarketData->ExchangeId))
		{
			RspUnSubMarketData->ExchangeId[sizeof(RspUnSubMarketData->ExchangeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeId, RspUnSubMarketData->ExchangeId);
		if (strlen(RspUnSubMarketData->InstrumentId) >= sizeof(RspUnSubMarketData->InstrumentId))
		{
			RspUnSubMarketData->InstrumentId[sizeof(RspUnSubMarketData->InstrumentId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::InstrumentId, RspUnSubMarketData->InstrumentId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspUnSubMarketDataField::FieldId);
	}
	if (RspInfo != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspInfoField::FieldId);
		StepUtility::WriteString(cursor, Items::ErrorId, RspInfo->ErrorId);
		if (strlen(RspInfo->ErrorMsg) >= sizeof(RspInfo->ErrorMsg))
		{
			RspInfo->ErrorMsg[sizeof(RspInfo->ErrorMsg) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ErrorMsg, RspInfo->ErrorMsg);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspInfoField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RspUnSubMarketDataPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case RspUnSubMarketDataField::FieldId:
			{
				RspUnSubMarketData = ObjectPool<RspUnSubMarketDataField>::GetInstance().Allocate();
				memset(RspUnSubMarketData, 0, sizeof(*RspUnSubMarketData));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ExchangeId:
						{
							size_t len = value.length() >= sizeof(RspUnSubMarketData->ExchangeId) ? sizeof(RspUnSubMarketData->ExchangeId) - 1 : value.length();
							memcpy(RspUnSubMarketData->ExchangeId, value.c_str(), len);
							break;
						}
						case Items::InstrumentId:
						{
							size_t len = value.length() >= sizeof(RspUnSubMarketData->InstrumentId) ? sizeof(RspUnSubMarketData->InstrumentId) - 1 : value.length();
							memcpy(RspUnSubMarketData->InstrumentId, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspUnSubMarketDataField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspUnSubMarketDataPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldId:
			{
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
				memset(RspInfo, 0, sizeof(*RspInfo));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ErrorId:
						{
							RspInfo->ErrorId = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(RspInfo->ErrorMsg) ? sizeof(RspInfo->ErrorMsg) - 1 : value.length();
							memcpy(RspInfo->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspInfoField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspUnSubMarketDataPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspUnSubMarketDataField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspUnSubMarketDataField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		memcpy(buff + offset, RspUnSubMarketData, sizeof(RspUnSubMarketDataField));
		offset += sizeof(RspUnSubMarketDataField);
	}
	if (RspInfo != nullptr)
	{
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspInfoField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspInfoField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case RspUnSubMarketDataField::FieldId:
		{
			RspUnSubMarketData = ObjectPool<RspUnSubMarketDataField>::GetInstance().Allocate();
			memcpy(RspUnSubMarketData, buff + offset, sizeof(RspUnSubMarketDataField));
			offset += sizeof(RspUnSubMarketDataField);	
			break;
		}
		case RspInfoField::FieldId:
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
		offset = AppendDebugString(offset, "RspUnSubMarketData:ExchangeId:[%s], InstrumentId:[%s]", RspUnSubMarketData->ExchangeId, RspUnSubMarketData->InstrumentId);
	}
	if (RspInfo != nullptr)
	{
		offset = AppendDebugString(offset, "RspInfo:ErrorId:[%d], ErrorMsg:[%s]", RspInfo->ErrorId, RspInfo->ErrorMsg);
	}
	return DataStringBuffer;
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
void ReqSubMarketDataFinishedPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int ReqSubMarketDataFinishedPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (ReqSubMarketDataFinished != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, ReqSubMarketDataFinishedField::FieldId);
		StepUtility::WriteString(cursor, Items::SessionId, ReqSubMarketDataFinished->SessionId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, ReqSubMarketDataFinishedField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool ReqSubMarketDataFinishedPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case ReqSubMarketDataFinishedField::FieldId:
			{
				ReqSubMarketDataFinished = ObjectPool<ReqSubMarketDataFinishedField>::GetInstance().Allocate();
				memset(ReqSubMarketDataFinished, 0, sizeof(*ReqSubMarketDataFinished));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::SessionId:
						{
							ReqSubMarketDataFinished->SessionId = atoll(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for ReqSubMarketDataFinishedField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqSubMarketDataFinishedPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(ReqSubMarketDataFinishedField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &ReqSubMarketDataFinishedField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case ReqSubMarketDataFinishedField::FieldId:
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
		offset = AppendDebugString(offset, "ReqSubMarketDataFinished:SessionId:[%lld]", ReqSubMarketDataFinished->SessionId);
	}
	return DataStringBuffer;
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
void RtnDepthMarketDataPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RtnDepthMarketDataPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (DepthMarketData != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, DepthMarketDataField::FieldId);
		if (strlen(DepthMarketData->TradingDay) >= sizeof(DepthMarketData->TradingDay))
		{
			DepthMarketData->TradingDay[sizeof(DepthMarketData->TradingDay) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::TradingDay, DepthMarketData->TradingDay);
		if (strlen(DepthMarketData->ExchangeId) >= sizeof(DepthMarketData->ExchangeId))
		{
			DepthMarketData->ExchangeId[sizeof(DepthMarketData->ExchangeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeId, DepthMarketData->ExchangeId);
		if (strlen(DepthMarketData->InstrumentId) >= sizeof(DepthMarketData->InstrumentId))
		{
			DepthMarketData->InstrumentId[sizeof(DepthMarketData->InstrumentId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::InstrumentId, DepthMarketData->InstrumentId);
		StepUtility::WriteString(cursor, Items::UpdateTs, DepthMarketData->UpdateTs);
		StepUtility::WriteString(cursor, Items::LastPrice, DepthMarketData->LastPrice);
		StepUtility::WriteString(cursor, Items::PreSettlementPrice, DepthMarketData->PreSettlementPrice);
		StepUtility::WriteString(cursor, Items::PreClosePrice, DepthMarketData->PreClosePrice);
		StepUtility::WriteString(cursor, Items::PreOpenInterest, DepthMarketData->PreOpenInterest);
		StepUtility::WriteString(cursor, Items::OpenPrice, DepthMarketData->OpenPrice);
		StepUtility::WriteString(cursor, Items::HighestPrice, DepthMarketData->HighestPrice);
		StepUtility::WriteString(cursor, Items::LowestPrice, DepthMarketData->LowestPrice);
		StepUtility::WriteString(cursor, Items::ClosePrice, DepthMarketData->ClosePrice);
		StepUtility::WriteString(cursor, Items::CurrVolume, DepthMarketData->CurrVolume);
		StepUtility::WriteString(cursor, Items::Volume, DepthMarketData->Volume);
		StepUtility::WriteString(cursor, Items::CurrTurnover, DepthMarketData->CurrTurnover);
		StepUtility::WriteString(cursor, Items::Turnover, DepthMarketData->Turnover);
		StepUtility::WriteString(cursor, Items::OpenInterest, DepthMarketData->OpenInterest);
		StepUtility::WriteString(cursor, Items::SettlementPrice, DepthMarketData->SettlementPrice);
		StepUtility::WriteString(cursor, Items::UpperLimitPrice, DepthMarketData->UpperLimitPrice);
		StepUtility::WriteString(cursor, Items::LowerLimitPrice, DepthMarketData->LowerLimitPrice);
		StepUtility::WriteString(cursor, Items::AveragePrice, DepthMarketData->AveragePrice);
		StepUtility::WriteString(cursor, Items::AskPrice1, DepthMarketData->AskPrice1);
		StepUtility::WriteString(cursor, Items::AskPrice2, DepthMarketData->AskPrice2);
		StepUtility::WriteString(cursor, Items::AskPrice3, DepthMarketData->AskPrice3);
		StepUtility::WriteString(cursor, Items::AskPrice4, DepthMarketData->AskPrice4);
		StepUtility::WriteString(cursor, Items::AskPrice5, DepthMarketData->AskPrice5);
		StepUtility::WriteString(cursor, Items::AskPrice6, DepthMarketData->AskPrice6);
		StepUtility::WriteString(cursor, Items::AskPrice7, DepthMarketData->AskPrice7);
		StepUtility::WriteString(cursor, Items::AskPrice8, DepthMarketData->AskPrice8);
		StepUtility::WriteString(cursor, Items::AskPrice9, DepthMarketData->AskPrice9);
		StepUtility::WriteString(cursor, Items::AskPrice10, DepthMarketData->AskPrice10);
		StepUtility::WriteString(cursor, Items::AskVolume1, DepthMarketData->AskVolume1);
		StepUtility::WriteString(cursor, Items::AskVolume2, DepthMarketData->AskVolume2);
		StepUtility::WriteString(cursor, Items::AskVolume3, DepthMarketData->AskVolume3);
		StepUtility::WriteString(cursor, Items::AskVolume4, DepthMarketData->AskVolume4);
		StepUtility::WriteString(cursor, Items::AskVolume5, DepthMarketData->AskVolume5);
		StepUtility::WriteString(cursor, Items::AskVolume6, DepthMarketData->AskVolume6);
		StepUtility::WriteString(cursor, Items::AskVolume7, DepthMarketData->AskVolume7);
		StepUtility::WriteString(cursor, Items::AskVolume8, DepthMarketData->AskVolume8);
		StepUtility::WriteString(cursor, Items::AskVolume9, DepthMarketData->AskVolume9);
		StepUtility::WriteString(cursor, Items::AskVolume10, DepthMarketData->AskVolume10);
		StepUtility::WriteString(cursor, Items::BidPrice1, DepthMarketData->BidPrice1);
		StepUtility::WriteString(cursor, Items::BidPrice2, DepthMarketData->BidPrice2);
		StepUtility::WriteString(cursor, Items::BidPrice3, DepthMarketData->BidPrice3);
		StepUtility::WriteString(cursor, Items::BidPrice4, DepthMarketData->BidPrice4);
		StepUtility::WriteString(cursor, Items::BidPrice5, DepthMarketData->BidPrice5);
		StepUtility::WriteString(cursor, Items::BidPrice6, DepthMarketData->BidPrice6);
		StepUtility::WriteString(cursor, Items::BidPrice7, DepthMarketData->BidPrice7);
		StepUtility::WriteString(cursor, Items::BidPrice8, DepthMarketData->BidPrice8);
		StepUtility::WriteString(cursor, Items::BidPrice9, DepthMarketData->BidPrice9);
		StepUtility::WriteString(cursor, Items::BidPrice10, DepthMarketData->BidPrice10);
		StepUtility::WriteString(cursor, Items::BidVolume1, DepthMarketData->BidVolume1);
		StepUtility::WriteString(cursor, Items::BidVolume2, DepthMarketData->BidVolume2);
		StepUtility::WriteString(cursor, Items::BidVolume3, DepthMarketData->BidVolume3);
		StepUtility::WriteString(cursor, Items::BidVolume4, DepthMarketData->BidVolume4);
		StepUtility::WriteString(cursor, Items::BidVolume5, DepthMarketData->BidVolume5);
		StepUtility::WriteString(cursor, Items::BidVolume6, DepthMarketData->BidVolume6);
		StepUtility::WriteString(cursor, Items::BidVolume7, DepthMarketData->BidVolume7);
		StepUtility::WriteString(cursor, Items::BidVolume8, DepthMarketData->BidVolume8);
		StepUtility::WriteString(cursor, Items::BidVolume9, DepthMarketData->BidVolume9);
		StepUtility::WriteString(cursor, Items::BidVolume10, DepthMarketData->BidVolume10);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, DepthMarketDataField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RtnDepthMarketDataPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case DepthMarketDataField::FieldId:
			{
				DepthMarketData = ObjectPool<DepthMarketDataField>::GetInstance().Allocate();
				memset(DepthMarketData, 0, sizeof(*DepthMarketData));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
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
						case Items::ExchangeId:
						{
							size_t len = value.length() >= sizeof(DepthMarketData->ExchangeId) ? sizeof(DepthMarketData->ExchangeId) - 1 : value.length();
							memcpy(DepthMarketData->ExchangeId, value.c_str(), len);
							break;
						}
						case Items::InstrumentId:
						{
							size_t len = value.length() >= sizeof(DepthMarketData->InstrumentId) ? sizeof(DepthMarketData->InstrumentId) - 1 : value.length();
							memcpy(DepthMarketData->InstrumentId, value.c_str(), len);
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
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for DepthMarketDataField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RtnDepthMarketDataPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(DepthMarketDataField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &DepthMarketDataField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case DepthMarketDataField::FieldId:
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
		offset = AppendDebugString(offset, "DepthMarketData:TradingDay:[%s], ExchangeId:[%s], InstrumentId:[%s], UpdateTs:[%lld], LastPrice:[%f], PreSettlementPrice:[%f], PreClosePrice:[%f], PreOpenInterest:[%f], OpenPrice:[%f], HighestPrice:[%f], LowestPrice:[%f], ClosePrice:[%f], CurrVolume:[%lld], Volume:[%lld], CurrTurnover:[%f], Turnover:[%f], OpenInterest:[%f], SettlementPrice:[%f], UpperLimitPrice:[%f], LowerLimitPrice:[%f], AveragePrice:[%f], AskPrice1:[%f], AskPrice2:[%f], AskPrice3:[%f], AskPrice4:[%f], AskPrice5:[%f], AskPrice6:[%f], AskPrice7:[%f], AskPrice8:[%f], AskPrice9:[%f], AskPrice10:[%f], AskVolume1:[%lld], AskVolume2:[%lld], AskVolume3:[%lld], AskVolume4:[%lld], AskVolume5:[%lld], AskVolume6:[%lld], AskVolume7:[%lld], AskVolume8:[%lld], AskVolume9:[%lld], AskVolume10:[%lld], BidPrice1:[%f], BidPrice2:[%f], BidPrice3:[%f], BidPrice4:[%f], BidPrice5:[%f], BidPrice6:[%f], BidPrice7:[%f], BidPrice8:[%f], BidPrice9:[%f], BidPrice10:[%f], BidVolume1:[%lld], BidVolume2:[%lld], BidVolume3:[%lld], BidVolume4:[%lld], BidVolume5:[%lld], BidVolume6:[%lld], BidVolume7:[%lld], BidVolume8:[%lld], BidVolume9:[%lld], BidVolume10:[%lld]", DepthMarketData->TradingDay, DepthMarketData->ExchangeId, DepthMarketData->InstrumentId, DepthMarketData->UpdateTs, DepthMarketData->LastPrice, DepthMarketData->PreSettlementPrice, DepthMarketData->PreClosePrice, DepthMarketData->PreOpenInterest, DepthMarketData->OpenPrice, DepthMarketData->HighestPrice, DepthMarketData->LowestPrice, DepthMarketData->ClosePrice, DepthMarketData->CurrVolume, DepthMarketData->Volume, DepthMarketData->CurrTurnover, DepthMarketData->Turnover, DepthMarketData->OpenInterest, DepthMarketData->SettlementPrice, DepthMarketData->UpperLimitPrice, DepthMarketData->LowerLimitPrice, DepthMarketData->AveragePrice, DepthMarketData->AskPrice1, DepthMarketData->AskPrice2, DepthMarketData->AskPrice3, DepthMarketData->AskPrice4, DepthMarketData->AskPrice5, DepthMarketData->AskPrice6, DepthMarketData->AskPrice7, DepthMarketData->AskPrice8, DepthMarketData->AskPrice9, DepthMarketData->AskPrice10, DepthMarketData->AskVolume1, DepthMarketData->AskVolume2, DepthMarketData->AskVolume3, DepthMarketData->AskVolume4, DepthMarketData->AskVolume5, DepthMarketData->AskVolume6, DepthMarketData->AskVolume7, DepthMarketData->AskVolume8, DepthMarketData->AskVolume9, DepthMarketData->AskVolume10, DepthMarketData->BidPrice1, DepthMarketData->BidPrice2, DepthMarketData->BidPrice3, DepthMarketData->BidPrice4, DepthMarketData->BidPrice5, DepthMarketData->BidPrice6, DepthMarketData->BidPrice7, DepthMarketData->BidPrice8, DepthMarketData->BidPrice9, DepthMarketData->BidPrice10, DepthMarketData->BidVolume1, DepthMarketData->BidVolume2, DepthMarketData->BidVolume3, DepthMarketData->BidVolume4, DepthMarketData->BidVolume5, DepthMarketData->BidVolume6, DepthMarketData->BidVolume7, DepthMarketData->BidVolume8, DepthMarketData->BidVolume9, DepthMarketData->BidVolume10);
	}
	return DataStringBuffer;
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
void RtnBarMarketDataPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RtnBarMarketDataPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (BarMarketData != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, BarMarketDataField::FieldId);
		if (strlen(BarMarketData->TradingDay) >= sizeof(BarMarketData->TradingDay))
		{
			BarMarketData->TradingDay[sizeof(BarMarketData->TradingDay) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::TradingDay, BarMarketData->TradingDay);
		if (strlen(BarMarketData->ExchangeId) >= sizeof(BarMarketData->ExchangeId))
		{
			BarMarketData->ExchangeId[sizeof(BarMarketData->ExchangeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeId, BarMarketData->ExchangeId);
		if (strlen(BarMarketData->InstrumentId) >= sizeof(BarMarketData->InstrumentId))
		{
			BarMarketData->InstrumentId[sizeof(BarMarketData->InstrumentId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::InstrumentId, BarMarketData->InstrumentId);
		StepUtility::WriteString(cursor, Items::BarPreces, static_cast<int>(BarMarketData->BarPreces));
		StepUtility::WriteString(cursor, Items::BarPeriod, BarMarketData->BarPeriod);
		StepUtility::WriteString(cursor, Items::BarTime, BarMarketData->BarTime);
		StepUtility::WriteString(cursor, Items::UpdateTs, BarMarketData->UpdateTs);
		StepUtility::WriteString(cursor, Items::PreSettlementPrice, BarMarketData->PreSettlementPrice);
		StepUtility::WriteString(cursor, Items::PreClosePrice, BarMarketData->PreClosePrice);
		StepUtility::WriteString(cursor, Items::HighestPrice, BarMarketData->HighestPrice);
		StepUtility::WriteString(cursor, Items::LowestPrice, BarMarketData->LowestPrice);
		StepUtility::WriteString(cursor, Items::Open, BarMarketData->Open);
		StepUtility::WriteString(cursor, Items::High, BarMarketData->High);
		StepUtility::WriteString(cursor, Items::Low, BarMarketData->Low);
		StepUtility::WriteString(cursor, Items::Close, BarMarketData->Close);
		StepUtility::WriteString(cursor, Items::CurrVolume, BarMarketData->CurrVolume);
		StepUtility::WriteString(cursor, Items::Volume, BarMarketData->Volume);
		StepUtility::WriteString(cursor, Items::CurrTurnover, BarMarketData->CurrTurnover);
		StepUtility::WriteString(cursor, Items::Turnover, BarMarketData->Turnover);
		StepUtility::WriteString(cursor, Items::OpenInterest, BarMarketData->OpenInterest);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, BarMarketDataField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RtnBarMarketDataPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case BarMarketDataField::FieldId:
			{
				BarMarketData = ObjectPool<BarMarketDataField>::GetInstance().Allocate();
				memset(BarMarketData, 0, sizeof(*BarMarketData));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
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
						case Items::ExchangeId:
						{
							size_t len = value.length() >= sizeof(BarMarketData->ExchangeId) ? sizeof(BarMarketData->ExchangeId) - 1 : value.length();
							memcpy(BarMarketData->ExchangeId, value.c_str(), len);
							break;
						}
						case Items::InstrumentId:
						{
							size_t len = value.length() >= sizeof(BarMarketData->InstrumentId) ? sizeof(BarMarketData->InstrumentId) - 1 : value.length();
							memcpy(BarMarketData->InstrumentId, value.c_str(), len);
							break;
						}
						case Items::BarPreces:
						{
							BarMarketData->BarPreces = static_cast<BarPrecesType>(atoi(value.c_str()));
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
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for BarMarketDataField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RtnBarMarketDataPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(BarMarketDataField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &BarMarketDataField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case BarMarketDataField::FieldId:
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
		offset = AppendDebugString(offset, "BarMarketData:TradingDay:[%s], ExchangeId:[%s], InstrumentId:[%s], BarPreces:[%d], BarPeriod:[%d], BarTime:[%lld], UpdateTs:[%lld], PreSettlementPrice:[%f], PreClosePrice:[%f], HighestPrice:[%f], LowestPrice:[%f], Open:[%f], High:[%f], Low:[%f], Close:[%f], CurrVolume:[%lld], Volume:[%lld], CurrTurnover:[%f], Turnover:[%f], OpenInterest:[%f]", BarMarketData->TradingDay, BarMarketData->ExchangeId, BarMarketData->InstrumentId, static_cast<int>(BarMarketData->BarPreces), BarMarketData->BarPeriod, BarMarketData->BarTime, BarMarketData->UpdateTs, BarMarketData->PreSettlementPrice, BarMarketData->PreClosePrice, BarMarketData->HighestPrice, BarMarketData->LowestPrice, BarMarketData->Open, BarMarketData->High, BarMarketData->Low, BarMarketData->Close, BarMarketData->CurrVolume, BarMarketData->Volume, BarMarketData->CurrTurnover, BarMarketData->Turnover, BarMarketData->OpenInterest);
	}
	return DataStringBuffer;
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
void RtnSessionBeginPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RtnSessionBeginPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (SessionBegin != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, SessionBeginField::FieldId);
		if (strlen(SessionBegin->TradingDay) >= sizeof(SessionBegin->TradingDay))
		{
			SessionBegin->TradingDay[sizeof(SessionBegin->TradingDay) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::TradingDay, SessionBegin->TradingDay);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, SessionBeginField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RtnSessionBeginPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case SessionBeginField::FieldId:
			{
				SessionBegin = ObjectPool<SessionBeginField>::GetInstance().Allocate();
				memset(SessionBegin, 0, sizeof(*SessionBegin));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
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
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for SessionBeginField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RtnSessionBeginPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(SessionBeginField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &SessionBeginField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case SessionBeginField::FieldId:
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
		offset = AppendDebugString(offset, "SessionBegin:TradingDay:[%s]", SessionBegin->TradingDay);
	}
	return DataStringBuffer;
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
void RtnSessionEndPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RtnSessionEndPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (SessionEnd != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, SessionEndField::FieldId);
		if (strlen(SessionEnd->TradingDay) >= sizeof(SessionEnd->TradingDay))
		{
			SessionEnd->TradingDay[sizeof(SessionEnd->TradingDay) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::TradingDay, SessionEnd->TradingDay);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, SessionEndField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RtnSessionEndPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case SessionEndField::FieldId:
			{
				SessionEnd = ObjectPool<SessionEndField>::GetInstance().Allocate();
				memset(SessionEnd, 0, sizeof(*SessionEnd));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
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
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for SessionEndField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RtnSessionEndPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(SessionEndField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &SessionEndField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case SessionEndField::FieldId:
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
		offset = AppendDebugString(offset, "SessionEnd:TradingDay:[%s]", SessionEnd->TradingDay);
	}
	return DataStringBuffer;
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
void RtnMarketDataEndPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RtnMarketDataEndPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (MarketDataEnd != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, MarketDataEndField::FieldId);
		if (strlen(MarketDataEnd->TradingDay) >= sizeof(MarketDataEnd->TradingDay))
		{
			MarketDataEnd->TradingDay[sizeof(MarketDataEnd->TradingDay) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::TradingDay, MarketDataEnd->TradingDay);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, MarketDataEndField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RtnMarketDataEndPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case MarketDataEndField::FieldId:
			{
				MarketDataEnd = ObjectPool<MarketDataEndField>::GetInstance().Allocate();
				memset(MarketDataEnd, 0, sizeof(*MarketDataEnd));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
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
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for MarketDataEndField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RtnMarketDataEndPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(MarketDataEndField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &MarketDataEndField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case MarketDataEndField::FieldId:
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
		offset = AppendDebugString(offset, "MarketDataEnd:TradingDay:[%s]", MarketDataEnd->TradingDay);
	}
	return DataStringBuffer;
}
 
ReqRegisterAccountPackage::ReqRegisterAccountPackage()
	:ReqRegisterAccount(nullptr)
{
}
ReqRegisterAccountPackage::~ReqRegisterAccountPackage()
{
	if (ReqRegisterAccount != nullptr)
	{
		ObjectPool<ReqRegisterAccountField>::GetInstance().Deallocate(ReqRegisterAccount);
		ReqRegisterAccount = nullptr;
	}
}
ReqRegisterAccountPackage* ReqRegisterAccountPackage::Allocate()
{
	return ObjectPool<ReqRegisterAccountPackage>::GetInstance().Allocate();
}
void ReqRegisterAccountPackage::Deallocate()
{
	ObjectPool<ReqRegisterAccountPackage>::GetInstance().Deallocate(this);
}
void ReqRegisterAccountPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int ReqRegisterAccountPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (ReqRegisterAccount != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, ReqRegisterAccountField::FieldId);
		if (strlen(ReqRegisterAccount->AccountId) >= sizeof(ReqRegisterAccount->AccountId))
		{
			ReqRegisterAccount->AccountId[sizeof(ReqRegisterAccount->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, ReqRegisterAccount->AccountId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, ReqRegisterAccountField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool ReqRegisterAccountPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case ReqRegisterAccountField::FieldId:
			{
				ReqRegisterAccount = ObjectPool<ReqRegisterAccountField>::GetInstance().Allocate();
				memset(ReqRegisterAccount, 0, sizeof(*ReqRegisterAccount));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(ReqRegisterAccount->AccountId) ? sizeof(ReqRegisterAccount->AccountId) - 1 : value.length();
							memcpy(ReqRegisterAccount->AccountId, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for ReqRegisterAccountField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqRegisterAccountPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
				return false;
			}
			startIndex = fieldEndIndex;
		}
		else
		{
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For ReqRegisterAccountPackage");
			return false;
		}
	}
	return true;
}
int ReqRegisterAccountPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (ReqRegisterAccount != nullptr)
	{
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(ReqRegisterAccountField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &ReqRegisterAccountField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		memcpy(buff + offset, ReqRegisterAccount, sizeof(ReqRegisterAccountField));
		offset += sizeof(ReqRegisterAccountField);
	}
	return offset;
}
bool ReqRegisterAccountPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case ReqRegisterAccountField::FieldId:
		{
			ReqRegisterAccount = ObjectPool<ReqRegisterAccountField>::GetInstance().Allocate();
			memcpy(ReqRegisterAccount, buff + offset, sizeof(ReqRegisterAccountField));
			offset += sizeof(ReqRegisterAccountField);	
			break;
		}
		default:
			return false;
		}
	}
	return offset == endIndex;
}
const char* ReqRegisterAccountPackage::GetDebugString() const
{
	int offset = 0;
	if (ReqRegisterAccount != nullptr)
	{
		offset = AppendDebugString(offset, "ReqRegisterAccount:AccountId:[%s]", ReqRegisterAccount->AccountId);
	}
	return DataStringBuffer;
}
 
RspRegisterAccountPackage::RspRegisterAccountPackage()
	:RspRegisterAccount(nullptr), RspInfo(nullptr)
{
}
RspRegisterAccountPackage::~RspRegisterAccountPackage()
{
	if (RspRegisterAccount != nullptr)
	{
		ObjectPool<RspRegisterAccountField>::GetInstance().Deallocate(RspRegisterAccount);
		RspRegisterAccount = nullptr;
	}
	if (RspInfo != nullptr)
	{
		ObjectPool<RspInfoField>::GetInstance().Deallocate(RspInfo);
		RspInfo = nullptr;
	}
}
RspRegisterAccountPackage* RspRegisterAccountPackage::Allocate()
{
	return ObjectPool<RspRegisterAccountPackage>::GetInstance().Allocate();
}
void RspRegisterAccountPackage::Deallocate()
{
	ObjectPool<RspRegisterAccountPackage>::GetInstance().Deallocate(this);
}
void RspRegisterAccountPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RspRegisterAccountPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (RspRegisterAccount != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspRegisterAccountField::FieldId);
		if (strlen(RspRegisterAccount->AccountId) >= sizeof(RspRegisterAccount->AccountId))
		{
			RspRegisterAccount->AccountId[sizeof(RspRegisterAccount->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, RspRegisterAccount->AccountId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspRegisterAccountField::FieldId);
	}
	if (RspInfo != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspInfoField::FieldId);
		StepUtility::WriteString(cursor, Items::ErrorId, RspInfo->ErrorId);
		if (strlen(RspInfo->ErrorMsg) >= sizeof(RspInfo->ErrorMsg))
		{
			RspInfo->ErrorMsg[sizeof(RspInfo->ErrorMsg) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ErrorMsg, RspInfo->ErrorMsg);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspInfoField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RspRegisterAccountPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case RspRegisterAccountField::FieldId:
			{
				RspRegisterAccount = ObjectPool<RspRegisterAccountField>::GetInstance().Allocate();
				memset(RspRegisterAccount, 0, sizeof(*RspRegisterAccount));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(RspRegisterAccount->AccountId) ? sizeof(RspRegisterAccount->AccountId) - 1 : value.length();
							memcpy(RspRegisterAccount->AccountId, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspRegisterAccountField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspRegisterAccountPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldId:
			{
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
				memset(RspInfo, 0, sizeof(*RspInfo));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ErrorId:
						{
							RspInfo->ErrorId = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(RspInfo->ErrorMsg) ? sizeof(RspInfo->ErrorMsg) - 1 : value.length();
							memcpy(RspInfo->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspInfoField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspRegisterAccountPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
				return false;
			}
			startIndex = fieldEndIndex;
		}
		else
		{
			WriteLog(LogLevel::Warning, "GetNextFieldZone Failed For RspRegisterAccountPackage");
			return false;
		}
	}
	return true;
}
int RspRegisterAccountPackage::ToXtpStream(char* buff, int size) const
{
	int offset = 0;
	if (RspRegisterAccount != nullptr)
	{
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspRegisterAccountField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspRegisterAccountField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		memcpy(buff + offset, RspRegisterAccount, sizeof(RspRegisterAccountField));
		offset += sizeof(RspRegisterAccountField);
	}
	if (RspInfo != nullptr)
	{
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspInfoField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspInfoField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		memcpy(buff + offset, RspInfo, sizeof(RspInfoField));
		offset += sizeof(RspInfoField);
	}
	return offset;
}
bool RspRegisterAccountPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	while(offset < endIndex)
	{
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case RspRegisterAccountField::FieldId:
		{
			RspRegisterAccount = ObjectPool<RspRegisterAccountField>::GetInstance().Allocate();
			memcpy(RspRegisterAccount, buff + offset, sizeof(RspRegisterAccountField));
			offset += sizeof(RspRegisterAccountField);	
			break;
		}
		case RspInfoField::FieldId:
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
const char* RspRegisterAccountPackage::GetDebugString() const
{
	int offset = 0;
	if (RspRegisterAccount != nullptr)
	{
		offset = AppendDebugString(offset, "RspRegisterAccount:AccountId:[%s]", RspRegisterAccount->AccountId);
	}
	if (RspInfo != nullptr)
	{
		offset = AppendDebugString(offset, "RspInfo:ErrorId:[%d], ErrorMsg:[%s]", RspInfo->ErrorId, RspInfo->ErrorMsg);
	}
	return DataStringBuffer;
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
void ReqAccountLoginPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int ReqAccountLoginPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (ReqAccountLogin != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, ReqAccountLoginField::FieldId);
		if (strlen(ReqAccountLogin->AccountId) >= sizeof(ReqAccountLogin->AccountId))
		{
			ReqAccountLogin->AccountId[sizeof(ReqAccountLogin->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, ReqAccountLogin->AccountId);
		if (strlen(ReqAccountLogin->Password) >= sizeof(ReqAccountLogin->Password))
		{
			ReqAccountLogin->Password[sizeof(ReqAccountLogin->Password) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::Password, ReqAccountLogin->Password);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, ReqAccountLoginField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool ReqAccountLoginPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case ReqAccountLoginField::FieldId:
			{
				ReqAccountLogin = ObjectPool<ReqAccountLoginField>::GetInstance().Allocate();
				memset(ReqAccountLogin, 0, sizeof(*ReqAccountLogin));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(ReqAccountLogin->AccountId) ? sizeof(ReqAccountLogin->AccountId) - 1 : value.length();
							memcpy(ReqAccountLogin->AccountId, value.c_str(), len);
							break;
						}
						case Items::Password:
						{
							size_t len = value.length() >= sizeof(ReqAccountLogin->Password) ? sizeof(ReqAccountLogin->Password) - 1 : value.length();
							memcpy(ReqAccountLogin->Password, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for ReqAccountLoginField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqAccountLoginPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(ReqAccountLoginField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &ReqAccountLoginField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case ReqAccountLoginField::FieldId:
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
		offset = AppendDebugString(offset, "ReqAccountLogin:AccountId:[%s], Password:[%s]", ReqAccountLogin->AccountId, ReqAccountLogin->Password);
	}
	return DataStringBuffer;
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
void RspAccountLoginPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RspAccountLoginPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (RspAccountLogin != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspAccountLoginField::FieldId);
		if (strlen(RspAccountLogin->AccountId) >= sizeof(RspAccountLogin->AccountId))
		{
			RspAccountLogin->AccountId[sizeof(RspAccountLogin->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, RspAccountLogin->AccountId);
		if (strlen(RspAccountLogin->LoginDate) >= sizeof(RspAccountLogin->LoginDate))
		{
			RspAccountLogin->LoginDate[sizeof(RspAccountLogin->LoginDate) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::LoginDate, RspAccountLogin->LoginDate);
		if (strlen(RspAccountLogin->LoginTime) >= sizeof(RspAccountLogin->LoginTime))
		{
			RspAccountLogin->LoginTime[sizeof(RspAccountLogin->LoginTime) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::LoginTime, RspAccountLogin->LoginTime);
		StepUtility::WriteString(cursor, Items::SessionId, RspAccountLogin->SessionId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspAccountLoginField::FieldId);
	}
	if (RspInfo != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspInfoField::FieldId);
		StepUtility::WriteString(cursor, Items::ErrorId, RspInfo->ErrorId);
		if (strlen(RspInfo->ErrorMsg) >= sizeof(RspInfo->ErrorMsg))
		{
			RspInfo->ErrorMsg[sizeof(RspInfo->ErrorMsg) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ErrorMsg, RspInfo->ErrorMsg);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspInfoField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RspAccountLoginPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case RspAccountLoginField::FieldId:
			{
				RspAccountLogin = ObjectPool<RspAccountLoginField>::GetInstance().Allocate();
				memset(RspAccountLogin, 0, sizeof(*RspAccountLogin));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(RspAccountLogin->AccountId) ? sizeof(RspAccountLogin->AccountId) - 1 : value.length();
							memcpy(RspAccountLogin->AccountId, value.c_str(), len);
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
						case Items::SessionId:
						{
							RspAccountLogin->SessionId = atoll(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspAccountLoginField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspAccountLoginPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldId:
			{
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
				memset(RspInfo, 0, sizeof(*RspInfo));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ErrorId:
						{
							RspInfo->ErrorId = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(RspInfo->ErrorMsg) ? sizeof(RspInfo->ErrorMsg) - 1 : value.length();
							memcpy(RspInfo->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspInfoField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspAccountLoginPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspAccountLoginField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspAccountLoginField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		memcpy(buff + offset, RspAccountLogin, sizeof(RspAccountLoginField));
		offset += sizeof(RspAccountLoginField);
	}
	if (RspInfo != nullptr)
	{
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspInfoField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspInfoField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case RspAccountLoginField::FieldId:
		{
			RspAccountLogin = ObjectPool<RspAccountLoginField>::GetInstance().Allocate();
			memcpy(RspAccountLogin, buff + offset, sizeof(RspAccountLoginField));
			offset += sizeof(RspAccountLoginField);	
			break;
		}
		case RspInfoField::FieldId:
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
		offset = AppendDebugString(offset, "RspAccountLogin:AccountId:[%s], LoginDate:[%s], LoginTime:[%s], SessionId:[%lld]", RspAccountLogin->AccountId, RspAccountLogin->LoginDate, RspAccountLogin->LoginTime, RspAccountLogin->SessionId);
	}
	if (RspInfo != nullptr)
	{
		offset = AppendDebugString(offset, "RspInfo:ErrorId:[%d], ErrorMsg:[%s]", RspInfo->ErrorId, RspInfo->ErrorMsg);
	}
	return DataStringBuffer;
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
void ReqAccountLogoutPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int ReqAccountLogoutPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (ReqAccountLogout != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, ReqAccountLogoutField::FieldId);
		if (strlen(ReqAccountLogout->AccountId) >= sizeof(ReqAccountLogout->AccountId))
		{
			ReqAccountLogout->AccountId[sizeof(ReqAccountLogout->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, ReqAccountLogout->AccountId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, ReqAccountLogoutField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool ReqAccountLogoutPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case ReqAccountLogoutField::FieldId:
			{
				ReqAccountLogout = ObjectPool<ReqAccountLogoutField>::GetInstance().Allocate();
				memset(ReqAccountLogout, 0, sizeof(*ReqAccountLogout));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(ReqAccountLogout->AccountId) ? sizeof(ReqAccountLogout->AccountId) - 1 : value.length();
							memcpy(ReqAccountLogout->AccountId, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for ReqAccountLogoutField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqAccountLogoutPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(ReqAccountLogoutField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &ReqAccountLogoutField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case ReqAccountLogoutField::FieldId:
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
		offset = AppendDebugString(offset, "ReqAccountLogout:AccountId:[%s]", ReqAccountLogout->AccountId);
	}
	return DataStringBuffer;
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
void RspAccountLogoutPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RspAccountLogoutPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (RspAccountLogout != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspAccountLogoutField::FieldId);
		if (strlen(RspAccountLogout->AccountId) >= sizeof(RspAccountLogout->AccountId))
		{
			RspAccountLogout->AccountId[sizeof(RspAccountLogout->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, RspAccountLogout->AccountId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspAccountLogoutField::FieldId);
	}
	if (RspInfo != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspInfoField::FieldId);
		StepUtility::WriteString(cursor, Items::ErrorId, RspInfo->ErrorId);
		if (strlen(RspInfo->ErrorMsg) >= sizeof(RspInfo->ErrorMsg))
		{
			RspInfo->ErrorMsg[sizeof(RspInfo->ErrorMsg) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ErrorMsg, RspInfo->ErrorMsg);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspInfoField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RspAccountLogoutPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case RspAccountLogoutField::FieldId:
			{
				RspAccountLogout = ObjectPool<RspAccountLogoutField>::GetInstance().Allocate();
				memset(RspAccountLogout, 0, sizeof(*RspAccountLogout));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(RspAccountLogout->AccountId) ? sizeof(RspAccountLogout->AccountId) - 1 : value.length();
							memcpy(RspAccountLogout->AccountId, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspAccountLogoutField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspAccountLogoutPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldId:
			{
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
				memset(RspInfo, 0, sizeof(*RspInfo));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ErrorId:
						{
							RspInfo->ErrorId = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(RspInfo->ErrorMsg) ? sizeof(RspInfo->ErrorMsg) - 1 : value.length();
							memcpy(RspInfo->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspInfoField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspAccountLogoutPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspAccountLogoutField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspAccountLogoutField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		memcpy(buff + offset, RspAccountLogout, sizeof(RspAccountLogoutField));
		offset += sizeof(RspAccountLogoutField);
	}
	if (RspInfo != nullptr)
	{
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspInfoField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspInfoField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case RspAccountLogoutField::FieldId:
		{
			RspAccountLogout = ObjectPool<RspAccountLogoutField>::GetInstance().Allocate();
			memcpy(RspAccountLogout, buff + offset, sizeof(RspAccountLogoutField));
			offset += sizeof(RspAccountLogoutField);	
			break;
		}
		case RspInfoField::FieldId:
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
		offset = AppendDebugString(offset, "RspAccountLogout:AccountId:[%s]", RspAccountLogout->AccountId);
	}
	if (RspInfo != nullptr)
	{
		offset = AppendDebugString(offset, "RspInfo:ErrorId:[%d], ErrorMsg:[%s]", RspInfo->ErrorId, RspInfo->ErrorMsg);
	}
	return DataStringBuffer;
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
void ReqQryAccountPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int ReqQryAccountPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (ReqQryAccount != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, ReqQryAccountField::FieldId);
		if (strlen(ReqQryAccount->AccountId) >= sizeof(ReqQryAccount->AccountId))
		{
			ReqQryAccount->AccountId[sizeof(ReqQryAccount->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, ReqQryAccount->AccountId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, ReqQryAccountField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool ReqQryAccountPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case ReqQryAccountField::FieldId:
			{
				ReqQryAccount = ObjectPool<ReqQryAccountField>::GetInstance().Allocate();
				memset(ReqQryAccount, 0, sizeof(*ReqQryAccount));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(ReqQryAccount->AccountId) ? sizeof(ReqQryAccount->AccountId) - 1 : value.length();
							memcpy(ReqQryAccount->AccountId, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for ReqQryAccountField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqQryAccountPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(ReqQryAccountField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &ReqQryAccountField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case ReqQryAccountField::FieldId:
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
		offset = AppendDebugString(offset, "ReqQryAccount:AccountId:[%s]", ReqQryAccount->AccountId);
	}
	return DataStringBuffer;
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
void RspQryAccountPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RspQryAccountPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (Account != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, AccountField::FieldId);
		if (strlen(Account->AccountId) >= sizeof(Account->AccountId))
		{
			Account->AccountId[sizeof(Account->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, Account->AccountId);
		StepUtility::WriteString(cursor, Items::AccountType, static_cast<int>(Account->AccountType));
		StepUtility::WriteString(cursor, Items::AccountStatus, static_cast<int>(Account->AccountStatus));
		StepUtility::WriteString(cursor, Items::TradeGroupId, Account->TradeGroupId);
		StepUtility::WriteString(cursor, Items::RiskGroupId, Account->RiskGroupId);
		StepUtility::WriteString(cursor, Items::CommissionGroupId, Account->CommissionGroupId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, AccountField::FieldId);
	}
	if (RspInfo != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspInfoField::FieldId);
		StepUtility::WriteString(cursor, Items::ErrorId, RspInfo->ErrorId);
		if (strlen(RspInfo->ErrorMsg) >= sizeof(RspInfo->ErrorMsg))
		{
			RspInfo->ErrorMsg[sizeof(RspInfo->ErrorMsg) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ErrorMsg, RspInfo->ErrorMsg);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspInfoField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RspQryAccountPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case AccountField::FieldId:
			{
				Account = ObjectPool<AccountField>::GetInstance().Allocate();
				memset(Account, 0, sizeof(*Account));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(Account->AccountId) ? sizeof(Account->AccountId) - 1 : value.length();
							memcpy(Account->AccountId, value.c_str(), len);
							break;
						}
						case Items::AccountType:
						{
							Account->AccountType = static_cast<AccountTypeType>(atoi(value.c_str()));
							break;
						}
						case Items::AccountStatus:
						{
							Account->AccountStatus = static_cast<AccountStatusType>(atoi(value.c_str()));
							break;
						}
						case Items::TradeGroupId:
						{
							Account->TradeGroupId = atoi(value.c_str());
							break;
						}
						case Items::RiskGroupId:
						{
							Account->RiskGroupId = atoi(value.c_str());
							break;
						}
						case Items::CommissionGroupId:
						{
							Account->CommissionGroupId = atoi(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for AccountField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryAccountPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldId:
			{
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
				memset(RspInfo, 0, sizeof(*RspInfo));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ErrorId:
						{
							RspInfo->ErrorId = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(RspInfo->ErrorMsg) ? sizeof(RspInfo->ErrorMsg) - 1 : value.length();
							memcpy(RspInfo->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspInfoField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryAccountPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(AccountField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &AccountField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		memcpy(buff + offset, Account, sizeof(AccountField));
		offset += sizeof(AccountField);
	}
	if (RspInfo != nullptr)
	{
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspInfoField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspInfoField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case AccountField::FieldId:
		{
			Account = ObjectPool<AccountField>::GetInstance().Allocate();
			memcpy(Account, buff + offset, sizeof(AccountField));
			offset += sizeof(AccountField);	
			break;
		}
		case RspInfoField::FieldId:
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
		offset = AppendDebugString(offset, "Account:AccountId:[%s], AccountType:[%d], AccountStatus:[%d], TradeGroupId:[%d], RiskGroupId:[%d], CommissionGroupId:[%d]", Account->AccountId, static_cast<int>(Account->AccountType), static_cast<int>(Account->AccountStatus), Account->TradeGroupId, Account->RiskGroupId, Account->CommissionGroupId);
	}
	if (RspInfo != nullptr)
	{
		offset = AppendDebugString(offset, "RspInfo:ErrorId:[%d], ErrorMsg:[%s]", RspInfo->ErrorId, RspInfo->ErrorMsg);
	}
	return DataStringBuffer;
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
void ReqQryHolderAccountPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int ReqQryHolderAccountPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (ReqQryHolderAccount != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, ReqQryHolderAccountField::FieldId);
		if (strlen(ReqQryHolderAccount->AccountId) >= sizeof(ReqQryHolderAccount->AccountId))
		{
			ReqQryHolderAccount->AccountId[sizeof(ReqQryHolderAccount->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, ReqQryHolderAccount->AccountId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, ReqQryHolderAccountField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool ReqQryHolderAccountPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case ReqQryHolderAccountField::FieldId:
			{
				ReqQryHolderAccount = ObjectPool<ReqQryHolderAccountField>::GetInstance().Allocate();
				memset(ReqQryHolderAccount, 0, sizeof(*ReqQryHolderAccount));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(ReqQryHolderAccount->AccountId) ? sizeof(ReqQryHolderAccount->AccountId) - 1 : value.length();
							memcpy(ReqQryHolderAccount->AccountId, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for ReqQryHolderAccountField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqQryHolderAccountPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(ReqQryHolderAccountField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &ReqQryHolderAccountField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case ReqQryHolderAccountField::FieldId:
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
		offset = AppendDebugString(offset, "ReqQryHolderAccount:AccountId:[%s]", ReqQryHolderAccount->AccountId);
	}
	return DataStringBuffer;
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
void RspQryHolderAccountPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RspQryHolderAccountPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (HolderAccount != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, HolderAccountField::FieldId);
		if (strlen(HolderAccount->ExchangeId) >= sizeof(HolderAccount->ExchangeId))
		{
			HolderAccount->ExchangeId[sizeof(HolderAccount->ExchangeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeId, HolderAccount->ExchangeId);
		if (strlen(HolderAccount->HolderAccountId) >= sizeof(HolderAccount->HolderAccountId))
		{
			HolderAccount->HolderAccountId[sizeof(HolderAccount->HolderAccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::HolderAccountId, HolderAccount->HolderAccountId);
		StepUtility::WriteString(cursor, Items::PrimaryFlag, HolderAccount->PrimaryFlag);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, HolderAccountField::FieldId);
	}
	if (RspInfo != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspInfoField::FieldId);
		StepUtility::WriteString(cursor, Items::ErrorId, RspInfo->ErrorId);
		if (strlen(RspInfo->ErrorMsg) >= sizeof(RspInfo->ErrorMsg))
		{
			RspInfo->ErrorMsg[sizeof(RspInfo->ErrorMsg) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ErrorMsg, RspInfo->ErrorMsg);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspInfoField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RspQryHolderAccountPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case HolderAccountField::FieldId:
			{
				HolderAccount = ObjectPool<HolderAccountField>::GetInstance().Allocate();
				memset(HolderAccount, 0, sizeof(*HolderAccount));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ExchangeId:
						{
							size_t len = value.length() >= sizeof(HolderAccount->ExchangeId) ? sizeof(HolderAccount->ExchangeId) - 1 : value.length();
							memcpy(HolderAccount->ExchangeId, value.c_str(), len);
							break;
						}
						case Items::HolderAccountId:
						{
							size_t len = value.length() >= sizeof(HolderAccount->HolderAccountId) ? sizeof(HolderAccount->HolderAccountId) - 1 : value.length();
							memcpy(HolderAccount->HolderAccountId, value.c_str(), len);
							break;
						}
						case Items::PrimaryFlag:
						{
							HolderAccount->PrimaryFlag = atoi(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for HolderAccountField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryHolderAccountPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldId:
			{
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
				memset(RspInfo, 0, sizeof(*RspInfo));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ErrorId:
						{
							RspInfo->ErrorId = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(RspInfo->ErrorMsg) ? sizeof(RspInfo->ErrorMsg) - 1 : value.length();
							memcpy(RspInfo->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspInfoField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryHolderAccountPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(HolderAccountField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &HolderAccountField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		memcpy(buff + offset, HolderAccount, sizeof(HolderAccountField));
		offset += sizeof(HolderAccountField);
	}
	if (RspInfo != nullptr)
	{
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspInfoField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspInfoField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case HolderAccountField::FieldId:
		{
			HolderAccount = ObjectPool<HolderAccountField>::GetInstance().Allocate();
			memcpy(HolderAccount, buff + offset, sizeof(HolderAccountField));
			offset += sizeof(HolderAccountField);	
			break;
		}
		case RspInfoField::FieldId:
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
		offset = AppendDebugString(offset, "HolderAccount:ExchangeId:[%s], HolderAccountId:[%s], PrimaryFlag:[%d]", HolderAccount->ExchangeId, HolderAccount->HolderAccountId, HolderAccount->PrimaryFlag);
	}
	if (RspInfo != nullptr)
	{
		offset = AppendDebugString(offset, "RspInfo:ErrorId:[%d], ErrorMsg:[%s]", RspInfo->ErrorId, RspInfo->ErrorMsg);
	}
	return DataStringBuffer;
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
void ReqQryCapitalPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int ReqQryCapitalPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (ReqQryCapital != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, ReqQryCapitalField::FieldId);
		if (strlen(ReqQryCapital->AccountId) >= sizeof(ReqQryCapital->AccountId))
		{
			ReqQryCapital->AccountId[sizeof(ReqQryCapital->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, ReqQryCapital->AccountId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, ReqQryCapitalField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool ReqQryCapitalPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case ReqQryCapitalField::FieldId:
			{
				ReqQryCapital = ObjectPool<ReqQryCapitalField>::GetInstance().Allocate();
				memset(ReqQryCapital, 0, sizeof(*ReqQryCapital));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(ReqQryCapital->AccountId) ? sizeof(ReqQryCapital->AccountId) - 1 : value.length();
							memcpy(ReqQryCapital->AccountId, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for ReqQryCapitalField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqQryCapitalPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(ReqQryCapitalField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &ReqQryCapitalField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case ReqQryCapitalField::FieldId:
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
		offset = AppendDebugString(offset, "ReqQryCapital:AccountId:[%s]", ReqQryCapital->AccountId);
	}
	return DataStringBuffer;
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
void RspQryCapitalPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RspQryCapitalPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (Capital != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, CapitalField::FieldId);
		if (strlen(Capital->TradingDay) >= sizeof(Capital->TradingDay))
		{
			Capital->TradingDay[sizeof(Capital->TradingDay) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::TradingDay, Capital->TradingDay);
		if (strlen(Capital->AccountId) >= sizeof(Capital->AccountId))
		{
			Capital->AccountId[sizeof(Capital->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, Capital->AccountId);
		StepUtility::WriteString(cursor, Items::AccountType, static_cast<int>(Capital->AccountType));
		StepUtility::WriteString(cursor, Items::Balance, Capital->Balance);
		StepUtility::WriteString(cursor, Items::PreBalance, Capital->PreBalance);
		StepUtility::WriteString(cursor, Items::Available, Capital->Available);
		StepUtility::WriteString(cursor, Items::MarketValue, Capital->MarketValue);
		StepUtility::WriteString(cursor, Items::CashIn, Capital->CashIn);
		StepUtility::WriteString(cursor, Items::CashOut, Capital->CashOut);
		StepUtility::WriteString(cursor, Items::Margin, Capital->Margin);
		StepUtility::WriteString(cursor, Items::Commission, Capital->Commission);
		StepUtility::WriteString(cursor, Items::FrozenCash, Capital->FrozenCash);
		StepUtility::WriteString(cursor, Items::FrozenMargin, Capital->FrozenMargin);
		StepUtility::WriteString(cursor, Items::FrozenCommission, Capital->FrozenCommission);
		StepUtility::WriteString(cursor, Items::CloseProfitByDate, Capital->CloseProfitByDate);
		StepUtility::WriteString(cursor, Items::CloseProfitByTrade, Capital->CloseProfitByTrade);
		StepUtility::WriteString(cursor, Items::PositionProfitByDate, Capital->PositionProfitByDate);
		StepUtility::WriteString(cursor, Items::PositionProfitByTrade, Capital->PositionProfitByTrade);
		StepUtility::WriteString(cursor, Items::Deposit, Capital->Deposit);
		StepUtility::WriteString(cursor, Items::Withdraw, Capital->Withdraw);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, CapitalField::FieldId);
	}
	if (RspInfo != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspInfoField::FieldId);
		StepUtility::WriteString(cursor, Items::ErrorId, RspInfo->ErrorId);
		if (strlen(RspInfo->ErrorMsg) >= sizeof(RspInfo->ErrorMsg))
		{
			RspInfo->ErrorMsg[sizeof(RspInfo->ErrorMsg) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ErrorMsg, RspInfo->ErrorMsg);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspInfoField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RspQryCapitalPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case CapitalField::FieldId:
			{
				Capital = ObjectPool<CapitalField>::GetInstance().Allocate();
				memset(Capital, 0, sizeof(*Capital));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
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
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(Capital->AccountId) ? sizeof(Capital->AccountId) - 1 : value.length();
							memcpy(Capital->AccountId, value.c_str(), len);
							break;
						}
						case Items::AccountType:
						{
							Capital->AccountType = static_cast<AccountTypeType>(atoi(value.c_str()));
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
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for CapitalField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryCapitalPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldId:
			{
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
				memset(RspInfo, 0, sizeof(*RspInfo));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ErrorId:
						{
							RspInfo->ErrorId = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(RspInfo->ErrorMsg) ? sizeof(RspInfo->ErrorMsg) - 1 : value.length();
							memcpy(RspInfo->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspInfoField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryCapitalPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(CapitalField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &CapitalField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		memcpy(buff + offset, Capital, sizeof(CapitalField));
		offset += sizeof(CapitalField);
	}
	if (RspInfo != nullptr)
	{
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspInfoField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspInfoField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case CapitalField::FieldId:
		{
			Capital = ObjectPool<CapitalField>::GetInstance().Allocate();
			memcpy(Capital, buff + offset, sizeof(CapitalField));
			offset += sizeof(CapitalField);	
			break;
		}
		case RspInfoField::FieldId:
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
		offset = AppendDebugString(offset, "Capital:TradingDay:[%s], AccountId:[%s], AccountType:[%d], Balance:[%f], PreBalance:[%f], Available:[%f], MarketValue:[%f], CashIn:[%f], CashOut:[%f], Margin:[%f], Commission:[%f], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f], CloseProfitByDate:[%f], CloseProfitByTrade:[%f], PositionProfitByDate:[%f], PositionProfitByTrade:[%f], Deposit:[%f], Withdraw:[%f]", Capital->TradingDay, Capital->AccountId, static_cast<int>(Capital->AccountType), Capital->Balance, Capital->PreBalance, Capital->Available, Capital->MarketValue, Capital->CashIn, Capital->CashOut, Capital->Margin, Capital->Commission, Capital->FrozenCash, Capital->FrozenMargin, Capital->FrozenCommission, Capital->CloseProfitByDate, Capital->CloseProfitByTrade, Capital->PositionProfitByDate, Capital->PositionProfitByTrade, Capital->Deposit, Capital->Withdraw);
	}
	if (RspInfo != nullptr)
	{
		offset = AppendDebugString(offset, "RspInfo:ErrorId:[%d], ErrorMsg:[%s]", RspInfo->ErrorId, RspInfo->ErrorMsg);
	}
	return DataStringBuffer;
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
void ReqQryPositionPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int ReqQryPositionPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (ReqQryPosition != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, ReqQryPositionField::FieldId);
		if (strlen(ReqQryPosition->AccountId) >= sizeof(ReqQryPosition->AccountId))
		{
			ReqQryPosition->AccountId[sizeof(ReqQryPosition->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, ReqQryPosition->AccountId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, ReqQryPositionField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool ReqQryPositionPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case ReqQryPositionField::FieldId:
			{
				ReqQryPosition = ObjectPool<ReqQryPositionField>::GetInstance().Allocate();
				memset(ReqQryPosition, 0, sizeof(*ReqQryPosition));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(ReqQryPosition->AccountId) ? sizeof(ReqQryPosition->AccountId) - 1 : value.length();
							memcpy(ReqQryPosition->AccountId, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for ReqQryPositionField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqQryPositionPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(ReqQryPositionField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &ReqQryPositionField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case ReqQryPositionField::FieldId:
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
		offset = AppendDebugString(offset, "ReqQryPosition:AccountId:[%s]", ReqQryPosition->AccountId);
	}
	return DataStringBuffer;
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
void RspQryPositionPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RspQryPositionPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (Position != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, PositionField::FieldId);
		if (strlen(Position->TradingDay) >= sizeof(Position->TradingDay))
		{
			Position->TradingDay[sizeof(Position->TradingDay) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::TradingDay, Position->TradingDay);
		if (strlen(Position->AccountId) >= sizeof(Position->AccountId))
		{
			Position->AccountId[sizeof(Position->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, Position->AccountId);
		StepUtility::WriteString(cursor, Items::AccountType, static_cast<int>(Position->AccountType));
		if (strlen(Position->ExchangeId) >= sizeof(Position->ExchangeId))
		{
			Position->ExchangeId[sizeof(Position->ExchangeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeId, Position->ExchangeId);
		if (strlen(Position->InstrumentId) >= sizeof(Position->InstrumentId))
		{
			Position->InstrumentId[sizeof(Position->InstrumentId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::InstrumentId, Position->InstrumentId);
		StepUtility::WriteString(cursor, Items::ProductClass, static_cast<int>(Position->ProductClass));
		StepUtility::WriteString(cursor, Items::PosiDirection, static_cast<int>(Position->PosiDirection));
		StepUtility::WriteString(cursor, Items::TotalPosition, Position->TotalPosition);
		StepUtility::WriteString(cursor, Items::PositionFrozen, Position->PositionFrozen);
		StepUtility::WriteString(cursor, Items::TodayPosition, Position->TodayPosition);
		StepUtility::WriteString(cursor, Items::MarketValue, Position->MarketValue);
		StepUtility::WriteString(cursor, Items::CashIn, Position->CashIn);
		StepUtility::WriteString(cursor, Items::CashOut, Position->CashOut);
		StepUtility::WriteString(cursor, Items::Margin, Position->Margin);
		StepUtility::WriteString(cursor, Items::Commission, Position->Commission);
		StepUtility::WriteString(cursor, Items::VolumeMultiple, Position->VolumeMultiple);
		StepUtility::WriteString(cursor, Items::CloseProfitByDate, Position->CloseProfitByDate);
		StepUtility::WriteString(cursor, Items::CloseProfitByTrade, Position->CloseProfitByTrade);
		StepUtility::WriteString(cursor, Items::PositionProfitByDate, Position->PositionProfitByDate);
		StepUtility::WriteString(cursor, Items::PositionProfitByTrade, Position->PositionProfitByTrade);
		StepUtility::WriteString(cursor, Items::LastPrice, Position->LastPrice);
		StepUtility::WriteString(cursor, Items::PreSettlementPrice, Position->PreSettlementPrice);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, PositionField::FieldId);
	}
	if (RspInfo != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspInfoField::FieldId);
		StepUtility::WriteString(cursor, Items::ErrorId, RspInfo->ErrorId);
		if (strlen(RspInfo->ErrorMsg) >= sizeof(RspInfo->ErrorMsg))
		{
			RspInfo->ErrorMsg[sizeof(RspInfo->ErrorMsg) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ErrorMsg, RspInfo->ErrorMsg);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspInfoField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RspQryPositionPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case PositionField::FieldId:
			{
				Position = ObjectPool<PositionField>::GetInstance().Allocate();
				memset(Position, 0, sizeof(*Position));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
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
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(Position->AccountId) ? sizeof(Position->AccountId) - 1 : value.length();
							memcpy(Position->AccountId, value.c_str(), len);
							break;
						}
						case Items::AccountType:
						{
							Position->AccountType = static_cast<AccountTypeType>(atoi(value.c_str()));
							break;
						}
						case Items::ExchangeId:
						{
							size_t len = value.length() >= sizeof(Position->ExchangeId) ? sizeof(Position->ExchangeId) - 1 : value.length();
							memcpy(Position->ExchangeId, value.c_str(), len);
							break;
						}
						case Items::InstrumentId:
						{
							size_t len = value.length() >= sizeof(Position->InstrumentId) ? sizeof(Position->InstrumentId) - 1 : value.length();
							memcpy(Position->InstrumentId, value.c_str(), len);
							break;
						}
						case Items::ProductClass:
						{
							Position->ProductClass = static_cast<ProductClassType>(atoi(value.c_str()));
							break;
						}
						case Items::PosiDirection:
						{
							Position->PosiDirection = static_cast<PosiDirectionType>(atoi(value.c_str()));
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
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for PositionField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryPositionPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldId:
			{
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
				memset(RspInfo, 0, sizeof(*RspInfo));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ErrorId:
						{
							RspInfo->ErrorId = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(RspInfo->ErrorMsg) ? sizeof(RspInfo->ErrorMsg) - 1 : value.length();
							memcpy(RspInfo->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspInfoField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryPositionPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(PositionField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &PositionField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		memcpy(buff + offset, Position, sizeof(PositionField));
		offset += sizeof(PositionField);
	}
	if (RspInfo != nullptr)
	{
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspInfoField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspInfoField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case PositionField::FieldId:
		{
			Position = ObjectPool<PositionField>::GetInstance().Allocate();
			memcpy(Position, buff + offset, sizeof(PositionField));
			offset += sizeof(PositionField);	
			break;
		}
		case RspInfoField::FieldId:
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
		offset = AppendDebugString(offset, "Position:TradingDay:[%s], AccountId:[%s], AccountType:[%d], ExchangeId:[%s], InstrumentId:[%s], ProductClass:[%d], PosiDirection:[%d], TotalPosition:[%lld], PositionFrozen:[%lld], TodayPosition:[%lld], MarketValue:[%f], CashIn:[%f], CashOut:[%f], Margin:[%f], Commission:[%f], VolumeMultiple:[%d], CloseProfitByDate:[%f], CloseProfitByTrade:[%f], PositionProfitByDate:[%f], PositionProfitByTrade:[%f], LastPrice:[%f], PreSettlementPrice:[%f]", Position->TradingDay, Position->AccountId, static_cast<int>(Position->AccountType), Position->ExchangeId, Position->InstrumentId, static_cast<int>(Position->ProductClass), static_cast<int>(Position->PosiDirection), Position->TotalPosition, Position->PositionFrozen, Position->TodayPosition, Position->MarketValue, Position->CashIn, Position->CashOut, Position->Margin, Position->Commission, Position->VolumeMultiple, Position->CloseProfitByDate, Position->CloseProfitByTrade, Position->PositionProfitByDate, Position->PositionProfitByTrade, Position->LastPrice, Position->PreSettlementPrice);
	}
	if (RspInfo != nullptr)
	{
		offset = AppendDebugString(offset, "RspInfo:ErrorId:[%d], ErrorMsg:[%s]", RspInfo->ErrorId, RspInfo->ErrorMsg);
	}
	return DataStringBuffer;
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
void ReqQryOrderPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int ReqQryOrderPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (ReqQryOrder != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, ReqQryOrderField::FieldId);
		if (strlen(ReqQryOrder->AccountId) >= sizeof(ReqQryOrder->AccountId))
		{
			ReqQryOrder->AccountId[sizeof(ReqQryOrder->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, ReqQryOrder->AccountId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, ReqQryOrderField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool ReqQryOrderPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case ReqQryOrderField::FieldId:
			{
				ReqQryOrder = ObjectPool<ReqQryOrderField>::GetInstance().Allocate();
				memset(ReqQryOrder, 0, sizeof(*ReqQryOrder));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(ReqQryOrder->AccountId) ? sizeof(ReqQryOrder->AccountId) - 1 : value.length();
							memcpy(ReqQryOrder->AccountId, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for ReqQryOrderField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqQryOrderPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(ReqQryOrderField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &ReqQryOrderField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case ReqQryOrderField::FieldId:
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
		offset = AppendDebugString(offset, "ReqQryOrder:AccountId:[%s]", ReqQryOrder->AccountId);
	}
	return DataStringBuffer;
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
void RspQryOrderPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RspQryOrderPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (Order != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, OrderField::FieldId);
		if (strlen(Order->TradingDay) >= sizeof(Order->TradingDay))
		{
			Order->TradingDay[sizeof(Order->TradingDay) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::TradingDay, Order->TradingDay);
		if (strlen(Order->AccountId) >= sizeof(Order->AccountId))
		{
			Order->AccountId[sizeof(Order->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, Order->AccountId);
		if (strlen(Order->ExchangeId) >= sizeof(Order->ExchangeId))
		{
			Order->ExchangeId[sizeof(Order->ExchangeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeId, Order->ExchangeId);
		if (strlen(Order->InstrumentId) >= sizeof(Order->InstrumentId))
		{
			Order->InstrumentId[sizeof(Order->InstrumentId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::InstrumentId, Order->InstrumentId);
		StepUtility::WriteString(cursor, Items::ProductClass, static_cast<int>(Order->ProductClass));
		StepUtility::WriteString(cursor, Items::OrderId, Order->OrderId);
		if (strlen(Order->OrderSysId) >= sizeof(Order->OrderSysId))
		{
			Order->OrderSysId[sizeof(Order->OrderSysId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::OrderSysId, Order->OrderSysId);
		StepUtility::WriteString(cursor, Items::Direction, static_cast<int>(Order->Direction));
		StepUtility::WriteString(cursor, Items::OffsetFlag, static_cast<int>(Order->OffsetFlag));
		StepUtility::WriteString(cursor, Items::OrderPriceType, static_cast<int>(Order->OrderPriceType));
		StepUtility::WriteString(cursor, Items::Price, Order->Price);
		StepUtility::WriteString(cursor, Items::Volume, Order->Volume);
		StepUtility::WriteString(cursor, Items::VolumeTotal, Order->VolumeTotal);
		StepUtility::WriteString(cursor, Items::VolumeTraded, Order->VolumeTraded);
		StepUtility::WriteString(cursor, Items::VolumeMultiple, Order->VolumeMultiple);
		StepUtility::WriteString(cursor, Items::OrderStatus, static_cast<int>(Order->OrderStatus));
		if (strlen(Order->OrderDate) >= sizeof(Order->OrderDate))
		{
			Order->OrderDate[sizeof(Order->OrderDate) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::OrderDate, Order->OrderDate);
		if (strlen(Order->OrderTime) >= sizeof(Order->OrderTime))
		{
			Order->OrderTime[sizeof(Order->OrderTime) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::OrderTime, Order->OrderTime);
		if (strlen(Order->CancelDate) >= sizeof(Order->CancelDate))
		{
			Order->CancelDate[sizeof(Order->CancelDate) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::CancelDate, Order->CancelDate);
		if (strlen(Order->CancelTime) >= sizeof(Order->CancelTime))
		{
			Order->CancelTime[sizeof(Order->CancelTime) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::CancelTime, Order->CancelTime);
		StepUtility::WriteString(cursor, Items::SessionId, Order->SessionId);
		StepUtility::WriteString(cursor, Items::ClientOrderId, Order->ClientOrderId);
		StepUtility::WriteString(cursor, Items::RequestId, Order->RequestId);
		StepUtility::WriteString(cursor, Items::FrozenCash, Order->FrozenCash);
		StepUtility::WriteString(cursor, Items::FrozenMargin, Order->FrozenMargin);
		StepUtility::WriteString(cursor, Items::FrozenCommission, Order->FrozenCommission);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, OrderField::FieldId);
	}
	if (RspInfo != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspInfoField::FieldId);
		StepUtility::WriteString(cursor, Items::ErrorId, RspInfo->ErrorId);
		if (strlen(RspInfo->ErrorMsg) >= sizeof(RspInfo->ErrorMsg))
		{
			RspInfo->ErrorMsg[sizeof(RspInfo->ErrorMsg) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ErrorMsg, RspInfo->ErrorMsg);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspInfoField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RspQryOrderPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case OrderField::FieldId:
			{
				Order = ObjectPool<OrderField>::GetInstance().Allocate();
				memset(Order, 0, sizeof(*Order));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
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
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(Order->AccountId) ? sizeof(Order->AccountId) - 1 : value.length();
							memcpy(Order->AccountId, value.c_str(), len);
							break;
						}
						case Items::ExchangeId:
						{
							size_t len = value.length() >= sizeof(Order->ExchangeId) ? sizeof(Order->ExchangeId) - 1 : value.length();
							memcpy(Order->ExchangeId, value.c_str(), len);
							break;
						}
						case Items::InstrumentId:
						{
							size_t len = value.length() >= sizeof(Order->InstrumentId) ? sizeof(Order->InstrumentId) - 1 : value.length();
							memcpy(Order->InstrumentId, value.c_str(), len);
							break;
						}
						case Items::ProductClass:
						{
							Order->ProductClass = static_cast<ProductClassType>(atoi(value.c_str()));
							break;
						}
						case Items::OrderId:
						{
							Order->OrderId = atoi(value.c_str());
							break;
						}
						case Items::OrderSysId:
						{
							size_t len = value.length() >= sizeof(Order->OrderSysId) ? sizeof(Order->OrderSysId) - 1 : value.length();
							memcpy(Order->OrderSysId, value.c_str(), len);
							break;
						}
						case Items::Direction:
						{
							Order->Direction = static_cast<DirectionType>(atoi(value.c_str()));
							break;
						}
						case Items::OffsetFlag:
						{
							Order->OffsetFlag = static_cast<OffsetFlagType>(atoi(value.c_str()));
							break;
						}
						case Items::OrderPriceType:
						{
							Order->OrderPriceType = static_cast<OrderPriceTypeType>(atoi(value.c_str()));
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
							Order->OrderStatus = static_cast<OrderStatusType>(atoi(value.c_str()));
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
						case Items::SessionId:
						{
							Order->SessionId = atoll(value.c_str());
							break;
						}
						case Items::ClientOrderId:
						{
							Order->ClientOrderId = atoi(value.c_str());
							break;
						}
						case Items::RequestId:
						{
							Order->RequestId = atoi(value.c_str());
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
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for OrderField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryOrderPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldId:
			{
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
				memset(RspInfo, 0, sizeof(*RspInfo));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ErrorId:
						{
							RspInfo->ErrorId = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(RspInfo->ErrorMsg) ? sizeof(RspInfo->ErrorMsg) - 1 : value.length();
							memcpy(RspInfo->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspInfoField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryOrderPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(OrderField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &OrderField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		memcpy(buff + offset, Order, sizeof(OrderField));
		offset += sizeof(OrderField);
	}
	if (RspInfo != nullptr)
	{
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspInfoField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspInfoField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case OrderField::FieldId:
		{
			Order = ObjectPool<OrderField>::GetInstance().Allocate();
			memcpy(Order, buff + offset, sizeof(OrderField));
			offset += sizeof(OrderField);	
			break;
		}
		case RspInfoField::FieldId:
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
		offset = AppendDebugString(offset, "Order:TradingDay:[%s], AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], ProductClass:[%d], OrderId:[%d], OrderSysId:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], VolumeTotal:[%lld], VolumeTraded:[%lld], VolumeMultiple:[%d], OrderStatus:[%d], OrderDate:[%s], OrderTime:[%s], CancelDate:[%s], CancelTime:[%s], SessionId:[%lld], ClientOrderId:[%d], RequestId:[%d], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f]", Order->TradingDay, Order->AccountId, Order->ExchangeId, Order->InstrumentId, static_cast<int>(Order->ProductClass), Order->OrderId, Order->OrderSysId, static_cast<int>(Order->Direction), static_cast<int>(Order->OffsetFlag), static_cast<int>(Order->OrderPriceType), Order->Price, Order->Volume, Order->VolumeTotal, Order->VolumeTraded, Order->VolumeMultiple, static_cast<int>(Order->OrderStatus), Order->OrderDate, Order->OrderTime, Order->CancelDate, Order->CancelTime, Order->SessionId, Order->ClientOrderId, Order->RequestId, Order->FrozenCash, Order->FrozenMargin, Order->FrozenCommission);
	}
	if (RspInfo != nullptr)
	{
		offset = AppendDebugString(offset, "RspInfo:ErrorId:[%d], ErrorMsg:[%s]", RspInfo->ErrorId, RspInfo->ErrorMsg);
	}
	return DataStringBuffer;
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
void ReqQryTradePackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int ReqQryTradePackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (ReqQryTrade != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, ReqQryTradeField::FieldId);
		if (strlen(ReqQryTrade->AccountId) >= sizeof(ReqQryTrade->AccountId))
		{
			ReqQryTrade->AccountId[sizeof(ReqQryTrade->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, ReqQryTrade->AccountId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, ReqQryTradeField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool ReqQryTradePackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case ReqQryTradeField::FieldId:
			{
				ReqQryTrade = ObjectPool<ReqQryTradeField>::GetInstance().Allocate();
				memset(ReqQryTrade, 0, sizeof(*ReqQryTrade));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(ReqQryTrade->AccountId) ? sizeof(ReqQryTrade->AccountId) - 1 : value.length();
							memcpy(ReqQryTrade->AccountId, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for ReqQryTradeField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqQryTradePackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(ReqQryTradeField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &ReqQryTradeField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case ReqQryTradeField::FieldId:
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
		offset = AppendDebugString(offset, "ReqQryTrade:AccountId:[%s]", ReqQryTrade->AccountId);
	}
	return DataStringBuffer;
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
void RspQryTradePackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RspQryTradePackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (Trade != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, TradeField::FieldId);
		if (strlen(Trade->TradingDay) >= sizeof(Trade->TradingDay))
		{
			Trade->TradingDay[sizeof(Trade->TradingDay) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::TradingDay, Trade->TradingDay);
		if (strlen(Trade->AccountId) >= sizeof(Trade->AccountId))
		{
			Trade->AccountId[sizeof(Trade->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, Trade->AccountId);
		if (strlen(Trade->ExchangeId) >= sizeof(Trade->ExchangeId))
		{
			Trade->ExchangeId[sizeof(Trade->ExchangeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeId, Trade->ExchangeId);
		if (strlen(Trade->InstrumentId) >= sizeof(Trade->InstrumentId))
		{
			Trade->InstrumentId[sizeof(Trade->InstrumentId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::InstrumentId, Trade->InstrumentId);
		StepUtility::WriteString(cursor, Items::ProductClass, static_cast<int>(Trade->ProductClass));
		StepUtility::WriteString(cursor, Items::OrderId, Trade->OrderId);
		if (strlen(Trade->OrderSysId) >= sizeof(Trade->OrderSysId))
		{
			Trade->OrderSysId[sizeof(Trade->OrderSysId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::OrderSysId, Trade->OrderSysId);
		if (strlen(Trade->TradeId) >= sizeof(Trade->TradeId))
		{
			Trade->TradeId[sizeof(Trade->TradeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::TradeId, Trade->TradeId);
		StepUtility::WriteString(cursor, Items::Direction, static_cast<int>(Trade->Direction));
		StepUtility::WriteString(cursor, Items::OffsetFlag, static_cast<int>(Trade->OffsetFlag));
		StepUtility::WriteString(cursor, Items::Price, Trade->Price);
		StepUtility::WriteString(cursor, Items::Volume, Trade->Volume);
		StepUtility::WriteString(cursor, Items::VolumeMultiple, Trade->VolumeMultiple);
		StepUtility::WriteString(cursor, Items::TradeAmount, Trade->TradeAmount);
		StepUtility::WriteString(cursor, Items::Commission, Trade->Commission);
		if (strlen(Trade->TradeDate) >= sizeof(Trade->TradeDate))
		{
			Trade->TradeDate[sizeof(Trade->TradeDate) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::TradeDate, Trade->TradeDate);
		if (strlen(Trade->TradeTime) >= sizeof(Trade->TradeTime))
		{
			Trade->TradeTime[sizeof(Trade->TradeTime) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::TradeTime, Trade->TradeTime);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, TradeField::FieldId);
	}
	if (RspInfo != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspInfoField::FieldId);
		StepUtility::WriteString(cursor, Items::ErrorId, RspInfo->ErrorId);
		if (strlen(RspInfo->ErrorMsg) >= sizeof(RspInfo->ErrorMsg))
		{
			RspInfo->ErrorMsg[sizeof(RspInfo->ErrorMsg) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ErrorMsg, RspInfo->ErrorMsg);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspInfoField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RspQryTradePackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case TradeField::FieldId:
			{
				Trade = ObjectPool<TradeField>::GetInstance().Allocate();
				memset(Trade, 0, sizeof(*Trade));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
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
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(Trade->AccountId) ? sizeof(Trade->AccountId) - 1 : value.length();
							memcpy(Trade->AccountId, value.c_str(), len);
							break;
						}
						case Items::ExchangeId:
						{
							size_t len = value.length() >= sizeof(Trade->ExchangeId) ? sizeof(Trade->ExchangeId) - 1 : value.length();
							memcpy(Trade->ExchangeId, value.c_str(), len);
							break;
						}
						case Items::InstrumentId:
						{
							size_t len = value.length() >= sizeof(Trade->InstrumentId) ? sizeof(Trade->InstrumentId) - 1 : value.length();
							memcpy(Trade->InstrumentId, value.c_str(), len);
							break;
						}
						case Items::ProductClass:
						{
							Trade->ProductClass = static_cast<ProductClassType>(atoi(value.c_str()));
							break;
						}
						case Items::OrderId:
						{
							Trade->OrderId = atoi(value.c_str());
							break;
						}
						case Items::OrderSysId:
						{
							size_t len = value.length() >= sizeof(Trade->OrderSysId) ? sizeof(Trade->OrderSysId) - 1 : value.length();
							memcpy(Trade->OrderSysId, value.c_str(), len);
							break;
						}
						case Items::TradeId:
						{
							size_t len = value.length() >= sizeof(Trade->TradeId) ? sizeof(Trade->TradeId) - 1 : value.length();
							memcpy(Trade->TradeId, value.c_str(), len);
							break;
						}
						case Items::Direction:
						{
							Trade->Direction = static_cast<DirectionType>(atoi(value.c_str()));
							break;
						}
						case Items::OffsetFlag:
						{
							Trade->OffsetFlag = static_cast<OffsetFlagType>(atoi(value.c_str()));
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
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for TradeField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryTradePackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldId:
			{
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
				memset(RspInfo, 0, sizeof(*RspInfo));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ErrorId:
						{
							RspInfo->ErrorId = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(RspInfo->ErrorMsg) ? sizeof(RspInfo->ErrorMsg) - 1 : value.length();
							memcpy(RspInfo->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspInfoField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryTradePackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(TradeField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &TradeField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		memcpy(buff + offset, Trade, sizeof(TradeField));
		offset += sizeof(TradeField);
	}
	if (RspInfo != nullptr)
	{
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspInfoField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspInfoField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case TradeField::FieldId:
		{
			Trade = ObjectPool<TradeField>::GetInstance().Allocate();
			memcpy(Trade, buff + offset, sizeof(TradeField));
			offset += sizeof(TradeField);	
			break;
		}
		case RspInfoField::FieldId:
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
		offset = AppendDebugString(offset, "Trade:TradingDay:[%s], AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], ProductClass:[%d], OrderId:[%d], OrderSysId:[%s], TradeId:[%s], Direction:[%d], OffsetFlag:[%d], Price:[%f], Volume:[%lld], VolumeMultiple:[%d], TradeAmount:[%f], Commission:[%f], TradeDate:[%s], TradeTime:[%s]", Trade->TradingDay, Trade->AccountId, Trade->ExchangeId, Trade->InstrumentId, static_cast<int>(Trade->ProductClass), Trade->OrderId, Trade->OrderSysId, Trade->TradeId, static_cast<int>(Trade->Direction), static_cast<int>(Trade->OffsetFlag), Trade->Price, Trade->Volume, Trade->VolumeMultiple, Trade->TradeAmount, Trade->Commission, Trade->TradeDate, Trade->TradeTime);
	}
	if (RspInfo != nullptr)
	{
		offset = AppendDebugString(offset, "RspInfo:ErrorId:[%d], ErrorMsg:[%s]", RspInfo->ErrorId, RspInfo->ErrorMsg);
	}
	return DataStringBuffer;
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
void ReqQryInstrumentPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int ReqQryInstrumentPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (ReqQryInstrument != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, ReqQryInstrumentField::FieldId);
		if (strlen(ReqQryInstrument->ExchangeId) >= sizeof(ReqQryInstrument->ExchangeId))
		{
			ReqQryInstrument->ExchangeId[sizeof(ReqQryInstrument->ExchangeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeId, ReqQryInstrument->ExchangeId);
		if (strlen(ReqQryInstrument->InstrumentId) >= sizeof(ReqQryInstrument->InstrumentId))
		{
			ReqQryInstrument->InstrumentId[sizeof(ReqQryInstrument->InstrumentId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::InstrumentId, ReqQryInstrument->InstrumentId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, ReqQryInstrumentField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool ReqQryInstrumentPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case ReqQryInstrumentField::FieldId:
			{
				ReqQryInstrument = ObjectPool<ReqQryInstrumentField>::GetInstance().Allocate();
				memset(ReqQryInstrument, 0, sizeof(*ReqQryInstrument));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ExchangeId:
						{
							size_t len = value.length() >= sizeof(ReqQryInstrument->ExchangeId) ? sizeof(ReqQryInstrument->ExchangeId) - 1 : value.length();
							memcpy(ReqQryInstrument->ExchangeId, value.c_str(), len);
							break;
						}
						case Items::InstrumentId:
						{
							size_t len = value.length() >= sizeof(ReqQryInstrument->InstrumentId) ? sizeof(ReqQryInstrument->InstrumentId) - 1 : value.length();
							memcpy(ReqQryInstrument->InstrumentId, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for ReqQryInstrumentField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqQryInstrumentPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(ReqQryInstrumentField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &ReqQryInstrumentField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case ReqQryInstrumentField::FieldId:
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
		offset = AppendDebugString(offset, "ReqQryInstrument:ExchangeId:[%s], InstrumentId:[%s]", ReqQryInstrument->ExchangeId, ReqQryInstrument->InstrumentId);
	}
	return DataStringBuffer;
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
void RspQryInstrumentPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RspQryInstrumentPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (Instrument != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, InstrumentField::FieldId);
		if (strlen(Instrument->ExchangeId) >= sizeof(Instrument->ExchangeId))
		{
			Instrument->ExchangeId[sizeof(Instrument->ExchangeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeId, Instrument->ExchangeId);
		if (strlen(Instrument->InstrumentId) >= sizeof(Instrument->InstrumentId))
		{
			Instrument->InstrumentId[sizeof(Instrument->InstrumentId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::InstrumentId, Instrument->InstrumentId);
		if (strlen(Instrument->ExchangeInstId) >= sizeof(Instrument->ExchangeInstId))
		{
			Instrument->ExchangeInstId[sizeof(Instrument->ExchangeInstId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeInstId, Instrument->ExchangeInstId);
		if (strlen(Instrument->InstrumentName) >= sizeof(Instrument->InstrumentName))
		{
			Instrument->InstrumentName[sizeof(Instrument->InstrumentName) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::InstrumentName, Instrument->InstrumentName);
		if (strlen(Instrument->ProductId) >= sizeof(Instrument->ProductId))
		{
			Instrument->ProductId[sizeof(Instrument->ProductId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ProductId, Instrument->ProductId);
		StepUtility::WriteString(cursor, Items::ProductClass, static_cast<int>(Instrument->ProductClass));
		StepUtility::WriteString(cursor, Items::VolumeMultiple, Instrument->VolumeMultiple);
		StepUtility::WriteString(cursor, Items::PriceTick, Instrument->PriceTick);
		StepUtility::WriteString(cursor, Items::MaxMarketOrderVolume, Instrument->MaxMarketOrderVolume);
		StepUtility::WriteString(cursor, Items::MinMarketOrderVolume, Instrument->MinMarketOrderVolume);
		StepUtility::WriteString(cursor, Items::MaxLimitOrderVolume, Instrument->MaxLimitOrderVolume);
		StepUtility::WriteString(cursor, Items::MinLimitOrderVolume, Instrument->MinLimitOrderVolume);
		if (strlen(Instrument->SessionName) >= sizeof(Instrument->SessionName))
		{
			Instrument->SessionName[sizeof(Instrument->SessionName) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::SessionName, Instrument->SessionName);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, InstrumentField::FieldId);
	}
	if (RspInfo != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspInfoField::FieldId);
		StepUtility::WriteString(cursor, Items::ErrorId, RspInfo->ErrorId);
		if (strlen(RspInfo->ErrorMsg) >= sizeof(RspInfo->ErrorMsg))
		{
			RspInfo->ErrorMsg[sizeof(RspInfo->ErrorMsg) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ErrorMsg, RspInfo->ErrorMsg);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspInfoField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RspQryInstrumentPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case InstrumentField::FieldId:
			{
				Instrument = ObjectPool<InstrumentField>::GetInstance().Allocate();
				memset(Instrument, 0, sizeof(*Instrument));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ExchangeId:
						{
							size_t len = value.length() >= sizeof(Instrument->ExchangeId) ? sizeof(Instrument->ExchangeId) - 1 : value.length();
							memcpy(Instrument->ExchangeId, value.c_str(), len);
							break;
						}
						case Items::InstrumentId:
						{
							size_t len = value.length() >= sizeof(Instrument->InstrumentId) ? sizeof(Instrument->InstrumentId) - 1 : value.length();
							memcpy(Instrument->InstrumentId, value.c_str(), len);
							break;
						}
						case Items::ExchangeInstId:
						{
							size_t len = value.length() >= sizeof(Instrument->ExchangeInstId) ? sizeof(Instrument->ExchangeInstId) - 1 : value.length();
							memcpy(Instrument->ExchangeInstId, value.c_str(), len);
							break;
						}
						case Items::InstrumentName:
						{
							size_t len = value.length() >= sizeof(Instrument->InstrumentName) ? sizeof(Instrument->InstrumentName) - 1 : value.length();
							memcpy(Instrument->InstrumentName, value.c_str(), len);
							break;
						}
						case Items::ProductId:
						{
							size_t len = value.length() >= sizeof(Instrument->ProductId) ? sizeof(Instrument->ProductId) - 1 : value.length();
							memcpy(Instrument->ProductId, value.c_str(), len);
							break;
						}
						case Items::ProductClass:
						{
							Instrument->ProductClass = static_cast<ProductClassType>(atoi(value.c_str()));
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
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for InstrumentField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryInstrumentPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldId:
			{
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
				memset(RspInfo, 0, sizeof(*RspInfo));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ErrorId:
						{
							RspInfo->ErrorId = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(RspInfo->ErrorMsg) ? sizeof(RspInfo->ErrorMsg) - 1 : value.length();
							memcpy(RspInfo->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspInfoField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryInstrumentPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(InstrumentField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &InstrumentField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		memcpy(buff + offset, Instrument, sizeof(InstrumentField));
		offset += sizeof(InstrumentField);
	}
	if (RspInfo != nullptr)
	{
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspInfoField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspInfoField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case InstrumentField::FieldId:
		{
			Instrument = ObjectPool<InstrumentField>::GetInstance().Allocate();
			memcpy(Instrument, buff + offset, sizeof(InstrumentField));
			offset += sizeof(InstrumentField);	
			break;
		}
		case RspInfoField::FieldId:
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
		offset = AppendDebugString(offset, "Instrument:ExchangeId:[%s], InstrumentId:[%s], ExchangeInstId:[%s], InstrumentName:[%s], ProductId:[%s], ProductClass:[%d], VolumeMultiple:[%d], PriceTick:[%f], MaxMarketOrderVolume:[%lld], MinMarketOrderVolume:[%lld], MaxLimitOrderVolume:[%lld], MinLimitOrderVolume:[%lld], SessionName:[%s]", Instrument->ExchangeId, Instrument->InstrumentId, Instrument->ExchangeInstId, Instrument->InstrumentName, Instrument->ProductId, static_cast<int>(Instrument->ProductClass), Instrument->VolumeMultiple, Instrument->PriceTick, Instrument->MaxMarketOrderVolume, Instrument->MinMarketOrderVolume, Instrument->MaxLimitOrderVolume, Instrument->MinLimitOrderVolume, Instrument->SessionName);
	}
	if (RspInfo != nullptr)
	{
		offset = AppendDebugString(offset, "RspInfo:ErrorId:[%d], ErrorMsg:[%s]", RspInfo->ErrorId, RspInfo->ErrorMsg);
	}
	return DataStringBuffer;
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
void ReqQryOptionInstrumentPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int ReqQryOptionInstrumentPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (ReqQryOptionInstrument != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, ReqQryOptionInstrumentField::FieldId);
		if (strlen(ReqQryOptionInstrument->ExchangeId) >= sizeof(ReqQryOptionInstrument->ExchangeId))
		{
			ReqQryOptionInstrument->ExchangeId[sizeof(ReqQryOptionInstrument->ExchangeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeId, ReqQryOptionInstrument->ExchangeId);
		if (strlen(ReqQryOptionInstrument->InstrumentId) >= sizeof(ReqQryOptionInstrument->InstrumentId))
		{
			ReqQryOptionInstrument->InstrumentId[sizeof(ReqQryOptionInstrument->InstrumentId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::InstrumentId, ReqQryOptionInstrument->InstrumentId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, ReqQryOptionInstrumentField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool ReqQryOptionInstrumentPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case ReqQryOptionInstrumentField::FieldId:
			{
				ReqQryOptionInstrument = ObjectPool<ReqQryOptionInstrumentField>::GetInstance().Allocate();
				memset(ReqQryOptionInstrument, 0, sizeof(*ReqQryOptionInstrument));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ExchangeId:
						{
							size_t len = value.length() >= sizeof(ReqQryOptionInstrument->ExchangeId) ? sizeof(ReqQryOptionInstrument->ExchangeId) - 1 : value.length();
							memcpy(ReqQryOptionInstrument->ExchangeId, value.c_str(), len);
							break;
						}
						case Items::InstrumentId:
						{
							size_t len = value.length() >= sizeof(ReqQryOptionInstrument->InstrumentId) ? sizeof(ReqQryOptionInstrument->InstrumentId) - 1 : value.length();
							memcpy(ReqQryOptionInstrument->InstrumentId, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for ReqQryOptionInstrumentField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqQryOptionInstrumentPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(ReqQryOptionInstrumentField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &ReqQryOptionInstrumentField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case ReqQryOptionInstrumentField::FieldId:
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
		offset = AppendDebugString(offset, "ReqQryOptionInstrument:ExchangeId:[%s], InstrumentId:[%s]", ReqQryOptionInstrument->ExchangeId, ReqQryOptionInstrument->InstrumentId);
	}
	return DataStringBuffer;
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
void RspQryOptionInstrumentPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RspQryOptionInstrumentPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (OptionInstrument != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, OptionInstrumentField::FieldId);
		if (strlen(OptionInstrument->ExchangeId) >= sizeof(OptionInstrument->ExchangeId))
		{
			OptionInstrument->ExchangeId[sizeof(OptionInstrument->ExchangeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeId, OptionInstrument->ExchangeId);
		if (strlen(OptionInstrument->InstrumentId) >= sizeof(OptionInstrument->InstrumentId))
		{
			OptionInstrument->InstrumentId[sizeof(OptionInstrument->InstrumentId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::InstrumentId, OptionInstrument->InstrumentId);
		if (strlen(OptionInstrument->ExchangeInstId) >= sizeof(OptionInstrument->ExchangeInstId))
		{
			OptionInstrument->ExchangeInstId[sizeof(OptionInstrument->ExchangeInstId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeInstId, OptionInstrument->ExchangeInstId);
		if (strlen(OptionInstrument->InstrumentName) >= sizeof(OptionInstrument->InstrumentName))
		{
			OptionInstrument->InstrumentName[sizeof(OptionInstrument->InstrumentName) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::InstrumentName, OptionInstrument->InstrumentName);
		StepUtility::WriteString(cursor, Items::VolumeMultiple, OptionInstrument->VolumeMultiple);
		StepUtility::WriteString(cursor, Items::OptionType, static_cast<int>(OptionInstrument->OptionType));
		if (strlen(OptionInstrument->UnderlyingInstrumentId) >= sizeof(OptionInstrument->UnderlyingInstrumentId))
		{
			OptionInstrument->UnderlyingInstrumentId[sizeof(OptionInstrument->UnderlyingInstrumentId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::UnderlyingInstrumentId, OptionInstrument->UnderlyingInstrumentId);
		StepUtility::WriteString(cursor, Items::ExecutePrice, OptionInstrument->ExecutePrice);
		StepUtility::WriteString(cursor, Items::UnitMargin, OptionInstrument->UnitMargin);
		StepUtility::WriteString(cursor, Items::PriceTick, OptionInstrument->PriceTick);
		StepUtility::WriteString(cursor, Items::MaxLimitOrderVolume, OptionInstrument->MaxLimitOrderVolume);
		StepUtility::WriteString(cursor, Items::MaxMarketOrderVolume, OptionInstrument->MaxMarketOrderVolume);
		if (strlen(OptionInstrument->ExpiringDate) >= sizeof(OptionInstrument->ExpiringDate))
		{
			OptionInstrument->ExpiringDate[sizeof(OptionInstrument->ExpiringDate) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExpiringDate, OptionInstrument->ExpiringDate);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, OptionInstrumentField::FieldId);
	}
	if (RspInfo != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspInfoField::FieldId);
		StepUtility::WriteString(cursor, Items::ErrorId, RspInfo->ErrorId);
		if (strlen(RspInfo->ErrorMsg) >= sizeof(RspInfo->ErrorMsg))
		{
			RspInfo->ErrorMsg[sizeof(RspInfo->ErrorMsg) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ErrorMsg, RspInfo->ErrorMsg);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspInfoField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RspQryOptionInstrumentPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case OptionInstrumentField::FieldId:
			{
				OptionInstrument = ObjectPool<OptionInstrumentField>::GetInstance().Allocate();
				memset(OptionInstrument, 0, sizeof(*OptionInstrument));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ExchangeId:
						{
							size_t len = value.length() >= sizeof(OptionInstrument->ExchangeId) ? sizeof(OptionInstrument->ExchangeId) - 1 : value.length();
							memcpy(OptionInstrument->ExchangeId, value.c_str(), len);
							break;
						}
						case Items::InstrumentId:
						{
							size_t len = value.length() >= sizeof(OptionInstrument->InstrumentId) ? sizeof(OptionInstrument->InstrumentId) - 1 : value.length();
							memcpy(OptionInstrument->InstrumentId, value.c_str(), len);
							break;
						}
						case Items::ExchangeInstId:
						{
							size_t len = value.length() >= sizeof(OptionInstrument->ExchangeInstId) ? sizeof(OptionInstrument->ExchangeInstId) - 1 : value.length();
							memcpy(OptionInstrument->ExchangeInstId, value.c_str(), len);
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
							OptionInstrument->OptionType = static_cast<OptionTypeType>(atoi(value.c_str()));
							break;
						}
						case Items::UnderlyingInstrumentId:
						{
							size_t len = value.length() >= sizeof(OptionInstrument->UnderlyingInstrumentId) ? sizeof(OptionInstrument->UnderlyingInstrumentId) - 1 : value.length();
							memcpy(OptionInstrument->UnderlyingInstrumentId, value.c_str(), len);
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
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for OptionInstrumentField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryOptionInstrumentPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldId:
			{
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
				memset(RspInfo, 0, sizeof(*RspInfo));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ErrorId:
						{
							RspInfo->ErrorId = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(RspInfo->ErrorMsg) ? sizeof(RspInfo->ErrorMsg) - 1 : value.length();
							memcpy(RspInfo->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspInfoField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryOptionInstrumentPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(OptionInstrumentField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &OptionInstrumentField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		memcpy(buff + offset, OptionInstrument, sizeof(OptionInstrumentField));
		offset += sizeof(OptionInstrumentField);
	}
	if (RspInfo != nullptr)
	{
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspInfoField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspInfoField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case OptionInstrumentField::FieldId:
		{
			OptionInstrument = ObjectPool<OptionInstrumentField>::GetInstance().Allocate();
			memcpy(OptionInstrument, buff + offset, sizeof(OptionInstrumentField));
			offset += sizeof(OptionInstrumentField);	
			break;
		}
		case RspInfoField::FieldId:
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
		offset = AppendDebugString(offset, "OptionInstrument:ExchangeId:[%s], InstrumentId:[%s], ExchangeInstId:[%s], InstrumentName:[%s], VolumeMultiple:[%d], OptionType:[%d], UnderlyingInstrumentId:[%s], ExecutePrice:[%f], UnitMargin:[%f], PriceTick:[%f], MaxLimitOrderVolume:[%lld], MaxMarketOrderVolume:[%lld], ExpiringDate:[%s]", OptionInstrument->ExchangeId, OptionInstrument->InstrumentId, OptionInstrument->ExchangeInstId, OptionInstrument->InstrumentName, OptionInstrument->VolumeMultiple, static_cast<int>(OptionInstrument->OptionType), OptionInstrument->UnderlyingInstrumentId, OptionInstrument->ExecutePrice, OptionInstrument->UnitMargin, OptionInstrument->PriceTick, OptionInstrument->MaxLimitOrderVolume, OptionInstrument->MaxMarketOrderVolume, OptionInstrument->ExpiringDate);
	}
	if (RspInfo != nullptr)
	{
		offset = AppendDebugString(offset, "RspInfo:ErrorId:[%d], ErrorMsg:[%s]", RspInfo->ErrorId, RspInfo->ErrorMsg);
	}
	return DataStringBuffer;
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
void ReqQryCommissionRatePackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int ReqQryCommissionRatePackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (ReqQryCommissionRate != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, ReqQryCommissionRateField::FieldId);
		if (strlen(ReqQryCommissionRate->AccountId) >= sizeof(ReqQryCommissionRate->AccountId))
		{
			ReqQryCommissionRate->AccountId[sizeof(ReqQryCommissionRate->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, ReqQryCommissionRate->AccountId);
		if (strlen(ReqQryCommissionRate->ExchangeId) >= sizeof(ReqQryCommissionRate->ExchangeId))
		{
			ReqQryCommissionRate->ExchangeId[sizeof(ReqQryCommissionRate->ExchangeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeId, ReqQryCommissionRate->ExchangeId);
		StepUtility::WriteString(cursor, Items::ProductClass, static_cast<int>(ReqQryCommissionRate->ProductClass));
		StepUtility::WriteHexString(cursor, Items::FieldEnd, ReqQryCommissionRateField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool ReqQryCommissionRatePackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case ReqQryCommissionRateField::FieldId:
			{
				ReqQryCommissionRate = ObjectPool<ReqQryCommissionRateField>::GetInstance().Allocate();
				memset(ReqQryCommissionRate, 0, sizeof(*ReqQryCommissionRate));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(ReqQryCommissionRate->AccountId) ? sizeof(ReqQryCommissionRate->AccountId) - 1 : value.length();
							memcpy(ReqQryCommissionRate->AccountId, value.c_str(), len);
							break;
						}
						case Items::ExchangeId:
						{
							size_t len = value.length() >= sizeof(ReqQryCommissionRate->ExchangeId) ? sizeof(ReqQryCommissionRate->ExchangeId) - 1 : value.length();
							memcpy(ReqQryCommissionRate->ExchangeId, value.c_str(), len);
							break;
						}
						case Items::ProductClass:
						{
							ReqQryCommissionRate->ProductClass = static_cast<ProductClassType>(atoi(value.c_str()));
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for ReqQryCommissionRateField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqQryCommissionRatePackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(ReqQryCommissionRateField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &ReqQryCommissionRateField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case ReqQryCommissionRateField::FieldId:
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
		offset = AppendDebugString(offset, "ReqQryCommissionRate:AccountId:[%s], ExchangeId:[%s], ProductClass:[%d]", ReqQryCommissionRate->AccountId, ReqQryCommissionRate->ExchangeId, static_cast<int>(ReqQryCommissionRate->ProductClass));
	}
	return DataStringBuffer;
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
void RspQryCommissionRatePackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RspQryCommissionRatePackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (CommissionRate != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, CommissionRateField::FieldId);
		if (strlen(CommissionRate->AccountId) >= sizeof(CommissionRate->AccountId))
		{
			CommissionRate->AccountId[sizeof(CommissionRate->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, CommissionRate->AccountId);
		if (strlen(CommissionRate->ExchangeId) >= sizeof(CommissionRate->ExchangeId))
		{
			CommissionRate->ExchangeId[sizeof(CommissionRate->ExchangeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeId, CommissionRate->ExchangeId);
		StepUtility::WriteString(cursor, Items::ProductClass, static_cast<int>(CommissionRate->ProductClass));
		StepUtility::WriteString(cursor, Items::OpenBuyByMoney, CommissionRate->OpenBuyByMoney);
		StepUtility::WriteString(cursor, Items::OpenSellByMoney, CommissionRate->OpenSellByMoney);
		StepUtility::WriteString(cursor, Items::CloseBuyByMoney, CommissionRate->CloseBuyByMoney);
		StepUtility::WriteString(cursor, Items::CloseSellByMoney, CommissionRate->CloseSellByMoney);
		StepUtility::WriteString(cursor, Items::OpenBuyByVolume, CommissionRate->OpenBuyByVolume);
		StepUtility::WriteString(cursor, Items::OpenSellByVolume, CommissionRate->OpenSellByVolume);
		StepUtility::WriteString(cursor, Items::CloseBuyByVolume, CommissionRate->CloseBuyByVolume);
		StepUtility::WriteString(cursor, Items::CloseSellByVolume, CommissionRate->CloseSellByVolume);
		StepUtility::WriteString(cursor, Items::MinCommission, CommissionRate->MinCommission);
		StepUtility::WriteString(cursor, Items::MaxCommission, CommissionRate->MaxCommission);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, CommissionRateField::FieldId);
	}
	if (RspInfo != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspInfoField::FieldId);
		StepUtility::WriteString(cursor, Items::ErrorId, RspInfo->ErrorId);
		if (strlen(RspInfo->ErrorMsg) >= sizeof(RspInfo->ErrorMsg))
		{
			RspInfo->ErrorMsg[sizeof(RspInfo->ErrorMsg) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ErrorMsg, RspInfo->ErrorMsg);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspInfoField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RspQryCommissionRatePackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case CommissionRateField::FieldId:
			{
				CommissionRate = ObjectPool<CommissionRateField>::GetInstance().Allocate();
				memset(CommissionRate, 0, sizeof(*CommissionRate));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(CommissionRate->AccountId) ? sizeof(CommissionRate->AccountId) - 1 : value.length();
							memcpy(CommissionRate->AccountId, value.c_str(), len);
							break;
						}
						case Items::ExchangeId:
						{
							size_t len = value.length() >= sizeof(CommissionRate->ExchangeId) ? sizeof(CommissionRate->ExchangeId) - 1 : value.length();
							memcpy(CommissionRate->ExchangeId, value.c_str(), len);
							break;
						}
						case Items::ProductClass:
						{
							CommissionRate->ProductClass = static_cast<ProductClassType>(atoi(value.c_str()));
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
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for CommissionRateField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryCommissionRatePackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldId:
			{
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
				memset(RspInfo, 0, sizeof(*RspInfo));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ErrorId:
						{
							RspInfo->ErrorId = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(RspInfo->ErrorMsg) ? sizeof(RspInfo->ErrorMsg) - 1 : value.length();
							memcpy(RspInfo->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspInfoField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryCommissionRatePackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(CommissionRateField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &CommissionRateField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		memcpy(buff + offset, CommissionRate, sizeof(CommissionRateField));
		offset += sizeof(CommissionRateField);
	}
	if (RspInfo != nullptr)
	{
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspInfoField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspInfoField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case CommissionRateField::FieldId:
		{
			CommissionRate = ObjectPool<CommissionRateField>::GetInstance().Allocate();
			memcpy(CommissionRate, buff + offset, sizeof(CommissionRateField));
			offset += sizeof(CommissionRateField);	
			break;
		}
		case RspInfoField::FieldId:
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
		offset = AppendDebugString(offset, "CommissionRate:AccountId:[%s], ExchangeId:[%s], ProductClass:[%d], OpenBuyByMoney:[%f], OpenSellByMoney:[%f], CloseBuyByMoney:[%f], CloseSellByMoney:[%f], OpenBuyByVolume:[%f], OpenSellByVolume:[%f], CloseBuyByVolume:[%f], CloseSellByVolume:[%f], MinCommission:[%f], MaxCommission:[%f]", CommissionRate->AccountId, CommissionRate->ExchangeId, static_cast<int>(CommissionRate->ProductClass), CommissionRate->OpenBuyByMoney, CommissionRate->OpenSellByMoney, CommissionRate->CloseBuyByMoney, CommissionRate->CloseSellByMoney, CommissionRate->OpenBuyByVolume, CommissionRate->OpenSellByVolume, CommissionRate->CloseBuyByVolume, CommissionRate->CloseSellByVolume, CommissionRate->MinCommission, CommissionRate->MaxCommission);
	}
	if (RspInfo != nullptr)
	{
		offset = AppendDebugString(offset, "RspInfo:ErrorId:[%d], ErrorMsg:[%s]", RspInfo->ErrorId, RspInfo->ErrorMsg);
	}
	return DataStringBuffer;
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
void ReqQryMoneyTransferPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int ReqQryMoneyTransferPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (ReqQryMoneyTransfer != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, ReqQryMoneyTransferField::FieldId);
		if (strlen(ReqQryMoneyTransfer->AccountId) >= sizeof(ReqQryMoneyTransfer->AccountId))
		{
			ReqQryMoneyTransfer->AccountId[sizeof(ReqQryMoneyTransfer->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, ReqQryMoneyTransfer->AccountId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, ReqQryMoneyTransferField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool ReqQryMoneyTransferPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case ReqQryMoneyTransferField::FieldId:
			{
				ReqQryMoneyTransfer = ObjectPool<ReqQryMoneyTransferField>::GetInstance().Allocate();
				memset(ReqQryMoneyTransfer, 0, sizeof(*ReqQryMoneyTransfer));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(ReqQryMoneyTransfer->AccountId) ? sizeof(ReqQryMoneyTransfer->AccountId) - 1 : value.length();
							memcpy(ReqQryMoneyTransfer->AccountId, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for ReqQryMoneyTransferField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqQryMoneyTransferPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(ReqQryMoneyTransferField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &ReqQryMoneyTransferField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case ReqQryMoneyTransferField::FieldId:
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
		offset = AppendDebugString(offset, "ReqQryMoneyTransfer:AccountId:[%s]", ReqQryMoneyTransfer->AccountId);
	}
	return DataStringBuffer;
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
void RspQryMoneyTransferPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RspQryMoneyTransferPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (MoneyTransfer != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, MoneyTransferField::FieldId);
		if (strlen(MoneyTransfer->TradingDay) >= sizeof(MoneyTransfer->TradingDay))
		{
			MoneyTransfer->TradingDay[sizeof(MoneyTransfer->TradingDay) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::TradingDay, MoneyTransfer->TradingDay);
		if (strlen(MoneyTransfer->AccountId) >= sizeof(MoneyTransfer->AccountId))
		{
			MoneyTransfer->AccountId[sizeof(MoneyTransfer->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, MoneyTransfer->AccountId);
		StepUtility::WriteString(cursor, Items::MoneyTransferId, MoneyTransfer->MoneyTransferId);
		StepUtility::WriteString(cursor, Items::AccountType, static_cast<int>(MoneyTransfer->AccountType));
		StepUtility::WriteString(cursor, Items::TransferDirection, static_cast<int>(MoneyTransfer->TransferDirection));
		StepUtility::WriteString(cursor, Items::TransferAmount, MoneyTransfer->TransferAmount);
		if (strlen(MoneyTransfer->InfoMessage) >= sizeof(MoneyTransfer->InfoMessage))
		{
			MoneyTransfer->InfoMessage[sizeof(MoneyTransfer->InfoMessage) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::InfoMessage, MoneyTransfer->InfoMessage);
		if (strlen(MoneyTransfer->UserId) >= sizeof(MoneyTransfer->UserId))
		{
			MoneyTransfer->UserId[sizeof(MoneyTransfer->UserId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::UserId, MoneyTransfer->UserId);
		if (strlen(MoneyTransfer->TransferDate) >= sizeof(MoneyTransfer->TransferDate))
		{
			MoneyTransfer->TransferDate[sizeof(MoneyTransfer->TransferDate) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::TransferDate, MoneyTransfer->TransferDate);
		if (strlen(MoneyTransfer->TransferTime) >= sizeof(MoneyTransfer->TransferTime))
		{
			MoneyTransfer->TransferTime[sizeof(MoneyTransfer->TransferTime) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::TransferTime, MoneyTransfer->TransferTime);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, MoneyTransferField::FieldId);
	}
	if (RspInfo != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspInfoField::FieldId);
		StepUtility::WriteString(cursor, Items::ErrorId, RspInfo->ErrorId);
		if (strlen(RspInfo->ErrorMsg) >= sizeof(RspInfo->ErrorMsg))
		{
			RspInfo->ErrorMsg[sizeof(RspInfo->ErrorMsg) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ErrorMsg, RspInfo->ErrorMsg);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspInfoField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RspQryMoneyTransferPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case MoneyTransferField::FieldId:
			{
				MoneyTransfer = ObjectPool<MoneyTransferField>::GetInstance().Allocate();
				memset(MoneyTransfer, 0, sizeof(*MoneyTransfer));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
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
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(MoneyTransfer->AccountId) ? sizeof(MoneyTransfer->AccountId) - 1 : value.length();
							memcpy(MoneyTransfer->AccountId, value.c_str(), len);
							break;
						}
						case Items::MoneyTransferId:
						{
							MoneyTransfer->MoneyTransferId = atoi(value.c_str());
							break;
						}
						case Items::AccountType:
						{
							MoneyTransfer->AccountType = static_cast<AccountTypeType>(atoi(value.c_str()));
							break;
						}
						case Items::TransferDirection:
						{
							MoneyTransfer->TransferDirection = static_cast<TransferDirectionType>(atoi(value.c_str()));
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
						case Items::UserId:
						{
							size_t len = value.length() >= sizeof(MoneyTransfer->UserId) ? sizeof(MoneyTransfer->UserId) - 1 : value.length();
							memcpy(MoneyTransfer->UserId, value.c_str(), len);
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
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for MoneyTransferField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryMoneyTransferPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldId:
			{
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
				memset(RspInfo, 0, sizeof(*RspInfo));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ErrorId:
						{
							RspInfo->ErrorId = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(RspInfo->ErrorMsg) ? sizeof(RspInfo->ErrorMsg) - 1 : value.length();
							memcpy(RspInfo->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspInfoField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspQryMoneyTransferPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(MoneyTransferField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &MoneyTransferField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		memcpy(buff + offset, MoneyTransfer, sizeof(MoneyTransferField));
		offset += sizeof(MoneyTransferField);
	}
	if (RspInfo != nullptr)
	{
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspInfoField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspInfoField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case MoneyTransferField::FieldId:
		{
			MoneyTransfer = ObjectPool<MoneyTransferField>::GetInstance().Allocate();
			memcpy(MoneyTransfer, buff + offset, sizeof(MoneyTransferField));
			offset += sizeof(MoneyTransferField);	
			break;
		}
		case RspInfoField::FieldId:
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
		offset = AppendDebugString(offset, "MoneyTransfer:TradingDay:[%s], AccountId:[%s], MoneyTransferId:[%d], AccountType:[%d], TransferDirection:[%d], TransferAmount:[%f], InfoMessage:[%s], UserId:[%s], TransferDate:[%s], TransferTime:[%s]", MoneyTransfer->TradingDay, MoneyTransfer->AccountId, MoneyTransfer->MoneyTransferId, static_cast<int>(MoneyTransfer->AccountType), static_cast<int>(MoneyTransfer->TransferDirection), MoneyTransfer->TransferAmount, MoneyTransfer->InfoMessage, MoneyTransfer->UserId, MoneyTransfer->TransferDate, MoneyTransfer->TransferTime);
	}
	if (RspInfo != nullptr)
	{
		offset = AppendDebugString(offset, "RspInfo:ErrorId:[%d], ErrorMsg:[%s]", RspInfo->ErrorId, RspInfo->ErrorMsg);
	}
	return DataStringBuffer;
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
void ReqInsertOrderPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int ReqInsertOrderPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (ReqInsertOrder != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, ReqInsertOrderField::FieldId);
		if (strlen(ReqInsertOrder->AccountId) >= sizeof(ReqInsertOrder->AccountId))
		{
			ReqInsertOrder->AccountId[sizeof(ReqInsertOrder->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, ReqInsertOrder->AccountId);
		if (strlen(ReqInsertOrder->ExchangeId) >= sizeof(ReqInsertOrder->ExchangeId))
		{
			ReqInsertOrder->ExchangeId[sizeof(ReqInsertOrder->ExchangeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeId, ReqInsertOrder->ExchangeId);
		if (strlen(ReqInsertOrder->InstrumentId) >= sizeof(ReqInsertOrder->InstrumentId))
		{
			ReqInsertOrder->InstrumentId[sizeof(ReqInsertOrder->InstrumentId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::InstrumentId, ReqInsertOrder->InstrumentId);
		StepUtility::WriteString(cursor, Items::Direction, static_cast<int>(ReqInsertOrder->Direction));
		StepUtility::WriteString(cursor, Items::OffsetFlag, static_cast<int>(ReqInsertOrder->OffsetFlag));
		StepUtility::WriteString(cursor, Items::OrderPriceType, static_cast<int>(ReqInsertOrder->OrderPriceType));
		StepUtility::WriteString(cursor, Items::Price, ReqInsertOrder->Price);
		StepUtility::WriteString(cursor, Items::Volume, ReqInsertOrder->Volume);
		StepUtility::WriteString(cursor, Items::ClientOrderId, ReqInsertOrder->ClientOrderId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, ReqInsertOrderField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool ReqInsertOrderPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case ReqInsertOrderField::FieldId:
			{
				ReqInsertOrder = ObjectPool<ReqInsertOrderField>::GetInstance().Allocate();
				memset(ReqInsertOrder, 0, sizeof(*ReqInsertOrder));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(ReqInsertOrder->AccountId) ? sizeof(ReqInsertOrder->AccountId) - 1 : value.length();
							memcpy(ReqInsertOrder->AccountId, value.c_str(), len);
							break;
						}
						case Items::ExchangeId:
						{
							size_t len = value.length() >= sizeof(ReqInsertOrder->ExchangeId) ? sizeof(ReqInsertOrder->ExchangeId) - 1 : value.length();
							memcpy(ReqInsertOrder->ExchangeId, value.c_str(), len);
							break;
						}
						case Items::InstrumentId:
						{
							size_t len = value.length() >= sizeof(ReqInsertOrder->InstrumentId) ? sizeof(ReqInsertOrder->InstrumentId) - 1 : value.length();
							memcpy(ReqInsertOrder->InstrumentId, value.c_str(), len);
							break;
						}
						case Items::Direction:
						{
							ReqInsertOrder->Direction = static_cast<DirectionType>(atoi(value.c_str()));
							break;
						}
						case Items::OffsetFlag:
						{
							ReqInsertOrder->OffsetFlag = static_cast<OffsetFlagType>(atoi(value.c_str()));
							break;
						}
						case Items::OrderPriceType:
						{
							ReqInsertOrder->OrderPriceType = static_cast<OrderPriceTypeType>(atoi(value.c_str()));
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
						case Items::ClientOrderId:
						{
							ReqInsertOrder->ClientOrderId = atoi(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for ReqInsertOrderField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqInsertOrderPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(ReqInsertOrderField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &ReqInsertOrderField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case ReqInsertOrderField::FieldId:
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
		offset = AppendDebugString(offset, "ReqInsertOrder:AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], ClientOrderId:[%d]", ReqInsertOrder->AccountId, ReqInsertOrder->ExchangeId, ReqInsertOrder->InstrumentId, static_cast<int>(ReqInsertOrder->Direction), static_cast<int>(ReqInsertOrder->OffsetFlag), static_cast<int>(ReqInsertOrder->OrderPriceType), ReqInsertOrder->Price, ReqInsertOrder->Volume, ReqInsertOrder->ClientOrderId);
	}
	return DataStringBuffer;
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
void RspInsertOrderPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RspInsertOrderPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (ReqInsertOrder != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, ReqInsertOrderField::FieldId);
		if (strlen(ReqInsertOrder->AccountId) >= sizeof(ReqInsertOrder->AccountId))
		{
			ReqInsertOrder->AccountId[sizeof(ReqInsertOrder->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, ReqInsertOrder->AccountId);
		if (strlen(ReqInsertOrder->ExchangeId) >= sizeof(ReqInsertOrder->ExchangeId))
		{
			ReqInsertOrder->ExchangeId[sizeof(ReqInsertOrder->ExchangeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeId, ReqInsertOrder->ExchangeId);
		if (strlen(ReqInsertOrder->InstrumentId) >= sizeof(ReqInsertOrder->InstrumentId))
		{
			ReqInsertOrder->InstrumentId[sizeof(ReqInsertOrder->InstrumentId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::InstrumentId, ReqInsertOrder->InstrumentId);
		StepUtility::WriteString(cursor, Items::Direction, static_cast<int>(ReqInsertOrder->Direction));
		StepUtility::WriteString(cursor, Items::OffsetFlag, static_cast<int>(ReqInsertOrder->OffsetFlag));
		StepUtility::WriteString(cursor, Items::OrderPriceType, static_cast<int>(ReqInsertOrder->OrderPriceType));
		StepUtility::WriteString(cursor, Items::Price, ReqInsertOrder->Price);
		StepUtility::WriteString(cursor, Items::Volume, ReqInsertOrder->Volume);
		StepUtility::WriteString(cursor, Items::ClientOrderId, ReqInsertOrder->ClientOrderId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, ReqInsertOrderField::FieldId);
	}
	if (RspInfo != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspInfoField::FieldId);
		StepUtility::WriteString(cursor, Items::ErrorId, RspInfo->ErrorId);
		if (strlen(RspInfo->ErrorMsg) >= sizeof(RspInfo->ErrorMsg))
		{
			RspInfo->ErrorMsg[sizeof(RspInfo->ErrorMsg) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ErrorMsg, RspInfo->ErrorMsg);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspInfoField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RspInsertOrderPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case ReqInsertOrderField::FieldId:
			{
				ReqInsertOrder = ObjectPool<ReqInsertOrderField>::GetInstance().Allocate();
				memset(ReqInsertOrder, 0, sizeof(*ReqInsertOrder));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(ReqInsertOrder->AccountId) ? sizeof(ReqInsertOrder->AccountId) - 1 : value.length();
							memcpy(ReqInsertOrder->AccountId, value.c_str(), len);
							break;
						}
						case Items::ExchangeId:
						{
							size_t len = value.length() >= sizeof(ReqInsertOrder->ExchangeId) ? sizeof(ReqInsertOrder->ExchangeId) - 1 : value.length();
							memcpy(ReqInsertOrder->ExchangeId, value.c_str(), len);
							break;
						}
						case Items::InstrumentId:
						{
							size_t len = value.length() >= sizeof(ReqInsertOrder->InstrumentId) ? sizeof(ReqInsertOrder->InstrumentId) - 1 : value.length();
							memcpy(ReqInsertOrder->InstrumentId, value.c_str(), len);
							break;
						}
						case Items::Direction:
						{
							ReqInsertOrder->Direction = static_cast<DirectionType>(atoi(value.c_str()));
							break;
						}
						case Items::OffsetFlag:
						{
							ReqInsertOrder->OffsetFlag = static_cast<OffsetFlagType>(atoi(value.c_str()));
							break;
						}
						case Items::OrderPriceType:
						{
							ReqInsertOrder->OrderPriceType = static_cast<OrderPriceTypeType>(atoi(value.c_str()));
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
						case Items::ClientOrderId:
						{
							ReqInsertOrder->ClientOrderId = atoi(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for ReqInsertOrderField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspInsertOrderPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldId:
			{
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
				memset(RspInfo, 0, sizeof(*RspInfo));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ErrorId:
						{
							RspInfo->ErrorId = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(RspInfo->ErrorMsg) ? sizeof(RspInfo->ErrorMsg) - 1 : value.length();
							memcpy(RspInfo->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspInfoField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspInsertOrderPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(ReqInsertOrderField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &ReqInsertOrderField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		memcpy(buff + offset, ReqInsertOrder, sizeof(ReqInsertOrderField));
		offset += sizeof(ReqInsertOrderField);
	}
	if (RspInfo != nullptr)
	{
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspInfoField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspInfoField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case ReqInsertOrderField::FieldId:
		{
			ReqInsertOrder = ObjectPool<ReqInsertOrderField>::GetInstance().Allocate();
			memcpy(ReqInsertOrder, buff + offset, sizeof(ReqInsertOrderField));
			offset += sizeof(ReqInsertOrderField);	
			break;
		}
		case RspInfoField::FieldId:
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
		offset = AppendDebugString(offset, "ReqInsertOrder:AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], ClientOrderId:[%d]", ReqInsertOrder->AccountId, ReqInsertOrder->ExchangeId, ReqInsertOrder->InstrumentId, static_cast<int>(ReqInsertOrder->Direction), static_cast<int>(ReqInsertOrder->OffsetFlag), static_cast<int>(ReqInsertOrder->OrderPriceType), ReqInsertOrder->Price, ReqInsertOrder->Volume, ReqInsertOrder->ClientOrderId);
	}
	if (RspInfo != nullptr)
	{
		offset = AppendDebugString(offset, "RspInfo:ErrorId:[%d], ErrorMsg:[%s]", RspInfo->ErrorId, RspInfo->ErrorMsg);
	}
	return DataStringBuffer;
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
void ReqCancelOrderPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int ReqCancelOrderPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (ReqCancelOrder != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, ReqCancelOrderField::FieldId);
		if (strlen(ReqCancelOrder->AccountId) >= sizeof(ReqCancelOrder->AccountId))
		{
			ReqCancelOrder->AccountId[sizeof(ReqCancelOrder->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, ReqCancelOrder->AccountId);
		if (strlen(ReqCancelOrder->ExchangeId) >= sizeof(ReqCancelOrder->ExchangeId))
		{
			ReqCancelOrder->ExchangeId[sizeof(ReqCancelOrder->ExchangeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeId, ReqCancelOrder->ExchangeId);
		if (strlen(ReqCancelOrder->InstrumentId) >= sizeof(ReqCancelOrder->InstrumentId))
		{
			ReqCancelOrder->InstrumentId[sizeof(ReqCancelOrder->InstrumentId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::InstrumentId, ReqCancelOrder->InstrumentId);
		StepUtility::WriteString(cursor, Items::ClientCancelOrderId, ReqCancelOrder->ClientCancelOrderId);
		StepUtility::WriteString(cursor, Items::OrderId, ReqCancelOrder->OrderId);
		if (strlen(ReqCancelOrder->OrderSysId) >= sizeof(ReqCancelOrder->OrderSysId))
		{
			ReqCancelOrder->OrderSysId[sizeof(ReqCancelOrder->OrderSysId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::OrderSysId, ReqCancelOrder->OrderSysId);
		StepUtility::WriteString(cursor, Items::SessionId, ReqCancelOrder->SessionId);
		StepUtility::WriteString(cursor, Items::ClientOrderId, ReqCancelOrder->ClientOrderId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, ReqCancelOrderField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool ReqCancelOrderPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case ReqCancelOrderField::FieldId:
			{
				ReqCancelOrder = ObjectPool<ReqCancelOrderField>::GetInstance().Allocate();
				memset(ReqCancelOrder, 0, sizeof(*ReqCancelOrder));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(ReqCancelOrder->AccountId) ? sizeof(ReqCancelOrder->AccountId) - 1 : value.length();
							memcpy(ReqCancelOrder->AccountId, value.c_str(), len);
							break;
						}
						case Items::ExchangeId:
						{
							size_t len = value.length() >= sizeof(ReqCancelOrder->ExchangeId) ? sizeof(ReqCancelOrder->ExchangeId) - 1 : value.length();
							memcpy(ReqCancelOrder->ExchangeId, value.c_str(), len);
							break;
						}
						case Items::InstrumentId:
						{
							size_t len = value.length() >= sizeof(ReqCancelOrder->InstrumentId) ? sizeof(ReqCancelOrder->InstrumentId) - 1 : value.length();
							memcpy(ReqCancelOrder->InstrumentId, value.c_str(), len);
							break;
						}
						case Items::ClientCancelOrderId:
						{
							ReqCancelOrder->ClientCancelOrderId = atoi(value.c_str());
							break;
						}
						case Items::OrderId:
						{
							ReqCancelOrder->OrderId = atoi(value.c_str());
							break;
						}
						case Items::OrderSysId:
						{
							size_t len = value.length() >= sizeof(ReqCancelOrder->OrderSysId) ? sizeof(ReqCancelOrder->OrderSysId) - 1 : value.length();
							memcpy(ReqCancelOrder->OrderSysId, value.c_str(), len);
							break;
						}
						case Items::SessionId:
						{
							ReqCancelOrder->SessionId = atoll(value.c_str());
							break;
						}
						case Items::ClientOrderId:
						{
							ReqCancelOrder->ClientOrderId = atoi(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for ReqCancelOrderField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For ReqCancelOrderPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(ReqCancelOrderField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &ReqCancelOrderField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case ReqCancelOrderField::FieldId:
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
		offset = AppendDebugString(offset, "ReqCancelOrder:AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], ClientCancelOrderId:[%d], OrderId:[%d], OrderSysId:[%s], SessionId:[%lld], ClientOrderId:[%d]", ReqCancelOrder->AccountId, ReqCancelOrder->ExchangeId, ReqCancelOrder->InstrumentId, ReqCancelOrder->ClientCancelOrderId, ReqCancelOrder->OrderId, ReqCancelOrder->OrderSysId, ReqCancelOrder->SessionId, ReqCancelOrder->ClientOrderId);
	}
	return DataStringBuffer;
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
void RspCancelOrderPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RspCancelOrderPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (ReqCancelOrder != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, ReqCancelOrderField::FieldId);
		if (strlen(ReqCancelOrder->AccountId) >= sizeof(ReqCancelOrder->AccountId))
		{
			ReqCancelOrder->AccountId[sizeof(ReqCancelOrder->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, ReqCancelOrder->AccountId);
		if (strlen(ReqCancelOrder->ExchangeId) >= sizeof(ReqCancelOrder->ExchangeId))
		{
			ReqCancelOrder->ExchangeId[sizeof(ReqCancelOrder->ExchangeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeId, ReqCancelOrder->ExchangeId);
		if (strlen(ReqCancelOrder->InstrumentId) >= sizeof(ReqCancelOrder->InstrumentId))
		{
			ReqCancelOrder->InstrumentId[sizeof(ReqCancelOrder->InstrumentId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::InstrumentId, ReqCancelOrder->InstrumentId);
		StepUtility::WriteString(cursor, Items::ClientCancelOrderId, ReqCancelOrder->ClientCancelOrderId);
		StepUtility::WriteString(cursor, Items::OrderId, ReqCancelOrder->OrderId);
		if (strlen(ReqCancelOrder->OrderSysId) >= sizeof(ReqCancelOrder->OrderSysId))
		{
			ReqCancelOrder->OrderSysId[sizeof(ReqCancelOrder->OrderSysId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::OrderSysId, ReqCancelOrder->OrderSysId);
		StepUtility::WriteString(cursor, Items::SessionId, ReqCancelOrder->SessionId);
		StepUtility::WriteString(cursor, Items::ClientOrderId, ReqCancelOrder->ClientOrderId);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, ReqCancelOrderField::FieldId);
	}
	if (RspInfo != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, RspInfoField::FieldId);
		StepUtility::WriteString(cursor, Items::ErrorId, RspInfo->ErrorId);
		if (strlen(RspInfo->ErrorMsg) >= sizeof(RspInfo->ErrorMsg))
		{
			RspInfo->ErrorMsg[sizeof(RspInfo->ErrorMsg) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ErrorMsg, RspInfo->ErrorMsg);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, RspInfoField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RspCancelOrderPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case ReqCancelOrderField::FieldId:
			{
				ReqCancelOrder = ObjectPool<ReqCancelOrderField>::GetInstance().Allocate();
				memset(ReqCancelOrder, 0, sizeof(*ReqCancelOrder));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(ReqCancelOrder->AccountId) ? sizeof(ReqCancelOrder->AccountId) - 1 : value.length();
							memcpy(ReqCancelOrder->AccountId, value.c_str(), len);
							break;
						}
						case Items::ExchangeId:
						{
							size_t len = value.length() >= sizeof(ReqCancelOrder->ExchangeId) ? sizeof(ReqCancelOrder->ExchangeId) - 1 : value.length();
							memcpy(ReqCancelOrder->ExchangeId, value.c_str(), len);
							break;
						}
						case Items::InstrumentId:
						{
							size_t len = value.length() >= sizeof(ReqCancelOrder->InstrumentId) ? sizeof(ReqCancelOrder->InstrumentId) - 1 : value.length();
							memcpy(ReqCancelOrder->InstrumentId, value.c_str(), len);
							break;
						}
						case Items::ClientCancelOrderId:
						{
							ReqCancelOrder->ClientCancelOrderId = atoi(value.c_str());
							break;
						}
						case Items::OrderId:
						{
							ReqCancelOrder->OrderId = atoi(value.c_str());
							break;
						}
						case Items::OrderSysId:
						{
							size_t len = value.length() >= sizeof(ReqCancelOrder->OrderSysId) ? sizeof(ReqCancelOrder->OrderSysId) - 1 : value.length();
							memcpy(ReqCancelOrder->OrderSysId, value.c_str(), len);
							break;
						}
						case Items::SessionId:
						{
							ReqCancelOrder->SessionId = atoll(value.c_str());
							break;
						}
						case Items::ClientOrderId:
						{
							ReqCancelOrder->ClientOrderId = atoi(value.c_str());
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for ReqCancelOrderField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspCancelOrderPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			case RspInfoField::FieldId:
			{
				RspInfo = ObjectPool<RspInfoField>::GetInstance().Allocate();
				memset(RspInfo, 0, sizeof(*RspInfo));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::ErrorId:
						{
							RspInfo->ErrorId = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(RspInfo->ErrorMsg) ? sizeof(RspInfo->ErrorMsg) - 1 : value.length();
							memcpy(RspInfo->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for RspInfoField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RspCancelOrderPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(ReqCancelOrderField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &ReqCancelOrderField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		memcpy(buff + offset, ReqCancelOrder, sizeof(ReqCancelOrderField));
		offset += sizeof(ReqCancelOrderField);
	}
	if (RspInfo != nullptr)
	{
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(RspInfoField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &RspInfoField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case ReqCancelOrderField::FieldId:
		{
			ReqCancelOrder = ObjectPool<ReqCancelOrderField>::GetInstance().Allocate();
			memcpy(ReqCancelOrder, buff + offset, sizeof(ReqCancelOrderField));
			offset += sizeof(ReqCancelOrderField);	
			break;
		}
		case RspInfoField::FieldId:
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
		offset = AppendDebugString(offset, "ReqCancelOrder:AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], ClientCancelOrderId:[%d], OrderId:[%d], OrderSysId:[%s], SessionId:[%lld], ClientOrderId:[%d]", ReqCancelOrder->AccountId, ReqCancelOrder->ExchangeId, ReqCancelOrder->InstrumentId, ReqCancelOrder->ClientCancelOrderId, ReqCancelOrder->OrderId, ReqCancelOrder->OrderSysId, ReqCancelOrder->SessionId, ReqCancelOrder->ClientOrderId);
	}
	if (RspInfo != nullptr)
	{
		offset = AppendDebugString(offset, "RspInfo:ErrorId:[%d], ErrorMsg:[%s]", RspInfo->ErrorId, RspInfo->ErrorMsg);
	}
	return DataStringBuffer;
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
void RtnOrderPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RtnOrderPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (Order != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, OrderField::FieldId);
		if (strlen(Order->TradingDay) >= sizeof(Order->TradingDay))
		{
			Order->TradingDay[sizeof(Order->TradingDay) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::TradingDay, Order->TradingDay);
		if (strlen(Order->AccountId) >= sizeof(Order->AccountId))
		{
			Order->AccountId[sizeof(Order->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, Order->AccountId);
		if (strlen(Order->ExchangeId) >= sizeof(Order->ExchangeId))
		{
			Order->ExchangeId[sizeof(Order->ExchangeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeId, Order->ExchangeId);
		if (strlen(Order->InstrumentId) >= sizeof(Order->InstrumentId))
		{
			Order->InstrumentId[sizeof(Order->InstrumentId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::InstrumentId, Order->InstrumentId);
		StepUtility::WriteString(cursor, Items::ProductClass, static_cast<int>(Order->ProductClass));
		StepUtility::WriteString(cursor, Items::OrderId, Order->OrderId);
		if (strlen(Order->OrderSysId) >= sizeof(Order->OrderSysId))
		{
			Order->OrderSysId[sizeof(Order->OrderSysId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::OrderSysId, Order->OrderSysId);
		StepUtility::WriteString(cursor, Items::Direction, static_cast<int>(Order->Direction));
		StepUtility::WriteString(cursor, Items::OffsetFlag, static_cast<int>(Order->OffsetFlag));
		StepUtility::WriteString(cursor, Items::OrderPriceType, static_cast<int>(Order->OrderPriceType));
		StepUtility::WriteString(cursor, Items::Price, Order->Price);
		StepUtility::WriteString(cursor, Items::Volume, Order->Volume);
		StepUtility::WriteString(cursor, Items::VolumeTotal, Order->VolumeTotal);
		StepUtility::WriteString(cursor, Items::VolumeTraded, Order->VolumeTraded);
		StepUtility::WriteString(cursor, Items::VolumeMultiple, Order->VolumeMultiple);
		StepUtility::WriteString(cursor, Items::OrderStatus, static_cast<int>(Order->OrderStatus));
		if (strlen(Order->OrderDate) >= sizeof(Order->OrderDate))
		{
			Order->OrderDate[sizeof(Order->OrderDate) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::OrderDate, Order->OrderDate);
		if (strlen(Order->OrderTime) >= sizeof(Order->OrderTime))
		{
			Order->OrderTime[sizeof(Order->OrderTime) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::OrderTime, Order->OrderTime);
		if (strlen(Order->CancelDate) >= sizeof(Order->CancelDate))
		{
			Order->CancelDate[sizeof(Order->CancelDate) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::CancelDate, Order->CancelDate);
		if (strlen(Order->CancelTime) >= sizeof(Order->CancelTime))
		{
			Order->CancelTime[sizeof(Order->CancelTime) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::CancelTime, Order->CancelTime);
		StepUtility::WriteString(cursor, Items::SessionId, Order->SessionId);
		StepUtility::WriteString(cursor, Items::ClientOrderId, Order->ClientOrderId);
		StepUtility::WriteString(cursor, Items::RequestId, Order->RequestId);
		StepUtility::WriteString(cursor, Items::FrozenCash, Order->FrozenCash);
		StepUtility::WriteString(cursor, Items::FrozenMargin, Order->FrozenMargin);
		StepUtility::WriteString(cursor, Items::FrozenCommission, Order->FrozenCommission);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, OrderField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RtnOrderPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case OrderField::FieldId:
			{
				Order = ObjectPool<OrderField>::GetInstance().Allocate();
				memset(Order, 0, sizeof(*Order));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
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
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(Order->AccountId) ? sizeof(Order->AccountId) - 1 : value.length();
							memcpy(Order->AccountId, value.c_str(), len);
							break;
						}
						case Items::ExchangeId:
						{
							size_t len = value.length() >= sizeof(Order->ExchangeId) ? sizeof(Order->ExchangeId) - 1 : value.length();
							memcpy(Order->ExchangeId, value.c_str(), len);
							break;
						}
						case Items::InstrumentId:
						{
							size_t len = value.length() >= sizeof(Order->InstrumentId) ? sizeof(Order->InstrumentId) - 1 : value.length();
							memcpy(Order->InstrumentId, value.c_str(), len);
							break;
						}
						case Items::ProductClass:
						{
							Order->ProductClass = static_cast<ProductClassType>(atoi(value.c_str()));
							break;
						}
						case Items::OrderId:
						{
							Order->OrderId = atoi(value.c_str());
							break;
						}
						case Items::OrderSysId:
						{
							size_t len = value.length() >= sizeof(Order->OrderSysId) ? sizeof(Order->OrderSysId) - 1 : value.length();
							memcpy(Order->OrderSysId, value.c_str(), len);
							break;
						}
						case Items::Direction:
						{
							Order->Direction = static_cast<DirectionType>(atoi(value.c_str()));
							break;
						}
						case Items::OffsetFlag:
						{
							Order->OffsetFlag = static_cast<OffsetFlagType>(atoi(value.c_str()));
							break;
						}
						case Items::OrderPriceType:
						{
							Order->OrderPriceType = static_cast<OrderPriceTypeType>(atoi(value.c_str()));
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
							Order->OrderStatus = static_cast<OrderStatusType>(atoi(value.c_str()));
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
						case Items::SessionId:
						{
							Order->SessionId = atoll(value.c_str());
							break;
						}
						case Items::ClientOrderId:
						{
							Order->ClientOrderId = atoi(value.c_str());
							break;
						}
						case Items::RequestId:
						{
							Order->RequestId = atoi(value.c_str());
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
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for OrderField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RtnOrderPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(OrderField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &OrderField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case OrderField::FieldId:
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
		offset = AppendDebugString(offset, "Order:TradingDay:[%s], AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], ProductClass:[%d], OrderId:[%d], OrderSysId:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], VolumeTotal:[%lld], VolumeTraded:[%lld], VolumeMultiple:[%d], OrderStatus:[%d], OrderDate:[%s], OrderTime:[%s], CancelDate:[%s], CancelTime:[%s], SessionId:[%lld], ClientOrderId:[%d], RequestId:[%d], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f]", Order->TradingDay, Order->AccountId, Order->ExchangeId, Order->InstrumentId, static_cast<int>(Order->ProductClass), Order->OrderId, Order->OrderSysId, static_cast<int>(Order->Direction), static_cast<int>(Order->OffsetFlag), static_cast<int>(Order->OrderPriceType), Order->Price, Order->Volume, Order->VolumeTotal, Order->VolumeTraded, Order->VolumeMultiple, static_cast<int>(Order->OrderStatus), Order->OrderDate, Order->OrderTime, Order->CancelDate, Order->CancelTime, Order->SessionId, Order->ClientOrderId, Order->RequestId, Order->FrozenCash, Order->FrozenMargin, Order->FrozenCommission);
	}
	return DataStringBuffer;
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
void RtnTradePackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RtnTradePackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (Trade != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, TradeField::FieldId);
		if (strlen(Trade->TradingDay) >= sizeof(Trade->TradingDay))
		{
			Trade->TradingDay[sizeof(Trade->TradingDay) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::TradingDay, Trade->TradingDay);
		if (strlen(Trade->AccountId) >= sizeof(Trade->AccountId))
		{
			Trade->AccountId[sizeof(Trade->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, Trade->AccountId);
		if (strlen(Trade->ExchangeId) >= sizeof(Trade->ExchangeId))
		{
			Trade->ExchangeId[sizeof(Trade->ExchangeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ExchangeId, Trade->ExchangeId);
		if (strlen(Trade->InstrumentId) >= sizeof(Trade->InstrumentId))
		{
			Trade->InstrumentId[sizeof(Trade->InstrumentId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::InstrumentId, Trade->InstrumentId);
		StepUtility::WriteString(cursor, Items::ProductClass, static_cast<int>(Trade->ProductClass));
		StepUtility::WriteString(cursor, Items::OrderId, Trade->OrderId);
		if (strlen(Trade->OrderSysId) >= sizeof(Trade->OrderSysId))
		{
			Trade->OrderSysId[sizeof(Trade->OrderSysId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::OrderSysId, Trade->OrderSysId);
		if (strlen(Trade->TradeId) >= sizeof(Trade->TradeId))
		{
			Trade->TradeId[sizeof(Trade->TradeId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::TradeId, Trade->TradeId);
		StepUtility::WriteString(cursor, Items::Direction, static_cast<int>(Trade->Direction));
		StepUtility::WriteString(cursor, Items::OffsetFlag, static_cast<int>(Trade->OffsetFlag));
		StepUtility::WriteString(cursor, Items::Price, Trade->Price);
		StepUtility::WriteString(cursor, Items::Volume, Trade->Volume);
		StepUtility::WriteString(cursor, Items::VolumeMultiple, Trade->VolumeMultiple);
		StepUtility::WriteString(cursor, Items::TradeAmount, Trade->TradeAmount);
		StepUtility::WriteString(cursor, Items::Commission, Trade->Commission);
		if (strlen(Trade->TradeDate) >= sizeof(Trade->TradeDate))
		{
			Trade->TradeDate[sizeof(Trade->TradeDate) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::TradeDate, Trade->TradeDate);
		if (strlen(Trade->TradeTime) >= sizeof(Trade->TradeTime))
		{
			Trade->TradeTime[sizeof(Trade->TradeTime) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::TradeTime, Trade->TradeTime);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, TradeField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RtnTradePackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case TradeField::FieldId:
			{
				Trade = ObjectPool<TradeField>::GetInstance().Allocate();
				memset(Trade, 0, sizeof(*Trade));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
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
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(Trade->AccountId) ? sizeof(Trade->AccountId) - 1 : value.length();
							memcpy(Trade->AccountId, value.c_str(), len);
							break;
						}
						case Items::ExchangeId:
						{
							size_t len = value.length() >= sizeof(Trade->ExchangeId) ? sizeof(Trade->ExchangeId) - 1 : value.length();
							memcpy(Trade->ExchangeId, value.c_str(), len);
							break;
						}
						case Items::InstrumentId:
						{
							size_t len = value.length() >= sizeof(Trade->InstrumentId) ? sizeof(Trade->InstrumentId) - 1 : value.length();
							memcpy(Trade->InstrumentId, value.c_str(), len);
							break;
						}
						case Items::ProductClass:
						{
							Trade->ProductClass = static_cast<ProductClassType>(atoi(value.c_str()));
							break;
						}
						case Items::OrderId:
						{
							Trade->OrderId = atoi(value.c_str());
							break;
						}
						case Items::OrderSysId:
						{
							size_t len = value.length() >= sizeof(Trade->OrderSysId) ? sizeof(Trade->OrderSysId) - 1 : value.length();
							memcpy(Trade->OrderSysId, value.c_str(), len);
							break;
						}
						case Items::TradeId:
						{
							size_t len = value.length() >= sizeof(Trade->TradeId) ? sizeof(Trade->TradeId) - 1 : value.length();
							memcpy(Trade->TradeId, value.c_str(), len);
							break;
						}
						case Items::Direction:
						{
							Trade->Direction = static_cast<DirectionType>(atoi(value.c_str()));
							break;
						}
						case Items::OffsetFlag:
						{
							Trade->OffsetFlag = static_cast<OffsetFlagType>(atoi(value.c_str()));
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
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for TradeField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RtnTradePackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(TradeField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &TradeField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case TradeField::FieldId:
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
		offset = AppendDebugString(offset, "Trade:TradingDay:[%s], AccountId:[%s], ExchangeId:[%s], InstrumentId:[%s], ProductClass:[%d], OrderId:[%d], OrderSysId:[%s], TradeId:[%s], Direction:[%d], OffsetFlag:[%d], Price:[%f], Volume:[%lld], VolumeMultiple:[%d], TradeAmount:[%f], Commission:[%f], TradeDate:[%s], TradeTime:[%s]", Trade->TradingDay, Trade->AccountId, Trade->ExchangeId, Trade->InstrumentId, static_cast<int>(Trade->ProductClass), Trade->OrderId, Trade->OrderSysId, Trade->TradeId, static_cast<int>(Trade->Direction), static_cast<int>(Trade->OffsetFlag), Trade->Price, Trade->Volume, Trade->VolumeMultiple, Trade->TradeAmount, Trade->Commission, Trade->TradeDate, Trade->TradeTime);
	}
	return DataStringBuffer;
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
void RtnMoneyTransferPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RtnMoneyTransferPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (MoneyTransfer != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, MoneyTransferField::FieldId);
		if (strlen(MoneyTransfer->TradingDay) >= sizeof(MoneyTransfer->TradingDay))
		{
			MoneyTransfer->TradingDay[sizeof(MoneyTransfer->TradingDay) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::TradingDay, MoneyTransfer->TradingDay);
		if (strlen(MoneyTransfer->AccountId) >= sizeof(MoneyTransfer->AccountId))
		{
			MoneyTransfer->AccountId[sizeof(MoneyTransfer->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, MoneyTransfer->AccountId);
		StepUtility::WriteString(cursor, Items::MoneyTransferId, MoneyTransfer->MoneyTransferId);
		StepUtility::WriteString(cursor, Items::AccountType, static_cast<int>(MoneyTransfer->AccountType));
		StepUtility::WriteString(cursor, Items::TransferDirection, static_cast<int>(MoneyTransfer->TransferDirection));
		StepUtility::WriteString(cursor, Items::TransferAmount, MoneyTransfer->TransferAmount);
		if (strlen(MoneyTransfer->InfoMessage) >= sizeof(MoneyTransfer->InfoMessage))
		{
			MoneyTransfer->InfoMessage[sizeof(MoneyTransfer->InfoMessage) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::InfoMessage, MoneyTransfer->InfoMessage);
		if (strlen(MoneyTransfer->UserId) >= sizeof(MoneyTransfer->UserId))
		{
			MoneyTransfer->UserId[sizeof(MoneyTransfer->UserId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::UserId, MoneyTransfer->UserId);
		if (strlen(MoneyTransfer->TransferDate) >= sizeof(MoneyTransfer->TransferDate))
		{
			MoneyTransfer->TransferDate[sizeof(MoneyTransfer->TransferDate) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::TransferDate, MoneyTransfer->TransferDate);
		if (strlen(MoneyTransfer->TransferTime) >= sizeof(MoneyTransfer->TransferTime))
		{
			MoneyTransfer->TransferTime[sizeof(MoneyTransfer->TransferTime) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::TransferTime, MoneyTransfer->TransferTime);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, MoneyTransferField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RtnMoneyTransferPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case MoneyTransferField::FieldId:
			{
				MoneyTransfer = ObjectPool<MoneyTransferField>::GetInstance().Allocate();
				memset(MoneyTransfer, 0, sizeof(*MoneyTransfer));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
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
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(MoneyTransfer->AccountId) ? sizeof(MoneyTransfer->AccountId) - 1 : value.length();
							memcpy(MoneyTransfer->AccountId, value.c_str(), len);
							break;
						}
						case Items::MoneyTransferId:
						{
							MoneyTransfer->MoneyTransferId = atoi(value.c_str());
							break;
						}
						case Items::AccountType:
						{
							MoneyTransfer->AccountType = static_cast<AccountTypeType>(atoi(value.c_str()));
							break;
						}
						case Items::TransferDirection:
						{
							MoneyTransfer->TransferDirection = static_cast<TransferDirectionType>(atoi(value.c_str()));
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
						case Items::UserId:
						{
							size_t len = value.length() >= sizeof(MoneyTransfer->UserId) ? sizeof(MoneyTransfer->UserId) - 1 : value.length();
							memcpy(MoneyTransfer->UserId, value.c_str(), len);
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
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for MoneyTransferField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RtnMoneyTransferPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(MoneyTransferField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &MoneyTransferField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case MoneyTransferField::FieldId:
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
		offset = AppendDebugString(offset, "MoneyTransfer:TradingDay:[%s], AccountId:[%s], MoneyTransferId:[%d], AccountType:[%d], TransferDirection:[%d], TransferAmount:[%f], InfoMessage:[%s], UserId:[%s], TransferDate:[%s], TransferTime:[%s]", MoneyTransfer->TradingDay, MoneyTransfer->AccountId, MoneyTransfer->MoneyTransferId, static_cast<int>(MoneyTransfer->AccountType), static_cast<int>(MoneyTransfer->TransferDirection), MoneyTransfer->TransferAmount, MoneyTransfer->InfoMessage, MoneyTransfer->UserId, MoneyTransfer->TransferDate, MoneyTransfer->TransferTime);
	}
	return DataStringBuffer;
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
void RtnAccountLogoutPackage::Prepare(SessionIdType sessionId, int messageChain, int msgSeqNum)
{
	Package::Prepare(sessionId, messageChain, msgSeqNum);
	Head.PackageId = PackageId;
}
int RtnAccountLogoutPackage::ToStepStream(char* buff, int size) const
{
	StepWriteCursor cursor(buff, size);
	if (AccountLogout != nullptr)
	{
		StepUtility::WriteHexString(cursor, Items::FieldStart, AccountLogoutField::FieldId);
		if (strlen(AccountLogout->AccountId) >= sizeof(AccountLogout->AccountId))
		{
			AccountLogout->AccountId[sizeof(AccountLogout->AccountId) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::AccountId, AccountLogout->AccountId);
		StepUtility::WriteString(cursor, Items::ErrorId, AccountLogout->ErrorId);
		if (strlen(AccountLogout->ErrorMsg) >= sizeof(AccountLogout->ErrorMsg))
		{
			AccountLogout->ErrorMsg[sizeof(AccountLogout->ErrorMsg) - 1] = 0;
		}
		StepUtility::WriteString(cursor, Items::ErrorMsg, AccountLogout->ErrorMsg);
		StepUtility::WriteHexString(cursor, Items::FieldEnd, AccountLogoutField::FieldId);
	}
	if (cursor.IsTruncated())
	{
		return -1;
	}
	return cursor.GetWrittenLength();
}
bool RtnAccountLogoutPackage::FromStepStream(char* buff, int startIndex, int endIndex)
{
	while (startIndex < endIndex)
	{
		unsigned short fieldId;
		int fieldStartIndex;
		int fieldEndIndex;
		if (StepUtility::GetNextFieldZone(buff, startIndex, endIndex, fieldId, fieldStartIndex, fieldEndIndex))
		{
			int itemStartIndex = fieldStartIndex;
			switch (fieldId)
			{
			case AccountLogoutField::FieldId:
			{
				AccountLogout = ObjectPool<AccountLogoutField>::GetInstance().Allocate();
				memset(AccountLogout, 0, sizeof(*AccountLogout));
				while (itemStartIndex < fieldEndIndex)
				{
					unsigned short  itemId;
					std::string value;
					int sohIndex;
					if (StepUtility::GetNext(buff, itemStartIndex, fieldEndIndex, itemId, value, sohIndex))
					{
						switch (itemId)
						{
						case Items::FieldStart:
						case Items::FieldEnd:
							break;
						case Items::AccountId:
						{
							size_t len = value.length() >= sizeof(AccountLogout->AccountId) ? sizeof(AccountLogout->AccountId) - 1 : value.length();
							memcpy(AccountLogout->AccountId, value.c_str(), len);
							break;
						}
						case Items::ErrorId:
						{
							AccountLogout->ErrorId = atoi(value.c_str());
							break;
						}
						case Items::ErrorMsg:
						{
							size_t len = value.length() >= sizeof(AccountLogout->ErrorMsg) ? sizeof(AccountLogout->ErrorMsg) - 1 : value.length();
							memcpy(AccountLogout->ErrorMsg, value.c_str(), len);
							break;
						}
						default:
							WriteLog(LogLevel::Warning, "Unexpected ItemId:0x%X for AccountLogoutField FieldId:0x%X, Please Check ApiVersion.", itemId, fieldId);
							return false;
						}
						itemStartIndex = sohIndex + 1;
					}
					else
					{
						WriteLog(LogLevel::Warning, "GetNext Failed For RtnAccountLogoutPackage FieldId:0x%X", fieldId);
						return false;
					}
				}
				break;
			}
			default:
				WriteLog(LogLevel::Warning, "Unexpected FieldId:0x%X, Please Check Api Version.", fieldId);
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
		const int fieldSize = static_cast<int>(sizeof(UInt16Type) + sizeof(AccountLogoutField));
		if (offset + fieldSize > size)
		{
			return -1;
		}
		memcpy(buff + offset, &AccountLogoutField::FieldId, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
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
		UInt16Type fieldId = 0;
		memcpy(&fieldId, buff + offset, sizeof(UInt16Type));
		offset += sizeof(UInt16Type);
		switch (fieldId)
		{
		case AccountLogoutField::FieldId:
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
		offset = AppendDebugString(offset, "AccountLogout:AccountId:[%s], ErrorId:[%d], ErrorMsg:[%s]", AccountLogout->AccountId, AccountLogout->ErrorId, AccountLogout->ErrorMsg);
	}
	return DataStringBuffer;
}
}
