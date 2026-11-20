// ===== 二部グラフ判定（2色の塗り分け） =====
// 【何ができる】辺でつながった2頂点が必ず違う色になるように、全頂点を 0 と 1 の2色で塗れるか調べる。O(N + M)
// 【使い方】
//   vector<vector<int>> g(n);           // 無向グラフ（両方向に辺を入れる）
//   vector<int> color = bipartite(g);
//   if(color.empty()) → 塗れない（二部グラフではない）
//   color[v]                            // 頂点 v の色（0 か 1）
//   ※ つながっていない部分ごとに、番号が一番小さい頂点を 0 にして塗る
// 【例】examples/graph/bipartite.cpp に、そのまま動くプログラムがある。

vector<int> bipartite(const vector<vector<int>>& g) {
    int n = g.size();
    vector<int> color(n, -1);  // -1 = まだ塗っていない
    for(int s = 0; s < n; s++)
    {
        if(color[s] != -1) continue;
        color[s] = 0;
        queue<int> q;
        q.push(s);
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            for(int v : g[u])
            {
                if(color[v] == -1)
                {
                    color[v] = 1 - color[u];
                    q.push(v);
                }
                else if(color[v] == color[u])
                {
                    return {};  // 隣と同じ色になってしまった
                }
            }
        }
    }
    return color;
}
