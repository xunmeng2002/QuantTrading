#!/usr/bin/env bash
#
# 打 Linux 发布包：把三个仓的运行时产物平铺进一个目录。
# 契约见 docs/engine-linux-release-package.md（§2 清单 / §7 打包要求 / §8 自检）。
#
# 取用一律走**白名单**，绝不写成「取该目录下全部 .so」：拍平输出目录之后，bin/$CONFIG 里
# 还躺着测试程序、MySQL/MariaDB 后端与跑测留下的 *.db —— 目录扫描分不出取舍，白名单才分得
# （契约 §7）。六个 API 中间层与两个应用自 2026-10-13 起进包（契约 §2.1、§2.3）。
#
# 用法：bash PackageLinuxRelease.sh [选项]（本仓 .sh 一律 100644，靠 bash 显式调用）
#   --config <Release|Debug>  取哪套构建产物（默认 Release）
#   --output <dir>            发布目录（默认 <仓根>/dist/linux-engine）
#   --libs <dir>              Spark / DbAdapters 安装树根（默认 <仓根>/../Libs）
#   --zip                     自检通过后，另打一个 zip 包（见下「zip 包形态」）
#   --force                   输出目录已存在且非空时，先递归清空它
#   -h, --help                打印本帮助
#
# 只能在 WSL / Linux 构建树里运行：产物是 .so，且 ../Libs 下需有 x64-linux 安装树。
# --force 的递归删除**只作用于 --output 指定的那个目录**，脚本不删任何其它路径。
#
# zip 包形态（--zip）：落在发布目录的**同级**，名字 QuantTrading-<版本>-linux-<架构>.zip；
# 包内是**一个顶层目录**（同名去 .zip），§2 清单的全部文件平铺其下——与平台侧「换版按版本留目录、
# 不原地覆盖」的约定一致（QuantPlatform docs/platform-plan.md）。解压后把 QUANT_ENGINE_ROOT
# 指到那一层即可。打包与校验只用解释器自带的 zipfile，不依赖 zip(1) / unzip(1)。

set -euo pipefail

ScriptDirectory=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

ConfigName=Release
OutputDirectory=
LibsRoot=
ForceOverwrite=0
CreateZipArchive=0
PythonExecutable=${PYTHON:-python3}
ProjectName=QuantTrading

# 白名单：逐条列名，不做目录扫描（契约 §7 的表）
EngineBinRuntimeNames=(libBackTest.so
    libMdApi.so libMdGbkApi.so libSimExchangeApi.so libSimExchangeGbkApi.so libTraderApi.so libTraderGbkApi.so)
# 引擎自己的产物：缺 $ORIGIN 即不合格；其余 .so 来自 Spark / DbAdapters 安装树（见自检 §8 的判据）
EngineOwnedLibraryNames=(libBackTest.so
    libMdApi.so libMdGbkApi.so libSimExchangeApi.so libSimExchangeGbkApi.so libTraderApi.so libTraderGbkApi.so)
# 引擎自己的应用（可执行文件）：与引擎自有库同档，只是名字不带 .so，故另列
EngineBinExecutableNames=(MdOffer SimExchange)
EngineBinDataNames=(engine-version.txt BackTest.json Sessions.json MdOffer.json SimExchange.json)
SparkRuntimeNames=(libCore.so libNetwork.so libSerialization.so)
DbAdaptersRuntimeNames=(libAsyncDbWriter.so libDuckdbWrapper.so libSqliteWrapper.so libduckdb.so)

# 不该出现在发布目录里的库：MySQL / MariaDB 两个后端。2026-10-13 用户裁定「数据库只需要 sqlite
# 和 duckdb」，故连「按需另定」的余地也不留（契约 §7）
ForbiddenPackageNames=(libMysqlWrapper.so libMariadbWrapper.so)

ExpectedPackageFileCount=22

# 依赖解析的放行名单：解析**不到**发布目录里、也不在系统库目录的依赖，必须逐条列在这里。CTP 的 SDK
# 按再分发边界不随包（契约 §2.3），目标机自备——放进发布目录或走 LD_LIBRARY_PATH 都行。未列名却出现
# 在包外即不合格：那意味着换一台机器就找不到。与 Windows 侧 package_windows_release.py 的
# UNPACKAGED_DEPENDENCY_NAMES 同语义
NotPackagedDependencyNames=(libthostmduserapi_se.so libthosttraderapi_se.so)

# 系统库目录：解析到这里的依赖由目标机的操作系统提供，不归发布包管。只列 OS 自身的库目录——
# /usr/local/lib 不在内，那儿装的是本机自建软件，目标机上未必有，正是这条判据要抓的一类
SystemLibraryDirectories=(/lib /lib64 /usr/lib /usr/lib64)

# 直接打印文件头部的注释块，用法文本只维护一处（表头内不得出现非 # 开头的行）
PrintUsage() {
    awk 'NR > 1 { if ($0 !~ /^#/) exit; sub(/^# ?/, ""); print }' "${BASH_SOURCE[0]}"
}

# 发布目录里每个 .so，加上引擎自己的可执行文件，依次交给回调（回调收到的是完整路径）。
# 几条自检都要遍历同一批产物，骨架抽出来，免得改一处漏一处（Harness §5）
ForEachPackageArtifact() {
    local ArtifactCallback=$1 ArtifactPath ExecutableName
    for ArtifactPath in "$OutputDirectory"/*.so; do
        if [ -f "$ArtifactPath" ]; then
            "$ArtifactCallback" "$ArtifactPath"
        fi
    done
    for ExecutableName in "${EngineBinExecutableNames[@]}"; do
        ArtifactPath="$OutputDirectory/$ExecutableName"
        if [ -f "$ArtifactPath" ]; then
            "$ArtifactCallback" "$ArtifactPath"
        fi
    done
}

# 判定 CandidatePath 是否为 TargetPath 的上级目录（含根：任何路径都在 / 之下）
IsPathAncestorOf() {
    local CandidatePath=$1
    local TargetPath=$2
    if [ "$CandidatePath" = "/" ]; then
        return 0
    fi
    case "$TargetPath" in
        "$CandidatePath"/*) return 0 ;;
    esac
    return 1
}

Fail() {
    printf '打包中止：%s\n' "$1" >&2
    exit "${2:-2}"
}

ReportSelfCheckFailure() {
    printf '  [不通过] %s\n' "$1" >&2
    SelfCheckFailureCount=$((SelfCheckFailureCount + 1))
}

ReportSelfCheckWarning() {
    printf '  [警告] %s\n' "$1" >&2
    SelfCheckWarningCount=$((SelfCheckWarningCount + 1))
}

IsEngineOwnedArtifact() {
    local ArtifactName=$1 CandidateName
    for CandidateName in "${EngineOwnedLibraryNames[@]}" "${EngineBinExecutableNames[@]}"; do
        if [ "$CandidateName" = "$ArtifactName" ]; then
            return 0
        fi
    done
    return 1
}

CopyWhitelistFile() {
    local SourcePath=$1
    local FileName
    FileName=$(basename -- "$SourcePath")
    if [ ! -f "$SourcePath" ]; then
        MissingSourcePaths+=("$SourcePath")
        return 0
    fi
    cp -f -- "$SourcePath" "$OutputDirectory/$FileName"
    CopiedFileCount=$((CopiedFileCount + 1))
    PackagedFileNames+=("$FileName")
}

CopyWhitelistNames() {
    local SourceDirectory=$1
    shift
    local FileName
    for FileName in "$@"; do
        CopyWhitelistFile "$SourceDirectory/$FileName"
    done
}

# 扩展模块的后缀随解释器而定，不写死（契约 §2.2）：按现存产物名匹配
CollectExtensionModulePaths() {
    local Candidate
    for Candidate in "$BinDirectory"/QuantTrading.*.so "$BinDirectory"/QuantTrading.so; do
        if [ -f "$Candidate" ]; then
            printf '%s\n' "$Candidate"
        fi
    done
}

# 与 §8 第 2 条同档：引擎产物缺依赖即不合格；Spark / DbAdapters 的 ship 库单独分析时看不到
# 同目录的 libCore.so（它们无 RUNPATH），只记警告——真实加载时 libCore.so 由扩展模块先映射好，
# 故第 3 条（解释器 import）才是决定性判据
SelfCheckResolvableDependencies() {
    ForEachPackageArtifact CheckArtifactDependenciesResolvable
}

IsSystemLibraryPath() {
    local DependencyPath=$1 SystemDirectory
    for SystemDirectory in "${SystemLibraryDirectories[@]}"; do
        case "$DependencyPath" in
            "$SystemDirectory"/*) return 0 ;;
        esac
    done
    return 1
}

IsNotPackagedDependencyName() {
    local DependencyName=$1 CandidateName
    for CandidateName in "${NotPackagedDependencyNames[@]}"; do
        if [ "$CandidateName" = "$DependencyName" ]; then
            return 0
        fi
    done
    return 1
}

# 「ldd 里没有 not found」在构建机上不等于「换机可跑」：构建机的 RUNPATH 本来就带着 Libs 安装树的
# 绝对目录，包外依赖在这台机器上照样解析成功，那条绿没有信息量。故对引擎自有产物再判一遍**解析到了
# 哪里**——每条依赖要么落在发布目录内、要么是系统库、要么在 NotPackagedDependencyNames 里列着
ReportDependenciesOutsidePackage() {
    local ArtifactName=$1 LddOutput=$2 DependencyName DependencyPath
    while read -r DependencyName DependencyPath; do
        case "$DependencyPath" in
            "$OutputDirectory"/*) continue ;;
        esac
        if IsSystemLibraryPath "$DependencyPath"; then
            continue
        fi
        if IsNotPackagedDependencyName "$DependencyName"; then
            continue
        fi
        ReportSelfCheckFailure "$ArtifactName 的依赖 $DependencyName 解析到包外（$DependencyPath）：该机之外不存在"
    done < <(printf '%s\n' "$LddOutput" |
        sed -n 's/^[[:space:]]*\([^[:space:]]*\) => \(.*\) (0x[0-9a-fA-F]*)$/\1 \2/p')
}

CheckArtifactDependenciesResolvable() {
    local ArtifactPath=$1 ArtifactName LddOutput NotFoundLibrary
    ArtifactName=$(basename -- "$ArtifactPath")
    # ldd 自身失败（非 ELF / 架构不符 / 文件损坏）不能算通过，须与「无缺失」区分开
    if ! LddOutput=$(ldd -- "$ArtifactPath" 2>&1); then
        ReportSelfCheckFailure "$ArtifactName 无法被 ldd 分析：$LddOutput"
        return 0
    fi
    NotFoundLibrary=$(printf '%s\n' "$LddOutput" | grep -i 'not found' || true)
    if ! IsEngineOwnedArtifact "$ArtifactName"; then
        if [ -n "$NotFoundLibrary" ]; then
            ReportSelfCheckWarning "$ArtifactName 无 RUNPATH，单独分析时看不见同目录兄弟库：$NotFoundLibrary"
        fi
        return 0
    fi
    if [ -n "$NotFoundLibrary" ]; then
        ReportSelfCheckFailure "$ArtifactName 的依赖未解析：$NotFoundLibrary"
    fi
    ReportDependenciesOutsidePackage "$ArtifactName" "$LddOutput"
}

# 判据（2026-10-09 裁定）：引擎自己的产物必须含 $ORIGIN，缺即不合格；Spark / DbAdapters
# 安装树来的 ship 库缺 RUNPATH 只记警告（契约 §4.4：不必现在重打 tag，家规随各自下次构建生效）
SelfCheckOriginRunpath() {
    WithAbsolutePathCount=0
    WithEmptyElementCount=0
    ForEachPackageArtifact CheckArtifactOriginRunpath
    if [ "$WithAbsolutePathCount" -gt 0 ]; then
        printf '  [提示] %s 个产物保留了构建机绝对路径（$ORIGIN 在最前，目标机上不存在即跳过）\n' "$WithAbsolutePathCount"
    fi
    if [ "$WithEmptyElementCount" -gt 0 ]; then
        printf '  [提示] %s 个产物的 RUNPATH 含空元素（等于当前目录，属 Libs 安装树遗留）\n' "$WithEmptyElementCount"
    fi
}

CheckArtifactOriginRunpath() {
    local ArtifactPath=$1 ArtifactName RunPath
    ArtifactName=$(basename -- "$ArtifactPath")
    RunPath=$(readelf -d -- "$ArtifactPath" 2>/dev/null | grep -o 'RPATH.*\|RUNPATH.*' || true)
    case "$RunPath" in
        *'$ORIGIN'*) ;;
        *)
            if IsEngineOwnedArtifact "$ArtifactName"; then
                ReportSelfCheckFailure "$ArtifactName 的 RUNPATH 未含 \$ORIGIN：${RunPath:-无 RPATH/RUNPATH}"
            else
                ReportSelfCheckWarning "$ArtifactName 无 \$ORIGIN（三方 ship 库，本批次暂可接受）：${RunPath:-无 RPATH/RUNPATH}"
            fi
            ;;
    esac
    case "$RunPath" in
        */*) WithAbsolutePathCount=$((WithAbsolutePathCount + 1)) ;;
    esac
    # 空元素在 glibc 下等于「当前目录」；来源是 Libs 安装树导出的链接片段带尾随冒号
    case "$RunPath" in
        *':]'*|*'::'*) WithEmptyElementCount=$((WithEmptyElementCount + 1)) ;;
    esac
}

# 契约 §2.3：带斜杠的 NEEDED 由 ld.so 按那条路径**直接**加载、不走 RUNPATH，往包目录里放一份同名库
# 也救不了它——只有目标机上那条路径真存在才能跑。2026-10-13 实测 22 个产物里只有 MdOffer 带绝对路径
# （CTP 的导入库没有 SONAME），2026-10-14 已在 CMakeLists.txt 给 CTP 的两个导入目标置 IMPORTED_NO_SONAME
# 修掉，放行档随之删除：本条对**全部**产物一律是硬闸
SelfCheckAbsoluteNeededPaths() {
    ForEachPackageArtifact CheckArtifactAbsoluteNeededPaths
}

CheckArtifactAbsoluteNeededPaths() {
    local ArtifactPath=$1 ArtifactName AbsoluteNeededPath
    ArtifactName=$(basename -- "$ArtifactPath")
    AbsoluteNeededPath=$(readelf -d -- "$ArtifactPath" 2>/dev/null |
        sed -n 's/.*(NEEDED).*\[\([^]]*\/[^]]*\)\]$/\1/p' || true)
    if [ -z "$AbsoluteNeededPath" ]; then
        return 0
    fi
    ReportSelfCheckFailure "$ArtifactName 的 DT_NEEDED 出现绝对路径（跨机不可用，须改成库名）：$AbsoluteNeededPath"
}

# 决定性的一条：它同时验证扩展模块能找到 libBackTest.so、后者能找到它的兄弟（契约 §8）
# 解释器可能先往 stderr 吐警告（DeprecationWarning 之类），故让 Python 给路径打上前缀，
# 只认带前缀的那一行——否则警告文本混进路径，会变成「扩展模块不在发布目录内」的假失败
SelfCheckInterpreterImport() {
    local InterpreterOutput ImportedModulePath ReleaseDirectory
    if ! InterpreterOutput=$(cd "$OutputDirectory" && PYTHONPATH="$OutputDirectory" "$PythonExecutable" -c \
        'import os, QuantTrading; print("PackageLinuxReleaseModulePath=" + os.path.realpath(QuantTrading.__file__))' 2>&1); then
        ReportSelfCheckFailure "解释器 import QuantTrading 失败：$InterpreterOutput"
        return 0
    fi
    ImportedModulePath=$(printf '%s\n' "$InterpreterOutput" |
        sed -n 's/^PackageLinuxReleaseModulePath=//p' | tail -n 1)
    if [ -z "$ImportedModulePath" ]; then
        ReportSelfCheckFailure "解释器没有打印出扩展模块路径：$InterpreterOutput"
        return 0
    fi
    ReleaseDirectory=$(cd "$OutputDirectory" && pwd -P)
    case "$ImportedModulePath" in
        "$ReleaseDirectory"/*) ;;
        *) ReportSelfCheckFailure "import 到的扩展模块不在发布目录内：$ImportedModulePath（期望前缀 $ReleaseDirectory/）" ;;
    esac
}

SelfCheckPackageContent() {
    local ForbiddenName UnexpectedArtifact ActualFileCount
    for ForbiddenName in "${ForbiddenPackageNames[@]}"; do
        if [ -e "$OutputDirectory/$ForbiddenName" ]; then
            ReportSelfCheckFailure "不该进包的库出现在发布目录：$ForbiddenName"
        fi
    done
    # 契约 §7 的排除项 *.a / *.pdb / .so.* 调试拆分：白名单本就不取，这里是正面兜底
    UnexpectedArtifact=$(find "$OutputDirectory" -mindepth 1 -maxdepth 1 -type f \( -name '*.so.*' -o -name '*.a' -o -name '*.pdb' \) -print)
    if [ -n "$UnexpectedArtifact" ]; then
        ReportSelfCheckFailure "发布目录出现不该进包的产物：$UnexpectedArtifact"
    fi
    if [ -n "$(find "$OutputDirectory" -mindepth 1 -maxdepth 1 -type d)" ]; then
        ReportSelfCheckFailure '发布目录出现子目录（契约要求扁平单目录）'
    fi
    ActualFileCount=$(find "$OutputDirectory" -maxdepth 1 -type f | wc -l)
    if [ "$ActualFileCount" -ne "$ExpectedPackageFileCount" ]; then
        ReportSelfCheckFailure "发布目录文件数 $ActualFileCount，与契约 §2 清单的 $ExpectedPackageFileCount 项不符"
    fi
}

# 打 zip 的实现与 Windows 打包脚本共用一份（release_zip.py，跨平台）：按白名单取件、不扫目录，
# 包内是**一个**顶层目录，写完立刻重开复验。这里只管算包名、转述摘要、映射退出码。
CreateReleaseZipArchive() {
    local ArchiveRootName ArchivePath ArchiveResult
    ArchiveRootName="$ProjectName-$EngineVersion-linux-$(uname -m)"
    ArchivePath="$(dirname -- "$OutputDirectory")/$ArchiveRootName.zip"
    if ! ArchiveResult=$("$PythonExecutable" "$ScriptDirectory/release_zip.py" \
        --source "$OutputDirectory" --archive "$ArchivePath" --root-name "$ArchiveRootName" \
        "${PackagedFileNames[@]}"); then
        Fail "打 zip 失败：$ArchiveResult" 5
    fi
    printf '\n%s\n' "$ArchiveResult"
}

while [ $# -gt 0 ]; do
    case "$1" in
        --config|--output|--libs)
            [ $# -ge 2 ] || Fail "$1 缺少取值"
            case "$2" in
                ''|-*) Fail "$1 的取值不可用：'$2'（空值或以 - 开头，像是把下一个选项吞了取值）" ;;
            esac
            case "$1" in
                --config)
                    ConfigName=$2
                    ;;
                --output)
                    case "$2" in
                        .|..) Fail "--output 不接受 . 或 ..：$2（会清空当前目录或它的上级，请写明目标目录）" ;;
                    esac
                    OutputDirectory=$2
                    ;;
                --libs)
                    LibsRoot=$2
                    ;;
            esac
            shift 2
            ;;
        --force)
            ForceOverwrite=1
            shift
            ;;
        --zip)
            CreateZipArchive=1
            shift
            ;;
        -h|--help)
            PrintUsage
            exit 0
            ;;
        *)
            Fail "未知参数：$1"
            ;;
    esac
done

case "$ConfigName" in
    Release|Debug) ;;
    *) Fail "--config 只接受 Release 或 Debug，收到：$ConfigName" ;;
esac

BinDirectory="$ScriptDirectory/bin/$ConfigName"
LibsRoot=${LibsRoot:-"$ScriptDirectory/../Libs"}
OutputDirectory=${OutputDirectory:-"$ScriptDirectory/dist/linux-engine"}

if [ ! -d "$BinDirectory" ]; then
    Fail "构建产物目录不存在（先在 WSL 里构建）：$BinDirectory"
fi
if [ ! -d "$LibsRoot" ]; then
    Fail "Libs 根目录不存在：$LibsRoot（Spark / DbAdapters 的 x64-linux 安装树需在其中）"
fi
LibsRoot=$(cd -- "$LibsRoot" && pwd)

# --force 会递归删除，故守卫一律作用于**规范化后**的路径：只看原始字符串时，
# "<目录>/"、"<目录>/."、"<软链>/" 等写法都能绕过比较，而 rm -rf 会跟随软链、落到链接目标。
# 符号链接用「逻辑规范化后是否仍是链接」来判：realpath -m -s 只做词法归一、不展开软链，
# 故它给出的路径若自身是链接，就说明用户指的就是链接本身（"<软链>/" 与 "<软链>/." 两种
# 写法下 `[ -L ]` 直接测原串都会返回假，这一句能把它们一并拦下）。
if [ -L "$(realpath -m -s -- "$OutputDirectory")" ]; then
    Fail "拒绝覆盖符号链接目录：$OutputDirectory（递归删除会跟随链接落到它的目标）"
fi
ResolvedOutputDirectory=$(realpath -m -- "$OutputDirectory")
ResolvedScriptDirectory=$(realpath -m -- "$ScriptDirectory")
if [ -z "${HOME:-}" ]; then
    Fail '环境变量 HOME 未设置：无法做「输出目录不得为家目录」的守卫'
fi
ResolvedHomeDirectory=$(realpath -m -- "$HOME")

if [ "$ResolvedOutputDirectory" = "$ResolvedScriptDirectory" ] || [ "$ResolvedOutputDirectory" = "$ResolvedHomeDirectory" ]; then
    Fail "--output 指向了不可清空的目录：$ResolvedOutputDirectory"
fi
if IsPathAncestorOf "$ResolvedOutputDirectory" "$ResolvedScriptDirectory" || IsPathAncestorOf "$ResolvedOutputDirectory" "$ResolvedHomeDirectory"; then
    Fail "--output 指向了仓库或家目录的上级：$ResolvedOutputDirectory"
fi

if [ -e "$ResolvedOutputDirectory" ] && [ ! -d "$ResolvedOutputDirectory" ]; then
    Fail "输出路径已存在且不是目录：$ResolvedOutputDirectory"
fi
if [ -d "$ResolvedOutputDirectory" ] && [ -n "$(ls -A -- "$ResolvedOutputDirectory")" ]; then
    if [ "$ForceOverwrite" -eq 0 ]; then
        printf '打包中止：输出目录非空：%s\n' "$ResolvedOutputDirectory" >&2
        printf '          确认可覆盖后再加 --force（该参数会递归清空此目录）\n' >&2
        exit 2
    fi
    printf '覆盖：清空输出目录 %s\n' "$ResolvedOutputDirectory" >&2
    rm -rf -- "$ResolvedOutputDirectory"
fi
mkdir -p -- "$ResolvedOutputDirectory"
OutputDirectory=$ResolvedOutputDirectory

MissingSourcePaths=()
CopiedFileCount=0
# 已进包的文件名（与复制同一处登记）：打 zip 时按清单取件，不再回头扫目录
PackagedFileNames=()

CopyWhitelistNames "$BinDirectory" "${EngineBinRuntimeNames[@]}"
CopyWhitelistNames "$BinDirectory" "${EngineBinExecutableNames[@]}"
CopyWhitelistNames "$BinDirectory" "${EngineBinDataNames[@]}"
CopyWhitelistNames "$LibsRoot/Spark/x64-linux/lib" "${SparkRuntimeNames[@]}"
CopyWhitelistNames "$LibsRoot/DbAdapters/x64-linux/lib" "${DbAdaptersRuntimeNames[@]}"

ExtensionModulePaths=()
while IFS= read -r ExtensionModulePath; do
    if [ -n "$ExtensionModulePath" ]; then
        ExtensionModulePaths+=("$ExtensionModulePath")
    fi
done < <(CollectExtensionModulePaths)

if [ ${#ExtensionModulePaths[@]} -eq 0 ]; then
    MissingSourcePaths+=("$BinDirectory/QuantTrading.<扩展模块后缀>.so")
elif [ ${#ExtensionModulePaths[@]} -gt 1 ]; then
    printf '打包中止：bin/%s 下有多个扩展模块，白名单只取 1 项（契约 §2.2）\n' "$ConfigName" >&2
    printf '  %s\n' "${ExtensionModulePaths[@]}" >&2
    printf '  请清理陈旧产物后重跑，脚本不代为择一\n' >&2
    exit 3
else
    CopyWhitelistFile "${ExtensionModulePaths[0]}"
    EngineOwnedLibraryNames+=("$(basename -- "${ExtensionModulePaths[0]}")")
fi

if [ ${#MissingSourcePaths[@]} -gt 0 ]; then
    printf '打包中止：以下白名单文件缺失（不静默少文件）\n' >&2
    printf '  %s\n' "${MissingSourcePaths[@]}" >&2
    exit 3
fi

EngineVersionFile="$OutputDirectory/engine-version.txt"
EngineVersion=$(sed -n '/^[[:space:]]*$/d; s/^[[:space:]]*//; s/[[:space:]]*$//; p; q' -- "$EngineVersionFile")
if [ -z "$EngineVersion" ]; then
    Fail "engine-version.txt 无可读版本行：$EngineVersionFile" 3
fi

SelfCheckFailureCount=0
SelfCheckWarningCount=0
SelfCheckPackageContent
SelfCheckResolvableDependencies
SelfCheckOriginRunpath
SelfCheckAbsoluteNeededPaths
SelfCheckInterpreterImport

printf '\n发布目录：%s\n' "$OutputDirectory"
printf '引擎版本（取自 engine-version.txt）：%s\n' "$EngineVersion"
printf '文件数：%s\n\n' "$CopiedFileCount"
ls -l -- "$OutputDirectory"

if [ "$SelfCheckFailureCount" -gt 0 ]; then
    printf '\n自检未通过：%s 项（契约 §8）\n' "$SelfCheckFailureCount" >&2
    exit 4
fi
# 只在自检全过之后打 zip：不合格的包不该被封装成「可交付的样子」
if [ "$CreateZipArchive" -eq 1 ]; then
    CreateReleaseZipArchive
fi
printf '\n自检全过（契约 §8）'
if [ "$SelfCheckWarningCount" -gt 0 ]; then
    printf '，另有 %s 条警告（不阻断）' "$SelfCheckWarningCount"
fi
printf '\n'
