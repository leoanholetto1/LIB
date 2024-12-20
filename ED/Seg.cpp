class  Seg{
private:
    vi tree;
public:
    Seg(int n){
        tree.resize(4*n);
    }
    //Complexidade: O(n)
    void build(int pos,int i,int f){
        if(i==f){
            tree[pos] = v[i];
            return ;
        }
        int m = (i+f)/2;
        int e = 2*pos, d = 2*pos +1;
        build(e,i,m);
        build(d,m+1,f);
        tree[pos] = min(tree[e],tree[d]);
    }
    //Complexidade: O(log n)
    void update(int pos,int ini,int fim,int id,int val){
        if(id<ini || id>fim) return ;
        if(ini==fim){
            tree[pos] = val;
            return ;
        }
        int m = (ini+fim)/2;
        int e = 2*pos, d = 2*pos +1;
        update(e,ini,m,id,val);
        update(d,m+1,fim,id,val);
        tree[pos] = min(tree[e],tree[d]);
    }
    //Complexidade: O(log n)
    int queryMin(int pos,int ini,int fim,int a,int b){
        if(b<ini || a>fim) return INT_MAX;
        if(a<=ini && fim<=b) return tree[pos];
        int m = (ini+fim)/2;
        int e = 2*pos, d = 2*pos+1;
        return min(queryMin(e,ini,m,a,b), queryMin(d,m+1,fim,a,b));
    }
};
