class MST {
private:
    vector<vector<int>> edgelist; // {weight, x, y}
public:
    //Complexidade: O(1)
    void addEdge(int x, int y, int w) {
        edgelist.push_back({w, x, y});
    }
    //Complexidade: O(m x log m)
    void kruskals_mst(int n) {
        sort(edgelist.begin(), edgelist.end());
        UnionFind s(n+1);
        int ans = 0;
        for (auto edge : edgelist) {
            int w = edge[0];
            int x = edge[1];
            int y = edge[2];

            if (!s.isSameSet(x,y)) {
                s.unionSet(x, y);
                ans += w;
            }
        }
        cout << ans << endl;
    }
};