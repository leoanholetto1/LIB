//Complexidade: O(n^3)
//Tem alguns objetivos e sua probabilidade, achar a probabilidade da origem usando Cadeias Markov + Gauss  Seidel
void solve(){
    vt<double> prob(n+1),new_prob(n+1);
    prob[c] = 0.0;
    prob[b] = 1.0;
    bool flag;
    do{
        flag = 1;
        for(int i=1;i<=n;i++){
            if(i!=b && i!=c){
                double sum=0.0;
                for(auto p: adj[i]){
                    sum+=prob[p];
                }
                new_prob[i] = sum/adj[i].sz;
                if (fabs(new_prob[i] - prob[i]) > eps) {
                    flag = 0;
                }
            }
            else new_prob[i] = prob[i];
        }
        prob = new_prob;
    }while(!flag);
    cout << fixed << setprecision(6) << prob[a] << endl;
}