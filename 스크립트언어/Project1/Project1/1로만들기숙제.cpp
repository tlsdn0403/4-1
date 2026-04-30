#include<iostream>
#include<vector>
#include<algorithm>
int dp[10000000];

using namespace std;
int n;

int main() {
	cin >> n;

	if (n <= 2) {
		dp[1] = 0;
		dp[2] = 1;
	}

	for (int i = 2; i <= n; ++i) {
		dp[i] = dp[i - 1] + 1;

		//2·Î ³ª´©¾î ¶³¾îÁü
		if (i % 2 == 0) {
			dp[i] = min(dp[i], dp[i / 2] + 1);
		}
		if (i % 3 == 0) {
			dp[i] = min(dp[i], dp[i / 3] + 1);
		}
	}

	cout << dp[n];
}