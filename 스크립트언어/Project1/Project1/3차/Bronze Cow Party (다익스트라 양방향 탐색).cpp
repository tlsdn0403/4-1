/*
 N개의 농장에 소들이 한 마리씩 있다. 어느 날 X번 농장에서 파티가 열린다.
 소들은 파티에 참석하기 위해 M개의 단방향 도로를 걸어서 X번 농장으로 가고, 파티가 끝나면 다시 집으로 돌아와야 한다. 
 각 도로마다 소요 시간이 다르다. 소들은 가장 최단 시간으로 오고 간다. 
 오고 가는 데 가장 많은 시간을 소비하는 소의 소요 시간을 구하시오.

	input :
		4 8 2
		1 2 4
		1 3 2
		1 4 7
		2 1 1
		2 3 5
		3 1 2
		3 4 4
		4 2 3
	output :
		10
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int INF = 1e9;
	
vector<int> dijkstra(int start, int N, const vector<vector<pair<int, int>>>& graph) {
	vector<int> dist(N + 1, INF);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	dist[start] = 0;
	pq.push({ 0, start });

	while (!pq.empty()) {
		int cost = pq.top().first;
		int curr = pq.top().second;
		pq.pop();

		if (dist[curr] < cost) continue;

		for (auto& edge : graph[curr]) {
			int next = edge.first;
			int next_cost = cost + edge.second;

			if (next_cost < dist[next]) {
				dist[next] = next_cost;
				pq.push({ next_cost, next });
			}
		}
	}
	return dist;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, M, X;
	cin >> N >> M >> X;

	vector<vector<pair<int, int>>> graph(N + 1);
	vector<vector<pair<int, int>>> reverse_graph(N + 1);

	for (int i = 0; i < M; ++i) {
		int u, v, t;
		cin >> u >> v >> t;
		graph[u].push_back({ v, t });
		reverse_graph[v].push_back({ u, t }); // 간선 방향 뒤집기
	}

	// 1. X에서 각자의 집으로 돌아가는 최단 시간
	vector<int> dist_from_X = dijkstra(X, N, graph);

	// 2. 각자의 집에서 X로 모이는 최단 시간
	vector<int> dist_to_X = dijkstra(X, N, reverse_graph);

	int max_time = 0;
	// 3. 오고 가는 데 걸리는 시간(합)이 가장 큰 값 찾기
	for (int i = 1; i <= N; ++i) {
		max_time = max(max_time, dist_from_X[i] + dist_to_X[i]);
	}

	cout << max_time << '\n';
	return 0;
}