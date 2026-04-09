#include<iostream>
#include<stack>
#include<vector>

using namespace std;

int n{}, m{};
vector<pair<int, int>> graph;

bool dfs(int deleteNode) {

	bool visited[301]{};
	stack<int> s;

	int start = -1;
	for (int i = 1; i < n + 1; ++i) {
		if (i != deleteNode) {
			start = i;
			break;
		}
	}
	if (start == -1) {
		return false;
	}
	
	s.push(start);

	while (!s.empty()) {
		start = s.top();
		s.pop();
		if (visited[start])continue;
		visited[start] = true;
		for (auto p : graph) {
			if (p.first == start) {
				if (p.second != deleteNode && !visited[p.second]) {
					s.push(p.second);
				}
				
			}
			else if (p.second == start) {
				if (p.first != deleteNode && !visited[p.first]) {
					s.push(p.first);
				}
			}
		}
	}
	for (int i = 1; i <= n ; ++i) {
		if (i == deleteNode)continue;
		if (!visited[i])return false;
	}
	return true;
}


int main() {
	
	cin >> n >> m;
	for (int i = 0; i < m; ++i) {
		pair<int, int> p;
		cin >> p.first >> p.second;
		graph.emplace_back(p);
	}
	vector<int>answer;
	int ansCount{};
	for (int i = 1; i < n + 1; ++i) {
		if (!dfs(i)) {
			ansCount++;
			answer.push_back(i);
		}
	}
	cout << ansCount << '\n';
	for (int i : answer) {
		cout << i << '\n';
	}
}