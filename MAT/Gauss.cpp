//Complexidade: O(min(n,m) x n x m)
const double EPS = 1e-9;

int gauss (vector < vector<double> > a, vector<double> & ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;

    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;
        if (abs (a[sel][col]) < EPS)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                double c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;
    }

    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i=0; i<n; ++i) {
        double sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * a[i][j];
        if (abs (sum - a[i][m]) > EPS)
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return 2;
    return 1;
}

//Para equações lineares modulares(%m)
int gauss_mod(vector<vector<long long>> a, vector<long long>& ans, long long m) {
    mod = m;
    int n = (int)a.size();
    int vars = (int)a[0].size() - 1;

    vector<int> where(vars, -1);
    for (int col = 0, row = 0; col < vars && row < n; ++col) {
        int sel = -1;
        for (int i = row; i < n; ++i) {
            if (a[i][col] % mod != 0) {
                sel = i;
                break;
            }
        }
        if (sel == -1) continue;
        swap(a[sel], a[row]);
        where[col] = row;

        long long inv = modinv((a[row][col] % mod + mod) % mod);
        for (int j = col; j <= vars; ++j)
            a[row][j] = (a[row][j] * inv) % mod;

        for (int i = 0; i < n; ++i) {
            if (i != row && a[i][col] != 0) {
                long long factor = a[i][col];
                for (int j = col; j <= vars; ++j) {
                    a[i][j] = (a[i][j] - factor * a[row][j]) % mod;
                    if (a[i][j] < 0) a[i][j] += mod;
                }
            }
        }
        ++row;
    }

    ans.assign(vars, 0);
    for (int i = 0; i < vars; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][vars];

    for (int i = 0; i < n; ++i) {
        long long sum = 0;
        for (int j = 0; j < vars; ++j)
            sum = (sum + ans[j] * a[i][j]) % mod;
        if ((sum - a[i][vars]) % mod != 0)
            return 0; // sem solução
    }

    for (int i = 0; i < vars; ++i)
        if (where[i] == -1)
            return 2; // infinitas soluções

    return 1; // solução única
}
