#pragma once
#include <vector>
#include <string>
#include <cstdint>
#include <chrono>

// mod 2^61-1 のローリングハッシュ（基数はランダム）
struct RollingHash {
    static constexpr uint64_t MOD = (1ULL << 61) - 1;
    static uint64_t mul(uint64_t a, uint64_t b) {
        __uint128_t t = (__uint128_t)a * b;
        uint64_t r = (uint64_t)(t >> 61) + (uint64_t)(t & MOD);
        return r >= MOD ? r - MOD : r;
    }
    static uint64_t base() {
        static uint64_t b = [] {
            uint64_t x = std::chrono::steady_clock::now().time_since_epoch().count();
            x ^= x << 13, x ^= x >> 7, x ^= x << 17;
            return x % (MOD - 1000) + 500;
        }();
        return b;
    }

    std::vector<uint64_t> h, pw;
    template <class Seq>
    explicit RollingHash(const Seq& s) : h(s.size() + 1, 0), pw(s.size() + 1, 1) {
        uint64_t b = base();
        for (size_t i = 0; i < s.size(); i++) {
            h[i + 1] = mul(h[i], b) + ((uint64_t)(int64_t)s[i] + 1) % MOD;
            if (h[i + 1] >= MOD) h[i + 1] -= MOD;
            pw[i + 1] = mul(pw[i], b);
        }
    }
    // [l, r) のハッシュ
    uint64_t get(int l, int r) const {
        uint64_t v = h[r] + MOD - mul(h[l], pw[r - l]);
        return v >= MOD ? v - MOD : v;
    }
};
