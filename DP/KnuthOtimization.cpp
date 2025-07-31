vt<ll> sum;
ll dp[5005][5005], opt[5005][5005];
ll knuth(int N) {
    auto C = [&](int i, int j) {
		if(i==0) return sum[j];
        return (sum[j]-sum[i-1]);
    };

    for (int i = 0; i < N; i++) {
        opt[i][i] = i;
		dp[i][i] = 0;
    }

    for (int i = N-2; i >= 0; i--) {
        for (int j = i+1; j < N; j++) {
            ll mn = LINF;
            ll cost = C(i, j);
            for (int k = opt[i][j-1]; k <= min<int>(j-1, opt[i+1][j]); k++) {
                if (mn >= dp[i][k] + dp[k+1][j] + cost) {
                    opt[i][j] = k; 
                    mn = dp[i][k] + dp[k+1][j] + cost; 
                }
            }
            dp[i][j] = mn; 
        }
    }

    return dp[0][N-1];
}