# 早見表ページ（HTML 1 枚）を作る。lib/・examples/・README.md の「いつ使う？」から自動で作るので、
# ライブラリや例を直したら、これを実行し直すだけでページも新しくなる。
#   python3 tools/build_page.py 出力先.html
import json
import os
import re
import sys

sys.path.insert(0, os.path.join(os.path.dirname(os.path.dirname(os.path.abspath(__file__))), "tests"))
from examples import ROOT, HEADER, all_examples, lib_with_deps, library_text, read  # noqa: E402

# 出番の目安（ABC の何問目あたりで出やすいか）と、検索用のキーワード
META = {
    "basic/prefix_sum.hpp": ("C〜D", "累積和 区間の合計 部分和 2次元 長方形"),
    "basic/imos.hpp": ("C〜D", "いもす 区間に足す 差分 イベント 何人いるか"),
    "basic/binary_search.hpp": ("C〜E", "二分探索 最小値 最大値 答えで二分探索 lower_bound upper_bound"),
    "basic/compress.hpp": ("D〜E", "座標圧縮 大きい値 番号に置き換える"),
    "basic/run_length.hpp": ("B〜C", "ランレングス 連続 同じ文字が続く 文字列"),
    "basic/lis.hpp": ("E〜F", "最長増加部分列 LIS 増加 部分列"),
    "basic/inversion.hpp": ("E〜F", "転倒数 入れ替え バブルソート 交換回数 並べ替え"),
    "basic/doubling.hpp": ("D〜E", "ダブリング テレポート K回 移動 10^18 くり返し"),
    "graph/grid_bfs.hpp": ("C〜D", "迷路 マス目 グリッド 最短 手数 BFS 壁"),
    "graph/bfs.hpp": ("C〜D", "BFS 幅優先探索 最短距離 連結 行ける グラフ"),
    "graph/dijkstra.hpp": ("D〜E", "ダイクストラ 最短距離 最短経路 重み 道路 コスト グラフ"),
    "graph/warshall_floyd.hpp": ("D〜E", "ワーシャルフロイド 全点対 最短距離 グラフ"),
    "graph/kruskal.hpp": ("E", "クラスカル 最小全域木 MST つなぐ 最小コスト グラフ"),
    "graph/bipartite.hpp": ("D〜E", "二部グラフ 塗り分け 2色 白黒 グラフ"),
    "graph/tree_diameter.hpp": ("E", "木の直径 一番遠い 木"),
    "graph/lca.hpp": ("E〜F", "LCA 共通祖先 木 距離"),
    "graph/topological_sort.hpp": ("D〜E", "トポロジカルソート 順番 閉路 DAG 有向グラフ"),
    "graph/scc.hpp": ("F〜G", "強連結成分 SCC 有向グラフ 行き来"),
    "ds/union_find.hpp": ("C〜D", "UnionFind ユニオンファインド グループ 連結 つなぐ 同じグループ"),
    "ds/weighted_union_find.hpp": ("D〜E", "重み付き 差 矛盾 ポテンシャル グループ"),
    "ds/bit.hpp": ("E〜F", "BIT フェニック木 区間の合計 1点に足す 転倒数"),
    "ds/segtree.hpp": ("E〜F", "セグ木 セグメント木 区間の最小値 区間の最大値 1点更新"),
    "ds/lazy_segtree.hpp": ("F〜G", "遅延セグ木 区間に足す 区間を変える 区間代入 区間の合計 区間の最小値"),
    "ds/sparse_table.hpp": ("E〜F", "スパーステーブル 区間の最小値 RMQ"),
    "math/mint.hpp": ("D〜E", "mod 998244353 1000000007 あまり modint"),
    "math/comb.hpp": ("D〜E", "nCr 組合せ 二項係数 経路数 階乗 何通り 998244353"),
    "math/prime.hpp": ("C〜D", "素数 約数 素因数分解 エラトステネス 篩"),
    "math/number_theory.hpp": ("C〜E", "切り捨て 切り上げ 平方根 sqrt 累乗 pow 逆元 中国剰余定理 gcd"),
    "math/base_conv.hpp": ("B〜C", "N進数 2進数 8進数 16進数 進法"),
    "math/convolution.hpp": ("G", "畳み込み NTT 多項式 FFT 998244353"),
    "string/z_algorithm.hpp": ("E〜F", "Z-algorithm 文字列 検索 一致 パターン 文字列"),
    "string/rolling_hash.hpp": ("E〜F", "ローリングハッシュ 文字列 一致 部分文字列 比較"),
}


def readme_table():
    """README の表から [(カテゴリ名, [(path, いつ使う), ...]), ...] を取り出す"""
    cats = []
    for line in read("README.md").splitlines():
        m = re.match(r"### (.+)", line)
        if m:
            cats.append((re.sub(r"（.*?）", "", m.group(1)).strip(), []))
            continue
        m = re.match(r"\| \[`(.+?)`\]\(lib/.+?\) \| (.+?) \|", line)
        if m and cats:
            when = m.group(2).replace("**", "").replace("`", "")
            cats[-1][1].append((m.group(1), when))
    return [c for c in cats if c[1]]


def header_comment(path):
    """hpp の先頭のコメント（タイトル行と【例】の行以外）"""
    lines = read("lib/" + path).splitlines()
    title = re.sub(r"=+", "", lines[0][2:]).strip()
    body = []
    for line in lines[1:]:
        if not line.startswith("//"):
            break
        if "【例】" in line:
            continue
        body.append(line[3:] if line.startswith("// ") else line[2:])
    return title, "\n".join(body).rstrip()


def main():
    out = sys.argv[1] if len(sys.argv) > 1 else "page.html"
    examples = all_examples()
    cats = []
    items = {}
    for name, rows in readme_table():
        ids = []
        for path, when in rows:
            iid = path.split("/")[1][:-4].replace("_", "-")
            title, usage = header_comment(path)
            level, keywords = META[path]
            items[iid] = {
                "id": iid,
                "path": path,
                "title": title,
                "when": when,
                "level": level,
                "keywords": keywords,
                "deps": [p for p in lib_with_deps(path) if p != path],
                "usage": usage,
                "lib": library_text(path),
                "examples": [
                    {"problem": ex["problem"], "input": ex["input"], "output": ex["output"],
                     "source": ex["source"]}
                    for ex in examples if ex["lib"] == path
                ],
            }
            ids.append(iid)
        cats.append({"name": name, "ids": ids})
    missing = set(META) - {it["path"] for it in items.values()}
    if missing:
        sys.exit("README の表にないファイル: " + ", ".join(sorted(missing)))
    data = {"header": HEADER, "categories": cats, "items": items}
    payload = json.dumps(data, ensure_ascii=False).replace("</", "<\\/")
    template = read("tools/page_template.html")
    with open(out, "w", encoding="utf-8") as f:
        f.write(template.replace("/*__DATA__*/", payload))
    print(f"wrote {out} ({len(items)} items, {os.path.getsize(out) // 1024} KB)")


if __name__ == "__main__":
    main()
