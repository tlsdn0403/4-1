#include <iostream>
#include <string>
#include <queue>

using namespace std;

int n, m;
int graph[101][101];
int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

int bfs(int x, int y) {
    queue<pair<int, int>> q;
    q.push({ x, y });

    while (!q.empty()) {
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;

            if (graph[nx][ny] == 1) {
                graph[nx][ny] = graph[cx][cy] + 1;
                q.push({ nx, ny });
            }
        }
    }
    return graph[n - 1][m - 1];
}


int main() {
    cin >> n >> m;

    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < m; ++j) {
            graph[i][j] = s[j] - '0';
        }
    }

    cout << bfs(0, 0) << '\n';
}