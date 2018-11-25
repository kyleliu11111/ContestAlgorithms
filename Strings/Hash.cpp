#include <bits/stdc++.h>

using namespace std; 

typedef long long ll;
#define PB push_back
#define A first
#define B second
const int MAXN = 1e5 + 1;


struct Hash {
    int N;
    string S;
    vector <ll> pwr, ipo, sum;
    ll BASE = 31;
    ll MOD = 1e9+7;
    
    inline ll madd(ll a, ll b) { return (a+b)%MOD; }
    inline ll mmul(ll a, ll b) { return (a*b)%MOD; }
    inline void add(ll &a, ll b) { a = madd(a, b); }
    inline void mul(ll &a, ll b) { a = mmul(a, b); }
    
    ll powmod(ll a, ll b ) {
        ll ret = 1LL;
        while(b) {
            if(b&1LL) mul(ret, a);
            mul(a, a);
            b /= 2LL;
        }
        return ret;
    }
    
    ll inv(ll x) { return powmod(x, MOD-2LL); }
    
    void go(string inp) {
        N = (int)inp.size(); S = inp;
        pwr.PB(1); ipo.PB(1);
        for(int i=1; i<N; i++) {
            pwr.PB(mmul(pwr.back(), BASE));
            ipo.PB(inv(pwr.back()));
        }
        sum.PB(0);
        for(int i=0; i<N; i++) sum.PB(madd(sum.back(), mmul(pwr[i], S[i]-'a'+1)));
    }
    
    ll get(int l, int r) {
        return mmul(ipo[l], madd(sum[r+1], MOD-sum[l]));
    }
};
    
string s, t;
int main() {
    cin >> s >> t;
    Hash h_s, h_t;
    h_s.go(s); h_t.go(t);
    
    int n = (int)s.length(); int m = (int)t.length();
    
    int num_match = 0;
    for(int i=0; i+n-1<m; i++) {
        num_match += h_s.get(0, n-1) == h_t.get(i, i+n-1);   
    }
    cout << num_match << '\n';
}
