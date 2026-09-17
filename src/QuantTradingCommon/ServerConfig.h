#pragma once
#include <string>

using std::string;

namespace QuantTrading
{
    class ServerConfig
    {
    public:
        static ServerConfig& GetInstance();
        void Load(const char* fileName);
        void Print();

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
        ServerConfig() = default;
        static ServerConfig instance_;
    };
}
