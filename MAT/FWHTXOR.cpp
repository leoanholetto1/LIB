//No caso de contar todos subarray xor, use o array freq[preix_xor] e faça a convolução com ele mesmo. Alem disso, trate o zero separado.

void fwht_xor(vector<int> &a) {
    int n = a.size();
    for (int s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
        for (int l = 0; l < n; l += s) {
            for (int i = 0; i < h; i++) {
                int t = a[l + h + i];
                a[l + h + i] = a[l + i] - t;
                a[l + i] += t;
            }
        }
    }
}

void ifwht_xor(vector<int> &a) {
    int n = a.size();
    for (int s = 2, h = 1; s <= n; s <<= 1, h <<= 1) {
        for (int l = 0; l < n; l += s) {
            for (int i = 0; i < h; i++) {
                int t = a[l + h + i];
                a[l + h + i] = (a[l + i] - t) / 2;
                a[l + i] = (a[l + i] + t) / 2;
            }
        }
    }
}

vector<int> conv_xor(vector<int> a, vector<int> b) {
    int n = 1;
    while (n < (int)max(a.size(), b.size())) n <<= 1;
    n <<= 1; 
    a.resize(n);
    b.resize(n);
    
    fwht_xor(a);
    fwht_xor(b);
    for (int i = 0; i < n; i++) a[i] *= b[i];
    ifwht_xor(a);
    return a;
}

//Tem a segunda, por que a primeira ja me enganou em alguns problemas!
void fwht_xor(vt<ll> &a) {
    int n = a.size();
    for(int len = 2; len <= n; len <<= 1){
        for(int i = 0; i < n; i += len){
            for(int j = 0; j < len/2; j++){
                ll u = a[i + j], v = a[i + j + len/2];
                a[i + j] = u + v;
                a[i + j + len/2] = u - v;
            }
        }
    }
}
 
void ifwht_xor(vt<ll> &a) {
    int n = a.size();
    for(int len = 2; len <= n; len <<= 1){
        for(int i = 0; i < n; i += len){
            for(int j = 0; j < len/2; j++){
                ll u = a[i + j], v = a[i + j + len/2];
                a[i + j] = (u + v) / 2;
                a[i + j + len/2] = (u - v) / 2;
            }
        }
    }
}