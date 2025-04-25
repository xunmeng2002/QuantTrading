#include "Environment.h"
#include "json/json.h"
#include <fstream>
#include <iostream>
#include <exception>

using namespace std;

void PrintEnvironment(Environment* environment)
{
	printf("Environment: Name:%s\n", environment->Name);
	for (auto frontInfo : environment->Fronts)
	{
		printf("\tTradeFront:%s, MdFront:%s\n", frontInfo->TradeFront, frontInfo->MdFront);
	}
	for (auto account : environment->Accounts)
	{
		printf("\tBrokerID:%s,  InvestorID:%s, Password:%s, Phone:%s, UserProductInfo:%s, AuthCode:%s,  AppID:%s\n",
			account->BrokerID, account->InvestorID, account->Password, account->Phone, account->UserProductInfo, account->AuthCode, account->AppID);
	}
}
void ReadEnvironment(const char* environmentFile, std::map<std::string, Environment*>& environments)
{
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value root;

	ifstream in_file(environmentFile, ios::binary);
	if (!reader.parse(in_file, root))
	{
		std::cout << "Parse Config Failed." << std::endl;
		std::string s;
		in_file >> s;
		std::cout << s << std::endl;
		throw std::exception("Parse Config Failed.");
	}
	else
	{
		std::cout << "Parse Config Success." << std::endl;
	}
	in_file.close();

	for (auto i = 0u; i < root.size(); i++)
	{
		Environment* environment = new Environment();
		strcpy(environment->Name, root[i]["Name"].asString().c_str());
		auto& frontsValue = root[i]["Fronts"];
		for (auto i = 0u; i < frontsValue.size(); i++)
		{
			FrontInfo* frontInfo = new FrontInfo();
			strcpy(frontInfo->TradeFront, frontsValue[i]["Tradefront"].asString().c_str());
			strcpy(frontInfo->MdFront, frontsValue[i]["MdFront"].asString().c_str());
			environment->Fronts.push_back(frontInfo);
		}
		auto& accountsValue = root[i]["Accounts"];
		for (auto i = 0u; i < accountsValue.size(); i++)
		{
			AccountInfo* accountInfo = new AccountInfo();
			strcpy(accountInfo->BrokerID, accountsValue[i]["BrokerID"].asString().c_str());
			strcpy(accountInfo->InvestorID, accountsValue[i]["InvestorID"].asString().c_str());
			strcpy(accountInfo->Password, accountsValue[i]["Password"].asString().c_str());
			strcpy(accountInfo->Phone, accountsValue[i]["Phone"].asString().c_str());
			strcpy(accountInfo->UserProductInfo, accountsValue[i]["UserProductInfo"].asString().c_str());
			strcpy(accountInfo->AuthCode, accountsValue[i]["AuthCode"].asString().c_str());
			strcpy(accountInfo->AppID, accountsValue[i]["AppID"].asString().c_str());
			environment->Accounts.push_back(accountInfo);
		}
		environments.insert(make_pair(environment->Name, environment));
	}
	for (auto& it : environments)
	{
		PrintEnvironment(it.second);
	}
}
