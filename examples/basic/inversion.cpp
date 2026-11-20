// 【使うもの】basic/inversion.hpp
// 【例題】数列 A を、隣どうしの入れ替えだけで小さい順に並べたい。最小で何回入れ替えればいいか。
// 【入力例】
// 5
// 3 1 5 4 2
// 【出力例】
// 5

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    cout << inversion_count(a) << "\n";
}
