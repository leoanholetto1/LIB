vi adj[maxN],ans(maxN);
set<int> cor[maxN];
//Complexidade: O(n x log n x log n)
void dfs(int u,int p=-1){
    for(int v :adj[u]){
        if(v==p) continue;
        dfs(v,u);
        if(cor[u].sz < cor[v].sz){
            swap(cor[u],cor[v]);
        }
        for(int x: cor[v]){
            cor[u].insert(x);
        }
    }
    ans[u] = cor[u].sz;
}