#pragma once
#include <vector>

// 遅延セグメント木
// S: 値, op(S,S), e(): Sの単位元
// F: 作用, mapping(F,S): 作用を適用, composition(f,g): f∘g（g を先に適用）, id(): 恒等作用
template <class S, auto op, auto e, class F, auto mapping, auto composition, auto id>
struct LazySegmentTree {
    int n, sz, lg;
    std::vector<S> d;
    std::vector<F> lz;

    explicit LazySegmentTree(int n = 0) : LazySegmentTree(std::vector<S>(n, e())) {}
    explicit LazySegmentTree(const std::vector<S>& v) : n((int)v.size()) {
        lg = 0;
        while ((1 << lg) < n) lg++;
        sz = 1 << lg;
        d.assign(2 * sz, e());
        lz.assign(sz, id());
        for (int i = 0; i < n; i++) d[sz + i] = v[i];
        for (int i = sz - 1; i >= 1; i--) update(i);
    }
    void set(int p, S x) {
        p += sz;
        for (int i = lg; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= lg; i++) update(p >> i);
    }
    S get(int p) {
        p += sz;
        for (int i = lg; i >= 1; i--) push(p >> i);
        return d[p];
    }
    // [l, r)
    S prod(int l, int r) {
        if (l == r) return e();
        l += sz, r += sz;
        for (int i = lg; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        S sl = e(), sr = e();
        for (; l < r; l >>= 1, r >>= 1) {
            if (l & 1) sl = op(sl, d[l++]);
            if (r & 1) sr = op(d[--r], sr);
        }
        return op(sl, sr);
    }
    S all_prod() const { return d[1]; }
    void apply(int p, F f) {
        p += sz;
        for (int i = lg; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= lg; i++) update(p >> i);
    }
    // [l, r) に f を作用
    void apply(int l, int r, F f) {
        if (l == r) return;
        l += sz, r += sz;
        for (int i = lg; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }
        {
            int l2 = l, r2 = r;
            for (; l < r; l >>= 1, r >>= 1) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
            }
            l = l2, r = r2;
        }
        for (int i = 1; i <= lg; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

private:
    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < sz) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};
