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
	
	
