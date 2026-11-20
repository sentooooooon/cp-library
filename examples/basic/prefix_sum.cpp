// 【使うもの】basic/prefix_sum.hpp
// 【例題】長さ N の数列 A と Q 個の質問がある。
//        各質問 l r について A_l + A_{l+1} + ... + A_r を答えよ。（l, r は 1 始まりで、r も含む）
// 【入力例】
// 5 3
// 1 2 3 4 5
// 1 3
// 2 5
// 4 4
// 【出力例】
// 6
// 14
// 4

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    PrefixSum ps(a);
    for(int i = 0; i < q; i++)
    {
        int l, r;
        cin >> l >> r;
        // 問題の「l 番目〜r 番目（1 始まり、r も含む）」は、
        // 0 始まりだと a[l-1] 〜 a[r-1]。r を含まない書き方にすると sum(l - 1, r)
        cout << ps.sum(l - 1, r) << "\n";
    }
}
