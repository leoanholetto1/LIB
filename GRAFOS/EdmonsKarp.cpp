#include <bits/stdc++.h>
#define fore(i,a,b) for(int i = (a); i<(b); i++)
#define _ ios_base::sync_with_stdio(0); cin.tie(0);
#define all(s) begin(s),end(s)
#define sz(s) int(s.size())
#define ENDL '\n'
using namespace std;
typedef long long lli;
 
lli INF = 1000000000000000;
 
struct Dinic{
    int nodes, src, dst;
    vector<int> dist, q, work;
    struct edge{int to, rev; lli f, cap;};
    vector<vector<edge>> g;
    Dinic(int x): nodes(x), g(x), dist(x), q(x), work(x){}
 
    void add_edge(int s, int t, lli cap){
        g[s].push_back((edge){t, sz(g[t]), 0, cap});
        g[t].push_back((edge){s, sz(g[s]) - 1, 0, 0});
    }
 
    bool dinic_bfs(){
        fill(all(dist), -1); dist[src] = 0;
        int qt = 0; q[qt++] = src;
        for(int qh = 0; qh < qt; qh++){
            int u = q[qh];
            fore(i, 0, sz(g[u])){
                edge &e = g[u][i];
                int v = g[u][i].to;
                if(dist[v]<0 and e.f < e.cap) dist[v] = dist[u]+1, q[qt++] = v;
            }
        }
        return dist[dst]>=0;
    }
 
    lli dinic_dfs(int u, lli f){
        if(u == dst) return f;
        for(int &i = work[u]; i<sz(g[u]); i++){
            edge &e = g[u][i];
            if(e.cap <= e.f) continue;
            int v = e.to;
            if(dist[v] == dist[u]+1){
                lli df = dinic_dfs(v, min(f, e.cap - e.f));
                if(df>0){
                    e.f += df;
                    g[v][e.rev].f-= df;
                    return df;
                }
            }
        }
        return 0;
    }
 
    lli max_flow(int _src, int _dst){
        src = _src, dst = _dst;
        lli result = 0;
        while(dinic_bfs()){
            fill(all(work), 0);
            while(lli delta = dinic_dfs(src, INF)) result += delta;
        }
        return result;
    }
 
    void ans(int NN){
        vector<pair<int, int>> ho, ve;
        for(int i = 1; i<=NN; i++){
            for(int j = 1; j<=NN; j++){
                if((i & 1) and !(j & 1)) continue;
                if(!(i & 1) and (j & 1)) continue;
                
                int nm = (NN * (i-1)) + j;
                for(int k = 0; k<sz(g[nm]); k++){
                    int other = g[nm][k].to;
                    if(other == src or other == dst) continue;
                    if(g[nm][k].f == 1){
                        if(other == nm + 1){ // izq
                            ve.push_back({i, j});
                        }
                        else if(other == nm - 1){ // der
                            ve.push_back({i, j-1});
                        }
                        else if(other < nm){ // abajo
                            ho.push_back({i-1, j});
                        }
                        else{ // arriba
                            ho.push_back({i, j});
                        }
                    }
                }
            }
        }
        cout << sz(ho) << ENDL;
        for(auto e: ho) cout << e.first << " " << e.second << ENDL;
        cout << sz(ve) << ENDL;
        for(auto e: ve) cout << e.first << " " << e.second << ENDL;
    }
};
 
vector<int> movx = {0, -1, 0, 1};
vector<int> movy = {-1, 0, 1, 0};
 
int main(){_
    int N, P; cin >> N >> P;
    Dinic mitim(N * N + 5);
    int src = 0, dst = N * N + 2;
    set<int> remov;
    for(int i = 0; i<P; i++){
        int x, y; cin>>x>>y;
        int cell = (N * (x-1)) + y;
        remov.insert(cell);
    }
 
    for(int i = 1; i<=N; i++){
        for(int j = 1; j<=N; j++){
            int num = (N * (i-1)) + j;
            if(remov.count(num)) continue;
            bool tp;
            if(i & 1){
                tp = (j & 1);
            }
            else{
                tp = !(j & 1);
            }
 
            if(tp){
                mitim.add_edge(src, num, 1);
            }
            else{
                mitim.add_edge(num, dst, 1);
                continue;
            }
 
            for(int k = 0; k<4; k++){
                int xx = i + movx[k], yy = j + movy[k];
                if(xx >= 1 and xx <= N and yy >= 1 and yy <= N){
                    int nw = (N * (xx-1)) + yy;
                    if(remov.count(nw)) continue;
                    mitim.add_edge(num, nw, 1);
                }
            }
        }
    }
 
    int mx_f = mitim.max_flow(src, dst);
    if(N*N == P + (mx_f * 2)){
        cout << "Yes" << ENDL;
        mitim.ans(N);
    }
    else{
        cout << "No" << ENDL;
    }
    return 0;
}