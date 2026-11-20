// 【使うもの】graph/lca.hpp
// 【例題】頂点 1 を根とする N 頂点の木がある。Q 個の質問 a b について、
//        a と b の一番近い共通の祖先と、a と b の距離（辺の本数）を答えよ。
// 【入力例】
// 5
// 1 2
// 1 3
// 2 4
// 2 5
// 3
// 4 5
// 4 3
// 1 5
// 【出力例】
// 2 2
// 1 3
// 1 2

int main() {
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    for(int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    LCA lca(g, 0);  // 頂点 1（番号 0）を根にする
    int q;
    cin >> q;
    for(int i = 0; i < q; i++)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        cout << lca.lca(a, b) + 1 << " " << lca.dist(a, b) << "\n";
    }
}
