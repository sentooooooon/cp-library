#pragma once
#include <vector>

// Kahn 法。DAG でなければ空 vector
inline std::vector<int> topological_sort(const std::vector<std::vector<int>>& g) {
    int n = (int)g.size();
    std::vector<int> indeg(n, 0), res;
    for (auto& es : g) for (int v : es) indeg[v]++;
    for (int i = 0; i < n; i++) if (indeg[i] == 0) res.push_back(i);
    for (size_t i = 0; i < res.size(); i++) {
        for (int v : g[res[i]]) if (--indeg[v] == 0) res.push_back(v);
    }
    if ((int)res.size() != n) return {};
    return res;
}
