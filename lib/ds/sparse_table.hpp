#pragma once
#include <vector>

// Sparse Table。冪等な演算（min, max, gcd 等）の区間クエリを O(1)
template <class T, auto op>
struct SparseTable {
    std::vector<std::vector<T>> t;
    std::vector<int> lg;

    SparseTable() = default;
    explicit SparseTable(const std::vector<T>& v) {
        int n = (int)v.size();
        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        t.assign(lg[n] + 1, v);
        for (int k = 1; k <= lg[n]; k++)
            for (int i = 0; i + (1 << k) <= n; i++)
                t[k][i] = op(t[k - 1][i], t[k - 1][i + (1 << (k - 1))]);
    }
    // [l, r)、l < r
    T query(int l, int r) const {
        int k = lg[r - l];
        return op(t[k][l], t[k][r - (1 << k)]);
    }
};
