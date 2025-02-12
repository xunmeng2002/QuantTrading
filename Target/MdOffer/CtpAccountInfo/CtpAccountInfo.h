#pragma once
#include "ThostFtdcUserApiStruct.h"
#include <set>
#include <map>
#include <string>

struct CtpAccountInfo
{
	TThostFtdcBrokerIDType	BrokerID;
	TThostFtdcUserIDType	UserID;
	TThostFtdcPasswordType	Password;
	TThostFtdcProductInfoType	UserProductInfo;
	TThostFtdcAuthCodeType	AuthCode;
	TThostFtdcAppIDType	AppID;
	std::set<std::string> TraderFrontAddrs;
	std::set<std::string> MdFrontAddrs;
};

void PrintCtpAccountInfo(CtpAccountInfo* ctpAccountInfo);
void ReadCtpAccountInfo(std::map<std::string, CtpAccountInfo*>& ctpAccountInfos);


