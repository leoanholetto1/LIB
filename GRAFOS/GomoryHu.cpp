// Gomory-Hu Tree (baseado no algoritmo de Gusfield) 
// Calcula o fluxo maximo entre todos os verticies (a,b)
// Complexity: O(n - 1) * max_flow
struct GomoryHuTree {
    int n;
    vector<int> pai;
    vector<ll> fpai;
    vector<vector<ll>> mincut;
    
    GomoryHuTree(int n) : n(n) {
        pai.resize(n);
        fpai.resize(n);
        mincut.assign(n, vector<ll>(n, -1));
    }
    
    ll min_cut(Dinic &dinic, int s, int t, vector<bool> &cuts) {
        dinic.reset();
        ll flow = dinic.flow(s, t);
        fill(cuts.begin(), cuts.end(), false);
        dinic.find_cut(s, cuts);
        return flow;
    }
    
    void build(Dinic &original_dinic) {
        fill(pai.begin(), pai.end(), 0);
        
        for (int s = 1; s < n; s++) {
            int t = pai[s];
            Dinic dinic_copy(n);
            for (int i = 0; i < original_dinic.edges.size(); i += 2) {
                const auto &edge = original_dinic.edges[i];
                dinic_copy.add_edge(edge.v, edge.u, edge.cap);
            }
            
            vector<bool> cuts(n);
            fpai[s] = min_cut(dinic_copy, s, t, cuts);
            
            mincut[s][t] = mincut[t][s] = fpai[s];
            
            for (int v = s + 1; v < n; v++) {
                if (cuts[v] && pai[v] == t) {
                    pai[v] = s;
                }
            }

            for (int v = 0; v < s; v++) {
                if (mincut[s][v] == -1) {
                    mincut[s][v] = mincut[v][s] = min(mincut[s][t], mincut[t][v]);
                }
            }
        }
    }
};