//Para minimo (-a,-b)
struct Line{
	ll a,b;
};
ll get_val(Line line,int x){
	return line.a*x+line.b;
}
vector<Line> li_chao;
int T;
void init(int n){
	T = n;
	li_chao.assign(4*T+1,{0,-LINF});
}
//Complexidade: O(log n)
ll query(int v,int x,int l,int r){
	if(l==r) return get_val(li_chao[v],x);
	ll ans = get_val(li_chao[v],x);
	int mid = (l+r)/2;
	if(x <= mid) ans = max(ans,query(2*v,x,l,mid));
	else ans = max(ans,query(2*v+1,x,mid+1,r));
	return ans;
}
//Complexidade: O(log n)
ll query(int x){
	return query(1,x,0,T-1);
}
//Complexidade: O(log n)
void add_line(int v,Line line,int l,int r){
	int m = (l+r)/2;
	if(get_val(line,m) > get_val(li_chao[v],m))
		swap(li_chao[v],line);
	if(get_val(line,l) > get_val(li_chao[v],l))
		add_line(2*v,line,l,m);
	if(get_val(line,r) > get_val(li_chao[v],r))
		add_line(2*v+1,line,m+1,r);
}
//Complexidade: O(log n)
void add_line(ll a,ll b){
	return add_line(1,{a,b},0,T-1);
}