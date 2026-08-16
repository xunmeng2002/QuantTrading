#include "StructLogFunc.h"
#include <Spark/Core/Logger/Logger.h>
#include <limits>

double GetDoubleValue(double& value)
{
	if (value == std::numeric_limits<double>::max())
	{
		return 0.0;
	}
	return value;
}


void WriteDissemination(CThostFtdcDisseminationField* Dissemination)
{
	if(Dissemination)
	{
		WriteLog(LogLevel::Info, "CThostFtdcDisseminationField: SequenceSeries[%d], SequenceNo[%d]",
			Dissemination->SequenceSeries, Dissemination->SequenceNo);
	}
}
void WriteReqUserLogin(CThostFtdcReqUserLoginField* ReqUserLogin)
{
	if(ReqUserLogin)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReqUserLoginField: TradingDay[%s], BrokerID[%s], UserID[%s], Password[%s], UserProductInfo[%s], InterfaceProductInfo[%s], ProtocolInfo[%s], MacAddress[%s], OneTimePassword[%s], reserve1[%s], LoginRemark[%s], ClientIPPort[%d], ClientIPAddress[%s]",
			ReqUserLogin->TradingDay, ReqUserLogin->BrokerID, ReqUserLogin->UserID, ReqUserLogin->Password, ReqUserLogin->UserProductInfo, ReqUserLogin->InterfaceProductInfo, ReqUserLogin->ProtocolInfo, ReqUserLogin->MacAddress, ReqUserLogin->OneTimePassword, ReqUserLogin->reserve1, ReqUserLogin->LoginRemark, ReqUserLogin->ClientIPPort, ReqUserLogin->ClientIPAddress);
	}
}
void WriteRspUserLogin(CThostFtdcRspUserLoginField* RspUserLogin)
{
	if(RspUserLogin)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRspUserLoginField: TradingDay[%s], LoginTime[%s], BrokerID[%s], UserID[%s], SystemName[%s], FrontID[%d], SessionID[%d], MaxOrderRef[%s], SHFETime[%s], DCETime[%s], CZCETime[%s], FFEXTime[%s], INETime[%s], SysVersion[%s], GFEXTime[%s], LoginDRIdentityID[%d], UserDRIdentityID[%d]",
			RspUserLogin->TradingDay, RspUserLogin->LoginTime, RspUserLogin->BrokerID, RspUserLogin->UserID, RspUserLogin->SystemName, RspUserLogin->FrontID, RspUserLogin->SessionID, RspUserLogin->MaxOrderRef, RspUserLogin->SHFETime, RspUserLogin->DCETime, RspUserLogin->CZCETime, RspUserLogin->FFEXTime, RspUserLogin->INETime, RspUserLogin->SysVersion, RspUserLogin->GFEXTime, RspUserLogin->LoginDRIdentityID, RspUserLogin->UserDRIdentityID);
	}
}
void WriteUserLogout(CThostFtdcUserLogoutField* UserLogout)
{
	if(UserLogout)
	{
		WriteLog(LogLevel::Info, "CThostFtdcUserLogoutField: BrokerID[%s], UserID[%s]",
			UserLogout->BrokerID, UserLogout->UserID);
	}
}
void WriteForceUserLogout(CThostFtdcForceUserLogoutField* ForceUserLogout)
{
	if(ForceUserLogout)
	{
		WriteLog(LogLevel::Info, "CThostFtdcForceUserLogoutField: BrokerID[%s], UserID[%s]",
			ForceUserLogout->BrokerID, ForceUserLogout->UserID);
	}
}
void WriteReqAuthenticate(CThostFtdcReqAuthenticateField* ReqAuthenticate)
{
	if(ReqAuthenticate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReqAuthenticateField: BrokerID[%s], UserID[%s], UserProductInfo[%s], AuthCode[%s], AppID[%s]",
			ReqAuthenticate->BrokerID, ReqAuthenticate->UserID, ReqAuthenticate->UserProductInfo, ReqAuthenticate->AuthCode, ReqAuthenticate->AppID);
	}
}
void WriteRspAuthenticate(CThostFtdcRspAuthenticateField* RspAuthenticate)
{
	if(RspAuthenticate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRspAuthenticateField: BrokerID[%s], UserID[%s], UserProductInfo[%s], AppID[%s], AppType[%c]",
			RspAuthenticate->BrokerID, RspAuthenticate->UserID, RspAuthenticate->UserProductInfo, RspAuthenticate->AppID, RspAuthenticate->AppType);
	}
}
void WriteAuthenticationInfo(CThostFtdcAuthenticationInfoField* AuthenticationInfo)
{
	if(AuthenticationInfo)
	{
		WriteLog(LogLevel::Info, "CThostFtdcAuthenticationInfoField: BrokerID[%s], UserID[%s], UserProductInfo[%s], AuthInfo[%s], IsResult[%d], AppID[%s], AppType[%c], reserve1[%s], ClientIPAddress[%s]",
			AuthenticationInfo->BrokerID, AuthenticationInfo->UserID, AuthenticationInfo->UserProductInfo, AuthenticationInfo->AuthInfo, AuthenticationInfo->IsResult, AuthenticationInfo->AppID, AuthenticationInfo->AppType, AuthenticationInfo->reserve1, AuthenticationInfo->ClientIPAddress);
	}
}
void WriteRspUserLogin2(CThostFtdcRspUserLogin2Field* RspUserLogin2)
{
	if(RspUserLogin2)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRspUserLogin2Field: TradingDay[%s], LoginTime[%s], BrokerID[%s], UserID[%s], SystemName[%s], FrontID[%d], SessionID[%d], MaxOrderRef[%s], SHFETime[%s], DCETime[%s], CZCETime[%s], FFEXTime[%s], INETime[%s], RandomString[%s]",
			RspUserLogin2->TradingDay, RspUserLogin2->LoginTime, RspUserLogin2->BrokerID, RspUserLogin2->UserID, RspUserLogin2->SystemName, RspUserLogin2->FrontID, RspUserLogin2->SessionID, RspUserLogin2->MaxOrderRef, RspUserLogin2->SHFETime, RspUserLogin2->DCETime, RspUserLogin2->CZCETime, RspUserLogin2->FFEXTime, RspUserLogin2->INETime, RspUserLogin2->RandomString);
	}
}
void WriteTransferHeader(CThostFtdcTransferHeaderField* TransferHeader)
{
	if(TransferHeader)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTransferHeaderField: Version[%s], TradeCode[%s], TradeDate[%s], TradeTime[%s], TradeSerial[%s], FutureID[%s], BankID[%s], BankBrchID[%s], OperNo[%s], DeviceID[%s], RecordNum[%s], SessionID[%d], RequestID[%d]",
			TransferHeader->Version, TransferHeader->TradeCode, TransferHeader->TradeDate, TransferHeader->TradeTime, TransferHeader->TradeSerial, TransferHeader->FutureID, TransferHeader->BankID, TransferHeader->BankBrchID, TransferHeader->OperNo, TransferHeader->DeviceID, TransferHeader->RecordNum, TransferHeader->SessionID, TransferHeader->RequestID);
	}
}
void WriteTransferBankToFutureReq(CThostFtdcTransferBankToFutureReqField* TransferBankToFutureReq)
{
	if(TransferBankToFutureReq)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTransferBankToFutureReqField: FutureAccount[%s], FuturePwdFlag[%c], FutureAccPwd[%s], TradeAmt[%f], CustFee[%f], CurrencyCode[%s]",
			TransferBankToFutureReq->FutureAccount, TransferBankToFutureReq->FuturePwdFlag, TransferBankToFutureReq->FutureAccPwd, GetDoubleValue(TransferBankToFutureReq->TradeAmt), GetDoubleValue(TransferBankToFutureReq->CustFee), TransferBankToFutureReq->CurrencyCode);
	}
}
void WriteTransferBankToFutureRsp(CThostFtdcTransferBankToFutureRspField* TransferBankToFutureRsp)
{
	if(TransferBankToFutureRsp)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTransferBankToFutureRspField: RetCode[%s], RetInfo[%s], FutureAccount[%s], TradeAmt[%f], CustFee[%f], CurrencyCode[%s]",
			TransferBankToFutureRsp->RetCode, TransferBankToFutureRsp->RetInfo, TransferBankToFutureRsp->FutureAccount, GetDoubleValue(TransferBankToFutureRsp->TradeAmt), GetDoubleValue(TransferBankToFutureRsp->CustFee), TransferBankToFutureRsp->CurrencyCode);
	}
}
void WriteTransferFutureToBankReq(CThostFtdcTransferFutureToBankReqField* TransferFutureToBankReq)
{
	if(TransferFutureToBankReq)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTransferFutureToBankReqField: FutureAccount[%s], FuturePwdFlag[%c], FutureAccPwd[%s], TradeAmt[%f], CustFee[%f], CurrencyCode[%s]",
			TransferFutureToBankReq->FutureAccount, TransferFutureToBankReq->FuturePwdFlag, TransferFutureToBankReq->FutureAccPwd, GetDoubleValue(TransferFutureToBankReq->TradeAmt), GetDoubleValue(TransferFutureToBankReq->CustFee), TransferFutureToBankReq->CurrencyCode);
	}
}
void WriteTransferFutureToBankRsp(CThostFtdcTransferFutureToBankRspField* TransferFutureToBankRsp)
{
	if(TransferFutureToBankRsp)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTransferFutureToBankRspField: RetCode[%s], RetInfo[%s], FutureAccount[%s], TradeAmt[%f], CustFee[%f], CurrencyCode[%s]",
			TransferFutureToBankRsp->RetCode, TransferFutureToBankRsp->RetInfo, TransferFutureToBankRsp->FutureAccount, GetDoubleValue(TransferFutureToBankRsp->TradeAmt), GetDoubleValue(TransferFutureToBankRsp->CustFee), TransferFutureToBankRsp->CurrencyCode);
	}
}
void WriteTransferQryBankReq(CThostFtdcTransferQryBankReqField* TransferQryBankReq)
{
	if(TransferQryBankReq)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTransferQryBankReqField: FutureAccount[%s], FuturePwdFlag[%c], FutureAccPwd[%s], CurrencyCode[%s]",
			TransferQryBankReq->FutureAccount, TransferQryBankReq->FuturePwdFlag, TransferQryBankReq->FutureAccPwd, TransferQryBankReq->CurrencyCode);
	}
}
void WriteTransferQryBankRsp(CThostFtdcTransferQryBankRspField* TransferQryBankRsp)
{
	if(TransferQryBankRsp)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTransferQryBankRspField: RetCode[%s], RetInfo[%s], FutureAccount[%s], TradeAmt[%f], UseAmt[%f], FetchAmt[%f], CurrencyCode[%s]",
			TransferQryBankRsp->RetCode, TransferQryBankRsp->RetInfo, TransferQryBankRsp->FutureAccount, GetDoubleValue(TransferQryBankRsp->TradeAmt), GetDoubleValue(TransferQryBankRsp->UseAmt), GetDoubleValue(TransferQryBankRsp->FetchAmt), TransferQryBankRsp->CurrencyCode);
	}
}
void WriteTransferQryDetailReq(CThostFtdcTransferQryDetailReqField* TransferQryDetailReq)
{
	if(TransferQryDetailReq)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTransferQryDetailReqField: FutureAccount[%s]",
			TransferQryDetailReq->FutureAccount);
	}
}
void WriteTransferQryDetailRsp(CThostFtdcTransferQryDetailRspField* TransferQryDetailRsp)
{
	if(TransferQryDetailRsp)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTransferQryDetailRspField: TradeDate[%s], TradeTime[%s], TradeCode[%s], FutureSerial[%d], FutureID[%s], FutureAccount[%s], BankSerial[%d], BankID[%s], BankBrchID[%s], BankAccount[%s], CertCode[%s], CurrencyCode[%s], TxAmount[%f], Flag[%c]",
			TransferQryDetailRsp->TradeDate, TransferQryDetailRsp->TradeTime, TransferQryDetailRsp->TradeCode, TransferQryDetailRsp->FutureSerial, TransferQryDetailRsp->FutureID, TransferQryDetailRsp->FutureAccount, TransferQryDetailRsp->BankSerial, TransferQryDetailRsp->BankID, TransferQryDetailRsp->BankBrchID, TransferQryDetailRsp->BankAccount, TransferQryDetailRsp->CertCode, TransferQryDetailRsp->CurrencyCode, GetDoubleValue(TransferQryDetailRsp->TxAmount), TransferQryDetailRsp->Flag);
	}
}
void WriteRspInfo(CThostFtdcRspInfoField* RspInfo)
{
	if(RspInfo)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRspInfoField: ErrorID[%d], ErrorMsg[%s]",
			RspInfo->ErrorID, RspInfo->ErrorMsg);
	}
}
void WriteExchange(CThostFtdcExchangeField* Exchange)
{
	if(Exchange)
	{
		WriteLog(LogLevel::Info, "CThostFtdcExchangeField: ExchangeID[%s], ExchangeName[%s], ExchangeProperty[%c]",
			Exchange->ExchangeID, Exchange->ExchangeName, Exchange->ExchangeProperty);
	}
}
void WriteProduct(CThostFtdcProductField* Product)
{
	if(Product)
	{
		WriteLog(LogLevel::Info, "CThostFtdcProductField: reserve1[%s], ProductName[%s], ExchangeID[%s], ProductClass[%c], VolumeMultiple[%d], PriceTick[%f], MaxMarketOrderVolume[%d], MinMarketOrderVolume[%d], MaxLimitOrderVolume[%d], MinLimitOrderVolume[%d], PositionType[%c], PositionDateType[%c], CloseDealType[%c], TradeCurrencyID[%s], MortgageFundUseRange[%c], reserve2[%s], UnderlyingMultiple[%f], ProductID[%s], ExchangeProductID[%s], OpenLimitControlLevel[%c], OrderFreqControlLevel[%c]",
			Product->reserve1, Product->ProductName, Product->ExchangeID, Product->ProductClass, Product->VolumeMultiple, GetDoubleValue(Product->PriceTick), Product->MaxMarketOrderVolume, Product->MinMarketOrderVolume, Product->MaxLimitOrderVolume, Product->MinLimitOrderVolume, Product->PositionType, Product->PositionDateType, Product->CloseDealType, Product->TradeCurrencyID, Product->MortgageFundUseRange, Product->reserve2, GetDoubleValue(Product->UnderlyingMultiple), Product->ProductID, Product->ExchangeProductID, Product->OpenLimitControlLevel, Product->OrderFreqControlLevel);
	}
}
void WriteInstrument(CThostFtdcInstrumentField* Instrument)
{
	if(Instrument)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInstrumentField: reserve1[%s], ExchangeID[%s], InstrumentName[%s], reserve2[%s], reserve3[%s], ProductClass[%c], DeliveryYear[%d], DeliveryMonth[%d], MaxMarketOrderVolume[%d], MinMarketOrderVolume[%d], MaxLimitOrderVolume[%d], MinLimitOrderVolume[%d], VolumeMultiple[%d], PriceTick[%f], CreateDate[%s], OpenDate[%s], ExpireDate[%s], StartDelivDate[%s], EndDelivDate[%s], InstLifePhase[%c], IsTrading[%d], PositionType[%c], PositionDateType[%c], LongMarginRatio[%f], ShortMarginRatio[%f], MaxMarginSideAlgorithm[%c], reserve4[%s], StrikePrice[%f], OptionsType[%c], UnderlyingMultiple[%f], CombinationType[%c], InstrumentID[%s], ExchangeInstID[%s], ProductID[%s], UnderlyingInstrID[%s]",
			Instrument->reserve1, Instrument->ExchangeID, Instrument->InstrumentName, Instrument->reserve2, Instrument->reserve3, Instrument->ProductClass, Instrument->DeliveryYear, Instrument->DeliveryMonth, Instrument->MaxMarketOrderVolume, Instrument->MinMarketOrderVolume, Instrument->MaxLimitOrderVolume, Instrument->MinLimitOrderVolume, Instrument->VolumeMultiple, GetDoubleValue(Instrument->PriceTick), Instrument->CreateDate, Instrument->OpenDate, Instrument->ExpireDate, Instrument->StartDelivDate, Instrument->EndDelivDate, Instrument->InstLifePhase, Instrument->IsTrading, Instrument->PositionType, Instrument->PositionDateType, GetDoubleValue(Instrument->LongMarginRatio), GetDoubleValue(Instrument->ShortMarginRatio), Instrument->MaxMarginSideAlgorithm, Instrument->reserve4, GetDoubleValue(Instrument->StrikePrice), Instrument->OptionsType, GetDoubleValue(Instrument->UnderlyingMultiple), Instrument->CombinationType, Instrument->InstrumentID, Instrument->ExchangeInstID, Instrument->ProductID, Instrument->UnderlyingInstrID);
	}
}
void WriteBroker(CThostFtdcBrokerField* Broker)
{
	if(Broker)
	{
		WriteLog(LogLevel::Info, "CThostFtdcBrokerField: BrokerID[%s], BrokerAbbr[%s], BrokerName[%s], IsActive[%d]",
			Broker->BrokerID, Broker->BrokerAbbr, Broker->BrokerName, Broker->IsActive);
	}
}
void WriteTrader(CThostFtdcTraderField* Trader)
{
	if(Trader)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTraderField: ExchangeID[%s], TraderID[%s], ParticipantID[%s], Password[%s], InstallCount[%d], BrokerID[%s], OrderCancelAlg[%c], TradeInstallCount[%d], MDInstallCount[%d]",
			Trader->ExchangeID, Trader->TraderID, Trader->ParticipantID, Trader->Password, Trader->InstallCount, Trader->BrokerID, Trader->OrderCancelAlg, Trader->TradeInstallCount, Trader->MDInstallCount);
	}
}
void WriteInvestor(CThostFtdcInvestorField* Investor)
{
	if(Investor)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInvestorField: InvestorID[%s], BrokerID[%s], InvestorGroupID[%s], InvestorName[%s], IdentifiedCardType[%c], IdentifiedCardNo[%s], IsActive[%d], Telephone[%s], Address[%s], OpenDate[%s], Mobile[%s], CommModelID[%s], MarginModelID[%s], IsOrderFreq[%c], IsOpenVolLimit[%c]",
			Investor->InvestorID, Investor->BrokerID, Investor->InvestorGroupID, Investor->InvestorName, Investor->IdentifiedCardType, Investor->IdentifiedCardNo, Investor->IsActive, Investor->Telephone, Investor->Address, Investor->OpenDate, Investor->Mobile, Investor->CommModelID, Investor->MarginModelID, Investor->IsOrderFreq, Investor->IsOpenVolLimit);
	}
}
void WriteTradingCode(CThostFtdcTradingCodeField* TradingCode)
{
	if(TradingCode)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTradingCodeField: InvestorID[%s], BrokerID[%s], ExchangeID[%s], ClientID[%s], IsActive[%d], ClientIDType[%c], BranchID[%s], BizType[%c], InvestUnitID[%s]",
			TradingCode->InvestorID, TradingCode->BrokerID, TradingCode->ExchangeID, TradingCode->ClientID, TradingCode->IsActive, TradingCode->ClientIDType, TradingCode->BranchID, TradingCode->BizType, TradingCode->InvestUnitID);
	}
}
void WritePartBroker(CThostFtdcPartBrokerField* PartBroker)
{
	if(PartBroker)
	{
		WriteLog(LogLevel::Info, "CThostFtdcPartBrokerField: BrokerID[%s], ExchangeID[%s], ParticipantID[%s], IsActive[%d]",
			PartBroker->BrokerID, PartBroker->ExchangeID, PartBroker->ParticipantID, PartBroker->IsActive);
	}
}
void WriteSuperUser(CThostFtdcSuperUserField* SuperUser)
{
	if(SuperUser)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSuperUserField: UserID[%s], UserName[%s], Password[%s], IsActive[%d]",
			SuperUser->UserID, SuperUser->UserName, SuperUser->Password, SuperUser->IsActive);
	}
}
void WriteSuperUserFunction(CThostFtdcSuperUserFunctionField* SuperUserFunction)
{
	if(SuperUserFunction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSuperUserFunctionField: UserID[%s], FunctionCode[%c]",
			SuperUserFunction->UserID, SuperUserFunction->FunctionCode);
	}
}
void WriteInvestorGroup(CThostFtdcInvestorGroupField* InvestorGroup)
{
	if(InvestorGroup)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInvestorGroupField: BrokerID[%s], InvestorGroupID[%s], InvestorGroupName[%s]",
			InvestorGroup->BrokerID, InvestorGroup->InvestorGroupID, InvestorGroup->InvestorGroupName);
	}
}
void WriteTradingAccount(CThostFtdcTradingAccountField* TradingAccount)
{
	if(TradingAccount)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTradingAccountField: BrokerID[%s], AccountID[%s], PreMortgage[%f], PreCredit[%f], PreDeposit[%f], PreBalance[%f], PreMargin[%f], InterestBase[%f], Interest[%f], Deposit[%f], Withdraw[%f], FrozenMargin[%f], FrozenCash[%f], FrozenCommission[%f], CurrMargin[%f], CashIn[%f], Commission[%f], CloseProfit[%f], PositionProfit[%f], Balance[%f], Available[%f], WithdrawQuota[%f], Reserve[%f], TradingDay[%s], SettlementID[%d], Credit[%f], Mortgage[%f], ExchangeMargin[%f], DeliveryMargin[%f], ExchangeDeliveryMargin[%f], ReserveBalance[%f], CurrencyID[%s], PreFundMortgageIn[%f], PreFundMortgageOut[%f], FundMortgageIn[%f], FundMortgageOut[%f], FundMortgageAvailable[%f], MortgageableFund[%f], SpecProductMargin[%f], SpecProductFrozenMargin[%f], SpecProductCommission[%f], SpecProductFrozenCommission[%f], SpecProductPositionProfit[%f], SpecProductCloseProfit[%f], SpecProductPositionProfitByAlg[%f], SpecProductExchangeMargin[%f], BizType[%c], FrozenSwap[%f], RemainSwap[%f]",
			TradingAccount->BrokerID, TradingAccount->AccountID, GetDoubleValue(TradingAccount->PreMortgage), GetDoubleValue(TradingAccount->PreCredit), GetDoubleValue(TradingAccount->PreDeposit), GetDoubleValue(TradingAccount->PreBalance), GetDoubleValue(TradingAccount->PreMargin), GetDoubleValue(TradingAccount->InterestBase), GetDoubleValue(TradingAccount->Interest), GetDoubleValue(TradingAccount->Deposit), GetDoubleValue(TradingAccount->Withdraw), GetDoubleValue(TradingAccount->FrozenMargin), GetDoubleValue(TradingAccount->FrozenCash), GetDoubleValue(TradingAccount->FrozenCommission), GetDoubleValue(TradingAccount->CurrMargin), GetDoubleValue(TradingAccount->CashIn), GetDoubleValue(TradingAccount->Commission), GetDoubleValue(TradingAccount->CloseProfit), GetDoubleValue(TradingAccount->PositionProfit), GetDoubleValue(TradingAccount->Balance), GetDoubleValue(TradingAccount->Available), GetDoubleValue(TradingAccount->WithdrawQuota), GetDoubleValue(TradingAccount->Reserve), TradingAccount->TradingDay, TradingAccount->SettlementID, GetDoubleValue(TradingAccount->Credit), GetDoubleValue(TradingAccount->Mortgage), GetDoubleValue(TradingAccount->ExchangeMargin), GetDoubleValue(TradingAccount->DeliveryMargin), GetDoubleValue(TradingAccount->ExchangeDeliveryMargin), GetDoubleValue(TradingAccount->ReserveBalance), TradingAccount->CurrencyID, GetDoubleValue(TradingAccount->PreFundMortgageIn), GetDoubleValue(TradingAccount->PreFundMortgageOut), GetDoubleValue(TradingAccount->FundMortgageIn), GetDoubleValue(TradingAccount->FundMortgageOut), GetDoubleValue(TradingAccount->FundMortgageAvailable), GetDoubleValue(TradingAccount->MortgageableFund), GetDoubleValue(TradingAccount->SpecProductMargin), GetDoubleValue(TradingAccount->SpecProductFrozenMargin), GetDoubleValue(TradingAccount->SpecProductCommission), GetDoubleValue(TradingAccount->SpecProductFrozenCommission), GetDoubleValue(TradingAccount->SpecProductPositionProfit), GetDoubleValue(TradingAccount->SpecProductCloseProfit), GetDoubleValue(TradingAccount->SpecProductPositionProfitByAlg), GetDoubleValue(TradingAccount->SpecProductExchangeMargin), TradingAccount->BizType, GetDoubleValue(TradingAccount->FrozenSwap), GetDoubleValue(TradingAccount->RemainSwap));
	}
}
void WriteInvestorPosition(CThostFtdcInvestorPositionField* InvestorPosition)
{
	if(InvestorPosition)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInvestorPositionField: reserve1[%s], BrokerID[%s], InvestorID[%s], PosiDirection[%c], HedgeFlag[%c], PositionDate[%c], YdPosition[%d], Position[%d], LongFrozen[%d], ShortFrozen[%d], LongFrozenAmount[%f], ShortFrozenAmount[%f], OpenVolume[%d], CloseVolume[%d], OpenAmount[%f], CloseAmount[%f], PositionCost[%f], PreMargin[%f], UseMargin[%f], FrozenMargin[%f], FrozenCash[%f], FrozenCommission[%f], CashIn[%f], Commission[%f], CloseProfit[%f], PositionProfit[%f], PreSettlementPrice[%f], SettlementPrice[%f], TradingDay[%s], SettlementID[%d], OpenCost[%f], ExchangeMargin[%f], CombPosition[%d], CombLongFrozen[%d], CombShortFrozen[%d], CloseProfitByDate[%f], CloseProfitByTrade[%f], TodayPosition[%d], MarginRateByMoney[%f], MarginRateByVolume[%f], StrikeFrozen[%d], StrikeFrozenAmount[%f], AbandonFrozen[%d], ExchangeID[%s], YdStrikeFrozen[%d], InvestUnitID[%s], PositionCostOffset[%f], TasPosition[%d], TasPositionCost[%f], InstrumentID[%s]",
			InvestorPosition->reserve1, InvestorPosition->BrokerID, InvestorPosition->InvestorID, InvestorPosition->PosiDirection, InvestorPosition->HedgeFlag, InvestorPosition->PositionDate, InvestorPosition->YdPosition, InvestorPosition->Position, InvestorPosition->LongFrozen, InvestorPosition->ShortFrozen, GetDoubleValue(InvestorPosition->LongFrozenAmount), GetDoubleValue(InvestorPosition->ShortFrozenAmount), InvestorPosition->OpenVolume, InvestorPosition->CloseVolume, GetDoubleValue(InvestorPosition->OpenAmount), GetDoubleValue(InvestorPosition->CloseAmount), GetDoubleValue(InvestorPosition->PositionCost), GetDoubleValue(InvestorPosition->PreMargin), GetDoubleValue(InvestorPosition->UseMargin), GetDoubleValue(InvestorPosition->FrozenMargin), GetDoubleValue(InvestorPosition->FrozenCash), GetDoubleValue(InvestorPosition->FrozenCommission), GetDoubleValue(InvestorPosition->CashIn), GetDoubleValue(InvestorPosition->Commission), GetDoubleValue(InvestorPosition->CloseProfit), GetDoubleValue(InvestorPosition->PositionProfit), GetDoubleValue(InvestorPosition->PreSettlementPrice), GetDoubleValue(InvestorPosition->SettlementPrice), InvestorPosition->TradingDay, InvestorPosition->SettlementID, GetDoubleValue(InvestorPosition->OpenCost), GetDoubleValue(InvestorPosition->ExchangeMargin), InvestorPosition->CombPosition, InvestorPosition->CombLongFrozen, InvestorPosition->CombShortFrozen, GetDoubleValue(InvestorPosition->CloseProfitByDate), GetDoubleValue(InvestorPosition->CloseProfitByTrade), InvestorPosition->TodayPosition, GetDoubleValue(InvestorPosition->MarginRateByMoney), GetDoubleValue(InvestorPosition->MarginRateByVolume), InvestorPosition->StrikeFrozen, GetDoubleValue(InvestorPosition->StrikeFrozenAmount), InvestorPosition->AbandonFrozen, InvestorPosition->ExchangeID, InvestorPosition->YdStrikeFrozen, InvestorPosition->InvestUnitID, GetDoubleValue(InvestorPosition->PositionCostOffset), InvestorPosition->TasPosition, GetDoubleValue(InvestorPosition->TasPositionCost), InvestorPosition->InstrumentID);
	}
}
void WriteInstrumentMarginRate(CThostFtdcInstrumentMarginRateField* InstrumentMarginRate)
{
	if(InstrumentMarginRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInstrumentMarginRateField: reserve1[%s], InvestorRange[%c], BrokerID[%s], InvestorID[%s], HedgeFlag[%c], LongMarginRatioByMoney[%f], LongMarginRatioByVolume[%f], ShortMarginRatioByMoney[%f], ShortMarginRatioByVolume[%f], IsRelative[%d], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			InstrumentMarginRate->reserve1, InstrumentMarginRate->InvestorRange, InstrumentMarginRate->BrokerID, InstrumentMarginRate->InvestorID, InstrumentMarginRate->HedgeFlag, GetDoubleValue(InstrumentMarginRate->LongMarginRatioByMoney), GetDoubleValue(InstrumentMarginRate->LongMarginRatioByVolume), GetDoubleValue(InstrumentMarginRate->ShortMarginRatioByMoney), GetDoubleValue(InstrumentMarginRate->ShortMarginRatioByVolume), InstrumentMarginRate->IsRelative, InstrumentMarginRate->ExchangeID, InstrumentMarginRate->InvestUnitID, InstrumentMarginRate->InstrumentID);
	}
}
void WriteInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField* InstrumentCommissionRate)
{
	if(InstrumentCommissionRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInstrumentCommissionRateField: reserve1[%s], InvestorRange[%c], BrokerID[%s], InvestorID[%s], OpenRatioByMoney[%f], OpenRatioByVolume[%f], CloseRatioByMoney[%f], CloseRatioByVolume[%f], CloseTodayRatioByMoney[%f], CloseTodayRatioByVolume[%f], ExchangeID[%s], BizType[%c], InvestUnitID[%s], InstrumentID[%s]",
			InstrumentCommissionRate->reserve1, InstrumentCommissionRate->InvestorRange, InstrumentCommissionRate->BrokerID, InstrumentCommissionRate->InvestorID, GetDoubleValue(InstrumentCommissionRate->OpenRatioByMoney), GetDoubleValue(InstrumentCommissionRate->OpenRatioByVolume), GetDoubleValue(InstrumentCommissionRate->CloseRatioByMoney), GetDoubleValue(InstrumentCommissionRate->CloseRatioByVolume), GetDoubleValue(InstrumentCommissionRate->CloseTodayRatioByMoney), GetDoubleValue(InstrumentCommissionRate->CloseTodayRatioByVolume), InstrumentCommissionRate->ExchangeID, InstrumentCommissionRate->BizType, InstrumentCommissionRate->InvestUnitID, InstrumentCommissionRate->InstrumentID);
	}
}
void WriteDepthMarketData(CThostFtdcDepthMarketDataField* DepthMarketData)
{
	if(DepthMarketData)
	{
		WriteLog(LogLevel::Info, "CThostFtdcDepthMarketDataField: TradingDay[%s], reserve1[%s], ExchangeID[%s], reserve2[%s], LastPrice[%f], PreSettlementPrice[%f], PreClosePrice[%f], PreOpenInterest[%f], OpenPrice[%f], HighestPrice[%f], LowestPrice[%f], Volume[%d], Turnover[%f], OpenInterest[%f], ClosePrice[%f], SettlementPrice[%f], UpperLimitPrice[%f], LowerLimitPrice[%f], PreDelta[%f], CurrDelta[%f], UpdateTime[%s], UpdateMillisec[%d], BidPrice1[%f], BidVolume1[%d], AskPrice1[%f], AskVolume1[%d], BidPrice2[%f], BidVolume2[%d], AskPrice2[%f], AskVolume2[%d], BidPrice3[%f], BidVolume3[%d], AskPrice3[%f], AskVolume3[%d], BidPrice4[%f], BidVolume4[%d], AskPrice4[%f], AskVolume4[%d], BidPrice5[%f], BidVolume5[%d], AskPrice5[%f], AskVolume5[%d], AveragePrice[%f], ActionDay[%s], InstrumentID[%s], ExchangeInstID[%s], BandingUpperPrice[%f], BandingLowerPrice[%f]",
			DepthMarketData->TradingDay, DepthMarketData->reserve1, DepthMarketData->ExchangeID, DepthMarketData->reserve2, GetDoubleValue(DepthMarketData->LastPrice), GetDoubleValue(DepthMarketData->PreSettlementPrice), GetDoubleValue(DepthMarketData->PreClosePrice), GetDoubleValue(DepthMarketData->PreOpenInterest), GetDoubleValue(DepthMarketData->OpenPrice), GetDoubleValue(DepthMarketData->HighestPrice), GetDoubleValue(DepthMarketData->LowestPrice), DepthMarketData->Volume, GetDoubleValue(DepthMarketData->Turnover), GetDoubleValue(DepthMarketData->OpenInterest), GetDoubleValue(DepthMarketData->ClosePrice), GetDoubleValue(DepthMarketData->SettlementPrice), GetDoubleValue(DepthMarketData->UpperLimitPrice), GetDoubleValue(DepthMarketData->LowerLimitPrice), GetDoubleValue(DepthMarketData->PreDelta), GetDoubleValue(DepthMarketData->CurrDelta), DepthMarketData->UpdateTime, DepthMarketData->UpdateMillisec, GetDoubleValue(DepthMarketData->BidPrice1), DepthMarketData->BidVolume1, GetDoubleValue(DepthMarketData->AskPrice1), DepthMarketData->AskVolume1, GetDoubleValue(DepthMarketData->BidPrice2), DepthMarketData->BidVolume2, GetDoubleValue(DepthMarketData->AskPrice2), DepthMarketData->AskVolume2, GetDoubleValue(DepthMarketData->BidPrice3), DepthMarketData->BidVolume3, GetDoubleValue(DepthMarketData->AskPrice3), DepthMarketData->AskVolume3, GetDoubleValue(DepthMarketData->BidPrice4), DepthMarketData->BidVolume4, GetDoubleValue(DepthMarketData->AskPrice4), DepthMarketData->AskVolume4, GetDoubleValue(DepthMarketData->BidPrice5), DepthMarketData->BidVolume5, GetDoubleValue(DepthMarketData->AskPrice5), DepthMarketData->AskVolume5, GetDoubleValue(DepthMarketData->AveragePrice), DepthMarketData->ActionDay, DepthMarketData->InstrumentID, DepthMarketData->ExchangeInstID, GetDoubleValue(DepthMarketData->BandingUpperPrice), GetDoubleValue(DepthMarketData->BandingLowerPrice));
	}
}
void WriteInstrumentTradingRight(CThostFtdcInstrumentTradingRightField* InstrumentTradingRight)
{
	if(InstrumentTradingRight)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInstrumentTradingRightField: reserve1[%s], InvestorRange[%c], BrokerID[%s], InvestorID[%s], TradingRight[%c], InstrumentID[%s]",
			InstrumentTradingRight->reserve1, InstrumentTradingRight->InvestorRange, InstrumentTradingRight->BrokerID, InstrumentTradingRight->InvestorID, InstrumentTradingRight->TradingRight, InstrumentTradingRight->InstrumentID);
	}
}
void WriteBrokerUser(CThostFtdcBrokerUserField* BrokerUser)
{
	if(BrokerUser)
	{
		WriteLog(LogLevel::Info, "CThostFtdcBrokerUserField: BrokerID[%s], UserID[%s], UserName[%s], UserType[%c], IsActive[%d], IsUsingOTP[%d], IsAuthForce[%d]",
			BrokerUser->BrokerID, BrokerUser->UserID, BrokerUser->UserName, BrokerUser->UserType, BrokerUser->IsActive, BrokerUser->IsUsingOTP, BrokerUser->IsAuthForce);
	}
}
void WriteBrokerUserPassword(CThostFtdcBrokerUserPasswordField* BrokerUserPassword)
{
	if(BrokerUserPassword)
	{
		WriteLog(LogLevel::Info, "CThostFtdcBrokerUserPasswordField: BrokerID[%s], UserID[%s], Password[%s], LastUpdateTime[%s], LastLoginTime[%s], ExpireDate[%s], WeakExpireDate[%s]",
			BrokerUserPassword->BrokerID, BrokerUserPassword->UserID, BrokerUserPassword->Password, BrokerUserPassword->LastUpdateTime, BrokerUserPassword->LastLoginTime, BrokerUserPassword->ExpireDate, BrokerUserPassword->WeakExpireDate);
	}
}
void WriteBrokerUserFunction(CThostFtdcBrokerUserFunctionField* BrokerUserFunction)
{
	if(BrokerUserFunction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcBrokerUserFunctionField: BrokerID[%s], UserID[%s], BrokerFunctionCode[%c]",
			BrokerUserFunction->BrokerID, BrokerUserFunction->UserID, BrokerUserFunction->BrokerFunctionCode);
	}
}
void WriteTraderOffer(CThostFtdcTraderOfferField* TraderOffer)
{
	if(TraderOffer)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTraderOfferField: ExchangeID[%s], TraderID[%s], ParticipantID[%s], Password[%s], InstallID[%d], OrderLocalID[%s], TraderConnectStatus[%c], ConnectRequestDate[%s], ConnectRequestTime[%s], LastReportDate[%s], LastReportTime[%s], ConnectDate[%s], ConnectTime[%s], StartDate[%s], StartTime[%s], TradingDay[%s], BrokerID[%s], MaxTradeID[%s], MaxOrderMessageReference[%s], OrderCancelAlg[%c]",
			TraderOffer->ExchangeID, TraderOffer->TraderID, TraderOffer->ParticipantID, TraderOffer->Password, TraderOffer->InstallID, TraderOffer->OrderLocalID, TraderOffer->TraderConnectStatus, TraderOffer->ConnectRequestDate, TraderOffer->ConnectRequestTime, TraderOffer->LastReportDate, TraderOffer->LastReportTime, TraderOffer->ConnectDate, TraderOffer->ConnectTime, TraderOffer->StartDate, TraderOffer->StartTime, TraderOffer->TradingDay, TraderOffer->BrokerID, TraderOffer->MaxTradeID, TraderOffer->MaxOrderMessageReference, TraderOffer->OrderCancelAlg);
	}
}
void WriteSettlementInfo(CThostFtdcSettlementInfoField* SettlementInfo)
{
	if(SettlementInfo)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSettlementInfoField: TradingDay[%s], SettlementID[%d], BrokerID[%s], InvestorID[%s], SequenceNo[%d], Content[%s], AccountID[%s], CurrencyID[%s]",
			SettlementInfo->TradingDay, SettlementInfo->SettlementID, SettlementInfo->BrokerID, SettlementInfo->InvestorID, SettlementInfo->SequenceNo, SettlementInfo->Content, SettlementInfo->AccountID, SettlementInfo->CurrencyID);
	}
}
void WriteInstrumentMarginRateAdjust(CThostFtdcInstrumentMarginRateAdjustField* InstrumentMarginRateAdjust)
{
	if(InstrumentMarginRateAdjust)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInstrumentMarginRateAdjustField: reserve1[%s], InvestorRange[%c], BrokerID[%s], InvestorID[%s], HedgeFlag[%c], LongMarginRatioByMoney[%f], LongMarginRatioByVolume[%f], ShortMarginRatioByMoney[%f], ShortMarginRatioByVolume[%f], IsRelative[%d], InstrumentID[%s]",
			InstrumentMarginRateAdjust->reserve1, InstrumentMarginRateAdjust->InvestorRange, InstrumentMarginRateAdjust->BrokerID, InstrumentMarginRateAdjust->InvestorID, InstrumentMarginRateAdjust->HedgeFlag, GetDoubleValue(InstrumentMarginRateAdjust->LongMarginRatioByMoney), GetDoubleValue(InstrumentMarginRateAdjust->LongMarginRatioByVolume), GetDoubleValue(InstrumentMarginRateAdjust->ShortMarginRatioByMoney), GetDoubleValue(InstrumentMarginRateAdjust->ShortMarginRatioByVolume), InstrumentMarginRateAdjust->IsRelative, InstrumentMarginRateAdjust->InstrumentID);
	}
}
void WriteExchangeMarginRate(CThostFtdcExchangeMarginRateField* ExchangeMarginRate)
{
	if(ExchangeMarginRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcExchangeMarginRateField: BrokerID[%s], reserve1[%s], HedgeFlag[%c], LongMarginRatioByMoney[%f], LongMarginRatioByVolume[%f], ShortMarginRatioByMoney[%f], ShortMarginRatioByVolume[%f], ExchangeID[%s], InstrumentID[%s]",
			ExchangeMarginRate->BrokerID, ExchangeMarginRate->reserve1, ExchangeMarginRate->HedgeFlag, GetDoubleValue(ExchangeMarginRate->LongMarginRatioByMoney), GetDoubleValue(ExchangeMarginRate->LongMarginRatioByVolume), GetDoubleValue(ExchangeMarginRate->ShortMarginRatioByMoney), GetDoubleValue(ExchangeMarginRate->ShortMarginRatioByVolume), ExchangeMarginRate->ExchangeID, ExchangeMarginRate->InstrumentID);
	}
}
void WriteExchangeMarginRateAdjust(CThostFtdcExchangeMarginRateAdjustField* ExchangeMarginRateAdjust)
{
	if(ExchangeMarginRateAdjust)
	{
		WriteLog(LogLevel::Info, "CThostFtdcExchangeMarginRateAdjustField: BrokerID[%s], reserve1[%s], HedgeFlag[%c], LongMarginRatioByMoney[%f], LongMarginRatioByVolume[%f], ShortMarginRatioByMoney[%f], ShortMarginRatioByVolume[%f], ExchLongMarginRatioByMoney[%f], ExchLongMarginRatioByVolume[%f], ExchShortMarginRatioByMoney[%f], ExchShortMarginRatioByVolume[%f], NoLongMarginRatioByMoney[%f], NoLongMarginRatioByVolume[%f], NoShortMarginRatioByMoney[%f], NoShortMarginRatioByVolume[%f], InstrumentID[%s]",
			ExchangeMarginRateAdjust->BrokerID, ExchangeMarginRateAdjust->reserve1, ExchangeMarginRateAdjust->HedgeFlag, GetDoubleValue(ExchangeMarginRateAdjust->LongMarginRatioByMoney), GetDoubleValue(ExchangeMarginRateAdjust->LongMarginRatioByVolume), GetDoubleValue(ExchangeMarginRateAdjust->ShortMarginRatioByMoney), GetDoubleValue(ExchangeMarginRateAdjust->ShortMarginRatioByVolume), GetDoubleValue(ExchangeMarginRateAdjust->ExchLongMarginRatioByMoney), GetDoubleValue(ExchangeMarginRateAdjust->ExchLongMarginRatioByVolume), GetDoubleValue(ExchangeMarginRateAdjust->ExchShortMarginRatioByMoney), GetDoubleValue(ExchangeMarginRateAdjust->ExchShortMarginRatioByVolume), GetDoubleValue(ExchangeMarginRateAdjust->NoLongMarginRatioByMoney), GetDoubleValue(ExchangeMarginRateAdjust->NoLongMarginRatioByVolume), GetDoubleValue(ExchangeMarginRateAdjust->NoShortMarginRatioByMoney), GetDoubleValue(ExchangeMarginRateAdjust->NoShortMarginRatioByVolume), ExchangeMarginRateAdjust->InstrumentID);
	}
}
void WriteExchangeRate(CThostFtdcExchangeRateField* ExchangeRate)
{
	if(ExchangeRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcExchangeRateField: BrokerID[%s], FromCurrencyID[%s], FromCurrencyUnit[%f], ToCurrencyID[%s], ExchangeRate[%f]",
			ExchangeRate->BrokerID, ExchangeRate->FromCurrencyID, GetDoubleValue(ExchangeRate->FromCurrencyUnit), ExchangeRate->ToCurrencyID, GetDoubleValue(ExchangeRate->ExchangeRate));
	}
}
void WriteSettlementRef(CThostFtdcSettlementRefField* SettlementRef)
{
	if(SettlementRef)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSettlementRefField: TradingDay[%s], SettlementID[%d]",
			SettlementRef->TradingDay, SettlementRef->SettlementID);
	}
}
void WriteCurrentTime(CThostFtdcCurrentTimeField* CurrentTime)
{
	if(CurrentTime)
	{
		WriteLog(LogLevel::Info, "CThostFtdcCurrentTimeField: CurrDate[%s], CurrTime[%s], CurrMillisec[%d], ActionDay[%s]",
			CurrentTime->CurrDate, CurrentTime->CurrTime, CurrentTime->CurrMillisec, CurrentTime->ActionDay);
	}
}
void WriteCommPhase(CThostFtdcCommPhaseField* CommPhase)
{
	if(CommPhase)
	{
		WriteLog(LogLevel::Info, "CThostFtdcCommPhaseField: TradingDay[%s], CommPhaseNo[%d], SystemID[%s]",
			CommPhase->TradingDay, CommPhase->CommPhaseNo, CommPhase->SystemID);
	}
}
void WriteLoginInfo(CThostFtdcLoginInfoField* LoginInfo)
{
	if(LoginInfo)
	{
		WriteLog(LogLevel::Info, "CThostFtdcLoginInfoField: FrontID[%d], SessionID[%d], BrokerID[%s], UserID[%s], LoginDate[%s], LoginTime[%s], reserve1[%s], UserProductInfo[%s], InterfaceProductInfo[%s], ProtocolInfo[%s], SystemName[%s], PasswordDeprecated[%s], MaxOrderRef[%s], SHFETime[%s], DCETime[%s], CZCETime[%s], FFEXTime[%s], MacAddress[%s], OneTimePassword[%s], INETime[%s], IsQryControl[%d], LoginRemark[%s], Password[%s], IPAddress[%s]",
			LoginInfo->FrontID, LoginInfo->SessionID, LoginInfo->BrokerID, LoginInfo->UserID, LoginInfo->LoginDate, LoginInfo->LoginTime, LoginInfo->reserve1, LoginInfo->UserProductInfo, LoginInfo->InterfaceProductInfo, LoginInfo->ProtocolInfo, LoginInfo->SystemName, LoginInfo->PasswordDeprecated, LoginInfo->MaxOrderRef, LoginInfo->SHFETime, LoginInfo->DCETime, LoginInfo->CZCETime, LoginInfo->FFEXTime, LoginInfo->MacAddress, LoginInfo->OneTimePassword, LoginInfo->INETime, LoginInfo->IsQryControl, LoginInfo->LoginRemark, LoginInfo->Password, LoginInfo->IPAddress);
	}
}
void WriteLogoutAll(CThostFtdcLogoutAllField* LogoutAll)
{
	if(LogoutAll)
	{
		WriteLog(LogLevel::Info, "CThostFtdcLogoutAllField: FrontID[%d], SessionID[%d], SystemName[%s]",
			LogoutAll->FrontID, LogoutAll->SessionID, LogoutAll->SystemName);
	}
}
void WriteFrontStatus(CThostFtdcFrontStatusField* FrontStatus)
{
	if(FrontStatus)
	{
		WriteLog(LogLevel::Info, "CThostFtdcFrontStatusField: FrontID[%d], LastReportDate[%s], LastReportTime[%s], IsActive[%d]",
			FrontStatus->FrontID, FrontStatus->LastReportDate, FrontStatus->LastReportTime, FrontStatus->IsActive);
	}
}
void WriteUserPasswordUpdate(CThostFtdcUserPasswordUpdateField* UserPasswordUpdate)
{
	if(UserPasswordUpdate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcUserPasswordUpdateField: BrokerID[%s], UserID[%s], OldPassword[%s], NewPassword[%s]",
			UserPasswordUpdate->BrokerID, UserPasswordUpdate->UserID, UserPasswordUpdate->OldPassword, UserPasswordUpdate->NewPassword);
	}
}
void WriteInputOrder(CThostFtdcInputOrderField* InputOrder)
{
	if(InputOrder)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInputOrderField: BrokerID[%s], InvestorID[%s], reserve1[%s], OrderRef[%s], UserID[%s], OrderPriceType[%c], Direction[%c], CombOffsetFlag[%s], CombHedgeFlag[%s], LimitPrice[%f], VolumeTotalOriginal[%d], TimeCondition[%c], GTDDate[%s], VolumeCondition[%c], MinVolume[%d], ContingentCondition[%c], StopPrice[%f], ForceCloseReason[%c], IsAutoSuspend[%d], BusinessUnit[%s], RequestID[%d], UserForceClose[%d], IsSwapOrder[%d], ExchangeID[%s], InvestUnitID[%s], AccountID[%s], CurrencyID[%s], ClientID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s], OrderMemo[%s], SessionReqSeq[%d]",
			InputOrder->BrokerID, InputOrder->InvestorID, InputOrder->reserve1, InputOrder->OrderRef, InputOrder->UserID, InputOrder->OrderPriceType, InputOrder->Direction, InputOrder->CombOffsetFlag, InputOrder->CombHedgeFlag, GetDoubleValue(InputOrder->LimitPrice), InputOrder->VolumeTotalOriginal, InputOrder->TimeCondition, InputOrder->GTDDate, InputOrder->VolumeCondition, InputOrder->MinVolume, InputOrder->ContingentCondition, GetDoubleValue(InputOrder->StopPrice), InputOrder->ForceCloseReason, InputOrder->IsAutoSuspend, InputOrder->BusinessUnit, InputOrder->RequestID, InputOrder->UserForceClose, InputOrder->IsSwapOrder, InputOrder->ExchangeID, InputOrder->InvestUnitID, InputOrder->AccountID, InputOrder->CurrencyID, InputOrder->ClientID, InputOrder->reserve2, InputOrder->MacAddress, InputOrder->InstrumentID, InputOrder->IPAddress, InputOrder->OrderMemo, InputOrder->SessionReqSeq);
	}
}
void WriteOrder(CThostFtdcOrderField* Order)
{
	if(Order)
	{
		WriteLog(LogLevel::Info, "CThostFtdcOrderField: BrokerID[%s], InvestorID[%s], reserve1[%s], OrderRef[%s], UserID[%s], OrderPriceType[%c], Direction[%c], CombOffsetFlag[%s], CombHedgeFlag[%s], LimitPrice[%f], VolumeTotalOriginal[%d], TimeCondition[%c], GTDDate[%s], VolumeCondition[%c], MinVolume[%d], ContingentCondition[%c], StopPrice[%f], ForceCloseReason[%c], IsAutoSuspend[%d], BusinessUnit[%s], RequestID[%d], OrderLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve2[%s], TraderID[%s], InstallID[%d], OrderSubmitStatus[%c], NotifySequence[%d], TradingDay[%s], SettlementID[%d], OrderSysID[%s], OrderSource[%c], OrderStatus[%c], OrderType[%c], VolumeTraded[%d], VolumeTotal[%d], InsertDate[%s], InsertTime[%s], ActiveTime[%s], SuspendTime[%s], UpdateTime[%s], CancelTime[%s], ActiveTraderID[%s], ClearingPartID[%s], SequenceNo[%d], FrontID[%d], SessionID[%d], UserProductInfo[%s], StatusMsg[%s], UserForceClose[%d], ActiveUserID[%s], BrokerOrderSeq[%d], RelativeOrderSysID[%s], ZCETotalTradedVolume[%d], IsSwapOrder[%d], BranchID[%s], InvestUnitID[%s], AccountID[%s], CurrencyID[%s], reserve3[%s], MacAddress[%s], InstrumentID[%s], ExchangeInstID[%s], IPAddress[%s], OrderMemo[%s], SessionReqSeq[%d]",
			Order->BrokerID, Order->InvestorID, Order->reserve1, Order->OrderRef, Order->UserID, Order->OrderPriceType, Order->Direction, Order->CombOffsetFlag, Order->CombHedgeFlag, GetDoubleValue(Order->LimitPrice), Order->VolumeTotalOriginal, Order->TimeCondition, Order->GTDDate, Order->VolumeCondition, Order->MinVolume, Order->ContingentCondition, GetDoubleValue(Order->StopPrice), Order->ForceCloseReason, Order->IsAutoSuspend, Order->BusinessUnit, Order->RequestID, Order->OrderLocalID, Order->ExchangeID, Order->ParticipantID, Order->ClientID, Order->reserve2, Order->TraderID, Order->InstallID, Order->OrderSubmitStatus, Order->NotifySequence, Order->TradingDay, Order->SettlementID, Order->OrderSysID, Order->OrderSource, Order->OrderStatus, Order->OrderType, Order->VolumeTraded, Order->VolumeTotal, Order->InsertDate, Order->InsertTime, Order->ActiveTime, Order->SuspendTime, Order->UpdateTime, Order->CancelTime, Order->ActiveTraderID, Order->ClearingPartID, Order->SequenceNo, Order->FrontID, Order->SessionID, Order->UserProductInfo, Order->StatusMsg, Order->UserForceClose, Order->ActiveUserID, Order->BrokerOrderSeq, Order->RelativeOrderSysID, Order->ZCETotalTradedVolume, Order->IsSwapOrder, Order->BranchID, Order->InvestUnitID, Order->AccountID, Order->CurrencyID, Order->reserve3, Order->MacAddress, Order->InstrumentID, Order->ExchangeInstID, Order->IPAddress, Order->OrderMemo, Order->SessionReqSeq);
	}
}
void WriteExchangeOrder(CThostFtdcExchangeOrderField* ExchangeOrder)
{
	if(ExchangeOrder)
	{
		WriteLog(LogLevel::Info, "CThostFtdcExchangeOrderField: OrderPriceType[%c], Direction[%c], CombOffsetFlag[%s], CombHedgeFlag[%s], LimitPrice[%f], VolumeTotalOriginal[%d], TimeCondition[%c], GTDDate[%s], VolumeCondition[%c], MinVolume[%d], ContingentCondition[%c], StopPrice[%f], ForceCloseReason[%c], IsAutoSuspend[%d], BusinessUnit[%s], RequestID[%d], OrderLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve1[%s], TraderID[%s], InstallID[%d], OrderSubmitStatus[%c], NotifySequence[%d], TradingDay[%s], SettlementID[%d], OrderSysID[%s], OrderSource[%c], OrderStatus[%c], OrderType[%c], VolumeTraded[%d], VolumeTotal[%d], InsertDate[%s], InsertTime[%s], ActiveTime[%s], SuspendTime[%s], UpdateTime[%s], CancelTime[%s], ActiveTraderID[%s], ClearingPartID[%s], SequenceNo[%d], BranchID[%s], reserve2[%s], MacAddress[%s], ExchangeInstID[%s], IPAddress[%s]",
			ExchangeOrder->OrderPriceType, ExchangeOrder->Direction, ExchangeOrder->CombOffsetFlag, ExchangeOrder->CombHedgeFlag, GetDoubleValue(ExchangeOrder->LimitPrice), ExchangeOrder->VolumeTotalOriginal, ExchangeOrder->TimeCondition, ExchangeOrder->GTDDate, ExchangeOrder->VolumeCondition, ExchangeOrder->MinVolume, ExchangeOrder->ContingentCondition, GetDoubleValue(ExchangeOrder->StopPrice), ExchangeOrder->ForceCloseReason, ExchangeOrder->IsAutoSuspend, ExchangeOrder->BusinessUnit, ExchangeOrder->RequestID, ExchangeOrder->OrderLocalID, ExchangeOrder->ExchangeID, ExchangeOrder->ParticipantID, ExchangeOrder->ClientID, ExchangeOrder->reserve1, ExchangeOrder->TraderID, ExchangeOrder->InstallID, ExchangeOrder->OrderSubmitStatus, ExchangeOrder->NotifySequence, ExchangeOrder->TradingDay, ExchangeOrder->SettlementID, ExchangeOrder->OrderSysID, ExchangeOrder->OrderSource, ExchangeOrder->OrderStatus, ExchangeOrder->OrderType, ExchangeOrder->VolumeTraded, ExchangeOrder->VolumeTotal, ExchangeOrder->InsertDate, ExchangeOrder->InsertTime, ExchangeOrder->ActiveTime, ExchangeOrder->SuspendTime, ExchangeOrder->UpdateTime, ExchangeOrder->CancelTime, ExchangeOrder->ActiveTraderID, ExchangeOrder->ClearingPartID, ExchangeOrder->SequenceNo, ExchangeOrder->BranchID, ExchangeOrder->reserve2, ExchangeOrder->MacAddress, ExchangeOrder->ExchangeInstID, ExchangeOrder->IPAddress);
	}
}
void WriteExchangeOrderInsertError(CThostFtdcExchangeOrderInsertErrorField* ExchangeOrderInsertError)
{
	if(ExchangeOrderInsertError)
	{
		WriteLog(LogLevel::Info, "CThostFtdcExchangeOrderInsertErrorField: ExchangeID[%s], ParticipantID[%s], TraderID[%s], InstallID[%d], OrderLocalID[%s], ErrorID[%d], ErrorMsg[%s]",
			ExchangeOrderInsertError->ExchangeID, ExchangeOrderInsertError->ParticipantID, ExchangeOrderInsertError->TraderID, ExchangeOrderInsertError->InstallID, ExchangeOrderInsertError->OrderLocalID, ExchangeOrderInsertError->ErrorID, ExchangeOrderInsertError->ErrorMsg);
	}
}
void WriteInputOrderAction(CThostFtdcInputOrderActionField* InputOrderAction)
{
	if(InputOrderAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInputOrderActionField: BrokerID[%s], InvestorID[%s], OrderActionRef[%d], OrderRef[%s], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], OrderSysID[%s], ActionFlag[%c], LimitPrice[%f], VolumeChange[%d], UserID[%s], reserve1[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s], OrderMemo[%s], SessionReqSeq[%d]",
			InputOrderAction->BrokerID, InputOrderAction->InvestorID, InputOrderAction->OrderActionRef, InputOrderAction->OrderRef, InputOrderAction->RequestID, InputOrderAction->FrontID, InputOrderAction->SessionID, InputOrderAction->ExchangeID, InputOrderAction->OrderSysID, InputOrderAction->ActionFlag, GetDoubleValue(InputOrderAction->LimitPrice), InputOrderAction->VolumeChange, InputOrderAction->UserID, InputOrderAction->reserve1, InputOrderAction->InvestUnitID, InputOrderAction->reserve2, InputOrderAction->MacAddress, InputOrderAction->InstrumentID, InputOrderAction->IPAddress, InputOrderAction->OrderMemo, InputOrderAction->SessionReqSeq);
	}
}
void WriteOrderAction(CThostFtdcOrderActionField* OrderAction)
{
	if(OrderAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcOrderActionField: BrokerID[%s], InvestorID[%s], OrderActionRef[%d], OrderRef[%s], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], OrderSysID[%s], ActionFlag[%c], LimitPrice[%f], VolumeChange[%d], ActionDate[%s], ActionTime[%s], TraderID[%s], InstallID[%d], OrderLocalID[%s], ActionLocalID[%s], ParticipantID[%s], ClientID[%s], BusinessUnit[%s], OrderActionStatus[%c], UserID[%s], StatusMsg[%s], reserve1[%s], BranchID[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s], OrderMemo[%s], SessionReqSeq[%d]",
			OrderAction->BrokerID, OrderAction->InvestorID, OrderAction->OrderActionRef, OrderAction->OrderRef, OrderAction->RequestID, OrderAction->FrontID, OrderAction->SessionID, OrderAction->ExchangeID, OrderAction->OrderSysID, OrderAction->ActionFlag, GetDoubleValue(OrderAction->LimitPrice), OrderAction->VolumeChange, OrderAction->ActionDate, OrderAction->ActionTime, OrderAction->TraderID, OrderAction->InstallID, OrderAction->OrderLocalID, OrderAction->ActionLocalID, OrderAction->ParticipantID, OrderAction->ClientID, OrderAction->BusinessUnit, OrderAction->OrderActionStatus, OrderAction->UserID, OrderAction->StatusMsg, OrderAction->reserve1, OrderAction->BranchID, OrderAction->InvestUnitID, OrderAction->reserve2, OrderAction->MacAddress, OrderAction->InstrumentID, OrderAction->IPAddress, OrderAction->OrderMemo, OrderAction->SessionReqSeq);
	}
}
void WriteExchangeOrderAction(CThostFtdcExchangeOrderActionField* ExchangeOrderAction)
{
	if(ExchangeOrderAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcExchangeOrderActionField: ExchangeID[%s], OrderSysID[%s], ActionFlag[%c], LimitPrice[%f], VolumeChange[%d], ActionDate[%s], ActionTime[%s], TraderID[%s], InstallID[%d], OrderLocalID[%s], ActionLocalID[%s], ParticipantID[%s], ClientID[%s], BusinessUnit[%s], OrderActionStatus[%c], UserID[%s], BranchID[%s], reserve1[%s], MacAddress[%s], IPAddress[%s]",
			ExchangeOrderAction->ExchangeID, ExchangeOrderAction->OrderSysID, ExchangeOrderAction->ActionFlag, GetDoubleValue(ExchangeOrderAction->LimitPrice), ExchangeOrderAction->VolumeChange, ExchangeOrderAction->ActionDate, ExchangeOrderAction->ActionTime, ExchangeOrderAction->TraderID, ExchangeOrderAction->InstallID, ExchangeOrderAction->OrderLocalID, ExchangeOrderAction->ActionLocalID, ExchangeOrderAction->ParticipantID, ExchangeOrderAction->ClientID, ExchangeOrderAction->BusinessUnit, ExchangeOrderAction->OrderActionStatus, ExchangeOrderAction->UserID, ExchangeOrderAction->BranchID, ExchangeOrderAction->reserve1, ExchangeOrderAction->MacAddress, ExchangeOrderAction->IPAddress);
	}
}
void WriteExchangeOrderActionError(CThostFtdcExchangeOrderActionErrorField* ExchangeOrderActionError)
{
	if(ExchangeOrderActionError)
	{
		WriteLog(LogLevel::Info, "CThostFtdcExchangeOrderActionErrorField: ExchangeID[%s], OrderSysID[%s], TraderID[%s], InstallID[%d], OrderLocalID[%s], ActionLocalID[%s], ErrorID[%d], ErrorMsg[%s]",
			ExchangeOrderActionError->ExchangeID, ExchangeOrderActionError->OrderSysID, ExchangeOrderActionError->TraderID, ExchangeOrderActionError->InstallID, ExchangeOrderActionError->OrderLocalID, ExchangeOrderActionError->ActionLocalID, ExchangeOrderActionError->ErrorID, ExchangeOrderActionError->ErrorMsg);
	}
}
void WriteExchangeTrade(CThostFtdcExchangeTradeField* ExchangeTrade)
{
	if(ExchangeTrade)
	{
		WriteLog(LogLevel::Info, "CThostFtdcExchangeTradeField: ExchangeID[%s], TradeID[%s], Direction[%c], OrderSysID[%s], ParticipantID[%s], ClientID[%s], TradingRole[%c], reserve1[%s], OffsetFlag[%c], HedgeFlag[%c], Price[%f], Volume[%d], TradeDate[%s], TradeTime[%s], TradeType[%c], PriceSource[%c], TraderID[%s], OrderLocalID[%s], ClearingPartID[%s], BusinessUnit[%s], SequenceNo[%d], TradeSource[%c], ExchangeInstID[%s]",
			ExchangeTrade->ExchangeID, ExchangeTrade->TradeID, ExchangeTrade->Direction, ExchangeTrade->OrderSysID, ExchangeTrade->ParticipantID, ExchangeTrade->ClientID, ExchangeTrade->TradingRole, ExchangeTrade->reserve1, ExchangeTrade->OffsetFlag, ExchangeTrade->HedgeFlag, GetDoubleValue(ExchangeTrade->Price), ExchangeTrade->Volume, ExchangeTrade->TradeDate, ExchangeTrade->TradeTime, ExchangeTrade->TradeType, ExchangeTrade->PriceSource, ExchangeTrade->TraderID, ExchangeTrade->OrderLocalID, ExchangeTrade->ClearingPartID, ExchangeTrade->BusinessUnit, ExchangeTrade->SequenceNo, ExchangeTrade->TradeSource, ExchangeTrade->ExchangeInstID);
	}
}
void WriteTrade(CThostFtdcTradeField* Trade)
{
	if(Trade)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTradeField: BrokerID[%s], InvestorID[%s], reserve1[%s], OrderRef[%s], UserID[%s], ExchangeID[%s], TradeID[%s], Direction[%c], OrderSysID[%s], ParticipantID[%s], ClientID[%s], TradingRole[%c], reserve2[%s], OffsetFlag[%c], HedgeFlag[%c], Price[%f], Volume[%d], TradeDate[%s], TradeTime[%s], TradeType[%c], PriceSource[%c], TraderID[%s], OrderLocalID[%s], ClearingPartID[%s], BusinessUnit[%s], SequenceNo[%d], TradingDay[%s], SettlementID[%d], BrokerOrderSeq[%d], TradeSource[%c], InvestUnitID[%s], InstrumentID[%s], ExchangeInstID[%s]",
			Trade->BrokerID, Trade->InvestorID, Trade->reserve1, Trade->OrderRef, Trade->UserID, Trade->ExchangeID, Trade->TradeID, Trade->Direction, Trade->OrderSysID, Trade->ParticipantID, Trade->ClientID, Trade->TradingRole, Trade->reserve2, Trade->OffsetFlag, Trade->HedgeFlag, GetDoubleValue(Trade->Price), Trade->Volume, Trade->TradeDate, Trade->TradeTime, Trade->TradeType, Trade->PriceSource, Trade->TraderID, Trade->OrderLocalID, Trade->ClearingPartID, Trade->BusinessUnit, Trade->SequenceNo, Trade->TradingDay, Trade->SettlementID, Trade->BrokerOrderSeq, Trade->TradeSource, Trade->InvestUnitID, Trade->InstrumentID, Trade->ExchangeInstID);
	}
}
void WriteUserSession(CThostFtdcUserSessionField* UserSession)
{
	if(UserSession)
	{
		WriteLog(LogLevel::Info, "CThostFtdcUserSessionField: FrontID[%d], SessionID[%d], BrokerID[%s], UserID[%s], LoginDate[%s], LoginTime[%s], reserve1[%s], UserProductInfo[%s], InterfaceProductInfo[%s], ProtocolInfo[%s], MacAddress[%s], LoginRemark[%s], IPAddress[%s]",
			UserSession->FrontID, UserSession->SessionID, UserSession->BrokerID, UserSession->UserID, UserSession->LoginDate, UserSession->LoginTime, UserSession->reserve1, UserSession->UserProductInfo, UserSession->InterfaceProductInfo, UserSession->ProtocolInfo, UserSession->MacAddress, UserSession->LoginRemark, UserSession->IPAddress);
	}
}
void WriteQryMaxOrderVolume(CThostFtdcQryMaxOrderVolumeField* QryMaxOrderVolume)
{
	if(QryMaxOrderVolume)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryMaxOrderVolumeField: BrokerID[%s], InvestorID[%s], reserve1[%s], Direction[%c], OffsetFlag[%c], HedgeFlag[%c], MaxVolume[%d], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			QryMaxOrderVolume->BrokerID, QryMaxOrderVolume->InvestorID, QryMaxOrderVolume->reserve1, QryMaxOrderVolume->Direction, QryMaxOrderVolume->OffsetFlag, QryMaxOrderVolume->HedgeFlag, QryMaxOrderVolume->MaxVolume, QryMaxOrderVolume->ExchangeID, QryMaxOrderVolume->InvestUnitID, QryMaxOrderVolume->InstrumentID);
	}
}
void WriteSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField* SettlementInfoConfirm)
{
	if(SettlementInfoConfirm)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSettlementInfoConfirmField: BrokerID[%s], InvestorID[%s], ConfirmDate[%s], ConfirmTime[%s], SettlementID[%d], AccountID[%s], CurrencyID[%s]",
			SettlementInfoConfirm->BrokerID, SettlementInfoConfirm->InvestorID, SettlementInfoConfirm->ConfirmDate, SettlementInfoConfirm->ConfirmTime, SettlementInfoConfirm->SettlementID, SettlementInfoConfirm->AccountID, SettlementInfoConfirm->CurrencyID);
	}
}
void WriteSyncDeposit(CThostFtdcSyncDepositField* SyncDeposit)
{
	if(SyncDeposit)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDepositField: DepositSeqNo[%s], BrokerID[%s], InvestorID[%s], Deposit[%f], IsForce[%d], CurrencyID[%s], IsFromSopt[%d], TradingPassword[%s], IsSecAgentTranfer[%d]",
			SyncDeposit->DepositSeqNo, SyncDeposit->BrokerID, SyncDeposit->InvestorID, GetDoubleValue(SyncDeposit->Deposit), SyncDeposit->IsForce, SyncDeposit->CurrencyID, SyncDeposit->IsFromSopt, SyncDeposit->TradingPassword, SyncDeposit->IsSecAgentTranfer);
	}
}
void WriteSyncFundMortgage(CThostFtdcSyncFundMortgageField* SyncFundMortgage)
{
	if(SyncFundMortgage)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncFundMortgageField: MortgageSeqNo[%s], BrokerID[%s], InvestorID[%s], FromCurrencyID[%s], MortgageAmount[%f], ToCurrencyID[%s]",
			SyncFundMortgage->MortgageSeqNo, SyncFundMortgage->BrokerID, SyncFundMortgage->InvestorID, SyncFundMortgage->FromCurrencyID, GetDoubleValue(SyncFundMortgage->MortgageAmount), SyncFundMortgage->ToCurrencyID);
	}
}
void WriteBrokerSync(CThostFtdcBrokerSyncField* BrokerSync)
{
	if(BrokerSync)
	{
		WriteLog(LogLevel::Info, "CThostFtdcBrokerSyncField: BrokerID[%s]",
			BrokerSync->BrokerID);
	}
}
void WriteSyncingInvestor(CThostFtdcSyncingInvestorField* SyncingInvestor)
{
	if(SyncingInvestor)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncingInvestorField: InvestorID[%s], BrokerID[%s], InvestorGroupID[%s], InvestorName[%s], IdentifiedCardType[%c], IdentifiedCardNo[%s], IsActive[%d], Telephone[%s], Address[%s], OpenDate[%s], Mobile[%s], CommModelID[%s], MarginModelID[%s], IsOrderFreq[%c], IsOpenVolLimit[%c]",
			SyncingInvestor->InvestorID, SyncingInvestor->BrokerID, SyncingInvestor->InvestorGroupID, SyncingInvestor->InvestorName, SyncingInvestor->IdentifiedCardType, SyncingInvestor->IdentifiedCardNo, SyncingInvestor->IsActive, SyncingInvestor->Telephone, SyncingInvestor->Address, SyncingInvestor->OpenDate, SyncingInvestor->Mobile, SyncingInvestor->CommModelID, SyncingInvestor->MarginModelID, SyncingInvestor->IsOrderFreq, SyncingInvestor->IsOpenVolLimit);
	}
}
void WriteSyncingTradingCode(CThostFtdcSyncingTradingCodeField* SyncingTradingCode)
{
	if(SyncingTradingCode)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncingTradingCodeField: InvestorID[%s], BrokerID[%s], ExchangeID[%s], ClientID[%s], IsActive[%d], ClientIDType[%c]",
			SyncingTradingCode->InvestorID, SyncingTradingCode->BrokerID, SyncingTradingCode->ExchangeID, SyncingTradingCode->ClientID, SyncingTradingCode->IsActive, SyncingTradingCode->ClientIDType);
	}
}
void WriteSyncingInvestorGroup(CThostFtdcSyncingInvestorGroupField* SyncingInvestorGroup)
{
	if(SyncingInvestorGroup)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncingInvestorGroupField: BrokerID[%s], InvestorGroupID[%s], InvestorGroupName[%s]",
			SyncingInvestorGroup->BrokerID, SyncingInvestorGroup->InvestorGroupID, SyncingInvestorGroup->InvestorGroupName);
	}
}
void WriteSyncingTradingAccount(CThostFtdcSyncingTradingAccountField* SyncingTradingAccount)
{
	if(SyncingTradingAccount)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncingTradingAccountField: BrokerID[%s], AccountID[%s], PreMortgage[%f], PreCredit[%f], PreDeposit[%f], PreBalance[%f], PreMargin[%f], InterestBase[%f], Interest[%f], Deposit[%f], Withdraw[%f], FrozenMargin[%f], FrozenCash[%f], FrozenCommission[%f], CurrMargin[%f], CashIn[%f], Commission[%f], CloseProfit[%f], PositionProfit[%f], Balance[%f], Available[%f], WithdrawQuota[%f], Reserve[%f], TradingDay[%s], SettlementID[%d], Credit[%f], Mortgage[%f], ExchangeMargin[%f], DeliveryMargin[%f], ExchangeDeliveryMargin[%f], ReserveBalance[%f], CurrencyID[%s], PreFundMortgageIn[%f], PreFundMortgageOut[%f], FundMortgageIn[%f], FundMortgageOut[%f], FundMortgageAvailable[%f], MortgageableFund[%f], SpecProductMargin[%f], SpecProductFrozenMargin[%f], SpecProductCommission[%f], SpecProductFrozenCommission[%f], SpecProductPositionProfit[%f], SpecProductCloseProfit[%f], SpecProductPositionProfitByAlg[%f], SpecProductExchangeMargin[%f], FrozenSwap[%f], RemainSwap[%f]",
			SyncingTradingAccount->BrokerID, SyncingTradingAccount->AccountID, GetDoubleValue(SyncingTradingAccount->PreMortgage), GetDoubleValue(SyncingTradingAccount->PreCredit), GetDoubleValue(SyncingTradingAccount->PreDeposit), GetDoubleValue(SyncingTradingAccount->PreBalance), GetDoubleValue(SyncingTradingAccount->PreMargin), GetDoubleValue(SyncingTradingAccount->InterestBase), GetDoubleValue(SyncingTradingAccount->Interest), GetDoubleValue(SyncingTradingAccount->Deposit), GetDoubleValue(SyncingTradingAccount->Withdraw), GetDoubleValue(SyncingTradingAccount->FrozenMargin), GetDoubleValue(SyncingTradingAccount->FrozenCash), GetDoubleValue(SyncingTradingAccount->FrozenCommission), GetDoubleValue(SyncingTradingAccount->CurrMargin), GetDoubleValue(SyncingTradingAccount->CashIn), GetDoubleValue(SyncingTradingAccount->Commission), GetDoubleValue(SyncingTradingAccount->CloseProfit), GetDoubleValue(SyncingTradingAccount->PositionProfit), GetDoubleValue(SyncingTradingAccount->Balance), GetDoubleValue(SyncingTradingAccount->Available), GetDoubleValue(SyncingTradingAccount->WithdrawQuota), GetDoubleValue(SyncingTradingAccount->Reserve), SyncingTradingAccount->TradingDay, SyncingTradingAccount->SettlementID, GetDoubleValue(SyncingTradingAccount->Credit), GetDoubleValue(SyncingTradingAccount->Mortgage), GetDoubleValue(SyncingTradingAccount->ExchangeMargin), GetDoubleValue(SyncingTradingAccount->DeliveryMargin), GetDoubleValue(SyncingTradingAccount->ExchangeDeliveryMargin), GetDoubleValue(SyncingTradingAccount->ReserveBalance), SyncingTradingAccount->CurrencyID, GetDoubleValue(SyncingTradingAccount->PreFundMortgageIn), GetDoubleValue(SyncingTradingAccount->PreFundMortgageOut), GetDoubleValue(SyncingTradingAccount->FundMortgageIn), GetDoubleValue(SyncingTradingAccount->FundMortgageOut), GetDoubleValue(SyncingTradingAccount->FundMortgageAvailable), GetDoubleValue(SyncingTradingAccount->MortgageableFund), GetDoubleValue(SyncingTradingAccount->SpecProductMargin), GetDoubleValue(SyncingTradingAccount->SpecProductFrozenMargin), GetDoubleValue(SyncingTradingAccount->SpecProductCommission), GetDoubleValue(SyncingTradingAccount->SpecProductFrozenCommission), GetDoubleValue(SyncingTradingAccount->SpecProductPositionProfit), GetDoubleValue(SyncingTradingAccount->SpecProductCloseProfit), GetDoubleValue(SyncingTradingAccount->SpecProductPositionProfitByAlg), GetDoubleValue(SyncingTradingAccount->SpecProductExchangeMargin), GetDoubleValue(SyncingTradingAccount->FrozenSwap), GetDoubleValue(SyncingTradingAccount->RemainSwap));
	}
}
void WriteSyncingInvestorPosition(CThostFtdcSyncingInvestorPositionField* SyncingInvestorPosition)
{
	if(SyncingInvestorPosition)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncingInvestorPositionField: reserve1[%s], BrokerID[%s], InvestorID[%s], PosiDirection[%c], HedgeFlag[%c], PositionDate[%c], YdPosition[%d], Position[%d], LongFrozen[%d], ShortFrozen[%d], LongFrozenAmount[%f], ShortFrozenAmount[%f], OpenVolume[%d], CloseVolume[%d], OpenAmount[%f], CloseAmount[%f], PositionCost[%f], PreMargin[%f], UseMargin[%f], FrozenMargin[%f], FrozenCash[%f], FrozenCommission[%f], CashIn[%f], Commission[%f], CloseProfit[%f], PositionProfit[%f], PreSettlementPrice[%f], SettlementPrice[%f], TradingDay[%s], SettlementID[%d], OpenCost[%f], ExchangeMargin[%f], CombPosition[%d], CombLongFrozen[%d], CombShortFrozen[%d], CloseProfitByDate[%f], CloseProfitByTrade[%f], TodayPosition[%d], MarginRateByMoney[%f], MarginRateByVolume[%f], StrikeFrozen[%d], StrikeFrozenAmount[%f], AbandonFrozen[%d], ExchangeID[%s], YdStrikeFrozen[%d], InvestUnitID[%s], PositionCostOffset[%f], TasPosition[%d], TasPositionCost[%f], InstrumentID[%s]",
			SyncingInvestorPosition->reserve1, SyncingInvestorPosition->BrokerID, SyncingInvestorPosition->InvestorID, SyncingInvestorPosition->PosiDirection, SyncingInvestorPosition->HedgeFlag, SyncingInvestorPosition->PositionDate, SyncingInvestorPosition->YdPosition, SyncingInvestorPosition->Position, SyncingInvestorPosition->LongFrozen, SyncingInvestorPosition->ShortFrozen, GetDoubleValue(SyncingInvestorPosition->LongFrozenAmount), GetDoubleValue(SyncingInvestorPosition->ShortFrozenAmount), SyncingInvestorPosition->OpenVolume, SyncingInvestorPosition->CloseVolume, GetDoubleValue(SyncingInvestorPosition->OpenAmount), GetDoubleValue(SyncingInvestorPosition->CloseAmount), GetDoubleValue(SyncingInvestorPosition->PositionCost), GetDoubleValue(SyncingInvestorPosition->PreMargin), GetDoubleValue(SyncingInvestorPosition->UseMargin), GetDoubleValue(SyncingInvestorPosition->FrozenMargin), GetDoubleValue(SyncingInvestorPosition->FrozenCash), GetDoubleValue(SyncingInvestorPosition->FrozenCommission), GetDoubleValue(SyncingInvestorPosition->CashIn), GetDoubleValue(SyncingInvestorPosition->Commission), GetDoubleValue(SyncingInvestorPosition->CloseProfit), GetDoubleValue(SyncingInvestorPosition->PositionProfit), GetDoubleValue(SyncingInvestorPosition->PreSettlementPrice), GetDoubleValue(SyncingInvestorPosition->SettlementPrice), SyncingInvestorPosition->TradingDay, SyncingInvestorPosition->SettlementID, GetDoubleValue(SyncingInvestorPosition->OpenCost), GetDoubleValue(SyncingInvestorPosition->ExchangeMargin), SyncingInvestorPosition->CombPosition, SyncingInvestorPosition->CombLongFrozen, SyncingInvestorPosition->CombShortFrozen, GetDoubleValue(SyncingInvestorPosition->CloseProfitByDate), GetDoubleValue(SyncingInvestorPosition->CloseProfitByTrade), SyncingInvestorPosition->TodayPosition, GetDoubleValue(SyncingInvestorPosition->MarginRateByMoney), GetDoubleValue(SyncingInvestorPosition->MarginRateByVolume), SyncingInvestorPosition->StrikeFrozen, GetDoubleValue(SyncingInvestorPosition->StrikeFrozenAmount), SyncingInvestorPosition->AbandonFrozen, SyncingInvestorPosition->ExchangeID, SyncingInvestorPosition->YdStrikeFrozen, SyncingInvestorPosition->InvestUnitID, GetDoubleValue(SyncingInvestorPosition->PositionCostOffset), SyncingInvestorPosition->TasPosition, GetDoubleValue(SyncingInvestorPosition->TasPositionCost), SyncingInvestorPosition->InstrumentID);
	}
}
void WriteSyncingInstrumentMarginRate(CThostFtdcSyncingInstrumentMarginRateField* SyncingInstrumentMarginRate)
{
	if(SyncingInstrumentMarginRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncingInstrumentMarginRateField: reserve1[%s], InvestorRange[%c], BrokerID[%s], InvestorID[%s], HedgeFlag[%c], LongMarginRatioByMoney[%f], LongMarginRatioByVolume[%f], ShortMarginRatioByMoney[%f], ShortMarginRatioByVolume[%f], IsRelative[%d], InstrumentID[%s]",
			SyncingInstrumentMarginRate->reserve1, SyncingInstrumentMarginRate->InvestorRange, SyncingInstrumentMarginRate->BrokerID, SyncingInstrumentMarginRate->InvestorID, SyncingInstrumentMarginRate->HedgeFlag, GetDoubleValue(SyncingInstrumentMarginRate->LongMarginRatioByMoney), GetDoubleValue(SyncingInstrumentMarginRate->LongMarginRatioByVolume), GetDoubleValue(SyncingInstrumentMarginRate->ShortMarginRatioByMoney), GetDoubleValue(SyncingInstrumentMarginRate->ShortMarginRatioByVolume), SyncingInstrumentMarginRate->IsRelative, SyncingInstrumentMarginRate->InstrumentID);
	}
}
void WriteSyncingInstrumentCommissionRate(CThostFtdcSyncingInstrumentCommissionRateField* SyncingInstrumentCommissionRate)
{
	if(SyncingInstrumentCommissionRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncingInstrumentCommissionRateField: reserve1[%s], InvestorRange[%c], BrokerID[%s], InvestorID[%s], OpenRatioByMoney[%f], OpenRatioByVolume[%f], CloseRatioByMoney[%f], CloseRatioByVolume[%f], CloseTodayRatioByMoney[%f], CloseTodayRatioByVolume[%f], InstrumentID[%s]",
			SyncingInstrumentCommissionRate->reserve1, SyncingInstrumentCommissionRate->InvestorRange, SyncingInstrumentCommissionRate->BrokerID, SyncingInstrumentCommissionRate->InvestorID, GetDoubleValue(SyncingInstrumentCommissionRate->OpenRatioByMoney), GetDoubleValue(SyncingInstrumentCommissionRate->OpenRatioByVolume), GetDoubleValue(SyncingInstrumentCommissionRate->CloseRatioByMoney), GetDoubleValue(SyncingInstrumentCommissionRate->CloseRatioByVolume), GetDoubleValue(SyncingInstrumentCommissionRate->CloseTodayRatioByMoney), GetDoubleValue(SyncingInstrumentCommissionRate->CloseTodayRatioByVolume), SyncingInstrumentCommissionRate->InstrumentID);
	}
}
void WriteSyncingInstrumentTradingRight(CThostFtdcSyncingInstrumentTradingRightField* SyncingInstrumentTradingRight)
{
	if(SyncingInstrumentTradingRight)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncingInstrumentTradingRightField: reserve1[%s], InvestorRange[%c], BrokerID[%s], InvestorID[%s], TradingRight[%c], InstrumentID[%s]",
			SyncingInstrumentTradingRight->reserve1, SyncingInstrumentTradingRight->InvestorRange, SyncingInstrumentTradingRight->BrokerID, SyncingInstrumentTradingRight->InvestorID, SyncingInstrumentTradingRight->TradingRight, SyncingInstrumentTradingRight->InstrumentID);
	}
}
void WriteQryOrder(CThostFtdcQryOrderField* QryOrder)
{
	if(QryOrder)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryOrderField: BrokerID[%s], InvestorID[%s], reserve1[%s], ExchangeID[%s], OrderSysID[%s], InsertTimeStart[%s], InsertTimeEnd[%s], InvestUnitID[%s], InstrumentID[%s]",
			QryOrder->BrokerID, QryOrder->InvestorID, QryOrder->reserve1, QryOrder->ExchangeID, QryOrder->OrderSysID, QryOrder->InsertTimeStart, QryOrder->InsertTimeEnd, QryOrder->InvestUnitID, QryOrder->InstrumentID);
	}
}
void WriteQryTrade(CThostFtdcQryTradeField* QryTrade)
{
	if(QryTrade)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryTradeField: BrokerID[%s], InvestorID[%s], reserve1[%s], ExchangeID[%s], TradeID[%s], TradeTimeStart[%s], TradeTimeEnd[%s], InvestUnitID[%s], InstrumentID[%s]",
			QryTrade->BrokerID, QryTrade->InvestorID, QryTrade->reserve1, QryTrade->ExchangeID, QryTrade->TradeID, QryTrade->TradeTimeStart, QryTrade->TradeTimeEnd, QryTrade->InvestUnitID, QryTrade->InstrumentID);
	}
}
void WriteQryInvestorPosition(CThostFtdcQryInvestorPositionField* QryInvestorPosition)
{
	if(QryInvestorPosition)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryInvestorPositionField: BrokerID[%s], InvestorID[%s], reserve1[%s], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			QryInvestorPosition->BrokerID, QryInvestorPosition->InvestorID, QryInvestorPosition->reserve1, QryInvestorPosition->ExchangeID, QryInvestorPosition->InvestUnitID, QryInvestorPosition->InstrumentID);
	}
}
void WriteQryTradingAccount(CThostFtdcQryTradingAccountField* QryTradingAccount)
{
	if(QryTradingAccount)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryTradingAccountField: BrokerID[%s], InvestorID[%s], CurrencyID[%s], BizType[%c], AccountID[%s]",
			QryTradingAccount->BrokerID, QryTradingAccount->InvestorID, QryTradingAccount->CurrencyID, QryTradingAccount->BizType, QryTradingAccount->AccountID);
	}
}
void WriteQryInvestor(CThostFtdcQryInvestorField* QryInvestor)
{
	if(QryInvestor)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryInvestorField: BrokerID[%s], InvestorID[%s]",
			QryInvestor->BrokerID, QryInvestor->InvestorID);
	}
}
void WriteQryTradingCode(CThostFtdcQryTradingCodeField* QryTradingCode)
{
	if(QryTradingCode)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryTradingCodeField: BrokerID[%s], InvestorID[%s], ExchangeID[%s], ClientID[%s], ClientIDType[%c], InvestUnitID[%s]",
			QryTradingCode->BrokerID, QryTradingCode->InvestorID, QryTradingCode->ExchangeID, QryTradingCode->ClientID, QryTradingCode->ClientIDType, QryTradingCode->InvestUnitID);
	}
}
void WriteQryInvestorGroup(CThostFtdcQryInvestorGroupField* QryInvestorGroup)
{
	if(QryInvestorGroup)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryInvestorGroupField: BrokerID[%s]",
			QryInvestorGroup->BrokerID);
	}
}
void WriteQryInstrumentMarginRate(CThostFtdcQryInstrumentMarginRateField* QryInstrumentMarginRate)
{
	if(QryInstrumentMarginRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryInstrumentMarginRateField: BrokerID[%s], InvestorID[%s], reserve1[%s], HedgeFlag[%c], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			QryInstrumentMarginRate->BrokerID, QryInstrumentMarginRate->InvestorID, QryInstrumentMarginRate->reserve1, QryInstrumentMarginRate->HedgeFlag, QryInstrumentMarginRate->ExchangeID, QryInstrumentMarginRate->InvestUnitID, QryInstrumentMarginRate->InstrumentID);
	}
}
void WriteQryInstrumentCommissionRate(CThostFtdcQryInstrumentCommissionRateField* QryInstrumentCommissionRate)
{
	if(QryInstrumentCommissionRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryInstrumentCommissionRateField: BrokerID[%s], InvestorID[%s], reserve1[%s], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			QryInstrumentCommissionRate->BrokerID, QryInstrumentCommissionRate->InvestorID, QryInstrumentCommissionRate->reserve1, QryInstrumentCommissionRate->ExchangeID, QryInstrumentCommissionRate->InvestUnitID, QryInstrumentCommissionRate->InstrumentID);
	}
}
void WriteQryInstrumentTradingRight(CThostFtdcQryInstrumentTradingRightField* QryInstrumentTradingRight)
{
	if(QryInstrumentTradingRight)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryInstrumentTradingRightField: BrokerID[%s], InvestorID[%s], reserve1[%s], InstrumentID[%s]",
			QryInstrumentTradingRight->BrokerID, QryInstrumentTradingRight->InvestorID, QryInstrumentTradingRight->reserve1, QryInstrumentTradingRight->InstrumentID);
	}
}
void WriteQryBroker(CThostFtdcQryBrokerField* QryBroker)
{
	if(QryBroker)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryBrokerField: BrokerID[%s]",
			QryBroker->BrokerID);
	}
}
void WriteQryTrader(CThostFtdcQryTraderField* QryTrader)
{
	if(QryTrader)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryTraderField: ExchangeID[%s], ParticipantID[%s], TraderID[%s]",
			QryTrader->ExchangeID, QryTrader->ParticipantID, QryTrader->TraderID);
	}
}
void WriteQrySuperUserFunction(CThostFtdcQrySuperUserFunctionField* QrySuperUserFunction)
{
	if(QrySuperUserFunction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQrySuperUserFunctionField: UserID[%s]",
			QrySuperUserFunction->UserID);
	}
}
void WriteQryUserSession(CThostFtdcQryUserSessionField* QryUserSession)
{
	if(QryUserSession)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryUserSessionField: FrontID[%d], SessionID[%d], BrokerID[%s], UserID[%s]",
			QryUserSession->FrontID, QryUserSession->SessionID, QryUserSession->BrokerID, QryUserSession->UserID);
	}
}
void WriteQryPartBroker(CThostFtdcQryPartBrokerField* QryPartBroker)
{
	if(QryPartBroker)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryPartBrokerField: ExchangeID[%s], BrokerID[%s], ParticipantID[%s]",
			QryPartBroker->ExchangeID, QryPartBroker->BrokerID, QryPartBroker->ParticipantID);
	}
}
void WriteQryFrontStatus(CThostFtdcQryFrontStatusField* QryFrontStatus)
{
	if(QryFrontStatus)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryFrontStatusField: FrontID[%d]",
			QryFrontStatus->FrontID);
	}
}
void WriteQryExchangeOrder(CThostFtdcQryExchangeOrderField* QryExchangeOrder)
{
	if(QryExchangeOrder)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryExchangeOrderField: ParticipantID[%s], ClientID[%s], reserve1[%s], ExchangeID[%s], TraderID[%s], ExchangeInstID[%s]",
			QryExchangeOrder->ParticipantID, QryExchangeOrder->ClientID, QryExchangeOrder->reserve1, QryExchangeOrder->ExchangeID, QryExchangeOrder->TraderID, QryExchangeOrder->ExchangeInstID);
	}
}
void WriteQryOrderAction(CThostFtdcQryOrderActionField* QryOrderAction)
{
	if(QryOrderAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryOrderActionField: BrokerID[%s], InvestorID[%s], ExchangeID[%s]",
			QryOrderAction->BrokerID, QryOrderAction->InvestorID, QryOrderAction->ExchangeID);
	}
}
void WriteQryExchangeOrderAction(CThostFtdcQryExchangeOrderActionField* QryExchangeOrderAction)
{
	if(QryExchangeOrderAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryExchangeOrderActionField: ParticipantID[%s], ClientID[%s], ExchangeID[%s], TraderID[%s]",
			QryExchangeOrderAction->ParticipantID, QryExchangeOrderAction->ClientID, QryExchangeOrderAction->ExchangeID, QryExchangeOrderAction->TraderID);
	}
}
void WriteQrySuperUser(CThostFtdcQrySuperUserField* QrySuperUser)
{
	if(QrySuperUser)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQrySuperUserField: UserID[%s]",
			QrySuperUser->UserID);
	}
}
void WriteQryExchange(CThostFtdcQryExchangeField* QryExchange)
{
	if(QryExchange)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryExchangeField: ExchangeID[%s]",
			QryExchange->ExchangeID);
	}
}
void WriteQryProduct(CThostFtdcQryProductField* QryProduct)
{
	if(QryProduct)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryProductField: reserve1[%s], ProductClass[%c], ExchangeID[%s], ProductID[%s]",
			QryProduct->reserve1, QryProduct->ProductClass, QryProduct->ExchangeID, QryProduct->ProductID);
	}
}
void WriteQryInstrument(CThostFtdcQryInstrumentField* QryInstrument)
{
	if(QryInstrument)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryInstrumentField: reserve1[%s], ExchangeID[%s], reserve2[%s], reserve3[%s], InstrumentID[%s], ExchangeInstID[%s], ProductID[%s]",
			QryInstrument->reserve1, QryInstrument->ExchangeID, QryInstrument->reserve2, QryInstrument->reserve3, QryInstrument->InstrumentID, QryInstrument->ExchangeInstID, QryInstrument->ProductID);
	}
}
void WriteQryDepthMarketData(CThostFtdcQryDepthMarketDataField* QryDepthMarketData)
{
	if(QryDepthMarketData)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryDepthMarketDataField: reserve1[%s], ExchangeID[%s], InstrumentID[%s], ProductClass[%c]",
			QryDepthMarketData->reserve1, QryDepthMarketData->ExchangeID, QryDepthMarketData->InstrumentID, QryDepthMarketData->ProductClass);
	}
}
void WriteQryBrokerUser(CThostFtdcQryBrokerUserField* QryBrokerUser)
{
	if(QryBrokerUser)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryBrokerUserField: BrokerID[%s], UserID[%s]",
			QryBrokerUser->BrokerID, QryBrokerUser->UserID);
	}
}
void WriteQryBrokerUserFunction(CThostFtdcQryBrokerUserFunctionField* QryBrokerUserFunction)
{
	if(QryBrokerUserFunction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryBrokerUserFunctionField: BrokerID[%s], UserID[%s]",
			QryBrokerUserFunction->BrokerID, QryBrokerUserFunction->UserID);
	}
}
void WriteQryTraderOffer(CThostFtdcQryTraderOfferField* QryTraderOffer)
{
	if(QryTraderOffer)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryTraderOfferField: ExchangeID[%s], ParticipantID[%s], TraderID[%s]",
			QryTraderOffer->ExchangeID, QryTraderOffer->ParticipantID, QryTraderOffer->TraderID);
	}
}
void WriteQrySyncDeposit(CThostFtdcQrySyncDepositField* QrySyncDeposit)
{
	if(QrySyncDeposit)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQrySyncDepositField: BrokerID[%s], DepositSeqNo[%s]",
			QrySyncDeposit->BrokerID, QrySyncDeposit->DepositSeqNo);
	}
}
void WriteQrySettlementInfo(CThostFtdcQrySettlementInfoField* QrySettlementInfo)
{
	if(QrySettlementInfo)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQrySettlementInfoField: BrokerID[%s], InvestorID[%s], TradingDay[%s], AccountID[%s], CurrencyID[%s]",
			QrySettlementInfo->BrokerID, QrySettlementInfo->InvestorID, QrySettlementInfo->TradingDay, QrySettlementInfo->AccountID, QrySettlementInfo->CurrencyID);
	}
}
void WriteQryExchangeMarginRate(CThostFtdcQryExchangeMarginRateField* QryExchangeMarginRate)
{
	if(QryExchangeMarginRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryExchangeMarginRateField: BrokerID[%s], reserve1[%s], HedgeFlag[%c], ExchangeID[%s], InstrumentID[%s]",
			QryExchangeMarginRate->BrokerID, QryExchangeMarginRate->reserve1, QryExchangeMarginRate->HedgeFlag, QryExchangeMarginRate->ExchangeID, QryExchangeMarginRate->InstrumentID);
	}
}
void WriteQryExchangeMarginRateAdjust(CThostFtdcQryExchangeMarginRateAdjustField* QryExchangeMarginRateAdjust)
{
	if(QryExchangeMarginRateAdjust)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryExchangeMarginRateAdjustField: BrokerID[%s], reserve1[%s], HedgeFlag[%c], InstrumentID[%s]",
			QryExchangeMarginRateAdjust->BrokerID, QryExchangeMarginRateAdjust->reserve1, QryExchangeMarginRateAdjust->HedgeFlag, QryExchangeMarginRateAdjust->InstrumentID);
	}
}
void WriteQryExchangeRate(CThostFtdcQryExchangeRateField* QryExchangeRate)
{
	if(QryExchangeRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryExchangeRateField: BrokerID[%s], FromCurrencyID[%s], ToCurrencyID[%s]",
			QryExchangeRate->BrokerID, QryExchangeRate->FromCurrencyID, QryExchangeRate->ToCurrencyID);
	}
}
void WriteQrySyncFundMortgage(CThostFtdcQrySyncFundMortgageField* QrySyncFundMortgage)
{
	if(QrySyncFundMortgage)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQrySyncFundMortgageField: BrokerID[%s], MortgageSeqNo[%s]",
			QrySyncFundMortgage->BrokerID, QrySyncFundMortgage->MortgageSeqNo);
	}
}
void WriteQryHisOrder(CThostFtdcQryHisOrderField* QryHisOrder)
{
	if(QryHisOrder)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryHisOrderField: BrokerID[%s], InvestorID[%s], reserve1[%s], ExchangeID[%s], OrderSysID[%s], InsertTimeStart[%s], InsertTimeEnd[%s], TradingDay[%s], SettlementID[%d], InstrumentID[%s]",
			QryHisOrder->BrokerID, QryHisOrder->InvestorID, QryHisOrder->reserve1, QryHisOrder->ExchangeID, QryHisOrder->OrderSysID, QryHisOrder->InsertTimeStart, QryHisOrder->InsertTimeEnd, QryHisOrder->TradingDay, QryHisOrder->SettlementID, QryHisOrder->InstrumentID);
	}
}
void WriteOptionInstrMiniMargin(CThostFtdcOptionInstrMiniMarginField* OptionInstrMiniMargin)
{
	if(OptionInstrMiniMargin)
	{
		WriteLog(LogLevel::Info, "CThostFtdcOptionInstrMiniMarginField: reserve1[%s], InvestorRange[%c], BrokerID[%s], InvestorID[%s], MinMargin[%f], ValueMethod[%c], IsRelative[%d], InstrumentID[%s]",
			OptionInstrMiniMargin->reserve1, OptionInstrMiniMargin->InvestorRange, OptionInstrMiniMargin->BrokerID, OptionInstrMiniMargin->InvestorID, GetDoubleValue(OptionInstrMiniMargin->MinMargin), OptionInstrMiniMargin->ValueMethod, OptionInstrMiniMargin->IsRelative, OptionInstrMiniMargin->InstrumentID);
	}
}
void WriteOptionInstrMarginAdjust(CThostFtdcOptionInstrMarginAdjustField* OptionInstrMarginAdjust)
{
	if(OptionInstrMarginAdjust)
	{
		WriteLog(LogLevel::Info, "CThostFtdcOptionInstrMarginAdjustField: reserve1[%s], InvestorRange[%c], BrokerID[%s], InvestorID[%s], SShortMarginRatioByMoney[%f], SShortMarginRatioByVolume[%f], HShortMarginRatioByMoney[%f], HShortMarginRatioByVolume[%f], AShortMarginRatioByMoney[%f], AShortMarginRatioByVolume[%f], IsRelative[%d], MShortMarginRatioByMoney[%f], MShortMarginRatioByVolume[%f], InstrumentID[%s]",
			OptionInstrMarginAdjust->reserve1, OptionInstrMarginAdjust->InvestorRange, OptionInstrMarginAdjust->BrokerID, OptionInstrMarginAdjust->InvestorID, GetDoubleValue(OptionInstrMarginAdjust->SShortMarginRatioByMoney), GetDoubleValue(OptionInstrMarginAdjust->SShortMarginRatioByVolume), GetDoubleValue(OptionInstrMarginAdjust->HShortMarginRatioByMoney), GetDoubleValue(OptionInstrMarginAdjust->HShortMarginRatioByVolume), GetDoubleValue(OptionInstrMarginAdjust->AShortMarginRatioByMoney), GetDoubleValue(OptionInstrMarginAdjust->AShortMarginRatioByVolume), OptionInstrMarginAdjust->IsRelative, GetDoubleValue(OptionInstrMarginAdjust->MShortMarginRatioByMoney), GetDoubleValue(OptionInstrMarginAdjust->MShortMarginRatioByVolume), OptionInstrMarginAdjust->InstrumentID);
	}
}
void WriteOptionInstrCommRate(CThostFtdcOptionInstrCommRateField* OptionInstrCommRate)
{
	if(OptionInstrCommRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcOptionInstrCommRateField: reserve1[%s], InvestorRange[%c], BrokerID[%s], InvestorID[%s], OpenRatioByMoney[%f], OpenRatioByVolume[%f], CloseRatioByMoney[%f], CloseRatioByVolume[%f], CloseTodayRatioByMoney[%f], CloseTodayRatioByVolume[%f], StrikeRatioByMoney[%f], StrikeRatioByVolume[%f], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			OptionInstrCommRate->reserve1, OptionInstrCommRate->InvestorRange, OptionInstrCommRate->BrokerID, OptionInstrCommRate->InvestorID, GetDoubleValue(OptionInstrCommRate->OpenRatioByMoney), GetDoubleValue(OptionInstrCommRate->OpenRatioByVolume), GetDoubleValue(OptionInstrCommRate->CloseRatioByMoney), GetDoubleValue(OptionInstrCommRate->CloseRatioByVolume), GetDoubleValue(OptionInstrCommRate->CloseTodayRatioByMoney), GetDoubleValue(OptionInstrCommRate->CloseTodayRatioByVolume), GetDoubleValue(OptionInstrCommRate->StrikeRatioByMoney), GetDoubleValue(OptionInstrCommRate->StrikeRatioByVolume), OptionInstrCommRate->ExchangeID, OptionInstrCommRate->InvestUnitID, OptionInstrCommRate->InstrumentID);
	}
}
void WriteOptionInstrTradeCost(CThostFtdcOptionInstrTradeCostField* OptionInstrTradeCost)
{
	if(OptionInstrTradeCost)
	{
		WriteLog(LogLevel::Info, "CThostFtdcOptionInstrTradeCostField: BrokerID[%s], InvestorID[%s], reserve1[%s], HedgeFlag[%c], FixedMargin[%f], MiniMargin[%f], Royalty[%f], ExchFixedMargin[%f], ExchMiniMargin[%f], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			OptionInstrTradeCost->BrokerID, OptionInstrTradeCost->InvestorID, OptionInstrTradeCost->reserve1, OptionInstrTradeCost->HedgeFlag, GetDoubleValue(OptionInstrTradeCost->FixedMargin), GetDoubleValue(OptionInstrTradeCost->MiniMargin), GetDoubleValue(OptionInstrTradeCost->Royalty), GetDoubleValue(OptionInstrTradeCost->ExchFixedMargin), GetDoubleValue(OptionInstrTradeCost->ExchMiniMargin), OptionInstrTradeCost->ExchangeID, OptionInstrTradeCost->InvestUnitID, OptionInstrTradeCost->InstrumentID);
	}
}
void WriteQryOptionInstrTradeCost(CThostFtdcQryOptionInstrTradeCostField* QryOptionInstrTradeCost)
{
	if(QryOptionInstrTradeCost)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryOptionInstrTradeCostField: BrokerID[%s], InvestorID[%s], reserve1[%s], HedgeFlag[%c], InputPrice[%f], UnderlyingPrice[%f], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			QryOptionInstrTradeCost->BrokerID, QryOptionInstrTradeCost->InvestorID, QryOptionInstrTradeCost->reserve1, QryOptionInstrTradeCost->HedgeFlag, GetDoubleValue(QryOptionInstrTradeCost->InputPrice), GetDoubleValue(QryOptionInstrTradeCost->UnderlyingPrice), QryOptionInstrTradeCost->ExchangeID, QryOptionInstrTradeCost->InvestUnitID, QryOptionInstrTradeCost->InstrumentID);
	}
}
void WriteQryOptionInstrCommRate(CThostFtdcQryOptionInstrCommRateField* QryOptionInstrCommRate)
{
	if(QryOptionInstrCommRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryOptionInstrCommRateField: BrokerID[%s], InvestorID[%s], reserve1[%s], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			QryOptionInstrCommRate->BrokerID, QryOptionInstrCommRate->InvestorID, QryOptionInstrCommRate->reserve1, QryOptionInstrCommRate->ExchangeID, QryOptionInstrCommRate->InvestUnitID, QryOptionInstrCommRate->InstrumentID);
	}
}
void WriteIndexPrice(CThostFtdcIndexPriceField* IndexPrice)
{
	if(IndexPrice)
	{
		WriteLog(LogLevel::Info, "CThostFtdcIndexPriceField: BrokerID[%s], reserve1[%s], ClosePrice[%f], InstrumentID[%s]",
			IndexPrice->BrokerID, IndexPrice->reserve1, GetDoubleValue(IndexPrice->ClosePrice), IndexPrice->InstrumentID);
	}
}
void WriteInputExecOrder(CThostFtdcInputExecOrderField* InputExecOrder)
{
	if(InputExecOrder)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInputExecOrderField: BrokerID[%s], InvestorID[%s], reserve1[%s], ExecOrderRef[%s], UserID[%s], Volume[%d], RequestID[%d], BusinessUnit[%s], OffsetFlag[%c], HedgeFlag[%c], ActionType[%c], PosiDirection[%c], ReservePositionFlag[%c], CloseFlag[%c], ExchangeID[%s], InvestUnitID[%s], AccountID[%s], CurrencyID[%s], ClientID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			InputExecOrder->BrokerID, InputExecOrder->InvestorID, InputExecOrder->reserve1, InputExecOrder->ExecOrderRef, InputExecOrder->UserID, InputExecOrder->Volume, InputExecOrder->RequestID, InputExecOrder->BusinessUnit, InputExecOrder->OffsetFlag, InputExecOrder->HedgeFlag, InputExecOrder->ActionType, InputExecOrder->PosiDirection, InputExecOrder->ReservePositionFlag, InputExecOrder->CloseFlag, InputExecOrder->ExchangeID, InputExecOrder->InvestUnitID, InputExecOrder->AccountID, InputExecOrder->CurrencyID, InputExecOrder->ClientID, InputExecOrder->reserve2, InputExecOrder->MacAddress, InputExecOrder->InstrumentID, InputExecOrder->IPAddress);
	}
}
void WriteInputExecOrderAction(CThostFtdcInputExecOrderActionField* InputExecOrderAction)
{
	if(InputExecOrderAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInputExecOrderActionField: BrokerID[%s], InvestorID[%s], ExecOrderActionRef[%d], ExecOrderRef[%s], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], ExecOrderSysID[%s], ActionFlag[%c], UserID[%s], reserve1[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			InputExecOrderAction->BrokerID, InputExecOrderAction->InvestorID, InputExecOrderAction->ExecOrderActionRef, InputExecOrderAction->ExecOrderRef, InputExecOrderAction->RequestID, InputExecOrderAction->FrontID, InputExecOrderAction->SessionID, InputExecOrderAction->ExchangeID, InputExecOrderAction->ExecOrderSysID, InputExecOrderAction->ActionFlag, InputExecOrderAction->UserID, InputExecOrderAction->reserve1, InputExecOrderAction->InvestUnitID, InputExecOrderAction->reserve2, InputExecOrderAction->MacAddress, InputExecOrderAction->InstrumentID, InputExecOrderAction->IPAddress);
	}
}
void WriteExecOrder(CThostFtdcExecOrderField* ExecOrder)
{
	if(ExecOrder)
	{
		WriteLog(LogLevel::Info, "CThostFtdcExecOrderField: BrokerID[%s], InvestorID[%s], reserve1[%s], ExecOrderRef[%s], UserID[%s], Volume[%d], RequestID[%d], BusinessUnit[%s], OffsetFlag[%c], HedgeFlag[%c], ActionType[%c], PosiDirection[%c], ReservePositionFlag[%c], CloseFlag[%c], ExecOrderLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve2[%s], TraderID[%s], InstallID[%d], OrderSubmitStatus[%c], NotifySequence[%d], TradingDay[%s], SettlementID[%d], ExecOrderSysID[%s], InsertDate[%s], InsertTime[%s], CancelTime[%s], ExecResult[%c], ClearingPartID[%s], SequenceNo[%d], FrontID[%d], SessionID[%d], UserProductInfo[%s], StatusMsg[%s], ActiveUserID[%s], BrokerExecOrderSeq[%d], BranchID[%s], InvestUnitID[%s], AccountID[%s], CurrencyID[%s], reserve3[%s], MacAddress[%s], InstrumentID[%s], ExchangeInstID[%s], IPAddress[%s]",
			ExecOrder->BrokerID, ExecOrder->InvestorID, ExecOrder->reserve1, ExecOrder->ExecOrderRef, ExecOrder->UserID, ExecOrder->Volume, ExecOrder->RequestID, ExecOrder->BusinessUnit, ExecOrder->OffsetFlag, ExecOrder->HedgeFlag, ExecOrder->ActionType, ExecOrder->PosiDirection, ExecOrder->ReservePositionFlag, ExecOrder->CloseFlag, ExecOrder->ExecOrderLocalID, ExecOrder->ExchangeID, ExecOrder->ParticipantID, ExecOrder->ClientID, ExecOrder->reserve2, ExecOrder->TraderID, ExecOrder->InstallID, ExecOrder->OrderSubmitStatus, ExecOrder->NotifySequence, ExecOrder->TradingDay, ExecOrder->SettlementID, ExecOrder->ExecOrderSysID, ExecOrder->InsertDate, ExecOrder->InsertTime, ExecOrder->CancelTime, ExecOrder->ExecResult, ExecOrder->ClearingPartID, ExecOrder->SequenceNo, ExecOrder->FrontID, ExecOrder->SessionID, ExecOrder->UserProductInfo, ExecOrder->StatusMsg, ExecOrder->ActiveUserID, ExecOrder->BrokerExecOrderSeq, ExecOrder->BranchID, ExecOrder->InvestUnitID, ExecOrder->AccountID, ExecOrder->CurrencyID, ExecOrder->reserve3, ExecOrder->MacAddress, ExecOrder->InstrumentID, ExecOrder->ExchangeInstID, ExecOrder->IPAddress);
	}
}
void WriteExecOrderAction(CThostFtdcExecOrderActionField* ExecOrderAction)
{
	if(ExecOrderAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcExecOrderActionField: BrokerID[%s], InvestorID[%s], ExecOrderActionRef[%d], ExecOrderRef[%s], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], ExecOrderSysID[%s], ActionFlag[%c], ActionDate[%s], ActionTime[%s], TraderID[%s], InstallID[%d], ExecOrderLocalID[%s], ActionLocalID[%s], ParticipantID[%s], ClientID[%s], BusinessUnit[%s], OrderActionStatus[%c], UserID[%s], ActionType[%c], StatusMsg[%s], reserve1[%s], BranchID[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			ExecOrderAction->BrokerID, ExecOrderAction->InvestorID, ExecOrderAction->ExecOrderActionRef, ExecOrderAction->ExecOrderRef, ExecOrderAction->RequestID, ExecOrderAction->FrontID, ExecOrderAction->SessionID, ExecOrderAction->ExchangeID, ExecOrderAction->ExecOrderSysID, ExecOrderAction->ActionFlag, ExecOrderAction->ActionDate, ExecOrderAction->ActionTime, ExecOrderAction->TraderID, ExecOrderAction->InstallID, ExecOrderAction->ExecOrderLocalID, ExecOrderAction->ActionLocalID, ExecOrderAction->ParticipantID, ExecOrderAction->ClientID, ExecOrderAction->BusinessUnit, ExecOrderAction->OrderActionStatus, ExecOrderAction->UserID, ExecOrderAction->ActionType, ExecOrderAction->StatusMsg, ExecOrderAction->reserve1, ExecOrderAction->BranchID, ExecOrderAction->InvestUnitID, ExecOrderAction->reserve2, ExecOrderAction->MacAddress, ExecOrderAction->InstrumentID, ExecOrderAction->IPAddress);
	}
}
void WriteQryExecOrder(CThostFtdcQryExecOrderField* QryExecOrder)
{
	if(QryExecOrder)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryExecOrderField: BrokerID[%s], InvestorID[%s], reserve1[%s], ExchangeID[%s], ExecOrderSysID[%s], InsertTimeStart[%s], InsertTimeEnd[%s], InstrumentID[%s]",
			QryExecOrder->BrokerID, QryExecOrder->InvestorID, QryExecOrder->reserve1, QryExecOrder->ExchangeID, QryExecOrder->ExecOrderSysID, QryExecOrder->InsertTimeStart, QryExecOrder->InsertTimeEnd, QryExecOrder->InstrumentID);
	}
}
void WriteExchangeExecOrder(CThostFtdcExchangeExecOrderField* ExchangeExecOrder)
{
	if(ExchangeExecOrder)
	{
		WriteLog(LogLevel::Info, "CThostFtdcExchangeExecOrderField: Volume[%d], RequestID[%d], BusinessUnit[%s], OffsetFlag[%c], HedgeFlag[%c], ActionType[%c], PosiDirection[%c], ReservePositionFlag[%c], CloseFlag[%c], ExecOrderLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve1[%s], TraderID[%s], InstallID[%d], OrderSubmitStatus[%c], NotifySequence[%d], TradingDay[%s], SettlementID[%d], ExecOrderSysID[%s], InsertDate[%s], InsertTime[%s], CancelTime[%s], ExecResult[%c], ClearingPartID[%s], SequenceNo[%d], BranchID[%s], reserve2[%s], MacAddress[%s], ExchangeInstID[%s], IPAddress[%s]",
			ExchangeExecOrder->Volume, ExchangeExecOrder->RequestID, ExchangeExecOrder->BusinessUnit, ExchangeExecOrder->OffsetFlag, ExchangeExecOrder->HedgeFlag, ExchangeExecOrder->ActionType, ExchangeExecOrder->PosiDirection, ExchangeExecOrder->ReservePositionFlag, ExchangeExecOrder->CloseFlag, ExchangeExecOrder->ExecOrderLocalID, ExchangeExecOrder->ExchangeID, ExchangeExecOrder->ParticipantID, ExchangeExecOrder->ClientID, ExchangeExecOrder->reserve1, ExchangeExecOrder->TraderID, ExchangeExecOrder->InstallID, ExchangeExecOrder->OrderSubmitStatus, ExchangeExecOrder->NotifySequence, ExchangeExecOrder->TradingDay, ExchangeExecOrder->SettlementID, ExchangeExecOrder->ExecOrderSysID, ExchangeExecOrder->InsertDate, ExchangeExecOrder->InsertTime, ExchangeExecOrder->CancelTime, ExchangeExecOrder->ExecResult, ExchangeExecOrder->ClearingPartID, ExchangeExecOrder->SequenceNo, ExchangeExecOrder->BranchID, ExchangeExecOrder->reserve2, ExchangeExecOrder->MacAddress, ExchangeExecOrder->ExchangeInstID, ExchangeExecOrder->IPAddress);
	}
}
void WriteQryExchangeExecOrder(CThostFtdcQryExchangeExecOrderField* QryExchangeExecOrder)
{
	if(QryExchangeExecOrder)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryExchangeExecOrderField: ParticipantID[%s], ClientID[%s], reserve1[%s], ExchangeID[%s], TraderID[%s], ExchangeInstID[%s]",
			QryExchangeExecOrder->ParticipantID, QryExchangeExecOrder->ClientID, QryExchangeExecOrder->reserve1, QryExchangeExecOrder->ExchangeID, QryExchangeExecOrder->TraderID, QryExchangeExecOrder->ExchangeInstID);
	}
}
void WriteQryExecOrderAction(CThostFtdcQryExecOrderActionField* QryExecOrderAction)
{
	if(QryExecOrderAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryExecOrderActionField: BrokerID[%s], InvestorID[%s], ExchangeID[%s]",
			QryExecOrderAction->BrokerID, QryExecOrderAction->InvestorID, QryExecOrderAction->ExchangeID);
	}
}
void WriteExchangeExecOrderAction(CThostFtdcExchangeExecOrderActionField* ExchangeExecOrderAction)
{
	if(ExchangeExecOrderAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcExchangeExecOrderActionField: ExchangeID[%s], ExecOrderSysID[%s], ActionFlag[%c], ActionDate[%s], ActionTime[%s], TraderID[%s], InstallID[%d], ExecOrderLocalID[%s], ActionLocalID[%s], ParticipantID[%s], ClientID[%s], BusinessUnit[%s], OrderActionStatus[%c], UserID[%s], ActionType[%c], BranchID[%s], reserve1[%s], MacAddress[%s], reserve2[%s], Volume[%d], IPAddress[%s], ExchangeInstID[%s]",
			ExchangeExecOrderAction->ExchangeID, ExchangeExecOrderAction->ExecOrderSysID, ExchangeExecOrderAction->ActionFlag, ExchangeExecOrderAction->ActionDate, ExchangeExecOrderAction->ActionTime, ExchangeExecOrderAction->TraderID, ExchangeExecOrderAction->InstallID, ExchangeExecOrderAction->ExecOrderLocalID, ExchangeExecOrderAction->ActionLocalID, ExchangeExecOrderAction->ParticipantID, ExchangeExecOrderAction->ClientID, ExchangeExecOrderAction->BusinessUnit, ExchangeExecOrderAction->OrderActionStatus, ExchangeExecOrderAction->UserID, ExchangeExecOrderAction->ActionType, ExchangeExecOrderAction->BranchID, ExchangeExecOrderAction->reserve1, ExchangeExecOrderAction->MacAddress, ExchangeExecOrderAction->reserve2, ExchangeExecOrderAction->Volume, ExchangeExecOrderAction->IPAddress, ExchangeExecOrderAction->ExchangeInstID);
	}
}
void WriteQryExchangeExecOrderAction(CThostFtdcQryExchangeExecOrderActionField* QryExchangeExecOrderAction)
{
	if(QryExchangeExecOrderAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryExchangeExecOrderActionField: ParticipantID[%s], ClientID[%s], ExchangeID[%s], TraderID[%s]",
			QryExchangeExecOrderAction->ParticipantID, QryExchangeExecOrderAction->ClientID, QryExchangeExecOrderAction->ExchangeID, QryExchangeExecOrderAction->TraderID);
	}
}
void WriteErrExecOrder(CThostFtdcErrExecOrderField* ErrExecOrder)
{
	if(ErrExecOrder)
	{
		WriteLog(LogLevel::Info, "CThostFtdcErrExecOrderField: BrokerID[%s], InvestorID[%s], reserve1[%s], ExecOrderRef[%s], UserID[%s], Volume[%d], RequestID[%d], BusinessUnit[%s], OffsetFlag[%c], HedgeFlag[%c], ActionType[%c], PosiDirection[%c], ReservePositionFlag[%c], CloseFlag[%c], ExchangeID[%s], InvestUnitID[%s], AccountID[%s], CurrencyID[%s], ClientID[%s], reserve2[%s], MacAddress[%s], ErrorID[%d], ErrorMsg[%s], InstrumentID[%s], IPAddress[%s]",
			ErrExecOrder->BrokerID, ErrExecOrder->InvestorID, ErrExecOrder->reserve1, ErrExecOrder->ExecOrderRef, ErrExecOrder->UserID, ErrExecOrder->Volume, ErrExecOrder->RequestID, ErrExecOrder->BusinessUnit, ErrExecOrder->OffsetFlag, ErrExecOrder->HedgeFlag, ErrExecOrder->ActionType, ErrExecOrder->PosiDirection, ErrExecOrder->ReservePositionFlag, ErrExecOrder->CloseFlag, ErrExecOrder->ExchangeID, ErrExecOrder->InvestUnitID, ErrExecOrder->AccountID, ErrExecOrder->CurrencyID, ErrExecOrder->ClientID, ErrExecOrder->reserve2, ErrExecOrder->MacAddress, ErrExecOrder->ErrorID, ErrExecOrder->ErrorMsg, ErrExecOrder->InstrumentID, ErrExecOrder->IPAddress);
	}
}
void WriteQryErrExecOrder(CThostFtdcQryErrExecOrderField* QryErrExecOrder)
{
	if(QryErrExecOrder)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryErrExecOrderField: BrokerID[%s], InvestorID[%s]",
			QryErrExecOrder->BrokerID, QryErrExecOrder->InvestorID);
	}
}
void WriteErrExecOrderAction(CThostFtdcErrExecOrderActionField* ErrExecOrderAction)
{
	if(ErrExecOrderAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcErrExecOrderActionField: BrokerID[%s], InvestorID[%s], ExecOrderActionRef[%d], ExecOrderRef[%s], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], ExecOrderSysID[%s], ActionFlag[%c], UserID[%s], reserve1[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], ErrorID[%d], ErrorMsg[%s], InstrumentID[%s], IPAddress[%s]",
			ErrExecOrderAction->BrokerID, ErrExecOrderAction->InvestorID, ErrExecOrderAction->ExecOrderActionRef, ErrExecOrderAction->ExecOrderRef, ErrExecOrderAction->RequestID, ErrExecOrderAction->FrontID, ErrExecOrderAction->SessionID, ErrExecOrderAction->ExchangeID, ErrExecOrderAction->ExecOrderSysID, ErrExecOrderAction->ActionFlag, ErrExecOrderAction->UserID, ErrExecOrderAction->reserve1, ErrExecOrderAction->InvestUnitID, ErrExecOrderAction->reserve2, ErrExecOrderAction->MacAddress, ErrExecOrderAction->ErrorID, ErrExecOrderAction->ErrorMsg, ErrExecOrderAction->InstrumentID, ErrExecOrderAction->IPAddress);
	}
}
void WriteQryErrExecOrderAction(CThostFtdcQryErrExecOrderActionField* QryErrExecOrderAction)
{
	if(QryErrExecOrderAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryErrExecOrderActionField: BrokerID[%s], InvestorID[%s]",
			QryErrExecOrderAction->BrokerID, QryErrExecOrderAction->InvestorID);
	}
}
void WriteOptionInstrTradingRight(CThostFtdcOptionInstrTradingRightField* OptionInstrTradingRight)
{
	if(OptionInstrTradingRight)
	{
		WriteLog(LogLevel::Info, "CThostFtdcOptionInstrTradingRightField: reserve1[%s], InvestorRange[%c], BrokerID[%s], InvestorID[%s], Direction[%c], TradingRight[%c], InstrumentID[%s]",
			OptionInstrTradingRight->reserve1, OptionInstrTradingRight->InvestorRange, OptionInstrTradingRight->BrokerID, OptionInstrTradingRight->InvestorID, OptionInstrTradingRight->Direction, OptionInstrTradingRight->TradingRight, OptionInstrTradingRight->InstrumentID);
	}
}
void WriteQryOptionInstrTradingRight(CThostFtdcQryOptionInstrTradingRightField* QryOptionInstrTradingRight)
{
	if(QryOptionInstrTradingRight)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryOptionInstrTradingRightField: BrokerID[%s], InvestorID[%s], reserve1[%s], Direction[%c], InstrumentID[%s]",
			QryOptionInstrTradingRight->BrokerID, QryOptionInstrTradingRight->InvestorID, QryOptionInstrTradingRight->reserve1, QryOptionInstrTradingRight->Direction, QryOptionInstrTradingRight->InstrumentID);
	}
}
void WriteInputForQuote(CThostFtdcInputForQuoteField* InputForQuote)
{
	if(InputForQuote)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInputForQuoteField: BrokerID[%s], InvestorID[%s], reserve1[%s], ForQuoteRef[%s], UserID[%s], ExchangeID[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			InputForQuote->BrokerID, InputForQuote->InvestorID, InputForQuote->reserve1, InputForQuote->ForQuoteRef, InputForQuote->UserID, InputForQuote->ExchangeID, InputForQuote->InvestUnitID, InputForQuote->reserve2, InputForQuote->MacAddress, InputForQuote->InstrumentID, InputForQuote->IPAddress);
	}
}
void WriteForQuote(CThostFtdcForQuoteField* ForQuote)
{
	if(ForQuote)
	{
		WriteLog(LogLevel::Info, "CThostFtdcForQuoteField: BrokerID[%s], InvestorID[%s], reserve1[%s], ForQuoteRef[%s], UserID[%s], ForQuoteLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve2[%s], TraderID[%s], InstallID[%d], InsertDate[%s], InsertTime[%s], ForQuoteStatus[%c], FrontID[%d], SessionID[%d], StatusMsg[%s], ActiveUserID[%s], BrokerForQutoSeq[%d], InvestUnitID[%s], reserve3[%s], MacAddress[%s], InstrumentID[%s], ExchangeInstID[%s], IPAddress[%s]",
			ForQuote->BrokerID, ForQuote->InvestorID, ForQuote->reserve1, ForQuote->ForQuoteRef, ForQuote->UserID, ForQuote->ForQuoteLocalID, ForQuote->ExchangeID, ForQuote->ParticipantID, ForQuote->ClientID, ForQuote->reserve2, ForQuote->TraderID, ForQuote->InstallID, ForQuote->InsertDate, ForQuote->InsertTime, ForQuote->ForQuoteStatus, ForQuote->FrontID, ForQuote->SessionID, ForQuote->StatusMsg, ForQuote->ActiveUserID, ForQuote->BrokerForQutoSeq, ForQuote->InvestUnitID, ForQuote->reserve3, ForQuote->MacAddress, ForQuote->InstrumentID, ForQuote->ExchangeInstID, ForQuote->IPAddress);
	}
}
void WriteQryForQuote(CThostFtdcQryForQuoteField* QryForQuote)
{
	if(QryForQuote)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryForQuoteField: BrokerID[%s], InvestorID[%s], reserve1[%s], ExchangeID[%s], InsertTimeStart[%s], InsertTimeEnd[%s], InvestUnitID[%s], InstrumentID[%s]",
			QryForQuote->BrokerID, QryForQuote->InvestorID, QryForQuote->reserve1, QryForQuote->ExchangeID, QryForQuote->InsertTimeStart, QryForQuote->InsertTimeEnd, QryForQuote->InvestUnitID, QryForQuote->InstrumentID);
	}
}
void WriteExchangeForQuote(CThostFtdcExchangeForQuoteField* ExchangeForQuote)
{
	if(ExchangeForQuote)
	{
		WriteLog(LogLevel::Info, "CThostFtdcExchangeForQuoteField: ForQuoteLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve1[%s], TraderID[%s], InstallID[%d], InsertDate[%s], InsertTime[%s], ForQuoteStatus[%c], reserve2[%s], MacAddress[%s], ExchangeInstID[%s], IPAddress[%s]",
			ExchangeForQuote->ForQuoteLocalID, ExchangeForQuote->ExchangeID, ExchangeForQuote->ParticipantID, ExchangeForQuote->ClientID, ExchangeForQuote->reserve1, ExchangeForQuote->TraderID, ExchangeForQuote->InstallID, ExchangeForQuote->InsertDate, ExchangeForQuote->InsertTime, ExchangeForQuote->ForQuoteStatus, ExchangeForQuote->reserve2, ExchangeForQuote->MacAddress, ExchangeForQuote->ExchangeInstID, ExchangeForQuote->IPAddress);
	}
}
void WriteQryExchangeForQuote(CThostFtdcQryExchangeForQuoteField* QryExchangeForQuote)
{
	if(QryExchangeForQuote)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryExchangeForQuoteField: ParticipantID[%s], ClientID[%s], reserve1[%s], ExchangeID[%s], TraderID[%s], ExchangeInstID[%s]",
			QryExchangeForQuote->ParticipantID, QryExchangeForQuote->ClientID, QryExchangeForQuote->reserve1, QryExchangeForQuote->ExchangeID, QryExchangeForQuote->TraderID, QryExchangeForQuote->ExchangeInstID);
	}
}
void WriteInputQuote(CThostFtdcInputQuoteField* InputQuote)
{
	if(InputQuote)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInputQuoteField: BrokerID[%s], InvestorID[%s], reserve1[%s], QuoteRef[%s], UserID[%s], AskPrice[%f], BidPrice[%f], AskVolume[%d], BidVolume[%d], RequestID[%d], BusinessUnit[%s], AskOffsetFlag[%c], BidOffsetFlag[%c], AskHedgeFlag[%c], BidHedgeFlag[%c], AskOrderRef[%s], BidOrderRef[%s], ForQuoteSysID[%s], ExchangeID[%s], InvestUnitID[%s], ClientID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s], ReplaceSysID[%s], TimeCondition[%c], OrderMemo[%s], SessionReqSeq[%d]",
			InputQuote->BrokerID, InputQuote->InvestorID, InputQuote->reserve1, InputQuote->QuoteRef, InputQuote->UserID, GetDoubleValue(InputQuote->AskPrice), GetDoubleValue(InputQuote->BidPrice), InputQuote->AskVolume, InputQuote->BidVolume, InputQuote->RequestID, InputQuote->BusinessUnit, InputQuote->AskOffsetFlag, InputQuote->BidOffsetFlag, InputQuote->AskHedgeFlag, InputQuote->BidHedgeFlag, InputQuote->AskOrderRef, InputQuote->BidOrderRef, InputQuote->ForQuoteSysID, InputQuote->ExchangeID, InputQuote->InvestUnitID, InputQuote->ClientID, InputQuote->reserve2, InputQuote->MacAddress, InputQuote->InstrumentID, InputQuote->IPAddress, InputQuote->ReplaceSysID, InputQuote->TimeCondition, InputQuote->OrderMemo, InputQuote->SessionReqSeq);
	}
}
void WriteInputQuoteAction(CThostFtdcInputQuoteActionField* InputQuoteAction)
{
	if(InputQuoteAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInputQuoteActionField: BrokerID[%s], InvestorID[%s], QuoteActionRef[%d], QuoteRef[%s], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], QuoteSysID[%s], ActionFlag[%c], UserID[%s], reserve1[%s], InvestUnitID[%s], ClientID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s], OrderMemo[%s], SessionReqSeq[%d]",
			InputQuoteAction->BrokerID, InputQuoteAction->InvestorID, InputQuoteAction->QuoteActionRef, InputQuoteAction->QuoteRef, InputQuoteAction->RequestID, InputQuoteAction->FrontID, InputQuoteAction->SessionID, InputQuoteAction->ExchangeID, InputQuoteAction->QuoteSysID, InputQuoteAction->ActionFlag, InputQuoteAction->UserID, InputQuoteAction->reserve1, InputQuoteAction->InvestUnitID, InputQuoteAction->ClientID, InputQuoteAction->reserve2, InputQuoteAction->MacAddress, InputQuoteAction->InstrumentID, InputQuoteAction->IPAddress, InputQuoteAction->OrderMemo, InputQuoteAction->SessionReqSeq);
	}
}
void WriteQuote(CThostFtdcQuoteField* Quote)
{
	if(Quote)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQuoteField: BrokerID[%s], InvestorID[%s], reserve1[%s], QuoteRef[%s], UserID[%s], AskPrice[%f], BidPrice[%f], AskVolume[%d], BidVolume[%d], RequestID[%d], BusinessUnit[%s], AskOffsetFlag[%c], BidOffsetFlag[%c], AskHedgeFlag[%c], BidHedgeFlag[%c], QuoteLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve2[%s], TraderID[%s], InstallID[%d], NotifySequence[%d], OrderSubmitStatus[%c], TradingDay[%s], SettlementID[%d], QuoteSysID[%s], InsertDate[%s], InsertTime[%s], CancelTime[%s], QuoteStatus[%c], ClearingPartID[%s], SequenceNo[%d], AskOrderSysID[%s], BidOrderSysID[%s], FrontID[%d], SessionID[%d], UserProductInfo[%s], StatusMsg[%s], ActiveUserID[%s], BrokerQuoteSeq[%d], AskOrderRef[%s], BidOrderRef[%s], ForQuoteSysID[%s], BranchID[%s], InvestUnitID[%s], AccountID[%s], CurrencyID[%s], reserve3[%s], MacAddress[%s], InstrumentID[%s], ExchangeInstID[%s], IPAddress[%s], ReplaceSysID[%s], TimeCondition[%c], OrderMemo[%s], SessionReqSeq[%d]",
			Quote->BrokerID, Quote->InvestorID, Quote->reserve1, Quote->QuoteRef, Quote->UserID, GetDoubleValue(Quote->AskPrice), GetDoubleValue(Quote->BidPrice), Quote->AskVolume, Quote->BidVolume, Quote->RequestID, Quote->BusinessUnit, Quote->AskOffsetFlag, Quote->BidOffsetFlag, Quote->AskHedgeFlag, Quote->BidHedgeFlag, Quote->QuoteLocalID, Quote->ExchangeID, Quote->ParticipantID, Quote->ClientID, Quote->reserve2, Quote->TraderID, Quote->InstallID, Quote->NotifySequence, Quote->OrderSubmitStatus, Quote->TradingDay, Quote->SettlementID, Quote->QuoteSysID, Quote->InsertDate, Quote->InsertTime, Quote->CancelTime, Quote->QuoteStatus, Quote->ClearingPartID, Quote->SequenceNo, Quote->AskOrderSysID, Quote->BidOrderSysID, Quote->FrontID, Quote->SessionID, Quote->UserProductInfo, Quote->StatusMsg, Quote->ActiveUserID, Quote->BrokerQuoteSeq, Quote->AskOrderRef, Quote->BidOrderRef, Quote->ForQuoteSysID, Quote->BranchID, Quote->InvestUnitID, Quote->AccountID, Quote->CurrencyID, Quote->reserve3, Quote->MacAddress, Quote->InstrumentID, Quote->ExchangeInstID, Quote->IPAddress, Quote->ReplaceSysID, Quote->TimeCondition, Quote->OrderMemo, Quote->SessionReqSeq);
	}
}
void WriteQuoteAction(CThostFtdcQuoteActionField* QuoteAction)
{
	if(QuoteAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQuoteActionField: BrokerID[%s], InvestorID[%s], QuoteActionRef[%d], QuoteRef[%s], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], QuoteSysID[%s], ActionFlag[%c], ActionDate[%s], ActionTime[%s], TraderID[%s], InstallID[%d], QuoteLocalID[%s], ActionLocalID[%s], ParticipantID[%s], ClientID[%s], BusinessUnit[%s], OrderActionStatus[%c], UserID[%s], StatusMsg[%s], reserve1[%s], BranchID[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s], OrderMemo[%s], SessionReqSeq[%d]",
			QuoteAction->BrokerID, QuoteAction->InvestorID, QuoteAction->QuoteActionRef, QuoteAction->QuoteRef, QuoteAction->RequestID, QuoteAction->FrontID, QuoteAction->SessionID, QuoteAction->ExchangeID, QuoteAction->QuoteSysID, QuoteAction->ActionFlag, QuoteAction->ActionDate, QuoteAction->ActionTime, QuoteAction->TraderID, QuoteAction->InstallID, QuoteAction->QuoteLocalID, QuoteAction->ActionLocalID, QuoteAction->ParticipantID, QuoteAction->ClientID, QuoteAction->BusinessUnit, QuoteAction->OrderActionStatus, QuoteAction->UserID, QuoteAction->StatusMsg, QuoteAction->reserve1, QuoteAction->BranchID, QuoteAction->InvestUnitID, QuoteAction->reserve2, QuoteAction->MacAddress, QuoteAction->InstrumentID, QuoteAction->IPAddress, QuoteAction->OrderMemo, QuoteAction->SessionReqSeq);
	}
}
void WriteQryQuote(CThostFtdcQryQuoteField* QryQuote)
{
	if(QryQuote)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryQuoteField: BrokerID[%s], InvestorID[%s], reserve1[%s], ExchangeID[%s], QuoteSysID[%s], InsertTimeStart[%s], InsertTimeEnd[%s], InvestUnitID[%s], InstrumentID[%s]",
			QryQuote->BrokerID, QryQuote->InvestorID, QryQuote->reserve1, QryQuote->ExchangeID, QryQuote->QuoteSysID, QryQuote->InsertTimeStart, QryQuote->InsertTimeEnd, QryQuote->InvestUnitID, QryQuote->InstrumentID);
	}
}
void WriteExchangeQuote(CThostFtdcExchangeQuoteField* ExchangeQuote)
{
	if(ExchangeQuote)
	{
		WriteLog(LogLevel::Info, "CThostFtdcExchangeQuoteField: AskPrice[%f], BidPrice[%f], AskVolume[%d], BidVolume[%d], RequestID[%d], BusinessUnit[%s], AskOffsetFlag[%c], BidOffsetFlag[%c], AskHedgeFlag[%c], BidHedgeFlag[%c], QuoteLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve1[%s], TraderID[%s], InstallID[%d], NotifySequence[%d], OrderSubmitStatus[%c], TradingDay[%s], SettlementID[%d], QuoteSysID[%s], InsertDate[%s], InsertTime[%s], CancelTime[%s], QuoteStatus[%c], ClearingPartID[%s], SequenceNo[%d], AskOrderSysID[%s], BidOrderSysID[%s], ForQuoteSysID[%s], BranchID[%s], reserve2[%s], MacAddress[%s], ExchangeInstID[%s], IPAddress[%s], TimeCondition[%c]",
			GetDoubleValue(ExchangeQuote->AskPrice), GetDoubleValue(ExchangeQuote->BidPrice), ExchangeQuote->AskVolume, ExchangeQuote->BidVolume, ExchangeQuote->RequestID, ExchangeQuote->BusinessUnit, ExchangeQuote->AskOffsetFlag, ExchangeQuote->BidOffsetFlag, ExchangeQuote->AskHedgeFlag, ExchangeQuote->BidHedgeFlag, ExchangeQuote->QuoteLocalID, ExchangeQuote->ExchangeID, ExchangeQuote->ParticipantID, ExchangeQuote->ClientID, ExchangeQuote->reserve1, ExchangeQuote->TraderID, ExchangeQuote->InstallID, ExchangeQuote->NotifySequence, ExchangeQuote->OrderSubmitStatus, ExchangeQuote->TradingDay, ExchangeQuote->SettlementID, ExchangeQuote->QuoteSysID, ExchangeQuote->InsertDate, ExchangeQuote->InsertTime, ExchangeQuote->CancelTime, ExchangeQuote->QuoteStatus, ExchangeQuote->ClearingPartID, ExchangeQuote->SequenceNo, ExchangeQuote->AskOrderSysID, ExchangeQuote->BidOrderSysID, ExchangeQuote->ForQuoteSysID, ExchangeQuote->BranchID, ExchangeQuote->reserve2, ExchangeQuote->MacAddress, ExchangeQuote->ExchangeInstID, ExchangeQuote->IPAddress, ExchangeQuote->TimeCondition);
	}
}
void WriteQryExchangeQuote(CThostFtdcQryExchangeQuoteField* QryExchangeQuote)
{
	if(QryExchangeQuote)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryExchangeQuoteField: ParticipantID[%s], ClientID[%s], reserve1[%s], ExchangeID[%s], TraderID[%s], ExchangeInstID[%s]",
			QryExchangeQuote->ParticipantID, QryExchangeQuote->ClientID, QryExchangeQuote->reserve1, QryExchangeQuote->ExchangeID, QryExchangeQuote->TraderID, QryExchangeQuote->ExchangeInstID);
	}
}
void WriteQryQuoteAction(CThostFtdcQryQuoteActionField* QryQuoteAction)
{
	if(QryQuoteAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryQuoteActionField: BrokerID[%s], InvestorID[%s], ExchangeID[%s]",
			QryQuoteAction->BrokerID, QryQuoteAction->InvestorID, QryQuoteAction->ExchangeID);
	}
}
void WriteExchangeQuoteAction(CThostFtdcExchangeQuoteActionField* ExchangeQuoteAction)
{
	if(ExchangeQuoteAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcExchangeQuoteActionField: ExchangeID[%s], QuoteSysID[%s], ActionFlag[%c], ActionDate[%s], ActionTime[%s], TraderID[%s], InstallID[%d], QuoteLocalID[%s], ActionLocalID[%s], ParticipantID[%s], ClientID[%s], BusinessUnit[%s], OrderActionStatus[%c], UserID[%s], reserve1[%s], MacAddress[%s], IPAddress[%s]",
			ExchangeQuoteAction->ExchangeID, ExchangeQuoteAction->QuoteSysID, ExchangeQuoteAction->ActionFlag, ExchangeQuoteAction->ActionDate, ExchangeQuoteAction->ActionTime, ExchangeQuoteAction->TraderID, ExchangeQuoteAction->InstallID, ExchangeQuoteAction->QuoteLocalID, ExchangeQuoteAction->ActionLocalID, ExchangeQuoteAction->ParticipantID, ExchangeQuoteAction->ClientID, ExchangeQuoteAction->BusinessUnit, ExchangeQuoteAction->OrderActionStatus, ExchangeQuoteAction->UserID, ExchangeQuoteAction->reserve1, ExchangeQuoteAction->MacAddress, ExchangeQuoteAction->IPAddress);
	}
}
void WriteQryExchangeQuoteAction(CThostFtdcQryExchangeQuoteActionField* QryExchangeQuoteAction)
{
	if(QryExchangeQuoteAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryExchangeQuoteActionField: ParticipantID[%s], ClientID[%s], ExchangeID[%s], TraderID[%s]",
			QryExchangeQuoteAction->ParticipantID, QryExchangeQuoteAction->ClientID, QryExchangeQuoteAction->ExchangeID, QryExchangeQuoteAction->TraderID);
	}
}
void WriteOptionInstrDelta(CThostFtdcOptionInstrDeltaField* OptionInstrDelta)
{
	if(OptionInstrDelta)
	{
		WriteLog(LogLevel::Info, "CThostFtdcOptionInstrDeltaField: reserve1[%s], InvestorRange[%c], BrokerID[%s], InvestorID[%s], Delta[%f], InstrumentID[%s]",
			OptionInstrDelta->reserve1, OptionInstrDelta->InvestorRange, OptionInstrDelta->BrokerID, OptionInstrDelta->InvestorID, GetDoubleValue(OptionInstrDelta->Delta), OptionInstrDelta->InstrumentID);
	}
}
void WriteForQuoteRsp(CThostFtdcForQuoteRspField* ForQuoteRsp)
{
	if(ForQuoteRsp)
	{
		WriteLog(LogLevel::Info, "CThostFtdcForQuoteRspField: TradingDay[%s], reserve1[%s], ForQuoteSysID[%s], ForQuoteTime[%s], ActionDay[%s], ExchangeID[%s], InstrumentID[%s]",
			ForQuoteRsp->TradingDay, ForQuoteRsp->reserve1, ForQuoteRsp->ForQuoteSysID, ForQuoteRsp->ForQuoteTime, ForQuoteRsp->ActionDay, ForQuoteRsp->ExchangeID, ForQuoteRsp->InstrumentID);
	}
}
void WriteStrikeOffset(CThostFtdcStrikeOffsetField* StrikeOffset)
{
	if(StrikeOffset)
	{
		WriteLog(LogLevel::Info, "CThostFtdcStrikeOffsetField: reserve1[%s], InvestorRange[%c], BrokerID[%s], InvestorID[%s], Offset[%f], OffsetType[%c], InstrumentID[%s]",
			StrikeOffset->reserve1, StrikeOffset->InvestorRange, StrikeOffset->BrokerID, StrikeOffset->InvestorID, GetDoubleValue(StrikeOffset->Offset), StrikeOffset->OffsetType, StrikeOffset->InstrumentID);
	}
}
void WriteQryStrikeOffset(CThostFtdcQryStrikeOffsetField* QryStrikeOffset)
{
	if(QryStrikeOffset)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryStrikeOffsetField: BrokerID[%s], InvestorID[%s], reserve1[%s], InstrumentID[%s]",
			QryStrikeOffset->BrokerID, QryStrikeOffset->InvestorID, QryStrikeOffset->reserve1, QryStrikeOffset->InstrumentID);
	}
}
void WriteInputBatchOrderAction(CThostFtdcInputBatchOrderActionField* InputBatchOrderAction)
{
	if(InputBatchOrderAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInputBatchOrderActionField: BrokerID[%s], InvestorID[%s], OrderActionRef[%d], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], UserID[%s], InvestUnitID[%s], reserve1[%s], MacAddress[%s], IPAddress[%s]",
			InputBatchOrderAction->BrokerID, InputBatchOrderAction->InvestorID, InputBatchOrderAction->OrderActionRef, InputBatchOrderAction->RequestID, InputBatchOrderAction->FrontID, InputBatchOrderAction->SessionID, InputBatchOrderAction->ExchangeID, InputBatchOrderAction->UserID, InputBatchOrderAction->InvestUnitID, InputBatchOrderAction->reserve1, InputBatchOrderAction->MacAddress, InputBatchOrderAction->IPAddress);
	}
}
void WriteBatchOrderAction(CThostFtdcBatchOrderActionField* BatchOrderAction)
{
	if(BatchOrderAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcBatchOrderActionField: BrokerID[%s], InvestorID[%s], OrderActionRef[%d], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], ActionDate[%s], ActionTime[%s], TraderID[%s], InstallID[%d], ActionLocalID[%s], ParticipantID[%s], ClientID[%s], BusinessUnit[%s], OrderActionStatus[%c], UserID[%s], StatusMsg[%s], InvestUnitID[%s], reserve1[%s], MacAddress[%s], IPAddress[%s]",
			BatchOrderAction->BrokerID, BatchOrderAction->InvestorID, BatchOrderAction->OrderActionRef, BatchOrderAction->RequestID, BatchOrderAction->FrontID, BatchOrderAction->SessionID, BatchOrderAction->ExchangeID, BatchOrderAction->ActionDate, BatchOrderAction->ActionTime, BatchOrderAction->TraderID, BatchOrderAction->InstallID, BatchOrderAction->ActionLocalID, BatchOrderAction->ParticipantID, BatchOrderAction->ClientID, BatchOrderAction->BusinessUnit, BatchOrderAction->OrderActionStatus, BatchOrderAction->UserID, BatchOrderAction->StatusMsg, BatchOrderAction->InvestUnitID, BatchOrderAction->reserve1, BatchOrderAction->MacAddress, BatchOrderAction->IPAddress);
	}
}
void WriteExchangeBatchOrderAction(CThostFtdcExchangeBatchOrderActionField* ExchangeBatchOrderAction)
{
	if(ExchangeBatchOrderAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcExchangeBatchOrderActionField: ExchangeID[%s], ActionDate[%s], ActionTime[%s], TraderID[%s], InstallID[%d], ActionLocalID[%s], ParticipantID[%s], ClientID[%s], BusinessUnit[%s], OrderActionStatus[%c], UserID[%s], reserve1[%s], MacAddress[%s], IPAddress[%s]",
			ExchangeBatchOrderAction->ExchangeID, ExchangeBatchOrderAction->ActionDate, ExchangeBatchOrderAction->ActionTime, ExchangeBatchOrderAction->TraderID, ExchangeBatchOrderAction->InstallID, ExchangeBatchOrderAction->ActionLocalID, ExchangeBatchOrderAction->ParticipantID, ExchangeBatchOrderAction->ClientID, ExchangeBatchOrderAction->BusinessUnit, ExchangeBatchOrderAction->OrderActionStatus, ExchangeBatchOrderAction->UserID, ExchangeBatchOrderAction->reserve1, ExchangeBatchOrderAction->MacAddress, ExchangeBatchOrderAction->IPAddress);
	}
}
void WriteQryBatchOrderAction(CThostFtdcQryBatchOrderActionField* QryBatchOrderAction)
{
	if(QryBatchOrderAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryBatchOrderActionField: BrokerID[%s], InvestorID[%s], ExchangeID[%s]",
			QryBatchOrderAction->BrokerID, QryBatchOrderAction->InvestorID, QryBatchOrderAction->ExchangeID);
	}
}
void WriteCombInstrumentGuard(CThostFtdcCombInstrumentGuardField* CombInstrumentGuard)
{
	if(CombInstrumentGuard)
	{
		WriteLog(LogLevel::Info, "CThostFtdcCombInstrumentGuardField: BrokerID[%s], reserve1[%s], GuarantRatio[%f], ExchangeID[%s], InstrumentID[%s]",
			CombInstrumentGuard->BrokerID, CombInstrumentGuard->reserve1, GetDoubleValue(CombInstrumentGuard->GuarantRatio), CombInstrumentGuard->ExchangeID, CombInstrumentGuard->InstrumentID);
	}
}
void WriteQryCombInstrumentGuard(CThostFtdcQryCombInstrumentGuardField* QryCombInstrumentGuard)
{
	if(QryCombInstrumentGuard)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryCombInstrumentGuardField: BrokerID[%s], reserve1[%s], ExchangeID[%s], InstrumentID[%s]",
			QryCombInstrumentGuard->BrokerID, QryCombInstrumentGuard->reserve1, QryCombInstrumentGuard->ExchangeID, QryCombInstrumentGuard->InstrumentID);
	}
}
void WriteInputCombAction(CThostFtdcInputCombActionField* InputCombAction)
{
	if(InputCombAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInputCombActionField: BrokerID[%s], InvestorID[%s], reserve1[%s], CombActionRef[%s], UserID[%s], Direction[%c], Volume[%d], CombDirection[%c], HedgeFlag[%c], ExchangeID[%s], reserve2[%s], MacAddress[%s], InvestUnitID[%s], FrontID[%d], SessionID[%d], InstrumentID[%s], IPAddress[%s]",
			InputCombAction->BrokerID, InputCombAction->InvestorID, InputCombAction->reserve1, InputCombAction->CombActionRef, InputCombAction->UserID, InputCombAction->Direction, InputCombAction->Volume, InputCombAction->CombDirection, InputCombAction->HedgeFlag, InputCombAction->ExchangeID, InputCombAction->reserve2, InputCombAction->MacAddress, InputCombAction->InvestUnitID, InputCombAction->FrontID, InputCombAction->SessionID, InputCombAction->InstrumentID, InputCombAction->IPAddress);
	}
}
void WriteCombAction(CThostFtdcCombActionField* CombAction)
{
	if(CombAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcCombActionField: BrokerID[%s], InvestorID[%s], reserve1[%s], CombActionRef[%s], UserID[%s], Direction[%c], Volume[%d], CombDirection[%c], HedgeFlag[%c], ActionLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve2[%s], TraderID[%s], InstallID[%d], ActionStatus[%c], NotifySequence[%d], TradingDay[%s], SettlementID[%d], SequenceNo[%d], FrontID[%d], SessionID[%d], UserProductInfo[%s], StatusMsg[%s], reserve3[%s], MacAddress[%s], ComTradeID[%s], BranchID[%s], InvestUnitID[%s], InstrumentID[%s], ExchangeInstID[%s], IPAddress[%s]",
			CombAction->BrokerID, CombAction->InvestorID, CombAction->reserve1, CombAction->CombActionRef, CombAction->UserID, CombAction->Direction, CombAction->Volume, CombAction->CombDirection, CombAction->HedgeFlag, CombAction->ActionLocalID, CombAction->ExchangeID, CombAction->ParticipantID, CombAction->ClientID, CombAction->reserve2, CombAction->TraderID, CombAction->InstallID, CombAction->ActionStatus, CombAction->NotifySequence, CombAction->TradingDay, CombAction->SettlementID, CombAction->SequenceNo, CombAction->FrontID, CombAction->SessionID, CombAction->UserProductInfo, CombAction->StatusMsg, CombAction->reserve3, CombAction->MacAddress, CombAction->ComTradeID, CombAction->BranchID, CombAction->InvestUnitID, CombAction->InstrumentID, CombAction->ExchangeInstID, CombAction->IPAddress);
	}
}
void WriteQryCombAction(CThostFtdcQryCombActionField* QryCombAction)
{
	if(QryCombAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryCombActionField: BrokerID[%s], InvestorID[%s], reserve1[%s], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			QryCombAction->BrokerID, QryCombAction->InvestorID, QryCombAction->reserve1, QryCombAction->ExchangeID, QryCombAction->InvestUnitID, QryCombAction->InstrumentID);
	}
}
void WriteExchangeCombAction(CThostFtdcExchangeCombActionField* ExchangeCombAction)
{
	if(ExchangeCombAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcExchangeCombActionField: Direction[%c], Volume[%d], CombDirection[%c], HedgeFlag[%c], ActionLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve1[%s], TraderID[%s], InstallID[%d], ActionStatus[%c], NotifySequence[%d], TradingDay[%s], SettlementID[%d], SequenceNo[%d], reserve2[%s], MacAddress[%s], ComTradeID[%s], BranchID[%s], ExchangeInstID[%s], IPAddress[%s]",
			ExchangeCombAction->Direction, ExchangeCombAction->Volume, ExchangeCombAction->CombDirection, ExchangeCombAction->HedgeFlag, ExchangeCombAction->ActionLocalID, ExchangeCombAction->ExchangeID, ExchangeCombAction->ParticipantID, ExchangeCombAction->ClientID, ExchangeCombAction->reserve1, ExchangeCombAction->TraderID, ExchangeCombAction->InstallID, ExchangeCombAction->ActionStatus, ExchangeCombAction->NotifySequence, ExchangeCombAction->TradingDay, ExchangeCombAction->SettlementID, ExchangeCombAction->SequenceNo, ExchangeCombAction->reserve2, ExchangeCombAction->MacAddress, ExchangeCombAction->ComTradeID, ExchangeCombAction->BranchID, ExchangeCombAction->ExchangeInstID, ExchangeCombAction->IPAddress);
	}
}
void WriteQryExchangeCombAction(CThostFtdcQryExchangeCombActionField* QryExchangeCombAction)
{
	if(QryExchangeCombAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryExchangeCombActionField: ParticipantID[%s], ClientID[%s], reserve1[%s], ExchangeID[%s], TraderID[%s], ExchangeInstID[%s]",
			QryExchangeCombAction->ParticipantID, QryExchangeCombAction->ClientID, QryExchangeCombAction->reserve1, QryExchangeCombAction->ExchangeID, QryExchangeCombAction->TraderID, QryExchangeCombAction->ExchangeInstID);
	}
}
void WriteProductExchRate(CThostFtdcProductExchRateField* ProductExchRate)
{
	if(ProductExchRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcProductExchRateField: reserve1[%s], QuoteCurrencyID[%s], ExchangeRate[%f], ExchangeID[%s], ProductID[%s]",
			ProductExchRate->reserve1, ProductExchRate->QuoteCurrencyID, GetDoubleValue(ProductExchRate->ExchangeRate), ProductExchRate->ExchangeID, ProductExchRate->ProductID);
	}
}
void WriteQryProductExchRate(CThostFtdcQryProductExchRateField* QryProductExchRate)
{
	if(QryProductExchRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryProductExchRateField: reserve1[%s], ExchangeID[%s], ProductID[%s]",
			QryProductExchRate->reserve1, QryProductExchRate->ExchangeID, QryProductExchRate->ProductID);
	}
}
void WriteQryForQuoteParam(CThostFtdcQryForQuoteParamField* QryForQuoteParam)
{
	if(QryForQuoteParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryForQuoteParamField: BrokerID[%s], reserve1[%s], ExchangeID[%s], InstrumentID[%s]",
			QryForQuoteParam->BrokerID, QryForQuoteParam->reserve1, QryForQuoteParam->ExchangeID, QryForQuoteParam->InstrumentID);
	}
}
void WriteForQuoteParam(CThostFtdcForQuoteParamField* ForQuoteParam)
{
	if(ForQuoteParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcForQuoteParamField: BrokerID[%s], reserve1[%s], ExchangeID[%s], LastPrice[%f], PriceInterval[%f], InstrumentID[%s]",
			ForQuoteParam->BrokerID, ForQuoteParam->reserve1, ForQuoteParam->ExchangeID, GetDoubleValue(ForQuoteParam->LastPrice), GetDoubleValue(ForQuoteParam->PriceInterval), ForQuoteParam->InstrumentID);
	}
}
void WriteMMOptionInstrCommRate(CThostFtdcMMOptionInstrCommRateField* MMOptionInstrCommRate)
{
	if(MMOptionInstrCommRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcMMOptionInstrCommRateField: reserve1[%s], InvestorRange[%c], BrokerID[%s], InvestorID[%s], OpenRatioByMoney[%f], OpenRatioByVolume[%f], CloseRatioByMoney[%f], CloseRatioByVolume[%f], CloseTodayRatioByMoney[%f], CloseTodayRatioByVolume[%f], StrikeRatioByMoney[%f], StrikeRatioByVolume[%f], InstrumentID[%s]",
			MMOptionInstrCommRate->reserve1, MMOptionInstrCommRate->InvestorRange, MMOptionInstrCommRate->BrokerID, MMOptionInstrCommRate->InvestorID, GetDoubleValue(MMOptionInstrCommRate->OpenRatioByMoney), GetDoubleValue(MMOptionInstrCommRate->OpenRatioByVolume), GetDoubleValue(MMOptionInstrCommRate->CloseRatioByMoney), GetDoubleValue(MMOptionInstrCommRate->CloseRatioByVolume), GetDoubleValue(MMOptionInstrCommRate->CloseTodayRatioByMoney), GetDoubleValue(MMOptionInstrCommRate->CloseTodayRatioByVolume), GetDoubleValue(MMOptionInstrCommRate->StrikeRatioByMoney), GetDoubleValue(MMOptionInstrCommRate->StrikeRatioByVolume), MMOptionInstrCommRate->InstrumentID);
	}
}
void WriteQryMMOptionInstrCommRate(CThostFtdcQryMMOptionInstrCommRateField* QryMMOptionInstrCommRate)
{
	if(QryMMOptionInstrCommRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryMMOptionInstrCommRateField: BrokerID[%s], InvestorID[%s], reserve1[%s], InstrumentID[%s]",
			QryMMOptionInstrCommRate->BrokerID, QryMMOptionInstrCommRate->InvestorID, QryMMOptionInstrCommRate->reserve1, QryMMOptionInstrCommRate->InstrumentID);
	}
}
void WriteMMInstrumentCommissionRate(CThostFtdcMMInstrumentCommissionRateField* MMInstrumentCommissionRate)
{
	if(MMInstrumentCommissionRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcMMInstrumentCommissionRateField: reserve1[%s], InvestorRange[%c], BrokerID[%s], InvestorID[%s], OpenRatioByMoney[%f], OpenRatioByVolume[%f], CloseRatioByMoney[%f], CloseRatioByVolume[%f], CloseTodayRatioByMoney[%f], CloseTodayRatioByVolume[%f], InstrumentID[%s]",
			MMInstrumentCommissionRate->reserve1, MMInstrumentCommissionRate->InvestorRange, MMInstrumentCommissionRate->BrokerID, MMInstrumentCommissionRate->InvestorID, GetDoubleValue(MMInstrumentCommissionRate->OpenRatioByMoney), GetDoubleValue(MMInstrumentCommissionRate->OpenRatioByVolume), GetDoubleValue(MMInstrumentCommissionRate->CloseRatioByMoney), GetDoubleValue(MMInstrumentCommissionRate->CloseRatioByVolume), GetDoubleValue(MMInstrumentCommissionRate->CloseTodayRatioByMoney), GetDoubleValue(MMInstrumentCommissionRate->CloseTodayRatioByVolume), MMInstrumentCommissionRate->InstrumentID);
	}
}
void WriteQryMMInstrumentCommissionRate(CThostFtdcQryMMInstrumentCommissionRateField* QryMMInstrumentCommissionRate)
{
	if(QryMMInstrumentCommissionRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryMMInstrumentCommissionRateField: BrokerID[%s], InvestorID[%s], reserve1[%s], InstrumentID[%s]",
			QryMMInstrumentCommissionRate->BrokerID, QryMMInstrumentCommissionRate->InvestorID, QryMMInstrumentCommissionRate->reserve1, QryMMInstrumentCommissionRate->InstrumentID);
	}
}
void WriteInstrumentOrderCommRate(CThostFtdcInstrumentOrderCommRateField* InstrumentOrderCommRate)
{
	if(InstrumentOrderCommRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInstrumentOrderCommRateField: reserve1[%s], InvestorRange[%c], BrokerID[%s], InvestorID[%s], HedgeFlag[%c], OrderCommByVolume[%f], OrderActionCommByVolume[%f], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s], OrderCommByTrade[%f], OrderActionCommByTrade[%f]",
			InstrumentOrderCommRate->reserve1, InstrumentOrderCommRate->InvestorRange, InstrumentOrderCommRate->BrokerID, InstrumentOrderCommRate->InvestorID, InstrumentOrderCommRate->HedgeFlag, GetDoubleValue(InstrumentOrderCommRate->OrderCommByVolume), GetDoubleValue(InstrumentOrderCommRate->OrderActionCommByVolume), InstrumentOrderCommRate->ExchangeID, InstrumentOrderCommRate->InvestUnitID, InstrumentOrderCommRate->InstrumentID, GetDoubleValue(InstrumentOrderCommRate->OrderCommByTrade), GetDoubleValue(InstrumentOrderCommRate->OrderActionCommByTrade));
	}
}
void WriteQryInstrumentOrderCommRate(CThostFtdcQryInstrumentOrderCommRateField* QryInstrumentOrderCommRate)
{
	if(QryInstrumentOrderCommRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryInstrumentOrderCommRateField: BrokerID[%s], InvestorID[%s], reserve1[%s], InstrumentID[%s]",
			QryInstrumentOrderCommRate->BrokerID, QryInstrumentOrderCommRate->InvestorID, QryInstrumentOrderCommRate->reserve1, QryInstrumentOrderCommRate->InstrumentID);
	}
}
void WriteTradeParam(CThostFtdcTradeParamField* TradeParam)
{
	if(TradeParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTradeParamField: BrokerID[%s], TradeParamID[%c], TradeParamValue[%s], Memo[%s]",
			TradeParam->BrokerID, TradeParam->TradeParamID, TradeParam->TradeParamValue, TradeParam->Memo);
	}
}
void WriteInstrumentMarginRateUL(CThostFtdcInstrumentMarginRateULField* InstrumentMarginRateUL)
{
	if(InstrumentMarginRateUL)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInstrumentMarginRateULField: reserve1[%s], InvestorRange[%c], BrokerID[%s], InvestorID[%s], HedgeFlag[%c], LongMarginRatioByMoney[%f], LongMarginRatioByVolume[%f], ShortMarginRatioByMoney[%f], ShortMarginRatioByVolume[%f], InstrumentID[%s]",
			InstrumentMarginRateUL->reserve1, InstrumentMarginRateUL->InvestorRange, InstrumentMarginRateUL->BrokerID, InstrumentMarginRateUL->InvestorID, InstrumentMarginRateUL->HedgeFlag, GetDoubleValue(InstrumentMarginRateUL->LongMarginRatioByMoney), GetDoubleValue(InstrumentMarginRateUL->LongMarginRatioByVolume), GetDoubleValue(InstrumentMarginRateUL->ShortMarginRatioByMoney), GetDoubleValue(InstrumentMarginRateUL->ShortMarginRatioByVolume), InstrumentMarginRateUL->InstrumentID);
	}
}
void WriteFutureLimitPosiParam(CThostFtdcFutureLimitPosiParamField* FutureLimitPosiParam)
{
	if(FutureLimitPosiParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcFutureLimitPosiParamField: InvestorRange[%c], BrokerID[%s], InvestorID[%s], reserve1[%s], SpecOpenVolume[%d], ArbiOpenVolume[%d], OpenVolume[%d], ProductID[%s]",
			FutureLimitPosiParam->InvestorRange, FutureLimitPosiParam->BrokerID, FutureLimitPosiParam->InvestorID, FutureLimitPosiParam->reserve1, FutureLimitPosiParam->SpecOpenVolume, FutureLimitPosiParam->ArbiOpenVolume, FutureLimitPosiParam->OpenVolume, FutureLimitPosiParam->ProductID);
	}
}
void WriteLoginForbiddenIP(CThostFtdcLoginForbiddenIPField* LoginForbiddenIP)
{
	if(LoginForbiddenIP)
	{
		WriteLog(LogLevel::Info, "CThostFtdcLoginForbiddenIPField: reserve1[%s], IPAddress[%s]",
			LoginForbiddenIP->reserve1, LoginForbiddenIP->IPAddress);
	}
}
void WriteIPList(CThostFtdcIPListField* IPList)
{
	if(IPList)
	{
		WriteLog(LogLevel::Info, "CThostFtdcIPListField: reserve1[%s], IsWhite[%d], IPAddress[%s]",
			IPList->reserve1, IPList->IsWhite, IPList->IPAddress);
	}
}
void WriteInputOptionSelfClose(CThostFtdcInputOptionSelfCloseField* InputOptionSelfClose)
{
	if(InputOptionSelfClose)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInputOptionSelfCloseField: BrokerID[%s], InvestorID[%s], reserve1[%s], OptionSelfCloseRef[%s], UserID[%s], Volume[%d], RequestID[%d], BusinessUnit[%s], HedgeFlag[%c], OptSelfCloseFlag[%c], ExchangeID[%s], InvestUnitID[%s], AccountID[%s], CurrencyID[%s], ClientID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			InputOptionSelfClose->BrokerID, InputOptionSelfClose->InvestorID, InputOptionSelfClose->reserve1, InputOptionSelfClose->OptionSelfCloseRef, InputOptionSelfClose->UserID, InputOptionSelfClose->Volume, InputOptionSelfClose->RequestID, InputOptionSelfClose->BusinessUnit, InputOptionSelfClose->HedgeFlag, InputOptionSelfClose->OptSelfCloseFlag, InputOptionSelfClose->ExchangeID, InputOptionSelfClose->InvestUnitID, InputOptionSelfClose->AccountID, InputOptionSelfClose->CurrencyID, InputOptionSelfClose->ClientID, InputOptionSelfClose->reserve2, InputOptionSelfClose->MacAddress, InputOptionSelfClose->InstrumentID, InputOptionSelfClose->IPAddress);
	}
}
void WriteInputOptionSelfCloseAction(CThostFtdcInputOptionSelfCloseActionField* InputOptionSelfCloseAction)
{
	if(InputOptionSelfCloseAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInputOptionSelfCloseActionField: BrokerID[%s], InvestorID[%s], OptionSelfCloseActionRef[%d], OptionSelfCloseRef[%s], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], OptionSelfCloseSysID[%s], ActionFlag[%c], UserID[%s], reserve1[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			InputOptionSelfCloseAction->BrokerID, InputOptionSelfCloseAction->InvestorID, InputOptionSelfCloseAction->OptionSelfCloseActionRef, InputOptionSelfCloseAction->OptionSelfCloseRef, InputOptionSelfCloseAction->RequestID, InputOptionSelfCloseAction->FrontID, InputOptionSelfCloseAction->SessionID, InputOptionSelfCloseAction->ExchangeID, InputOptionSelfCloseAction->OptionSelfCloseSysID, InputOptionSelfCloseAction->ActionFlag, InputOptionSelfCloseAction->UserID, InputOptionSelfCloseAction->reserve1, InputOptionSelfCloseAction->InvestUnitID, InputOptionSelfCloseAction->reserve2, InputOptionSelfCloseAction->MacAddress, InputOptionSelfCloseAction->InstrumentID, InputOptionSelfCloseAction->IPAddress);
	}
}
void WriteOptionSelfClose(CThostFtdcOptionSelfCloseField* OptionSelfClose)
{
	if(OptionSelfClose)
	{
		WriteLog(LogLevel::Info, "CThostFtdcOptionSelfCloseField: BrokerID[%s], InvestorID[%s], reserve1[%s], OptionSelfCloseRef[%s], UserID[%s], Volume[%d], RequestID[%d], BusinessUnit[%s], HedgeFlag[%c], OptSelfCloseFlag[%c], OptionSelfCloseLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve2[%s], TraderID[%s], InstallID[%d], OrderSubmitStatus[%c], NotifySequence[%d], TradingDay[%s], SettlementID[%d], OptionSelfCloseSysID[%s], InsertDate[%s], InsertTime[%s], CancelTime[%s], ExecResult[%c], ClearingPartID[%s], SequenceNo[%d], FrontID[%d], SessionID[%d], UserProductInfo[%s], StatusMsg[%s], ActiveUserID[%s], BrokerOptionSelfCloseSeq[%d], BranchID[%s], InvestUnitID[%s], AccountID[%s], CurrencyID[%s], reserve3[%s], MacAddress[%s], InstrumentID[%s], ExchangeInstID[%s], IPAddress[%s]",
			OptionSelfClose->BrokerID, OptionSelfClose->InvestorID, OptionSelfClose->reserve1, OptionSelfClose->OptionSelfCloseRef, OptionSelfClose->UserID, OptionSelfClose->Volume, OptionSelfClose->RequestID, OptionSelfClose->BusinessUnit, OptionSelfClose->HedgeFlag, OptionSelfClose->OptSelfCloseFlag, OptionSelfClose->OptionSelfCloseLocalID, OptionSelfClose->ExchangeID, OptionSelfClose->ParticipantID, OptionSelfClose->ClientID, OptionSelfClose->reserve2, OptionSelfClose->TraderID, OptionSelfClose->InstallID, OptionSelfClose->OrderSubmitStatus, OptionSelfClose->NotifySequence, OptionSelfClose->TradingDay, OptionSelfClose->SettlementID, OptionSelfClose->OptionSelfCloseSysID, OptionSelfClose->InsertDate, OptionSelfClose->InsertTime, OptionSelfClose->CancelTime, OptionSelfClose->ExecResult, OptionSelfClose->ClearingPartID, OptionSelfClose->SequenceNo, OptionSelfClose->FrontID, OptionSelfClose->SessionID, OptionSelfClose->UserProductInfo, OptionSelfClose->StatusMsg, OptionSelfClose->ActiveUserID, OptionSelfClose->BrokerOptionSelfCloseSeq, OptionSelfClose->BranchID, OptionSelfClose->InvestUnitID, OptionSelfClose->AccountID, OptionSelfClose->CurrencyID, OptionSelfClose->reserve3, OptionSelfClose->MacAddress, OptionSelfClose->InstrumentID, OptionSelfClose->ExchangeInstID, OptionSelfClose->IPAddress);
	}
}
void WriteOptionSelfCloseAction(CThostFtdcOptionSelfCloseActionField* OptionSelfCloseAction)
{
	if(OptionSelfCloseAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcOptionSelfCloseActionField: BrokerID[%s], InvestorID[%s], OptionSelfCloseActionRef[%d], OptionSelfCloseRef[%s], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], OptionSelfCloseSysID[%s], ActionFlag[%c], ActionDate[%s], ActionTime[%s], TraderID[%s], InstallID[%d], OptionSelfCloseLocalID[%s], ActionLocalID[%s], ParticipantID[%s], ClientID[%s], BusinessUnit[%s], OrderActionStatus[%c], UserID[%s], StatusMsg[%s], reserve1[%s], BranchID[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			OptionSelfCloseAction->BrokerID, OptionSelfCloseAction->InvestorID, OptionSelfCloseAction->OptionSelfCloseActionRef, OptionSelfCloseAction->OptionSelfCloseRef, OptionSelfCloseAction->RequestID, OptionSelfCloseAction->FrontID, OptionSelfCloseAction->SessionID, OptionSelfCloseAction->ExchangeID, OptionSelfCloseAction->OptionSelfCloseSysID, OptionSelfCloseAction->ActionFlag, OptionSelfCloseAction->ActionDate, OptionSelfCloseAction->ActionTime, OptionSelfCloseAction->TraderID, OptionSelfCloseAction->InstallID, OptionSelfCloseAction->OptionSelfCloseLocalID, OptionSelfCloseAction->ActionLocalID, OptionSelfCloseAction->ParticipantID, OptionSelfCloseAction->ClientID, OptionSelfCloseAction->BusinessUnit, OptionSelfCloseAction->OrderActionStatus, OptionSelfCloseAction->UserID, OptionSelfCloseAction->StatusMsg, OptionSelfCloseAction->reserve1, OptionSelfCloseAction->BranchID, OptionSelfCloseAction->InvestUnitID, OptionSelfCloseAction->reserve2, OptionSelfCloseAction->MacAddress, OptionSelfCloseAction->InstrumentID, OptionSelfCloseAction->IPAddress);
	}
}
void WriteQryOptionSelfClose(CThostFtdcQryOptionSelfCloseField* QryOptionSelfClose)
{
	if(QryOptionSelfClose)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryOptionSelfCloseField: BrokerID[%s], InvestorID[%s], reserve1[%s], ExchangeID[%s], OptionSelfCloseSysID[%s], InsertTimeStart[%s], InsertTimeEnd[%s], InstrumentID[%s]",
			QryOptionSelfClose->BrokerID, QryOptionSelfClose->InvestorID, QryOptionSelfClose->reserve1, QryOptionSelfClose->ExchangeID, QryOptionSelfClose->OptionSelfCloseSysID, QryOptionSelfClose->InsertTimeStart, QryOptionSelfClose->InsertTimeEnd, QryOptionSelfClose->InstrumentID);
	}
}
void WriteExchangeOptionSelfClose(CThostFtdcExchangeOptionSelfCloseField* ExchangeOptionSelfClose)
{
	if(ExchangeOptionSelfClose)
	{
		WriteLog(LogLevel::Info, "CThostFtdcExchangeOptionSelfCloseField: Volume[%d], RequestID[%d], BusinessUnit[%s], HedgeFlag[%c], OptSelfCloseFlag[%c], OptionSelfCloseLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve1[%s], TraderID[%s], InstallID[%d], OrderSubmitStatus[%c], NotifySequence[%d], TradingDay[%s], SettlementID[%d], OptionSelfCloseSysID[%s], InsertDate[%s], InsertTime[%s], CancelTime[%s], ExecResult[%c], ClearingPartID[%s], SequenceNo[%d], BranchID[%s], reserve2[%s], MacAddress[%s], ExchangeInstID[%s], IPAddress[%s]",
			ExchangeOptionSelfClose->Volume, ExchangeOptionSelfClose->RequestID, ExchangeOptionSelfClose->BusinessUnit, ExchangeOptionSelfClose->HedgeFlag, ExchangeOptionSelfClose->OptSelfCloseFlag, ExchangeOptionSelfClose->OptionSelfCloseLocalID, ExchangeOptionSelfClose->ExchangeID, ExchangeOptionSelfClose->ParticipantID, ExchangeOptionSelfClose->ClientID, ExchangeOptionSelfClose->reserve1, ExchangeOptionSelfClose->TraderID, ExchangeOptionSelfClose->InstallID, ExchangeOptionSelfClose->OrderSubmitStatus, ExchangeOptionSelfClose->NotifySequence, ExchangeOptionSelfClose->TradingDay, ExchangeOptionSelfClose->SettlementID, ExchangeOptionSelfClose->OptionSelfCloseSysID, ExchangeOptionSelfClose->InsertDate, ExchangeOptionSelfClose->InsertTime, ExchangeOptionSelfClose->CancelTime, ExchangeOptionSelfClose->ExecResult, ExchangeOptionSelfClose->ClearingPartID, ExchangeOptionSelfClose->SequenceNo, ExchangeOptionSelfClose->BranchID, ExchangeOptionSelfClose->reserve2, ExchangeOptionSelfClose->MacAddress, ExchangeOptionSelfClose->ExchangeInstID, ExchangeOptionSelfClose->IPAddress);
	}
}
void WriteQryOptionSelfCloseAction(CThostFtdcQryOptionSelfCloseActionField* QryOptionSelfCloseAction)
{
	if(QryOptionSelfCloseAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryOptionSelfCloseActionField: BrokerID[%s], InvestorID[%s], ExchangeID[%s]",
			QryOptionSelfCloseAction->BrokerID, QryOptionSelfCloseAction->InvestorID, QryOptionSelfCloseAction->ExchangeID);
	}
}
void WriteExchangeOptionSelfCloseAction(CThostFtdcExchangeOptionSelfCloseActionField* ExchangeOptionSelfCloseAction)
{
	if(ExchangeOptionSelfCloseAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcExchangeOptionSelfCloseActionField: ExchangeID[%s], OptionSelfCloseSysID[%s], ActionFlag[%c], ActionDate[%s], ActionTime[%s], TraderID[%s], InstallID[%d], OptionSelfCloseLocalID[%s], ActionLocalID[%s], ParticipantID[%s], ClientID[%s], BusinessUnit[%s], OrderActionStatus[%c], UserID[%s], BranchID[%s], reserve1[%s], MacAddress[%s], reserve2[%s], OptSelfCloseFlag[%c], IPAddress[%s], ExchangeInstID[%s]",
			ExchangeOptionSelfCloseAction->ExchangeID, ExchangeOptionSelfCloseAction->OptionSelfCloseSysID, ExchangeOptionSelfCloseAction->ActionFlag, ExchangeOptionSelfCloseAction->ActionDate, ExchangeOptionSelfCloseAction->ActionTime, ExchangeOptionSelfCloseAction->TraderID, ExchangeOptionSelfCloseAction->InstallID, ExchangeOptionSelfCloseAction->OptionSelfCloseLocalID, ExchangeOptionSelfCloseAction->ActionLocalID, ExchangeOptionSelfCloseAction->ParticipantID, ExchangeOptionSelfCloseAction->ClientID, ExchangeOptionSelfCloseAction->BusinessUnit, ExchangeOptionSelfCloseAction->OrderActionStatus, ExchangeOptionSelfCloseAction->UserID, ExchangeOptionSelfCloseAction->BranchID, ExchangeOptionSelfCloseAction->reserve1, ExchangeOptionSelfCloseAction->MacAddress, ExchangeOptionSelfCloseAction->reserve2, ExchangeOptionSelfCloseAction->OptSelfCloseFlag, ExchangeOptionSelfCloseAction->IPAddress, ExchangeOptionSelfCloseAction->ExchangeInstID);
	}
}
void WriteSyncDelaySwap(CThostFtdcSyncDelaySwapField* SyncDelaySwap)
{
	if(SyncDelaySwap)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDelaySwapField: DelaySwapSeqNo[%s], BrokerID[%s], InvestorID[%s], FromCurrencyID[%s], FromAmount[%f], FromFrozenSwap[%f], FromRemainSwap[%f], ToCurrencyID[%s], ToAmount[%f], IsManualSwap[%d], IsAllRemainSetZero[%d]",
			SyncDelaySwap->DelaySwapSeqNo, SyncDelaySwap->BrokerID, SyncDelaySwap->InvestorID, SyncDelaySwap->FromCurrencyID, GetDoubleValue(SyncDelaySwap->FromAmount), GetDoubleValue(SyncDelaySwap->FromFrozenSwap), GetDoubleValue(SyncDelaySwap->FromRemainSwap), SyncDelaySwap->ToCurrencyID, GetDoubleValue(SyncDelaySwap->ToAmount), SyncDelaySwap->IsManualSwap, SyncDelaySwap->IsAllRemainSetZero);
	}
}
void WriteQrySyncDelaySwap(CThostFtdcQrySyncDelaySwapField* QrySyncDelaySwap)
{
	if(QrySyncDelaySwap)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQrySyncDelaySwapField: BrokerID[%s], DelaySwapSeqNo[%s]",
			QrySyncDelaySwap->BrokerID, QrySyncDelaySwap->DelaySwapSeqNo);
	}
}
void WriteInvestUnit(CThostFtdcInvestUnitField* InvestUnit)
{
	if(InvestUnit)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInvestUnitField: BrokerID[%s], InvestorID[%s], InvestUnitID[%s], InvestorUnitName[%s], InvestorGroupID[%s], CommModelID[%s], MarginModelID[%s], AccountID[%s], CurrencyID[%s]",
			InvestUnit->BrokerID, InvestUnit->InvestorID, InvestUnit->InvestUnitID, InvestUnit->InvestorUnitName, InvestUnit->InvestorGroupID, InvestUnit->CommModelID, InvestUnit->MarginModelID, InvestUnit->AccountID, InvestUnit->CurrencyID);
	}
}
void WriteQryInvestUnit(CThostFtdcQryInvestUnitField* QryInvestUnit)
{
	if(QryInvestUnit)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryInvestUnitField: BrokerID[%s], InvestorID[%s], InvestUnitID[%s]",
			QryInvestUnit->BrokerID, QryInvestUnit->InvestorID, QryInvestUnit->InvestUnitID);
	}
}
void WriteSecAgentCheckMode(CThostFtdcSecAgentCheckModeField* SecAgentCheckMode)
{
	if(SecAgentCheckMode)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSecAgentCheckModeField: InvestorID[%s], BrokerID[%s], CurrencyID[%s], BrokerSecAgentID[%s], CheckSelfAccount[%d]",
			SecAgentCheckMode->InvestorID, SecAgentCheckMode->BrokerID, SecAgentCheckMode->CurrencyID, SecAgentCheckMode->BrokerSecAgentID, SecAgentCheckMode->CheckSelfAccount);
	}
}
void WriteSecAgentTradeInfo(CThostFtdcSecAgentTradeInfoField* SecAgentTradeInfo)
{
	if(SecAgentTradeInfo)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSecAgentTradeInfoField: BrokerID[%s], BrokerSecAgentID[%s], InvestorID[%s], LongCustomerName[%s]",
			SecAgentTradeInfo->BrokerID, SecAgentTradeInfo->BrokerSecAgentID, SecAgentTradeInfo->InvestorID, SecAgentTradeInfo->LongCustomerName);
	}
}
void WriteMarketData(CThostFtdcMarketDataField* MarketData)
{
	if(MarketData)
	{
		WriteLog(LogLevel::Info, "CThostFtdcMarketDataField: TradingDay[%s], reserve1[%s], ExchangeID[%s], reserve2[%s], LastPrice[%f], PreSettlementPrice[%f], PreClosePrice[%f], PreOpenInterest[%f], OpenPrice[%f], HighestPrice[%f], LowestPrice[%f], Volume[%d], Turnover[%f], OpenInterest[%f], ClosePrice[%f], SettlementPrice[%f], UpperLimitPrice[%f], LowerLimitPrice[%f], PreDelta[%f], CurrDelta[%f], UpdateTime[%s], UpdateMillisec[%d], ActionDay[%s], InstrumentID[%s], ExchangeInstID[%s]",
			MarketData->TradingDay, MarketData->reserve1, MarketData->ExchangeID, MarketData->reserve2, GetDoubleValue(MarketData->LastPrice), GetDoubleValue(MarketData->PreSettlementPrice), GetDoubleValue(MarketData->PreClosePrice), GetDoubleValue(MarketData->PreOpenInterest), GetDoubleValue(MarketData->OpenPrice), GetDoubleValue(MarketData->HighestPrice), GetDoubleValue(MarketData->LowestPrice), MarketData->Volume, GetDoubleValue(MarketData->Turnover), GetDoubleValue(MarketData->OpenInterest), GetDoubleValue(MarketData->ClosePrice), GetDoubleValue(MarketData->SettlementPrice), GetDoubleValue(MarketData->UpperLimitPrice), GetDoubleValue(MarketData->LowerLimitPrice), GetDoubleValue(MarketData->PreDelta), GetDoubleValue(MarketData->CurrDelta), MarketData->UpdateTime, MarketData->UpdateMillisec, MarketData->ActionDay, MarketData->InstrumentID, MarketData->ExchangeInstID);
	}
}
void WriteMarketDataBase(CThostFtdcMarketDataBaseField* MarketDataBase)
{
	if(MarketDataBase)
	{
		WriteLog(LogLevel::Info, "CThostFtdcMarketDataBaseField: TradingDay[%s], PreSettlementPrice[%f], PreClosePrice[%f], PreOpenInterest[%f], PreDelta[%f]",
			MarketDataBase->TradingDay, GetDoubleValue(MarketDataBase->PreSettlementPrice), GetDoubleValue(MarketDataBase->PreClosePrice), GetDoubleValue(MarketDataBase->PreOpenInterest), GetDoubleValue(MarketDataBase->PreDelta));
	}
}
void WriteMarketDataStatic(CThostFtdcMarketDataStaticField* MarketDataStatic)
{
	if(MarketDataStatic)
	{
		WriteLog(LogLevel::Info, "CThostFtdcMarketDataStaticField: OpenPrice[%f], HighestPrice[%f], LowestPrice[%f], ClosePrice[%f], UpperLimitPrice[%f], LowerLimitPrice[%f], SettlementPrice[%f], CurrDelta[%f]",
			GetDoubleValue(MarketDataStatic->OpenPrice), GetDoubleValue(MarketDataStatic->HighestPrice), GetDoubleValue(MarketDataStatic->LowestPrice), GetDoubleValue(MarketDataStatic->ClosePrice), GetDoubleValue(MarketDataStatic->UpperLimitPrice), GetDoubleValue(MarketDataStatic->LowerLimitPrice), GetDoubleValue(MarketDataStatic->SettlementPrice), GetDoubleValue(MarketDataStatic->CurrDelta));
	}
}
void WriteMarketDataLastMatch(CThostFtdcMarketDataLastMatchField* MarketDataLastMatch)
{
	if(MarketDataLastMatch)
	{
		WriteLog(LogLevel::Info, "CThostFtdcMarketDataLastMatchField: LastPrice[%f], Volume[%d], Turnover[%f], OpenInterest[%f]",
			GetDoubleValue(MarketDataLastMatch->LastPrice), MarketDataLastMatch->Volume, GetDoubleValue(MarketDataLastMatch->Turnover), GetDoubleValue(MarketDataLastMatch->OpenInterest));
	}
}
void WriteMarketDataBestPrice(CThostFtdcMarketDataBestPriceField* MarketDataBestPrice)
{
	if(MarketDataBestPrice)
	{
		WriteLog(LogLevel::Info, "CThostFtdcMarketDataBestPriceField: BidPrice1[%f], BidVolume1[%d], AskPrice1[%f], AskVolume1[%d]",
			GetDoubleValue(MarketDataBestPrice->BidPrice1), MarketDataBestPrice->BidVolume1, GetDoubleValue(MarketDataBestPrice->AskPrice1), MarketDataBestPrice->AskVolume1);
	}
}
void WriteMarketDataBid23(CThostFtdcMarketDataBid23Field* MarketDataBid23)
{
	if(MarketDataBid23)
	{
		WriteLog(LogLevel::Info, "CThostFtdcMarketDataBid23Field: BidPrice2[%f], BidVolume2[%d], BidPrice3[%f], BidVolume3[%d]",
			GetDoubleValue(MarketDataBid23->BidPrice2), MarketDataBid23->BidVolume2, GetDoubleValue(MarketDataBid23->BidPrice3), MarketDataBid23->BidVolume3);
	}
}
void WriteMarketDataAsk23(CThostFtdcMarketDataAsk23Field* MarketDataAsk23)
{
	if(MarketDataAsk23)
	{
		WriteLog(LogLevel::Info, "CThostFtdcMarketDataAsk23Field: AskPrice2[%f], AskVolume2[%d], AskPrice3[%f], AskVolume3[%d]",
			GetDoubleValue(MarketDataAsk23->AskPrice2), MarketDataAsk23->AskVolume2, GetDoubleValue(MarketDataAsk23->AskPrice3), MarketDataAsk23->AskVolume3);
	}
}
void WriteMarketDataBid45(CThostFtdcMarketDataBid45Field* MarketDataBid45)
{
	if(MarketDataBid45)
	{
		WriteLog(LogLevel::Info, "CThostFtdcMarketDataBid45Field: BidPrice4[%f], BidVolume4[%d], BidPrice5[%f], BidVolume5[%d]",
			GetDoubleValue(MarketDataBid45->BidPrice4), MarketDataBid45->BidVolume4, GetDoubleValue(MarketDataBid45->BidPrice5), MarketDataBid45->BidVolume5);
	}
}
void WriteMarketDataAsk45(CThostFtdcMarketDataAsk45Field* MarketDataAsk45)
{
	if(MarketDataAsk45)
	{
		WriteLog(LogLevel::Info, "CThostFtdcMarketDataAsk45Field: AskPrice4[%f], AskVolume4[%d], AskPrice5[%f], AskVolume5[%d]",
			GetDoubleValue(MarketDataAsk45->AskPrice4), MarketDataAsk45->AskVolume4, GetDoubleValue(MarketDataAsk45->AskPrice5), MarketDataAsk45->AskVolume5);
	}
}
void WriteMarketDataUpdateTime(CThostFtdcMarketDataUpdateTimeField* MarketDataUpdateTime)
{
	if(MarketDataUpdateTime)
	{
		WriteLog(LogLevel::Info, "CThostFtdcMarketDataUpdateTimeField: reserve1[%s], UpdateTime[%s], UpdateMillisec[%d], ActionDay[%s], InstrumentID[%s]",
			MarketDataUpdateTime->reserve1, MarketDataUpdateTime->UpdateTime, MarketDataUpdateTime->UpdateMillisec, MarketDataUpdateTime->ActionDay, MarketDataUpdateTime->InstrumentID);
	}
}
void WriteMarketDataBandingPrice(CThostFtdcMarketDataBandingPriceField* MarketDataBandingPrice)
{
	if(MarketDataBandingPrice)
	{
		WriteLog(LogLevel::Info, "CThostFtdcMarketDataBandingPriceField: BandingUpperPrice[%f], BandingLowerPrice[%f]",
			GetDoubleValue(MarketDataBandingPrice->BandingUpperPrice), GetDoubleValue(MarketDataBandingPrice->BandingLowerPrice));
	}
}
void WriteMarketDataExchange(CThostFtdcMarketDataExchangeField* MarketDataExchange)
{
	if(MarketDataExchange)
	{
		WriteLog(LogLevel::Info, "CThostFtdcMarketDataExchangeField: ExchangeID[%s]",
			MarketDataExchange->ExchangeID);
	}
}
void WriteSpecificInstrument(CThostFtdcSpecificInstrumentField* SpecificInstrument)
{
	if(SpecificInstrument)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSpecificInstrumentField: reserve1[%s], InstrumentID[%s]",
			SpecificInstrument->reserve1, SpecificInstrument->InstrumentID);
	}
}
void WriteInstrumentStatus(CThostFtdcInstrumentStatusField* InstrumentStatus)
{
	if(InstrumentStatus)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInstrumentStatusField: ExchangeID[%s], reserve1[%s], SettlementGroupID[%s], reserve2[%s], InstrumentStatus[%c], TradingSegmentSN[%d], EnterTime[%s], EnterReason[%c], ExchangeInstID[%s], InstrumentID[%s]",
			InstrumentStatus->ExchangeID, InstrumentStatus->reserve1, InstrumentStatus->SettlementGroupID, InstrumentStatus->reserve2, InstrumentStatus->InstrumentStatus, InstrumentStatus->TradingSegmentSN, InstrumentStatus->EnterTime, InstrumentStatus->EnterReason, InstrumentStatus->ExchangeInstID, InstrumentStatus->InstrumentID);
	}
}
void WriteQryInstrumentStatus(CThostFtdcQryInstrumentStatusField* QryInstrumentStatus)
{
	if(QryInstrumentStatus)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryInstrumentStatusField: ExchangeID[%s], reserve1[%s], ExchangeInstID[%s]",
			QryInstrumentStatus->ExchangeID, QryInstrumentStatus->reserve1, QryInstrumentStatus->ExchangeInstID);
	}
}
void WriteInvestorAccount(CThostFtdcInvestorAccountField* InvestorAccount)
{
	if(InvestorAccount)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInvestorAccountField: BrokerID[%s], InvestorID[%s], AccountID[%s], CurrencyID[%s]",
			InvestorAccount->BrokerID, InvestorAccount->InvestorID, InvestorAccount->AccountID, InvestorAccount->CurrencyID);
	}
}
void WritePositionProfitAlgorithm(CThostFtdcPositionProfitAlgorithmField* PositionProfitAlgorithm)
{
	if(PositionProfitAlgorithm)
	{
		WriteLog(LogLevel::Info, "CThostFtdcPositionProfitAlgorithmField: BrokerID[%s], AccountID[%s], Algorithm[%c], Memo[%s], CurrencyID[%s]",
			PositionProfitAlgorithm->BrokerID, PositionProfitAlgorithm->AccountID, PositionProfitAlgorithm->Algorithm, PositionProfitAlgorithm->Memo, PositionProfitAlgorithm->CurrencyID);
	}
}
void WriteDiscount(CThostFtdcDiscountField* Discount)
{
	if(Discount)
	{
		WriteLog(LogLevel::Info, "CThostFtdcDiscountField: BrokerID[%s], InvestorRange[%c], InvestorID[%s], Discount[%f]",
			Discount->BrokerID, Discount->InvestorRange, Discount->InvestorID, GetDoubleValue(Discount->Discount));
	}
}
void WriteQryTransferBank(CThostFtdcQryTransferBankField* QryTransferBank)
{
	if(QryTransferBank)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryTransferBankField: BankID[%s], BankBrchID[%s]",
			QryTransferBank->BankID, QryTransferBank->BankBrchID);
	}
}
void WriteTransferBank(CThostFtdcTransferBankField* TransferBank)
{
	if(TransferBank)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTransferBankField: BankID[%s], BankBrchID[%s], BankName[%s], IsActive[%d]",
			TransferBank->BankID, TransferBank->BankBrchID, TransferBank->BankName, TransferBank->IsActive);
	}
}
void WriteQryInvestorPositionDetail(CThostFtdcQryInvestorPositionDetailField* QryInvestorPositionDetail)
{
	if(QryInvestorPositionDetail)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryInvestorPositionDetailField: BrokerID[%s], InvestorID[%s], reserve1[%s], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			QryInvestorPositionDetail->BrokerID, QryInvestorPositionDetail->InvestorID, QryInvestorPositionDetail->reserve1, QryInvestorPositionDetail->ExchangeID, QryInvestorPositionDetail->InvestUnitID, QryInvestorPositionDetail->InstrumentID);
	}
}
void WriteInvestorPositionDetail(CThostFtdcInvestorPositionDetailField* InvestorPositionDetail)
{
	if(InvestorPositionDetail)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInvestorPositionDetailField: reserve1[%s], BrokerID[%s], InvestorID[%s], HedgeFlag[%c], Direction[%c], OpenDate[%s], TradeID[%s], Volume[%d], OpenPrice[%f], TradingDay[%s], SettlementID[%d], TradeType[%c], reserve2[%s], ExchangeID[%s], CloseProfitByDate[%f], CloseProfitByTrade[%f], PositionProfitByDate[%f], PositionProfitByTrade[%f], Margin[%f], ExchMargin[%f], MarginRateByMoney[%f], MarginRateByVolume[%f], LastSettlementPrice[%f], SettlementPrice[%f], CloseVolume[%d], CloseAmount[%f], TimeFirstVolume[%d], InvestUnitID[%s], SpecPosiType[%c], InstrumentID[%s], CombInstrumentID[%s]",
			InvestorPositionDetail->reserve1, InvestorPositionDetail->BrokerID, InvestorPositionDetail->InvestorID, InvestorPositionDetail->HedgeFlag, InvestorPositionDetail->Direction, InvestorPositionDetail->OpenDate, InvestorPositionDetail->TradeID, InvestorPositionDetail->Volume, GetDoubleValue(InvestorPositionDetail->OpenPrice), InvestorPositionDetail->TradingDay, InvestorPositionDetail->SettlementID, InvestorPositionDetail->TradeType, InvestorPositionDetail->reserve2, InvestorPositionDetail->ExchangeID, GetDoubleValue(InvestorPositionDetail->CloseProfitByDate), GetDoubleValue(InvestorPositionDetail->CloseProfitByTrade), GetDoubleValue(InvestorPositionDetail->PositionProfitByDate), GetDoubleValue(InvestorPositionDetail->PositionProfitByTrade), GetDoubleValue(InvestorPositionDetail->Margin), GetDoubleValue(InvestorPositionDetail->ExchMargin), GetDoubleValue(InvestorPositionDetail->MarginRateByMoney), GetDoubleValue(InvestorPositionDetail->MarginRateByVolume), GetDoubleValue(InvestorPositionDetail->LastSettlementPrice), GetDoubleValue(InvestorPositionDetail->SettlementPrice), InvestorPositionDetail->CloseVolume, GetDoubleValue(InvestorPositionDetail->CloseAmount), InvestorPositionDetail->TimeFirstVolume, InvestorPositionDetail->InvestUnitID, InvestorPositionDetail->SpecPosiType, InvestorPositionDetail->InstrumentID, InvestorPositionDetail->CombInstrumentID);
	}
}
void WriteTradingAccountPassword(CThostFtdcTradingAccountPasswordField* TradingAccountPassword)
{
	if(TradingAccountPassword)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTradingAccountPasswordField: BrokerID[%s], AccountID[%s], Password[%s], CurrencyID[%s]",
			TradingAccountPassword->BrokerID, TradingAccountPassword->AccountID, TradingAccountPassword->Password, TradingAccountPassword->CurrencyID);
	}
}
void WriteMDTraderOffer(CThostFtdcMDTraderOfferField* MDTraderOffer)
{
	if(MDTraderOffer)
	{
		WriteLog(LogLevel::Info, "CThostFtdcMDTraderOfferField: ExchangeID[%s], TraderID[%s], ParticipantID[%s], Password[%s], InstallID[%d], OrderLocalID[%s], TraderConnectStatus[%c], ConnectRequestDate[%s], ConnectRequestTime[%s], LastReportDate[%s], LastReportTime[%s], ConnectDate[%s], ConnectTime[%s], StartDate[%s], StartTime[%s], TradingDay[%s], BrokerID[%s], MaxTradeID[%s], MaxOrderMessageReference[%s], OrderCancelAlg[%c]",
			MDTraderOffer->ExchangeID, MDTraderOffer->TraderID, MDTraderOffer->ParticipantID, MDTraderOffer->Password, MDTraderOffer->InstallID, MDTraderOffer->OrderLocalID, MDTraderOffer->TraderConnectStatus, MDTraderOffer->ConnectRequestDate, MDTraderOffer->ConnectRequestTime, MDTraderOffer->LastReportDate, MDTraderOffer->LastReportTime, MDTraderOffer->ConnectDate, MDTraderOffer->ConnectTime, MDTraderOffer->StartDate, MDTraderOffer->StartTime, MDTraderOffer->TradingDay, MDTraderOffer->BrokerID, MDTraderOffer->MaxTradeID, MDTraderOffer->MaxOrderMessageReference, MDTraderOffer->OrderCancelAlg);
	}
}
void WriteQryMDTraderOffer(CThostFtdcQryMDTraderOfferField* QryMDTraderOffer)
{
	if(QryMDTraderOffer)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryMDTraderOfferField: ExchangeID[%s], ParticipantID[%s], TraderID[%s]",
			QryMDTraderOffer->ExchangeID, QryMDTraderOffer->ParticipantID, QryMDTraderOffer->TraderID);
	}
}
void WriteQryNotice(CThostFtdcQryNoticeField* QryNotice)
{
	if(QryNotice)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryNoticeField: BrokerID[%s]",
			QryNotice->BrokerID);
	}
}
void WriteNotice(CThostFtdcNoticeField* Notice)
{
	if(Notice)
	{
		WriteLog(LogLevel::Info, "CThostFtdcNoticeField: BrokerID[%s], Content[%s], SequenceLabel[%s]",
			Notice->BrokerID, Notice->Content, Notice->SequenceLabel);
	}
}
void WriteUserRight(CThostFtdcUserRightField* UserRight)
{
	if(UserRight)
	{
		WriteLog(LogLevel::Info, "CThostFtdcUserRightField: BrokerID[%s], UserID[%s], UserRightType[%c], IsForbidden[%d]",
			UserRight->BrokerID, UserRight->UserID, UserRight->UserRightType, UserRight->IsForbidden);
	}
}
void WriteQrySettlementInfoConfirm(CThostFtdcQrySettlementInfoConfirmField* QrySettlementInfoConfirm)
{
	if(QrySettlementInfoConfirm)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQrySettlementInfoConfirmField: BrokerID[%s], InvestorID[%s], AccountID[%s], CurrencyID[%s]",
			QrySettlementInfoConfirm->BrokerID, QrySettlementInfoConfirm->InvestorID, QrySettlementInfoConfirm->AccountID, QrySettlementInfoConfirm->CurrencyID);
	}
}
void WriteLoadSettlementInfo(CThostFtdcLoadSettlementInfoField* LoadSettlementInfo)
{
	if(LoadSettlementInfo)
	{
		WriteLog(LogLevel::Info, "CThostFtdcLoadSettlementInfoField: BrokerID[%s]",
			LoadSettlementInfo->BrokerID);
	}
}
void WriteBrokerWithdrawAlgorithm(CThostFtdcBrokerWithdrawAlgorithmField* BrokerWithdrawAlgorithm)
{
	if(BrokerWithdrawAlgorithm)
	{
		WriteLog(LogLevel::Info, "CThostFtdcBrokerWithdrawAlgorithmField: BrokerID[%s], WithdrawAlgorithm[%c], UsingRatio[%f], IncludeCloseProfit[%c], AllWithoutTrade[%c], AvailIncludeCloseProfit[%c], IsBrokerUserEvent[%d], CurrencyID[%s], FundMortgageRatio[%f], BalanceAlgorithm[%c]",
			BrokerWithdrawAlgorithm->BrokerID, BrokerWithdrawAlgorithm->WithdrawAlgorithm, GetDoubleValue(BrokerWithdrawAlgorithm->UsingRatio), BrokerWithdrawAlgorithm->IncludeCloseProfit, BrokerWithdrawAlgorithm->AllWithoutTrade, BrokerWithdrawAlgorithm->AvailIncludeCloseProfit, BrokerWithdrawAlgorithm->IsBrokerUserEvent, BrokerWithdrawAlgorithm->CurrencyID, GetDoubleValue(BrokerWithdrawAlgorithm->FundMortgageRatio), BrokerWithdrawAlgorithm->BalanceAlgorithm);
	}
}
void WriteTradingAccountPasswordUpdateV1(CThostFtdcTradingAccountPasswordUpdateV1Field* TradingAccountPasswordUpdateV1)
{
	if(TradingAccountPasswordUpdateV1)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTradingAccountPasswordUpdateV1Field: BrokerID[%s], InvestorID[%s], OldPassword[%s], NewPassword[%s]",
			TradingAccountPasswordUpdateV1->BrokerID, TradingAccountPasswordUpdateV1->InvestorID, TradingAccountPasswordUpdateV1->OldPassword, TradingAccountPasswordUpdateV1->NewPassword);
	}
}
void WriteTradingAccountPasswordUpdate(CThostFtdcTradingAccountPasswordUpdateField* TradingAccountPasswordUpdate)
{
	if(TradingAccountPasswordUpdate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTradingAccountPasswordUpdateField: BrokerID[%s], AccountID[%s], OldPassword[%s], NewPassword[%s], CurrencyID[%s]",
			TradingAccountPasswordUpdate->BrokerID, TradingAccountPasswordUpdate->AccountID, TradingAccountPasswordUpdate->OldPassword, TradingAccountPasswordUpdate->NewPassword, TradingAccountPasswordUpdate->CurrencyID);
	}
}
void WriteQryCombinationLeg(CThostFtdcQryCombinationLegField* QryCombinationLeg)
{
	if(QryCombinationLeg)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryCombinationLegField: reserve1[%s], LegID[%d], reserve2[%s], CombInstrumentID[%s], LegInstrumentID[%s]",
			QryCombinationLeg->reserve1, QryCombinationLeg->LegID, QryCombinationLeg->reserve2, QryCombinationLeg->CombInstrumentID, QryCombinationLeg->LegInstrumentID);
	}
}
void WriteQrySyncStatus(CThostFtdcQrySyncStatusField* QrySyncStatus)
{
	if(QrySyncStatus)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQrySyncStatusField: TradingDay[%s]",
			QrySyncStatus->TradingDay);
	}
}
void WriteCombinationLeg(CThostFtdcCombinationLegField* CombinationLeg)
{
	if(CombinationLeg)
	{
		WriteLog(LogLevel::Info, "CThostFtdcCombinationLegField: reserve1[%s], LegID[%d], reserve2[%s], Direction[%c], LegMultiple[%d], ImplyLevel[%d], CombInstrumentID[%s], LegInstrumentID[%s]",
			CombinationLeg->reserve1, CombinationLeg->LegID, CombinationLeg->reserve2, CombinationLeg->Direction, CombinationLeg->LegMultiple, CombinationLeg->ImplyLevel, CombinationLeg->CombInstrumentID, CombinationLeg->LegInstrumentID);
	}
}
void WriteSyncStatus(CThostFtdcSyncStatusField* SyncStatus)
{
	if(SyncStatus)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncStatusField: TradingDay[%s], DataSyncStatus[%c]",
			SyncStatus->TradingDay, SyncStatus->DataSyncStatus);
	}
}
void WriteQryLinkMan(CThostFtdcQryLinkManField* QryLinkMan)
{
	if(QryLinkMan)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryLinkManField: BrokerID[%s], InvestorID[%s]",
			QryLinkMan->BrokerID, QryLinkMan->InvestorID);
	}
}
void WriteLinkMan(CThostFtdcLinkManField* LinkMan)
{
	if(LinkMan)
	{
		WriteLog(LogLevel::Info, "CThostFtdcLinkManField: BrokerID[%s], InvestorID[%s], PersonType[%c], IdentifiedCardType[%c], IdentifiedCardNo[%s], PersonName[%s], Telephone[%s], Address[%s], ZipCode[%s], Priority[%d], UOAZipCode[%s], PersonFullName[%s]",
			LinkMan->BrokerID, LinkMan->InvestorID, LinkMan->PersonType, LinkMan->IdentifiedCardType, LinkMan->IdentifiedCardNo, LinkMan->PersonName, LinkMan->Telephone, LinkMan->Address, LinkMan->ZipCode, LinkMan->Priority, LinkMan->UOAZipCode, LinkMan->PersonFullName);
	}
}
void WriteQryBrokerUserEvent(CThostFtdcQryBrokerUserEventField* QryBrokerUserEvent)
{
	if(QryBrokerUserEvent)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryBrokerUserEventField: BrokerID[%s], UserID[%s], UserEventType[%c]",
			QryBrokerUserEvent->BrokerID, QryBrokerUserEvent->UserID, QryBrokerUserEvent->UserEventType);
	}
}
void WriteBrokerUserEvent(CThostFtdcBrokerUserEventField* BrokerUserEvent)
{
	if(BrokerUserEvent)
	{
		WriteLog(LogLevel::Info, "CThostFtdcBrokerUserEventField: BrokerID[%s], UserID[%s], UserEventType[%c], EventSequenceNo[%d], EventDate[%s], EventTime[%s], UserEventInfo[%s], InvestorID[%s], reserve1[%s], InstrumentID[%s], DRIdentityID[%d], TradingDay[%s]",
			BrokerUserEvent->BrokerID, BrokerUserEvent->UserID, BrokerUserEvent->UserEventType, BrokerUserEvent->EventSequenceNo, BrokerUserEvent->EventDate, BrokerUserEvent->EventTime, BrokerUserEvent->UserEventInfo, BrokerUserEvent->InvestorID, BrokerUserEvent->reserve1, BrokerUserEvent->InstrumentID, BrokerUserEvent->DRIdentityID, BrokerUserEvent->TradingDay);
	}
}
void WriteQryContractBank(CThostFtdcQryContractBankField* QryContractBank)
{
	if(QryContractBank)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryContractBankField: BrokerID[%s], BankID[%s], BankBrchID[%s]",
			QryContractBank->BrokerID, QryContractBank->BankID, QryContractBank->BankBrchID);
	}
}
void WriteContractBank(CThostFtdcContractBankField* ContractBank)
{
	if(ContractBank)
	{
		WriteLog(LogLevel::Info, "CThostFtdcContractBankField: BrokerID[%s], BankID[%s], BankBrchID[%s], BankName[%s]",
			ContractBank->BrokerID, ContractBank->BankID, ContractBank->BankBrchID, ContractBank->BankName);
	}
}
void WriteInvestorPositionCombineDetail(CThostFtdcInvestorPositionCombineDetailField* InvestorPositionCombineDetail)
{
	if(InvestorPositionCombineDetail)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInvestorPositionCombineDetailField: TradingDay[%s], OpenDate[%s], ExchangeID[%s], SettlementID[%d], BrokerID[%s], InvestorID[%s], ComTradeID[%s], TradeID[%s], reserve1[%s], HedgeFlag[%c], Direction[%c], TotalAmt[%d], Margin[%f], ExchMargin[%f], MarginRateByMoney[%f], MarginRateByVolume[%f], LegID[%d], LegMultiple[%d], reserve2[%s], TradeGroupID[%d], InvestUnitID[%s], InstrumentID[%s], CombInstrumentID[%s]",
			InvestorPositionCombineDetail->TradingDay, InvestorPositionCombineDetail->OpenDate, InvestorPositionCombineDetail->ExchangeID, InvestorPositionCombineDetail->SettlementID, InvestorPositionCombineDetail->BrokerID, InvestorPositionCombineDetail->InvestorID, InvestorPositionCombineDetail->ComTradeID, InvestorPositionCombineDetail->TradeID, InvestorPositionCombineDetail->reserve1, InvestorPositionCombineDetail->HedgeFlag, InvestorPositionCombineDetail->Direction, InvestorPositionCombineDetail->TotalAmt, GetDoubleValue(InvestorPositionCombineDetail->Margin), GetDoubleValue(InvestorPositionCombineDetail->ExchMargin), GetDoubleValue(InvestorPositionCombineDetail->MarginRateByMoney), GetDoubleValue(InvestorPositionCombineDetail->MarginRateByVolume), InvestorPositionCombineDetail->LegID, InvestorPositionCombineDetail->LegMultiple, InvestorPositionCombineDetail->reserve2, InvestorPositionCombineDetail->TradeGroupID, InvestorPositionCombineDetail->InvestUnitID, InvestorPositionCombineDetail->InstrumentID, InvestorPositionCombineDetail->CombInstrumentID);
	}
}
void WriteParkedOrder(CThostFtdcParkedOrderField* ParkedOrder)
{
	if(ParkedOrder)
	{
		WriteLog(LogLevel::Info, "CThostFtdcParkedOrderField: BrokerID[%s], InvestorID[%s], reserve1[%s], OrderRef[%s], UserID[%s], OrderPriceType[%c], Direction[%c], CombOffsetFlag[%s], CombHedgeFlag[%s], LimitPrice[%f], VolumeTotalOriginal[%d], TimeCondition[%c], GTDDate[%s], VolumeCondition[%c], MinVolume[%d], ContingentCondition[%c], StopPrice[%f], ForceCloseReason[%c], IsAutoSuspend[%d], BusinessUnit[%s], RequestID[%d], UserForceClose[%d], ExchangeID[%s], ParkedOrderID[%s], UserType[%c], Status[%c], ErrorID[%d], ErrorMsg[%s], IsSwapOrder[%d], AccountID[%s], CurrencyID[%s], ClientID[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			ParkedOrder->BrokerID, ParkedOrder->InvestorID, ParkedOrder->reserve1, ParkedOrder->OrderRef, ParkedOrder->UserID, ParkedOrder->OrderPriceType, ParkedOrder->Direction, ParkedOrder->CombOffsetFlag, ParkedOrder->CombHedgeFlag, GetDoubleValue(ParkedOrder->LimitPrice), ParkedOrder->VolumeTotalOriginal, ParkedOrder->TimeCondition, ParkedOrder->GTDDate, ParkedOrder->VolumeCondition, ParkedOrder->MinVolume, ParkedOrder->ContingentCondition, GetDoubleValue(ParkedOrder->StopPrice), ParkedOrder->ForceCloseReason, ParkedOrder->IsAutoSuspend, ParkedOrder->BusinessUnit, ParkedOrder->RequestID, ParkedOrder->UserForceClose, ParkedOrder->ExchangeID, ParkedOrder->ParkedOrderID, ParkedOrder->UserType, ParkedOrder->Status, ParkedOrder->ErrorID, ParkedOrder->ErrorMsg, ParkedOrder->IsSwapOrder, ParkedOrder->AccountID, ParkedOrder->CurrencyID, ParkedOrder->ClientID, ParkedOrder->InvestUnitID, ParkedOrder->reserve2, ParkedOrder->MacAddress, ParkedOrder->InstrumentID, ParkedOrder->IPAddress);
	}
}
void WriteParkedOrderAction(CThostFtdcParkedOrderActionField* ParkedOrderAction)
{
	if(ParkedOrderAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcParkedOrderActionField: BrokerID[%s], InvestorID[%s], OrderActionRef[%d], OrderRef[%s], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], OrderSysID[%s], ActionFlag[%c], LimitPrice[%f], VolumeChange[%d], UserID[%s], reserve1[%s], ParkedOrderActionID[%s], UserType[%c], Status[%c], ErrorID[%d], ErrorMsg[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s]",
			ParkedOrderAction->BrokerID, ParkedOrderAction->InvestorID, ParkedOrderAction->OrderActionRef, ParkedOrderAction->OrderRef, ParkedOrderAction->RequestID, ParkedOrderAction->FrontID, ParkedOrderAction->SessionID, ParkedOrderAction->ExchangeID, ParkedOrderAction->OrderSysID, ParkedOrderAction->ActionFlag, GetDoubleValue(ParkedOrderAction->LimitPrice), ParkedOrderAction->VolumeChange, ParkedOrderAction->UserID, ParkedOrderAction->reserve1, ParkedOrderAction->ParkedOrderActionID, ParkedOrderAction->UserType, ParkedOrderAction->Status, ParkedOrderAction->ErrorID, ParkedOrderAction->ErrorMsg, ParkedOrderAction->InvestUnitID, ParkedOrderAction->reserve2, ParkedOrderAction->MacAddress, ParkedOrderAction->InstrumentID, ParkedOrderAction->IPAddress);
	}
}
void WriteQryParkedOrder(CThostFtdcQryParkedOrderField* QryParkedOrder)
{
	if(QryParkedOrder)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryParkedOrderField: BrokerID[%s], InvestorID[%s], reserve1[%s], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			QryParkedOrder->BrokerID, QryParkedOrder->InvestorID, QryParkedOrder->reserve1, QryParkedOrder->ExchangeID, QryParkedOrder->InvestUnitID, QryParkedOrder->InstrumentID);
	}
}
void WriteQryParkedOrderAction(CThostFtdcQryParkedOrderActionField* QryParkedOrderAction)
{
	if(QryParkedOrderAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryParkedOrderActionField: BrokerID[%s], InvestorID[%s], reserve1[%s], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			QryParkedOrderAction->BrokerID, QryParkedOrderAction->InvestorID, QryParkedOrderAction->reserve1, QryParkedOrderAction->ExchangeID, QryParkedOrderAction->InvestUnitID, QryParkedOrderAction->InstrumentID);
	}
}
void WriteRemoveParkedOrder(CThostFtdcRemoveParkedOrderField* RemoveParkedOrder)
{
	if(RemoveParkedOrder)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRemoveParkedOrderField: BrokerID[%s], InvestorID[%s], ParkedOrderID[%s], InvestUnitID[%s]",
			RemoveParkedOrder->BrokerID, RemoveParkedOrder->InvestorID, RemoveParkedOrder->ParkedOrderID, RemoveParkedOrder->InvestUnitID);
	}
}
void WriteRemoveParkedOrderAction(CThostFtdcRemoveParkedOrderActionField* RemoveParkedOrderAction)
{
	if(RemoveParkedOrderAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRemoveParkedOrderActionField: BrokerID[%s], InvestorID[%s], ParkedOrderActionID[%s], InvestUnitID[%s]",
			RemoveParkedOrderAction->BrokerID, RemoveParkedOrderAction->InvestorID, RemoveParkedOrderAction->ParkedOrderActionID, RemoveParkedOrderAction->InvestUnitID);
	}
}
void WriteInvestorWithdrawAlgorithm(CThostFtdcInvestorWithdrawAlgorithmField* InvestorWithdrawAlgorithm)
{
	if(InvestorWithdrawAlgorithm)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInvestorWithdrawAlgorithmField: BrokerID[%s], InvestorRange[%c], InvestorID[%s], UsingRatio[%f], CurrencyID[%s], FundMortgageRatio[%f]",
			InvestorWithdrawAlgorithm->BrokerID, InvestorWithdrawAlgorithm->InvestorRange, InvestorWithdrawAlgorithm->InvestorID, GetDoubleValue(InvestorWithdrawAlgorithm->UsingRatio), InvestorWithdrawAlgorithm->CurrencyID, GetDoubleValue(InvestorWithdrawAlgorithm->FundMortgageRatio));
	}
}
void WriteQryInvestorPositionCombineDetail(CThostFtdcQryInvestorPositionCombineDetailField* QryInvestorPositionCombineDetail)
{
	if(QryInvestorPositionCombineDetail)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryInvestorPositionCombineDetailField: BrokerID[%s], InvestorID[%s], reserve1[%s], ExchangeID[%s], InvestUnitID[%s], CombInstrumentID[%s]",
			QryInvestorPositionCombineDetail->BrokerID, QryInvestorPositionCombineDetail->InvestorID, QryInvestorPositionCombineDetail->reserve1, QryInvestorPositionCombineDetail->ExchangeID, QryInvestorPositionCombineDetail->InvestUnitID, QryInvestorPositionCombineDetail->CombInstrumentID);
	}
}
void WriteMarketDataAveragePrice(CThostFtdcMarketDataAveragePriceField* MarketDataAveragePrice)
{
	if(MarketDataAveragePrice)
	{
		WriteLog(LogLevel::Info, "CThostFtdcMarketDataAveragePriceField: AveragePrice[%f]",
			GetDoubleValue(MarketDataAveragePrice->AveragePrice));
	}
}
void WriteVerifyInvestorPassword(CThostFtdcVerifyInvestorPasswordField* VerifyInvestorPassword)
{
	if(VerifyInvestorPassword)
	{
		WriteLog(LogLevel::Info, "CThostFtdcVerifyInvestorPasswordField: BrokerID[%s], InvestorID[%s], Password[%s]",
			VerifyInvestorPassword->BrokerID, VerifyInvestorPassword->InvestorID, VerifyInvestorPassword->Password);
	}
}
void WriteUserIP(CThostFtdcUserIPField* UserIP)
{
	if(UserIP)
	{
		WriteLog(LogLevel::Info, "CThostFtdcUserIPField: BrokerID[%s], UserID[%s], reserve1[%s], reserve2[%s], MacAddress[%s], IPAddress[%s], IPMask[%s]",
			UserIP->BrokerID, UserIP->UserID, UserIP->reserve1, UserIP->reserve2, UserIP->MacAddress, UserIP->IPAddress, UserIP->IPMask);
	}
}
void WriteTradingNoticeInfo(CThostFtdcTradingNoticeInfoField* TradingNoticeInfo)
{
	if(TradingNoticeInfo)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTradingNoticeInfoField: BrokerID[%s], InvestorID[%s], SendTime[%s], FieldContent[%s], SequenceSeries[%d], SequenceNo[%d], InvestUnitID[%s]",
			TradingNoticeInfo->BrokerID, TradingNoticeInfo->InvestorID, TradingNoticeInfo->SendTime, TradingNoticeInfo->FieldContent, TradingNoticeInfo->SequenceSeries, TradingNoticeInfo->SequenceNo, TradingNoticeInfo->InvestUnitID);
	}
}
void WriteTradingNotice(CThostFtdcTradingNoticeField* TradingNotice)
{
	if(TradingNotice)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTradingNoticeField: BrokerID[%s], InvestorRange[%c], InvestorID[%s], SequenceSeries[%d], UserID[%s], SendTime[%s], SequenceNo[%d], FieldContent[%s], InvestUnitID[%s]",
			TradingNotice->BrokerID, TradingNotice->InvestorRange, TradingNotice->InvestorID, TradingNotice->SequenceSeries, TradingNotice->UserID, TradingNotice->SendTime, TradingNotice->SequenceNo, TradingNotice->FieldContent, TradingNotice->InvestUnitID);
	}
}
void WriteQryTradingNotice(CThostFtdcQryTradingNoticeField* QryTradingNotice)
{
	if(QryTradingNotice)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryTradingNoticeField: BrokerID[%s], InvestorID[%s], InvestUnitID[%s]",
			QryTradingNotice->BrokerID, QryTradingNotice->InvestorID, QryTradingNotice->InvestUnitID);
	}
}
void WriteQryErrOrder(CThostFtdcQryErrOrderField* QryErrOrder)
{
	if(QryErrOrder)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryErrOrderField: BrokerID[%s], InvestorID[%s]",
			QryErrOrder->BrokerID, QryErrOrder->InvestorID);
	}
}
void WriteErrOrder(CThostFtdcErrOrderField* ErrOrder)
{
	if(ErrOrder)
	{
		WriteLog(LogLevel::Info, "CThostFtdcErrOrderField: BrokerID[%s], InvestorID[%s], reserve1[%s], OrderRef[%s], UserID[%s], OrderPriceType[%c], Direction[%c], CombOffsetFlag[%s], CombHedgeFlag[%s], LimitPrice[%f], VolumeTotalOriginal[%d], TimeCondition[%c], GTDDate[%s], VolumeCondition[%c], MinVolume[%d], ContingentCondition[%c], StopPrice[%f], ForceCloseReason[%c], IsAutoSuspend[%d], BusinessUnit[%s], RequestID[%d], UserForceClose[%d], ErrorID[%d], ErrorMsg[%s], IsSwapOrder[%d], ExchangeID[%s], InvestUnitID[%s], AccountID[%s], CurrencyID[%s], ClientID[%s], reserve2[%s], MacAddress[%s], InstrumentID[%s], IPAddress[%s], OrderMemo[%s], SessionReqSeq[%d]",
			ErrOrder->BrokerID, ErrOrder->InvestorID, ErrOrder->reserve1, ErrOrder->OrderRef, ErrOrder->UserID, ErrOrder->OrderPriceType, ErrOrder->Direction, ErrOrder->CombOffsetFlag, ErrOrder->CombHedgeFlag, GetDoubleValue(ErrOrder->LimitPrice), ErrOrder->VolumeTotalOriginal, ErrOrder->TimeCondition, ErrOrder->GTDDate, ErrOrder->VolumeCondition, ErrOrder->MinVolume, ErrOrder->ContingentCondition, GetDoubleValue(ErrOrder->StopPrice), ErrOrder->ForceCloseReason, ErrOrder->IsAutoSuspend, ErrOrder->BusinessUnit, ErrOrder->RequestID, ErrOrder->UserForceClose, ErrOrder->ErrorID, ErrOrder->ErrorMsg, ErrOrder->IsSwapOrder, ErrOrder->ExchangeID, ErrOrder->InvestUnitID, ErrOrder->AccountID, ErrOrder->CurrencyID, ErrOrder->ClientID, ErrOrder->reserve2, ErrOrder->MacAddress, ErrOrder->InstrumentID, ErrOrder->IPAddress, ErrOrder->OrderMemo, ErrOrder->SessionReqSeq);
	}
}
void WriteErrorConditionalOrder(CThostFtdcErrorConditionalOrderField* ErrorConditionalOrder)
{
	if(ErrorConditionalOrder)
	{
		WriteLog(LogLevel::Info, "CThostFtdcErrorConditionalOrderField: BrokerID[%s], InvestorID[%s], reserve1[%s], OrderRef[%s], UserID[%s], OrderPriceType[%c], Direction[%c], CombOffsetFlag[%s], CombHedgeFlag[%s], LimitPrice[%f], VolumeTotalOriginal[%d], TimeCondition[%c], GTDDate[%s], VolumeCondition[%c], MinVolume[%d], ContingentCondition[%c], StopPrice[%f], ForceCloseReason[%c], IsAutoSuspend[%d], BusinessUnit[%s], RequestID[%d], OrderLocalID[%s], ExchangeID[%s], ParticipantID[%s], ClientID[%s], reserve2[%s], TraderID[%s], InstallID[%d], OrderSubmitStatus[%c], NotifySequence[%d], TradingDay[%s], SettlementID[%d], OrderSysID[%s], OrderSource[%c], OrderStatus[%c], OrderType[%c], VolumeTraded[%d], VolumeTotal[%d], InsertDate[%s], InsertTime[%s], ActiveTime[%s], SuspendTime[%s], UpdateTime[%s], CancelTime[%s], ActiveTraderID[%s], ClearingPartID[%s], SequenceNo[%d], FrontID[%d], SessionID[%d], UserProductInfo[%s], StatusMsg[%s], UserForceClose[%d], ActiveUserID[%s], BrokerOrderSeq[%d], RelativeOrderSysID[%s], ZCETotalTradedVolume[%d], ErrorID[%d], ErrorMsg[%s], IsSwapOrder[%d], BranchID[%s], InvestUnitID[%s], AccountID[%s], CurrencyID[%s], reserve3[%s], MacAddress[%s], InstrumentID[%s], ExchangeInstID[%s], IPAddress[%s]",
			ErrorConditionalOrder->BrokerID, ErrorConditionalOrder->InvestorID, ErrorConditionalOrder->reserve1, ErrorConditionalOrder->OrderRef, ErrorConditionalOrder->UserID, ErrorConditionalOrder->OrderPriceType, ErrorConditionalOrder->Direction, ErrorConditionalOrder->CombOffsetFlag, ErrorConditionalOrder->CombHedgeFlag, GetDoubleValue(ErrorConditionalOrder->LimitPrice), ErrorConditionalOrder->VolumeTotalOriginal, ErrorConditionalOrder->TimeCondition, ErrorConditionalOrder->GTDDate, ErrorConditionalOrder->VolumeCondition, ErrorConditionalOrder->MinVolume, ErrorConditionalOrder->ContingentCondition, GetDoubleValue(ErrorConditionalOrder->StopPrice), ErrorConditionalOrder->ForceCloseReason, ErrorConditionalOrder->IsAutoSuspend, ErrorConditionalOrder->BusinessUnit, ErrorConditionalOrder->RequestID, ErrorConditionalOrder->OrderLocalID, ErrorConditionalOrder->ExchangeID, ErrorConditionalOrder->ParticipantID, ErrorConditionalOrder->ClientID, ErrorConditionalOrder->reserve2, ErrorConditionalOrder->TraderID, ErrorConditionalOrder->InstallID, ErrorConditionalOrder->OrderSubmitStatus, ErrorConditionalOrder->NotifySequence, ErrorConditionalOrder->TradingDay, ErrorConditionalOrder->SettlementID, ErrorConditionalOrder->OrderSysID, ErrorConditionalOrder->OrderSource, ErrorConditionalOrder->OrderStatus, ErrorConditionalOrder->OrderType, ErrorConditionalOrder->VolumeTraded, ErrorConditionalOrder->VolumeTotal, ErrorConditionalOrder->InsertDate, ErrorConditionalOrder->InsertTime, ErrorConditionalOrder->ActiveTime, ErrorConditionalOrder->SuspendTime, ErrorConditionalOrder->UpdateTime, ErrorConditionalOrder->CancelTime, ErrorConditionalOrder->ActiveTraderID, ErrorConditionalOrder->ClearingPartID, ErrorConditionalOrder->SequenceNo, ErrorConditionalOrder->FrontID, ErrorConditionalOrder->SessionID, ErrorConditionalOrder->UserProductInfo, ErrorConditionalOrder->StatusMsg, ErrorConditionalOrder->UserForceClose, ErrorConditionalOrder->ActiveUserID, ErrorConditionalOrder->BrokerOrderSeq, ErrorConditionalOrder->RelativeOrderSysID, ErrorConditionalOrder->ZCETotalTradedVolume, ErrorConditionalOrder->ErrorID, ErrorConditionalOrder->ErrorMsg, ErrorConditionalOrder->IsSwapOrder, ErrorConditionalOrder->BranchID, ErrorConditionalOrder->InvestUnitID, ErrorConditionalOrder->AccountID, ErrorConditionalOrder->CurrencyID, ErrorConditionalOrder->reserve3, ErrorConditionalOrder->MacAddress, ErrorConditionalOrder->InstrumentID, ErrorConditionalOrder->ExchangeInstID, ErrorConditionalOrder->IPAddress);
	}
}
void WriteQryErrOrderAction(CThostFtdcQryErrOrderActionField* QryErrOrderAction)
{
	if(QryErrOrderAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryErrOrderActionField: BrokerID[%s], InvestorID[%s]",
			QryErrOrderAction->BrokerID, QryErrOrderAction->InvestorID);
	}
}
void WriteErrOrderAction(CThostFtdcErrOrderActionField* ErrOrderAction)
{
	if(ErrOrderAction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcErrOrderActionField: BrokerID[%s], InvestorID[%s], OrderActionRef[%d], OrderRef[%s], RequestID[%d], FrontID[%d], SessionID[%d], ExchangeID[%s], OrderSysID[%s], ActionFlag[%c], LimitPrice[%f], VolumeChange[%d], ActionDate[%s], ActionTime[%s], TraderID[%s], InstallID[%d], OrderLocalID[%s], ActionLocalID[%s], ParticipantID[%s], ClientID[%s], BusinessUnit[%s], OrderActionStatus[%c], UserID[%s], StatusMsg[%s], reserve1[%s], BranchID[%s], InvestUnitID[%s], reserve2[%s], MacAddress[%s], ErrorID[%d], ErrorMsg[%s], InstrumentID[%s], IPAddress[%s], OrderMemo[%s], SessionReqSeq[%d]",
			ErrOrderAction->BrokerID, ErrOrderAction->InvestorID, ErrOrderAction->OrderActionRef, ErrOrderAction->OrderRef, ErrOrderAction->RequestID, ErrOrderAction->FrontID, ErrOrderAction->SessionID, ErrOrderAction->ExchangeID, ErrOrderAction->OrderSysID, ErrOrderAction->ActionFlag, GetDoubleValue(ErrOrderAction->LimitPrice), ErrOrderAction->VolumeChange, ErrOrderAction->ActionDate, ErrOrderAction->ActionTime, ErrOrderAction->TraderID, ErrOrderAction->InstallID, ErrOrderAction->OrderLocalID, ErrOrderAction->ActionLocalID, ErrOrderAction->ParticipantID, ErrOrderAction->ClientID, ErrOrderAction->BusinessUnit, ErrOrderAction->OrderActionStatus, ErrOrderAction->UserID, ErrOrderAction->StatusMsg, ErrOrderAction->reserve1, ErrOrderAction->BranchID, ErrOrderAction->InvestUnitID, ErrOrderAction->reserve2, ErrOrderAction->MacAddress, ErrOrderAction->ErrorID, ErrOrderAction->ErrorMsg, ErrOrderAction->InstrumentID, ErrOrderAction->IPAddress, ErrOrderAction->OrderMemo, ErrOrderAction->SessionReqSeq);
	}
}
void WriteQryExchangeSequence(CThostFtdcQryExchangeSequenceField* QryExchangeSequence)
{
	if(QryExchangeSequence)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryExchangeSequenceField: ExchangeID[%s]",
			QryExchangeSequence->ExchangeID);
	}
}
void WriteExchangeSequence(CThostFtdcExchangeSequenceField* ExchangeSequence)
{
	if(ExchangeSequence)
	{
		WriteLog(LogLevel::Info, "CThostFtdcExchangeSequenceField: ExchangeID[%s], SequenceNo[%d], MarketStatus[%c]",
			ExchangeSequence->ExchangeID, ExchangeSequence->SequenceNo, ExchangeSequence->MarketStatus);
	}
}
void WriteQryMaxOrderVolumeWithPrice(CThostFtdcQryMaxOrderVolumeWithPriceField* QryMaxOrderVolumeWithPrice)
{
	if(QryMaxOrderVolumeWithPrice)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryMaxOrderVolumeWithPriceField: BrokerID[%s], InvestorID[%s], reserve1[%s], Direction[%c], OffsetFlag[%c], HedgeFlag[%c], MaxVolume[%d], Price[%f], ExchangeID[%s], InvestUnitID[%s], InstrumentID[%s]",
			QryMaxOrderVolumeWithPrice->BrokerID, QryMaxOrderVolumeWithPrice->InvestorID, QryMaxOrderVolumeWithPrice->reserve1, QryMaxOrderVolumeWithPrice->Direction, QryMaxOrderVolumeWithPrice->OffsetFlag, QryMaxOrderVolumeWithPrice->HedgeFlag, QryMaxOrderVolumeWithPrice->MaxVolume, GetDoubleValue(QryMaxOrderVolumeWithPrice->Price), QryMaxOrderVolumeWithPrice->ExchangeID, QryMaxOrderVolumeWithPrice->InvestUnitID, QryMaxOrderVolumeWithPrice->InstrumentID);
	}
}
void WriteQryBrokerTradingParams(CThostFtdcQryBrokerTradingParamsField* QryBrokerTradingParams)
{
	if(QryBrokerTradingParams)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryBrokerTradingParamsField: BrokerID[%s], InvestorID[%s], CurrencyID[%s], AccountID[%s]",
			QryBrokerTradingParams->BrokerID, QryBrokerTradingParams->InvestorID, QryBrokerTradingParams->CurrencyID, QryBrokerTradingParams->AccountID);
	}
}
void WriteBrokerTradingParams(CThostFtdcBrokerTradingParamsField* BrokerTradingParams)
{
	if(BrokerTradingParams)
	{
		WriteLog(LogLevel::Info, "CThostFtdcBrokerTradingParamsField: BrokerID[%s], InvestorID[%s], MarginPriceType[%c], Algorithm[%c], AvailIncludeCloseProfit[%c], CurrencyID[%s], OptionRoyaltyPriceType[%c], AccountID[%s]",
			BrokerTradingParams->BrokerID, BrokerTradingParams->InvestorID, BrokerTradingParams->MarginPriceType, BrokerTradingParams->Algorithm, BrokerTradingParams->AvailIncludeCloseProfit, BrokerTradingParams->CurrencyID, BrokerTradingParams->OptionRoyaltyPriceType, BrokerTradingParams->AccountID);
	}
}
void WriteQryBrokerTradingAlgos(CThostFtdcQryBrokerTradingAlgosField* QryBrokerTradingAlgos)
{
	if(QryBrokerTradingAlgos)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryBrokerTradingAlgosField: BrokerID[%s], ExchangeID[%s], reserve1[%s], InstrumentID[%s]",
			QryBrokerTradingAlgos->BrokerID, QryBrokerTradingAlgos->ExchangeID, QryBrokerTradingAlgos->reserve1, QryBrokerTradingAlgos->InstrumentID);
	}
}
void WriteBrokerTradingAlgos(CThostFtdcBrokerTradingAlgosField* BrokerTradingAlgos)
{
	if(BrokerTradingAlgos)
	{
		WriteLog(LogLevel::Info, "CThostFtdcBrokerTradingAlgosField: BrokerID[%s], ExchangeID[%s], reserve1[%s], HandlePositionAlgoID[%c], FindMarginRateAlgoID[%c], HandleTradingAccountAlgoID[%c], InstrumentID[%s]",
			BrokerTradingAlgos->BrokerID, BrokerTradingAlgos->ExchangeID, BrokerTradingAlgos->reserve1, BrokerTradingAlgos->HandlePositionAlgoID, BrokerTradingAlgos->FindMarginRateAlgoID, BrokerTradingAlgos->HandleTradingAccountAlgoID, BrokerTradingAlgos->InstrumentID);
	}
}
void WriteQueryBrokerDeposit(CThostFtdcQueryBrokerDepositField* QueryBrokerDeposit)
{
	if(QueryBrokerDeposit)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQueryBrokerDepositField: BrokerID[%s], ExchangeID[%s]",
			QueryBrokerDeposit->BrokerID, QueryBrokerDeposit->ExchangeID);
	}
}
void WriteBrokerDeposit(CThostFtdcBrokerDepositField* BrokerDeposit)
{
	if(BrokerDeposit)
	{
		WriteLog(LogLevel::Info, "CThostFtdcBrokerDepositField: TradingDay[%s], BrokerID[%s], ParticipantID[%s], ExchangeID[%s], PreBalance[%f], CurrMargin[%f], CloseProfit[%f], Balance[%f], Deposit[%f], Withdraw[%f], Available[%f], Reserve[%f], FrozenMargin[%f]",
			BrokerDeposit->TradingDay, BrokerDeposit->BrokerID, BrokerDeposit->ParticipantID, BrokerDeposit->ExchangeID, GetDoubleValue(BrokerDeposit->PreBalance), GetDoubleValue(BrokerDeposit->CurrMargin), GetDoubleValue(BrokerDeposit->CloseProfit), GetDoubleValue(BrokerDeposit->Balance), GetDoubleValue(BrokerDeposit->Deposit), GetDoubleValue(BrokerDeposit->Withdraw), GetDoubleValue(BrokerDeposit->Available), GetDoubleValue(BrokerDeposit->Reserve), GetDoubleValue(BrokerDeposit->FrozenMargin));
	}
}
void WriteQryCFMMCBrokerKey(CThostFtdcQryCFMMCBrokerKeyField* QryCFMMCBrokerKey)
{
	if(QryCFMMCBrokerKey)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryCFMMCBrokerKeyField: BrokerID[%s]",
			QryCFMMCBrokerKey->BrokerID);
	}
}
void WriteCFMMCBrokerKey(CThostFtdcCFMMCBrokerKeyField* CFMMCBrokerKey)
{
	if(CFMMCBrokerKey)
	{
		WriteLog(LogLevel::Info, "CThostFtdcCFMMCBrokerKeyField: BrokerID[%s], ParticipantID[%s], CreateDate[%s], CreateTime[%s], KeyID[%d], CurrentKey[%s], KeyKind[%c]",
			CFMMCBrokerKey->BrokerID, CFMMCBrokerKey->ParticipantID, CFMMCBrokerKey->CreateDate, CFMMCBrokerKey->CreateTime, CFMMCBrokerKey->KeyID, CFMMCBrokerKey->CurrentKey, CFMMCBrokerKey->KeyKind);
	}
}
void WriteCFMMCTradingAccountKey(CThostFtdcCFMMCTradingAccountKeyField* CFMMCTradingAccountKey)
{
	if(CFMMCTradingAccountKey)
	{
		WriteLog(LogLevel::Info, "CThostFtdcCFMMCTradingAccountKeyField: BrokerID[%s], ParticipantID[%s], AccountID[%s], KeyID[%d], CurrentKey[%s]",
			CFMMCTradingAccountKey->BrokerID, CFMMCTradingAccountKey->ParticipantID, CFMMCTradingAccountKey->AccountID, CFMMCTradingAccountKey->KeyID, CFMMCTradingAccountKey->CurrentKey);
	}
}
void WriteQryCFMMCTradingAccountKey(CThostFtdcQryCFMMCTradingAccountKeyField* QryCFMMCTradingAccountKey)
{
	if(QryCFMMCTradingAccountKey)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryCFMMCTradingAccountKeyField: BrokerID[%s], InvestorID[%s]",
			QryCFMMCTradingAccountKey->BrokerID, QryCFMMCTradingAccountKey->InvestorID);
	}
}
void WriteBrokerUserOTPParam(CThostFtdcBrokerUserOTPParamField* BrokerUserOTPParam)
{
	if(BrokerUserOTPParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcBrokerUserOTPParamField: BrokerID[%s], UserID[%s], OTPVendorsID[%s], SerialNumber[%s], AuthKey[%s], LastDrift[%d], LastSuccess[%d], OTPType[%c]",
			BrokerUserOTPParam->BrokerID, BrokerUserOTPParam->UserID, BrokerUserOTPParam->OTPVendorsID, BrokerUserOTPParam->SerialNumber, BrokerUserOTPParam->AuthKey, BrokerUserOTPParam->LastDrift, BrokerUserOTPParam->LastSuccess, BrokerUserOTPParam->OTPType);
	}
}
void WriteManualSyncBrokerUserOTP(CThostFtdcManualSyncBrokerUserOTPField* ManualSyncBrokerUserOTP)
{
	if(ManualSyncBrokerUserOTP)
	{
		WriteLog(LogLevel::Info, "CThostFtdcManualSyncBrokerUserOTPField: BrokerID[%s], UserID[%s], OTPType[%c], FirstOTP[%s], SecondOTP[%s]",
			ManualSyncBrokerUserOTP->BrokerID, ManualSyncBrokerUserOTP->UserID, ManualSyncBrokerUserOTP->OTPType, ManualSyncBrokerUserOTP->FirstOTP, ManualSyncBrokerUserOTP->SecondOTP);
	}
}
void WriteCommRateModel(CThostFtdcCommRateModelField* CommRateModel)
{
	if(CommRateModel)
	{
		WriteLog(LogLevel::Info, "CThostFtdcCommRateModelField: BrokerID[%s], CommModelID[%s], CommModelName[%s]",
			CommRateModel->BrokerID, CommRateModel->CommModelID, CommRateModel->CommModelName);
	}
}
void WriteQryCommRateModel(CThostFtdcQryCommRateModelField* QryCommRateModel)
{
	if(QryCommRateModel)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryCommRateModelField: BrokerID[%s], CommModelID[%s]",
			QryCommRateModel->BrokerID, QryCommRateModel->CommModelID);
	}
}
void WriteMarginModel(CThostFtdcMarginModelField* MarginModel)
{
	if(MarginModel)
	{
		WriteLog(LogLevel::Info, "CThostFtdcMarginModelField: BrokerID[%s], MarginModelID[%s], MarginModelName[%s]",
			MarginModel->BrokerID, MarginModel->MarginModelID, MarginModel->MarginModelName);
	}
}
void WriteQryMarginModel(CThostFtdcQryMarginModelField* QryMarginModel)
{
	if(QryMarginModel)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryMarginModelField: BrokerID[%s], MarginModelID[%s]",
			QryMarginModel->BrokerID, QryMarginModel->MarginModelID);
	}
}
void WriteEWarrantOffset(CThostFtdcEWarrantOffsetField* EWarrantOffset)
{
	if(EWarrantOffset)
	{
		WriteLog(LogLevel::Info, "CThostFtdcEWarrantOffsetField: TradingDay[%s], BrokerID[%s], InvestorID[%s], ExchangeID[%s], reserve1[%s], Direction[%c], HedgeFlag[%c], Volume[%d], InvestUnitID[%s], InstrumentID[%s]",
			EWarrantOffset->TradingDay, EWarrantOffset->BrokerID, EWarrantOffset->InvestorID, EWarrantOffset->ExchangeID, EWarrantOffset->reserve1, EWarrantOffset->Direction, EWarrantOffset->HedgeFlag, EWarrantOffset->Volume, EWarrantOffset->InvestUnitID, EWarrantOffset->InstrumentID);
	}
}
void WriteQryEWarrantOffset(CThostFtdcQryEWarrantOffsetField* QryEWarrantOffset)
{
	if(QryEWarrantOffset)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryEWarrantOffsetField: BrokerID[%s], InvestorID[%s], ExchangeID[%s], reserve1[%s], InvestUnitID[%s], InstrumentID[%s]",
			QryEWarrantOffset->BrokerID, QryEWarrantOffset->InvestorID, QryEWarrantOffset->ExchangeID, QryEWarrantOffset->reserve1, QryEWarrantOffset->InvestUnitID, QryEWarrantOffset->InstrumentID);
	}
}
void WriteQryInvestorProductGroupMargin(CThostFtdcQryInvestorProductGroupMarginField* QryInvestorProductGroupMargin)
{
	if(QryInvestorProductGroupMargin)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryInvestorProductGroupMarginField: BrokerID[%s], InvestorID[%s], reserve1[%s], HedgeFlag[%c], ExchangeID[%s], InvestUnitID[%s], ProductGroupID[%s]",
			QryInvestorProductGroupMargin->BrokerID, QryInvestorProductGroupMargin->InvestorID, QryInvestorProductGroupMargin->reserve1, QryInvestorProductGroupMargin->HedgeFlag, QryInvestorProductGroupMargin->ExchangeID, QryInvestorProductGroupMargin->InvestUnitID, QryInvestorProductGroupMargin->ProductGroupID);
	}
}
void WriteInvestorProductGroupMargin(CThostFtdcInvestorProductGroupMarginField* InvestorProductGroupMargin)
{
	if(InvestorProductGroupMargin)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInvestorProductGroupMarginField: reserve1[%s], BrokerID[%s], InvestorID[%s], TradingDay[%s], SettlementID[%d], FrozenMargin[%f], LongFrozenMargin[%f], ShortFrozenMargin[%f], UseMargin[%f], LongUseMargin[%f], ShortUseMargin[%f], ExchMargin[%f], LongExchMargin[%f], ShortExchMargin[%f], CloseProfit[%f], FrozenCommission[%f], Commission[%f], FrozenCash[%f], CashIn[%f], PositionProfit[%f], OffsetAmount[%f], LongOffsetAmount[%f], ShortOffsetAmount[%f], ExchOffsetAmount[%f], LongExchOffsetAmount[%f], ShortExchOffsetAmount[%f], HedgeFlag[%c], ExchangeID[%s], InvestUnitID[%s], ProductGroupID[%s]",
			InvestorProductGroupMargin->reserve1, InvestorProductGroupMargin->BrokerID, InvestorProductGroupMargin->InvestorID, InvestorProductGroupMargin->TradingDay, InvestorProductGroupMargin->SettlementID, GetDoubleValue(InvestorProductGroupMargin->FrozenMargin), GetDoubleValue(InvestorProductGroupMargin->LongFrozenMargin), GetDoubleValue(InvestorProductGroupMargin->ShortFrozenMargin), GetDoubleValue(InvestorProductGroupMargin->UseMargin), GetDoubleValue(InvestorProductGroupMargin->LongUseMargin), GetDoubleValue(InvestorProductGroupMargin->ShortUseMargin), GetDoubleValue(InvestorProductGroupMargin->ExchMargin), GetDoubleValue(InvestorProductGroupMargin->LongExchMargin), GetDoubleValue(InvestorProductGroupMargin->ShortExchMargin), GetDoubleValue(InvestorProductGroupMargin->CloseProfit), GetDoubleValue(InvestorProductGroupMargin->FrozenCommission), GetDoubleValue(InvestorProductGroupMargin->Commission), GetDoubleValue(InvestorProductGroupMargin->FrozenCash), GetDoubleValue(InvestorProductGroupMargin->CashIn), GetDoubleValue(InvestorProductGroupMargin->PositionProfit), GetDoubleValue(InvestorProductGroupMargin->OffsetAmount), GetDoubleValue(InvestorProductGroupMargin->LongOffsetAmount), GetDoubleValue(InvestorProductGroupMargin->ShortOffsetAmount), GetDoubleValue(InvestorProductGroupMargin->ExchOffsetAmount), GetDoubleValue(InvestorProductGroupMargin->LongExchOffsetAmount), GetDoubleValue(InvestorProductGroupMargin->ShortExchOffsetAmount), InvestorProductGroupMargin->HedgeFlag, InvestorProductGroupMargin->ExchangeID, InvestorProductGroupMargin->InvestUnitID, InvestorProductGroupMargin->ProductGroupID);
	}
}
void WriteQueryCFMMCTradingAccountToken(CThostFtdcQueryCFMMCTradingAccountTokenField* QueryCFMMCTradingAccountToken)
{
	if(QueryCFMMCTradingAccountToken)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQueryCFMMCTradingAccountTokenField: BrokerID[%s], InvestorID[%s], InvestUnitID[%s]",
			QueryCFMMCTradingAccountToken->BrokerID, QueryCFMMCTradingAccountToken->InvestorID, QueryCFMMCTradingAccountToken->InvestUnitID);
	}
}
void WriteCFMMCTradingAccountToken(CThostFtdcCFMMCTradingAccountTokenField* CFMMCTradingAccountToken)
{
	if(CFMMCTradingAccountToken)
	{
		WriteLog(LogLevel::Info, "CThostFtdcCFMMCTradingAccountTokenField: BrokerID[%s], ParticipantID[%s], AccountID[%s], KeyID[%d], Token[%s]",
			CFMMCTradingAccountToken->BrokerID, CFMMCTradingAccountToken->ParticipantID, CFMMCTradingAccountToken->AccountID, CFMMCTradingAccountToken->KeyID, CFMMCTradingAccountToken->Token);
	}
}
void WriteQryProductGroup(CThostFtdcQryProductGroupField* QryProductGroup)
{
	if(QryProductGroup)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryProductGroupField: reserve1[%s], ExchangeID[%s], ProductID[%s]",
			QryProductGroup->reserve1, QryProductGroup->ExchangeID, QryProductGroup->ProductID);
	}
}
void WriteProductGroup(CThostFtdcProductGroupField* ProductGroup)
{
	if(ProductGroup)
	{
		WriteLog(LogLevel::Info, "CThostFtdcProductGroupField: reserve1[%s], ExchangeID[%s], reserve2[%s], ProductID[%s], ProductGroupID[%s]",
			ProductGroup->reserve1, ProductGroup->ExchangeID, ProductGroup->reserve2, ProductGroup->ProductID, ProductGroup->ProductGroupID);
	}
}
void WriteBulletin(CThostFtdcBulletinField* Bulletin)
{
	if(Bulletin)
	{
		WriteLog(LogLevel::Info, "CThostFtdcBulletinField: ExchangeID[%s], TradingDay[%s], BulletinID[%d], SequenceNo[%d], NewsType[%s], NewsUrgency[%c], SendTime[%s], Abstract[%s], ComeFrom[%s], Content[%s], URLLink[%s], MarketID[%s]",
			Bulletin->ExchangeID, Bulletin->TradingDay, Bulletin->BulletinID, Bulletin->SequenceNo, Bulletin->NewsType, Bulletin->NewsUrgency, Bulletin->SendTime, Bulletin->Abstract, Bulletin->ComeFrom, Bulletin->Content, Bulletin->URLLink, Bulletin->MarketID);
	}
}
void WriteQryBulletin(CThostFtdcQryBulletinField* QryBulletin)
{
	if(QryBulletin)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryBulletinField: ExchangeID[%s], BulletinID[%d], SequenceNo[%d], NewsType[%s], NewsUrgency[%c]",
			QryBulletin->ExchangeID, QryBulletin->BulletinID, QryBulletin->SequenceNo, QryBulletin->NewsType, QryBulletin->NewsUrgency);
	}
}
void WriteMulticastInstrument(CThostFtdcMulticastInstrumentField* MulticastInstrument)
{
	if(MulticastInstrument)
	{
		WriteLog(LogLevel::Info, "CThostFtdcMulticastInstrumentField: TopicID[%d], reserve1[%s], InstrumentNo[%d], CodePrice[%f], VolumeMultiple[%d], PriceTick[%f], InstrumentID[%s]",
			MulticastInstrument->TopicID, MulticastInstrument->reserve1, MulticastInstrument->InstrumentNo, GetDoubleValue(MulticastInstrument->CodePrice), MulticastInstrument->VolumeMultiple, GetDoubleValue(MulticastInstrument->PriceTick), MulticastInstrument->InstrumentID);
	}
}
void WriteQryMulticastInstrument(CThostFtdcQryMulticastInstrumentField* QryMulticastInstrument)
{
	if(QryMulticastInstrument)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryMulticastInstrumentField: TopicID[%d], reserve1[%s], InstrumentID[%s]",
			QryMulticastInstrument->TopicID, QryMulticastInstrument->reserve1, QryMulticastInstrument->InstrumentID);
	}
}
void WriteAppIDAuthAssign(CThostFtdcAppIDAuthAssignField* AppIDAuthAssign)
{
	if(AppIDAuthAssign)
	{
		WriteLog(LogLevel::Info, "CThostFtdcAppIDAuthAssignField: BrokerID[%s], AppID[%s], DRIdentityID[%d]",
			AppIDAuthAssign->BrokerID, AppIDAuthAssign->AppID, AppIDAuthAssign->DRIdentityID);
	}
}
void WriteReqOpenAccount(CThostFtdcReqOpenAccountField* ReqOpenAccount)
{
	if(ReqOpenAccount)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReqOpenAccountField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], Gender[%c], CountryCode[%s], CustType[%c], Address[%s], ZipCode[%s], Telephone[%s], MobilePhone[%s], Fax[%s], EMail[%s], MoneyAccountStatus[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], InstallID[%d], VerifyCertNoFlag[%c], CurrencyID[%s], CashExchangeCode[%c], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], TID[%d], UserID[%s], LongCustomerName[%s]",
			ReqOpenAccount->TradeCode, ReqOpenAccount->BankID, ReqOpenAccount->BankBranchID, ReqOpenAccount->BrokerID, ReqOpenAccount->BrokerBranchID, ReqOpenAccount->TradeDate, ReqOpenAccount->TradeTime, ReqOpenAccount->BankSerial, ReqOpenAccount->TradingDay, ReqOpenAccount->PlateSerial, ReqOpenAccount->LastFragment, ReqOpenAccount->SessionID, ReqOpenAccount->CustomerName, ReqOpenAccount->IdCardType, ReqOpenAccount->IdentifiedCardNo, ReqOpenAccount->Gender, ReqOpenAccount->CountryCode, ReqOpenAccount->CustType, ReqOpenAccount->Address, ReqOpenAccount->ZipCode, ReqOpenAccount->Telephone, ReqOpenAccount->MobilePhone, ReqOpenAccount->Fax, ReqOpenAccount->EMail, ReqOpenAccount->MoneyAccountStatus, ReqOpenAccount->BankAccount, ReqOpenAccount->BankPassWord, ReqOpenAccount->AccountID, ReqOpenAccount->Password, ReqOpenAccount->InstallID, ReqOpenAccount->VerifyCertNoFlag, ReqOpenAccount->CurrencyID, ReqOpenAccount->CashExchangeCode, ReqOpenAccount->Digest, ReqOpenAccount->BankAccType, ReqOpenAccount->DeviceID, ReqOpenAccount->BankSecuAccType, ReqOpenAccount->BrokerIDByBank, ReqOpenAccount->BankSecuAcc, ReqOpenAccount->BankPwdFlag, ReqOpenAccount->SecuPwdFlag, ReqOpenAccount->OperNo, ReqOpenAccount->TID, ReqOpenAccount->UserID, ReqOpenAccount->LongCustomerName);
	}
}
void WriteReqCancelAccount(CThostFtdcReqCancelAccountField* ReqCancelAccount)
{
	if(ReqCancelAccount)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReqCancelAccountField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], Gender[%c], CountryCode[%s], CustType[%c], Address[%s], ZipCode[%s], Telephone[%s], MobilePhone[%s], Fax[%s], EMail[%s], MoneyAccountStatus[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], InstallID[%d], VerifyCertNoFlag[%c], CurrencyID[%s], CashExchangeCode[%c], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], TID[%d], UserID[%s], LongCustomerName[%s]",
			ReqCancelAccount->TradeCode, ReqCancelAccount->BankID, ReqCancelAccount->BankBranchID, ReqCancelAccount->BrokerID, ReqCancelAccount->BrokerBranchID, ReqCancelAccount->TradeDate, ReqCancelAccount->TradeTime, ReqCancelAccount->BankSerial, ReqCancelAccount->TradingDay, ReqCancelAccount->PlateSerial, ReqCancelAccount->LastFragment, ReqCancelAccount->SessionID, ReqCancelAccount->CustomerName, ReqCancelAccount->IdCardType, ReqCancelAccount->IdentifiedCardNo, ReqCancelAccount->Gender, ReqCancelAccount->CountryCode, ReqCancelAccount->CustType, ReqCancelAccount->Address, ReqCancelAccount->ZipCode, ReqCancelAccount->Telephone, ReqCancelAccount->MobilePhone, ReqCancelAccount->Fax, ReqCancelAccount->EMail, ReqCancelAccount->MoneyAccountStatus, ReqCancelAccount->BankAccount, ReqCancelAccount->BankPassWord, ReqCancelAccount->AccountID, ReqCancelAccount->Password, ReqCancelAccount->InstallID, ReqCancelAccount->VerifyCertNoFlag, ReqCancelAccount->CurrencyID, ReqCancelAccount->CashExchangeCode, ReqCancelAccount->Digest, ReqCancelAccount->BankAccType, ReqCancelAccount->DeviceID, ReqCancelAccount->BankSecuAccType, ReqCancelAccount->BrokerIDByBank, ReqCancelAccount->BankSecuAcc, ReqCancelAccount->BankPwdFlag, ReqCancelAccount->SecuPwdFlag, ReqCancelAccount->OperNo, ReqCancelAccount->TID, ReqCancelAccount->UserID, ReqCancelAccount->LongCustomerName);
	}
}
void WriteReqChangeAccount(CThostFtdcReqChangeAccountField* ReqChangeAccount)
{
	if(ReqChangeAccount)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReqChangeAccountField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], Gender[%c], CountryCode[%s], CustType[%c], Address[%s], ZipCode[%s], Telephone[%s], MobilePhone[%s], Fax[%s], EMail[%s], MoneyAccountStatus[%c], BankAccount[%s], BankPassWord[%s], NewBankAccount[%s], NewBankPassWord[%s], AccountID[%s], Password[%s], BankAccType[%c], InstallID[%d], VerifyCertNoFlag[%c], CurrencyID[%s], BrokerIDByBank[%s], BankPwdFlag[%c], SecuPwdFlag[%c], TID[%d], Digest[%s], LongCustomerName[%s]",
			ReqChangeAccount->TradeCode, ReqChangeAccount->BankID, ReqChangeAccount->BankBranchID, ReqChangeAccount->BrokerID, ReqChangeAccount->BrokerBranchID, ReqChangeAccount->TradeDate, ReqChangeAccount->TradeTime, ReqChangeAccount->BankSerial, ReqChangeAccount->TradingDay, ReqChangeAccount->PlateSerial, ReqChangeAccount->LastFragment, ReqChangeAccount->SessionID, ReqChangeAccount->CustomerName, ReqChangeAccount->IdCardType, ReqChangeAccount->IdentifiedCardNo, ReqChangeAccount->Gender, ReqChangeAccount->CountryCode, ReqChangeAccount->CustType, ReqChangeAccount->Address, ReqChangeAccount->ZipCode, ReqChangeAccount->Telephone, ReqChangeAccount->MobilePhone, ReqChangeAccount->Fax, ReqChangeAccount->EMail, ReqChangeAccount->MoneyAccountStatus, ReqChangeAccount->BankAccount, ReqChangeAccount->BankPassWord, ReqChangeAccount->NewBankAccount, ReqChangeAccount->NewBankPassWord, ReqChangeAccount->AccountID, ReqChangeAccount->Password, ReqChangeAccount->BankAccType, ReqChangeAccount->InstallID, ReqChangeAccount->VerifyCertNoFlag, ReqChangeAccount->CurrencyID, ReqChangeAccount->BrokerIDByBank, ReqChangeAccount->BankPwdFlag, ReqChangeAccount->SecuPwdFlag, ReqChangeAccount->TID, ReqChangeAccount->Digest, ReqChangeAccount->LongCustomerName);
	}
}
void WriteReqTransfer(CThostFtdcReqTransferField* ReqTransfer)
{
	if(ReqTransfer)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReqTransferField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], InstallID[%d], FutureSerial[%d], UserID[%s], VerifyCertNoFlag[%c], CurrencyID[%s], TradeAmount[%f], FutureFetchAmount[%f], FeePayFlag[%c], CustFee[%f], BrokerFee[%f], Message[%s], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], RequestID[%d], TID[%d], TransferStatus[%c], LongCustomerName[%s]",
			ReqTransfer->TradeCode, ReqTransfer->BankID, ReqTransfer->BankBranchID, ReqTransfer->BrokerID, ReqTransfer->BrokerBranchID, ReqTransfer->TradeDate, ReqTransfer->TradeTime, ReqTransfer->BankSerial, ReqTransfer->TradingDay, ReqTransfer->PlateSerial, ReqTransfer->LastFragment, ReqTransfer->SessionID, ReqTransfer->CustomerName, ReqTransfer->IdCardType, ReqTransfer->IdentifiedCardNo, ReqTransfer->CustType, ReqTransfer->BankAccount, ReqTransfer->BankPassWord, ReqTransfer->AccountID, ReqTransfer->Password, ReqTransfer->InstallID, ReqTransfer->FutureSerial, ReqTransfer->UserID, ReqTransfer->VerifyCertNoFlag, ReqTransfer->CurrencyID, GetDoubleValue(ReqTransfer->TradeAmount), GetDoubleValue(ReqTransfer->FutureFetchAmount), ReqTransfer->FeePayFlag, GetDoubleValue(ReqTransfer->CustFee), GetDoubleValue(ReqTransfer->BrokerFee), ReqTransfer->Message, ReqTransfer->Digest, ReqTransfer->BankAccType, ReqTransfer->DeviceID, ReqTransfer->BankSecuAccType, ReqTransfer->BrokerIDByBank, ReqTransfer->BankSecuAcc, ReqTransfer->BankPwdFlag, ReqTransfer->SecuPwdFlag, ReqTransfer->OperNo, ReqTransfer->RequestID, ReqTransfer->TID, ReqTransfer->TransferStatus, ReqTransfer->LongCustomerName);
	}
}
void WriteRspTransfer(CThostFtdcRspTransferField* RspTransfer)
{
	if(RspTransfer)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRspTransferField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], InstallID[%d], FutureSerial[%d], UserID[%s], VerifyCertNoFlag[%c], CurrencyID[%s], TradeAmount[%f], FutureFetchAmount[%f], FeePayFlag[%c], CustFee[%f], BrokerFee[%f], Message[%s], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], RequestID[%d], TID[%d], TransferStatus[%c], ErrorID[%d], ErrorMsg[%s], LongCustomerName[%s]",
			RspTransfer->TradeCode, RspTransfer->BankID, RspTransfer->BankBranchID, RspTransfer->BrokerID, RspTransfer->BrokerBranchID, RspTransfer->TradeDate, RspTransfer->TradeTime, RspTransfer->BankSerial, RspTransfer->TradingDay, RspTransfer->PlateSerial, RspTransfer->LastFragment, RspTransfer->SessionID, RspTransfer->CustomerName, RspTransfer->IdCardType, RspTransfer->IdentifiedCardNo, RspTransfer->CustType, RspTransfer->BankAccount, RspTransfer->BankPassWord, RspTransfer->AccountID, RspTransfer->Password, RspTransfer->InstallID, RspTransfer->FutureSerial, RspTransfer->UserID, RspTransfer->VerifyCertNoFlag, RspTransfer->CurrencyID, GetDoubleValue(RspTransfer->TradeAmount), GetDoubleValue(RspTransfer->FutureFetchAmount), RspTransfer->FeePayFlag, GetDoubleValue(RspTransfer->CustFee), GetDoubleValue(RspTransfer->BrokerFee), RspTransfer->Message, RspTransfer->Digest, RspTransfer->BankAccType, RspTransfer->DeviceID, RspTransfer->BankSecuAccType, RspTransfer->BrokerIDByBank, RspTransfer->BankSecuAcc, RspTransfer->BankPwdFlag, RspTransfer->SecuPwdFlag, RspTransfer->OperNo, RspTransfer->RequestID, RspTransfer->TID, RspTransfer->TransferStatus, RspTransfer->ErrorID, RspTransfer->ErrorMsg, RspTransfer->LongCustomerName);
	}
}
void WriteReqRepeal(CThostFtdcReqRepealField* ReqRepeal)
{
	if(ReqRepeal)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReqRepealField: RepealTimeInterval[%d], RepealedTimes[%d], BankRepealFlag[%c], BrokerRepealFlag[%c], PlateRepealSerial[%d], BankRepealSerial[%s], FutureRepealSerial[%d], TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], InstallID[%d], FutureSerial[%d], UserID[%s], VerifyCertNoFlag[%c], CurrencyID[%s], TradeAmount[%f], FutureFetchAmount[%f], FeePayFlag[%c], CustFee[%f], BrokerFee[%f], Message[%s], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], RequestID[%d], TID[%d], TransferStatus[%c], LongCustomerName[%s]",
			ReqRepeal->RepealTimeInterval, ReqRepeal->RepealedTimes, ReqRepeal->BankRepealFlag, ReqRepeal->BrokerRepealFlag, ReqRepeal->PlateRepealSerial, ReqRepeal->BankRepealSerial, ReqRepeal->FutureRepealSerial, ReqRepeal->TradeCode, ReqRepeal->BankID, ReqRepeal->BankBranchID, ReqRepeal->BrokerID, ReqRepeal->BrokerBranchID, ReqRepeal->TradeDate, ReqRepeal->TradeTime, ReqRepeal->BankSerial, ReqRepeal->TradingDay, ReqRepeal->PlateSerial, ReqRepeal->LastFragment, ReqRepeal->SessionID, ReqRepeal->CustomerName, ReqRepeal->IdCardType, ReqRepeal->IdentifiedCardNo, ReqRepeal->CustType, ReqRepeal->BankAccount, ReqRepeal->BankPassWord, ReqRepeal->AccountID, ReqRepeal->Password, ReqRepeal->InstallID, ReqRepeal->FutureSerial, ReqRepeal->UserID, ReqRepeal->VerifyCertNoFlag, ReqRepeal->CurrencyID, GetDoubleValue(ReqRepeal->TradeAmount), GetDoubleValue(ReqRepeal->FutureFetchAmount), ReqRepeal->FeePayFlag, GetDoubleValue(ReqRepeal->CustFee), GetDoubleValue(ReqRepeal->BrokerFee), ReqRepeal->Message, ReqRepeal->Digest, ReqRepeal->BankAccType, ReqRepeal->DeviceID, ReqRepeal->BankSecuAccType, ReqRepeal->BrokerIDByBank, ReqRepeal->BankSecuAcc, ReqRepeal->BankPwdFlag, ReqRepeal->SecuPwdFlag, ReqRepeal->OperNo, ReqRepeal->RequestID, ReqRepeal->TID, ReqRepeal->TransferStatus, ReqRepeal->LongCustomerName);
	}
}
void WriteRspRepeal(CThostFtdcRspRepealField* RspRepeal)
{
	if(RspRepeal)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRspRepealField: RepealTimeInterval[%d], RepealedTimes[%d], BankRepealFlag[%c], BrokerRepealFlag[%c], PlateRepealSerial[%d], BankRepealSerial[%s], FutureRepealSerial[%d], TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], InstallID[%d], FutureSerial[%d], UserID[%s], VerifyCertNoFlag[%c], CurrencyID[%s], TradeAmount[%f], FutureFetchAmount[%f], FeePayFlag[%c], CustFee[%f], BrokerFee[%f], Message[%s], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], RequestID[%d], TID[%d], TransferStatus[%c], ErrorID[%d], ErrorMsg[%s], LongCustomerName[%s]",
			RspRepeal->RepealTimeInterval, RspRepeal->RepealedTimes, RspRepeal->BankRepealFlag, RspRepeal->BrokerRepealFlag, RspRepeal->PlateRepealSerial, RspRepeal->BankRepealSerial, RspRepeal->FutureRepealSerial, RspRepeal->TradeCode, RspRepeal->BankID, RspRepeal->BankBranchID, RspRepeal->BrokerID, RspRepeal->BrokerBranchID, RspRepeal->TradeDate, RspRepeal->TradeTime, RspRepeal->BankSerial, RspRepeal->TradingDay, RspRepeal->PlateSerial, RspRepeal->LastFragment, RspRepeal->SessionID, RspRepeal->CustomerName, RspRepeal->IdCardType, RspRepeal->IdentifiedCardNo, RspRepeal->CustType, RspRepeal->BankAccount, RspRepeal->BankPassWord, RspRepeal->AccountID, RspRepeal->Password, RspRepeal->InstallID, RspRepeal->FutureSerial, RspRepeal->UserID, RspRepeal->VerifyCertNoFlag, RspRepeal->CurrencyID, GetDoubleValue(RspRepeal->TradeAmount), GetDoubleValue(RspRepeal->FutureFetchAmount), RspRepeal->FeePayFlag, GetDoubleValue(RspRepeal->CustFee), GetDoubleValue(RspRepeal->BrokerFee), RspRepeal->Message, RspRepeal->Digest, RspRepeal->BankAccType, RspRepeal->DeviceID, RspRepeal->BankSecuAccType, RspRepeal->BrokerIDByBank, RspRepeal->BankSecuAcc, RspRepeal->BankPwdFlag, RspRepeal->SecuPwdFlag, RspRepeal->OperNo, RspRepeal->RequestID, RspRepeal->TID, RspRepeal->TransferStatus, RspRepeal->ErrorID, RspRepeal->ErrorMsg, RspRepeal->LongCustomerName);
	}
}
void WriteReqQueryAccount(CThostFtdcReqQueryAccountField* ReqQueryAccount)
{
	if(ReqQueryAccount)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReqQueryAccountField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], FutureSerial[%d], InstallID[%d], UserID[%s], VerifyCertNoFlag[%c], CurrencyID[%s], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], RequestID[%d], TID[%d], LongCustomerName[%s]",
			ReqQueryAccount->TradeCode, ReqQueryAccount->BankID, ReqQueryAccount->BankBranchID, ReqQueryAccount->BrokerID, ReqQueryAccount->BrokerBranchID, ReqQueryAccount->TradeDate, ReqQueryAccount->TradeTime, ReqQueryAccount->BankSerial, ReqQueryAccount->TradingDay, ReqQueryAccount->PlateSerial, ReqQueryAccount->LastFragment, ReqQueryAccount->SessionID, ReqQueryAccount->CustomerName, ReqQueryAccount->IdCardType, ReqQueryAccount->IdentifiedCardNo, ReqQueryAccount->CustType, ReqQueryAccount->BankAccount, ReqQueryAccount->BankPassWord, ReqQueryAccount->AccountID, ReqQueryAccount->Password, ReqQueryAccount->FutureSerial, ReqQueryAccount->InstallID, ReqQueryAccount->UserID, ReqQueryAccount->VerifyCertNoFlag, ReqQueryAccount->CurrencyID, ReqQueryAccount->Digest, ReqQueryAccount->BankAccType, ReqQueryAccount->DeviceID, ReqQueryAccount->BankSecuAccType, ReqQueryAccount->BrokerIDByBank, ReqQueryAccount->BankSecuAcc, ReqQueryAccount->BankPwdFlag, ReqQueryAccount->SecuPwdFlag, ReqQueryAccount->OperNo, ReqQueryAccount->RequestID, ReqQueryAccount->TID, ReqQueryAccount->LongCustomerName);
	}
}
void WriteRspQueryAccount(CThostFtdcRspQueryAccountField* RspQueryAccount)
{
	if(RspQueryAccount)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRspQueryAccountField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], FutureSerial[%d], InstallID[%d], UserID[%s], VerifyCertNoFlag[%c], CurrencyID[%s], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], RequestID[%d], TID[%d], BankUseAmount[%f], BankFetchAmount[%f], LongCustomerName[%s]",
			RspQueryAccount->TradeCode, RspQueryAccount->BankID, RspQueryAccount->BankBranchID, RspQueryAccount->BrokerID, RspQueryAccount->BrokerBranchID, RspQueryAccount->TradeDate, RspQueryAccount->TradeTime, RspQueryAccount->BankSerial, RspQueryAccount->TradingDay, RspQueryAccount->PlateSerial, RspQueryAccount->LastFragment, RspQueryAccount->SessionID, RspQueryAccount->CustomerName, RspQueryAccount->IdCardType, RspQueryAccount->IdentifiedCardNo, RspQueryAccount->CustType, RspQueryAccount->BankAccount, RspQueryAccount->BankPassWord, RspQueryAccount->AccountID, RspQueryAccount->Password, RspQueryAccount->FutureSerial, RspQueryAccount->InstallID, RspQueryAccount->UserID, RspQueryAccount->VerifyCertNoFlag, RspQueryAccount->CurrencyID, RspQueryAccount->Digest, RspQueryAccount->BankAccType, RspQueryAccount->DeviceID, RspQueryAccount->BankSecuAccType, RspQueryAccount->BrokerIDByBank, RspQueryAccount->BankSecuAcc, RspQueryAccount->BankPwdFlag, RspQueryAccount->SecuPwdFlag, RspQueryAccount->OperNo, RspQueryAccount->RequestID, RspQueryAccount->TID, GetDoubleValue(RspQueryAccount->BankUseAmount), GetDoubleValue(RspQueryAccount->BankFetchAmount), RspQueryAccount->LongCustomerName);
	}
}
void WriteFutureSignIO(CThostFtdcFutureSignIOField* FutureSignIO)
{
	if(FutureSignIO)
	{
		WriteLog(LogLevel::Info, "CThostFtdcFutureSignIOField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], InstallID[%d], UserID[%s], Digest[%s], CurrencyID[%s], DeviceID[%s], BrokerIDByBank[%s], OperNo[%s], RequestID[%d], TID[%d]",
			FutureSignIO->TradeCode, FutureSignIO->BankID, FutureSignIO->BankBranchID, FutureSignIO->BrokerID, FutureSignIO->BrokerBranchID, FutureSignIO->TradeDate, FutureSignIO->TradeTime, FutureSignIO->BankSerial, FutureSignIO->TradingDay, FutureSignIO->PlateSerial, FutureSignIO->LastFragment, FutureSignIO->SessionID, FutureSignIO->InstallID, FutureSignIO->UserID, FutureSignIO->Digest, FutureSignIO->CurrencyID, FutureSignIO->DeviceID, FutureSignIO->BrokerIDByBank, FutureSignIO->OperNo, FutureSignIO->RequestID, FutureSignIO->TID);
	}
}
void WriteRspFutureSignIn(CThostFtdcRspFutureSignInField* RspFutureSignIn)
{
	if(RspFutureSignIn)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRspFutureSignInField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], InstallID[%d], UserID[%s], Digest[%s], CurrencyID[%s], DeviceID[%s], BrokerIDByBank[%s], OperNo[%s], RequestID[%d], TID[%d], ErrorID[%d], ErrorMsg[%s], PinKey[%s], MacKey[%s]",
			RspFutureSignIn->TradeCode, RspFutureSignIn->BankID, RspFutureSignIn->BankBranchID, RspFutureSignIn->BrokerID, RspFutureSignIn->BrokerBranchID, RspFutureSignIn->TradeDate, RspFutureSignIn->TradeTime, RspFutureSignIn->BankSerial, RspFutureSignIn->TradingDay, RspFutureSignIn->PlateSerial, RspFutureSignIn->LastFragment, RspFutureSignIn->SessionID, RspFutureSignIn->InstallID, RspFutureSignIn->UserID, RspFutureSignIn->Digest, RspFutureSignIn->CurrencyID, RspFutureSignIn->DeviceID, RspFutureSignIn->BrokerIDByBank, RspFutureSignIn->OperNo, RspFutureSignIn->RequestID, RspFutureSignIn->TID, RspFutureSignIn->ErrorID, RspFutureSignIn->ErrorMsg, RspFutureSignIn->PinKey, RspFutureSignIn->MacKey);
	}
}
void WriteReqFutureSignOut(CThostFtdcReqFutureSignOutField* ReqFutureSignOut)
{
	if(ReqFutureSignOut)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReqFutureSignOutField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], InstallID[%d], UserID[%s], Digest[%s], CurrencyID[%s], DeviceID[%s], BrokerIDByBank[%s], OperNo[%s], RequestID[%d], TID[%d]",
			ReqFutureSignOut->TradeCode, ReqFutureSignOut->BankID, ReqFutureSignOut->BankBranchID, ReqFutureSignOut->BrokerID, ReqFutureSignOut->BrokerBranchID, ReqFutureSignOut->TradeDate, ReqFutureSignOut->TradeTime, ReqFutureSignOut->BankSerial, ReqFutureSignOut->TradingDay, ReqFutureSignOut->PlateSerial, ReqFutureSignOut->LastFragment, ReqFutureSignOut->SessionID, ReqFutureSignOut->InstallID, ReqFutureSignOut->UserID, ReqFutureSignOut->Digest, ReqFutureSignOut->CurrencyID, ReqFutureSignOut->DeviceID, ReqFutureSignOut->BrokerIDByBank, ReqFutureSignOut->OperNo, ReqFutureSignOut->RequestID, ReqFutureSignOut->TID);
	}
}
void WriteRspFutureSignOut(CThostFtdcRspFutureSignOutField* RspFutureSignOut)
{
	if(RspFutureSignOut)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRspFutureSignOutField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], InstallID[%d], UserID[%s], Digest[%s], CurrencyID[%s], DeviceID[%s], BrokerIDByBank[%s], OperNo[%s], RequestID[%d], TID[%d], ErrorID[%d], ErrorMsg[%s]",
			RspFutureSignOut->TradeCode, RspFutureSignOut->BankID, RspFutureSignOut->BankBranchID, RspFutureSignOut->BrokerID, RspFutureSignOut->BrokerBranchID, RspFutureSignOut->TradeDate, RspFutureSignOut->TradeTime, RspFutureSignOut->BankSerial, RspFutureSignOut->TradingDay, RspFutureSignOut->PlateSerial, RspFutureSignOut->LastFragment, RspFutureSignOut->SessionID, RspFutureSignOut->InstallID, RspFutureSignOut->UserID, RspFutureSignOut->Digest, RspFutureSignOut->CurrencyID, RspFutureSignOut->DeviceID, RspFutureSignOut->BrokerIDByBank, RspFutureSignOut->OperNo, RspFutureSignOut->RequestID, RspFutureSignOut->TID, RspFutureSignOut->ErrorID, RspFutureSignOut->ErrorMsg);
	}
}
void WriteReqQueryTradeResultBySerial(CThostFtdcReqQueryTradeResultBySerialField* ReqQueryTradeResultBySerial)
{
	if(ReqQueryTradeResultBySerial)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReqQueryTradeResultBySerialField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], Reference[%d], RefrenceIssureType[%c], RefrenceIssure[%s], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], CurrencyID[%s], TradeAmount[%f], Digest[%s], LongCustomerName[%s]",
			ReqQueryTradeResultBySerial->TradeCode, ReqQueryTradeResultBySerial->BankID, ReqQueryTradeResultBySerial->BankBranchID, ReqQueryTradeResultBySerial->BrokerID, ReqQueryTradeResultBySerial->BrokerBranchID, ReqQueryTradeResultBySerial->TradeDate, ReqQueryTradeResultBySerial->TradeTime, ReqQueryTradeResultBySerial->BankSerial, ReqQueryTradeResultBySerial->TradingDay, ReqQueryTradeResultBySerial->PlateSerial, ReqQueryTradeResultBySerial->LastFragment, ReqQueryTradeResultBySerial->SessionID, ReqQueryTradeResultBySerial->Reference, ReqQueryTradeResultBySerial->RefrenceIssureType, ReqQueryTradeResultBySerial->RefrenceIssure, ReqQueryTradeResultBySerial->CustomerName, ReqQueryTradeResultBySerial->IdCardType, ReqQueryTradeResultBySerial->IdentifiedCardNo, ReqQueryTradeResultBySerial->CustType, ReqQueryTradeResultBySerial->BankAccount, ReqQueryTradeResultBySerial->BankPassWord, ReqQueryTradeResultBySerial->AccountID, ReqQueryTradeResultBySerial->Password, ReqQueryTradeResultBySerial->CurrencyID, GetDoubleValue(ReqQueryTradeResultBySerial->TradeAmount), ReqQueryTradeResultBySerial->Digest, ReqQueryTradeResultBySerial->LongCustomerName);
	}
}
void WriteRspQueryTradeResultBySerial(CThostFtdcRspQueryTradeResultBySerialField* RspQueryTradeResultBySerial)
{
	if(RspQueryTradeResultBySerial)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRspQueryTradeResultBySerialField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], ErrorID[%d], ErrorMsg[%s], Reference[%d], RefrenceIssureType[%c], RefrenceIssure[%s], OriginReturnCode[%s], OriginDescrInfoForReturnCode[%s], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], CurrencyID[%s], TradeAmount[%f], Digest[%s]",
			RspQueryTradeResultBySerial->TradeCode, RspQueryTradeResultBySerial->BankID, RspQueryTradeResultBySerial->BankBranchID, RspQueryTradeResultBySerial->BrokerID, RspQueryTradeResultBySerial->BrokerBranchID, RspQueryTradeResultBySerial->TradeDate, RspQueryTradeResultBySerial->TradeTime, RspQueryTradeResultBySerial->BankSerial, RspQueryTradeResultBySerial->TradingDay, RspQueryTradeResultBySerial->PlateSerial, RspQueryTradeResultBySerial->LastFragment, RspQueryTradeResultBySerial->SessionID, RspQueryTradeResultBySerial->ErrorID, RspQueryTradeResultBySerial->ErrorMsg, RspQueryTradeResultBySerial->Reference, RspQueryTradeResultBySerial->RefrenceIssureType, RspQueryTradeResultBySerial->RefrenceIssure, RspQueryTradeResultBySerial->OriginReturnCode, RspQueryTradeResultBySerial->OriginDescrInfoForReturnCode, RspQueryTradeResultBySerial->BankAccount, RspQueryTradeResultBySerial->BankPassWord, RspQueryTradeResultBySerial->AccountID, RspQueryTradeResultBySerial->Password, RspQueryTradeResultBySerial->CurrencyID, GetDoubleValue(RspQueryTradeResultBySerial->TradeAmount), RspQueryTradeResultBySerial->Digest);
	}
}
void WriteReqDayEndFileReady(CThostFtdcReqDayEndFileReadyField* ReqDayEndFileReady)
{
	if(ReqDayEndFileReady)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReqDayEndFileReadyField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], FileBusinessCode[%c], Digest[%s]",
			ReqDayEndFileReady->TradeCode, ReqDayEndFileReady->BankID, ReqDayEndFileReady->BankBranchID, ReqDayEndFileReady->BrokerID, ReqDayEndFileReady->BrokerBranchID, ReqDayEndFileReady->TradeDate, ReqDayEndFileReady->TradeTime, ReqDayEndFileReady->BankSerial, ReqDayEndFileReady->TradingDay, ReqDayEndFileReady->PlateSerial, ReqDayEndFileReady->LastFragment, ReqDayEndFileReady->SessionID, ReqDayEndFileReady->FileBusinessCode, ReqDayEndFileReady->Digest);
	}
}
void WriteReturnResult(CThostFtdcReturnResultField* ReturnResult)
{
	if(ReturnResult)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReturnResultField: ReturnCode[%s], DescrInfoForReturnCode[%s]",
			ReturnResult->ReturnCode, ReturnResult->DescrInfoForReturnCode);
	}
}
void WriteVerifyFuturePassword(CThostFtdcVerifyFuturePasswordField* VerifyFuturePassword)
{
	if(VerifyFuturePassword)
	{
		WriteLog(LogLevel::Info, "CThostFtdcVerifyFuturePasswordField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], AccountID[%s], Password[%s], BankAccount[%s], BankPassWord[%s], InstallID[%d], TID[%d], CurrencyID[%s]",
			VerifyFuturePassword->TradeCode, VerifyFuturePassword->BankID, VerifyFuturePassword->BankBranchID, VerifyFuturePassword->BrokerID, VerifyFuturePassword->BrokerBranchID, VerifyFuturePassword->TradeDate, VerifyFuturePassword->TradeTime, VerifyFuturePassword->BankSerial, VerifyFuturePassword->TradingDay, VerifyFuturePassword->PlateSerial, VerifyFuturePassword->LastFragment, VerifyFuturePassword->SessionID, VerifyFuturePassword->AccountID, VerifyFuturePassword->Password, VerifyFuturePassword->BankAccount, VerifyFuturePassword->BankPassWord, VerifyFuturePassword->InstallID, VerifyFuturePassword->TID, VerifyFuturePassword->CurrencyID);
	}
}
void WriteVerifyCustInfo(CThostFtdcVerifyCustInfoField* VerifyCustInfo)
{
	if(VerifyCustInfo)
	{
		WriteLog(LogLevel::Info, "CThostFtdcVerifyCustInfoField: CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], LongCustomerName[%s]",
			VerifyCustInfo->CustomerName, VerifyCustInfo->IdCardType, VerifyCustInfo->IdentifiedCardNo, VerifyCustInfo->CustType, VerifyCustInfo->LongCustomerName);
	}
}
void WriteVerifyFuturePasswordAndCustInfo(CThostFtdcVerifyFuturePasswordAndCustInfoField* VerifyFuturePasswordAndCustInfo)
{
	if(VerifyFuturePasswordAndCustInfo)
	{
		WriteLog(LogLevel::Info, "CThostFtdcVerifyFuturePasswordAndCustInfoField: CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], AccountID[%s], Password[%s], CurrencyID[%s], LongCustomerName[%s]",
			VerifyFuturePasswordAndCustInfo->CustomerName, VerifyFuturePasswordAndCustInfo->IdCardType, VerifyFuturePasswordAndCustInfo->IdentifiedCardNo, VerifyFuturePasswordAndCustInfo->CustType, VerifyFuturePasswordAndCustInfo->AccountID, VerifyFuturePasswordAndCustInfo->Password, VerifyFuturePasswordAndCustInfo->CurrencyID, VerifyFuturePasswordAndCustInfo->LongCustomerName);
	}
}
void WriteDepositResultInform(CThostFtdcDepositResultInformField* DepositResultInform)
{
	if(DepositResultInform)
	{
		WriteLog(LogLevel::Info, "CThostFtdcDepositResultInformField: DepositSeqNo[%s], BrokerID[%s], InvestorID[%s], Deposit[%f], RequestID[%d], ReturnCode[%s], DescrInfoForReturnCode[%s]",
			DepositResultInform->DepositSeqNo, DepositResultInform->BrokerID, DepositResultInform->InvestorID, GetDoubleValue(DepositResultInform->Deposit), DepositResultInform->RequestID, DepositResultInform->ReturnCode, DepositResultInform->DescrInfoForReturnCode);
	}
}
void WriteReqSyncKey(CThostFtdcReqSyncKeyField* ReqSyncKey)
{
	if(ReqSyncKey)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReqSyncKeyField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], InstallID[%d], UserID[%s], Message[%s], DeviceID[%s], BrokerIDByBank[%s], OperNo[%s], RequestID[%d], TID[%d]",
			ReqSyncKey->TradeCode, ReqSyncKey->BankID, ReqSyncKey->BankBranchID, ReqSyncKey->BrokerID, ReqSyncKey->BrokerBranchID, ReqSyncKey->TradeDate, ReqSyncKey->TradeTime, ReqSyncKey->BankSerial, ReqSyncKey->TradingDay, ReqSyncKey->PlateSerial, ReqSyncKey->LastFragment, ReqSyncKey->SessionID, ReqSyncKey->InstallID, ReqSyncKey->UserID, ReqSyncKey->Message, ReqSyncKey->DeviceID, ReqSyncKey->BrokerIDByBank, ReqSyncKey->OperNo, ReqSyncKey->RequestID, ReqSyncKey->TID);
	}
}
void WriteRspSyncKey(CThostFtdcRspSyncKeyField* RspSyncKey)
{
	if(RspSyncKey)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRspSyncKeyField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], InstallID[%d], UserID[%s], Message[%s], DeviceID[%s], BrokerIDByBank[%s], OperNo[%s], RequestID[%d], TID[%d], ErrorID[%d], ErrorMsg[%s]",
			RspSyncKey->TradeCode, RspSyncKey->BankID, RspSyncKey->BankBranchID, RspSyncKey->BrokerID, RspSyncKey->BrokerBranchID, RspSyncKey->TradeDate, RspSyncKey->TradeTime, RspSyncKey->BankSerial, RspSyncKey->TradingDay, RspSyncKey->PlateSerial, RspSyncKey->LastFragment, RspSyncKey->SessionID, RspSyncKey->InstallID, RspSyncKey->UserID, RspSyncKey->Message, RspSyncKey->DeviceID, RspSyncKey->BrokerIDByBank, RspSyncKey->OperNo, RspSyncKey->RequestID, RspSyncKey->TID, RspSyncKey->ErrorID, RspSyncKey->ErrorMsg);
	}
}
void WriteNotifyQueryAccount(CThostFtdcNotifyQueryAccountField* NotifyQueryAccount)
{
	if(NotifyQueryAccount)
	{
		WriteLog(LogLevel::Info, "CThostFtdcNotifyQueryAccountField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], FutureSerial[%d], InstallID[%d], UserID[%s], VerifyCertNoFlag[%c], CurrencyID[%s], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], RequestID[%d], TID[%d], BankUseAmount[%f], BankFetchAmount[%f], ErrorID[%d], ErrorMsg[%s], LongCustomerName[%s]",
			NotifyQueryAccount->TradeCode, NotifyQueryAccount->BankID, NotifyQueryAccount->BankBranchID, NotifyQueryAccount->BrokerID, NotifyQueryAccount->BrokerBranchID, NotifyQueryAccount->TradeDate, NotifyQueryAccount->TradeTime, NotifyQueryAccount->BankSerial, NotifyQueryAccount->TradingDay, NotifyQueryAccount->PlateSerial, NotifyQueryAccount->LastFragment, NotifyQueryAccount->SessionID, NotifyQueryAccount->CustomerName, NotifyQueryAccount->IdCardType, NotifyQueryAccount->IdentifiedCardNo, NotifyQueryAccount->CustType, NotifyQueryAccount->BankAccount, NotifyQueryAccount->BankPassWord, NotifyQueryAccount->AccountID, NotifyQueryAccount->Password, NotifyQueryAccount->FutureSerial, NotifyQueryAccount->InstallID, NotifyQueryAccount->UserID, NotifyQueryAccount->VerifyCertNoFlag, NotifyQueryAccount->CurrencyID, NotifyQueryAccount->Digest, NotifyQueryAccount->BankAccType, NotifyQueryAccount->DeviceID, NotifyQueryAccount->BankSecuAccType, NotifyQueryAccount->BrokerIDByBank, NotifyQueryAccount->BankSecuAcc, NotifyQueryAccount->BankPwdFlag, NotifyQueryAccount->SecuPwdFlag, NotifyQueryAccount->OperNo, NotifyQueryAccount->RequestID, NotifyQueryAccount->TID, GetDoubleValue(NotifyQueryAccount->BankUseAmount), GetDoubleValue(NotifyQueryAccount->BankFetchAmount), NotifyQueryAccount->ErrorID, NotifyQueryAccount->ErrorMsg, NotifyQueryAccount->LongCustomerName);
	}
}
void WriteTransferSerial(CThostFtdcTransferSerialField* TransferSerial)
{
	if(TransferSerial)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTransferSerialField: PlateSerial[%d], TradeDate[%s], TradingDay[%s], TradeTime[%s], TradeCode[%s], SessionID[%d], BankID[%s], BankBranchID[%s], BankAccType[%c], BankAccount[%s], BankSerial[%s], BrokerID[%s], BrokerBranchID[%s], FutureAccType[%c], AccountID[%s], InvestorID[%s], FutureSerial[%d], IdCardType[%c], IdentifiedCardNo[%s], CurrencyID[%s], TradeAmount[%f], CustFee[%f], BrokerFee[%f], AvailabilityFlag[%c], OperatorCode[%s], BankNewAccount[%s], ErrorID[%d], ErrorMsg[%s]",
			TransferSerial->PlateSerial, TransferSerial->TradeDate, TransferSerial->TradingDay, TransferSerial->TradeTime, TransferSerial->TradeCode, TransferSerial->SessionID, TransferSerial->BankID, TransferSerial->BankBranchID, TransferSerial->BankAccType, TransferSerial->BankAccount, TransferSerial->BankSerial, TransferSerial->BrokerID, TransferSerial->BrokerBranchID, TransferSerial->FutureAccType, TransferSerial->AccountID, TransferSerial->InvestorID, TransferSerial->FutureSerial, TransferSerial->IdCardType, TransferSerial->IdentifiedCardNo, TransferSerial->CurrencyID, GetDoubleValue(TransferSerial->TradeAmount), GetDoubleValue(TransferSerial->CustFee), GetDoubleValue(TransferSerial->BrokerFee), TransferSerial->AvailabilityFlag, TransferSerial->OperatorCode, TransferSerial->BankNewAccount, TransferSerial->ErrorID, TransferSerial->ErrorMsg);
	}
}
void WriteQryTransferSerial(CThostFtdcQryTransferSerialField* QryTransferSerial)
{
	if(QryTransferSerial)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryTransferSerialField: BrokerID[%s], AccountID[%s], BankID[%s], CurrencyID[%s]",
			QryTransferSerial->BrokerID, QryTransferSerial->AccountID, QryTransferSerial->BankID, QryTransferSerial->CurrencyID);
	}
}
void WriteNotifyFutureSignIn(CThostFtdcNotifyFutureSignInField* NotifyFutureSignIn)
{
	if(NotifyFutureSignIn)
	{
		WriteLog(LogLevel::Info, "CThostFtdcNotifyFutureSignInField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], InstallID[%d], UserID[%s], Digest[%s], CurrencyID[%s], DeviceID[%s], BrokerIDByBank[%s], OperNo[%s], RequestID[%d], TID[%d], ErrorID[%d], ErrorMsg[%s], PinKey[%s], MacKey[%s]",
			NotifyFutureSignIn->TradeCode, NotifyFutureSignIn->BankID, NotifyFutureSignIn->BankBranchID, NotifyFutureSignIn->BrokerID, NotifyFutureSignIn->BrokerBranchID, NotifyFutureSignIn->TradeDate, NotifyFutureSignIn->TradeTime, NotifyFutureSignIn->BankSerial, NotifyFutureSignIn->TradingDay, NotifyFutureSignIn->PlateSerial, NotifyFutureSignIn->LastFragment, NotifyFutureSignIn->SessionID, NotifyFutureSignIn->InstallID, NotifyFutureSignIn->UserID, NotifyFutureSignIn->Digest, NotifyFutureSignIn->CurrencyID, NotifyFutureSignIn->DeviceID, NotifyFutureSignIn->BrokerIDByBank, NotifyFutureSignIn->OperNo, NotifyFutureSignIn->RequestID, NotifyFutureSignIn->TID, NotifyFutureSignIn->ErrorID, NotifyFutureSignIn->ErrorMsg, NotifyFutureSignIn->PinKey, NotifyFutureSignIn->MacKey);
	}
}
void WriteNotifyFutureSignOut(CThostFtdcNotifyFutureSignOutField* NotifyFutureSignOut)
{
	if(NotifyFutureSignOut)
	{
		WriteLog(LogLevel::Info, "CThostFtdcNotifyFutureSignOutField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], InstallID[%d], UserID[%s], Digest[%s], CurrencyID[%s], DeviceID[%s], BrokerIDByBank[%s], OperNo[%s], RequestID[%d], TID[%d], ErrorID[%d], ErrorMsg[%s]",
			NotifyFutureSignOut->TradeCode, NotifyFutureSignOut->BankID, NotifyFutureSignOut->BankBranchID, NotifyFutureSignOut->BrokerID, NotifyFutureSignOut->BrokerBranchID, NotifyFutureSignOut->TradeDate, NotifyFutureSignOut->TradeTime, NotifyFutureSignOut->BankSerial, NotifyFutureSignOut->TradingDay, NotifyFutureSignOut->PlateSerial, NotifyFutureSignOut->LastFragment, NotifyFutureSignOut->SessionID, NotifyFutureSignOut->InstallID, NotifyFutureSignOut->UserID, NotifyFutureSignOut->Digest, NotifyFutureSignOut->CurrencyID, NotifyFutureSignOut->DeviceID, NotifyFutureSignOut->BrokerIDByBank, NotifyFutureSignOut->OperNo, NotifyFutureSignOut->RequestID, NotifyFutureSignOut->TID, NotifyFutureSignOut->ErrorID, NotifyFutureSignOut->ErrorMsg);
	}
}
void WriteNotifySyncKey(CThostFtdcNotifySyncKeyField* NotifySyncKey)
{
	if(NotifySyncKey)
	{
		WriteLog(LogLevel::Info, "CThostFtdcNotifySyncKeyField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], InstallID[%d], UserID[%s], Message[%s], DeviceID[%s], BrokerIDByBank[%s], OperNo[%s], RequestID[%d], TID[%d], ErrorID[%d], ErrorMsg[%s]",
			NotifySyncKey->TradeCode, NotifySyncKey->BankID, NotifySyncKey->BankBranchID, NotifySyncKey->BrokerID, NotifySyncKey->BrokerBranchID, NotifySyncKey->TradeDate, NotifySyncKey->TradeTime, NotifySyncKey->BankSerial, NotifySyncKey->TradingDay, NotifySyncKey->PlateSerial, NotifySyncKey->LastFragment, NotifySyncKey->SessionID, NotifySyncKey->InstallID, NotifySyncKey->UserID, NotifySyncKey->Message, NotifySyncKey->DeviceID, NotifySyncKey->BrokerIDByBank, NotifySyncKey->OperNo, NotifySyncKey->RequestID, NotifySyncKey->TID, NotifySyncKey->ErrorID, NotifySyncKey->ErrorMsg);
	}
}
void WriteQryAccountregister(CThostFtdcQryAccountregisterField* QryAccountregister)
{
	if(QryAccountregister)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryAccountregisterField: BrokerID[%s], AccountID[%s], BankID[%s], BankBranchID[%s], CurrencyID[%s]",
			QryAccountregister->BrokerID, QryAccountregister->AccountID, QryAccountregister->BankID, QryAccountregister->BankBranchID, QryAccountregister->CurrencyID);
	}
}
void WriteAccountregister(CThostFtdcAccountregisterField* Accountregister)
{
	if(Accountregister)
	{
		WriteLog(LogLevel::Info, "CThostFtdcAccountregisterField: TradeDay[%s], BankID[%s], BankBranchID[%s], BankAccount[%s], BrokerID[%s], BrokerBranchID[%s], AccountID[%s], IdCardType[%c], IdentifiedCardNo[%s], CustomerName[%s], CurrencyID[%s], OpenOrDestroy[%c], RegDate[%s], OutDate[%s], TID[%d], CustType[%c], BankAccType[%c], LongCustomerName[%s]",
			Accountregister->TradeDay, Accountregister->BankID, Accountregister->BankBranchID, Accountregister->BankAccount, Accountregister->BrokerID, Accountregister->BrokerBranchID, Accountregister->AccountID, Accountregister->IdCardType, Accountregister->IdentifiedCardNo, Accountregister->CustomerName, Accountregister->CurrencyID, Accountregister->OpenOrDestroy, Accountregister->RegDate, Accountregister->OutDate, Accountregister->TID, Accountregister->CustType, Accountregister->BankAccType, Accountregister->LongCustomerName);
	}
}
void WriteOpenAccount(CThostFtdcOpenAccountField* OpenAccount)
{
	if(OpenAccount)
	{
		WriteLog(LogLevel::Info, "CThostFtdcOpenAccountField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], Gender[%c], CountryCode[%s], CustType[%c], Address[%s], ZipCode[%s], Telephone[%s], MobilePhone[%s], Fax[%s], EMail[%s], MoneyAccountStatus[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], InstallID[%d], VerifyCertNoFlag[%c], CurrencyID[%s], CashExchangeCode[%c], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], TID[%d], UserID[%s], ErrorID[%d], ErrorMsg[%s], LongCustomerName[%s]",
			OpenAccount->TradeCode, OpenAccount->BankID, OpenAccount->BankBranchID, OpenAccount->BrokerID, OpenAccount->BrokerBranchID, OpenAccount->TradeDate, OpenAccount->TradeTime, OpenAccount->BankSerial, OpenAccount->TradingDay, OpenAccount->PlateSerial, OpenAccount->LastFragment, OpenAccount->SessionID, OpenAccount->CustomerName, OpenAccount->IdCardType, OpenAccount->IdentifiedCardNo, OpenAccount->Gender, OpenAccount->CountryCode, OpenAccount->CustType, OpenAccount->Address, OpenAccount->ZipCode, OpenAccount->Telephone, OpenAccount->MobilePhone, OpenAccount->Fax, OpenAccount->EMail, OpenAccount->MoneyAccountStatus, OpenAccount->BankAccount, OpenAccount->BankPassWord, OpenAccount->AccountID, OpenAccount->Password, OpenAccount->InstallID, OpenAccount->VerifyCertNoFlag, OpenAccount->CurrencyID, OpenAccount->CashExchangeCode, OpenAccount->Digest, OpenAccount->BankAccType, OpenAccount->DeviceID, OpenAccount->BankSecuAccType, OpenAccount->BrokerIDByBank, OpenAccount->BankSecuAcc, OpenAccount->BankPwdFlag, OpenAccount->SecuPwdFlag, OpenAccount->OperNo, OpenAccount->TID, OpenAccount->UserID, OpenAccount->ErrorID, OpenAccount->ErrorMsg, OpenAccount->LongCustomerName);
	}
}
void WriteCancelAccount(CThostFtdcCancelAccountField* CancelAccount)
{
	if(CancelAccount)
	{
		WriteLog(LogLevel::Info, "CThostFtdcCancelAccountField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], Gender[%c], CountryCode[%s], CustType[%c], Address[%s], ZipCode[%s], Telephone[%s], MobilePhone[%s], Fax[%s], EMail[%s], MoneyAccountStatus[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], InstallID[%d], VerifyCertNoFlag[%c], CurrencyID[%s], CashExchangeCode[%c], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], TID[%d], UserID[%s], ErrorID[%d], ErrorMsg[%s], LongCustomerName[%s]",
			CancelAccount->TradeCode, CancelAccount->BankID, CancelAccount->BankBranchID, CancelAccount->BrokerID, CancelAccount->BrokerBranchID, CancelAccount->TradeDate, CancelAccount->TradeTime, CancelAccount->BankSerial, CancelAccount->TradingDay, CancelAccount->PlateSerial, CancelAccount->LastFragment, CancelAccount->SessionID, CancelAccount->CustomerName, CancelAccount->IdCardType, CancelAccount->IdentifiedCardNo, CancelAccount->Gender, CancelAccount->CountryCode, CancelAccount->CustType, CancelAccount->Address, CancelAccount->ZipCode, CancelAccount->Telephone, CancelAccount->MobilePhone, CancelAccount->Fax, CancelAccount->EMail, CancelAccount->MoneyAccountStatus, CancelAccount->BankAccount, CancelAccount->BankPassWord, CancelAccount->AccountID, CancelAccount->Password, CancelAccount->InstallID, CancelAccount->VerifyCertNoFlag, CancelAccount->CurrencyID, CancelAccount->CashExchangeCode, CancelAccount->Digest, CancelAccount->BankAccType, CancelAccount->DeviceID, CancelAccount->BankSecuAccType, CancelAccount->BrokerIDByBank, CancelAccount->BankSecuAcc, CancelAccount->BankPwdFlag, CancelAccount->SecuPwdFlag, CancelAccount->OperNo, CancelAccount->TID, CancelAccount->UserID, CancelAccount->ErrorID, CancelAccount->ErrorMsg, CancelAccount->LongCustomerName);
	}
}
void WriteChangeAccount(CThostFtdcChangeAccountField* ChangeAccount)
{
	if(ChangeAccount)
	{
		WriteLog(LogLevel::Info, "CThostFtdcChangeAccountField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], Gender[%c], CountryCode[%s], CustType[%c], Address[%s], ZipCode[%s], Telephone[%s], MobilePhone[%s], Fax[%s], EMail[%s], MoneyAccountStatus[%c], BankAccount[%s], BankPassWord[%s], NewBankAccount[%s], NewBankPassWord[%s], AccountID[%s], Password[%s], BankAccType[%c], InstallID[%d], VerifyCertNoFlag[%c], CurrencyID[%s], BrokerIDByBank[%s], BankPwdFlag[%c], SecuPwdFlag[%c], TID[%d], Digest[%s], ErrorID[%d], ErrorMsg[%s], LongCustomerName[%s]",
			ChangeAccount->TradeCode, ChangeAccount->BankID, ChangeAccount->BankBranchID, ChangeAccount->BrokerID, ChangeAccount->BrokerBranchID, ChangeAccount->TradeDate, ChangeAccount->TradeTime, ChangeAccount->BankSerial, ChangeAccount->TradingDay, ChangeAccount->PlateSerial, ChangeAccount->LastFragment, ChangeAccount->SessionID, ChangeAccount->CustomerName, ChangeAccount->IdCardType, ChangeAccount->IdentifiedCardNo, ChangeAccount->Gender, ChangeAccount->CountryCode, ChangeAccount->CustType, ChangeAccount->Address, ChangeAccount->ZipCode, ChangeAccount->Telephone, ChangeAccount->MobilePhone, ChangeAccount->Fax, ChangeAccount->EMail, ChangeAccount->MoneyAccountStatus, ChangeAccount->BankAccount, ChangeAccount->BankPassWord, ChangeAccount->NewBankAccount, ChangeAccount->NewBankPassWord, ChangeAccount->AccountID, ChangeAccount->Password, ChangeAccount->BankAccType, ChangeAccount->InstallID, ChangeAccount->VerifyCertNoFlag, ChangeAccount->CurrencyID, ChangeAccount->BrokerIDByBank, ChangeAccount->BankPwdFlag, ChangeAccount->SecuPwdFlag, ChangeAccount->TID, ChangeAccount->Digest, ChangeAccount->ErrorID, ChangeAccount->ErrorMsg, ChangeAccount->LongCustomerName);
	}
}
void WriteSecAgentACIDMap(CThostFtdcSecAgentACIDMapField* SecAgentACIDMap)
{
	if(SecAgentACIDMap)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSecAgentACIDMapField: BrokerID[%s], UserID[%s], AccountID[%s], CurrencyID[%s], BrokerSecAgentID[%s]",
			SecAgentACIDMap->BrokerID, SecAgentACIDMap->UserID, SecAgentACIDMap->AccountID, SecAgentACIDMap->CurrencyID, SecAgentACIDMap->BrokerSecAgentID);
	}
}
void WriteQrySecAgentACIDMap(CThostFtdcQrySecAgentACIDMapField* QrySecAgentACIDMap)
{
	if(QrySecAgentACIDMap)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQrySecAgentACIDMapField: BrokerID[%s], UserID[%s], AccountID[%s], CurrencyID[%s]",
			QrySecAgentACIDMap->BrokerID, QrySecAgentACIDMap->UserID, QrySecAgentACIDMap->AccountID, QrySecAgentACIDMap->CurrencyID);
	}
}
void WriteUserRightsAssign(CThostFtdcUserRightsAssignField* UserRightsAssign)
{
	if(UserRightsAssign)
	{
		WriteLog(LogLevel::Info, "CThostFtdcUserRightsAssignField: BrokerID[%s], UserID[%s], DRIdentityID[%d]",
			UserRightsAssign->BrokerID, UserRightsAssign->UserID, UserRightsAssign->DRIdentityID);
	}
}
void WriteBrokerUserRightAssign(CThostFtdcBrokerUserRightAssignField* BrokerUserRightAssign)
{
	if(BrokerUserRightAssign)
	{
		WriteLog(LogLevel::Info, "CThostFtdcBrokerUserRightAssignField: BrokerID[%s], DRIdentityID[%d], Tradeable[%d]",
			BrokerUserRightAssign->BrokerID, BrokerUserRightAssign->DRIdentityID, BrokerUserRightAssign->Tradeable);
	}
}
void WriteDRTransfer(CThostFtdcDRTransferField* DRTransfer)
{
	if(DRTransfer)
	{
		WriteLog(LogLevel::Info, "CThostFtdcDRTransferField: OrigDRIdentityID[%d], DestDRIdentityID[%d], OrigBrokerID[%s], DestBrokerID[%s]",
			DRTransfer->OrigDRIdentityID, DRTransfer->DestDRIdentityID, DRTransfer->OrigBrokerID, DRTransfer->DestBrokerID);
	}
}
void WriteFensUserInfo(CThostFtdcFensUserInfoField* FensUserInfo)
{
	if(FensUserInfo)
	{
		WriteLog(LogLevel::Info, "CThostFtdcFensUserInfoField: BrokerID[%s], UserID[%s], LoginMode[%c]",
			FensUserInfo->BrokerID, FensUserInfo->UserID, FensUserInfo->LoginMode);
	}
}
void WriteCurrTransferIdentity(CThostFtdcCurrTransferIdentityField* CurrTransferIdentity)
{
	if(CurrTransferIdentity)
	{
		WriteLog(LogLevel::Info, "CThostFtdcCurrTransferIdentityField: IdentityID[%d]",
			CurrTransferIdentity->IdentityID);
	}
}
void WriteLoginForbiddenUser(CThostFtdcLoginForbiddenUserField* LoginForbiddenUser)
{
	if(LoginForbiddenUser)
	{
		WriteLog(LogLevel::Info, "CThostFtdcLoginForbiddenUserField: BrokerID[%s], UserID[%s], reserve1[%s], IPAddress[%s]",
			LoginForbiddenUser->BrokerID, LoginForbiddenUser->UserID, LoginForbiddenUser->reserve1, LoginForbiddenUser->IPAddress);
	}
}
void WriteQryLoginForbiddenUser(CThostFtdcQryLoginForbiddenUserField* QryLoginForbiddenUser)
{
	if(QryLoginForbiddenUser)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryLoginForbiddenUserField: BrokerID[%s], UserID[%s]",
			QryLoginForbiddenUser->BrokerID, QryLoginForbiddenUser->UserID);
	}
}
void WriteTradingAccountReserve(CThostFtdcTradingAccountReserveField* TradingAccountReserve)
{
	if(TradingAccountReserve)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTradingAccountReserveField: BrokerID[%s], AccountID[%s], Reserve[%f], CurrencyID[%s]",
			TradingAccountReserve->BrokerID, TradingAccountReserve->AccountID, GetDoubleValue(TradingAccountReserve->Reserve), TradingAccountReserve->CurrencyID);
	}
}
void WriteQryLoginForbiddenIP(CThostFtdcQryLoginForbiddenIPField* QryLoginForbiddenIP)
{
	if(QryLoginForbiddenIP)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryLoginForbiddenIPField: reserve1[%s], IPAddress[%s]",
			QryLoginForbiddenIP->reserve1, QryLoginForbiddenIP->IPAddress);
	}
}
void WriteQryIPList(CThostFtdcQryIPListField* QryIPList)
{
	if(QryIPList)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryIPListField: reserve1[%s], IPAddress[%s]",
			QryIPList->reserve1, QryIPList->IPAddress);
	}
}
void WriteQryUserRightsAssign(CThostFtdcQryUserRightsAssignField* QryUserRightsAssign)
{
	if(QryUserRightsAssign)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryUserRightsAssignField: BrokerID[%s], UserID[%s]",
			QryUserRightsAssign->BrokerID, QryUserRightsAssign->UserID);
	}
}
void WriteReserveOpenAccountConfirm(CThostFtdcReserveOpenAccountConfirmField* ReserveOpenAccountConfirm)
{
	if(ReserveOpenAccountConfirm)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReserveOpenAccountConfirmField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], Gender[%c], CountryCode[%s], CustType[%c], Address[%s], ZipCode[%s], Telephone[%s], MobilePhone[%s], Fax[%s], EMail[%s], MoneyAccountStatus[%c], BankAccount[%s], BankPassWord[%s], InstallID[%d], VerifyCertNoFlag[%c], CurrencyID[%s], Digest[%s], BankAccType[%c], BrokerIDByBank[%s], TID[%d], AccountID[%s], Password[%s], BankReserveOpenSeq[%s], BookDate[%s], BookPsw[%s], ErrorID[%d], ErrorMsg[%s]",
			ReserveOpenAccountConfirm->TradeCode, ReserveOpenAccountConfirm->BankID, ReserveOpenAccountConfirm->BankBranchID, ReserveOpenAccountConfirm->BrokerID, ReserveOpenAccountConfirm->BrokerBranchID, ReserveOpenAccountConfirm->TradeDate, ReserveOpenAccountConfirm->TradeTime, ReserveOpenAccountConfirm->BankSerial, ReserveOpenAccountConfirm->TradingDay, ReserveOpenAccountConfirm->PlateSerial, ReserveOpenAccountConfirm->LastFragment, ReserveOpenAccountConfirm->SessionID, ReserveOpenAccountConfirm->CustomerName, ReserveOpenAccountConfirm->IdCardType, ReserveOpenAccountConfirm->IdentifiedCardNo, ReserveOpenAccountConfirm->Gender, ReserveOpenAccountConfirm->CountryCode, ReserveOpenAccountConfirm->CustType, ReserveOpenAccountConfirm->Address, ReserveOpenAccountConfirm->ZipCode, ReserveOpenAccountConfirm->Telephone, ReserveOpenAccountConfirm->MobilePhone, ReserveOpenAccountConfirm->Fax, ReserveOpenAccountConfirm->EMail, ReserveOpenAccountConfirm->MoneyAccountStatus, ReserveOpenAccountConfirm->BankAccount, ReserveOpenAccountConfirm->BankPassWord, ReserveOpenAccountConfirm->InstallID, ReserveOpenAccountConfirm->VerifyCertNoFlag, ReserveOpenAccountConfirm->CurrencyID, ReserveOpenAccountConfirm->Digest, ReserveOpenAccountConfirm->BankAccType, ReserveOpenAccountConfirm->BrokerIDByBank, ReserveOpenAccountConfirm->TID, ReserveOpenAccountConfirm->AccountID, ReserveOpenAccountConfirm->Password, ReserveOpenAccountConfirm->BankReserveOpenSeq, ReserveOpenAccountConfirm->BookDate, ReserveOpenAccountConfirm->BookPsw, ReserveOpenAccountConfirm->ErrorID, ReserveOpenAccountConfirm->ErrorMsg);
	}
}
void WriteReserveOpenAccount(CThostFtdcReserveOpenAccountField* ReserveOpenAccount)
{
	if(ReserveOpenAccount)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReserveOpenAccountField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], Gender[%c], CountryCode[%s], CustType[%c], Address[%s], ZipCode[%s], Telephone[%s], MobilePhone[%s], Fax[%s], EMail[%s], MoneyAccountStatus[%c], BankAccount[%s], BankPassWord[%s], InstallID[%d], VerifyCertNoFlag[%c], CurrencyID[%s], Digest[%s], BankAccType[%c], BrokerIDByBank[%s], TID[%d], ReserveOpenAccStas[%c], ErrorID[%d], ErrorMsg[%s]",
			ReserveOpenAccount->TradeCode, ReserveOpenAccount->BankID, ReserveOpenAccount->BankBranchID, ReserveOpenAccount->BrokerID, ReserveOpenAccount->BrokerBranchID, ReserveOpenAccount->TradeDate, ReserveOpenAccount->TradeTime, ReserveOpenAccount->BankSerial, ReserveOpenAccount->TradingDay, ReserveOpenAccount->PlateSerial, ReserveOpenAccount->LastFragment, ReserveOpenAccount->SessionID, ReserveOpenAccount->CustomerName, ReserveOpenAccount->IdCardType, ReserveOpenAccount->IdentifiedCardNo, ReserveOpenAccount->Gender, ReserveOpenAccount->CountryCode, ReserveOpenAccount->CustType, ReserveOpenAccount->Address, ReserveOpenAccount->ZipCode, ReserveOpenAccount->Telephone, ReserveOpenAccount->MobilePhone, ReserveOpenAccount->Fax, ReserveOpenAccount->EMail, ReserveOpenAccount->MoneyAccountStatus, ReserveOpenAccount->BankAccount, ReserveOpenAccount->BankPassWord, ReserveOpenAccount->InstallID, ReserveOpenAccount->VerifyCertNoFlag, ReserveOpenAccount->CurrencyID, ReserveOpenAccount->Digest, ReserveOpenAccount->BankAccType, ReserveOpenAccount->BrokerIDByBank, ReserveOpenAccount->TID, ReserveOpenAccount->ReserveOpenAccStas, ReserveOpenAccount->ErrorID, ReserveOpenAccount->ErrorMsg);
	}
}
void WriteAccountProperty(CThostFtdcAccountPropertyField* AccountProperty)
{
	if(AccountProperty)
	{
		WriteLog(LogLevel::Info, "CThostFtdcAccountPropertyField: BrokerID[%s], AccountID[%s], BankID[%s], BankAccount[%s], OpenName[%s], OpenBank[%s], IsActive[%d], AccountSourceType[%c], OpenDate[%s], CancelDate[%s], OperatorID[%s], OperateDate[%s], OperateTime[%s], CurrencyID[%s]",
			AccountProperty->BrokerID, AccountProperty->AccountID, AccountProperty->BankID, AccountProperty->BankAccount, AccountProperty->OpenName, AccountProperty->OpenBank, AccountProperty->IsActive, AccountProperty->AccountSourceType, AccountProperty->OpenDate, AccountProperty->CancelDate, AccountProperty->OperatorID, AccountProperty->OperateDate, AccountProperty->OperateTime, AccountProperty->CurrencyID);
	}
}
void WriteQryCurrDRIdentity(CThostFtdcQryCurrDRIdentityField* QryCurrDRIdentity)
{
	if(QryCurrDRIdentity)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryCurrDRIdentityField: DRIdentityID[%d]",
			QryCurrDRIdentity->DRIdentityID);
	}
}
void WriteCurrDRIdentity(CThostFtdcCurrDRIdentityField* CurrDRIdentity)
{
	if(CurrDRIdentity)
	{
		WriteLog(LogLevel::Info, "CThostFtdcCurrDRIdentityField: DRIdentityID[%d]",
			CurrDRIdentity->DRIdentityID);
	}
}
void WriteQrySecAgentCheckMode(CThostFtdcQrySecAgentCheckModeField* QrySecAgentCheckMode)
{
	if(QrySecAgentCheckMode)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQrySecAgentCheckModeField: BrokerID[%s], InvestorID[%s]",
			QrySecAgentCheckMode->BrokerID, QrySecAgentCheckMode->InvestorID);
	}
}
void WriteQrySecAgentTradeInfo(CThostFtdcQrySecAgentTradeInfoField* QrySecAgentTradeInfo)
{
	if(QrySecAgentTradeInfo)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQrySecAgentTradeInfoField: BrokerID[%s], BrokerSecAgentID[%s]",
			QrySecAgentTradeInfo->BrokerID, QrySecAgentTradeInfo->BrokerSecAgentID);
	}
}
void WriteReqUserAuthMethod(CThostFtdcReqUserAuthMethodField* ReqUserAuthMethod)
{
	if(ReqUserAuthMethod)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReqUserAuthMethodField: TradingDay[%s], BrokerID[%s], UserID[%s]",
			ReqUserAuthMethod->TradingDay, ReqUserAuthMethod->BrokerID, ReqUserAuthMethod->UserID);
	}
}
void WriteRspUserAuthMethod(CThostFtdcRspUserAuthMethodField* RspUserAuthMethod)
{
	if(RspUserAuthMethod)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRspUserAuthMethodField: UsableAuthMethod[%d]",
			RspUserAuthMethod->UsableAuthMethod);
	}
}
void WriteReqGenUserCaptcha(CThostFtdcReqGenUserCaptchaField* ReqGenUserCaptcha)
{
	if(ReqGenUserCaptcha)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReqGenUserCaptchaField: TradingDay[%s], BrokerID[%s], UserID[%s]",
			ReqGenUserCaptcha->TradingDay, ReqGenUserCaptcha->BrokerID, ReqGenUserCaptcha->UserID);
	}
}
void WriteRspGenUserCaptcha(CThostFtdcRspGenUserCaptchaField* RspGenUserCaptcha)
{
	if(RspGenUserCaptcha)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRspGenUserCaptchaField: BrokerID[%s], UserID[%s], CaptchaInfoLen[%d], CaptchaInfo[%s]",
			RspGenUserCaptcha->BrokerID, RspGenUserCaptcha->UserID, RspGenUserCaptcha->CaptchaInfoLen, RspGenUserCaptcha->CaptchaInfo);
	}
}
void WriteReqGenUserText(CThostFtdcReqGenUserTextField* ReqGenUserText)
{
	if(ReqGenUserText)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReqGenUserTextField: TradingDay[%s], BrokerID[%s], UserID[%s]",
			ReqGenUserText->TradingDay, ReqGenUserText->BrokerID, ReqGenUserText->UserID);
	}
}
void WriteRspGenUserText(CThostFtdcRspGenUserTextField* RspGenUserText)
{
	if(RspGenUserText)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRspGenUserTextField: UserTextSeq[%d]",
			RspGenUserText->UserTextSeq);
	}
}
void WriteReqUserLoginWithCaptcha(CThostFtdcReqUserLoginWithCaptchaField* ReqUserLoginWithCaptcha)
{
	if(ReqUserLoginWithCaptcha)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReqUserLoginWithCaptchaField: TradingDay[%s], BrokerID[%s], UserID[%s], Password[%s], UserProductInfo[%s], InterfaceProductInfo[%s], ProtocolInfo[%s], MacAddress[%s], reserve1[%s], LoginRemark[%s], Captcha[%s], ClientIPPort[%d], ClientIPAddress[%s]",
			ReqUserLoginWithCaptcha->TradingDay, ReqUserLoginWithCaptcha->BrokerID, ReqUserLoginWithCaptcha->UserID, ReqUserLoginWithCaptcha->Password, ReqUserLoginWithCaptcha->UserProductInfo, ReqUserLoginWithCaptcha->InterfaceProductInfo, ReqUserLoginWithCaptcha->ProtocolInfo, ReqUserLoginWithCaptcha->MacAddress, ReqUserLoginWithCaptcha->reserve1, ReqUserLoginWithCaptcha->LoginRemark, ReqUserLoginWithCaptcha->Captcha, ReqUserLoginWithCaptcha->ClientIPPort, ReqUserLoginWithCaptcha->ClientIPAddress);
	}
}
void WriteReqUserLoginWithText(CThostFtdcReqUserLoginWithTextField* ReqUserLoginWithText)
{
	if(ReqUserLoginWithText)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReqUserLoginWithTextField: TradingDay[%s], BrokerID[%s], UserID[%s], Password[%s], UserProductInfo[%s], InterfaceProductInfo[%s], ProtocolInfo[%s], MacAddress[%s], reserve1[%s], LoginRemark[%s], Text[%s], ClientIPPort[%d], ClientIPAddress[%s]",
			ReqUserLoginWithText->TradingDay, ReqUserLoginWithText->BrokerID, ReqUserLoginWithText->UserID, ReqUserLoginWithText->Password, ReqUserLoginWithText->UserProductInfo, ReqUserLoginWithText->InterfaceProductInfo, ReqUserLoginWithText->ProtocolInfo, ReqUserLoginWithText->MacAddress, ReqUserLoginWithText->reserve1, ReqUserLoginWithText->LoginRemark, ReqUserLoginWithText->Text, ReqUserLoginWithText->ClientIPPort, ReqUserLoginWithText->ClientIPAddress);
	}
}
void WriteReqUserLoginWithOTP(CThostFtdcReqUserLoginWithOTPField* ReqUserLoginWithOTP)
{
	if(ReqUserLoginWithOTP)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReqUserLoginWithOTPField: TradingDay[%s], BrokerID[%s], UserID[%s], Password[%s], UserProductInfo[%s], InterfaceProductInfo[%s], ProtocolInfo[%s], MacAddress[%s], reserve1[%s], LoginRemark[%s], OTPPassword[%s], ClientIPPort[%d], ClientIPAddress[%s]",
			ReqUserLoginWithOTP->TradingDay, ReqUserLoginWithOTP->BrokerID, ReqUserLoginWithOTP->UserID, ReqUserLoginWithOTP->Password, ReqUserLoginWithOTP->UserProductInfo, ReqUserLoginWithOTP->InterfaceProductInfo, ReqUserLoginWithOTP->ProtocolInfo, ReqUserLoginWithOTP->MacAddress, ReqUserLoginWithOTP->reserve1, ReqUserLoginWithOTP->LoginRemark, ReqUserLoginWithOTP->OTPPassword, ReqUserLoginWithOTP->ClientIPPort, ReqUserLoginWithOTP->ClientIPAddress);
	}
}
void WriteReqApiHandshake(CThostFtdcReqApiHandshakeField* ReqApiHandshake)
{
	if(ReqApiHandshake)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReqApiHandshakeField: CryptoKeyVersion[%s]",
			ReqApiHandshake->CryptoKeyVersion);
	}
}
void WriteRspApiHandshake(CThostFtdcRspApiHandshakeField* RspApiHandshake)
{
	if(RspApiHandshake)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRspApiHandshakeField: FrontHandshakeDataLen[%d], FrontHandshakeData[%s], IsApiAuthEnabled[%d]",
			RspApiHandshake->FrontHandshakeDataLen, RspApiHandshake->FrontHandshakeData, RspApiHandshake->IsApiAuthEnabled);
	}
}
void WriteReqVerifyApiKey(CThostFtdcReqVerifyApiKeyField* ReqVerifyApiKey)
{
	if(ReqVerifyApiKey)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReqVerifyApiKeyField: ApiHandshakeDataLen[%d], ApiHandshakeData[%s]",
			ReqVerifyApiKey->ApiHandshakeDataLen, ReqVerifyApiKey->ApiHandshakeData);
	}
}
void WriteDepartmentUser(CThostFtdcDepartmentUserField* DepartmentUser)
{
	if(DepartmentUser)
	{
		WriteLog(LogLevel::Info, "CThostFtdcDepartmentUserField: BrokerID[%s], UserID[%s], InvestorRange[%c], InvestorID[%s]",
			DepartmentUser->BrokerID, DepartmentUser->UserID, DepartmentUser->InvestorRange, DepartmentUser->InvestorID);
	}
}
void WriteQueryFreq(CThostFtdcQueryFreqField* QueryFreq)
{
	if(QueryFreq)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQueryFreqField: QueryFreq[%d], FTDPkgFreq[%d]",
			QueryFreq->QueryFreq, QueryFreq->FTDPkgFreq);
	}
}
void WriteAuthForbiddenIP(CThostFtdcAuthForbiddenIPField* AuthForbiddenIP)
{
	if(AuthForbiddenIP)
	{
		WriteLog(LogLevel::Info, "CThostFtdcAuthForbiddenIPField: IPAddress[%s]",
			AuthForbiddenIP->IPAddress);
	}
}
void WriteQryAuthForbiddenIP(CThostFtdcQryAuthForbiddenIPField* QryAuthForbiddenIP)
{
	if(QryAuthForbiddenIP)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryAuthForbiddenIPField: IPAddress[%s]",
			QryAuthForbiddenIP->IPAddress);
	}
}
void WriteSyncDelaySwapFrozen(CThostFtdcSyncDelaySwapFrozenField* SyncDelaySwapFrozen)
{
	if(SyncDelaySwapFrozen)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDelaySwapFrozenField: DelaySwapSeqNo[%s], BrokerID[%s], InvestorID[%s], FromCurrencyID[%s], FromRemainSwap[%f], IsManualSwap[%d]",
			SyncDelaySwapFrozen->DelaySwapSeqNo, SyncDelaySwapFrozen->BrokerID, SyncDelaySwapFrozen->InvestorID, SyncDelaySwapFrozen->FromCurrencyID, GetDoubleValue(SyncDelaySwapFrozen->FromRemainSwap), SyncDelaySwapFrozen->IsManualSwap);
	}
}
void WriteUserSystemInfo(CThostFtdcUserSystemInfoField* UserSystemInfo)
{
	if(UserSystemInfo)
	{
		WriteLog(LogLevel::Info, "CThostFtdcUserSystemInfoField: BrokerID[%s], UserID[%s], ClientSystemInfoLen[%d], ClientSystemInfo[%s], reserve1[%s], ClientIPPort[%d], ClientLoginTime[%s], ClientAppID[%s], ClientPublicIP[%s], ClientLoginRemark[%s]",
			UserSystemInfo->BrokerID, UserSystemInfo->UserID, UserSystemInfo->ClientSystemInfoLen, UserSystemInfo->ClientSystemInfo, UserSystemInfo->reserve1, UserSystemInfo->ClientIPPort, UserSystemInfo->ClientLoginTime, UserSystemInfo->ClientAppID, UserSystemInfo->ClientPublicIP, UserSystemInfo->ClientLoginRemark);
	}
}
void WriteAuthUserID(CThostFtdcAuthUserIDField* AuthUserID)
{
	if(AuthUserID)
	{
		WriteLog(LogLevel::Info, "CThostFtdcAuthUserIDField: BrokerID[%s], AppID[%s], UserID[%s], AuthType[%c]",
			AuthUserID->BrokerID, AuthUserID->AppID, AuthUserID->UserID, AuthUserID->AuthType);
	}
}
void WriteAuthIP(CThostFtdcAuthIPField* AuthIP)
{
	if(AuthIP)
	{
		WriteLog(LogLevel::Info, "CThostFtdcAuthIPField: BrokerID[%s], AppID[%s], IPAddress[%s]",
			AuthIP->BrokerID, AuthIP->AppID, AuthIP->IPAddress);
	}
}
void WriteQryClassifiedInstrument(CThostFtdcQryClassifiedInstrumentField* QryClassifiedInstrument)
{
	if(QryClassifiedInstrument)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryClassifiedInstrumentField: InstrumentID[%s], ExchangeID[%s], ExchangeInstID[%s], ProductID[%s], TradingType[%c], ClassType[%c]",
			QryClassifiedInstrument->InstrumentID, QryClassifiedInstrument->ExchangeID, QryClassifiedInstrument->ExchangeInstID, QryClassifiedInstrument->ProductID, QryClassifiedInstrument->TradingType, QryClassifiedInstrument->ClassType);
	}
}
void WriteQryCombPromotionParam(CThostFtdcQryCombPromotionParamField* QryCombPromotionParam)
{
	if(QryCombPromotionParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryCombPromotionParamField: ExchangeID[%s], InstrumentID[%s]",
			QryCombPromotionParam->ExchangeID, QryCombPromotionParam->InstrumentID);
	}
}
void WriteCombPromotionParam(CThostFtdcCombPromotionParamField* CombPromotionParam)
{
	if(CombPromotionParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcCombPromotionParamField: ExchangeID[%s], InstrumentID[%s], CombHedgeFlag[%s], Xparameter[%f]",
			CombPromotionParam->ExchangeID, CombPromotionParam->InstrumentID, CombPromotionParam->CombHedgeFlag, GetDoubleValue(CombPromotionParam->Xparameter));
	}
}
void WriteReqUserLoginSM(CThostFtdcReqUserLoginSMField* ReqUserLoginSM)
{
	if(ReqUserLoginSM)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReqUserLoginSMField: TradingDay[%s], BrokerID[%s], UserID[%s], Password[%s], UserProductInfo[%s], InterfaceProductInfo[%s], ProtocolInfo[%s], MacAddress[%s], OneTimePassword[%s], reserve1[%s], LoginRemark[%s], ClientIPPort[%d], ClientIPAddress[%s], BrokerName[%s], AuthCode[%s], AppID[%s], PIN[%s]",
			ReqUserLoginSM->TradingDay, ReqUserLoginSM->BrokerID, ReqUserLoginSM->UserID, ReqUserLoginSM->Password, ReqUserLoginSM->UserProductInfo, ReqUserLoginSM->InterfaceProductInfo, ReqUserLoginSM->ProtocolInfo, ReqUserLoginSM->MacAddress, ReqUserLoginSM->OneTimePassword, ReqUserLoginSM->reserve1, ReqUserLoginSM->LoginRemark, ReqUserLoginSM->ClientIPPort, ReqUserLoginSM->ClientIPAddress, ReqUserLoginSM->BrokerName, ReqUserLoginSM->AuthCode, ReqUserLoginSM->AppID, ReqUserLoginSM->PIN);
	}
}
void WriteQryRiskSettleInvstPosition(CThostFtdcQryRiskSettleInvstPositionField* QryRiskSettleInvstPosition)
{
	if(QryRiskSettleInvstPosition)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryRiskSettleInvstPositionField: BrokerID[%s], InvestorID[%s], InstrumentID[%s]",
			QryRiskSettleInvstPosition->BrokerID, QryRiskSettleInvstPosition->InvestorID, QryRiskSettleInvstPosition->InstrumentID);
	}
}
void WriteQryRiskSettleProductStatus(CThostFtdcQryRiskSettleProductStatusField* QryRiskSettleProductStatus)
{
	if(QryRiskSettleProductStatus)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryRiskSettleProductStatusField: ProductID[%s]",
			QryRiskSettleProductStatus->ProductID);
	}
}
void WriteRiskSettleInvstPosition(CThostFtdcRiskSettleInvstPositionField* RiskSettleInvstPosition)
{
	if(RiskSettleInvstPosition)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRiskSettleInvstPositionField: InstrumentID[%s], BrokerID[%s], InvestorID[%s], PosiDirection[%c], HedgeFlag[%c], PositionDate[%c], YdPosition[%d], Position[%d], LongFrozen[%d], ShortFrozen[%d], LongFrozenAmount[%f], ShortFrozenAmount[%f], OpenVolume[%d], CloseVolume[%d], OpenAmount[%f], CloseAmount[%f], PositionCost[%f], PreMargin[%f], UseMargin[%f], FrozenMargin[%f], FrozenCash[%f], FrozenCommission[%f], CashIn[%f], Commission[%f], CloseProfit[%f], PositionProfit[%f], PreSettlementPrice[%f], SettlementPrice[%f], TradingDay[%s], SettlementID[%d], OpenCost[%f], ExchangeMargin[%f], CombPosition[%d], CombLongFrozen[%d], CombShortFrozen[%d], CloseProfitByDate[%f], CloseProfitByTrade[%f], TodayPosition[%d], MarginRateByMoney[%f], MarginRateByVolume[%f], StrikeFrozen[%d], StrikeFrozenAmount[%f], AbandonFrozen[%d], ExchangeID[%s], YdStrikeFrozen[%d], InvestUnitID[%s], PositionCostOffset[%f], TasPosition[%d], TasPositionCost[%f]",
			RiskSettleInvstPosition->InstrumentID, RiskSettleInvstPosition->BrokerID, RiskSettleInvstPosition->InvestorID, RiskSettleInvstPosition->PosiDirection, RiskSettleInvstPosition->HedgeFlag, RiskSettleInvstPosition->PositionDate, RiskSettleInvstPosition->YdPosition, RiskSettleInvstPosition->Position, RiskSettleInvstPosition->LongFrozen, RiskSettleInvstPosition->ShortFrozen, GetDoubleValue(RiskSettleInvstPosition->LongFrozenAmount), GetDoubleValue(RiskSettleInvstPosition->ShortFrozenAmount), RiskSettleInvstPosition->OpenVolume, RiskSettleInvstPosition->CloseVolume, GetDoubleValue(RiskSettleInvstPosition->OpenAmount), GetDoubleValue(RiskSettleInvstPosition->CloseAmount), GetDoubleValue(RiskSettleInvstPosition->PositionCost), GetDoubleValue(RiskSettleInvstPosition->PreMargin), GetDoubleValue(RiskSettleInvstPosition->UseMargin), GetDoubleValue(RiskSettleInvstPosition->FrozenMargin), GetDoubleValue(RiskSettleInvstPosition->FrozenCash), GetDoubleValue(RiskSettleInvstPosition->FrozenCommission), GetDoubleValue(RiskSettleInvstPosition->CashIn), GetDoubleValue(RiskSettleInvstPosition->Commission), GetDoubleValue(RiskSettleInvstPosition->CloseProfit), GetDoubleValue(RiskSettleInvstPosition->PositionProfit), GetDoubleValue(RiskSettleInvstPosition->PreSettlementPrice), GetDoubleValue(RiskSettleInvstPosition->SettlementPrice), RiskSettleInvstPosition->TradingDay, RiskSettleInvstPosition->SettlementID, GetDoubleValue(RiskSettleInvstPosition->OpenCost), GetDoubleValue(RiskSettleInvstPosition->ExchangeMargin), RiskSettleInvstPosition->CombPosition, RiskSettleInvstPosition->CombLongFrozen, RiskSettleInvstPosition->CombShortFrozen, GetDoubleValue(RiskSettleInvstPosition->CloseProfitByDate), GetDoubleValue(RiskSettleInvstPosition->CloseProfitByTrade), RiskSettleInvstPosition->TodayPosition, GetDoubleValue(RiskSettleInvstPosition->MarginRateByMoney), GetDoubleValue(RiskSettleInvstPosition->MarginRateByVolume), RiskSettleInvstPosition->StrikeFrozen, GetDoubleValue(RiskSettleInvstPosition->StrikeFrozenAmount), RiskSettleInvstPosition->AbandonFrozen, RiskSettleInvstPosition->ExchangeID, RiskSettleInvstPosition->YdStrikeFrozen, RiskSettleInvstPosition->InvestUnitID, GetDoubleValue(RiskSettleInvstPosition->PositionCostOffset), RiskSettleInvstPosition->TasPosition, GetDoubleValue(RiskSettleInvstPosition->TasPositionCost));
	}
}
void WriteRiskSettleProductStatus(CThostFtdcRiskSettleProductStatusField* RiskSettleProductStatus)
{
	if(RiskSettleProductStatus)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRiskSettleProductStatusField: ExchangeID[%s], ProductID[%s], ProductStatus[%c]",
			RiskSettleProductStatus->ExchangeID, RiskSettleProductStatus->ProductID, RiskSettleProductStatus->ProductStatus);
	}
}
void WriteSyncDeltaInfo(CThostFtdcSyncDeltaInfoField* SyncDeltaInfo)
{
	if(SyncDeltaInfo)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaInfoField: SyncDeltaSequenceNo[%d], SyncDeltaStatus[%c], SyncDescription[%s], IsOnlyTrdDelta[%d]",
			SyncDeltaInfo->SyncDeltaSequenceNo, SyncDeltaInfo->SyncDeltaStatus, SyncDeltaInfo->SyncDescription, SyncDeltaInfo->IsOnlyTrdDelta);
	}
}
void WriteSyncDeltaProductStatus(CThostFtdcSyncDeltaProductStatusField* SyncDeltaProductStatus)
{
	if(SyncDeltaProductStatus)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaProductStatusField: SyncDeltaSequenceNo[%d], ExchangeID[%s], ProductID[%s], ProductStatus[%c]",
			SyncDeltaProductStatus->SyncDeltaSequenceNo, SyncDeltaProductStatus->ExchangeID, SyncDeltaProductStatus->ProductID, SyncDeltaProductStatus->ProductStatus);
	}
}
void WriteSyncDeltaInvstPosDtl(CThostFtdcSyncDeltaInvstPosDtlField* SyncDeltaInvstPosDtl)
{
	if(SyncDeltaInvstPosDtl)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaInvstPosDtlField: InstrumentID[%s], BrokerID[%s], InvestorID[%s], HedgeFlag[%c], Direction[%c], OpenDate[%s], TradeID[%s], Volume[%d], OpenPrice[%f], TradingDay[%s], SettlementID[%d], TradeType[%c], CombInstrumentID[%s], ExchangeID[%s], CloseProfitByDate[%f], CloseProfitByTrade[%f], PositionProfitByDate[%f], PositionProfitByTrade[%f], Margin[%f], ExchMargin[%f], MarginRateByMoney[%f], MarginRateByVolume[%f], LastSettlementPrice[%f], SettlementPrice[%f], CloseVolume[%d], CloseAmount[%f], TimeFirstVolume[%d], SpecPosiType[%c], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaInvstPosDtl->InstrumentID, SyncDeltaInvstPosDtl->BrokerID, SyncDeltaInvstPosDtl->InvestorID, SyncDeltaInvstPosDtl->HedgeFlag, SyncDeltaInvstPosDtl->Direction, SyncDeltaInvstPosDtl->OpenDate, SyncDeltaInvstPosDtl->TradeID, SyncDeltaInvstPosDtl->Volume, GetDoubleValue(SyncDeltaInvstPosDtl->OpenPrice), SyncDeltaInvstPosDtl->TradingDay, SyncDeltaInvstPosDtl->SettlementID, SyncDeltaInvstPosDtl->TradeType, SyncDeltaInvstPosDtl->CombInstrumentID, SyncDeltaInvstPosDtl->ExchangeID, GetDoubleValue(SyncDeltaInvstPosDtl->CloseProfitByDate), GetDoubleValue(SyncDeltaInvstPosDtl->CloseProfitByTrade), GetDoubleValue(SyncDeltaInvstPosDtl->PositionProfitByDate), GetDoubleValue(SyncDeltaInvstPosDtl->PositionProfitByTrade), GetDoubleValue(SyncDeltaInvstPosDtl->Margin), GetDoubleValue(SyncDeltaInvstPosDtl->ExchMargin), GetDoubleValue(SyncDeltaInvstPosDtl->MarginRateByMoney), GetDoubleValue(SyncDeltaInvstPosDtl->MarginRateByVolume), GetDoubleValue(SyncDeltaInvstPosDtl->LastSettlementPrice), GetDoubleValue(SyncDeltaInvstPosDtl->SettlementPrice), SyncDeltaInvstPosDtl->CloseVolume, GetDoubleValue(SyncDeltaInvstPosDtl->CloseAmount), SyncDeltaInvstPosDtl->TimeFirstVolume, SyncDeltaInvstPosDtl->SpecPosiType, SyncDeltaInvstPosDtl->ActionDirection, SyncDeltaInvstPosDtl->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaInvstPosCombDtl(CThostFtdcSyncDeltaInvstPosCombDtlField* SyncDeltaInvstPosCombDtl)
{
	if(SyncDeltaInvstPosCombDtl)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaInvstPosCombDtlField: TradingDay[%s], OpenDate[%s], ExchangeID[%s], SettlementID[%d], BrokerID[%s], InvestorID[%s], ComTradeID[%s], TradeID[%s], InstrumentID[%s], HedgeFlag[%c], Direction[%c], TotalAmt[%d], Margin[%f], ExchMargin[%f], MarginRateByMoney[%f], MarginRateByVolume[%f], LegID[%d], LegMultiple[%d], TradeGroupID[%d], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaInvstPosCombDtl->TradingDay, SyncDeltaInvstPosCombDtl->OpenDate, SyncDeltaInvstPosCombDtl->ExchangeID, SyncDeltaInvstPosCombDtl->SettlementID, SyncDeltaInvstPosCombDtl->BrokerID, SyncDeltaInvstPosCombDtl->InvestorID, SyncDeltaInvstPosCombDtl->ComTradeID, SyncDeltaInvstPosCombDtl->TradeID, SyncDeltaInvstPosCombDtl->InstrumentID, SyncDeltaInvstPosCombDtl->HedgeFlag, SyncDeltaInvstPosCombDtl->Direction, SyncDeltaInvstPosCombDtl->TotalAmt, GetDoubleValue(SyncDeltaInvstPosCombDtl->Margin), GetDoubleValue(SyncDeltaInvstPosCombDtl->ExchMargin), GetDoubleValue(SyncDeltaInvstPosCombDtl->MarginRateByMoney), GetDoubleValue(SyncDeltaInvstPosCombDtl->MarginRateByVolume), SyncDeltaInvstPosCombDtl->LegID, SyncDeltaInvstPosCombDtl->LegMultiple, SyncDeltaInvstPosCombDtl->TradeGroupID, SyncDeltaInvstPosCombDtl->ActionDirection, SyncDeltaInvstPosCombDtl->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaTradingAccount(CThostFtdcSyncDeltaTradingAccountField* SyncDeltaTradingAccount)
{
	if(SyncDeltaTradingAccount)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaTradingAccountField: BrokerID[%s], AccountID[%s], PreMortgage[%f], PreCredit[%f], PreDeposit[%f], PreBalance[%f], PreMargin[%f], InterestBase[%f], Interest[%f], Deposit[%f], Withdraw[%f], FrozenMargin[%f], FrozenCash[%f], FrozenCommission[%f], CurrMargin[%f], CashIn[%f], Commission[%f], CloseProfit[%f], PositionProfit[%f], Balance[%f], Available[%f], WithdrawQuota[%f], Reserve[%f], TradingDay[%s], SettlementID[%d], Credit[%f], Mortgage[%f], ExchangeMargin[%f], DeliveryMargin[%f], ExchangeDeliveryMargin[%f], ReserveBalance[%f], CurrencyID[%s], PreFundMortgageIn[%f], PreFundMortgageOut[%f], FundMortgageIn[%f], FundMortgageOut[%f], FundMortgageAvailable[%f], MortgageableFund[%f], SpecProductMargin[%f], SpecProductFrozenMargin[%f], SpecProductCommission[%f], SpecProductFrozenCommission[%f], SpecProductPositionProfit[%f], SpecProductCloseProfit[%f], SpecProductPositionProfitByAlg[%f], SpecProductExchangeMargin[%f], FrozenSwap[%f], RemainSwap[%f], SyncDeltaSequenceNo[%d]",
			SyncDeltaTradingAccount->BrokerID, SyncDeltaTradingAccount->AccountID, GetDoubleValue(SyncDeltaTradingAccount->PreMortgage), GetDoubleValue(SyncDeltaTradingAccount->PreCredit), GetDoubleValue(SyncDeltaTradingAccount->PreDeposit), GetDoubleValue(SyncDeltaTradingAccount->PreBalance), GetDoubleValue(SyncDeltaTradingAccount->PreMargin), GetDoubleValue(SyncDeltaTradingAccount->InterestBase), GetDoubleValue(SyncDeltaTradingAccount->Interest), GetDoubleValue(SyncDeltaTradingAccount->Deposit), GetDoubleValue(SyncDeltaTradingAccount->Withdraw), GetDoubleValue(SyncDeltaTradingAccount->FrozenMargin), GetDoubleValue(SyncDeltaTradingAccount->FrozenCash), GetDoubleValue(SyncDeltaTradingAccount->FrozenCommission), GetDoubleValue(SyncDeltaTradingAccount->CurrMargin), GetDoubleValue(SyncDeltaTradingAccount->CashIn), GetDoubleValue(SyncDeltaTradingAccount->Commission), GetDoubleValue(SyncDeltaTradingAccount->CloseProfit), GetDoubleValue(SyncDeltaTradingAccount->PositionProfit), GetDoubleValue(SyncDeltaTradingAccount->Balance), GetDoubleValue(SyncDeltaTradingAccount->Available), GetDoubleValue(SyncDeltaTradingAccount->WithdrawQuota), GetDoubleValue(SyncDeltaTradingAccount->Reserve), SyncDeltaTradingAccount->TradingDay, SyncDeltaTradingAccount->SettlementID, GetDoubleValue(SyncDeltaTradingAccount->Credit), GetDoubleValue(SyncDeltaTradingAccount->Mortgage), GetDoubleValue(SyncDeltaTradingAccount->ExchangeMargin), GetDoubleValue(SyncDeltaTradingAccount->DeliveryMargin), GetDoubleValue(SyncDeltaTradingAccount->ExchangeDeliveryMargin), GetDoubleValue(SyncDeltaTradingAccount->ReserveBalance), SyncDeltaTradingAccount->CurrencyID, GetDoubleValue(SyncDeltaTradingAccount->PreFundMortgageIn), GetDoubleValue(SyncDeltaTradingAccount->PreFundMortgageOut), GetDoubleValue(SyncDeltaTradingAccount->FundMortgageIn), GetDoubleValue(SyncDeltaTradingAccount->FundMortgageOut), GetDoubleValue(SyncDeltaTradingAccount->FundMortgageAvailable), GetDoubleValue(SyncDeltaTradingAccount->MortgageableFund), GetDoubleValue(SyncDeltaTradingAccount->SpecProductMargin), GetDoubleValue(SyncDeltaTradingAccount->SpecProductFrozenMargin), GetDoubleValue(SyncDeltaTradingAccount->SpecProductCommission), GetDoubleValue(SyncDeltaTradingAccount->SpecProductFrozenCommission), GetDoubleValue(SyncDeltaTradingAccount->SpecProductPositionProfit), GetDoubleValue(SyncDeltaTradingAccount->SpecProductCloseProfit), GetDoubleValue(SyncDeltaTradingAccount->SpecProductPositionProfitByAlg), GetDoubleValue(SyncDeltaTradingAccount->SpecProductExchangeMargin), GetDoubleValue(SyncDeltaTradingAccount->FrozenSwap), GetDoubleValue(SyncDeltaTradingAccount->RemainSwap), SyncDeltaTradingAccount->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaInitInvstMargin(CThostFtdcSyncDeltaInitInvstMarginField* SyncDeltaInitInvstMargin)
{
	if(SyncDeltaInitInvstMargin)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaInitInvstMarginField: BrokerID[%s], InvestorID[%s], LastRiskTotalInvstMargin[%f], LastRiskTotalExchMargin[%f], ThisSyncInvstMargin[%f], ThisSyncExchMargin[%f], RemainRiskInvstMargin[%f], RemainRiskExchMargin[%f], LastRiskSpecTotalInvstMargin[%f], LastRiskSpecTotalExchMargin[%f], ThisSyncSpecInvstMargin[%f], ThisSyncSpecExchMargin[%f], RemainRiskSpecInvstMargin[%f], RemainRiskSpecExchMargin[%f], SyncDeltaSequenceNo[%d]",
			SyncDeltaInitInvstMargin->BrokerID, SyncDeltaInitInvstMargin->InvestorID, GetDoubleValue(SyncDeltaInitInvstMargin->LastRiskTotalInvstMargin), GetDoubleValue(SyncDeltaInitInvstMargin->LastRiskTotalExchMargin), GetDoubleValue(SyncDeltaInitInvstMargin->ThisSyncInvstMargin), GetDoubleValue(SyncDeltaInitInvstMargin->ThisSyncExchMargin), GetDoubleValue(SyncDeltaInitInvstMargin->RemainRiskInvstMargin), GetDoubleValue(SyncDeltaInitInvstMargin->RemainRiskExchMargin), GetDoubleValue(SyncDeltaInitInvstMargin->LastRiskSpecTotalInvstMargin), GetDoubleValue(SyncDeltaInitInvstMargin->LastRiskSpecTotalExchMargin), GetDoubleValue(SyncDeltaInitInvstMargin->ThisSyncSpecInvstMargin), GetDoubleValue(SyncDeltaInitInvstMargin->ThisSyncSpecExchMargin), GetDoubleValue(SyncDeltaInitInvstMargin->RemainRiskSpecInvstMargin), GetDoubleValue(SyncDeltaInitInvstMargin->RemainRiskSpecExchMargin), SyncDeltaInitInvstMargin->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaDceCombInstrument(CThostFtdcSyncDeltaDceCombInstrumentField* SyncDeltaDceCombInstrument)
{
	if(SyncDeltaDceCombInstrument)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaDceCombInstrumentField: CombInstrumentID[%s], ExchangeID[%s], ExchangeInstID[%s], TradeGroupID[%d], CombHedgeFlag[%c], CombinationType[%c], Direction[%c], ProductID[%s], Xparameter[%f], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaDceCombInstrument->CombInstrumentID, SyncDeltaDceCombInstrument->ExchangeID, SyncDeltaDceCombInstrument->ExchangeInstID, SyncDeltaDceCombInstrument->TradeGroupID, SyncDeltaDceCombInstrument->CombHedgeFlag, SyncDeltaDceCombInstrument->CombinationType, SyncDeltaDceCombInstrument->Direction, SyncDeltaDceCombInstrument->ProductID, GetDoubleValue(SyncDeltaDceCombInstrument->Xparameter), SyncDeltaDceCombInstrument->ActionDirection, SyncDeltaDceCombInstrument->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaInvstMarginRate(CThostFtdcSyncDeltaInvstMarginRateField* SyncDeltaInvstMarginRate)
{
	if(SyncDeltaInvstMarginRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaInvstMarginRateField: InstrumentID[%s], InvestorRange[%c], BrokerID[%s], InvestorID[%s], HedgeFlag[%c], LongMarginRatioByMoney[%f], LongMarginRatioByVolume[%f], ShortMarginRatioByMoney[%f], ShortMarginRatioByVolume[%f], IsRelative[%d], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaInvstMarginRate->InstrumentID, SyncDeltaInvstMarginRate->InvestorRange, SyncDeltaInvstMarginRate->BrokerID, SyncDeltaInvstMarginRate->InvestorID, SyncDeltaInvstMarginRate->HedgeFlag, GetDoubleValue(SyncDeltaInvstMarginRate->LongMarginRatioByMoney), GetDoubleValue(SyncDeltaInvstMarginRate->LongMarginRatioByVolume), GetDoubleValue(SyncDeltaInvstMarginRate->ShortMarginRatioByMoney), GetDoubleValue(SyncDeltaInvstMarginRate->ShortMarginRatioByVolume), SyncDeltaInvstMarginRate->IsRelative, SyncDeltaInvstMarginRate->ActionDirection, SyncDeltaInvstMarginRate->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaExchMarginRate(CThostFtdcSyncDeltaExchMarginRateField* SyncDeltaExchMarginRate)
{
	if(SyncDeltaExchMarginRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaExchMarginRateField: BrokerID[%s], InstrumentID[%s], HedgeFlag[%c], LongMarginRatioByMoney[%f], LongMarginRatioByVolume[%f], ShortMarginRatioByMoney[%f], ShortMarginRatioByVolume[%f], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaExchMarginRate->BrokerID, SyncDeltaExchMarginRate->InstrumentID, SyncDeltaExchMarginRate->HedgeFlag, GetDoubleValue(SyncDeltaExchMarginRate->LongMarginRatioByMoney), GetDoubleValue(SyncDeltaExchMarginRate->LongMarginRatioByVolume), GetDoubleValue(SyncDeltaExchMarginRate->ShortMarginRatioByMoney), GetDoubleValue(SyncDeltaExchMarginRate->ShortMarginRatioByVolume), SyncDeltaExchMarginRate->ActionDirection, SyncDeltaExchMarginRate->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaOptExchMargin(CThostFtdcSyncDeltaOptExchMarginField* SyncDeltaOptExchMargin)
{
	if(SyncDeltaOptExchMargin)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaOptExchMarginField: BrokerID[%s], InstrumentID[%s], SShortMarginRatioByMoney[%f], SShortMarginRatioByVolume[%f], HShortMarginRatioByMoney[%f], HShortMarginRatioByVolume[%f], AShortMarginRatioByMoney[%f], AShortMarginRatioByVolume[%f], MShortMarginRatioByMoney[%f], MShortMarginRatioByVolume[%f], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaOptExchMargin->BrokerID, SyncDeltaOptExchMargin->InstrumentID, GetDoubleValue(SyncDeltaOptExchMargin->SShortMarginRatioByMoney), GetDoubleValue(SyncDeltaOptExchMargin->SShortMarginRatioByVolume), GetDoubleValue(SyncDeltaOptExchMargin->HShortMarginRatioByMoney), GetDoubleValue(SyncDeltaOptExchMargin->HShortMarginRatioByVolume), GetDoubleValue(SyncDeltaOptExchMargin->AShortMarginRatioByMoney), GetDoubleValue(SyncDeltaOptExchMargin->AShortMarginRatioByVolume), GetDoubleValue(SyncDeltaOptExchMargin->MShortMarginRatioByMoney), GetDoubleValue(SyncDeltaOptExchMargin->MShortMarginRatioByVolume), SyncDeltaOptExchMargin->ActionDirection, SyncDeltaOptExchMargin->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaOptInvstMargin(CThostFtdcSyncDeltaOptInvstMarginField* SyncDeltaOptInvstMargin)
{
	if(SyncDeltaOptInvstMargin)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaOptInvstMarginField: InstrumentID[%s], InvestorRange[%c], BrokerID[%s], InvestorID[%s], SShortMarginRatioByMoney[%f], SShortMarginRatioByVolume[%f], HShortMarginRatioByMoney[%f], HShortMarginRatioByVolume[%f], AShortMarginRatioByMoney[%f], AShortMarginRatioByVolume[%f], IsRelative[%d], MShortMarginRatioByMoney[%f], MShortMarginRatioByVolume[%f], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaOptInvstMargin->InstrumentID, SyncDeltaOptInvstMargin->InvestorRange, SyncDeltaOptInvstMargin->BrokerID, SyncDeltaOptInvstMargin->InvestorID, GetDoubleValue(SyncDeltaOptInvstMargin->SShortMarginRatioByMoney), GetDoubleValue(SyncDeltaOptInvstMargin->SShortMarginRatioByVolume), GetDoubleValue(SyncDeltaOptInvstMargin->HShortMarginRatioByMoney), GetDoubleValue(SyncDeltaOptInvstMargin->HShortMarginRatioByVolume), GetDoubleValue(SyncDeltaOptInvstMargin->AShortMarginRatioByMoney), GetDoubleValue(SyncDeltaOptInvstMargin->AShortMarginRatioByVolume), SyncDeltaOptInvstMargin->IsRelative, GetDoubleValue(SyncDeltaOptInvstMargin->MShortMarginRatioByMoney), GetDoubleValue(SyncDeltaOptInvstMargin->MShortMarginRatioByVolume), SyncDeltaOptInvstMargin->ActionDirection, SyncDeltaOptInvstMargin->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaInvstMarginRateUL(CThostFtdcSyncDeltaInvstMarginRateULField* SyncDeltaInvstMarginRateUL)
{
	if(SyncDeltaInvstMarginRateUL)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaInvstMarginRateULField: InstrumentID[%s], InvestorRange[%c], BrokerID[%s], InvestorID[%s], HedgeFlag[%c], LongMarginRatioByMoney[%f], LongMarginRatioByVolume[%f], ShortMarginRatioByMoney[%f], ShortMarginRatioByVolume[%f], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaInvstMarginRateUL->InstrumentID, SyncDeltaInvstMarginRateUL->InvestorRange, SyncDeltaInvstMarginRateUL->BrokerID, SyncDeltaInvstMarginRateUL->InvestorID, SyncDeltaInvstMarginRateUL->HedgeFlag, GetDoubleValue(SyncDeltaInvstMarginRateUL->LongMarginRatioByMoney), GetDoubleValue(SyncDeltaInvstMarginRateUL->LongMarginRatioByVolume), GetDoubleValue(SyncDeltaInvstMarginRateUL->ShortMarginRatioByMoney), GetDoubleValue(SyncDeltaInvstMarginRateUL->ShortMarginRatioByVolume), SyncDeltaInvstMarginRateUL->ActionDirection, SyncDeltaInvstMarginRateUL->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaOptInvstCommRate(CThostFtdcSyncDeltaOptInvstCommRateField* SyncDeltaOptInvstCommRate)
{
	if(SyncDeltaOptInvstCommRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaOptInvstCommRateField: InstrumentID[%s], InvestorRange[%c], BrokerID[%s], InvestorID[%s], OpenRatioByMoney[%f], OpenRatioByVolume[%f], CloseRatioByMoney[%f], CloseRatioByVolume[%f], CloseTodayRatioByMoney[%f], CloseTodayRatioByVolume[%f], StrikeRatioByMoney[%f], StrikeRatioByVolume[%f], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaOptInvstCommRate->InstrumentID, SyncDeltaOptInvstCommRate->InvestorRange, SyncDeltaOptInvstCommRate->BrokerID, SyncDeltaOptInvstCommRate->InvestorID, GetDoubleValue(SyncDeltaOptInvstCommRate->OpenRatioByMoney), GetDoubleValue(SyncDeltaOptInvstCommRate->OpenRatioByVolume), GetDoubleValue(SyncDeltaOptInvstCommRate->CloseRatioByMoney), GetDoubleValue(SyncDeltaOptInvstCommRate->CloseRatioByVolume), GetDoubleValue(SyncDeltaOptInvstCommRate->CloseTodayRatioByMoney), GetDoubleValue(SyncDeltaOptInvstCommRate->CloseTodayRatioByVolume), GetDoubleValue(SyncDeltaOptInvstCommRate->StrikeRatioByMoney), GetDoubleValue(SyncDeltaOptInvstCommRate->StrikeRatioByVolume), SyncDeltaOptInvstCommRate->ActionDirection, SyncDeltaOptInvstCommRate->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaInvstCommRate(CThostFtdcSyncDeltaInvstCommRateField* SyncDeltaInvstCommRate)
{
	if(SyncDeltaInvstCommRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaInvstCommRateField: InstrumentID[%s], InvestorRange[%c], BrokerID[%s], InvestorID[%s], OpenRatioByMoney[%f], OpenRatioByVolume[%f], CloseRatioByMoney[%f], CloseRatioByVolume[%f], CloseTodayRatioByMoney[%f], CloseTodayRatioByVolume[%f], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaInvstCommRate->InstrumentID, SyncDeltaInvstCommRate->InvestorRange, SyncDeltaInvstCommRate->BrokerID, SyncDeltaInvstCommRate->InvestorID, GetDoubleValue(SyncDeltaInvstCommRate->OpenRatioByMoney), GetDoubleValue(SyncDeltaInvstCommRate->OpenRatioByVolume), GetDoubleValue(SyncDeltaInvstCommRate->CloseRatioByMoney), GetDoubleValue(SyncDeltaInvstCommRate->CloseRatioByVolume), GetDoubleValue(SyncDeltaInvstCommRate->CloseTodayRatioByMoney), GetDoubleValue(SyncDeltaInvstCommRate->CloseTodayRatioByVolume), SyncDeltaInvstCommRate->ActionDirection, SyncDeltaInvstCommRate->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaProductExchRate(CThostFtdcSyncDeltaProductExchRateField* SyncDeltaProductExchRate)
{
	if(SyncDeltaProductExchRate)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaProductExchRateField: ProductID[%s], QuoteCurrencyID[%s], ExchangeRate[%f], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaProductExchRate->ProductID, SyncDeltaProductExchRate->QuoteCurrencyID, GetDoubleValue(SyncDeltaProductExchRate->ExchangeRate), SyncDeltaProductExchRate->ActionDirection, SyncDeltaProductExchRate->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaDepthMarketData(CThostFtdcSyncDeltaDepthMarketDataField* SyncDeltaDepthMarketData)
{
	if(SyncDeltaDepthMarketData)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaDepthMarketDataField: TradingDay[%s], InstrumentID[%s], ExchangeID[%s], ExchangeInstID[%s], LastPrice[%f], PreSettlementPrice[%f], PreClosePrice[%f], PreOpenInterest[%f], OpenPrice[%f], HighestPrice[%f], LowestPrice[%f], Volume[%d], Turnover[%f], OpenInterest[%f], ClosePrice[%f], SettlementPrice[%f], UpperLimitPrice[%f], LowerLimitPrice[%f], PreDelta[%f], CurrDelta[%f], UpdateTime[%s], UpdateMillisec[%d], BidPrice1[%f], BidVolume1[%d], AskPrice1[%f], AskVolume1[%d], BidPrice2[%f], BidVolume2[%d], AskPrice2[%f], AskVolume2[%d], BidPrice3[%f], BidVolume3[%d], AskPrice3[%f], AskVolume3[%d], BidPrice4[%f], BidVolume4[%d], AskPrice4[%f], AskVolume4[%d], BidPrice5[%f], BidVolume5[%d], AskPrice5[%f], AskVolume5[%d], AveragePrice[%f], ActionDay[%s], BandingUpperPrice[%f], BandingLowerPrice[%f], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaDepthMarketData->TradingDay, SyncDeltaDepthMarketData->InstrumentID, SyncDeltaDepthMarketData->ExchangeID, SyncDeltaDepthMarketData->ExchangeInstID, GetDoubleValue(SyncDeltaDepthMarketData->LastPrice), GetDoubleValue(SyncDeltaDepthMarketData->PreSettlementPrice), GetDoubleValue(SyncDeltaDepthMarketData->PreClosePrice), GetDoubleValue(SyncDeltaDepthMarketData->PreOpenInterest), GetDoubleValue(SyncDeltaDepthMarketData->OpenPrice), GetDoubleValue(SyncDeltaDepthMarketData->HighestPrice), GetDoubleValue(SyncDeltaDepthMarketData->LowestPrice), SyncDeltaDepthMarketData->Volume, GetDoubleValue(SyncDeltaDepthMarketData->Turnover), GetDoubleValue(SyncDeltaDepthMarketData->OpenInterest), GetDoubleValue(SyncDeltaDepthMarketData->ClosePrice), GetDoubleValue(SyncDeltaDepthMarketData->SettlementPrice), GetDoubleValue(SyncDeltaDepthMarketData->UpperLimitPrice), GetDoubleValue(SyncDeltaDepthMarketData->LowerLimitPrice), GetDoubleValue(SyncDeltaDepthMarketData->PreDelta), GetDoubleValue(SyncDeltaDepthMarketData->CurrDelta), SyncDeltaDepthMarketData->UpdateTime, SyncDeltaDepthMarketData->UpdateMillisec, GetDoubleValue(SyncDeltaDepthMarketData->BidPrice1), SyncDeltaDepthMarketData->BidVolume1, GetDoubleValue(SyncDeltaDepthMarketData->AskPrice1), SyncDeltaDepthMarketData->AskVolume1, GetDoubleValue(SyncDeltaDepthMarketData->BidPrice2), SyncDeltaDepthMarketData->BidVolume2, GetDoubleValue(SyncDeltaDepthMarketData->AskPrice2), SyncDeltaDepthMarketData->AskVolume2, GetDoubleValue(SyncDeltaDepthMarketData->BidPrice3), SyncDeltaDepthMarketData->BidVolume3, GetDoubleValue(SyncDeltaDepthMarketData->AskPrice3), SyncDeltaDepthMarketData->AskVolume3, GetDoubleValue(SyncDeltaDepthMarketData->BidPrice4), SyncDeltaDepthMarketData->BidVolume4, GetDoubleValue(SyncDeltaDepthMarketData->AskPrice4), SyncDeltaDepthMarketData->AskVolume4, GetDoubleValue(SyncDeltaDepthMarketData->BidPrice5), SyncDeltaDepthMarketData->BidVolume5, GetDoubleValue(SyncDeltaDepthMarketData->AskPrice5), SyncDeltaDepthMarketData->AskVolume5, GetDoubleValue(SyncDeltaDepthMarketData->AveragePrice), SyncDeltaDepthMarketData->ActionDay, GetDoubleValue(SyncDeltaDepthMarketData->BandingUpperPrice), GetDoubleValue(SyncDeltaDepthMarketData->BandingLowerPrice), SyncDeltaDepthMarketData->ActionDirection, SyncDeltaDepthMarketData->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaIndexPrice(CThostFtdcSyncDeltaIndexPriceField* SyncDeltaIndexPrice)
{
	if(SyncDeltaIndexPrice)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaIndexPriceField: BrokerID[%s], InstrumentID[%s], ClosePrice[%f], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaIndexPrice->BrokerID, SyncDeltaIndexPrice->InstrumentID, GetDoubleValue(SyncDeltaIndexPrice->ClosePrice), SyncDeltaIndexPrice->ActionDirection, SyncDeltaIndexPrice->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaEWarrantOffset(CThostFtdcSyncDeltaEWarrantOffsetField* SyncDeltaEWarrantOffset)
{
	if(SyncDeltaEWarrantOffset)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaEWarrantOffsetField: TradingDay[%s], BrokerID[%s], InvestorID[%s], ExchangeID[%s], InstrumentID[%s], Direction[%c], HedgeFlag[%c], Volume[%d], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaEWarrantOffset->TradingDay, SyncDeltaEWarrantOffset->BrokerID, SyncDeltaEWarrantOffset->InvestorID, SyncDeltaEWarrantOffset->ExchangeID, SyncDeltaEWarrantOffset->InstrumentID, SyncDeltaEWarrantOffset->Direction, SyncDeltaEWarrantOffset->HedgeFlag, SyncDeltaEWarrantOffset->Volume, SyncDeltaEWarrantOffset->ActionDirection, SyncDeltaEWarrantOffset->SyncDeltaSequenceNo);
	}
}
void WriteSPBMFutureParameter(CThostFtdcSPBMFutureParameterField* SPBMFutureParameter)
{
	if(SPBMFutureParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSPBMFutureParameterField: TradingDay[%s], ExchangeID[%s], InstrumentID[%s], ProdFamilyCode[%s], Cvf[%d], TimeRange[%c], MarginRate[%f], LockRateX[%f], AddOnRate[%f], PreSettlementPrice[%f], AddOnLockRateX2[%f]",
			SPBMFutureParameter->TradingDay, SPBMFutureParameter->ExchangeID, SPBMFutureParameter->InstrumentID, SPBMFutureParameter->ProdFamilyCode, SPBMFutureParameter->Cvf, SPBMFutureParameter->TimeRange, GetDoubleValue(SPBMFutureParameter->MarginRate), GetDoubleValue(SPBMFutureParameter->LockRateX), GetDoubleValue(SPBMFutureParameter->AddOnRate), GetDoubleValue(SPBMFutureParameter->PreSettlementPrice), GetDoubleValue(SPBMFutureParameter->AddOnLockRateX2));
	}
}
void WriteSPBMOptionParameter(CThostFtdcSPBMOptionParameterField* SPBMOptionParameter)
{
	if(SPBMOptionParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSPBMOptionParameterField: TradingDay[%s], ExchangeID[%s], InstrumentID[%s], ProdFamilyCode[%s], Cvf[%d], DownPrice[%f], Delta[%f], SlimiDelta[%f], PreSettlementPrice[%f]",
			SPBMOptionParameter->TradingDay, SPBMOptionParameter->ExchangeID, SPBMOptionParameter->InstrumentID, SPBMOptionParameter->ProdFamilyCode, SPBMOptionParameter->Cvf, GetDoubleValue(SPBMOptionParameter->DownPrice), GetDoubleValue(SPBMOptionParameter->Delta), GetDoubleValue(SPBMOptionParameter->SlimiDelta), GetDoubleValue(SPBMOptionParameter->PreSettlementPrice));
	}
}
void WriteSPBMIntraParameter(CThostFtdcSPBMIntraParameterField* SPBMIntraParameter)
{
	if(SPBMIntraParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSPBMIntraParameterField: TradingDay[%s], ExchangeID[%s], ProdFamilyCode[%s], IntraRateY[%f], AddOnIntraRateY2[%f]",
			SPBMIntraParameter->TradingDay, SPBMIntraParameter->ExchangeID, SPBMIntraParameter->ProdFamilyCode, GetDoubleValue(SPBMIntraParameter->IntraRateY), GetDoubleValue(SPBMIntraParameter->AddOnIntraRateY2));
	}
}
void WriteSPBMInterParameter(CThostFtdcSPBMInterParameterField* SPBMInterParameter)
{
	if(SPBMInterParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSPBMInterParameterField: TradingDay[%s], ExchangeID[%s], SpreadId[%d], InterRateZ[%f], Leg1ProdFamilyCode[%s], Leg2ProdFamilyCode[%s]",
			SPBMInterParameter->TradingDay, SPBMInterParameter->ExchangeID, SPBMInterParameter->SpreadId, GetDoubleValue(SPBMInterParameter->InterRateZ), SPBMInterParameter->Leg1ProdFamilyCode, SPBMInterParameter->Leg2ProdFamilyCode);
	}
}
void WriteSyncSPBMParameterEnd(CThostFtdcSyncSPBMParameterEndField* SyncSPBMParameterEnd)
{
	if(SyncSPBMParameterEnd)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncSPBMParameterEndField: TradingDay[%s]",
			SyncSPBMParameterEnd->TradingDay);
	}
}
void WriteQrySPBMFutureParameter(CThostFtdcQrySPBMFutureParameterField* QrySPBMFutureParameter)
{
	if(QrySPBMFutureParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQrySPBMFutureParameterField: ExchangeID[%s], InstrumentID[%s], ProdFamilyCode[%s]",
			QrySPBMFutureParameter->ExchangeID, QrySPBMFutureParameter->InstrumentID, QrySPBMFutureParameter->ProdFamilyCode);
	}
}
void WriteQrySPBMOptionParameter(CThostFtdcQrySPBMOptionParameterField* QrySPBMOptionParameter)
{
	if(QrySPBMOptionParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQrySPBMOptionParameterField: ExchangeID[%s], InstrumentID[%s], ProdFamilyCode[%s]",
			QrySPBMOptionParameter->ExchangeID, QrySPBMOptionParameter->InstrumentID, QrySPBMOptionParameter->ProdFamilyCode);
	}
}
void WriteQrySPBMIntraParameter(CThostFtdcQrySPBMIntraParameterField* QrySPBMIntraParameter)
{
	if(QrySPBMIntraParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQrySPBMIntraParameterField: ExchangeID[%s], ProdFamilyCode[%s]",
			QrySPBMIntraParameter->ExchangeID, QrySPBMIntraParameter->ProdFamilyCode);
	}
}
void WriteQrySPBMInterParameter(CThostFtdcQrySPBMInterParameterField* QrySPBMInterParameter)
{
	if(QrySPBMInterParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQrySPBMInterParameterField: ExchangeID[%s], Leg1ProdFamilyCode[%s], Leg2ProdFamilyCode[%s]",
			QrySPBMInterParameter->ExchangeID, QrySPBMInterParameter->Leg1ProdFamilyCode, QrySPBMInterParameter->Leg2ProdFamilyCode);
	}
}
void WriteSPBMPortfDefinition(CThostFtdcSPBMPortfDefinitionField* SPBMPortfDefinition)
{
	if(SPBMPortfDefinition)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSPBMPortfDefinitionField: ExchangeID[%s], PortfolioDefID[%d], ProdFamilyCode[%s], IsSPBM[%d]",
			SPBMPortfDefinition->ExchangeID, SPBMPortfDefinition->PortfolioDefID, SPBMPortfDefinition->ProdFamilyCode, SPBMPortfDefinition->IsSPBM);
	}
}
void WriteSPBMInvestorPortfDef(CThostFtdcSPBMInvestorPortfDefField* SPBMInvestorPortfDef)
{
	if(SPBMInvestorPortfDef)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSPBMInvestorPortfDefField: ExchangeID[%s], BrokerID[%s], InvestorID[%s], PortfolioDefID[%d]",
			SPBMInvestorPortfDef->ExchangeID, SPBMInvestorPortfDef->BrokerID, SPBMInvestorPortfDef->InvestorID, SPBMInvestorPortfDef->PortfolioDefID);
	}
}
void WriteInvestorPortfMarginRatio(CThostFtdcInvestorPortfMarginRatioField* InvestorPortfMarginRatio)
{
	if(InvestorPortfMarginRatio)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInvestorPortfMarginRatioField: InvestorRange[%c], BrokerID[%s], InvestorID[%s], ExchangeID[%s], MarginRatio[%f], ProductGroupID[%s]",
			InvestorPortfMarginRatio->InvestorRange, InvestorPortfMarginRatio->BrokerID, InvestorPortfMarginRatio->InvestorID, InvestorPortfMarginRatio->ExchangeID, GetDoubleValue(InvestorPortfMarginRatio->MarginRatio), InvestorPortfMarginRatio->ProductGroupID);
	}
}
void WriteQrySPBMPortfDefinition(CThostFtdcQrySPBMPortfDefinitionField* QrySPBMPortfDefinition)
{
	if(QrySPBMPortfDefinition)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQrySPBMPortfDefinitionField: ExchangeID[%s], PortfolioDefID[%d], ProdFamilyCode[%s]",
			QrySPBMPortfDefinition->ExchangeID, QrySPBMPortfDefinition->PortfolioDefID, QrySPBMPortfDefinition->ProdFamilyCode);
	}
}
void WriteQrySPBMInvestorPortfDef(CThostFtdcQrySPBMInvestorPortfDefField* QrySPBMInvestorPortfDef)
{
	if(QrySPBMInvestorPortfDef)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQrySPBMInvestorPortfDefField: ExchangeID[%s], BrokerID[%s], InvestorID[%s]",
			QrySPBMInvestorPortfDef->ExchangeID, QrySPBMInvestorPortfDef->BrokerID, QrySPBMInvestorPortfDef->InvestorID);
	}
}
void WriteQryInvestorPortfMarginRatio(CThostFtdcQryInvestorPortfMarginRatioField* QryInvestorPortfMarginRatio)
{
	if(QryInvestorPortfMarginRatio)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryInvestorPortfMarginRatioField: BrokerID[%s], InvestorID[%s], ExchangeID[%s], ProductGroupID[%s]",
			QryInvestorPortfMarginRatio->BrokerID, QryInvestorPortfMarginRatio->InvestorID, QryInvestorPortfMarginRatio->ExchangeID, QryInvestorPortfMarginRatio->ProductGroupID);
	}
}
void WriteInvestorProdSPBMDetail(CThostFtdcInvestorProdSPBMDetailField* InvestorProdSPBMDetail)
{
	if(InvestorProdSPBMDetail)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInvestorProdSPBMDetailField: ExchangeID[%s], BrokerID[%s], InvestorID[%s], ProdFamilyCode[%s], IntraInstrMargin[%f], BCollectingMargin[%f], SCollectingMargin[%f], IntraProdMargin[%f], NetMargin[%f], InterProdMargin[%f], SingleMargin[%f], AddOnMargin[%f], DeliveryMargin[%f], CallOptionMinRisk[%f], PutOptionMinRisk[%f], OptionMinRisk[%f], OptionValueOffset[%f], OptionRoyalty[%f], RealOptionValueOffset[%f], Margin[%f], ExchMargin[%f]",
			InvestorProdSPBMDetail->ExchangeID, InvestorProdSPBMDetail->BrokerID, InvestorProdSPBMDetail->InvestorID, InvestorProdSPBMDetail->ProdFamilyCode, GetDoubleValue(InvestorProdSPBMDetail->IntraInstrMargin), GetDoubleValue(InvestorProdSPBMDetail->BCollectingMargin), GetDoubleValue(InvestorProdSPBMDetail->SCollectingMargin), GetDoubleValue(InvestorProdSPBMDetail->IntraProdMargin), GetDoubleValue(InvestorProdSPBMDetail->NetMargin), GetDoubleValue(InvestorProdSPBMDetail->InterProdMargin), GetDoubleValue(InvestorProdSPBMDetail->SingleMargin), GetDoubleValue(InvestorProdSPBMDetail->AddOnMargin), GetDoubleValue(InvestorProdSPBMDetail->DeliveryMargin), GetDoubleValue(InvestorProdSPBMDetail->CallOptionMinRisk), GetDoubleValue(InvestorProdSPBMDetail->PutOptionMinRisk), GetDoubleValue(InvestorProdSPBMDetail->OptionMinRisk), GetDoubleValue(InvestorProdSPBMDetail->OptionValueOffset), GetDoubleValue(InvestorProdSPBMDetail->OptionRoyalty), GetDoubleValue(InvestorProdSPBMDetail->RealOptionValueOffset), GetDoubleValue(InvestorProdSPBMDetail->Margin), GetDoubleValue(InvestorProdSPBMDetail->ExchMargin));
	}
}
void WriteQryInvestorProdSPBMDetail(CThostFtdcQryInvestorProdSPBMDetailField* QryInvestorProdSPBMDetail)
{
	if(QryInvestorProdSPBMDetail)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryInvestorProdSPBMDetailField: ExchangeID[%s], BrokerID[%s], InvestorID[%s], ProdFamilyCode[%s]",
			QryInvestorProdSPBMDetail->ExchangeID, QryInvestorProdSPBMDetail->BrokerID, QryInvestorProdSPBMDetail->InvestorID, QryInvestorProdSPBMDetail->ProdFamilyCode);
	}
}
void WritePortfTradeParamSetting(CThostFtdcPortfTradeParamSettingField* PortfTradeParamSetting)
{
	if(PortfTradeParamSetting)
	{
		WriteLog(LogLevel::Info, "CThostFtdcPortfTradeParamSettingField: ExchangeID[%s], BrokerID[%s], InvestorID[%s], Portfolio[%c], IsActionVerify[%d], IsCloseVerify[%d]",
			PortfTradeParamSetting->ExchangeID, PortfTradeParamSetting->BrokerID, PortfTradeParamSetting->InvestorID, PortfTradeParamSetting->Portfolio, PortfTradeParamSetting->IsActionVerify, PortfTradeParamSetting->IsCloseVerify);
	}
}
void WriteInvestorTradingRight(CThostFtdcInvestorTradingRightField* InvestorTradingRight)
{
	if(InvestorTradingRight)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInvestorTradingRightField: BrokerID[%s], InvestorID[%s], InvstTradingRight[%c]",
			InvestorTradingRight->BrokerID, InvestorTradingRight->InvestorID, InvestorTradingRight->InvstTradingRight);
	}
}
void WriteMortgageParam(CThostFtdcMortgageParamField* MortgageParam)
{
	if(MortgageParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcMortgageParamField: BrokerID[%s], AccountID[%s], MortgageBalance[%f], CheckMortgageRatio[%d]",
			MortgageParam->BrokerID, MortgageParam->AccountID, GetDoubleValue(MortgageParam->MortgageBalance), MortgageParam->CheckMortgageRatio);
	}
}
void WriteWithDrawParam(CThostFtdcWithDrawParamField* WithDrawParam)
{
	if(WithDrawParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcWithDrawParamField: BrokerID[%s], AccountID[%s], WithDrawParamID[%c], WithDrawParamValue[%s]",
			WithDrawParam->BrokerID, WithDrawParam->AccountID, WithDrawParam->WithDrawParamID, WithDrawParam->WithDrawParamValue);
	}
}
void WriteThostUserFunction(CThostFtdcThostUserFunctionField* ThostUserFunction)
{
	if(ThostUserFunction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcThostUserFunctionField: BrokerID[%s], UserID[%s], ThostFunctionCode[%d]",
			ThostUserFunction->BrokerID, ThostUserFunction->UserID, ThostUserFunction->ThostFunctionCode);
	}
}
void WriteQryThostUserFunction(CThostFtdcQryThostUserFunctionField* QryThostUserFunction)
{
	if(QryThostUserFunction)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryThostUserFunctionField: BrokerID[%s], UserID[%s]",
			QryThostUserFunction->BrokerID, QryThostUserFunction->UserID);
	}
}
void WriteSPBMAddOnInterParameter(CThostFtdcSPBMAddOnInterParameterField* SPBMAddOnInterParameter)
{
	if(SPBMAddOnInterParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSPBMAddOnInterParameterField: TradingDay[%s], ExchangeID[%s], SpreadId[%d], AddOnInterRateZ2[%f], Leg1ProdFamilyCode[%s], Leg2ProdFamilyCode[%s]",
			SPBMAddOnInterParameter->TradingDay, SPBMAddOnInterParameter->ExchangeID, SPBMAddOnInterParameter->SpreadId, GetDoubleValue(SPBMAddOnInterParameter->AddOnInterRateZ2), SPBMAddOnInterParameter->Leg1ProdFamilyCode, SPBMAddOnInterParameter->Leg2ProdFamilyCode);
	}
}
void WriteQrySPBMAddOnInterParameter(CThostFtdcQrySPBMAddOnInterParameterField* QrySPBMAddOnInterParameter)
{
	if(QrySPBMAddOnInterParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQrySPBMAddOnInterParameterField: ExchangeID[%s], Leg1ProdFamilyCode[%s], Leg2ProdFamilyCode[%s]",
			QrySPBMAddOnInterParameter->ExchangeID, QrySPBMAddOnInterParameter->Leg1ProdFamilyCode, QrySPBMAddOnInterParameter->Leg2ProdFamilyCode);
	}
}
void WriteQryInvestorCommoditySPMMMargin(CThostFtdcQryInvestorCommoditySPMMMarginField* QryInvestorCommoditySPMMMargin)
{
	if(QryInvestorCommoditySPMMMargin)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryInvestorCommoditySPMMMarginField: BrokerID[%s], InvestorID[%s], CommodityID[%s]",
			QryInvestorCommoditySPMMMargin->BrokerID, QryInvestorCommoditySPMMMargin->InvestorID, QryInvestorCommoditySPMMMargin->CommodityID);
	}
}
void WriteQryInvestorCommodityGroupSPMMMargin(CThostFtdcQryInvestorCommodityGroupSPMMMarginField* QryInvestorCommodityGroupSPMMMargin)
{
	if(QryInvestorCommodityGroupSPMMMargin)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryInvestorCommodityGroupSPMMMarginField: BrokerID[%s], InvestorID[%s], CommodityGroupID[%s]",
			QryInvestorCommodityGroupSPMMMargin->BrokerID, QryInvestorCommodityGroupSPMMMargin->InvestorID, QryInvestorCommodityGroupSPMMMargin->CommodityGroupID);
	}
}
void WriteQrySPMMInstParam(CThostFtdcQrySPMMInstParamField* QrySPMMInstParam)
{
	if(QrySPMMInstParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQrySPMMInstParamField: InstrumentID[%s]",
			QrySPMMInstParam->InstrumentID);
	}
}
void WriteQrySPMMProductParam(CThostFtdcQrySPMMProductParamField* QrySPMMProductParam)
{
	if(QrySPMMProductParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQrySPMMProductParamField: ProductID[%s]",
			QrySPMMProductParam->ProductID);
	}
}
void WriteInvestorCommoditySPMMMargin(CThostFtdcInvestorCommoditySPMMMarginField* InvestorCommoditySPMMMargin)
{
	if(InvestorCommoditySPMMMargin)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInvestorCommoditySPMMMarginField: ExchangeID[%s], BrokerID[%s], InvestorID[%s], CommodityID[%s], MarginBeforeDiscount[%f], MarginNoDiscount[%f], LongPosRisk[%f], LongOpenFrozenRisk[%f], LongCloseFrozenRisk[%f], ShortPosRisk[%f], ShortOpenFrozenRisk[%f], ShortCloseFrozenRisk[%f], IntraCommodityRate[%f], OptionDiscountRate[%f], PosDiscount[%f], OpenFrozenDiscount[%f], NetRisk[%f], CloseFrozenMargin[%f], FrozenCommission[%f], Commission[%f], FrozenCash[%f], CashIn[%f], StrikeFrozenMargin[%f]",
			InvestorCommoditySPMMMargin->ExchangeID, InvestorCommoditySPMMMargin->BrokerID, InvestorCommoditySPMMMargin->InvestorID, InvestorCommoditySPMMMargin->CommodityID, GetDoubleValue(InvestorCommoditySPMMMargin->MarginBeforeDiscount), GetDoubleValue(InvestorCommoditySPMMMargin->MarginNoDiscount), GetDoubleValue(InvestorCommoditySPMMMargin->LongPosRisk), GetDoubleValue(InvestorCommoditySPMMMargin->LongOpenFrozenRisk), GetDoubleValue(InvestorCommoditySPMMMargin->LongCloseFrozenRisk), GetDoubleValue(InvestorCommoditySPMMMargin->ShortPosRisk), GetDoubleValue(InvestorCommoditySPMMMargin->ShortOpenFrozenRisk), GetDoubleValue(InvestorCommoditySPMMMargin->ShortCloseFrozenRisk), GetDoubleValue(InvestorCommoditySPMMMargin->IntraCommodityRate), GetDoubleValue(InvestorCommoditySPMMMargin->OptionDiscountRate), GetDoubleValue(InvestorCommoditySPMMMargin->PosDiscount), GetDoubleValue(InvestorCommoditySPMMMargin->OpenFrozenDiscount), GetDoubleValue(InvestorCommoditySPMMMargin->NetRisk), GetDoubleValue(InvestorCommoditySPMMMargin->CloseFrozenMargin), GetDoubleValue(InvestorCommoditySPMMMargin->FrozenCommission), GetDoubleValue(InvestorCommoditySPMMMargin->Commission), GetDoubleValue(InvestorCommoditySPMMMargin->FrozenCash), GetDoubleValue(InvestorCommoditySPMMMargin->CashIn), GetDoubleValue(InvestorCommoditySPMMMargin->StrikeFrozenMargin));
	}
}
void WriteInvestorCommodityGroupSPMMMargin(CThostFtdcInvestorCommodityGroupSPMMMarginField* InvestorCommodityGroupSPMMMargin)
{
	if(InvestorCommodityGroupSPMMMargin)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInvestorCommodityGroupSPMMMarginField: ExchangeID[%s], BrokerID[%s], InvestorID[%s], CommodityGroupID[%s], MarginBeforeDiscount[%f], MarginNoDiscount[%f], LongRisk[%f], ShortRisk[%f], CloseFrozenMargin[%f], InterCommodityRate[%f], MiniMarginRatio[%f], AdjustRatio[%f], IntraCommodityDiscount[%f], InterCommodityDiscount[%f], ExchMargin[%f], InvestorMargin[%f], FrozenCommission[%f], Commission[%f], FrozenCash[%f], CashIn[%f], StrikeFrozenMargin[%f]",
			InvestorCommodityGroupSPMMMargin->ExchangeID, InvestorCommodityGroupSPMMMargin->BrokerID, InvestorCommodityGroupSPMMMargin->InvestorID, InvestorCommodityGroupSPMMMargin->CommodityGroupID, GetDoubleValue(InvestorCommodityGroupSPMMMargin->MarginBeforeDiscount), GetDoubleValue(InvestorCommodityGroupSPMMMargin->MarginNoDiscount), GetDoubleValue(InvestorCommodityGroupSPMMMargin->LongRisk), GetDoubleValue(InvestorCommodityGroupSPMMMargin->ShortRisk), GetDoubleValue(InvestorCommodityGroupSPMMMargin->CloseFrozenMargin), GetDoubleValue(InvestorCommodityGroupSPMMMargin->InterCommodityRate), GetDoubleValue(InvestorCommodityGroupSPMMMargin->MiniMarginRatio), GetDoubleValue(InvestorCommodityGroupSPMMMargin->AdjustRatio), GetDoubleValue(InvestorCommodityGroupSPMMMargin->IntraCommodityDiscount), GetDoubleValue(InvestorCommodityGroupSPMMMargin->InterCommodityDiscount), GetDoubleValue(InvestorCommodityGroupSPMMMargin->ExchMargin), GetDoubleValue(InvestorCommodityGroupSPMMMargin->InvestorMargin), GetDoubleValue(InvestorCommodityGroupSPMMMargin->FrozenCommission), GetDoubleValue(InvestorCommodityGroupSPMMMargin->Commission), GetDoubleValue(InvestorCommodityGroupSPMMMargin->FrozenCash), GetDoubleValue(InvestorCommodityGroupSPMMMargin->CashIn), GetDoubleValue(InvestorCommodityGroupSPMMMargin->StrikeFrozenMargin));
	}
}
void WriteSPMMInstParam(CThostFtdcSPMMInstParamField* SPMMInstParam)
{
	if(SPMMInstParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSPMMInstParamField: ExchangeID[%s], InstrumentID[%s], InstMarginCalID[%c], CommodityID[%s], CommodityGroupID[%s]",
			SPMMInstParam->ExchangeID, SPMMInstParam->InstrumentID, SPMMInstParam->InstMarginCalID, SPMMInstParam->CommodityID, SPMMInstParam->CommodityGroupID);
	}
}
void WriteSPMMProductParam(CThostFtdcSPMMProductParamField* SPMMProductParam)
{
	if(SPMMProductParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSPMMProductParamField: ExchangeID[%s], ProductID[%s], CommodityID[%s], CommodityGroupID[%s]",
			SPMMProductParam->ExchangeID, SPMMProductParam->ProductID, SPMMProductParam->CommodityID, SPMMProductParam->CommodityGroupID);
	}
}
void WriteQryTraderAssign(CThostFtdcQryTraderAssignField* QryTraderAssign)
{
	if(QryTraderAssign)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryTraderAssignField: TraderID[%s]",
			QryTraderAssign->TraderID);
	}
}
void WriteTraderAssign(CThostFtdcTraderAssignField* TraderAssign)
{
	if(TraderAssign)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTraderAssignField: BrokerID[%s], ExchangeID[%s], TraderID[%s], ParticipantID[%s], DRIdentityID[%d]",
			TraderAssign->BrokerID, TraderAssign->ExchangeID, TraderAssign->TraderID, TraderAssign->ParticipantID, TraderAssign->DRIdentityID);
	}
}
void WriteInvestorInfoCntSetting(CThostFtdcInvestorInfoCntSettingField* InvestorInfoCntSetting)
{
	if(InvestorInfoCntSetting)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInvestorInfoCntSettingField: ExchangeID[%s], BrokerID[%s], InvestorID[%s], ProductID[%s], IsCalInfoComm[%d], IsLimitInfoMax[%d], InfoMaxLimit[%d]",
			InvestorInfoCntSetting->ExchangeID, InvestorInfoCntSetting->BrokerID, InvestorInfoCntSetting->InvestorID, InvestorInfoCntSetting->ProductID, InvestorInfoCntSetting->IsCalInfoComm, InvestorInfoCntSetting->IsLimitInfoMax, InvestorInfoCntSetting->InfoMaxLimit);
	}
}
void WriteRCAMSCombProductInfo(CThostFtdcRCAMSCombProductInfoField* RCAMSCombProductInfo)
{
	if(RCAMSCombProductInfo)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRCAMSCombProductInfoField: TradingDay[%s], ExchangeID[%s], ProductID[%s], CombProductID[%s], ProductGroupID[%s]",
			RCAMSCombProductInfo->TradingDay, RCAMSCombProductInfo->ExchangeID, RCAMSCombProductInfo->ProductID, RCAMSCombProductInfo->CombProductID, RCAMSCombProductInfo->ProductGroupID);
	}
}
void WriteRCAMSInstrParameter(CThostFtdcRCAMSInstrParameterField* RCAMSInstrParameter)
{
	if(RCAMSInstrParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRCAMSInstrParameterField: TradingDay[%s], ExchangeID[%s], ProductID[%s], HedgeRate[%f]",
			RCAMSInstrParameter->TradingDay, RCAMSInstrParameter->ExchangeID, RCAMSInstrParameter->ProductID, GetDoubleValue(RCAMSInstrParameter->HedgeRate));
	}
}
void WriteRCAMSIntraParameter(CThostFtdcRCAMSIntraParameterField* RCAMSIntraParameter)
{
	if(RCAMSIntraParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRCAMSIntraParameterField: TradingDay[%s], ExchangeID[%s], CombProductID[%s], HedgeRate[%f]",
			RCAMSIntraParameter->TradingDay, RCAMSIntraParameter->ExchangeID, RCAMSIntraParameter->CombProductID, GetDoubleValue(RCAMSIntraParameter->HedgeRate));
	}
}
void WriteRCAMSInterParameter(CThostFtdcRCAMSInterParameterField* RCAMSInterParameter)
{
	if(RCAMSInterParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRCAMSInterParameterField: TradingDay[%s], ExchangeID[%s], ProductGroupID[%s], Priority[%d], CreditRate[%f], CombProduct1[%s], CombProduct2[%s]",
			RCAMSInterParameter->TradingDay, RCAMSInterParameter->ExchangeID, RCAMSInterParameter->ProductGroupID, RCAMSInterParameter->Priority, GetDoubleValue(RCAMSInterParameter->CreditRate), RCAMSInterParameter->CombProduct1, RCAMSInterParameter->CombProduct2);
	}
}
void WriteRCAMSShortOptAdjustParam(CThostFtdcRCAMSShortOptAdjustParamField* RCAMSShortOptAdjustParam)
{
	if(RCAMSShortOptAdjustParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRCAMSShortOptAdjustParamField: TradingDay[%s], ExchangeID[%s], CombProductID[%s], HedgeFlag[%c], AdjustValue[%f]",
			RCAMSShortOptAdjustParam->TradingDay, RCAMSShortOptAdjustParam->ExchangeID, RCAMSShortOptAdjustParam->CombProductID, RCAMSShortOptAdjustParam->HedgeFlag, GetDoubleValue(RCAMSShortOptAdjustParam->AdjustValue));
	}
}
void WriteRCAMSInvestorCombPosition(CThostFtdcRCAMSInvestorCombPositionField* RCAMSInvestorCombPosition)
{
	if(RCAMSInvestorCombPosition)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRCAMSInvestorCombPositionField: ExchangeID[%s], BrokerID[%s], InvestorID[%s], InstrumentID[%s], HedgeFlag[%c], PosiDirection[%c], CombInstrumentID[%s], LegID[%d], ExchangeInstID[%s], TotalAmt[%d], ExchMargin[%f], Margin[%f]",
			RCAMSInvestorCombPosition->ExchangeID, RCAMSInvestorCombPosition->BrokerID, RCAMSInvestorCombPosition->InvestorID, RCAMSInvestorCombPosition->InstrumentID, RCAMSInvestorCombPosition->HedgeFlag, RCAMSInvestorCombPosition->PosiDirection, RCAMSInvestorCombPosition->CombInstrumentID, RCAMSInvestorCombPosition->LegID, RCAMSInvestorCombPosition->ExchangeInstID, RCAMSInvestorCombPosition->TotalAmt, GetDoubleValue(RCAMSInvestorCombPosition->ExchMargin), GetDoubleValue(RCAMSInvestorCombPosition->Margin));
	}
}
void WriteInvestorProdRCAMSMargin(CThostFtdcInvestorProdRCAMSMarginField* InvestorProdRCAMSMargin)
{
	if(InvestorProdRCAMSMargin)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInvestorProdRCAMSMarginField: ExchangeID[%s], BrokerID[%s], InvestorID[%s], CombProductID[%s], HedgeFlag[%c], ProductGroupID[%s], RiskBeforeDiscount[%f], IntraInstrRisk[%f], BPosRisk[%f], SPosRisk[%f], IntraProdRisk[%f], NetRisk[%f], InterProdRisk[%f], ShortOptRiskAdj[%f], OptionRoyalty[%f], MMSACloseFrozenMargin[%f], CloseCombFrozenMargin[%f], CloseFrozenMargin[%f], MMSAOpenFrozenMargin[%f], DeliveryOpenFrozenMargin[%f], OpenFrozenMargin[%f], UseFrozenMargin[%f], MMSAExchMargin[%f], DeliveryExchMargin[%f], CombExchMargin[%f], ExchMargin[%f], UseMargin[%f]",
			InvestorProdRCAMSMargin->ExchangeID, InvestorProdRCAMSMargin->BrokerID, InvestorProdRCAMSMargin->InvestorID, InvestorProdRCAMSMargin->CombProductID, InvestorProdRCAMSMargin->HedgeFlag, InvestorProdRCAMSMargin->ProductGroupID, GetDoubleValue(InvestorProdRCAMSMargin->RiskBeforeDiscount), GetDoubleValue(InvestorProdRCAMSMargin->IntraInstrRisk), GetDoubleValue(InvestorProdRCAMSMargin->BPosRisk), GetDoubleValue(InvestorProdRCAMSMargin->SPosRisk), GetDoubleValue(InvestorProdRCAMSMargin->IntraProdRisk), GetDoubleValue(InvestorProdRCAMSMargin->NetRisk), GetDoubleValue(InvestorProdRCAMSMargin->InterProdRisk), GetDoubleValue(InvestorProdRCAMSMargin->ShortOptRiskAdj), GetDoubleValue(InvestorProdRCAMSMargin->OptionRoyalty), GetDoubleValue(InvestorProdRCAMSMargin->MMSACloseFrozenMargin), GetDoubleValue(InvestorProdRCAMSMargin->CloseCombFrozenMargin), GetDoubleValue(InvestorProdRCAMSMargin->CloseFrozenMargin), GetDoubleValue(InvestorProdRCAMSMargin->MMSAOpenFrozenMargin), GetDoubleValue(InvestorProdRCAMSMargin->DeliveryOpenFrozenMargin), GetDoubleValue(InvestorProdRCAMSMargin->OpenFrozenMargin), GetDoubleValue(InvestorProdRCAMSMargin->UseFrozenMargin), GetDoubleValue(InvestorProdRCAMSMargin->MMSAExchMargin), GetDoubleValue(InvestorProdRCAMSMargin->DeliveryExchMargin), GetDoubleValue(InvestorProdRCAMSMargin->CombExchMargin), GetDoubleValue(InvestorProdRCAMSMargin->ExchMargin), GetDoubleValue(InvestorProdRCAMSMargin->UseMargin));
	}
}
void WriteQryRCAMSCombProductInfo(CThostFtdcQryRCAMSCombProductInfoField* QryRCAMSCombProductInfo)
{
	if(QryRCAMSCombProductInfo)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryRCAMSCombProductInfoField: ProductID[%s], CombProductID[%s], ProductGroupID[%s]",
			QryRCAMSCombProductInfo->ProductID, QryRCAMSCombProductInfo->CombProductID, QryRCAMSCombProductInfo->ProductGroupID);
	}
}
void WriteQryRCAMSInstrParameter(CThostFtdcQryRCAMSInstrParameterField* QryRCAMSInstrParameter)
{
	if(QryRCAMSInstrParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryRCAMSInstrParameterField: ProductID[%s]",
			QryRCAMSInstrParameter->ProductID);
	}
}
void WriteQryRCAMSIntraParameter(CThostFtdcQryRCAMSIntraParameterField* QryRCAMSIntraParameter)
{
	if(QryRCAMSIntraParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryRCAMSIntraParameterField: CombProductID[%s]",
			QryRCAMSIntraParameter->CombProductID);
	}
}
void WriteQryRCAMSInterParameter(CThostFtdcQryRCAMSInterParameterField* QryRCAMSInterParameter)
{
	if(QryRCAMSInterParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryRCAMSInterParameterField: ProductGroupID[%s], CombProduct1[%s], CombProduct2[%s]",
			QryRCAMSInterParameter->ProductGroupID, QryRCAMSInterParameter->CombProduct1, QryRCAMSInterParameter->CombProduct2);
	}
}
void WriteQryRCAMSShortOptAdjustParam(CThostFtdcQryRCAMSShortOptAdjustParamField* QryRCAMSShortOptAdjustParam)
{
	if(QryRCAMSShortOptAdjustParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryRCAMSShortOptAdjustParamField: CombProductID[%s]",
			QryRCAMSShortOptAdjustParam->CombProductID);
	}
}
void WriteQryRCAMSInvestorCombPosition(CThostFtdcQryRCAMSInvestorCombPositionField* QryRCAMSInvestorCombPosition)
{
	if(QryRCAMSInvestorCombPosition)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryRCAMSInvestorCombPositionField: BrokerID[%s], InvestorID[%s], InstrumentID[%s], CombInstrumentID[%s]",
			QryRCAMSInvestorCombPosition->BrokerID, QryRCAMSInvestorCombPosition->InvestorID, QryRCAMSInvestorCombPosition->InstrumentID, QryRCAMSInvestorCombPosition->CombInstrumentID);
	}
}
void WriteQryInvestorProdRCAMSMargin(CThostFtdcQryInvestorProdRCAMSMarginField* QryInvestorProdRCAMSMargin)
{
	if(QryInvestorProdRCAMSMargin)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryInvestorProdRCAMSMarginField: BrokerID[%s], InvestorID[%s], CombProductID[%s], ProductGroupID[%s]",
			QryInvestorProdRCAMSMargin->BrokerID, QryInvestorProdRCAMSMargin->InvestorID, QryInvestorProdRCAMSMargin->CombProductID, QryInvestorProdRCAMSMargin->ProductGroupID);
	}
}
void WriteRULEInstrParameter(CThostFtdcRULEInstrParameterField* RULEInstrParameter)
{
	if(RULEInstrParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRULEInstrParameterField: TradingDay[%s], ExchangeID[%s], InstrumentID[%s], InstrumentClass[%c], StdInstrumentID[%s], BSpecRatio[%f], SSpecRatio[%f], BHedgeRatio[%f], SHedgeRatio[%f], BAddOnMargin[%f], SAddOnMargin[%f], CommodityGroupID[%d]",
			RULEInstrParameter->TradingDay, RULEInstrParameter->ExchangeID, RULEInstrParameter->InstrumentID, RULEInstrParameter->InstrumentClass, RULEInstrParameter->StdInstrumentID, GetDoubleValue(RULEInstrParameter->BSpecRatio), GetDoubleValue(RULEInstrParameter->SSpecRatio), GetDoubleValue(RULEInstrParameter->BHedgeRatio), GetDoubleValue(RULEInstrParameter->SHedgeRatio), GetDoubleValue(RULEInstrParameter->BAddOnMargin), GetDoubleValue(RULEInstrParameter->SAddOnMargin), RULEInstrParameter->CommodityGroupID);
	}
}
void WriteRULEIntraParameter(CThostFtdcRULEIntraParameterField* RULEIntraParameter)
{
	if(RULEIntraParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRULEIntraParameterField: TradingDay[%s], ExchangeID[%s], ProdFamilyCode[%s], StdInstrumentID[%s], StdInstrMargin[%f], UsualIntraRate[%f], DeliveryIntraRate[%f]",
			RULEIntraParameter->TradingDay, RULEIntraParameter->ExchangeID, RULEIntraParameter->ProdFamilyCode, RULEIntraParameter->StdInstrumentID, GetDoubleValue(RULEIntraParameter->StdInstrMargin), GetDoubleValue(RULEIntraParameter->UsualIntraRate), GetDoubleValue(RULEIntraParameter->DeliveryIntraRate));
	}
}
void WriteRULEInterParameter(CThostFtdcRULEInterParameterField* RULEInterParameter)
{
	if(RULEInterParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRULEInterParameterField: TradingDay[%s], ExchangeID[%s], SpreadId[%d], InterRate[%f], Leg1ProdFamilyCode[%s], Leg2ProdFamilyCode[%s], Leg1PropFactor[%d], Leg2PropFactor[%d], CommodityGroupID[%d], CommodityGroupName[%s]",
			RULEInterParameter->TradingDay, RULEInterParameter->ExchangeID, RULEInterParameter->SpreadId, GetDoubleValue(RULEInterParameter->InterRate), RULEInterParameter->Leg1ProdFamilyCode, RULEInterParameter->Leg2ProdFamilyCode, RULEInterParameter->Leg1PropFactor, RULEInterParameter->Leg2PropFactor, RULEInterParameter->CommodityGroupID, RULEInterParameter->CommodityGroupName);
	}
}
void WriteQryRULEInstrParameter(CThostFtdcQryRULEInstrParameterField* QryRULEInstrParameter)
{
	if(QryRULEInstrParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryRULEInstrParameterField: ExchangeID[%s], InstrumentID[%s]",
			QryRULEInstrParameter->ExchangeID, QryRULEInstrParameter->InstrumentID);
	}
}
void WriteQryRULEIntraParameter(CThostFtdcQryRULEIntraParameterField* QryRULEIntraParameter)
{
	if(QryRULEIntraParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryRULEIntraParameterField: ExchangeID[%s], ProdFamilyCode[%s]",
			QryRULEIntraParameter->ExchangeID, QryRULEIntraParameter->ProdFamilyCode);
	}
}
void WriteQryRULEInterParameter(CThostFtdcQryRULEInterParameterField* QryRULEInterParameter)
{
	if(QryRULEInterParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryRULEInterParameterField: ExchangeID[%s], Leg1ProdFamilyCode[%s], Leg2ProdFamilyCode[%s], CommodityGroupID[%d]",
			QryRULEInterParameter->ExchangeID, QryRULEInterParameter->Leg1ProdFamilyCode, QryRULEInterParameter->Leg2ProdFamilyCode, QryRULEInterParameter->CommodityGroupID);
	}
}
void WriteInvestorProdRULEMargin(CThostFtdcInvestorProdRULEMarginField* InvestorProdRULEMargin)
{
	if(InvestorProdRULEMargin)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInvestorProdRULEMarginField: ExchangeID[%s], BrokerID[%s], InvestorID[%s], ProdFamilyCode[%s], InstrumentClass[%c], CommodityGroupID[%d], BStdPosition[%f], SStdPosition[%f], BStdOpenFrozen[%f], SStdOpenFrozen[%f], BStdCloseFrozen[%f], SStdCloseFrozen[%f], IntraProdStdPosition[%f], NetStdPosition[%f], InterProdStdPosition[%f], SingleStdPosition[%f], IntraProdMargin[%f], InterProdMargin[%f], SingleMargin[%f], NonCombMargin[%f], AddOnMargin[%f], ExchMargin[%f], AddOnFrozenMargin[%f], OpenFrozenMargin[%f], CloseFrozenMargin[%f], Margin[%f], FrozenMargin[%f]",
			InvestorProdRULEMargin->ExchangeID, InvestorProdRULEMargin->BrokerID, InvestorProdRULEMargin->InvestorID, InvestorProdRULEMargin->ProdFamilyCode, InvestorProdRULEMargin->InstrumentClass, InvestorProdRULEMargin->CommodityGroupID, GetDoubleValue(InvestorProdRULEMargin->BStdPosition), GetDoubleValue(InvestorProdRULEMargin->SStdPosition), GetDoubleValue(InvestorProdRULEMargin->BStdOpenFrozen), GetDoubleValue(InvestorProdRULEMargin->SStdOpenFrozen), GetDoubleValue(InvestorProdRULEMargin->BStdCloseFrozen), GetDoubleValue(InvestorProdRULEMargin->SStdCloseFrozen), GetDoubleValue(InvestorProdRULEMargin->IntraProdStdPosition), GetDoubleValue(InvestorProdRULEMargin->NetStdPosition), GetDoubleValue(InvestorProdRULEMargin->InterProdStdPosition), GetDoubleValue(InvestorProdRULEMargin->SingleStdPosition), GetDoubleValue(InvestorProdRULEMargin->IntraProdMargin), GetDoubleValue(InvestorProdRULEMargin->InterProdMargin), GetDoubleValue(InvestorProdRULEMargin->SingleMargin), GetDoubleValue(InvestorProdRULEMargin->NonCombMargin), GetDoubleValue(InvestorProdRULEMargin->AddOnMargin), GetDoubleValue(InvestorProdRULEMargin->ExchMargin), GetDoubleValue(InvestorProdRULEMargin->AddOnFrozenMargin), GetDoubleValue(InvestorProdRULEMargin->OpenFrozenMargin), GetDoubleValue(InvestorProdRULEMargin->CloseFrozenMargin), GetDoubleValue(InvestorProdRULEMargin->Margin), GetDoubleValue(InvestorProdRULEMargin->FrozenMargin));
	}
}
void WriteQryInvestorProdRULEMargin(CThostFtdcQryInvestorProdRULEMarginField* QryInvestorProdRULEMargin)
{
	if(QryInvestorProdRULEMargin)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryInvestorProdRULEMarginField: ExchangeID[%s], BrokerID[%s], InvestorID[%s], ProdFamilyCode[%s], CommodityGroupID[%d]",
			QryInvestorProdRULEMargin->ExchangeID, QryInvestorProdRULEMargin->BrokerID, QryInvestorProdRULEMargin->InvestorID, QryInvestorProdRULEMargin->ProdFamilyCode, QryInvestorProdRULEMargin->CommodityGroupID);
	}
}
void WriteSyncDeltaSPBMPortfDefinition(CThostFtdcSyncDeltaSPBMPortfDefinitionField* SyncDeltaSPBMPortfDefinition)
{
	if(SyncDeltaSPBMPortfDefinition)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaSPBMPortfDefinitionField: ExchangeID[%s], PortfolioDefID[%d], ProdFamilyCode[%s], IsSPBM[%d], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaSPBMPortfDefinition->ExchangeID, SyncDeltaSPBMPortfDefinition->PortfolioDefID, SyncDeltaSPBMPortfDefinition->ProdFamilyCode, SyncDeltaSPBMPortfDefinition->IsSPBM, SyncDeltaSPBMPortfDefinition->ActionDirection, SyncDeltaSPBMPortfDefinition->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaSPBMInvstPortfDef(CThostFtdcSyncDeltaSPBMInvstPortfDefField* SyncDeltaSPBMInvstPortfDef)
{
	if(SyncDeltaSPBMInvstPortfDef)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaSPBMInvstPortfDefField: ExchangeID[%s], BrokerID[%s], InvestorID[%s], PortfolioDefID[%d], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaSPBMInvstPortfDef->ExchangeID, SyncDeltaSPBMInvstPortfDef->BrokerID, SyncDeltaSPBMInvstPortfDef->InvestorID, SyncDeltaSPBMInvstPortfDef->PortfolioDefID, SyncDeltaSPBMInvstPortfDef->ActionDirection, SyncDeltaSPBMInvstPortfDef->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaSPBMFutureParameter(CThostFtdcSyncDeltaSPBMFutureParameterField* SyncDeltaSPBMFutureParameter)
{
	if(SyncDeltaSPBMFutureParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaSPBMFutureParameterField: TradingDay[%s], ExchangeID[%s], InstrumentID[%s], ProdFamilyCode[%s], Cvf[%d], TimeRange[%c], MarginRate[%f], LockRateX[%f], AddOnRate[%f], PreSettlementPrice[%f], AddOnLockRateX2[%f], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaSPBMFutureParameter->TradingDay, SyncDeltaSPBMFutureParameter->ExchangeID, SyncDeltaSPBMFutureParameter->InstrumentID, SyncDeltaSPBMFutureParameter->ProdFamilyCode, SyncDeltaSPBMFutureParameter->Cvf, SyncDeltaSPBMFutureParameter->TimeRange, GetDoubleValue(SyncDeltaSPBMFutureParameter->MarginRate), GetDoubleValue(SyncDeltaSPBMFutureParameter->LockRateX), GetDoubleValue(SyncDeltaSPBMFutureParameter->AddOnRate), GetDoubleValue(SyncDeltaSPBMFutureParameter->PreSettlementPrice), GetDoubleValue(SyncDeltaSPBMFutureParameter->AddOnLockRateX2), SyncDeltaSPBMFutureParameter->ActionDirection, SyncDeltaSPBMFutureParameter->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaSPBMOptionParameter(CThostFtdcSyncDeltaSPBMOptionParameterField* SyncDeltaSPBMOptionParameter)
{
	if(SyncDeltaSPBMOptionParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaSPBMOptionParameterField: TradingDay[%s], ExchangeID[%s], InstrumentID[%s], ProdFamilyCode[%s], Cvf[%d], DownPrice[%f], Delta[%f], SlimiDelta[%f], PreSettlementPrice[%f], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaSPBMOptionParameter->TradingDay, SyncDeltaSPBMOptionParameter->ExchangeID, SyncDeltaSPBMOptionParameter->InstrumentID, SyncDeltaSPBMOptionParameter->ProdFamilyCode, SyncDeltaSPBMOptionParameter->Cvf, GetDoubleValue(SyncDeltaSPBMOptionParameter->DownPrice), GetDoubleValue(SyncDeltaSPBMOptionParameter->Delta), GetDoubleValue(SyncDeltaSPBMOptionParameter->SlimiDelta), GetDoubleValue(SyncDeltaSPBMOptionParameter->PreSettlementPrice), SyncDeltaSPBMOptionParameter->ActionDirection, SyncDeltaSPBMOptionParameter->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaSPBMIntraParameter(CThostFtdcSyncDeltaSPBMIntraParameterField* SyncDeltaSPBMIntraParameter)
{
	if(SyncDeltaSPBMIntraParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaSPBMIntraParameterField: TradingDay[%s], ExchangeID[%s], ProdFamilyCode[%s], IntraRateY[%f], AddOnIntraRateY2[%f], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaSPBMIntraParameter->TradingDay, SyncDeltaSPBMIntraParameter->ExchangeID, SyncDeltaSPBMIntraParameter->ProdFamilyCode, GetDoubleValue(SyncDeltaSPBMIntraParameter->IntraRateY), GetDoubleValue(SyncDeltaSPBMIntraParameter->AddOnIntraRateY2), SyncDeltaSPBMIntraParameter->ActionDirection, SyncDeltaSPBMIntraParameter->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaSPBMInterParameter(CThostFtdcSyncDeltaSPBMInterParameterField* SyncDeltaSPBMInterParameter)
{
	if(SyncDeltaSPBMInterParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaSPBMInterParameterField: TradingDay[%s], ExchangeID[%s], SpreadId[%d], InterRateZ[%f], Leg1ProdFamilyCode[%s], Leg2ProdFamilyCode[%s], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaSPBMInterParameter->TradingDay, SyncDeltaSPBMInterParameter->ExchangeID, SyncDeltaSPBMInterParameter->SpreadId, GetDoubleValue(SyncDeltaSPBMInterParameter->InterRateZ), SyncDeltaSPBMInterParameter->Leg1ProdFamilyCode, SyncDeltaSPBMInterParameter->Leg2ProdFamilyCode, SyncDeltaSPBMInterParameter->ActionDirection, SyncDeltaSPBMInterParameter->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaSPBMAddOnInterParam(CThostFtdcSyncDeltaSPBMAddOnInterParamField* SyncDeltaSPBMAddOnInterParam)
{
	if(SyncDeltaSPBMAddOnInterParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaSPBMAddOnInterParamField: TradingDay[%s], ExchangeID[%s], SpreadId[%d], AddOnInterRateZ2[%f], Leg1ProdFamilyCode[%s], Leg2ProdFamilyCode[%s], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaSPBMAddOnInterParam->TradingDay, SyncDeltaSPBMAddOnInterParam->ExchangeID, SyncDeltaSPBMAddOnInterParam->SpreadId, GetDoubleValue(SyncDeltaSPBMAddOnInterParam->AddOnInterRateZ2), SyncDeltaSPBMAddOnInterParam->Leg1ProdFamilyCode, SyncDeltaSPBMAddOnInterParam->Leg2ProdFamilyCode, SyncDeltaSPBMAddOnInterParam->ActionDirection, SyncDeltaSPBMAddOnInterParam->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaSPMMInstParam(CThostFtdcSyncDeltaSPMMInstParamField* SyncDeltaSPMMInstParam)
{
	if(SyncDeltaSPMMInstParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaSPMMInstParamField: ExchangeID[%s], InstrumentID[%s], InstMarginCalID[%c], CommodityID[%s], CommodityGroupID[%s], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaSPMMInstParam->ExchangeID, SyncDeltaSPMMInstParam->InstrumentID, SyncDeltaSPMMInstParam->InstMarginCalID, SyncDeltaSPMMInstParam->CommodityID, SyncDeltaSPMMInstParam->CommodityGroupID, SyncDeltaSPMMInstParam->ActionDirection, SyncDeltaSPMMInstParam->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaSPMMProductParam(CThostFtdcSyncDeltaSPMMProductParamField* SyncDeltaSPMMProductParam)
{
	if(SyncDeltaSPMMProductParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaSPMMProductParamField: ExchangeID[%s], ProductID[%s], CommodityID[%s], CommodityGroupID[%s], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaSPMMProductParam->ExchangeID, SyncDeltaSPMMProductParam->ProductID, SyncDeltaSPMMProductParam->CommodityID, SyncDeltaSPMMProductParam->CommodityGroupID, SyncDeltaSPMMProductParam->ActionDirection, SyncDeltaSPMMProductParam->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaInvestorSPMMModel(CThostFtdcSyncDeltaInvestorSPMMModelField* SyncDeltaInvestorSPMMModel)
{
	if(SyncDeltaInvestorSPMMModel)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaInvestorSPMMModelField: ExchangeID[%s], BrokerID[%s], InvestorID[%s], SPMMModelID[%s], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaInvestorSPMMModel->ExchangeID, SyncDeltaInvestorSPMMModel->BrokerID, SyncDeltaInvestorSPMMModel->InvestorID, SyncDeltaInvestorSPMMModel->SPMMModelID, SyncDeltaInvestorSPMMModel->ActionDirection, SyncDeltaInvestorSPMMModel->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaSPMMModelParam(CThostFtdcSyncDeltaSPMMModelParamField* SyncDeltaSPMMModelParam)
{
	if(SyncDeltaSPMMModelParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaSPMMModelParamField: ExchangeID[%s], SPMMModelID[%s], CommodityGroupID[%s], IntraCommodityRate[%f], InterCommodityRate[%f], OptionDiscountRate[%f], MiniMarginRatio[%f], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaSPMMModelParam->ExchangeID, SyncDeltaSPMMModelParam->SPMMModelID, SyncDeltaSPMMModelParam->CommodityGroupID, GetDoubleValue(SyncDeltaSPMMModelParam->IntraCommodityRate), GetDoubleValue(SyncDeltaSPMMModelParam->InterCommodityRate), GetDoubleValue(SyncDeltaSPMMModelParam->OptionDiscountRate), GetDoubleValue(SyncDeltaSPMMModelParam->MiniMarginRatio), SyncDeltaSPMMModelParam->ActionDirection, SyncDeltaSPMMModelParam->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaRCAMSCombProdInfo(CThostFtdcSyncDeltaRCAMSCombProdInfoField* SyncDeltaRCAMSCombProdInfo)
{
	if(SyncDeltaRCAMSCombProdInfo)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaRCAMSCombProdInfoField: TradingDay[%s], ExchangeID[%s], ProductID[%s], CombProductID[%s], ProductGroupID[%s], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaRCAMSCombProdInfo->TradingDay, SyncDeltaRCAMSCombProdInfo->ExchangeID, SyncDeltaRCAMSCombProdInfo->ProductID, SyncDeltaRCAMSCombProdInfo->CombProductID, SyncDeltaRCAMSCombProdInfo->ProductGroupID, SyncDeltaRCAMSCombProdInfo->ActionDirection, SyncDeltaRCAMSCombProdInfo->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaRCAMSInstrParameter(CThostFtdcSyncDeltaRCAMSInstrParameterField* SyncDeltaRCAMSInstrParameter)
{
	if(SyncDeltaRCAMSInstrParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaRCAMSInstrParameterField: TradingDay[%s], ExchangeID[%s], ProductID[%s], HedgeRate[%f], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaRCAMSInstrParameter->TradingDay, SyncDeltaRCAMSInstrParameter->ExchangeID, SyncDeltaRCAMSInstrParameter->ProductID, GetDoubleValue(SyncDeltaRCAMSInstrParameter->HedgeRate), SyncDeltaRCAMSInstrParameter->ActionDirection, SyncDeltaRCAMSInstrParameter->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaRCAMSIntraParameter(CThostFtdcSyncDeltaRCAMSIntraParameterField* SyncDeltaRCAMSIntraParameter)
{
	if(SyncDeltaRCAMSIntraParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaRCAMSIntraParameterField: TradingDay[%s], ExchangeID[%s], CombProductID[%s], HedgeRate[%f], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaRCAMSIntraParameter->TradingDay, SyncDeltaRCAMSIntraParameter->ExchangeID, SyncDeltaRCAMSIntraParameter->CombProductID, GetDoubleValue(SyncDeltaRCAMSIntraParameter->HedgeRate), SyncDeltaRCAMSIntraParameter->ActionDirection, SyncDeltaRCAMSIntraParameter->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaRCAMSInterParameter(CThostFtdcSyncDeltaRCAMSInterParameterField* SyncDeltaRCAMSInterParameter)
{
	if(SyncDeltaRCAMSInterParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaRCAMSInterParameterField: TradingDay[%s], ExchangeID[%s], ProductGroupID[%s], Priority[%d], CreditRate[%f], CombProduct1[%s], CombProduct2[%s], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaRCAMSInterParameter->TradingDay, SyncDeltaRCAMSInterParameter->ExchangeID, SyncDeltaRCAMSInterParameter->ProductGroupID, SyncDeltaRCAMSInterParameter->Priority, GetDoubleValue(SyncDeltaRCAMSInterParameter->CreditRate), SyncDeltaRCAMSInterParameter->CombProduct1, SyncDeltaRCAMSInterParameter->CombProduct2, SyncDeltaRCAMSInterParameter->ActionDirection, SyncDeltaRCAMSInterParameter->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaRCAMSSOptAdjParam(CThostFtdcSyncDeltaRCAMSSOptAdjParamField* SyncDeltaRCAMSSOptAdjParam)
{
	if(SyncDeltaRCAMSSOptAdjParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaRCAMSSOptAdjParamField: TradingDay[%s], ExchangeID[%s], CombProductID[%s], HedgeFlag[%c], AdjustValue[%f], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaRCAMSSOptAdjParam->TradingDay, SyncDeltaRCAMSSOptAdjParam->ExchangeID, SyncDeltaRCAMSSOptAdjParam->CombProductID, SyncDeltaRCAMSSOptAdjParam->HedgeFlag, GetDoubleValue(SyncDeltaRCAMSSOptAdjParam->AdjustValue), SyncDeltaRCAMSSOptAdjParam->ActionDirection, SyncDeltaRCAMSSOptAdjParam->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaRCAMSCombRuleDtl(CThostFtdcSyncDeltaRCAMSCombRuleDtlField* SyncDeltaRCAMSCombRuleDtl)
{
	if(SyncDeltaRCAMSCombRuleDtl)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaRCAMSCombRuleDtlField: TradingDay[%s], ExchangeID[%s], ProdGroup[%s], RuleId[%s], Priority[%d], HedgeFlag[%c], CombMargin[%f], ExchangeInstID[%s], LegID[%d], LegInstrumentID[%s], Direction[%c], LegMultiple[%d], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaRCAMSCombRuleDtl->TradingDay, SyncDeltaRCAMSCombRuleDtl->ExchangeID, SyncDeltaRCAMSCombRuleDtl->ProdGroup, SyncDeltaRCAMSCombRuleDtl->RuleId, SyncDeltaRCAMSCombRuleDtl->Priority, SyncDeltaRCAMSCombRuleDtl->HedgeFlag, GetDoubleValue(SyncDeltaRCAMSCombRuleDtl->CombMargin), SyncDeltaRCAMSCombRuleDtl->ExchangeInstID, SyncDeltaRCAMSCombRuleDtl->LegID, SyncDeltaRCAMSCombRuleDtl->LegInstrumentID, SyncDeltaRCAMSCombRuleDtl->Direction, SyncDeltaRCAMSCombRuleDtl->LegMultiple, SyncDeltaRCAMSCombRuleDtl->ActionDirection, SyncDeltaRCAMSCombRuleDtl->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaRCAMSInvstCombPos(CThostFtdcSyncDeltaRCAMSInvstCombPosField* SyncDeltaRCAMSInvstCombPos)
{
	if(SyncDeltaRCAMSInvstCombPos)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaRCAMSInvstCombPosField: ExchangeID[%s], BrokerID[%s], InvestorID[%s], InstrumentID[%s], HedgeFlag[%c], PosiDirection[%c], CombInstrumentID[%s], LegID[%d], ExchangeInstID[%s], TotalAmt[%d], ExchMargin[%f], Margin[%f], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaRCAMSInvstCombPos->ExchangeID, SyncDeltaRCAMSInvstCombPos->BrokerID, SyncDeltaRCAMSInvstCombPos->InvestorID, SyncDeltaRCAMSInvstCombPos->InstrumentID, SyncDeltaRCAMSInvstCombPos->HedgeFlag, SyncDeltaRCAMSInvstCombPos->PosiDirection, SyncDeltaRCAMSInvstCombPos->CombInstrumentID, SyncDeltaRCAMSInvstCombPos->LegID, SyncDeltaRCAMSInvstCombPos->ExchangeInstID, SyncDeltaRCAMSInvstCombPos->TotalAmt, GetDoubleValue(SyncDeltaRCAMSInvstCombPos->ExchMargin), GetDoubleValue(SyncDeltaRCAMSInvstCombPos->Margin), SyncDeltaRCAMSInvstCombPos->ActionDirection, SyncDeltaRCAMSInvstCombPos->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaRULEInstrParameter(CThostFtdcSyncDeltaRULEInstrParameterField* SyncDeltaRULEInstrParameter)
{
	if(SyncDeltaRULEInstrParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaRULEInstrParameterField: TradingDay[%s], ExchangeID[%s], InstrumentID[%s], InstrumentClass[%c], StdInstrumentID[%s], BSpecRatio[%f], SSpecRatio[%f], BHedgeRatio[%f], SHedgeRatio[%f], BAddOnMargin[%f], SAddOnMargin[%f], CommodityGroupID[%d], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaRULEInstrParameter->TradingDay, SyncDeltaRULEInstrParameter->ExchangeID, SyncDeltaRULEInstrParameter->InstrumentID, SyncDeltaRULEInstrParameter->InstrumentClass, SyncDeltaRULEInstrParameter->StdInstrumentID, GetDoubleValue(SyncDeltaRULEInstrParameter->BSpecRatio), GetDoubleValue(SyncDeltaRULEInstrParameter->SSpecRatio), GetDoubleValue(SyncDeltaRULEInstrParameter->BHedgeRatio), GetDoubleValue(SyncDeltaRULEInstrParameter->SHedgeRatio), GetDoubleValue(SyncDeltaRULEInstrParameter->BAddOnMargin), GetDoubleValue(SyncDeltaRULEInstrParameter->SAddOnMargin), SyncDeltaRULEInstrParameter->CommodityGroupID, SyncDeltaRULEInstrParameter->ActionDirection, SyncDeltaRULEInstrParameter->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaRULEIntraParameter(CThostFtdcSyncDeltaRULEIntraParameterField* SyncDeltaRULEIntraParameter)
{
	if(SyncDeltaRULEIntraParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaRULEIntraParameterField: TradingDay[%s], ExchangeID[%s], ProdFamilyCode[%s], StdInstrumentID[%s], StdInstrMargin[%f], UsualIntraRate[%f], DeliveryIntraRate[%f], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaRULEIntraParameter->TradingDay, SyncDeltaRULEIntraParameter->ExchangeID, SyncDeltaRULEIntraParameter->ProdFamilyCode, SyncDeltaRULEIntraParameter->StdInstrumentID, GetDoubleValue(SyncDeltaRULEIntraParameter->StdInstrMargin), GetDoubleValue(SyncDeltaRULEIntraParameter->UsualIntraRate), GetDoubleValue(SyncDeltaRULEIntraParameter->DeliveryIntraRate), SyncDeltaRULEIntraParameter->ActionDirection, SyncDeltaRULEIntraParameter->SyncDeltaSequenceNo);
	}
}
void WriteSyncDeltaRULEInterParameter(CThostFtdcSyncDeltaRULEInterParameterField* SyncDeltaRULEInterParameter)
{
	if(SyncDeltaRULEInterParameter)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSyncDeltaRULEInterParameterField: TradingDay[%s], ExchangeID[%s], SpreadId[%d], InterRate[%f], Leg1ProdFamilyCode[%s], Leg2ProdFamilyCode[%s], Leg1PropFactor[%d], Leg2PropFactor[%d], CommodityGroupID[%d], CommodityGroupName[%s], ActionDirection[%c], SyncDeltaSequenceNo[%d]",
			SyncDeltaRULEInterParameter->TradingDay, SyncDeltaRULEInterParameter->ExchangeID, SyncDeltaRULEInterParameter->SpreadId, GetDoubleValue(SyncDeltaRULEInterParameter->InterRate), SyncDeltaRULEInterParameter->Leg1ProdFamilyCode, SyncDeltaRULEInterParameter->Leg2ProdFamilyCode, SyncDeltaRULEInterParameter->Leg1PropFactor, SyncDeltaRULEInterParameter->Leg2PropFactor, SyncDeltaRULEInterParameter->CommodityGroupID, SyncDeltaRULEInterParameter->CommodityGroupName, SyncDeltaRULEInterParameter->ActionDirection, SyncDeltaRULEInterParameter->SyncDeltaSequenceNo);
	}
}
void WriteIpAddrParam(CThostFtdcIpAddrParamField* IpAddrParam)
{
	if(IpAddrParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcIpAddrParamField: BrokerID[%s], Address[%s], DRIdentityID[%d], DRIdentityName[%s], AddrSrvMode[%c], AddrVer[%c], AddrNo[%d], AddrName[%s], IsSM[%d], IsLocalAddr[%d], Remark[%s], Site[%s], NetOperator[%s]",
			IpAddrParam->BrokerID, IpAddrParam->Address, IpAddrParam->DRIdentityID, IpAddrParam->DRIdentityName, IpAddrParam->AddrSrvMode, IpAddrParam->AddrVer, IpAddrParam->AddrNo, IpAddrParam->AddrName, IpAddrParam->IsSM, IpAddrParam->IsLocalAddr, IpAddrParam->Remark, IpAddrParam->Site, IpAddrParam->NetOperator);
	}
}
void WriteQryIpAddrParam(CThostFtdcQryIpAddrParamField* QryIpAddrParam)
{
	if(QryIpAddrParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryIpAddrParamField: BrokerID[%s]",
			QryIpAddrParam->BrokerID);
	}
}
void WriteTGIpAddrParam(CThostFtdcTGIpAddrParamField* TGIpAddrParam)
{
	if(TGIpAddrParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTGIpAddrParamField: BrokerID[%s], UserID[%s], Address[%s], DRIdentityID[%d], DRIdentityName[%s], AddrSrvMode[%c], AddrVer[%c], AddrNo[%d], AddrName[%s], IsSM[%d], IsLocalAddr[%d], Remark[%s], Site[%s], NetOperator[%s]",
			TGIpAddrParam->BrokerID, TGIpAddrParam->UserID, TGIpAddrParam->Address, TGIpAddrParam->DRIdentityID, TGIpAddrParam->DRIdentityName, TGIpAddrParam->AddrSrvMode, TGIpAddrParam->AddrVer, TGIpAddrParam->AddrNo, TGIpAddrParam->AddrName, TGIpAddrParam->IsSM, TGIpAddrParam->IsLocalAddr, TGIpAddrParam->Remark, TGIpAddrParam->Site, TGIpAddrParam->NetOperator);
	}
}
void WriteQryTGIpAddrParam(CThostFtdcQryTGIpAddrParamField* QryTGIpAddrParam)
{
	if(QryTGIpAddrParam)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryTGIpAddrParamField: BrokerID[%s], UserID[%s], AppID[%s]",
			QryTGIpAddrParam->BrokerID, QryTGIpAddrParam->UserID, QryTGIpAddrParam->AppID);
	}
}
void WriteTGSessionQryStatus(CThostFtdcTGSessionQryStatusField* TGSessionQryStatus)
{
	if(TGSessionQryStatus)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTGSessionQryStatusField: LastQryFreq[%d], QryStatus[%c]",
			TGSessionQryStatus->LastQryFreq, TGSessionQryStatus->QryStatus);
	}
}
void WriteLocalAddrConfig(CThostFtdcLocalAddrConfigField* LocalAddrConfig)
{
	if(LocalAddrConfig)
	{
		WriteLog(LogLevel::Info, "CThostFtdcLocalAddrConfigField: BrokerID[%s], PeerAddr[%s], NetMask[%s], DRIdentityID[%d], LocalAddress[%s]",
			LocalAddrConfig->BrokerID, LocalAddrConfig->PeerAddr, LocalAddrConfig->NetMask, LocalAddrConfig->DRIdentityID, LocalAddrConfig->LocalAddress);
	}
}
void WriteQryLocalAddrConfig(CThostFtdcQryLocalAddrConfigField* QryLocalAddrConfig)
{
	if(QryLocalAddrConfig)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryLocalAddrConfigField: BrokerID[%s]",
			QryLocalAddrConfig->BrokerID);
	}
}
void WriteReqQueryBankAccountBySec(CThostFtdcReqQueryBankAccountBySecField* ReqQueryBankAccountBySec)
{
	if(ReqQueryBankAccountBySec)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReqQueryBankAccountBySecField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], FutureSerial[%d], InstallID[%d], UserID[%s], VerifyCertNoFlag[%c], CurrencyID[%s], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], RequestID[%d], TID[%d], LongCustomerName[%s], DRIdentityID[%d], SecFutureSerial[%d]",
			ReqQueryBankAccountBySec->TradeCode, ReqQueryBankAccountBySec->BankID, ReqQueryBankAccountBySec->BankBranchID, ReqQueryBankAccountBySec->BrokerID, ReqQueryBankAccountBySec->BrokerBranchID, ReqQueryBankAccountBySec->TradeDate, ReqQueryBankAccountBySec->TradeTime, ReqQueryBankAccountBySec->BankSerial, ReqQueryBankAccountBySec->TradingDay, ReqQueryBankAccountBySec->PlateSerial, ReqQueryBankAccountBySec->LastFragment, ReqQueryBankAccountBySec->SessionID, ReqQueryBankAccountBySec->CustomerName, ReqQueryBankAccountBySec->IdCardType, ReqQueryBankAccountBySec->IdentifiedCardNo, ReqQueryBankAccountBySec->CustType, ReqQueryBankAccountBySec->BankAccount, ReqQueryBankAccountBySec->BankPassWord, ReqQueryBankAccountBySec->AccountID, ReqQueryBankAccountBySec->Password, ReqQueryBankAccountBySec->FutureSerial, ReqQueryBankAccountBySec->InstallID, ReqQueryBankAccountBySec->UserID, ReqQueryBankAccountBySec->VerifyCertNoFlag, ReqQueryBankAccountBySec->CurrencyID, ReqQueryBankAccountBySec->Digest, ReqQueryBankAccountBySec->BankAccType, ReqQueryBankAccountBySec->DeviceID, ReqQueryBankAccountBySec->BankSecuAccType, ReqQueryBankAccountBySec->BrokerIDByBank, ReqQueryBankAccountBySec->BankSecuAcc, ReqQueryBankAccountBySec->BankPwdFlag, ReqQueryBankAccountBySec->SecuPwdFlag, ReqQueryBankAccountBySec->OperNo, ReqQueryBankAccountBySec->RequestID, ReqQueryBankAccountBySec->TID, ReqQueryBankAccountBySec->LongCustomerName, ReqQueryBankAccountBySec->DRIdentityID, ReqQueryBankAccountBySec->SecFutureSerial);
	}
}
void WriteRspQueryBankAccountBySec(CThostFtdcRspQueryBankAccountBySecField* RspQueryBankAccountBySec)
{
	if(RspQueryBankAccountBySec)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRspQueryBankAccountBySecField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], FutureSerial[%d], InstallID[%d], UserID[%s], VerifyCertNoFlag[%c], CurrencyID[%s], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], RequestID[%d], TID[%d], BankUseAmount[%f], BankFetchAmount[%f], LongCustomerName[%s], DRIdentityID[%d], SecFutureSerial[%d]",
			RspQueryBankAccountBySec->TradeCode, RspQueryBankAccountBySec->BankID, RspQueryBankAccountBySec->BankBranchID, RspQueryBankAccountBySec->BrokerID, RspQueryBankAccountBySec->BrokerBranchID, RspQueryBankAccountBySec->TradeDate, RspQueryBankAccountBySec->TradeTime, RspQueryBankAccountBySec->BankSerial, RspQueryBankAccountBySec->TradingDay, RspQueryBankAccountBySec->PlateSerial, RspQueryBankAccountBySec->LastFragment, RspQueryBankAccountBySec->SessionID, RspQueryBankAccountBySec->CustomerName, RspQueryBankAccountBySec->IdCardType, RspQueryBankAccountBySec->IdentifiedCardNo, RspQueryBankAccountBySec->CustType, RspQueryBankAccountBySec->BankAccount, RspQueryBankAccountBySec->BankPassWord, RspQueryBankAccountBySec->AccountID, RspQueryBankAccountBySec->Password, RspQueryBankAccountBySec->FutureSerial, RspQueryBankAccountBySec->InstallID, RspQueryBankAccountBySec->UserID, RspQueryBankAccountBySec->VerifyCertNoFlag, RspQueryBankAccountBySec->CurrencyID, RspQueryBankAccountBySec->Digest, RspQueryBankAccountBySec->BankAccType, RspQueryBankAccountBySec->DeviceID, RspQueryBankAccountBySec->BankSecuAccType, RspQueryBankAccountBySec->BrokerIDByBank, RspQueryBankAccountBySec->BankSecuAcc, RspQueryBankAccountBySec->BankPwdFlag, RspQueryBankAccountBySec->SecuPwdFlag, RspQueryBankAccountBySec->OperNo, RspQueryBankAccountBySec->RequestID, RspQueryBankAccountBySec->TID, GetDoubleValue(RspQueryBankAccountBySec->BankUseAmount), GetDoubleValue(RspQueryBankAccountBySec->BankFetchAmount), RspQueryBankAccountBySec->LongCustomerName, RspQueryBankAccountBySec->DRIdentityID, RspQueryBankAccountBySec->SecFutureSerial);
	}
}
void WriteReqTransferBySec(CThostFtdcReqTransferBySecField* ReqTransferBySec)
{
	if(ReqTransferBySec)
	{
		WriteLog(LogLevel::Info, "CThostFtdcReqTransferBySecField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], InstallID[%d], FutureSerial[%d], UserID[%s], VerifyCertNoFlag[%c], CurrencyID[%s], TradeAmount[%f], FutureFetchAmount[%f], FeePayFlag[%c], CustFee[%f], BrokerFee[%f], Message[%s], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], RequestID[%d], TID[%d], TransferStatus[%c], LongCustomerName[%s], DRIdentityID[%d], SecFutureSerial[%d]",
			ReqTransferBySec->TradeCode, ReqTransferBySec->BankID, ReqTransferBySec->BankBranchID, ReqTransferBySec->BrokerID, ReqTransferBySec->BrokerBranchID, ReqTransferBySec->TradeDate, ReqTransferBySec->TradeTime, ReqTransferBySec->BankSerial, ReqTransferBySec->TradingDay, ReqTransferBySec->PlateSerial, ReqTransferBySec->LastFragment, ReqTransferBySec->SessionID, ReqTransferBySec->CustomerName, ReqTransferBySec->IdCardType, ReqTransferBySec->IdentifiedCardNo, ReqTransferBySec->CustType, ReqTransferBySec->BankAccount, ReqTransferBySec->BankPassWord, ReqTransferBySec->AccountID, ReqTransferBySec->Password, ReqTransferBySec->InstallID, ReqTransferBySec->FutureSerial, ReqTransferBySec->UserID, ReqTransferBySec->VerifyCertNoFlag, ReqTransferBySec->CurrencyID, GetDoubleValue(ReqTransferBySec->TradeAmount), GetDoubleValue(ReqTransferBySec->FutureFetchAmount), ReqTransferBySec->FeePayFlag, GetDoubleValue(ReqTransferBySec->CustFee), GetDoubleValue(ReqTransferBySec->BrokerFee), ReqTransferBySec->Message, ReqTransferBySec->Digest, ReqTransferBySec->BankAccType, ReqTransferBySec->DeviceID, ReqTransferBySec->BankSecuAccType, ReqTransferBySec->BrokerIDByBank, ReqTransferBySec->BankSecuAcc, ReqTransferBySec->BankPwdFlag, ReqTransferBySec->SecuPwdFlag, ReqTransferBySec->OperNo, ReqTransferBySec->RequestID, ReqTransferBySec->TID, ReqTransferBySec->TransferStatus, ReqTransferBySec->LongCustomerName, ReqTransferBySec->DRIdentityID, ReqTransferBySec->SecFutureSerial);
	}
}
void WriteRspTransferBySec(CThostFtdcRspTransferBySecField* RspTransferBySec)
{
	if(RspTransferBySec)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRspTransferBySecField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], InstallID[%d], FutureSerial[%d], UserID[%s], VerifyCertNoFlag[%c], CurrencyID[%s], TradeAmount[%f], FutureFetchAmount[%f], FeePayFlag[%c], CustFee[%f], BrokerFee[%f], Message[%s], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], RequestID[%d], TID[%d], TransferStatus[%c], ErrorID[%d], ErrorMsg[%s], LongCustomerName[%s], DRIdentityID[%d], SecFutureSerial[%d]",
			RspTransferBySec->TradeCode, RspTransferBySec->BankID, RspTransferBySec->BankBranchID, RspTransferBySec->BrokerID, RspTransferBySec->BrokerBranchID, RspTransferBySec->TradeDate, RspTransferBySec->TradeTime, RspTransferBySec->BankSerial, RspTransferBySec->TradingDay, RspTransferBySec->PlateSerial, RspTransferBySec->LastFragment, RspTransferBySec->SessionID, RspTransferBySec->CustomerName, RspTransferBySec->IdCardType, RspTransferBySec->IdentifiedCardNo, RspTransferBySec->CustType, RspTransferBySec->BankAccount, RspTransferBySec->BankPassWord, RspTransferBySec->AccountID, RspTransferBySec->Password, RspTransferBySec->InstallID, RspTransferBySec->FutureSerial, RspTransferBySec->UserID, RspTransferBySec->VerifyCertNoFlag, RspTransferBySec->CurrencyID, GetDoubleValue(RspTransferBySec->TradeAmount), GetDoubleValue(RspTransferBySec->FutureFetchAmount), RspTransferBySec->FeePayFlag, GetDoubleValue(RspTransferBySec->CustFee), GetDoubleValue(RspTransferBySec->BrokerFee), RspTransferBySec->Message, RspTransferBySec->Digest, RspTransferBySec->BankAccType, RspTransferBySec->DeviceID, RspTransferBySec->BankSecuAccType, RspTransferBySec->BrokerIDByBank, RspTransferBySec->BankSecuAcc, RspTransferBySec->BankPwdFlag, RspTransferBySec->SecuPwdFlag, RspTransferBySec->OperNo, RspTransferBySec->RequestID, RspTransferBySec->TID, RspTransferBySec->TransferStatus, RspTransferBySec->ErrorID, RspTransferBySec->ErrorMsg, RspTransferBySec->LongCustomerName, RspTransferBySec->DRIdentityID, RspTransferBySec->SecFutureSerial);
	}
}
void WriteNotifyQueryFutureAccountBySec(CThostFtdcNotifyQueryFutureAccountBySecField* NotifyQueryFutureAccountBySec)
{
	if(NotifyQueryFutureAccountBySec)
	{
		WriteLog(LogLevel::Info, "CThostFtdcNotifyQueryFutureAccountBySecField: TradeCode[%s], BankID[%s], BankBranchID[%s], BrokerID[%s], BrokerBranchID[%s], TradeDate[%s], TradeTime[%s], BankSerial[%s], TradingDay[%s], PlateSerial[%d], LastFragment[%c], SessionID[%d], CustomerName[%s], IdCardType[%c], IdentifiedCardNo[%s], CustType[%c], BankAccount[%s], BankPassWord[%s], AccountID[%s], Password[%s], FutureSerial[%d], InstallID[%d], UserID[%s], VerifyCertNoFlag[%c], CurrencyID[%s], Digest[%s], BankAccType[%c], DeviceID[%s], BankSecuAccType[%c], BrokerIDByBank[%s], BankSecuAcc[%s], BankPwdFlag[%c], SecuPwdFlag[%c], OperNo[%s], RequestID[%d], TID[%d], BankUseAmount[%f], BankFetchAmount[%f], ErrorID[%d], ErrorMsg[%s], LongCustomerName[%s], DRIdentityID[%d], SecFutureSerial[%d]",
			NotifyQueryFutureAccountBySec->TradeCode, NotifyQueryFutureAccountBySec->BankID, NotifyQueryFutureAccountBySec->BankBranchID, NotifyQueryFutureAccountBySec->BrokerID, NotifyQueryFutureAccountBySec->BrokerBranchID, NotifyQueryFutureAccountBySec->TradeDate, NotifyQueryFutureAccountBySec->TradeTime, NotifyQueryFutureAccountBySec->BankSerial, NotifyQueryFutureAccountBySec->TradingDay, NotifyQueryFutureAccountBySec->PlateSerial, NotifyQueryFutureAccountBySec->LastFragment, NotifyQueryFutureAccountBySec->SessionID, NotifyQueryFutureAccountBySec->CustomerName, NotifyQueryFutureAccountBySec->IdCardType, NotifyQueryFutureAccountBySec->IdentifiedCardNo, NotifyQueryFutureAccountBySec->CustType, NotifyQueryFutureAccountBySec->BankAccount, NotifyQueryFutureAccountBySec->BankPassWord, NotifyQueryFutureAccountBySec->AccountID, NotifyQueryFutureAccountBySec->Password, NotifyQueryFutureAccountBySec->FutureSerial, NotifyQueryFutureAccountBySec->InstallID, NotifyQueryFutureAccountBySec->UserID, NotifyQueryFutureAccountBySec->VerifyCertNoFlag, NotifyQueryFutureAccountBySec->CurrencyID, NotifyQueryFutureAccountBySec->Digest, NotifyQueryFutureAccountBySec->BankAccType, NotifyQueryFutureAccountBySec->DeviceID, NotifyQueryFutureAccountBySec->BankSecuAccType, NotifyQueryFutureAccountBySec->BrokerIDByBank, NotifyQueryFutureAccountBySec->BankSecuAcc, NotifyQueryFutureAccountBySec->BankPwdFlag, NotifyQueryFutureAccountBySec->SecuPwdFlag, NotifyQueryFutureAccountBySec->OperNo, NotifyQueryFutureAccountBySec->RequestID, NotifyQueryFutureAccountBySec->TID, GetDoubleValue(NotifyQueryFutureAccountBySec->BankUseAmount), GetDoubleValue(NotifyQueryFutureAccountBySec->BankFetchAmount), NotifyQueryFutureAccountBySec->ErrorID, NotifyQueryFutureAccountBySec->ErrorMsg, NotifyQueryFutureAccountBySec->LongCustomerName, NotifyQueryFutureAccountBySec->DRIdentityID, NotifyQueryFutureAccountBySec->SecFutureSerial);
	}
}
void WriteExitEmergency(CThostFtdcExitEmergencyField* ExitEmergency)
{
	if(ExitEmergency)
	{
		WriteLog(LogLevel::Info, "CThostFtdcExitEmergencyField: BrokerID[%s]",
			ExitEmergency->BrokerID);
	}
}
void WriteInvestorPortfMarginModel(CThostFtdcInvestorPortfMarginModelField* InvestorPortfMarginModel)
{
	if(InvestorPortfMarginModel)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInvestorPortfMarginModelField: BrokerID[%s], InvestorID[%s], MarginModelID[%s]",
			InvestorPortfMarginModel->BrokerID, InvestorPortfMarginModel->InvestorID, InvestorPortfMarginModel->MarginModelID);
	}
}
void WriteInvestorPortfSetting(CThostFtdcInvestorPortfSettingField* InvestorPortfSetting)
{
	if(InvestorPortfSetting)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInvestorPortfSettingField: ExchangeID[%s], BrokerID[%s], InvestorID[%s], HedgeFlag[%c], UsePortf[%d]",
			InvestorPortfSetting->ExchangeID, InvestorPortfSetting->BrokerID, InvestorPortfSetting->InvestorID, InvestorPortfSetting->HedgeFlag, InvestorPortfSetting->UsePortf);
	}
}
void WriteQryInvestorPortfSetting(CThostFtdcQryInvestorPortfSettingField* QryInvestorPortfSetting)
{
	if(QryInvestorPortfSetting)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryInvestorPortfSettingField: ExchangeID[%s], BrokerID[%s], InvestorID[%s]",
			QryInvestorPortfSetting->ExchangeID, QryInvestorPortfSetting->BrokerID, QryInvestorPortfSetting->InvestorID);
	}
}
void WriteUserPasswordUpdateFromSec(CThostFtdcUserPasswordUpdateFromSecField* UserPasswordUpdateFromSec)
{
	if(UserPasswordUpdateFromSec)
	{
		WriteLog(LogLevel::Info, "CThostFtdcUserPasswordUpdateFromSecField: BrokerID[%s], UserID[%s], OldPassword[%s], NewPassword[%s], FromSec[%d]",
			UserPasswordUpdateFromSec->BrokerID, UserPasswordUpdateFromSec->UserID, UserPasswordUpdateFromSec->OldPassword, UserPasswordUpdateFromSec->NewPassword, UserPasswordUpdateFromSec->FromSec);
	}
}
void WriteSettlementInfoConfirmFromSec(CThostFtdcSettlementInfoConfirmFromSecField* SettlementInfoConfirmFromSec)
{
	if(SettlementInfoConfirmFromSec)
	{
		WriteLog(LogLevel::Info, "CThostFtdcSettlementInfoConfirmFromSecField: BrokerID[%s], InvestorID[%s], ConfirmDate[%s], ConfirmTime[%s], FromSec[%d]",
			SettlementInfoConfirmFromSec->BrokerID, SettlementInfoConfirmFromSec->InvestorID, SettlementInfoConfirmFromSec->ConfirmDate, SettlementInfoConfirmFromSec->ConfirmTime, SettlementInfoConfirmFromSec->FromSec);
	}
}
void WriteTradingAccountPasswordUpdateFromSec(CThostFtdcTradingAccountPasswordUpdateFromSecField* TradingAccountPasswordUpdateFromSec)
{
	if(TradingAccountPasswordUpdateFromSec)
	{
		WriteLog(LogLevel::Info, "CThostFtdcTradingAccountPasswordUpdateFromSecField: BrokerID[%s], AccountID[%s], OldPassword[%s], NewPassword[%s], CurrencyID[%s], FromSec[%d]",
			TradingAccountPasswordUpdateFromSec->BrokerID, TradingAccountPasswordUpdateFromSec->AccountID, TradingAccountPasswordUpdateFromSec->OldPassword, TradingAccountPasswordUpdateFromSec->NewPassword, TradingAccountPasswordUpdateFromSec->CurrencyID, TradingAccountPasswordUpdateFromSec->FromSec);
	}
}
void WriteRiskForbiddenRight(CThostFtdcRiskForbiddenRightField* RiskForbiddenRight)
{
	if(RiskForbiddenRight)
	{
		WriteLog(LogLevel::Info, "CThostFtdcRiskForbiddenRightField: BrokerID[%s], InvestorID[%s], InstrumentID[%s], UserID[%s]",
			RiskForbiddenRight->BrokerID, RiskForbiddenRight->InvestorID, RiskForbiddenRight->InstrumentID, RiskForbiddenRight->UserID);
	}
}
void WriteInvestorInfoCommRec(CThostFtdcInvestorInfoCommRecField* InvestorInfoCommRec)
{
	if(InvestorInfoCommRec)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInvestorInfoCommRecField: ExchangeID[%s], BrokerID[%s], InvestorID[%s], InstrumentID[%s], OrderCount[%d], OrderActionCount[%d], ForQuoteCnt[%d], InfoComm[%f], IsOptSeries[%d], ProductID[%s], InfoCnt[%d]",
			InvestorInfoCommRec->ExchangeID, InvestorInfoCommRec->BrokerID, InvestorInfoCommRec->InvestorID, InvestorInfoCommRec->InstrumentID, InvestorInfoCommRec->OrderCount, InvestorInfoCommRec->OrderActionCount, InvestorInfoCommRec->ForQuoteCnt, GetDoubleValue(InvestorInfoCommRec->InfoComm), InvestorInfoCommRec->IsOptSeries, InvestorInfoCommRec->ProductID, InvestorInfoCommRec->InfoCnt);
	}
}
void WriteQryInvestorInfoCommRec(CThostFtdcQryInvestorInfoCommRecField* QryInvestorInfoCommRec)
{
	if(QryInvestorInfoCommRec)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryInvestorInfoCommRecField: InvestorID[%s], InstrumentID[%s], BrokerID[%s]",
			QryInvestorInfoCommRec->InvestorID, QryInvestorInfoCommRec->InstrumentID, QryInvestorInfoCommRec->BrokerID);
	}
}
void WriteCombLeg(CThostFtdcCombLegField* CombLeg)
{
	if(CombLeg)
	{
		WriteLog(LogLevel::Info, "CThostFtdcCombLegField: CombInstrumentID[%s], LegID[%d], LegInstrumentID[%s], Direction[%c], LegMultiple[%d], ImplyLevel[%d]",
			CombLeg->CombInstrumentID, CombLeg->LegID, CombLeg->LegInstrumentID, CombLeg->Direction, CombLeg->LegMultiple, CombLeg->ImplyLevel);
	}
}
void WriteQryCombLeg(CThostFtdcQryCombLegField* QryCombLeg)
{
	if(QryCombLeg)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryCombLegField: LegInstrumentID[%s]",
			QryCombLeg->LegInstrumentID);
	}
}
void WriteInputOffsetSetting(CThostFtdcInputOffsetSettingField* InputOffsetSetting)
{
	if(InputOffsetSetting)
	{
		WriteLog(LogLevel::Info, "CThostFtdcInputOffsetSettingField: BrokerID[%s], InvestorID[%s], InstrumentID[%s], UnderlyingInstrID[%s], ProductID[%s], OffsetType[%c], Volume[%d], IsOffset[%d], RequestID[%d], UserID[%s], ExchangeID[%s], IPAddress[%s], MacAddress[%s]",
			InputOffsetSetting->BrokerID, InputOffsetSetting->InvestorID, InputOffsetSetting->InstrumentID, InputOffsetSetting->UnderlyingInstrID, InputOffsetSetting->ProductID, InputOffsetSetting->OffsetType, InputOffsetSetting->Volume, InputOffsetSetting->IsOffset, InputOffsetSetting->RequestID, InputOffsetSetting->UserID, InputOffsetSetting->ExchangeID, InputOffsetSetting->IPAddress, InputOffsetSetting->MacAddress);
	}
}
void WriteOffsetSetting(CThostFtdcOffsetSettingField* OffsetSetting)
{
	if(OffsetSetting)
	{
		WriteLog(LogLevel::Info, "CThostFtdcOffsetSettingField: BrokerID[%s], InvestorID[%s], InstrumentID[%s], UnderlyingInstrID[%s], ProductID[%s], OffsetType[%c], Volume[%d], IsOffset[%d], RequestID[%d], UserID[%s], ExchangeID[%s], IPAddress[%s], MacAddress[%s], ExchangeInstID[%s], ExchangeSerialNo[%s], ExchangeProductID[%s], ParticipantID[%s], ClientID[%s], TraderID[%s], InstallID[%d], OrderSubmitStatus[%c], TradingDay[%s], SettlementID[%d], InsertDate[%s], InsertTime[%s], CancelTime[%s], ExecResult[%c], SequenceNo[%d], FrontID[%d], SessionID[%d], StatusMsg[%s], ActiveUserID[%s], BrokerOffsetSettingSeq[%d]",
			OffsetSetting->BrokerID, OffsetSetting->InvestorID, OffsetSetting->InstrumentID, OffsetSetting->UnderlyingInstrID, OffsetSetting->ProductID, OffsetSetting->OffsetType, OffsetSetting->Volume, OffsetSetting->IsOffset, OffsetSetting->RequestID, OffsetSetting->UserID, OffsetSetting->ExchangeID, OffsetSetting->IPAddress, OffsetSetting->MacAddress, OffsetSetting->ExchangeInstID, OffsetSetting->ExchangeSerialNo, OffsetSetting->ExchangeProductID, OffsetSetting->ParticipantID, OffsetSetting->ClientID, OffsetSetting->TraderID, OffsetSetting->InstallID, OffsetSetting->OrderSubmitStatus, OffsetSetting->TradingDay, OffsetSetting->SettlementID, OffsetSetting->InsertDate, OffsetSetting->InsertTime, OffsetSetting->CancelTime, OffsetSetting->ExecResult, OffsetSetting->SequenceNo, OffsetSetting->FrontID, OffsetSetting->SessionID, OffsetSetting->StatusMsg, OffsetSetting->ActiveUserID, OffsetSetting->BrokerOffsetSettingSeq);
	}
}
void WriteCancelOffsetSetting(CThostFtdcCancelOffsetSettingField* CancelOffsetSetting)
{
	if(CancelOffsetSetting)
	{
		WriteLog(LogLevel::Info, "CThostFtdcCancelOffsetSettingField: BrokerID[%s], InvestorID[%s], InstrumentID[%s], UnderlyingInstrID[%s], ProductID[%s], OffsetType[%c], Volume[%d], IsOffset[%d], RequestID[%d], UserID[%s], ExchangeID[%s], IPAddress[%s], MacAddress[%s], ExchangeInstID[%s], ExchangeSerialNo[%s], ExchangeProductID[%s], TraderID[%s], InstallID[%d], ParticipantID[%s], ClientID[%s], OrderActionStatus[%c], StatusMsg[%s], ActionLocalID[%s], ActionDate[%s], ActionTime[%s]",
			CancelOffsetSetting->BrokerID, CancelOffsetSetting->InvestorID, CancelOffsetSetting->InstrumentID, CancelOffsetSetting->UnderlyingInstrID, CancelOffsetSetting->ProductID, CancelOffsetSetting->OffsetType, CancelOffsetSetting->Volume, CancelOffsetSetting->IsOffset, CancelOffsetSetting->RequestID, CancelOffsetSetting->UserID, CancelOffsetSetting->ExchangeID, CancelOffsetSetting->IPAddress, CancelOffsetSetting->MacAddress, CancelOffsetSetting->ExchangeInstID, CancelOffsetSetting->ExchangeSerialNo, CancelOffsetSetting->ExchangeProductID, CancelOffsetSetting->TraderID, CancelOffsetSetting->InstallID, CancelOffsetSetting->ParticipantID, CancelOffsetSetting->ClientID, CancelOffsetSetting->OrderActionStatus, CancelOffsetSetting->StatusMsg, CancelOffsetSetting->ActionLocalID, CancelOffsetSetting->ActionDate, CancelOffsetSetting->ActionTime);
	}
}
void WriteQryOffsetSetting(CThostFtdcQryOffsetSettingField* QryOffsetSetting)
{
	if(QryOffsetSetting)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryOffsetSettingField: BrokerID[%s], InvestorID[%s], ProductID[%s], OffsetType[%c]",
			QryOffsetSetting->BrokerID, QryOffsetSetting->InvestorID, QryOffsetSetting->ProductID, QryOffsetSetting->OffsetType);
	}
}
void WriteAddrAppIDRelation(CThostFtdcAddrAppIDRelationField* AddrAppIDRelation)
{
	if(AddrAppIDRelation)
	{
		WriteLog(LogLevel::Info, "CThostFtdcAddrAppIDRelationField: BrokerID[%s], Address[%s], DRIdentityID[%d], AppID[%s]",
			AddrAppIDRelation->BrokerID, AddrAppIDRelation->Address, AddrAppIDRelation->DRIdentityID, AddrAppIDRelation->AppID);
	}
}
void WriteQryAddrAppIDRelation(CThostFtdcQryAddrAppIDRelationField* QryAddrAppIDRelation)
{
	if(QryAddrAppIDRelation)
	{
		WriteLog(LogLevel::Info, "CThostFtdcQryAddrAppIDRelationField: BrokerID[%s]",
			QryAddrAppIDRelation->BrokerID);
	}
}
void WriteFrontInfo(CThostFtdcFrontInfoField* FrontInfo)
{
	if(FrontInfo)
	{
		WriteLog(LogLevel::Info, "CThostFtdcFrontInfoField: FrontAddr[%s], QryFreq[%d], FTDPkgFreq[%d]",
			FrontInfo->FrontAddr, FrontInfo->QryFreq, FrontInfo->FTDPkgFreq);
	}
}
