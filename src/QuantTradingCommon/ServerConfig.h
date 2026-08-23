#pragma once
#include <string>

using std::string;

namespace quanttrading
{
    class ServerConfig
    {
        ServerConfig();
    public:
        static ServerConfig& GetInstance();
        void Load(const char* fileName);
        void Print();

    public:
        string SEMdOfferAddress;
        string SETradeFrontAddress;
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
}
