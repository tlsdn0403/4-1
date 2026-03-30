#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

int n{}, m{};
int graph[51][51];

bool dfs(int x, int y) {

	if (x <= -1 || x >= n || y <= -1 || y >= m) {
		return false;
	}
	// 섬이라면
	if (graph[x][y] == 1) {
		graph[x][y] = 0; //방문처리

		dfs(x + 1, y);
		dfs(x + 1, y + 1);
		dfs(x + 1, y-1);
		dfs(x - 1, y);
		dfs(x - 1, y + 1);
		dfs(x -1, y -1);
		dfs(x , y + 1);
		dfs(x, y - 1);
		return true;
	}
	return false;
}

int main() {
	vector<int> result;
	while (true) {
		cin >> m >> n;   // m=가로, n=세로
		if (m == 0 && n == 0) break;

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				cin>> graph[i][j];
			}
		}
		if (n == 5 && m == 4) {
			cout << '\n';
		}
		int answer{};
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (dfs(i, j)) {
					answer++;
				}
			}
		}
		result.emplace_back(answer);
		memset(graph, 0, sizeof(graph));
	}
	for (int i : result) {
		cout << i << '\n';
	}
}