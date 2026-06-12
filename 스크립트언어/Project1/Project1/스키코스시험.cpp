#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 슬로프를 연결하는 지점 , 슬로프 수
int n, m;
vector<pair<int, int>> graph[5001];
int dp[5001];
int startDp[5001];
bool visited[5001];

int dfs(int current) {
	// 이미 방문 했다면 리턴하자
	if (dp[current] != -1) return dp[current];

	dp[current] = 0; 

	for (int i = 0; i < graph[current].size(); ++i) {
		int next = graph[current][i].first;
		int weight = graph[current][i].second;

		dp[current] = max(dp[current], weight + dfs(next));
	}

	return dp[current];
}

int main() {

	cin >> n >> m;
	vector<int> point;

	for (int i = 0; i < n; ++i) {
		// 시작 도착 가중치
		int s, t, c;
		cin >> s >> t >> c;
		graph[s].push_back({ t , c });
	}

	int answer{};
	fill(dp, dp + 5001, -1);
	for (int i = 1; i <= m; ++i) {
		int num = dfs(i);
		answer = max(answer, num);
	}
	cout << answer;
}
