// 【使うもの】graph/topological_sort.hpp
// 【例題】N 個の作業がある。M 個の条件「作業 a_i は作業 b_i より先にやる」を全部守る順番を 1 つ出力せよ。
//        そんな順番がなければ -1。
// 【入力例】
// 4 3
// 1 2
// 1 3
// 3 2
// 【出力例】
// 1 4 3 2

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    for(int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        a--; b--;
        g[a].push_back(b);  // a → b（a が先）
    }

    vector<int> order = topological_sort(g);
    if(order.empty())
    {
        cout << -1 << "\n";
        return 0;
    }
    for(int i = 0; i < n; i++)
    {
        cout << order[i] + 1 << (i + 1 < n ? " " : "\n");
    }
}
