vet(ll) sum = {0};
//Complexidade: O(1)
ll query(int l,int r){
	return sum[r] - sum[l-1];
}
//Complexidade: O(n)
for(int i=1;i<=n;i++){
    cin>>k;
    sum.pb(sum.back()+k);
}