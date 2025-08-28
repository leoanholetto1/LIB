struct node{
	map<char,int> ch;
	int suf,par,cnt;
	int found;
	bool term;
};

node aho[maxN];
int tt=0;

//Complexidade: O(|s|)
void add(string &s, int id){
	int cur =  0;
	for(char c: s){
		if(!aho[cur].ch.count(c)){
			++tt;
			aho[tt].ch.clear();
			aho[tt].cnt = 0;
			aho[tt].par = cur;
			aho[tt].suf  = 0;
			aho[cur].ch[c] = tt;
		}
		cur = aho[cur].ch[c];
	}
	aho[cur].term = 1;
}

//Complexidade: O(|N|)
void build_aho(){
	queue<pair<int,char>> q;
	for(auto &[c,v]: aho[0].ch){
		q.emplace(v,c);
	}
	while(!q.empty()){
		auto [u,c] =  q.front();
		q.pop();
		if(aho[u].par){
			int &j = aho[u].suf;
			j  = aho[aho[u].par].suf;
			while(j && aho[j].ch.count(c)==0){
				j = aho[j].suf;
			}
			if(aho[j].ch.count(c)){
				j = aho[j].ch[c];
			}
		}
		for(auto &[c,v]: aho[u].ch){
			q.emplace(v,c);
		}
	}
}

//Complexidade: O(1) - amortizado
int nxt(int cur,char c){
	while(cur &&  aho[cur].ch.count(c) ==0){
		cur = aho[cur].suf;
	}
	if(aho[cur].ch.count(c)){
		cur = aho[cur].ch[c];
	}
	return cur;
}