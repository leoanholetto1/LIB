//Complexidade: O(n)
//Probabilida de colisão: 1/L ou 1-Q/L
//Serve para comparar coisas para comparar a[r]-a[l-1] = b[R]-b[L-1]
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
void precompute(){
    for (int i = 1; i <= n ;i++){
        h_val[i] = rng();
    }

    for (int i = 1; i <= n ;i++){
        a[i] = a[i - 1] + h_val[a[i]];
        b[i] = b[i - 1] + h_val[b[i]];
    }
}
