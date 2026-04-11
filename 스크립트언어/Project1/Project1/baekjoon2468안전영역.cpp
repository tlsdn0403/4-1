#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

int n{};
int graph[101][101];
int visited[101][101];
bool dfs(int x, int y ,int num) {

	if (x <= -1 || x >= n || y <= -1 || y >= n) {
		return false;
	}
	// 안전하고 방문 x
	if (graph[x][y] > num && !visited[x][y]) {
		visited[x][y] = 1; //방문처리

		dfs(x + 1, y , num);
		dfs(x , y + 1, num);
		dfs(x , y - 1 , num);
		dfs(x - 1, y , num);

		return true;
	}
	return false;
}

int main() {
	cin >> n;
	int maxHeight{};
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> graph[i][j];
			maxHeight = max(maxHeight, graph[i][j]);
		}
	}
	int maxAnswer{};
	

	for (int k = 0; k < maxHeight; ++k) {
		int answer{};
		memset(visited, 0, sizeof(visited));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < n; ++j) {
				if (dfs(i, j , k)) {
					answer++;
				}
			}
		}
		maxAnswer = max(maxAnswer, answer);
	}
	
	cout << maxAnswer;

}