/*
Heavy-light Path Decomposition on a Tree

Facts:
- Decomposes a tree into vertex-disjoint chains such that the path between any node and the root crosses O(logN) chains
- Constructs in-order traversal arrays to allow path and subtree updates

How it works:
- Reorders children of each node such that the first child has the largest subtree
- Edges to the first child are called "heavy", all others are "light"
- Chains are constructed of consecutive heavy edges. In this implementation, top[u] denotes the highest node in the
chain containing u.
- Now we can verify that the nodes on the path {top[u], u} are consecutive in the in-order tree traversal.
- Thus, an update to the root consists of updating segments of at most log(N) chains, which can be done in O(logN)
using segment trees with lazy propagation.
- We can also perform subtree updates quickly, as the nodes in the subtree of {u} are also consecutive in the in-order
tree traversal.

Applications:
- Path increment and path sum, min, max queries in O(log^2N)
- Subtree increment and subtree sum, min, max queries in O(logN)
- LCA computation in O(logN)

Implemented: 
Preprocess a tree to support quick path increment and path sum queries
*/

#include <bits/stdc++.h>

using namespace std;

#define PB push_back

const int MAXN = 1e5 + 1;

template <int SZ> struct LazySeg {
    int T[SZ*4], lzy[SZ*4];
    
    void push_down(int x, int l, int r) {
        if(lzy[x]) {
            T[x] += lzy[x] * (r-l+1);
            if(l != r) { lzy[2*x] += lzy[x];  lzy[2*x+1] += lzy[x]; }
            lzy[x] = 0;
        }
    }
    
    void upd(int x, int l, int r, int lq, int rq, int to_inc) {
        push_down(x, l, r);
        if(l > rq || r < lq) return;
        if(lq <= l && rq >= r) {
            lzy[x] += to_inc;
            push_down(x, l, r); return;
        }
        int md = (l+r)/2;
        upd(x*2, l, md, lq, rq, to_inc); upd(x*2+1, md+1, r, lq, rq, to_inc);
        T[x] = T[x*2] + T[x*2+1];
    }
    
    int qry(int x, int l, int r, int lq, int rq) {
        push_down(x, l, r);
        if(l > rq || r < lq) return 0;
        if(lq <= l && rq >= r) return T[x];
        int md = (l+r)/2;
        return qry(x*2, l, md, lq, rq) + qry(x*2+1, md+1,  r, lq, rq);
    }
};

template <int SZ> struct HLD {
    int N;
    int in[SZ], rin[SZ], top[SZ], out[SZ], sz[SZ], par[SZ], tot;
    vector <int> adj[SZ], g[SZ];
    LazySeg <SZ> T;
    
    void addEdge(int u, int v) {
        adj[u].PB(v); adj[v].PB(u);
    }
    
    void dfs1(int u, int p) {
        sz[u] = 1;
        par[u] = p;
        for(int v : adj[u]) if(v != p) {
            dfs1(v, u); 
            sz[u] += sz[v]; g[u].PB(v);
        }
        for(int& v : g[u]) if(sz[v] > sz[g[u][0]]) swap(g[u][0], v);
    }
    
    void dfs2(int u) {
        in[u] = tot++;
        rin[in[u]] = u;
        for(int v : g[u]) {
            if(v ==  g[u][0]) top[v] = top[u];
            else top[v] = v;
            dfs2(v);
        } out[u] = tot;
    }
    
    void path_inc(int a, int b, int v) {
        while(top[a] != top[b]) {
            T.upd(1, 0, N-1, in[top[a]], in[a], v); a = par[top[a]];
            T.upd(1, 0, N-1, in[top[b]], in[b], v); b = par[top[b]];
        }
        if(in[a] > in[b]) swap(a, b);
        T.upd(1, 0, N-1, in[a], in[b], v);
    }
    
    int path_sum(int a, int b) {
        int sum = 0;
        while(top[a] != top[b]) {
            sum += T.qry(1, 0, N-1, in[top[a]], in[a]); a = par[top[a]];
            sum += T.qry(1, 0, N-1, in[top[b]], in[b]); b = par[top[b]];
        }
        if(in[a] > in[b]) swap(a, b);
        sum += T.qry(1, 0, N-1, in[a], in[b]);
        return sum;
    }
};

HLD <MAXN> Solver;
int N, Q;
int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N >> Q;
	for(int i=0; i<N-1; i++) {
	    int a, b;
	    cin >> a >> b;
	    Solver.addEdge(a, b);
	}
	
	Solver.dfs1(1, 1);
	Solver.dfs2(1);
	
	for(int i=0; i<Q; i++) {
	    int t, a, b, v;
	    cin >> t >> a >> b;
	    if(t == 1) {
	        cin >> v;
	        Solver.path_inc(a, b, v);
	    }
	    else {
	        cout << Solver.path_sum(a, b) << '\n';
	    }
	}
}
