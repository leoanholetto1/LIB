//Fib(Fib(n)) mod m  = Fib(Fib(n) mod Pisano(m) ) mod m
//F(i)%mod = F(i)%pi(mod)
//Existe um resto zero até 6*n
//pi(n) <= 6*n
ll pisano(ll m){
    ll a = 1;
    ll b = 1;
    ll ans = 1;
    
    while (1){
        ll temp = b % m;
        b = (a + b) % m;
        a = temp;
        ++ans;
        
        if (a == 1 && b == 1) return ans - 1;
    }
}

ll fib(ll n, ll mod) {
    if (n <= 1) return n;
    ll a = 0;
    ll b = 1;
    ll i = 1ll << (63 - __builtin_clzll(n) - 1);
    for (; i; i >>= 1) {
      ll na = (__int128(a) * a % mod + __int128(b) * b % mod) % mod;
      ll nb = __int128(2ll * a + b) * b % mod;
      a = na;
      b = nb;
      if (n & i) {
        ll c = a + b; if (c >= mod) c -= mod;
        a = b;
        b = c;
      }
    }
    return b;
}

ll pisano_period(ll n) {
    auto v = PollardRho::factorize(n);
    map<ll, int> mp;
    for (auto x: v) {
      mp[x]++;
    }
    ll ans = 1;
    for (auto [p, e]: mp) {
      ll cur = pisano_period_prime(p);
      for (int i = 1; i < e; i++) {
        cur *= p;
      }
      ans = ans / __gcd(ans, cur) * cur;
    }
    return ans;
}

PollardRho::init();
cout << pisano_period(1000000007) << endl;