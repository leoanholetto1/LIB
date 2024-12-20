int trie[maxN][27];
int no;
bool term[maxN];

//Complexidade: O(1)
void init(){
    no=1;
    memset(trie[0], -1, sizeof(trie[0]));
	memset(term,0,sizeof(term));
}


//Complexidade: O(n)
void addWord(const string &s){
    int cur=0;
    for(char c: s){
        int l = c-'a';
        if(trie[cur][l]==-1){
            trie[cur][l] = no;
			memset(trie[no], -1, sizeof(trie[no]));
            no++;
        }
        cur = trie[cur][l];
    }
    term[cur]=1;
}

//Complexidade: O(n)
bool search(const string &s){
    int cur=0;
    for(char c: s){
        int l = c-'a';
        if(trie[cur][l]==-1){
            return 0;
        }
        cur = trie[cur][l];
    }
    return term[cur]==1;
}

