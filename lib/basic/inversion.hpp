// ===== 転倒数 =====
// 【何ができる】i < j なのに a[i] > a[j] となっているペアの数を O(N log N) で。
//              =「隣どうしを入れ替えて小さい順に並べる」ときの最小回数（バブルソートの交換回数）
// 【使い方】
//   long long cnt = inversion_count(a);     // vector<long long> a（a は書き換わらない）

// 中身（読まなくてOK）: a[l] 〜 a[r-1] をマージソートしながら転倒数を数える
long long inversion_count_rec(vector<long long>& a, vector<long long>& tmp, int l, int r) {
    if(r - l <= 1) return 0;
    int mid = (l + r) / 2;
    long long cnt = inversion_count_rec(a, tmp, l, mid) + inversion_count_rec(a, tmp, mid, r);
    int i = l, j = mid, k = l;
    while(i < mid || j < r)
    {
        if(j == r || (i < mid && a[i] <= a[j]))
        {
            tmp[k++] = a[i++];
        }
        else
        {
            cnt += mid - i;  // 左に残っている a[i] 〜 a[mid-1] は全部 a[j] より大きい
            tmp[k++] = a[j++];
        }
    }
    for(int t = l; t < r; t++) a[t] = tmp[t];
    return cnt;
}

long long inversion_count(vector<long long> a) {
    vector<long long> tmp(a.size());
    return inversion_count_rec(a, tmp, 0, a.size());
}
