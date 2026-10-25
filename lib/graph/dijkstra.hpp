#pragma once
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <functional>

// g[u] = {{v, cost}, ...}。到達不能は numeric_limits<T>::max()
template <class T>
std::vector<T> dijkstra(const std::vector<std::vector<std::pair<int, T>>>& g, int s) {
    const T INF = std::numeric_limits<T>::max();
    std::vector<T> dist(g.size(), INF);
    using P = std::pair<T, int>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
    dist[s] = 0;
    pq.emplace(0, s);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u]) continue;
        for (auto [v, c] : g[u]) {
            if (d + c < dist[v]) {
                dist[v] = d + c;
                pq.emplace(dist[v], v);
            }
        }
    }
    return dist;
}
