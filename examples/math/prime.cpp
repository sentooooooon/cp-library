// 【使うもの】math/prime.hpp
// 【例題】整数 N について、次の 4 つを出力せよ。
//        ・N が素数なら Yes、違うなら No
//        ・N の約数（小さい順）
//        ・N の素因数分解（「素数^何乗」を並べる）
//        ・N 以下の素数の個数
// 【入力例】
// 60
// 【出力例】
// No
// 1 2 3 4 5 6 10 12 15 20 30 60
// 2^2 3^1 5^1
// 17

int main() {
    long long n;
    cin >> n;

    cout << (is_prime(n) ? "Yes" : "No") << "\n";

    vector<long long> d = divisors(n);
    for(int i = 0; i < (int)d.size(); i++)
    {
        cout << d[i] << (i + 1 < (int)d.size() ? " " : "\n");
    }

    vector<pair<long long, int>> f = factorize(n);
    for(int i = 0; i < (int)f.size(); i++)
    {
        auto [p, e] = f[i];
        cout << p << "^" << e << (i + 1 < (int)f.size() ? " " : "\n");
    }

    Sieve sv(n);  // n 以下の素数を全部求める（n ≦ 10^7 くらいまで）
    cout << sv.primes.size() << "\n";
}
