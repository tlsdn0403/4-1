/*
 존의 농장에는 1번부터 N번까지 번호가 매겨진 소가 있다. 
 각 소의 젖을 짜는 데는 정해진 시간이 걸린다. 몇몇 소들은 특정 소의 젖을 먼저 짜야만 젖을 짤 수 있다는 선행 제약 조건이 있다. 
 소들의 젖 짜는 시간과 선행 조건이 주어질 때, 모든 소의 젖을 짜는 데 필요한 최소 시간을 구하시오.  
 (동시에 여러 마리의 젖을 짤 수 있다고 가정한다.)

	input:
		7
		5 0
		1 1 1
		3 1 2
		6 1 1
		1 2 2 4
		8 2 2 4
		4 3 3 5 6

	output:
		20
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;

	vector<vector<int>> graph(N + 1);
	vector<int> in_degree(N + 1, 0); // 진입 차수 배열
	vector<int> time(N + 1, 0);      // 각 소별 순수 소요 시간
	vector<int> dp(N + 1, 0);        // 해당 소까지 완료하는 데 걸리는 '누적 최대 시간'

	for (int i = 1; i <= N; ++i) {
		int t, k;
		cin >> t >> k;
		time[i] = t;
		dp[i] = t; // 초기 세팅: 최소 내 시간만큼은 무조건 걸림

		for (int j = 0; j < k; ++j) {
			int pre;
			cin >> pre;
			graph[pre].push_back(i); // pre가 끝나야 i를 할 수 있음
			in_degree[i]++;          // i의 진입 차수 증가
		}
	}

	queue<int> q;

	for (int i = 1; i <= N; ++i) {
		if (in_degree[i] == 0) q.push(i);
	}

	while (!q.empty()) {
		int curr = q.front();
		q.pop();

		for (int next : graph[curr]) {
			// [핵심] next를 시작하기 위해 기다려야 하는 최대 시간 갱신
			dp[next] = max(dp[next], dp[curr] + time[next]);

			in_degree[next]--; // 선행 조건 하나 해결
			if (in_degree[next] == 0) {
				q.push(next);
			}
		}
	}

	// 3. 모든 소를 다 짜는 데 걸린 시간은 dp 배열 중 최댓값
	int total_time = 0;
	for (int i = 1; i <= N; ++i) {
		total_time = max(total_time, dp[i]);
	}

	cout << total_time << '\n';
	return 0;
}