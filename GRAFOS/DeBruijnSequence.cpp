//Complexidade: O(k^n)
vi adj[(1<<16)];
string s;int n;
void AcharCicloEuler(int u) {
    while(adj[u].size() != 0) {
        int v = adj[u].back();
        adj[u].pop_back();
        AcharCicloEuler(v);
    }
	if((u/(1<<(n-2)))&1) s+="1";
	else s+="0";
}
 
void solve(){
	cin>>n;
	if(n==1){
		cout <<"01"<<endl;
	}
	else{
		for(int i=0;i<(1<<(n-1));i++){
			adj[i].pb(i/2);
			adj[i].pb((i/2)|(1<<(n-2)));
		}
		AcharCicloEuler(0);
		for(int i=1;i<n-1;i++) s+="0";
		cout << s << endl;
	}
}
