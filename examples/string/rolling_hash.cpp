// 【使うもの】string/rolling_hash.hpp
// 【例題】文字列 S と Q 個の質問がある。各質問 a b c d について、
//        S の a 〜 b 文字目と c 〜 d 文字目が同じ文字列なら Yes、違うなら No と出力せよ。（1 始まり）
// 【入力例】
// abcabc
// 3
// 1 3 4 6
// 1 2 2 3
// 2 2 5 5
// 【出力例】
// Yes
// No
// Yes

int main() {
    string s;
    int q;
    cin >> s >> q;

    RollingHash rh(s);
    for(int i = 0; i < q; i++)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        // a 〜 b 文字目（1 始まり）は、0 始まりで [a-1, b)
        if(rh.get(a - 1, b) == rh.get(c - 1, d)) cout << "Yes\n";
        else cout << "No\n";
    }
}
