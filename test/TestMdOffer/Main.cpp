#include "InnerMdApi.h"
#include "InnerMdSpiImpl.h"
#include "Config/Config.h"
#include "ServerConfig.h"
#include <Spark/Core/Logger/Logger.h>

using namespace quanttrading::testmdoffer;
using namespace quanttrading;

const char* ConfigName = "TestMdOffer.json";

int main(int argc, char* argv[])
{
    auto& config = Config::GetInstance();
    config.Load(ConfigName);
    auto& serverConfig = ServerConfig::GetInstance();
    serverConfig.Load(config.ServerConfigPath.c_str());

    Logger::GetInstance().Init(argv[0]);
    Logger::GetInstance().SetLogLevel(LogLevel(config.LogLevel), LogLevel::Info);
    Logger::GetInstance().Start();


    InnerMdApi* innerMdApi = new InnerMdApi();
    InnerMdSpiImpl* innerMdSpi = new InnerMdSpiImpl(innerMdApi, config.MdUser, config.MdPassword);

    innerMdApi->RegisterSpi(innerMdSpi);
    innerMdApi->RegisterFront(serverConfig.MdOfferAddress.c_str());
    for (auto subscribeInstrument : config.SubscribeInstruments)
    {
        innerMdSpi->AddSubscribeInstrument(subscribeInstrument);
    }
    innerMdApi->Init();
    innerMdApi->Join();

    Logger::GetInstance().Stop();
    Logger::GetInstance().Join();
    return 0;
}
