#pragma once
#include <vector>
#include <cassert>

// セグメント木。S: 値の型, op: 結合的な二項演算, e: 単位元
// 例: SegmentTree<int, [](int a, int b) { return std::min(a, b); }, [] { return INT_MAX; }>
template <class S, auto op, auto e>
struct SegmentTree {
    int n, sz;
    std::vector<S> d;

    explicit SegmentTree(int n = 0) : SegmentTree(std::vector<S>(n, e())) {}
    explicit SegmentTree(const std::vector<S>& v) : n((int)v.size()) {
        sz = 1;
        while (sz < n) sz <<= 1;
        d.assign(2 * sz, e());
        for (int i = 0; i < n; i++) d[sz + i] = v[i];
        for (int i = sz - 1; i >= 1; i--) d[i] = op(d[2 * i], d[2 * i + 1]);
    }
    void set(int p, S x) {
        p += sz;
        d[p] = x;
        for (p >>= 1; p; p >>= 1) d[p] = op(d[2 * p], d[2 * p + 1]);
    }
    S get(int p) const { return d[p + sz]; }
    // [l, r)
    S prod(int l, int r) const {
        S sl = e(), sr = e();
        for (l += sz, r += sz; l < r; l >>= 1, r >>= 1) {
            if (l & 1) sl = op(sl, d[l++]);
            if (r & 1) sr = op(d[--r], sr);
        }
        return op(sl, sr);
    }
    S all_prod() const { return d[1]; }

    // f(prod[l, r)) が true となる最大の r（f は単調、f(e()) = true）
    template <class F>
    int max_right(int l, F f) const {
        if (l == n) return n;
        l += sz;
        S s = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!f(op(s, d[l]))) {
                while (l < sz) {
                    l = 2 * l;
                    if (f(op(s, d[l]))) s = op(s, d[l++]);
                }
                return l - sz;
            }
            s = op(s, d[l++]);
        } while ((l & -l) != l);
        return n;
    }
    // f(prod[l, r)) が true となる最小の l
    template <class F>
    int min_left(int r, F f) const {
        if (r == 0) return 0;
        r += sz;
        S s = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!f(op(d[r], s))) {
                while (r < sz) {
                    r = 2 * r + 1;
                    if (f(op(d[r], s))) s = op(d[r--], s);
                }
                return r + 1 - sz;
            }
            s = op(d[r], s);
        } while ((r & -r) != r);
        return 0;
    }
};
