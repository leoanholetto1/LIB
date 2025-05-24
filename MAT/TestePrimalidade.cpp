//Complexidade: O(sqrt(n))
bool primo(ll n){
    for(ll i=2; i*i<=n;i++){
        if(n%i==0) return 0;
    }
    return 1;
}

//Miler Rabin
//Complexidade: O(k x log n)
//Probabilidade: 1 - (1/4)^k
int power(int x, unsigned int y, int p){
    int res = 1;
    x = x % p; 
    while (y > 0){
        if (y & 1)
            res = (res*x) % p;
        y = y>>1; 
        x = (x*x) % p;
    }
    return res;
}
 
bool miillerTest(int d, int n){
    int a = 2 + rand() % (n - 4);
    int x = power(a, d, n);
    if (x == 1  || x == n-1)
       return true;
    while (d != n-1){
        x = (x * x) % n;
        d *= 2;
        if (x == 1)      return false;
        if (x == n-1)    return true;
    }
    return false;
}
 
// It returns false if n is composite and returns true if n
// is probably prime.  k is an input parameter that determines
// accuracy level. Higher value of k indicates more accuracy.
bool isPrime(int n, int k){
    if (n <= 1 || n == 4)  return false;
    if (n <= 3) return true;
    int d = n - 1;
    while (d % 2 == 0)
        d /= 2;
    for (int i = 0; i < k; i++)
         if (!miillerTest(d, n))
              return false;
    return true;
}

//Miler Rabin Deterministico n < 2^64
//Complexidade: O(k x log n)
bool check_composite(ll n, ll a, ll d, int s) {
    ll x = power(a, d, n);
    if (x == 1 || x == n - 1)
        return false;
    for (int r = 1; r < s; ++r) {
        x = mulmod(x, x, n);
        if (x == n - 1)
            return false;
    }
    return true;
}

bool is_prime(u64 n) {
    if (n < 2)
        return false;
    int s = 0;
    ll d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        ++s;
    }
    vector<ll> bases = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    for (ll a : bases) {
        if (a >= n)
            break;
        if (check_composite(n, a, d, s))
            return false;
    }
    return true;
}