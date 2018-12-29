/*
Bellman-Ford Shortest Path Algorithm
Facts:
- Single source shortest path algorithm
- Handles negative edge weights
- O(NM) SSSP
- Detects negative cycles
How it works:
- Assume no negative cycles exist: then any shortest path contains at most N-1 edges
- Perform N-1 "relaxation" steps: 
    at the i'th step, we compute d[v], the shortest path from 1->v using at most i edges
- Run the relaxation step an N'th time -- if our d[v] values change, 
    then a shortest path contains more than N-1 edges, so a negative cycle exists
Applications:
- Solve systems of difference constraints with shortest paths
- Shortest path with negative cycles
Implemented:
- Given a directed graph, determine the shortest path between 1->N, or report that a negative cycle exists
*/
#include <bits/stdc++.h>

using namespace std; 

typedef pair <int, int> pp;
#define PB push_back
#define A first
#define B second
const int MAXN = 1e5 + 1;

int N, M;
vector <pp> g[MAXN];
int d[MAXN];

int main(void)
{
    cin >> N >> M;
    for(int i=0; i<M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].PB(pp(b, c));
    }
    for(int i=1; i<=N; i++) d[i] = INT_MAX;
    
    d[1] = 0;
    for(int i=0; i<N-1; i++) 
        for(int j=1; j<=N; j++) 
            for(pp e : g[j]) d[e.A] = min(d[e.A], d[j] + e.B);
    
    bool neg_cycle = 0;
    for(int i=1; i<=N; i++) for(pp e : g[i]) if(d[e.A] > d[i] + e.B) neg_cycle = 1;
    
    if(neg_cycle) {
        cout << "Negative Cycle Exists" << '\n';
    }
    else cout << d[N] << endl;
}
