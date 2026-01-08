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
		LoadDepthMarketDataTable(mdb, dir);
		LoadSEBrokerTable(mdb, dir);
		LoadSEInstrumentTable(mdb, dir);
		LoadSEOrderTable(mdb, dir);
		LoadSETradeTable(mdb, dir);
		LoadSEBrokerLoginSessionTable(mdb, dir);
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
	void InitMdbFromCsv::LoadSEBrokerTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		sprintf(fullPath, "%s/t_SEBroker.csv", dir);
		fstream file(fullPath, fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CSVRecord csv_record;
		if (!csv_record.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_SEBroker.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csv_record.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_SEBroker.csv failed");
			}

			auto record = new SEBroker();
			record->BrokerID = csv_record.GetFieldAsInt("BrokerID");
			Strcpy(record->BrokerName, csv_record.GetFieldAsString("BrokerName"));
			Strcpy(record->Password, csv_record.GetFieldAsString("Password"));
			mdb->t_SEBroker->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadSEInstrumentTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		sprintf(fullPath, "%s/t_SEInstrument.csv", dir);
		fstream file(fullPath, fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CSVRecord csv_record;
		if (!csv_record.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_SEInstrument.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csv_record.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_SEInstrument.csv failed");
			}

			auto record = new SEInstrument();
			Strcpy(record->ExchangeID, csv_record.GetFieldAsString("ExchangeID"));
			Strcpy(record->InstrumentID, csv_record.GetFieldAsString("InstrumentID"));
			Strcpy(record->ExchangeInstID, csv_record.GetFieldAsString("ExchangeInstID"));
			Strcpy(record->InstrumentName, csv_record.GetFieldAsString("InstrumentName"));
			Strcpy(record->ProductID, csv_record.GetFieldAsString("ProductID"));
			record->ProductClass = (ProductClassType)csv_record.GetFieldAsInt("ProductClass");
			record->MaxMarketOrderVolume = csv_record.GetFieldAsInt64("MaxMarketOrderVolume");
			record->MinMarketOrderVolume = csv_record.GetFieldAsInt64("MinMarketOrderVolume");
			record->MaxLimitOrderVolume = csv_record.GetFieldAsInt64("MaxLimitOrderVolume");
			record->MinLimitOrderVolume = csv_record.GetFieldAsInt64("MinLimitOrderVolume");
			record->VolumeMultiple = csv_record.GetFieldAsInt("VolumeMultiple");
			record->PriceTick = csv_record.GetFieldAsDouble("PriceTick");
			record->UpperLimitPrice = csv_record.GetFieldAsDouble("UpperLimitPrice");
			record->LowerLimitPrice = csv_record.GetFieldAsDouble("LowerLimitPrice");
			Strcpy(record->SessionName, csv_record.GetFieldAsString("SessionName"));
			mdb->t_SEInstrument->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadSEOrderTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		sprintf(fullPath, "%s/t_SEOrder.csv", dir);
		fstream file(fullPath, fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CSVRecord csv_record;
		if (!csv_record.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_SEOrder.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csv_record.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_SEOrder.csv failed");
			}

			auto record = new SEOrder();
			Strcpy(record->TradingDay, csv_record.GetFieldAsString("TradingDay"));
			record->BrokerID = csv_record.GetFieldAsInt("BrokerID");
			Strcpy(record->AccountID, csv_record.GetFieldAsString("AccountID"));
			Strcpy(record->ExchangeID, csv_record.GetFieldAsString("ExchangeID"));
			Strcpy(record->InstrumentID, csv_record.GetFieldAsString("InstrumentID"));
			record->ProductClass = (ProductClassType)csv_record.GetFieldAsInt("ProductClass");
			record->OrderID = csv_record.GetFieldAsInt("OrderID");
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
			mdb->t_SEOrder->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadSETradeTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		sprintf(fullPath, "%s/t_SETrade.csv", dir);
		fstream file(fullPath, fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CSVRecord csv_record;
		if (!csv_record.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_SETrade.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csv_record.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_SETrade.csv failed");
			}

			auto record = new SETrade();
			Strcpy(record->TradingDay, csv_record.GetFieldAsString("TradingDay"));
			record->BrokerID = csv_record.GetFieldAsInt("BrokerID");
			Strcpy(record->AccountID, csv_record.GetFieldAsString("AccountID"));
			Strcpy(record->ExchangeID, csv_record.GetFieldAsString("ExchangeID"));
			Strcpy(record->InstrumentID, csv_record.GetFieldAsString("InstrumentID"));
			record->ProductClass = (ProductClassType)csv_record.GetFieldAsInt("ProductClass");
			record->OrderID = csv_record.GetFieldAsInt("OrderID");
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
			mdb->t_SETrade->Insert(record);
		}
		file.close();
	}
	void InitMdbFromCsv::LoadSEBrokerLoginSessionTable(Mdb* mdb, const char* dir)
	{
		char fullPath[260];
		sprintf(fullPath, "%s/t_SEBrokerLoginSession.csv", dir);
		fstream file(fullPath, fstream::in);
		if (!file)
		{
			throw std::string(fullPath) + " Open Failed.";
		}

		file.getline(HeaderBuffer, sizeof(HeaderBuffer), '\n');
		CSVRecord csv_record;
		if (!csv_record.AnalysisFieldName(HeaderBuffer))
		{
			throw std::string("AnalysisFieldName t_SEBrokerLoginSession.csv failed");
		}
		while (!file.eof())
		{
			::memset(ContentBuffer, 0, sizeof(ContentBuffer));
			file.getline(ContentBuffer, sizeof(ContentBuffer), '\n');
			if (ContentBuffer[0] == '\0')
				break;
			if (!csv_record.AnalysisFieldContent(ContentBuffer))
			{
				throw std::string("AnalysisFieldContent t_SEBrokerLoginSession.csv failed");
			}

			auto record = new SEBrokerLoginSession();
			record->BrokerID = csv_record.GetFieldAsInt("BrokerID");
			record->SessionID = csv_record.GetFieldAsInt64("SessionID");
			Strcpy(record->IPAddress, csv_record.GetFieldAsString("IPAddress"));
			mdb->t_SEBrokerLoginSession->Insert(record);
		}
		file.close();
	}
}
