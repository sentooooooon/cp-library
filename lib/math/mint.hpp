// ===== mint（あまりを自動でとる整数） =====
// 【何ができる】「答えを 998244353 で割ったあまりを出力せよ」系の問題で、
//              足し算・引き算・掛け算・割り算を、あまりを気にせず普通に書ける。
// 【使い方】
//   mint a = 5, b = 3;
//   mint c = a * b + 1;     // 自動であまりがとられる
//   mint d = a / b;         // 割り算もできる（MOD が素数のとき）
//   mint e = a.pow(100);    // 5 の 100 乗
//   cout << c << "\n";      // そのまま出力できる
//   cout << c.x << "\n";    // 中身（0 〜 MOD-1）は .x
// 【注意】1000000007 の問題なら下の MOD を書き換える。

const long long MOD = 998244353;

struct mint {
    long long x;

    mint(long long v = 0) {
        x = v % MOD;
        if(x < 0) x += MOD;
    }

    mint& operator+=(mint b) { x += b.x; if(x >= MOD) x -= MOD; return *this; }
    mint& operator-=(mint b) { x -= b.x; if(x < 0) x += MOD; return *this; }
    mint& operator*=(mint b) { x = x * b.x % MOD; return *this; }
    mint& operator/=(mint b) { return *this *= b.inv(); }
    mint operator+(mint b) const { return mint(*this) += b; }
    mint operator-(mint b) const { return mint(*this) -= b; }
    mint operator*(mint b) const { return mint(*this) *= b; }
    mint operator/(mint b) const { return mint(*this) /= b; }
    mint operator-() const { return mint(0) - *this; }
    bool operator==(mint b) const { return x == b.x; }
    bool operator!=(mint b) const { return x != b.x; }

    // 累乗 O(log n)
    mint pow(long long n) const {
        mint res = 1, a = *this;
        while(n > 0)
        {
            if(n & 1) res *= a;
            a *= a;
            n >>= 1;
        }
        return res;
    }

    // 逆数（割り算用）
    mint inv() const { return pow(MOD - 2); }
};

ostream& operator<<(ostream& os, mint a) { return os << a.x; }
istream& operator>>(istream& is, mint& a) { long long v; is >> v; a = mint(v); return is; }
