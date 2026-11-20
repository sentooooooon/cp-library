// 【使うもの】graph/bfs.hpp
// 【例題】N 頂点 M 辺の無向グラフがある。i 本目の辺は頂点 a_i と b_i をつなぐ。
//        頂点 1 から各頂点まで、最短で何本の辺を通れば行けるか。行けないなら -1。
// 【入力例】
// 5 4
// 1 2
// 2 3
// 1 4
// 4 3
// 【出力例】
// 0
// 1
// 2
// 1
// -1

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for(int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;  // 1 始まり → 0 始まり
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> dist = bfs(g, 0);  // 頂点 1 は番号 0
    for(int v = 0; v < n; v++)
    {
        cout << dist[v] << "\n";
    }
}
