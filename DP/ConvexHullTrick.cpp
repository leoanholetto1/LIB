struct Line{
	ll a,b,x_inter;
	bool operator<(ll x) const{
		return x_inter < x;
	}
};
vector<Line> cht;
ll intersec(Line x,Line y){
	assert(x.a!=y.a);
	return (x.b-y.b)/(y.a-x.a);
}
//Complexidade: O(1)
void add_line(ll a,ll b){
	if(!cht.empty() && cht.back().a==a) cht.pop_back(); //substitui pra return nop caso de menor
	while(cht.sz>=2){
		auto x = cht[cht.sz - 2];
		auto y = cht[cht.sz - 1];
		if(intersec(y,{a,b,0}) < intersec(x,y)){
			cht.pop_back();
		}
		else break;
	}
	if(!cht.empty()) cht.back().x_inter = intersec(cht.back(),{a,b,0});
	cht.push_back({a,b,INF});
}

//Complexidade: O(log n)
ll query(ll x){
	int j = lower_bound(all(cht),x)-cht.begin();
	return cht[j].a*x + cht[j].b;
}