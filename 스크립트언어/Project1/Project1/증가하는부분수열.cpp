#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int n{};
vector<int> v;
int main() {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int num;
		cin >> num;
		v.push_back(num);
	}

	int dp[1001]{};
	for (int i = 0; i < n; ++i) {
		dp[i] = v[i];
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			if (v[i] > v[j]) {
				dp[i] = max(dp[i], dp[j] + v[i]);
			}
		}
	}
	int maxVal = 0;
	for(int i =0 ; i < n; ++i) {
		maxVal = max(maxVal, dp[i]);
	}
	cout << maxVal;
}