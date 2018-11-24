#include <bits/stdc++.h>

using namespace std; 

typedef pair <int, int> pp;
#define PB push_back
#define A first
#define B second
const int MAXN = 1e5 + 1;

template <int SZ> struct Kosaraju_SCC {
    int N;
    vector <int> adj[SZ], rev[SZ];
    int ord[SZ], comp[SZ], vis[SZ], tot, num_scc;
    
    void addEdge(int u, int v) {
        adj[u].PB(v);  rev[v].PB(u);
    }
    void dfs1(int u) {
        vis[u] = 1;
        for(int v : adj[u]) if(!vis[v]) dfs1(v);
        ord[tot++] = u;
    }
    
    void dfs2(int u) {
        vis[u] = 1;
        comp[u] = num_scc;
        for(int v : rev[u]) if(!vis[v]) dfs2(v);
    }
    
    void run(int N) {
        for(int i=1; i<=N; i++) if(!vis[i]) dfs1(i);
        memset(vis, 0, sizeof(vis));
        for(int i=0; i<N; i++) {
            int u = ord[N-1-i];
            if(!vis[u]) {
                num_scc++;
                dfs2(u); // traverse all nodes in this scc
            }
        }
    }
};

int N, M;
Kosaraju_SCC <MAXN> Solver;
int main(void)
{
    cin >> N >> M;
    for(int i=0; i<M; i++) {
        int a, b;
        cin >> a >> b;
        Solver.addEdge(a, b);
    }
    
    Solver.run(N);
    cout << Solver.num_scc << '\n';
}
