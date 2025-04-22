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
		depthMds[depthMd->DepthMarketData->InstrumentID] = depthMd;
		return depthMd;
	}
	else
	{
		memcpy(it->second->DepthMarketData, depthMd->DepthMarketData, sizeof(DepthMarketDataField));
		return it->second;
	}
}