#pragma once
#include <Spark/Types.h>
#include <map>
#include <vector>
#include <string>

namespace QuantTrading
{
    struct FrontInfo
    {
        IpAddressType	TradeFront;
        IpAddressType	MdFront;
    };
    struct AccountInfo
    {
        BrokerIdType	BrokerId;
        UserIdType		InvestorId;
        PasswordType	Password;
        PhoneNumberType	Phone;
        ProductInfoType	UserProductInfo;
        AuthCodeType	AuthCode;
        AppIdType		AppId;
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

