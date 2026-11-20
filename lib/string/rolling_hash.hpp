// ===== ローリングハッシュ =====
// 【何ができる】文字列の一部分どうしが等しいかを O(1) で判定する。（前計算 O(N)）
// 【使い方】
//   RollingHash rh(s);
//   rh.get(l, r)                          // s[l] 〜 s[r-1] のハッシュ値（r は含まない）
//   if(rh.get(0, 3) == rh.get(5, 8))      // s の [0,3) と [5,8) が同じ文字列か
//   ※ 別の文字列 t と比べるときは RollingHash rt(t); を作って rh.get(..) == rt.get(..)
// 【例】examples/string/rolling_hash.cpp に、そのまま動くプログラムがある。

struct RollingHash {
    static const unsigned long long M = (1ULL << 61) - 1;
    static unsigned long long base;
    vector<unsigned long long> h, pw;

    static unsigned long long mul(unsigned long long a, unsigned long long b) {
        __uint128_t t = (__uint128_t)a * b;
        unsigned long long r = (t >> 61) + (t & M);
        if(r >= M) r -= M;
        return r;
    }

    RollingHash(const string& s) {
        int n = s.size();
        h.assign(n + 1, 0);
        pw.assign(n + 1, 1);
        for(int i = 0; i < n; i++)
        {
            h[i + 1] = (mul(h[i], base) + (unsigned char)s[i]) % M;
            pw[i + 1] = mul(pw[i], base);
        }
    }

    unsigned long long get(int l, int r) {
        unsigned long long v = h[r] + M - mul(h[l], pw[r - l]);
        if(v >= M) v -= M;
        return v;
    }
};
// 基数はランダムに決める（狙い撃ちされないように）
unsigned long long RollingHash::base = mt19937_64(chrono::steady_clock::now().time_since_epoch().count())() % (RollingHash::M - 2) + 2;
