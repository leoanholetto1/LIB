class DSU{
    int pai[maxN];
    int tam[maxN];
    int his[maxN];
    int n;
    //Complexidade: O(n)
    void init(){
        for(int i=1;i<=n;i++){
            pai[i] = i;
            tam[i] = 0;
            his[i] = 0;
        }
    }
    //Complexidade: O(1)
    int find(int x,int t){
        if(pai[x]==x) return x;
        if(his[x] > t) return x;
        return find(pai[x],t);
    }
    //Complexidade: O(1)
    void merge(int u,int v,int t){
        int a = find(u,t);
        int b = find(v,t);
        if (a == b)
            return ;
        if (tam[a] < tam[b]) {
            pai[a] = b;
            his[a] = t;
        }
        else if (tam[a] > tam[b]) {
            pai[b] = a;
            his[b] = t;
        }
        else {
            pai[b] = a;
            tam[a] = tam[b] + 1;
            his[b] = t;
        }
    }
}
