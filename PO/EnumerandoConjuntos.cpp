//Complexidade: O(2^n)
int mask;
for(int subset=mask;subset;subset=mask&(subset-1))
    cout<<subset<<endl;

//Complexidade: O(3^n)
for(int i=1;i<(1<<n);i++){
    int mask=i;
    for(int subset=mask;subset;subset=mask&(subset-1)){
        dp[mask] = max(dp[mask],dp[mask^subset]+dp2[subset]);
    }
}