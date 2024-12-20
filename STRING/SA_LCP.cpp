ll sa[maxN],pos[maxN], tmp[maxN], lcp[maxN];
ll gap, n;
string s;

bool comp(ll x, ll y) {
    if(pos[x] != pos[y]){
        return pos[x] < pos[y];
    } 
    x += gap;
    y += gap;
    return (x < n && y < n) ? pos[x] < pos[y] : x > y;
}
//Complexidade: O(n x log n x log n)
void suffix(){
    for(ll i=0;i<n;i++){
        sa[i] = i, pos[i] = s[i];
    }
 
    for(gap=1;;gap <<= 1){
        sort(sa, sa+n, comp);
 
        for(ll i=0;i< n-1;i++){
            tmp[i+1] = tmp[i] + comp(sa[i], sa[i+1]);
        }
 
        for(ll i=0;i< n; i++){
            pos[sa[i]] = tmp[i];
        }
 
        if(tmp[n-1] == n-1){
            break;
        }
    }
}
//Complexidade: O(n)
void build_lcp(){
    for(ll i=0,k=0; i < n ; i++){
        if(pos[i] != n-1){
            ll j = sa[pos[i] + 1];
            while(s[i+k] == s[j+k])
                k++;
 
            lcp[pos[i]] = k;
            if(k) k--;
        }
    }
}