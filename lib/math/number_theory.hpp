#pragma once
#include <utility>
#include <tuple>
#include <cstdint>

// a^e mod m
inline long long pow_mod(long long a, long long e, long long m) {
    if (m == 1) return 0;
    long long r = 1;
    a %= m;
    if (a < 0) a += m;
    for (; e; e >>= 1, a = (__int128)a * a % m) if (e & 1) r = (__int128)r * a % m;
    return r;
}

// ax + by = g = gcd(a, b) を満たす {g, x, y}
inline std::tuple<long long, long long, long long> ext_gcd(long long a, long long b) {
    if (b == 0) return {a, 1, 0};
    auto [g, x, y] = ext_gcd(b, a % b);
    return {g, y, x - (a / b) * y};
}

// a の mod m での逆元（gcd(a, m) = 1 が必要）。存在しなければ -1
inline long long inv_mod(long long a, long long m) {
    a %= m;
    if (a < 0) a += m;
    auto [g, x, y] = ext_gcd(a, m);
    if (g != 1) return -1;
    x %= m;
    return x < 0 ? x + m : x;
}

// 中国剰余定理: x ≡ r1 (mod m1), x ≡ r2 (mod m2) → {x, lcm}。解なしなら {0, 0}
inline std::pair<long long, long long> crt(long long r1, long long m1, long long r2, long long m2) {
    r1 %= m1; if (r1 < 0) r1 += m1;
    r2 %= m2; if (r2 < 0) r2 += m2;
    auto [g, p, q] = ext_gcd(m1, m2);
    if ((r2 - r1) % g != 0) return {0, 0};
    long long m2g = m2 / g;
    long long t = (__int128)((r2 - r1) / g) * p % m2g;
    if (t < 0) t += m2g;
    long long lcm = m1 * m2g;
    long long x = (r1 + (__int128)m1 * t) % lcm;
    return {x, lcm};
}

// floor(a / b), ceil(a / b)（負数対応）
inline long long floor_div(long long a, long long b) {
    return a / b - ((a % b != 0) && ((a < 0) != (b < 0)));
}
inline long long ceil_div(long long a, long long b) {
    return a / b + ((a % b != 0) && ((a < 0) == (b < 0)));
}
