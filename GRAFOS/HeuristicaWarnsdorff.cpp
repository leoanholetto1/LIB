int grid[9][9];
 
int conta(int i,int j){
	int c=0;
	for(int p=0;p<movC.sz;p++){
		int ni = i + movC[p].f;
		int nj = j + movC[p].s;
		if(ni >0 && nj>0 && ni<=8 && nj<=8 && grid[ni][nj] == -1){
			c++;
		}
	}
	return c;
}
 
bool rec(int i,int j,int mov){
	grid[i][j] =mov;
	if(mov == 64) return 1;
	vt<tuple<int,int,int>> v;
	for(int p=0;p<movC.sz;p++){
		int ni = i + movC[p].f;
		int nj = j + movC[p].s;
		if(ni >0 && nj>0 && ni<=8 && nj<=8 && grid[ni][nj] == -1){
			v.pb({conta(ni,nj),ni,nj});
		}
	}
	sort(all(v));
	for(int i=0;i<v.sz;i++){
		if(rec(get<1>(v[i]),get<2>(v[i]),mov+1)){
			return 1;
		}
	}
	grid[i][j] = -1;
	return 0;
}
 
 
void solve(){
	int x,y;
	cin>>x>>y;
	mem(grid,-1);
	rec(y,x,1);
	for(int i=1;i<=8;i++){
		for(int j=1;j<=8;j++){
			cout << grid[i][j] <<" ";
		}
		cout << endl;
	}
}