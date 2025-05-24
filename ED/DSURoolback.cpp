//Complexidade: O(log  n)
struct DSU {
	vector<int> p, sz;
	vector<pair<int, int>> past_parent, past_size;
    //Complexidade: O(n)
	DSU(int n) {
		p.resize(n);
		sz.resize(n, 1);
		iota(p.begin(), p.end(), 0);
	}

	int get(int x) { return (p[x] == x) ? x : get(p[x]); }

	void unite(int a, int b) {
		a = get(a);
		b = get(b);
		if (sz[a] < sz[b]) { swap(a, b); }
		past_parent.push_back({b, p[b]});
		past_size.push_back({a, sz[a]});

		if (a != b) {
			p[b] = a;
			sz[a] += sz[b];
		}
	}

	bool sameset(int a, int b) { return get(a) == get(b); }

	void rollback() {
		p[past_parent.back().first] = past_parent.back().second;
		sz[past_size.back().first] = past_size.back().second;
		past_parent.pop_back();
		past_size.pop_back();
	}
};
