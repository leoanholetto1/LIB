struct node{
    ll sum,lz;
};

node seg[4*maxN];
//Complexidade: O(1)
void propagate(int pos,int ini,int fim){
    if(seg[pos].lz==0) return ;
    ll num = seg[pos].lz;
    seg[pos].lz = 0;
    seg[pos].sum+=(fim-ini+1)*num;
    if(ini == fim) return ;
    int e=2*pos,d=2*pos+1;
    seg[e].lz+=num;
    seg[d].lz+=num;
}
//Complexidade: O(log n)
void update(int pos,int ini,int fim,int p,int q,int val){
    propagate(pos,ini,fim);
    if(q<ini || p>fim) return ;
    if(p<=ini && fim<=q){
        seg[pos].lz+=val;
        propagate(pos,ini,fim);
        return ;
    }
    int m = (ini+fim)/2;
    int e=2*pos,d=2*pos+1;
    update(e,ini,m,p,q,val);
    update(d,m+1,fim,p,q,val);
    seg[pos].sum = seg[e].sum + seg[d].sum;
}
//Complexidade: O(log n)
ll query(int pos,int ini,int fim,int p,int q){
    propagate(pos,ini,fim);
    if(q<ini || p>fim) return 0;
    if(p<=ini && fim<=q) return seg[pos].sum;
    int m = (ini+fim)/2;
    int e=2*pos,d=2*pos+1;
    return query(e,ini,m,p,q) + query(d,m+1,fim,p,q);
}