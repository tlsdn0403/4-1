#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

// 도시 개수, 버스 노선의 수
int city, bus;

// 가중치 , 도착 지점
vector<pair<int, int>> graph[50001];

int d[50001]{1e9,};

void dikstra(int start) {
	
	

	fill(d, 50001 + d, 1e9);

	d[start] = 0;
	// 자료형 , 내부적으로 저장할 컨테이너, 비교기준
	priority_queue<pair <int, int>, vector<pair<int, int>>, greater<pair<int, int>> > pq;

	// 가중치, 시작지점
	pq.push({0, start});

	while (!pq.empty()) {
		int currentNode = pq.top().second;
		int currentWeight = pq.top().first;

		pq.pop();

		if (d[currentNode] < currentWeight) {
			continue;
		}

		// currentNode랑 연결된 노드 다 가져옴
		for (int i = 0; i < graph[currentNode].size(); ++i) {
			int w = graph[currentNode][i].first;
			int end = graph[currentNode][i].second;

			if (currentWeight + w < d[end]) {
				d[end] = currentWeight + w;
				pq.push({ d[end] , end });
				
			}
		}
	}
}

int main() {
	cin >> city >> bus;

	for (int i = 0; i < bus; ++i) {
		int s, e ,w;
		cin >> s >> e >> w;
		graph[s].push_back({ w , e });
	}

	int startPoint, EndPoint;

	cin >> startPoint >> EndPoint;

	dikstra(startPoint);
	
	cout << d[EndPoint];
	
}
