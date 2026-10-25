#pragma once
#include <vector>

// BIT。0-indexed、区間は半開 [l, r)
template <class T>
struct FenwickTree {
    int n;
    std::vector<T> d;

    explicit FenwickTree(int n = 0) : n(n), d(n + 1, T()) {}
    void add(int i, T x) {
        for (i++; i <= n; i += i & -i) d[i] += x;
    }
    // [0, r)
    T sum(int r) const {
        T s = T();
        for (; r > 0; r -= r & -r) s += d[r];
        return s;
    }
    T sum(int l, int r) const { return sum(r) - sum(l); }
    // sum(0..k] >= w となる最小の k（要素が非負のとき）。なければ n
    int lower_bound(T w) const {
        if (w <= T()) return 0;
        int x = 0, k = 1;
        while (k * 2 <= n) k <<= 1;
        for (; k > 0; k >>= 1) {
            if (x + k <= n && d[x + k] < w) w -= d[x + k], x += k;
        }
        return x;
    }
};
