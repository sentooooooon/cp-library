// 【使うもの】graph/kruskal.hpp
// 【例題】N 個の町と、道の候補が M 本ある。i 本目は町 a_i と b_i をつなぎ、作るのに c_i 円かかる。
//        いくつか道を作って全部の町を行き来できるようにするとき、最小で何円かかるか。無理なら -1。
// 【入力例】
// 4 5
// 1 2 1
// 2 3 2
// 3 4 3
// 1 3 3
// 2 4 5
// 【出力例】
// 6

int main() {
    int n, m;
    cin >> n >> m;
    vector<tuple<int, int, long long>> edges;
    for(int i = 0; i < m; i++)
    {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        a--; b--;
        edges.push_back({a, b, c});
    }

    cout << kruskal(n, edges) << "\n";
}
