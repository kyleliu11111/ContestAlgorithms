/*
Dijkstra's Shortest Path Algorithm
Facts:
- Single source shortest path algorithm
- O((N+M)logN) SSSP
- Assumes non-negative edge weights
How it works:
- Build shortest path tree in N steps, maintain d[v]. Initially, d[1] = 0, d[v != 1] = INF.
- In each step, retrieve v with minimum d[v] not yet explored
- Traverse each edge from v, updating d[] accordingly
- After N steps, d[v] contains the shortest path from 1->v
- O(N^2 + M)
- In sparce graphs, speed up to O((N+M)logN) with a priority queue to retrieve minimum d[v]
Applications:
- Fast single source shortest path
Implemented:
- Given a directed graph, determine the shortest path between 1->N
*/
#include <bits/stdc++.h>

using namespace std; 

typedef pair <int, int> pp;
#define A first
#define B second
#define PB push_back
#define MP make_pair

const int MAXN = 1e5 + 1;

template <int SZ> struct Dijkstra {
    int d[SZ], vis[SZ];
    vector <pp> g[SZ];
    
    void addEdge(int u, int v, int c) { g[u].PB(pp(v, c)); }
                                                
    void go(int s) {
        priority_queue <pp, vector<pp>, greater<pp> > PQ;
        
        PQ.push(MP(0, s));
        while(PQ.size()) {
            int u = PQ.top().B;
            int di = PQ.top().A;
            PQ.pop();
            if(vis[u]) continue;
            vis[u] = 1; d[u] = di;
            for(pp e : g[u]) if(!vis[e.A]) PQ.push(MP(e.A,  di + e.B)); 
        }
    }
};
int main(void)
{
    int N, M;
    Dijkstra <MAXN> SP;
    cin >> N >> M;
    for(int i=0; i<M; i++) {
        int a, b, c; cin >> a >> b >> c;
        SP.addEdge(a, b, c);
    }
    SP.go(1);
    
    cout << SP.d[N] << '\n';
}
