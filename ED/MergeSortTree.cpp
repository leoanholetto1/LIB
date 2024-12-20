const int maxn = 1e5+10;
int num[maxn];
vector<int> tree[4*maxn];
//Complexidade: O(n x log n)
void build(int node, int l, int r){
    if (l == r){
        tree[node].push_back(num[l]);
        return;
    }   
    int mid = (l+r)>>1;
    build(2*node, l, mid); build(2*node+1, mid+1, r); 
    int a = 2*node, b = 2*node+1;
    merge(tree[a].begin(), tree[a].end(), tree[b].begin(), tree[b].end(), back_inserter(tree[node]));
}
//Complexidade: O(log n x log n)
int query(int node, int l, int r, int a, int b, int x) {
    if (l > b || r < a) return 0;
    if (l >= a && r <= b) 
        return tree[node].end()-upper_bound(tree[node].begin(), tree[node].end(), x);
    int mid = (l+r)>>1;
    return (query(2*node, l, mid, a, b, x)+query(2*node+1, mid+1, r, a, b, x));
}