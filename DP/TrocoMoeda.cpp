//Complexidade: O(n x m)
//top-dow
vi moedas;
map<int,int> memo; //int memo[maxN];
int troco(int x){
    if(x==0) return 0;
    if(memo.count(x)) return memo[x];
    memo[x] = INT_MAX;
    for(int m: moedas){
        if(m > x) continue;
        memo[x] = min(memo[x], 1 + troco(x-m));
    }
    return memo[x];
}
//botton-up
int troco(vi &moedas,int m){
    int n = moedas.sz;
    vi dp(m+1,INT_MAX);
    dp[0] = 0;
    for(int i=1;i<=m;i++){
        for(int j=0;j<n;j++){
            dp[i] = min(dp[i], dp[i-moedas[j]]+1);
        }
    }
    return dp[m];
}