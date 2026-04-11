#include <iostream>
#include <string>
#include <queue>

using namespace std;

int n, m;
int graph[1001][1001];
int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };
int maxNum = 0;
queue<pair<int, int>> q;

void bfs() {

    while (!q.empty()) {
        int cx = q.front().first;
        int cy = q.front().second;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) continue;
            maxNum = max(maxNum, graph[cx][cy]);
           
            
            if (graph[nx][ny] == 0) {
                graph[nx][ny] = graph[cx][cy] + 1;
				
                q.push({ nx, ny });
            }
        }
    }
    bool fail = false;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (graph[i][j] == 0) {
                fail = true;
            }
        }
    }

    if (fail) cout << -1;

    else cout << maxNum - 1;
 
}


int main() {
    cin >> m >> n;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> graph[i][j];
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (graph[i][j] == 1) {
                q.push({ i, j });
            }
        }
    }
    bfs();
    
}