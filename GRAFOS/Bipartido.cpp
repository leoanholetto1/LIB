//Complexidade: O(n + m)
bool flag=1;
void dfs(int a,int ant,int cor){
    vis[a] = cor;
    for(auto v: adj[a]){
        if(ant!=v){
            if(!vis[v]) dfs(v,a,(cor==1) ? 2 : 1);
            else if(cor == vis[v]) flag = 0;
        }
    }
}