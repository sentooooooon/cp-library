// ===== 畳み込み（NTT） =====
// 【必要】先に mint.hpp を貼っておく。MOD は 998244353 のままにすること。
// 【何ができる】c[k] = Σ a[i] × b[k - i] を O(N log N) で求める。
//              「多項式の掛け算」と同じ。
// 【使い方】
//   vector<mint> a = {1, 2, 3}, b = {4, 5};
//   vector<mint> c = convolution(a, b);   // {4, 13, 22, 15}
// 【例】examples/math/convolution.cpp に、そのまま動くプログラムがある。

void ntt(vector<mint>& a, bool inverse) {
    int n = a.size();
    for(int i = 1, j = 0; i < n; i++)
    {
        int bit = n >> 1;
        while(j & bit)
        {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;
        if(i < j) swap(a[i], a[j]);
    }
    for(int len = 2; len <= n; len <<= 1)
    {
        mint w = mint(3).pow((MOD - 1) / len);  // 3 は 998244353 の原始根
        if(inverse) w = w.inv();
        for(int i = 0; i < n; i += len)
        {
            mint wk = 1;
            for(int k = 0; k < len / 2; k++)
            {
                mint u = a[i + k], v = a[i + k + len / 2] * wk;
                a[i + k] = u + v;
                a[i + k + len / 2] = u - v;
                wk *= w;
            }
        }
    }
    if(inverse)
    {
        mint n_inv = mint(n).inv();
        for(auto& x : a) x *= n_inv;
    }
}

vector<mint> convolution(vector<mint> a, vector<mint> b) {
    if(a.empty() || b.empty()) return {};
    int need = a.size() + b.size() - 1;
    int n = 1;
    while(n < need) n <<= 1;
    a.resize(n);
    b.resize(n);
    ntt(a, false);
    ntt(b, false);
    for(int i = 0; i < n; i++) a[i] *= b[i];
    ntt(a, true);
    a.resize(need);
    return a;
}
