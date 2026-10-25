// ===== 遅延セグメント木（区間に足す ＋ 区間の最小値・合計） =====
// 【何ができる】「a[l] 〜 a[r-1] 全部に x を足す」
//              「a[l] 〜 a[r-1] の最小値 / 最大値 / 合計」を O(log N) で。
// 【使い方】
//   LazySegTree seg(n);          // 全部 0 で初期化
//   LazySegTree seg(a);          // vector<long long> a で初期化
//   seg.add(l, r, x);            // a[l] 〜 a[r-1] に x を足す（r は含まない）
//   seg.get_min(l, r)            // a[l] 〜 a[r-1] の最小値
//   seg.get_max(l, r)            // a[l] 〜 a[r-1] の最大値
//   seg.get_sum(l, r)            // a[l] 〜 a[r-1] の合計

struct LazySegTree {
    int n;
    vector<long long> mn, mx, sm, lazy;

    LazySegTree(int n_) : LazySegTree(vector<long long>(n_, 0)) {}

    LazySegTree(const vector<long long>& a) {
        n = 1;
        while(n < (int)a.size()) n *= 2;
        mn.assign(2 * n, LLONG_MAX);
        mx.assign(2 * n, LLONG_MIN);
        sm.assign(2 * n, 0);
        lazy.assign(2 * n, 0);
        for(int i = 0; i < (int)a.size(); i++)
        {
            mn[n + i] = mx[n + i] = sm[n + i] = a[i];
        }
        for(int i = n - 1; i >= 1; i--) pull(i);
    }

    void add(int l, int r, long long x) { add(l, r, x, 1, 0, n); }
    long long get_min(int l, int r) { return query(l, r, 1, 0, n, 0); }
    long long get_max(int l, int r) { return query(l, r, 1, 0, n, 1); }
    long long get_sum(int l, int r) { return query(l, r, 1, 0, n, 2); }

    // ---- ここから下は中身（読まなくてOK） ----
    // k 番のノードは区間 [kl, kr) を担当している
    void apply(int k, int len, long long x) {
        if(mn[k] != LLONG_MAX) mn[k] += x;
        if(mx[k] != LLONG_MIN) mx[k] += x;
        sm[k] += x * len;
        lazy[k] += x;
    }

    void push(int k, int len) {
        if(lazy[k] == 0) return;
        apply(2 * k, len / 2, lazy[k]);
        apply(2 * k + 1, len / 2, lazy[k]);
        lazy[k] = 0;
    }

    void pull(int k) {
        mn[k] = min(mn[2 * k], mn[2 * k + 1]);
        mx[k] = max(mx[2 * k], mx[2 * k + 1]);
        sm[k] = sm[2 * k] + sm[2 * k + 1];
    }

    void add(int l, int r, long long x, int k, int kl, int kr) {
        if(r <= kl || kr <= l) return;
        if(l <= kl && kr <= r)
        {
            apply(k, kr - kl, x);
            return;
        }
        push(k, kr - kl);
        int mid = (kl + kr) / 2;
        add(l, r, x, 2 * k, kl, mid);
        add(l, r, x, 2 * k + 1, mid, kr);
        pull(k);
    }

    // type: 0 = min, 1 = max, 2 = sum
    long long query(int l, int r, int k, int kl, int kr, int type) {
        if(r <= kl || kr <= l)
        {
            if(type == 0) return LLONG_MAX;
            if(type == 1) return LLONG_MIN;
            return 0;
        }
        if(l <= kl && kr <= r)
        {
            if(type == 0) return mn[k];
            if(type == 1) return mx[k];
            return sm[k];
        }
        push(k, kr - kl);
        int mid = (kl + kr) / 2;
        long long a = query(l, r, 2 * k, kl, mid, type);
        long long b = query(l, r, 2 * k + 1, mid, kr, type);
        if(type == 0) return min(a, b);
        if(type == 1) return max(a, b);
        return a + b;
    }
};
