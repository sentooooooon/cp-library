#pragma once
#include <vector>
#include "modint.hpp"

// NTT による畳み込み（mod 998244353、原始根 3）
namespace ntt_internal {
template <class mint>
void ntt(std::vector<mint>& a, bool invert) {
    int n = (int)a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) std::swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        mint w = mint(3).pow((mint::mod() - 1) / len);
        if (invert) w = w.inv();
        int half = len / 2;
        std::vector<mint> ws(half);
        ws[0] = 1;
        for (int k = 1; k < half; k++) ws[k] = ws[k - 1] * w;
        for (int i = 0; i < n; i += len) {
            for (int k = 0; k < half; k++) {
                mint u = a[i + k], v = a[i + k + half] * ws[k];
                a[i + k] = u + v;
                a[i + k + half] = u - v;
            }
        }
    }
    if (invert) {
        mint ninv = mint(n).inv();
        for (auto& x : a) x *= ninv;
    }
}
}  // namespace ntt_internal

inline std::vector<mint998> convolution(std::vector<mint998> a, std::vector<mint998> b) {
    if (a.empty() || b.empty()) return {};
    int need = (int)(a.size() + b.size() - 1);
    if (std::min(a.size(), b.size()) <= 40) {
        std::vector<mint998> c(need);
        for (size_t i = 0; i < a.size(); i++)
            for (size_t j = 0; j < b.size(); j++) c[i + j] += a[i] * b[j];
        return c;
    }
    int n = 1;
    while (n < need) n <<= 1;
    a.resize(n);
    b.resize(n);
    ntt_internal::ntt(a, false);
    ntt_internal::ntt(b, false);
    for (int i = 0; i < n; i++) a[i] *= b[i];
    ntt_internal::ntt(a, true);
    a.resize(need);
    return a;
}
