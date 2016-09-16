#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
#define N 100005
#define K 202

int n, k; ll cum[N];
ll curc[N], curm[N], curi[N], curlen, advc[N], advm[N], advi[N], advlen, dp;
int tr[K][N], ans[K];
void ins(ll c, ll m, ll i) {
	if (advlen && m == advm[advlen-1]) {
		if (c > advc[advlen-1]) advlen--;
		else return;
	}
	while (advlen >= 2 && (long double) (c - advc[advlen-2])*(advm[advlen-1] - m) > (long double) (c - advc[advlen-1])*(advm[advlen-2] - m)) advlen--;
	advc[advlen] = c; advm[advlen] = m; advi[advlen++] = i;
}
void swp() {
	swap(curc, advc); swap(curm, advm); swap(curi, advi); swap(curlen, advlen);
	advlen = 0;
}
int main() {
	freopen("inp.txt", "r", stdin);
//	freopen("out1.txt", "w", stdout);
//	 freopen("sequence.out", "w", stdout);
	scanf("%d %d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%lld", cum+i);
	for (int i = 1; i <= n; i++) cum[i] += cum[i-1];
	for (int i = 1; i <= n; i++) ins(-(cum[i]*cum[i]), cum[i], i);
	swp();
	for (int lay = 1; lay <= k; lay++) {
		int hllpnt = 0;
		for (int i = lay+1; i <= n; i++) {
			ll qx = cum[i];
			while (hllpnt+1 < curlen && curi[hllpnt+1] < i && curm[hllpnt]*qx + curc[hllpnt] <= curm[hllpnt+1]*qx + curc[hllpnt+1]) hllpnt++;
			dp = curm[hllpnt]*qx + curc[hllpnt];
//			printf("%lld %lld %lld %lld\n", curm[hllpnt], curc[hllpnt], qx, dp);
//			printf("%lld\n", dp);
			tr[lay][i] = curi[hllpnt];
			if (i < n) ins(dp - cum[i]*cum[i], cum[i], i);
		}
		swp();
	}
	printf("%lld\n", dp);
	int trn = n, trk = k;
	while (trk) {
		trn = tr[trk][trn]; 
		trk--;
		ans[trk] = trn;
	}	
	for (int i = 0; i < k; i++) printf("%d%c", ans[i], i==k-1 ? '\n' : ' ');

	return 0;
}
