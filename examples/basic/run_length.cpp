// 【使うもの】basic/run_length.hpp
// 【例題】文字列 S の、同じ文字が続くところを「文字 + 個数」にまとめて出力せよ。
// 【入力例】
// aaabbcaa
// 【出力例】
// a3b2c1a2

int main() {
    string s;
    cin >> s;

    for(auto [c, cnt] : run_length(s))
    {
        cout << c << cnt;
    }
    cout << "\n";
}
