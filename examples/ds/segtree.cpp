// 【使うもの】ds/segtree.hpp
// 【例題】長さ N の数列 A がある。Q 個の命令を順に処理せよ。
//        「1 i x」: A_i を x に変える
//        「2 l r」: A_l 〜 A_r の最小値を出力（l, r は 1 始まりで、r も含む）
// 【入力例】
// 5 4
// 5 3 8 6 1
// 2 1 3
// 1 2 10
// 2 1 3
// 2 3 5
// 【出力例】
// 3
// 5
// 1

int main() {
    int n, q;
    cin >> n >> q;
    vector<long long> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    SegTree seg(a);  // 最小値のセグ木（最大値や合計にしたいときは ★ を書き換える）
    for(int k = 0; k < q; k++)
    {
        int type;
        cin >> type;
        if(type == 1)
        {
            int i;
            long long x;
            cin >> i >> x;
            seg.set(i - 1, x);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << seg.query(l - 1, r) << "\n";
        }
    }
}
