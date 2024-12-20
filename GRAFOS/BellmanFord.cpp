//Complexidade: O(n^2)
void solve(){
    vector<int> d(n, INF);
    d[v] = 0;
    for (int i = 0; i < n ; ++i){
        x = -1;
        for (Edge e : edges)
            if (d[e.a] < INF){
                if (d[e.b] > d[e.a] + e.cost) x = e.b;
                d[e.b] = min(d[e.b], d[e.a] + e.cost);
            }
    }
    if(x == -1) cout << "No negative cycle from ";    
    else cout << "Negative cycle from ";
}