//Complexidade: O(n + m)
vector<int> adj[maxN],adjT[maxN];
vector<int> regiao(maxN);
vector<bool> vis(maxN);
stack<int> pilha;
void dfs(int v){
    vis[v] = 1;
    for(auto u : adj[v]){
        if(!vis[u])
            dfs(u);
    }
    pilha.push(v);
} 
void dfsT(int v,int c){
    vis[v] = 1;
    regiao[v] = c;
    for(auto u : adjT[v]){
        if(!vis[u])
            dfsT(u,c);
    }
}
void solve(){
    int n,m;
    cin>>n>>m;
    int a,b;
    for(int i=0;i<m;i++){
        cin>>a>>b;
        adj[a].push_back(b);
        adjT[b].push_back(a);
    }
    for(int i=1;i<=n;i++){
        if(!vis[i]) dfs(i);
    }
    
    for(int i = 1; i <=n ; i++)
        vis[i] = false;
    
    int c=1;
    while (!pilha.empty()){
        int v = pilha.top();
        pilha.pop();
        if(!vis[v]){
            dfsT(v,c);
                c++;
        }
    }
    cout<<c-1<<endl;
    for(int i=1;i<=n;i++)
        cout<<regiao[i]<<" ";
}