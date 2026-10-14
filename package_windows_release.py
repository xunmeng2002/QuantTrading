#!/usr/bin/env python3
"""打 Windows 发布包：把引擎运行时产物平铺进一个目录，并按需封装成一个 zip。

与 `PackageLinuxRelease.sh` 同源，差异全部来自平台本身：

- Linux 的依赖靠 `RUNPATH: $ORIGIN` 解析，三方库走系统包管理器，包内只背 `libduckdb.so`；
  Windows 的依赖靠「与镜像同目录」解析（PE 没有 RPATH 这回事），故三方 DLL 必须随包。
  这是本脚本多出 `sqlite3.dll` 一项的原因——Linux 上它由系统提供。
- Linux 侧的产物从 `bin/<配置>` 与 `../Libs/*/x64-linux/lib` 两处取；Windows 侧 CMake
  已把 Spark / DbAdapters 的 DLL 拷进 `bin/<配置>`，故本脚本只有一个来源目录。
- 契约：本平台见 `docs/engine-windows-release-package.md`（与 Linux 那份同骨架、同口径）。
  §7 的通用要求（显式白名单、缺项点名并非零退出、扁平单目录、版本只取自 `engine-version.txt`、
  zip 在自检全过之后）两边一致，§2 的清单按平台替换，Windows 侧即本文件的常量元组。

**目标机前提**：MSVC 运行库（`MSVCP140.dll` / `VCRUNTIME140.dll` / `VCRUNTIME140_1.dll`）与
系统 API 集（`KERNEL32.dll` / `api-ms-win-crt-*.dll` 等）由目标机提供，本包不含——装了
Visual C++ 2015-2022 可再发行包或装过带它的程序即可。自检只能判「构建目录里有的依赖有没
有进包」，判不了这一层，故单列成前提。

两处**刻意不进包**的依赖，自检认得它们、不误报：

- `python314.dll`：宿主解释器进程里已加载同名模块，包内再放一份既无用、又会在解释器补丁
  版本不一致时被优先命中。
- `thostmduserapi_se.dll`（CTP 行情 SDK）：`MdOffer.exe` 静态导入它，但第三方 SDK 的再分发
  责任不背（2026-10-13 就 Linux 侧定的同一条边界）。要用 `MdOffer` 的机器，把该 DLL 放进
  发布目录即可——PE 按镜像同目录解析，本就没有「绝对路径绕开搜索」的余地，与 Linux 侧
  2026-10-14 修掉绝对路径 `DT_NEEDED` 之后的口径一致。

用法：`py -3.14 package_windows_release.py [选项]`

    --config <Release|Debug>  取哪套构建产物（默认 Release）
    --output <目录>           发布目录（默认 <仓根>/dist/windows-engine）
    --zip                     自检通过后，另打一个 zip（落在发布目录的**同级**）
    --force                   输出目录已存在且非空时，先递归清空它（只作用于 --output 指向的目录）
    -h, --help                打印本帮助

`--zip` 的包内是**一个顶层目录**，清单里的文件平铺其下——与平台侧「换版按版本留目录、不原地
覆盖」的约定一致。
"""

import argparse
import os
import pathlib
import shutil
import struct
import subprocess
import sys

import release_zip

SCRIPT_DIRECTORY = pathlib.Path(__file__).resolve().parent
PROJECT_NAME = "QuantTrading"

ENGINE_BIN_RUNTIME_NAMES = (
    "BackTest.dll",
    "MdApi.dll",
    "MdGbkApi.dll",
    "SimExchangeApi.dll",
    "SimExchangeGbkApi.dll",
    "TraderApi.dll",
    "TraderGbkApi.dll",
)
ENGINE_BIN_EXECUTABLE_NAMES = ("MdOffer.exe", "SimExchange.exe")
ENGINE_BIN_DATA_NAMES = ("engine-version.txt", "BackTest.json", "Sessions.json", "MdOffer.json", "SimExchange.json")
SPARK_RUNTIME_NAMES = ("Core.dll", "Network.dll", "Serialization.dll")
DB_ADAPTERS_RUNTIME_NAMES = ("AsyncDbWriter.dll", "DuckdbWrapper.dll", "SqliteWrapper.dll", "duckdb.dll", "sqlite3.dll")

FORBIDDEN_PACKAGE_NAMES = (
    "MariadbWrapper.dll",
    "MysqlWrapper.dll",
    "mariadbcpp.dll",
    "mysqlcppconnx-2-vs14.dll",
    "libmariadb.dll",
)
UNPACKAGED_DEPENDENCY_NAMES = ("python314.dll", "thostmduserapi_se.dll")
DEBUG_ARTIFACT_SUFFIXES = (".pdb", ".lib", ".exp", ".obj", ".ilk")

PE_IMPORT_DLL_SUFFIXES = (".dll", ".exe", ".pyd")
PE_SECTION_HEADER_SIZE = 40
PE32_DATA_DIRECTORY_OFFSET = 96
PE32_PLUS_DATA_DIRECTORY_OFFSET = 112
IMPORT_DIRECTORY_INDEX = 1
IMPORT_DESCRIPTOR_SIZE = 20


class SelfCheckReport:
    """自检结论：失败拦下交付，警告只留给读者看。"""

    def __init__(self) -> None:
        self.failure_messages: list[str] = []
        self.warning_messages: list[str] = []

    def add_failure(self, message: str) -> None:
        self.failure_messages.append(message)

    def add_warning(self, message: str) -> None:
        self.warning_messages.append(message)

    def has_failures(self) -> bool:
        return bool(self.failure_messages)

    def print_report(self) -> None:
        for message in self.failure_messages:
            print(f"  [不通过] {message}", file=sys.stderr)
        for message in self.warning_messages:
            print(f"  [警告] {message}", file=sys.stderr)


def read_pe_import_names(pe_path: pathlib.Path) -> list[str]:
    """读出 PE 的导入 DLL 名。只认静态导入表，不覆盖 delay-import，够「该带没带」这一问用。"""
    image = pe_path.read_bytes()
    pe_offset = struct.unpack_from("<I", image, 0x3C)[0]
    if image[pe_offset:pe_offset + 4] != b"PE\0\0":
        raise ValueError(f"不是 PE 文件：{pe_path}")
    section_count, = struct.unpack_from("<H", image, pe_offset + 6)
    optional_header_size, = struct.unpack_from("<H", image, pe_offset + 20)
    optional_header_offset = pe_offset + 24
    magic, = struct.unpack_from("<H", image, optional_header_offset)
    data_directory_offset = optional_header_offset + (
        PE32_PLUS_DATA_DIRECTORY_OFFSET if magic == 0x20B else PE32_DATA_DIRECTORY_OFFSET
    )
    import_rva, _ = struct.unpack_from("<II", image, data_directory_offset + IMPORT_DIRECTORY_INDEX * 8)
    if import_rva == 0:
        return []

    sections: list[tuple[int, int, int]] = []
    section_header_offset = optional_header_offset + optional_header_size
    for index in range(section_count):
        base = section_header_offset + index * PE_SECTION_HEADER_SIZE
        virtual_size, virtual_address, raw_size, raw_offset = struct.unpack_from("<IIII", image, base + 8)
        sections.append((virtual_address, max(virtual_size, raw_size), raw_offset))

    def to_file_offset(rva: int) -> int:
        for virtual_address, span, raw_offset in sections:
            if virtual_address <= rva < virtual_address + span:
                return raw_offset + (rva - virtual_address)
        raise ValueError(f"RVA {rva:#x} 不在任何节内：{pe_path}")

    import_names: list[str] = []
    descriptor_offset = to_file_offset(import_rva)
    while True:
        _, _, _, name_rva, _ = struct.unpack_from("<IIIII", image, descriptor_offset)
        if name_rva == 0:
            break
        name_offset = to_file_offset(name_rva)
        name_end = image.index(b"\0", name_offset)
        import_names.append(image[name_offset:name_end].decode("ascii"))
        descriptor_offset += IMPORT_DESCRIPTOR_SIZE
    return import_names


def copy_whitelist_files(source_directory: pathlib.Path, file_names: tuple[str, ...], output_directory: pathlib.Path) -> list[str]:
    missing_names: list[str] = []
    for file_name in file_names:
        source_path = source_directory / file_name
        if not source_path.is_file():
            missing_names.append(file_name)
            continue
        shutil.copyfile(source_path, output_directory / file_name)
    return missing_names


def collect_extension_module_names(bin_directory: pathlib.Path) -> list[str]:
    candidates = sorted(entry.name for entry in bin_directory.glob("QuantTrading.*.pyd"))
    plain_module = bin_directory / "QuantTrading.pyd"
    if plain_module.is_file():
        candidates.append(plain_module.name)
    return candidates


def check_package_content(output_directory: pathlib.Path, expected_file_count: int, report: SelfCheckReport) -> None:
    for forbidden_name in FORBIDDEN_PACKAGE_NAMES:
        if (output_directory / forbidden_name).exists():
            report.add_failure(f"不该进包的库出现在发布目录：{forbidden_name}")
    for entry in sorted(output_directory.iterdir()):
        if entry.is_dir():
            report.add_failure(f"发布目录出现子目录（契约要求扁平单目录）：{entry.name}")
        elif entry.suffix.lower() in DEBUG_ARTIFACT_SUFFIXES:
            report.add_failure(f"发布目录出现不该进包的产物：{entry.name}")
    actual_file_count = sum(1 for entry in output_directory.iterdir() if entry.is_file())
    if actual_file_count != expected_file_count:
        report.add_failure(f"发布目录文件数 {actual_file_count}，与清单的 {expected_file_count} 项不符")


def check_whitelist_covers_dependencies(output_directory: pathlib.Path, bin_directory: pathlib.Path, report: SelfCheckReport) -> None:
    """判「构建目录里有的依赖，是不是都进了包」——系统运行库不在射程内（见模块说明的「目标机前提」）。"""
    packaged_names = {entry.name.lower() for entry in output_directory.iterdir() if entry.is_file()}
    for entry in sorted(output_directory.iterdir()):
        if not entry.is_file() or entry.suffix.lower() not in PE_IMPORT_DLL_SUFFIXES:
            continue
        try:
            import_names = read_pe_import_names(entry)
        except (ValueError, struct.error) as error:
            report.add_failure(f"{entry.name} 无法解析导入表：{error}")
            continue
        absent_names = [
            name for name in import_names
            if (bin_directory / name).is_file()
            and name.lower() not in packaged_names
            and name.lower() not in UNPACKAGED_DEPENDENCY_NAMES
        ]
        if absent_names:
            report.add_failure(f"{entry.name} 依赖了构建目录里有、却没进包的库：{', '.join(sorted(set(absent_names)))}")


def check_interpreter_import(output_directory: pathlib.Path, report: SelfCheckReport) -> None:
    """与 Linux 侧 §8 第 3 条同构：它同时验扩展模块、`BackTest.dll` 与它们的三方依赖。"""
    import_check_source = "import os, QuantTrading; print('ReleasePackageModulePath=' + os.path.realpath(QuantTrading.__file__))"
    completed = subprocess.run(
        [sys.executable, "-c", import_check_source],
        cwd=output_directory,
        env={**os.environ, "PYTHONPATH": str(output_directory)},
        capture_output=True,
        text=True,
    )
    if completed.returncode != 0:
        report.add_failure(f"解释器 import QuantTrading 失败：{completed.stdout}{completed.stderr}")
        return
    module_path_lines = [
        line.removeprefix("ReleasePackageModulePath=")
        for line in completed.stdout.splitlines()
        if line.startswith("ReleasePackageModulePath=")
    ]
    if not module_path_lines:
        report.add_failure(f"解释器没有打印出扩展模块路径：{completed.stdout}{completed.stderr}")
        return
    imported_module_path = pathlib.Path(module_path_lines[-1])
    if not imported_module_path.is_relative_to(output_directory):
        report.add_failure(f"import 到的扩展模块不在发布目录内：{imported_module_path}")


def read_engine_version(version_file_path: pathlib.Path) -> str:
    for line in version_file_path.read_text(encoding="utf-8-sig").splitlines():
        stripped = line.strip()
        if stripped:
            return stripped
    return ""


def is_path_same_or_ancestor_of(candidate_path: pathlib.Path, target_path: pathlib.Path) -> bool:
    return candidate_path == target_path or candidate_path in target_path.parents


def resolve_output_directory(requested_directory: str, force_overwrite: bool) -> pathlib.Path:
    if requested_directory.strip() in ("", ".", ".."):
        raise ValueError(f"--output 不接受空值、. 或 ..：{requested_directory!r}（会清空当前目录或它的上级，请写明目标目录）")
    requested_path = pathlib.Path(requested_directory)
    if requested_path.is_symlink():
        raise ValueError(f"拒绝覆盖符号链接目录：{requested_path}（递归清空会落到它的目标）")
    output_directory = requested_path.resolve()
    reserved_directories = (SCRIPT_DIRECTORY, pathlib.Path.home().resolve())
    for reserved_directory in reserved_directories:
        if is_path_same_or_ancestor_of(output_directory, reserved_directory):
            raise ValueError(f"--output 指向了仓库或家目录本身及其上级：{output_directory}")
    if output_directory.exists() and not output_directory.is_dir():
        raise ValueError(f"输出路径已存在且不是目录：{output_directory}")
    if output_directory.is_dir() and any(output_directory.iterdir()):
        if not force_overwrite:
            raise ValueError(f"输出目录非空：{output_directory}（确认可覆盖后再加 --force，该参数会递归清空它）")
        print(f"覆盖：清空输出目录 {output_directory}", file=sys.stderr)
        shutil.rmtree(output_directory)
    output_directory.mkdir(parents=True, exist_ok=True)
    return output_directory


def parse_arguments() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    parser.add_argument("--config", default="Release", choices=("Release", "Debug"), help="取哪套构建产物（默认 Release）")
    parser.add_argument("--output", default=str(SCRIPT_DIRECTORY / "dist" / "windows-engine"), help="发布目录（默认 <仓根>/dist/windows-engine）")
    parser.add_argument("--zip", dest="create_zip", action="store_true", help="自检通过后，另打一个 zip（落在发布目录的同级）")
    parser.add_argument("--force", dest="force_overwrite", action="store_true", help="输出目录已存在且非空时，先递归清空它")
    return parser.parse_args()


def collect_extension_module_name(bin_directory: pathlib.Path, config_name: str) -> str:
    extension_module_names = collect_extension_module_names(bin_directory)
    if len(extension_module_names) == 1:
        return extension_module_names[0]
    if not extension_module_names:
        raise ValueError(f"打包中止：bin/{config_name} 下没有扩展模块（找的是 QuantTrading.*.pyd 与 QuantTrading.pyd）")
    raise ValueError(
        f"打包中止：bin/{config_name} 下有 {len(extension_module_names)} 个扩展模块，清单只取 1 项："
        f"{extension_module_names}（请清理陈旧产物后重跑，脚本不代为择一）"
    )


def main() -> int:
    arguments = parse_arguments()
    if sys.platform != "win32":
        print("打包中止：本脚本只在 Windows 构建树里运行（产物是 PE）", file=sys.stderr)
        return 2
    bin_directory = SCRIPT_DIRECTORY / "bin" / arguments.config
    if not bin_directory.is_dir():
        print(f"打包中止：构建产物目录不存在：{bin_directory}", file=sys.stderr)
        return 2

    try:
        extension_module_name = collect_extension_module_name(bin_directory, arguments.config)
        output_directory = resolve_output_directory(arguments.output, arguments.force_overwrite)
        whitelist_names = (
            ENGINE_BIN_RUNTIME_NAMES + ENGINE_BIN_EXECUTABLE_NAMES + ENGINE_BIN_DATA_NAMES
            + SPARK_RUNTIME_NAMES + DB_ADAPTERS_RUNTIME_NAMES + (extension_module_name,)
        )
        missing_names = copy_whitelist_files(bin_directory, whitelist_names, output_directory)
    except OSError as error:
        print(f"打包中止：{error}", file=sys.stderr)
        return 2
    except ValueError as error:
        print(f"{error}", file=sys.stderr)
        return 3

    if missing_names:
        print("打包中止：以下清单文件缺失（不静默少文件）", file=sys.stderr)
        for missing_name in missing_names:
            print(f"  {bin_directory / missing_name}", file=sys.stderr)
        return 3

    engine_version = read_engine_version(output_directory / "engine-version.txt")
    if not engine_version:
        print(f"打包中止：engine-version.txt 无可读版本行：{output_directory / 'engine-version.txt'}", file=sys.stderr)
        return 3

    report = SelfCheckReport()
    check_package_content(output_directory, len(whitelist_names), report)
    check_whitelist_covers_dependencies(output_directory, bin_directory, report)
    check_interpreter_import(output_directory, report)

    print(f"\n发布目录：{output_directory}")
    print(f"引擎版本（取自 engine-version.txt）：{engine_version}")
    print(f"文件数：{len(whitelist_names)}\n")
    for file_name in sorted(whitelist_names):
        print(f"  {(output_directory / file_name).stat().st_size:>12,}  {file_name}")

    report.print_report()
    if report.has_failures():
        print(f"\n自检未通过：{len(report.failure_messages)} 项（契约 §8）", file=sys.stderr)
        return 4
    if arguments.create_zip:
        try:
            print()
            archive_root_name = f"{PROJECT_NAME}-{engine_version}-windows-x86_64"
            release_zip.create_release_zip(
                output_directory, list(whitelist_names), output_directory.parent / f"{archive_root_name}.zip", archive_root_name
            )
        except (ValueError, OSError) as error:
            print(f"打包中止：{error}", file=sys.stderr)
            return 5
    summary = "\n自检全过（契约 §8）"
    if report.warning_messages:
        summary += f"，另有 {len(report.warning_messages)} 条警告（不阻断）"
    print(summary)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
