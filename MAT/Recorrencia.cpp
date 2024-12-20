//Complexidade: O(n^3 x log m)
struct Matrix {
    ll a[2][2] = {{0,0},{0,0}};
    Matrix() {}
    Matrix(ll a00, ll a01, ll a10, ll a11) {
        a[0][0] = a00;
        a[0][1] = a01;
        a[1][0] = a10;
        a[1][1] = a11;
    }
    Matrix operator *(const Matrix& other) {
        Matrix product;
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                for(int k=0;k<2;k++){
                    product.a[i][k] += a[i][j] * other.a[j][k];
                    product.a[i][k]%=mod;
                }
            }
        }
        return product;
    }
};

Matrix expo_power(Matrix a, ll k) {
    Matrix product;
    for(int i=0;i<2;i++) 
        product.a[i][i] = 1;
    while(k > 0) {
        if(k % 2) {
            product = product * a;
        }
        a = a * a;
        k /= 2;
    }
    return product;
}


long long fib(long long n){
    Matrix single(0,1,l,k);
    single = expo_power(single, n);
    return single.a[0][1];
}