//Antes de tudo fazer uma dfs para processar o size de cada subarvore
//Complexidade: O(n x logn)
void dfs_size(int v, int p){
    sze[v] = 1;
    for(int u: adj[v]){
        if(u != p){
            dfs_size(u,v);
            sze[v] += sze[u];
        }
    }
}

void dfs(int v, int p, bool keep) {
	int Max = -1, bigchild = -1;
	for (auto u : adj[v]) {
		if (u != p && Max < sze[u]) {
			Max = sze[u];
			bigchild = u;
		}
	}
	for (auto u : adj[v]) {
		if (u != p && u != bigchild) {
			dfs(u, v, 0);
		}
	}
	if (bigchild != -1) {
		dfs(bigchild, v, 1);
		swap(vec[v], vec[bigchild]);
	}
	vec[v].push_back(v);
	cnt[color[v]]++;
	for (auto u : adj[v]) {
		if (u != p && u != bigchild) {
			for (auto x : vec[u]) {
				cnt[color[x]]++;
				vec[v].push_back(x);
			}
		}
	}
	// existem cnt[c] vértices na subárvore v coloridos com c
	if (keep == 0) {
		for (auto u : vec[v]) {
			cnt[color[u]]--;
		}
	}
}