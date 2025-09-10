// Complexidade: O(n) - Lehmer Code
ll permToInt(const vi& v) {
    ll use = 0, r = 0;
    int i = 0;
    for (int x : v) {
        r = r * ++i + __builtin_popcountll(use & -(1LL << x));
        use |= 1LL << x;
    }
    return r;
}

// Converte a permutacao p para Lehmer Code(1-indexado)
//Complexidade: O(n log n)
vector<int> permToLehmer(const vector<int>& p) {
    int n = p.size();
    vector<int> code(n, 0);
    set<int> s;  

    for (int i = 0; i < n; i++) s.insert(i+1);  

    for (int i = 0; i < n; i++) {
        auto it = s.lower_bound(p[i]);
        code[i] = distance(s.begin(), it); 
        s.erase(it);
    }
    return code;
}

// Converte Lehmer Code para posicao lexicografica(começando de 0)
//Complexidade: O(n)
ll lehmerToIndex(const vector<int>& code) {
    int n = code.size();
    ll fact = 1;
    ll idx = 0;
    for (int i = n-1; i >= 0; i--) {
        idx += code[i] * fact;
        fact *= (n - i);
    }
    return idx;
}

//Converte a posicao da permutacao para permutacao original(1-indexed)
//O array gerado eh 0-indexado
//Complexidade: O(n^2)
vi intToPerm(int n, ll k) {
    k--; // se o índice começa em 1
    std::vector<ll> fact(n);
    fact[0] = 1;
    for (int i = 1; i < n; i++) fact[i] = fact[i-1] * i;

    vi perm;
    vi nums(n);
    std::iota(nums.begin(), nums.end(), 0);

    for (int i = n-1; i >= 0; i--) {
        ll idx = k / fact[i];
        perm.push_back(nums[idx]);
        nums.erase(nums.begin() + idx);
        k %= fact[i];
    }
    return perm;
}