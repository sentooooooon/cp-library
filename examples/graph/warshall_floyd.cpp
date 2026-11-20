// 【使うもの】graph/warshall_floyd.hpp
// 【例題】N 頂点 M 辺の無向グラフがある。i 本目の辺は頂点 a_i と b_i をつなぎ、長さは c_i。
//        全部の 2 頂点の間の最短距離を、N 行 N 列の表にして出力せよ。
// 【入力例】
// 3 3
// 1 2 4
// 2 3 1
// 1 3 7
// 【出力例】
// 0 4 5
// 4 0 1
// 5 1 0

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
        g[b].push_back({a, c});
    }

    vector<vector<long long>> d = warshall_floyd(g);
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            cout << d[i][j] << (j + 1 < n ? " " : "\n");
        }
    }
}
