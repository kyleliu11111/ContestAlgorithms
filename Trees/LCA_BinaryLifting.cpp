/*
Lowest Common Ancestor with Binary Lifting

Facts : 
- Answers lowest common ancestor queries on a tree of N nodes in O(logN)
- Precomputations in <O(NlogN), O(NlogN)>

How it works:
- Computes the parent and depth arrays of a tree with dfs in O(N)
- Uses dynamic programming to find the 2^k'th parents of each node, for k=0...[log2(N)]
- Answers LCA queries by a form of binary search

Applications:
- Query the distance between two nodes in a tree in O(logN)
- Answer path min, sum, max queries in a tree in O(logN)

Implemented:
Preprocess a tree to answer lowest common ancestor queries in O(logN)
*/
#include <bits/stdc++.h>

using namespace std; 

typedef pair <int, int> pp;
#define A first
#define B second
#define PB push_back
#define MP make_pair

const int MAXN = 1e5 + 1;
const int MAXL = 17;

int N, Q;
vector <int> g[MAXN];

int par[MAXL][MAXN], dep[MAXN];

void dfs(int u, int p) {
    par[0][u] = p;
    dep[u] = dep[p] + 1;
    for(int v : g[u]) if(v != p) dfs(v, u);
}

int LCA(int a, int b) {
    if(dep[a] < dep[b]) swap(a, b);
    for(int i=MAXL-1; i>=0; i--) if(dep[par[i][a]] >= dep[b]) a = par[i][a];
    if(a == b) return a;
    for(int i=MAXL-1; i>=0; i--) if(par[i][a] != par[i][b]) {
        a = par[i][a]; b = par[i][b];
    }
    return par[0][a];
}
int main(void)
{
    cin >> N >> Q;
    for(int i=0; i<N-1; i++) {
        int a, b; cin >> a >> b;
        g[a].PB(b); g[b].PB(a);
    }
    dfs(1, 1);
    
    for(int i=1; i<MAXL; i++) for(int j=1; j<=N; j++) 
        par[i][j] = par[i-1][par[i-1][j]];
        
    for(int i=0; i<Q; i++) {
        int a, b;
        cin >> a >> b;
        cout << LCA(a, b) << '\n';
    }
}
