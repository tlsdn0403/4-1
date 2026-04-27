#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int n{}, m{};
vector<int> light;


bool check(long long height) {
	
	int width = 0;
	for (int i = 0; i < m; ++i) {
		if (light[i] - height > width) {
			return false;
		}
		if(i == m-1) {
			if (n - light[i] > height) {
				return false;
			}
		}
		width = light[i] + height;
	}
	return true;
}

int main() {
	cin >> n;
	cin >> m;

	for (int i = 0; i < m; ++i) {
		int num;
		cin >> num;
		light.push_back(num);
	}
	long long start = 0;
	long long end = n;

	long long answer = 0;
	while (start <= end) {
		long long height = (start + end) / 2;
		// 중간값으로 조건 만족하는지 검사. 
		if (check(height)) {
			//조건을 만족한다면
			answer = height;
			end = height - 1;
			
		}
		else {
			start = height + 1; //오른쪽 범위 탐색
		}
	}
	cout << answer;
}