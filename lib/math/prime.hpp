#pragma once
#include <vector>
#include <cstdint>
#include <utility>
#include <algorithm>
#include <numeric>

// 試し割り素因数分解 O(√n)。{素因数, 指数} の昇順
inline std::vector<std::pair<long long, int>> factorize(long long n) {
    std::vector<std::pair<long long, int>> res;
    for (long long p = 2; p * p <= n; p++) {
        if (n % p) continue;
        int e = 0;
        while (n % p == 0) n /= p, e++;
        res.emplace_back(p, e);
    }
    if (n > 1) res.emplace_back(n, 1);
    return res;
}

// 約数列挙 O(√n)、昇順
inline std::vector<long long> divisors(long long n) {
    std::vector<long long> lo, hi;
    for (long long d = 1; d * d <= n; d++) {
        if (n % d) continue;
        lo.push_back(d);
        if (d != n / d) hi.push_back(n / d);
    }
    lo.insert(lo.end(), hi.rbegin(), hi.rend());
    return lo;
}

// 線形篩。lpf[x] = x の最小素因数。高速な素因数分解にも使える
struct Sieve {
    std::vector<int> lpf, primes;
    explicit Sieve(int n) : lpf(n + 1, 0) {
        for (int i = 2; i <= n; i++) {
            if (lpf[i] == 0) lpf[i] = i, primes.push_back(i);
            for (int p : primes) {
                if (p > lpf[i] || (long long)p * i > n) break;
                lpf[p * i] = p;
            }
        }
    }
    bool is_prime(int x) const { return x >= 2 && lpf[x] == x; }
    std::vector<std::pair<int, int>> factorize(int x) const {
        std::vector<std::pair<int, int>> res;
        while (x > 1) {
            int p = lpf[x], e = 0;
            while (x % p == 0) x /= p, e++;
            res.emplace_back(p, e);
        }
        return res;
    }
};

// 決定的 Miller-Rabin（64bit 全域）
inline bool is_prime_u64(uint64_t n) {
    if (n < 2) return false;
    for (uint64_t p : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n % p == 0) return n == p;
    }
    auto mul = [&](uint64_t a, uint64_t b) { return (uint64_t)((__uint128_t)a * b % n); };
    auto pw = [&](uint64_t a, uint64_t e) {
        uint64_t r = 1;
        for (; e; e >>= 1, a = mul(a, a)) if (e & 1) r = mul(r, a);
        return r;
    };
    uint64_t d = n - 1;
    int s = 0;
    while (d % 2 == 0) d /= 2, s++;
    for (uint64_t a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022}) {
        if (a % n == 0) continue;
        uint64_t x = pw(a, d);
        if (x == 1 || x == n - 1) continue;
        bool ok = false;
        for (int i = 1; i < s; i++) {
            x = mul(x, x);
            if (x == n - 1) { ok = true; break; }
        }
        if (!ok) return false;
    }
    return true;
}
