ll dp[1005][1005];//guarda a soma de prefixo de cada linha

ll kadane(vt<ll> &sum){
    ll mx = -LINF,s=0;
    for(int i=0;i<sum.sz;i++){
        s+=sum[i];
        mx = max(mx,s);
        if(s < 0) s  = 0;
    }
    return mx;
}

ll kadane2d(){
    ll ans = -LINF;
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            vt<ll> sum;
            for(int linha=0;linha<n;linha++){
                if(i>0) sum.pb(dp[linha][j]-dp[linha][i-1]);
                else sum.pb(dp[linha][j]);
            }
            ans = max(ans,kadane(sum));
        }
    }
    return ans;
}