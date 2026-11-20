// 【使うもの】string/z_algorithm.hpp
// 【例題】文字列 S の中で、文字列 T が出てくる位置（1 始まり）を全部出力せよ。
// 【入力例】
// abababa
// aba
// 【出力例】
// 1 3 5

int main() {
    string s, t;
    cin >> s >> t;

    // T + "$" + S の z を作ると、z[i] == T の長さ のところで T が見つかっている
    string u = t + "$" + s;
    vector<int> z = z_algorithm(u);
    vector<int> pos;
    for(int i = t.size() + 1; i < (int)u.size(); i++)
    {
        if(z[i] == (int)t.size()) pos.push_back(i - t.size());  // S の中での位置（1 始まり）
    }
    for(int i = 0; i < (int)pos.size(); i++)
    {
        cout << pos[i] << (i + 1 < (int)pos.size() ? " " : "\n");
    }
}
