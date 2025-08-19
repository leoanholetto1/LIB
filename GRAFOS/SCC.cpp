#include <stdio.h>
#include <vector>
 
#define ll long long
constexpr int maxN = 1e5+2;
 
class DAG {
 
    int v;
    std::vector<int> adj[maxN];
 
public:
 
    DAG(int v) : v(v) {};
 
    void AddEdge(int a, int b) {
        adj[a].push_back(b);
    }
 
    // Stuff to solve
};
 
class Graph {
 
    int v;
    std::vector<int> adj[maxN], rAdj[maxN];
 
public:
 
    Graph(int v) : v(v) {};
 
    void AddEdge(int a, int b) {
        adj[a].push_back(b);
        rAdj[b].push_back(a);
    }
 
private:
 
    void DFS(int node, bool visited[maxN], std::vector<int>& postOrder) {
        visited[node] = true;
        for (int e : adj[node]) {
            if (visited[e]) continue;
            DFS(e, visited, postOrder);
        }
 
        postOrder.push_back(node);
    }
 
    // Reverse DFS to assign scc
    void rDFS(int node, int scc, int nodes[maxN], bool visited[maxN]) {
        visited[node] = true;
        nodes[node] = scc;
        for (int e : rAdj[node]) {
            if (visited[e]) continue;
            rDFS(e, scc, nodes, visited);
        }
    }
 
    void GenSCC(int nodes[maxN]) {
        bool visited[2][maxN] = {{false}};
        
        std::vector<int> postOrder = std::vector<int>();
 
        // Get post order
        for (int i = 1; i <= v; i++)
            if (!visited[0][i]) 
                DFS(i, visited[0], postOrder);
 
        int scc = 1;
        while (!postOrder.empty()) {
            int node = postOrder.back();
            postOrder.pop_back();
            
            if (visited[1][node]) continue;
 
            rDFS(node, scc, nodes, visited[1]);
            scc++;
        }
    }
 
public:
 
    // Condensates the Graph by SCC, turning it into a DAG
    DAG Condensated() {
        int nodes[maxN];
        this->GenSCC(nodes);
 
        int cV = 0;
        for(int i = 1; i <= v; i++)
            cV = std::max(cV, nodes[i]);
        
        DAG cGraph = DAG(cV+1);
        for(int i = 1; i <= v; i++)
            for(int e : this->adj[i])
                if(nodes[i] != nodes[e])
                    cGraph.AddEdge(nodes[i], nodes[e]);
 
        return cGraph;
    }
};