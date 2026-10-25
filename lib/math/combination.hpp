#pragma once
#include <vector>
#include <cassert>

// 階乗・逆階乗の前計算による nCr, nPr, nHr
template <class mint>
struct Combination {
    std::vector<mint> f, fi;

    explicit Combination(int n = 0) { extend(n); }

    void extend(int n) {
        int m = (int)f.size();
        if (n < m) return;
        f.resize(n + 1);
        fi.resize(n + 1);
        if (m == 0) { f[0] = 1; m = 1; }
        for (int i = m; i <= n; i++) f[i] = f[i - 1] * i;
        fi[n] = f[n].inv();
        for (int i = n; i > m; i--) fi[i - 1] = fi[i] * i;
        if (m == 1) fi[0] = 1;
    }
    mint fact(int n) { extend(n); return f[n]; }
    mint ifact(int n) { extend(n); return fi[n]; }
    mint C(int n, int r) {
        if (r < 0 || n < r || n < 0) return 0;
        extend(n);
        return f[n] * fi[r] * fi[n - r];
    }
    mint P(int n, int r) {
        if (r < 0 || n < r || n < 0) return 0;
        extend(n);
        return f[n] * fi[n - r];
    }
    // 重複組合せ: n 種類から重複を許して r 個
    mint H(int n, int r) {
        if (n == 0 && r == 0) return 1;
        return C(n + r - 1, r);
    }
};
