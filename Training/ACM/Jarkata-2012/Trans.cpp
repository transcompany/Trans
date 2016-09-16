//This is getting accepted!
// I HATE BUG
// God Of The Bugs
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
#define ld long double

typedef pair<int, int> pii;
typedef pair<double, double> pdd;
typedef pair<int, pii> ppi;
typedef pair<ll, int> pli;

const double PI = acos(0) * 2;
const double EPS = 1e-8;
const ll MOD = 1e9 + 7;
const int MAXN = 2e5 + 5;
const int oo = 1e9;
const double foo = 1e30;

template<class T> int getbit(T s, int i) { return (s >> i) & 1; }
template<class T> T onbit(T s, int i) { return s | (T(1) << i); }
template<class T> T offbit(T s, int i) { return s & (~(T(1) << i)); }
template<class T> int cntbit(T s) { return __builtin_popcounll(s);}

inline void addmod(int& a, int val, int p = MOD) {if ((a = (a + val)) >= p) a -= p;}
inline void submod(int& a, int val, int p = MOD) {if ((a = (a - val)) < 0) a += p;}
inline int mult(int a, int b, int p = MOD) {return (ll) a * b % p;}

set<pli> segY[MAXN * 3];
int n, q;
ll x[MAXN], y[MAXN], cX[MAXN], cY[MAXN];
int xk, ek, yk;
ll va, vb, vc, vd, ve, vf, W, H;
int tc, T;

void readInput() {
	cin >> n >> q >> W >> H;
	for (int i=0; i<n; i++) {
		cin >> x[i] >> y[i];
		cX[i] = x[i] + y[i];
		cY[i] = x[i] - y[i];
	}
}

void build (int node, ll l, ll r) {
	if (l > r) return;
	segY[node].clear();
	if (l == r) return;
	int mid = (l + r) >> 1;
	build(node * 2, l, mid);
	build(node * 2 + 1, mid + 1, r);
}

void update(int node, ll l, ll r, ll vx, ll vy, int i) {
	if (vx < l || vx > r) return;
	if (l > r) return;
	if (l <= vx && r >= vx) {
		segY[node].insert(mp(vy, i));
	}
	if (l < r) {
		int mid = (l + r) >> 1;
		update(node * 2, l, mid, vx, vy, i);
		update(node * 2 + 1, mid + 1, r, vx, vy, i);
	}
}

void del(int node, ll l, ll r, ll vx, ll vy, int i) {
	if (vx < l || vx > r) return;
	if (l > r) return;
	if (l <= vx && r >= vx) {
		segY[node].erase(mp(vy, i));
	}
	if (l < r) {
		int mid = (l + r) >> 1;
		del(node * 2, l, mid, vx, vy, i);
		del(node * 2 + 1, mid + 1, r, vx, vy, i);
	}
}

void query(int node, ll l, ll r, ll L, ll R, ll vy1, ll vy2, vector<pli>& v) {
	if (l > R || r < L) return;
	if (L > R) return;
	if (l <= L && R <= r) {
//		cout << L << " "<< R << " " << sz(segY[node]) << endl;
		set<pli>::iterator s = segY[node].lower_bound(mp(vy1, -1));
		set<pli>::iterator e = segY[node].upper_bound(mp(vy2, oo));
		for (set<pli>::iterator it = s; it != e; it++) {
			if (it != segY[node].end() && it->FI <= vy2) v.pb(*it);
//			cout << x[it->SE] << " " << y[it->SE] << endl;
		}
		return;
	}
	if (L < R) {
		int mid = (L + R) >> 1;
		query(node * 2, l, r, L, mid, vy1, vy2, v);
		query(node * 2 + 1, l, r, mid + 1, R, vy1, vy2, v);
	}
}

ll getnewX(int i) {
	ll tmpx = x[i-1];
	ll tmpy = y[i-1];
	ll ret = tmpx * va + tmpy * vb + (ll) i * vc;
	ret %= W;
	return ret;
}

ll getnewY(int i) {
	ll tmpx = x[i-1];
	ll tmpy = y[i-1];
	ll ret = tmpx * vd + tmpy * ve + (ll) i * vf;
	ret %= H;
	return ret;
}

void solve() {
	readInput();
	build(1, 0, W + H);
	for (int i=0; i<n; i++) {
		update(1, 0, W + H, cX[i], cY[i], i);
	}
	while (q--) {
		cin >> xk >> yk >> ek >> va >> vb >> vc >> vd >> ve >> vf;
		ll x1 = xk + yk - ek;
		x1 = max(x1, 0ll);
		ll x2 = xk + yk + ek;
		x2 = min(x2, W + H);
		ll y1 = xk - yk - ek;
		ll y2 = xk - yk + ek;
		vector<pli> v;
		v.clear();
		query(1, x1, x2, 0, W + H, y1, y2, v);
//		cout << sz(v) << endl;
		for (int i=0; i<sz(v); i++) {
			int idex = v[i].SE;
			del(1, 0, W + H, cX[idex], cY[idex], idex);
//			cout << x[idex] << " "<< y[idex] << endl;
			ll tmpx = getnewX(idex + 1);
			ll tmpy = getnewY(idex + 1);
			x[idex] = tmpx;
			y[idex] = tmpy;
			cX[idex] = x[idex] + y[idex];
			cY[idex] = x[idex] - y[idex];
			update(1, 0, W + H, cX[idex], cY[idex], idex);
		}
	}
	cout << "Case #" << ++tc << ":" << endl;
	for (int i=0; i<n; i++) {
		cout << x[i] << " " << y[i] << endl;
	}
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("inp.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
	
	cin >> T;
	while (T--) {
		solve();
	}

}

