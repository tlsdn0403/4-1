#include<iostream>
#include<queue>
#include<algorithm>
#include<vector>
using namespace std;

// 헛갈 , 길 개수
int N, M;
int d[50001];

// [시작점] first: 도착점 , second: 가중치
vector<pair<int,int>> graph[50001];

void dikstra(int start) {
	fill(d, d + 50001, 1e9);

	// 오름 차순 정렬
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

	d[start] = 0;
	// 가중치, 시작점 이렇게 해야 가중치 기준으로 정렬이 됨
	pq.push({ 0, start });

	while (!pq.empty()) {
		int currentDistance = pq.top().first;
		int currentStart = pq.top().second;
		pq.pop();

		if (d[currentStart] < currentDistance) {
			//저장된 가중치값이 작다면 continue
			continue;
		}
		
		for (int i = 0; i < graph[currentStart].size(); ++i) {
			int next = graph[currentStart][i].first;
			int nextWeight = graph[currentStart][i].second;
			
			if (d[next] > currentDistance +nextWeight) {
				d[next] = currentDistance+ nextWeight;
				pq.push({ d[next] , next });
			}
			
		}
	}
}

int main() {
	// 헛간 , 길
	cin >> N >> M;

	for(int i = 0; i < M; i++) {
		int a, b, c;
		cin >> a >> b >> c;

		graph[a].push_back({ b, c});
		graph[b].push_back({ a, c});
	}

	dikstra(1);


	cout << d[N];

}
