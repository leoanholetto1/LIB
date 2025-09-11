vi CicloEuleriano,edges_id[100000+5];
vt<pair<int,int> > edges;
vt<bool> vis(200005,0);
//Complexidade: O(n+m)
void AcharCicloEuler(int u) {
    while(edges_id[u].size() != 0) {
        int id = edges_id[u].back();
        if(vis[id] == 1) {
            edges_id[u].pop_back();
            continue;
        }
        int v = edges[id].first+edges[id].second-u;
        vis[id] = 1;
        edges_id[u].pop_back();
        AcharCicloEuler(v);
    }
    CicloEuleriano.pb(u);
}

void ciclo_euler(){
    int n,m,x,y;
    cin>>n>>m;
    for(int a=0;a<m;a++){
        cin>>x>>y;
        edges_id[x].push_back(a);
        edges_id[y].push_back(a);
        edges.push_back({x,y});
    }
    bool flag=1;
    for(int a=1;a<=n;a++){
        if(edges_id[a].size()&1) flag=0;
    }
    if(flag){
        AcharCicloEuler(1);
        if(CicloEuleriano.size() != m+1)  cout << "IMPOSSIBLE\n";
        else{
            reverse(CicloEuleriano.begin(),CicloEuleriano.end());
            for(int a=0;a<CicloEuleriano.size();a++)
                cout<<CicloEuleriano[a]<<" ";
            cout<<endl;
        }
    }
    else cout<<"IMPOSSIBLE\n";
}