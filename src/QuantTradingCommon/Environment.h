#pragma once
#include <Spark/Types.h>
#include <map>
#include <vector>
#include <string>

namespace quanttrading::quanttradingcommon
{
    struct FrontInfo
    {
        IPAddressType	TradeFront;
        IPAddressType	MdFront;
    };
    struct AccountInfo
    {
        BrokerIDType	BrokerID;
        UserIDType		InvestorID;
        PasswordType	Password;
        PhoneNumberType	Phone;
        ProductInfoType	UserProductInfo;
        AuthCodeType	AuthCode;
        AppIDType		AppID;
    };

    struct Environment
    {
        NameType Name;
        std::vector<FrontInfo*> Fronts;
        std::vector<AccountInfo*> Accounts;
    };

    void PrintEnvironment(Environment* environment);
    void ReadEnvironment(std::map<std::string, Environment*>& environments, const char* environmentFile = "../../CtpAccountInfo.json");
    Environment* GetEnvironment(std::map<std::string, Environment*>& environments, const std::string& environmentName, const std::string& environmentName24);
}

