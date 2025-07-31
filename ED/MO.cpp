int B;
struct qry{
    int l,r,ix;
};
int freq[200005];
int dist=0;
vi v;
//Complexidade: O(1)
void ins(int i, char dir) {
    i= v[i];
    if(!freq[i]) dist++;
    freq[i]++;
}
//Complexidade: O(1)
void rem(int i, char dir) {
    i=v[i];
    freq[i]--;
    if(!freq[i]) dist--;
}
 
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
        while (l > q.l) { l--; ins(l, 'l'); }
        while (r < q.r) { r++; ins(r, 'r'); }
        while (l < q.l) { rem(l, 'l'); l++; }
        while (r > q.r) { rem(r, 'r'); r--; }
        ans[q.ix] = get_ans();
    }
    return ans;
}
 
void solve(){
    int n,q,k,a,b;
    cin>>n>>q;
    B = 555;  //320
    for(int i=0;i<n;i++){
        cin>>k;
        v.pb(k);
    }
    for(int i=0;i<n;i++){
        cin>>k;
        v3.pb(k);
    }
    vector<qry> v2;
    for(int i=0;i<q;i++){
        cin>>a>>b;
        v2.pb({a-1,b-1,i});
    }
    vi rep = mo(v2); 
    for(int i=0;i<rep.sz;i++) cout << rep[i] << endl;
}