//Complexidade: O(n^2)
int lps( int l, int r ) {
    if(dp[l][r] != -1 ) return dp[l][r];
    if( l == r ) {
               dp[l][r] = 1;
    } else if( l + 1 == r ) {
            dp[l][r] = ( s[l] == s[r] ? 2 : 1 );
    } else {
        if( s[l] == s[r] ) {
            dp[l][r] = lps( l + 1, r - 1 );
        }
        dp[l][r] = max(dp[l][r],max(lps(l,r-1),lps(l+1,r)));
    }
    return dp[l][r];
}