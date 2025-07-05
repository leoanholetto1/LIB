//Hash = hs.get_hash(i, j)
//Hash string invertida = hs_inv.get_hash(n - j, n - i)


mt19937 rng((int) chrono::steady_clock::now().time_since_epoch().count()); // Random number generator
static long long P = uniform_int_distribution<int>(356, M1 - 1)(rng); // In case TL, use const
// Remember (alfabet < base < mod)
//Other large primes: 1000041323, 100663319, 201326611 , 1000015553, 1000028537
vector<int> bases = {37,61,79,83,97,53,61,
                         107,127,137,163,191 ,
                         199,211,229,239,263 ,
                         271,281,293 };      
vector<int> mods = {1000000007, 1000000009, 1000000433, 1000001329, 1000001927,
                    1000003051, 1000003253, 1000003397, 1000003579, 1000003751,
                    1000003793, 1000002043, 1000003967, 1000003987, 1000004123,
                    1000004843, 1000006129, 1000006961, 1000012253, 1000015271};
class Hashing {
private:
    const ll P = 31;
	const ll M1 = 1e9 + 7;
	const ll M2 = 1e9 + 9;
    vector<long long> base_pow, base_pow2, pref, pref2;

public:
    //Complexidade: O(n)
    Hashing(const string &s) {
        int a = s.size();
        base_pow.resize(a);
        base_pow2.resize(a);
        pref.resize(a + 1);
        pref2.resize(a + 1);

        base_pow[0] = 1;
        base_pow2[0] = 1;
        for (int i = 1; i < a; i++) {
            base_pow[i] = base_pow[i - 1] * P % M1;
            base_pow2[i] = base_pow2[i - 1] * P % M2;
        }

        pref[0] = pref2[0] = s[0];
        for (int i = 1; i < a; i++) {
            pref[i] = (pref[i - 1] * P + s[i]) % M1;
            pref2[i] = (pref2[i - 1] * P + s[i]) % M2;
        }
    }
    //Complexidade: O(1)
    long long get_hash(int l, int r) {
        if (l == 0) return (pref[r] << 30) ^ (pref2[r]);
        long long ret1 = ((pref[r] - (pref[l - 1] * base_pow[r - l + 1]) % M1 + M1) % M1);
        long long ret2 = ((pref2[r] - (pref2[l - 1] * base_pow2[r - l + 1]) % M2 + M2) % M2);
        return (ret1 << 30) ^ (ret2);
    }
};

//Tipo 2
const ll P = 31;
const ll M = 1e9 + 9;
const ll P2 = 53;
const ll M2 = 1e9 + 7;
vector<ll> base_pow(a);
set<pair<ll,ll>> se;
base_pow[0] = 1;
for (int i = 1; i < a; i++) { base_pow[i] = base_pow[i - 1] * P % M; }
vector<ll> pref(a + 1);
for (int i = 1; i <= a; i++) { pref[i] = (pref[i - 1] * P + s[i - 1]) % M; }
auto get_hash = [&](int l, int r) -> ll {
    ll h = pref[r + 1] - (base_pow[r - l + 1] * pref[l] % M) % M;
    return h < 0 ? h + M : h;
};
vector<ll> base_pow2(a);
base_pow2[0] = 1;
for (int i = 1; i < a; i++) { base_pow2[i] = base_pow2[i - 1] * P2 % M2; }
vector<ll> pref2(a + 1);
for (int i = 1; i <= a; i++) { pref2[i] = (pref2[i - 1] * P2 + s[i - 1]) % M2; }
auto get_hash2 = [&](int l, int r) -> ll {
    ll h = pref2[r + 1] - (base_pow2[r - l + 1] * pref2[l] % M2) % M2;
    return h < 0 ? h + M2 : h;
};
for(int i=0;i<a-b+1;i++){
    se.insert({get_hash(i,i+b-1),get_hash2(i,i+b-1)});
}