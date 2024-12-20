ll seg[4*maxN];
//Complexidade: O(log n)
void update(int pos,int ini,int fim,int p,int q,int val){
    if(q<ini || p>fim) return ;
    if(p<=ini && fim<=q){
        seg[pos]+=val;
        return ;
    }
    int m = (ini+fim)/2;
    int e = 2*pos, d =2*pos+1;
    update(e,ini,m,p,q,val);
    update(d,m+1,fim,p,q,val);
}
//Complexidade: O(log n)
ll query(int pos,int ini,int fim,int id){
    if(id<ini || id>fim) return 0;
    if(ini==fim) return seg[pos];
    int m = (ini+fim)/2;
    int e = 2*pos, d=2*pos+1;
    if(id<=m) return seg[pos] + query(e,ini,m,id);
    else return seg[pos] + query(d,m+1,fim,id);
}