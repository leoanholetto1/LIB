//Complexidade: O(idx x tight x sum)$
ll dp[101][2][100005]; 
ll solve(int idx,bool tight,int sum,vi &t){
    if(idx == -1) return sum;
    ll &ans = dp[idx][tight][sum];
    if(ans != -1) return ans;
    ans = 0;
    int k= tight ? t[idx] : 9;
    for(int i=0;i <= k; i++)
        ans += solve(idx-1,tight && (i==k), sum+(i==dig), t);
    return ans;
}
//Complexidade: O(log n)
vi convert(ll n){ 
    vi v;
    while(n){v.pb(n%10); n/=10;} 
    return v;
}

void solve(){
    vi v;ll n,a,b;
    cin>>n;
    while(n--){
        cin>>a>>b;
        if(a>b) swap(a,b);
        v = convert(a-1);
        memset(dp,-1,sizeof(dp));
        ll sum = solve(v.sz-1,1,0,v);
        v = convert(b);
        memset(dp,-1,sizeof(dp));
        ll sum2 = solve(v.sz-1,1,0,v);
        cout<<sum2-sum<<endl;
    }
}   

//Conta numeros de zero, sem contar zero a esquerda
ll dp2[10][2][30][2]; 
ll countZeros(int idx, int tight, int hasNonZero, vi  &v,int c) {
    if (idx == -1){
        if (!hasNonZero) return 0;
        return c;
    }
    ll &ans = dp2[idx][tight][c][hasNonZero];
    if(ans != -1) return ans;
    ans = 0;
    int k= tight ? v[idx] : 9;
    for(int i=0;i <= k; i++){
        if(hasNonZero) ans += countZeros(idx-1,tight && (i==k), hasNonZero ,v , c+(i==0));
        else{
            if(idx==0) ans += countZeros(idx-1,tight && (i==k), 1 ,v , c+(i==0));
            else  ans += countZeros(idx-1,tight && (i==k), i!=0,v , c);
        }
    }
    return ans;
}