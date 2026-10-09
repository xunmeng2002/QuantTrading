# 引擎 Linux 发布包要求

本文是平台侧（QuantPlatform）对上游引擎包（QuantTrading）的**验收契约**：约定
Linux Release 包长什么样、怎么打、怎么自检。满足本文的包，平台侧只需把
`ENGINE_ROOT` 指向包内唯一目录即可挂载运行。

与 [`backtest-run-contract.md`](backtest-run-contract.md) 并列：那份约定**怎么跑**
（一次性进程 + 退出码 + `result.json` + 相对写入路径），本源约定**怎么打包**。

> **注意**：本文只描述**部署运行包**，不描述链接用的开发包。两者的区别见 §3。

## 1. 一句话契约

平台只认一个目录。`ENGINE_ROOT` 指向的那个目录里，必须同时有：

- Python 扩展模块（`QuantTrading.*.so`）；
- **全部**运行时 `.so`（来自三个仓，见 §2）；
- `engine-version.txt`；
- 两个模板 json。

该目录之外，运行时不再有任何依赖。

## 2. 发布包目录结构

运行时 `.so` **不来自单一仓**：引擎依赖 Spark 与 DbAdapters 的 `.so`，靠
`DT_NEEDED` 动态加载。打包必须把三个仓的产物**收拢到同一个目录**：

```text
engine/
├── QuantTrading.cpython-312-x86_64-linux-gnu.so   ← 引擎
├── libBackTest.so                                  ← 引擎
├── libCore.so                                      ← Spark
├── libNetwork.so                                   ← Spark
├── libSerialization.so                             ← Spark
├── libAsyncDbWriter.so                             ← DbAdapters
├── libDuckdbWrapper.so                             ← DbAdapters
├── libSqliteWrapper.so                             ← DbAdapters
├── libduckdb.so                                    ← DbAdapters 转发
├── engine-version.txt
├── BackTest.json
└── Sessions.json
```

| 文件 | 归属 | 角色 |
| :--- | :--- | :--- |
| `QuantTrading.*.so` | 引擎 | Python 扩展模块，解释器 import 的入口 |
| `libBackTest.so` | 引擎 | 回测主库，扩展模块的直接依赖 |
| `libCore.so` | Spark | 基础库，**多个 `.so` 共用的直接依赖** |
| `libNetwork.so` | Spark | 网络，依赖 `libCore.so` |
| `libSerialization.so` | Spark | 序列化 |
| `libAsyncDbWriter.so` | DbAdapters | 异步落库，依赖 `libCore.so` |
| `libDuckdbWrapper.so` | DbAdapters | DuckDB 封装，依赖 `libCore.so` + `libduckdb.so` |
| `libSqliteWrapper.so` | DbAdapters | SQLite 封装，依赖 `libCore.so`，**按名 `dlopen`** |
| `libduckdb.so` | 三方 | 唯一非自家库，由 `libDuckdbWrapper.so` 加载 |
| `engine-version.txt` | 引擎 | 版本标识，一行文本，见 §6 |
| `BackTest.json` | 引擎 | 引擎主配置模板 |
| `Sessions.json` | 引擎 | 会话模板，平台逐作业拷贝 |

> **警告**：`libSqliteWrapper.so` 由 `BackTest.json` 的 `DbType` 决定是否
> 按名字 `dlopen` 加载，因此**不会出现在 `ldd` 的输出里**。清单必须
> 「`ldd` 结果 + 已知 dlopen 名单」两者合并，只看 `ldd` 会漏掉它。

### 2.1 六个 API 中间层：**不进包**（2026-10-09 引擎侧查证确认）

`QuantTrading/bin/$<CONFIG>` 下另有 6 个交易/行情 API 中间层：

```text
libMdApi.so  libMdGbkApi.so
libSimExchangeApi.so  libSimExchangeGbkApi.so
libTraderApi.so  libTraderGbkApi.so
```

**结论：回测发布包不含它们**，打包时必须显式排除。依据（引擎侧实测）：

- 引擎源码树里**没有任何按名装载器**——`src/`、`include/`、`test/` 全树
  `dlopen` / `dlsym` / `LoadLibrary` / `GetProcAddress` **零命中**。本仓唯一可达的
  按名装载是 DbAdapters 的 `LoadDatabaseBackend`，它按 `DbType` 只拼得出
  `DuckdbWrapper` / `SqliteWrapper` / `MysqlWrapper` / `MariadbWrapper` 四个
  **数据库后端**名，没有分支能产出 `MdApi` / `TraderApi` / `SimExchangeApi`。
- 这 6 个库是 `SimExchange` 应用与三个 `Test*Api` 应用的**构建期 `DT_NEEDED`**，
  **不在回测闭包**：`libBackTest.so` 与扩展模块的链接行都不含它们。

> **警告**：拍平输出目录（§5）之后，这 6 个库会与运行时闭包**同处
> `bin/$<CONFIG>`**。故 §7 的取用必须是**白名单**，不可写成"取该目录下全部 `.so`"。

### 2.2 扩展模块后缀不写死

扩展模块的后缀随解释器而定，**不要硬编码**：

| 平台 | 后缀 |
| :--- | :--- |
| Windows | `.cp314-win_amd64.pyd` / `.pyd` |
| Linux | `.cpython-312-x86_64-linux-gnu.so` / `.abi3.so` / `.so` |

平台侧的判据与 import 机制同源，取 `importlib.machinery.EXTENSION_SUFFIXES`。
引擎侧打包时按实际产物命名即可，平台会按当前解释器的后缀表去认。

两个平台的次版本由 `CMakePresets.json` 的 `QUANTTRADING_PYTHON_VERSION` 钉死
（Windows `3.14`、WSL/Linux `3.12`），表内示例即现状产物；改版本时以 preset 为唯一来源。

## 3. 只有一类产物进发布包

同一份源码会产出三类东西，**只有第三类**进发布包：

| 产物 | 内容 | 给谁用 | 进发布包 |
| :--- | :--- | :--- | :--- |
| 链接用 | `include/` 头文件、`lib/cmake/*.cmake` | 编译别的项目 | 否 |
| 调试用 | `*.pdb`（Windows）、`*.a` 静态库 | 符号调试 / 静态链接 | 否 |
| **运行时** | `*.so`、扩展模块、json | `ld.so` 与解释器 | **是** |

头文件、CMake 配置、静态库只服务于**编译期**；引擎一旦编出 Release 包，
它们的使命就结束了。部署目录里出现它们即为打包错误。

## 4. 每个 `.so` 必须自带 `RUNPATH: $ORIGIN`

### 4.1 为什么必须逐个设

`RUNPATH` **不传递**。`ld.so` 解析某个对象的 `DT_NEEDED` 时，只用
**发起加载的那个对象自己**的 `RUNPATH`，不继承调用者的：

| 对象 | 它的直接依赖 | 用谁的 `RUNPATH` 找 |
| :--- | :--- | :--- |
| 扩展模块 | `libBackTest.so`, `libCore.so` | 扩展模块自己的 |
| `libBackTest.so` | `libCore`, `libNetwork`, `libSerialization`… | **`libBackTest.so` 自己的** |
| `libNetwork.so` | `libCore.so` | **`libNetwork.so` 自己的** |

所以「扩展模块带了 `$ORIGIN`」帮不到 `libBackTest.so` 去找它的兄弟。
**每一个有非系统依赖的 `.so` 都必须自带 `RUNPATH: $ORIGIN`**。

### 4.2 怎么设（一处，全体生效）

`CMakeCommon.cmake` 顶部已加入家规，**两条并用**：

```cmake
set(CMAKE_BUILD_RPATH_USE_ORIGIN ON)
if(UNIX AND NOT APPLE)
    add_link_options(-Wl,-rpath,$ORIGIN)
endif()
```

- 只有第二条对本仓产物有效。`CMAKE_BUILD_RPATH_USE_ORIGIN` 只把
  **CMake 二进制目录（`out/build/...`）之内**的库换算成 `$ORIGIN` 相对形式；
  本仓把产物输出到 `${CMAKE_SOURCE_DIR}/bin/...`（二进制目录之外），三方库又来自
  `${CMAKE_SOURCE_DIR}/../Libs` 安装树，两处都在其管辖之外。**2026-10-09 实测**：
  一轮完整 Release 构建后 8 个产物 RUNPATH 全是绝对路径，`$ORIGIN` 一个都没有。
- 第二条显式追加一个 `$ORIGIN` 条目，与 CMake 自动算出的构建机绝对路径
  **并存**（实测值形如 `[$ORIGIN:/home/<用户>/...]`）。取舍：构建树内照旧可直接运行
  （`bin/Release` 下的宿主与 `import` 都不需要 `LD_LIBRARY_PATH`），发布包在目标机上
  靠 `$ORIGIN` 解析同目录的兄弟库，那些绝对项不存在时被 `ld.so` 跳过。

> **注意**：`RUNPATH` 是链接期写进 ELF 的字段，**必须重新链接**才生效
> （`.o` 复用；2026-10-09 实测一次「只重链接、无重编译」的构建即拿到新 RUNPATH）。三个产品仓都在各自
> `CMakeLists.txt` 顶部 `include(submodules/CMakeCommon/CMakeCommon.cmake)`，
> 故第二条对本仓所有 target 一体生效（第一条只管二进制目录内的产物）。版本要求
> `CMake ≥ 3.13`（`add_link_options`），
> 三家现状 3.20 / 3.25 满足。

### 4.3 怎么验

```shell
cd engine
for so in *.so; do
    printf '%-40s' "$so"
    readelf -d "$so" | grep -o 'RPATH.*\|RUNPATH.*' || echo '  (无 RPATH/RUNPATH)'
done
```

判据按产物归属分档（2026-10-09 裁定）：

| 产物 | 判据 | 缺 `$ORIGIN` 时 |
| :--- | :--- | :--- |
| 引擎自己的产物（扩展模块、`libBackTest.so`） | **必须**含 `$ORIGIN` | 不合格 |
| Spark / DbAdapters 安装树来的 ship 库 | 暂记**警告**（见 §4.4） | 不阻断 |

- 判「含」不判「恰为」：绝对项按 §4.2 的取舍保留，`$ORIGIN` 在最前即可。
- **2026-10-09 实测**（补家规并重链接后）：引擎 8 个产物的首个条目均为 `$ORIGIN`；
  7 个 ship 库中只有 `libDuckdbWrapper.so` 带 `$ORIGIN`，其余 6 个**无任何** `RPATH/RUNPATH`。
- **附带缺陷（实测确认）**：12 项里有 **1 项**产物的 RUNPATH **末尾带一个空元素**
  （形如 `.../Spark/x64-linux/lib:`）。glibc 把空元素当作**当前工作目录**搜索——
  2026-10-09 用构造 `.so` 实测：依赖只放在 cwd 时能解析，换一个 cwd 立刻 `not found`。
  来源不在本仓（全树 `rpath` / `link_directories` 零命中），是 Libs 安装树导出的链接
  片段带尾随冒号；修它要动 Spark / DbAdapters 的导出配置，不在本批范围。实际影响有限：
  包内 `DT_NEEDED` 的库都能先被 `$ORIGIN` 解析到，空元素轮不到；但 `dlopen` 裸名加载
  （§2 的 `libSqliteWrapper.so`）会把作业的工作目录纳入搜索范围。

### 4.4 谁必须重建（实测，2026-10-09）

| 产物 | 绝对 `RUNPATH` | `$ORIGIN` | 结论 |
| :--- | :--- | :--- | :--- |
| 引擎 8 个产物 | 有（指向构建机 `Libs/...`） | 补家规前**无**，补后**有** | 必须重新链接（本轮已完成） |
| Spark / DbAdapters 的 ship 库 | 无 | 6 个无、1 个有 | 无需现在重打 tag |

Spark 与 DbAdapters 的 ship 库**无需重建即可工作**，但原因是两个巧合，
而非它们更"干净"：

1. 它们**没有**绝对 `RUNPATH`；
2. 它们唯一的非系统依赖 `libCore.so` 恰好是**扩展模块的直接 `DT_NEEDED`**，
   必先映射（`libDuckdbWrapper.so` 找 `libduckdb.so` 则靠它**已自带**的 `$ORIGIN`）。

第 2 条的代价是**`ldd` 单独分析会假阳性**：`libNetwork.so`、`libAsyncDbWriter.so`、
`libSqliteWrapper.so` 在发布目录里单独 `ldd` 会报 `libCore.so => not found`——它们自己
没有 `RUNPATH`，`ld.so` 不会去看同目录的兄弟库。真实加载路径里 `libCore.so` 由扩展模块
先映射好，故 §8 第 3 条（`import`）才是**决定性判据**，实测通过。

第 2 条本身是**加载顺序的巧合**：一旦依赖图变动即可能碎于运行时、且无声。统一
`$ORIGIN` 后即消除。故 **Spark / DbAdapters 不需要现在重打 tag**——家规随
各自下次构建生效即可；届时上表右列转绿，§8 的分档警告自动消失。

## 5. 拍平：`bin/` 与 `lib/` 合成一个目录

### 5.1 改前的两层结构

引擎原先输出到两个目录（`QuantTrading/CMakeLists.txt:59-61`）：扩展模块进
`bin/$<CONFIG>`，7 个 `.so` 与 15 个 `.a` 进 `lib/$<CONFIG>`。如此，`$ORIGIN` 会推出
`$ORIGIN/../lib/Release`，包成两层，且 `.a` 混在同一目录里。

### 5.2 改法：共享库目录指向 `bin/`（2026-10-09 已落地）

把**共享库**输出目录也指向 `bin/$<CONFIG>`：

```cmake
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/$<CONFIG>)
```

- 效果：`bin/$<CONFIG>` 里只剩扩展模块与全部 `.so`，`.a` 仍留在 `lib/`，
  天然被发布包排除；原先进 RUNPATH 的那条「仓内库目录」不再需要，改由 §4.2 的
  `$ORIGIN` 条目承担（构建机绝对项按 §4.2 的取舍仍在，实测见附录 A.1）。
- **Windows 不受影响**：`CMAKE_LIBRARY_OUTPUT_DIRECTORY` 只作用于
  非 DLL 共享库（Linux `.so` / macOS `.dylib`）；Windows 的 `.dll` 走
  `RUNTIME_OUTPUT_DIRECTORY`，本就落在 `bin/`。
- 已查证无消费者按 `lib/$<CONFIG>` 取库：`Configs/*.json` 无库路径字段，
  `test/` 无按路径寻库。
- 注意：`$ORIGIN` 只覆盖**引擎构建树内的**库。Spark / DbAdapters 的
  `.so` 来自各自安装树，构建期仍靠链接目录的绝对路径寻址；**拍平发生在
  §7 的打包脚本**——把三处的 `.so` 一并收进发布目录。

## 6. `engine-version.txt` 必须在 Linux 侧产出

平台用它标识「这一轮跑的是哪个引擎构建」（取首个非空行）。引擎侧现行写法
（`QuantTrading/CMakeLists.txt:28`）：

```cmake
file(GENERATE OUTPUT ${CMAKE_SOURCE_DIR}/bin/$<CONFIG>/engine-version.txt CONTENT "${PROJECT_VERSION}\n")
```

**2026-10-09 实测结案**：此前 Linux 构建树与 Windows `bin/Debug` 里都没有该文件，
原因是**这两棵树在该行落地之后还没重新 configure**——不是写法问题。对同一个
`WSL-GCC-Release` 预设重跑一次构建（configure 段随之重跑）后，WSL 侧即产出
`bin/Release/engine-version.txt`（内容 `1.0.0`）；**代码不动**。

原先揣测的两个候选**均被实测否证**：

1. `$<CONFIG>` 在 Ninja（单配置生成器）下取 `CMAKE_BUILD_TYPE`，实测路径正确
   落在 `bin/Release/`；
2. `file(GENERATE)` 会自行创建缺失的父目录，写入不会静默失败。

> **注意**：该文件由**配置期**产生，故「改完不重跑 configure 就构建」看不到它——
> 这与「`.o` 复用、只重链接」的情形不同，是本次误诊的根源。

缺失时平台退回「扩展模块 + 运行时库」的内容摘要，仍能跑，但拿不到
人可读版本号——Release 包应避免走到这条兜底。

## 7. 打包脚本要求

打包脚本把**三处**产物平铺进发布目录。取用必须是**显式白名单**——不可写成
「取该目录下全部 `.so`」，理由见 §2.1 的警告：

| 来源 | 取用（白名单，逐条列名） |
| :--- | :--- |
| `QuantTrading/bin/$<CONFIG>` | 扩展模块 `QuantTrading.*`（后缀按 §2.2 认）、`libBackTest.so`、`engine-version.txt`、`BackTest.json`、`Sessions.json` |
| `Libs/Spark/x64-linux/lib` | `libCore.so`、`libNetwork.so`、`libSerialization.so` |
| `Libs/DbAdapters/x64-linux/lib` | `libAsyncDbWriter.so`、`libDuckdbWrapper.so`、`libSqliteWrapper.so`、`libduckdb.so` |

- 白名单共 **12 项**（扩展模块按实际名计 1 项），与 §2 的清单一一对应；
- 排除：`*.a`、`*.pdb`、`include/`、`lib/cmake/`、任何 `.so.*` 调试拆分；
- 排除：六个 API 中间层（§2.1）；
- 排除：`libMysqlWrapper.so`、`libMariadbWrapper.so`（各 11–15 MB，按需另定）；
- 输出：**一个目录**，无子目录（这是**发布目录**的形态，即下面 `--zip` 解压出来的那一层）；
- 白名单任一文件缺失即**非零退出并点名**，不得静默少文件；
- 版本号只从 `engine-version.txt` 读，脚本不得手写（见 §6）。

**归档形态（可选，`--zip`）**：把发布目录打成
`QuantTrading-<版本>-linux-<架构>.zip`，包内是**一个**顶层目录（同名去 `.zip`），12 个文件平铺其下。
本条不改变上面「一个目录、无子目录」的要求——zip 只是那一层目录的封装，解压后仍是扁平单目录。
平台侧「换版按版本留目录、不原地覆盖」的约定因此天然满足：解压即得一层可直接
`QUANT_ENGINE_ROOT` 指过去的目录（`QuantPlatform` 的 `docs/platform-plan.md`）。归档一律在 §8
自检**全过之后**才产出。

> 引擎侧实现：仓根 `PackageLinuxRelease.sh`（`--config` / `--output` / `--libs` / `--zip` / `--force`）。
> 它把上表与「排除」两节逐条写成白名单，缺失即点名且非零退出，并内嵌 §8 的判据；
> 默认拒绝写非空输出目录，`--force` 只清它自己那个输出目录。`--zip` 的打包与包内校验（可读、
> 条目数一致、无嵌套目录）只用解释器自带的 `zipfile`，不引入 `zip(1)` / `unzip(1)` 依赖。

## 8. 引擎侧自检（全过才算合格）

```shell
cd engine

# 1. 依赖齐全: 应无任何输出
ldd ./*.so | grep -i "not found"

# 2. RUNPATH 里应含 $ORIGIN: 按 §4.3 分档判定
for so in *.so; do
    printf '%-40s' "$so"; readelf -d "$so" | grep -o 'RPATH.*\|RUNPATH.*' || echo '  (无)'
done

# 3. 解释器能 import: 打印出的路径应在发布目录内
python -c "import QuantTrading; print(QuantTrading.__file__)"

# 4. 版本文件在: 应打印一行版本号
cat engine-version.txt
```

判据按 §4.3 / §4.4 **分档**（2026-10-09 裁定）：

| 条目 | 引擎自己的产物 | Spark / DbAdapters ship 库 |
| :--- | :--- | :--- |
| 第 1 条（依赖解析） | 有缺失即不合格 | 缺 `libCore.so` 只记警告 |
| 第 2 条（含 `$ORIGIN`） | 缺即不合格 | 缺只记警告 |

- 第 3 条是**决定性**的：它同时验证扩展模块能找到 `libBackTest.so`、
  `libBackTest.so` 能找到它的兄弟——即整套 `$ORIGIN` 链是否真的成立。
  **但它不能替代第 2 条**：在构建机上那些绝对路径还在，`import` 即便不靠
  `$ORIGIN` 也会成功；只有 `readelf` 能证明 `$ORIGIN` 确实写进了 ELF。
  反过来，在目标机上第 3 条通过即终局通过。
- 第 1 条对 ship 库报 `libCore.so => not found` 是**假阳性**（§4.4）：它们没有
  `RUNPATH`，单独分析时看不见同目录的兄弟库；真实加载路径里兄弟库由扩展模块先映射。
- `ldd` 对 `dlopen` 类库（§2 的 `libSqliteWrapper.so`、§2.1 的 API 中间层）
  不可见，第 1 条只覆盖 `DT_NEEDED` 闭包。

> **引擎侧实现**：仓根 `PackageLinuxRelease.sh` 已内嵌这些判据（分档同上）。
> 注意它的「四条自检」与本节 1–4 **不是同一组编号**，对应关系见下表。
> 2026-10-09 实测：12 项文件、四条全过，另有 9 条警告（6 条 ship 库无 `$ORIGIN`、
> 3 条 ship 库单独 `ldd` 假阳性），exit 0。

脚本的四条自检（执行顺序）与本节手工验法的对应：

| 脚本内嵌的检查 | 对应本节 |
| :--- | :--- |
| 包内容（§7 白名单与排除项 + 文件数 12 + 无子目录） | 本节未列，手工看 §7 |
| 依赖解析（`ldd` 无缺失） | 第 1 条 |
| RUNPATH 含 `$ORIGIN` | 第 2 条 |
| 解释器 `import` | 第 3 条 |

「`engine-version.txt` 读不到版本行」在脚本里**先于自检**按硬失败处理（exit 3），
即本节第 4 条不合格时脚本不会走到自检，而是直接中止——故脚本口头报的
「四条全过」不含第 4 条，版本文件是它的前置条件。

---

## 附录 A：实测依赖关系（2026-10-09，WSL）

`NEEDED` 列只列非系统库；`RUNPATH` 列标注**是否已正确**。

| 对象 | 归属 | `DT_NEEDED`（非系统） | `RUNPATH` |
| :--- | :--- | :--- | :--- |
| 扩展模块 | 引擎 | `libBackTest.so`, `libCore.so` | ✗ 绝对 |
| `libBackTest.so` | 引擎 | `libAsyncDbWriter`, `libDuckdbWrapper`, `libSerialization`, `libNetwork`, `libCore` | ✗ 绝对 |
| `libMdApi` / `libMdGbkApi` | 引擎 | `libNetwork`, `libCore`, （`libSerialization`） | ✗ 绝对 |
| `libSimExchangeApi` / `libSimExchangeGbkApi` | 引擎 | 同上 | ✗ 绝对 |
| `libTraderApi` / `libTraderGbkApi` | 引擎 | 同上 | ✗ 绝对 |
| `libCore.so` | Spark | （仅系统） | 无（可接受） |
| `libNetwork.so` | Spark | `libCore.so` | 无 |
| `libSerialization.so` | Spark | （仅系统） | 无（可接受） |
| `libAsyncDbWriter.so` | DbAdapters | `libCore.so` | 无 |
| `libDuckdbWrapper.so` | DbAdapters | `libCore.so`, `libduckdb.so` | ✓ `$ORIGIN` |
| `libSqliteWrapper.so` | DbAdapters | `libCore.so`（**且按名 dlopen**） | 无 |
| `libduckdb.so` | 三方 | `libdl`, `libpthread` | 无（可接受） |

> **提示**：本表由 `readelf -d` 实测得出；`libSqliteWrapper.so` 的 "按名
> dlopen" 是手工补注——它属 dyld 盲区，见 §2 的警告。

### 附录 A.1 补家规并重链接后的复测（2026-10-09）

上表 `RUNPATH` 列的 ✗ 是**补家规前**的状态。给 `CMakeCommon.cmake` 追加
`-Wl,-rpath,$ORIGIN` 后重新链接，引擎 8 个产物全部转正：

| 对象 | 重链接后的 `RUNPATH` |
| :--- | :--- |
| 扩展模块 | `[$ORIGIN : Libs/Spark/... : Libs/duckdb/... : Libs/DbAdapters/...]` |
| `libBackTest.so` | `[$ORIGIN : Libs/duckdb/... : Libs/DbAdapters/... : Libs/Spark/...]` |
| 六个 API 中间层 | `[$ORIGIN : Libs/Spark/...]`（不进发布包，仅记录） |
| Spark / DbAdapters ship 库 | 与上表一致，未变（`libDuckdbWrapper.so` 仍为 `[$ORIGIN]`） |

两处实测细节：

- 绝对项**未被清除**，`$ORIGIN` 只是排在最前——见 §4.2 的取舍说明；
- 12 项发布文件里有 1 项 RUNPATH 末尾带**空元素**，glibc 视作当前工作目录；
  来源是 Libs 安装树导出的链接片段，详见 §4.3 的附带缺陷段。

## 附录 B：一次实测留档（原始输出）

```text
扩展模块  RUNPATH = [.../QuantTrading/lib/Release : .../Libs/Spark/x64-linux/lib
                     : .../Libs/duckdb/x64-linux/lib : .../Libs/DbAdapters/x64-linux/lib]
libBackTest.so  RUNPATH = [.../Libs/duckdb/... : .../Libs/DbAdapters/... : .../Libs/Spark/...]
libMdApi.so 等  RUNPATH = [.../Libs/Spark/x64-linux/lib]
libDuckdbWrapper.so  RUNPATH = [$ORIGIN]
libCore.so / libNetwork.so / libSerialization.so / libAsyncDbWriter.so
      / libSqliteWrapper.so / libduckdb.so  → 无 RUNPATH
```

结论：**带绝对 `RUNPATH` 的只有引擎自己的产物**；Spark / DbAdapters 的 ship
库要么无 `RUNPATH`、要么已正确 `$ORIGIN`。

补家规（`-Wl,-rpath,$ORIGIN`）并重新链接后，同日复测：

```text
bin/Release 的 8 个产物   → 每条 RUNPATH 均以 $ORIGIN 开头（绝对项保留在后）

bash PackageLinuxRelease.sh --force
  发布目录：~/.vs/QuantTrading/dist/linux-engine
  引擎版本（取自 engine-version.txt）：1.0.0
  文件数：12
  自检四条全过（契约 §8），另有 9 条警告（不阻断）
  exit=0

探针：把 libNetwork.so 临时改判为「引擎自有」后重跑
  [不通过] libNetwork.so 的依赖未解析：	libCore.so => not found
  [不通过] libNetwork.so 的 RUNPATH 未含 $ORIGIN：无 RPATH/RUNPATH
  exit=4（期望 4）——分档的硬失败侧确实会拦下
```
