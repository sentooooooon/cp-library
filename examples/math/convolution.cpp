// 【使うもの】math/convolution.hpp
// 【例題】多項式 f(x) = A_0 + A_1 x + ... + A_{N-1} x^{N-1} と g(x) = B_0 + ... + B_{M-1} x^{M-1} がある。
//        f(x) × g(x) の係数を、x^0 から順に 998244353 で割ったあまりで出力せよ。
// 【入力例】
// 3 2
// 1 2 3
// 4 5
// 【出力例】
// 4 13 22 15

int main() {
    int n, m;
    cin >> n >> m;
    vector<mint> a(n), b(m);
    for(int i = 0; i < n; i++) cin >> a[i];
    for(int i = 0; i < m; i++) cin >> b[i];

    vector<mint> c = convolution(a, b);
    for(int i = 0; i < (int)c.size(); i++)
    {
        cout << c[i] << (i + 1 < (int)c.size() ? " " : "\n");
    }
}
