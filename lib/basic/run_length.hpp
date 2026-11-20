// ===== ランレングス圧縮 =====
// 【何ができる】同じものが続くところを「(もの, 何個続いたか)」にまとめる。O(N)
//              "aaabbc" → {('a', 3), ('b', 2), ('c', 1)}
// 【使い方】
//   for(auto [c, cnt] : run_length(s))   // string s
//   {
//       // c = 文字、cnt = 何個続いたか
//   }
//   run_length(a)                        // vector<long long> a でも使える
// 【例】examples/basic/run_length.cpp に、そのまま動くプログラムがある。

vector<pair<char, int>> run_length(const string& s) {
    vector<pair<char, int>> res;
    for(char c : s)
    {
        if(!res.empty() && res.back().first == c) res.back().second++;
        else res.push_back({c, 1});
    }
    return res;
}

vector<pair<long long, int>> run_length(const vector<long long>& a) {
    vector<pair<long long, int>> res;
    for(long long x : a)
    {
        if(!res.empty() && res.back().first == x) res.back().second++;
        else res.push_back({x, 1});
    }
    return res;
}
