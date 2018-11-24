#include <bits/stdc++.h> 

using namespace std;

#define PB push_back

const int MAXN = 1e5 + 1;
const int MAXL = 17;

int N, Q;
int rmq[MAXL][MAXN];

int get_min(int l, int r) {
    int ret = min(rmq[0][l], rmq[0][r]);
    for(int i=MAXL-1; i>=0; i--) 
        if(l + (1<<i) - 1 <= r) {
            ret = min(ret, rmq[i][l]);
            l += (1<<i);
        }
    return ret;
}
    
int main(void)
{
	ios_base::sync_with_stdio(false);
	cin.tie(0);
    cin >> N >> Q;
    for(int i=1; i<=N; i++) cin >> rmq[0][i];
    
    for(int i=1; i<MAXL; i++) for(int j=1; j+(1<<i)-1<=N; j++) {
        rmq[i][j] = min(rmq[i-1][j], rmq[i-1][j + (1<<(i-1))]);
    }
    
    for(int i=0; i<Q; i++) {
        int l, r;
        cin >> l >> r;
        cout << get_min(l, r) << '\n';
    }
}
