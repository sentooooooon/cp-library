# cp-library

AtCoder 用のライブラリ（C++）。

## 使い方（3ステップ）

1. 下の表から使いたいものを選んで、ファイルを開く
2. ファイルの中身を **全部コピー**
3. 自分のコードの **`using namespace std;` と `int main()` の間** に貼る

```cpp
#include <bits/stdc++.h>
using namespace std;

// ↓↓↓ ここに貼る ↓↓↓
struct UnionFind {
    ...
};
// ↑↑↑ ここまで ↑↑↑

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    UnionFind uf(n);
    for(int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;            // 1-indexed → 0-indexed
        uf.merge(a, b);
    }
    cout << uf.count() << "\n";
    return 0;
}
```

各ファイルの先頭に **【何ができる】【使い方】** を書いてあるので、まずそこを読めばOK。

- 番号はすべて **0 始まり**、区間 `(l, r)` は **l 以上 r 未満**（r は含まない）
- 数の配列（`a` など）は **`vector<long long>`** で渡す（`vector<int>` だとエラーになる）。グラフ `g` は `vector<vector<int>>`
- 「行けない」「見つからない」は基本 **-1** で返ってくる

## 一覧

### 基本（ABC の C・D でよく使う）

| ファイル | いつ使う？ |
|---|---|
| [`basic/prefix_sum.hpp`](lib/basic/prefix_sum.hpp) | 区間の合計をたくさん聞かれる（配列は変わらない）。**2次元**（長方形の合計）もある |
| [`basic/imos.hpp`](lib/basic/imos.hpp) | 「区間に足す」をたくさんやって、最後に全体を見る |
| [`basic/binary_search.hpp`](lib/basic/binary_search.hpp) | 「〇〇の最小値/最大値を求めよ」で、〇〇 = x にできるかの判定は簡単 |
| [`basic/compress.hpp`](lib/basic/compress.hpp) | 値が大きい（10^9 とか）けど種類は少ない → 0, 1, 2, ... に置き換える |
| [`basic/run_length.hpp`](lib/basic/run_length.hpp) | 同じ文字が何個続くか（`"aaabbc"` → a3 b2 c1） |
| [`basic/lis.hpp`](lib/basic/lis.hpp) | 最長増加部分列（だんだん大きくなるように選ぶ最長の長さ） |
| [`basic/inversion.hpp`](lib/basic/inversion.hpp) | 転倒数・隣どうしの入れ替えで並べ替える最小回数 |
| [`basic/doubling.hpp`](lib/basic/doubling.hpp) | 「K 回移動したあとどこにいる？」（K ≦ 10^18） |

### グラフ

| ファイル | いつ使う？ |
|---|---|
| [`graph/grid_bfs.hpp`](lib/graph/grid_bfs.hpp) | **迷路**・マス目で最短何手 |
| [`graph/bfs.hpp`](lib/graph/bfs.hpp) | 辺の長さがない（全部 1）グラフの最短距離・行ける頂点を調べる |
| [`graph/dijkstra.hpp`](lib/graph/dijkstra.hpp) | 辺に長さがあるグラフの最短距離 |
| [`graph/warshall_floyd.hpp`](lib/graph/warshall_floyd.hpp) | 全部の2頂点の間の最短距離（N ≦ 400 くらい） |
| [`graph/kruskal.hpp`](lib/graph/kruskal.hpp) | 全部の頂点をつなぐ最小コスト（最小全域木）（**union_find.hpp も必要**） |
| [`graph/bipartite.hpp`](lib/graph/bipartite.hpp) | 2色で塗り分けられるか（二部グラフ判定） |
| [`graph/tree_diameter.hpp`](lib/graph/tree_diameter.hpp) | 木の中で一番遠い2頂点（木の直径） |
| [`graph/lca.hpp`](lib/graph/lca.hpp) | 木の2頂点の共通祖先・距離 |
| [`graph/topological_sort.hpp`](lib/graph/topological_sort.hpp) | 有向グラフの順番決め・閉路判定 |
| [`graph/scc.hpp`](lib/graph/scc.hpp) | 有向グラフで行き来できる頂点のグループ分け |

### データ構造

| ファイル | いつ使う？ |
|---|---|
| [`ds/union_find.hpp`](lib/ds/union_find.hpp) | グループ分け。「つなぐ」「同じグループ？」 |
| [`ds/weighted_union_find.hpp`](lib/ds/weighted_union_find.hpp) | 「b は a より w 大きい」の情報から差を答える・矛盾チェック |
| [`ds/bit.hpp`](lib/ds/bit.hpp) | 1点に足す ＋ 区間の合計 |
| [`ds/segtree.hpp`](lib/ds/segtree.hpp) | 1点を変更 ＋ 区間の最小値/最大値/合計 |
| [`ds/lazy_segtree.hpp`](lib/ds/lazy_segtree.hpp) | **区間に足す・区間を x にする** ＋ 区間の最小値/最大値/合計 |
| [`ds/sparse_table.hpp`](lib/ds/sparse_table.hpp) | 配列が変わらないときの区間最小値（超速い） |

### 数学

| ファイル | いつ使う？ |
|---|---|
| [`math/mint.hpp`](lib/math/mint.hpp) | 「998244353 で割ったあまりを出力」系 |
| [`math/comb.hpp`](lib/math/comb.hpp) | nCr を何回も求める（**mint.hpp も必要**） |
| [`math/prime.hpp`](lib/math/prime.hpp) | 素数判定・約数列挙・素因数分解・エラトステネスの篩 |
| [`math/number_theory.hpp`](lib/math/number_theory.hpp) | `pow_mod`、負の数の切り捨て/切り上げ、誤差なし `isqrt`、逆元、中国剰余定理 |
| [`math/base_conv.hpp`](lib/math/base_conv.hpp) | N 進数との変換（`to_base(10, 2)` → `"1010"`） |
| [`math/convolution.hpp`](lib/math/convolution.hpp) | 畳み込み・多項式の掛け算（**mint.hpp も必要**） |

### 文字列

| ファイル | いつ使う？ |
|---|---|
| [`string/z_algorithm.hpp`](lib/string/z_algorithm.hpp) | 先頭との一致の長さ・パターン検索 |
| [`string/rolling_hash.hpp`](lib/string/rolling_hash.hpp) | 部分文字列が同じかを O(1) で判定 |

## 2つ以上使うとき

全部同じ場所に続けて貼ればOK（どの組み合わせでもぶつからないことを確認済み）。
**先に貼るものがある** のはこの3つだけ:

- `comb.hpp`・`convolution.hpp` → 先に `mint.hpp`
- `kruskal.hpp` → 先に `union_find.hpp`

## テスト（ライブラリを直したとき用）

```bash
make test
```

全部のライブラリを愚直解とランダムに比べるテストと、
「そのファイルだけコピペしてもコンパイルが通るか」のチェックが走る。
