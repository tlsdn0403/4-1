#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
int N{};
int main() {
	cin >> N;
	// n+1 크기로 5001로 초기화
	vector<int> dp(N + 1, 5001);

	if (N < 5) {
		if (N == 3) {
			cout << 1;
		}
		else {
			cout << -1;
		}
	}
	else {
		dp[3] = 1;
		dp[5] = 1;
		for (int i = 5; i <= N; ++i) {
			dp[i] = min(dp[i], 1 + dp[i - 3]);
			dp[i] = min(dp[i], 1 + dp[i - 5]);
		}
		if (dp[N] == 5001) {
			cout << -1;
		}
		else {
			cout << dp[N];
		}
	}
	
	
}