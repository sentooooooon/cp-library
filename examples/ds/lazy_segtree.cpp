// 【使うもの】ds/lazy_segtree.hpp
// 【例題】長さ N の数列 A（最初は全部 0）がある。Q 個の命令を順に処理せよ。（l, r は 1 始まりで、r も含む）
//        「1 l r x」: A_l 〜 A_r に x を足す
//        「2 l r x」: A_l 〜 A_r を全部 x にする
//        「3 l r」  : A_l 〜 A_r の合計と最小値を出力
// 【入力例】
// 5 4
// 1 1 3 2
// 3 1 5
// 2 2 4 7
// 3 1 4
// 【出力例】
// 6 0
// 23 2

int main() {
    int n, q;
    cin >> n >> q;

    LazySegTree seg(n);
    for(int k = 0; k < q; k++)
    {
        int type, l, r;
        cin >> type >> l >> r;
        l--;  // 0 始まりにすると a[l-1] 〜 a[r-1] → (l-1, r) を渡す
        if(type == 1)
        {
            long long x;
            cin >> x;
            seg.add(l, r, x);
        }
        else if(type == 2)
        {
            long long x;
            cin >> x;
            seg.assign(l, r, x);
        }
        else
        {
            cout << seg.get_sum(l, r) << " " << seg.get_min(l, r) << "\n";
        }
    }
}
