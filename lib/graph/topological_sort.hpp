// ===== トポロジカルソート =====
// 【何ができる】有向グラフで「辺 u → v なら u が先」となる順番に並べる。
// 【使い方】
//   vector<vector<int>> g(n);    // g[u] = u から出る辺の行き先
//   vector<int> order = topological_sort(g);
//   if(order.empty()) → 閉路がある（並べられない）
// 【例】examples/graph/topological_sort.cpp に、そのまま動くプログラムがある。

vector<int> topological_sort(const vector<vector<int>>& g) {
    int n = g.size();
    vector<int> indeg(n, 0);  // 入ってくる辺の数
    for(int u = 0; u < n; u++)
    {
        for(int v : g[u]) indeg[v]++;
    }
    queue<int> q;
    for(int i = 0; i < n; i++)
    {
        if(indeg[i] == 0) q.push(i);
    }
    vector<int> order;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for(int v : g[u])
        {
            indeg[v]--;
            if(indeg[v] == 0) q.push(v);
        }
    }
    if((int)order.size() != n) return {};
    return order;
}
