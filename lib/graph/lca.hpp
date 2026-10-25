#pragma once
#include <vector>
#include <utility>

// ダブリングによる LCA。構築 O(N log N)、クエリ O(log N)
struct LCA {
    int n, lg;
    std::vector<std::vector<int>> up;
    std::vector<int> depth;

    LCA(const std::vector<std::vector<int>>& g, int root = 0) : n((int)g.size()) {
        lg = 1;
        while ((1 << lg) < n) lg++;
        up.assign(lg, std::vector<int>(n, root));
        depth.assign(n, -1);
        // 再帰を避けて BFS
        std::vector<int> q = {root};
        depth[root] = 0;
        for (size_t i = 0; i < q.size(); i++) {
            int u = q[i];
            for (int v : g[u]) {
                if (depth[v] != -1) continue;
                depth[v] = depth[u] + 1;
                up[0][v] = u;
                q.push_back(v);
            }
        }
        for (int k = 1; k < lg; k++)
            for (int v = 0; v < n; v++) up[k][v] = up[k - 1][up[k - 1][v]];
    }
    // v から k 個上の祖先（k > depth なら -1）
    int ancestor(int v, int k) const {
        if (k > depth[v]) return -1;
        for (int i = 0; k; i++, k >>= 1) if (k & 1) v = up[i][v];
        return v;
    }
    int lca(int a, int b) const {
        if (depth[a] < depth[b]) std::swap(a, b);
        a = ancestor(a, depth[a] - depth[b]);
        if (a == b) return a;
        for (int k = lg - 1; k >= 0; k--) {
            if (up[k][a] != up[k][b]) a = up[k][a], b = up[k][b];
        }
        return up[0][a];
    }
    int dist(int a, int b) const { return depth[a] + depth[b] - 2 * depth[lca(a, b)]; }
};
