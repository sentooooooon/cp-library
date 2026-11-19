#!/bin/bash
# 各ファイルを「それだけコピペしたとき」にコンパイルが通るかを確認する。
# 【必要】に書いてあるファイルは先に貼る。
set -e
cd "$(dirname "$0")/.."
CXX=${CXX:-g++}
tmp=$(mktemp -d)
trap 'rm -rf "$tmp"' EXIT
for f in lib/*/*.hpp; do
    {
        echo '#include <bits/stdc++.h>'
        echo 'using namespace std;'
        for dep in $(grep '【必要】' "$f" | grep -o '[a-z_]*\.hpp' || true); do
            cat lib/*/"$dep"
        done
        cat "$f"
        echo 'int main() {}'
    } > "$tmp/a.cpp"
    if ! "$CXX" -std=c++20 -fsyntax-only -Wall -Wextra -Werror "$tmp/a.cpp"; then
        echo "NG: $f"
        exit 1
    fi
done
echo "Standalone OK ($(ls lib/*/*.hpp | wc -l) files)"
