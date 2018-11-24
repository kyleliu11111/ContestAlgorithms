#include <bits/stdc++.h>

using namespace std; 

typedef pair <int, int> pp;
#define A first
#define B second
#define PB push_back
#define MP make_pair

const int MAXN = 1e5 + 1;

int N, M;
vector <pair <int, pp> > Edges;
int par[MAXN];

int get(int x) {
    if(x == par[x]) return x;
    return par[x] = get(par[x]);
}

void join(int x, int y) {
    par[get(x)] = par[get(y)];
}

int main(void)
{
    cin >> N >> M;
    for(int i=1; i<=N; i++) par[i] = i;
    for(int i=0; i<M; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        Edges.PB(MP(c, pp(a, b)));
    }
    
    sort(Edges.begin(), Edges.end());
    
    int MST_COST = 0;
    for(pair <int, pp> e : Edges) {
        int u = e.B.A; int v = e.B.B; int w = e.A;
        u = get(u); v = get(v);
        if(u != v) {
            MST_COST += w;
            join(u, v);
        }
    }
    cout << MST_COST << '\n';
}
