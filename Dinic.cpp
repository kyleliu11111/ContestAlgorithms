#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

#define MAXN 50005
#define PB push_back
const ll INF = 1e16;

struct Edge {
	int v;
	ll f, cap;
	int rev;
};

template <int SZ> struct Dinic {
	int lev[SZ], st[SZ]; vector <Edge> g[MAXN];
	void addEdge(int u, int v, ll c) {
		Edge e1 = {v, 0, c, g[v].size()};
		Edge e2 = {u, 0, 0, g[u].size()};
		g[u].PB(e1); g[v].PB(e2);
	}
	bool bfs(int s, int t) {
		for(int i=0; i<SZ; i++) lev[i] = -1;
		queue <int> q; q.push(s); lev[s] = 0;
		while(q.size()) {
			int u = q.front(); q.pop();
			for(auto e : g[u]) if(lev[e.v] < 0 && e.f < e.cap) {
				lev[e.v] = lev[u] + 1; q.push(e.v);
			}
		} return lev[t] >= 0;
	}
	ll aug(int s, int t, ll flow) {
		if(s == t) return flow;
		for(; st[s]<g[s].size(); st[s]++) {
			Edge &e = g[s][st[s]];
			if(lev[e.v] == lev[s] + 1 && e.f < e.cap) {
				ll flo = min(flow, e.cap-e.f); ll add = aug(e.v, t, flo);
				if(add > 0) {
					e.f += add;
					g[e.v][e.rev] -= add;
					return add;
				}
			}
		} return 0;
	}
	ll go(int s, int t) {
		if(s == t) return -1;
		ll maxflow = 0;
		while(bfs(s, t)) {
			for(int i=0; i<SZ; i++) st[i] = 0;
			while(1) {
				ll flow = aug(s, t, INF);
				if(flow > 0) maxflow += flow;
				else break;
			}
		} return maxflow;
	}
};

Dinic <MAXN> MaxFlow;

int main() {
	
}
