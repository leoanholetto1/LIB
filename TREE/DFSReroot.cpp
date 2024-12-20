//Complexidade: O(n+m)
void dfs(int nw){
      int ans[nw] = dp[nw];
      for(auto v: g[nw]){
            move(v,nw);//muda a raiz
            dfs(v);
            move(nw,v); // volta a raiz
      }
}

int main(){
      calculateDP(rat);//enraiza em qualquer no
      dfs(rat);//recalcula raiz
}