// 【使うもの】basic/prefix_sum.hpp
// 【例題】H 行 W 列のマスに数が書いてある。Q 個の質問がある。
//        各質問 a b c d について、左上が a 行 b 列、右下が c 行 d 列の長方形の合計を答えよ。（1 始まり）
// 【入力例】
// 3 4 2
// 1 2 3 4
// 5 6 7 8
// 9 10 11 12
// 1 1 2 2
// 2 2 3 4
// 【出力例】
// 14
// 54

int main() {
    int h, w, q;
    cin >> h >> w >> q;
    vector<vector<long long>> g(h, vector<long long>(w));
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++) cin >> g[i][j];
    }

    PrefixSum2D ps(g);
    for(int i = 0; i < q; i++)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        // 行 a-1 〜 c-1、列 b-1 〜 d-1（0 始まり）→ 終わりは含まないので sum(a-1, b-1, c, d)
        cout << ps.sum(a - 1, b - 1, c, d) << "\n";
    }
}
