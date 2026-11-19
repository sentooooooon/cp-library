// ===== 最長増加部分列（LIS） =====
// 【何ができる】数列から順番を変えずにいくつか取り出して「だんだん大きくなる」列を作るとき、
//              一番長くできる長さを O(N log N) で。
// 【使い方】
//   lis(a)              // a[i1] < a[i2] < ...（同じ数はダメ）の最長の長さ。vector<long long> a
//   lis(a, false)       // a[i1] <= a[i2] <= ...（同じ数もOK）の最長の長さ
//   ※ だんだん小さくなる列がほしいときは、全部に -1 を掛けてから lis する。

int lis(const vector<long long>& a, bool strict = true) {
    vector<long long> dp;  // dp[k] = 長さ k+1 の列の「最後の数」としてありえる一番小さい数
    for(long long x : a)
    {
        auto it = strict ? lower_bound(dp.begin(), dp.end(), x) : upper_bound(dp.begin(), dp.end(), x);
        if(it == dp.end()) dp.push_back(x);
        else *it = x;
    }
    return dp.size();
}
