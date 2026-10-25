#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template <class T> using V = vector<T>;
template <class T> using VV = vector<vector<T>>;
#define rep(i, n) for (ll i = 0; i < (ll)(n); i++)
#define rep2(i, a, b) for (ll i = (a); i < (ll)(b); i++)
#define rrep(i, n) for (ll i = (ll)(n) - 1; i >= 0; i--)
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
template <class T> bool chmin(T& a, const T& b) { return b < a ? (a = b, true) : false; }
template <class T> bool chmax(T& a, const T& b) { return a < b ? (a = b, true) : false; }
constexpr ll INF = 1LL << 60;
constexpr int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

// ライブラリは必要なものだけ include（提出前に tools/expand.py で展開）
// #include "math/modint.hpp"

#ifdef LOCAL
#define dbg(...) cerr << "[" << #__VA_ARGS__ << "] = ", dbg_out(__VA_ARGS__)
template <class... T> void dbg_out(const T&... a) { ((cerr << a << ' '), ...); cerr << '\n'; }
#else
#define dbg(...) (void)0
#endif

void solve() {
}

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    solve();
}
