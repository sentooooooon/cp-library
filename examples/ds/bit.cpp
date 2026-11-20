// 【使うもの】ds/bit.hpp
// 【例題】長さ N の数列 A（最初は全部 0）がある。Q 個の命令を順に処理せよ。
//        「1 i x」: A_i に x を足す
//        「2 l r」: A_l + ... + A_r を出力（l, r は 1 始まりで、r も含む）
// 【入力例】
// 5 4
// 1 2 5
// 1 4 3
// 2 1 3
// 2 2 4
// 【出力例】
// 5
// 8

int main() {
    int n, q;
    cin >> n >> q;

    BIT bit(n);
    for(int k = 0; k < q; k++)
    {
        int type;
        cin >> type;
        if(type == 1)
        {
            int i;
            long long x;
            cin >> i >> x;
            bit.add(i - 1, x);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << bit.sum(l - 1, r) << "\n";  // 0 始まりで a[l-1] 〜 a[r-1]
        }
    }
}
