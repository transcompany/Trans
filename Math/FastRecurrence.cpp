//O(k^2log(n))
//Solve recursive formula: x[n + 1] = a[0] * x[n] + a[1] * x[n - 1] + ... + a[k - 1] * x[n - k + 1]
const int MOD = (int) 1e9 + 7;
const int MAXN = 1000 + 10;
int k; int x[MAXN]; int a[MAXN]; int c[MAXN][MAXN]; int d[MAXN][MAXN]; 
void build() {
	c[0][0] = 1;
	for (int i = 1; i < (k << 1); i++) {
		for (int j = 0; j < k; j++) {
			c[i][j] = (long long) c[i - 1][0] * a[j] % MOD;
			if (j < k - 1) {
				c[i][j] = (c[i][j] + c[i - 1][j + 1]) % MOD;
			}
		}
	}
	for (int i = 0; i < k; i++) {
		d[0][i] = a[k - i - 1];
	}
	for (int i = 1; i < k; i++) {
		d[i][0] = (long long) d[i - 1][k - 1] * a[k - 1] % MOD;
		for (int j = 1; j < k; j++) {
			d[i][j] = ((long long) d[i - 1][k - 1] * a[k - j - 1] + d[i - 1][j - 1]) % MOD;
		}
	}
}
vector<int> calc(long long n) {
	if (n < k) {
		vector<int> res(k, 0);
		res[n] = 1;
		return res;
	}
	if (n & 1) {
		vector<int> r = calc(n - 1);
		vector<int> res(k, 0);
		res[0] = (long long) r[k - 1] * a[k - 1] % MOD;
		for (int i = 1; i < k; i++) {
			res[i] = ((long long) r[k - 1] * a[k - i - 1] + r[i - 1]) % MOD;
		}
		return res;
	}
	else {
		vector<int> r = calc(n >> 1);
		vector<int> s(k << 1, 0);
		for (int i = 0; i < k; i++) {
			for (int j = 0; j < k; j++) {
				s[i + j] = (s[i + j] + (long long) r[i] * r[j]) % MOD;
			}
		}
		vector<int> res(k, 0);
		for (int i = 0; i < k; i++) {
			res[i] = s[i];
		}
		for (int i = k; i < (k << 1); i++) {
			for (int j = 0; j < k; j++) {
				res[j] = (res[j] + (long long) s[i] * d[i - k][j]) % MOD;
			}
		}
		return res;
	}
}
vector<int> firstrow(long long n) {
	vector<int> r = calc(n);
	vector<int> res(k, 0);
	for (int i = 0; i < k; i++) {
		for (int j = 0; j < k; j++) {
			res[j] = (res[j] + (long long) r[i] * c[i][j]) % MOD;
		}
	}
	return res;
}
int nthelement(long long n) {
	if (n < k) return x[n] % MOD;
	vector<int> r = firstrow(n - k + 1);
	int res = 0;
	for (int i = 0; i < k; i++) {
		res = (res + (long long) r[i] * x[k - i - 1]) % MOD;
	}
	return res;
}

int main() {
	srand(time(NULL));
	k = 1000;
	for (int i = 0; i < k; i++) {
		x[i] = abs(rand());
		a[i] = abs(rand());
	}
	build();
	int n = abs(rand()) % 2000 + 1000;
	int y[n + 1];
	for (int i = 0; i < k; i++) {
		y[i] = x[i];
	}
	for (int i = k; i <= n; i++) {
		y[i] = 0;
		for (int j = 0; j < k; j++) {
			y[i] = (y[i] + (long long) a[j] * y[i - j - 1]) % MOD;
		}
	}
	if (nthelement(n) == y[n]) {
		cout << "Correct!\n";
	}
	else {
		cout << "Wrong!\n";
	}
	return 0;
}
