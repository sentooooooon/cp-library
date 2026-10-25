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
番号はすべて **0 始まり**、区間 `(l, r)` は **l 以上 r 未満**（r は含まない）。

## 一覧

### データ構造

| ファイル | いつ使う？ |
|---|---|
| [`ds/union_find.hpp`](lib/ds/union_find.hpp) | グループ分け。「つなぐ」「同じグループ？」 |
| [`ds/bit.hpp`](lib/ds/bit.hpp) | 1点に足す ＋ 区間の合計。転倒数 |
| [`ds/segtree.hpp`](lib/ds/segtree.hpp) | 1点を変更 ＋ 区間の最小値/最大値/合計 |
| [`ds/lazy_segtree.hpp`](lib/ds/lazy_segtree.hpp) | **区間に足す** ＋ 区間の最小値/最大値/合計 |
| [`ds/sparse_table.hpp`](lib/ds/sparse_table.hpp) | 配列が変わらないときの区間最小値（超速い） |

### 数学

| ファイル | いつ使う？ |
|---|---|
| [`math/mint.hpp`](lib/math/mint.hpp) | 「998244353 で割ったあまりを出力」系 |
| [`math/comb.hpp`](lib/math/comb.hpp) | nCr を何回も求める（**mint.hpp も必要**） |
| [`math/prime.hpp`](lib/math/prime.hpp) | 素数判定・約数列挙・素因数分解・エラトステネスの篩 |
| [`math/number_theory.hpp`](lib/math/number_theory.hpp) | `pow_mod`、負の数の切り捨て/切り上げ、逆元、中国剰余定理 |
| [`math/convolution.hpp`](lib/math/convolution.hpp) | 畳み込み・多項式の掛け算（**mint.hpp も必要**） |

### グラフ

| ファイル | いつ使う？ |
|---|---|
| [`graph/dijkstra.hpp`](lib/graph/dijkstra.hpp) | 重み付きグラフの最短距離 |
| [`graph/lca.hpp`](lib/graph/lca.hpp) | 木の2頂点の共通祖先・距離 |
| [`graph/topological_sort.hpp`](lib/graph/topological_sort.hpp) | 有向グラフの順番決め・閉路判定 |
| [`graph/scc.hpp`](lib/graph/scc.hpp) | 有向グラフで行き来できる頂点のグループ分け |

### 文字列

| ファイル | いつ使う？ |
|---|---|
| [`string/z_algorithm.hpp`](lib/string/z_algorithm.hpp) | 先頭との一致の長さ・パターン検索 |
| [`string/rolling_hash.hpp`](lib/string/rolling_hash.hpp) | 部分文字列が同じかを O(1) で判定 |

## 2つ以上使うとき

全部同じ場所に続けて貼ればOK（どの組み合わせでもぶつからないことを確認済み）。
`comb.hpp` と `convolution.hpp` は **先に `mint.hpp` を貼る**。

## テスト（ライブラリを直したとき用）

```bash
make test
```
