class Hashing {
private:
    const ll P = 69420;
    const ll M = 1e9 + 9;
    vector<long long> base_pow, pref;

public:
    //Complexidade: O(n)
    Hashing(const string &s) {
        int a = s.size();
        base_pow.resize(a);
        pref.resize(a + 1);
        base_pow[0] = 1;
        for (int i = 1; i < a; i++) {
            base_pow[i] = base_pow[i - 1] * P % M1;
        }
        pref[0]  = s[0];
        for (int i = 1; i < a; i++) {
            pref[i] = (pref[i - 1] * P + s[i]) % M1;
        }
    }
    //Complexidade: O(1)
    long long get_hash(int l, int r) {
        if (l == 0) return pref[r];
        long long ret1 = ((pref[r] - (pref[l - 1] * base_pow[r - l + 1]) % M1 + M1) % M1);
        return ret1;
    }
};