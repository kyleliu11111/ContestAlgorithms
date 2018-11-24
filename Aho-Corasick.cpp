#include <bits/stdc++.h>

const int sigma = 26;

template <int SZ> struct Aho {
	int to[SZ][sigma], link[SZ], trans[SZ][sigma], sz = 0;
	int term[SZ];
	void ins(string s, int val) {
		int u = 0;
		for(char ch : s) {
			int c = ch - 'a';
			if(!to[u][c]) to[u][c] = ++sz;
			u = to[u][c];
		} term[u] += val;
	}
	
	void push_links() {
		link[0] = -1;
		queue <int> todo; todo.push(0);
		while(todo.size()) {
			int u = todo.front(); todo.pop();
			for(int c=0; c<sigma; c++) if(to[u][c]) {
				int v = to[u][c];
				int k = link[u];
				while(k != -1 && !to[k][c]) k = link[k];
				if(k == -1) link[v] = 0;
				else link[v] = to[k][c];	
				if(link[v]) term[v] += term[link[v]];
				todo.push(to[u][c]);
			}
		}
		
		for(int i=0; i<=sz; i++) for(int c=0; c<sigma; c++) {
			int k = i;
			while(k > -1 && !to[k][c]) k = link[k];
			if(k == -1) trans[i][c] = 0;
			else trans[i][c] = to[k][c];
		}
	}
};

int main() {
}
