// ===== Z-algorithm =====
// 【何ができる】z[i] = 「s」と「s の i 文字目から後ろ」が先頭から何文字一致するか、を O(N) で。
//              パターン検索: z_algorithm(t + "$" + s) で z[i] == t.size() の場所が一致位置。
// 【使い方】
//   vector<int> z = z_algorithm("aabaa");   // {5, 1, 0, 2, 1}
// 【例】examples/string/z_algorithm.cpp に、そのまま動くプログラムがある。

vector<int> z_algorithm(const string& s) {
    int n = s.size();
    if(n == 0) return {};
    vector<int> z(n, 0);
    z[0] = n;
    int l = 0, r = 0;
    for(int i = 1; i < n; i++)
    {
        if(i < r) z[i] = min(r - i, z[i - l]);
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if(i + z[i] > r)
        {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}
