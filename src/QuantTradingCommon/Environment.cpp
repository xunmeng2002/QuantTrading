#include "Environment.h"
#include <Spark/Serialization/json/json.h>
#include <Spark/Core/Utility/TimeUtility.h>
#include <Spark/Core/Logger/Logger.h>
#include <fstream>
#include <stdexcept>

using namespace std;
using namespace spark::core;

namespace quanttrading
{

    void PrintEnvironment(Environment* environment)
    {
        WriteLog(LogLevel::Info, "Environment: Name:%s", environment->Name);
        for (auto frontInfo : environment->Fronts)
        {
            WriteLog(LogLevel::Info, "TradeFront:%s, MdFront:%s", frontInfo->TradeFront, frontInfo->MdFront);
        }
        for (auto account : environment->Accounts)
        {
            WriteLog(LogLevel::Info, "BrokerID:%s, InvestorID:%s, Phone:%s, UserProductInfo:%s, AppID:%s",
                account->BrokerID, account->InvestorID, account->Phone, account->UserProductInfo, account->AppID);
        }
    }
    void ReadEnvironment(std::map<std::string, Environment*>& environments, const char* environmentFile)
    {
        Json::Reader reader;
        Json::FastWriter writer;
        Json::Value root;

        ifstream in_file(environmentFile, ios::binary);
        if (!reader.parse(in_file, root))
        {
            WriteLog(LogLevel::Error, "Parse Config Failed: %s", environmentFile);
            throw std::logic_error("Parse Config Failed.");
        }
        else
        {
            WriteLog(LogLevel::Info, "Parse Config Success: %s", environmentFile);
        }
        for (auto i = 0u; i < root.size(); i++)
        {
            Environment* environment = new Environment();
            strcpy(environment->Name, root[i]["Name"].asString().c_str());
            auto& frontsValue = root[i]["Fronts"];
            for (auto i = 0u; i < frontsValue.size(); i++)
            {
                FrontInfo* frontInfo = new FrontInfo();
                strcpy(frontInfo->TradeFront, frontsValue[i]["TradeFront"].asString().c_str());
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
        in_file.close();
        for (auto& it : environments)
        {
            PrintEnvironment(it.second);
        }
    }
    Environment* GetEnvironment(std::map<std::string, Environment*>& environments, const std::string& environmentName, const std::string& environmentName24)
    {
        auto localTm = TimeUtility::GetLocalTm();
        Environment* environment = nullptr;
        if (localTm->tm_hour >= 16 || localTm->tm_hour < 9)
        {
            environment = environments[environmentName24];
            if (environment == nullptr)
            {
                WriteLog(LogLevel::Error, "environment is nullptr, EnvironmentName:%s", environmentName24.c_str());
            }
            return environment;
        }
        else
        {
            environment = environments[environmentName];
            if (environment == nullptr)
            {
                WriteLog(LogLevel::Error, "environment is nullptr, EnvironmentName:%s", environmentName.c_str());
            }
            return environment;
        }
    }
}

