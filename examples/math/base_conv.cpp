// 【使うもの】math/base_conv.hpp
// 【例題】整数 N と K が与えられる。N を K 進数で表したものを出力せよ。
//        さらに、その文字列を K 進数として読んで 10 進数に戻したものを出力せよ。
// 【入力例】
// 255 16
// 【出力例】
// FF
// 255

int main() {
    long long n;
    int k;
    cin >> n >> k;

    string s = to_base(n, k);
    cout << s << "\n";
    cout << from_base(s, k) << "\n";
}
