#include<iostream>
#include<vector>
#include<algorithm>
int dp[30001];

using namespace std;
int n;

int main() {
	cin >> n;

	dp[1] = 0;

	for (int i = 2; i < n; ++i) {
		dp[i] = dp[i - 1] + 1;

		//2·Î ³ª´©¾î ¶³¾îÁü
		if (i % 2 == 0) {
			dp[i] = min(dp[i], dp[i / 2] + 1);
		}
		if (i % 3 == 0) {
			dp[i] = min(dp[i], dp[i / 3] + 1);

		}
		if (i % 5 == 0) {
			dp[i] = min(dp[i], dp[i / 5] + 1);
		}
	}
}