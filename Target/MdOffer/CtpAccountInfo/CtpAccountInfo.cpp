#include "CtpAccountInfo.h"
#include "json/json.h"
#include <fstream>
#include <iostream>

using namespace std;


void PrintCtpAccountInfo(CtpAccountInfo* ctpAccountInfo)
{
	printf("CtpAccountInfo: BrokerID[%s],  UserID[%s], Password[%s],  UserProductInfo[%s], AuthCode[%s],  AppID[%s]\n",
		ctpAccountInfo->BrokerID, ctpAccountInfo->UserID, ctpAccountInfo->Password, ctpAccountInfo->UserProductInfo, ctpAccountInfo->AuthCode, ctpAccountInfo->AppID);
	for (auto& traderFrontAddr : ctpAccountInfo->TraderFrontAddrs)
	{
		printf("TraderFrontAddrs:[%s]\t", traderFrontAddr.c_str());
	}
	printf("\n");
	for (auto& mdFrontAddr : ctpAccountInfo->MdFrontAddrs)
	{
		printf("MdFrontAddr:[%s]\t", mdFrontAddr.c_str());
	}
	printf("\n");
}
void ReadCtpAccountInfo(std::map<std::string, CtpAccountInfo*>& ctpAccountInfos)
{
	Json::Reader reader;
	Json::FastWriter writer;
	Json::Value root;

	ifstream in_file("CtpAccountInfo.json", ios::binary);
	cout << "parse: " << reader.parse(in_file, root) << endl;
	in_file.close();

	for (auto i = 0u; i < root.size(); i++)
	{
		CtpAccountInfo* ctpAccountInfo = new CtpAccountInfo();
		strcpy(ctpAccountInfo->BrokerID, root[i]["BrokerID"].asString().c_str());
		strcpy(ctpAccountInfo->UserID, root[i]["UserID"].asString().c_str());
		strcpy(ctpAccountInfo->Password, root[i]["Password"].asString().c_str());
		strcpy(ctpAccountInfo->UserProductInfo, root[i]["UserProductInfo"].asString().c_str());
		strcpy(ctpAccountInfo->AuthCode, root[i]["AuthCode"].asString().c_str());
		strcpy(ctpAccountInfo->AppID, root[i]["AppID"].asString().c_str());
		for (auto j = 0u; j < root[i]["TraderFrontAddrs"].size(); j++)
		{
			ctpAccountInfo->TraderFrontAddrs.insert(root[i]["TraderFrontAddrs"][j].asString());
		}
		for (auto j = 0u; j < root[i]["MdFrontAddrs"].size(); j++)
		{
			ctpAccountInfo->MdFrontAddrs.insert(root[i]["MdFrontAddrs"][j].asString());
		}
		ctpAccountInfos.insert(make_pair(ctpAccountInfo->UserID, ctpAccountInfo));
	}
	for (auto& it : ctpAccountInfos)
	{
		PrintCtpAccountInfo(it.second);
	}
}
