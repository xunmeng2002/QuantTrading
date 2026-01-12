#pragma once
#include "ThostFtdcUserApiStruct.h"
#include <map>
#include <vector>
#include <string>

struct FrontInfo
{
	TThostFtdcIPAddressType	TradeFront;
	TThostFtdcIPAddressType	MdFront;
};
struct AccountInfo
{
	TThostFtdcBrokerIDType	BrokerID;
	TThostFtdcUserIDType	InvestorID;
	TThostFtdcPasswordType	Password;
	TThostFtdcMobilePhoneType	Phone;
	TThostFtdcProductInfoType	UserProductInfo;
	TThostFtdcAuthCodeType	AuthCode;
	TThostFtdcAppIDType	AppID;
};

struct Environment
{
	TThostFtdcServiceNameType Name;
	std::vector<FrontInfo*> Fronts;
	std::vector<AccountInfo*> Accounts;
};

void PrintEnvironment(Environment* environment);
void ReadEnvironment(const char* environmentFile, std::map<std::string, Environment*>& environments);
Environment* GetEnvironment(std::map<std::string, Environment*>& environments, const std::string& environmentName, const std::string& environmentName24);


