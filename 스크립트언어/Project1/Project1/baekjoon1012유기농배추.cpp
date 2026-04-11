#include<iostream>
#include<vector>
#include<cstring>
using namespace std;

int n{}, m{};
int graph[51][51]{};

bool dfs(int x, int y) {

	if (x <= -1 || x >= m || y <= -1 || y >= n) {
		return false;
	}
	if (graph[x][y] == 1) {
		graph[x][y] = 0; //방문처리

		dfs(x + 1, y);
		dfs(x , y + 1);
		dfs(x , y - 1);
		dfs(x - 1, y);
		return true;
	}
	return false;
}

int main() {
	int testCase{};
	cin >> testCase;
	vector<int> result;
	for (int i = 0; i < testCase; ++i) {

		int count{};
		cin >> m >> n >> count;   // m=가로, n=세로 , count 배추 개수
		for (int j = 0; j < count; ++j) {
			int a{}, b{};
			cin >> a >> b;
			graph[a][b] = 1;
		}
		int answer{};
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (dfs(i, j)) {
					answer++;
				}
				//cout << graph[i][j] << ' ';
			}
			/*cout << '\n';*/
		}
		result.emplace_back(answer);
		memset(graph, 0, sizeof(graph));
	}
	for(int i : result) {
		cout << i << '\n';
	}

}
