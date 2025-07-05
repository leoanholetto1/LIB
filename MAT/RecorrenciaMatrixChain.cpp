struct Matrix {
    ll a[3][3] = {{0,0,0},{0,0,0},{0,0,0}};
    Matrix(bool flag) {
		if(flag) {
			a[0][1]  = a[1][2] = a[2][0] = a[2][1] = 1;
		}
	}
	Matrix() {
	}
    Matrix operator *(const Matrix& other) {
        Matrix product;
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                for(int k=0;k<3;k++){
                    product.a[i][k] += a[i][j] * other.a[j][k];
                    product.a[i][k]%=mod;
                }
            }
        }
        return product;
    }
};

Matrix expo_power(Matrix a, ll k) {
    Matrix product(0);
    for(int i=0;i<3;i++) 
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
	if(n==0) return 0;
    Matrix single(1);
    single = expo_power(single, n);
	ll arr[3][1] = {{0},{1},{1}};  // f(0),f(1),f(2)
	ll ans[3][1] = {{0}, {0}, {0}}; //f(n),(f+1),f(n+2)
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			for(int k=0;k<1;k++){
				ans[i][k] += single.a[i][j] * arr[j][k];
				ans[i][k]%=mod;
			}
		}
	}
    return ans[0][0];
}