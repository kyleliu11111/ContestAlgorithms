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
