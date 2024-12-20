ll x[maxN], y[maxN], ans;
//Complexidade: O(n)
void solve(){
    x[n] = x[0]; y[n] = y[0];
    ans =0;
    for(int i = 0; i < n; i++){
        ans += x[i] * y[i+1];
        ans -= y[i] * x[i+1];
    }
    cout<<abs(ans)<<endl;
}