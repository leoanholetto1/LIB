//Complexidade: O(n x sqrt(n))
void sumSubset() {
    // Sum of elements <= N implies that every element is <= N
    vector<int> freq(N + 1, 0);
    for (int i = 0; i < N; i++) {
        int x;
        cin >> x;
        freq[x]++;
    }

    vector<pair<int, int>> compressed;
    for (int i = 1; i <= N; i++) {
        if (freq[i] > 0) compressed.emplace_back(i, freq[i]);
    }

    vector<int> dp(N + 1, 0);
    dp[0] = 1;

    for (const auto &[w, k] : compressed) {
        vector<int> ndp = dp;

        for (int p = 0; p < w; p++) {
            int sum = 0;

            for (int multiple = p, count = 0; multiple <= N; multiple += w, count++) {
                if (count > k) {
                    sum -= dp[multiple - w * count];
                    count--;
                }
                
                if (sum > 0) ndp[multiple] = 1;
                sum += dp[multiple];
            }
        }

        swap(dp, ndp);
    }

    cout << "Possible subset sums are:\n";
    for (int i = 0; i <= N; i++) {
        if (dp[i] > 0) cout << i << " ";
    }
}

//Complexidade: O(n^2)
void sumSubset(){
    bs[0]=1;
    for(int i=0;i<q;i++){
        cin >> aux;
		sum+=aux;
		bs|=(bs<<aux);
    }
}