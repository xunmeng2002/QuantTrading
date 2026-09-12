# 项目进度跟踪

> 按 Harness 规则 8 维护：每次会话结束更新。新会话开始先读本文件。

## 项目定位

CTP 期货量化交易系统（C++20），当前处于**前期整理阶段**：行情服务 **MdOffer**、回测引擎 **BackTest**（C++/Python 双端策略）、模拟盘 **SimExchange** 均已落地并经单测/冒烟验证；实盘交易链路（TraderApiMiddle）已封装但未接入应用。

## 🗂 归档索引

> `PROGRESS.md` 只保留活内容：🔄 进行中、❓ 未决、最近 3 批 ✅。已关闭与已了结的条目**原文**在 [`PROGRESS-archive.md`](PROGRESS-archive.md)（2026-09-13 拆分，不删不改）。

- 检索：`grep "关键词" PROGRESS-archive.md`（例：`grep "TradeSessions" PROGRESS-archive.md`）。
- 条目 ID：`D.*` = 原 ✅ 已完成（`D.00`–`D.40` 已归档）；`Q.*` = 原 ❓ 待讨论；`R.*` = 原 🔄 进行中。ID 取自 2026-09-13 拆分时的文档顺序。
- 必须查归档的时机：引用 2026-09-12 及更早的结论时；复审某个已关闭事项时；主文件某条写明"见归档 `Q.xx` / `R.xx`"时。
- 滚动规矩：已完成区超过 5 批时，把最旧的整条**原样**移入归档（主文件目标 ≤ 50 KB）。

## ✅ 已完成

> 更早的 41 条（`D.00`–`D.40`，2026-08-08 ~ 2026-09-12）已归档，见 [`PROGRESS-archive.md`](PROGRESS-archive.md)。

- **2026-09-12（第七批）修 `HandleReqMdUserLogin` 成功登录仍回「用户不存在」（第五批 C3 引入的回归）**：
  - **现象**（用户跑 TestMdApi 冒烟）：登录回 `RspInfoField:ErrorID:[4098], ErrorMsg:[用户不存在]`，但紧接着的 4 条 `ReqSubMarketData` **全部回 `ErrorID:[0]`**，且服务端日志显示内核真的把这 4 个合约订阅到了 CTP（`bin/Release/log/MdOffer.20260912-224105.log:54-69`：每条 `HandleReqSubMarketData` 后跟 `SubscribeMd` + `SubscribeMarketData`）。即"登录报错、会话却已建立"——而订阅网关（`MdKernel.cpp:294` 的 `m_LoggedSessions.find`）是当时**唯一**的会话检查点。
  - **定位**：`m_LoggedSessions` 只在 `MdKernel.cpp:216` 写入，且写入前必先通过 `t_MdUser` 查表与密码比对（两者任一失败都在 `:194/:198` 回错误、进不到插入分支；密码错回 `ErrorIncorrectPassword` 0x0002，与观测到的 4098 互斥）。故"订阅被受理"反证了**登录实际成功**，4098 是响应里的 `errorID` 没被回写——`auto errorID = ErrorUserNotExist;`（`:184`）是第五批 C3（`0b07e60`）为"字段区缺失回错误而非成功"而设的初值，但**成功分支自始至终没有一处 `errorID = ErrorNone;`**（`0b07e60^` 版本初值是 `ErrorNone`，靠默认值侥幸正确）。同一处还解释了两个附带现象：`LoginDate`/`LoginTime` 只在 `errorID == ErrorNone` 时填写（`:239-242`），故客户端日志恒为 `LoginDate:[], LoginTime:[]`（`TestMdApi.20260912-224110.log:22/52`）。**这是我的 C3 改动引入的回归**，此前无测试覆盖登录成功路径，直到本次冒烟才暴露。
  - **修法（一行）**：在插入会话成功处回写成功状态，`m_LoggedSessions.insert(package->SessionID);` 之后加 `errorID = ErrorNone;`。保留"默认失败"的初值不动——登录是鉴权路径，宁可少认不可错认，后续若新增提前返回分支忘了置错也只表现为"登录被拒"，不会静默放行。
  - **同类核查**：`src/SimExchange/SimExchange.cpp` 6 处 `auto errorID = ErrorNone;`、`MdKernel::HandleReqSubMarketData`（`:293`）均为"默认成功 + 逐项置错"，无同类问题；全仓 `errorID` 初值与成功路径回写已逐处比对，仅此一处缺回写。
  - **测试 I/O 示例**（重编 `MdOffer` + `TestMdApi` 后应看到）：

    ```text
    正确 MdUser/MdPassword → RspInfoField:ErrorID:[0], ErrorMsg:[正确]，且 LoginDate/LoginTime 非空
    错误密码               → RspInfoField:ErrorID:[2], ErrorMsg:[密码错误]
    不存在的用户           → RspInfoField:ErrorID:[4098], ErrorMsg:[用户不存在]
    登出后同连接重登       → 第二次 ErrorID:[0]（回 0x2015 才说明登出清理失效）
    ```

  - **风险（§7）**：无。一行赋值，不改所有权、不加锁、不放宽任何鉴权（`m_LoggedSessions` 仍只在登录成功且会话行插入成功后写入）。**未验证**：编译与重跑仍由用户在 VS 侧执行；本次仅静态定位 + 改动。
  - **同批冒烟的另一发现（与登录缺陷独立，属测试配置）**：`Configs/TestMdApi.json` 订阅的 IF2603 / rb2603 / jd2603 / AP605 分别是 2026-03、2026-03、2026-03、2026-05 合约，相对当前日期（2026-09-12）**均已到期**，CTP 受理订阅（回 `No Error`）但不会推送任何 tick——这才是 `Timeout waiting for market data.`（120s 有界轮询走满）的直接原因，与登录无关。建议把冒烟合约换成活跃月份；另注意 22:41 属日盘收市后，CFFEX 无夜盘，即便合约活跃也只有 SHFE/DCE/CZCE 的夜盘品种在推。
- **2026-09-12（第八批）MdOffer 移除 MdOfferInit：种子用户改配置项，启动订阅改配置清单**：
  - **需求**（用户口头）：「设计有点问题了，我之前刚把 BackTestInit 给干掉了，把初始化放到 BackTest 内部了。这里的 MdOffer 也这样做吧，完全移除 MdOfferInit 相关的内容。主要看看种子用户怎么提供，是使用简单的配置项，还是提供一个 List？」→ 两个子问题经 `AskUserQuestion` 定稿为「单配置项」+「改为配置订阅清单」。**范围仅 MdOffer**；`SimExchange` 仍保留同款 `SimExchangeInit`/`DbInitHost` 模式（用户未点名，未动）。
  - **问题根因（为什么原来跑不通）**：`DbInitHost` 指向的种子库 `MdOfferInit.db` 是 0 字节、0 张表，且**仓库内无任何生产者**——`InitMdbFromDB::LoadMdUserTable/LoadExchangeTable/LoadInstrumentTable` 三个装载全部 `no such table`（对应此前"怎么没有用户表"的排查）。同时 `HandleNotifyDBConnect` 的"全市场订阅"遍历 `t_Instrument->m_PrimaryKey->SelectAll()`，种子库没表 → 空集 → **启动订阅静默失效**，一根 bar 都不会落库，除非客户端逐个 `ReqSubMarketData`。第一版还有一处死代码 `ExchangeIDType exchangeID = "SHFE";`（赋值后从未使用）与逐合约裸分配泄漏（每一行 `Allocate` 的 `ReqSubMarketDataField` 都不释放、也不入注册表）。
  - **移除**（`src/MdOffer/` 侧已无任何 `MdOfferInit`/`DbInitHost`/`t_Instrument` 残留，grep 复核为"无"）：`Main.cpp` 的 `#include "InitMdbFromDB.h"`、种子库常量 `./MdOfferInit.db`、整个 `SqliteWrapper* initDB = new SqliteWrapper(config.DbInitHost.empty() ? ... : ...)` + 三次 `Load*Table` + `DisConnect/delete` 块；`Model/Configs/MdOffer.xml` 与 `Configs/MdOffer.json` 的 `DbInitHost`；`MdKernel.cpp` 的 `SelectAll` 遍历与死变量。
  - **替代（种子用户=单配置项）**：**该路径本就存在、本批一字未改**——`Main.cpp:102-109` 在 `config.MdUserID` 非空时构造一条 `MdUser`（`MdUserName` 置空、密码取 `config.MdPassword`）插入 `mdb->t_MdUser`，此前一直被上面三条失败的 `Load*Table` 挡在噪声之下（`git diff` 中该块为上下文行，非新增）。故"单配置项"的落地成本为零：只删 `DbInitHost`、不新增配置键、`MdUserID`/`MdPassword` 原样复用。空 `MdUserID` 则完全不插（保持"无用户则无法登录"的语义，不静默造默认账号）。表本身由 Mdb 的 `CreateTables()` 在 DB 连接后自动建（数据库路径），不再依赖外部种子库。
  - **替代（启动订阅=配置清单）**：`Model/Configs/MdOffer.xml` 新增 `SubscribeInstruments`（`type="list"` + 标量 `modeltype="SubscribeInstrument"` → 生成 `std::list<SubscribeInstrument*>`），复用 Spark `ConfigStructs.h` 里既有的 `SubscribeInstrument`；`Configs/MdOffer.json` 填 CFFEX/IF2603、SHFE/rb2603、DCE/jd2603、CZCE/AP605（与 `Configs/TestMdApi.json` 同四个，**均为已到期月份，属占位**）。`Config.{h,cpp}` 由仓库根 `python pumpall.py` 重生成（本次仅这两个文件变化）。清单以构造参数注入 `MdKernel`（照 `TradeSessions` 注入的先例，而非在 kernel 里读配置单例）：`HandleNotifyDBConnect` 改为遍历该清单，逐项 `m_SubscribeInstruments.insert`（全局注册表去重、复用 set 节点地址）、新合约才 `m_MinuteBar->ReqSubMarketData` 并收集，最后一次性 `m_MdSpi->SubscribeMds(reqSubMds)`。DB 重连会重跑该流程，靠注册表幂等，不会重复订阅 CTP。
  - **测试 I/O 示例**（重编 `MdOffer` 后）：

    ```text
    启动（不含任何客户端连接）：
      旧：SqliteWrapper: SELECT failed. Table:t_MdUser, Error:no such table: t_MdUser
      新：无该行；改为 4 条 SubscribeMd: ExchangeID:..., InstrumentID:...
           + SubscribeMarketData: nCount[1]（每合约一条）
    MdOffer.db：7 张表照建（DB 连接后 CreateTables），t_MdUser 内有 1 行
    客户端登录（正确口令）→ RspInfoField:ErrorID:[0]（第七批修好后）
    清单留空 → 启动零订阅、零报错，订阅完全由客户端驱动
    ```

  - **风险（§7）**：① 清单项是从配置单例 `new` 出来并被 `MdKernel` 以裸指针持有的（模板生成规则：list + 非标量 → `std::list<SubscribeInstrument*>`，逐条 `new` 且模板不生成释放），生命周期与进程同长，无悬垂、亦不免泄漏——与 `Config` 现有全部 list 字段同款，未单独处理。② `SubscribeInstrument` 只有 `ExchangeID`/`InstrumentID` 两个字段，**无 bar 周期**，故启动订阅按既有约定把 `BarPreces/BarPeriod` 置 0（与客户端 `ReqSubMarketData` 的周期语义不同，落库的前两者恒为 0，若后续要用 bar 表需再扩字段）。③ 空清单 = 服务端不订阅任何合约 → `t_MinuteBar` 只在客户端订阅后才产生数据，非故障但需知晓。④ JSON 里四个合约已到期，验证时须换成活跃月份，否则依旧无 tick（见第七批同项）。⑤ `Main.cpp` 的 `#include <DBAdapters/DBInterface/TypedTable.h>` 改动后已无直接使用点，**刻意保留**以免造成无法验证的编译中断。
  - **注释披露（§4）**：本批新增/改写注释两处——`MdKernel.h` 构造函数注释补一句「启动订阅清单项指向配置单例，生命周期同进程」（即风险①的契约）；`MdKernel.cpp` 原有两行注释里的「全市场订阅」改为「启动订阅」（遍历对象已变，不写清会误导）。其余为删除，未新增。
  - **未验证**：编译与运行仍由用户在 VS 侧执行（按约定）。本批仅静态改动 + `pumpall.py` 生成；`bin/Release/MdOffer.json` 待下次构建经 `copy_config_file`（`CMakeLists.txt:145`）刷新后生效。
- **2026-09-13 入站包方向过滤（第九批，方案乙）**：第六批把方向纪律做进了内核分发（**内核侧"少认"**），本批补上网络侧的"不收"——**对端在本协议角色下不可能发出的包，在包对象创建之前即被拒绝**。用户决策走乙（代价最小），方向表来源取 (c) 生成期按类名前缀推导（乙 方案自带的实现选择）。
  - **Spark 侧（新增公开 API，Harness §3.1 确认点在用户）**：`PackageFactoryBase` 增 `virtual bool IsInboundPackageAccepted(UShortType packageID) { return true; }`——默认全放行为**纯增量**，任何既有实现不覆写即维持原语义（本仓唯一子类已覆写）。`PackageReader` 在 Xtp/Step **两条解析路径**的校验和之后、`CreatePackage` 之前插入判定：不通过则记 Error 日志 `Inbound Package Not Accepted. PackageID:%d, SessionID:%lld, IP:%s` 后 `Reset(); return false;`，复用既有的"解析失败 → `m_IOBase->DisConnect(sessionID)`"路径断 TCP。选在 `CreatePackage` 之前是乙的核心价值——**被拒的 ID 一个包对象都不会被分配**，不存在"先造出来再丢"的浪费，也不牵动对象池的 `Deallocate` 漏点。
  - **Templates 侧（外部仓 `D:\Gitee\Templates`，待用户提交）**：`Cpp/Protocol/Packages/PackageFactory.{h,cpp}.tpl`——头文件加 `ServerTypeType` 构造参数与 override 声明，实现加构造定义与方向开关：`Notify*` → `false`；`Req*` → `m_ServerType == ServerTypeType::Server`；`Rsp*`/`Rtn*` → `m_ServerType == ServerTypeType::Client`；`else` 与 `default` → `false`。方向用 DSL 的 `@name.startswith(...)` 在**生成期**算成常数，运行期无字符串操作、无查表。
  - **QuantTrading 侧**：`pumpall.py` 再生 `src/Packages/PackageFactory.{h,cpp}`（仅此二文件变化，重跑幂等）。核对：52 个 `case` = 20 个 Server + 28 个 Client + 4 个 `false`（Notify），加尾部 `default: break; return false;`，**每个包都被分类，无 fail-open 分支**。4 个构造点补角色实参：`src/Apis/ApiBase/ApiBase.cpp:13`（10 个客户端 `Api*Impl` 共用的唯一 Protocol，`Client`）、`src/MdOffer/MdFront.cpp:9`、`src/SimExchange/TradeFront.cpp:10`、`src/SimExchange/MdFront.cpp:11`（三者 `Server`；末者是死对象，但代码确实构造，故必须传参）。
  - **语义边界（本批不是"鉴权修好了"）**：内部/自造包（`MdKernel.cpp:47` 与 `SimExchange.cpp:82` 的 `NotifyDisConnect`、CTP SPI tick、`DBSubscriber`）都**直调 `OnMessage`、不经 reader**，故"`Notify*` 一律拒"不会误伤它们；同一原因，**方向合法 ≠ 会话合法**——`NotifyDisConnect` 取的是报文体里的 `SessionID`、可指定他人会话这个病灶与本批**正交，仍未修**（等用户定的会话登录检查）。`Model/PackageNames/*.xml` 未动（仍无运行期读者）；方案 (a) 由 `PackageNames` 生成运行期查表、(b) `Packages.xml` 加 `direction` 列，均未做。
  - **测试建议（§7）**：

    ```text
    TestMdApi（客户端角色）：登录 → 订阅 → RtnDepthMarketData 照常到达（Rtn 在 Client 侧放行）
    伪造：向 MdOffer 的 MdFront 发字段区合法的 RtnDepthMarketDataPackage（0x100A = 4106）
        旧：FieldToMdb 落库 + MdSnap 改写快照 + PushToAllSubscribed 广播给所有订阅者
        新：MdOffer 记 `Inbound Package Not Accepted. PackageID:4106, ...`，连接被断，
            零落库、零广播
    伪造：客户端发 NotifyDisConnectPackage → 同上被拒，不再能借报文体 SessionID 清他人会话
    反向：服务端误发 Req* 给客户端 → 客户端侧同样拒绝（此前客户端实例完全不设防）
    ```

  - **风险（§7）**：① **构建顺序有硬约束**——生成代码对 `IsInboundPackageAccepted` 用了 `override`，故 **Spark 必须先重编并重装到 `Libs`，QuantTrading 之后才能编译**（Spark 头文件 1 处 + `PackageReader.cpp` 2 处）。② 拒绝即断 TCP：以往"未知 PackageID"经 `CreatePackage == nullptr` 也是断，但**"已知包、方向不对"此前是被正常收下的**，现在变为拒绝 + 断连——这是本批的意图，属可观测行为变化；已逐一核对本仓 4 个 Protocol 实例 / 10 个订阅者无此情形（6 个客户端 `Api*Impl` 只分派 `Rsp*`/`Rtn*`；两个内核只处理 `Req*` 与内部自造包；`ReqSubMarketDataFinished` 只在进程内回测）。③ 拒绝时记 Error 级日志且无限流，一次伪造一条，沿用既有解析失败路径的做法未加限流。④ `default: return false` 对未知 ID fail-closed，与既有 `CreatePackage` 返回 `nullptr` 的结局等价（都断连），无新增暴露面。
  - **注释披露（§4）**：本批新增注释 2 处，均属"外部前提"性质、命名无法表达者——`PackageFactoryBase.h` 新虚函数上方一行（默认全放行 + 由应用侧按自己协议收紧的契约）；模板 `PackageFactory.cpp.tpl` 中新函数体首行（方向族由包名前缀推导——这条映射不写下来，看生成结果会以为那些常数是手工维护的）。其余改动未加注释。
  - **未验证**：编译与运行仍由用户在 VS 侧执行（按约定）。本批为 6 个文件静态改动（含 2 个生成文件）+ 生成文件再生，无新增运行期验证。**已提交**：本仓 `407509c` + Spark 仓 `50b5e31`；`D:\Gitee\Templates` 的两处模板改动待用户提交。

- **2026-09-13 PROGRESS.md 分层归档（活文件 + 归档层）**：主文件 168.6 KB → 23.8 KB（−86%），每次会话开头通读的体积随之下降；已关闭与已了结的条目**原文**移入新增的 `PROGRESS-archive.md`（152.9 KB，按 `D.*` / `Q.*` / `R.*` 分三段倒序）。
  - **完整性**：69 条逐条断言"原文逐字出现在目标文件"，**0 条失败**；唯一丢弃的是 🔄 段那句 `- 无。` 占位符（3 字节，无信息）。两文件合计 176.7 KB 对原始 168.6 KB，多出的约 8 KB 是标题与索引脚手架。
  - **四条承接条目**（半关闭条目的尾巴不能随归档一起埋掉）：入站包方向留"① 已落地 / ② 会话合法性未决 + 候选 (a)(b) 仍在"；实时行情不消费 bar 周期的短版**带上撤回警告**（`FieldsCompare` 比较器补齐周期会中断行情推送，不留在主文件里下次可能被重新提议）；另新增两条——`ReqSubMarketDataField` 未绑定到 Python（原 `Q.19` 尾巴）、解析失败路径上已分配的 package 未回收（原 `R.03` 尾巴；2026-09-13 复核：`PackageReader.cpp:35`、`Protocol.cpp:131` 两处 `Deallocate` 都只回收 `PackageReader` 自身，无一处回收 package，原记录成立）。
  - **规则**：`C:\Users\15031\.claude\CLAUDE.md` 新增 §8.1——活文件/归档层分工、只移动不删改、半关闭条目的未决部分必须留下、滚动（已完成区超 5 批移最旧、主文件 ≤ 50 KB）、引用主文件不载的结论前先 grep 归档。拆分脚本为一次性转换（按条目边界搬移，原文取自 `407509c:PROGRESS.md`，从 git HEAD 读故可重入），放在 `%TEMP%`、未入仓。
  - **验证**：无代码改动，故无编译/运行验证；等价校验即上述 69 条完整性断言与两文件体积统计。

- **2026-09-13 会话登录改造落地（第十批）：交易所按主账号、MdOffer 按 MdUser，会话状态一律以 mdb 会话表为准**：
  - **模型 / 清单**：`Model/TableNames/SimExchangeTableNames.xml:14` 把 `AccountLoginSession` 换成 `PrimaryAccountLoginSession`，跑 `pumpall.py` 后 `src/SimExchange/SimExchangeTableList.h` 与 `src/SimExchangeInit/SimExchangeTableList.h` 各一行随之换名（三张会话表均由用户改成联合主键 + SessionID 索引，模型与生成提交见 `deb32af`/`c143df5`）。
  - **SimExchange（交易所 = 主账号层，只认 `t_PrimaryAccount`）**：`CheckSessionLogin` 拆两重载——无账号报文（`HandleReqQryInstrument`）只查 `t_PrimaryAccountLoginSession->m_SessionIDIndex`；有账号报文（下单/撤单/查委托/查成交）查 `(PrimaryAccountID, SessionID)` 联合主键，未命中**直接回 `ErrorAccountNotLogin`**（用户改法：登录记录找不到就回，不再多查一次）。登录/登出/断开三处全部改走 `PrimaryAccountLoginSession`，断开以 `EraseBySessionIDIndex` 一行替换"Select 后 Erase"，推送侧索引变量随表改名；顺带删除 `SendRspAccountLogin` 里未使用的包分配。业务字段仍取自 `t_Account`（`OrderUtility.cpp:142/163-165` 的 `AccountType`/`TradeGroupID` 只挂在 Account 上），故双表同 ID 是设计而非巧合。
  - **MdOffer（行情 = `MdUser` 层）**：删除 `std::set<SessionIDType> m_LoggedSessions` 及其 4 处使用（成员、断开与登出清理、登录成功写入、订阅守卫），改为 `bool IsSessionLoggedIn(const SessionIDType&)`（`MdKernel.h:61` / `MdKernel.cpp:364`）查 `t_MdUserLoginSession->m_SessionIDIndex->EqualRange`；订阅守卫保持原 if/else-if 形状（`if (!IsSessionLoggedIn(package->SessionID))`），零结构改动。登录重复仍回 `ErrorSessionAlreadyLogin`，登出/断开仍按传输层会话清理。
  - **验证**：静态为主——`m_LoggedSessions` 全仓仅剩 PROGRESS 历史文本；`MdUserLoginSessionTable::m_SessionIDIndex`（`src/Mdb/MdbTables.h:299`）与 `MdUserLoginSessionIndexSessionID::EqualRange(const SessionIDType&)`（`src/Mdb/MdbIndexes.h:69`）均为 public；`#include <set>` 仍被 `m_SubscribeInstruments` 需要，未动。**编译与运行仍在用户 VS 侧执行；本批已提交**（模板侧的会话表过滤落在 `D:\Gitee\Templates` 的 `fe01756`）。
  - **`session="true"` 过滤落地（用户选方案 a，`Templates` 仓 + 重 pump）**：起因是核到该标记**只被传递、无一处消费**——① 全 `D:\Gitee` 搜读取方，只有 `ParseTableModel.py` 自己的 `:19` 初始化 / `:53` 读 / `:93` 写三行命中（`DataBase`、`DBPerformance`、`Libs`、`LibTest`、`Mdb`、`Python`、`QuantTrading` 七个副本皆然）；② `D:\Gitee\Templates\Cpp\Mdb\*.tpl` 共 23 个模板里 `session` **零命中**；③ 生成的 `InitMdbFromDB::LoadTables` 对清单内每张表无条件发 `case <Table>::TableID: Load<Table>Table(...)`（`Load<Table>Table` 即 `SelectAll` → `Insert`）。而 `src/SimExchange/Main.cpp:78/84/88-89` 是完整闭环：`AsyncDBWriter` 按清单建 schema 并双向订阅（登录行落运行时库）→ 重启后 `LoadTables` 把会话行读回内存 → `CheckSessionLogin` 认定该 `(账号, SessionID)` 已登录。**改动**：`Templates/Cpp/Mdb/InitMdbFromDB.{h,cpp}.tpl` 的 `!!if @name in tables:!!` 追加 `and @session != 'true'`（模板引擎将 `@session` 译作 `get_attr(curr_node, "session")`，属性缺失回 `""`，故非会话表一律放行，无 fail-closed 风险；两处 `!!#...!!` 注释写在模板里、只进 pump 脚本不入生成文件），随后 `pump.py` 重 pump 得 `src/Mdb/InitMdbFromDB.{h,cpp}`：三张会话表既无 `case` 也无 `LoadXxxTable` 定义，其余表全部保留（36 行纯删除，0 新增）；复跑 `pumpall.py` 无待生成项，证明树自洽。**效果**：启动不再把上个进程的残留会话读回内存，进程重启后一律要求重新登录；会话表仍在 schema 里（`AsyncDBWriter` 按清单建表）并照旧被写入，只是不再被读回。**可达性注**：原问题的现实可利用性本就有限（`IOBase::GetSessionID()` 为 `GetMilliSecondTimeStamp() * 100 + (++m_LastSessionIndex) % 100`，`Spark/src/Network/IO/IOBase.cpp:107`，残留行需客户端恰在同一毫秒被 accept 才命中），成立的是"重启后旧会话仍算已登录""鉴权结论取决于库内容"两点；**批注**：非本批引入——换表前 `AccountLoginSession`（同样 `session="true"`）就在交易所清单里，同样被载入。**未决**：`InitMdbFromCsv` 同一改法未套用，见 ❓。
  - **风险（§7）**：登录/登出/断开同在内核线程（`MdKernel::HandlePackage`）里串行处理，无新增锁与共享可变状态；会话判定改读表后，"内存集合 vs 会话表"两份状态合一。模板改动是跨仓（`D:\Gitee\Templates`）且全局生效的，其他项目下次跑各自的 `pumpall.py` 时其 `InitMdbFromDB.cpp` 也会按同一规则过滤会话表——这正是原意图，但需知悉其波及面；该仓原有两笔本批之外的 `.tpl` 改动（`PackageFactory.cpp/h.tpl`，即第九批入站包方向过滤的生成侧，生成物早已提交在本仓 `407509c`），按用户指示已一并提交为该仓 `726fad4`。

## 🔄 进行中

- **实时行情（MdOffer）链路不消费 bar 周期（待决策，2026-09-13 复审）**：`DeclareBarPeriod` 的周期只在回测链路生效——`MdKernel.cpp:315` 调 `MinuteBar::ReqSubMarketData(ExchangeID, InstrumentID)`，该函数无周期参数（`src/Bar/MinuteBar.h:18`），输出硬编码 `Minute/1`；发送侧 `src/SimExchange/SimExchange.cpp:556` 亦为 `reqSubMd{0}`。后果：策略在回测按 5m 验证后直跑实时，`OnBar` 变成每分钟一次而指标窗口错位，且客户端收到的是 `ErrorNone`（回了成功、实际 no-op）。**待办**：`MdKernel::HandleReqSubMarketData` 对 `BarPeriod > 0` 记 Warning。⚠️ 曾提议的"`FieldsCompare` 比较器补齐 `BarPreces`/`BarPeriod`"**已撤回**——该比较器是"合约身份键"，补齐周期会让 `PushToAllSubscribed` 的 0 周期探针匹配不到带周期入集的会话，**直接中断行情推送**；撤回证据见归档 `R.01` 与归档 `D.36`。

## ❓ 待讨论 / 待决策

> 已关闭/已了结的条目（`Q.00`–`Q.15`、`Q.19` 等）已归档；下面只留未决项。

- **入站包方向与鉴权校验缺失（半关闭；2026-09-13 第九批落地网络侧"不收"）**：`PackageFactoryBase::IsInboundPackageAccepted` + `PackageReader` 两条解析路径过滤，反向包在 `CreatePackage` **之前**即被拒（生成代码按类名前缀推导方向，52 包全分类、无 fail-open）；内核侧"少认"见第六批分发生成。**仍未解决**：① 会话合法性——`NotifyDisConnect` 取的是**报文体**里的 `SessionID`、可指定他人会话（与方向正交），等用户定的会话登录检查；② 候选方案 (a)（由 `PackageNames/*.xml` 生成运行期查表）与 (b)（`Packages.xml` 加 `direction` 列）未采纳但仍在。完整侦察记录（网络层全貌核对、执法点论证、第二层过滤治不了的部分、三件待拍板）见归档 `Q.16`。
- **`InitMdbFromCsv` 仍枚举会话表（2026-09-13 记录，待决策）**：方案 (a) 只落在 `InitMdbFromDB.{h,cpp}.tpl`（启动从库载入这条活路径）。`InitMdbFromCsv.{h,cpp}` 的 `LoadTables` 仍对三张会话表发 `case ...: LoadXxxTable(mdb, dir)`（`src/Mdb/InitMdbFromCsv.cpp:32/40/41`），同一过滤（`and @session != 'true'`）可原样套用。**未做**：该路径今天**零调用者**——除 `InitMdbFromCsv.*` 自身外全仓只有两处 `#include "InitMdbFromCsv.h"`（`src/BackTest/SimExchange.cpp:9`、`src/SimExchange/SimExchange.cpp:4`），无一处调用 `InitMdbFromCsv::LoadTables`，动它只增重 pump 面、无行为变化。**若将来有模块改用 CSV 播种**，需同步补这个过滤，否则会话表会从 CSV 被载入。
- **数据源整理对齐 mdb**（用户负责）：TestBackTest 已能在旧格式 parquet（`LastTraded`/`LastTurnover`/数组盘口，缺 OpenPrice/ClosePrice/Upper/LowerLimitPrice/AveragePrice 5 列）上端到端跑通，**靠 MdReader SQL 的 NULL 占位 + 旧列名兜底**；数据侧未真正对齐 mdb schema。真正对齐后 SQL 可删掉占位符，且 tick 的涨跌停价列才真实可用（当前 OrderMatch 的涨跌停校验处于注释状态，`GetSettlementPrice` 对 +inf 有回退，故暂不影响撮合/结算正确性）。
- **P2-1 MdKernel 职责拆分**：`HandleRtnDepthMarketData` 同时做 bar 聚合/Mdb 更新/快照/广播，建议预留 tick 处理管线。
- **P2-2 Bar 内存策略**：`MinuteBar` 用裸 `new` 且 `m_TodayBars` 无日界清理，考虑改对象池 + 日界重置。
- **`SimExchange::HandleReqAccountLogin` 未判空即解引用（2026-09-12 网络层核对时发现，与 C3 同级，未修）**：`src/SimExchange/SimExchange.cpp:197` 直接取 `reqPackage->ReqAccountLogin->AccountID` 作为 `t_PrimaryAccount` 的查询键、`:202` 再取 `->Password` 做 `strcmp`（函数名与行号 2026-09-13 复核校正：第六批已改名 `HandleReqAccountLogin`，原记 `:232`/`:240`），**全程无判空**。而 `ReqAccountLoginPackage`（`0x2003`）与 MdKernel 的登录包同属"只挡多余字段、不校验缺失字段"的生成代码（见下一条模板条目），故只有包头（`BodyLen=0`）的登录报文会让字段指针保持 `nullptr`：`MdKernel::HandleReqMdUserLogin` 在第五批已补判空（`MdKernel.cpp:223`），**SimExchange 这半边漏了**。可达性：`0x2003` 是登录请求本身，无需任何前置状态即可到达。后果：未鉴权可达的空指针解引用（`Select` 与 `strcmp` 各一次）。修法照抄 MdKernel 的判空分支即可（`errorID` 保持初始值 + 记 Warning）。**同类未修**：`SimExchange::HandleReqAccountLogout`（`:225` 起，唯一字段区解引用在 `:230` 的 `reqPackage->ReqAccountLogout->AccountID`；原记 `:270` 有误，2026-09-13 复核校正）、`HandleInsertOrder`/`HandleCancelOrder`/`HandleQry*` 的字段区解引用尚未逐一核对（本次只核到登录处）。另记：`src/SimExchange/SimExchange.cpp` 共 12 处裸 `strcpy`（`:27/:86/:256/:258/:270/:277/:282/:452/:454/:464` 等），但核对后**两侧同宽**（`AccountIDType ← AccountIDType`、`ErrorMsg ← 字面量`），与 C4 的"项目类型 → 更窄的 CTP 类型"不同级，属 `rules/cpp-style.md` §6 风格问题，非内存安全缺陷。**2026-09-12（第六批）可达路径已封**：上述 7 个包全部登记进 `SimExchangeKernelPackageNames.xml` 且以 `Req` 开头 → 生成的分发守卫在进入 Handler 前即对空字段区回绝（`ErrorReqPackageParseFailed`），**网线来的空指针不再可达**（这 7 个包在 SimExchange 侧只从网线来，无内部产生者）。Handler 内部仍无判空，作为纵深防御缺口保留记录；建议后续按同一清单逐条补判空（或由"生成期必填字段区"的模板级修法一次解决，见下一条）。
- **生成模板级"缺字段区不校验"（2026-09-12 记录，待决策）**：`src/Packages/Packages.cpp` 由 `D:\Gitee\Templates` 的 `Cpp/Protocol/Packages/Packages.cpp.tpl` 生成，48 个字段区一律"只在遇到 FieldID 时分配、函数尾无条件 `return true`"，故**每个包的必填字段区缺失都靠消费方判空兜底**（本批已在 MdKernel 补 5 处）。模板级修法是让"唯一字段区"的包在末尾 `return <字段指针> != nullptr;`——失败即表现为解析失败，由 Spark `Protocol.cpp` 走既有 `DisConnect(sessionID)` 路径断 TCP，消费方无需判空。**未做**：改模板需重 pump 全部生成文件并核对，且会影响所有消费方（含测试客户端），属跨仓库改动，待用户决策走模板还是维持"消费方判空"的现状。
- **解析失败路径上已分配的 package 未回收（待决策，属生成层 + Spark 侧）**：`Protocol::OnRecv` 解析失败即断 TCP，但失败前已 `CreatePackage` 出来的对象无人释放，可耗对象池——2026-09-13 复核：`src/Network/Protocol/{PackageReader,Protocol}.cpp` 里 `Deallocate` 只用于 `PackageReader` 自身（`:35`、`Protocol.cpp:131`），**没有一处回收 package**，原记录成立。第九批的网络侧过滤只挡在 `CreatePackage` **之前**（被拒 ID 不分配），未触及这条失败路径。同类但不同源：`src/BackTest/SimExchange.cpp:500` 的 `continue` 跳过 `:535` 的 `::Deallocate(reqSubMd)`（归档 `R.00` ③，属 `fd7afef init` 既有）。
- **`ReqSubMarketDataField` 未绑定到 Python（待决策，2026-09-12 记录）**：补 `BarMarketDataField` 的 `BarPreces`/`BarPeriod` 时留下的尾巴——它不属策略面向 API（Python 侧声明周期走 `declare_bar_period("5m")` 字符串，与 C++ 签名一致），故当时未绑。完整记录见归档 `Q.19`。
- **Python 绑定构建前置未就绪（2026-09-12 记录）**：`CMakeLists.txt:269` 走 `python -m pybind11 --cmakedir`，要求目标解释器已 `pip install pybind11`；本机 Python 3.14.5 无该模块，而 `Libs/pybind11/2.13.4` 只有 `include/` + `pybind11/` python 包（无 `share/cmake`）、`Libs/python/3.12` 只有 `include/`（无 libs/exe），都无法替代。**发布相关**：`.pyd` 受解释器 ABI 版本锁定（本机编出的只能被对应次版本导入），若 Release 包内含 `quanttrading.pyd`，需在 README 写明目标 Python 次版本，或作为可选组件单独提供。

## 备注

- 提交信息历史多为 `1`，建议后续写描述性提交信息。
- `D:\Gitee\Templates` 仓库的模板改动（S1/S3/H10/H12 对应 `.tpl`）已提交（`6d12e3d`）。
- `rules/cpp-style.md` 成员命名要求 snake_case，现有代码为 `m_` + PascalCase，项目自洽但与规范不一致（待统一）。
