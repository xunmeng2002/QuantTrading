#pragma once
#include <string>

using std::string;

class ServerConfig
{
	ServerConfig();
public:
	static ServerConfig& GetInstance();
	void Load(const char* fileName = "../../ServerConfig.json");
	void Print();
	
public:
	string MdOfferAddress;
	string TradeFrontAddress;
	string RiskFrontAddress;
	string AdminFrontAddress;
	string OfferFrontAddress;
	string DBHostAdmin;
	string DBHostHistory;
	string DBHostInit;
	string DBHostSync;
	string DBUser;
	string DBPasswd;
	
private:
	static ServerConfig m_Instance;
};
