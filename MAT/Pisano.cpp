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

ll pisano_period_prime(ll p) {
  if (p == 2) return 3;
  if (p == 5) return 20;
  ll x = p % 5 == 1 or p % 5 == 4 ? p - 1 : 2 * p + 2;
  auto v = PollardRho::factorize(x);
  map<ll, int> mp;
  for (auto x: v) {
    mp[x]++;
  }
  vector<ll> d;
  d.push_back(1);
  for (auto [p, e]: mp) {
    ll cur = 1;
    int sz = d.size();
    for (int i = 0; i < e; i++) {
      cur *= p;
      for (int j = 0; j < sz; j++) {
        d.push_back(d[j] * cur);
      }
    }
  }
  sort(d.begin(), d.end());
  for (auto x: d) {
    if (fib(x, p) == 0 and fib(x + 1, p) == 1) {
      return x;
    }
  }
  assert(0);
  return -1;
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