//Complexidade: O(n)
void solve(){
    int field_num;
    cin >> field_num;
    vector<int> deg(field_num + 1); 
    for (int p = 0; p < field_num - 1; p++) {
        int field1, field2;
        cin >> field1 >> field2;
        deg[field1]++;
        deg[field2]++;
    }
    int max_deg = 0;
    for (int f = 1; f <= field_num; f++) { 
        max_deg = max(max_deg, deg[f]); 
    }
    cout << max_deg + 1 << endl;
} 