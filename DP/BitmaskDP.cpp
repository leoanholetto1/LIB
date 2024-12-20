//Complexidade: O(n x 2^n)
//top-dow
int calc(int mask,int j){
    if(j==(int) vet.sz){
        if(mask == (1<<n)-1) return 0;
        return -1e9;
    }
    int &resp = dp[mask][j];
    if(resp!=-1) return resp;
    return resp = max(calc(mask,j+1),calc(mask|(1<<get<3>(vet[j])),pr[j])+get<2>(vet[j]));
}
//botton-up
int calc(int cost[maxN][maxN],int n){
    int dp[1<<n];
    memset(dp,inf,sizeof(dp));
    dp[0] = 0;
    for(int mask=0;mask<(1<<n);mask++){
        x = conta_bits(mask);
        for(int j=0;j<n;j++){
            dp[mask | (1<<j)] = min(dp[mask] + cost[x][j],  dp[mask | (1<<j)]);
        }
    }
    return dp[(1<<n) - 1 ];
}