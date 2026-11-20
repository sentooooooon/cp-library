// 【使うもの】ds/weighted_union_find.hpp
// 【例題】N 人が一直線に並んでいる。M 個の情報「人 r_i は人 l_i より d_i だけ右にいる」がある。
//        全部の情報が同時に正しくなりうるなら Yes、矛盾しているなら No と出力せよ。
// 【入力例】
// 3 3
// 1 2 1
// 2 3 1
// 1 3 2
// 【出力例】
// Yes

int main() {
    int n, m;
    cin >> n >> m;

    WeightedUnionFind uf(n);
    bool ok = true;
    for(int i = 0; i < m; i++)
    {
        int l, r;
        long long d;
        cin >> l >> r >> d;
        l--; r--;
        // 「(r の位置) - (l の位置) = d」を追加。矛盾したら false が返ってくる
        if(!uf.merge(l, r, d)) ok = false;
    }
    cout << (ok ? "Yes" : "No") << "\n";
}
