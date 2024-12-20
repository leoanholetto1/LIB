//Complexidade: O(m * sqrt(n))
vi adj[n];
vi dist(n),matchL(n),matchR(n);

bool dfs(int l){
    if(l==0) return true;
    for(int r: adj[l]){
        if(dist[matchR[r]] == dist[l]+1){
            if(dfs(matchR[r])){
                matchR[r] = l;
                matchL[l] = r;
                return true;
            }
        }
    }
    return false;
}

bool bfs(){
    queue<int> q ;
    for(int l = 1;l  <=n ;l++){
        if(matchL[l] == 0){
            dist[l] = 0;
            q.push(l);
        }
        else dist[l] = INF;
    }
    dist[0] = INF;
    while(!q.empty()){
        int l = q.front();
        q.pop();
        if(dist[l] <dist[0]){
            for(int r: adj[l]){
                if(dist[matchR[r]] == INF){
                    dist[matchR[r]] = dist[l]+1;
                    q.push(matchR[r]);
                }
            }
        }
    }
    return dist[0] < INF;
}

int hopcraft_karp(){
    for(int i=1;i<=n;i++){
        matchL[i] = matchR[i] = 0;
    }
    int matching = 0;
    while(bfs()){
        for(int i=1;i<=n;i++){
            if(matchL[i]==0 && dfs(i)) matching++;
        }
    }
    return matching;
}