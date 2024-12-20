//Complexidade: O(n x m)
//top-dow
int minDis(string s1, string s2, int n, int m){
    if (n == 0)
        return m;
    if (m == 0)
        return n;
    if (dp[n][m] != -1)
        return dp[n][m];
    if (s1[n - 1] == s2[m - 1]) {
        return dp[n][m] = minDis(s1, s2, n - 1, m - 1, dp);
    }
    else {
        int insert, del, replace; // temp variables
        insert = minDis(s1, s2, n, m - 1, dp);
        del = minDis(s1, s2, n - 1, m, dp);
        replace = minDis(s1, s2, n - 1, m - 1, dp);
        return dp[n][m]
               = 1 + min(insert, min(del, replace));
    }
}
//botton-up
int min(int x, int y, int z) { return min(min(x, y), z); }
int editDistDP(string str1, string str2, int m, int n){
    int dp[m + 1][n + 1];
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0)
                dp[i][j] = j;
            else if (j == 0)
                dp[i][j] = i; 
            else if (str1[i - 1] == str2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j]
                    = 1
                      + min(dp[i][j - 1], // Insert
                            dp[i - 1][j], // Remove
                            dp[i - 1][j - 1]); // Replace
        }
    }
    return dp[m][n];
}
//otimizacao de espaco
int editDistance(string s, string t){
    int m = s.size();int n = t.size();
    vector<int> prev(n + 1, j), curr(n + 1, 0);
    for (int i = 1; i <= m; i++) {
        curr[0] = i;
        for (int j = 1; j <= n; j++) {
            if (s[i - 1] == t[j - 1]) 
                curr[j] = prev[j - 1];
            else {
                int mn
                 = min(1 + prev[j], 1 + curr[j - 1]);
                curr[j] = min(mn, 1 + prev[j - 1]);
            }
        }
        prev = curr;
    }

    return prev[n];
}