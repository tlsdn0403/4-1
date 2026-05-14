#include<iostream>
#include<queue>
#include<algorithm>

using namespace std;

int N, M;
int d[50001];
vector<pair<pair<int, int>, int>> graph[50001];

void dikstra(int start) {
	priority_queue <pair<int, int>> pq;
	pq.push({ 0, start });
	d[start] = 0;

	while (!pq.empty()) {
		int dist = -pq.top().first;
		int now = pq.top().second;
		pq.pop();
		if (d[now] < dist) {
			continue;
		}

		for(int i = 0; i < graph[now].size(); ++i) {
			int cost = dist + graph[now][i].second;
			if (cost < d[graph[now][i].first]) {
				d[graph[now][i].first] = cost;
				pq.push({ -cost, graph[now][i].first });
			}
		}
	}
}

int main() {
	cin >> N >> M;
	for(int i = 0; i < M; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		graph[a].push_back({ b, c });
		graph[b].push_back({ a, c });
	}
}
