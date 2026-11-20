# examples/ の例を全部「ライブラリを貼った完成形」にしてコンパイル・実行し、出力例と一致するか確認する。
# tools/build_page.py からも使う。
import os
import re
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
HEADER = "#include <bits/stdc++.h>\nusing namespace std;\n\n"


def read(path):
    with open(os.path.join(ROOT, path), encoding="utf-8") as f:
        return f.read()


def lib_with_deps(lib):
    """lib（例: 'graph/kruskal.hpp'）と、【必要】に書いてあるファイルを貼る順に並べる"""
    order = []

    def visit(path):
        if path in order:
            return
        for line in read("lib/" + path).splitlines():
            if "【必要】" in line:
                for name in re.findall(r"[a-z_]+\.hpp", line):
                    visit(find_lib(name))
        order.append(path)

    visit(lib)
    return order


def find_lib(name):
    for d in sorted(os.listdir(os.path.join(ROOT, "lib"))):
        if os.path.exists(os.path.join(ROOT, "lib", d, name)):
            return d + "/" + name
    raise FileNotFoundError(name)


def parse_example(path):
    """例のファイルを {lib, problem, input, output, code} に分ける"""
    text = read(path)
    sections = {}
    cur = None
    code_start = 0
    lines = text.splitlines()
    for i, line in enumerate(lines):
        if not line.startswith("//"):
            code_start = i
            break
        body = line[3:] if line.startswith("// ") else line[2:]
        m = re.match(r"【(.+?)】(.*)", body)
        if m:
            cur = m.group(1)
            sections[cur] = [m.group(2)] if m.group(2).strip() else []
        else:
            sections[cur].append(body.strip() if cur == "例題" else body)
    return {
        "path": path,
        "lib": sections["使うもの"][0].strip(),
        "problem": "\n".join(sections["例題"]),
        "input": "\n".join(sections["入力例"]) + "\n",
        "output": "\n".join(sections["出力例"]) + "\n",
        "source": text,
        "code": "\n".join(lines[code_start:]).strip() + "\n",
    }


def all_examples():
    res = []
    for d in sorted(os.listdir(os.path.join(ROOT, "examples"))):
        for f in sorted(os.listdir(os.path.join(ROOT, "examples", d))):
            if f.endswith(".cpp"):
                res.append(parse_example("examples/" + d + "/" + f))
    return res


def library_text(lib):
    return "\n".join(read("lib/" + p) for p in lib_with_deps(lib))


def full_program(ex):
    """そのまま提出できる形: #include + ライブラリ（必要なものも） + 例の main"""
    return HEADER + library_text(ex["lib"]) + "\n" + ex["source"]


def main():
    cxx = os.environ.get("CXX", "g++")
    examples = all_examples()
    with tempfile.TemporaryDirectory() as tmp:
        for ex in examples:
            src = os.path.join(tmp, "a.cpp")
            exe = os.path.join(tmp, "a.out")
            with open(src, "w", encoding="utf-8") as f:
                f.write(full_program(ex))
            r = subprocess.run([cxx, "-std=c++20", "-O2", "-Wall", "-Wextra", "-Werror", "-o", exe, src],
                               capture_output=True, text=True)
            if r.returncode != 0:
                print("NG (compile):", ex["path"])
                print(r.stderr)
                sys.exit(1)
            r = subprocess.run([exe], input=ex["input"], capture_output=True, text=True, timeout=10)
            if r.stdout.split() != ex["output"].split() or r.stdout.strip().splitlines() != ex["output"].strip().splitlines():
                print("NG (output):", ex["path"])
                print("expected:\n" + ex["output"] + "got:\n" + r.stdout)
                sys.exit(1)
    # どのライブラリにも例があるか
    has = {ex["lib"] for ex in examples}
    for d in sorted(os.listdir(os.path.join(ROOT, "lib"))):
        for f in sorted(os.listdir(os.path.join(ROOT, "lib", d))):
            if d + "/" + f not in has:
                print("NG (no example):", d + "/" + f)
                sys.exit(1)
    print(f"Examples OK ({len(examples)} programs)")


if __name__ == "__main__":
    main()
