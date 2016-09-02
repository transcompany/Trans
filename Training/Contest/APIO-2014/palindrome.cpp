//This is getting accepted!
//Palindromic tree sol
#include<bits/stdc++.h>

using namespace std;

#define ms(s, n) memset(s, n, sizeof(s))
#define FI first
#define SE second
#define pb push_back
#define mp make_pair
#define ll long long
#define sz(a) ((int)(a).size())
#define __builtin_popcount __builtin_popcounll

typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef pair<int, pii> ppi;

const double PI = acos(0) * 2;
const double EPS = 1e-8;
const ll MOD = 51123987;
const int MAXN = 3e5 + 5;
const int oo = 1e9;
const double foo = 1e30;

template<class T> int getbit(T s, int i) { return (s >> i) & 1; }
template<class T> T onbit(T s, int i) { return s | (T(1) << i); }
template<class T> T offbit(T s, int i) { return s & (~(T(1) << i)); }
template<class T> int cntbit(T s) { return __builtin_popcounll(s);}

inline void addmod(int& a, int val, int p = MOD) {if ((a = (a + val)) >= p) a -= p;}
inline void submod(int& a, int val, int p = MOD) {if ((a = (a - val)) < 0) a += p;}
inline int mult(int a, int b, int p = MOD) {return (ll) a * b % p;}

const int MAXC = 26;

struct PalindromeTree {
	int next[MAXN][MAXC], fail[MAXN];
	ll cnt[MAXN];
	int num[MAXN], len[MAXN], s[MAXN];
	int last, n, p;
	int newnode(int l) {
		for(int i = 0; i < MAXC; i++) next[p][i] = 0;
		cnt[p] = num[p] = 0;
		len[p] = l;
		return p++;
	}
	void init() {
		p = 0;
		newnode(0); newnode(-1);
		n = last = 0;
		s[n] = -1; fail[0] = 1;
	}
	int getfail(int x) {
		while (s[n - len[x] - 1] != s[n]) x = fail[x];
		return x;
	}
	int add(char c) {
		c -= 'a';
		s[++n] = c;
		int cur = getfail(last);
//		cout << cur << endl;
		if(next[cur][c] == 0) {
			int now = newnode(len[cur] + 2);
			fail[now] = next[getfail(fail[cur])][c];
			next[cur][c] = now;
			num[now] = num[fail[now]] + 1;
		}
		last = next[cur][c];
		cnt[last]++;
		return num[last];
	}
	ll count() {
		for (int i=p-1; i>=0; i--) cnt[fail[i]] += cnt[i];
		ll ret = -1;
		for (int i=0; i<p; i++) {
			ret = max(ret, (ll) len[i] * cnt[i]);
		}
		return ret;
	}
} PA;

int n;
char s[300100];

int main() {
#ifndef ONLINE_JUDGE
    freopen("inp.txt", "r", stdin);
//    freopen("out.txt", "w", stdout);
#endif

	scanf("%s", s);
//	cout << n << " " << s << endl;
	PA.init();
	int n = strlen(s);
	for (int i=0; i<n; i++) {
		PA.add(s[i]);
	}
	
	ll ans = PA.count();
	
	cout << ans;

}
