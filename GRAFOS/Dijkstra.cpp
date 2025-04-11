//Complexidade: O(n*log n + m*log n)
int dist[maxN];
vector<pii> grafo[maxN];
void dijkstra(int S){
    for (int i = 0; i <= n; i++)
        dist[i] = INF;
    dist[S] = 0;
    priority_queue<pii, vector<pii>, greater<pii>> fila;
    fila.push({0, S});
    while (!fila.empty()){
        int u = fila.top().second;
		int W = fila.top().f;
        fila.pop();
		if(u == n) return ;
        for (auto V: grafo[u]){
            int v = V.first, w = V.second;
            if (dist[v] > dist[u] + w){
                dist[v] = dist[u] + w;
                fila.push({dist[v], v});
            }
        }
    }
}
//Mais rapido
void dijkstra(int start, int n) {
    dist[start] = 0;
    set<pair<int, int>> pq;
    pq.insert({0, start});

    while (!pq.empty()) {
        auto [d, u] = *pq.begin();
        pq.erase(pq.begin());

        for (auto [v, w] : graph[u]) {
            if (dist[u] + w < dist[v]) {
                if(pq.count({dist[v], v})) pq.erase({dist[v], v});
                dist[v] = dist[u] + w;
                pq.insert({dist[v], v});
            }
        }
    }
}