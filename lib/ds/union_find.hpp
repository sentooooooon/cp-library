#pragma once
#include <vector>
#include <utility>

// Union-Find（union by size + 経路圧縮）
struct UnionFind {
    std::vector<int> p;  // 根なら -(サイズ)、それ以外は親
    int comps;

    explicit UnionFind(int n = 0) : p(n, -1), comps(n) {}
    int leader(int x) { return p[x] < 0 ? x : p[x] = leader(p[x]); }
    bool same(int a, int b) { return leader(a) == leader(b); }
    int size(int x) { return -p[leader(x)]; }
    int count() const { return comps; }
    // 併合できたら true
    bool merge(int a, int b) {
        a = leader(a), b = leader(b);
        if (a == b) return false;
        if (p[a] > p[b]) std::swap(a, b);
        p[a] += p[b];
        p[b] = a;
        comps--;
        return true;
    }
    std::vector<std::vector<int>> groups() {
        int n = (int)p.size();
        std::vector<std::vector<int>> g(n);
        for (int i = 0; i < n; i++) g[leader(i)].push_back(i);
        std::vector<std::vector<int>> res;
        for (auto& v : g) if (!v.empty()) res.push_back(std::move(v));
        return res;
    }
};
