#!/usr/bin/env bash
#
# 打 Linux 回测发布包：把三个仓的运行时产物平铺进一个目录。
# 契约见 docs/engine-linux-release-package.md（§2 清单 / §7 打包要求 / §8 自检四条）。
#
# 取用一律走**白名单**，绝不写成「取该目录下全部 .so」：拍平输出目录之后，
# bin/$CONFIG 里同时装着六个 API 中间层，它们不在回测闭包、不进发布包（契约 §2.1）。
#
# 用法：bash PackageLinuxRelease.sh [选项]（本仓 .sh 一律 100644，靠 bash 显式调用）
#   --config <Release|Debug>  取哪套构建产物（默认 Release）
#   --output <dir>            发布目录（默认 <仓根>/dist/linux-engine）
#   --libs <dir>              Spark / DbAdapters 安装树根（默认 <仓根>/../Libs）
#   --force                   输出目录已存在且非空时，先递归清空它
#   -h, --help                打印本帮助
#
# 只能在 WSL / Linux 构建树里运行：产物是 .so，且 ../Libs 下需有 x64-linux 安装树。
# --force 的递归删除**只作用于 --output 指定的那个目录**，脚本不删任何其它路径。

set -euo pipefail

ScriptDirectory=$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)

ConfigName=Release
OutputDirectory=
LibsRoot=
ForceOverwrite=0
PythonExecutable=${PYTHON:-python3}

# 白名单：逐条列名，不做目录扫描（契约 §7 的表）
EngineBinRuntimeNames=(libBackTest.so)
# 引擎自己的产物：缺 $ORIGIN 即不合格；其余 .so 来自 Spark / DbAdapters 安装树（见自检 §8 的判据）
EngineOwnedLibraryNames=(libBackTest.so)
EngineBinDataNames=(engine-version.txt BackTest.json Sessions.json)
SparkRuntimeNames=(libCore.so libNetwork.so libSerialization.so)
DbAdaptersRuntimeNames=(libAsyncDbWriter.so libDuckdbWrapper.so libSqliteWrapper.so libduckdb.so)

# 不该出现在发布目录里的库：六个 API 中间层（契约 §2.1）+ 按需另定的两个数据库后端（契约 §7）
ForbiddenPackageNames=(libMdApi.so libMdGbkApi.so libSimExchangeApi.so libSimExchangeGbkApi.so
    libTraderApi.so libTraderGbkApi.so libMysqlWrapper.so libMariadbWrapper.so)

ExpectedPackageFileCount=12

# 直接打印文件头部的注释块，用法文本只维护一处（表头内不得出现非 # 开头的行）
PrintUsage() {
    awk 'NR > 1 { if ($0 !~ /^#/) exit; sub(/^# ?/, ""); print }' "${BASH_SOURCE[0]}"
}

# 发布目录里的每个 .so 依次交给回调（回调收到的参数是该 .so 的完整路径）。
# 两条自检都要遍历同一批文件，骨架抽出来，免得改一处漏一处（Harness §5）
ForEachPackageLibrary() {
    local LibraryCallback=$1 LibraryFile
    for LibraryFile in "$OutputDirectory"/*.so; do
        if [ -f "$LibraryFile" ]; then
            "$LibraryCallback" "$LibraryFile"
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

IsEngineOwnedLibrary() {
    local LibraryName=$1 CandidateName
    for CandidateName in "${EngineOwnedLibraryNames[@]}"; do
        if [ "$CandidateName" = "$LibraryName" ]; then
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
    ForEachPackageLibrary CheckLibraryDependenciesResolvable
}

CheckLibraryDependenciesResolvable() {
    local LibraryFile=$1 LibraryName LddOutput NotFoundLibrary
    LibraryName=$(basename -- "$LibraryFile")
    # ldd 自身失败（非 ELF / 架构不符 / 文件损坏）不能算通过，须与「无缺失」区分开
    if ! LddOutput=$(ldd -- "$LibraryFile" 2>&1); then
        ReportSelfCheckFailure "$LibraryName 无法被 ldd 分析：$LddOutput"
        return 0
    fi
    NotFoundLibrary=$(printf '%s\n' "$LddOutput" | grep -i 'not found' || true)
    if [ -z "$NotFoundLibrary" ]; then
        return 0
    fi
    if IsEngineOwnedLibrary "$LibraryName"; then
        ReportSelfCheckFailure "$LibraryName 的依赖未解析：$NotFoundLibrary"
    else
        ReportSelfCheckWarning "$LibraryName 无 RUNPATH，单独分析时看不见同目录兄弟库：$NotFoundLibrary"
    fi
}

# 判据（2026-10-09 裁定）：引擎自己的产物必须含 $ORIGIN，缺即不合格；Spark / DbAdapters
# 安装树来的 ship 库缺 RUNPATH 只记警告（契约 §4.4：不必现在重打 tag，家规随各自下次构建生效）
SelfCheckOriginRunpath() {
    WithAbsolutePathCount=0
    WithEmptyElementCount=0
    ForEachPackageLibrary CheckLibraryOriginRunpath
    if [ "$WithAbsolutePathCount" -gt 0 ]; then
        printf '  [提示] %s 个产物保留了构建机绝对路径（$ORIGIN 在最前，目标机上不存在即跳过）\n' "$WithAbsolutePathCount"
    fi
    if [ "$WithEmptyElementCount" -gt 0 ]; then
        printf '  [提示] %s 个产物的 RUNPATH 含空元素（等于当前目录，属 Libs 安装树遗留）\n' "$WithEmptyElementCount"
    fi
}

CheckLibraryOriginRunpath() {
    local LibraryFile=$1 LibraryName RunPath
    LibraryName=$(basename -- "$LibraryFile")
    RunPath=$(readelf -d -- "$LibraryFile" 2>/dev/null | grep -o 'RPATH.*\|RUNPATH.*' || true)
    case "$RunPath" in
        *'$ORIGIN'*) ;;
        *)
            if IsEngineOwnedLibrary "$LibraryName"; then
                ReportSelfCheckFailure "$LibraryName 的 RUNPATH 未含 \$ORIGIN：${RunPath:-无 RPATH/RUNPATH}"
            else
                ReportSelfCheckWarning "$LibraryName 无 \$ORIGIN（三方 ship 库，本批次暂可接受）：${RunPath:-无 RPATH/RUNPATH}"
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

CopyWhitelistNames "$BinDirectory" "${EngineBinRuntimeNames[@]}"
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
SelfCheckInterpreterImport

printf '\n发布目录：%s\n' "$OutputDirectory"
printf '引擎版本（取自 engine-version.txt）：%s\n' "$EngineVersion"
printf '文件数：%s\n\n' "$CopiedFileCount"
ls -l -- "$OutputDirectory"

if [ "$SelfCheckFailureCount" -gt 0 ]; then
    printf '\n自检未通过：%s 项（契约 §8）\n' "$SelfCheckFailureCount" >&2
    exit 4
fi
if [ "$SelfCheckWarningCount" -gt 0 ]; then
    printf '\n自检四条全过（契约 §8），另有 %s 条警告（不阻断）\n' "$SelfCheckWarningCount"
    exit 0
fi
printf '\n自检四条全过（契约 §8）\n'
