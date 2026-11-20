// 【使うもの】graph/dijkstra.hpp
// 【例題】N 頂点 M 辺の無向グラフがある。i 本目の辺は頂点 a_i と b_i をつなぎ、長さは c_i。
//        頂点 1 から頂点 N までの最短距離を答えよ。行けないなら -1。
// 【入力例】
// 4 5
// 1 2 3
// 1 3 1
// 3 2 1
// 2 4 5
// 3 4 10
// 【出力例】
// 7

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, long long>>> g(n);
    for(int i = 0; i < m; i++)
    {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        a--; b--;
        g[a].push_back({b, c});
        g[b].push_back({a, c});  // 無向なので逆向きも
    }

    vector<long long> dist = dijkstra(g, 0);
    cout << dist[n - 1] << "\n";  // 1 → 3 → 2 → 4 で 1 + 1 + 5 = 7
}
