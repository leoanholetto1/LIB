//Complexidade: O(log n)
ll modInverse(ll A, ll M){
    ll m0 = M;
    ll y = 0, x = 1;
    if (M == 1)
     return 0;
    while (A > 1) {
        ll q = A / M;
        ll t = M;
        M = A % M, A = t;
        t = y;
        y = x - q * y;
        x = t;
    }
    if (x < 0)
        x += m0;
    return x;
}

//Se M for primo
ll power(ll x, ll y,ll M){
    if (y == 0)
        return 1;
    int p = power(x, y / 2, M) % M;
    p = (p * p) % M;
    return (y % 2 == 0) ? p : (x * p) % M;
}

void modInverse(ll A, ll M){
    int g = gcd(A, M);
    if (g != 1)
        cout << "-1";
    else {
        cout <<  power(A, M - 2, M);
    }
}