//Complexidade: O(n+m)
void preprocess(int u, int p){
    for(auto adj: tree[u]){
        if(adj.f==p) continue;
        depth[adj.f] = depth[u] + 1;
        distMax[adj.f][0] = adj.s; 
        preprocess(adj.f, u);
    }
}
//Complexidade: O(n x log n)
void binary(int u,int p){
    pai[u][0] = p;
    for(int i = 1; i <= 20; i++){
        pai[u][i] = pai[pai[u][i-1]][i-1];
        distMax[u][i] = min(distMax[u][i-1],distMax[pai[u][i-1]][i-1]);
    }
     for(auto adj: tree[u]){
        if(adj.f==p) continue;
        binary(adj.f, u);
    }
}
//Complexidade: O(log n)
int lca(int u, int v){
    if (depth[u] < depth[v]){
        swap(u, v);
    }
    int dMax=INF;
    for (int i = 20; i >= 0; i--)  
        if ((depth[u] - (1 << i)) >= depth[v] && pai[u][i]!=-1) {
            dMax = min(dMax,distMax[u][i]);
            u = pai[u][i];
        }
    if (u == v)
        return dMax;   
    for (int i = 20; i >= 0; i--)  
    {  
        if (pai[u][i] != pai[v][i])  
        {  
            dMax = min(dMax,distMax[u][i]);
            dMax = min(dMax,distMax[v][i]);
            u = pai[u][i];  
            v = pai[v][i];  
        }  
    }  
    dMax = min(dMax,distMax[u][0]);
    dMax = min(dMax,distMax[v][0]);
    return dMax;   
}