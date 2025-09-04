//Complexidade: O(n x 2^n)
void sos(){	
	int N = 20;
	int n,k;
	vi v;
	cin>>n;
	for(int i=0;i<n;i++){
		cin>>k;
		v.pb(k);
		F[k]++;
		F2[k]++;
	}
	for(int i = 0;i < N; ++i) 
		for(int mask = 0; mask < (1<<N); ++mask){
			if(mask & (1<<i)) F[mask] += F[mask^(1<<i)]; //x|y=x
			if ((mask & (1 << i)) == 0) F2[mask] +=  F2[mask|(1<<i)]; //x&y=x
		}
	for(int i=0;i<n;i++){
		int inv = v[i] ^ ((1<<N)-1); //x&y!=0
		cout << F[v[i]] << " " << F2[v[i]] <<" " << n-F[inv] <<  endl;
	}
}