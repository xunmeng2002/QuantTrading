#pragma warning(disable: 4311)
#include "ServerConfig.h"
#include <Spark/Serialization/json/json.h>
#include <iostream>
#include <fstream>
#include <stdexcept>

using namespace std;

namespace quanttrading::quanttradingcommon
{
    ServerConfig ServerConfig::m_Instance;
    ServerConfig::ServerConfig()
    {

    }
    ServerConfig& ServerConfig::GetInstance()
    {
        return m_Instance;
    }
    void ServerConfig::Load(const char* fileName)
    {
        Json::Reader reader;
        Json::FastWriter writer;
        Json::Value root;
        std::ifstream in_file(fileName, std::ios::binary);
        if (!reader.parse(in_file, root))
        {
            std::cout << "Parse ServerConfig Failed." << std::endl;
            std::string s;
            in_file >> s;
            std::cout << s << std::endl;
            throw std::logic_error("Parse Config Failed.");
        }
        else
        {
            std::cout << "Parse ServerConfig Success." << std::endl;
        }
        in_file.close();

        SEMdOfferAddress = root["SEMdOfferAddress"].asString();
        SETradeFrontAddress = root["SETradeFrontAddress"].asString();
        MdOfferAddress = root["MdOfferAddress"].asString();
        TradeFrontAddress = root["TradeFrontAddress"].asString();
        RiskFrontAddress = root["RiskFrontAddress"].asString();
        AdminFrontAddress = root["AdminFrontAddress"].asString();
        OfferFrontAddress = root["OfferFrontAddress"].asString();
        DBHostAdmin = root["DBHostAdmin"].asString();
        DBHostHistory = root["DBHostHistory"].asString();
        DBHostInit = root["DBHostInit"].asString();
        DBHostSync = root["DBHostSync"].asString();
        DBUser = root["DBUser"].asString();
        DBPasswd = root["DBPasswd"].asString();

        Print();
    }

    void ServerConfig::Print()
    {
        printf("SEMdOfferAddress:[%s], SETradeFrontAddress:[%s], MdOfferAddress:[%s], TradeFrontAddress:[%s], RiskFrontAddress:[%s], AdminFrontAddress:[%s], OfferFrontAddress:[%s], DBHostAdmin:[%s], DBHostHistory:[%s], DBHostInit:[%s], DBHostSync:[%s], DBUser:[%s], DBPasswd:[%s]\n",
            SEMdOfferAddress.c_str(), SETradeFrontAddress.c_str(), MdOfferAddress.c_str(), TradeFrontAddress.c_str(), RiskFrontAddress.c_str(), AdminFrontAddress.c_str(), OfferFrontAddress.c_str(), DBHostAdmin.c_str(), DBHostHistory.c_str(), DBHostInit.c_str(), DBHostSync.c_str(), DBUser.c_str(), DBPasswd.c_str());
    }
}
