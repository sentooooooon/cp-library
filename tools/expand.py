#!/usr/bin/env python3
"""ライブラリの #include "..." を再帰的に展開し、提出用の単一ファイルを出力する。

使い方:
    python3 tools/expand.py main.cpp            # 標準出力へ
    python3 tools/expand.py main.cpp -o sub.cpp # ファイルへ
#pragma once は同一ファイルの二重展開防止として扱い、出力からは除去する。
"""
import argparse
import re
import sys
from pathlib import Path

LIB_DIR = Path(__file__).resolve().parent.parent / "lib"
INCLUDE_RE = re.compile(r'^\s*#\s*include\s*"([^"]+)"\s*$')
PRAGMA_ONCE_RE = re.compile(r"^\s*#\s*pragma\s+once\s*$")


def resolve(name: str, cur_dir: Path) -> Path:
    for base in (cur_dir, LIB_DIR):
        p = (base / name).resolve()
        if p.is_file():
            return p
    raise FileNotFoundError(f"include not found: {name} (from {cur_dir})")


def expand(path: Path, seen: set, out: list) -> None:
    path = path.resolve()
    if path in seen:
        return
    seen.add(path)
    for line in path.read_text(encoding="utf-8").splitlines():
        if PRAGMA_ONCE_RE.match(line):
            continue
        m = INCLUDE_RE.match(line)
        if m:
            expand(resolve(m.group(1), path.parent), seen, out)
        else:
            out.append(line)


def main() -> None:
    ap = argparse.ArgumentParser()
    ap.add_argument("src")
    ap.add_argument("-o", "--output")
    args = ap.parse_args()
    out: list = []
    expand(Path(args.src), set(), out)
    text = "\n".join(out) + "\n"
    if args.output:
        Path(args.output).write_text(text, encoding="utf-8")
    else:
        sys.stdout.write(text)


if __name__ == "__main__":
    main()
