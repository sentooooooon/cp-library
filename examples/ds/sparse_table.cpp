// 【使うもの】ds/sparse_table.hpp
// 【例題】長さ N の数列 A と Q 個の質問がある。各質問 l r について A_l 〜 A_r の最小値を答えよ。
//        （l, r は 1 始まりで、r も含む）
// 【入力例】
// 6 3
// 4 2 7 1 8 3
// 1 3
// 3 6
// 5 6
// 【出力例】
// 2
// 1
// 3

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    SparseTable st(a);
    for(int i = 0; i < q; i++)
    {
        int l, r;
        cin >> l >> r;
        cout << st.query(l - 1, r) << "\n";
    }
}
