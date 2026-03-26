#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std;
vector<vector<int>> graph;
int n{}, m{}, v{};
const int maxInt = 1001;

void dfs(int node) {
	bool visited[maxInt]{};
	stack<int> s;
	s.push(node);
	int currentNode;
	cout << node << " ";
	visited[node] = true;
	while (!s.empty()) {
		currentNode = s.top();
		s.pop();
		for (int i : graph[currentNode]) {
			if (!visited[i]) {
				s.push(currentNode); //이걸 집어넣는 이유 : current Node랑 연결된 노드를 다 읽기 위해.	
				s.push(i);						
				visited[i] = true;
				cout << i << " ";
				break;
			}
		}
	}

}

void bfs(int node) {
	bool visited[maxInt]{};
	queue<int> q;
	q.push(node);
	int currentNode;
	cout << node << " ";
	visited[node] = true;
	while (!q.empty()) {
		currentNode = q.front();
		q.pop();
		for (int i : graph[currentNode]) {
			if (!visited[i]) {
				q.push(i);
				visited[i] = true;
				cout << i << " ";
			}
		}
	}

}



int main() {
	cin >> n >> m >> v;
	graph = vector<vector<int>>(n + 1);
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);
	}
	for (int i = 1; i <= n; ++i) {
		sort(graph[i].begin(), graph[i].end());
	}
	dfs(v);
	cout << '\n';
	bfs(v);

	
}