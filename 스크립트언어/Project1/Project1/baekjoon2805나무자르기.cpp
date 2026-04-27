#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int n{}, m{};
vector<int> tree;
bool check(long long mid) {
	long long total{}; //잘린 나무길이의 합

	for (int i : tree) {
		if (i > mid) {
			total += i - mid; //자르고 남은 길이를 누적
		}
	}

	return total >= m; //잘린 나무길이의 합이 m보다 크거나 같은지

}


int main() {
	cin >> n >> m;
	
	for (int i = 0; i < n; ++i) {
		int num;
		cin >> num;
		tree.push_back(num);
	}
	long long start = 0;
	long long end = 1000000000;

	long long answer{};
	while (start <= end) {
		long long mid = (start + end) / 2;
		// 중간값으로 조건 만족하는지 검사. 
		if (check(mid)) {
			//조건을 만족한다면
			answer = mid;
			start = mid + 1; //오른쪽 범위 탐색
		}
		else {
			end = mid - 1;
		}
	}
	cout << answer;
}