// 【使うもの】basic/binary_search.hpp
// 【例題】N 台の機械がある。機械 i は A_i 秒ごとに 1 個ずつ商品を作る。
//        全部の機械を同時に動かして、合計 K 個作れるのは最短で何秒後か。
// 【入力例】
// 3 10
// 1 2 3
// 【出力例】
// 6

int main() {
    int n;
    long long k;
    cin >> n >> k;
    vector<long long> a(n);
    for(int i = 0; i < n; i++) cin >> a[i];

    // t 秒で K 個以上作れるか？（t が大きいほど作れる → 二分探索できる）
    auto can = [&](long long t) {
        long long cnt = 0;
        for(int i = 0; i < n; i++)
        {
            cnt += t / a[i];
            if(cnt >= k) return true;  // 早めに抜ける（足しすぎてオーバーフローしないように）
        }
        return false;
    };

    // 0 秒では絶対に作れない（NG）
    // k * a[0] 秒あれば機械 0 だけで作れる（OK）
    long long ans = bin_search(k * a[0], 0, can);
    cout << ans << "\n";
}
