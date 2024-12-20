stack<pair<int,int>> old_pai;
stack<pair<int,int>> old_tam;
//Complexidade: O(log n)
int find(int x){
    if(pai[x] == x) return x;
    return find(pai[x]);
}
//Complexidade: O(log n)
void merge(int u,int v){
    int a = find(u);
    int b = find(v);
    if(tam[a] > tam[b])
        swap(a,b);
    old_pai.emplace(a,pai[a]);
    old_tam.emplace(b,tam[b]);
    pai[a] = b;
    tam[b]+=tam[a];
}
//Complexidade: O(1)
void roolback(){
    auto paiAnt = old_pai.top();
    auto tamAnt = old_tam.top();
    pai[paiAnt.first()] = paiAnt.second();
    tam[tamAnt.first()] = tamAnt.second();
    old_pai.pop();
    old_tam.pop();
}