#include "SimExchange.h"
#include "InitMdbFromCsv.h"

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
void SimExchange::Run()
{

}

