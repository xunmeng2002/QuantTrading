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

		LoadDepthMarketDataTable(mdb, dir);
		LoadBarMarketDataTable(mdb, dir);
		LoadMdSubscribeTable(mdb, dir);
		LoadMdUserTable(mdb, dir);
		LoadMdUserLoginSessionTable(mdb, dir);
	}

	void InitMdbFromCsv::LoadDepthMarketDataTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		sprintf(fullPath, "%s/t_DepthMarketData.csv", dir);
		fstream file(fullPath, fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CSVRecord csv_record;
		if (!csv_record.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_DepthMarketData.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csv_record.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_DepthMarketData.csv failed");
			}

			auto record = new DepthMarketData();
			Strcpy(record->TradingDay, csv_record.GetFieldAsString("TradingDay"));
			Strcpy(record->ExchangeID, csv_record.GetFieldAsString("ExchangeID"));
			Strcpy(record->InstrumentID, csv_record.GetFieldAsString("InstrumentID"));
			record->UpdateTs = csv_record.GetFieldAsInt64("UpdateTs");
			record->LastPrice = csv_record.GetFieldAsDouble("LastPrice");
			record->PreSettlementPrice = csv_record.GetFieldAsDouble("PreSettlementPrice");
			record->PreClosePrice = csv_record.GetFieldAsDouble("PreClosePrice");
			record->PreOpenInterest = csv_record.GetFieldAsDouble("PreOpenInterest");
			record->OpenPrice = csv_record.GetFieldAsDouble("OpenPrice");
			record->HighestPrice = csv_record.GetFieldAsDouble("HighestPrice");
			record->LowestPrice = csv_record.GetFieldAsDouble("LowestPrice");
			record->ClosePrice = csv_record.GetFieldAsDouble("ClosePrice");
			record->CurrVolume = csv_record.GetFieldAsInt64("CurrVolume");
			record->Volume = csv_record.GetFieldAsInt64("Volume");
			record->CurrTurnover = csv_record.GetFieldAsDouble("CurrTurnover");
			record->Turnover = csv_record.GetFieldAsDouble("Turnover");
			record->OpenInterest = csv_record.GetFieldAsDouble("OpenInterest");
			record->SettlementPrice = csv_record.GetFieldAsDouble("SettlementPrice");
			record->UpperLimitPrice = csv_record.GetFieldAsDouble("UpperLimitPrice");
			record->LowerLimitPrice = csv_record.GetFieldAsDouble("LowerLimitPrice");
			record->AveragePrice = csv_record.GetFieldAsDouble("AveragePrice");
			record->AskPrice1 = csv_record.GetFieldAsDouble("AskPrice1");
			record->AskPrice2 = csv_record.GetFieldAsDouble("AskPrice2");
			record->AskPrice3 = csv_record.GetFieldAsDouble("AskPrice3");
			record->AskPrice4 = csv_record.GetFieldAsDouble("AskPrice4");
			record->AskPrice5 = csv_record.GetFieldAsDouble("AskPrice5");
			record->AskPrice6 = csv_record.GetFieldAsDouble("AskPrice6");
			record->AskPrice7 = csv_record.GetFieldAsDouble("AskPrice7");
			record->AskPrice8 = csv_record.GetFieldAsDouble("AskPrice8");
			record->AskPrice9 = csv_record.GetFieldAsDouble("AskPrice9");
			record->AskPrice10 = csv_record.GetFieldAsDouble("AskPrice10");
			record->AskVolume1 = csv_record.GetFieldAsInt64("AskVolume1");
			record->AskVolume2 = csv_record.GetFieldAsInt64("AskVolume2");
			record->AskVolume3 = csv_record.GetFieldAsInt64("AskVolume3");
			record->AskVolume4 = csv_record.GetFieldAsInt64("AskVolume4");
			record->AskVolume5 = csv_record.GetFieldAsInt64("AskVolume5");
			record->AskVolume6 = csv_record.GetFieldAsInt64("AskVolume6");
			record->AskVolume7 = csv_record.GetFieldAsInt64("AskVolume7");
			record->AskVolume8 = csv_record.GetFieldAsInt64("AskVolume8");
			record->AskVolume9 = csv_record.GetFieldAsInt64("AskVolume9");
			record->AskVolume10 = csv_record.GetFieldAsInt64("AskVolume10");
			record->BidPrice1 = csv_record.GetFieldAsDouble("BidPrice1");
			record->BidPrice2 = csv_record.GetFieldAsDouble("BidPrice2");
			record->BidPrice3 = csv_record.GetFieldAsDouble("BidPrice3");
			record->BidPrice4 = csv_record.GetFieldAsDouble("BidPrice4");
			record->BidPrice5 = csv_record.GetFieldAsDouble("BidPrice5");
			record->BidPrice6 = csv_record.GetFieldAsDouble("BidPrice6");
			record->BidPrice7 = csv_record.GetFieldAsDouble("BidPrice7");
			record->BidPrice8 = csv_record.GetFieldAsDouble("BidPrice8");
			record->BidPrice9 = csv_record.GetFieldAsDouble("BidPrice9");
			record->BidPrice10 = csv_record.GetFieldAsDouble("BidPrice10");
			record->BidVolume1 = csv_record.GetFieldAsInt64("BidVolume1");
			record->BidVolume2 = csv_record.GetFieldAsInt64("BidVolume2");
			record->BidVolume3 = csv_record.GetFieldAsInt64("BidVolume3");
			record->BidVolume4 = csv_record.GetFieldAsInt64("BidVolume4");
			record->BidVolume5 = csv_record.GetFieldAsInt64("BidVolume5");
			record->BidVolume6 = csv_record.GetFieldAsInt64("BidVolume6");
			record->BidVolume7 = csv_record.GetFieldAsInt64("BidVolume7");
			record->BidVolume8 = csv_record.GetFieldAsInt64("BidVolume8");
			record->BidVolume9 = csv_record.GetFieldAsInt64("BidVolume9");
			record->BidVolume10 = csv_record.GetFieldAsInt64("BidVolume10");
			mdb->t_DepthMarketData->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadBarMarketDataTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		sprintf(fullPath, "%s/t_BarMarketData.csv", dir);
		fstream file(fullPath, fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CSVRecord csv_record;
		if (!csv_record.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_BarMarketData.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csv_record.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_BarMarketData.csv failed");
			}

			auto record = new BarMarketData();
			Strcpy(record->TradingDay, csv_record.GetFieldAsString("TradingDay"));
			Strcpy(record->ExchangeID, csv_record.GetFieldAsString("ExchangeID"));
			Strcpy(record->InstrumentID, csv_record.GetFieldAsString("InstrumentID"));
			record->BarPreces = (BarPrecesType)csv_record.GetFieldAsInt("BarPreces");
			record->BarPeriod = csv_record.GetFieldAsInt("BarPeriod");
			record->BarTime = csv_record.GetFieldAsInt64("BarTime");
			record->UpdateTs = csv_record.GetFieldAsInt64("UpdateTs");
			record->PreSettlementPrice = csv_record.GetFieldAsDouble("PreSettlementPrice");
			record->PreClosePrice = csv_record.GetFieldAsDouble("PreClosePrice");
			record->Open = csv_record.GetFieldAsDouble("Open");
			record->High = csv_record.GetFieldAsDouble("High");
			record->Low = csv_record.GetFieldAsDouble("Low");
			record->Close = csv_record.GetFieldAsDouble("Close");
			record->CurrVolume = csv_record.GetFieldAsInt64("CurrVolume");
			record->Volume = csv_record.GetFieldAsInt64("Volume");
			record->CurrTurnover = csv_record.GetFieldAsDouble("CurrTurnover");
			record->Turnover = csv_record.GetFieldAsDouble("Turnover");
			record->OpenInterest = csv_record.GetFieldAsDouble("OpenInterest");
			mdb->t_BarMarketData->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadMdSubscribeTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		sprintf(fullPath, "%s/t_MdSubscribe.csv", dir);
		fstream file(fullPath, fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CSVRecord csv_record;
		if (!csv_record.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_MdSubscribe.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csv_record.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_MdSubscribe.csv failed");
			}

			auto record = new MdSubscribe();
			Strcpy(record->ExchangeID, csv_record.GetFieldAsString("ExchangeID"));
			Strcpy(record->InstrumentID, csv_record.GetFieldAsString("InstrumentID"));
			Strcpy(record->RealInstrumentID, csv_record.GetFieldAsString("RealInstrumentID"));
			Strcpy(record->ProductID, csv_record.GetFieldAsString("ProductID"));
			record->ProductClass = (ProductClassType)csv_record.GetFieldAsInt("ProductClass");
			Strcpy(record->StartTradingDay, csv_record.GetFieldAsString("StartTradingDay"));
			Strcpy(record->EndTradingDay, csv_record.GetFieldAsString("EndTradingDay"));
			mdb->t_MdSubscribe->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadMdUserTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		sprintf(fullPath, "%s/t_MdUser.csv", dir);
		fstream file(fullPath, fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CSVRecord csv_record;
		if (!csv_record.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_MdUser.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csv_record.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_MdUser.csv failed");
			}

			auto record = new MdUser();
			Strcpy(record->MdUserID, csv_record.GetFieldAsString("MdUserID"));
			Strcpy(record->MdUserName, csv_record.GetFieldAsString("MdUserName"));
			Strcpy(record->Password, csv_record.GetFieldAsString("Password"));
			mdb->t_MdUser->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadMdUserLoginSessionTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		sprintf(fullPath, "%s/t_MdUserLoginSession.csv", dir);
		fstream file(fullPath, fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CSVRecord csv_record;
		if (!csv_record.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_MdUserLoginSession.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csv_record.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_MdUserLoginSession.csv failed");
			}

			auto record = new MdUserLoginSession();
			Strcpy(record->MdUserID, csv_record.GetFieldAsString("MdUserID"));
			record->SessionID = csv_record.GetFieldAsInt64("SessionID");
			Strcpy(record->IPAddress, csv_record.GetFieldAsString("IPAddress"));
			mdb->t_MdUserLoginSession->Insert(record);
		}
		file.close();
	}
}
