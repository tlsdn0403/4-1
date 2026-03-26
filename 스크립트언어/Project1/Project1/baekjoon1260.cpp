#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
using namespace std;

int n{}, m{}, v{};
vector<vector<int>> graph;
bool visited[1001]{};
bool d_visited[1001]{};

void dfs(int start) {
	stack<int> s;
	s.push(start);
	d_visited[start] = true;
	while (!s.empty()) {
		int nx = s.top();
		s.pop();
		cout << nx << " ";
		sort(graph[nx].begin(), graph[nx].end(), [](int a, int b) {
			return a > b;
			});
		for (int i : graph[nx]) {
			if (!d_visited[i]) {
				d_visited[i] = true;
				s.push(i);
			}
		}
	}
}

void bfs(int start){
	queue<int> q;
	q.push(start);
	visited[start] = true;
	while (!q.empty()) {
		int nx = q.front();
		q.pop();

		cout << nx << " ";
		sort(graph[nx].begin(), graph[nx].end(), [](int a, int b) {
			return a < b;
			});
		for (int i : graph[nx]) {
			if (!visited[i]) {
				q.push(i);
				visited[i] = true;
			}
			
		}
	}
}

int main() {
	cin >> n >> m >> v;
	graph.resize(n+1);

	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		graph[a].push_back(b);
		graph[b].push_back(a);  // 빠진 부분
	}
	dfs(v);
	cout << '\n';
	bfs(v);
}