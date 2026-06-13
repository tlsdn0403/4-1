#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>

using namespace std;

int v, e;

// 각 정점의 진입차수(각 정점에 꽃히는 간선의 개수)
int indegree[100001];

vector<int> graph[100001];

void topologysort() {
	vector<int> result;
	queue<int> q;

	for (int i = 1; i <= v; i++) {
		if (indegree[i] == 0) {
			q.push(i);
		}
	}

	while (!q.empty()) {
		int current = q.front();
		q.pop();
		result.push_back(current);
		// 꺼낸 노드랑 이어지는 간선을 제거
		for (int i = 0; i < graph[current].size(); i++) {
			int next = graph[current][i];
			// 진입차수 감소
			indegree[next]--;
			if (indegree[next] == 0) {
				q.push(next);
			}
		}
	}
	
}

int main() {
	cin >> v >> e;
	for (int i = 0; i < e; i++) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		// end 지점의 진입차수를 증가시켜준다
		indegree[b]++;
	}
	topologysort();

	
	return 0;
}