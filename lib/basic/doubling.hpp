// ===== ダブリング =====
// 【何ができる】「場所 i の次は nxt[i]」という移動を k 回（k は 10^18 くらいまでOK）
//              くり返したあとの場所を O(log k) で。（前計算 O(N log k)）
//              「K 回テレポートしたあとどこにいる？」のような問題で使う。
// 【使い方】
//   vector<int> nxt(n);         // nxt[i] = i の次に行く場所（0 〜 n-1）
//   Doubling db(nxt);
//   db.jump(x, k)               // x から k 回進んだ場所

struct Doubling {
    static const int LOG = 61;  // 2^61 > 2 × 10^18
    vector<vector<int>> to;     // to[d][i] = i から 2^d 回進んだ場所

    Doubling(const vector<int>& nxt) {
        to.assign(LOG, nxt);
        for(int d = 1; d < LOG; d++)
        {
            for(int i = 0; i < (int)nxt.size(); i++)
            {
                to[d][i] = to[d - 1][to[d - 1][i]];
            }
        }
    }

    int jump(int x, long long k) {
        for(int d = 0; d < LOG; d++)
        {
            if(k >> d & 1) x = to[d][x];
        }
        return x;
    }
};
