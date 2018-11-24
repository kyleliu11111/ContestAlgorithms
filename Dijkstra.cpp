#include <bits/stdc++.h>

using namespace std; 

typedef pair <int, int> pp;
#define A first
#define B second
#define PB push_back
#define MP make_pair

const int MAXN = 1e5 + 1;

int N, M;
vector <pp> g[MAXN];
int d[MAXN], vis[MAXN];

int main(void)
{
    cin >> N >> M;
    for(int i=0; i<M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        g[a].PB(pp(b, c));
    }
    
    priority_queue <pp, vector<pp>, greater<pp> > PQ;
    
    PQ.push(MP(0, 1));
    while(PQ.size()) {
        int u = PQ.top().B;
        int di = PQ.top().A;
        PQ.pop();
        if(vis[u]) continue;
        vis[u] = 1; d[u] = di;
        for(pp e : g[u]) if(!vis[e.A]) PQ.push(MP(e.A,  di + e.B)); 
    }
    
    cout << d[N] << '\n';
}
