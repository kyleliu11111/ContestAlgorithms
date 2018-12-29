/*
LiChao Segment Tree for Dynamic Upper/Lower Hull Maintenance

Facts:
- Accepts functions F() with condition that no two functions intersect twice
- Builds a segment tree over x-values to query min or max over F_i(x)
How it works:
- Each node contains the "dominating" function over a range -- the extrema at the center x-value
- Pushes non-dominating functions down the tree based on intersection point with dominating function
- Guarantees : For each x-value, argmin F_i(x) lies on the path from the root of the segment tree 
  to the corresponding leaf node
Applications:
- Online upper/lower hull maintenance for mono-intersecting functions
- non-amortized O(logN) insertions and O(logN) extrema queries
- Offline dynamic upper/lower hull maintenance (insertions and deletions) in O(Qlog^2N)
Implemented:
- Given a set of linear functions, query the maximum over all functions at many x-values
*/

#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

const int MAXN = 1e7;
const int MAXX = 1e5;
const ll INF = 1e16;

struct Line {
	ll m, b;
	ll eval(ll x) { return x*m + b; } // to handle negative indices
	bool operator < (const Line& r) const {
		if(r.m != m) return b < r.b;
		return m < r.m;
	}
};

Line nil = {0, -INF};

template <int SZ> struct LiChaoSegmentTree { // query max
	Line L[SZ];
	int ch[SZ][2], root, tot = 0;

	int newnode(int &x) {
		x = ++tot;
		L[x] = nil;
	}

	int getch(int x, bool w) { if(!ch[x][w]) newnode(ch[x][w]); return ch[x][w]; }

	void ins(int x, Line v, int l, int r) {
		int md = (l+r)/2;
		bool lft = v.eval(l) > L[x].eval(l);
		bool mid = v.eval(md+1) > L[x].eval(md+1);
		if(mid) swap(L[x], v);
		if(l == r) return;
		if(lft != mid) ins(getch(x, 0), v, l, md);
		else ins(getch(x, 1), v, md+1, r);
	}
	
	ll qry_max(int x, int l, int r, ll q_x) {
		if(l == r) return L[x].eval(q_x);
		int md =  (l+r)/2; ll ret = L[x].eval(q_x);
		if(x <= md) if(ch[x][0]) ret = max(ret, qry_max(getch(x, 0), l, md, q_x));
		if(x > md) if(ch[x][1]) ret = max(ret, qry_max(getch(x,1 ), md+1, r, q_x));
		return ret;
	}

	void init() {
		newnode(root);
	}
};

int N, Q;
LiChaoSegmentTree <MAXN> T;
int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cin >> N >> Q;
	
	for(int i=0; i<N; i++) {
		ll m_i, b_i;
		cin >> m_i >> b_i;
		Line v = {m_i, b_i};
		T.ins(T.root, v, 1, MAXX);
	}
	for(int i=0; i<Q; i++) {
		ll x_q; cin >> x_q;
		cout << T.qry_max(T.root, 1, MAXX, x_q) << ' ';
	}
	cout << '\n';
}
