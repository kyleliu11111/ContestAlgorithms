/*
Splay Tree

Facts:
- Self-balancing binary search tree
- Recently accessed elements are quick to access again
- Amortized O(logN) access, insert, delete

How it works:
- Balances by a sequence of tree rotations after accessing a node (called a "Splay")
- Maintains summary statistics in each node (in this implementation -- subtree size)

Applications:
- "Rope" applications -- remove and reinsert a subarray in O(logN)
- Subarray cyclic shift in O(logN)
- Process segment tree statistics with dynamic insertions and deletions

Implemented:
- Perform subarray reversal updates in O(logN) and print the final array
*/
#include <bits/stdc++.h> 

using namespace std;

#define keynode ch[ch[root][1]][0]
const int MAXN = 3e5 + 1;

int N, Q;

template <int SZ> struct SplayTree {
	int par[SZ], ch[SZ][2], sz[SZ], key[SZ], flip[SZ], root, tot;

	// input array
	int ar[SZ];
	
	void upd(int x) {
		sz[x] = 1 + sz[ch[x][0]] + sz[ch[x][1]];
	}

	void Reverse(int x)  {
		if(x) {
			swap(ch[x][0],  ch[x][1]);
			flip[x] ^= 1;
		}
	}

	void push_down(int x) {
		if(flip[x]) {
			Reverse(ch[x][0]); Reverse(ch[x][1]);
			flip[x] = 0;
		}
	}

	int Kth(int x, int k) {
		push_down(x);
		int t = sz[ch[x][0]] + 1;
		if(t == k) return x;
		if(t > k) return Kth(ch[x][0], k);
		return Kth(ch[x][1], k-t);
	}

	void ro(int x) {
		int y = par[x], d = (ch[y][1] == x);
		push_down(y); push_down(x);
		ch[y][d] = ch[x][!d]; ch[x][!d] = y;
		if(par[y]) ch[par[y]][ch[par[y]][1] == y] = x;
		par[ch[y][d]] = y; par[x] = par[y];
		par[y] = x;
		upd(y);
	}

	void splay(int x, int gf = 0) {
		int y;
		while((y = par[x]) != gf) {
			if(par[y] != gf) {
				if((ch[par[y]][1] == y) ^ (ch[par[x]][1] == x)) ro(x);
				else ro(y);
			} ro(x);
		} upd(x);
		if(gf == 0) root = x;
	}

	void expose(int a, int b) {
		splay(Kth(root, a), 0);
		splay(Kth(root, b+2), root);
	}
	
	void rev_upd(int a, int b) {
		expose(a, b);
		Reverse(keynode);
		upd(ch[root][1]); upd(root);
	}
	
	int get(int a) {
		expose(a, a);
		int ret = key[keynode];
		upd(ch[root][1]); upd(root);
		return ret;
	}

	void newnode(int &x, int v, int p) {
 		x = ++tot;
 		par[x] = p; 
 		key[x]  = v;
 		upd(x);
 	}

 	void build(int &x, int l, int r, int p) {
		int md = (l+r)/2;
		newnode(x, ar[md], p);
		if(l < md) build(ch[x][0], l, md-1, x);
		if(md < r) build(ch[x][1], md+1, r, x);
		upd(x);
	}

	void init() {
		root = tot = 0;
		newnode(root, -1, 0);
		newnode(ch[root][1], -1, root);
		build(keynode,  1,  N, ch[root][1]);
		upd(ch[root][1]); upd(root); 
	}
};

SplayTree <MAXN> T;

int main()
{
	cin >> N >> Q;
	for(int i=1; i<=N; i++) cin >> T.ar[i];
	T.init();
	for(int i=0; i<Q; i++) {
		int l_q, r_q;
		cin >> l_q >> r_q;
		T.rev_upd(l_q, r_q);
	}
	for(int i=1; i<=N; i++) {
		cout << T.get(i) << ' ';
	}
	cout << '\n';
}
