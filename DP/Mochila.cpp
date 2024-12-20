//complexidade: O(w*n)
//top-dow
int knapsack(int w,int n){
    if(memo[w][n]!=-1) return memo[w][n];
    if(n==0 || w==0) return 0;
    if(weight[n-1] > w) return memo[w][n] = knapsack(w,n-1);
    return memo[w][n] = max(knapsack(w,n-1),
                        knapsack(w-weight[n-1],n-1)+val[n-1]);
}
//botton-up
int knapsack(int w,int n){
    int dp[n+1][w+1];
    for(int i=0;i<=n;i++) dp[i][0] = 0;
    for(int i=0;i<=w;i++) dp[0][i] = 0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=w;j++){
            if(weight[i-1] > j) 
                dp[i][j] = dp[i-1][j];
            else 
                dp[i][j] = max(dp[i-1][j],
                               dp[i-1][j-weight[i-1]]+val[i-1]);
        }
    }
    for (int i = n; i > 0 && w > 0; --i) {
        if (dp[i][w] != dp[i - 1][w]) {
            aux.push_back(i); 
            w -= v[i - 1]; 
        }
    }
}
//Otimização
int KnapSack(int val[], int wt[], int n, int W){
    int dp[W + 1];
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i < n; i++)
        for (int j = W; j >= wt[i]; j--)
            dp[j] = max(dp[j], val[i] + dp[j - wt[i]]);
    return dp[W];
}