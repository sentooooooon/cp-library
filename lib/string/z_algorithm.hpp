#pragma once
#include <vector>
#include <string>
#include <algorithm>

// z[i] = s と s[i:] の最長共通接頭辞長（z[0] = |s|）
template <class Seq>
std::vector<int> z_algorithm(const Seq& s) {
    int n = (int)s.size();
    if (n == 0) return {};
    std::vector<int> z(n, 0);
    z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i < r) z[i] = std::min(r - i, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
}
