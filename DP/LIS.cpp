//Complexidade: O(n^2)
//top-dow
int memo[maxN];
memo[0] = 1;
int lis(int x){
    if(memo[x]!=-1) return memo[x];
    memo[x] = 1;
    for(int j=0;j<x;j++){
        if(a[j] <= a[i]) memo[x] = max(memo[x], lis(j) + 1);
    }
    return memo[x];
}
//botton-up
int lis(int n){
    int memo[n], lisMax=0;
    for(int i=0;i<n;i++){
        memo[i] = 1;
        for(int j=0;j<i;j++){
            if(a[j]<=a[i]) memo[i] = max(memo[i],memo[j]+1);
        }
        lisMax = max(lisMax,memo[i]);
    }
    return lisMax;
}
//Complexidade: O(n x log n)
int LIS(vector<int>& nums){
    int n = nums.size();
    vector<int> ans;
    ans.push_back(nums[0]);
    for (int i = 1; i < n; i++) {
        if (nums[i] > ans.back()) {
            ans.push_back(nums[i]);
        }
        else {
            int low =lower_bound(ans.begin(), ans.end(),nums[i])- ans.begin();
            ans[low] = nums[i];
        }
    }
    return ans.size();
}
void print_LIS(int i) {                          
  if (p[i] == -1) { printf("%d", A[i]); return; }
  print_LIS(p[i]);                              
  printf(" %d", A[i]);
}

int k = 0, lis_end = 0;
vi L(n, 0), L_id(n, 0);
p.assign(n, -1);
for (int i = 0; i < n; ++i) {                  
    int pos = lower_bound(L.begin(), L.begin()+k, A[i]) - L.begin();
    L[pos] = A[i];                               
    L_id[pos] = i;                               
    p[i] = pos ? L_id[pos-1] : -1;               
    if (pos == k) {                              
        k = pos+1;                                 
        lis_end = i;                               
    }
}