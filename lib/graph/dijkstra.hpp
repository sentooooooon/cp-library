// ===== ダイクストラ法（最短経路） =====
// 【何ができる】辺の長さが 0 以上のグラフで、スタート s から各頂点への最短距離を O(M log N) で。
// 【使い方】
//   vector<vector<pair<int, long long>>> g(n);   // g[u] = {行き先, 長さ} のリスト
//   g[u].push_back({v, c});                      // u → v に長さ c の辺（無向なら逆向きも追加）
//   vector<long long> dist = dijkstra(g, s);
//   dist[v]                                      // s から v への最短距離。行けないなら -1

vector<long long> dijkstra(const vector<vector<pair<int, long long>>>& g, int s) {
    int n = g.size();
    vector<long long> dist(n, -1);
    // {距離, 頂点} を距離が小さい順に取り出す
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    dist[s] = 0;
    pq.push({0, s});
    while(!pq.empty())
    {
        auto [d, u] = pq.top();
        pq.pop();
        if(d > dist[u]) continue;
        for(auto [v, c] : g[u])
        {
            if(dist[v] == -1 || d + c < dist[v])
            {
                dist[v] = d + c;
                pq.push({dist[v], v});
            }
        }
    }
    return dist;
}
