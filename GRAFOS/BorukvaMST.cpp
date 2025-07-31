
//Complexidade O(m log n)
void borukva(){
    int comp=n;
    UnionFind dsu(n);
    ll ans =  0;
    while(comp>1){
        for(int i=1;i<=n;i++) min_edge[i] = -1;
        for(int i=0;i<m;i++){
            if(dsu.isSameSet(g[i].v,g[i].u)) continue;
            int r_v = dsu.findSet(g[i].v);
            if(min_edge[r_v]==-1  or g[i].cost < g[min_edge[i]].cost){
                min_edge[r_v] = i;
            }
            int r_u = dsu.findSet(g[i].u);
            if(min_edge[r_u]==-1  or g[i].cost < g[min_edge[i]].cost){
                min_edge[r_u] = i;
            }
        }
        for(int i=1;i<=n;i++){
            if(min_edge[i]!=-1 && !dsu.isSameSet(g[min_edge[i]].v,g[min_edge[i]].u)){
                ans+=g[min_edge[i]].cost;
                comp--;
                dsu.unionSet(g[min_edge[i]].v,g[min_edge[i]].u);
            }
        }
    }
}