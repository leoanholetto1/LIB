struct Vertex {
    int next[K];
    int cont=0;

    Vertex() {
        fill(begin(next), end(next), -1);
    }
};

vector<Vertex> trie(1);
//Complexidade: O(n)
void insert(string const& s) {
    int v = 0;
    for (int i = 0; i < s.size(); i++){
        int c = s[i] - 'a';
        if (trie[v].next[c] == -1) {
            trie[v].next[c] = trie.size();
            trie.emplace_back();
        }
        v = trie[v].next[c];
    }
    trie[v].cont=1;
}
//Complexidade: O(n)
int search(string const& s){
    int v = 0;
    for (int i = 0; i < s.size(); i++){
        int c = s[i] - 'a';
        if (trie[v].next[c] == -1)
            return 0;
        v = trie[v].next[c];
    }
    return trie[v].cont;
}
