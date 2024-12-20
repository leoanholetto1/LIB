//Complexidade: O(n x log n)
void sieve(){
    for(ll p=2;p<=maxn;p++) vet[p] = p;
    for(ll i=2;i*i<=maxn;i++){
        if(vet[i]==i){
            for(ll p=i;p<=maxn;p+=i){
                vet[p] = i;
            }
        }
    }
}
 
ll conta(int n){
    if(n==1) return 0;
    else{
        ll num=n;
        map<ll,ll> mp;
        do{
            mp[vet[n]]++;
            n/=vet[n];
        }while(n>1);
        ll ans = 1;
        for (auto it : mp){
            ll pw = 1;
            ll sum = 0;
            do {
                sum += pw;
                pw *= it.first;
            } while (it.second-- > 0);
            ans *= sum;
        }
        return ans-num;
    }
}