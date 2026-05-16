#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

int n{};

int main() {
	cin >> n;
	vector<pair<int, int>> time;
	
	for (int i = 0; i < n; ++i) {
		int a, b;
		cin >> a >> b;
		time.push_back({ a,b });
	}
	// 걸리는 시간 우선 정렬 아니면 도착시간
	sort(time.begin(), time.end(), [](pair<int, int> a, pair<int, int> b) {
		if (a.second = b.second) return a.first < b.first;
		return  a.second <  b.second;
		});
	int answer{};
	for (auto a : time) {
		if (a.first > answer) {
			answer = a.first + a.second;
		}
		else {
			answer = answer + a.second;
		}
	}
	cout << answer;
}
