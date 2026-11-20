// 【使うもの】math/mint.hpp
// 【例題】N 個の整数 A_1, ..., A_N がある。
//        A_1 × A_2 × ... × A_N と、2^N を、それぞれ 998244353 で割ったあまりを出力せよ。
// 【入力例】
// 3
// 1000000000000000000 999999999999 123456789
// 【出力例】
// 653372238
// 8

int main() {
    int n;
    cin >> n;

    mint prod = 1;  // mint で計算すると、勝手にあまりをとってくれる
    for(int i = 0; i < n; i++)
    {
        long long a;
        cin >> a;
        prod *= a;
    }
    cout << prod << "\n";
    cout << mint(2).pow(n) << "\n";
}
