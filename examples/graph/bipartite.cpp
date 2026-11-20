// 【使うもの】graph/bipartite.hpp
// 【例題】N 頂点 M 辺の無向グラフがある。辺でつながった頂点どうしが違う色になるように、
//        全部の頂点を白と黒で塗れるなら Yes、塗れないなら No と出力せよ。
// 【入力例】
// 4 4
// 1 2
// 2 3
// 3 4
// 4 1
// 【出力例】
// Yes

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for(int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);
        g[b].push_back(a);
    }

    vector<int> color = bipartite(g);
    if(color.empty()) cout << "No\n";
    else cout << "Yes\n";
}
