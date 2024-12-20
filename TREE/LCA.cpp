vi tree[maxN];
int depth[maxN];
int pai[maxN][21];
//Complexidade: O(n x log n)
void preprocess(int u, int p){
    pai[u][0] = p;
    for(int i = 1; i <= 20; i++){
        pai[u][i] = pai[pai[u][i-1]][i-1];
    }
    for(auto adj: tree[u]){
		if(adj!=p){
			depth[adj] = depth[u] + 1;
        	preprocess(adj, u);
		}
    }
}
//Complexidade: O(log n)
int lca(int u, int v){
    if (depth[u] < depth[v]){
        swap(u, v);
    }
    for (int i = 20; i >= 0; i--)  
        if ((depth[u] - (1 << i)) >= depth[v])  
            u = pai[u][i];
 
    if (u == v)  
        return u;  
      
    for (int i = 20; i >= 0; i--)  
    {  
        if (pai[u][i] != pai[v][i])  
        {  
            u = pai[u][i];  
            v = pai[v][i];  
        }  
    }  
    return pai[u][0];  
}
 
void solve(){
    depth[1] = 0;
    preprocess(1, 1);
    int z = lca(a,b);
}