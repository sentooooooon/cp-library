// ===== N 進数 =====
// 【使い方】
//   to_base(10, 2)          // "1010"（10 を 2 進数の文字列に）
//   from_base("1010", 2)    // 10（2 進数の文字列を数に）
//   ※ 2 〜 36 進数まで。10 以上の桁は 'A', 'B', ...（from_base は小文字でもOK）
//   ※ to_base に渡す数は 0 以上。
// 【例】examples/math/base_conv.cpp に、そのまま動くプログラムがある。

string to_base(long long n, int b) {
    if(n == 0) return "0";
    string s;
    while(n > 0)
    {
        int d = n % b;
        s += (char)(d < 10 ? '0' + d : 'A' + d - 10);
        n /= b;
    }
    reverse(s.begin(), s.end());
    return s;
}

long long from_base(const string& s, int b) {
    long long n = 0;
    for(char c : s)
    {
        int d;
        if('0' <= c && c <= '9') d = c - '0';
        else if('A' <= c && c <= 'Z') d = c - 'A' + 10;
        else d = c - 'a' + 10;
        n = n * b + d;
    }
    return n;
}
