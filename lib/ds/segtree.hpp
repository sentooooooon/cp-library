// ===== セグメント木 =====
// 【何ができる】「a[i] を x に変える」「a[l] 〜 a[r-1] の最小値（や合計など）」を O(log N) で。
// 【使い方】
//   SegTree seg(n);              // 全部 e() で初期化
//   SegTree seg(a);              // vector<long long> a で初期化
//   seg.set(i, x);               // a[i] = x
//   seg.get(i)                   // a[i]
//   seg.query(l, r)              // a[l] 〜 a[r-1] をまとめた値（r は含まない）
//
// 【書き換えるところ】★ の2か所。デフォルトは「区間の最小値」。
//   最大値: e() = -INF (LLONG_MIN),  op = max(a, b)
//   合計  : e() = 0,                 op = a + b
//   gcd   : e() = 0,                 op = gcd(a, b)
// 【例】examples/ds/segtree.cpp に、そのまま動くプログラムがある。

struct SegTree {
    // ★ 何もない区間の値
    long long e() { return LLONG_MAX; }
    // ★ 2つをまとめる方法
    long long op(long long a, long long b) { return min(a, b); }

    int n;
    vector<long long> d;

    SegTree(int n_) {
        n = 1;
        while(n < n_) n *= 2;
        d.assign(2 * n, e());
    }

    SegTree(const vector<long long>& a) : SegTree(a.size()) {
        for(int i = 0; i < (int)a.size(); i++) d[n + i] = a[i];
        for(int i = n - 1; i >= 1; i--) d[i] = op(d[2 * i], d[2 * i + 1]);
    }

    void set(int i, long long x) {
        i += n;
        d[i] = x;
        while(i > 1)
        {
            i /= 2;
            d[i] = op(d[2 * i], d[2 * i + 1]);
        }
    }

    long long get(int i) { return d[n + i]; }

    long long query(int l, int r) {
        long long left = e(), right = e();
        l += n;
        r += n;
        while(l < r)
        {
            if(l & 1) left = op(left, d[l++]);
            if(r & 1) right = op(d[--r], right);
            l /= 2;
            r /= 2;
        }
        return op(left, right);
    }
};
