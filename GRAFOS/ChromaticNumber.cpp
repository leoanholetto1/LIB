//Contar o numero minimo de cores para pintar um grafo, de maneira a não ter dois numeros adjacentes 

int n;
vi adjMask; // máscara de adjacência
vi isIndependent; // isIndependent[mask] = true se o conjunto for independente
vi dp,color(20);

// Verifica se um subconjunto é independente (sem arestas entre si)
//Complexidade: O(n)
bool checkIndependent(int mask) {
    for (int i = 0; i < n; ++i) {
        if (mask & (1 << i)) {
            if (adjMask[i] & mask) return false;
        }
    }
    return true;
}

//Complexidade: O(3^n)
int chromaticNumber() {
    int size = 1 << n;
    isIndependent.assign(size, false);
    dp.assign(size, INF);

    // Pré-processa todos os subconjuntos independentes
    for (int mask = 0; mask < size; ++mask)
        isIndependent[mask] = checkIndependent(mask);

    dp[0] = 0; // vazio precisa de 0 cores

    for (int mask = 1; mask < size; ++mask) {
        // Tenta dividir o conjunto atual em subconjuntos independentes
        for (int sub = mask; sub; sub = (sub - 1) & mask) {
            if (isIndependent[sub]) {
                dp[mask] = min(dp[mask], dp[mask ^ sub] + 1);
            }
        }
    }
    return dp[size - 1];
}

void recupera(int ans){
	int c = 1;
	int mask = (1 << n) - 1;
	while(c <= ans){
		for (int sub = mask; sub; sub = (sub - 1) & mask) {
            if (isIndependent[sub] && dp[mask] ==  dp[mask ^ sub] + 1) {
				for(int i=0;i<n;i++){
					if(mask&(1<<i) && (sub&(1<<i))){
						color[i] = c;
					}
				}
				c++;
				mask ^= sub;
                break;
            }
        }
	}
}

//(a,b) = adjMask[a]|=(1<<b); & adjMask[b]|=(1<<a);