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
		LoadDepthMarketDataTable(mdb, dir);
		LoadBarMarketDataTable(mdb, dir);
		LoadMdUserTable(mdb, dir);
		LoadPrimaryAccountTable(mdb, dir);
		LoadAccountTable(mdb, dir);
		LoadCapitalTable(mdb, dir);
		LoadPositionTable(mdb, dir);
		LoadPositionDetailTable(mdb, dir);
		LoadOrderTable(mdb, dir);
		LoadTradeTable(mdb, dir);
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
	void InitMdbFromCsv::LoadPrimaryAccountTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		sprintf(fullPath, "%s/t_PrimaryAccount.csv", dir);
		fstream file(fullPath, fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CSVRecord csv_record;
		if (!csv_record.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_PrimaryAccount.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csv_record.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_PrimaryAccount.csv failed");
			}

			auto record = new PrimaryAccount();
			Strcpy(record->PrimaryAccountID, csv_record.GetFieldAsString("PrimaryAccountID"));
			Strcpy(record->PrimaryAccountName, csv_record.GetFieldAsString("PrimaryAccountName"));
			record->AccountClass = (AccountClassType)csv_record.GetFieldAsInt("AccountClass");
			Strcpy(record->Password, csv_record.GetFieldAsString("Password"));
			record->OfferID = csv_record.GetFieldAsInt("OfferID");
			record->IsAllowLogin = (bool)csv_record.GetFieldAsInt("IsAllowLogin");
			record->IsSimulateAccount = (bool)csv_record.GetFieldAsInt("IsSimulateAccount");
			record->LoginStatus = (LoginStatusType)csv_record.GetFieldAsInt("LoginStatus");
			record->InitStatus = (InitStatusType)csv_record.GetFieldAsInt("InitStatus");
			mdb->t_PrimaryAccount->Insert(record);
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
	void InitMdbFromCsv::LoadCapitalTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		sprintf(fullPath, "%s/t_Capital.csv", dir);
		fstream file(fullPath, fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CSVRecord csv_record;
		if (!csv_record.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_Capital.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csv_record.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_Capital.csv failed");
			}

			auto record = new Capital();
			Strcpy(record->TradingDay, csv_record.GetFieldAsString("TradingDay"));
			Strcpy(record->AccountID, csv_record.GetFieldAsString("AccountID"));
			record->AccountType = (AccountTypeType)csv_record.GetFieldAsInt("AccountType");
			record->Balance = csv_record.GetFieldAsDouble("Balance");
			record->PreBalance = csv_record.GetFieldAsDouble("PreBalance");
			record->Available = csv_record.GetFieldAsDouble("Available");
			record->MarketValue = csv_record.GetFieldAsDouble("MarketValue");
			record->CashIn = csv_record.GetFieldAsDouble("CashIn");
			record->CashOut = csv_record.GetFieldAsDouble("CashOut");
			record->Margin = csv_record.GetFieldAsDouble("Margin");
			record->Commission = csv_record.GetFieldAsDouble("Commission");
			record->FrozenCash = csv_record.GetFieldAsDouble("FrozenCash");
			record->FrozenMargin = csv_record.GetFieldAsDouble("FrozenMargin");
			record->FrozenCommission = csv_record.GetFieldAsDouble("FrozenCommission");
			record->CloseProfitByDate = csv_record.GetFieldAsDouble("CloseProfitByDate");
			record->CloseProfitByTrade = csv_record.GetFieldAsDouble("CloseProfitByTrade");
			record->PositionProfitByDate = csv_record.GetFieldAsDouble("PositionProfitByDate");
			record->PositionProfitByTrade = csv_record.GetFieldAsDouble("PositionProfitByTrade");
			record->Deposit = csv_record.GetFieldAsDouble("Deposit");
			record->Withdraw = csv_record.GetFieldAsDouble("Withdraw");
			mdb->t_Capital->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadPositionTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		sprintf(fullPath, "%s/t_Position.csv", dir);
		fstream file(fullPath, fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CSVRecord csv_record;
		if (!csv_record.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_Position.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csv_record.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_Position.csv failed");
			}

			auto record = new Position();
			Strcpy(record->TradingDay, csv_record.GetFieldAsString("TradingDay"));
			Strcpy(record->AccountID, csv_record.GetFieldAsString("AccountID"));
			record->AccountType = (AccountTypeType)csv_record.GetFieldAsInt("AccountType");
			Strcpy(record->ExchangeID, csv_record.GetFieldAsString("ExchangeID"));
			Strcpy(record->InstrumentID, csv_record.GetFieldAsString("InstrumentID"));
			record->ProductClass = (ProductClassType)csv_record.GetFieldAsInt("ProductClass");
			record->PosiDirection = (PosiDirectionType)csv_record.GetFieldAsInt("PosiDirection");
			record->TotalPosition = csv_record.GetFieldAsInt64("TotalPosition");
			record->PositionFrozen = csv_record.GetFieldAsInt64("PositionFrozen");
			record->TodayPosition = csv_record.GetFieldAsInt64("TodayPosition");
			record->MarketValue = csv_record.GetFieldAsDouble("MarketValue");
			record->CashIn = csv_record.GetFieldAsDouble("CashIn");
			record->CashOut = csv_record.GetFieldAsDouble("CashOut");
			record->Margin = csv_record.GetFieldAsDouble("Margin");
			record->Commission = csv_record.GetFieldAsDouble("Commission");
			record->FrozenCash = csv_record.GetFieldAsDouble("FrozenCash");
			record->FrozenMargin = csv_record.GetFieldAsDouble("FrozenMargin");
			record->FrozenCommission = csv_record.GetFieldAsDouble("FrozenCommission");
			record->VolumeMultiple = csv_record.GetFieldAsInt("VolumeMultiple");
			record->CloseProfitByDate = csv_record.GetFieldAsDouble("CloseProfitByDate");
			record->CloseProfitByTrade = csv_record.GetFieldAsDouble("CloseProfitByTrade");
			record->PositionProfitByDate = csv_record.GetFieldAsDouble("PositionProfitByDate");
			record->PositionProfitByTrade = csv_record.GetFieldAsDouble("PositionProfitByTrade");
			record->SettlementPrice = csv_record.GetFieldAsDouble("SettlementPrice");
			record->PreSettlementPrice = csv_record.GetFieldAsDouble("PreSettlementPrice");
			mdb->t_Position->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadPositionDetailTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		sprintf(fullPath, "%s/t_PositionDetail.csv", dir);
		fstream file(fullPath, fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CSVRecord csv_record;
		if (!csv_record.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_PositionDetail.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csv_record.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_PositionDetail.csv failed");
			}

			auto record = new PositionDetail();
			Strcpy(record->TradingDay, csv_record.GetFieldAsString("TradingDay"));
			Strcpy(record->AccountID, csv_record.GetFieldAsString("AccountID"));
			record->AccountType = (AccountTypeType)csv_record.GetFieldAsInt("AccountType");
			Strcpy(record->ExchangeID, csv_record.GetFieldAsString("ExchangeID"));
			Strcpy(record->InstrumentID, csv_record.GetFieldAsString("InstrumentID"));
			record->ProductClass = (ProductClassType)csv_record.GetFieldAsInt("ProductClass");
			record->PosiDirection = (PosiDirectionType)csv_record.GetFieldAsInt("PosiDirection");
			Strcpy(record->OpenDate, csv_record.GetFieldAsString("OpenDate"));
			Strcpy(record->TradeID, csv_record.GetFieldAsString("TradeID"));
			record->Volume = csv_record.GetFieldAsInt64("Volume");
			record->OpenPrice = csv_record.GetFieldAsDouble("OpenPrice");
			record->MarketValue = csv_record.GetFieldAsDouble("MarketValue");
			record->CashIn = csv_record.GetFieldAsDouble("CashIn");
			record->CashOut = csv_record.GetFieldAsDouble("CashOut");
			record->Margin = csv_record.GetFieldAsDouble("Margin");
			record->Commission = csv_record.GetFieldAsDouble("Commission");
			record->VolumeMultiple = csv_record.GetFieldAsInt("VolumeMultiple");
			record->CloseProfitByDate = csv_record.GetFieldAsDouble("CloseProfitByDate");
			record->CloseProfitByTrade = csv_record.GetFieldAsDouble("CloseProfitByTrade");
			record->PositionProfitByDate = csv_record.GetFieldAsDouble("PositionProfitByDate");
			record->PositionProfitByTrade = csv_record.GetFieldAsDouble("PositionProfitByTrade");
			record->SettlementPrice = csv_record.GetFieldAsDouble("SettlementPrice");
			record->PreSettlementPrice = csv_record.GetFieldAsDouble("PreSettlementPrice");
			record->CloseVolume = csv_record.GetFieldAsInt64("CloseVolume");
			record->CloseAmount = csv_record.GetFieldAsDouble("CloseAmount");
			mdb->t_PositionDetail->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadOrderTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		sprintf(fullPath, "%s/t_Order.csv", dir);
		fstream file(fullPath, fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CSVRecord csv_record;
		if (!csv_record.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_Order.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csv_record.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_Order.csv failed");
			}

			auto record = new Order();
			Strcpy(record->TradingDay, csv_record.GetFieldAsString("TradingDay"));
			Strcpy(record->AccountID, csv_record.GetFieldAsString("AccountID"));
			record->AccountType = (AccountTypeType)csv_record.GetFieldAsInt("AccountType");
			Strcpy(record->ExchangeID, csv_record.GetFieldAsString("ExchangeID"));
			Strcpy(record->InstrumentID, csv_record.GetFieldAsString("InstrumentID"));
			record->ProductClass = (ProductClassType)csv_record.GetFieldAsInt("ProductClass");
			record->OrderID = csv_record.GetFieldAsInt("OrderID");
			Strcpy(record->OrderSysID, csv_record.GetFieldAsString("OrderSysID"));
			record->Direction = (DirectionType)csv_record.GetFieldAsInt("Direction");
			record->OffsetFlag = (OffsetFlagType)csv_record.GetFieldAsInt("OffsetFlag");
			record->OrderPriceType = (OrderPriceTypeType)csv_record.GetFieldAsInt("OrderPriceType");
			record->Price = csv_record.GetFieldAsDouble("Price");
			record->Volume = csv_record.GetFieldAsInt64("Volume");
			record->VolumeTotal = csv_record.GetFieldAsInt64("VolumeTotal");
			record->VolumeTraded = csv_record.GetFieldAsInt64("VolumeTraded");
			record->VolumeMultiple = csv_record.GetFieldAsInt("VolumeMultiple");
			record->OrderStatus = (OrderStatusType)csv_record.GetFieldAsInt("OrderStatus");
			Strcpy(record->OrderDate, csv_record.GetFieldAsString("OrderDate"));
			Strcpy(record->OrderTime, csv_record.GetFieldAsString("OrderTime"));
			Strcpy(record->CancelDate, csv_record.GetFieldAsString("CancelDate"));
			Strcpy(record->CancelTime, csv_record.GetFieldAsString("CancelTime"));
			record->SessionID = csv_record.GetFieldAsInt64("SessionID");
			record->ClientOrderID = csv_record.GetFieldAsInt("ClientOrderID");
			record->RequestID = csv_record.GetFieldAsInt("RequestID");
			record->OfferID = csv_record.GetFieldAsInt("OfferID");
			record->TradeGroupID = csv_record.GetFieldAsInt("TradeGroupID");
			record->RiskGroupID = csv_record.GetFieldAsInt("RiskGroupID");
			record->CommissionGroupID = csv_record.GetFieldAsInt("CommissionGroupID");
			record->FrozenCash = csv_record.GetFieldAsDouble("FrozenCash");
			record->FrozenMargin = csv_record.GetFieldAsDouble("FrozenMargin");
			record->FrozenCommission = csv_record.GetFieldAsDouble("FrozenCommission");
			record->RebuildMark = (bool)csv_record.GetFieldAsInt("RebuildMark");
			record->IsForceClose = (bool)csv_record.GetFieldAsInt("IsForceClose");
			mdb->t_Order->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadTradeTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		sprintf(fullPath, "%s/t_Trade.csv", dir);
		fstream file(fullPath, fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CSVRecord csv_record;
		if (!csv_record.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_Trade.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csv_record.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_Trade.csv failed");
			}

			auto record = new Trade();
			Strcpy(record->TradingDay, csv_record.GetFieldAsString("TradingDay"));
			Strcpy(record->AccountID, csv_record.GetFieldAsString("AccountID"));
			record->AccountType = (AccountTypeType)csv_record.GetFieldAsInt("AccountType");
			Strcpy(record->ExchangeID, csv_record.GetFieldAsString("ExchangeID"));
			Strcpy(record->InstrumentID, csv_record.GetFieldAsString("InstrumentID"));
			record->ProductClass = (ProductClassType)csv_record.GetFieldAsInt("ProductClass");
			record->OrderID = csv_record.GetFieldAsInt("OrderID");
			Strcpy(record->OrderSysID, csv_record.GetFieldAsString("OrderSysID"));
			Strcpy(record->TradeID, csv_record.GetFieldAsString("TradeID"));
			record->Direction = (DirectionType)csv_record.GetFieldAsInt("Direction");
			record->OffsetFlag = (OffsetFlagType)csv_record.GetFieldAsInt("OffsetFlag");
			record->Price = csv_record.GetFieldAsDouble("Price");
			record->Volume = csv_record.GetFieldAsInt64("Volume");
			record->VolumeMultiple = csv_record.GetFieldAsInt("VolumeMultiple");
			record->TradeAmount = csv_record.GetFieldAsDouble("TradeAmount");
			record->Commission = csv_record.GetFieldAsDouble("Commission");
			Strcpy(record->TradeDate, csv_record.GetFieldAsString("TradeDate"));
			Strcpy(record->TradeTime, csv_record.GetFieldAsString("TradeTime"));
			mdb->t_Trade->Insert(record);
		}
		file.close();
	}
}
