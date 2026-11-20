// 【使うもの】basic/doubling.hpp
// 【例題】町 1 〜 N がある。町 i のテレポーターを使うと町 A_i に行く。
//        町 1 からスタートしてテレポーターを K 回使ったとき、どの町にいるか。（K ≦ 10^18）
// 【入力例】
// 4 5
// 3 2 4 1
// 【出力例】
// 4

int main() {
    int n;
    long long k;
    cin >> n >> k;
    vector<int> nxt(n);
    for(int i = 0; i < n; i++)
    {
        cin >> nxt[i];
        nxt[i]--;  // 1 始まり → 0 始まり
    }

    Doubling db(nxt);
    cout << db.jump(0, k) + 1 << "\n";  // 町 1 は番号 0。答えは 1 始まりに戻す
}
