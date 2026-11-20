// ===== LCA（木の共通祖先） =====
// 【何ができる】根付き木で、2頂点の一番近い共通の祖先・2頂点間の距離を O(log N) で。
// 【使い方】
//   vector<vector<int>> g(n);    // 木（無向で両方向に辺を入れる）
//   LCA lca(g, 0);               // 0 を根にする
//   lca.lca(a, b)                // a と b の共通祖先
//   lca.dist(a, b)               // a と b の距離（辺の本数）
//   lca.depth[v]                 // 根からの深さ
//   lca.ancestor(v, k)           // v から k 個上の頂点（なければ -1）
// 【例】examples/graph/lca.cpp に、そのまま動くプログラムがある。

struct LCA {
    int LOG;
    vector<vector<int>> parent;  // parent[k][v] = v から 2^k 個上
    vector<int> depth;

    LCA(const vector<vector<int>>& g, int root) {
        int n = g.size();
        LOG = 1;
        while((1 << LOG) < n) LOG++;
        parent.assign(LOG, vector<int>(n, root));
        depth.assign(n, -1);
        // BFS で深さと親を求める
        queue<int> q;
        q.push(root);
        depth[root] = 0;
        while(!q.empty())
        {
            int u = q.front();
            q.pop();
            for(int v : g[u])
            {
                if(depth[v] != -1) continue;
                depth[v] = depth[u] + 1;
                parent[0][v] = u;
                q.push(v);
            }
        }
        for(int k = 1; k < LOG; k++)
        {
            for(int v = 0; v < n; v++)
            {
                parent[k][v] = parent[k - 1][parent[k - 1][v]];
            }
        }
    }

    int ancestor(int v, int k) {
        if(k > depth[v]) return -1;
        for(int i = 0; i < LOG; i++)
        {
            if(k >> i & 1) v = parent[i][v];
        }
        return v;
    }

    int lca(int a, int b) {
        if(depth[a] < depth[b]) swap(a, b);
        a = ancestor(a, depth[a] - depth[b]);
        if(a == b) return a;
        for(int k = LOG - 1; k >= 0; k--)
        {
            if(parent[k][a] != parent[k][b])
            {
                a = parent[k][a];
                b = parent[k][b];
            }
        }
        return parent[0][a];
    }

    int dist(int a, int b) { return depth[a] + depth[b] - 2 * depth[lca(a, b)]; }
};
