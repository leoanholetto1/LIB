//Complexidade: O(m log n)
//Observações: Essa dominator esta indexada em 1, só trocar o inicio das dfs
//Dominator: Um nó que está em todos os caminhos de u->v
//Obs: 0-indexado

int n;

struct d_tree {
    //Grafo original
	vector<int> g[maxN];

	//dominator tree
	vector<int> tree[maxN];
	int dfs_l[maxN], dfs_r[maxN];

	//Auxiliar
	vector<int> rg[maxN], bucket[maxN];
	int idom[maxN], sdom[maxN], prv[maxN], pre[maxN];
	int ancestor[maxN], label[maxN];
	vector<int> preorder;
    vi ans;
    int dest;

	void dfs(int v) {
		static int t = 0;
		pre[v] = ++t;
		sdom[v] = label[v] = v;
		preorder.push_back(v);
		for (int nxt: g[v]) {
			if (sdom[nxt] == -1) {
				prv[nxt] = v;
				dfs(nxt);
			}
			rg[nxt].push_back(v);
		}
	}
	int eval(int v) {
		if (ancestor[v] == -1) return v;
		if (ancestor[ancestor[v]] == -1) return label[v];
		int u = eval(ancestor[v]);
		if (pre[sdom[u]] < pre[sdom[label[v]]]) label[v] = u;
		ancestor[v] = ancestor[u];
		return label[v];
	}
	void dfs2(int v) {
		static int t = 0;
		dfs_l[v] = t++;
		for (int nxt: tree[v]) dfs2(nxt);
		dfs_r[v] = t++;
	}
	void build(int s) {
		for (int i = 0; i < n; i++) {
			sdom[i] = pre[i] = ancestor[i] = -1;
			rg[i].clear();
			tree[i].clear();
			bucket[i].clear();
		}
		preorder.clear();
		dfs(s);
		if (preorder.size() == 1) return;
		for (int i = int(preorder.size()) - 1; i >= 1; i--) {
			int w = preorder[i];
			for (int v: rg[w]) {
				int u = eval(v);
				if (pre[sdom[u]] < pre[sdom[w]]) sdom[w] = sdom[u];
			}
			bucket[sdom[w]].push_back(w);
			ancestor[w] = prv[w];
			for (int v: bucket[prv[w]]) {
				int u = eval(v);
				idom[v] = (u == v) ? sdom[v] : u;
			}
			bucket[prv[w]].clear();
		}
		for (int i = 1; i < preorder.size(); i++) {
			int w = preorder[i];
			if (idom[w] != sdom[w]) idom[w] = idom[idom[w]];
			tree[idom[w]].push_back(w);
		}
		idom[s] = sdom[s] = -1;
		dfs2(s);
	}

	//Dado um raiz verifica se todo caminho de s até v passa por u, antes de usar execute a dfs2 passando s.
	bool dominates(int u, int v) {
		if (pre[v] == -1) return 1; 
		return dfs_l[u] <= dfs_l[v] && dfs_r[v] <= dfs_r[u];
	}

    //Recupera todos dominator no caminho de u até v
    //Obs: Não esquecer de setar o dest.
    bool dfs_dom(int u=0,int p=-1){
        bool flag = (u==dest);
        for(auto v: tree[u]){
            if(v == p) continue;
            flag|=dfs_dom(v,u);
        }
        if(flag) ans.pb(u);
        return flag;
    }
};