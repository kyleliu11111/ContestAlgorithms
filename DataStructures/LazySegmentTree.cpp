/*
Lazy Propagation on Segment Tree

Facts:
- Creates a balanced binary search tree on a static array, splitting by the middle element
- Preprocesses an array to perform many types of subarray queries and updates in ~O(logN)

How it works:
- Each node contains the sum of its elements, with children containing half of its elements
- Any subarray is the union of at most O(logN) segments in the segment tree
- Determine sum queries by computing the sum of these O(logN) segments
- Perform subarray updates by updating nodes as needed, leaving a "lazy" tag on nodes still pending updates

Applications:
- Determine the area covered by a set of axis-alligned rectangles
- Perform subarray increments and subarray sum, min, max queries
- Perform subarray assignments and subarray sum, min, max queries

Implemented:
- Preprocess an array to answer subarray sum queries in O(logN).
*/

#include <bits/stdc++.h>

using namespace std; 

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

int N, Q;
int V[MAXN];
LazySeg <MAXN> T;
int main(void)
{
    cin >> N >> Q;
    for(int i=1; i<=N; i++) cin >> V[i];
    for(int i=1; i<=N; i++) T.upd(1, 1, N, i, i, V[i]);
    for(int i=0; i<Q; i++) {
        int l, r;
        cin >> l >> r;
        cout << T.qry(1, 1, N, l, r) << '\n';
    }
}
