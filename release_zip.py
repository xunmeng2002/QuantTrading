"""发布包 zip 的公共实现：两个平台的打包脚本共用一份，免得同一段写法在两处各自漂移。

包内是**一个**顶层目录，清单里的文件平铺其下（解压即得「按版本留」的那一层）。只用解释器
自带的 `zipfile`：`zip(1)` / `unzip(1)` 不保证每台机器都有，而解释器是本引擎的硬要求。
写完立刻重开复验（能读出、条目数一致、无嵌套目录）——包坏了要在打包时报出来，不能留到
部署时才发现。

条目走 `ZipFile.write`，它内部按 `ZipInfo.from_file` 建条目，权限位随文件带上（Linux 侧的
可执行位靠它）；顺序由本模块统一排序，调用方给集不给序。

命令行（供 `PackageLinuxRelease.sh` 调用）：

    python3 release_zip.py --source <发布目录> --archive <zip 路径> --root-name <顶层目录名> <文件名...>

退出码：0 成功；1 失败（原因打到 stderr，调用方原样转述）。
"""

import argparse
import pathlib
import sys
import zipfile


def create_release_zip(source_directory: pathlib.Path, file_names: list[str], archive_path: pathlib.Path, archive_root_name: str) -> int:
    """按清单打 zip 并复验，返回 zip 字节数；摘要打到 stdout，失败抛 `ValueError`。"""
    if not file_names:
        raise ValueError(f"清单为空，拒绝打出空包：{source_directory}")
    if archive_path.exists():
        print(f"覆盖既有 zip：{archive_path}", file=sys.stderr)
    with zipfile.ZipFile(archive_path, "w", zipfile.ZIP_DEFLATED) as archive:
        for file_name in sorted(file_names):
            archive.write(source_directory / file_name, f"{archive_root_name}/{file_name}")
    with zipfile.ZipFile(archive_path) as archive:
        broken_name = archive.testzip()
        if broken_name is not None:
            raise ValueError(f"zip 校验失败，首个损坏条目：{broken_name}")
        archived_names = [name for name in archive.namelist() if not name.endswith("/")]
        if len(archived_names) != len(file_names):
            raise ValueError(f"zip 里条目数 {len(archived_names)} 与发布文件数 {len(file_names)} 不符")
        stray_names = [
            name for name in archived_names
            if name.count("/") != 1 or name.split("/")[0] != archive_root_name
        ]
        if stray_names:
            raise ValueError(f"zip 里出现不在顶层目录下的条目：{stray_names}")
    archive_size = archive_path.stat().st_size
    print(f"zip 包：{archive_path}")
    print(f"包内顶层目录：{archive_root_name}/（{len(file_names)} 个文件）")
    print(f"zip 大小：{archive_size} 字节")
    return archive_size


def parse_arguments() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="按清单把发布目录打成一个 zip 并复验（两个平台的打包脚本共用）。")
    parser.add_argument("--source", required=True, help="发布目录")
    parser.add_argument("--archive", required=True, help="zip 的落地路径")
    parser.add_argument("--root-name", required=True, help="包内唯一顶层目录名")
    parser.add_argument("file_names", nargs="+", metavar="文件名", help="要收进包的文件名（在发布目录下按名取）")
    return parser.parse_args()


def main() -> int:
    arguments = parse_arguments()
    try:
        create_release_zip(
            pathlib.Path(arguments.source), list(arguments.file_names), pathlib.Path(arguments.archive), arguments.root_name
        )
    except (ValueError, OSError) as error:
        print(f"打 zip 失败：{error}", file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
