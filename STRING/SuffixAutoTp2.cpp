struct sam {
	int cur, sz, len[2*MAX], link[2*MAX], acc[2*MAX];
	int nxt[2*MAX][26];
	//Complexidade: O(n)
	void add(int c) {
		int at = cur;
		len[sz] = len[cur]+1, cur = sz++;
		while (at != -1 and !nxt[at][c]) nxt[at][c] = cur, at = link[at];
		if (at == -1) { link[cur] = 0; return; }
		int q = nxt[at][c];
		if (len[q] == len[at]+1) { link[cur] = q; return; }
		int qq = sz++;
		len[qq] = len[at]+1, link[qq] = link[q];
		for (int i = 0; i < 26; i++) nxt[qq][i] = nxt[q][i];
		while (at != -1 and nxt[at][c] == q) nxt[at][c] = qq, at = link[at];
		link[cur] = link[q] = qq;
	}
	//Complexidade: O(n)
	void build(string& s) {
		cur = 0, sz = 0, len[0] = 0, link[0] = -1, sz++;
		for (auto i : s) add(i-'a');
		int at = cur;
		while (at) acc[at] = 1, at = link[at];
	}

	//Complexidade: O(n)
	// coisas que da pra fazer:
	ll distinct_substrings() {
		ll ans = 0;
		for (int i = 1; i < sz; i++) ans += len[i] - len[link[i]];
		return ans;
	}
	string longest_common_substring(string& S, string& T) {
		build(S);
		int at = 0, l = 0, ans = 0, pos = -1;
		for (int i = 0; i < T.size(); i++) {
			while (at and !nxt[at][T[i]-'a']) at = link[at], l = len[at];
			if (nxt[at][T[i]-'a']) at = nxt[at][T[i]-'a'], l++;
			else at = 0, l = 0;
			if (l > ans) ans = l, pos = i;
		}
		return T.substr(pos-ans+1, ans);
	}
	ll dp[2*MAX];
	ll paths(int i) {
		auto& x = dp[i];
		if (x) return x;
		x = 1;
		for (int j = 0; j < 26; j++) if (nxt[i][j]) x += paths(nxt[i][j]);
		return x;
	}
	void kth_substring_distinta(int k, int at=0) { // k=1 : menor substring lexicog.
		for (int i = 0; i < 26; i++) if (k and nxt[at][i]) {
			if (paths(nxt[at][i]) >= k) {
				cout << char('a'+i);
				kth_substring_distinta(k-1, nxt[at][i]);
				return;
			}
			k -= paths(nxt[at][i]);
		}
	}
	ll calc(int i=0) {
		auto& x = dp[i];
		if (x) return x;
		x = ctn[i];
		for (int j = 0; j < 26; j++) if (nxt[i][j]) x += calc(nxt[i][j]);
		return x;
	}
	void update_cnts(){
		vi aux[sz];
		for(int i = 0; i < sz; i++)
			aux[len[i]].pb(i);
		for(int i = sz-1; i >= 0; i--)
			for(int u :aux[i])
				if(linke[u] != -1)
					ctn[linke[u]] += ctn[u];
	}
	void kth_substring_(ll k, int at=0) { 
		if(k < 0) return ;
		for (int i = 0; i < 26; i++) 
			if (k and nxt[at][i]) {
				if (dp[nxt[at][i]] >= k) {
					cout << char('a'+i);
					kth_substring(k-ctn[nxt[at][i]], nxt[at][i]);
					return ;
				}
				k -= dp[nxt[at][i]];
			}
	}
};