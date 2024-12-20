//Complexidade: O(n x m)
long long bin[MAXN][MAXR];
void calcularCoefBin(int n, int k){
    int i, j;
    for (i = 0; i <= n; i++){
        for (j = 0; j <= min(i, k); j++){
            if (j == 0 || j == i) bin[i][j] = 1;
            else
            bin[i][j] = bin[i - 1][j - 1] + bin[i - 1][j];
        }
    }
}