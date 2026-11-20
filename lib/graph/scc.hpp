// ===== 強連結成分分解（SCC） =====
// 【何ができる】有向グラフで「お互いに行き来できる頂点」をグループにまとめる。O(N + M)
// 【使い方】
//   vector<vector<int>> g(n);    // g[u] = u から出る辺の行き先
//   vector<vector<int>> groups = scc(g);
//   groups[i]                    // i 番目のグループの頂点たち
//   ※ グループはトポロジカル順（前のグループから後ろのグループへしか辺がない）
// 【例】examples/graph/scc.cpp に、そのまま動くプログラムがある。

void scc_dfs1(int u, const vector<vector<int>>& g, vector<bool>& used, vector<int>& order) {
    used[u] = true;
    for(int v : g[u])
    {
        if(!used[v]) scc_dfs1(v, g, used, order);
    }
    order.push_back(u);
}

void scc_dfs2(int u, const vector<vector<int>>& rg, vector<int>& id, int k, vector<int>& group) {
    id[u] = k;
    group.push_back(u);
    for(int v : rg[u])
    {
        if(id[v] == -1) scc_dfs2(v, rg, id, k, group);
    }
}

vector<vector<int>> scc(const vector<vector<int>>& g) {
    int n = g.size();
    vector<vector<int>> rg(n);  // 辺を逆向きにしたグラフ
    for(int u = 0; u < n; u++)
    {
        for(int v : g[u]) rg[v].push_back(u);
    }
    // 1回目の DFS: 帰りがけ順を記録
    vector<bool> used(n, false);
    vector<int> order;
    for(int i = 0; i < n; i++)
    {
        if(!used[i]) scc_dfs1(i, g, used, order);
    }
    // 2回目の DFS: 帰りがけ順の逆から、逆グラフでたどる
    vector<int> id(n, -1);
    vector<vector<int>> groups;
    for(int i = n - 1; i >= 0; i--)
    {
        int u = order[i];
        if(id[u] != -1) continue;
        groups.push_back({});
        scc_dfs2(u, rg, id, groups.size() - 1, groups.back());
    }
    return groups;
}
