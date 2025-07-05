//Complexidade: O(n^2)
for(int a=1;a<=n;a++){
    for(int b=1;b<=n;b++){
        cin>>x;
        dp[a][b] = dp[a-1][b] - dp[a-1][b-1] + dp[a][b-1] + v[a][b];
    }
}
//Complexidade: O(1)
int query(int x1, int y1, int x2, int y2){
    return dp[x2][y2] - dp[x1-1][y2] - dp[x2][y1-1] + dp[x1-1][y1-1];
}