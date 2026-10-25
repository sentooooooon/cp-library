#pragma once
#include <cstdint>
#include <iostream>

// 静的modint。MOD は素数を想定（inv はフェルマーの小定理）
template <uint32_t MOD>
struct StaticModInt {
    using mint = StaticModInt;
    uint32_t v;

    constexpr StaticModInt() : v(0) {}
    template <class T>
    constexpr StaticModInt(T x) {
        int64_t y = (int64_t)(x % (int64_t)MOD);
        if (y < 0) y += MOD;
        v = (uint32_t)y;
    }
    static constexpr uint32_t mod() { return MOD; }
    constexpr uint32_t val() const { return v; }

    constexpr mint& operator+=(const mint& r) { v += r.v; if (v >= MOD) v -= MOD; return *this; }
    constexpr mint& operator-=(const mint& r) { v += MOD - r.v; if (v >= MOD) v -= MOD; return *this; }
    constexpr mint& operator*=(const mint& r) { v = (uint64_t)v * r.v % MOD; return *this; }
    constexpr mint& operator/=(const mint& r) { return *this *= r.inv(); }
    constexpr mint operator-() const { return mint() - *this; }
    friend constexpr mint operator+(mint a, const mint& b) { return a += b; }
    friend constexpr mint operator-(mint a, const mint& b) { return a -= b; }
    friend constexpr mint operator*(mint a, const mint& b) { return a *= b; }
    friend constexpr mint operator/(mint a, const mint& b) { return a /= b; }
    friend constexpr bool operator==(const mint& a, const mint& b) { return a.v == b.v; }
    friend constexpr bool operator!=(const mint& a, const mint& b) { return a.v != b.v; }

    constexpr mint pow(uint64_t e) const {
        mint r = 1, b = *this;
        for (; e; e >>= 1, b *= b) if (e & 1) r *= b;
        return r;
    }
    constexpr mint inv() const { return pow(MOD - 2); }

    friend std::ostream& operator<<(std::ostream& os, const mint& m) { return os << m.v; }
    friend std::istream& operator>>(std::istream& is, mint& m) { int64_t x; is >> x; m = mint(x); return is; }
};

using mint998 = StaticModInt<998244353>;
using mint107 = StaticModInt<1000000007>;
