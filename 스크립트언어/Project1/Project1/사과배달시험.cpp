#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 목초지 , 소의 길
int P{}, C{};
// 어떤식으로든 방문을 해야하는 하는곳 PB는 시작지점
int PB, PA1, PA2;

// [출발지] <도착지 , 길이>
vector<pair<int, int>> graph[100001];

int dp[1000001];



void PA1toPA2() {
	fill(dp, dp + 1000001, 1e9);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	dp[PA1] = 0;

	//pa1에서 pa2로 가는 최단거리 구하기
	pq.push({ 0, PA1 });
	while (!pq.empty()) {
		int dist = pq.top().first;
		int current = pq.top().second;
		pq.pop();
		if (dp[current] < dist) {
			continue;
		}
		for (auto& edge : graph[current]) {
			int next = edge.first;
			int nextDist = dist + edge.second;
			if (nextDist < dp[next]) {
				dp[next] = nextDist;
				pq.push({ nextDist, next });
			}
		}
	}
}

void dijkstra() {
	fill(dp, dp + 1000001, 1e9);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	dp[PB] = 0;

	// 거리 , 도착점
	pq.push({ 0, PB });

	while (!pq.empty()) {
		int dist = pq.top().first;
		int current = pq.top().second;
		pq.pop();
		if (dp[current] < dist) {
			continue;
		} 
		for (auto& edge : graph[current]) {
			int next = edge.first;
			int nextDist = dist + edge.second;
			if (nextDist < dp[next]) {
				dp[next] = nextDist;
				pq.push({ nextDist, next });
			}
		}
	}
}

int main() {
	
	cin >> C >> P >> PB >> PA1 >> PA2;
	for (int i = 0; i < C; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		graph[a].push_back({ b, c });
		graph[b].push_back({ a, c });
	}
	dijkstra();
	int answer{};
	answer = min(dp[PA1], dp[PA2]);

	PA1toPA2();
	answer += dp[PA2];

	cout << answer;
	return 0;
}