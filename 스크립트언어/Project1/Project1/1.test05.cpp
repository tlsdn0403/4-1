#include<queue>
#include<algorithm>
#include<iostream>
using namespace std;

int row{}, col{}, D{};
char board[26][26];
bool visited[26][26];

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };
int maxNum{};
void dfs(int x, int y, int count) {
	if (x < 0 || x >= row || y < 0 || y >= col || board[x][y] == 'T') {
		return;
	}

	if (visited[x][y]) {
		return;
	}

	if (x == 0 && y == col - 1) {
		if (count == D) {
			maxNum++;
		}
		return;
	}

	if (count >= D) {
		return;
	}

	visited[x][y] = true;
	for (int i = 0; i < 4; ++i) {
		dfs(x + dx[i], y + dy[i], count + 1);
	}
	visited[x][y] = false;

}

int main() {
	cin >> row >> col >> D;

	for (int i = 0; i < row; ++i) {
		string s;
		cin >> s;
		for (int j = 0; j < col; ++j) {
			if (j >= 26)break;
			board[i][j] = s[j];
		}
	}

	dfs(row-1, 0, 1);
	cout << maxNum;

}