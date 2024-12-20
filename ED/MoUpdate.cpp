//Complexidade: O(cqrt(n^2))
int B;
struct qry{
    int l,r,time,ix,w;
};
vector<pair<int, int>> updateQueries;
void ins(int i) {
    freq[i]++;
}
void rem(int i) {
    freq[i]--;
}

int get_ans(int w) {
    return freq[w];
}

void update(int i, int x, int y) {
    int idx = updateQueries[i].f;
    int val = updateQueries[i].s;
    int old = v[idx];
    v[idx] = val;
    updateQueries[i].s = old;
    if(idx>=x && idx<=y) { 
        rem(old);
        ins(val);
    }
}


void mo(vector<qry> qs) {
    sort(qs.begin(), qs.end(), [](qry a, qry b) {
        if (a.l/B != b.l/B) {
            return a.l < b.l;
        }
        if(a.r/B != b.r/B){
            return a.r < b.r;
        }
        return a.time < b.time;
    });
    int l = 0, r = -1;
    int t=0;
    for (qry q : qs) {
        while (l > q.l) { l--; ins(v[l]); }
        while (r < q.r) { r++; ins(v[r]); }
        while (l < q.l) { rem(v[l]); l++; }
        while (r > q.r) { rem(v[r]); r--; }
        while(t<q.time) update(t++, l, r);  
        while(t>q.time) update(--t, l, r); 
        ans[q.ix] = r-l + 1 - get_ans(q.w);
    }
}

void solve(){
    int n,q,k,a,b;
    scanf("%d %d", &n, &q);
    B =2e3; // sqrt(n) ou 555 ou pow(2*n*n,1/3.0)
    for(int i=0;i<q;i++){
        scanf("%d", &op);
        if(op==2){
            scanf("%d %d %d", &a, &b, &w);
            int t = updateQueries.sz;
            v2.pb({a-1,b-1,t,i,w});
        }
        else{
            scanf("%d %d", &a, &b);
            ans[i] = -1;
            updateQueries.pb({a-1, b});
        }
    }
    mo(v2); 
    for(int i=0;i<q;i++){
        if(ans[i]!=-1)
            printf("%d\n", ans[i]);
    }
}