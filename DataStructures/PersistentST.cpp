#include <bits/stdc++.h> 

using namespace std;

#define PB push_back

const int MAXN = 1e5 + 1;
const int MAXL = 20;

template <int SZ> struct Persistent_ST {
    int root[SZ], ch[SZ*MAXL][2], T[SZ*MAXL], tot;
    
    int build(int l, int r) {
        int x = ++tot;
        if(l == r) return x;
        int md = (l+r)/2;
        ch[x][0] = build(l, md);
        ch[x][1] = build(md+1, r);
        return x;
    }
    
    int ins(int p, int cur, int l, int r) {
        if(p < l || p > r) return cur;
        int x = ++tot;
        T[x]++;
        if(l == r) return x;
        int md = (l+r)/2;
        ch[x][0] = ins(p, ch[cur][0], l, md);
        ch[x][1] = ins(p, ch[cur][1], md+1, r);
        T[x]  = T[ch[x][0]] + T[ch[x][1]];
        return x;
    }
    
    int qsum(int x, int l, int r, int lq, int rq) {
        if(l > rq || r < lq) return 0;
        if(lq <= l && rq >= r) return T[x];
        int md = (l+r)/2;
        return qsum(ch[x][0], l, md, lq, rq) + qsum(ch[x][1], md+1, r, lq, rq);
    }
};

int N, Q;
Persistent_ST <MAXN> T;

int main(void)
{
    cin >> N >> Q;
    T.root[0] = T.build(1, N);
    for(int i=1; i<=N; i++) {
        int x; cin >> x;
        T.root[i] = T.ins(x, T.root[i-1], 1, N);
    }
    
    for(int i=0; i<Q; i++) {
        int idx, lq, rq;
        cin >> idx >> lq >> rq;
        cout << T.qsum(T.root[idx], 1, N,  lq, rq) << '\n';
    }
}
