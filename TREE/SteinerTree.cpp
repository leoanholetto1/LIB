//Complexidade: O(2^k * n^2 + 3^k * N)
//Find the steiner tree, where nodes from 0,k-1 are terminals
//dist[i][j] has the distance between the nodes (floyd wharshall?)
for(int i=k;i<n;i++){
    for(int j=0;j<k;j++){
        dp[i-k][(1<<j)] = dist[i][j];
    }
    dp[i-k][0] = 0;
}

for(int msk = 1;msk<(1<<k);msk++){
    for(int root = k;root < n;root ++ ){
        for(int sub = msk;sub>0;sub = (sub-1)&msk){
            if(sub == msk)continue;
            dp[root - k][msk] = min(dp[root-k][msk],dp[root-k][sub] + dp[root-k][msk^sub] ); 
        }
        for(int other = k;other<n;other++){
            if(other == root)continue;
            dp[other - k][msk] = min(dp[other - k][msk],dp[root-k][msk] + dist[root][other]);
        }
    }
}

double ans = INF;
for(int i=k;i<n;i++){
    ans = min(ans,dp[i-k][(1<<k)-1]);
}