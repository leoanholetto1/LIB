struct State {
	int len, link;
	map<char, int> next;
};
class SuffixAutomaton {
private:
	vector<State> st;
    int sz, last;
    ll cont;
public:
    SuffixAutomaton(int n){
		st.resize(2*n+5);
    }

	void sa_init() {
        st[0].len = 0;
        st[0].link = -1;
        sz=1;
        last = 0;
        cont = 0;
    }

    //Complexidade: O(1)
	ll getcont(){
		return cont;
	}

    //Complexidade: O(n x log 26)
    void sa_extend(char c) {
        int cur = sz++;
        st[cur].len = st[last].len + 1;
        int p = last;
        while (p != -1 && !st[p].next.count(c)) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
            cont += st[cur].len;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
                cont -= st[q].len;
                cont += st[cur].len;
            } else {
                int clone = sz++;
                st[clone].len = st[p].len + 1;
                st[clone].next = st[q].next;
                st[clone].link = st[q].link;
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
                cont -= st[clone].len;
                cont += st[cur].len;
            }
        }
        last = cur;
    }
};