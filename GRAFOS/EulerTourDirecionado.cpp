//Complexidade: O(n+m)
void AcharCicloEuler(int u) {
    while(adj[u].size() != 0) {
        int v = adj[u].back();
        adj[u].pop_back();
        AcharCicloEuler(v);
    }
    CicloEuleriano.push_back(u);
}
 
void solve() {
    IOS;
    int n,m,x,y;
    cin>>n>>m;
    for(int a=0;a<m;a++){
        cin>>x>>y;
        edges_out[x]++;
        edges_in[y]++;
        adj[x].push_back(y);
    }
    if (edges_out[1] != edges_in[1] + 1 || edges_in[n] != edges_out[n] + 1) {
        cout << "IMPOSSIBLE\n";
        return ;
    }
    for (int i = 2; i < n; i++) {
        if (edges_out[i] != edges_in[i]) {
            cout << "IMPOSSIBLE\n";
            return ;
        }
    }
    AcharCicloEuler(1);
    if(CicloEuleriano.size() != m+1) cout << "IMPOSSIBLE\n";
    else{
        reverse(CicloEuleriano.begin(),CicloEuleriano.end());
        for(auto i : CicloEuleriano)
            cout<<i<<" ";
        cout<<endl;
    }
}