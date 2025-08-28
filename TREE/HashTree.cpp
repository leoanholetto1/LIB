//Pode ser usado para comparar árvores/subávores
//Complexidade: O(n x log n)
map<vi,int> mp;
vi  adj[maxN];
int idx = 0;
int n; 
int dfs(int s, int p) {
    vi v;
    for (auto i: adj[s]) {
        if (i != p) 
            v.push_back(dfs(i, s));
    }
    sort(v.begin(), v.end());
    if (!mp.count(v)) mp[v] = idx++;
    return mp[v];
}
