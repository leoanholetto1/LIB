//Complexidade: O(n x m^2)
int N, M, p[maxN];
ll cap[maxN][maxN];
vector<int> G[maxN];
 
ll bfs(int s, int t){
    fill(p+1, p+N+M+2, -1);
    p[s] = -2;
    queue<pil> Q;
    Q.push({s, INF});
    while(!Q.empty()){
        int u = Q.front().first;
        ll f = Q.front().second;
        Q.pop();
 
        for(int v : G[u]){
            if(p[v] == -1 && cap[u][v]){
                p[v] = u;
                ll aug = min(f, cap[u][v]);
                if(v == t)  return aug;
                Q.push({v, aug});
            }
        }
    }
 
    return 0;
}

ll maxflow(int s, int t){
    ll flow = 0, aug = 0;
    while(aug = bfs(0,t)){
        flow += aug;
        int u = t;
        while(u != s){
            int v = p[u];
            cap[v][u] -= aug;
            cap[u][v] += aug;
            u = v;
        }
    }
    return flow;
}
