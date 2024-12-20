//Complexidade: O(n x log n)
void computaMinimo() {
    for (int i = 1; i <= n; i++)
        tab[i][0] = v[i];
    for (int j = 1; j <= log_n; j++) {
        for (int i = 1; i <= n; i++) {
            if (i + (1<<j) - 1 > n) break;
            tab[i][j]=min(tab[i][j-1],tab[i + (1<<(j-1))][j-1]);
        }
    }
}
int flog(int x) {
    return 31 - __builtin_clz(x);
}

int flog(long long x) { 
    return 63 - __builtin_clzll(x);
}
//Complexidade: O(1)
int query(int l, int r) {
    int k = flog(r - l + 1);
    return min(tab[l][k], tab[r - (1<<k) + 1][k]);
}
//Complexidade: O(n x log n)
void build(){
    for (int i = 1; i <= n; i++)
		tab[i][0] = v[i];
    for (int j = 1; j <= log_n; j++) {
        for (int i = 1; i <= n; i++) {
            if (i + (1<<j) - 1 > n) break;
            tab[i][j] =f(tab[i][j-1], tab[i + (1<<(j-1))][j-1]);
        }
    }
}
//Complexidade: O(log n)
int query(int l,int r){
    int acc = ele_neutro;
    for(int i=log_n;i>=0;i--){
        if((1<<i) <= r-l+1){
            acc = f(acc,tab[l][i]);
            l+=(1<<i);
        }
    }
    return acc;
}