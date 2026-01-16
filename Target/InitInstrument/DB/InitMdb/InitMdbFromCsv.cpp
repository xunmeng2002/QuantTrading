#include "InitMdbFromCsv.h"
#include "CsvRecord.h"
#include "Utility.h"
#include <fstream>
#include <assert.h>

using namespace std;


namespace mdb
{
	static char HeaderBuffer[1024] = { 0 };
	static char ContentBuffer[64 * 1024] = { 0 };

	void InitMdbFromCsv::LoadTables(Mdb* mdb, const char* dir)
	{

		LoadTradingDayTable(mdb, dir);
		LoadExchangeTable(mdb, dir);
		LoadProductTable(mdb, dir);
		LoadHotInstrumentTable(mdb, dir);
		LoadInstrumentTable(mdb, dir);
		LoadAccountTable(mdb, dir);
	}

	void InitMdbFromCsv::LoadTradingDayTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		sprintf(fullPath, "%s/t_TradingDay.csv", dir);
		fstream file(fullPath, fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CSVRecord csv_record;
		if (!csv_record.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_TradingDay.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csv_record.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_TradingDay.csv failed");
			}

			auto record = new TradingDay();
			record->PK = csv_record.GetFieldAsInt("PK");
			Strcpy(record->CurrTradingDay, csv_record.GetFieldAsString("CurrTradingDay"));
			Strcpy(record->PreTradingDay, csv_record.GetFieldAsString("PreTradingDay"));
			mdb->t_TradingDay->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadExchangeTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		sprintf(fullPath, "%s/t_Exchange.csv", dir);
		fstream file(fullPath, fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CSVRecord csv_record;
		if (!csv_record.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_Exchange.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csv_record.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_Exchange.csv failed");
			}

			auto record = new Exchange();
			Strcpy(record->ExchangeID, csv_record.GetFieldAsString("ExchangeID"));
			Strcpy(record->ExchangeName, csv_record.GetFieldAsString("ExchangeName"));
			mdb->t_Exchange->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadProductTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		sprintf(fullPath, "%s/t_Product.csv", dir);
		fstream file(fullPath, fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CSVRecord csv_record;
		if (!csv_record.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_Product.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csv_record.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_Product.csv failed");
			}

			auto record = new Product();
			Strcpy(record->ExchangeID, csv_record.GetFieldAsString("ExchangeID"));
			Strcpy(record->ProductID, csv_record.GetFieldAsString("ProductID"));
			Strcpy(record->ProductName, csv_record.GetFieldAsString("ProductName"));
			record->ProductClass = (ProductClassType)csv_record.GetFieldAsInt("ProductClass");
			record->VolumeMultiple = csv_record.GetFieldAsInt("VolumeMultiple");
			record->PriceTick = csv_record.GetFieldAsDouble("PriceTick");
			record->MaxMarketOrderVolume = csv_record.GetFieldAsInt64("MaxMarketOrderVolume");
			record->MinMarketOrderVolume = csv_record.GetFieldAsInt64("MinMarketOrderVolume");
			record->MaxLimitOrderVolume = csv_record.GetFieldAsInt64("MaxLimitOrderVolume");
			record->MinLimitOrderVolume = csv_record.GetFieldAsInt64("MinLimitOrderVolume");
			Strcpy(record->SessionName, csv_record.GetFieldAsString("SessionName"));
			mdb->t_Product->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadHotInstrumentTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		sprintf(fullPath, "%s/t_HotInstrument.csv", dir);
		fstream file(fullPath, fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CSVRecord csv_record;
		if (!csv_record.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_HotInstrument.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csv_record.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_HotInstrument.csv failed");
			}

			auto record = new HotInstrument();
			Strcpy(record->TradingDay, csv_record.GetFieldAsString("TradingDay"));
			Strcpy(record->ExchangeID, csv_record.GetFieldAsString("ExchangeID"));
			Strcpy(record->ProductID, csv_record.GetFieldAsString("ProductID"));
			Strcpy(record->InstrumentID, csv_record.GetFieldAsString("InstrumentID"));
			record->ProductClass = (ProductClassType)csv_record.GetFieldAsInt("ProductClass");
			record->Volume = csv_record.GetFieldAsInt64("Volume");
			record->MaxVolume = csv_record.GetFieldAsInt64("MaxVolume");
			record->Turnover = csv_record.GetFieldAsDouble("Turnover");
			record->MaxTurnover = csv_record.GetFieldAsDouble("MaxTurnover");
			record->OpenInterest = csv_record.GetFieldAsDouble("OpenInterest");
			record->MaxOpenInterest = csv_record.GetFieldAsDouble("MaxOpenInterest");
			record->Rank = csv_record.GetFieldAsInt("Rank");
			mdb->t_HotInstrument->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadInstrumentTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		sprintf(fullPath, "%s/t_Instrument.csv", dir);
		fstream file(fullPath, fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CSVRecord csv_record;
		if (!csv_record.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_Instrument.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csv_record.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_Instrument.csv failed");
			}

			auto record = new Instrument();
			Strcpy(record->ExchangeID, csv_record.GetFieldAsString("ExchangeID"));
			Strcpy(record->InstrumentID, csv_record.GetFieldAsString("InstrumentID"));
			Strcpy(record->ExchangeInstID, csv_record.GetFieldAsString("ExchangeInstID"));
			Strcpy(record->InstrumentName, csv_record.GetFieldAsString("InstrumentName"));
			Strcpy(record->ProductID, csv_record.GetFieldAsString("ProductID"));
			record->ProductClass = (ProductClassType)csv_record.GetFieldAsInt("ProductClass");
			record->InstrumentClass = (InstrumentClassType)csv_record.GetFieldAsInt("InstrumentClass");
			record->Rank = csv_record.GetFieldAsInt("Rank");
			record->VolumeMultiple = csv_record.GetFieldAsInt("VolumeMultiple");
			record->PriceTick = csv_record.GetFieldAsDouble("PriceTick");
			record->MaxMarketOrderVolume = csv_record.GetFieldAsInt64("MaxMarketOrderVolume");
			record->MinMarketOrderVolume = csv_record.GetFieldAsInt64("MinMarketOrderVolume");
			record->MaxLimitOrderVolume = csv_record.GetFieldAsInt64("MaxLimitOrderVolume");
			record->MinLimitOrderVolume = csv_record.GetFieldAsInt64("MinLimitOrderVolume");
			Strcpy(record->SessionName, csv_record.GetFieldAsString("SessionName"));
			mdb->t_Instrument->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadAccountTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		sprintf(fullPath, "%s/t_Account.csv", dir);
		fstream file(fullPath, fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CSVRecord csv_record;
		if (!csv_record.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_Account.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csv_record.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_Account.csv failed");
			}

			auto record = new Account();
			Strcpy(record->AccountID, csv_record.GetFieldAsString("AccountID"));
			Strcpy(record->AccountName, csv_record.GetFieldAsString("AccountName"));
			record->AccountType = (AccountTypeType)csv_record.GetFieldAsInt("AccountType");
			record->AccountStatus = (AccountStatusType)csv_record.GetFieldAsInt("AccountStatus");
			Strcpy(record->Password, csv_record.GetFieldAsString("Password"));
			record->TradeGroupID = csv_record.GetFieldAsInt("TradeGroupID");
			record->RiskGroupID = csv_record.GetFieldAsInt("RiskGroupID");
			record->CommissionGroupID = csv_record.GetFieldAsInt("CommissionGroupID");
			mdb->t_Account->Insert(record);
		}
		file.close();
	}
}
