//Complexidade: O(m x log m)
void addEdge(int x, int y, int w) { 
    edgelist.push_back({ w, x, y }); 
} 

void kruskals_mst() { 
    sort(edgelist.begin(), edgelist.end()); 
    makeset();
    int ans = 0; 
    for (auto edge : edgelist) { 
        int w = edge[0]; 
        int x = edge[1]; 
        int y = edge[2]; 
        if (s.find(x) != s.find(y)) { 
            s.unite(x, y); 
            ans += w; 
        } 
    } 
    cout << ans <<endl; 
} 