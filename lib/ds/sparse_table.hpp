// ===== Sparse Table =====
// 【何ができる】配列が変わらないとき、a[l] 〜 a[r-1] の最小値を O(1) で。（前計算 O(N log N)）
// 【使い方】
//   SparseTable st(a);       // vector<long long> a
//   st.query(l, r)           // a[l] 〜 a[r-1] の最小値（l < r）
// 【書き換えるところ】★ を max にすれば最大値、gcd にすれば gcd。（足し算はダメ）
// 【例】examples/ds/sparse_table.cpp に、そのまま動くプログラムがある。

struct SparseTable {
    // ★
    long long op(long long a, long long b) { return min(a, b); }

    vector<vector<long long>> table;
    vector<int> lg;

    SparseTable(const vector<long long>& a) {
        int n = a.size();
        lg.assign(n + 1, 0);
        for(int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        table.assign(lg[n] + 1, a);
        for(int k = 1; k <= lg[n]; k++)
        {
            for(int i = 0; i + (1 << k) <= n; i++)
            {
                table[k][i] = op(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
            }
        }
    }

    long long query(int l, int r) {
        int k = lg[r - l];
        return op(table[k][l], table[k][r - (1 << k)]);
    }
};
