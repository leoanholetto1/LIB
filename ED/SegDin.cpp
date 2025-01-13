vi sum,e,d;
//Complexidade: O(1)
int created(){
    sum.pb(0);
    e.pb(-1);
    d.pb(-1);
    return sum.sz-1;
}
//Complexidade: O(log n)
void update(int pos,ll ini,ll fim,ll id,int val){
    if(id<ini || id>fim) return ;
    if(ini==fim){
        sum[pos]+=val;
        return ;
    }
    ll m = (ini+fim)>>1;
    if(id<=m){
        if(e[pos]==-1) e[pos] = created();
        update(e[pos],ini,m,id,val);
    } else{
        if(d[pos]==-1) d[pos] = created();
        update(d[pos],m+1,fim,id,val);
    }
    int sumE = (e[pos]==-1) ? 0 : sum[e[pos]];
    int sumD = (d[pos]==-1) ? 0 : sum[d[pos]];
    sum[pos] = sumE + sumD;
}
//Complexidade: O(log n) 
ll query(int pos,ll ini,ll fim,int p,int q){
    if(pos==-1) return 0;
    if(q<ini || p>fim) return 0;
    if(p<=ini && fim<=q) return sum[pos];
    ll m = (ini+fim)>>1;
    return query(e[pos],ini,m,p,q) + query(d[pos],m+1,fim,p,q);
}

class SegmentTreeDynamic {
private:
    vt<ll> sum, e, d;
    int created() {
        sum.push_back(0);
        e.push_back(-1);
        d.push_back(-1);
        return sum.size() - 1;
    }

public:
    SegmentTreeDynamic() {
        created();
    }
	//Complexidade: O(log n)
    void update(int pos, ll ini, ll fim, ll id, ll val) {
        if (id < ini || id > fim) return;
        if (ini == fim) {
            sum[pos] += val;
            return;
        }
        ll m = (ini + fim) >> 1;
        if (id <= m) {
            if (e[pos] == -1) e[pos] = created();
            update(e[pos], ini, m, id, val);
        } else {
            if (d[pos] == -1) d[pos] = created();
            update(d[pos], m + 1, fim, id, val);
        }
        ll sumE = (e[pos] == -1) ? 0 : sum[e[pos]];
        ll sumD = (d[pos] == -1) ? 0 : sum[d[pos]];
        sum[pos] = sumE + sumD;
    }
    //Complexidade: O(log n)
    ll query(int pos,ll ini, ll fim, int p, int q) {
        if (pos == -1) return 0;
        if (q < ini || p > fim) return 0;
        if (p <= ini && fim <= q) return sum[pos];
        ll m = (ini + fim) >> 1;
        return query(e[pos], ini, m, p, q) +  query(d[pos], m + 1, fim, p, q);
    }
};