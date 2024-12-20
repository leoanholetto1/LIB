//Complexidade: O(n*log n + m*log n)
int dist[maxn];
bool mark[maxn];
vector<pii> grafo[maxn];
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