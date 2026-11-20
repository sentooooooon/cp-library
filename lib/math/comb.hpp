// ===== 二項係数 nCr =====
// 【必要】先に mint.hpp を貼っておく。
// 【何ができる】nCr, nPr, nHr を O(1) で求める（最初に O(N) の前計算）。
// 【使い方】
//   Comb comb(200000);         // n の最大値を渡す
//   mint a = comb.C(5, 2);     // 5C2 = 10
//   mint b = comb.P(5, 2);     // 5P2 = 20
//   mint c = comb.H(3, 2);     // 3H2 = 6（重複組合せ）
//   mint d = comb.fact[10];    // 10!
// 【例】examples/math/comb.cpp に、そのまま動くプログラムがある。

struct Comb {
    vector<mint> fact, ifact;

    Comb(int n) {
        fact.resize(n + 1);
        ifact.resize(n + 1);
        fact[0] = 1;
        for(int i = 1; i <= n; i++)
        {
            fact[i] = fact[i - 1] * i;
        }
        ifact[n] = fact[n].inv();
        for(int i = n; i >= 1; i--)
        {
            ifact[i - 1] = ifact[i] * i;
        }
    }

    mint C(int n, int r) {
        if(r < 0 || r > n || n < 0) return 0;
        return fact[n] * ifact[r] * ifact[n - r];
    }

    mint P(int n, int r) {
        if(r < 0 || r > n || n < 0) return 0;
        return fact[n] * ifact[n - r];
    }

    // n 種類から重複を許して r 個選ぶ
    mint H(int n, int r) {
        if(n == 0 && r == 0) return 1;
        return C(n + r - 1, r);
    }
};
