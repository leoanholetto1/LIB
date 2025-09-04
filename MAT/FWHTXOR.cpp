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