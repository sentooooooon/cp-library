// ===== グリッド BFS（迷路の最短手数） =====
// 【何ができる】マス目の迷路で、スタートから各マスへの最短手数を O(HW) で。上下左右に1マスずつ動ける。
// 【使い方】
//   int h, w;
//   cin >> h >> w;
//   vector<string> s(h);
//   for(int i = 0; i < h; i++) cin >> s[i];          // '#' が壁、それ以外は通れる
//   vector<vector<int>> dist = grid_bfs(s, si, sj);  // (si, sj) からスタート（0 始まり）
//   dist[i][j]                                       // (i, j) までの最短手数。行けないなら -1
//   ※ 問題文のマスが 1 始まりなら si--, sj-- してから渡す。
// 【書き換えるところ】★ 斜めにも動けるなら 8 方向に、壁の文字が '#' でないならそこを書き換える。
// 【例】examples/graph/grid_bfs.cpp に、そのまま動くプログラムがある。

vector<vector<int>> grid_bfs(const vector<string>& s, int si, int sj) {
    // ★ 動ける方向（下・右・上・左）
    vector<int> di = {1, 0, -1, 0};
    vector<int> dj = {0, 1, 0, -1};
    // 8 方向にするなら:
    // vector<int> di = {1, 1, 0, -1, -1, -1, 0, 1};
    // vector<int> dj = {0, 1, 1, 1, 0, -1, -1, -1};
    // ★ 壁の文字
    char wall = '#';

    int h = s.size(), w = s[0].size();
    vector<vector<int>> dist(h, vector<int>(w, -1));
    queue<pair<int, int>> q;
    dist[si][sj] = 0;
    q.push({si, sj});
    while(!q.empty())
    {
        auto [i, j] = q.front();
        q.pop();
        for(int d = 0; d < (int)di.size(); d++)
        {
            int ni = i + di[d], nj = j + dj[d];
            if(ni < 0 || ni >= h || nj < 0 || nj >= w) continue;  // 外に出る
            if(s[ni][nj] == wall) continue;                       // 壁
            if(dist[ni][nj] != -1) continue;                      // もう来た
            dist[ni][nj] = dist[i][j] + 1;
            q.push({ni, nj});
        }
    }
    return dist;
}
