// 【使うもの】basic/lis.hpp
// 【例題】数列 A から順番を変えずにいくつか選んで、だんだん大きくなる（同じ値はダメ）ようにしたい。
//        最大で何個選べるか。
// 【入力例】
// 6
// 3 1 4 1 5 9
// 【出力例】
// 4

int main() {
    int n;
    cin >> n;
    vector<long long> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    cout << lis(a) << "\n";  // 例えば 3 4 5 9 や 1 4 5 9
}
