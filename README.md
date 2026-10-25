# cp-library

AtCoder 用 C++ ライブラリ（C++20, ヘッダオンリー）。

## 使い方

```bash
cp template/main.cpp a.cpp                 # テンプレートから開始
# a.cpp 内で #include "ds/union_find.hpp" などを書く
g++ -std=c++20 -O2 -DLOCAL -Ilib a.cpp     # ローカル実行（-DLOCAL で dbg() 有効）
python3 tools/expand.py a.cpp -o sub.cpp   # 提出用に1ファイルへ展開
```

`expand.py` は `#include "..."` を再帰展開し（同じファイルは1回だけ）、`#pragma once` を除去します。
`<...>` の標準ヘッダはそのまま残します。

## 収録

| ファイル | 内容 |
|---|---|
| `math/modint.hpp` | `StaticModInt<MOD>`、`mint998` / `mint107` |
| `math/combination.hpp` | `Combination<mint>`: `C`, `P`, `H`, `fact`, `ifact`（自動拡張） |
| `math/prime.hpp` | `factorize`, `divisors`, `Sieve`（線形篩・高速素因数分解）, `is_prime_u64`（Miller-Rabin） |
| `math/number_theory.hpp` | `pow_mod`, `ext_gcd`, `inv_mod`, `crt`, `floor_div`, `ceil_div` |
| `math/convolution.hpp` | NTT 畳み込み（mod 998244353） |
| `ds/union_find.hpp` | `UnionFind`: `merge`, `same`, `size`, `count`, `groups` |
| `ds/fenwick_tree.hpp` | `FenwickTree<T>`: `add`, `sum(l, r)`, `lower_bound` |
| `ds/segment_tree.hpp` | `SegmentTree<S, op, e>`: `set`, `get`, `prod`, `max_right`, `min_left` |
| `ds/lazy_segment_tree.hpp` | `LazySegmentTree<S, op, e, F, mapping, composition, id>` |
| `ds/sparse_table.hpp` | `SparseTable<T, op>`（冪等演算の区間クエリ O(1)） |
| `graph/dijkstra.hpp` | `dijkstra(g, s)`（到達不能は `numeric_limits<T>::max()`） |
| `graph/lca.hpp` | `LCA`: `lca`, `dist`, `ancestor`（ダブリング） |
| `graph/scc.hpp` | `scc(g)`: 強連結成分（トポロジカル順） |
| `graph/topological_sort.hpp` | `topological_sort(g)`（DAG でなければ空） |
| `string/z_algorithm.hpp` | `z_algorithm(s)` |
| `string/rolling_hash.hpp` | `RollingHash`（mod 2^61-1、ランダム基数） |

区間はすべて 0-indexed・半開区間 `[l, r)`。

### セグ木の例

```cpp
int op(int a, int b) { return min(a, b); }
int e() { return INT_MAX; }
SegmentTree<int, op, e> seg(a);
// ラムダでも可: SegmentTree<int, [](int a, int b) { return min(a, b); }, [] { return INT_MAX; }>
```

### 遅延セグ木の例（区間加算・区間和）

```cpp
struct S { ll sum, len; };
S op(S a, S b) { return {a.sum + b.sum, a.len + b.len}; }
S e() { return {0, 0}; }
S mapping(ll f, S s) { return {s.sum + f * s.len, s.len}; }
ll composition(ll f, ll g) { return f + g; }
ll id() { return 0; }
LazySegmentTree<S, op, e, ll, mapping, composition, id> seg(vector<S>(n, {0, 1}));
```

## テスト

```bash
make test   # 全ライブラリを愚直解とランダム比較（ASan/UBSan 有効）
```
