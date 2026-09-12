#include "Packages.h"

#include "doctest/doctest.h"

using namespace quanttrading::packages;

TEST_SUITE("PackageParse")
{

// 解析层只拦"多余字段"（未知 FieldID 直接失败），不校验"缺失字段"：包体里一个字段区都没有时
// FromStepStream 仍返回 true，字段指针保持 nullptr。MdKernel 各处理函数的判空分支以此为前提，
// 本用例把该前提钉住——将来若在解析层改为直接拒绝空字段区，此处会失败，提示同步清理那批分支。
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
}

}
