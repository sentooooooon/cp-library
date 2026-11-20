// ===== BIT（Fenwick Tree） =====
// 【何ができる】「a[i] に x を足す」「a[l] + ... + a[r-1] を求める」を O(log N) で。
//              転倒数を数えるのにもよく使う。
// 【使い方】
//   BIT bit(n);              // a[0] 〜 a[n-1]、最初は全部 0
//   bit.add(i, x);           // a[i] += x
//   bit.sum(l, r)            // a[l] + a[l+1] + ... + a[r-1]（r は含まない）
//   bit.sum(r)               // a[0] + ... + a[r-1]
// 【例】examples/ds/bit.cpp に、そのまま動くプログラムがある。

struct BIT {
    int n;
    vector<long long> data;

    BIT(int n_) {
        n = n_;
        data.assign(n + 1, 0);
    }

    void add(int i, long long x) {
        for(i++; i <= n; i += i & -i)
        {
            data[i] += x;
        }
    }

    long long sum(int r) {
        long long s = 0;
        for(; r > 0; r -= r & -r)
        {
            s += data[r];
        }
        return s;
    }

    long long sum(int l, int r) { return sum(r) - sum(l); }
};
