#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

using namespace std;

int N;

vector<pair<int, int>> v;
int main() {
	cin >> N;
	priority_queue <int, vector<int>, greater<int>> q; //우선순위 큐.min heap
	for (int i = 0; i < N; i++) {
		int pay, day;
		cin >> pay >> day;
		v.push_back({ day, pay });
	}
	// 날짜 기준으로 우선 정렬
	sort(v.begin(), v.end());
	
	// 날짜순서대로 실행이 된다.
	for(int i =0 ; i < N; i++) {
		int pay = v[i].second;
		int day = v[i].first;
		// pay를 우선순위 큐에 넣는다.
		// day보다 큐의 크기가 커지면 가장 작은 pay를 제거한다.
		q.push(pay);
		// 큐안에 날짜의 개수보다 많이 들어가 있다면 , 페이가 작은 애들을 제거
		if (q.size() > day) {
			q.pop();
		}
	}
	int sum{};
	while (!q.empty()) {
		sum += q.top();
		q.pop();
	}
	cout << sum;
}