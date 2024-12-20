class FenwickTree{
private:
	vll ft;
public:
	FenwickTree(int m){ ft.assign(m+1,0); }
	//Complexidade: O(n)
	void build(const vll &f){
		int m = (int) f.sz-1;
		ft.assign(m+1,0);
		for(int i=1;i<=m;i++){
			ft[i]+=f[i];
			if(i+LSOne(i)<=m) ft[i+LSOne(i)]+=ft[i];
		}
	}
	FenwickTree(const vll &f){ build(f);}
	//Complexidade: O(n)
	void build(int m,const vll &s){
		vll f(m+1,0);
		for(int i=0;i<s.sz;i++){
			++f[s[i]];
		}
		build(f);
	}
	//Complexidade: O(log n)
	ll rsq(int j){
		ll sum = 0;
		for(;j;j-=LSOne(j))
			sum+=ft[j];
		return sum;
	}
	//Complexidade: O(log n)
	ll rsq(int i,int j) {return rsq(j)-rsq(i-1);}
	//Complexidade: O(log n)
	void update(int i,ll v){
		for(;i<ft.sz;i+=LSOne(i)){
			ft[i]+=v;
		}
	}
};

class RUPQ{
private:
	FenwickTree ft;
public:
	RUPQ(int m) : ft(FenwickTree(m)) {};
	//Complexidade: O(log n)
	void range_update(int ui,int uj,ll v){
		ft.update(ui,v);
		ft.update(uj+1,-v);
	}
	//Complexidade: O(log n)
	ll point_query(int i){
		return ft.rsq(i);
	}
};

class RUQR{
private:
	RUPQ rupq;
	FenwickTree purq;
public:
	//Complexidade: O(log n)
	void range_update(int ui,int uj,ll v){
		rupq.range_update(ui,uj,v);
		purq.update(ui,v*(ui-1));
		purq.update(uj+1,-v*uj);
	}
	//Complexidade: O(log n)
	ll rsq(int j){
		return rupq.point_query(j)*j - purq.rsq(j);
	}
	//Complexidade: O(log n)
	ll rsq(int i,int j) {
		return rsq(j) - rsq(i-1);
	}
};
