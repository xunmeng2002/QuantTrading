#include "Environment.h"
#include <Spark/Serialization/json/json.h>
#include <Spark/Core/Utility/TimeUtility.h>
#include <Spark/Core/Logger/Logger.h>
#include <cctype>
#include <cstdlib>
#include <cstring>
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
    // 用系统环境变量值覆盖凭证字段,超长时拒绝并跳过(不截断,避免拼出错误凭证)
    static void OverrideSecretField(char* field, size_t fieldSize, const std::string& systemEnvironmentKey, const std::string& systemEnvironmentValue, const char* environmentName)
    {
        if (systemEnvironmentValue.size() >= fieldSize)
        {
            WriteLog(LogLevel::Error, "OverrideSecretsFromSystemEnvironment: %s value too long, Environment:%s, skipped.", systemEnvironmentKey.c_str(), environmentName);
            return;
        }
        systemEnvironmentValue.copy(field, fieldSize - 1);
        field[systemEnvironmentValue.size()] = '\0';
        WriteLog(LogLevel::Info, "OverrideSecretsFromSystemEnvironment: %s applied, Environment:%s.", systemEnvironmentKey.c_str(), environmentName);
    }
    // 凭证(Password/AuthCode)不入库,改由系统环境变量提供:键名 CTP_<环境名大写>_PASSWORD / _AUTHCODE,非空才覆盖
    static void OverrideSecretsFromSystemEnvironment(std::map<std::string, Environment*>& environments)
    {
        for (auto& it : environments)
        {
            Environment* environment = it.second;
            std::string keyPrefix = "CTP_";
            for (auto& nameChar : std::string(environment->Name))
            {
                keyPrefix.push_back(static_cast<char>(toupper(static_cast<unsigned char>(nameChar))));
            }
            const char* passwordValue = getenv((keyPrefix + "_PASSWORD").c_str());
            const char* authCodeValue = getenv((keyPrefix + "_AUTHCODE").c_str());
            for (auto account : environment->Accounts)
            {
                if (passwordValue != nullptr && passwordValue[0] != '\0')
                {
                    OverrideSecretField(account->Password, sizeof(account->Password), keyPrefix + "_PASSWORD", passwordValue, environment->Name);
                }
                else if (strlen(account->Password) == 0)
                {
                    WriteLog(LogLevel::Warning, "OverrideSecretsFromSystemEnvironment: Password empty, Environment:%s. Set %s_PASSWORD, CTP login will fail otherwise.", environment->Name, keyPrefix.c_str());
                }
                if (authCodeValue != nullptr && authCodeValue[0] != '\0')
                {
                    OverrideSecretField(account->AuthCode, sizeof(account->AuthCode), keyPrefix + "_AUTHCODE", authCodeValue, environment->Name);
                }
                else if (strlen(account->AuthCode) == 0)
                {
                    WriteLog(LogLevel::Warning, "OverrideSecretsFromSystemEnvironment: AuthCode empty, Environment:%s. Set %s_AUTHCODE, CTP authentication will fail otherwise.", environment->Name, keyPrefix.c_str());
                }
            }
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
        OverrideSecretsFromSystemEnvironment(environments);
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

