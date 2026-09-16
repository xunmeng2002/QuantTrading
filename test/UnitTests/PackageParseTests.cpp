#include "Packages.h"

#include "doctest/doctest.h"

using namespace QuantTrading::Packages;

TEST_SUITE("PackageParse")
{

// 解析层只拦"多余字段"（未知 FieldID 直接失败），不校验"缺失字段"：包体里一个字段区都没有时
// FromStepStream 仍返回 true，字段指针保持 nullptr。各处理函数的判空分支、以及生成代码里
// "字段区为空即回绝"的分发守卫都以此为前提，本用例把该前提钉住——将来若在解析层改为直接拒绝
// 空字段区，此处会失败，提示同步清理那批分支。Req 包的字段成员名与包名同名，故判空可照名直写。
TEST_CASE("包体无字段区时解析成功且字段指针为空")
{
	char emptyBody[64] = { 0 };

	ReqMdUserLoginPackage* mdUserLoginPackage = ReqMdUserLoginPackage::Allocate();
	CHECK(mdUserLoginPackage->FromStepStream(emptyBody, 0, 0));
	CHECK(mdUserLoginPackage->ReqMdUserLogin == nullptr);
	mdUserLoginPackage->Deallocate();

	ReqMdUserLogoutPackage* mdUserLogoutPackage = ReqMdUserLogoutPackage::Allocate();
	CHECK(mdUserLogoutPackage->FromStepStream(emptyBody, 0, 0));
	CHECK(mdUserLogoutPackage->ReqMdUserLogout == nullptr);
	mdUserLogoutPackage->Deallocate();

	ReqSubMarketDataPackage* subMarketDataPackage = ReqSubMarketDataPackage::Allocate();
	CHECK(subMarketDataPackage->FromStepStream(emptyBody, 0, 0));
	CHECK(subMarketDataPackage->ReqSubMarketData == nullptr);
	subMarketDataPackage->Deallocate();

	NotifyDisConnectPackage* notifyDisConnectPackage = NotifyDisConnectPackage::Allocate();
	CHECK(notifyDisConnectPackage->FromStepStream(emptyBody, 0, 0));
	CHECK(notifyDisConnectPackage->NotifyDisConnect == nullptr);
	notifyDisConnectPackage->Deallocate();

	RtnDepthMarketDataPackage* rtnDepthMarketDataPackage = RtnDepthMarketDataPackage::Allocate();
	CHECK(rtnDepthMarketDataPackage->FromStepStream(emptyBody, 0, 0));
	CHECK(rtnDepthMarketDataPackage->DepthMarketData == nullptr);
	rtnDepthMarketDataPackage->Deallocate();

	ReqAccountLoginPackage* accountLoginPackage = ReqAccountLoginPackage::Allocate();
	CHECK(accountLoginPackage->FromStepStream(emptyBody, 0, 0));
	CHECK(accountLoginPackage->ReqAccountLogin == nullptr);
	accountLoginPackage->Deallocate();

	ReqAccountLogoutPackage* accountLogoutPackage = ReqAccountLogoutPackage::Allocate();
	CHECK(accountLogoutPackage->FromStepStream(emptyBody, 0, 0));
	CHECK(accountLogoutPackage->ReqAccountLogout == nullptr);
	accountLogoutPackage->Deallocate();

	ReqInsertOrderPackage* insertOrderPackage = ReqInsertOrderPackage::Allocate();
	CHECK(insertOrderPackage->FromStepStream(emptyBody, 0, 0));
	CHECK(insertOrderPackage->ReqInsertOrder == nullptr);
	insertOrderPackage->Deallocate();

	ReqCancelOrderPackage* cancelOrderPackage = ReqCancelOrderPackage::Allocate();
	CHECK(cancelOrderPackage->FromStepStream(emptyBody, 0, 0));
	CHECK(cancelOrderPackage->ReqCancelOrder == nullptr);
	cancelOrderPackage->Deallocate();

	ReqQryOrderPackage* qryOrderPackage = ReqQryOrderPackage::Allocate();
	CHECK(qryOrderPackage->FromStepStream(emptyBody, 0, 0));
	CHECK(qryOrderPackage->ReqQryOrder == nullptr);
	qryOrderPackage->Deallocate();

	ReqQryTradePackage* qryTradePackage = ReqQryTradePackage::Allocate();
	CHECK(qryTradePackage->FromStepStream(emptyBody, 0, 0));
	CHECK(qryTradePackage->ReqQryTrade == nullptr);
	qryTradePackage->Deallocate();

	ReqQryInstrumentPackage* qryInstrumentPackage = ReqQryInstrumentPackage::Allocate();
	CHECK(qryInstrumentPackage->FromStepStream(emptyBody, 0, 0));
	CHECK(qryInstrumentPackage->ReqQryInstrument == nullptr);
	qryInstrumentPackage->Deallocate();
}

}
