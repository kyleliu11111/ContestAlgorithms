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
