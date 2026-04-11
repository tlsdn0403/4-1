#include <iostream>
#include <string>
#include <queue>
// row 가로 , col 세로
// 물이랑 고슴도치 그냥 같은 큐에 넣으면 되는것;;
// 그리고 물이 한 웅덩이만 있는 것이 아니다.
using namespace std;

struct node {
    int x;
    int y;
    char type;
};
int row, col;
char graph[51][51];
int visited[51][51];
int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };

int bfs(int x, int y , vector<node> waterNodes) {
    queue<node> q;
    node start{ x, y, 'S' };
    for(auto & wnode : waterNodes) {
        q.push(wnode);
	}
	q.push(start);
    while (!q.empty()) {
        int cx = q.front().x;
        int cy = q.front().y;
		char type = q.front().type;
        q.pop();

        for (int i = 0; i < 4; ++i) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (nx < 0 || nx >= row || ny < 0 || ny >= col) continue;

            if (type == '*') {
                if (graph[nx][ny] == '.') {
                    graph[nx][ny] = '*';
					node wnode{ nx, ny, '*' };
                    q.push(wnode);
                }
            }
            else if (type == 'S') {
                if (graph[nx][ny] == '.') {
                    visited[nx][ny] = visited[cx][cy] + 1;
                    graph[nx][ny] = 'S';
					node snode{ nx, ny, 'S' };
                    q.push(snode);
                }
                else if (graph[nx][ny] == 'D') {
                    return visited[cx][cy] + 1;
                }
            }
        }
    }
    return 0;
}

int main() {
    cin >> row >> col;
    int startX{}, startY{};
	vector<node> waterNodes;
    for (int i = 0; i < row; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < col; ++j) {
            graph[i][j] = s[j];
            if (s[j] == 'S') {
				startX = i;
				startY = j;
            }
            if (s[j] == '*') {
				node wnode{ i, j, '*' };
				waterNodes.push_back(wnode);
            }
        }
    }
	int answer = bfs(startX, startY, waterNodes);
    if (answer == 0) {
        cout << "KAKTUS";
    }
    else {
        cout << answer << '\n';
    }
    
}