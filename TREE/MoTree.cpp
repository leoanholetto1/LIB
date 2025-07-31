//Observações: Cuidado quando o peso ta na aresta, como você passa o valor para o vértice debaixo 
//não é necessário processar o LCA, além disso quando a é ancestral de b, o interlavo comeã no start[a]+1.


vi adj[maxN], start(maxN), fim(maxN),val(maxN);
int depth[maxN];
int pai[maxN][21];
bool vis[maxN];
int ver[maxN];
int timer = 0;
int freq[maxN];
int dist=0;
vi v,v2;
int B=sqrt(maxN);

struct qry{
    int l,r,ix;
	int anc;
};

//Complexidade: O(1)
void add(int idx){
    int u = ver[idx]; // nó correspondente à posição idx no Euler Tour
    if(vis[u]){
        // já estava no conjunto, então vamos remover (segunda visita)
        int color = v[idx];
        freq[color]--;
        if(freq[color] == 0) dist--;
        vis[u] = false;
    } else {
        // ainda não estava no conjunto, então vamos adicionar
        int color = v[idx];
        if(freq[color] == 0) dist++;
        freq[color]++;
        vis[u] = true;
    }
}

//Complexidade: O(1)
int get_ans() {
    return dist;
}

//Complexidade: O(n x sqrt(n))
vector<int> mo(vector<qry> qs) {
    vector<int> ans (qs.size());
    sort(qs.begin(), qs.end(), [](qry a, qry b) {
        if (a.l/B != b.l/B) {
            return make_pair(a.l, a.r) < make_pair(b.l, b.r);
        }
        return (a.l/B) % 2 ? a.r < b.r : a.r > b.r;
    });
    int l = 0, r = -1;
    for (qry q : qs) {
        while (l > q.l) { l--; add(l); }
        while (r < q.r) { r++; add(r); }
        while (l < q.l) { add(l); l++; }
        while (r > q.r) { add(r); r--; }
		if (q.anc != -1) {
            int u = q.anc;
            int color = v[start[u]];
            if (freq[color] == 0) dist++;
            freq[color]++;
            ans[q.ix] = get_ans();
            freq[color]--;
            if (freq[color] == 0) dist--;
        } else {
            ans[q.ix] = get_ans();
        }
    }
    return ans;
}
//Complexidade: O(n) 
void euler_tour(int at, int prev) {
	v.pb(v2[at-1]);
	ver[timer] = at;
	start[at] = timer++;
	pai[at][0] = prev;
    for(int i = 1; i <= 20; i++){
        pai[at][i] = pai[pai[at][i-1]][i-1];
    }
	for (int n : adj[at]) {
		if (n != prev) { 
			depth[n] = depth[at] + 1;
			euler_tour(n, at); 
		}
	}
	v.pb(v2[at-1]);
	ver[timer] = at;
	fim[at] = timer++;
}
//Complexidade: O(log n)
int lca(int u, int v){
    if (depth[u] < depth[v]){
        swap(u, v);
    }
    for (int i = 20; i >= 0; i--)  
        if ((depth[u] - (1 << i)) >= depth[v])  
            u = pai[u][i];
 
    if (u == v)  
        return u;  
      
    for (int i = 20; i >= 0; i--)  
    {  
        if (pai[u][i] != pai[v][i])  
        {  
            u = pai[u][i];  
            v = pai[v][i];  
        }  
    }  
 
    return pai[u][0];  
}


void solve(){
	depth[1] = 0;
	euler_tour(1,0);
	vector<qry> v3;
    for(int i=0;i<q;i++){
        cin>>a>>b;
		int anc = lca(a,b);
		if(start[b] < start[a]) swap(a,b);
		if(anc==a) v3.pb({start[a],start[b],i,-1});
		else v3.pb({fim[a],start[b],i,anc});
    }
	vi rep = mo(v3);
	for(int i=0;i<rep.sz;i++) cout << rep[i] << endl;
}