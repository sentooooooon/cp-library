// ===== 重み付き Union-Find =====
// 【何ができる】「b は a より w 大きい」という情報をどんどん追加して、
//              「b は a よりいくつ大きい？」「情報が矛盾していない？」にほぼ O(1) で答える。
// 【使い方】
//   WeightedUnionFind uf(n);
//   uf.merge(a, b, w)          // 「(b の値) - (a の値) = w」を追加。今までの情報と矛盾したら false
//   uf.same(a, b)              // a と b の差がわかるなら true
//   uf.diff(a, b)              // (b の値) - (a の値)。same(a, b) が true のときだけ使える
//   uf.size(a)                 // a がいるグループの人数
//   uf.count()                 // グループの数

struct WeightedUnionFind {
    vector<int> parent, sz;
    vector<long long> pot;  // pot[x] = (x の値) - (親の値)
    int num;

    WeightedUnionFind(int n) {
        parent.resize(n);
        sz.assign(n, 1);
        pot.assign(n, 0);
        num = n;
        for(int i = 0; i < n; i++) parent[i] = i;
    }

    int root(int x) {
        if(parent[x] == x) return x;
        int r = root(parent[x]);
        pot[x] += pot[parent[x]];  // 親の値の差を足して、根との差にする
        return parent[x] = r;
    }

    // (x の値) - (根の値)
    long long weight(int x) {
        root(x);
        return pot[x];
    }

    bool merge(int a, int b, long long w) {
        // 根どうしの関係に直す: (b の根の値) - (a の根の値) = w + weight(a) - weight(b)
        w += weight(a) - weight(b);
        a = root(a);
        b = root(b);
        if(a == b) return w == 0;
        if(sz[a] < sz[b])
        {
            swap(a, b);
            w = -w;
        }
        parent[b] = a;
        pot[b] = w;
        sz[a] += sz[b];
        num--;
        return true;
    }

    bool same(int a, int b) { return root(a) == root(b); }
    long long diff(int a, int b) { return weight(b) - weight(a); }
    int size(int a) { return sz[root(a)]; }
    int count() { return num; }
};
