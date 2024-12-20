struct VeniceSet {
	multiset<ll> S;
	ll water_level = 0;
	//Complexidade: O(log n)
	void add(ll v) {
		S.insert(v - water_level);
	}
	//Complexidade: O(log n)
	void remove(ll v) {
		S.erase(S.find(v - water_level));
	}
	//Complexidade: O(1)
	void updateAll(ll v) {
		water_level += v;
	}
	//Complexidade: O(1)
	ll getMin() {
		return *S.begin() + water_level;
	}
	//Complexidade: O(1)
	ll size() {
		return S.size();
	}
};