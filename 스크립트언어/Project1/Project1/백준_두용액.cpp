#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>
#include<numeric>
using namespace std;

vector<int> san;

int n;

int main() {
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int num;
		cin >> num;
		san.push_back(num);
	}
	// ¿À¸§
	sort(san.begin(), san.end());
	pair<int, int> answer;

	int minAbs = numeric_limits<int>::max();
	auto start = san.begin();
	auto end = san.begin()+ san.size() -1;

	while (start != end) {
		auto num = *start + *end;
		if (abs(num) < minAbs) {
			minAbs = abs(num);
			answer.first = *start;
			answer.second = *end;
		}
		if (num > 0) {
			--end;
		}
		else {
			++start;
		}
	}
	cout << answer.first << " "<< answer.second;
}