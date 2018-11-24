#include  <bits/stdc++.h>

using namespace std;

const int MAXN = 5e5 + 1;

template <int SZ> struct SuffixArray {
    int N, M;
    int pre[SZ], rank[SZ], sa[SZ], ht[SZ], tmp[SZ];
    string s;
    
    void radix_sort() {
        for(int i=0; i<=M; i++) pre[i] = 0;
        for(int i=1; i<=N; i++) pre[rank[i]]++;
        for(int i=1; i<=M; i++) pre[i] += pre[i-1];
        for(int i=N; i>0; i--)  sa[pre[rank[tmp[i]]]--] = tmp[i];
    }
    void calc_height()
    {
    	memset(ht, 0, sizeof(ht));
    	int len = 0;
    	for(int i=1; i<=N; i++) {
	    	if(len > 0) len--;
	    	int j = sa[rank[i]-1];
	    	while(i+len <= N && j+len <= N && s[i+len] == s[j+len]) len++;
	    	ht[rank[i]] = len;
	    }   
    }
    void build(int len, string imp) {
        N = len;
        s = imp;
        
        for(int i=1; i<=N; i++) {
            tmp[i] = i;
            rank[i] = (int)s[i];
        }
        M = 266;
        radix_sort();
        for(int p=1; p<N; p=p*2) {
            int tot = 0;
            for(int i=N; i>N-p; i--) tmp[++tot] = i;
	    	for(int i=1; i<=N; i++) if(sa[i]-p >= 1) tmp[++tot] = sa[i]-p;
	    	M = N;
	    	radix_sort();
	    	memset(tmp, 0, sizeof(tmp));
	    	tot = 1, tmp[sa[1]] = 1;
	    	for(int i=2; i<=N; i++) {
	    	    int a1 = rank[sa[i-1]], b1 = -1;
	    	    int a2 = rank[sa[i]], b2 = -1;
	    	    if(sa[i-1] + p <= N) b1 = rank[sa[i-1] + p];
	    	    if(sa[i] + p <= N) b2 = rank[sa[i] + p];
	    	    if((a1 != a2) || (b1 != b2)) ++tot;
	    	    tmp[sa[i]] = tot;
	    	}
	    	memcpy(rank, tmp, sizeof(tmp));
	    	if(tot == N) break;
        }
        calc_height();
    }
};

int main(void)
{
    int N, M;
    string s, t;

    cin >> s >> t;
    M = (int)s.length();
    
    s = '$' + s + '(' + t  + ')';
    N = (int)s.length()-2;
	
	SuffixArray <MAXN> SA;
	SA.build(N, s);
	int ans = 0;
	for(int i=0; i<N; i++) {
		if(SA.ht[i+1] > ans) {
			if(SA.sa[i] <= M && SA.sa[i+1] > M) ans = max(ans, SA.ht[i+1]);
			if(SA.sa[i] > M && SA.sa[i+1] <= M) ans = max(ans, SA.ht[i+1]);
		}
	}
    cout << ans << endl;
}
	
	
