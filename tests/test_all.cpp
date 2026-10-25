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
    puts("All tests passed.");
}
