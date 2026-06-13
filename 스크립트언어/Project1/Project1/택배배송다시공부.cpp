#include<iostream>
#include<vector>
#include<queue>
using namespace std;

// 헛간 , 소들의 길
int N{}, M{};

// [시작점] (가중치 , 도착점)
vector<pair<int, int>> graph[50001];
int d[50001];


void dijkstra(int start) {

	// d의 값 최대로 해둠.
	fill(d, d + 50001, 1e9);
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;

	
	// 가중치 , 도착점.
	pq.push({ 0 , start });
	
	d[start] = 0;
	while (!pq.empty()) {
		int currentWeight = pq.top().first;
		int currentNode = pq.top().second;

		pq.pop();
		if (d[currentNode] < currentWeight ) {
			continue;
		}

		for (int i = 0; i < graph[currentNode].size(); ++i) {
			int nextWeight = graph[currentNode][i].first;
			int nextNode = graph[currentNode][i].second;

			if (d[nextNode] > nextWeight + currentWeight) {
				d[nextNode] = nextWeight + currentWeight;
				pq.push({ nextWeight + currentWeight  , nextNode });
			}
		}
	}
}


int main() {

	cin >> N >> M;

	for (int i = 0; i < M; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		graph[a].push_back({ c,b });
		graph[b].push_back({ c,a });
	}

	dijkstra(1);

	cout << d[N];
}