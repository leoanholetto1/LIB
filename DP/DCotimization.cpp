int m, n;
vt<ll> dp_before, dp_cur;
vt<ll> sum = {0};
 
ll C(int i, int j){
    return (sum[j]-sum[i-1])*(sum[j]-sum[i-1]);
}
 
void compute(int l, int r, int optl, int optr) {
    if (l > r)
        return;
 
    int mid = (l + r) >> 1;
    pair<ll, int> best = {LINF, -1};
 
    for (int k = optl; k <= min(mid, optr); k++) {
        best = min(best, {(k ? dp_before[k - 1] : 0) + C(k, mid), k});
    }
 
    dp_cur[mid] = best.first;
    int opt = best.second;
 
    compute(l, mid - 1, optl, opt);
    compute(mid + 1, r, opt, optr);
}
 
ll dc(){
    dp_before.assign(n+1,0);
    dp_cur.assign(n+1,0);
 
    for (int i = 1; i <= n; i++)
        dp_before[i] = C(1,i);
    for (int i = 1; i < m; i++) {
        compute(1, n, 1, n);
        dp_before = dp_cur;
    }
 
    return dp_before[n];
}