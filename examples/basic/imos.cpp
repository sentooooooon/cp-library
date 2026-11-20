// 【使うもの】basic/imos.hpp
// 【例題】N 日間のイベントに M 人が来る。i 人目は l_i 日目から r_i 日目まで（r_i 日目も含む）いる。
//        各日に何人いるかを答えよ。
// 【入力例】
// 5 3
// 1 3
// 2 5
// 3 3
// 【出力例】
// 1 2 3 1 1

int main() {
    int n, m;
    cin >> n >> m;

    Imos im(n);
    for(int i = 0; i < m; i++)
    {
        int l, r;
        cin >> l >> r;
        im.add(l - 1, r, 1);  // 0 始まりで a[l-1] 〜 a[r-1] に 1 を足す
    }
    vector<long long> a = im.build();

    for(int i = 0; i < n; i++)
    {
        cout << a[i] << (i + 1 < n ? " " : "\n");
    }
}
