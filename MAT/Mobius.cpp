//Complexidade: O(n x loglogn)
int mobius[maxN + 10],prime[maxN+10]; 
void precompute_mobius() { 
	for (ll i = 1; i <= maxN; ++i){
		prime[i] = mobius[i] = 1;
	}
    for (ll i = 2; i <= maxN; ++i) {
        if (!prime[i]) continue;
        mobius[i] = -1;
        for (ll j = 2; j <= maxN / i; ++j) {
            prime[i * j] = 0;
            mobius[i * j] *= -1;
        }
        for (ll j = 1; j <= maxN / (i * i); ++j) {
            mobius[j * i * i] = 0;
        }
    }
}
//contar quantida de numeros livre de quadrados
//Complexidade: O(sqrt(n))
ll cont(ll n){
	ll sum=0;
	for(ll i=1;i*i<=n;i++){
		sum+=(n/(i*i))*mobius[i];
	}
	return sum;
}