// ===== BFS（幅優先探索・辺の長さがないグラフの最短距離） =====
// 【何ができる】辺の長さが全部 1 のグラフで、s から各頂点への最短距離（何本の辺で行けるか）を O(N + M) で。
//              「s から行ける頂点はどれ？」を調べるのにも使える（行けない頂点は -1）。
// 【使い方】
//   vector<vector<int>> g(n);
//   g[a].push_back(b);                  // a → b の辺
//   g[b].push_back(a);                  // 無向グラフなら逆向きも入れる
//   vector<int> dist = bfs(g, s);
//   dist[v]                             // s から v への最短距離。行けないなら -1

vector<int> bfs(const vector<vector<int>>& g, int s) {
    int n = g.size();
    vector<int> dist(n, -1);
    queue<int> q;
    dist[s] = 0;
    q.push(s);
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int v : g[u])
        {
            if(dist[v] != -1) continue;  // もう来た
            dist[v] = dist[u] + 1;
            q.push(v);
        }
    }
    return dist;
}
