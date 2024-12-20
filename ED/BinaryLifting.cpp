//Complexidade: O(n x log n)
int pai[maxN][32]; 
void preprocess(int n){
    for(int i = 1; i <= 30; i++){
        for(int u=0;u<n;u++){
            pai[u][i] = pai[pai[u][i-1]][i-1];
        }
    }
}
//Complexidade: O(log n)
int query(int a,int b){
    for(int i=30;i>=0;i--){
        if(b&(1<<i)){
            a = pai[a][i];
        }
    }
    return a;
}