/*
Sparse Table
Facts:
- Preprocesses an array to answer decomposable subarray statistics quickly
- Can apply to trees, functional graphs, etc...
How it works:
- Maintain summary statistics for all subarrays of length 2^k for k = [0 ... log(N)]
- Precompute these with dynamic programming
- Any subarray can be decomposed into at most O(log(N)) (and in fact O(1)!) of these subarrays
- Merge precomputed answers to retrieve answers for queries
Applications:
- Preprocess an array to answer subarray min, max, gcd queries in O(logN)
- Preprocess an array to answer subarray min, max queries in O(1)
- Preprocess a tree to answer LCA, path min, max, sum queries in O(logN)
- Compute P'th power of an NxN matrix in O(N^3logP)
Implemented:
- Preprocess an array to answer subarray min queries in O(logN).
*/

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
