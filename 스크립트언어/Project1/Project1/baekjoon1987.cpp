#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<algorithm>
using namespace std;

int row{}, col{};
char board[26][26];
bool visited[26];

int dx[4] = { 1, -1, 0, 0 };
int dy[4] = { 0, 0, 1, -1 };
int maxNum{};
void dfs(int x, int y , int count) {
	maxNum = max(maxNum, count);
	if (x <= -1 || x >= row || y <= -1 || y >= col) {
		return;
	}
	int boardNum = board[x][y] - 'A';
	// 이거 안넣어주니까 터짐
	if (visited[boardNum]) {
		return;
	}
	if (!visited[boardNum]) {
		visited[boardNum] = true;
		for (int i = 0; i < 4; ++i) {
			dfs(x+dx[i],y+ dy[i], count+1);
		}
	}
	visited[boardNum] = false;
	
}

int main() {
	cin >> row >> col;

	for (int i = 0; i < row; ++i) {
		string s;
		cin >> s;
		for (int j = 0; j < col; ++j) {
			if (j >= 26)break;
			board[i][j] = s[j];
		}
	}
	//for (int i = 0; i < row; ++i) {
	//	for (int j = 0; j < col; ++j) {
	//		cout << board[i][j];
	//	}
	//	cout<<'\n';
	//}
	dfs(0, 0 ,0);
	cout << maxNum;

}