//Complexidade: O(n x log n)
int succ[maxN][20]; 
for (int i = 1; i <=20; i++) {
    for (int j = 1; j <=n; j++) {
        succ[j][i] = succ[succ[j][i-1]][i-1];
    }
}
//Complexidade: O(log n)
int lift(int x, int d) {
    int i = 0;
    while(d > 0) {
        if (d&1) 
            x = succ[x][i];
        d>>=1;
        i++;
    }
    return x;
}