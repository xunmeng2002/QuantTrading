#include "Packages.h"
#include "Items.h"
#include "StepUtility.h"
#include "Logger.h"
#include "MemCacheTemplateSingleton.h"
#include <cstring>

thread_local char t_DataStringBuffer[10240];



 
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
	memcpy(buff + offset, ReqQryInstrument, sizeof(ReqQryInstrumentField));
	offset += sizeof(ReqQryInstrumentField);
	return offset;
}
bool ReqQryInstrumentPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	ReqQryInstrument = ::Allocate<ReqQryInstrumentField>();
	memcpy(ReqQryInstrument, buff + offset, sizeof(ReqQryInstrumentField));
	offset += sizeof(ReqQryInstrumentField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* ReqQryInstrumentPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "ReqQryInstrument:ExchangeID:[%s], InstrumentID:[%s]", ReqQryInstrument->ExchangeID, ReqQryInstrument->InstrumentID);
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
		WriteString(ppos, Items::VolumeMultiple, Instrument->VolumeMultiple);
		WriteString(ppos, Items::ProductClass, (int)Instrument->ProductClass);
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
						case Items::VolumeMultiple:
						{
							Instrument->VolumeMultiple = atoi(value.c_str());
							break;
						}
						case Items::ProductClass:
						{
							Instrument->ProductClass = (ProductClassType)(atoi(value.c_str()));
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
	memcpy(buff + offset, Instrument, sizeof(InstrumentField));
	offset += sizeof(InstrumentField);
	memcpy(buff + offset, RspInfo, sizeof(RspInfoField));
	offset += sizeof(RspInfoField);
	return offset;
}
bool RspQryInstrumentPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	Instrument = ::Allocate<InstrumentField>();
	memcpy(Instrument, buff + offset, sizeof(InstrumentField));
	offset += sizeof(InstrumentField);
	RspInfo = ::Allocate<RspInfoField>();
	memcpy(RspInfo, buff + offset, sizeof(RspInfoField));
	offset += sizeof(RspInfoField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* RspQryInstrumentPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "Instrument:ExchangeID:[%s], InstrumentID:[%s], ExchangeInstID:[%s], InstrumentName:[%s], VolumeMultiple:[%d], ProductClass:[%d]", Instrument->ExchangeID, Instrument->InstrumentID, Instrument->ExchangeInstID, Instrument->InstrumentName, Instrument->VolumeMultiple, (int)Instrument->ProductClass);
	offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
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
		WriteString(ppos, Items::OrderID, ReqSEInsertOrder->OrderID);
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
						case Items::OrderID:
						{
							ReqSEInsertOrder->OrderID = atoi(value.c_str());
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
	memcpy(buff + offset, ReqSEInsertOrder, sizeof(ReqSEInsertOrderField));
	offset += sizeof(ReqSEInsertOrderField);
	return offset;
}
bool ReqSEInsertOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	ReqSEInsertOrder = ::Allocate<ReqSEInsertOrderField>();
	memcpy(ReqSEInsertOrder, buff + offset, sizeof(ReqSEInsertOrderField));
	offset += sizeof(ReqSEInsertOrderField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* ReqSEInsertOrderPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "ReqSEInsertOrder:AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], OrderID:[%d]", ReqSEInsertOrder->AccountID, ReqSEInsertOrder->ExchangeID, ReqSEInsertOrder->InstrumentID, (int)ReqSEInsertOrder->Direction, (int)ReqSEInsertOrder->OffsetFlag, (int)ReqSEInsertOrder->OrderPriceType, ReqSEInsertOrder->Price, ReqSEInsertOrder->Volume, ReqSEInsertOrder->OrderID);
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
		WriteString(ppos, Items::OrderID, ReqSEInsertOrder->OrderID);
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
						case Items::OrderID:
						{
							ReqSEInsertOrder->OrderID = atoi(value.c_str());
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
	memcpy(buff + offset, ReqSEInsertOrder, sizeof(ReqSEInsertOrderField));
	offset += sizeof(ReqSEInsertOrderField);
	memcpy(buff + offset, RspInfo, sizeof(RspInfoField));
	offset += sizeof(RspInfoField);
	return offset;
}
bool RspSEInsertOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	ReqSEInsertOrder = ::Allocate<ReqSEInsertOrderField>();
	memcpy(ReqSEInsertOrder, buff + offset, sizeof(ReqSEInsertOrderField));
	offset += sizeof(ReqSEInsertOrderField);
	RspInfo = ::Allocate<RspInfoField>();
	memcpy(RspInfo, buff + offset, sizeof(RspInfoField));
	offset += sizeof(RspInfoField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* RspSEInsertOrderPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "ReqSEInsertOrder:AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], OrderID:[%d]", ReqSEInsertOrder->AccountID, ReqSEInsertOrder->ExchangeID, ReqSEInsertOrder->InstrumentID, (int)ReqSEInsertOrder->Direction, (int)ReqSEInsertOrder->OffsetFlag, (int)ReqSEInsertOrder->OrderPriceType, ReqSEInsertOrder->Price, ReqSEInsertOrder->Volume, ReqSEInsertOrder->OrderID);
	offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
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
		if (strlen(ReqSECancelOrder->OrderSysID) >= sizeof(ReqSECancelOrder->OrderSysID))
		{
			ReqSECancelOrder->OrderSysID[sizeof(ReqSECancelOrder->OrderSysID) - 1] = 0;
		}
		WriteString(ppos, Items::OrderSysID, ReqSECancelOrder->OrderSysID);
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
						case Items::OrderSysID:
						{
							size_t len = value.length() >= sizeof(ReqSECancelOrder->OrderSysID) ? sizeof(ReqSECancelOrder->OrderSysID) - 1 : value.length();
							memcpy(ReqSECancelOrder->OrderSysID, value.c_str(), len);
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
	memcpy(buff + offset, ReqSECancelOrder, sizeof(ReqSECancelOrderField));
	offset += sizeof(ReqSECancelOrderField);
	return offset;
}
bool ReqSECancelOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	ReqSECancelOrder = ::Allocate<ReqSECancelOrderField>();
	memcpy(ReqSECancelOrder, buff + offset, sizeof(ReqSECancelOrderField));
	offset += sizeof(ReqSECancelOrderField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* ReqSECancelOrderPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "ReqSECancelOrder:AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], CancelOrderID:[%d], OrderID:[%d], OrderSysID:[%s], SessionID:[%lld]", ReqSECancelOrder->AccountID, ReqSECancelOrder->ExchangeID, ReqSECancelOrder->InstrumentID, ReqSECancelOrder->CancelOrderID, ReqSECancelOrder->OrderID, ReqSECancelOrder->OrderSysID, ReqSECancelOrder->SessionID);
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
		if (strlen(ReqSECancelOrder->OrderSysID) >= sizeof(ReqSECancelOrder->OrderSysID))
		{
			ReqSECancelOrder->OrderSysID[sizeof(ReqSECancelOrder->OrderSysID) - 1] = 0;
		}
		WriteString(ppos, Items::OrderSysID, ReqSECancelOrder->OrderSysID);
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
						case Items::OrderSysID:
						{
							size_t len = value.length() >= sizeof(ReqSECancelOrder->OrderSysID) ? sizeof(ReqSECancelOrder->OrderSysID) - 1 : value.length();
							memcpy(ReqSECancelOrder->OrderSysID, value.c_str(), len);
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
	memcpy(buff + offset, ReqSECancelOrder, sizeof(ReqSECancelOrderField));
	offset += sizeof(ReqSECancelOrderField);
	memcpy(buff + offset, RspInfo, sizeof(RspInfoField));
	offset += sizeof(RspInfoField);
	return offset;
}
bool RspSECancelOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	ReqSECancelOrder = ::Allocate<ReqSECancelOrderField>();
	memcpy(ReqSECancelOrder, buff + offset, sizeof(ReqSECancelOrderField));
	offset += sizeof(ReqSECancelOrderField);
	RspInfo = ::Allocate<RspInfoField>();
	memcpy(RspInfo, buff + offset, sizeof(RspInfoField));
	offset += sizeof(RspInfoField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* RspSECancelOrderPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "ReqSECancelOrder:AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], CancelOrderID:[%d], OrderID:[%d], OrderSysID:[%s], SessionID:[%lld]", ReqSECancelOrder->AccountID, ReqSECancelOrder->ExchangeID, ReqSECancelOrder->InstrumentID, ReqSECancelOrder->CancelOrderID, ReqSECancelOrder->OrderID, ReqSECancelOrder->OrderSysID, ReqSECancelOrder->SessionID);
	offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
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
	memcpy(buff + offset, ReqQrySEOrder, sizeof(ReqQrySEOrderField));
	offset += sizeof(ReqQrySEOrderField);
	return offset;
}
bool ReqQrySEOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	ReqQrySEOrder = ::Allocate<ReqQrySEOrderField>();
	memcpy(ReqQrySEOrder, buff + offset, sizeof(ReqQrySEOrderField));
	offset += sizeof(ReqQrySEOrderField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* ReqQrySEOrderPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "ReqQrySEOrder:AccountID:[%s]", ReqQrySEOrder->AccountID);
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
		if (strlen(SEOrder->OrderSysID) >= sizeof(SEOrder->OrderSysID))
		{
			SEOrder->OrderSysID[sizeof(SEOrder->OrderSysID) - 1] = 0;
		}
		WriteString(ppos, Items::OrderSysID, SEOrder->OrderSysID);
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
		WriteString(ppos, Items::OrderID, SEOrder->OrderID);
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
						case Items::OrderSysID:
						{
							size_t len = value.length() >= sizeof(SEOrder->OrderSysID) ? sizeof(SEOrder->OrderSysID) - 1 : value.length();
							memcpy(SEOrder->OrderSysID, value.c_str(), len);
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
						case Items::OrderID:
						{
							SEOrder->OrderID = atoi(value.c_str());
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
	memcpy(buff + offset, SEOrder, sizeof(SEOrderField));
	offset += sizeof(SEOrderField);
	memcpy(buff + offset, RspInfo, sizeof(RspInfoField));
	offset += sizeof(RspInfoField);
	return offset;
}
bool RspQrySEOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	SEOrder = ::Allocate<SEOrderField>();
	memcpy(SEOrder, buff + offset, sizeof(SEOrderField));
	offset += sizeof(SEOrderField);
	RspInfo = ::Allocate<RspInfoField>();
	memcpy(RspInfo, buff + offset, sizeof(RspInfoField));
	offset += sizeof(RspInfoField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* RspQrySEOrderPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "SEOrder:TradingDay:[%s], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderSysID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], VolumeTotal:[%lld], VolumeTraded:[%lld], VolumeMultiple:[%d], OrderStatus:[%d], OrderDate:[%s], OrderTime:[%s], CancelDate:[%s], CancelTime:[%s], SessionID:[%lld], OrderID:[%d]", SEOrder->TradingDay, SEOrder->AccountID, SEOrder->ExchangeID, SEOrder->InstrumentID, (int)SEOrder->ProductClass, SEOrder->OrderSysID, (int)SEOrder->Direction, (int)SEOrder->OffsetFlag, (int)SEOrder->OrderPriceType, SEOrder->Price, SEOrder->Volume, SEOrder->VolumeTotal, SEOrder->VolumeTraded, SEOrder->VolumeMultiple, (int)SEOrder->OrderStatus, SEOrder->OrderDate, SEOrder->OrderTime, SEOrder->CancelDate, SEOrder->CancelTime, SEOrder->SessionID, SEOrder->OrderID);
	offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
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
	memcpy(buff + offset, ReqQrySETrade, sizeof(ReqQrySETradeField));
	offset += sizeof(ReqQrySETradeField);
	return offset;
}
bool ReqQrySETradePackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	ReqQrySETrade = ::Allocate<ReqQrySETradeField>();
	memcpy(ReqQrySETrade, buff + offset, sizeof(ReqQrySETradeField));
	offset += sizeof(ReqQrySETradeField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* ReqQrySETradePackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "ReqQrySETrade:AccountID:[%s]", ReqQrySETrade->AccountID);
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
		if (strlen(SETrade->OrderSysID) >= sizeof(SETrade->OrderSysID))
		{
			SETrade->OrderSysID[sizeof(SETrade->OrderSysID) - 1] = 0;
		}
		WriteString(ppos, Items::OrderSysID, SETrade->OrderSysID);
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
						case Items::OrderSysID:
						{
							size_t len = value.length() >= sizeof(SETrade->OrderSysID) ? sizeof(SETrade->OrderSysID) - 1 : value.length();
							memcpy(SETrade->OrderSysID, value.c_str(), len);
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
	memcpy(buff + offset, SETrade, sizeof(SETradeField));
	offset += sizeof(SETradeField);
	memcpy(buff + offset, RspInfo, sizeof(RspInfoField));
	offset += sizeof(RspInfoField);
	return offset;
}
bool RspQrySETradePackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	SETrade = ::Allocate<SETradeField>();
	memcpy(SETrade, buff + offset, sizeof(SETradeField));
	offset += sizeof(SETradeField);
	RspInfo = ::Allocate<RspInfoField>();
	memcpy(RspInfo, buff + offset, sizeof(RspInfoField));
	offset += sizeof(RspInfoField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* RspQrySETradePackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "SETrade:TradingDay:[%s], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], OrderSysID:[%s], TradeID:[%s], Direction:[%d], OffsetFlag:[%d], Price:[%f], Volume:[%lld], VolumeMultiple:[%d], TradeAmount:[%f], Commission:[%f], TradeDate:[%s], TradeTime:[%s]", SETrade->TradingDay, SETrade->AccountID, SETrade->ExchangeID, SETrade->InstrumentID, (int)SETrade->ProductClass, SETrade->OrderID, SETrade->OrderSysID, SETrade->TradeID, (int)SETrade->Direction, (int)SETrade->OffsetFlag, SETrade->Price, SETrade->Volume, SETrade->VolumeMultiple, SETrade->TradeAmount, SETrade->Commission, SETrade->TradeDate, SETrade->TradeTime);
	offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
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
		if (strlen(SEOrder->OrderSysID) >= sizeof(SEOrder->OrderSysID))
		{
			SEOrder->OrderSysID[sizeof(SEOrder->OrderSysID) - 1] = 0;
		}
		WriteString(ppos, Items::OrderSysID, SEOrder->OrderSysID);
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
		WriteString(ppos, Items::OrderID, SEOrder->OrderID);
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
						case Items::OrderSysID:
						{
							size_t len = value.length() >= sizeof(SEOrder->OrderSysID) ? sizeof(SEOrder->OrderSysID) - 1 : value.length();
							memcpy(SEOrder->OrderSysID, value.c_str(), len);
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
						case Items::OrderID:
						{
							SEOrder->OrderID = atoi(value.c_str());
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
	memcpy(buff + offset, SEOrder, sizeof(SEOrderField));
	offset += sizeof(SEOrderField);
	return offset;
}
bool RtnSEOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	SEOrder = ::Allocate<SEOrderField>();
	memcpy(SEOrder, buff + offset, sizeof(SEOrderField));
	offset += sizeof(SEOrderField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* RtnSEOrderPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "SEOrder:TradingDay:[%s], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderSysID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], VolumeTotal:[%lld], VolumeTraded:[%lld], VolumeMultiple:[%d], OrderStatus:[%d], OrderDate:[%s], OrderTime:[%s], CancelDate:[%s], CancelTime:[%s], SessionID:[%lld], OrderID:[%d]", SEOrder->TradingDay, SEOrder->AccountID, SEOrder->ExchangeID, SEOrder->InstrumentID, (int)SEOrder->ProductClass, SEOrder->OrderSysID, (int)SEOrder->Direction, (int)SEOrder->OffsetFlag, (int)SEOrder->OrderPriceType, SEOrder->Price, SEOrder->Volume, SEOrder->VolumeTotal, SEOrder->VolumeTraded, SEOrder->VolumeMultiple, (int)SEOrder->OrderStatus, SEOrder->OrderDate, SEOrder->OrderTime, SEOrder->CancelDate, SEOrder->CancelTime, SEOrder->SessionID, SEOrder->OrderID);
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
		if (strlen(SETrade->OrderSysID) >= sizeof(SETrade->OrderSysID))
		{
			SETrade->OrderSysID[sizeof(SETrade->OrderSysID) - 1] = 0;
		}
		WriteString(ppos, Items::OrderSysID, SETrade->OrderSysID);
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
						case Items::OrderSysID:
						{
							size_t len = value.length() >= sizeof(SETrade->OrderSysID) ? sizeof(SETrade->OrderSysID) - 1 : value.length();
							memcpy(SETrade->OrderSysID, value.c_str(), len);
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
	memcpy(buff + offset, SETrade, sizeof(SETradeField));
	offset += sizeof(SETradeField);
	return offset;
}
bool RtnSETradePackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	SETrade = ::Allocate<SETradeField>();
	memcpy(SETrade, buff + offset, sizeof(SETradeField));
	offset += sizeof(SETradeField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* RtnSETradePackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "SETrade:TradingDay:[%s], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], OrderSysID:[%s], TradeID:[%s], Direction:[%d], OffsetFlag:[%d], Price:[%f], Volume:[%lld], VolumeMultiple:[%d], TradeAmount:[%f], Commission:[%f], TradeDate:[%s], TradeTime:[%s]", SETrade->TradingDay, SETrade->AccountID, SETrade->ExchangeID, SETrade->InstrumentID, (int)SETrade->ProductClass, SETrade->OrderID, SETrade->OrderSysID, SETrade->TradeID, (int)SETrade->Direction, (int)SETrade->OffsetFlag, SETrade->Price, SETrade->Volume, SETrade->VolumeMultiple, SETrade->TradeAmount, SETrade->Commission, SETrade->TradeDate, SETrade->TradeTime);
	return t_DataStringBuffer;
}
