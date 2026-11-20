// 【使うもの】basic/compress.hpp
// 【例題】数列 A の各要素を「A の中で小さい方から何番目の値か」（0 始まり、同じ値は同じ番号）に置き換えて出力せよ。
// 【入力例】
// 5
// 100 5 100 30 7
// 【出力例】
// 3 0 3 2 1

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    Compress cp(a);
    vector<int> b = cp.ids(a);

    for(int i = 0; i < n; i++)
    {
        cout << b[i] << (i + 1 < n ? " " : "\n");
    }
}
