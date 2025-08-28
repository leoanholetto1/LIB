struct SegmentTreeDynamicLazy {
private:
    vt<ll> sum, e, d, lazy;
    int root;
    ll L, R;

    // Cria um novo nó da árvore
    int created() {
        sum.push_back(0);
        e.push_back(-1);
        d.push_back(-1);
        lazy.push_back(0);
        return sum.size() - 1;
    }

    // Propaga o valor lazy para os filhos (se necessário)
    // Complexidade: O(1)
    void push(int pos, ll ini, ll fim) {
        if (lazy[pos] == 0) return;
        sum[pos] += lazy[pos] * (fim - ini + 1);
        if (ini != fim) {
            if (e[pos] == -1) e[pos] = created();
            if (d[pos] == -1) d[pos] = created();
            lazy[e[pos]] += lazy[pos];
            lazy[d[pos]] += lazy[pos];
        }
        lazy[pos] = 0;
    }

    // Atualiza intervalo [l, r] com valor val no nó `pos`
    // Complexidade: O(log N), onde N é o tamanho do intervalo [L, R]
    void update(int pos, ll ini, ll fim, ll l, ll r, ll val) {
        push(pos, ini, fim);
        if (r < ini || fim < l) return;
        if (l <= ini && fim <= r) {
            lazy[pos] += val;
            push(pos, ini, fim);
            return;
        }
        ll m = (ini + fim) >> 1;
        if (e[pos] == -1) e[pos] = created();
        if (d[pos] == -1) d[pos] = created();
        update(e[pos], ini, m, l, r, val);
        update(d[pos], m + 1, fim, l, r, val);
        sum[pos] = sum[e[pos]] + sum[d[pos]];
    }

    // Consulta soma no intervalo [l, r] no nó `pos`
    // Complexidade: O(log N)
    ll query(int pos, ll ini, ll fim, ll l, ll r) {
        if (pos == -1 || r < ini || fim < l) return 0;
        push(pos, ini, fim);
        if (l <= ini && fim <= r) return sum[pos];
        ll m = (ini + fim) >> 1;
        ll left = query(e[pos], ini, m, l, r);
        ll right = query(d[pos], m + 1, fim, l, r);
        return left + right;
    }

public:
    // Inicializa árvore com intervalo de operação [ini, fim]
    SegmentTreeDynamicLazy(ll ini = 0, ll fim = 1e18) {
        L = ini;
        R = fim;
        root = created();
    }

    // Atualiza intervalo [l, r] com valor val
    // Complexidade: O(log N)
    void update(ll l, ll r, ll val) {
        update(root, L, R, l, r, val);
    }

    // Consulta soma no intervalo [l, r]
    // Complexidade: O(log N)
    ll query(ll l, ll r) {
        return query(root, L, R, l, r);
    }
};
