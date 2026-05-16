#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
long long n;


int main() {
	cin >> n;
	if (n < 4) {
		if (n == 1) {
			cout << 0;
		}
		else {
			cout << 1;
		}
		return 0;
	}
	
	vector<long long> dp(n+1, 1000000);
	dp[1] = 0;
	dp[2] = 1;
	dp[3] = 1;
	for (int i = 4; i <= n; ++i) {
		//3으로 나누어진다면.
		if (i % 3 == 0) {
			dp[i] = min(dp[i], 1 + dp[i / 3]);
		}
		if (i % 2 == 0) {
			dp[i] = min(dp[i], 1 + dp[i / 2]);
		}
		dp[i] = min(dp[i], 1 + dp[i-1]);
	}

	cout << dp[n];
}