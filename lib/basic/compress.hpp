// ===== 座標圧縮 =====
// 【何ができる】大きな数（10^9 など）を「小さい方から何番目か」（0, 1, 2, ...）に置き換える。
//              同じ数は同じ番号になる。大きな数を BIT やセグ木の番号に使いたいときに。
// 【使い方】
//   vector<long long> a = {100, 5, 100, 30};
//   Compress cp(a);
//   cp.ids(a)                // {2, 0, 2, 1}（a を全部番号に置き換えたもの）
//   cp.id(30)                // 1（30 の番号）
//   cp.val(2)                // 100（番号 2 の元の数）
//   cp.size()                // 3（何種類あるか）
//   ※ 2つ以上の配列をまとめて圧縮したいときは、1つの vector にまとめてから渡す。
// 【例】examples/basic/compress.cpp に、そのまま動くプログラムがある。

struct Compress {
    vector<long long> vals;  // 小さい順・重複なし

    Compress(const vector<long long>& a) {
        vals = a;
        sort(vals.begin(), vals.end());
        vals.erase(unique(vals.begin(), vals.end()), vals.end());
    }

    // x の番号（x が a に入っていなかったときは「x 以上で一番小さい数」の番号）
    int id(long long x) { return lower_bound(vals.begin(), vals.end(), x) - vals.begin(); }

    vector<int> ids(const vector<long long>& a) {
        vector<int> res(a.size());
        for(int i = 0; i < (int)a.size(); i++) res[i] = id(a[i]);
        return res;
    }

    long long val(int i) { return vals[i]; }
    int size() { return vals.size(); }
};
