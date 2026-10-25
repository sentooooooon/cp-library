// ===== Union-Find =====
// 【何ができる】「a と b を同じグループにする」「a と b は同じグループ？」をほぼ O(1) で。
// 【使い方】
//   UnionFind uf(n);         // 0 〜 n-1 の n 人。最初は全員バラバラ
//   uf.merge(a, b);          // a と b のグループをくっつける
//   uf.same(a, b)            // 同じグループなら true
//   uf.size(a)               // a がいるグループの人数
//   uf.count()               // グループの数
//   uf.groups()              // グループごとの頂点リスト

struct UnionFind {
    vector<int> parent, sz;
    int num;

    UnionFind(int n) {
        parent.resize(n);
        sz.assign(n, 1);
        num = n;
        for(int i = 0; i < n; i++) parent[i] = i;
    }

    int root(int x) {
        if(parent[x] == x) return x;
        return parent[x] = root(parent[x]);
    }

    // くっつけたら true、もともと同じグループなら false
    bool merge(int a, int b) {
        a = root(a);
        b = root(b);
        if(a == b) return false;
        if(sz[a] < sz[b]) swap(a, b);
        parent[b] = a;
        sz[a] += sz[b];
        num--;
        return true;
    }

    bool same(int a, int b) { return root(a) == root(b); }
    int size(int a) { return sz[root(a)]; }
    int count() { return num; }

    vector<vector<int>> groups() {
        int n = parent.size();
        vector<vector<int>> g(n);
        for(int i = 0; i < n; i++) g[root(i)].push_back(i);
        vector<vector<int>> res;
        for(int i = 0; i < n; i++)
        {
            if(!g[i].empty()) res.push_back(g[i]);
        }
        return res;
    }
};
