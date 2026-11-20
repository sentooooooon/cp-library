// ===== 木の直径 =====
// 【何ができる】木の中で一番遠い2頂点の距離（辺の本数）と、その2頂点を O(N) で。
// 【使い方】
//   vector<vector<int>> g(n);                // 木（無向なので両方向に辺を入れる）
//   auto [d, a, b] = tree_diameter(g);       // 直径 d、両端の頂点 a と b
// 【例】examples/graph/tree_diameter.cpp に、そのまま動くプログラムがある。

tuple<int, int, int> tree_diameter(const vector<vector<int>>& g) {
    int n = g.size();
    // s から一番遠い頂点と、そこまでの距離を返す
    auto farthest = [&](int s) {
        vector<int> dist(n, -1);
        queue<int> q;
        dist[s] = 0;
        q.push(s);
        int far = s;
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            if(dist[u] > dist[far]) far = u;
            for(int v : g[u])
            {
                if(dist[v] != -1) continue;
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
        return pair<int, int>(far, dist[far]);
    };
    // どこかから一番遠い頂点 a は直径の端。a から一番遠い頂点 b がもう片方の端
    int a = farthest(0).first;
    auto [b, d] = farthest(a);
    return {d, a, b};
}
