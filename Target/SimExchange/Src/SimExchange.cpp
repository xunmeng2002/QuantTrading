#include "SimExchange.h"
#include "InitMdbFromCsv.h"
#include "Error.h"

using namespace std;
using namespace mdb;

SimExchange::SimExchange(const Config& config)
	:ThreadBase("SimExchange"), m_Mdb(nullptr)
{
	m_Mdb = new mdb::Mdb();
	InitMdbFromCsv::LoadTables(m_Mdb, config.CsvPath.c_str());
}
SimExchange::~SimExchange()
{

}
void SimExchange::Init()
{

}
int SimExchange::ReqInsertOrder(ReqInsertOrderField* reqInsertOrder, int requestID)
{
	return ErrorNone;
}
int SimExchange::ReqCancelOrder(ReqCancelOrderField* reqCancelOrder, int requestID)
{
	return ErrorNone;
}

void SimExchange::Run()
{

}

