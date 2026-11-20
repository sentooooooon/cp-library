// ===== 二分探索（答えで二分探索） =====
// 【何ができる】「x がある値以上なら全部 OK、それより小さいと全部 NG」（またはその逆）のとき、
//              OK と NG の境目を O(log) で見つける。
//              「〇〇の最小値を求めよ」「〇〇の最大値を求めよ」で、
//              「〇〇 = x にできる？」の判定なら簡単、というときに使う。
// 【使い方】
//   long long ans = bin_search(ok, ng, [&](long long x) { return x が OK なら true; });
//   ・ok には「絶対に OK な値」、ng には「絶対に NG な値」を入れる（ok > ng でもいい）
//   ・返り値は、OK な値のうち一番 ng に近いもの
//   ・ok と ng そのものは判定されない（範囲の外側の値を入れてOK）
//
//   例1: x * x >= 1000 となる最小の x → 32
//     bin_search(1000, 0, [&](long long x) { return x * x >= 1000; })
//   例2: x * x <= 1000 となる最大の x → 31
//     bin_search(0, 1000, [&](long long x) { return x * x <= 1000; })
// 【注意】判定の中で掛け算をするときは、オーバーフローしないように ok, ng を大きくしすぎない。
// 【おまけ】ソート済みの配列 a の中を探すだけなら標準の lower_bound / upper_bound で十分:
//   lower_bound(a.begin(), a.end(), x) - a.begin()   // x 以上が最初に出てくる位置
//   upper_bound(a.begin(), a.end(), x) - a.begin()   // x より大きいのが最初に出てくる位置
//   （x 未満の個数 = lower_bound の位置、x 以下の個数 = upper_bound の位置）
// 【例】examples/basic/binary_search.cpp に、そのまま動くプログラムがある。

long long bin_search(long long ok, long long ng, function<bool(long long)> f) {
    while(abs(ok - ng) > 1)
    {
        long long mid = ok + (ng - ok) / 2;
        if(f(mid)) ok = mid;
        else ng = mid;
    }
    return ok;
}
