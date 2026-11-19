// ===== いもす法 =====
// 【何ができる】「a[l] 〜 a[r-1] に x を足す」をたくさんやってから、最後に配列全体を求める。
//              足すのは 1回 O(1)、最後にまとめて O(N)。
//              （途中で値を見たいときは bit.hpp や lazy_segtree.hpp を使う）
// 【使い方】
//   Imos im(n);                       // a[0] 〜 a[n-1]、最初は全部 0
//   im.add(l, r, x);                  // a[l] 〜 a[r-1] に x を足す（r は含まない）
//   vector<long long> a = im.build(); // 全部足し終わったあとの配列

struct Imos {
    vector<long long> d;  // d[i] = a[i] - a[i-1]

    Imos(int n) { d.assign(n + 1, 0); }

    void add(int l, int r, long long x) {
        d[l] += x;
        d[r] -= x;
    }

    vector<long long> build() {
        int n = (int)d.size() - 1;
        vector<long long> a(n);
        long long cur = 0;
        for(int i = 0; i < n; i++)
        {
            cur += d[i];
            a[i] = cur;
        }
        return a;
    }
};
