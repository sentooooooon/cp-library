// ===== 整数の便利関数 =====
// 【使い方】
//   pow_mod(2, 10, 1000)      // 2^10 % 1000 = 24。O(log)
//   floor_div(-7, 2)          // -4（負の数でも正しく切り捨て）
//   ceil_div(7, 2)            // 4（切り上げ）
//   isqrt(10)                 // 3（√10 の切り捨て。sqrt() と違って誤差でずれない）
//   inv_mod(3, 7)             // 5（3 × 5 ≡ 1 mod 7）。逆元がなければ -1
//   ext_gcd(a, b, x, y)       // ax + by = gcd(a, b) となる x, y を求め、gcd を返す
//   crt(r1, m1, r2, m2)       // x ≡ r1 (mod m1) かつ x ≡ r2 (mod m2) となる x を返す
//                             // 戻り値 {x, lcm(m1, m2)}。解がなければ {-1, -1}

long long pow_mod(long long a, long long n, long long m) {
    long long res = 1 % m;
    a %= m;
    if(a < 0) a += m;
    while(n > 0)
    {
        if(n & 1) res = (__int128)res * a % m;
        a = (__int128)a * a % m;
        n >>= 1;
    }
    return res;
}

long long floor_div(long long a, long long b) {
    long long q = a / b;
    if(a % b != 0 && ((a < 0) != (b < 0))) q--;
    return q;
}

long long ceil_div(long long a, long long b) {
    long long q = a / b;
    if(a % b != 0 && ((a < 0) == (b < 0))) q++;
    return q;
}

// n は 0 以上
long long isqrt(long long n) {
    long long r = sqrtl((long double)n);
    while(r > 0 && (__int128)r * r > n) r--;
    while((__int128)(r + 1) * (r + 1) <= n) r++;
    return r;
}

long long ext_gcd(long long a, long long b, long long& x, long long& y) {
    if(b == 0)
    {
        x = 1;
        y = 0;
        return a;
    }
    long long g = ext_gcd(b, a % b, y, x);
    y -= (a / b) * x;
    return g;
}

long long inv_mod(long long a, long long m) {
    a %= m;
    if(a < 0) a += m;
    long long x, y;
    if(ext_gcd(a, m, x, y) != 1) return -1;
    x %= m;
    if(x < 0) x += m;
    return x;
}

pair<long long, long long> crt(long long r1, long long m1, long long r2, long long m2) {
    r1 %= m1; if(r1 < 0) r1 += m1;
    r2 %= m2; if(r2 < 0) r2 += m2;
    long long p, q;
    long long g = ext_gcd(m1, m2, p, q);
    if((r2 - r1) % g != 0) return {-1, -1};
    long long m2g = m2 / g;
    long long t = (__int128)((r2 - r1) / g) * p % m2g;
    if(t < 0) t += m2g;
    long long l = m1 * m2g;
    long long x = ((__int128)m1 * t + r1) % l;
    return {x, l};
}
