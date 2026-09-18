// 本文件由 ../Templates/Cpp/Mdb/InitMdbFromCsv.cpp.tpl 生成；请勿手改，改动请改模板后重跑 pumpall.py
#include "InitMdbFromCsv.h"
#include <Spark/Serialization/Csv/CsvRecord.h>
#include <Spark/Core/Utility/Utility.h>
#include <fstream>
#include <assert.h>

using namespace Spark::Core;
using namespace Spark::Serialization;


namespace QuantTrading
{
	static char HeaderBuffer[1024] = { 0 };
	static char ContentBuffer[64 * 1024] = { 0 };

	void InitMdbFromCsv::LoadTables(Mdb* mdb, const char* dir, const TableList& tableList)
	{
		for (int i = 0; i < tableList.Count; ++i)
		{
			switch (tableList.TableIds[i])
			{
			case TradingDay::TableId:  LoadTradingDayTable(mdb, dir); break;
			case Exchange::TableId:  LoadExchangeTable(mdb, dir); break;
			case Product::TableId:  LoadProductTable(mdb, dir); break;
			case HotInstrument::TableId:  LoadHotInstrumentTable(mdb, dir); break;
			case Instrument::TableId:  LoadInstrumentTable(mdb, dir); break;
			case DepthMarketData::TableId:  LoadDepthMarketDataTable(mdb, dir); break;
			case BarMarketData::TableId:  LoadBarMarketDataTable(mdb, dir); break;
			case MdSubscribe::TableId:  LoadMdSubscribeTable(mdb, dir); break;
			case MdUser::TableId:  LoadMdUserTable(mdb, dir); break;
			case PrimaryAccount::TableId:  LoadPrimaryAccountTable(mdb, dir); break;
			case Account::TableId:  LoadAccountTable(mdb, dir); break;
			case Capital::TableId:  LoadCapitalTable(mdb, dir); break;
			case Position::TableId:  LoadPositionTable(mdb, dir); break;
			case PositionDetail::TableId:  LoadPositionDetailTable(mdb, dir); break;
			case Order::TableId:  LoadOrderTable(mdb, dir); break;
			case Trade::TableId:  LoadTradeTable(mdb, dir); break;
			case CommissionGroup::TableId:  LoadCommissionGroupTable(mdb, dir); break;
			case BaseCommission::TableId:  LoadBaseCommissionTable(mdb, dir); break;
			default: break;
			}
		}
	}

	void InitMdbFromCsv::LoadTradingDayTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		snprintf(fullPath, sizeof(fullPath), "%s/t_TradingDay.csv", dir);
		std::fstream file(fullPath, std::fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CsvRecord csvRecord;
		if (!csvRecord.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_TradingDay.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csvRecord.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_TradingDay.csv failed");
			}

			auto record = TradingDay::Allocate();
			record->Pk = csvRecord.GetFieldAsInt("Pk");
			Utility::Strcpy(record->CurrTradingDay, csvRecord.GetFieldAsString("CurrTradingDay"));
			Utility::Strcpy(record->PreTradingDay, csvRecord.GetFieldAsString("PreTradingDay"));
			mdb->TradingDay->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadExchangeTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		snprintf(fullPath, sizeof(fullPath), "%s/t_Exchange.csv", dir);
		std::fstream file(fullPath, std::fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CsvRecord csvRecord;
		if (!csvRecord.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_Exchange.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csvRecord.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_Exchange.csv failed");
			}

			auto record = Exchange::Allocate();
			Utility::Strcpy(record->ExchangeId, csvRecord.GetFieldAsString("ExchangeId"));
			Utility::Strcpy(record->ExchangeName, csvRecord.GetFieldAsString("ExchangeName"));
			mdb->Exchange->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadProductTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		snprintf(fullPath, sizeof(fullPath), "%s/t_Product.csv", dir);
		std::fstream file(fullPath, std::fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CsvRecord csvRecord;
		if (!csvRecord.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_Product.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csvRecord.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_Product.csv failed");
			}

			auto record = Product::Allocate();
			Utility::Strcpy(record->ExchangeId, csvRecord.GetFieldAsString("ExchangeId"));
			Utility::Strcpy(record->ProductId, csvRecord.GetFieldAsString("ProductId"));
			Utility::Strcpy(record->ProductName, csvRecord.GetFieldAsString("ProductName"));
			record->ProductClass = static_cast<ProductClassType>(csvRecord.GetFieldAsInt("ProductClass"));
			record->VolumeMultiple = csvRecord.GetFieldAsInt("VolumeMultiple");
			record->PriceTick = csvRecord.GetFieldAsDouble("PriceTick");
			record->MaxMarketOrderVolume = csvRecord.GetFieldAsInt64("MaxMarketOrderVolume");
			record->MinMarketOrderVolume = csvRecord.GetFieldAsInt64("MinMarketOrderVolume");
			record->MaxLimitOrderVolume = csvRecord.GetFieldAsInt64("MaxLimitOrderVolume");
			record->MinLimitOrderVolume = csvRecord.GetFieldAsInt64("MinLimitOrderVolume");
			Utility::Strcpy(record->SessionName, csvRecord.GetFieldAsString("SessionName"));
			mdb->Product->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadHotInstrumentTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		snprintf(fullPath, sizeof(fullPath), "%s/t_HotInstrument.csv", dir);
		std::fstream file(fullPath, std::fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CsvRecord csvRecord;
		if (!csvRecord.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_HotInstrument.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csvRecord.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_HotInstrument.csv failed");
			}

			auto record = HotInstrument::Allocate();
			Utility::Strcpy(record->TradingDay, csvRecord.GetFieldAsString("TradingDay"));
			Utility::Strcpy(record->ExchangeId, csvRecord.GetFieldAsString("ExchangeId"));
			Utility::Strcpy(record->ProductId, csvRecord.GetFieldAsString("ProductId"));
			Utility::Strcpy(record->InstrumentId, csvRecord.GetFieldAsString("InstrumentId"));
			record->ProductClass = static_cast<ProductClassType>(csvRecord.GetFieldAsInt("ProductClass"));
			record->Volume = csvRecord.GetFieldAsInt64("Volume");
			record->MaxVolume = csvRecord.GetFieldAsInt64("MaxVolume");
			record->Turnover = csvRecord.GetFieldAsDouble("Turnover");
			record->MaxTurnover = csvRecord.GetFieldAsDouble("MaxTurnover");
			record->OpenInterest = csvRecord.GetFieldAsDouble("OpenInterest");
			record->MaxOpenInterest = csvRecord.GetFieldAsDouble("MaxOpenInterest");
			record->Rank = csvRecord.GetFieldAsInt("Rank");
			mdb->HotInstrument->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadInstrumentTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		snprintf(fullPath, sizeof(fullPath), "%s/t_Instrument.csv", dir);
		std::fstream file(fullPath, std::fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CsvRecord csvRecord;
		if (!csvRecord.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_Instrument.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csvRecord.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_Instrument.csv failed");
			}

			auto record = Instrument::Allocate();
			Utility::Strcpy(record->ExchangeId, csvRecord.GetFieldAsString("ExchangeId"));
			Utility::Strcpy(record->InstrumentId, csvRecord.GetFieldAsString("InstrumentId"));
			Utility::Strcpy(record->ExchangeInstId, csvRecord.GetFieldAsString("ExchangeInstId"));
			Utility::Strcpy(record->InstrumentName, csvRecord.GetFieldAsString("InstrumentName"));
			Utility::Strcpy(record->ProductId, csvRecord.GetFieldAsString("ProductId"));
			record->ProductClass = static_cast<ProductClassType>(csvRecord.GetFieldAsInt("ProductClass"));
			record->InstrumentClass = static_cast<InstrumentClassType>(csvRecord.GetFieldAsInt("InstrumentClass"));
			record->Rank = csvRecord.GetFieldAsInt("Rank");
			record->VolumeMultiple = csvRecord.GetFieldAsInt("VolumeMultiple");
			record->PriceTick = csvRecord.GetFieldAsDouble("PriceTick");
			record->MaxMarketOrderVolume = csvRecord.GetFieldAsInt64("MaxMarketOrderVolume");
			record->MinMarketOrderVolume = csvRecord.GetFieldAsInt64("MinMarketOrderVolume");
			record->MaxLimitOrderVolume = csvRecord.GetFieldAsInt64("MaxLimitOrderVolume");
			record->MinLimitOrderVolume = csvRecord.GetFieldAsInt64("MinLimitOrderVolume");
			Utility::Strcpy(record->SessionName, csvRecord.GetFieldAsString("SessionName"));
			mdb->Instrument->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadDepthMarketDataTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		snprintf(fullPath, sizeof(fullPath), "%s/t_DepthMarketData.csv", dir);
		std::fstream file(fullPath, std::fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CsvRecord csvRecord;
		if (!csvRecord.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_DepthMarketData.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csvRecord.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_DepthMarketData.csv failed");
			}

			auto record = DepthMarketData::Allocate();
			Utility::Strcpy(record->TradingDay, csvRecord.GetFieldAsString("TradingDay"));
			Utility::Strcpy(record->ExchangeId, csvRecord.GetFieldAsString("ExchangeId"));
			Utility::Strcpy(record->InstrumentId, csvRecord.GetFieldAsString("InstrumentId"));
			record->UpdateTs = csvRecord.GetFieldAsInt64("UpdateTs");
			record->LastPrice = csvRecord.GetFieldAsDouble("LastPrice");
			record->PreSettlementPrice = csvRecord.GetFieldAsDouble("PreSettlementPrice");
			record->PreClosePrice = csvRecord.GetFieldAsDouble("PreClosePrice");
			record->PreOpenInterest = csvRecord.GetFieldAsDouble("PreOpenInterest");
			record->OpenPrice = csvRecord.GetFieldAsDouble("OpenPrice");
			record->HighestPrice = csvRecord.GetFieldAsDouble("HighestPrice");
			record->LowestPrice = csvRecord.GetFieldAsDouble("LowestPrice");
			record->ClosePrice = csvRecord.GetFieldAsDouble("ClosePrice");
			record->CurrVolume = csvRecord.GetFieldAsInt64("CurrVolume");
			record->Volume = csvRecord.GetFieldAsInt64("Volume");
			record->CurrTurnover = csvRecord.GetFieldAsDouble("CurrTurnover");
			record->Turnover = csvRecord.GetFieldAsDouble("Turnover");
			record->OpenInterest = csvRecord.GetFieldAsDouble("OpenInterest");
			record->SettlementPrice = csvRecord.GetFieldAsDouble("SettlementPrice");
			record->UpperLimitPrice = csvRecord.GetFieldAsDouble("UpperLimitPrice");
			record->LowerLimitPrice = csvRecord.GetFieldAsDouble("LowerLimitPrice");
			record->AveragePrice = csvRecord.GetFieldAsDouble("AveragePrice");
			record->AskPrice1 = csvRecord.GetFieldAsDouble("AskPrice1");
			record->AskPrice2 = csvRecord.GetFieldAsDouble("AskPrice2");
			record->AskPrice3 = csvRecord.GetFieldAsDouble("AskPrice3");
			record->AskPrice4 = csvRecord.GetFieldAsDouble("AskPrice4");
			record->AskPrice5 = csvRecord.GetFieldAsDouble("AskPrice5");
			record->AskPrice6 = csvRecord.GetFieldAsDouble("AskPrice6");
			record->AskPrice7 = csvRecord.GetFieldAsDouble("AskPrice7");
			record->AskPrice8 = csvRecord.GetFieldAsDouble("AskPrice8");
			record->AskPrice9 = csvRecord.GetFieldAsDouble("AskPrice9");
			record->AskPrice10 = csvRecord.GetFieldAsDouble("AskPrice10");
			record->AskVolume1 = csvRecord.GetFieldAsInt64("AskVolume1");
			record->AskVolume2 = csvRecord.GetFieldAsInt64("AskVolume2");
			record->AskVolume3 = csvRecord.GetFieldAsInt64("AskVolume3");
			record->AskVolume4 = csvRecord.GetFieldAsInt64("AskVolume4");
			record->AskVolume5 = csvRecord.GetFieldAsInt64("AskVolume5");
			record->AskVolume6 = csvRecord.GetFieldAsInt64("AskVolume6");
			record->AskVolume7 = csvRecord.GetFieldAsInt64("AskVolume7");
			record->AskVolume8 = csvRecord.GetFieldAsInt64("AskVolume8");
			record->AskVolume9 = csvRecord.GetFieldAsInt64("AskVolume9");
			record->AskVolume10 = csvRecord.GetFieldAsInt64("AskVolume10");
			record->BidPrice1 = csvRecord.GetFieldAsDouble("BidPrice1");
			record->BidPrice2 = csvRecord.GetFieldAsDouble("BidPrice2");
			record->BidPrice3 = csvRecord.GetFieldAsDouble("BidPrice3");
			record->BidPrice4 = csvRecord.GetFieldAsDouble("BidPrice4");
			record->BidPrice5 = csvRecord.GetFieldAsDouble("BidPrice5");
			record->BidPrice6 = csvRecord.GetFieldAsDouble("BidPrice6");
			record->BidPrice7 = csvRecord.GetFieldAsDouble("BidPrice7");
			record->BidPrice8 = csvRecord.GetFieldAsDouble("BidPrice8");
			record->BidPrice9 = csvRecord.GetFieldAsDouble("BidPrice9");
			record->BidPrice10 = csvRecord.GetFieldAsDouble("BidPrice10");
			record->BidVolume1 = csvRecord.GetFieldAsInt64("BidVolume1");
			record->BidVolume2 = csvRecord.GetFieldAsInt64("BidVolume2");
			record->BidVolume3 = csvRecord.GetFieldAsInt64("BidVolume3");
			record->BidVolume4 = csvRecord.GetFieldAsInt64("BidVolume4");
			record->BidVolume5 = csvRecord.GetFieldAsInt64("BidVolume5");
			record->BidVolume6 = csvRecord.GetFieldAsInt64("BidVolume6");
			record->BidVolume7 = csvRecord.GetFieldAsInt64("BidVolume7");
			record->BidVolume8 = csvRecord.GetFieldAsInt64("BidVolume8");
			record->BidVolume9 = csvRecord.GetFieldAsInt64("BidVolume9");
			record->BidVolume10 = csvRecord.GetFieldAsInt64("BidVolume10");
			mdb->DepthMarketData->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadBarMarketDataTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		snprintf(fullPath, sizeof(fullPath), "%s/t_BarMarketData.csv", dir);
		std::fstream file(fullPath, std::fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CsvRecord csvRecord;
		if (!csvRecord.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_BarMarketData.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csvRecord.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_BarMarketData.csv failed");
			}

			auto record = BarMarketData::Allocate();
			Utility::Strcpy(record->TradingDay, csvRecord.GetFieldAsString("TradingDay"));
			Utility::Strcpy(record->ExchangeId, csvRecord.GetFieldAsString("ExchangeId"));
			Utility::Strcpy(record->InstrumentId, csvRecord.GetFieldAsString("InstrumentId"));
			record->BarPreces = static_cast<BarPrecesType>(csvRecord.GetFieldAsInt("BarPreces"));
			record->BarPeriod = csvRecord.GetFieldAsInt("BarPeriod");
			record->BarTime = csvRecord.GetFieldAsInt64("BarTime");
			record->UpdateTs = csvRecord.GetFieldAsInt64("UpdateTs");
			record->PreSettlementPrice = csvRecord.GetFieldAsDouble("PreSettlementPrice");
			record->PreClosePrice = csvRecord.GetFieldAsDouble("PreClosePrice");
			record->HighestPrice = csvRecord.GetFieldAsDouble("HighestPrice");
			record->LowestPrice = csvRecord.GetFieldAsDouble("LowestPrice");
			record->Open = csvRecord.GetFieldAsDouble("Open");
			record->High = csvRecord.GetFieldAsDouble("High");
			record->Low = csvRecord.GetFieldAsDouble("Low");
			record->Close = csvRecord.GetFieldAsDouble("Close");
			record->CurrVolume = csvRecord.GetFieldAsInt64("CurrVolume");
			record->Volume = csvRecord.GetFieldAsInt64("Volume");
			record->CurrTurnover = csvRecord.GetFieldAsDouble("CurrTurnover");
			record->Turnover = csvRecord.GetFieldAsDouble("Turnover");
			record->OpenInterest = csvRecord.GetFieldAsDouble("OpenInterest");
			mdb->BarMarketData->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadMdSubscribeTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		snprintf(fullPath, sizeof(fullPath), "%s/t_MdSubscribe.csv", dir);
		std::fstream file(fullPath, std::fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CsvRecord csvRecord;
		if (!csvRecord.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_MdSubscribe.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csvRecord.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_MdSubscribe.csv failed");
			}

			auto record = MdSubscribe::Allocate();
			Utility::Strcpy(record->ExchangeId, csvRecord.GetFieldAsString("ExchangeId"));
			Utility::Strcpy(record->InstrumentId, csvRecord.GetFieldAsString("InstrumentId"));
			Utility::Strcpy(record->RealInstrumentId, csvRecord.GetFieldAsString("RealInstrumentId"));
			Utility::Strcpy(record->ProductId, csvRecord.GetFieldAsString("ProductId"));
			record->ProductClass = static_cast<ProductClassType>(csvRecord.GetFieldAsInt("ProductClass"));
			Utility::Strcpy(record->StartTradingDay, csvRecord.GetFieldAsString("StartTradingDay"));
			Utility::Strcpy(record->EndTradingDay, csvRecord.GetFieldAsString("EndTradingDay"));
			mdb->MdSubscribe->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadMdUserTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		snprintf(fullPath, sizeof(fullPath), "%s/t_MdUser.csv", dir);
		std::fstream file(fullPath, std::fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CsvRecord csvRecord;
		if (!csvRecord.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_MdUser.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csvRecord.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_MdUser.csv failed");
			}

			auto record = MdUser::Allocate();
			Utility::Strcpy(record->MdUserId, csvRecord.GetFieldAsString("MdUserId"));
			Utility::Strcpy(record->MdUserName, csvRecord.GetFieldAsString("MdUserName"));
			Utility::Strcpy(record->Password, csvRecord.GetFieldAsString("Password"));
			mdb->MdUser->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadPrimaryAccountTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		snprintf(fullPath, sizeof(fullPath), "%s/t_PrimaryAccount.csv", dir);
		std::fstream file(fullPath, std::fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CsvRecord csvRecord;
		if (!csvRecord.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_PrimaryAccount.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csvRecord.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_PrimaryAccount.csv failed");
			}

			auto record = PrimaryAccount::Allocate();
			Utility::Strcpy(record->PrimaryAccountId, csvRecord.GetFieldAsString("PrimaryAccountId"));
			Utility::Strcpy(record->PrimaryAccountName, csvRecord.GetFieldAsString("PrimaryAccountName"));
			record->AccountClass = static_cast<AccountClassType>(csvRecord.GetFieldAsInt("AccountClass"));
			Utility::Strcpy(record->Password, csvRecord.GetFieldAsString("Password"));
			record->OfferId = csvRecord.GetFieldAsInt("OfferId");
			record->IsAllowLogin = static_cast<bool>(csvRecord.GetFieldAsInt("IsAllowLogin"));
			record->IsSimulateAccount = static_cast<bool>(csvRecord.GetFieldAsInt("IsSimulateAccount"));
			record->LoginStatus = static_cast<LoginStatusType>(csvRecord.GetFieldAsInt("LoginStatus"));
			record->InitStatus = static_cast<InitStatusType>(csvRecord.GetFieldAsInt("InitStatus"));
			mdb->PrimaryAccount->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadAccountTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		snprintf(fullPath, sizeof(fullPath), "%s/t_Account.csv", dir);
		std::fstream file(fullPath, std::fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CsvRecord csvRecord;
		if (!csvRecord.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_Account.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csvRecord.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_Account.csv failed");
			}

			auto record = Account::Allocate();
			Utility::Strcpy(record->AccountId, csvRecord.GetFieldAsString("AccountId"));
			Utility::Strcpy(record->AccountName, csvRecord.GetFieldAsString("AccountName"));
			record->AccountType = static_cast<AccountTypeType>(csvRecord.GetFieldAsInt("AccountType"));
			record->AccountStatus = static_cast<AccountStatusType>(csvRecord.GetFieldAsInt("AccountStatus"));
			Utility::Strcpy(record->Password, csvRecord.GetFieldAsString("Password"));
			record->TradeGroupId = csvRecord.GetFieldAsInt("TradeGroupId");
			record->RiskGroupId = csvRecord.GetFieldAsInt("RiskGroupId");
			record->CommissionGroupId = csvRecord.GetFieldAsInt("CommissionGroupId");
			mdb->Account->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadCapitalTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		snprintf(fullPath, sizeof(fullPath), "%s/t_Capital.csv", dir);
		std::fstream file(fullPath, std::fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CsvRecord csvRecord;
		if (!csvRecord.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_Capital.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csvRecord.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_Capital.csv failed");
			}

			auto record = Capital::Allocate();
			Utility::Strcpy(record->TradingDay, csvRecord.GetFieldAsString("TradingDay"));
			Utility::Strcpy(record->AccountId, csvRecord.GetFieldAsString("AccountId"));
			record->AccountType = static_cast<AccountTypeType>(csvRecord.GetFieldAsInt("AccountType"));
			record->Balance = csvRecord.GetFieldAsDouble("Balance");
			record->PreBalance = csvRecord.GetFieldAsDouble("PreBalance");
			record->Available = csvRecord.GetFieldAsDouble("Available");
			record->MarketValue = csvRecord.GetFieldAsDouble("MarketValue");
			record->CashIn = csvRecord.GetFieldAsDouble("CashIn");
			record->CashOut = csvRecord.GetFieldAsDouble("CashOut");
			record->Margin = csvRecord.GetFieldAsDouble("Margin");
			record->Commission = csvRecord.GetFieldAsDouble("Commission");
			record->FrozenCash = csvRecord.GetFieldAsDouble("FrozenCash");
			record->FrozenMargin = csvRecord.GetFieldAsDouble("FrozenMargin");
			record->FrozenCommission = csvRecord.GetFieldAsDouble("FrozenCommission");
			record->CloseProfitByDate = csvRecord.GetFieldAsDouble("CloseProfitByDate");
			record->CloseProfitByTrade = csvRecord.GetFieldAsDouble("CloseProfitByTrade");
			record->PositionProfitByDate = csvRecord.GetFieldAsDouble("PositionProfitByDate");
			record->PositionProfitByTrade = csvRecord.GetFieldAsDouble("PositionProfitByTrade");
			record->Deposit = csvRecord.GetFieldAsDouble("Deposit");
			record->Withdraw = csvRecord.GetFieldAsDouble("Withdraw");
			record->StampTax = csvRecord.GetFieldAsDouble("StampTax");
			record->TransferFee = csvRecord.GetFieldAsDouble("TransferFee");
			mdb->Capital->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadPositionTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		snprintf(fullPath, sizeof(fullPath), "%s/t_Position.csv", dir);
		std::fstream file(fullPath, std::fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CsvRecord csvRecord;
		if (!csvRecord.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_Position.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csvRecord.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_Position.csv failed");
			}

			auto record = Position::Allocate();
			Utility::Strcpy(record->TradingDay, csvRecord.GetFieldAsString("TradingDay"));
			Utility::Strcpy(record->AccountId, csvRecord.GetFieldAsString("AccountId"));
			record->AccountType = static_cast<AccountTypeType>(csvRecord.GetFieldAsInt("AccountType"));
			Utility::Strcpy(record->ExchangeId, csvRecord.GetFieldAsString("ExchangeId"));
			Utility::Strcpy(record->InstrumentId, csvRecord.GetFieldAsString("InstrumentId"));
			record->ProductClass = static_cast<ProductClassType>(csvRecord.GetFieldAsInt("ProductClass"));
			record->PosiDirection = static_cast<PosiDirectionType>(csvRecord.GetFieldAsInt("PosiDirection"));
			record->TotalPosition = csvRecord.GetFieldAsInt64("TotalPosition");
			record->PositionFrozen = csvRecord.GetFieldAsInt64("PositionFrozen");
			record->TodayPosition = csvRecord.GetFieldAsInt64("TodayPosition");
			record->MarketValue = csvRecord.GetFieldAsDouble("MarketValue");
			record->CashIn = csvRecord.GetFieldAsDouble("CashIn");
			record->CashOut = csvRecord.GetFieldAsDouble("CashOut");
			record->Margin = csvRecord.GetFieldAsDouble("Margin");
			record->Commission = csvRecord.GetFieldAsDouble("Commission");
			record->FrozenCash = csvRecord.GetFieldAsDouble("FrozenCash");
			record->FrozenMargin = csvRecord.GetFieldAsDouble("FrozenMargin");
			record->FrozenCommission = csvRecord.GetFieldAsDouble("FrozenCommission");
			record->VolumeMultiple = csvRecord.GetFieldAsInt("VolumeMultiple");
			record->CloseProfitByDate = csvRecord.GetFieldAsDouble("CloseProfitByDate");
			record->CloseProfitByTrade = csvRecord.GetFieldAsDouble("CloseProfitByTrade");
			record->PositionProfitByDate = csvRecord.GetFieldAsDouble("PositionProfitByDate");
			record->PositionProfitByTrade = csvRecord.GetFieldAsDouble("PositionProfitByTrade");
			record->SettlementPrice = csvRecord.GetFieldAsDouble("SettlementPrice");
			record->PreSettlementPrice = csvRecord.GetFieldAsDouble("PreSettlementPrice");
			record->StampTax = csvRecord.GetFieldAsDouble("StampTax");
			record->TransferFee = csvRecord.GetFieldAsDouble("TransferFee");
			mdb->Position->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadPositionDetailTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		snprintf(fullPath, sizeof(fullPath), "%s/t_PositionDetail.csv", dir);
		std::fstream file(fullPath, std::fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CsvRecord csvRecord;
		if (!csvRecord.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_PositionDetail.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csvRecord.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_PositionDetail.csv failed");
			}

			auto record = PositionDetail::Allocate();
			Utility::Strcpy(record->TradingDay, csvRecord.GetFieldAsString("TradingDay"));
			Utility::Strcpy(record->AccountId, csvRecord.GetFieldAsString("AccountId"));
			record->AccountType = static_cast<AccountTypeType>(csvRecord.GetFieldAsInt("AccountType"));
			Utility::Strcpy(record->ExchangeId, csvRecord.GetFieldAsString("ExchangeId"));
			Utility::Strcpy(record->InstrumentId, csvRecord.GetFieldAsString("InstrumentId"));
			record->ProductClass = static_cast<ProductClassType>(csvRecord.GetFieldAsInt("ProductClass"));
			record->PosiDirection = static_cast<PosiDirectionType>(csvRecord.GetFieldAsInt("PosiDirection"));
			Utility::Strcpy(record->OpenDate, csvRecord.GetFieldAsString("OpenDate"));
			Utility::Strcpy(record->TradeId, csvRecord.GetFieldAsString("TradeId"));
			record->Volume = csvRecord.GetFieldAsInt64("Volume");
			record->OpenPrice = csvRecord.GetFieldAsDouble("OpenPrice");
			record->MarketValue = csvRecord.GetFieldAsDouble("MarketValue");
			record->CashIn = csvRecord.GetFieldAsDouble("CashIn");
			record->CashOut = csvRecord.GetFieldAsDouble("CashOut");
			record->Margin = csvRecord.GetFieldAsDouble("Margin");
			record->Commission = csvRecord.GetFieldAsDouble("Commission");
			record->VolumeMultiple = csvRecord.GetFieldAsInt("VolumeMultiple");
			record->CloseProfitByDate = csvRecord.GetFieldAsDouble("CloseProfitByDate");
			record->CloseProfitByTrade = csvRecord.GetFieldAsDouble("CloseProfitByTrade");
			record->PositionProfitByDate = csvRecord.GetFieldAsDouble("PositionProfitByDate");
			record->PositionProfitByTrade = csvRecord.GetFieldAsDouble("PositionProfitByTrade");
			record->SettlementPrice = csvRecord.GetFieldAsDouble("SettlementPrice");
			record->PreSettlementPrice = csvRecord.GetFieldAsDouble("PreSettlementPrice");
			record->CloseVolume = csvRecord.GetFieldAsInt64("CloseVolume");
			record->CloseAmount = csvRecord.GetFieldAsDouble("CloseAmount");
			record->StampTax = csvRecord.GetFieldAsDouble("StampTax");
			record->TransferFee = csvRecord.GetFieldAsDouble("TransferFee");
			mdb->PositionDetail->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadOrderTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		snprintf(fullPath, sizeof(fullPath), "%s/t_Order.csv", dir);
		std::fstream file(fullPath, std::fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CsvRecord csvRecord;
		if (!csvRecord.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_Order.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csvRecord.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_Order.csv failed");
			}

			auto record = Order::Allocate();
			Utility::Strcpy(record->TradingDay, csvRecord.GetFieldAsString("TradingDay"));
			Utility::Strcpy(record->AccountId, csvRecord.GetFieldAsString("AccountId"));
			record->AccountType = static_cast<AccountTypeType>(csvRecord.GetFieldAsInt("AccountType"));
			Utility::Strcpy(record->ExchangeId, csvRecord.GetFieldAsString("ExchangeId"));
			Utility::Strcpy(record->InstrumentId, csvRecord.GetFieldAsString("InstrumentId"));
			record->ProductClass = static_cast<ProductClassType>(csvRecord.GetFieldAsInt("ProductClass"));
			record->OrderId = csvRecord.GetFieldAsInt("OrderId");
			Utility::Strcpy(record->OrderSysId, csvRecord.GetFieldAsString("OrderSysId"));
			record->Direction = static_cast<DirectionType>(csvRecord.GetFieldAsInt("Direction"));
			record->OffsetFlag = static_cast<OffsetFlagType>(csvRecord.GetFieldAsInt("OffsetFlag"));
			record->OrderPriceType = static_cast<OrderPriceTypeType>(csvRecord.GetFieldAsInt("OrderPriceType"));
			record->Price = csvRecord.GetFieldAsDouble("Price");
			record->Volume = csvRecord.GetFieldAsInt64("Volume");
			record->VolumeTotal = csvRecord.GetFieldAsInt64("VolumeTotal");
			record->VolumeTraded = csvRecord.GetFieldAsInt64("VolumeTraded");
			record->VolumeMultiple = csvRecord.GetFieldAsInt("VolumeMultiple");
			record->OrderStatus = static_cast<OrderStatusType>(csvRecord.GetFieldAsInt("OrderStatus"));
			Utility::Strcpy(record->OrderDate, csvRecord.GetFieldAsString("OrderDate"));
			Utility::Strcpy(record->OrderTime, csvRecord.GetFieldAsString("OrderTime"));
			Utility::Strcpy(record->CancelDate, csvRecord.GetFieldAsString("CancelDate"));
			Utility::Strcpy(record->CancelTime, csvRecord.GetFieldAsString("CancelTime"));
			record->SessionId = csvRecord.GetFieldAsInt64("SessionId");
			record->ClientOrderId = csvRecord.GetFieldAsInt("ClientOrderId");
			record->RequestId = csvRecord.GetFieldAsInt("RequestId");
			record->OfferId = csvRecord.GetFieldAsInt("OfferId");
			record->TradeGroupId = csvRecord.GetFieldAsInt("TradeGroupId");
			record->RiskGroupId = csvRecord.GetFieldAsInt("RiskGroupId");
			record->CommissionGroupId = csvRecord.GetFieldAsInt("CommissionGroupId");
			record->FrozenCash = csvRecord.GetFieldAsDouble("FrozenCash");
			record->FrozenMargin = csvRecord.GetFieldAsDouble("FrozenMargin");
			record->FrozenCommission = csvRecord.GetFieldAsDouble("FrozenCommission");
			record->RebuildMark = static_cast<bool>(csvRecord.GetFieldAsInt("RebuildMark"));
			record->IsForceClose = static_cast<bool>(csvRecord.GetFieldAsInt("IsForceClose"));
			mdb->Order->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadTradeTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		snprintf(fullPath, sizeof(fullPath), "%s/t_Trade.csv", dir);
		std::fstream file(fullPath, std::fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CsvRecord csvRecord;
		if (!csvRecord.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_Trade.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csvRecord.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_Trade.csv failed");
			}

			auto record = Trade::Allocate();
			Utility::Strcpy(record->TradingDay, csvRecord.GetFieldAsString("TradingDay"));
			Utility::Strcpy(record->AccountId, csvRecord.GetFieldAsString("AccountId"));
			record->AccountType = static_cast<AccountTypeType>(csvRecord.GetFieldAsInt("AccountType"));
			Utility::Strcpy(record->ExchangeId, csvRecord.GetFieldAsString("ExchangeId"));
			Utility::Strcpy(record->InstrumentId, csvRecord.GetFieldAsString("InstrumentId"));
			record->ProductClass = static_cast<ProductClassType>(csvRecord.GetFieldAsInt("ProductClass"));
			record->OrderId = csvRecord.GetFieldAsInt("OrderId");
			Utility::Strcpy(record->OrderSysId, csvRecord.GetFieldAsString("OrderSysId"));
			Utility::Strcpy(record->TradeId, csvRecord.GetFieldAsString("TradeId"));
			record->Direction = static_cast<DirectionType>(csvRecord.GetFieldAsInt("Direction"));
			record->OffsetFlag = static_cast<OffsetFlagType>(csvRecord.GetFieldAsInt("OffsetFlag"));
			record->Price = csvRecord.GetFieldAsDouble("Price");
			record->Volume = csvRecord.GetFieldAsInt64("Volume");
			record->VolumeMultiple = csvRecord.GetFieldAsInt("VolumeMultiple");
			record->TradeAmount = csvRecord.GetFieldAsDouble("TradeAmount");
			record->Commission = csvRecord.GetFieldAsDouble("Commission");
			Utility::Strcpy(record->TradeDate, csvRecord.GetFieldAsString("TradeDate"));
			Utility::Strcpy(record->TradeTime, csvRecord.GetFieldAsString("TradeTime"));
			record->StampTax = csvRecord.GetFieldAsDouble("StampTax");
			record->TransferFee = csvRecord.GetFieldAsDouble("TransferFee");
			mdb->Trade->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadCommissionGroupTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		snprintf(fullPath, sizeof(fullPath), "%s/t_CommissionGroup.csv", dir);
		std::fstream file(fullPath, std::fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CsvRecord csvRecord;
		if (!csvRecord.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_CommissionGroup.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csvRecord.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_CommissionGroup.csv failed");
			}

			auto record = CommissionGroup::Allocate();
			record->CommissionGroupId = csvRecord.GetFieldAsInt("CommissionGroupId");
			Utility::Strcpy(record->CommissionGroupName, csvRecord.GetFieldAsString("CommissionGroupName"));
			mdb->CommissionGroup->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadBaseCommissionTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		snprintf(fullPath, sizeof(fullPath), "%s/t_BaseCommission.csv", dir);
		std::fstream file(fullPath, std::fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CsvRecord csvRecord;
		if (!csvRecord.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_BaseCommission.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csvRecord.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_BaseCommission.csv failed");
			}

			auto record = BaseCommission::Allocate();
			record->CommissionGroupId = csvRecord.GetFieldAsInt("CommissionGroupId");
			Utility::Strcpy(record->ExchangeId, csvRecord.GetFieldAsString("ExchangeId"));
			Utility::Strcpy(record->InstrumentId, csvRecord.GetFieldAsString("InstrumentId"));
			record->Direction = static_cast<DirectionType>(csvRecord.GetFieldAsInt("Direction"));
			record->OpenByMoney = csvRecord.GetFieldAsDouble("OpenByMoney");
			record->CloseByMoney = csvRecord.GetFieldAsDouble("CloseByMoney");
			record->OpenByVolume = csvRecord.GetFieldAsDouble("OpenByVolume");
			record->CloseByVolume = csvRecord.GetFieldAsDouble("CloseByVolume");
			record->OpenStampTaxByMoney = csvRecord.GetFieldAsDouble("OpenStampTaxByMoney");
			record->CloseStampTaxByMoney = csvRecord.GetFieldAsDouble("CloseStampTaxByMoney");
			record->OpenTransferFeeByMoney = csvRecord.GetFieldAsDouble("OpenTransferFeeByMoney");
			record->CloseTransferFeeByMoney = csvRecord.GetFieldAsDouble("CloseTransferFeeByMoney");
			record->MinCommission = csvRecord.GetFieldAsDouble("MinCommission");
			record->MaxCommission = csvRecord.GetFieldAsDouble("MaxCommission");
			mdb->BaseCommission->Insert(record);
		}
		file.close();
	}
}
