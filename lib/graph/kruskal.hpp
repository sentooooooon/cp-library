// ===== クラスカル法（最小全域木） =====
// 【必要】先に union_find.hpp を貼っておく。
// 【何ができる】辺をいくつか選んで全部の頂点をつなぐとき、選んだ辺の長さの合計の最小値を O(M log M) で。
// 【使い方】
//   vector<tuple<int, int, long long>> edges;    // {a, b, 長さ}
//   edges.push_back({a, b, c});                  // a と b をつなぐ長さ c の辺
//   long long cost = kruskal(n, edges);          // 合計の最小値。全部はつなげないなら -1

long long kruskal(int n, vector<tuple<int, int, long long>> edges) {
    // 短い辺から順に見て、まだつながっていない2頂点をつなぐ辺だけ使う
    sort(edges.begin(), edges.end(), [](const auto& x, const auto& y) { return get<2>(x) < get<2>(y); });
    UnionFind uf(n);
    long long cost = 0;
    for(auto [a, b, c] : edges)
    {
        if(uf.merge(a, b)) cost += c;
    }
    if(uf.count() != 1) return -1;
    return cost;
}
