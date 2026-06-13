#include<iostream>
#include<vector>
using namespace std;

// За , ї­
int M, N;


int main() {

	cin >> M >> N;

	vector<vector<long long>> dp(M + 1, vector<long long>(N + 1, 0));

	for (int i = 1; i <= M; ++i) {
		for (int j = 1; j <= N; ++j) {

			long long x;
			cin >> x;

			dp[i][j] = x + dp[i - 1][j] + dp[i][j - 1] - dp[i - 1][j - 1];
		}
	}

	int count{};

	cin >> count;

	vector<int> v;
	while (count > 0) {

		int r1, l1, r2, l2;

		cin >> r1 >> l1 >> r2 >> l2;

		v.push_back(dp[r2][l2] - dp[r1 - 1][l2] - dp[r2][l1 - 1] + dp[r1 - 1][l1 - 1]);
		count--;
	}

	for (int i : v) {
		cout << i << endl;
	}
}