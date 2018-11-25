/*
Aho-Corasick string searching algorithm implementation

Facts :
Optimal string searching algorithm
Determines all occurences of strings d in a dictionary in a given text T in O(sum{|d|} + |T|) time

How it works:
- Constructs a finite-state machine(automaton) on a trie with suffix links in 
O(sum{|d|} * sigma) time, where sigma is the size of the alphabet
- Memoizes creation of transitions between states with suffix links to ensure linear time
- Based on KMP string matching algorithm

Applications: 
- Find all strings from a given set in a text
- Find the lexicographical smallest string of a given length that doesn't match any given strings
- Find the shortest string containing all given strings

Implemented:
Given a set of N strings of lowercase letters, find the positions of all of their occurances in a text T
*/



#include <bits/stdc++.h>
 
using namespace std;
#define PB push_back
#define A first
#define B second
const int MAXN = 1e5 + 1;
const int sigma = 26;

template <int SZ> struct Aho_Corasick {
	int to[SZ][sigma], trans[SZ][sigma], link[SZ], par[SZ], term[SZ], sz=0;
	char pch[SZ];
	
	// problem-specific 
	vector <pair <int, int> > ends_here[SZ]; int size_dict = 0;
	
	void reset(int u) { link[u] = -1; for(int i=0; i<sigma; i++) trans[u][i] = -1; }
	void insert_string(string s) {
		int u = 0;
		reset(u);
		for(char ch : s) {
			int c = ch - 'a';
			if(!to[u][c]) to[u][c] = ++sz;
			par[to[u][c]] = u, pch[to[u][c]] =  ch;
			u = to[u][c];
			reset(u);
		} term[u] = u; ends_here[u].PB({size_dict++, (int)s.length()});
	}
	int get_link(int u) {
		if(link[u] == -1) {
			if(u == 0 || par[u] == 0) link[u] = 0;
			else link[u] = get_trans(get_link(par[u]), pch[u]);
		} 
		if(!term[u]) term[u] = term[link[u]];
		return link[u];
	}
	int get_trans(int u, char ch) {
		int c = ch - 'a';
		if(trans[u][c] == -1) {
			if(to[u][c]) trans[u][c] = to[u][c];
			else trans[u][c] = u == 0 ? 0 : get_trans(get_link(u), ch);
		}
		return trans[u][c];
	}
};

int N;
string T;
Aho_Corasick <MAXN> AC;
vector <int> occurances[MAXN];
void solve() {
	cin >> N;
	for(int i=0; i<N; i++) {
		string d; 
		cin >> d;
		AC.insert_string(d);
	}
	
	cin >> T;
	int cur = 0;
	for(int i=0; i<T.size(); i++) {
		cur = AC.get_trans(cur, T[i]);
		int tmp = cur;
		while(tmp) {
			for(auto dat : AC.ends_here[tmp]) occurances[dat.A].PB(i - dat.B + 1);
			tmp = AC.term[AC.get_link(tmp)];
		}
	}
	for(int i=0; i<N; i++) {
		for(int occ : occurances[i]) cout << occ << ' ';
		cout << '\n';
	}
}
int main() {
	solve();
}
