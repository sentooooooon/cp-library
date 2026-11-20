// 【使うもの】ds/union_find.hpp
// 【例題】N 人いて、最初は全員バラバラのグループ。Q 個の命令を順に処理せよ。
//        「0 a b」: a のグループと b のグループをくっつける
//        「1 a b」: a と b が同じグループなら Yes、違うなら No と出力
// 【入力例】
// 4 5
// 0 1 2
// 1 1 3
// 0 2 3
// 1 1 3
// 1 1 4
// 【出力例】
// No
// Yes
// No

int main() {
    int n, q;
    cin >> n >> q;

    UnionFind uf(n);
    for(int i = 0; i < q; i++)
    {
        int type, a, b;
        cin >> type >> a >> b;
        a--; b--;
        if(type == 0)
        {
            uf.merge(a, b);
        }
        else
        {
            if(uf.same(a, b)) cout << "Yes\n";
            else cout << "No\n";
        }
    }
}
