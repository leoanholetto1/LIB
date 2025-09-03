//Complexidade: O(n x logn) -> como um todo 

int get_subtree_size(int node, int parent = -1) {
	subtree_size[node] = 1;
	for (int child : adj[node]) {
		if (child == parent || is_removed[child]) { continue; }
		subtree_size[node] += get_subtree_size(child, node);
	}
	return subtree_size[node];
}
 
int get_centroid(int node, int tree_size, int parent = -1) {
	for (int child : adj[node]) {
		if (child == parent || is_removed[child]) { continue; }
		if (subtree_size[child] * 2 > tree_size) {
			return get_centroid(child, tree_size, node);
		}
	}
	return node;
}
 
void dfs(int u,int d,int p=-1){
	if(d > k) return ;
	path.push_back(d);
	mx = max(mx,d);
	for(auto v: adj[u]){
		if(v == p or is_removed[v]) continue;
		dfs(v,d+1,u);
	}
}

void build_centroid_decomp(int node = 0) {
	int centroid = get_centroid(node, get_subtree_size(node));
	is_removed[centroid] = true;
	mx = 0;
	dist[0] = 1;
	for (int child : adj[centroid]) {
		if (is_removed[child]) { continue; }
        path.clear();
		dfs(child,1,0);
		for (int d : path)
			sum += dist[k-d];
		for (int d : path) dist[d]++;
	}
 
	fill(dist.begin(),dist.begin()+mx+1,0);

	for (int child : adj[centroid]) {
		if (is_removed[child]) { continue; }
		build_centroid_decomp(child);
	}
}

