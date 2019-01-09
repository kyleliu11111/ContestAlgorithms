/*
D'Esopo-Pape's Shortest Path Algorithm (Shortest-Path Faster Algorithm)
Facts:
- Fast SSSP Algorithm in practice
- Handles negative-weight edges
- Typically faster than Dijkstra and Bellman-Ford
- Unproven Complexity
How it works:
- Maintain d[u] -- shortest path from source s->u at all times
- Repeatedly "relax" paths with edges
- Maintain a queue of recently relaxed nodes. At each step, pop a node and:
	- Try relaxing each neighbor
		- If relaxed, add it to the queue if it's not already in
Applications:
- Find the shortest path from s->v in general graph
- Solve system of difference constraints in large graphs
Implemented:
- Find the shortest path from 1->u for u = {2, ..., N} in directed graph
*/

#include  <bits/stdc++.h>

using namespace std;
typedef pair <int, int> pp;
#define PB push_back
#define A first
#define B second
const int MAXN = 5e5 + 1;

int N, M;
vector <pp> g[MAXN];
int d[MAXN], in[MAXN];

int main(void)
{
    cin >> N >> M;
    for(int i=0; i<M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].PB(pp(b, c));
    }
    
    for(int i=1; i<=N; i++) d[i] = INT_MAX;
    queue <int> q;
    q.push(1); d[1] = 0; in[1] = 1;
    while(q.size()) {
        int u = q.front();
        q.pop();
        in[u] = 0;
        for(pp e : g[u]) {
            if(d[e.A] > d[u] + e.B) {
                d[e.A] = d[u] + e.B;
                if(!in[e.A]) q.push(e.A);
            }
        }
    }
    for(int i=2; i<=N; i++) cout << d[i] << '\n';
}
	
	
