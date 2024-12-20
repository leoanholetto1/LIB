typedef tree<pair<ll,ll>, null_type, less<pair<ll,ll>>, rb_tree_tag, 
             tree_order_statistics_node_update> pds; 
vector <ll> arr(N);
pds mst[N];

void init(ll pp){
    for(ll i=0;i<4*pp;i++){
        mst[i].clear();
    }
}
//Complexidade: O(n x log n x log n)
void build(ll n,ll b,ll e){
    if(b==e){
        mst[n].insert({arr[b],b});
        return;
    }
    for(ll i=b;i<=e;i++)
        mst[n].insert({arr[i],i});
        
    ll mid=(b+e)/2;
    build(lc,b,mid);
    build(rc,mid+1,e);
}

//numeros menor que x
//se for para acha qdt de num maior que x: 
//mst[n].sz - mst[n].order_of_key({v,idx});
//Complexidade: O(log n x log n x log n)
ll query(ll n,ll b,ll e,ll i,ll j,ll v,ll idx){
    if(b>j or e<i)  return 0;
    if(b>=i and e<=j){
        ll k=mst[n].order_of_key({v,idx});
        return k;
    }
    ll mid=(b+e)/2;
    return query(lc,b,mid,i,j,v,idx) + query(rc,mid+1,e,i,j,v,idx);
}
//Complexidade: O(log n x log n)
void update(ll n,ll b,ll e,ll i,ll v,ll nw){
    if(i<b or e<i)  return;
    if(b==i and e==i){
        mst[n].erase(mst[n].find({v,i}));
        mst[n].insert({nw,i});
        return;
    }
    ll mid=(b+e)/2;
    update(lc,b,mid,i,v,nw);
    update(rc,mid+1,e,i,v,nw);
    mst[n].erase(mst[n].find({v,i}));
    mst[n].insert({nw,i});
}