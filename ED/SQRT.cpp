int len;
vi b(maxN);

//Complexidade: O(n)
void preprocess(int n,vi &a){
    len = (int) sqrt (n + .0) + 1; 
    vi b (len);
    for (int i=0; i<n; ++i)
        b[i / len] += a[i];

}

//Complexidade: O(sqrt(n))
int query(int l,int r){
    int sum = 0;
    for (int i=l; i<=r;)
        if (i % len == 0 && i + len - 1 <= r) {
            sum += b[i / len];
            i += len;
        }
        else {
            sum += a[i];
            ++i;
        }
    return sum;
}