void fwht_and(vi &a) {
    int n = a.size();
    for (int s = 2, h = 1; s <= n; s <<= 1, h <<= 1)
        for (int l = 0; l < n; l += s)
            for (int i = 0; i < h; i++)
                a[l + i] += a[l + h + i];
}

void ifwht_and(vi &a) {
    int n = a.size();
    for (int s = 2, h = 1; s <= n; s <<= 1, h <<= 1)
        for (int l = 0; l < n; l += s)
            for (int i = 0; i < h; i++)
                a[l + i] -= a[l + h + i];
}

vi conv_and(const vi &a, const vi &b) {
    int n = max(a.size(), b.size());
    int sze = 1;
    while (sze < n) sze <<= 1;

    vi A = a, B = b;
    A.resize(sze);
    B.resize(sze);

    fwht_and(A);
    fwht_and(B);

    for (int i = 0; i < sze; i++) A[i] *= B[i];

    ifwht_and(A);
    return A;
}
