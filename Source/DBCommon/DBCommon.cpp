#include "DBCommon.h"
#include "Types.h"
#include "Logger.h"
#include "DuckDB.h"
#include "SqliteDB.h"
#include "MysqlDB.h"

DB* CreateDB(const std::string& dbType, const std::string& dbHost, const std::string& dbUser, const std::string& dbPassword)
{
	switch (DBTypeType(dbType[0]))
	{
	case DBTypeType::DuckDB:
		return new DuckDB(dbHost);
	case DBTypeType::SqliteDB:
		return new SqliteDB(dbHost);
	case DBTypeType::MysqlDB:
		return new MysqlDB(dbHost, dbUser, dbPassword);
	case DBTypeType::MariaDB:
	default:
		WriteLog(LogLevel::Error, "Unsupported DBType:%s", dbType);
		break;
	}
	return nullptr;
}