// 各ライブラリを愚直解とランダム比較するテスト（make test で実行）
#include <bits/stdc++.h>
using namespace std;
#include "math/mint.hpp"
#include "math/comb.hpp"
#include "math/prime.hpp"
#include "math/number_theory.hpp"
#include "math/convolution.hpp"
#include "ds/union_find.hpp"
#include "ds/bit.hpp"
#include "ds/segtree.hpp"
#include "ds/lazy_segtree.hpp"
#include "ds/sparse_table.hpp"
#include "graph/dijkstra.hpp"
#include "graph/lca.hpp"
#include "graph/scc.hpp"
#include "graph/topological_sort.hpp"
#include "string/z_algorithm.hpp"
#include "string/rolling_hash.hpp"
#include "basic/compress.hpp"
#include "basic/run_length.hpp"
#include "basic/prefix_sum.hpp"
#include "basic/imos.hpp"
#include "basic/binary_search.hpp"
#include "basic/lis.hpp"
#include "basic/inversion.hpp"
#include "basic/doubling.hpp"
#include "math/base_conv.hpp"
#include "ds/weighted_union_find.hpp"
#include "graph/bfs.hpp"
#include "graph/grid_bfs.hpp"
#include "graph/warshall_floyd.hpp"
#include "graph/kruskal.hpp"
#include "graph/tree_diameter.hpp"
#include "graph/bipartite.hpp"
using ll = long long;

mt19937_64 rng(12345);
ll rnd(ll l, ll r) { return uniform_int_distribution<ll>(l, r)(rng); }
#define CHECK(c) do { if (!(c)) { fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #c); exit(1); } } while (0)

void test_mint() {
    for (int t = 0; t < 1000; t++) {
        ll a = rnd(-1e18, 1e18), b = rnd(1, MOD - 1);
        mint x(a), y(b);
        ll am = ((a % MOD) + MOD) % MOD;
        CHECK(x.x == am);
        CHECK((x * y).x == (ll)((__int128)am * b % MOD));
        CHECK(x / y * y == x);
        CHECK(x - y + y == x);
        CHECK(-x + x == mint(0));
    }
    CHECK(mint(2).pow(10).x == 1024);
}

void test_comb() {
    Comb C(100);
    vector<vector<ll>> pas(60, vector<ll>(60, 0));
    for (int n = 0; n < 60; n++) {
        pas[n][0] = 1;
        for (int r = 1; r <= n; r++) pas[n][r] = (pas[n - 1][r - 1] + pas[n - 1][r]) % MOD;
    }
    for (int n = 0; n < 60; n++)
        for (int r = -1; r <= n + 1; r++) CHECK(C.C(n, r).x == ((r < 0 || r > n) ? 0 : pas[n][r]));
    CHECK(C.fact[10].x == 3628800);
    CHECK(C.P(5, 2).x == 20);
    CHECK(C.H(3, 2).x == 6);
}

void test_prime() {
    Sieve sv(10000);
    for (int x = 0; x <= 10000; x++) {
        bool p = x >= 2;
        for (int d = 2; d * d <= x; d++) if (x % d == 0) p = false;
        CHECK(sv.is_prime[x] == p);
        CHECK(is_prime(x) == p);
        if (x >= 1) {
            auto f1 = factorize(x);
            auto f2 = sv.factorize(x);
            ll prod = 1;
            CHECK(f1.size() == f2.size());
            for (size_t i = 0; i < f1.size(); i++) {
                CHECK(f1[i].first == f2[i].first && f1[i].second == f2[i].second);
                for (int k = 0; k < f1[i].second; k++) prod *= f1[i].first;
            }
            CHECK(prod == x);
            vector<ll> bf;
            for (int d = 1; d <= x; d++) if (x % d == 0) bf.push_back(d);
            CHECK(divisors(x) == bf);
        }
    }
    CHECK((int)sv.primes.size() == 1229);
}

void test_number_theory() {
    for (int t = 0; t < 2000; t++) {
        ll a = rnd(-1000, 1000), b = rnd(-1000, 1000);
        if (b == 0) continue;
        CHECK(floor_div(a, b) == (ll)floor((double)a / b));
        CHECK(ceil_div(a, b) == (ll)ceil((double)a / b));
    }
    for (int t = 0; t < 2000; t++) {
        ll m1 = rnd(1, 50), m2 = rnd(1, 50), r1 = rnd(0, m1 - 1), r2 = rnd(0, m2 - 1);
        auto [x, l] = crt(r1, m1, r2, m2);
        ll bf = -1, L = lcm(m1, m2);
        for (ll y = 0; y < L; y++) if (y % m1 == r1 && y % m2 == r2) { bf = y; break; }
        if (bf == -1) CHECK(x == -1 && l == -1);
        else CHECK(x == bf && l == L);
        ll a = rnd(1, 1000), m = rnd(1, 1000);
        ll iv = inv_mod(a, m);
        if (gcd(a, m) == 1) CHECK(a * iv % m == 1 % m);
        else CHECK(iv == -1);
        ll e = rnd(0, 20), bf2 = 1 % m;
        for (int i = 0; i < e; i++) bf2 = bf2 * a % m;
        CHECK(pow_mod(a, e, m) == bf2);
    }
}

void test_convolution() {
    for (int t = 0; t < 50; t++) {
        int n = rnd(1, 300), m = rnd(1, 300);
        vector<mint> a(n), b(m);
        for (auto& x : a) x = rnd(0, MOD - 1);
        for (auto& x : b) x = rnd(0, MOD - 1);
        vector<mint> c(n + m - 1);
        for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) c[i + j] += a[i] * b[j];
        CHECK(convolution(a, b) == c);
    }
}

void test_union_find() {
    for (int t = 0; t < 100; t++) {
        int n = rnd(1, 50);
        UnionFind uf(n);
        vector<int> col(n);
        iota(col.begin(), col.end(), 0);
        for (int q = 0; q < 100; q++) {
            int a = rnd(0, n - 1), b = rnd(0, n - 1);
            CHECK(uf.merge(a, b) == (col[a] != col[b]));
            int ca = col[a], cb = col[b];
            for (auto& c : col) if (c == cb) c = ca;
            int x = rnd(0, n - 1), y = rnd(0, n - 1);
            CHECK(uf.same(x, y) == (col[x] == col[y]));
            CHECK(uf.size(x) == count(col.begin(), col.end(), col[x]));
            CHECK(uf.count() == (int)set<int>(col.begin(), col.end()).size());
        }
        CHECK((int)uf.groups().size() == uf.count());
    }
}

void test_bit() {
    for (int t = 0; t < 100; t++) {
        int n = rnd(1, 60);
        BIT bit(n);
        vector<ll> a(n, 0);
        for (int q = 0; q < 200; q++) {
            int i = rnd(0, n - 1);
            ll x = rnd(-10, 10);
            bit.add(i, x), a[i] += x;
            int l = rnd(0, n), r = rnd(0, n);
            if (l > r) swap(l, r);
            CHECK(bit.sum(l, r) == accumulate(a.begin() + l, a.begin() + r, 0LL));
        }
    }
}

void test_segtree() {
    for (int t = 0; t < 100; t++) {
        int n = rnd(1, 40);
        vector<ll> a(n);
        for (auto& x : a) x = rnd(-100, 100);
        SegTree seg(a);
        for (int q = 0; q < 200; q++) {
            int p = rnd(0, n - 1);
            a[p] = rnd(-100, 100);
            seg.set(p, a[p]);
            CHECK(seg.get(p) == a[p]);
            int l = rnd(0, n), r = rnd(0, n);
            if (l > r) swap(l, r);
            ll mn = LLONG_MAX;
            for (int i = l; i < r; i++) mn = min(mn, a[i]);
            CHECK(seg.query(l, r) == mn);
        }
    }
}

void test_lazy_segtree() {
    for (int t = 0; t < 100; t++) {
        int n = rnd(1, 40);
        vector<ll> a(n);
        for (auto& x : a) x = rnd(-100, 100);
        LazySegTree seg(a);
        for (int q = 0; q < 200; q++) {
            int l = rnd(0, n), r = rnd(0, n);
            if (l > r) swap(l, r);
            if (rnd(0, 1)) {
                ll x = rnd(-10, 10);
                seg.add(l, r, x);
                for (int i = l; i < r; i++) a[i] += x;
            }
            l = rnd(0, n - 1), r = rnd(l + 1, n);
            CHECK(seg.get_sum(l, r) == accumulate(a.begin() + l, a.begin() + r, 0LL));
            CHECK(seg.get_min(l, r) == *min_element(a.begin() + l, a.begin() + r));
            CHECK(seg.get_max(l, r) == *max_element(a.begin() + l, a.begin() + r));
        }
    }
}

void test_sparse_table() {
    for (int t = 0; t < 100; t++) {
        int n = rnd(1, 60);
        vector<ll> a(n);
        for (auto& x : a) x = rnd(-1000, 1000);
        SparseTable st(a);
        for (int l = 0; l < n; l++)
            for (int r = l + 1; r <= n; r++) CHECK(st.query(l, r) == *min_element(a.begin() + l, a.begin() + r));
    }
}

void test_dijkstra() {
    for (int t = 0; t < 100; t++) {
        int n = rnd(1, 30), m = rnd(0, 100);
        vector<vector<pair<int, ll>>> g(n);
        const ll INF = LLONG_MAX;
        vector<vector<ll>> d(n, vector<ll>(n, INF));
        for (int i = 0; i < n; i++) d[i][i] = 0;
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1);
            ll c = rnd(0, 100);
            g[u].push_back({v, c});
            d[u][v] = min(d[u][v], c);
        }
        for (int k = 0; k < n; k++) for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
            if (d[i][k] != INF && d[k][j] != INF) d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
        int s = rnd(0, n - 1);
        auto dist = dijkstra(g, s);
        for (int v = 0; v < n; v++) CHECK(dist[v] == (d[s][v] == INF ? -1 : d[s][v]));
    }
}

void test_lca() {
    for (int t = 0; t < 100; t++) {
        int n = rnd(1, 60);
        vector<vector<int>> g(n);
        vector<int> par(n, -1);
        for (int i = 1; i < n; i++) {
            par[i] = rnd(0, i - 1);
            g[i].push_back(par[i]);
            g[par[i]].push_back(i);
        }
        LCA lca(g, 0);
        auto anc = [&](int v) { vector<int> r; while (v != -1) r.push_back(v), v = par[v]; return r; };
        for (int q = 0; q < 100; q++) {
            int a = rnd(0, n - 1), b = rnd(0, n - 1);
            auto A = anc(a), B = anc(b);
            set<int> sb(B.begin(), B.end());
            int exp = -1;
            for (int v : A) if (sb.count(v)) { exp = v; break; }
            CHECK(lca.lca(a, b) == exp);
            int k = rnd(0, n);
            CHECK(lca.ancestor(a, k) == (k < (int)A.size() ? A[k] : -1));
            CHECK(lca.dist(a, b) == lca.depth[a] + lca.depth[b] - 2 * lca.depth[exp]);
        }
    }
}

void test_scc_topo() {
    for (int t = 0; t < 200; t++) {
        int n = rnd(1, 25), m = rnd(0, 60);
        vector<vector<int>> g(n);
        vector<vector<bool>> reach(n, vector<bool>(n, false));
        for (int i = 0; i < n; i++) reach[i][i] = true;
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1);
            g[u].push_back(v);
            reach[u][v] = true;
        }
        for (int k = 0; k < n; k++) for (int i = 0; i < n; i++) for (int j = 0; j < n; j++)
            if (reach[i][k] && reach[k][j]) reach[i][j] = true;
        auto comps = scc(g);
        vector<int> id(n, -1);
        for (int c = 0; c < (int)comps.size(); c++) for (int v : comps[c]) { CHECK(id[v] == -1); id[v] = c; }
        for (int i = 0; i < n; i++) {
            CHECK(id[i] != -1);
            for (int j = 0; j < n; j++) {
                CHECK((id[i] == id[j]) == (reach[i][j] && reach[j][i]));
                if (reach[i][j]) CHECK(id[i] <= id[j]);
            }
        }
        bool dag = (int)comps.size() == n;
        for (int i = 0; i < n; i++) for (int v : g[i]) if (v == i) dag = false;
        auto ts = topological_sort(g);
        if (!dag) CHECK(ts.empty());
        else {
            CHECK((int)ts.size() == n);
            vector<int> pos(n);
            for (int i = 0; i < n; i++) pos[ts[i]] = i;
            for (int u = 0; u < n; u++) for (int v : g[u]) CHECK(pos[u] < pos[v]);
        }
    }
}

void test_string() {
    CHECK(z_algorithm("aabaa") == vector<int>({5, 1, 0, 2, 1}));
    for (int t = 0; t < 300; t++) {
        int n = rnd(0, 40);
        string s;
        for (int i = 0; i < n; i++) s += (char)('a' + rnd(0, 2));
        auto z = z_algorithm(s);
        for (int i = 0; i < n; i++) {
            int k = 0;
            while (i + k < n && s[k] == s[i + k]) k++;
            CHECK(z[i] == k);
        }
        RollingHash rh(s);
        for (int q = 0; q < 50 && n > 0; q++) {
            int l1 = rnd(0, n), l2 = rnd(0, n);
            int len = rnd(0, n - max(l1, l2));
            CHECK((rh.get(l1, l1 + len) == rh.get(l2, l2 + len)) == (s.substr(l1, len) == s.substr(l2, len)));
        }
    }
}

void test_lazy_segtree_assign() {
    for (int t = 0; t < 200; t++) {
        int n = rnd(1, 40);
        vector<ll> a(n);
        for (auto& x : a) x = rnd(-100, 100);
        LazySegTree seg(a);
        for (int q = 0; q < 200; q++) {
            int l = rnd(0, n), r = rnd(0, n);
            if (l > r) swap(l, r);
            ll x = rnd(-50, 50);
            int op = rnd(0, 2);
            if (op == 0) { seg.add(l, r, x); for (int i = l; i < r; i++) a[i] += x; }
            if (op == 1) { seg.assign(l, r, x); for (int i = l; i < r; i++) a[i] = x; }
            l = rnd(0, n - 1), r = rnd(l + 1, n);
            CHECK(seg.get_sum(l, r) == accumulate(a.begin() + l, a.begin() + r, 0LL));
            CHECK(seg.get_min(l, r) == *min_element(a.begin() + l, a.begin() + r));
            CHECK(seg.get_max(l, r) == *max_element(a.begin() + l, a.begin() + r));
            int i = rnd(0, n - 1);
            CHECK(seg.get(i) == a[i]);
        }
    }
}

void test_isqrt() {
    for (ll n = 0; n <= 100000; n++) {
        ll r = isqrt(n);
        CHECK(r * r <= n && (r + 1) * (r + 1) > n);
    }
    for (int t = 0; t < 100000; t++) {
        ll n = rnd(0, LLONG_MAX);
        if (t % 3 == 0) { ll k = rnd(1, 3037000499LL); n = k * k - rnd(0, 1); }
        ll r = isqrt(n);
        CHECK((__int128)r * r <= n && (__int128)(r + 1) * (r + 1) > n);
    }
    CHECK(isqrt(LLONG_MAX) == 3037000499LL);
}

void test_compress() {
    for (int t = 0; t < 200; t++) {
        int n = rnd(0, 30);
        vector<ll> a(n);
        for (auto& x : a) x = rnd(-1e9, 1e9) / rnd(1, 1e8);
        Compress cp(a);
        auto b = cp.ids(a);
        set<ll> st(a.begin(), a.end());
        CHECK(cp.size() == (int)st.size());
        for (int i = 0; i < n; i++) {
            CHECK(cp.val(b[i]) == a[i]);
            CHECK(b[i] == (int)count_if(st.begin(), st.end(), [&](ll v) { return v < a[i]; }));
        }
    }
}

void test_run_length() {
    CHECK(run_length("aaabbc") == (vector<pair<char, int>>{{'a', 3}, {'b', 2}, {'c', 1}}));
    CHECK(run_length("").empty());
    for (int t = 0; t < 200; t++) {
        int n = rnd(0, 30);
        vector<ll> a(n);
        for (auto& x : a) x = rnd(0, 2);
        auto rl = run_length(a);
        vector<ll> back;
        for (int i = 0; i < (int)rl.size(); i++) {
            CHECK(rl[i].second >= 1);
            if (i > 0) CHECK(rl[i].first != rl[i - 1].first);
            for (int k = 0; k < rl[i].second; k++) back.push_back(rl[i].first);
        }
        CHECK(back == a);
    }
}

void test_prefix_sum_imos() {
    for (int t = 0; t < 100; t++) {
        int n = rnd(0, 30);
        vector<ll> a(n);
        for (auto& x : a) x = rnd(-1e9, 1e9);
        PrefixSum ps(a);
        for (int l = 0; l <= n; l++)
            for (int r = l; r <= n; r++) CHECK(ps.sum(l, r) == accumulate(a.begin() + l, a.begin() + r, 0LL));
        Imos im(n);
        vector<ll> b(n, 0);
        for (int q = 0; q < 50 && n > 0; q++) {
            int l = rnd(0, n), r = rnd(0, n);
            if (l > r) swap(l, r);
            ll x = rnd(-100, 100);
            im.add(l, r, x);
            for (int i = l; i < r; i++) b[i] += x;
        }
        CHECK(im.build() == b);
    }
    for (int t = 0; t < 100; t++) {
        int h = rnd(1, 12), w = rnd(1, 12);
        vector<vector<ll>> g(h, vector<ll>(w));
        for (auto& row : g) for (auto& x : row) x = rnd(-100, 100);
        PrefixSum2D ps(g);
        for (int q = 0; q < 100; q++) {
            int i1 = rnd(0, h), i2 = rnd(0, h), j1 = rnd(0, w), j2 = rnd(0, w);
            if (i1 > i2) swap(i1, i2);
            if (j1 > j2) swap(j1, j2);
            ll s = 0;
            for (int i = i1; i < i2; i++) for (int j = j1; j < j2; j++) s += g[i][j];
            CHECK(ps.sum(i1, j1, i2, j2) == s);
        }
    }
    PrefixSum2D empty2d(vector<vector<ll>>{});
    CHECK(empty2d.sum(0, 0, 0, 0) == 0);
}

void test_bin_search() {
    CHECK(bin_search(1000, 0, [&](ll x) { return x * x >= 1000; }) == 32);
    CHECK(bin_search(0, 1000, [&](ll x) { return x * x <= 1000; }) == 31);
    for (int t = 0; t < 2000; t++) {
        ll lo = rnd(-1e18, 1e18), hi = rnd(-1e18, 1e18);
        if (lo > hi) swap(lo, hi);
        if (hi - lo < 2) continue;
        ll b = rnd(lo + 1, hi);  // x >= b なら OK
        CHECK(bin_search(hi, lo, [&](ll x) { return x >= b; }) == b);
        CHECK(bin_search(lo, hi, [&](ll x) { return x < b; }) == b - 1);
    }
}

void test_lis() {
    for (int t = 0; t < 300; t++) {
        int n = rnd(0, 12);
        vector<ll> a(n);
        for (auto& x : a) x = rnd(0, 5);
        int best_s = 0, best_w = 0;
        for (int mask = 0; mask < (1 << n); mask++) {
            vector<ll> s;
            for (int i = 0; i < n; i++) if (mask >> i & 1) s.push_back(a[i]);
            bool inc = true, ndec = true;
            for (int i = 1; i < (int)s.size(); i++) {
                if (!(s[i - 1] < s[i])) inc = false;
                if (!(s[i - 1] <= s[i])) ndec = false;
            }
            if (inc) best_s = max(best_s, (int)s.size());
            if (ndec) best_w = max(best_w, (int)s.size());
        }
        CHECK(lis(a) == best_s);
        CHECK(lis(a, false) == best_w);
    }
}

void test_inversion() {
    for (int t = 0; t < 300; t++) {
        int n = rnd(0, 60);
        vector<ll> a(n);
        for (auto& x : a) x = rnd(-5, 5);
        auto orig = a;
        ll bf = 0;
        for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) if (a[i] > a[j]) bf++;
        CHECK(inversion_count(a) == bf);
        CHECK(a == orig);
    }
}

void test_doubling() {
    for (int t = 0; t < 100; t++) {
        int n = rnd(1, 30);
        vector<int> nxt(n);
        for (auto& x : nxt) x = rnd(0, n - 1);
        Doubling db(nxt);
        for (int q = 0; q < 50; q++) {
            int x = rnd(0, n - 1);
            ll k = rnd(0, 200);
            int y = x;
            for (ll i = 0; i < k; i++) y = nxt[y];
            CHECK(db.jump(x, k) == y);
        }
        // 大きい k: 周期を使って答え合わせ
        int x = rnd(0, n - 1);
        ll k = rnd(1e17, 1e18);
        vector<int> seen(n, -1), path;
        int y = x;
        while (seen[y] == -1) { seen[y] = path.size(); path.push_back(y); y = nxt[y]; }
        ll mu = seen[y], lam = (ll)path.size() - mu;
        int expect = path[mu + (k - mu) % lam];
        CHECK(db.jump(x, k) == expect);
    }
}

void test_base_conv() {
    CHECK(to_base(10, 2) == "1010");
    CHECK(to_base(0, 7) == "0");
    CHECK(to_base(255, 16) == "FF");
    CHECK(from_base("ff", 16) == 255);
    CHECK(from_base("1010", 2) == 10);
    for (int t = 0; t < 5000; t++) {
        ll n = rnd(0, LLONG_MAX);
        int b = rnd(2, 36);
        string s = to_base(n, b);
        CHECK(from_base(s, b) == n);
        if (b == 10) CHECK(s == to_string(n));
    }
}

void test_weighted_union_find() {
    for (int t = 0; t < 300; t++) {
        int n = rnd(1, 20);
        // 正解の値を決めておき、正しい情報と（すでにつながっている2点には）嘘の情報を混ぜる
        vector<ll> val(n);
        for (auto& x : val) x = rnd(-100, 100);
        WeightedUnionFind uf(n);
        UnionFind ref(n);
        for (int q = 0; q < 60; q++) {
            int a = rnd(0, n - 1), b = rnd(0, n - 1);
            bool lie = ref.same(a, b) && rnd(0, 2) == 0;
            ll w = val[b] - val[a] + (lie ? (rnd(0, 1) ? 1 : -1) * rnd(1, 5) : 0);
            CHECK(uf.merge(a, b, w) == !lie);
            if (!lie) ref.merge(a, b);
            int x = rnd(0, n - 1), y = rnd(0, n - 1);
            CHECK(uf.same(x, y) == ref.same(x, y));
            if (uf.same(x, y)) CHECK(uf.diff(x, y) == val[y] - val[x]);
            CHECK(uf.size(x) == ref.size(x));
            CHECK(uf.count() == ref.count());
        }
    }
}

void test_bfs_family() {
    for (int t = 0; t < 200; t++) {
        int n = rnd(1, 25), m = rnd(0, 60);
        vector<vector<int>> g(n);
        vector<vector<pair<int, ll>>> wg(n), ug(n);
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1);
            g[u].push_back(v);
            wg[u].push_back({v, 1});
            ll c = rnd(0, 100);
            ug[u].push_back({v, c});
        }
        auto D = warshall_floyd(ug);
        for (int s = 0; s < n; s++) {
            auto dw = dijkstra(wg, s);
            CHECK(bfs(g, s) == vector<int>(dw.begin(), dw.end()));
            CHECK(D[s] == dijkstra(ug, s));
        }
    }
}

void test_grid_bfs() {
    for (int t = 0; t < 200; t++) {
        int h = rnd(1, 10), w = rnd(1, 10);
        vector<string> s(h, string(w, '.'));
        for (auto& row : s) for (auto& c : row) if (rnd(0, 3) == 0) c = '#';
        int si = rnd(0, h - 1), sj = rnd(0, w - 1);
        s[si][sj] = '.';
        // 普通のグラフにして bfs と比べる
        vector<vector<int>> g(h * w);
        for (int i = 0; i < h; i++) for (int j = 0; j < w; j++) {
            if (s[i][j] == '#') continue;
            if (i + 1 < h && s[i + 1][j] != '#') g[i * w + j].push_back((i + 1) * w + j), g[(i + 1) * w + j].push_back(i * w + j);
            if (j + 1 < w && s[i][j + 1] != '#') g[i * w + j].push_back(i * w + j + 1), g[i * w + j + 1].push_back(i * w + j);
        }
        auto d1 = grid_bfs(s, si, sj);
        auto d2 = bfs(g, si * w + sj);
        for (int i = 0; i < h; i++) for (int j = 0; j < w; j++) CHECK(d1[i][j] == d2[i * w + j]);
    }
}

void test_kruskal() {
    for (int t = 0; t < 300; t++) {
        int n = rnd(1, 7), m = rnd(0, 10);
        vector<tuple<int, int, ll>> edges;
        for (int i = 0; i < m; i++) edges.push_back({(int)rnd(0, n - 1), (int)rnd(0, n - 1), rnd(-10, 10)});
        // 全部の辺の選び方を試す
        ll best = LLONG_MAX;
        for (int mask = 0; mask < (1 << m); mask++) {
            UnionFind uf(n);
            ll c = 0;
            for (int i = 0; i < m; i++) if (mask >> i & 1) { uf.merge(get<0>(edges[i]), get<1>(edges[i])); c += get<2>(edges[i]); }
            if (uf.count() == 1 && __builtin_popcount(mask) == n - 1) best = min(best, c);
        }
        ll got = kruskal(n, edges);
        if (best == LLONG_MAX) CHECK(got == -1);
        else CHECK(got == best);
    }
}

void test_tree_diameter() {
    for (int t = 0; t < 200; t++) {
        int n = rnd(1, 40);
        vector<vector<int>> g(n);
        for (int i = 1; i < n; i++) {
            int p = rnd(0, i - 1);
            g[i].push_back(p), g[p].push_back(i);
        }
        int best = 0;
        for (int s = 0; s < n; s++) { auto d = bfs(g, s); best = max(best, *max_element(d.begin(), d.end())); }
        auto [d, a, b] = tree_diameter(g);
        CHECK(d == best);
        CHECK(bfs(g, a)[b] == d);
    }
}

void test_bipartite() {
    for (int t = 0; t < 300; t++) {
        int n = rnd(1, 12), m = rnd(0, 15);
        vector<vector<int>> g(n);
        vector<pair<int, int>> es;
        for (int i = 0; i < m; i++) {
            int u = rnd(0, n - 1), v = rnd(0, n - 1);
            g[u].push_back(v), g[v].push_back(u);
            es.push_back({u, v});
        }
        bool exist = false;
        for (int mask = 0; mask < (1 << n) && !exist; mask++) {
            bool ok = true;
            for (auto [u, v] : es) if ((mask >> u & 1) == (mask >> v & 1)) ok = false;
            exist = ok;
        }
        auto col = bipartite(g);
        if (!exist) CHECK(col.empty());
        else {
            CHECK((int)col.size() == n);
            for (auto [u, v] : es) CHECK(col[u] != col[v]);
            for (int v = 0; v < n; v++) CHECK(col[v] == 0 || col[v] == 1);
        }
    }
}

int main() {
    test_mint();
    test_comb();
    test_prime();
    test_number_theory();
    test_convolution();
    test_union_find();
    test_bit();
    test_segtree();
    test_lazy_segtree();
    test_sparse_table();
    test_dijkstra();
    test_lca();
    test_scc_topo();
    test_string();
    test_lazy_segtree_assign();
    test_isqrt();
    test_compress();
    test_run_length();
    test_prefix_sum_imos();
    test_bin_search();
    test_lis();
    test_inversion();
    test_doubling();
    test_base_conv();
    test_weighted_union_find();
    test_bfs_family();
    test_grid_bfs();
    test_kruskal();
    test_tree_diameter();
    test_bipartite();
    puts("All tests passed.");
}
