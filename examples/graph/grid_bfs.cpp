// 【使うもの】graph/grid_bfs.hpp
// 【例題】H 行 W 列の迷路がある。'S' がスタート、'G' がゴール、'#' が壁、'.' が通路。
//        上下左右に 1 マスずつ動けるとき、S から G まで最短何手で行けるか。行けないなら -1。
// 【入力例】
// 3 4
// S..#
// .#..
// ...G
// 【出力例】
// 5

int main() {
    int h, w;
    cin >> h >> w;
    vector<string> s(h);
    for(int i = 0; i < h; i++) cin >> s[i];

    // S と G の場所を探す
    int si = 0, sj = 0, gi = 0, gj = 0;
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            if(s[i][j] == 'S') { si = i; sj = j; }
            if(s[i][j] == 'G') { gi = i; gj = j; }
        }
    }

    vector<vector<int>> dist = grid_bfs(s, si, sj);
    cout << dist[gi][gj] << "\n";
}
