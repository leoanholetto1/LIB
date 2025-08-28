vi getCentroids(const vt<vi> &G, int n) {
    vi tam(n+1, 0);
    vi centroids;
    function<void(int,int)> dfs = [&](int u, int p) {
        tam[u] = 1;
        bool isCentroid = true;
        for (int v : G[u]) if (v != p) {
            dfs(v, u);
            tam[u] += tam[v];
            if (tam[v] > n/2) isCentroid = false;
        }
        if (n - tam[u] > n/2) isCentroid = false;
        if (isCentroid) centroids.push_back(u);
    };
    dfs(1, -1);
    return centroids;
}