//Complexidade: O(n + m)
void solve(int u){
    queue<int> q;
    int d=0,vert;
    q.push(u);
    while(!q.empty()){
        u = q.front();q.pop();
        for(auto v: u){
            if(vis[v]) continue;
            dist[v] = dist[u] + 1;
            p.push(v);
            if(dist[v] >d){
                d = dist[v];
                vert = v;
            }
        } 
    }
    d=0;
    q.push(vert);
    memset(vis,0,sizeof(vis));
    dist[vert] = 0;
    while(!q.empty()){
        u = q.front();q.pop();
        for(auto v: u){
            if(vis[v]) continue;
            dist[v] = dist[u] + 1;
            p.push(v);
            if(dist[v] >d){
                d = dist[v];
                vert = v;
            }
        } 
    }
    cout<<d<<endl;
}