#pragma once
#include <vector>
#include <algorithm>

// 強連結成分分解（Tarjan、非再帰）。戻り値の成分はトポロジカル順
inline std::vector<std::vector<int>> scc(const std::vector<std::vector<int>>& g) {
    int n = (int)g.size(), timer = 0;
    std::vector<int> ord(n, -1), low(n), comp(n, -1), st, it(n, 0), call;
    std::vector<std::vector<int>> res;
    for (int s = 0; s < n; s++) {
        if (ord[s] != -1) continue;
        call.push_back(s);
        ord[s] = low[s] = timer++;
        st.push_back(s);
        while (!call.empty()) {
            int u = call.back();
            if (it[u] < (int)g[u].size()) {
                int v = g[u][it[u]++];
                if (ord[v] == -1) {
                    ord[v] = low[v] = timer++;
                    st.push_back(v);
                    call.push_back(v);
                } else if (comp[v] == -1) {
                    low[u] = std::min(low[u], ord[v]);
                }
                continue;
            }
            call.pop_back();
            if (!call.empty()) low[call.back()] = std::min(low[call.back()], low[u]);
            if (low[u] == ord[u]) {
                std::vector<int> c;
                while (true) {
                    int v = st.back();
                    st.pop_back();
                    comp[v] = (int)res.size();
                    c.push_back(v);
                    if (v == u) break;
                }
                res.push_back(std::move(c));
            }
        }
    }
    std::reverse(res.begin(), res.end());
    return res;
}
