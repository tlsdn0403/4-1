#include<iostream>
#include<vector>

using namespace std;

int n, m;
vector<long long> budget;


bool check(long long mid) {
	long long sum{};
	for (int i = 0; i < budget.size(); ++i) {
		if (budget[i] > mid) {
			sum += mid;
		}
		else {
			sum += budget[i];
		}
		
	}

	return sum <= m;
}


int main() {
	cin >> n;

	for (int i = 0; i < n; ++i) {
		long long num;
		cin >> num;
		budget.push_back(num);
	}
	cin >> m;
	long long sum{};
	long long maxNum{};
	for (int i = 0; i < budget.size(); ++i) {
		sum += budget[i];
		maxNum = max(budget[i], maxNum);
	}

	long long start = 0;
	long long end = maxNum;
	long long answer{};
	while (start <= end) {
		long long mid = (start + end) / 2;

		if (check(mid)) {
			answer = mid;
			start = mid + 1;
			
		}
		else {
			end = mid - 1;
		}
	}
	cout << answer;
}