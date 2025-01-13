//raiz[b] = update(raiz[b-1],1,n,i+1,a);
//raiz[1] = update(raiz[1],1,n,i+1,a);
vt<ll> soma,e,d;
vi raiz;
//Complexidade: O(1)
int create(){
	soma.pb(0);
	e.pb(0);
	d.pb(0);
	return soma.sz-1;
}
//Complexidade: O(log n)
int update(int pos,ll ini,ll fim,ll id,ll val){
	int novo = create();
	soma[novo] = soma[pos];
	e[novo] = e[pos];
	d[novo] = d[pos];
	if(ini == fim){
		soma[novo] = val;
		return novo;
	}
	ll m = (ini+fim)>>1;
	if(id <=m) e[novo] = update(e[novo],ini,m,id,val);
	else d[novo] = update(d[novo],m+1,fim,id,val);
	soma[novo] = soma[e[novo]] + soma[d[novo]];
	return novo;
}

//Complexidade: O(log n)
ll query(int pos,ll ini,ll fim,int p,int q){
	if(pos==0) return  0;
    if(q<ini || p>fim) return 0;
    if(p<=ini && fim<=q) return soma[pos];
    ll m = (ini+fim)>>1;
    return query(e[pos],ini,m,p,q) + query(d[pos],m+1,fim,p,q);
}

