//FFT de bits
//Pode ser usado para gerar todas somas xor de um array
//Obs: As operações de bits podem representar operaçõs de conjunto
//Complexidade: O(n x logn)

void fwht_or(vi &a) {
    int n = a.size();
    for (int s = 2, h = 1; s <= n; s <<= 1, h <<= 1)
        for (int l = 0; l < n; l += s)
            for (int i = 0; i < h; i++)
                a[l + h + i] += a[l + i];
}

void ifwht_or(vi &a) {
    int n = a.size();
    for (int s = 2, h = 1; s <= n; s <<= 1, h <<= 1)
        for (int l = 0; l < n; l += s)
            for (int i = 0; i < h; i++)
                a[l + h + i] -= a[l + i];
}

vi conv_or(const vi &a, const vi &b) {
    int n = max(a.size(), b.size());
    int sze = 1;
    while (sze < n) sze <<= 1;

    vi A = a, B = b;
    A.resize(sze);
    B.resize(sze);

    fwht_or(A);
    fwht_or(B);

    for (int i = 0; i < sze; i++) A[i] *= B[i];

    ifwht_or(A);
    return A;
}


