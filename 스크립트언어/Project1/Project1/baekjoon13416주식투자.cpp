#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int main() {
	int testCase{};
	cin >> testCase;
	vector<int> answer;
	for(int i = 0; i < testCase; i++) {
		int n{};
		cin >> n;
		int result{};
		vector<vector<int>> company(n, vector<int>(3, 0));
		for(int j = 0; j < n; j++) {
			int a{}, b{}, c{};
			cin >> a >> b >> c;
			company[j][0] = a;
			company[j][1] = b;
			company[j][2] = c;
		}
		for(int j = 0; j < n; j++) {
			sort(company[j].begin(), company[j].end());
			if (company[j][2] > 0) {
				result += company[j][2];
			}
		}
		answer.push_back(result);
	}
	for(int i: answer) {
		cout << i << "\n";
	}
}