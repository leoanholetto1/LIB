//Complexidade: O(m * sqrt(n))
//Complexidade: O(m * sqrt(n))
struct BipartiteMatcher {
    int n, m;
    vector<vector<int>> adj;
    vector<int> dist, matchL, matchR;
    vector<bool> visL, visR;
    vi grau,pai;

    BipartiteMatcher(int _n, int _m) : n(_n), m(_m) {
        adj.resize(n + 1);
        dist.assign(n + 1, 0);
        matchL.assign(n + 1, 0);
        matchR.assign(m + 1, 0);
        pai.assign(n + 1, 0);
        grau.assign(n + 1, 0);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }

    bool bfs() {
        queue<int> q;
        for (int i = 1; i <= n; ++i) {
            if (matchL[i] == 0) {
                dist[i] = 0;
                q.push(i);
            } else {
                dist[i] = INF;
            }
        }
        dist[0] = INF;

        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (dist[u] < dist[0]) {
                for (int v : adj[u]) {
                    if (dist[matchR[v]] == INF) {
                        dist[matchR[v]] = dist[u] + 1;
                        q.push(matchR[v]);
                    }
                }
            }
        }
        return dist[0] != INF;
    }

    bool dfs(int u) {
        if (u == 0) return true;
        for (int v : adj[u]) {
            if (dist[matchR[v]] == dist[u] + 1) {
                if (dfs(matchR[v])) {
                    matchL[u] = v;
                    matchR[v] = u;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }

    int max_matching() {
        int matching = 0;
        while (bfs()) {
            for (int i = 1; i <= n; ++i) {
                if (matchL[i] == 0 && dfs(i))
                    ++matching;
            }
        }
        return matching;
    }

    void print_matching() {
        for (int i = 1; i <= n; ++i) {
            if (matchL[i]){
                pai[matchL[i]] = i;
                grau[i]++;
            }
        }
    }

    void dfs_cover(int u) {
        visL[u] = true;
        for (int v : adj[u]) {
            if (!visR[v] && matchL[u] != v) {
                visR[v] = true;
                if (matchR[v] && !visL[matchR[v]])
                    dfs_cover(matchR[v]);
            }
        }
    }

    void min_vertex_cover() {
        visL.assign(n + 1, false);
        visR.assign(m + 1, false);

        for (int i = 1; i <= n; ++i) {
            if (matchL[i] == 0) {
                dfs_cover(i);
            }
        }

        vector<int> coverL, coverR;

        for (int i = 1; i <= n; ++i) {
            if (!visL[i]) coverL.push_back(i);
        }
        for (int i = 1; i <= m; ++i) {
            if (visR[i]) coverR.push_back(i);
        }
        cout << coverL.size();
        for (int x : coverL) cout << " " << x;
        cout << "\n";
        cout <<  coverR.size();
        for (int x : coverR)  cout << " " << x;
        cout << "\n";
    }

    void minimum_path_cover(){
        int ans = max_matching();
        cout << n-ans << endl;
        print_matching();
        for(int i=1;i<=n;i++){
            if(grau[i]==0){
                vi path;
                int aux=i;
                while(aux!=-1){
                    path.pb(aux);
                    aux = pai[aux];
                }
                reverse(all(path));
                for(int j=0;j<path.sz;j++){
                    if(j!=0) cout <<" ";
                    cout << path[j];
                }
                cout << endl;
            }
        }
    }
};