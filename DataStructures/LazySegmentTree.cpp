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
