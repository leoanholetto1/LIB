//Complexidade: O(log n)
void multiply(ll F[2][2], ll M[2][2]) {
    ll x = ((F[0][0] * M[0][0])%P + (F[0][1] * M[1][0])%P)%P;
    ll y = ((F[0][0] * M[0][1])%P + (F[0][1] * M[1][1])%P)%P;
    ll z = ((F[1][0] * M[0][0])%P + (F[1][1] * M[1][0])%P)%P;
    ll w = ((F[1][0] * M[0][1])%P + (F[1][1] * M[1][1])%P)%P;
    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}

void power(ll F[2][2], ll n){
    if (n == 0 || n == 1)
        return;
    ll M[2][2] = { { 1LL, 1LL }, { 1LL, 0 } };
 
    power(F, n / 2);
    multiply(F, F);
    if (n % 2 != 0)
        multiply(F, M);
}

ll fib(ll n){
    ll F[2][2] = { { 1LL, 1LL }, { 1LL, 0 } };
    if (n == 0)
        return 0;
    power(F, n - 1);
    return F[0][0];
}