//Complexidade: O(n x w)
int knaspck(int n,int w){
    memset(dp,0,sizeof(dp));
    for(int j=1;j<=w;j++){
        for(int i=1;i<=n;i++){
            if(weight[i-1] <=j){
                dp[j] = max(dp[j],dp[j-weight[i-1]]+val[i-1]);
            }
        }
    }
    return dp[w];
}