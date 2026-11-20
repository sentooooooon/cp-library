// ===== 累積和（1次元・2次元） =====
// 【何ができる】配列が変わらないとき、区間の合計を O(1) で。（前計算 O(N)）
// 【使い方】
//   PrefixSum ps(a);                  // vector<long long> a
//   ps.sum(l, r)                      // a[l] + a[l+1] + ... + a[r-1]（r は含まない）
//
//   PrefixSum2D ps2(g);               // vector<vector<long long>> g（H 行 W 列）
//   ps2.sum(i1, j1, i2, j2)           // 行 i1 〜 i2-1、列 j1 〜 j2-1 の長方形の合計
//                                     // （i2 行目と j2 列目は含まない）
// 【例】examples/basic/prefix_sum.cpp と examples/basic/prefix_sum_2d.cpp に、そのまま動くプログラムがある。

struct PrefixSum {
    vector<long long> s;  // s[i] = a[0] + ... + a[i-1]

    PrefixSum(const vector<long long>& a) {
        s.assign(a.size() + 1, 0);
        for(int i = 0; i < (int)a.size(); i++) s[i + 1] = s[i] + a[i];
    }

    long long sum(int l, int r) { return s[r] - s[l]; }
};

struct PrefixSum2D {
    vector<vector<long long>> s;  // s[i][j] = 行 0 〜 i-1、列 0 〜 j-1 の合計

    PrefixSum2D(const vector<vector<long long>>& g) {
        int h = g.size();
        int w = (h == 0 ? 0 : g[0].size());
        s.assign(h + 1, vector<long long>(w + 1, 0));
        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                s[i + 1][j + 1] = s[i][j + 1] + s[i + 1][j] - s[i][j] + g[i][j];
            }
        }
    }

    long long sum(int i1, int j1, int i2, int j2) {
        return s[i2][j2] - s[i1][j2] - s[i2][j1] + s[i1][j1];
    }
};
