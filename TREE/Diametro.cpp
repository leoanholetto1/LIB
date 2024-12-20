int vert;
//Complexidade: O(n)
void dfs(int v,int d,int pai){
    if(d > maior ){
        maior = d;
        vert = v;
    }
    for(auto u: adj[v]){
        if(u!=pai) dfs(u,d+1,v);
    }
}
//Complexidade: O(n)
void solve(){
    maior = 0;
    dfs(1,0,-1);
    maior = 0;
    dfs(vert,0,-1);
    cout<<maior<<endl;
}