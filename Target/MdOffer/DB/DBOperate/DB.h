#pragma once
#include "MdbStructs.h"
#include <string>
#include <list>


class DB
{
public:
	virtual bool Connect() = 0;
	virtual void DisConnect() = 0;
	virtual void InitDB() = 0;
	virtual void CreateTables() = 0;
	virtual void DropTables() = 0;
	virtual void TruncateTables() = 0;
	virtual void TruncateSessionTables() = 0;
	
	virtual void CreateExchange() = 0;
	virtual void DropExchange() = 0;
	virtual void InsertExchange(mdb::Exchange* record) = 0;
	virtual void BatchInsertExchange(std::list<mdb::Exchange*>* records) = 0;
	virtual void DeleteExchange(mdb::Exchange* record) = 0;
	virtual void UpdateExchange(mdb::Exchange* record) = 0;
	virtual void SelectExchange(std::list<mdb::Exchange*>& records) = 0;
	virtual void TruncateExchange() = 0;

	virtual void CreateInstrument() = 0;
	virtual void DropInstrument() = 0;
	virtual void InsertInstrument(mdb::Instrument* record) = 0;
	virtual void BatchInsertInstrument(std::list<mdb::Instrument*>* records) = 0;
	virtual void DeleteInstrument(mdb::Instrument* record) = 0;
	virtual void UpdateInstrument(mdb::Instrument* record) = 0;
	virtual void SelectInstrument(std::list<mdb::Instrument*>& records) = 0;
	virtual void TruncateInstrument() = 0;

	virtual void CreateDepthMarketData() = 0;
	virtual void DropDepthMarketData() = 0;
	virtual void InsertDepthMarketData(mdb::DepthMarketData* record) = 0;
	virtual void BatchInsertDepthMarketData(std::list<mdb::DepthMarketData*>* records) = 0;
	virtual void DeleteDepthMarketData(mdb::DepthMarketData* record) = 0;
	virtual void UpdateDepthMarketData(mdb::DepthMarketData* record) = 0;
	virtual void SelectDepthMarketData(std::list<mdb::DepthMarketData*>& records) = 0;
	virtual void TruncateDepthMarketData() = 0;

	virtual void CreateBarMarketData() = 0;
	virtual void DropBarMarketData() = 0;
	virtual void InsertBarMarketData(mdb::BarMarketData* record) = 0;
	virtual void BatchInsertBarMarketData(std::list<mdb::BarMarketData*>* records) = 0;
	virtual void DeleteBarMarketData(mdb::BarMarketData* record) = 0;
	virtual void UpdateBarMarketData(mdb::BarMarketData* record) = 0;
	virtual void SelectBarMarketData(std::list<mdb::BarMarketData*>& records) = 0;
	virtual void TruncateBarMarketData() = 0;

	virtual void CreateMdSubscribe() = 0;
	virtual void DropMdSubscribe() = 0;
	virtual void InsertMdSubscribe(mdb::MdSubscribe* record) = 0;
	virtual void BatchInsertMdSubscribe(std::list<mdb::MdSubscribe*>* records) = 0;
	virtual void DeleteMdSubscribe(mdb::MdSubscribe* record) = 0;
	virtual void UpdateMdSubscribe(mdb::MdSubscribe* record) = 0;
	virtual void SelectMdSubscribe(std::list<mdb::MdSubscribe*>& records) = 0;
	virtual void TruncateMdSubscribe() = 0;

	virtual void CreateMdUser() = 0;
	virtual void DropMdUser() = 0;
	virtual void InsertMdUser(mdb::MdUser* record) = 0;
	virtual void BatchInsertMdUser(std::list<mdb::MdUser*>* records) = 0;
	virtual void DeleteMdUser(mdb::MdUser* record) = 0;
	virtual void UpdateMdUser(mdb::MdUser* record) = 0;
	virtual void SelectMdUser(std::list<mdb::MdUser*>& records) = 0;
	virtual void TruncateMdUser() = 0;

	virtual void CreateMdUserLoginSession() = 0;
	virtual void DropMdUserLoginSession() = 0;
	virtual void InsertMdUserLoginSession(mdb::MdUserLoginSession* record) = 0;
	virtual void BatchInsertMdUserLoginSession(std::list<mdb::MdUserLoginSession*>* records) = 0;
	virtual void DeleteMdUserLoginSession(mdb::MdUserLoginSession* record) = 0;
	virtual void DeleteMdUserLoginSessionByMdUserIDIndex(mdb::MdUserLoginSession* record) = 0;
	virtual void UpdateMdUserLoginSession(mdb::MdUserLoginSession* record) = 0;
	virtual void SelectMdUserLoginSession(std::list<mdb::MdUserLoginSession*>& records) = 0;
	virtual void TruncateMdUserLoginSession() = 0;

};
