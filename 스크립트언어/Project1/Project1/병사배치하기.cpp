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

	reverse(v.begin(), v.end());
	int dp[2001];
	for (int i = 0; i < n; ++i) {
		dp[i] = 1;
	}

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < i; ++j) {
			
		}
	}
}