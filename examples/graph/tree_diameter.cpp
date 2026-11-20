// 【使うもの】graph/tree_diameter.hpp
// 【例題】N 頂点の木がある。i 本目の辺は頂点 a_i と b_i をつなぐ。
//        一番遠い 2 頂点の間には何本の辺があるか。
// 【入力例】
// 6
// 1 2
// 2 3
// 2 4
// 4 5
// 5 6
// 【出力例】
// 4

int main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for(int i = 0; i < n - 1; i++)  // 木の辺は N-1 本
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    auto [d, a, b] = tree_diameter(g);
    cout << d << "\n";  // 両端の頂点は a + 1 と b + 1
}
