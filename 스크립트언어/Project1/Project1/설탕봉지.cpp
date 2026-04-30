#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;



int n;

int main() {
	cin >> n;

	vector<int> dp(n+1, 5001);
	int num[2] = { 3,5 };
	dp[0] = 0;
	
	for (int i = 0; i < 2; ++i) {
		for (int j = num[i]; j <= n; ++j) {
			if (dp[j - num[i]] != 5001) {
				dp[j] = min(dp[j], dp[j - num[i]] + 1);
			}
		}
	}
	if (dp[n] == 5001) {
		dp[n] = -1;
	}
	cout << dp[n];
}