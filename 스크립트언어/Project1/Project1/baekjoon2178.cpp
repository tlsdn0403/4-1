#include<iostream>
#include<vector>
#include<queue>
#include<string>
using namespace std;
int n, m;

vector<bool> visited;
int graph[100][100];
int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

int bfs(int x, int y) {
	queue<pair<int, int>> q;
	q.push({ x, y });

	while (q.empty()) {
		int nx = q.front().first;
	}
}

int main() {
	cin >> n >> m;
	string s;
	for (int i = 0; i < n; ++i) {
		cin >> s;
		for (int j = 0; j < m; ++j){
			graph[i][j] = s[j] - '0';
		}
	}

}