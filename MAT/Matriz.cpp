struct Matrix {
	ll a[6][6];
	int t=6;
	Matrix() {
		memset(a,0,sizeof(a));
		t = 6;
	}
	Matrix(int n) {
		memset(a,0,sizeof(a));
		t = n;
	}
	Matrix(int n,int k) {
		memset(a,k,sizeof(a));
		t = n;
	}
	Matrix operator *(const Matrix& other) {
		Matrix product(t);
		for(int i=0;i<t;i++){
			for(int j=0;j<t;j++){
				for(int k=0;k<t;k++){
					product.a[i][k] += a[i][j] * other.a[j][k];
					product.a[i][k]%=mod;
				}
			}
		}
		return product;
	}
	Matrix operator +(const Matrix& other) {
		Matrix product(t);
		for(int i=0;i<t;i++){
			for(int j=0;j<t;j++){
				for(int k=0;k<t;k++){
					product.a[i][k] = a[i][j] + other.a[j][k];
				}
			}
		}
		return product;
	}
};
