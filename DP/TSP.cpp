//Complexidade: O(n x 2^n)
ll dist2[20][20];
ll dp[20][(1<<17)];
ll tsp(int i,int mask){
    //para caminho deve-se retorna 0
    if(mask == (1<<tl)-1) return dist2[i][0]; 
    if(dp[i][mask]!=-1) return dp[i][mask];
    ll ans = LINF;
    for(int j=0;j<tl;j++){
        if((mask&(1<<j)) || dist2[i][j]==-1) continue;
        ans = min(ans , tsp(j, mask|(1<<j))+dist2[i][j]);
    }
    return dp[i][mask] = ans; 
}
tsp(0,1);