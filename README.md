# cp-library

AtCoder 用のライブラリ（C++）。

**→ [早見表ページ](https://claude.ai/artifact/DydnXuGjHpsPLWXvyaToEA)**（自分のアカウントでだけ開ける）
キーワード（「迷路」「区間の合計」など）で探して、ボタン 1 つで **そのまま動くプログラム** をコピーできる。迷ったらまずここ。

## 使い方

### いちばん簡単なやり方

1. 下の表の「いつ使う？」を見て、問題に合うものを選ぶ
2. その行の **「例」** を開く。例題・入力例・出力例と、それを解く `main` が書いてある
3. ライブラリのファイル（表の左の列）の中身を **全部コピー** して、例の `main` の **上** に貼る → そのまま動く
4. `main` の中を、自分の問題に合わせて書き換える

できあがりはこういう形になる（迷路の最短手数 = `graph/grid_bfs.hpp` の例）:

```cpp
#include <bits/stdc++.h>
using namespace std;

// ↓↓↓ lib/graph/grid_bfs.hpp の中身をまるごと貼る ↓↓↓
vector<vector<int>> grid_bfs(const vector<string>& s, int si, int sj) {
    ...
}
// ↑↑↑ ここまで ↑↑↑

// ↓↓↓ ここから下が自分で書くところ（examples/graph/grid_bfs.cpp の main） ↓↓↓
int main() {
    int h, w;
    cin >> h >> w;
    vector<string> s(h);
    for(int i = 0; i < h; i++) cin >> s[i];

    // S と G の場所を探す
    int si = 0, sj = 0, gi = 0, gj = 0;
    ...

    vector<vector<int>> dist = grid_bfs(s, si, sj);   // ← ライブラリを呼ぶのはここだけ
    cout << dist[gi][gj] << "\n";
}
```

各ファイルの先頭にも **【何ができる】【使い方】** が書いてある。

### 気をつけること（全部のファイルで共通）

- 番号はすべて **0 始まり**。入力が 1 始まりなら、読んだあとに `a--;` する
- 区間 `(l, r)` は **l 以上 r 未満**（r は含まない）。
  問題の「l 番目から r 番目まで（r も含む、1 始まり）」は **`(l - 1, r)`** を渡す
- 数の配列（`a` など）は **`vector<long long>`** で渡す（`vector<int>` だとエラーになる）。グラフ `g` は `vector<vector<int>>`
- 「行けない」「見つからない」は基本 **-1** で返ってくる

## 一覧

### 基本（ABC の C・D でよく使う）

| ファイル | いつ使う？ | 例 |
|---|---|---|
| [`basic/prefix_sum.hpp`](lib/basic/prefix_sum.hpp) | 区間の合計をたくさん聞かれる（配列は変わらない）。**2次元**（長方形の合計）もある | [例1](examples/basic/prefix_sum.cpp) [例2](examples/basic/prefix_sum_2d.cpp) |
| [`basic/imos.hpp`](lib/basic/imos.hpp) | 「区間に足す」をたくさんやって、最後に全体を見る | [例](examples/basic/imos.cpp) |
| [`basic/binary_search.hpp`](lib/basic/binary_search.hpp) | 「〇〇の最小値/最大値を求めよ」で、〇〇 = x にできるかの判定は簡単 | [例](examples/basic/binary_search.cpp) |
| [`basic/compress.hpp`](lib/basic/compress.hpp) | 値が大きい（10^9 とか）けど種類は少ない → 0, 1, 2, ... に置き換える | [例](examples/basic/compress.cpp) |
| [`basic/run_length.hpp`](lib/basic/run_length.hpp) | 同じ文字が何個続くか（`"aaabbc"` → a3 b2 c1） | [例](examples/basic/run_length.cpp) |
| [`basic/lis.hpp`](lib/basic/lis.hpp) | 最長増加部分列（だんだん大きくなるように選ぶ最長の長さ） | [例](examples/basic/lis.cpp) |
| [`basic/inversion.hpp`](lib/basic/inversion.hpp) | 転倒数・隣どうしの入れ替えで並べ替える最小回数 | [例](examples/basic/inversion.cpp) |
| [`basic/doubling.hpp`](lib/basic/doubling.hpp) | 「K 回移動したあとどこにいる？」（K ≦ 10^18） | [例](examples/basic/doubling.cpp) |

### グラフ

| ファイル | いつ使う？ | 例 |
|---|---|---|
| [`graph/grid_bfs.hpp`](lib/graph/grid_bfs.hpp) | **迷路**・マス目で最短何手 | [例](examples/graph/grid_bfs.cpp) |
| [`graph/bfs.hpp`](lib/graph/bfs.hpp) | 辺の長さがない（全部 1）グラフの最短距離・行ける頂点を調べる | [例](examples/graph/bfs.cpp) |
| [`graph/dijkstra.hpp`](lib/graph/dijkstra.hpp) | 辺に長さがあるグラフの最短距離 | [例](examples/graph/dijkstra.cpp) |
| [`graph/warshall_floyd.hpp`](lib/graph/warshall_floyd.hpp) | 全部の2頂点の間の最短距離（N ≦ 400 くらい） | [例](examples/graph/warshall_floyd.cpp) |
| [`graph/kruskal.hpp`](lib/graph/kruskal.hpp) | 全部の頂点をつなぐ最小コスト（最小全域木）（**union_find.hpp も必要**） | [例](examples/graph/kruskal.cpp) |
| [`graph/bipartite.hpp`](lib/graph/bipartite.hpp) | 2色で塗り分けられるか（二部グラフ判定） | [例](examples/graph/bipartite.cpp) |
| [`graph/tree_diameter.hpp`](lib/graph/tree_diameter.hpp) | 木の中で一番遠い2頂点（木の直径） | [例](examples/graph/tree_diameter.cpp) |
| [`graph/lca.hpp`](lib/graph/lca.hpp) | 木の2頂点の共通祖先・距離 | [例](examples/graph/lca.cpp) |
| [`graph/topological_sort.hpp`](lib/graph/topological_sort.hpp) | 有向グラフの順番決め・閉路判定 | [例](examples/graph/topological_sort.cpp) |
| [`graph/scc.hpp`](lib/graph/scc.hpp) | 有向グラフで行き来できる頂点のグループ分け | [例](examples/graph/scc.cpp) |

### データ構造

| ファイル | いつ使う？ | 例 |
|---|---|---|
| [`ds/union_find.hpp`](lib/ds/union_find.hpp) | グループ分け。「つなぐ」「同じグループ？」 | [例](examples/ds/union_find.cpp) |
| [`ds/weighted_union_find.hpp`](lib/ds/weighted_union_find.hpp) | 「b は a より w 大きい」の情報から差を答える・矛盾チェック | [例](examples/ds/weighted_union_find.cpp) |
| [`ds/bit.hpp`](lib/ds/bit.hpp) | 1点に足す ＋ 区間の合計 | [例](examples/ds/bit.cpp) |
| [`ds/segtree.hpp`](lib/ds/segtree.hpp) | 1点を変更 ＋ 区間の最小値/最大値/合計 | [例](examples/ds/segtree.cpp) |
| [`ds/lazy_segtree.hpp`](lib/ds/lazy_segtree.hpp) | **区間に足す・区間を x にする** ＋ 区間の最小値/最大値/合計 | [例](examples/ds/lazy_segtree.cpp) |
| [`ds/sparse_table.hpp`](lib/ds/sparse_table.hpp) | 配列が変わらないときの区間最小値（超速い） | [例](examples/ds/sparse_table.cpp) |

### 数学

| ファイル | いつ使う？ | 例 |
|---|---|---|
| [`math/mint.hpp`](lib/math/mint.hpp) | 「998244353 で割ったあまりを出力」系 | [例](examples/math/mint.cpp) |
| [`math/comb.hpp`](lib/math/comb.hpp) | nCr を何回も求める（**mint.hpp も必要**） | [例](examples/math/comb.cpp) |
| [`math/prime.hpp`](lib/math/prime.hpp) | 素数判定・約数列挙・素因数分解・エラトステネスの篩 | [例](examples/math/prime.cpp) |
| [`math/number_theory.hpp`](lib/math/number_theory.hpp) | `pow_mod`、負の数の切り捨て/切り上げ、誤差なし `isqrt`、逆元、中国剰余定理 | [例](examples/math/number_theory.cpp) |
| [`math/base_conv.hpp`](lib/math/base_conv.hpp) | N 進数との変換（`to_base(10, 2)` → `"1010"`） | [例](examples/math/base_conv.cpp) |
| [`math/convolution.hpp`](lib/math/convolution.hpp) | 畳み込み・多項式の掛け算（**mint.hpp も必要**） | [例](examples/math/convolution.cpp) |

### 文字列

| ファイル | いつ使う？ | 例 |
|---|---|---|
| [`string/z_algorithm.hpp`](lib/string/z_algorithm.hpp) | 先頭との一致の長さ・パターン検索 | [例](examples/string/z_algorithm.cpp) |
| [`string/rolling_hash.hpp`](lib/string/rolling_hash.hpp) | 部分文字列が同じかを O(1) で判定 | [例](examples/string/rolling_hash.cpp) |

## 2つ以上使うとき

全部同じ場所に続けて貼ればOK（どの組み合わせでもぶつからないことを確認済み）。
**先に貼るものがある** のはこの3つだけ:

- `comb.hpp`・`convolution.hpp` → 先に `mint.hpp`
- `kruskal.hpp` → 先に `union_find.hpp`

## テスト（ライブラリを直したとき用）

```bash
make test
```

- 全部のライブラリを愚直解とランダムに比べるテスト
- 「そのファイルだけコピペしてもコンパイルが通るか」のチェック
- `examples/` の例を全部実行して、出力例と一致するかのチェック

が走る。早見表ページは `python3 tools/build_page.py 出力先.html` で作り直せる
（`lib/`・`examples/`・この README の表から自動で作る）。
