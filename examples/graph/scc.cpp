// 【使うもの】graph/scc.hpp
// 【例題】N 頂点 M 辺の有向グラフがある。お互いに行き来できる頂点どうしをグループにまとめるとき、
//        グループの数と、各グループの頂点（小さい順）を出力せよ。
// 【入力例】
// 5 5
// 1 2
// 2 3
// 3 1
// 3 4
// 4 5
// 【出力例】
// 3
// 1 2 3
// 4
// 5

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
    }

    vector<vector<int>> groups = scc(g);
    cout << groups.size() << "\n";
    for(auto& grp : groups)
    {
        sort(grp.begin(), grp.end());
        for(int i = 0; i < (int)grp.size(); i++)
        {
            cout << grp[i] + 1 << (i + 1 < (int)grp.size() ? " " : "\n");
        }
    }
}
