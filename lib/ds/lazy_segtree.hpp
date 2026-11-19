// ===== 遅延セグメント木（区間に足す・区間を変える ＋ 区間の最小値・最大値・合計） =====
// 【何ができる】「a[l] 〜 a[r-1] 全部に x を足す」「a[l] 〜 a[r-1] を全部 x にする」
//              「a[l] 〜 a[r-1] の最小値 / 最大値 / 合計」を O(log N) で。
// 【使い方】
//   LazySegTree seg(n);          // 全部 0 で初期化
//   LazySegTree seg(a);          // vector<long long> a で初期化
//   seg.add(l, r, x);            // a[l] 〜 a[r-1] に x を足す（r は含まない）
//   seg.assign(l, r, x);         // a[l] 〜 a[r-1] を全部 x にする
//   seg.get_min(l, r)            // a[l] 〜 a[r-1] の最小値
//   seg.get_max(l, r)            // a[l] 〜 a[r-1] の最大値
//   seg.get_sum(l, r)            // a[l] 〜 a[r-1] の合計
//   seg.get(i)                   // a[i]

struct LazySegTree {
    int n;
    vector<long long> mn, mx, sm;
    vector<long long> add_lz, set_lz;  // まだ子に伝えていない「足す」「変える」
    vector<bool> has_set;              // 「変える」がたまっているか

    LazySegTree(int n_) : LazySegTree(vector<long long>(n_, 0)) {}

    LazySegTree(const vector<long long>& a) {
        n = 1;
        while(n < (int)a.size()) n *= 2;
        mn.assign(2 * n, LLONG_MAX);
        mx.assign(2 * n, LLONG_MIN);
        sm.assign(2 * n, 0);
        add_lz.assign(2 * n, 0);
        set_lz.assign(2 * n, 0);
        has_set.assign(2 * n, false);
        for(int i = 0; i < (int)a.size(); i++)
        {
            mn[n + i] = mx[n + i] = sm[n + i] = a[i];
        }
        for(int i = n - 1; i >= 1; i--) pull(i);
    }

    void add(int l, int r, long long x) { update(l, r, x, false, 1, 0, n); }
    void assign(int l, int r, long long x) { update(l, r, x, true, 1, 0, n); }
    long long get_min(int l, int r) { return query(l, r, 1, 0, n, 0); }
    long long get_max(int l, int r) { return query(l, r, 1, 0, n, 1); }
    long long get_sum(int l, int r) { return query(l, r, 1, 0, n, 2); }
    long long get(int i) { return get_sum(i, i + 1); }

    // ---- ここから下は中身（読まなくてOK） ----
    // k 番のノードは区間 [kl, kr) を担当している。len = kr - kl
    void apply_add(int k, int len, long long x) {
        if(mn[k] != LLONG_MAX) mn[k] += x;
        if(mx[k] != LLONG_MIN) mx[k] += x;
        sm[k] += x * len;
        if(has_set[k]) set_lz[k] += x;  // 「y にする」→「x 足す」は「y + x にする」と同じ
        else add_lz[k] += x;
    }

    void apply_set(int k, int len, long long x) {
        mn[k] = mx[k] = x;
        sm[k] = x * len;
        has_set[k] = true;
        set_lz[k] = x;
        add_lz[k] = 0;
    }

    void push(int k, int len) {
        if(has_set[k])
        {
            apply_set(2 * k, len / 2, set_lz[k]);
            apply_set(2 * k + 1, len / 2, set_lz[k]);
            has_set[k] = false;
        }
        if(add_lz[k] != 0)
        {
            apply_add(2 * k, len / 2, add_lz[k]);
            apply_add(2 * k + 1, len / 2, add_lz[k]);
            add_lz[k] = 0;
        }
    }

    void pull(int k) {
        mn[k] = min(mn[2 * k], mn[2 * k + 1]);
        mx[k] = max(mx[2 * k], mx[2 * k + 1]);
        sm[k] = sm[2 * k] + sm[2 * k + 1];
    }

    void update(int l, int r, long long x, bool is_set, int k, int kl, int kr) {
        if(r <= kl || kr <= l) return;
        if(l <= kl && kr <= r)
        {
            if(is_set) apply_set(k, kr - kl, x);
            else apply_add(k, kr - kl, x);
            return;
        }
        push(k, kr - kl);
        int mid = (kl + kr) / 2;
        update(l, r, x, is_set, 2 * k, kl, mid);
        update(l, r, x, is_set, 2 * k + 1, mid, kr);
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
