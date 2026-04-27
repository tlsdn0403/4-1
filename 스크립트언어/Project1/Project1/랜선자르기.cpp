#include<iostream>
#include<vector>
using namespace std;

int K, N;
vector<long long> Line;


bool check(long long mid) {
	int count = 0;

	for(int i : Line) {
		count += i / mid;
	}
	return count >= N;
}


int main(){
	cin >> K >> N;
	long long start = 1;
	long long end = 0;
	
	for(int i = 0; i < K; ++i) {
		long long num;
		cin >> num;
		Line.push_back(num);
		end = max(end, num);
	}
	long long answer{};
	while (start <= end) {
		long long mid = (start + end) / 2;

		// 이 길이가  N개를 만들 수 있다면
		if(check(mid)) {
			//오른쪽 탐색	
			answer = mid;	
			start = mid + 1;
		}
		else {
			// 왼쪽 탐색
			end = mid - 1;
		}
		
	}

	cout << answer;
}