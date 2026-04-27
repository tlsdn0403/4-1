#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

int n{}, c{};
vector<int> House;



int main() {
	cin >> n;
	cin >> c;

	for (int i = 0; i < n; ++i) {
		int num;
		cin >> num;
		House.push_back(num);
	}

	sort(House.begin(), House.end());

	long long start = 1; //최소거리
	long long end = House.back() - House.front(); // 최대거리
	long long answer = 0;

	while (start <= end) {
		long long mid = (start + end) / 2; // 중간값

		int count = 1;  // 첫 번째 집에 공유기 설치

		int prev_house = House[0]; // 이전 집의 위치
		for(int i =1; i<n; ++i) {
			if (House[i] - prev_house >= mid) { // 현재 집과 이전 집의 거리가 중간값 이상인 경우
				count++; // 공유기 설치
				prev_house = House[i];
			}
		}

		if( count >= c) { // 설치한 공유기의 수가 필요한 공유기의 수보다 많거나 같은 경우
			answer = mid; 
			start = mid + 1; 
		}
		else {
			end = mid - 1; 
		}
		
	}
	cout << answer;
}