# 项目进度归档

> 本文件是 [`PROGRESS.md`](PROGRESS.md) 的归档层。2026-09-13 拆分：主文件只保留活内容（🔄 进行中 / ❓ 未决 / 最近 3 批 ✅），
> 已关闭与已了结的条目**原文搬到这里，不删不改**，供追溯当时的根因、风险与验证记录。

- 检索：`grep "关键词" PROGRESS-archive.md`。
- 条目 ID：`D.*` = 原 ✅ 已完成；`Q.*` = 原 ❓ 待讨论；`R.*` = 原 🔄 进行中。ID 取自 2026-09-13 拆分时的文档顺序。
- 本文件不参与每会话开头的通读，只在主文件的归档索引指向这里时按需检索。

---

## ✅ 已完成（历史，倒序）

### D.43 · 2026-09-13 （第九批） 入站包方向过滤（方案乙）

- **2026-09-13 入站包方向过滤（第九批，方案乙）**：第六批把方向纪律做进了内核分发（**内核侧"少认"**），本批补上网络侧的"不收"——**对端在本协议角色下不可能发出的包，在包对象创建之前即被拒绝**。用户决策走乙（代价最小），方向表来源取 (c) 生成期按类名前缀推导（乙 方案自带的实现选择）。
  - **Spark 侧（新增公开 API，Harness §3.1 确认点在用户）**：`PackageFactoryBase` 增 `virtual bool IsInboundPackageAccepted(UShortType packageID) { return true; }`——默认全放行为**纯增量**，任何既有实现不覆写即维持原语义（本仓唯一子类已覆写）。`PackageReader` 在 Xtp/Step **两条解析路径**的校验和之后、`CreatePackage` 之前插入判定：不通过则记 Error 日志 `Inbound Package Not Accepted. PackageID:%d, SessionId:%lld, IP:%s` 后 `Reset(); return false;`，复用既有的"解析失败 → `m_IOBase->DisConnect(sessionId)`"路径断 TCP。选在 `CreatePackage` 之前是乙的核心价值——**被拒的 ID 一个包对象都不会被分配**，不存在"先造出来再丢"的浪费，也不牵动对象池的 `Deallocate` 漏点。
  - **Templates 侧（外部仓 `D:\Gitee\Templates`，待用户提交）**：`Cpp/Protocol/Packages/PackageFactory.{h,cpp}.tpl`——头文件加 `ServerTypeType` 构造参数与 override 声明，实现加构造定义与方向开关：`Notify*` → `false`；`Req*` → `m_ServerType == ServerTypeType::Server`；`Rsp*`/`Rtn*` → `m_ServerType == ServerTypeType::Client`；`else` 与 `default` → `false`。方向用 DSL 的 `@name.startswith(...)` 在**生成期**算成常数，运行期无字符串操作、无查表。
  - **QuantTrading 侧**：`pumpall.py` 再生 `src/Packages/PackageFactory.{h,cpp}`（仅此二文件变化，重跑幂等）。核对：52 个 `case` = 20 个 Server + 28 个 Client + 4 个 `false`（Notify），加尾部 `default: break; return false;`，**每个包都被分类，无 fail-open 分支**。4 个构造点补角色实参：`src/Apis/ApiBase/ApiBase.cpp:13`（10 个客户端 `Api*Impl` 共用的唯一 Protocol，`Client`）、`src/MdOffer/MdFront.cpp:9`、`src/SimExchange/TradeFront.cpp:10`、`src/SimExchange/MdFront.cpp:11`（三者 `Server`；末者是死对象，但代码确实构造，故必须传参）。
  - **语义边界（本批不是"鉴权修好了"）**：内部/自造包（`MdKernel.cpp:47` 与 `SimExchange.cpp:82` 的 `NotifyDisConnect`、CTP SPI tick、`DbSubscriber`）都**直调 `OnMessage`、不经 reader**，故"`Notify*` 一律拒"不会误伤它们；同一原因，**方向合法 ≠ 会话合法**——`NotifyDisConnect` 取的是报文体里的 `SessionId`、可指定他人会话这个病灶与本批**正交，仍未修**（等用户定的会话登录检查）。`Model/PackageNames/*.xml` 未动（仍无运行期读者）；方案 (a) 由 `PackageNames` 生成运行期查表、(b) `Packages.xml` 加 `direction` 列，均未做。
  - **测试建议（§7）**：

    ```text
    TestMdApi（客户端角色）：登录 → 订阅 → RtnDepthMarketData 照常到达（Rtn 在 Client 侧放行）
    伪造：向 MdOffer 的 MdFront 发字段区合法的 RtnDepthMarketDataPackage（0x100A = 4106）
        旧：FieldToMdb 落库 + MdSnap 改写快照 + PushToAllSubscribed 广播给所有订阅者
        新：MdOffer 记 `Inbound Package Not Accepted. PackageID:4106, ...`，连接被断，
            零落库、零广播
    伪造：客户端发 NotifyDisConnectPackage → 同上被拒，不再能借报文体 SessionId 清他人会话
    反向：服务端误发 Req* 给客户端 → 客户端侧同样拒绝（此前客户端实例完全不设防）
    ```

  - **风险（§7）**：① **构建顺序有硬约束**——生成代码对 `IsInboundPackageAccepted` 用了 `override`，故 **Spark 必须先重编并重装到 `Libs`，QuantTrading 之后才能编译**（Spark 头文件 1 处 + `PackageReader.cpp` 2 处）。② 拒绝即断 TCP：以往"未知 PackageID"经 `CreatePackage == nullptr` 也是断，但**"已知包、方向不对"此前是被正常收下的**，现在变为拒绝 + 断连——这是本批的意图，属可观测行为变化；已逐一核对本仓 4 个 Protocol 实例 / 10 个订阅者无此情形（6 个客户端 `Api*Impl` 只分派 `Rsp*`/`Rtn*`；两个内核只处理 `Req*` 与内部自造包；`ReqSubMarketDataFinished` 只在进程内回测）。③ 拒绝时记 Error 级日志且无限流，一次伪造一条，沿用既有解析失败路径的做法未加限流。④ `default: return false` 对未知 ID fail-closed，与既有 `CreatePackage` 返回 `nullptr` 的结局等价（都断连），无新增暴露面。
  - **注释披露（§4）**：本批新增注释 2 处，均属"外部前提"性质、命名无法表达者——`PackageFactoryBase.h` 新虚函数上方一行（默认全放行 + 由应用侧按自己协议收紧的契约）；模板 `PackageFactory.cpp.tpl` 中新函数体首行（方向族由包名前缀推导——这条映射不写下来，看生成结果会以为那些常数是手工维护的）。其余改动未加注释。
  - **未验证**：编译与运行仍由用户在 VS 侧执行（按约定）。本批为 6 个文件静态改动（含 2 个生成文件）+ 生成文件再生，无新增运行期验证。**已提交**：本仓 `407509c` + Spark 仓 `50b5e31`；`D:\Gitee\Templates` 的两处模板改动待用户提交。

### D.42 · 2026-09-12 （第八批） MdOffer 移除 MdOfferInit

- **2026-09-12（第八批）MdOffer 移除 MdOfferInit：种子用户改配置项，启动订阅改配置清单**：
  - **需求**（用户口头）：「设计有点问题了，我之前刚把 BackTestInit 给干掉了，把初始化放到 BackTest 内部了。这里的 MdOffer 也这样做吧，完全移除 MdOfferInit 相关的内容。主要看看种子用户怎么提供，是使用简单的配置项，还是提供一个 List？」→ 两个子问题经 `AskUserQuestion` 定稿为「单配置项」+「改为配置订阅清单」。**范围仅 MdOffer**；`SimExchange` 仍保留同款 `SimExchangeInit`/`DbInitHost` 模式（用户未点名，未动）。
  - **问题根因（为什么原来跑不通）**：`DbInitHost` 指向的种子库 `MdOfferInit.db` 是 0 字节、0 张表，且**仓库内无任何生产者**——`InitMdbFromDB::LoadMdUserTable/LoadExchangeTable/LoadInstrumentTable` 三个装载全部 `no such table`（对应此前"怎么没有用户表"的排查）。同时 `HandleNotifyDBConnect` 的"全市场订阅"遍历 `t_Instrument->m_PrimaryKey->SelectAll()`，种子库没表 → 空集 → **启动订阅静默失效**，一根 bar 都不会落库，除非客户端逐个 `ReqSubMarketData`。第一版还有一处死代码 `ExchangeIdType exchangeId = "SHFE";`（赋值后从未使用）与逐合约裸分配泄漏（每一行 `Allocate` 的 `ReqSubMarketDataField` 都不释放、也不入注册表）。
  - **移除**（`src/MdOffer/` 侧已无任何 `MdOfferInit`/`DbInitHost`/`t_Instrument` 残留，grep 复核为"无"）：`Main.cpp` 的 `#include "InitMdbFromDB.h"`、种子库常量 `./MdOfferInit.db`、整个 `SqliteWrapper* initDB = new SqliteWrapper(config.DbInitHost.empty() ? ... : ...)` + 三次 `Load*Table` + `DisConnect/delete` 块；`Model/Configs/MdOffer.xml` 与 `Configs/MdOffer.json` 的 `DbInitHost`；`MdKernel.cpp` 的 `SelectAll` 遍历与死变量。
  - **替代（种子用户=单配置项）**：**该路径本就存在、本批一字未改**——`Main.cpp:102-109` 在 `config.MdUserId` 非空时构造一条 `MdUser`（`MdUserName` 置空、密码取 `config.MdPassword`）插入 `mdb->t_MdUser`，此前一直被上面三条失败的 `Load*Table` 挡在噪声之下（`git diff` 中该块为上下文行，非新增）。故"单配置项"的落地成本为零：只删 `DbInitHost`、不新增配置键、`MdUserId`/`MdPassword` 原样复用。空 `MdUserId` 则完全不插（保持"无用户则无法登录"的语义，不静默造默认账号）。表本身由 Mdb 的 `CreateTables()` 在 DB 连接后自动建（数据库路径），不再依赖外部种子库。
  - **替代（启动订阅=配置清单）**：`Model/Configs/MdOffer.xml` 新增 `SubscribeInstruments`（`type="list"` + 标量 `modeltype="SubscribeInstrument"` → 生成 `std::list<SubscribeInstrument*>`），复用 Spark `ConfigStructs.h` 里既有的 `SubscribeInstrument`；`Configs/MdOffer.json` 填 CFFEX/IF2603、SHFE/rb2603、DCE/jd2603、CZCE/AP605（与 `Configs/TestMdApi.json` 同四个，**均为已到期月份，属占位**）。`Config.{h,cpp}` 由仓库根 `python pumpall.py` 重生成（本次仅这两个文件变化）。清单以构造参数注入 `MdKernel`（照 `TradeSessions` 注入的先例，而非在 kernel 里读配置单例）：`HandleNotifyDBConnect` 改为遍历该清单，逐项 `subscribeInstruments_.insert`（全局注册表去重、复用 set 节点地址）、新合约才 `minuteBar_->ReqSubMarketData` 并收集，最后一次性 `mdSpi_->SubscribeMds(reqSubMds)`。DB 重连会重跑该流程，靠注册表幂等，不会重复订阅 CTP。
  - **测试 I/O 示例**（重编 `MdOffer` 后）：

    ```text
    启动（不含任何客户端连接）：
      旧：SqliteWrapper: SELECT failed. Table:t_MdUser, Error:no such table: t_MdUser
      新：无该行；改为 4 条 SubscribeMd: ExchangeId:..., InstrumentId:...
           + SubscribeMarketData: nCount[1]（每合约一条）
    MdOffer.db：7 张表照建（DB 连接后 CreateTables），t_MdUser 内有 1 行
    客户端登录（正确口令）→ RspInfoField:ErrorId:[0]（第七批修好后）
    清单留空 → 启动零订阅、零报错，订阅完全由客户端驱动
    ```

  - **风险（§7）**：① 清单项是从配置单例 `new` 出来并被 `MdKernel` 以裸指针持有的（模板生成规则：list + 非标量 → `std::list<SubscribeInstrument*>`，逐条 `new` 且模板不生成释放），生命周期与进程同长，无悬垂、亦不免泄漏——与 `Config` 现有全部 list 字段同款，未单独处理。② `SubscribeInstrument` 只有 `ExchangeId`/`InstrumentId` 两个字段，**无 bar 周期**，故启动订阅按既有约定把 `BarPreces/BarPeriod` 置 0（与客户端 `ReqSubMarketData` 的周期语义不同，落库的前两者恒为 0，若后续要用 bar 表需再扩字段）。③ 空清单 = 服务端不订阅任何合约 → `t_MinuteBar` 只在客户端订阅后才产生数据，非故障但需知晓。④ JSON 里四个合约已到期，验证时须换成活跃月份，否则依旧无 tick（见第七批同项）。⑤ `Main.cpp` 的 `#include <DBAdapters/DBInterface/TypedTable.h>` 改动后已无直接使用点，**刻意保留**以免造成无法验证的编译中断。
  - **注释披露（§4）**：本批新增/改写注释两处——`MdKernel.h` 构造函数注释补一句「启动订阅清单项指向配置单例，生命周期同进程」（即风险①的契约）；`MdKernel.cpp` 原有两行注释里的「全市场订阅」改为「启动订阅」（遍历对象已变，不写清会误导）。其余为删除，未新增。
  - **未验证**：编译与运行仍由用户在 VS 侧执行（按约定）。本批仅静态改动 + `pumpall.py` 生成；`bin/Release/MdOffer.json` 待下次构建经 `copy_config_file`（`CMakeLists.txt:145`）刷新后生效。

### D.41 · 2026-09-12 （第七批） 修登录成功仍回「用户不存在」

- **2026-09-12（第七批）修 `HandleReqMdUserLogin` 成功登录仍回「用户不存在」（第五批 C3 引入的回归）**：
  - **现象**（用户跑 TestMdApi 冒烟）：登录回 `RspInfoField:ErrorId:[4098], ErrorMsg:[用户不存在]`，但紧接着的 4 条 `ReqSubMarketData` **全部回 `ErrorId:[0]`**，且服务端日志显示内核真的把这 4 个合约订阅到了 CTP（`bin/Release/log/MdOffer.20260912-224105.log:54-69`：每条 `HandleReqSubMarketData` 后跟 `SubscribeMd` + `SubscribeMarketData`）。即"登录报错、会话却已建立"——而订阅网关（`MdKernel.cpp:294` 的 `m_LoggedSessions.find`）是当时**唯一**的会话检查点。
  - **定位**：`m_LoggedSessions` 只在 `MdKernel.cpp:216` 写入，且写入前必先通过 `t_MdUser` 查表与密码比对（两者任一失败都在 `:194/:198` 回错误、进不到插入分支；密码错回 `ErrorIncorrectPassword` 0x0002，与观测到的 4098 互斥）。故"订阅被受理"反证了**登录实际成功**，4098 是响应里的 `errorId` 没被回写——`auto errorId = ErrorUserNotExist;`（`:184`）是第五批 C3（`0b07e60`）为"字段区缺失回错误而非成功"而设的初值，但**成功分支自始至终没有一处 `errorId = ErrorNone;`**（`0b07e60^` 版本初值是 `ErrorNone`，靠默认值侥幸正确）。同一处还解释了两个附带现象：`LoginDate`/`LoginTime` 只在 `errorId == ErrorNone` 时填写（`:239-242`），故客户端日志恒为 `LoginDate:[], LoginTime:[]`（`TestMdApi.20260912-224110.log:22/52`）。**这是我的 C3 改动引入的回归**，此前无测试覆盖登录成功路径，直到本次冒烟才暴露。
  - **修法（一行）**：在插入会话成功处回写成功状态，`m_LoggedSessions.insert(package->SessionId);` 之后加 `errorId = ErrorNone;`。保留"默认失败"的初值不动——登录是鉴权路径，宁可少认不可错认，后续若新增提前返回分支忘了置错也只表现为"登录被拒"，不会静默放行。
  - **同类核查**：`src/SimExchange/SimExchange.cpp` 6 处 `auto errorId = ErrorNone;`、`MdKernel::HandleReqSubMarketData`（`:293`）均为"默认成功 + 逐项置错"，无同类问题；全仓 `errorId` 初值与成功路径回写已逐处比对，仅此一处缺回写。
  - **测试 I/O 示例**（重编 `MdOffer` + `TestMdApi` 后应看到）：

    ```text
    正确 MdUser/MdPassword → RspInfoField:ErrorId:[0], ErrorMsg:[正确]，且 LoginDate/LoginTime 非空
    错误密码               → RspInfoField:ErrorId:[2], ErrorMsg:[密码错误]
    不存在的用户           → RspInfoField:ErrorId:[4098], ErrorMsg:[用户不存在]
    登出后同连接重登       → 第二次 ErrorId:[0]（回 0x2015 才说明登出清理失效）
    ```

  - **风险（§7）**：无。一行赋值，不改所有权、不加锁、不放宽任何鉴权（`m_LoggedSessions` 仍只在登录成功且会话行插入成功后写入）。**未验证**：编译与重跑仍由用户在 VS 侧执行；本次仅静态定位 + 改动。
  - **同批冒烟的另一发现（与登录缺陷独立，属测试配置）**：`Configs/TestMdApi.json` 订阅的 IF2603 / rb2603 / jd2603 / AP605 分别是 2026-03、2026-03、2026-03、2026-05 合约，相对当前日期（2026-09-12）**均已到期**，CTP 受理订阅（回 `No Error`）但不会推送任何 tick——这才是 `Timeout waiting for market data.`（120s 有界轮询走满）的直接原因，与登录无关。建议把冒烟合约换成活跃月份；另注意 22:41 属日盘收市后，CFFEX 无夜盘，即便合约活跃也只有 SHFE/DCE/CZCE 的夜盘品种在推。


### D.40 · 2026-09-12 （第六批） Kernel 分发改为生成

- **2026-09-12（第六批）Kernel 分发改为生成（包方向纪律进生成层）**（用户批准："可以，你直接实现好了，我去看代码"）：
  - **问题**：两个内核的分发是手写 `switch`，成员与 `Model/PackageNames/*.xml`（每侧允许哪些包的白名单）各写各的；叠加 Spark `Protocol::OnRecv` 不做 PackageID 白名单（见 ❓ 条目），客户端伪造 `Rtn*`/`Notify*` 即可驱动内核。
  - **设计**：把"本内核分派哪些包、各自走哪条链路"落成两份内核清单（`Model/PackageNames/MdKernelPackageNames.xml` 7 条、`SimExchangeKernelPackageNames.xml` 12 条），由新模板 `../Templates/Cpp/Protocol/Kernel/KernelGen.cpp.tpl` 生成 `bool <Class>::DispatchPackage(Package*)`：`case` 只来自内核清单（不在全局 52 包中的条目渲染成 `pass`）；条目同时出现在链路清单（`<apipackages>`）且以 `Req` 开头时自动加"字段区为空即回绝"守卫，`Rtn*` 等内部/下行包不加。
  - **清单只写 name**（用户："只需要 name 就够了，handler 都是在 name 前面加一个 Handle"）：handler 默认按 `Handle` + 包名推导，**例外才写 `handler` 属性**（模板内 `handlerName = @handler or "Handle" + @name`）。逐条核对两内核 19 个条目：MdOffer 侧 **7/7 全部符合**；SimExchange 侧 **9/12 例外**——`RtnDepthMarketData→HandleDepthMarketData`、`RtnBarMarketData→HandleBarMarketData`（丢 `Rtn` 前缀），以及 7 个 `Req*→Handle<动作>`（`ReqAccountLogin→HandleAccountLogin`、`ReqAccountLogout`、`ReqInsertOrder`、`ReqCancelOrder`、`ReqQryOrder`、`ReqQryTrade`、`ReqQryInstrument`）。例外全部落在 SimExchange 手写文件里。**用户选择改名并把该方案落地（2026-09-12 同日）**：`HandleDepthMarketData→HandleRtnDepthMarketData`、`HandleBarMarketData→HandleRtnBarMarketData`、`HandleAccountLogin→HandleReqAccountLogin`、`HandleAccountLogout→HandleReqAccountLogout`、`HandleInsertOrder→HandleReqInsertOrder`、`HandleCancelOrder→HandleReqCancelOrder`、`HandleQryOrder→HandleReqQryOrder`、`HandleQryTrade→HandleReqQryTrade`、`HandleQryInstrument→HandleReqQryInstrument`（各含声明、定义、`WriteLog` 文案一处），改动面仅 `src/SimExchange/SimExchange.{h,cpp}`，无跨文件调用者。改后两份清单 **19/19 全部只写 name**，重跑 `pumpall.py`，生成物 19 处调用逐一与头文件声明比对一致（脚本校验，无缺失）。模板里的 `@handler or` 兜底分支保留（当前无任何条目使用），供后续内核出现约定外命名时就地覆盖、不必再改模板。本文件其余条目若出现这 9 个旧名，按上句映射对照即可（历史记录不追改，但注意：`src/BackTest/SimExchange.{h,cpp}` 也有 `HandleInsertOrder`/`HandleCancelOrder` 等同名函数，那是另一个类的，**未改也不该改**，勿按映射替换）。`src/BackTest/SimExchange.cpp` 的同名 handler 属另一个类，未动。
  - **单趟遍历而非三趟**（不照搬 SAMS 旧模板的 Admin/Trade/Kernel 三集合写法）：同一包若同时出现在两张清单里，三趟会生成重复 `case` 标签；本模板只遍历内核清单，用 `@name in wirePackages and @name.startswith("Req")` 就地判定。
  - **所有权语义进返回值**：`DispatchPackage` 返回 `true` = 包已用完可回收、`false` = Handler 接管。`MdKernel::HandlePackage` 与 `SimExchange::HandlePackages` 的 `switch` 整段删除，只留各自循环形态（`while (GetPackage())` / `for (i < 100) GetNextPackage()`）+ `if (DispatchPackage(package)) package->Deallocate();`；`needFree` 标志消失，`HandleRtnDepthMarketData` 中引用它的注释同步改写。`HandleXxx` 全部留在手写文件不动，头文件各加一行声明。
  - **守卫复用**：新增 `src/QuantTradingCommon/PackageReply.h` 的 `ReplyPackageParseFailed<RspPackageType>(Protocol*, SessionIdType, int)`（响应类型随请求包而变，故取模板参数；`ReqXxx → RspXxx` 名称对应在生成期完成），两内核共用，取代 SAMS 逐 case 展开的约 30 行守卫；`Send` 失败记 Error 后再回收包。
  - **行为变更（两处）**：① 外部链路来的 `Req` 若字段区为空，现在在分发处即回绝（`ErrorReqPackageParseFailed` 0x7000，`Error.h` 已有、无需改错误模型），不再进入 Handler——这正是 ❓ 条目里 `SimExchange::HandleAccountLogin` 未判空解引用（`:232/:240`）的可达路径，**该空指针自此不可达**，其余 6 个外部 `Req` 同为"只从网线来"，一并被守卫生效；各 Handler 内基于域内原因的判空分支（C3 补的 5 处）保留为纵深防御，对外链路已走不到。② `SimExchange` 的 `default` 日志文案由 `"UnExpect Package, PackageID:%d"` 统一为 `"UnExpected PackageID:%d"`。case 体由无括号单语句改为带括号块，类型转换沿用 `(T*)package`（与既有生成代码一致；转换点现已收敛到模板一处）。
  - **顺带核清三件**：① 字段成员名前提 52 包逐包核对——20 个 `Req*` 全部为 `XxxField* Xxx`（模板"按包名判空"由假设变为已核实）；`Rtn*`/`Rsp*` 有去前缀成员（`RtnOrder`→`Order`、`RspQryOrder`→`Order`），故判空只对 `Req` 生成。② `MdKernel::HandleReqMdUserLogout` 声明与定义俱全但旧 `switch` 里从无 case（`ReqMdUserLogout` 在 `MdApiPackageNames.xml` 里），**此前是死代码**——用户判定"应该补上使用"，已登记进内核清单，登出能力自此可用（客户端侧本就可发 `ReqMdUserLogout`、可收 `RspMdUserLogout`，此前只是服务端永不应答）。核对该 handler 行为：按**传输层** `SessionId` 清 `m_LoggedSessions`/`sessionSubscribeInstruments_` 与 Mdb 会话行，回 `RspMdUserLogout(ErrorNone)`；因键为传输层会话号，无法借此退掉他人会话；**未做**登录态检查（未登录即登出也回 `ErrorNone`），属幂等语义，暂不视为缺陷。**（同日补上调用点）**：核对发现仓内 `ReqMdUserLogout` **0 个调用点**——`test/TestMdApi` 只在 `OnConnected()` 里 `ReqUserLogin()`、`OnDisConnected()` 空实现，`ReqUnSubMarketData` 同样 0 调用点，故"服务端能应答"与"被真正使用"是两件事（该 API 的对外入口是 `MdCApi.h` 的 `MDAPI_CALL ReqMdUserLogout`，仓外程序调它才用得上）。经用户确认已在 `test/TestMdApi` 补冒烟：`main` 收到行情后调 `MdSpiImpl::ReqUserLogout()`，`OnRspMdUserLogout` 里**立即用同一条连接重登**——内核若没清掉 `t_MdUserLoginSession`，重登会回 `ErrorSessionAlreadyLogin`（0x2015），所以这次重登本身就是"登出清理"的验证（期望 `OnRspMdUserLogin` 第二次的 `RspInfo.ErrorId` 为 0；`MdSpiMiddle` 已打印 `RspInfoField:ErrorId`，无需另加日志）。随之把 `MdSpiImpl::requestId_` 由 `int` 改为 `std::atomic<int>`：登出是从 main 线程发出的（真实客户端本就在自己线程里调 Req*，"从用户线程发请求"正是该 API 的契约），而网络回调线程也会递增它，原为纯 `int` 即构成数据竞争。③ `ReqUnSubMarketData`（在 MdApi 链路清单里）全仓无 handler；`ReqQryAccount`/`RspQryAccount` 不在任何链路清单里（既无发送方也无接收方）——均保持原状，仅由此纪律暴露。
  - **"共用一份 PackageNames"未采用（用户："我原本是考虑 MdKernel 与 MdApi 公用一个 PackageNames……分开也是可以接受的"）**：核对后合并需要**逐条加角色标记**，反而是增属性而非减文件——`MdApiPackageNames.xml` 的 10 条里内核只分派 4 条（`ReqMdUserLogin`/`ReqMdUserLogout`/`ReqSubMarketData`/`RtnDepthMarketData`），`SimExchangeApiPackageNames.xml` 的 16 条里内核只分派 7 条（全部是 `Req*`），且**按名字前缀过滤会误判**：`RtnDepthMarketData` 内核分派（走内部产生路径）而 `RtnBarMarketData` 内核不分派（只作为下行发出），`RtnOrder`/`RtnTrade` 在链路清单里是**客户端收**、内核只发不派——若合并后按"Req*/Notify*/Rtn* 一律分派"会生成 `HandleRtnBarMarketData`/`HandleRtnOrder` 等不存在的函数（编译期即失败）。故维持两份：链路清单答"这条线上能收发哪些包"（客户端生成既有用途不变，内核侧借它判定"这个 Req 是否来自网线"以决定是否加守卫），内核清单答"内核分派哪几条、调谁、谁持有所有权"。两文件的 9 条外部 `Req` 重叠是**有意义的引用**（守卫触发条件即"在内核清单 ∩ 链路清单"），非重复定义。
  - **未覆盖**：`src/BackTest/SimExchange.cpp:275` 有同形状的 `HandlePackages` `switch`（4 个 case，全为 `BackTestApiImpl` 进程内直调、无会话概念、不继承 `ProtocolSubscriber`），本次未动——同为"清单驱动"的候选，但属另一个类，需单独确认。**顺带核对**：其 4 个 handler（`HandleRegisterAccount`/`HandleSubMarketDataFinished`/`HandleInsertOrder`/`HandleCancelOrder`）**0/4 符合 `Handle` + 包名**，若日后同样改清单驱动，需一并改名或就地写 `handler` 属性（这 4 处也是保留模板兜底分支的实证理由）。
  - **验证**：生成 `src/MdOffer/MdKernelGen.cpp`、`src/SimExchange/SimExchangeGen.cpp` 并逐 case 与旧手写 `switch` 核对（成员、Handler 名、返回值、日志文案全等，除上述两处有意变更）；`pumplist.xml` 已登记两条，`add_application` 的 `GLOB_RECURSE` 自动纳入、无需改 CMake。**未做**：编译与单测运行（按约定由用户在 VS 侧执行）；已把新增的 7 个 SimExchange 外部 `Req` 包补进 `test/UnitTests/PackageParseTests.cpp` 的"无字段区 → 指针为空"用例，钉住守卫依赖的解析层前提。
  - **风险（§7）**：`DispatchPackage` 的返回值即"谁负责 `Deallocate`"，而 `return false` 现在只由 `RtnDepthMarketData`（`MdKernel`，所有权交 `MdSnap`）一处触发；模型清单漏标或错标 `transferOwnership` 会造成 double free / 泄漏，故该属性必须与该 Handler 的实际所有权处理同步维护。新增外部 `Req` 包时若忘登记进链路清单，守卫会静默缺失（包仍被分派，缺字段区时不再被回绝）。

### D.39 · 2026-09-12 （第五批续） Python 绑定补齐 bar 周期字段

- **2026-09-12（第五批续）Python 绑定补齐 bar 周期字段**（用户："Python 的应该补上，Python 的接口应该与 C++ 保持一致"）：
  - **改动**（`src/PythonBindings/FieldsBindings.cpp`，约 6 行）：`BindEnums` 增补 `py::enum_<BarPrecesType>`（`Second`/`Minute`/`Day`）；`BarMarketDataField` 在 `instrumentId` 之后、按 `Fields.h` 的成员顺序补 `def_readonly("bar_preces", &BarMarketDataField::BarPreces)` 与 `def_readonly("bar_period", &BarMarketDataField::BarPeriod)`。枚举值命名沿用本文件既有约定（保留 C++ 枚举字面量 `PascalCase`，与 `DirectionType::Buy`/`OrderStatusType::PartTraded` 一致），字段名沿用 snake_case。属性类型即 C++ 侧类型（`BarPrecesType` 与 `IntType`），Python 侧不再"两种精度的 bar 长得一模一样"。
  - **输入侧无需改动**：Python 声明周期本就与 C++ 一致——`declare_bar_period("5m")` 对 `StrategyBase::DeclareBarPeriod(const char*)`，走的都是字符串解析（`ParseBarPreces`），不是枚举。
  - **验证**：以 Release 语义（`/O2 /DNDEBUG /MD /std:c++20`）+ pybind11 2.13.4 + `Libs/python/3.12/include` 重新编译两个绑定 TU，`RC=0`、零错误零警告（只编译不链接，理由见 ❓"Python 绑定构建前置未就绪"）。**未验证**：`QuantTrading` 目标的 CMake 配置与 `.pyd` 链接、以及 `.pyd` 导入后的实际取值——本机前置（`python -m pybind11 --cmakedir` 与 python libs）不可用。
  - **测试 I/O 示例**（pyd 构建可用后可直接跑）：

    ```python
    def on_bar(self, bar):
        # 未 declare_bar_period → bar 携带数据集精度；declare_bar_period("5m") → bar_period == 5
        if bar.bar_preces != qt.BarPrecesType.Minute or bar.bar_period != 5:
            return
        self.on_5m_bar(bar)
    ```

  - **风险标注（§7）**：纯绑定新增，不改任何 C++ 行为、不加锁、不涉及所有权；对既有 Python 脚本是纯增量（新属性出现，旧属性语义与取值不变），不存在破坏性变更。
  - **未做（仍待决策）**：`ReqSubMarketDataField`（订阅请求字段）未绑定。它不是策略面向 API 的一部分——Python 侧订阅周期经 `declare_bar_period` 字符串声明，与 C++ `StrategyBase` 完全对齐；若要让 Python 直接构造订阅请求，属新能力而非"补齐字段"，需先定接口形态。

### D.38 · 2026-09-12 （第五批） Release 前置 C 组修复

- **2026-09-12（第五批）Release 前置 C 组修复**（用户批准："先修 C 组 6 项"；已提交本仓 `0b07e60` + Spark 仓 `ae5b4b8`，均未推送）：
  - **C3 缺字段区空指针**（`src/MdOffer/MdKernel.cpp`）：`HandleReqSubMarketData` 补 `ReqSubMarketData == nullptr` 判空并按 `ErrorInstrumentNotExist` 回复；**同一缺口另有 4 处**一并补齐——`HandleReqMdUserLogin`（首处解引用在鉴权之前）、`HandleReqMdUserLogout`、`HandleNotifyDisConnect`、`HandleRtnDepthMarketData`（缺失时 `MinuteBar::OnDepthMarketData` 会按空指针取合约会话）。其中 Rtn 分支在 `HandlePackage` 中被置 `needFree=false`（所有权交 `MdSnap`），故丢弃路径须自行 `Deallocate()`，否则泄漏。
  - **可达性证据链（源码级）**：`StepUtility::HeadFromStream`（Spark `src/Network/Protocol/StepUtility.cpp:177`）缺 `BodyLen` 不报错（memset 后为 0）→ `PackageReader::ParseStepPackage` 只要求 header+BodyLen+tail 齐备且校验和匹配（校验和为累加和，客户端可算，非 MAC）→ `XxxPackage::FromStepStream(buff, headerEnd, headerEnd+BodyLen)` 的 `while (startIndex < endIndex)` 循环体不执行、在函数尾 `return true`，字段指针保持 `nullptr` → `Protocol::OnRecv`（`Protocol.cpp:139`）不做 PackageID/鉴权校验直接 `m_Subscriber->OnMessage(package)`（`m_ServerType` 仅用于 `IOFactory::CreateIO` 选 TcpServer/TcpClient）。即"只有包头、BodyLen=0"的报文能一路走到处理函数。
  - **C4 无界 `strcpy`**（`src/SimExchangeInit/ThostFtdcTraderSpiImpl.cpp`）：14 处裸 `strcpy` → `Utility::Strcpy`（按 `sizeof(dest)` 限宽，即 CTP 宽度），其前的 `::memset` 保留。字段宽度复核：BrokerId 16→11、UserId 32→16、UserProductInfo 32→11、AuthCode 64→17、Password 64→41 均"源更宽"（原必溢出），AppId 32→33 安全。
  - **C6 无超时死等**（`src/SimExchangeInit/Main.cpp`）：`while (!qryFinished_)` 加 600s 上限，超时记 ERROR 后仍走正常收尾（种子库可能不完整）。
  - **C5 Python 绑定试构建结论**：`src/PythonBindings/{QuantTradingBindings,FieldsBindings}.cpp` 是 Release 专属 TU（`CMakeLists.txt:266` Debug 跳过），此前从未编译过。以 Release 语义（`/O2 /DNDEBUG /MD`）配 pybind11 2.13.4 + Python 3.12 头文件与 Python 3.14 头文件**各编译一次，均零错误零警告**（先前的"2.13.4 不支持 3.14"担忧不成立）；`StrategyBase` 的 10 个虚函数与 trampoline 覆写一一对应无遗漏；`test/PythonStrategyGrid/grid_strategy.py` 的全部调用点参数个数与 C++ 签名吻合；`error_already_set` 构造即 `PyErr_Fetch`（错误指示器已清空），`what()` 与 shared_ptr deleter 均在 `gil_scoped_acquire` 作用域内，**无 GIL 缺陷**。**未验证**：`QuantTrading` 目标自身的 CMake 配置与链接——`CMakeLists.txt:269` 要求 `python -m pybind11 --cmakedir`，本机未 `pip install pybind11`；`Libs/pybind11/2.13.4` 只有 `include/` 与 python 包、缺 `share/cmake`，`Libs/python/3.12` 只有 `include/`（无 libs/exe），二者都不足以走通 CMake 路径。
  - **验证**：x64-Debug 全量构建通过（中途一次 `BackTestd.dll` 的 z-applocal 步骤报 `MariadbWrapperd.dll permission denied`，属文件占用，重跑即过，与改动无关）；`UnitTests` 101/101 用例、676/676 断言 SUCCESS；新增 `test/UnitTests/PackageParseTests.cpp` 把"包体无字段区时解析返回 true 且字段指针为空"钉成断言（5 个包 × 2 断言）——将来解析层若改为直接拒绝空字段区，该用例会失败并提示同步清理上述判空分支。
  - **风险标注（§7）**：改动全在事件循环单线程内，未加锁、未改协议、未改对象池实现与表的所有权约定；唯一涉及所有权的改动是 `HandleRtnDepthMarketData` 丢弃分支自行 `Deallocate()`（理由见上）。**未做 socket 级端到端复现**：畸形报文 PoC 需自建 Step 协议客户端，四项判断均为源码级论证 + 单测钉住解析前提，未实跑崩溃。

### D.37 · 2026-09-12 （第四批） DBAdapters 写库失败可见性

- **2026-09-12（第四批）DBAdapters 写库失败可见性**（用户批准："可以，去完善一下DBAdapters的日志输出吧"）：本地提交 `DBAdapters@416b0ac`（未推送）。原状即上一批复查的第六项——`DB` 接口全 `void`，四种 Wrapper 拿到失败原因（`sqlite3_open`/`sqlite3_step` 返回码、`sqlite3_errmsg`、stmt 有效性、`duckdb_result_error`、异常）后一律丢弃，回测 `DbType=1`(Sqlite) 路径因此"跑完没落库"与"落库成功"在日志里完全同形（全仓仅 4 处日志点，其中 `AsyncDBWriter.cpp:180` 只对抛异常的 MySQL/Maria 生效，SQLite 一律静默）。改动：新增 `include/DBAdapters/DBInterface/FailureLogThrottle.h`（首失败 + 每 1000 次上报一次并附累计失败次数；`LogOperationFailure` 统一按 wrapper/操作/表名/后端原生错误文本上报），四 Wrapper 逐语句接入，`BatchInsert` 另补 `FailedRecords:x/y` 整批规模（逐条上报会被节流掩盖总量，故单独汇总）；`AsyncDBWriter` 补连接失败上报（含积压条数、按固定重试次数节流）、`DisConnect` 丢弃条数、新增 `ThreadExit()` 上报"退出时仍未落库"条数、`HandleDBOperate` 的 catch 由 `catch(exception e)`（按值）改按引用并用 `SchemaRegistry::GetSchema` 解析表名。**行为变更**：`MariadbWrapper::Connect()` 由"抛 `sql::SQLException` 穿透 `AsyncDBWriter::Run()` → `ThreadBase::ThreadFunc`（无 catch）→ `std::terminate`"改为捕获记日志后返回 false（潜在崩溃，非本次需求）；`MysqlWrapper` 构造期建连失败仍抛出（语义不变，仅补日志）。**新增依赖**：四个 Wrapper DLL 私有链接 `Spark::Core`（`CMakeLists.txt` 四行），故 `DBAdaptersConfig.cmake` 安装后缺 `find_dependency(Spark)`。**验证**：`TestDB` 新增 `TestFailureVisibility()`（刻意打在不存在的目录/表上，属预期输出），`bin/Debug/TestDB.exe` 退出码 0，日志 `bin/Debug/Log/TestDB.20260912-180821.log` 实测出现 `SqliteWrapper: Open database failed. ... ReturnCode:14`、`EXEC skipped, database is not open.`、`INSERT failed. Table:t_test_tick, Error:no such table...`、`BATCH INSERT incomplete. Table:t_test_tick, FailedRecords:2/2`、`DuckdbWrapper: INSERT failed. ... Error:Catalog Error...`；既有四条用例（Tick / Vectorized / MultiChunk）输出与改前一致、无新增 ERROR。注意 `AsyncDBWriter` 不在 `TestDB` 的链接集内（`test/CMakeLists.txt`），其改动需显式 `cmake --build . --target AsyncDBWriter` 才编到（已单独重建通过）。
  - **未做（用户只批了 DBAdapters 侧）**：QuantTrading 侧"`OnMdEnd` 在 `Join` 之后汇总一行写了多少/是否落库"——DBAdapters 的 `ThreadExit` 已覆盖"没落库"的告警语义，此项可能已无必要，待决策。
  - **配套修复（Spark 仓，`9380bfa`，本地未推送）**：排查中发现 Spark `Logger` 没有"退出前最后一次落盘"——`FlushBuffers()` 全项目只在 `Run()` 内调用、`~Logger()` 是空体，故 Logger 线程最后一次 `Run()` 之后写下的日志永不入文件：各 `ThreadBase` 派生对象的 `ThreadExit` 行（含 `Thread:Logger Exit` 本身）与宿主 `Stop()` 后才写的收尾告警全部丢失，而 `LogData::~LogData()` 只是把未推送的缓冲区直接 `Deallocate`。修法（用户要求"在最合理的地方处理"）：`Logger::ThreadExit()` 在 `delete m_LogData` 前调新增的 `FlushRemainingBuffers()`（不做 `SwapInnerLogBuffers` 里那次最长 1s 的等待），并给 `WriteToLog()` 首行加 `m_LogData == nullptr` 判空（`Stop()`+`Join()` 后 `GetWriteLogFunc()` 仍指向 `Logger::Write`，任何后续 `WriteLog` 会解引用空指针——临时移除该守卫实测 `TestCore.exe` 段错误 exit 139，恢复后 exit 0）。实证（同 harness 改前/改后）：`Thread:Logger Start` 1 次 / `Thread:Logger Exit` **0 次** → 1 次 / 1 次；`test/TestCore` 去掉 `Stop()` 前那个 1s `sleep_for`（本缺陷的事实 workaround）。`UnitTests` 339/339 通过。**注意**：该修复只改在 Spark 工作区，`../Libs/Spark/x64-windows`（两个仓库实际链接的预编译库）尚未重新安装，故 QuantTrading/DBAdapters 当前的 `Cored.dll` 仍是旧行为——是否重装待决策（与 DBAdapters 是否 `cmake --install` 是同一类决定）。**未改的残留**：宿主若从不调用 `Stop()`/`Join()`，`ThreadBase::~ThreadBase()` 兜底 Stop+Join 时动态类型已降为 `ThreadBase`，虚调用落到 `ThreadBase::ThreadExit()`，`m_LogData` 既不落盘也不释放；最小修法是 `~Logger()` 补 `Stop(); Join();`，待决策。
  - **风险标注（§7）**：四 Wrapper 由"纯库"变为依赖 `Spark::Core` 的日志调用方（运行期多一层 DLL 依赖，安装包与 `find_dependency` 未同步）；`MariadbWrapper::Connect()` 的异常→false 是行为变更（影响写库线程的重试路径，不涉及数据正确性），可回退为原抛出；日志节流为"首失败 + 每 1000 次"，长时间故障期间中间态被抽样而非全量。未改：MySQL `Connect()` 恒真、各 Wrapper 的连接/重连语义、MySQL/Maria 的语句级日志（其异常经 `AsyncDBWriter` 的 catch 带表名上报）。

### D.36 · 2026-09-12 （第三批） 修复引擎侧聚合缺陷 4 项、撤回 1 项错误提议

- **2026-09-12（第三批）修复引擎侧聚合缺陷 4 项、撤回 1 项错误提议**（用户批准"前五项"中的 1/2/4/5 项实施）：
  - **① 聚合绑定键与查表键口径统一**（`src/BackTest/SimExchange.cpp:555`）：`BindBarAggregator` 的绑定键由 `mdSubscribe->RealInstrumentId` 改为 `mdSubscribe->InstrumentId`，与 `PushBarMarketData` 的查表键（`:384`）以及 `MdReader` 给 bar 打戳的字段（`MdReader.cpp:176`）对齐；`RealInstrumentId` 仍只用于 SQL 取数。Normal 合约二者本就相等（冒烟行为不变），`.Hot`/`.Second`/`.Third` 别名不再静默走透传分支。
  - **② 目标合法性预校验前移**（`src/Bar/BarAggregator.cpp:117-123`）：`IsValidBarPrecesTarget` 提到 `ValidatePrecesRelation` 顶部、置于同精度短路之前，使装载期预校验（`BindBarAggregator` 的 `try`）与首根 bar 校验共用同一完整判据。`Second` 目标与 `BarPeriod <= 0` 自此在装载期即被拒并记 Error 日志后走 `OnMdEnd()` 收尾，不再经同精度短路直通构造期、以未捕获异常逃出 `try`。
  - **③ `Insert` 返回值检查（两处）**：`PushNextBar`（`:377`）改为仅在 `t_BarMarketData->Insert` 成功后登记 `lastMdBars_`——失败即回池，原代码既写入悬空指针又读取已释放对象（结算价来源 `:844` 会取到它）；装载期 `t_MdSubscribe->Insert`（`:574`）改为先入库再入年份队列，失败则记 Warning 并跳过，避免行情读取线程拿已释放订阅取数（表内已记失败明细，不再重复打印记录内容）。
  - **④ 合约 upsert 的二次回池**（`:727-731`、`:749-753`）：两处同构块按 DRY 合并为文件内静态函数 `InsertInstrumentOrUpdate`，改为先 `Select` 再 Insert/Update。原写法在 Insert 失败（记录已被表 `Deallocate`）后仍对它 `Select`/`Update`——从未入表对象 `memcpy` 并二次回池。等价性依据：`InstrumentPrimaryKey::CheckInsert` 就是 `m_Index.find(record) == m_Index.end()`（`src/Mdb/MdbPrimaryKeys.cpp:194`），与按同键 `Select` 同判据。
  - **⑤ 撤回**：原建议"`FieldsCompare.cpp` 比较器补齐 `BarPreces`/`BarPeriod`"**经复核为错误方向，未实施**。该比较器实为"合约身份键"，两个消费方都不容忍周期敏感：`MdKernel::PushToAllSubscribed`（`:386-391`）用探针 `reqSubMarketData_` 做 `find` 路由 tick，而该探针在 ctor 中 `memset` 为 0 后只写 ExchangeId/InstrumentId，`BarPeriod` **恒为 0**——比较器一旦带上周期，带周期入集的会话就匹配不到探针，**行情推送会直接中断**；`subscribeInstruments_` 同时兼作"全市场订阅（周期 0）"与"策略订阅"的去重表，带上周期会让同合约产生第二条记录并触发重复 `SubscribeMd`。实时链路不消费周期的问题应在 `MdKernel::HandleReqSubMarketData` 层解决（记 Warning 或补周期），不该改身份键。
  - **验证**：`UnitTests` 100/100 用例、666/666 断言 SUCCESS——本批在"装载期精度预校验矩阵"新增 4 条断言，其中"数据集与目标同为 `Second`"（原会直通构造期）实测抛出 `invalid target preces`，`Minute 0`/`Day 0` 目标同样命中新判据。端到端以判别性周期复跑：`bin/Debug/TestStrategyGrid.json` 临时声明 `60m`（数据集仍 5m，SSE 午前 570 分钟 `570 % 60 != 0`），策略侧 61 个交易日的锚点价（当日首根 bar 的 Close）与 parquet 复原的 60m 桶收盘 **61/61 命中**、与 5m 透传假设 **0/61**；全期 2928 根 5m bar 恰为 244 个 60m 桶（61 日 × 4 桶）。临时配置已还原为 `5m`。
  - **风险标注（§7）**：③④ 触碰对象池所有权（Insert 失败即回池），改动仅为返回值判断与调用顺序，未改对象池实现、未新增锁、未改表的所有权约定；④ 的 `Select` 与 `Insert`/`Update` 各自加锁，两次调用之间存在 TOCTOU 窗口（与改前同样两次调用同窗口），且该路径仅在装载期单线程执行。**未被单测覆盖**：①③④ 位于 `BackTest` 模块内，`UnitTests` 不链接该模块（`CMakeLists.txt:211`），仅由上述端到端复跑与代码等价性论证覆盖；热门合约（`InstrumentId != RealInstrumentId`）路径无可用数据集，仍属"按设计修正、未实测"。

### D.35 · 2026-09-12 （第二批） 引擎侧聚合端到端实证 + 补齐 `TestStrategyGrid` 的 `Sessions.json` 

- **2026-09-12（第二批）引擎侧聚合端到端实证 + 补齐 `TestStrategyGrid` 的 `Sessions.json` 部署**：
  - **缘起**：用户补齐测试数据（`D:\MdBaoStock\Bar\Identity={SSE,SZSE}.Stock`，精度 `5m`）后跑通冒烟，要求复查项目其余问题。复查中发现上一提交（`e5fd794`）遗漏一处构建配置。
  - **缺陷（本提交引入，已修）**：`SimExchange::Init` 现在按 `BackTest.json` 的 `SessionFile` 硬装载交易节，装载失败 `WriteLog(Error)` 并 `return false`（经 `BackTestApiImpl::Init` 的 `simExchange_->Init() && simExchange_->Start()` 短路，不会带病启动）。而 `CMakeLists.txt` 只给 `TestBackTest` 加了 `copy_config_file(... Sessions.json)`，**`TestStrategyGrid` 漏加**——它同样链 `BackTestApiMiddleStatic` → 同一引擎、同一 `SessionFile`。当前不发作只因 `bin/<CONFIG>` 是共享输出目录，`MdOffer`/`TestBackTest` 的 POST_BUILD 顺带把 `Sessions.json` 落了进去；一旦单独构建 `TestStrategyGrid` 到干净输出目录，引擎会在 `LoadFromFile("")` 处失败拒启。已补 `copy_config_file(TestStrategyGrid .../Configs/Sessions.json)`，重建确认 POST_BUILD 已输出 `Copying config file .../Configs/Sessions.json to output directory`。
  - **端到端冒烟（补齐上一条目遗留的未验证项）**：数据集就位、范围 `20241001`–`20241231`、标的 `SSE.600519`。
    - **先证实"上一轮 5m→5m 冒烟走的是透传分支"**：数据集精度 `5m`、`BackTest.json` 与 `TestStrategyGrid.json` 声明同为 `5m`，`OnBarMarketData` 同精度同周期短路，**不建桶、不走聚合**；日志仅见 `TradeSessions: Trade sessions loaded. SessionCount:7, SessionFile:Sessions.json`（`TradeSession.cpp:184`，证明装载发生在 dll 内的引擎里）与 `ReqSubMarketDataField:ExchangeId:[SSE], InstrumentId:[600519], BarPreces:[1], BarPeriod:[5]`（`BackTestApiMiddle.cpp:56`，证明策略声明的周期已挂到订阅上）。
    - **再跑判别性用例**：把部署目录的 `bin/Debug/TestStrategyGrid.json`（`/bin` 已 gitignore，纯scratch，非源码）改为 `"BarPreces": "60m"` 重跑。60m 对 SSE 是**判别周期**——段首 570 分钟（09:30）不被 60 整除，墙钟网格（09:00/10:00/11:00…）与交易节网格（09:30/10:30/11:30…）不重合，而 5/10/15/30 均整除 570（这正是上一轮测不出回归的原因）。运行结果显著不同：`closedPairs:55 realizedProfit:550.0`（vs 5m 的 `40 / 430.7`），首日锚点由 `1889.07` 变 `1770.00`。
    - **三重比对定位对齐口径**：用 pyarrow 直接读 `Year=2024/2024_5m.parquet` 取 600519 的 5m 收盘，对回测区间前 5 个交易日分别算三种假设下的"首根 bar 收盘"——(a) 5m 不聚合 = `09:35` 收盘、(b) 60m 墙钟 = `09:00`–`10:00` 桶即 `10:00` 收盘、(c) 60m 交易节锚定 = `09:30`–`10:30` 桶即 `10:30` 收盘，与日志实测锚点逐一对照：

      | 交易日 | (a) 5m 不聚合 | (b) 60m 墙钟 | (c) 60m 交易节 | 实测锚点 |
      | :--- | ---: | ---: | ---: | ---: |
      | 20241008 | 1889.07 | 1852.15 | 1770.00 | 1770.00 |
      | 20241009 | 1675.00 | 1655.00 | 1638.95 | 1638.95 |
      | 20241010 | 1624.99 | 1608.00 | 1616.66 | 1616.66 |
      | 20241011 | 1631.72 | 1633.00 | 1618.01 | 1618.01 |
      | 20241014 | 1606.01 | 1592.81 | 1585.01 | 1585.01 |

      **5/5 命中 (c)、0/5 命中 (a)(b)** —— 声明周期确实端到端驱动了引擎侧聚合，且桶边界锚定在交易节段首而非午夜墙钟。这是上一批"未验证"项的正面闭环。
    - **单测侧的对应覆盖**（此前已存在，本次一并核实）：`BarAggregatorTests.cpp` 的 fixture 直接抄自提交版 `Configs/Sessions.json` 的 SSE 段（`925-930` 集合竞价 / `930-1130` / `1300-1500`），其中 60m 用例断言桶尾为 `1030`/`1130`（非墙钟 `1000`/`1100`）、45m 用例断言段末不满桶收口——与本次实盘数据结论一致。
  - **验证**：`UnitTests` 100/100 用例 662/662 断言 SUCCESS（提交版工作区复跑）；`TestStrategyGrid` 5m 与 60m 两次冒烟均退出码 0、有序关停、`Dump Completed`；`TestStrategyGrid` 单目标重建通过且 POST_BUILD 三份配置齐备。
  - **本次遗留（未修，供决策）**：① `Configs/SimExchangeInit.json` 的 `SessionFile` 键在 `Model/Configs/SimExchangeInit.xml` 无对应原型、`src/SimExchangeInit/Config/Config.h` 无声明，属死配置（不读不报错），可删可留；② `bin/<CONFIG>` 残留已退役目标的 `BackTestInit.exe`/`TestMdOffer.exe`（CMake 现仅 9 个 `add_application`，输出目录有 11 个 exe），仅本地产物、已 gitignore，但会误导"跑旧 exe 看新行为"；③ Python 绑定侧 `FieldsBindings.cpp` 未暴露 `BarPreces`/`BarPeriod`，且 `src/PythonBindings` 在 Debug 下不参与构建（CPython 官方解释器为 Release CRT），若后续在 Python 策略里依赖 bar 周期会静默缺字段而无编译期提示。**✅ 2026-09-12 已修前半个问题**：字段已补齐，见下方 ✅ 条目"Python 绑定补齐 bar 周期字段"；Debug 不构建 pyd 属构建约定，不变。

### D.34 · 2026-09-12 交易节去全局化 + bar 聚合下沉引擎侧 + 周期随订阅上报

- **2026-09-12 交易节去全局化 + bar 聚合下沉引擎侧 + 周期随订阅上报（用户拍板：要合理设计，不为减少改动妥协）**：
  - **缘起**：09-11 遗留的「`BarStatic` 被 `BackTestd.dll` 与策略宿主 exe 各链一份 → `TradeSessions` 进程内两份、装载与读取可落在不同副本」。用户明确否决"最小补丁"取向：`SessionFile` 是 BackTest 层配置，不该由策略宿主装载，且"策略与 BackTest 各自引用 Bar 库"本身就不是好设计，要求给合理方案。
  - **方案（用户批准"都一起做了"）**：① **`TradeSessions` 去全局**——静态成员（`m_Inited`/`m_SessionJsonString`/`tradeSessions_`）与静态方法（`LoadFromFile`/`ParseTradeSessions`/`GetTradeSession`/`GetTradeSessionForInstrument`）全部改实例成员，各运行环境各自持有一份（MdOffer 组合根持 MdOffer.json 的 `SessionFile`；回测引擎持 BackTest.json 的 `SessionFile`），双份问题从"两份不可见副本"变成"两份各有其主"，物理上不复存在。`ParseTradeSessions` 更名 `ParseFromJsonString(std::string)`（供不经文件的单测），`LoadFromFile` 失败返回 false 并 WriteLog，重复装载被 `RejectIfAlreadyLoaded` 拒绝（装载后内容不变是聚合器/MinuteBar 缓存 `TradeSession*` 的前提）。② **聚合下沉引擎侧**——`BarAggregator`/`MinuteBar` 由消费方注入 `const TradeSessions&`；回测链路的聚合从策略层移入 `SimExchange`，策略层不再链接 `BarStatic`（`StrategyStatic` 依赖面缩小为 `QuantTradingInterface QuantTradingCommonStatic Spark::Core`）。③ **周期挂在订阅上**——`ReqSubMarketDataField` 新增 `BarPreces`(BarPrecesType)/`BarPeriod`(Int)，`StrategyBase::DeclareBarPeriod("5m")` 存下值，后续每次 `SubscribeMarketData` 自动填；引擎在 `HandleSubMarketDataFinished` 按合约登记聚合器（同周期合约共用一个实例），未声明的合约纯透传数据集精度 bar。④ **MdOffer 侧一并做**（做后 `src/Bar` 才算真正无全局）：`MdKernel(mdb, tradeSessions)`、`MdOffer/Main.cpp` 组合根持 `TradeSessions` 局部量并装载。
  - **`ParseBarPreces` 迁 `QuantTradingCommon`**：策略层只做"字符串 → 精度/周期数"转换，不应为此链接 `BarStatic`；解析与目标合法性判据（`IsValidBarPrecesTarget`，Second 不可表达、周期数须 >0）落在 `QuantUtility.{h,cpp}`，策略的声明校验与引擎聚合器构造共用同一判据，避免两处规则漂移。
  - **装载期预校验替代引擎线程内抛异常**：聚合器首根输入才校验周期关系，而首根 bar 到达时已在引擎线程内——`ThreadBase::ThreadFunc` 无 try/catch，抛异常等于硬崩。抽出 `BarAggregator::ValidatePrecesRelation(inputPreces, inputPeriod, targetPreces, targetPeriod, instrumentId)` 公开静态（`ValidateInputBar` 改为一行委托），引擎在 `BindBarAggregator` 用 `mdReader_->GetBarPrecesType()/GetBarPeriod()`（数据集精度本就在手）预校验；不合法的订阅记 Error 日志后走既有"订阅为空"的收尾路径（`OnMdEnd(); return;`），不静默降级为数据集精度。为让该判据既能当"首根输入校验"又能当"装载期预校验"，补**同精度同周期短路**（透传分支直发不建桶），否则"数据集 1d + 声明 1d"会被误判为跨精度聚合而拒启。
  - **日切/收尾闭合残桶**：`ChangeTradingDay` 与 `OnMdEnd` 调 `FlushBarAggregators()`。漏掉前者会让交易日 N 的尾桶晚到交易日 N+1 的首根 bar 才收口、在 N+1 当天推给策略。
  - **单一 bar 出口（DRY）**：`PushBarMarketData(mdBar)` 把字段读进 `pushMdBar_` 一次，再按合约路由（无聚合器 → `OnBarMarketData` 直发；有 → 交聚合器，闭桶时经 `OnBarMarketData` 推出桶内 bar）。原 `SendRtnBarMarketData` 与新出口内容重复且只剩一个调用点，已删除（private 成员、非导出符号）；`OnBarMarketData` 成为唯一 `OnRtnBarMarketData` 推送点。
  - **`TradeSession::TradeSections` 改 `vector<unique_ptr<TradeSection>>`**（原 `vector<TradeSection*>`）：解析里 `new TradeSession()`/`new TradeSection()` 从不释放，属真实泄漏，改 `make_unique` 后由 `TradeSessions` 析构回收（Harness §6 RAII）。这是公开数据成员的类型变更——`TradeSession` 是库内部类（`src/Bar`，不随 `install(DIRECTORY include/)` 导出），影响面限于仓内。
  - **顺带清理**：`TradeSession.cpp` 的 `printf` 改 `WriteLog`；`ToString()` 由 `static char buff[1024]` + `sprintf` 改 `ostringstream` 返回 `std::string`；`MinuteBar` 的 `printf("NextTradeSection Not Exist")` 改 `WriteLog(Warning)`；新增字段后 `ReqSubMarketDataField` 的**未初始化构造点**（`TestBackTest/BackTestSpiImpl.cpp`、`TestMdApi/MdSpiImpl.cpp`、`MdOffer/MdKernel.cpp` 两处）补 `memset`——新字段带随机值会让引擎误判 `BarPeriod` 并走拒启分支。
  - **验证**：全量构建（含 `BackTestd.dll`/`MdOffer`/`TestStrategyGrid`/`TestBackTest`）零错误零警告；UnitTests **100/100 用例 662/662 断言 SUCCESS**（基线 99/643），新增「装载期精度预校验矩阵」（同精度透传、目标粗于数据集、非整除 5m→7m、数据集周期数 0 不触发除零、Day 目标跨精度、Day/Second 输入不可聚合）、「声明的周期随订阅请求上报引擎」（未声明 → BarPeriod 0；`5m` → Minute×5；`60m` → Minute×60），改写两个 StrategyBase 用例为"声明周期上报 + OnBar 原样透传"（聚合已在引擎侧，策略侧不再有可单测的聚合路径）。`TradeSessionTests.cpp` 的 `SectionOwner` 收紧为 `AddTradeSection(tradeSession, from, to, class)`（所有权归 `TradeSession`，返回裸指针仅供身份断言）。
  - **端到端冒烟（部分）**：`TestStrategyGrid` 与 `TestBackTest` 均正常启动，**引擎侧日志 `TradeSessions: Trade sessions loaded. SessionCount:7, SessionFile:Sessions.json`**（宿主已不再装载，证明交易节装载确实发生在 dll 内的引擎里，`SessionFile` 归于 BackTest 层这一意图达成），无 `rejected`/周期拒启日志。
  - **未验证（须补）**：本环境 `D:\MdBaoStock` 数据集缺失（`IO Error: No files found that match the pattern`），两个冒烟都在数据集发现阶段止步，**bar 流经引擎侧聚合器的端到端路径未跑通**。现有 5m 冒烟即便有数据也测不出桶对齐回归（SSE 570 分钟可被 5/10/15/30 整除，墙钟网格与交易节网格重合）——需非整除周期（45m）或夜盘品种（SHFE cu）才能暴露。**✅ 2026-09-12（第二批）关闭**：用户补齐 `D:\MdBaoStock` 后已用 60m 声明跑通并三重比对证实桶按交易节段首锚定，详见下方第二批条目。
  - **风险点**：① **线协议破坏性变更**——`ReqSubMarketDataField` 加字段，序列化按 ItemID 自描述但对未知 ItemID `return false`（"Unexpected ItemID:0x%X ... Please Check ApiVersion."），旧客户端解析新消息即失败；而 `GetApiVersion()` 仍返回 `QUANTTRADING_VERSION`(`1.0.0`)，**不随模型变更递增**，无法用它做兼容性判别（既有弱点，本期未动）。② `SimExchange::tradeSessions_` 声明必须早于 `barAggregators_`（聚合器持其引用），已按序；`MdOffer/Main.cpp` 的 `TradeSessions` 为 `main` 局部量、`MdKernel` 为 `new` 且不析构，靠"`mdKernel->Join()` 早于 `main` 返回"保证生命周期，未改其现有 `new` 风格（改智能指针属内存管理重构，须另行确认）。③ 桶内 bar 由聚合器内部存储发出（`&bucket.Bar`），指针仅在本次回调内有效——与既有"回调内有效"契约一致，跨回调暂存仍会悬空。

### D.33 · 2026-09-11 Bar 聚合器交易节锚定

- **2026-09-11 Bar 聚合器交易节锚定（对齐修复 + 交易节装载入口 + 日线拒聚合）**：
  - **缘起（用户三连纠正）**：① `AlignBucketEndMinute` 用 `barMinute % 10000` 取打包十进制 HHMM 当分钟数参与取模——时间是 60 进制（1500 应为 15*60=900 分钟），只有能被 40 整除的周期（5/10/20/40）碰巧正确，3m/15m/30m/60m 全错；② 桶边界必须按交易节而**非午夜墙钟**——"60m 线开盘 9:30，9:30-10:30 应是第一根 60m K 线"，且交易节信息本已存在（09-10 聚合器未接，"像被改丢了"）；③ `D:\Md` 是期货数据（9:00 开盘，交易节不一样），交易节跟交易所与品种走，源在 `Configs/Sessions.json`。
  - **30-进制/60-进制修复**：墙钟回退路径改 `TimeUtility::CalculateMinutes(hour, minute)` 折算真实分钟后再取模（旧实现 P=15 在 1305 处 delta=0 立即闭桶、P=60 在 1015 处少补 40 分钟）。
  - **交易节锚定（核心）**：`BarAggregator` 按合约缓存 `TradeSession*`（先 `GetUnderlyingID` 品种**精确匹配**、再按交易所 `"*"` 兜底——`Check` 是字面量匹配无通配语义，故 SHFE 的 `FD0900("*")` 不会抢走 `FD0100("cu","al",...)`；两路皆空则 Warning 一次并回落墙钟，按合约缓存 nullptr 避免逐 bar 重复查询与刷日志）。桶尾计算改由 `GetSectionBarTime` 给出**日期化**段起止（夜盘 From>1800 取前一交易日、To≥2400 换算为次日真实时刻），自段首起按目标周期逐桶 `MinuteAdd` 推进至覆盖当根 bar，**段末不满一桶钳到段末**（如 SHFE 日盘 9:00 开盘 60m：10:00 与 10:15 两桶）；换段即闭合故**午休不跨桶**；集合竞价段（`SectionClass=Auction`）落到其后首个连续竞价段（与行情侧 `MinuteBar::CalculateBarTime` 把竞价成交并入首根 bar 的约定一致）；段起止日期化后不含 bar 时回落墙钟（防数据集 TradingDay 约定不一致时静默算错）。
  - **日线目标改同精度透传 + 跨精度拒启**：日线是交易日历概念（午休/夜盘/法定假日）非定长分钟周期，名义桶尾无定义，且日线量额/结算字段无法由分钟 bar 等价重建；原实现因 `targetPeriod_=1` 使 `AlignBucketEndMinute` 返回自身分钟 → **每根输入即闭桶**（Day 目标退化为逐 bar 输出）。现首根输入即 WriteLog + 抛 `logic_error`（提示把 `BackTest.json BarPreces` 设为数据集日线精度），`CloseBucket` 的 Day 分支随之成为死代码并删除。
  - **交易节装载入口（此前完全缺失）**：`TradeSessions` 只有 `ParseTradeSessions`（吃静态 JSON 串，仅 MdOffer 手写 ifstream 调用过），无文件装载 API。新增 `TradeSessions::LoadFromFile`（幂等、打开/解析失败 WriteLog Error 返回 false、成功打 Info 落会话数），`MdOffer/Main.cpp` 手写三行改调它（DRY），`TestStrategyGrid/Main.cpp` 在**策略宿主侧**装载并失败即拒启。
  - **装载位置为何必须在宿主侧（原方案改正）**：`BarStatic` 是静态库，被 `BackTest`（`add_shared_module`，CMakeLists:159 PRIVATE）与策略宿主 exe（经 `StrategyStatic` PUBLIC）分别链接 → `TradeSessions` 静态成员**进程内两份**；聚合器运行在跑 `StrategyStatic` 的宿主侧，故在 DLL 侧（如 `BackTestApiImpl::Init`）装载宿主**看不到**。这是 MdOffer 路径之外新增装载点的硬约束。
  - **配置面**：`Model/Configs/TestStrategyGrid.xml` 增 `SessionFile` 项 → `pump.py` 再生 `Config.{h,cpp}`（仅 +3 行，BOM/行尾保持）；`Configs/TestStrategyGrid.json` 落 `"SessionFile": "Sessions.json"`（与 `BackTest.json` 同值同语义，必选键——缺失则打开失败拒启）；`CMakeLists.txt` 补 `copy_config_file(TestStrategyGrid .../Configs/Sessions.json)`。
  - **验证（单测）**：UnitTests **97/97 用例 632/632 断言 SUCCESS**（基线 90/567 → 净增 7 用例 65 断言），`BarAggregatorTests.cpp` 新增：60 进制墙钟回退（15m/30m/60m 三组，旧实现会分别错在 1305/1020/无关）、SSE 60m 会话锚定四桶（1030/1130/1400/1500，段末满桶 Flush 无残留）、SSE 45m 段末收口（1015/1100/1130）、SHFE 日盘段末尾桶（1000/1015/1130/1430/1500，含夜盘品种优先级：`ni` 走交易所级 `"*"`）、夜盘跨零点（cu/FD0100：202402292200/2300 + 202403010000/0100，前一日取 20240229 验证 GetPreTradingDay 跳周末）、日线跨精度拒启 + 同精度透传、`StrategyBase` 声明 60m 端到端收到锚定桶。用例各以 RAII 环境对象独立装载/清理交易节静态区（`"[]"` 表示不装载 → 走墙钟回退），避免跨用例残留。
  - **验证（端到端 + 独立交叉核对）**：`D:\Md` 1m 数据集（SSE/688581、20241101）+ 策略声明 5m + **真实 `Configs/Sessions.json`**：`Trade sessions loaded. SessionCount:7`、Replay 读 240 根 1m、锚定价来自 `OnBar`（证明 1m→5m 聚合 bar 经 `StrategyBase` 送达策略）、挂单回报正常、exit 0。另用 PyArrow 独立复算（不依赖引擎）拿 `600000` 同日的 1m→5m 聚合与 `D:\MdBaoStock` 的 **BaoStock 5m 参考表**逐桶对账：**48 桶时间戳 48/48 完全一致**（09:35…15:00），Open/High 48/48 相等、Low 46/48、Close 45/48、当根量 29/48（后四项差异源于 `D:\Md` 与 BaoStock 两路 1m/5m 源表本身的口径差，与对齐无关）——即新规则复现了市场通行桶尾约定。同日 1h 对照：数据集内旧 1h = 1000/1100/**1200**/1400/1500（1200 系午休横跨的伪桶），新锚定 = 1030/1130/1400/1500，旧墙钟实现 = 1030/1130/**1301**/1401/1500（断档处产生退化桶）——**时间戳语义变化即本次改动目的**，下游若有按旧戳对齐的产物需同步。运行时冒烟配置已复原。
  - **代码审查回合（code-reviewer，0 严重 / 1 高 / 3 中 / 6 低）已处理**：① **[高·DRY]** "品种精确匹配 + 交易所 `*` 兜底"原被复制成两份（`MinuteBar::ReqSubMarketData` 与 `ResolveTradeSession`，且两处对未命中的处理还不一致）——抽为 `TradeSessions::GetTradeSessionForInstrument(exchangeId, instrumentId)`，两处改调，告警/缓存留在各自消费方；② **[中]** 头文件原写"段内首根 bar 的分钟为首桶起点"与实现（锚段首）不符——改正措辞并补用例「首根 bar 迟到仍落在段首网格」（10:40 迟到→11:30 桶、14:05 迟到→段末 15:00 桶），坐实"与首根输入无关"；③ **[中]** `atoi(bar.TradingDay)` 改 `std::from_chars` 的 `ParseTradingDay`（空串/非法/非全数字返回 0 并 WriteLog Warning 后回落墙钟，不再静默按"0 年"推算日期），补用例「TradingDay 非法回落墙钟」；④ **[低]** 删单成员结构体 `InstrumentTradeSession`（`map` 的 `find` 本身已能区分"未解析/解析为 nullptr"）、`MdOffer/Main.cpp` 删无用 `<fstream>`、`TradeSession.h` 删无用 `<iostream>`、缓存成员补"静态区进程内只装载一次故不设失效钩子"与"键仅 InstrumentId"说明、竞价段注释补前提（行情侧已把竞价成交并入其后连续段首根 bar，竞价自身分钟会被包含性校验挡下回落墙钟）。⑤ **删 `<iostream>` 暴露的传递依赖**：`test/UnitTests/GridStrategyDaySwitchTests.cpp` 一直靠该头间接带入 `<stdexcept>`，已改显式 `#include <stdexcept>`（自包含）；全量 `all` 构建通过，无其他受影响文件。⑥ **未采纳**：`PrecesToSeconds` 的 Day/Second 分支在当前校验顺序下不可达，但保留其枚举全覆盖形态可避免读者误判 input>target 守卫对日线仍生效（评审亦标注非必须）；**day 目标拒启未前移到 `DeclareBarPeriod`**——该处只知目标、不知输入精度，前移会误杀"数据集 1d + 声明 1d"的合法透传，要真正在启动期判需引擎暴露数据集 BarPreces（属新增公开 API，需另行确认）。改后单测 **99/99 用例 643/643 断言**；增量复审（仅针对本轮修复自身）结论 0 严重/0 高/0 中、建议合入，其"`MdOffer/Main.cpp` 的 `<iostream>` 已无使用点"系误报（该文件 `Main.cpp:124` 仍在用 `cout`/`endl`，故保留）。
  - **遗留（09-10 三项收窄）**：① **关闭**（描述反向）：真正会拒启的是"输入精度粗于目标"（数据集 5m + 策略声明 1m）或非整除组合（5m→15m 的整除例外），受数据集所限未跑端到端，拒启逻辑已由单测覆盖；② **关闭**：`D:\MdBaoStock` 只有 BaoStock 5m（无 1d 交付物）本就是"对账基准不存在"，且 Day 目标已改同精度透传 + 跨精度拒启，"日桶时间戳对账"命题不再存在；③ WSL-GCC 完整构建仍受无 Spark x64-linux 预编译库阻塞，未补。
  - **新增遗留**：① 引擎侧（`MdReader`/回放）不消费交易节，`BackTest.json` 的 `SessionFile` 目前无消费方；根因是 `BarStatic` 导致 `TradeSessions` 全局进程内双份（见「待讨论」条，2026-09-11 记录待下周决策），当前装载点落在策略宿主侧而非用户本意的 BackTest 层；② 交易节未覆盖的品种/交易所（如 `D:\Md` 的 `SSE.Fund`/`SSE.Index` 无对应 `*` 条目？SSE 有 `*` 故覆盖）无节可用时按墙钟对齐并告警，属设计内降级而非缺陷。

### D.32 · 2026-09-10 （第二批） BackTestInit 退役

- **2026-09-10（第二批）BackTestInit 退役：账户前置注册 + RunID 独立输出库 + init 库降级可选**：
  - **必要性判定**（用户发起，结论：对回测不必要）：BackTestInit 4 张种子表中 t_TradingDay/t_Exchange 回测运行时零消费（死数据，6 家期货所硬编码无 SSE 属无害残留）；t_Capital 仅记录性（结算 EqualRange 空安全 + SettlementRoll 按日自建）；t_Account 唯一硬依赖（`HandleInsertOrder` 的 `ErrorAccountNotExist` 拒单分支，且账户 ID 与 BackTestInit.json 隐性耦合）。回测所需数据全部可由配置（StartTradingDay）+ 行情查询（Instrument/Product 经 ReadMdInstrument）+ 下单请求（AccountId）自举。
  - **账户前置注册**：包模型新增 `ReqRegisterAccount`/`RspRegisterAccount`（0x2001/0x2002，仅 AccountId 字段；XML 生成管线与 BackTestApi/BackTestApiImpl/BackTestApiMiddle 转发层由用户完成）。SimExchange 侧 `ReqRegisterAccount` 入 `packages_` 队列 → `HandleRegisterAccount` 幂等自建 Account+Capital（`QuantTrading::Account/Capital::Allocate` + memset 清零，Balance=0，TradingDay=tradingDay_）→ `SendRspRegisterAccount` 应答；`StrategyBase::Start` 在 `OnStart()` 之前自动注册（注册与下单同队列 FIFO，撮合检查账户时必已存在），C++/Python 策略零改动；裸 SPI 的 TestBackTest 在 `ReqSubMarketData()` 前显式 `ReqRegisterAccount()`。
  - **RunID 独立输出库**：`MakeRunId()`（本地时间到毫秒，`GetLocalTm` + chrono 毫秒）→ 输出库派生 `./BackTest_<RunID>.db`（扩展名前插入），Dump 快照隔离到 `<DumpPath>/<RunID>/`（`create_directories` 先行——Dump 用 fopen 不建目录）；多次回测互不覆盖、OrderId 每次从 1 起号（SeedNextOrderID 空库 no-op）、云上自动化单次运行单份归档产物；启动日志打印 RunID/DbHost/DumpPath。
  - **DbInitHost 降级可选**（同日稍后被彻底移除，见下条）：构造期做文件存在性检查（不能用 Connect 失败判断——SQLite/DuckDB 会静默建空库），存在才 CreateDataDb+Connect+LoadTables+SeedNextOrderID，缺失时 Warning+空表自举。
  - **BackTestInit 工程弃用**：CMakeLists 注释排除构建（源码与 Configs/BackTestInit.json 保留备查）。**2026-09-10 用户确认后彻底删除**：`git rm` 移除 `src/BackTestInit/`（6 文件）、`Configs/BackTestInit.json`、`Model/Configs/BackTestInit.xml`，pumplist.xml 三条生成泵与 CMake 注释块同步清理（`Model/TableNames/BackTestTableNames.xml` 被 src/BackTest 共用故保留），git 历史可随时恢复。**引擎侧 m_InitDB 路径同步拔除**（用户重生成配置：BackTest.xml 删 DbInitHost 项 → Config.h/.cpp 再生、BackTest.json 删键）：SimExchange 删 `m_InitDB` 成员、ctor 存在性检查块、Init 的 Connect/LoadTables/SeedNextOrderIDFromOrders 调用与 t_Capital TradingDay 覆盖环（init 库路径专属死代码）、`InitMdbFromDB.h` include——空库自举 + 账户前置注册成为唯一启动路径；`SeedNextOrderIDFromOrders` 函数与 OrderIDSeedTests 保留（仿真盘 src/SimExchange:66 共用）。
  - **验证**：UnitTests 90/90 用例 567/567 断言（新增 2 用例：注册先于订阅——requestId 1<2 且账户一致；单次 Start 恰一次注册）；TestStrategyGrid 双路径冒烟基线逐字一致（40 对/430.7/退出码 0）——init 库在→幂等跳过（Account already registered），挪走→空库自建（Account registered, TradingDay:20241001）；输出库实测 t_Account 恰 1 行自建 + t_Capital 62 行（注册日行 + 61 个结算滚动日，Balance 真实演进）；TestBackTest 空库自举冒烟 2928 bars/62 sessions/ErrorId 全 0/退出码 0；WSL-GCC `-fsyntax-only` 通过（补 DBAdapters 导出宏桩；chrono 毫秒值加 `static_cast<long long>` 消除 Linux 上 `%lld` 格式告警）。
  - **风险点**：① BackTestApi 加虚函数=vtable 变化，同构建树全量重编无碍，若有跨产物预编译部署须同步；② 每次运行新 DB 留磁盘文件，云上需配清理策略（本期不做）；③ RunID 秒级部分同秒并发启动理论可碰撞（已带毫秒后缀，实际回测运行分钟级，风险可忽略）。

### D.31 · 2026-09-10 策略层 Bar 周期聚合器

- **2026-09-10 策略层 Bar 周期聚合器（StrategyBase::DeclareBarPeriod）**：
  - **缘起**：三个「周期」概念此前混淆——①数据集精度（BaoStock 5m/实盘 MdApi 1m）②回放查询周期（BackTest.json BarPreces，09-09 落地）③策略期望周期（此前不存在，OnBar 被动接受②灌入的任何精度）。②被①绑架导致回测与实盘周期永远对不齐。方案（用户拍板）：查询周期归 BackTest.config（依赖数据源）不动；策略声明期望周期，由 StrategyBase 基类聚合。
  - **落地**：新增 `src/Bar/BarAggregator.{h,cpp}` 通用聚合器——构造 `(targetPreces, targetPeriod)`（Second 精度/周期 ≤0 拒启抛 `logic_error`）；`std::map<InstrumentId, Bucket>` 分桶；输入==目标透传直发；桶闭合四路＝到达名义桶尾/下一根越过桶尾（断档部分桶闭合）/TradingDay 变化（跨日重置）/Flush；输出 `BarTime=UpdateTs=名义桶尾分钟×100000`（Day 目标除外，保留末根输入时间待与 BaoStock 1d 对账）；`AlignBucketEndMinute` 复用 Spark `TimeUtility::MinuteAdd` 夜盘跨日进位（2356+4min→次日 0000 同桶，单测锁定）；OHLC/量账目合并全部复用 `BarUtility::UpdateBarFromBar`（原零调用者转正），**开桶整字段拷贝而非清零合并**（清零后合并丢 Low/LowestPrice 极值）。`ParseBarPreces` 从 `MdReader.cpp` 匿名空间原样上移至 `BarUtility`（bar 域语义归位，MdReader 改调用零行为变化；CMake 两行：StrategyStatic PUBLIC、BackTest PRIVATE 链 BarStatic）。`StrategyBase` 私有继承 `Bar::BarSubscriber` 桥接聚合输出至 OnBar，新增 protected `DeclareBarPeriod(const char*)`（"5m" 格式，解析失败抛 `logic_error`）；`OnRtnBarMarketData` 按开关分发，**未声明=纯透传（默认行为零变化）**；`OnRtnMarketDataEnd` 收尾 Flush 保证尾桶不丢。拒启语义（首根校验，`validated_` 门闩）：秒级输入/输出、Day→Minute、输入>目标、Minute 目标不整除 → WriteLog Error + 抛 `logic_error`（引擎线程 abort 形态见风险）。Python 绑定补 `declare_bar_period` 一行（Debug 构建按项目约定跳过 pyd，随下次 Release 构建验证）。
  - **乱序修复**：单测暴露桶仅记 BeginMinute 时「同分钟迟到/重复 bar」判不住（0932 之后到达的 0931 bar 不满足 `< BeginMinute` 被当新输入合并，当根量重复累加）——Bucket 改记 `LastMinute`（最后合并分钟，单调不减），迟到/重复判定收紧为 `barMinute <= LastMinute` 丢弃 + Warning（对齐 MinuteBar 迟到 tick 处理）。
  - **配置键接入（用户拍板：周期声明接进策略配置文件）**：策略配置加**必选**键 `BarPreces`（"5m" 格式，同 BackTest.json BarPreces 词汇；C++ 配置文件由 XML 原型生成、无可选参数语义，用户改定 `asString()` 直读，**配置缺失/为空即拒启**）——`TestStrategyGrid` 的 `Config` 解析 + `GridParams.BarPreces` 透传 + `GridStrategy` 构造期 `!empty()` 即 `DeclareBarPeriod`（非法格式构造期抛 `logic_error` 拒启，Main 无捕获与 Config::Load 抛错风格一致）；Python 版 `GridParams.bar_preces`（dataclass 缺省空串，`config.get` 可选读）在 `__init__` 内 `declare_bar_period`；`Configs/TestStrategyGrid.json` 落 `"BarPreces": "5m"`。TestBackTest 的 `BackTestSpiImpl` 是裸 `BackTestSpiMiddle`（不经 StrategyBase），不适用本次接入（未改）。新增单测：params 声明 "5m" 构造成功 + "5x" 构造期抛 `logic_error`。
  - **GridStrategy 补 bar 锚定（用户实测 SSE/600519 Bar 模式零交易根因修复）**：GridStrategy 原**纯 tick 驱动**——`OnStart` 订 tick、`OnTick` 取 `LastPrice` 锚定，而 Bar 回放（MatchMode=Bar）无 tick 回调 → `awaitingAnchor_` 永真 → 永不下单零交易（设计使然非回归，此前 IF2503 Bar 模式 0 交易同因）。修复：新增 `OnBar` 覆写——首根有效 bar 的 `Close` 为锚价补挂阶梯，与 `OnTick` 先到先锚（`awaitingAnchor_` 互斥），tick/Bar 双模式可跑；`TestHelpers.h` 增 `MakeMdBarField` 值类型工厂 + 单测「首根 bar 锚定/后续 bar 不重锚」。修复后用户场景（SSE/600519、Bar 模式 5m、`D:\MdBaoStock`）：**61 次日级锚定、364 次开仓挂单、closedPairs:40 / realizedProfit:430.7、期末 3 多 1 空、零 "zero remaining"、零真实错误（654 处 error 字样全为 ErrorId:0 成功回报）、exit 0**。注：利润非整步长倍数系 Bar 撮合价规则（挂单价≠成交价时按对手/收盘价成交）与股票 PriceTick=0 兜底组合的自然结果，策略按实际成交价记账自洽。
  - **新发现缺陷（遗留）**：tick 模式 + 无 tick 数据合约（如 SSE/600519 + `D:\Md`——Tick 目录仅 CFFEX.IC/IF/IM）→ 合约发现（Bar glob）成功但 tick 查询 `read_parquet` 空 glob 抛 IO 异常 → 引擎线程 `std::terminate` → **abort 退出码 3**（异步 Logger 缓冲丢失尾部日志，比「找不到合约」的优雅空跑路径更糟）。应在 MdReader/SimExchange 对零文件 glob 预检或捕获降级为空数据集。
  - **验证**：新增 `test/UnitTests/BarAggregatorTests.cpp` 12 用例（未声明透传/等周期直发/1m→5m 完整桶 OHLC+量账目/断档名义桶尾/跨日重置/夜盘跨日/Flush 收口/多合约分桶/首根与构造期拒启/迟到丢弃/StrategyBase 桥接含收尾）+ GridStrategy 配置键声明/拒启与 bar 锚定 2 用例；UnitTests **88/88 用例 560/560 断言 SUCCESS**（基线 74/478 → 净增 14 用例 82 断言）；TestBackTest 冒烟（SZSE/000001、Bar 模式 5m、`D:\MdBaoStock`）：62 组会话、2928 根、ErrorId 全 0、exit 0；TestStrategyGrid 双模式冒烟——tick（IF2503、OppositePrice、`D:\Md`，**配置已声明 BarPreces=5m**）：**closedPairs:161 / realizedProfit:1714.200000 / 期末 3 多 3 空 / 零 "zero remaining" / 零错误码 / exit 0 与基线逐字一致**；Bar（SSE/600519、`D:\MdBaoStock`）：见上。GCC 13.3 `-fsyntax-only` 五个改动/新增 TU 全过（本机 WSL 无 Spark x64-linux 预编译库，完整 GCC 构建不可行——`~/.vs/QuantTrading` 副本系旧环境遗留快照未动）。
  - **冒烟环境考古**（排障结论，非回归）：①IF2503 基线须跑 **tick 模式**——GridStrategy 是 tick 驱动（OnStart 订阅 tick、锚定价取自 OnTick 的 LastPrice），Bar 回放无 tick 回调 → 永不锚定 0 交易，设计使然；②Bar 模式+`D:\Md` 组合不可用——旧树 1m/1h/1d 混存无 5m，`Preces='5m'` 过滤后 0 行；③`D:\MdBaoStock` 现仅 SSE/SZSE 股票 5m（CFFEX 未迁入），TestStrategyGrid 的 Bar 模式冒烟待 CFFEX 数据落位。运行时配置已复原。
  - **遗留**：①负例端到端（策略声明 5m 跑 1m 数据集 → 启动即拒）未跑（拒启逻辑单测已覆盖）；②Day 目标日桶时间戳与 BaoStock 1d UpdateTs 格式待对账；③WSL-GCC 完整构建待环境具备后补验。

### D.30 · 2026-09-09 Bar 回放周期配置化

- **2026-09-09 Bar 回放周期配置化（BackTest.json 新增 `BarPreces`）**：
  - **缘起**：用户跑股票回测发现 Bar 回放 SQL 无周期字段/过滤。考古证实**非回归而是历史缺口**：`GetBarSqlString` 自 init 提交（`fd7afef`）起硬编码 `Minute/1` 且无 Preces 过滤，配置面从未有过周期键（全历史 grep 证实）；仅合约发现 SQL 曾有 `Preces='1d'`（f64eb99 按批准放开）。**实测旧 `D:\Md` 树单个 parquet 内 1m/1h/1d 三精度混存**——旧 Bar 回放一直把三种周期混着当 1 分钟跑，属潜在缺陷。
  - **落地**：`BackTest.json`（XML 原型生成，只存用户字段）新增 `BarPreces`，字符串与 Parquet `Preces` 列同格式 `<n><s|m|h|d>`（1m/5m/15m/30m/60m/1h/1d）。`Config` 按既有惯例仅作字段袋（对齐 `DbType` 字符串→消费方 `CreateDataDb` 转换的模式）；解析在唯一消费方 `MdReader` 构造时完成——`ParseBarPreces` 拆解为（`BarPrecesType` 枚举, 周期数）：s→Second、m/h→Minute（h×60）、d→Day，失败 WriteLog + 抛 `logic_error` 拒启；`GetBarSqlString` 第 4/5 列由解析结果填充并加 `and Preces = '<配置串>'` 过滤（同根多精度文件不再混入；`BarPreces`/`BarPeriod` 是行情主键组成部分，此前错标会污染 Mdb 去重）。首版曾把解析与 `1m` 兜底放进 `Config::Load`，用户纠正（配置文件由 XML 原型生成、不得承载解析语义）后移至 `MdReader`（`967bf47`）。
  - **验证**：BackTest 目标重编零警告；UnitTests 74/74 用例 478/478 断言保持基线；端到端冒烟（SZSE/000001、2024Q4、`D:\MdBaoStock`）：SQL 实测 `Select ..., 1, 5, ... and Preces = '5m'`，RecordCount 2928 与过滤前一致、ErrorId 全 0、exit 0；负例 `BarPreces:"5x"` 启动即报 `Invalid BarPreces...` 拒绝运行。
  - **遗留收窄**：原遗留①（Bar 回放 SQL 无 Preces 过滤、周期硬编码）中"过滤+周期配置化"部分已关闭；`MinuteBar.cpp` tick→bar 聚合的 `BarPreces=Minute/BarPeriod=1` 硬编码仍在（实时聚合另属 SimExchange 配置面），仅 Bar 回放不受影响。

### D.29 · 2026-09-09 QuoteHub

- **2026-09-09 QuoteHub：库重建溯源、分钟回补与量差明细报告**：
  - **库文件重建溯源**：`stock_data.db` 创建时间 2026-09-09 10:33（比用户 10:43 `--update-all` 早 10 分钟），昨日 8.2MB 旧库（含 34,848 根分钟 bar）整体丢失、分钟表归零；日线/基本面由当日 `--update-all` 重建。`D:\MdBaoStock` Parquet 交付物不受影响，回测照常。删除成因未查明（非本会话任何操作），已向用户标记留意。
  - **分钟回补**：用户执行 `backfill --start 2020-01-01`，分钟表回补至 233,424 根 bar / 4,863 交易日统计（3 只 × 2020~2026），年度文件 2020~2026 齐备。
  - **量差告警成因核实**（探针脚本 `probe_volume_mismatch.py`，一次性分析用，未入库）：`update`/`backfill` 日志中"分钟量与日量对不上"经逐日分类核实**非检测误判**（0 天累计口径误判），属 BaoStock 分钟/日线两套源表固有口径差——两个方向皆有（600000 2024：10 天分钟多 + 12 天分钟少；000001 2024：67 天全偏多，似该股系统性口径问题），幅度 ±1% ~ 7.29%；对回测无影响（Bar 撮合消费价格，量列文件内自洽，日线量仅用于口径监测）。另核实日志归属：告警在建文件时打出，属于其**下面**一行"写入"的年份。
  - **量口径明细报告落地**（QuoteHub `4508720`，用户三选一决策：明细 CSV / 按日线缩放 / 现状，取明细 CSV）：`build_bar_frame` 改为返回 (bar_frame, mismatch_records)，偏差 >1% 逐日记录；`export_bars_from_database` 统一写 `<period>_<freq>m_mismatch.csv` 到 Parquet 同目录（utf-8-sig 可直接 Excel 打开，按代码+日期排序，列 InstrumentId/TradingDay/MinuteVolumeSum/DailyVolume/DeviationPercent，正偏差=分钟多于日线），>5% 极端天逐日 WARNING，原"有 N 天对不上"告警改为指向明细文件。**验证**：`merge-year --year 2024` 离线重导行数不变（SSE 23232 / SZSE 11616），明细数与探针一致（SSE 28 = 22+6、SZSE 67），-7.29% 极端天告警触发；管线文档第 6/7 节同步。

### D.28 · 2026-09-08 回测行情源切换 BaoStock

- **2026-09-08 回测行情源切换 BaoStock（股票 Bar 数据链路落地）**：
  - **背景与决策**：原 `D:\Md` parquet 生产源断供。评估结论：BaoStock 完全免费但仅覆盖沪深 A 股 + 部分指数（无期货/期权、无 tick、无 1 分钟，指数无分钟线）；akshare 免积分但期货分钟线为新浪固定窗口（5m 约 1 个月）无法回补历史。决策：回测标的转向 A 股个股，用 BaoStock 5 分钟线 + Bar 撮合模式；导出器落在 `D:\Gitee\QuoteHub`（`BaoStockParquet.py`，新依赖 pyarrow，用户批准）。
  - **既有数据发现**：`D:\Md\Bar` 下已有旧源落好的股票 bar（`Identity=SSE.Stock/SSE.Fund`、`SZSE.Index`，2024-11 起，1m/1h/1d 混存、按天分文件、ProductId=代码前三位）——2024-11 之后的回测可直接用旧数据。
  - **QuoteHub 导出器**：BaoStock 5m+日线 → Bar parquet，24 列镜像既有文件类型（int64 时间戳、decimal128(24,8) 价格、ZSTD 压缩）；`UpdateTs`=bar 结束分钟（12 位，BaoStock 分钟 time 即结束时间）；Volume=日内累计/LastTraded=增量（按日自动判别累计口径并 diff 还原）；首根 PreClosePrice/PreSettlementPrice 取日线 preclose；分钟量合计与日线存在 ~0.4% 固有口径差（大宗交易/集合竞价归属），偏差 >1% 才告警；幂等合并（同 InstrumentId+日期段重跑覆盖）。输出独立根（默认 `D:\MdBaoStock`）——Bar 回放 SQL 无 Preces 过滤且按 `Identity=<EXCH>.*` 交易所前缀通配，与旧树混放会同窗口混精度重放。
  - **QuantTrading 改动**（用户批准）：`MdReader::GetInstrumentSqlString` 的 `Identity=CFFEX.*` 放开为 `Identity=*` 且删除 `Preces='1d'` 过滤——任意一行即可标识合约（CFFEX distinct 集合不变）；不改则股票合约无法发现、订阅被拒（`SimExchange.cpp:357`）。
  - **验证**：导出 600000/600519/000001 全年 2024（各 11616 根 = 242 交易日 × 48 根，0935→1500）；产出 schema 与既有文件逐字段一致。TestBackTest 端到端（SSE.600519、MatchMode=Bar、`MdDataPath=D:\MdBaoStock`、`DbHost=./BackTest600519.db` 独立运行库）：合约发现 3 只、600519 读 2928 根（61 交易日 × 48）、62 组 SessionBegin/End、406 笔成交、ErrorId 全 0、零告警、退出码 0；UnitTests 74/74 用例 478/478 断言保持基线；运行时配置已复原（CFFEX IF2503 OppositePrice）。
  - **使用方式**：`cd D:\Gitee\QuoteHub && python BaoStockParquet.py <子命令>`（缺省读 `config.json` stocks，输出 `D:\MdBaoStock`）；股票回测改 `BackTest.json`：`MdDataPath=D:\MdBaoStock`、`MatchMode=3`，`TestBackTest.json`：`ExchangeId=SSE/SZSE` + 6 位代码。
  - **导出器管线重设计（2026-09-08 同日，用户决策：SQLite 为事实源）**：`BaoStockParquet.py` 重构为四子命令管线，Parquet 不再做文件侧合并（旧"幂等掩码"按 InstrumentId+TradingDay 删行不区分 Preces，换频率重跑会误删跨精度数据——新架构下问题整体消解）：
    - `update`：增量拉取入库（续传起点=库中最后交易日本身，当日重拉自愈半截数据；主键 UPSERT 幂等），每个交易日写一个独立 Parquet（`YYYYMMDD_5m.parquet`，当月只增不改——Parquet 不可修改）；
    - `merge-month [--month YYYYMM]`（缺省上月）：整月从库导出 `YYYYMM_5m.parquet`，日度文件移入 `Year=YYYY/archive/`（重命名不删除，回放 glob `Year=*/*.parquet` 不扫描 archive 层）；
    - `merge-year [--year YYYY]`（缺省去年）：整年导出 `YYYY_5m.parquet`，归档月度/残留日度文件；
    - `backfill --start --end`：区间入库并直接写出年度文件（不产生日度文件）。
    - 库表：`MinuteBars`（PK Code+Frequency+Time）与 `MinuteBarTradingDays`（PK Code+TradingDay，存 preclose/日量额），`sql/upgrades/Update_v2.1.0.sql` 随 `BaoStock.init_database` 自动应用；文件名带频率后缀（四种频率可并存）；重写既有文件前做覆盖收缩双告警（既有 span 超出导出区间 / 超出库中数据）。
    - **验证**：测试根 D:\MdBaoStockTest 全链路（backfill→update→merge-month→merge-year→幂等重跑，行数 2784/1392 稳定，schema 与既有文件逐字段一致，覆盖告警两分支实测触发）；真实根迁移：旧 `2024_0.parquet` 移入 archive/，全 2024 回补后 SSE 23232 行/SZSE 11616 行与旧文件完全一致，600000/600519 七关键列逐行相等；TestBackTest 复跑（SSE.600519、Bar 模式、`MdDataPath=D:\MdBaoStock`）exit 0、ErrorId 全 0、2928 根/62 组会话/203 笔成交（此前记录"406 笔"为 OnRtnTrade+TradeField 两行模式的双重计数，实际 203）；运行时配置已复原（CFFEX IF2503 OppositePrice）。QuoteHub 提交 `1da468d`。
  - **遗留**：① Bar 回放 SQL 无 Preces 过滤、`BarPreces/BarPeriod` 硬编码 Minute/1——混精度树无法共存（独立根规避），将来合一需加 Preces 过滤与周期参数化；② BaoStock 停牌/零成交日仍产出平价 bar，Bar 引擎无量门控会按平价撮合（数据保真优先，暂不剔除）；③ `t_Product` 无股票条目，走兜底 VolumeMultiple=1/PriceTick=0/SessionName=FD0900（不影响 Bar 撮合正确性）。

### D.27 · 2026-09-08 配置明文凭证出库

- **2026-09-08 配置明文凭证出库（CtpAccountInfo 环境变量覆盖层）**：
  - **背景**：仓库托管在 Gitee **公开仓库**，`CtpAccountInfo.json` 匿名可下载——SimNow Password/AuthCode 实际已公开泄露，仅靠后续历史清理无意义，凭证轮换（用户在 SimNow 站点改密）才是根治；代码侧任务是让配置文件不再携带凭证。
  - **设计**（用户决策"覆盖层"）：`Environment` 语义不变（交易环境信息，与 OS 环境变量无关）；在 `ReadEnvironment` 末尾追加 `OverrideSecretsFromSystemEnvironment`——按环境名生成键 `CTP_<环境名大写>_PASSWORD` / `_AUTHCODE`（如 `CTP_SIMNOW_PASSWORD`、`CTP_SIMNOW24_AUTHCODE`），非空则覆盖内存中凭证字段，超长拒绝并跳过（不截断避免拼出错误凭证），无环境变量且配置为空时打 Warning 提示键名。`Configs/CtpAccountInfo.json` 两个环境的 `Password`/`AuthCode` 全部清空入库。
  - **验证**：Debug + Release 四消费方（MdOffer/SimExchangeInit/TestTraderApi/TestSimExchangeApi）构建零警告错误；`bin/` 下两份运行时配置确认无旧凭证（bin/ 已 gitignore）。功能冒烟：设置哑值环境变量运行 MdOffer → 4 条 `applied` Info 日志（两环境 × Password/AuthCode）齐全；不设变量运行 → 4 条 `Password/AuthCode empty ... Set CTP_xxx` Warning 日志齐全。
  - **用户侧待办**：SimNow 站点改密后 `setx CTP_SIMNOW_PASSWORD <新密码>`、`setx CTP_SIMNOW24_PASSWORD <新密码>`、`setx CTP_SIMNOW_AUTHCODE <新AuthCode>`、`setx CTP_SIMNOW24_AUTHCODE <新AuthCode>`（setx 仅对新开控制台生效）。
  - **范围外遗留**：各 `Configs/*.json` 的 `DbPassword`/`MdPassword`（开发库测试凭证，无外泄风险）与 git 历史中的旧凭证（改写历史需 force push，须用户书面授权；轮换后旧值作废，不建议做）。

### D.26 · 2026-09-08 OnConnected 状态恢复 + Spark Send 空守卫

- **2026-09-08 OnConnected 状态恢复（P1-1 应用层收尾）+ Spark Send 空守卫**：
  - **背景**：TCP 自动重连已由 Spark `TcpBase::TryAutoReconnect` 落地（Spark `9881aa6`，2026-09-07 晚），每次重连成功 `Protocol::OnConnect → ApiBase::OnProtocolConnect` 重设 `m_SessionID` 并重放 SPI `OnConnected()`。探索核实：各消费方补订/重登链路**已隐式闭环**（SimExchange `HandleRspMdUserLogin` 全量重放 `subscribeInstruments_`、TestMdApi 按全局 Config 重订、TestTraderApi/TestSimExchangeApi `OnConnected→登录` 自动重放、CTP 两侧 SPI 早已具备恢复；StrategyBase 回测无 TCP，`OnConnected` 不触发，实盘适配器维持未来工作）。真实缺口两项：断连窗口 Send 崩溃 + `isMdLogged_` 不复位。
  - **Spark Send 空守卫**（Spark `14b188b`）：`TcpBase::Send`（Select/Epoll 客户端与服务端共用）与 `TcpIocpBase::Send` 在 `GetConnect` 返回 nullptr 时 Warning 日志 + `buffer->Deallocate()` + 丢弃，修复断连窗口内任何 `Req*` 调用及服务端向刚断会话扇出回报的**空指针崩溃**；不改 `IOBase::Send` 签名；守卫路径必须 Deallocate（`Protocol::Send` 已移交池所有权，裸 return 永久泄漏池节点），对齐 `ShmBase::Send` 既有同型守卫。Spark GTest 339/339 通过，`cmake --install` 刷新 `D:\Gitee\Libs\Spark\x64-windows`。
  - **SimExchange MD 登录态复位**（`src/SimExchange/{SimExchange.h,SimExchange.cpp,MdSpiImpl.cpp}`）：`isMdLogged_` 改 `std::atomic<bool>`（原 `bool` 被 SimExchange 工作线程与 MD 客户端 IO 线程无同步读写，属既有数据竞争）；新增 `SimExchange::OnMdDisConnected()` 断连复位登录态，`MdSpiImpl::OnDisConnected` 直接调用（断连非包事件，`simExchange_` 在 `mdApi->Init()` 前必已 Set）。复位后重连闭环：3s 重连 → `OnConnected` → `ReqMdUserLogin` → `HandleRspMdUserLogin` 置位 + 全量重放订阅集（与首次启动同路径）；已知良性交错（旧连接迟到登录响应短暂置回 true）由 Spark 丢弃守卫 + 下次登录幂等重放自愈。
  - **六个 ApiBase SPI 判空**（用户决策一并修）：`MdApi`/`MdGbkApi`/`TraderApi`/`TraderGbkApi`/`SimExchangeApi`/`SimExchangeGbkApi` 的 `OnProtocolConnect`/`OnProtocolDisConnect` 将 SPI 回调包进 `!= nullptr` 判空（连接事件先于 `RegisterSpi` 到达不再空指针解引用；当前所有入口先 RegisterSpi 后 Init，不可达，纯加固，与 Spark 自身对 subscriber 判空惯例一致）。
  - 验证：Windows x64-Debug 构建 SimExchange/UnitTests 通过（本机 shell 无 ninja，经 VS 18 Insiders vcvars64 + 自带 ninja）；UnitTests **74/74 用例 478/478 断言 SUCCESS**（与基线一致）；`bin/Debug/Networkd.dll` 经 applocal 重拷新装 Spark DLL。**端到端冒烟通过**（2026-09-08，真实控制台用户执行确认）：`SimExchangeInit` 重建种子库（原 0 字节 `SimExchangeInit.db` 系历史中断遗留）→ `SimExchange` 重启装载后 `TestSimExchangeApi` 登录/查询正常，不再 4127/12294。冒烟过程顺带发现 `SimExchangeInit` 无超时死等缺口（见 ❓ 条目，已记录）。断连重连链路（Ctrl+C 杀 MdOffer → 3s 自动重连 → 重登 → 订阅集重放 → tick 恢复）与最后 SimExchange 的 Ctrl+C 有序关停亦经用户确认通过。

### D.25 · 2026-09-07 删除死代码 `GetMatchPrice`

- **2026-09-07 删除死代码 `GetMatchPrice`（三价取中近似）**：该函数自 `712e8bb` 引入起零生产调用（仅单测引用），其语义（成交价 = median(委托价, 对手一档, 最新价)）是回测平台无订单簿时的近似启发式——本项目 OrderBook 模式已实现真实交易所的 maker 价规则（成交价 = 被吃挂单价），三价取中无立足点；tick 模式定价维持各自文档化简化（LastPrice 按最新价、OppositePrice 按对手一档、Bar 按区间/中价），构成信息量递进谱系。删除 `OrderUtility.{h,cpp}` 定义与声明、`OrderMatchTests.cpp` 对应用例及 `<limits>` 包含。验证：Windows x64-Debug UnitTests 74/74 用例 478/478 断言 SUCCESS（较前恰少 1 用例 6 断言），全量构建 137/137 无警告错误。

### D.24 · 2026-09-07 H15 关闭

- **2026-09-07 H15 关闭：`OrderPriceTypeType` 精简（17→7 值）+ 四引擎市价语义落地**：Spark 类型 model 由用户改为 7 值——`LimitPrice`（受价吃簿、剩余挂簿排队；下单者出价的"市价转限价"与之逐模式等价，故不设显式转限价值）、`AnyPriceFAK`（不受价吃簿、剩余撤销）、`AnyPriceFOK`（预扫对手簿可成量，足额逐档全成或整单零成交撤）、`LimitPriceFAK`/`LimitPriceFOK`（受价版 FAK/FOK）、`BestOwnPrice`（按本方簿最优价入限价队列，空簿撤）、`BestOppoPrice`（按对手簿最优价成交，剩余挂该价，空簿撤）。消费端改造：`CheckForInsertOrder` 7 值白名单 + 量限按类分流（市价类走 `Max/MinMarketOrderVolume`，其余走 `Max/MinLimitOrderVolume`）；`OrderMatch` 基类 `InsertOrder` 转非纯虚标准体并新增共享设施（`AddOrderToLimitQueue`/`AddOrderToMarketQueue` 按值路由、`TryGetOwn/OpponentBookBestPrice` 簿窥探、`CountOpponentFillableVolume` FOK 预扫、`MatchMarketOrderAtPrice` 市价按值定价、`CancelOrderOnInsert` 统一 已报→已撤 回报序列、`CancelUnfilledImmediateOrders` 限价 FAK/FOK 首机会后置撤单模板）；`OrderBookOrderMatch::InsertOrder` 按值分派（**H15 缺口修复：FAK 剩余量立即撤销、不再滞留 `m_MarketBuy/SellOrders`**，BestOppoPrice 剩余挂解析价，`CheckMatchForTwoOrder` 价格守卫放宽为 `HasOrderPriceBound`）；三个 tick/bar 引擎删除各自 `InsertOrder` 覆写（基类接管），LastPrice 市价族按最新价/对方最优按盘口对手价（无效即撤）、Bar 对方最优按收盘价其余市价按 (High+Low)/2、OppositePrice 市价路径不变，三者限价队列均挂 FAK/FOK 首机会撤单。tick 模式无流动性模型：FAK/FOK/市价族首事件全额成交、剩余恒 0。新增 `test/UnitTests/OrderBookMarketOrdersTests.cpp` 13 用例（FAK 全成/部成撤/零成撤、FOK 足额逐档/预扫不足整撤、限价 FOK 受价预扫、限价 FAK 部成撤/零成撤、本方/对方最优入簿与空簿撤、校验量限分流）。验证：Windows x64-Debug UnitTests 75/75 用例 484/484 断言 SUCCESS；TestStrategyGrid 冒烟与基线逐字一致（161 对 / 1714.2 / 退出码 0）；TestBackTest 冒烟 62/62 日切、2238 笔成交、退出码 0。

### D.23 · 2026-09-04 Python 绑定落地 + 平台宏统一收官

- **2026-09-04 Python 绑定落地 + 平台宏统一收官**：新增 `src/PythonBindings`（QuantTrading.pyd：BackTestApi + StrategyBase 十钩子经 GIL 手动 `get_overload` 分发（Python 收快照拷贝、回退走基类指针路径）+ 9 字段类型注册）；绑定开关跟随构建类型（Debug 自动跳过——CPython 官方解释器为 Release CRT，非 Debug 自动启用，仅显式 `-DQUANTTRADING_ENABLE_PYTHON=OFF` 关闭）；`test/PythonStrategyGrid/grid_strategy.py` 为 GridStrategy 的 Python 移植，经回测冒烟验证；策略配置归集至 `Configs/TestStrategyGrid.json`（与 C++ 版共用单份），脚本与配置随 pyd 构建拷贝至 `bin/<CONFIG>`，运行方式 `cd bin/<CONFIG> && python grid_strategy.py`（`bd54728`）。平台宏统一五仓收官：QuantTrading 头文件 `WIN32→_WIN32`、Beacon/DBAdapters/Mdb CMake 平台块收敛为 `if(WIN32)` 最小块、Spark 源码 36 文件 115 处 `WINDOWS/LINUX→_WIN32/__linux__` 迁移（`cmake_minimum_required` 升 3.25 撑起 `LINUX` 变量）。

### D.22 · 2026-09-03 Order/Trade 回报字段拷贝提取

- **2026-09-03 Order/Trade 回报字段拷贝提取（DRY）**：`MdbFieldConverter` 新增 `MdbToField`（QuantTrading::Order→OrderField、QuantTrading::Trade→TradeField，memset 清零 + 逐字段映射）；替换回测/模拟盘共 6 处手写字段拷贝（SendRtnOrder / SendRtnTrade / SendRspQryOrder / SendRspQryTrade），净删约 170 行。关键点：QuantTrading::Order/Trade 比报文字段多库内字段（AccountType/OfferId/分组 ID 等），布局非镜像，**不走 `TryBulkCopy` 整块拷贝捷径**（代码注释已说明）；模拟盘四处原无 memset，统一清零仅影响 padding 字节（字段已全覆盖），回测侧原 memset 语义保留。验证：UnitTests 62/62 用例 399/399 断言 SUCCESS；TestStrategyGrid 冒烟与基线逐字一致（161 对 / 1714.2 / 退出码 0）；TestBackTest 冒烟 62/62 日切、2238 笔成交、退出码 0。用户决策：两个 SimExchange 的 HandleInsertOrder/HandleCancelOrder 校验段与 tick 落库 upsert 属各自业务代码，不提取。

### D.21 · 2026-09-03 结算库抽取 + 模拟盘运行期持仓维护

- **2026-09-03 结算库抽取（src/Settlement）+ 模拟盘运行期持仓维护**：
  - **模块**：新增 `src/Settlement`（SettlementStatic）三件套——① `PositionMaintenance::UpdateOnTrade`：开仓建/累计持仓与逐笔明细，平仓按 FIFO（OpenDate 升序、TradeId 同日次序）配对，写 CloseVolume/CloseAmount/CloseProfitByTrade/CloseProfitByDate（当日明细按 OpenPrice、跨日明细按 PreSettlementPrice），期权/证券/ETF 记 CashIn/CashOut，超量平仓告警并允许持仓扣负（与原回测行为一致）；② `Settlement::Settle(day)`：结算价源逐笔取价 → PositionDetail 盈亏三级计算（含期权 MarketValue）→ Position 聚合 → Capital 核算（Balance/Available）；③ `Settlement::RollToNextDay(day, nextDay)`：InitAccount/InitPosition/InitPositionDetail 跨日结转（已平明细、零持仓跳过）。结算价经 `SettlementPriceSource` 接口注入：回测 Tick 模式用 `MdbTickSettlementPriceSource`（行情 LastPrice → 行情 PreSettlementPrice → 明细 PreSettlementPrice，isinf/isnan 逐级回退），Bar 模式取各合约当日末根 bar 收盘价（`BarSettlementPriceSource`，嵌套于 backtest::SimExchange）。
  - **BackTest 等价重构**：`backtest::SimExchange` 的 OnTrade 持仓维护 / Settlement / Init 日切三段（约 240 行）整体删除改为委托结算库；逐字节等价移植并注释保留原有行为怪癖：加仓路径只累计 TotalPosition（TodayPosition 保持首开值）、结转路径不重置 Margin/CloseProfitByTrade/PositionProfitByTrade/MarketValue、原 Settle 中重复的 `CloseProfitByDate = 0.0` 去重（零行为变化）；排序仿函数随迁修正拼写（`PositionDetialLessForOpenDate` → `PositionDetailLessForOpenDate`），`src/BackTest/BackTestUtility.{h,cpp}` 两文件删除。
  - **模拟盘**：`SimExchange::SimExchange::OnTrade` 接入 `PositionMaintenance->UpdateOnTrade`，运行期持仓/开仓明细/盈亏字段实时维护（内存库内，与回测同构）；用户决策：模拟盘结算与日切仍不做，独立结算程序（应使用历史库）延后。
  - **单测 +11 例**（`PositionMaintenanceTests.cpp` 7 例 / `SettlementTests.cpp` 4 例 + `SettlementTestHelpers.h` 测试设施）：开仓建仓与明细、同向加仓（锁定 TodayPosition 移植基线）、FIFO 先开先平 + 跨日盈亏按昨结算、当日开平按开仓价、同日按 TradeId、超量平仓扣负、期权平仓 CashOut；Settle 三级盈亏 + 期权市值、Settle 聚合与资金核算（Balance/Available）、RollToNextDay 结转与过滤、MdbTickSettlementPriceSource 异常值逐级回退（LastPrice inf / PreSettlementPrice inf / 缺行情 / 全 inf）。
  - 验证（Windows x64-Debug）：UnitTests **62/62 用例、399/399 断言 SUCCESS**；`TestStrategyGrid.exe` 冒烟与基线**逐字一致**（closedPairs:161 realizedProfit:1714.200000、期末 3 多 3 空、零 "zero remaining" 告警、退出码 0）；`TestBackTest.exe` 冒烟 20241001→20241231 全程 62 次 SessionBegin/SessionEnd、2238 笔成交、零错误码、退出码 0。WSL-GCC 双平台编译本轮未跑（后续补验）。

### D.20 · 2026-09-02 OrderMatch 日切统一撤单 + 交易日切换 + GridStrategy 适配

- **2026-09-02 OrderMatch 日切统一撤单 + 交易日切换 + GridStrategy 适配**：
  - **引擎侧**（用户实现，本会话复核）：`OrderMatch::OnTradingDayChange`（public virtual）= `CancelOrders()`（protected，逐单调 `CancelOrder` 推送撤单回报；`VolumeTotal > 0` 守卫跳过已终态滞留单——OrderBook 模式无队列清理、全成单永久滞留，无守卫会被改判 PartTradedCanceled 造成状态污染）→ 翻转 `tradingDay_` → `maxTradeId_ = 0`（对齐交易所 TradeId 按日分配）→ 清空四张委托队列。BackTest `ChangeTradingDay` 在 `Settlement()` 前调用（撤单回报先于 SessionEnd/SessionBegin，撤单戳为旧日末笔行情时间）；`OnMdEnd` 收尾同样清算（传当前日，dump 显示终态）。
  - **模拟盘决策**：维持"不支持结算与交易日切换"（用户确认）——交易日经 SimExchangeInit 固化、运行期资金/持仓表不更新（无可结算实时状态）、结算结果无落库结转闭环，维持"每日停机 → 重跑 SimExchangeInit → 重启"外部流程；`src/SimExchange` 零日切改动。
  - **双重 OnTick 修复**：`src/SimExchange` `HandleDepthMarketData` 原在同一 tick 上调用两次 `orderMatch_->OnTick`，部分成交场景（市价量 > 对手量）第二次调用以同一 tick 对手量再成交、流动性被重复扣减；删除多余调用（保留与回测 `PushNextTick` 一致的先撮合后落库顺序）。
  - **GridStrategy 适配**（原"挂单跨日有效、日终不撤单"前提失效）：新增 `OnOrder` 覆写处理 Canceled/PartTradedCanceled——零成交开仓格复位 Empty（次日重锚重挂）、部分成交开仓格按已成交量即时补平仓、被撤平仓格按剩余量原价位重下（`CloseFilledVolume` 累计保留）；平仓价计算抽为 `UpdateClosePrice`（与满量成交路径 DRY）。测试设施上收 `GridStrategyTestHelpers.h`（`MakeGridParams`/`GridStrategyProbe`/`MakeCanceledOrderField`，消除跨文件重复定义）。
  - **单测 +4**（`GridStrategyDaySwitchTests.cpp`）：零成交撤单复位重挂、部成撤单补平、平仓单被撤重下（累计保留）、四格全撤重锚全量重挂。
  - **用户实测抓住适配引入的真 Bug（格位困死停摆）**：`GridSlot.CloseFilledVolume` 从未在复位时清零（三个复位路径只改 State），格位跨周期复用残留上周期值；旧代码下无害（结对待条件 `CloseFilledVolume >= OpenFilledVolume` 立即成立），但新加的 `HandleCloseOrderCanceled` 以 `OpenFilledVolume - CloseFilledVolume` 算剩余量被污染为 0 → "zero remaining" 分支放弃重下平仓单 → 格位带持仓困死 ClosePending，数日内全部格位困死、策略停摆（实证：20241106 起每日仅锚价 + 日结日志、零委托）。修复：抽 `ResetSlotToEmpty` 统一清净周期态（State + Open/Close ClientOrderId + 两个成交量字段），三个复位路径（SessionBegin Closed 复位、拒单复位、零成交撤单复位）全部收敛调用；"zero remaining" 分支保留为防御性告警（正常流此后不可达）。单测 +1 回归（配对完成 → 次日 SessionBegin 复用该格 → 新周期平仓单被日终撤 → 必须重下 1 手，修复前该用例少一笔委托插入即失败）。
  - 验证：UnitTests **51/51 用例、292/292 断言 SUCCESS**（Windows x64-Debug）；`TestStrategyGrid.exe` 冒烟 IF2503 三个月：161 对平仓 / 已实现盈亏 1714.2、期末余 3 多 3 空（末日 6 个 ClosePending 格位的平仓单被日终清算后重下、数据结束时尚未成交，预期）、全程零 "zero remaining" 告警、零 4115 零错误、退出码 0；末段交易日（12 月下旬）每日仍有 1-5 笔开仓，停摆消失。**注意：修复前的冒烟数字（73 对 / 779.2）受困死格位污染，不可作为基线。**

### D.19 · 2026-09-01 策略层抽象 StrategyBase + 网格策略 Demo

- **2026-09-01 策略层抽象 StrategyBase + 网格策略 Demo（TestStrategyGrid）**：
  - **`src/Strategy`（新静态库 `StrategyStatic`）**：`StrategyBase : protected BackTestSpi` 吸收策略脚手架——订阅两步走（ReqSubMarketData + Finished，RequestId 自增）、四向限价报单封装（自动填 AccountId/OrderPriceType/ClientOrderId）、`CancelOrder` 双路径（有回报缓存走 OrderId 主路径；未收到过回报的挂单——OppositePrice/LastPrice 模式引擎不推报单接受确认——走 `ClientCancelOrderId=ClientOrderId` 回退路径）、事件流维护的持仓/最新价视图、`OnRtnMarketDataEnd → OnEnd → api->Release` 生命周期收口（修正旧 Demo 的倒挂）。线程契约写入类注释：钩子均在引擎线程触发，内部状态无锁。`OnTrade` 钩子带 `clientOrderID`（TradeField 无此字段，经 OrderId 反查补齐）。
  - **`test/TestStrategyGrid`（新 Demo，不动 TestBackTest）**：成对网格策略（每格一开一平，利润 = 步长 × 乘数 × 手数），格位状态机 Empty → OpenPending → OpenFilled → ClosePending → Closed；日级重锚（SessionBegin 复位 Closed 格为 Empty，首笔有效 tick 为新中枢补挂）、**未成交格位跨日保留、日终不撤单**（引擎挂单跨日仍有效且会成交，撤单反而制造幻影风险，见下条冒烟发现）、平仓单价格取自开仓成交价 ∓ 步长与锚点无关、防重复补单（状态机守卫）。Config 经 pumpall 生成（`Model/Configs/TestStrategyGrid.xml` + pumplist 2 条目），参数结构 `GridParams` 不依赖生成代码以便单测直驱。
  - **单测 +13 例**（`StrategyBaseTests.cpp` 7 例 / `GridStrategyTests.cpp` 6 例，`FakeBackTestApi` 捕获 SPI 注册与 Req 请求）：订阅、持仓/最新价累计、撤单主/回退/拒绝路径、Release 幂等、首锚挂梯价格序列、成交补平仓恰一笔（重放不重复）、配对平仓归零、拒单次日电位重挂、ClosePending/OpenPending 跨日保留不重挂、Closed 格次日按新锚重挂。`TestHelpers.h` 增 `FakeBackTestApi` 与 `MakeMdTickField/MakeTradeField/MakeOrderField` 工厂。
  - **单测抓住 1 个真 Bug**：GridStrategy 原未重写 `OnSessionBegin`，日切后 `awaitingAnchor_` 恒为 false，次日永不重锚——已补上。另 UnitTests 定义 `BACKTEST_STATIC_DEFINE`（FakeBackTestApi 继承 BackTestApi 但不链接 BackTest DLL，消除 dllimport 符号）。
  - **冒烟发现（引擎行为实证，推翻此前代码阅读推测）**：首轮冒烟日终撤单 4115"委托不存在"——根因是 `SimExchange::HandleCancelOrder` 两条查单路径都以**当前** `tradingDay_` 为首键（`SimExchange.cpp:575-580`），而撤单请求经队列在日切翻日之后才被消费，前日订单必然查不到；同时 `Settlement`/`Init` 均不触碰 `orderMatch_`（构造时创建一次）→ **挂单跨日不清、价格到了仍会成交，只是跨日撤单永远失败**。据此修正策略：日终不撤单、未成交格位跨日保留原价位（fixed level 即网格语义），避免"复位 Empty 重挂 + 旧单仍活着"的幻影仓位。引擎侧修复（查单去掉交易日域或日切结算时统一撤单并推送回报）列入待决策（2026-09-02 已按方案②实现，见下文条目）。
  - 验证：**双平台全绿** —— Windows x64-Debug（vcvars64 + VS ninja）与 WSL-GCC-Debug 均编译通过，UnitTests 均 **46/46 用例、241/241 断言 SUCCESS**；`TestStrategyGrid.exe` 冒烟 IF2503 三个月数据：66 笔开仓 / 56 对平仓 / 已实现盈亏 613.8 / 期末双向持仓 0 / 全程零撤单零 4115 / 退出码 0（修正前 Closed 格不复活导致两天后停摆：15 笔 / 10 对 / 120.4）。

### D.18 · 2026-09-01 撮合引擎第二批单测 + OppositePrice 成交价方向修正 + 两处小修

- **2026-09-01 撮合引擎第二批单测 + OppositePrice 成交价方向修正 + 两处小修**：
  - **OppositePrice 成交价方向修正**（`src/OrderMatch/OppositePriceOrderMatch.{h,cpp}`，用户判定为 bug）：原实现买单按 `BidPrice1`、卖单按 `AskPrice1` 成交（本方价），与 README"对手价"语义相反——市价买单以买一价成交在任何微观结构模型下不成立；且 `Configs/BackTest.json` 默认 `MatchMode:2` 正用此模式，直接影响回测成交假设（买得更低、卖得更高，整体偏乐观）。改为教科书对手价：买单按 `AskPrice1`（守卫 `AskVolume1`）、卖单按 `BidPrice1`（守卫 `BidVolume1`），protected 方法改名 `CheckBidMatch/CheckAskMatch → CheckBuyMatch/CheckSellMatch`（对外接口不变）。TestBackTest 端到端冒烟重跑通过（全链路至 20241231 撮合/成交/结算/Dump 正常，成交价如 3925.2 限价单按对手价 3925.0 成交，符合修正后语义）。
  - **第二批单测**（`LastPriceOrderMatchTests.cpp` / `OppositePriceOrderMatchTests.cpp` / `BarOrderMatchTests.cpp` / `OrderIDSeedTests.cpp`，每文件 <200 行）：
    - LastPrice：市价单首个有效 tick 全额成交于最新价且不重复成交、限价按最新价成交、低于最新价不追价（挂单待回落成交）、无效 tick（LastPrice=+inf / Volume=0）与 OnBar 不触发。
    - OppositePrice（修正后行为基线）：市价买按卖一/市价卖按买一、限价按对手价成交与挂单后续成交、对手方无流动性或 +inf 不撮合。
    - Bar：限价在 bar 区间内按委托价、高于 bar 最高价按最高价成交（悲观假设）、低于 bar 最低价不成交直到触及（按触及 bar 最高价成交）、卖单对称（低于最低价按最低价）、市价单按 (High+Low)/2、OnTick 不触发。
    - OrderIDSeed（H17 回归）：`SeedNextOrderIDFromMaxOrderID` 只上移不拉低；`SeedNextOrderIDFromOrders` 从栈构 `OrderTable`（3 行订单，ClientOrderId 互异避免唯一键冲突，Insert 失败路径会 Deallocate）取最大 OrderId 续接；断言采用相对/隔离写法，不依赖用例执行顺序。
  - **测试设施 DRY**：`RecordingOrderMatchSubscriber`/`OrderPoolGuard` 自 `OrderMatchTests.cpp` 上收至 `TestHelpers.h`；新增泛型 `PoolRecordGuard<T>`（池记录登记回池）与 `MakeMdTick`/`MakeBarRecord` 行情工厂；`OrderPoolGuard` 改为复用 `PoolRecordGuard<QuantTrading::Order>`，`MakeOrder` 增加 `OrderPriceType` 参数支持市价单。
  - **yearMdSubscribes 泄漏修复**（`src/BackTest/SimExchange.cpp`）：`map<int, list<MdSubscribe*>*>` 改值语义 `map<int, list<MdSubscribe*>>`，消除按年 `new list` 随函数返回泄漏（元素仍归 `t_MdSubscribe` 表管理）；读取处 `auto` 改 `auto&` 避免整表拷贝。
  - **TestMdApi 等待改造**：`sleep(120s)` 死等改为 `RtnMdCount`（`MdSpiImpl::OnRtnDepthMarketData` 内原子计数）+ 120s 超时轮询，收到首笔行情即提前退出，超时打印提示（对齐 TestTraderApi 既有模式）。
  - 验证：**双平台全绿** —— Windows x64-Debug 与 WSL-GCC-Debug 的 UnitTests/BackTest(TestMdApi) 均编译链接通过，UnitTests 均 **33/33 用例、169/169 断言 SUCCESS**；TestBackTest 端到端冒烟（动态加载修正后 `BackTestd.dll`，默认配置即 OppositePrice 模式）重跑通过。

### D.17 · 2026-08-31 单元测试框架落地 + 首批用例

- **2026-08-31 单元测试框架落地（doctest v2.5.3）+ 首批用例**：
  - 框架选型：对比 gtest（vcpkg 路线）/ FetchContent / submodule 后采用 **vendored 单头文件**——doctest 全库即一个头，WSL 构建流不走 vcpkg、配置期零网络依赖，符合"单元测试越轻越好"的标准。`test/UnitTests/doctest/doctest.h`（v2.5.3，9148 行，MIT）+ `LICENSE.txt` 入库；仓库内 `parts/`（拼装脚手架）、`extensions/`（MPI 附加）、`doctest.cpp`（独立 TU 便利文件）均不需要。
  - CMake：根 `CMakeLists.txt` 新增 `add_application(UnitTests ...)`，链接 BarStatic/OrderMatchStatic（含传递依赖）与 Spark::Serialization（TradeSession.cpp 的 Json::Reader 链接符号）；零被测代码改动。
  - 首批用例（`Main.cpp` / `OrderMatchTests.cpp` / `TradeSessionTests.cpp` / `MinuteBarTests.cpp` + `TestHelpers.h`，每文件 <200 行）：
    - OrderMatch（OrderBookOrderMatch）：同价 FIFO（**H14 回归**：买盘队列同价按 OrderId 升序，修复前 LIFO）、卖盘同价 FIFO、价格优先吃穿多档深度、部分成交状态机、限价不越过（99 不成交/100 成交）、`GetMatchPrice` 三价取值分支。
    - TradeSession：无时段/仅集合竞价时段 `GetFirstBarTime` 返回 0（**H19 回归**，修复前空指针解引用）、日盘首根与时段起止 bar 时间、夜盘与跨零点（2400-2700）换算、`GetTradeSection` 边界与 <800 跨零点归属、`GetNextTradeSection` 跳过集合竞价、`ParseTradeSessions` JSON 解析与 `From/To<800 → +2400` 归一化。
    - MinuteBar：分钟内聚合并跨分钟闭合（OHLC/CurrVolume/CurrTurnover 账目）、仅集合竞价时段丢失 bar 合成不崩溃（H19 配套路径）、开盘跳档按交易时段合成丢失 bar（901-1435 共 320 根）、早于上一根 bar `UpdateTs` 的乱序 tick 被忽略。
  - 测试基础设施：`TestHelpers.h` 提供 `CopyString`（规范禁用 strcpy）/`MakeUpdateTs`/`LoadTradeSessionJson`/`ResetTradeSessions`（`ParseTradeSessions` 只 new 不 delete，测试侧配平）；撮合测试池对象经 `OrderPoolGuard` 在用例结束回池（`Match()` 的 newOrder/trade 副本所有权归订阅方）。
  - 契约发现（重要）：`OrderMatch` 引擎从不修改调用方传入的原始 `QuantTrading::Order`，撮合队列持有原始指针并**依赖订阅方在 `OnOrderUpdate` 中把 `newOrder` 状态写回原对象**（实盘/回测经 `t_Order->Update` 的 `memcpy(oldRecord, newRecord)` 落实）；不写回则同一挂单会被重复撮合。测试订阅者按此契约写回。
  - 用例修正记录：丢帧合成数量最初断言 320 系把 HHMM 当十进制连减误算（0901→1015 跨小时实为 75 根），引擎输出 200 根（75+60+65）经分段探针逐段核对正确；另 JSON 归一化期望 `To:230 → 2630`（初版误写 2700）。
  - 验证：**双平台全绿** —— Windows x64-Debug（vcvars64 + VS ninja → `bin/Debug/UnitTests.exe`）与 WSL-GCC-Debug（`~/.vs/QuantTrading` 远程副本，38/38 步含依赖库重建）均 **17/17 用例、101/101 断言通过**。

### D.16 · 2026-08-31 WSL-GCC 构建打通

- **2026-08-31 WSL-GCC 构建打通（缺 `<string>` 自包含修复 ×8）**：
  - 现象：WSL-GCC-Debug 全量重编时 `MdSpiImpl.h:14` 报 `'string' in namespace 'std' does not name a type`。
  - **与同日 CMake 改动无关（实验证明）**：用旧 Linux Debug 标志（`-DLINUX -D_DEBUG -O0 -g -ggdb`）编译同一 TU，报一模一样的错。根因是 `MdSpiImpl.h` 于 2026-08-24（`2bab7a2`）引入 `std::string` 成员后从未在 GCC 下编译过（MSVC 的 `<cstring>` 传递包含 `<string>`，libstdc++ 没有）；当日 CMake flag 变更触发全量重编才第一次在 GCC 踩到。
  - 修复：8 个"用 `std::string` 但未含 `<string>`"的头文件补 `#include <string>`（`SimExchange/MdSpiImpl.h`、`SimExchangeInit/{ThostFtdcTraderSpiImpl.h,Init.h}`、`Bar/{TradeSession.h,MinuteBar.h}`、`MdOffer/MdFront.h`、`BackTestInit/Init.h`、`BackTest/SimExchange.h`）；预扫 `std::vector`/`std::shared_ptr` 无同类缺口。
  - 验证：WSL-GCC-Debug 28/28 全绿（MdOffer/SimExchange/SimExchangeInit/BackTestInit/TestBackTest + `libBackTestd.so`），**真实 Linux/GCC 环境验证了 `LINUX` define 删除的正确性**（编译行已无 `-DLINUX`）；Windows x64-Debug 131/131 重建通过。修复文件经 cp 同步至 VS 远程副本 `~/.vs/QuantTrading` 后在 WSL 内 ninja 执行，VS 下次同步自动覆盖为相同内容。

### D.15 · 2026-08-31 CMake 全局标志整改

- **2026-08-31 CMake 全局标志整改**（`CMakeLists.txt`）：
  - 删除 `set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc /bigobj /utf-8")` 全局变异与按 config 重复的 `add_compile_options`/`add_compile_definitions`（`/Od /Zi /O2 /O1`、`-O0/-O3/-O2/-Os`、`NDEBUG` 均与 CMake 默认值逐项等价，`/EHsc` 本就在 MSVC 默认标志内，曾致 `/EHsc /EHsc` 重复）。
  - 改为平台分支：`if(WIN32)` 内 `add_compile_definitions(UNICODE _UNICODE _CRT_SECURE_NO_WARNINGS _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING)` + `add_compile_options(/utf-8 /bigobj)`（不设 `MSVC` 子门，按用户约定分流；`/bigobj` 供 Packages.cpp 等超段上限的生成文件）。WSL 实测（g++，即 WSL-GCC-* preset 环境）：`MSVC` 为空、`UNIX=1`——撤 `MSVC` 门对 Linux 构建无影响，Windows 构建 FLAGS 与改前逐字节一致。
  - **`WINDOWS`/`LINUX` 平台 define 删除**（当日二次评估）：C++ 侧平台判断统一为编译器内置宏（`ShutdownSignal.cpp` 改 `_WIN32`）。Spark 源码虽 15+ 文件使用 `WINDOWS`/`LINUX`，但由 **Spark 自身构建**的 CMake 定义解析，与其消费者无关；消费者侧核查为零引用——QuantTrading 全目录零引用，Spark 公共头仅 `Platform.h:3` 一处 `#ifdef LINUX`（经 `Core.h` 传递包含，仅声明 `Spark::Core::GetLastError`/`WSAGetLastError`，QuantTrading 零调用，声明消失无影响），DBAdapters/Templates 零引用。`elseif(UNIX)` 空分支一并移除。
  - 生效核对（build.ninja FLAGS）：Debug `/DWIN32 /D_WINDOWS /EHsc /Zi /Ob0 /Od /RTC1 -std:c++20 -MDd /utf-8 /bigobj`（重复 `/Od /Zi` 消除）；Release `/DWIN32 /D_WINDOWS /EHsc /O2 /Ob2 /DNDEBUG -std:c++20 -MD /utf-8 /bigobj`（`/O2`、`NDEBUG` 由默认提供）。Linux Debug 的 `-ggdb` 与 `_DEBUG` 因全库（含 Spark/DBAdapters 头）零引用而删。
  - x64-Debug / x64-Release 全量编译链接验证通过（各 131/131 步；删除两个平台 define 后 x64-Debug 再次全量重建通过，DEFINES 已无 `-DWINDOWS`）。本机 shell 无 ninja，验证经 VS 2022 Enterprise 自带 ninja + vcvars64 执行；x64-Debug 缓存 `CMAKE_MAKE_PROGRAM` 已固化为该 ninja 路径（与 VS 所用一致，无副作用）。

### D.14 · 2026-08-27 评审修复 H13–H19

- **2026-08-27 评审修复 H13–H19（OrderMatch / SimExchange / Bar）**：
  - **H13 BackTest 包队列数据竞争**（`src/BackTest/SimExchange.{h,cpp}`）：测试线程 `ReqXxx` 对 `reqSubMds_`/`packages_` push、SimExchange 线程 `HandlePackages`/`HandleSubMarketDataFinished` pop/读/清均无锁 → 数据竞争。新增 `queueMutex_`（`#include <mutex>`），4 处 push 上锁；`HandlePackages` 锁内 `swap` 出队、`HandleSubMarketDataFinished` 锁内 `swap reqSubMds_` 后处理，对齐实盘 `OnMessage`/`GetNextPackage` 既有模式。**附带修复同函数池泄漏**：重复订阅/找不到合约两条 `continue` 路径跳过 `::Deallocate(reqSubMd)`，补回池。
  - **H14 买盘同价 LIFO 违反 FIFO**（`src/OrderMatch/OrderUtility.cpp`）：`OrderLessForPriceOpposite` 同价 tiebreak `OrderId >` 使最新单先成交（LIFO）；改 `<`，与卖盘 `OrderLessForPrice`（`OrderId <`）一致，同价转最早单优先（价格-时间优先）。
  - **H15 OrderBook 市价单（用户决策：仅文档化，代码零改动）**：`CheckMatch` 只遍历对手限价队列，`m_MarketBuy/SellOrders` 滞留无消费；且 `OnTick/OnBar` 为空实现，该模式本就无价格驱动撮合，属整条路径缺口而非单点 bug。经用户确认不修代码，列入待办（见 ❓）。
  - **H16 实盘 `OnTick(mdTick)` 悬垂**（`src/SimExchange/SimExchange.cpp`）：`InitMdbFromDB::LoadTables` 不调 `InitDB()` → `m_DBInited==false`；实盘 `Update(oldMdTick, mdTick)` 走 `else→Deallocate()` 释放 `mdTick`，随后 `OnTick(mdTick)` 悬垂（回测 `PushNextTick` 顺序正确，先 OnTick 后落库）。改为 `OnTick` 移至 `Insert/Update` 之前；`HandleBarMarketData` 同理（`OnBar` 提前于 `Insert`）。
  - **H17 OrderId 计数器无种子**（`src/OrderMatch/OrderUtility.{h,cpp}`）：`GetNextOrderID()` 静态从 0 起，而实盘/回测均从 init DB 装载 t_Order，重复回测或装载历史单时主键冲突。计数器改文件级静态 `g_MaxOrderID`，新增 `SeedNextOrderIDFromMaxOrderID`/`SeedNextOrderIDFromOrders`；回测 `SimExchange::Init`、实盘 `SimExchange::Init` 在 `LoadTables` 后从 t_Order 最大 OrderId 续接。
  - **H18 BackTest `new`→池不匹配**（`src/BackTest/SimExchange.cpp`）：`new MdSubscribe/Capital/Position/PositionDetail` 后被 `Mdb.Insert` 池回收 → 分配器不匹配/堆损坏；改 `X::Allocate()`（与 `CreateOrder`/`CreatePosition` 模式一致，`Allocate()` 值初始化 + `memcpy` 覆盖）。
  - **H19 `GetFirstBarTime` 空指针解引用**（`src/Bar/TradeSession.cpp` + `src/Bar/MinuteBar.cpp`）：无 `Section` 段时 `GetFirstTradeSection()` 返回 `nullptr`，`tradeSection->From` 崩溃；加空守卫返回 0，`CheckHasLostBar` 调用侧对 `lostBarMinuteTime <= 0` 直接返回，避免合成 0 时伪造丢失 bar。
  - x64-Debug 编译链接验证通过（2026-08-27）：OrderMatchStatic/BarStatic 重建，MdOffer.exe、SimExchange.exe、BackTestd.dll 均成功（TestBackTest 动态加载新 BackTestd.dll）。

### D.13 · 2026-08-27 评审修复 H10/H12

- **2026-08-27 评审修复 H10/H12（Mdb 模板）**：
  - **H10 对象池分配器不匹配**：`Templates/Cpp/Mdb/InitMdbFromCsv.cpp.tpl` 的 `new !!@name!!()` → `!!@name!!::Allocate()`；`MdbTables.cpp.tpl` 的 `InitDB` 内 `new !!$structName!!(**it)` → `!!$structName!!::Allocate()` + `memcpy`（与 `BatchInsert` 既有模式一致）。此前 `new` 分配的对象被 DB 订阅者经池 `Deallocate()` 回收 → 分配器不匹配/堆损坏；`ObjectPool<T>::Allocate()` 无参 placement-new `T()` 值初始化，与 `new X()` 零初始化语义完全一致，行为保持。重新 pump 生成 `src/Mdb/MdbTables.cpp`、`src/Mdb/InitMdbFromCsv.cpp`。
  - **H12 InitDB 空守卫**：`InitDB()` 无 `m_MdbSubscriber` 守卫，`OnRecordTruncate`/`OnRecordBatchInsert` 直接解引用 → 无订阅者时空指针崩溃；改为无订阅者提前返回（置 `m_DBInited=true`），并将锁作用域收敛到拷贝循环（对齐 `BatchInsert`，避免持共享锁调用订阅者回调）。重新 pump 后 x64-Debug 编译链接通过（MdOffer.exe）。
  - **H11 读方法锁契约（用户决策：仅记录文档，代码零改动）**：`Select`/`SelectAll`（主键）与 `LowerBound`/`UpperBound`/`EqualRange`（索引）内部 `std::shared_lock` 只保护查找本身，返回的裸指针/迭代器在锁释放后被使用。核查结论：全库无 `LockShared()` 调用者（无嵌套加锁死锁），表访问按模块串行化（MdKernel 单线程、SimExchange 各自 `mutex_`），**当前无活跃 bug，属潜在设计缺陷**。经用户确认不做代码改动，契约仅记录于此：**返回的指针/迭代器仅在调用方间串行访问表（无并发 Erase/Update/Truncate）时有效**。未来交易链路接入时若需跨线程改表，须在调用方持锁或改返回语义。x64-Debug 编译链接通过（MdOffer.exe）。

### D.12 · 2026-08-27 安全修复 S1–S4

- **2026-08-27 安全修复 S1–S4**（先修安全问题，按类型/名称过滤 + 配置驱动）：
  - **S1 行情日志脱敏**（模板 `Templates/Cpp/LibTest/CtpWrapper/StructLogFunc.cpp.tpl`，重新 pump `src/Ctp/StructLogFunc/StructLogFunc.cpp`）：定义 15 个 CTP 敏感类型集合（`TThostFtdcPasswordType`/`*KeyType`/`*AuthKeyType`/`*AuthenticDataType` 等），日志生成按类型过滤 Password/Key/Token 字段，逗号与字段均受保护；497 处 WriteLog 格式串/实参 0 失配，无敏感字段名残留。`WriteReqUserLogin` 不再打印 Password/OneTimePassword。
  - **S2 Environment 输出修复**（`src/QuantTradingCommon/Environment.cpp`）：`PrintEnvironment` 不再打印账户 `Password`/`AuthCode`（只输出 BrokerId/InvestorId/Phone/UserProductInfo/AppId）；`ReadEnvironment` 解析失败路径不再 `in_file >> s; std::cout << s;` 倾倒配置文件内容；输出全部改走 `WriteLog`（4 个调用点均在 Logger 启动后）。
  - **S3 Config 模板密码过滤**（`Templates/Cpp/Config/Config.cpp.tpl`，重新 pump 9 个 `src/*/Config/Config.cpp`）：`Print()` 顶层/记录字段/子记录三处统一按 `@name.lower().endswith('password')` 过滤（配置模型为扁平 string/int，无法按类型过滤）；9 个模块的配置文件打印不再输出 `DbPassword`/`MdPassword`。
  - **S4 MdOffer 种子用户配置化**（`Model/Configs/MdOffer.xml` + `Configs/MdOffer.json` + `src/MdOffer/Main.cpp`）：删除 `Main.cpp` 6 个死常量（sqliteDBName/duckdbDBName/mysqlHost/mariadbHost/mariadbUser/mariadbPassword）；`t_MdUser` 种子记录改由 `MdUserId`/`MdPassword` 配置驱动，`MdUserId` 为空时跳过插入（杜绝空凭证记录，防"空 UserId+空密码"登录）；默认值 `MdUser`/`123456` 与 `TestMdApi.json` 一致，测试登录不受影响。重新 pump 后 `Config.h` 新增两字段，`Print()` 按 S3 过滤不打印 `MdPassword`。**记录用 `MdUser::Allocate()` + `Utility::Strcpy` 逐字段填充**（MSVC 的 C++20 括号聚合初始化无法用字符串字面量初始化 `char[N]` 数组成员，初版 `new MdUser(...)` 触发 C2440；改用对象池分配，与 `Insert` 失败时表调用 `Deallocate()` 回池的契约一致）。x64-Debug 编译链接通过（MdOffer.exe）。

### D.11 · 2026-08-24 BackTest 端到端验证

- **2026-08-24 BackTest 端到端验证**（TestBackTest，`D:\Md` 旧格式 parquet）：MdReader 读 tick/bar → OrderMatch 撮合（IF2503，20241001-20241231，61 根日 Bar、10 月 45 万+ tick）→ 结算 → 落库全链路跑通。注意：数据为旧列名格式，MdReader SQL 的 NULL 占位符与 `AskPrices[1]` 等旧列名兜底正是为此而设；撮合/结算正确性由 `GetSettlementPrice` 对 +inf 回退 + OrderMatch 涨跌停校验注释保证，数据真正对齐 mdb 前该回退不可移除。

### D.10 · 2026-08-24 P1-1 重连路径并发修复 + 优雅退出

- **2026-08-24 P1-1 重连路径并发修复 + 优雅退出**：
  - **并发修复**（`src/MdOffer/ThostFtdcMdSpiImpl.cpp`）：`OnRtnDepthMarketData` 反查 `reqSubMds_` 改同锁 `find()`（消除 `operator[]` 键缺失插入副作用）；`OnRspUserLogin` 重连补订改锁内取 `reqSubInstruments_` 快照后批量订阅。
  - **优雅退出**（新增 `src/QuantTradingCommon/ShutdownSignal.{h,cpp}`，改 `src/MdOffer/Main.cpp`、`src/SimExchange/Main.cpp`）：Windows `SetConsoleCtrlHandler` / Linux `signal(SIGINT/SIGTERM)` 仅置位原子标志；main 尾部由阻塞 Join 链改为「轮询退出标志 → 按依赖序 Stop/Join」。MdOffer 顺序：mdApi Release → mdKernel → mdFront → dbWriter → Logger；SimExchange：mdApi Release → simExchange → tradeFront → mdFront → dbWriter → Logger。
  - 依据库源码核实：所有 ThreadBase 派生线程 `Run()` 均以 `wait_for`/`select` 超时兜底，`Stop()` 后 ≤100ms 退出；`AsyncDBWriter` 退出前刷完剩余 `m_DBOperates`。全量 x64-Debug 编译链接通过，MdOffer.exe 启动冒烟通过；Ctrl+C 交互验证待真实控制台执行。

### D.09 · 2026-08-13 API 测试客户端

- **2026-08-13 API 测试客户端**（`test/`）：
  - ApiMiddle/SpiMiddle 封装由新模板 `Templates/Cpp/ApiTest/*.tpl` + `Model/Packages/Packages.xml` 生成（`test/ApiMiddles/{Md,Trader,SimExchange}ApiMiddle`），注册为 3 个静态库；`TestMdApi`/`TestTraderApi`/`TestSimExchangeApi` 三个测试 exe 均编译链接通过。
  - **安全修复**：`ApiMiddle.cpp.tpl` 生成日志时排除 `Password` 字段（逗号与字段均受 `@name != 'Password'` 保护），三个封装登录不再打印明文密码（原打印 UserId/AccountId + Password）。
  - **健壮性修复**（TestTraderApi/TestSimExchangeApi）：`instrument_` 裸指针 + `new` 泄漏 → 值成员 + `hasInstrument_` 标志（消除泄漏与空指针解引用，查询无 CFFEX 合约时不再发单）；`ReqQryOrder`/`ReqAccountLogin` 补 `memset` 清零脏字节；`Main.cpp` 的 `while (!Finished)` 死等加 120s 超时兜底。
  - 遗留：`TestMdApi` 仍硬编码 `sleep(120s)`；C# 模板 `TableViews.razor.cs.tpl` 仍引用 `@withtradingday`（C# 侧计划整体重写，暂缓）。

### D.08 · 2026-08-13 放弃按 TradingDay 单日导入，数据初始化改走专用 Init 库

- **2026-08-13 放弃按 TradingDay 单日导入，数据初始化改走专用 Init 库**：
  - 决策背景：原计划按表支持 `withtradingday` 导入某一天历史数据，但该属性是表级全局的，无法表达"同一表在 A 模块按日导入、B 模块全量导入"的按（模块 × 表）差异，且 `TypedTable` 仅提供 `SelectAll`，无法扩展按日查询。故整个功能废弃。
  - 数据初始化输入改为各应用已有的专用 Init 库（`DbInitHost` → `initDB` → `LoadTables` 全量 `SelectAll`），按日过滤职责从加载层前移到数据准备层，天然支持按模块差异。
  - 清理：`InitMdbFromDB.{h,cpp}.tpl` 移除 `!!if @withtradingday == 'true':!!` 条件段，加载器统一固定 2 参 `(Mdb*, DB*)`；`Model/Tables/ShortTables.xml` 中 `DepthMarketData` / `BarMarketData` 的 `withtradingday="true"` 属性移除。重新 pump 后生成文件无内容变化（本就为 2 参），x64-Debug 编译链接通过。

### D.07 · 2026-08-13 TableList 按模块落地

- **2026-08-13 TableList 按模块落地（从共享核心拆分）**：
  - 共享类型：`src/Mdb/TableList.h`（`struct QuantTrading::TableList`，去掉复数 `s`）；旧 `src/Mdb/TableLists.h` 删除，共享核心不再包含任何应用专属表集合，依赖方向修正（核心不感知消费者）。
  - 各模块清单落各自目录：`src/MdOffer/MdOfferTableList.h`（7 表）→ `QuantTrading::MdOfferTableList`、`src/SimExchange/SimExchangeTableList.h`（14 表）→ `QuantTrading::SimExchangeTableList`、`src/BackTest/BackTestTableList.h`（15 表）→ `QuantTrading::BackTestTableList`。
  - 去掉 `TableLists::` 复数命名空间，调用点直呼变量名（`Mdb(MdOfferTableList)` 等）；文件按"模块名 + TableList"命名，避免与共享 `TableList.h` 同名 basename 冲突。
  - 模板：`TableLists.h.tpl` → `TableList.h.tpl`（纯类型）+ 新建 `ModuleTableList.h.tpl`（模型仍为各 `Model/TableNames/XxxTableNames.xml`）；`pumplist.xml` 拆为 1 条核心条目 + 3 条模块条目。
  - x64-Debug 编译链接验证通过（2026-08-13）：MdbStatic、MdOffer.exe、SimExchange.exe、BackTestd.dll 均成功重建。

### D.06 · 2026-08-13 Mdb 按需装配

- **2026-08-13 Mdb 按需装配（on-demand assembly）**：Mdb 运行时从"全量 18 表"改为"按各模块 TableList 装配自己的表"：
  - `Mdb` 构造改为 `explicit Mdb(const TableList&)`，构造时按 `TableList.TableIDs` 只 `new` 本模块的表并存入 `m_Tables`（`std::vector<MdbTableBase*>`）；未装配表成员初始化为 `nullptr`，各 bulk 方法（Subscribe/UnSubscribe/InitDB/SetInitStatus/Dump/TruncateTables/OnDbDisConnected）统一遍历 `m_Tables`。
  - `MdbTableRegistry` 删除全量单例 `Instance()` 与默认构造，改为 `MdbTableRegistry(const TableList&)` 按模块过滤 schema（`m_TableIDs`/`m_Schemas`）。`AsyncDBWriter` 经 `GetAllSchemas()`/`GetTableCount()`/`GetSchema()` 取本模块 schema，故 **CreateTables / DropTables / TruncateTables 及所有写入只作用于本模块的表**；越界表 `GetSchema` 返回 `nullptr` 被跳过，机制上杜绝模块访问非本模块表。
  - `InitMdbFromDB` 删除 `LoadTablesWith/WithoutTradingDay`，统一为 `LoadTables(Mdb*, DB*, const TableList&)` 调度器；`InitMdbFromCsv` 的 `LoadTables` 改为 TableList 门控（`LoadTables(Mdb*, const char*, const TableList&)`）。
  - 装配点：`MdOffer/Main.cpp`、`SimExchange/Main.cpp` 用 `Mdb(MdOfferTableList)` / `Mdb(SimExchangeTableList)` + 局部 `MdbTableRegistry` 传 `AsyncDBWriter`；`BackTest/SimExchange.{h,cpp}` 新增成员 `registry_(BackTestTableList)` 并将 writer/Mdb 改用之。
  - 8 个模板同步（独立仓库 `D:\Gitee\Templates`：`Cpp/Mdb/Mdb.*.tpl`、`MdbTableRegistry.*.tpl`、`InitMdbFromDB.*.tpl`、`InitMdbFromCsv.*.tpl`），重新 pump 生成 `src/Mdb` 对应 8 文件并核对。
  - x64-Debug 编译链接验证通过（2026-08-13）：MdbStatic、MdOffer.exe、SimExchange.exe、BackTestd.dll 均成功重建（BackTest 阻断已随此前提交消除）。

### D.05 · 2026-08-13 Mdb 表类基类重构 + 表清单生成

- **2026-08-13 Mdb 表类基类重构 + 表清单生成**：
  - 新增 `MdbTableBase`（`src/Mdb/MdbTableBase.h`），上收各表重复的 `m_DBInited` 及 Subscribe/UnSubscribe/InitDB/TruncateTables/Dump 公共接口；`src/Mdb/MdbTables.h` 由模板重新生成（全部表类改为 `public MdbTableBase` 并加 `override`）。
  - 新增 `src/Mdb/TableLists.h`：按 MdOffer / SimExchange / BackTest 分组输出表 ID 清单（`TableList` 结构 + `TableLists::MdOffer/SimExchange/BackTest`），`pumplist.xml` 已登记生成条目；当前尚无消费方，为后续统一 Mdb 管理预留。
  - 模板侧改动位于独立仓库 `D:\Gitee\Templates`（`Cpp/Mdb/MdbTables.h.tpl` 已改、`Cpp/Mdb/TableLists.h.tpl` 新建，未提交）。
  - x64-Debug 全量编译链接验证通过（2026-08-13）：MdbStatic、MdOffer.exe、SimExchange.exe、BackTestd.dll 均成功重建。

### D.04 · 2026-08-10 MdReader 复用 mdb `GetSchema`

- **2026-08-10 MdReader 复用 mdb `GetSchema()`**（按用户决策，数据源将统一到 mdb 表结构）：
  - 删除本地投影 schema（`InstrumentReadFields`/`TickReadFields`/`TickReadSchema`/`InstrumentReadSchema`）与三个 factory，统一复用 `Instrument::GetSchema()` / `DepthMarketData::GetSchema()` / `BarMarketData::GetSchema()`；分配/追加回调收敛为通用模板 `MakeVectorizedRecordFactory<T>()`。
  - SQL 按 mdb 字段序 + mdb 列名重写（含 61 列 tick 全字段、15 列 instrument 全字段；Bar 也由 `LastTraded/LastTurnover` 改为 `CurrVolume/CurrTurnover`）。
  - **数据源依赖**：当前 parquet 缺 tick 的 6 列（OpenPrice/ClosePrice/SettlementPrice/Upper/LowerLimitPrice/AveragePrice）与 instrument 元数据列，且列名为 `AskPrices[1]`/`LastTraded` 等旧名——需数据源整理对齐 mdb 后 SQL 才可执行。旧 `PreOpenInterest`↔`OpenInterest` 交换在新序下自然消除，若旧数据该两列值本身是交换写入的，整理时需一并修正。

### D.03 · 2026-08-09 MdReader 迁移向量化读

- **2026-08-09 MdReader 迁移向量化读**（`src/BackTest/MdReader.{h,cpp}`）：
  - 迁移到 `DuckdbWrapper::SelectWithSqlVectorized`，消除手写逐列绑定的 DRY 违规；MdReader.cpp.obj TU 级编译通过。
  - **附带修复 DBAdapters 真实 bug**：`duckdb_value_*` 访问器在流式（`duckdb_fetch_chunk`）结果上失效，导致向量化读值全部为空——所有类型转换改为仅从 chunk 向量 raw data 推导；`TestDB` 新增 `TestDuckdbVectorizedMultiChunk`（6000 行 / 3 chunk 跨边界回归）并通过，修复后的 DLL 已 `cmake --install` 至 `D:\Gitee\Libs\DBAdapters\x64-windows`。

### D.02 · 2026-08-09 DBAdapters 向量化批量读扩展

- **2026-08-09 DBAdapters 向量化批量读扩展**（`D:\Gitee\DBAdapters`，独立仓库）：
  - `DuckdbWrapper` 新增 `SelectWithSqlVectorized`（chunk 向量逐列绑定，DECIMAL 经 `duckdb_decimal_to_double` 精确转换，NULL 写入类型哨兵：Double→+inf、Int/Int64→0、Char→空串、Bool→false；错误透出 duckdb 错误信息）。
  - `TestDB` 新增 `TestDuckdbVectorized` 用例并通过（DECIMAL(24,8)→double、NULL→+inf、错误传播均 PASS），x64-Debug 编译 + 运行验证完成。
  - 为 MdReader 由逐行 `duckdb_value_*` 迁移到向量化读预留接口（SQL 列序须与 schema 字段序对应）。

### D.01 · 2026-08-08 设计分析 + P0/P1 修复

- **2026-08-08 设计分析 + P0/P1 修复**：
  - P0-1 夜盘 `TradingDay` 归属修复（改用 CTP `TradingDay`，空时回退 `ActionDay`）— `src/MdOffer/ThostFtdcMdSpiImpl.cpp`
  - P0-2 订阅字段生命周期重构（**值集合**：全局 `std::set<ReqSubMarketDataField>` 去重并持进程级节点，会话集合每会话一份、断开整行 `erase`；消除对象池手动分配/释放、canonical 拷贝、`IsGlobalCanonical`；`SubscribeMd/SubscribeMds` 接口 const 化）— `src/MdOffer/MdKernel.{h,cpp}`、`src/MdOffer/FieldsCompare.{h,cpp}`、`src/MdOffer/ThostFtdcMdSpiImpl.{h,cpp}`
  - P1-1 CTP 断线重置登录态（`OnFrontDisconnected` 置 `isLogged_=false`）— `src/MdOffer/ThostFtdcMdSpiImpl.cpp`
  - P1-2 按配置 `DbType` 分发数据库（替代硬编码 SqliteWrapper）— `src/MdOffer/Main.cpp`
  - 全部通过 x64-Debug 编译验证（MdOffer.exe 链接成功）。

### D.00 · MdOffer 行情主流程

- **MdOffer 行情主流程**：CTP 订阅 → MdKernel 单线程事件循环 → Mdb 内存表 + AsyncDBWriter 异步落库 → MdFront 广播；支持 4 种 DB（DuckDB/SQLite/MySQL/MariaDB）。

---

## ❓ 待讨论（已关闭 / 已了结，倒序）

### Q.19 · Python 绑定未暴露 bar 周期字段

- **Python 绑定未暴露 bar 周期字段（2026-09-12 记录，待决策）**：`src/PythonBindings/FieldsBindings.cpp` 的 `BarMarketDataField` 只暴露 `bar_time`/`open`/`high`/`low`/`close`/`curr_volume`/`volume`/`open_interest` 等，**未暴露 `BarPreces`/`BarPeriod`**（`include/QuantTrading/Fields.h:176-177`）。而 `StrategyBase::DeclareBarPeriod` 声明后"未声明 → OnBar 收到数据集精度 bar"（`StrategyBase.h:45`），两种精度的 bar 会在同一回调里到来且 Python 侧无法区分——多周期 Python 策略因此写不出来（C++ 侧同样只靠 `BarPeriod` 判断，示例 `GridStrategy::OnBar` 未用）。修法：`BindEnums` 补 `BarPrecesType` 枚举绑定 + `BarMarketDataField` 补两个 `def_readonly`（约 6 行）。**关联**：`test/PythonStrategyGrid/grid_strategy.py` 声明了周期却未覆写 `on_bar`，示例本身不消费 bar。**✅ 2026-09-12 已修**（用户："Python 的应该补上，Python 的接口应该与 C++ 保持一致"）：按上述修法落地并编译验证通过，见 ✅ 条目"Python 绑定补齐 bar 周期字段"；唯一未做的是 `ReqSubMarketDataField` 未绑定——它不属策略面向 API（Python 侧声明周期走 `declare_bar_period("5m")` 字符串，与 C++ 签名一致），仍在待决策之列。

### Q.16 · 入站包方向与鉴权校验缺失

- **入站包方向与鉴权校验缺失（2026-09-12 复查发现，待决策）**：Md 协议的**下行/内部包类型可被客户端伪造**。已核实的链路：`PackageFactory::CreatePackage` 是整族单工厂（`src/Packages/PackageFactory.cpp`，`Rtn*`/`Notify*`/`Req*` 一视同仁，无方向表）；`Protocol::OnRecv`（Spark `Protocol.cpp:139`）解析后直接 `m_Subscriber->OnMessage(package)`，无 PackageID 白名单、无鉴权（`m_ServerType` 只影响 `IOFactory` 选 TcpServer/TcpClient）；`MdKernel::HandlePackage` 仅按 `PackageID` 分派，只有 `HandleReqSubMarketData` 内部查过 `m_LoggedSessions`。后果（源码级论证，未做 socket 级 PoC）：① 客户端发一个字段区合法的 `RtnDepthMarketDataPackage` → `FieldToMdb` 落库 + `MdSnap::AddDepthMd` 改写快照 + `PushToAllSubscribed` 广播给**所有**订阅者，即伪造行情注入；② 发 `NotifyDisConnectPackage`（字段内 `SessionId` 与传输会话各由报文/IO 层赋值，互相独立）→ 可清掉**他人**会话的登录态与订阅集合；③ 发 `NotifyDbConnectPackage` → 触发 `mdb_->InitDB()` + 全市场重订阅；④ 任何此类包 `BodyLen=0` 即触发上一批的缺字段区空指针（现已判空，不再崩）。候选修法：**甲** 在 `MdFront` 覆写 `OnRecv` 做入站白名单（只放行 `Req*` 五类）——但需复制 `Protocol::OnRecv` 约 25 行解析循环（成员均 protected，可编译，DRY 上不舒服）；**乙（建议）** `MdKernel` 拆入口——网络入口 `OnMessage` 加白名单，本地通知（`OnProtocolDisConnect`/`OnDbConnected`/`OnDbDisConnected`）与 CTP tick（`ThostFtdcMdSpiImpl.cpp:124`）改走新增的独立方法，代价是改 `OnMessage` 语义 + 4 处调用点；**丙** 给 Spark `Protocol` 加"包方向/白名单"虚钩子——需改 Spark 公开 API（Harness §3.1）并重建重装 Spark 到 `Libs`。另：`Rtn*`/`Notify*` 的处理函数即使保留，也宜按 `m_LoggedSessions` 判是否本端已知会话；但这治不了伪造本身。**发布前建议至少落乙**。
  - **2026-09-12 复查（网络层全貌核对；用户判断："这个问题应该对所有的 Kernel 都存在，最合适的修改不是在 MdKernel，而是要考虑整个网络层的设计"——核对后成立，但修点与范围都要修正）**：
    - **范围钉死**：全仓 `Protocol` 构造只有 4 处——1 个客户端（`src/Apis/ApiBase/ApiBase.cpp:13`，10 个 `Api*Impl` 共用）与 3 个服务端（`MdOffer/MdFront.cpp:9`、`SimExchange/TradeFront.cpp:10`、`SimExchange/MdFront.cpp:11`——后者**从未 `Subscribe`/`Init`/`Start`**，是死对象，`SimExchange/Main.cpp:100/106/111` 三行全注释）。`ProtocolSubscriber` 共 10 个：2 个服务端内核（`MdOffer::MdKernel`、`SimExchange::SimExchange`）+ 8 个客户端实现（`Apis/{MdApi,MdGbkApi,TraderApi,TraderGbkApi,SimExchangeApi,SimExchangeGbkApi}` 各自 `*Impl.cpp`，只按 `PackageID` 分派、`default: break`，**接受 `Req*` 同样无校验**，方向相反但同样不设防）。**一处限缩**：`BackTest::SimExchange` 不是 `ProtocolSubscriber`（`BackTestApiImpl.cpp:59-78` 进程内直调，无会话概念）、`SimExchangeInit/` 根本没有网络层（只有 CTP Middle）——准确说法是"**所有 `ProtocolSubscriber`**"，不是字面的"所有 Kernel"。另 `SimExchange::MdFront` 既继承 `Protocol` 又空实现 `OnMessage`（`MdFront.cpp:25-28`），是第三处死对象。
    - **方向信息今天不存在，且不可能算出来**：52 个包的 ID 分布否掉一切算术规则——`RtnDepthMarketData 0x100A` 是**偶数**（奇偶规则会误判为 Rsp）、`RtnOrder 0x201F` 是**奇数**（会误判为 Req）、`0x1xxx` 段 Req/Rsp（`0x1001-0x1009`）与 Rtn（`0x100A-0x100E`）混排。模型 `Model/Packages/Packages.xml` 只有 `name/id/desc` 三个属性，`ParsePackageModel.py:57-75` 的 `GetPackages` 只读这三个，模板 `Packages.h.tpl:30` 只吐 `static constexpr UShortType PackageID`。Spark 侧也无判据：`include/Spark/Network/Protocol/Head.h` 仅 `PackageID/BodyLen/MessageChain/MsgSeqNum`，全仓无 `Direction`/`IsReq` 类符号。**但类名前缀 52/52 一致**（Req 20 / Rsp 19 / Rtn 9 / Notify 4；原记为 Notify 4 / Req 18 / Rsp 17 / Rtn 13，2026-09-13 复核校正），故方向可在**生成期**从 name 推导，不必改模型。
    - **现成却从未被运行时使用的资产**：`Model/PackageNames/{MdApi,TraderApi,SimExchangeApi,BackTestApi}PackageNames.xml` 已经是"每一侧允许哪些包"的白名单（如 `SimExchangeApiPackageNames.xml` 恰好只列 `Req/Rsp AccountLogin`、`AccountLogout`、`InsertOrder`、`CancelOrder`、`Qry*` 与 `RtnOrder/RtnTrade`），**编译期躺着无人读**。把它生成为运行期可查的表，比新造一套方向语义更贴合既有设计意图。
    - **执法点应是 Spark `Protocol::OnRecv`**（`Protocol.cpp:163-166`）：它是网线包进入应用代码的**唯一**入口，且 `m_ServerType` 就在那里（`Protocol.h:38` protected，构造后除 `RegisterFront` 外再未被读过）。一处过滤 → 4 个 Protocol 实例、10 个订阅者同时受益，且客户端实例顺带获得反向保护。
    - **第二层过滤治不了的部分（必须另修，别指望方向过滤包打天下）**：CTP SPI（`ThostFtdcMdSpiImpl.cpp:124`、`SimExchange/MdSpiImpl.cpp:66/101/165/185`）、`DbSubscriber`、以及内核自造的 `NotifyDisConnect`（`MdKernel.cpp:47`、`SimExchange.cpp:82`）都**直接调 `OnMessage`、绕过 `Protocol::OnRecv`**——好处是内部事件天然不被方向规则误伤，代价是队列里分不出来源（今天的隐式约定是 `SessionId == 0 ⇒ 内部`，未文档化）。而且**方向合法不等于会话合法**：`NotifyDisConnect` 用的是报文**体**里的 `SessionId`（`MdKernel.cpp:174`）而非传输层 `SessionId`，任意合法客户端仍可指定他人会话。这才是真正的病灶——**检查点分散**：MdKernel 侧只有 `ReqSubMarketData` 一处查过 `m_LoggedSessions`（`MdKernel.cpp:332`）；SimExchange 侧 `CheckSessionLogin` 覆盖得其实不差（`SimExchange.cpp:292/325/356/382/408` 五处，未调的两处是 `HandleAccountLogin` 与 `HandleAccountLogout`——前者是登录本身、后者自己判了 `ErrorAccountNotLogin`，两处都正当）。所以缺口**不是"当前漏了几处"，而是没有任何结构保证新加的 handler 会记得查**——MdKernel 的老登出 handler 就是活证（既不可达、也没查）。根治应把会话判定收成**进入 switch 前的一处入口前置条件**，而不是继续在每个 handler 里补。
    - **待拍板三件（成本都在协调，不在代码量）**：① 方向/白名单表从哪来——(a) 用现成的 `PackageNames/*.xml` 生成运行期查表（推荐）／(b) `Packages.xml` 加 `direction` 列／(c) 生成期按类名前缀推导；**三者都要改 `D:\Gitee\Templates\Cpp\Protocol\Packages\*.tpl`，而模板在本仓之外**（`pumplist.xml:32-35` 引用），属共享资源，按 Harness §2 不擅自动。② Spark 是否开口子——需新增公开 API/导出符号（Harness §3.1 强制确认点）；形态候选：`Protocol` 上注册 `std::function<bool(ServerTypeType, UShortType)>`，或给 `ProtocolSubscriber` 加一个默认 `true` 的虚函数（后者无需改各构造点接线，倾向后者）。③ 是否先把"不依赖任何设计决策的真 bug"单独立项修掉（见下一条）。
    - **2026-09-12（第六批）部分落地——内核入口那一半**：方向信息不再需要"运行期查表"才可用。分发改为**生成**（内核清单 + 链路清单 → `bool <Class>::DispatchPackage`，见上方 ✅ 条目），两条纪律因此由结构承担：不在本链路清单里的包**根本没有 `case`**（`Rtn*` 伪造包在 `MdKernel` 只落 `default` 告警，与今天行为一致但成员不再手抄），外部 `Req` 缺字段区在分发处即被回绝。**仍未解决**（本条主体未变）：① 这是"内核侧少认"而非"网络侧不收"，`Protocol::OnRecv` 仍无白名单；② `SimExchange` 侧伪造 `NotifyDisConnect` 指定他人会话 `SessionId` 的问题与方向无关，仍待前置会话判定；③ Spark 是否开口子、`PackageNames` 是否生成运行期查表，均未动。三者仍是发布前建议处理项。**✅ 2026-09-13（第九批）落地 ①**：Spark 开口子（`PackageFactoryBase::IsInboundPackageAccepted`）+ `PackageReader` 两条解析路径过滤，方向表按 (c) 生成期从类名前缀推导（即"待拍板三件"① 的第三个候选）；被拒包在 `CreatePackage` 之前即止，**网络侧"不收"到此补齐**。**仍未解决**：② 会话合法性（`NotifyDisConnect` 用报文体 `SessionId` 指定他人会话，与方向正交，等用户定的会话登录检查）；(a) 用 `PackageNames/*.xml` 生成运行期查表、(b) `Packages.xml` 加 `direction` 列两项候选方案未采纳但仍在；"待拍板三件"里的 ③（把不依赖设计决策的真 bug 单独立项）已由第六批的分发守卫覆盖，不再单独立项。详见上方 ✅ 第九批条目。

### Q.15 · LICENSE 缺失

- **LICENSE 缺失**：项目无 LICENSE 文件，发布前需确定开源协议（README 中已标注待定）。**✅ 2026-09-12 关闭**：`LICENSE` 已存在且已纳入版本控制（MIT License，Copyright (c) 2026 xunmeng2002，2026-09-04 落盘）。**残留（发布前需处理）**：`README.md:350` 仍写"待定（项目暂未添加 LICENSE 文件）"，与事实不符；另需确认署名主体与年份是否即为发布主体。

### Q.14 · TestMdApi 遗留

- **TestMdApi 遗留**：仍硬编码 `sleep(120s)` 等待行情，应改为条件变量/超时轮询。**✅ 2026-09-12 关闭**：已改为 `spi->RtnMdCount` 驱动的 120s 有界轮询（`test/TestMdApi/TestMdApi.cpp:36-44`，与 C6 同一写法），超时打印 `Timeout waiting for market data.`。

### Q.13 · 优雅退出 Ctrl + C 交互验证

- **优雅退出 Ctrl+C 交互验证**：MdOffer / SimExchange 的有序关停逻辑已就绪，但 shell 无法模拟 Ctrl+C，需在真实控制台运行并确认退出顺序与日志。**✅ 2026-09-08 关闭**：用户在真实控制台完成验证——MdOffer 断连重连冒烟（Ctrl+C 杀 MdOffer → 3s 自动重连 → 重登 → 订阅重放 → tick 恢复）与最后 SimExchange 的 Ctrl+C 有序关停，退出顺序与日志确认正常。

### Q.12 · （第五批） SimExchangeInit 无超时死等

- **SimExchangeInit 无超时死等**（2026-09-08 冒烟发现）：`Main.cpp:94` 的 `while (!qryFinished_)` 无超时兜底，`OnFrontDisconnected`（`ThostFtdcTraderSpiImpl.cpp:28`）不置完成标志——SimNow 不可达或认证失败时进程永久挂起；此时 Ctrl+C 强退会丢失已排队未落库的种子数据（0 字节 `SimExchangeInit.db` 实证），下游 SimExchange 空库启动后登录一律 `ErrorBrokerNotExist`(4127)。修复方向：断线/认证失败置位 + 超时兜底退出（可循 TestMdApi 120s 轮询先例），并考虑启动时对 init 库空表告警。**✅ 2026-09-12（第五批）超时兜底已修**：`while (!traderSpi->qryFinished_ && waitedSeconds < 600)` 每秒轮询，超时记 ERROR（提示查前置可达性与账户）后仍走正常收尾（见上方 ✅ 条目 C6）。**未做**：`OnFrontDisconnected` 置位（仍只转基类，故超时是唯一兜底）、启动时对 init 库空表的告警。

### Q.11 · 配置明文凭证

- **配置明文凭证（源码硬编码已消除，S4 完成）**：`Main.cpp` 的 MdOffer 种子用户与死常量已迁移到配置（S4），但配置文件本身仍明文存储密码——`CtpAccountInfo.json`（SimNow 账户 Password/AuthCode）、各 `Configs/*.json`（`DbPassword`/`MdPassword`）、`TestMdApi.json`（`MdPassword`）。接真实环境前需迁移到密钥管理/环境变量；`MdPassword` 测试值 `123456` 仅限开发。**✅ 2026-09-08 关闭（CtpAccountInfo 部分）**：`CtpAccountInfo.json` 凭证清空 + `ReadEnvironment` 环境变量覆盖层落地（见当日 ✅ 条目）；`DbPassword`/`MdPassword` 为开发库测试凭证，风险可接受，记录在 ✅ 条目"范围外遗留"。剩余动作在用户侧：SimNow 凭证轮换 + `setx` 四个环境变量。

### Q.10 · P2-4 订阅范围配置化

- **P2-4 订阅范围配置化**：当前 `HandleNotifyDBConnect` 遍历 `t_Instrument` 全市场订阅，应改为按交易所/产品/合约配置。
  - **2026-09-12 复查：该全市场订阅今天一条都不订**（用户察问"MdOffer 怎么没有用户表"时带出）。根因是**补数库没有生产者**：`Configs/MdOffer.json:13` 的 `DbInitHost=./MdOfferInit.db` 指向的文件在仓内只被读、从无产出——全仓搜 `MdOfferInit` 只有该配置与 `src/MdOffer/Main.cpp:40/97` 两处消费；SimExchange 侧有专门查 CTP 前置产出 `SimExchangeInit.db` 的 `src/SimExchangeInit` 应用，MdOffer 侧没有对等工具（`Mdb::Dump` 导 CSV + `InitMdbFromCsv` 载入这对函数本可充当生产者，但 `InitMdbFromCsv::LoadTables` 在仓内**零调用者**）。SQLite 打开不存在的文件即建空库，故 `bin/Release/MdOfferInit.db` 实为 **0 字节 0 表**，`Main.cpp:106-108` 的三条 `LoadXxxTable`（MdUser/Exchange/Instrument）全部 "no such table"（本次日志只暴露了第一条 `t_MdUser`）。后果：`t_Instrument` 空 → `MdKernel.cpp:152` 的 `SelectAll()` 返回空 → **全市场订阅空转**，行情只能靠客户端显式 `ReqSubMarketData`（与 TestMdApi 日志只有 4 个合约被订到 CTP 一致）；`t_Exchange` 在 MdOffer 运行路径**无任何读者**（死加载）；`t_MdUser` 空不影响登录——种子用户由 `Main.cpp:112-119` 从配置 `MdUserId/MdPassword` 直接插入内存表，运行库 `MdOffer.db` 的 `t_MdUser`/`t_MdUserLoginSession` 则由 `Mdb::OnDbConnected() → InitDB() → CreateTables()` 正常建出（实证 7 张表）。**待决策**：① 给 MdOffer 补数库定生产者（导出/载入工具，或复用 SimExchangeInit 产出）；② 或先摘掉/降级三条 Load（缺表跳过、不再记 ERROR）并去掉 `t_Exchange` 死加载；③ 是否干脆取消全市场订阅、只保留客户端显式订阅。**未做**（记录时）：未改任何代码，仅在 `PROGRESS.md` 记录。**已了结（2026-09-12 第八批）**：用户定稿走 ③ 的方向——取消 `t_Instrument` 全市场遍历，改为配置清单订阅；① 随之一并消解（不再需要补数库，三条 `Load*Table` 与 `t_Exchange` 死加载同批删除，`Main.cpp` 里再无扇入）；`t_MdUser` 的配置回退成为唯一注入口。详见上方 ✅ 第八批条目。`InitMdbFromDB` 本体未动，仍由 `src/SimExchange/Main.cpp:5/84` 使用（用户仅点名 MdOffer）。

### Q.09 · P2-3 Bar 算法单测

- **P2-3 Bar 算法单测**：已由 2026-08-31/09-01 两批 UnitTests 覆盖（bar 聚合、交易时段、集合竞价、丢失 bar 合成、撮合四模式），条目关闭。

### Q.06 · P1-1 完整重连

- **P1-1 完整重连**（2026-09-08 重新划线）：原条目"CTP 断线自动重连/退避策略未实现"表述有误——TCP 层自动重连已在 **Spark** 落地：`TcpBase::TryAutoReconnect`（`src/Network/Tcp/TcpBase.cpp:107`）客户端 IO 循环内检测无连接且无在途连接时按固定 3s 间隔重试，首连同步失败同样交 IO 循环兜底（`Init`），三种 IO 模型（Select/Iocp/Epoll）全继承，重连成功经 `Protocol::OnConnect` 回调上层（Spark `9881aa6`，2026-09-07 19:44 Windows Debug 编译验证；WSL 侧未验，改动仅用 std::chrono 可移植面）。现状分链路：**CTP 链路**（MdOffer→CTP 前置）SDK 自带 TCP 重连 + 2026-08-24 应用侧重置登录态/重登补订，基本闭环；**Spark TCP 链路**（策略/测试端↔MdFront/TradeFront）TCP 层已通，但重连后为新会话，**应用层会话恢复仍缺**——需在 `OnConnected` 里重登（Trader/SimExchange）+ 按原订阅清单补订行情（`ReqSubMarketData`），当前 `StrategyBase::OnConnected`（`StrategyBase.cpp:131`）仅打日志。注意 `OnConnected` 在 IO 线程触发，恢复动作涉及与请求序号/订阅集合的并发访问，实施前需评审。**✅ 2026-09-08 落地**（见当日 ✅ 条目）：探索证实各消费方登录/补订链路本就挂在 `OnConnected`/登录响应处理器上、重连即自动重放，缺口仅为 Spark Send 断连窗口崩溃（`14b188b` 守卫修复）与 SimExchange `isMdLogged_` 断连不复位（已复位 + 原子化）；另六处 ApiBase SPI 判空加固。残留两项记录不修：① `SimExchange::HandleCancelOrder` 回退路径唯一键含 SessionId（`SimExchange.cpp` `m_ClientOrderIDUniqueKey->Select(..., reqPackage->SessionId, ...)`），重连后新会话查不到旧会话订单（主路径按 OrderId 不受影响，且 accept 回报 2026-09-04 起统一推送、回退路径极少触发）；② StrategyBase 实盘适配器（回测无 TCP 不触发 `OnConnected`，维持未来工作）。**✅ 2026-09-08 关闭**：随当日 ✅ 条目落地并冒烟通过，残留两项各自记录在案，不阻塞本条关闭。

### Q.04 · H15 OrderBook 市价撮合缺口

- **H15 OrderBook 市价撮合缺口**（2026-08-27 用户决策：先文档化，代码不动）：`OrderBookOrderMatch::CheckMatch` 只遍历对手限价队列，`m_MarketBuy/SellOrders`（`OrderMatch.h:48-49`）滞留无消费；`OnTick`/`OnBar`（`OrderBookOrderMatch.cpp:19-26`）为空实现，整条路径无价格驱动撮合。待 OrderBook 引擎设计（OnTick 驱动撮合 + 市价队列语义）时一并处理。**✅ 2026-09-07 关闭**：随 `OrderPriceTypeType` 精简（17→7）一并落地四引擎市价语义——OrderBook 市价族吃簿后剩余按 FAK 撤销/FOK 预扫/最优价转挂，市价队列在 OrderBook 模式不再有入队路径（见 ✅ 2026-09-07 条目）。

### Q.03 · 平台宏统一

- **平台宏统一（WINDOWS→_WIN32、LINUX→__linux__）**（2026-08-31 评估）：`_WIN32`/`__linux__` 为编译器内置宏，可替代 CMake 注入的 `WINDOWS`/`LINUX` 家族约定。使用面：Spark 15+ 文件（Logger、Network/Tcp Iocp/Epoll/Select、Shm 等），DBAdapters/Templates 零使用。QuantTrading 侧已完成：`ShutdownSignal.cpp` 3 处 `#ifdef WIN32` 改 `_WIN32`（裸 cl 对照实验证实 `WIN32` 非编译器内置、依赖 CMake 注入 `/DWIN32`，离开构建系统即走错平台分支——且 MSVC CRT 也有 signal.h/signal，属静默劣化而非编译错误）。CMakeLists 的 `WINDOWS`/`LINUX` define 已于当日删除（消费面核查为零引用）；剩余待决策：Spark 仓库源码内部迁移 `WINDOWS→_WIN32`、`LINUX→__linux__`（属 Spark 自身构建范围，不影响 QuantTrading；迁移前 Spark 自己的 CMake 需继续定义这两个宏）。**✅ 2026-09-04 全部关闭**：Spark 源码 36 文件 115 处迁移完毕，其 CMake 不再定义 `WINDOWS`/`LINUX`；Beacon/DBAdapters/Mdb CMake 平台块同步收敛至 QuantTrading 约定。

### Q.02 · HandleCancelOrder 跨日查单失败 + 字段疑似误用

- **HandleCancelOrder 跨日查单失败 + 字段疑似误用**（2026-09-01 实证）：两条查单路径都以当前 `tradingDay_` 为首键（`SimExchange.cpp:575-580`），撤单请求经队列在日切后消费时前日订单必查不到（冒烟实证 4115"委托不存在"）；且回退路径用撤单请求的 `ClientCancelOrderId` 匹配订单 `ClientOrderId` 唯一键，语义上该字段应为撤单请求自身编号。**跨日语义已于 2026-09-02 落地"日切结算统一撤单并推送 OnRtnOrder(Canceled)"**（`OrderMatch::OnTradingDayChange`）：日切后跨日撤单请求面对已清算订单返回 4115 属对齐真实交易所的预期行为，策略侧原"挂单跨日有效"设计已由 GridStrategy 适配（2026-09-02）替代。残留待决策：同日撤单回退路径的 `ClientCancelOrderId` 字段语义修正（需单独评审 + 回归）。**✅ 2026-09-04 关闭**：回测/模拟盘两侧回退查单改按 `req.ClientOrderId`（被撤订单）匹配订单唯一键，`StrategyBase::CancelOrder` 改填 `ClientCancelOrderId = ++nextClientCancelOrderId_`（撤单请求自身序号），字段语义与定义对齐，workaround 注释删除（`205e89b`）。

### Q.01 · 引擎补报单接受确认

- **引擎补报单接受确认**（2026-09-01 提出，StrategyBase 实施时发现）：`OppositePriceOrderMatch`/`LastPriceOrderMatch` 的 `InsertOrder` 不调 `orderMatchSubscriber_->OnOrder(order)`（仅 `OrderBookOrderMatch.cpp:37` 有），挂单未成交前策略拿不到引擎 OrderId——与真实 CTP"已报"回报语义不一致。StrategyBase 已用 `ClientCancelOrderId` 回退路径兼容，但属引擎行为缺口，修复需单独评审 + 回归（TestBackTest 冒烟 + 单测）。**✅ 2026-09-04 关闭**：`OppositePrice`/`LastPrice`/`Bar` 三个撮合实现入队后统一补推 `OnOrder`（与 OrderBook 参照语义一致——插入时必有剩余量，无条件推送正确）；策略自此可从已报回报取得引擎 OrderId，`CancelOrder` 主查单路径恢复可用（`205e89b`）。

### Q.00 · Bar 静态库导致 `TradeSessions` 全局进程内双份

- **Bar 静态库导致 `TradeSessions` 全局进程内双份**（2026-09-11 记录，**✅ 2026-09-12 关闭**：用户否决丙/乙的最小补丁取向，采用**丁**——`TradeSessions` 静态成员改实例注入 + 聚合下沉引擎侧 + 周期随订阅上报，`SessionFile` 归于 BackTest 层；详见 ✅ 2026-09-12 条目。以下为当时记录，保留备查）：`BarStatic` 被 `BackTest`（`add_shared_module` → `BackTestd.dll`，CMakeLists PRIVATE）与策略宿主 exe（经 `StrategyStatic` PUBLIC）分别链接，而 `Bar` 里唯一的进程级可变全局 `TradeSessions`（`m_Inited`/`m_SessionJsonString`/`tradeSessions_`）因此在一个进程内存在两份——装载与读取可落在不同副本上，DLL 侧的 `LoadFromFile` 对宿主不可见。Bar 其余部分不受影响（`BarUtility` 纯函数、`MinuteBar`/`BarAggregator` 为实例且各自只在自身模块内使用）；同样被两侧链接的 `QuantTradingCommonStatic`/`PackagesStatic` 无跨模块消费的可变全局，故全项目仅此一处。**实证**：`dumpbin /exports BackTestd.dll` 仅 8 个符号且全为 `QuantTrading::BackTestApi`，`dumpbin /imports TestStrategyGrid.exe` 只取 `CreateBackTestApi`/`BackTestApi` 构造/`GetApiVersion`，零 `Bar::` 符号跨边界——DLL 与宿主间唯一通道是 `BackTestApi` 虚接口。
  - **用户意图（2026-09-11 明确）**：`SessionFile` 属 **BackTest 层**配置（回测内部使用），策略不关心、不应每个策略各配一份；当前实现落在策略层（`Model/Configs/TestStrategyGrid.xml` + `Configs/TestStrategyGrid.json` + `Main.cpp` 宿主装载）是偏差，待改回。
  - **候选方案**：**丙（建议）** = `Bar` 改共享库（`add_static_md_module` → `add_shared_module`），假全局变真全局，引擎 `Init` 装载即全局生效、零公开 API 变化；范围 = `src/Bar/` 5 个头文件加 `BAR_EXPORTS`（6 类 + 5 自由函数）、CMake 一行 + 4 处 `BarStatic`→`Bar`、三宿主补 `copy_dll_file`/`install`；代价 = `BarSubscriber` 变跨 DLL 回调（项目已有 API/SPI 先例）。**丁** = `TradeSessions` 静态成员改实例注入（最彻底，可顺带删掉单测的 `ResetTradeSessions` 静态清理，但改现有公开 API 需 Harness §3.1 确认、动 `MdOffer` tick 路径，且不解决"宿主从哪拿路径"）。**乙** = 引擎经 `BackTestApi` 回传路径 + 宿主装载（最小补丁，保留双份坑）。
  - **采用丙/乙后的连带改动**：`SessionFile` 从 `Model/Configs/TestStrategyGrid.xml` 与 `Configs/TestStrategyGrid.json` 移除（`pump.py` 再生 `Config.{h,cpp}`）、`test/TestStrategyGrid/Main.cpp` 装载块回退、`CMakeLists.txt` 的 `copy_config_file(TestStrategyGrid Sessions.json)` 回退。
  - **注意**：现有单测与冒烟**测不出**该偏差——`D:\Md` 冒烟用的 SSE 5m 数据集 570 分钟可被 5/10/15/30 整除，墙钟网格与交易节网格重合；60m/45m/夜盘/午休才会暴露。

---

## 🔄 进行中（已关闭记录与半关闭条目的历史部分，倒序）

### R.03 · 2026-09-12 （第五批） `ReqSubMarketData` 报文缺失字段区即解引用空指针

- **2026-09-12 复查发现：`ReqSubMarketData` 报文缺失字段区即解引用空指针（既有，加固项）**：`ReqSubMarketDataPackage::FromStepStream` 只在遇到该 FieldID 时才分配字段（`src/Packages/Packages.cpp:1460`），报文体无该区域时循环体不执行、在 `:1520` 返回 true，字段指针保持 `nullptr`，随后 `src/MdOffer/MdKernel.cpp:312` 解引用崩溃（登录后可达）。这是 48 个字段生成代码的共性缺口——**只挡"多余字段"（未知 ItemID 直接 `return false`），不校验"缺失字段"**。另需修正既有记录的严重度：未知 ItemID 的 `return false` 一路上传会在 Spark `Protocol.cpp` 触发 `m_IOBase->DisConnect(sessionId)` **直接断 TCP**，且失败路径上已分配的 package 未 `Deallocate()`（可耗对象池）。**✅ 2026-09-12（第五批）已修**：`HandleReqSubMarketData` 及同缺口的另外 4 个处理函数补齐判空，另新增 `test/UnitTests/PackageParseTests.cpp` 钉住解析层前提；详见上方 ✅ 条目 C3。**未修**：失败路径上 package 未 `Deallocate()` 一事（属生成层与 Spark 侧，见 ❓"入站包方向与字段区校验"）。

### R.02 · 2026-09-12 （第五批） `SimExchangeInit` 登录结构体无界 `strcpy` → 栈溢出

- **2026-09-12 复查发现：`SimExchangeInit` 登录结构体无界 `strcpy` → 栈溢出（既有，潜伏）**：`src/SimExchangeInit/ThostFtdcTraderSpiImpl.cpp:216-220/229-233/242-245` 共 14 处裸 `strcpy` 把本项目类型拷进 CTP SDK 的**更窄**栈结构体，两侧均无长度校验。按 `Libs/Ctp/x64-windows/include/ThostFtdcUserApiDataType.h` 与 `Spark/Types.h` 逐字段核对：`BrokerId` 16→11、`UserId` 32→16、`UserProductInfo` 32→11、`AuthCode` 64→17、`Password` 64→41 均为"源更宽"，`AppId` 32→33 安全。即 `CtpAccountInfo.json` 中对应值超过 CTP 宽度即溢出（`ReqUserLogin` 每次 `OnFrontConnected` 重放）。**同文件已有 10 处 `Utility::Strcpy`**（`Spark/Core/Utility/Utility.h:19`，按 `sizeof(dest)` 即 CTP 宽度限宽，配合其前的 `::memset` 补齐终止符后安全），仅这 14 处登录调用用了裸 `strcpy`——属该文件内的局部疏漏，同时违反 `rules/cpp-style.md` §6「禁止 `strcpy`」。实盘 SimNow 取值（BrokerId `9999`、AuthCode 16 字符）目前不会触发，故定为潜伏项而非活动缺陷。**✅ 2026-09-12（第五批）已修**：14 处全部改为 `Utility::Strcpy`（按目标宽度限宽，不再依赖"源更窄"这一外部前提），详见上方 ✅ 条目 C4。

### R.01 · 2026-09-12 （第三批） 实时行情路径不消费 bar 周期

- **2026-09-12 复查发现：实时行情（MdOffer）路径不消费 bar 周期（待决策）**：`DeclareBarPeriod` 声明的周期只在回测链路生效——`MdOffer/MdKernel.cpp:315` 调 `minuteBar_->ReqSubMarketData(ExchangeId, InstrumentId)`，而 `MinuteBar::ReqSubMarketData` 无周期参数（`src/Bar/MinuteBar.h:18`），输出硬编码 `Minute/1`；`src/SimExchange/SimExchange.cpp:556` 发送侧亦为 `ReqSubMarketDataField reqSubMd{0}`。叠加 `FieldsCompare.cpp` 的 `std::less<ReqSubMarketDataField>` 只比较 ExchangeId+InstrumentId（我加的 `BarPreces`/`BarPeriod` 未参与），同合约以不同周期二次订阅与首条"相等"→ 不入集合 → 不重新订阅，**但仍回 `ErrorNone`**，客户端以为按新周期订阅成功。当前不产生错误结果（该路径本就不聚合），但属"回了成功实际 no-op"的静默陷阱：策略在回测按 5m 验证后直接跑实时，`OnBar` 会变成每分钟一次而指标窗口错位。修法：比较器补齐两个字段（或改整结构体逐字节比较），并至少在 `MdKernel::HandleReqSubMarketData` 对 `BarPeriod > 0` 记 Warning。**❌ 2026-09-12（第三批）撤回前半句**：比较器补齐周期会让 `PushToAllSubscribed` 的 0 周期探针匹配不到带周期入集的会话，**直接中断行情推送**——见上方 ✅ 条目 ⑤ 的证据；该比较器是"合约身份键"，不应带周期。真正待办的只剩后半句：在 `MdKernel::HandleReqSubMarketData` 对"声明了周期但实时链路不消费"记 Warning（未做，仍待决策）。

### R.00 · 2026-09-12 （第三批） 引擎侧聚合的两处缺陷

- **2026-09-12 复查发现：引擎侧聚合的两处缺陷（均属 `e5fd794` 引入）** —— **✅ 2026-09-12（第三批）已修**，见上方 ✅ 条目（绑定键统一、目标合法性预校验）；以下为当时记录，保留备查：
  - **绑定键与查表键口径不一致 → 热门/主力合约声明的周期被静默忽略**。`BindBarAggregator` 用 `mdSubscribe->RealInstrumentId` 登记（`src/BackTest/SimExchange.cpp:555`），而 `PushBarMarketData` 用 `mdBar->InstrumentId` 查表（`:384`）——后者由 `MdReader::UpdateMdBars` 盖成**请求别名** `mdSubscribe->InstrumentId`（`src/BackTest/MdReader.cpp:176`；`:227` 的 SQL 才是按 `RealInstrumentId` 过滤取数）。Normal 合约二者相等故冒烟测不出；`.Hot`/`.Second`/`.Third` 别名（`InitMainInstrument`，`:773`）不等 → `find` 必然 miss → 走透传分支，聚合器一根 bar 都收不到且无告警。`:442` 的注释已写明「热门合约滚动时二者不同」，`:543` 的注释写的是"按推送 bar 实际的 InstrumentId 登记"（即正确设计），代码却取了 `RealInstrumentId`——注释与代码自相矛盾。修法：`:555` 改用 `mdSubscribe->InstrumentId` 作绑定键（`RealInstrumentId` 仍只用于 SQL 取数）。
  - **目标合法性未预校验 → 构造期异常逃出 `try` → 引擎线程 `std::terminate`**。`BindBarAggregator` 的 `try` 只包住 `ValidatePrecesRelation`（`:403-411`），`std::make_unique<BarAggregator>` 在 `try` 之外（`:419`）；`BarAggregator` 构造函数对 Second 目标抛 `std::logic_error`。而 `ValidatePrecesRelation` 只校验"输入→目标"关系、从不校验目标本身，本批新增的**同精度同周期短路**更放行了 `5s` 数据集 + `5s` 声明（另有数据集 1m + 声明 120s 的可整除路径）。修法：把 `IsValidBarPrecesTarget`（`!= Second && period > 0`，`src/QuantTradingCommon/QuantUtility.cpp:66`）提到 `ValidatePrecesRelation` 顶部、置于短路之前，使装载期预校验与首根校验共用同一完整判据。此短路本为放行"数据集 1d + 声明 1d"，却开了 Second 目标的口子。
  - **同类但更低危（记录不修）**：① 同合约跨批次二次订阅按 `instrumentBarAggregators_[id] = ...` 后写覆盖，被覆盖聚合器内该合约的 `HasBar` 残桶会在下次 `Flush` 时以名义桶尾推给策略（陈旧假 bar）；② `BarPeriod <= 0` 的透传分支在 Tick 撮合模式下不参与，但声明了无法服务周期仍会终止整个回测；③ `src/BackTest/SimExchange.cpp:500` 的 `continue` 跳过 `:535` 的 `::Deallocate(reqSubMd)` 确有泄漏（原记为 `SimExchange.cpp:483`/`:518`，2026-09-13 复核校正），但经 `git show e5fd794` 确认属 `fd7afef init` 既有（本次仅在全市场订阅循环与 ctor 处改动）。
