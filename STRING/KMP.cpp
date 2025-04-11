//Complexidade: O(n)
vector<int> pi(string s) {
    int n = (int)s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

//Complexidade: O(n+m)
vector<int> matching(string &t,string &s){
    vector<int> p = pi(s+'$'),match;
    for(int i=0,j=0;i<t.size();i++){
        while(j>0 and s[j]!=t[i]) j = p[j-1];
        if(s[j]==t[i]) j++;
        if(j == s.size()) match.push_back(i-j+1);
    }
    return match;
}

//Complexidade: O(n + m)
vector<int> matching(string &t,string &s){
    vector<int> p = pi(s+'$'+t),match;
    for(int i=s.size()+1;i<p.size();i++){
        if(p[i] == s.size()) match.push_back(i-2*s.size());
    }
    return match;
}