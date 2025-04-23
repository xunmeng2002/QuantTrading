#include "MdSnap.h"


MdSnap MdSnap::m_Instance;
MdSnap::MdSnap()
{
}
MdSnap& MdSnap::GetInstance()
{
	return m_Instance;
}
RtnDepthMarketDataPackage* MdSnap::GetDepthMd(const char* exchangeID, const char* instrumentID)
{
	auto& depthMds = m_ExchangeDepthMds[exchangeID];
	auto depthMdIt = depthMds.find(instrumentID);
	if (depthMdIt == depthMds.end())
	{
		return nullptr;
	}
	return depthMdIt->second;
}
RtnDepthMarketDataPackage* MdSnap::AddDepthMd(RtnDepthMarketDataPackage* depthMd)
{
	auto& depthMds = m_ExchangeDepthMds[depthMd->DepthMarketData->ExchangeID];
	auto it = depthMds.find(depthMd->DepthMarketData->InstrumentID);
	if (it == depthMds.end())
	{
		depthMd->DepthMarketData->CurrVolume = depthMd->DepthMarketData->Volume;
		depthMd->DepthMarketData->CurrTurnover = depthMd->DepthMarketData->Turnover;
		depthMds[depthMd->DepthMarketData->InstrumentID] = depthMd;
		return depthMd;
	}
	else
	{
		auto lastDepthMd = it->second->DepthMarketData;
		depthMd->DepthMarketData->CurrVolume = depthMd->DepthMarketData->Volume - lastDepthMd->Volume;
		depthMd->DepthMarketData->CurrTurnover = depthMd->DepthMarketData->Turnover - lastDepthMd->Turnover;
		memcpy(it->second->DepthMarketData, depthMd->DepthMarketData, sizeof(DepthMarketDataField));
		depthMd->Free();
		return it->second;
	}
}