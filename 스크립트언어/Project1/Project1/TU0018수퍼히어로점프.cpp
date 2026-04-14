#include<iostream>
#include<queue>
#include<vector>

using namespace std;

int n{}, m{}, start{}, target{};
vector<vector<int>> graph;

int bfs() {

	bool visited[3501]{};
	int answer[3501]{};
	queue<int> q;
	q.push(start);
	int currentNode;
	visited[start] = true;
	answer[start] = 0;
	while (!q.empty()) {
		currentNode = q.front();
		q.pop();
		for (int i : graph[currentNode]) {
			if (!visited[i]) {
				q.push(i);
				visited[i] = true;
				answer[i] = answer[currentNode] + 1;
			}
		}
	}
	return answer[target];
}


int main() {
	cin >> n >> m;
	graph = vector<vector<int>>(n + 1);
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	cin >> start >> target;

	cout<< bfs();

}