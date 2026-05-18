#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;


vector<int> stair;

int N{};
// ∞‘¥‹¿« √˛ , ø¨º”µ» »Ωºˆ
int dp[301][2]{0,};
int main() {
	cin >> N;

	for (int i = 0; i < N; ++i) {
		int num{};
		cin >> num;
		stair.push_back(num);
	}
	//3 ø¨º”¿∏∑Œ ∞Ë¥‹ π‚±‚ x


	dp[0][0] = stair[0];
	dp[1][0] = stair[1];
	dp[1][1] = stair[0] + stair[1];
	for (int i = 2; i < N; ++i) {
		if (i <= N - 1) {
			// 2ƒ≠ ∞«≥ ∂‹ ±◊∑°º≠ ø¨º”µ  »Ωºˆ∞° 0
			dp[i][0] = max(dp[i - 2][0], dp[i - 2][1]) + stair[i];
			// 1π¯ø¨º” 1ƒ≠ π‚±‚
			dp[i][1] = dp[i - 1][0] + stair[i];
		}
		
	}

	cout << max(dp[N-1][0], dp[N-1][1]) << endl;
}