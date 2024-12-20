//Complexidade: O(2^n)
int mask;
for(int subset=mask;subset;subset=mask&(subset-1))
    cout<<subset<<endl;