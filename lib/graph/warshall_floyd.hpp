// ===== ワーシャルフロイド法（全部の2頂点の間の最短距離） =====
// 【何ができる】全ての2頂点の間の最短距離をまとめて O(N^3) で求める。N ≦ 400 くらいまで。
// 【使い方】（グラフの作り方は dijkstra.hpp と同じ）
//   vector<vector<pair<int, long long>>> g(n);   // g[u] = {行き先, 長さ} のリスト
//   g[u].push_back({v, c});                      // u → v に長さ c の辺（無向なら逆向きも追加）
//   vector<vector<long long>> d = warshall_floyd(g);
//   d[u][v]                                      // u から v への最短距離。行けないなら -1
// 【注意】辺の長さが 0 以上のとき用。
// 【例】examples/graph/warshall_floyd.cpp に、そのまま動くプログラムがある。

vector<vector<long long>> warshall_floyd(const vector<vector<pair<int, long long>>>& g) {
    int n = g.size();
    // LLONG_MAX = まだ行けない
    vector<vector<long long>> d(n, vector<long long>(n, LLONG_MAX));
    for(int i = 0; i < n; i++) d[i][i] = 0;
    for(int u = 0; u < n; u++)
    {
        for(auto [v, c] : g[u]) d[u][v] = min(d[u][v], c);
    }
    // k を経由して i → j に行く方が近ければ更新
    for(int k = 0; k < n; k++)
    {
        for(int i = 0; i < n; i++)
        {
            if(d[i][k] == LLONG_MAX) continue;
            for(int j = 0; j < n; j++)
            {
                if(d[k][j] == LLONG_MAX) continue;
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            if(d[i][j] == LLONG_MAX) d[i][j] = -1;
        }
    }
    return d;
}
