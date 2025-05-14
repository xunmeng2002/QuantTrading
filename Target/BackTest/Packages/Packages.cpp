#include "Packages.h"
#include "Items.h"
#include "StepUtility.h"
#include "Logger.h"
#include "MemCacheTemplateSingleton.h"
#include <cstring>

thread_local char t_DataStringBuffer[10240];



 
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
	offset += sprintf(t_DataStringBuffer + offset, "ReqSubMarketData:ExchangeID:[%s], InstrumentID:[%s]", ReqSubMarketData->ExchangeID, ReqSubMarketData->InstrumentID);
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
	offset += sprintf(t_DataStringBuffer + offset, "RspSubMarketData:ExchangeID:[%s], InstrumentID:[%s]", RspSubMarketData->ExchangeID, RspSubMarketData->InstrumentID);
	offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
	return t_DataStringBuffer;
}
 
ReqSubMarketDataFinishedPackage* ReqSubMarketDataFinishedPackage::Allocate()
{
	return ::Allocate<ReqSubMarketDataFinishedPackage>();
}
void ReqSubMarketDataFinishedPackage::Free()
{
	Package::Free();
	if (ReqSubMarketDataFinished != nullptr)
	{
		::Free<ReqSubMarketDataFinishedField>(ReqSubMarketDataFinished);
		ReqSubMarketDataFinished = nullptr;
	}
	MemCacheTemplateSingleton<ReqSubMarketDataFinishedPackage>::GetInstance().Free(this);
}
void ReqSubMarketDataFinishedPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
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
				ReqSubMarketDataFinished = ::Allocate<ReqSubMarketDataFinishedField>();
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
	memcpy(buff + offset, ReqSubMarketDataFinished, sizeof(ReqSubMarketDataFinishedField));
	offset += sizeof(ReqSubMarketDataFinishedField);
	return offset;
}
bool ReqSubMarketDataFinishedPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	ReqSubMarketDataFinished = ::Allocate<ReqSubMarketDataFinishedField>();
	memcpy(ReqSubMarketDataFinished, buff + offset, sizeof(ReqSubMarketDataFinishedField));
	offset += sizeof(ReqSubMarketDataFinishedField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* ReqSubMarketDataFinishedPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "ReqSubMarketDataFinished:");
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
	offset += sprintf(t_DataStringBuffer + offset, "DepthMarketData:TradingDay:[%s], ExchangeID:[%s], InstrumentID:[%s], UpdateTs:[%lld], LastPrice:[%f], PreSettlementPrice:[%f], PreClosePrice:[%f], PreOpenInterest:[%f], OpenPrice:[%f], HighestPrice:[%f], LowestPrice:[%f], ClosePrice:[%f], CurrVolume:[%lld], Volume:[%lld], CurrTurnover:[%f], Turnover:[%f], OpenInterest:[%f], SettlementPrice:[%f], UpperLimitPrice:[%f], LowerLimitPrice:[%f], AveragePrice:[%f], AskPrice1:[%f], AskPrice2:[%f], AskPrice3:[%f], AskPrice4:[%f], AskPrice5:[%f], AskPrice6:[%f], AskPrice7:[%f], AskPrice8:[%f], AskPrice9:[%f], AskPrice10:[%f], AskVolume1:[%lld], AskVolume2:[%lld], AskVolume3:[%lld], AskVolume4:[%lld], AskVolume5:[%lld], AskVolume6:[%lld], AskVolume7:[%lld], AskVolume8:[%lld], AskVolume9:[%lld], AskVolume10:[%lld], BidPrice1:[%f], BidPrice2:[%f], BidPrice3:[%f], BidPrice4:[%f], BidPrice5:[%f], BidPrice6:[%f], BidPrice7:[%f], BidPrice8:[%f], BidPrice9:[%f], BidPrice10:[%f], BidVolume1:[%lld], BidVolume2:[%lld], BidVolume3:[%lld], BidVolume4:[%lld], BidVolume5:[%lld], BidVolume6:[%lld], BidVolume7:[%lld], BidVolume8:[%lld], BidVolume9:[%lld], BidVolume10:[%lld]", DepthMarketData->TradingDay, DepthMarketData->ExchangeID, DepthMarketData->InstrumentID, DepthMarketData->UpdateTs, DepthMarketData->LastPrice, DepthMarketData->PreSettlementPrice, DepthMarketData->PreClosePrice, DepthMarketData->PreOpenInterest, DepthMarketData->OpenPrice, DepthMarketData->HighestPrice, DepthMarketData->LowestPrice, DepthMarketData->ClosePrice, DepthMarketData->CurrVolume, DepthMarketData->Volume, DepthMarketData->CurrTurnover, DepthMarketData->Turnover, DepthMarketData->OpenInterest, DepthMarketData->SettlementPrice, DepthMarketData->UpperLimitPrice, DepthMarketData->LowerLimitPrice, DepthMarketData->AveragePrice, DepthMarketData->AskPrice1, DepthMarketData->AskPrice2, DepthMarketData->AskPrice3, DepthMarketData->AskPrice4, DepthMarketData->AskPrice5, DepthMarketData->AskPrice6, DepthMarketData->AskPrice7, DepthMarketData->AskPrice8, DepthMarketData->AskPrice9, DepthMarketData->AskPrice10, DepthMarketData->AskVolume1, DepthMarketData->AskVolume2, DepthMarketData->AskVolume3, DepthMarketData->AskVolume4, DepthMarketData->AskVolume5, DepthMarketData->AskVolume6, DepthMarketData->AskVolume7, DepthMarketData->AskVolume8, DepthMarketData->AskVolume9, DepthMarketData->AskVolume10, DepthMarketData->BidPrice1, DepthMarketData->BidPrice2, DepthMarketData->BidPrice3, DepthMarketData->BidPrice4, DepthMarketData->BidPrice5, DepthMarketData->BidPrice6, DepthMarketData->BidPrice7, DepthMarketData->BidPrice8, DepthMarketData->BidPrice9, DepthMarketData->BidPrice10, DepthMarketData->BidVolume1, DepthMarketData->BidVolume2, DepthMarketData->BidVolume3, DepthMarketData->BidVolume4, DepthMarketData->BidVolume5, DepthMarketData->BidVolume6, DepthMarketData->BidVolume7, DepthMarketData->BidVolume8, DepthMarketData->BidVolume9, DepthMarketData->BidVolume10);
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
	offset += sprintf(t_DataStringBuffer + offset, "BarMarketData:TradingDay:[%s], ExchangeID:[%s], InstrumentID:[%s], BarPreces:[%d], BarPeriod:[%d], BarTime:[%lld], UpdateTs:[%lld], HighestPrice:[%f], LowestPrice:[%f], Open:[%f], High:[%f], Low:[%f], Close:[%f], CurrVolume:[%lld], Volume:[%lld], CurrTurnover:[%f], Turnover:[%f], OpenInterest:[%f]", BarMarketData->TradingDay, BarMarketData->ExchangeID, BarMarketData->InstrumentID, (int)BarMarketData->BarPreces, BarMarketData->BarPeriod, BarMarketData->BarTime, BarMarketData->UpdateTs, BarMarketData->HighestPrice, BarMarketData->LowestPrice, BarMarketData->Open, BarMarketData->High, BarMarketData->Low, BarMarketData->Close, BarMarketData->CurrVolume, BarMarketData->Volume, BarMarketData->CurrTurnover, BarMarketData->Turnover, BarMarketData->OpenInterest);
	return t_DataStringBuffer;
}
 
RtnSessionBeginPackage* RtnSessionBeginPackage::Allocate()
{
	return ::Allocate<RtnSessionBeginPackage>();
}
void RtnSessionBeginPackage::Free()
{
	Package::Free();
	if (SessionBegin != nullptr)
	{
		::Free<SessionBeginField>(SessionBegin);
		SessionBegin = nullptr;
	}
	MemCacheTemplateSingleton<RtnSessionBeginPackage>::GetInstance().Free(this);
}
void RtnSessionBeginPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
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
				SessionBegin = ::Allocate<SessionBeginField>();
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
	memcpy(buff + offset, SessionBegin, sizeof(SessionBeginField));
	offset += sizeof(SessionBeginField);
	return offset;
}
bool RtnSessionBeginPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	SessionBegin = ::Allocate<SessionBeginField>();
	memcpy(SessionBegin, buff + offset, sizeof(SessionBeginField));
	offset += sizeof(SessionBeginField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* RtnSessionBeginPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "SessionBegin:TradingDay:[%s]", SessionBegin->TradingDay);
	return t_DataStringBuffer;
}
 
RtnSessionEndPackage* RtnSessionEndPackage::Allocate()
{
	return ::Allocate<RtnSessionEndPackage>();
}
void RtnSessionEndPackage::Free()
{
	Package::Free();
	if (SessionEnd != nullptr)
	{
		::Free<SessionEndField>(SessionEnd);
		SessionEnd = nullptr;
	}
	MemCacheTemplateSingleton<RtnSessionEndPackage>::GetInstance().Free(this);
}
void RtnSessionEndPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
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
				SessionEnd = ::Allocate<SessionEndField>();
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
	memcpy(buff + offset, SessionEnd, sizeof(SessionEndField));
	offset += sizeof(SessionEndField);
	return offset;
}
bool RtnSessionEndPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	SessionEnd = ::Allocate<SessionEndField>();
	memcpy(SessionEnd, buff + offset, sizeof(SessionEndField));
	offset += sizeof(SessionEndField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* RtnSessionEndPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "SessionEnd:TradingDay:[%s]", SessionEnd->TradingDay);
	return t_DataStringBuffer;
}
 
RtnMarketDataEndPackage* RtnMarketDataEndPackage::Allocate()
{
	return ::Allocate<RtnMarketDataEndPackage>();
}
void RtnMarketDataEndPackage::Free()
{
	Package::Free();
	if (MarketDataEnd != nullptr)
	{
		::Free<MarketDataEndField>(MarketDataEnd);
		MarketDataEnd = nullptr;
	}
	MemCacheTemplateSingleton<RtnMarketDataEndPackage>::GetInstance().Free(this);
}
void RtnMarketDataEndPackage::Prepare(SessionIDType sessionID, bool messageChain, int msgSeqNum)
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
				MarketDataEnd = ::Allocate<MarketDataEndField>();
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
	memcpy(buff + offset, MarketDataEnd, sizeof(MarketDataEndField));
	offset += sizeof(MarketDataEndField);
	return offset;
}
bool RtnMarketDataEndPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	MarketDataEnd = ::Allocate<MarketDataEndField>();
	memcpy(MarketDataEnd, buff + offset, sizeof(MarketDataEndField));
	offset += sizeof(MarketDataEndField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* RtnMarketDataEndPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "MarketDataEnd:TradingDay:[%s]", MarketDataEnd->TradingDay);
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
	memcpy(buff + offset, ReqInsertOrder, sizeof(ReqInsertOrderField));
	offset += sizeof(ReqInsertOrderField);
	return offset;
}
bool ReqInsertOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	ReqInsertOrder = ::Allocate<ReqInsertOrderField>();
	memcpy(ReqInsertOrder, buff + offset, sizeof(ReqInsertOrderField));
	offset += sizeof(ReqInsertOrderField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* ReqInsertOrderPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "ReqInsertOrder:AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], ClientOrderID:[%d]", ReqInsertOrder->AccountID, ReqInsertOrder->ExchangeID, ReqInsertOrder->InstrumentID, (int)ReqInsertOrder->Direction, (int)ReqInsertOrder->OffsetFlag, (int)ReqInsertOrder->OrderPriceType, ReqInsertOrder->Price, ReqInsertOrder->Volume, ReqInsertOrder->ClientOrderID);
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
	memcpy(buff + offset, ReqInsertOrder, sizeof(ReqInsertOrderField));
	offset += sizeof(ReqInsertOrderField);
	memcpy(buff + offset, RspInfo, sizeof(RspInfoField));
	offset += sizeof(RspInfoField);
	return offset;
}
bool RspInsertOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	ReqInsertOrder = ::Allocate<ReqInsertOrderField>();
	memcpy(ReqInsertOrder, buff + offset, sizeof(ReqInsertOrderField));
	offset += sizeof(ReqInsertOrderField);
	RspInfo = ::Allocate<RspInfoField>();
	memcpy(RspInfo, buff + offset, sizeof(RspInfoField));
	offset += sizeof(RspInfoField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* RspInsertOrderPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "ReqInsertOrder:AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], ClientOrderID:[%d]", ReqInsertOrder->AccountID, ReqInsertOrder->ExchangeID, ReqInsertOrder->InstrumentID, (int)ReqInsertOrder->Direction, (int)ReqInsertOrder->OffsetFlag, (int)ReqInsertOrder->OrderPriceType, ReqInsertOrder->Price, ReqInsertOrder->Volume, ReqInsertOrder->ClientOrderID);
	offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
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
	memcpy(buff + offset, ReqCancelOrder, sizeof(ReqCancelOrderField));
	offset += sizeof(ReqCancelOrderField);
	return offset;
}
bool ReqCancelOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	ReqCancelOrder = ::Allocate<ReqCancelOrderField>();
	memcpy(ReqCancelOrder, buff + offset, sizeof(ReqCancelOrderField));
	offset += sizeof(ReqCancelOrderField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* ReqCancelOrderPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "ReqCancelOrder:AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ClientCancelOrderID:[%d], OrderID:[%d], OrderSysID:[%s], SessionID:[%lld], ClientOrderID:[%d]", ReqCancelOrder->AccountID, ReqCancelOrder->ExchangeID, ReqCancelOrder->InstrumentID, ReqCancelOrder->ClientCancelOrderID, ReqCancelOrder->OrderID, ReqCancelOrder->OrderSysID, ReqCancelOrder->SessionID, ReqCancelOrder->ClientOrderID);
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
	memcpy(buff + offset, ReqCancelOrder, sizeof(ReqCancelOrderField));
	offset += sizeof(ReqCancelOrderField);
	memcpy(buff + offset, RspInfo, sizeof(RspInfoField));
	offset += sizeof(RspInfoField);
	return offset;
}
bool RspCancelOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	ReqCancelOrder = ::Allocate<ReqCancelOrderField>();
	memcpy(ReqCancelOrder, buff + offset, sizeof(ReqCancelOrderField));
	offset += sizeof(ReqCancelOrderField);
	RspInfo = ::Allocate<RspInfoField>();
	memcpy(RspInfo, buff + offset, sizeof(RspInfoField));
	offset += sizeof(RspInfoField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* RspCancelOrderPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "ReqCancelOrder:AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ClientCancelOrderID:[%d], OrderID:[%d], OrderSysID:[%s], SessionID:[%lld], ClientOrderID:[%d]", ReqCancelOrder->AccountID, ReqCancelOrder->ExchangeID, ReqCancelOrder->InstrumentID, ReqCancelOrder->ClientCancelOrderID, ReqCancelOrder->OrderID, ReqCancelOrder->OrderSysID, ReqCancelOrder->SessionID, ReqCancelOrder->ClientOrderID);
	offset += sprintf(t_DataStringBuffer + offset, "RspInfo:ErrorID:[%d], ErrorMsg:[%s]", RspInfo->ErrorID, RspInfo->ErrorMsg);
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
	memcpy(buff + offset, Order, sizeof(OrderField));
	offset += sizeof(OrderField);
	return offset;
}
bool RtnOrderPackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	Order = ::Allocate<OrderField>();
	memcpy(Order, buff + offset, sizeof(OrderField));
	offset += sizeof(OrderField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* RtnOrderPackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "Order:TradingDay:[%s], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], OrderSysID:[%s], Direction:[%d], OffsetFlag:[%d], OrderPriceType:[%d], Price:[%f], Volume:[%lld], VolumeTotal:[%lld], VolumeTraded:[%lld], VolumeMultiple:[%d], OrderStatus:[%d], OrderDate:[%s], OrderTime:[%s], CancelDate:[%s], CancelTime:[%s], SessionID:[%lld], ClientOrderID:[%d], RequestID:[%d], FrozenCash:[%f], FrozenMargin:[%f], FrozenCommission:[%f]", Order->TradingDay, Order->AccountID, Order->ExchangeID, Order->InstrumentID, (int)Order->ProductClass, Order->OrderID, Order->OrderSysID, (int)Order->Direction, (int)Order->OffsetFlag, (int)Order->OrderPriceType, Order->Price, Order->Volume, Order->VolumeTotal, Order->VolumeTraded, Order->VolumeMultiple, (int)Order->OrderStatus, Order->OrderDate, Order->OrderTime, Order->CancelDate, Order->CancelTime, Order->SessionID, Order->ClientOrderID, Order->RequestID, Order->FrozenCash, Order->FrozenMargin, Order->FrozenCommission);
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
	memcpy(buff + offset, Trade, sizeof(TradeField));
	offset += sizeof(TradeField);
	return offset;
}
bool RtnTradePackage::FromXtpStream(char* buff, int startIndex, int endIndex)
{
	int offset = startIndex;
	Trade = ::Allocate<TradeField>();
	memcpy(Trade, buff + offset, sizeof(TradeField));
	offset += sizeof(TradeField);
	if (offset != endIndex)
	{
		return false;
	}
	return true;
}
const char* RtnTradePackage::GetDebugString() const
{
	int offset = 0;
	offset += sprintf(t_DataStringBuffer + offset, "Trade:TradingDay:[%s], AccountID:[%s], ExchangeID:[%s], InstrumentID:[%s], ProductClass:[%d], OrderID:[%d], OrderSysID:[%s], TradeID:[%s], Direction:[%d], OffsetFlag:[%d], Price:[%f], Volume:[%lld], VolumeMultiple:[%d], TradeAmount:[%f], Commission:[%f], TradeDate:[%s], TradeTime:[%s]", Trade->TradingDay, Trade->AccountID, Trade->ExchangeID, Trade->InstrumentID, (int)Trade->ProductClass, Trade->OrderID, Trade->OrderSysID, Trade->TradeID, (int)Trade->Direction, (int)Trade->OffsetFlag, Trade->Price, Trade->Volume, Trade->VolumeMultiple, Trade->TradeAmount, Trade->Commission, Trade->TradeDate, Trade->TradeTime);
	return t_DataStringBuffer;
}
