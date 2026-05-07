#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int n{};

struct RGB {
	int r;
	int g;
	int b;
};

int main() {
	cin >> n;
	vector<RGB> v(n);

	vector<RGB> dp(n);
	for (int i = 0; i < n; ++i) {
		cin >> v[i].r >> v[i].g >> v[i].b;
	}
	
	for(int i =0 ; i < n; ++i) {
		if (i == 0) {
			dp[i] = v[i];
		}
		else {
			dp[i].r = min(dp[i - 1].g, dp[i - 1].b) + v[i].r;
			dp[i].g = min(dp[i - 1].r, dp[i - 1].b) + v[i].g;
			dp[i].b = min(dp[i - 1].r, dp[i - 1].g) + v[i].b;
		}
	}
	int minNum = min(dp[n - 1].r, dp[n - 1].g);
	minNum = min(minNum, dp[n - 1].b);
	cout << minNum;
}