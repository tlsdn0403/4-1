#include<iostream>
#include<algorithm>
#include<vector>



// n: 행 , m: 열 , t  턴
using namespace std;
int n{}, m{}, t{};

int dp[151][151][151]{0, }; // n ,m , t
int board[151][151]{0,};
int main() {
	//n 행 , m 열
	cin >> n >> m;

	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			int num;
			cin >> num;
			board[i][j] = num;
			dp[i][j][0] = 0;
		}
	}
	cin >> t;

	//for (int i = 0; i < n; i++) {
	//	for (int j = 0; j < m; j++) {

	//		cout << board[i][j] << " ";
	//	}
	//	cout << endl;
	//}
	
	// 방향은 4방향 이동가능 상하좌우
	for(int k = 1; k <= t; k++) {
		for(int i = 0; i < n; i++) {
			for(int j = 0; j < m; j++) {

				if(i > 0) {
					dp[i][j][k] = max(dp[i][j][k], dp[i-1][j][k-1] + board[i][j]);
				}
				if(i < n-1) {
					dp[i][j][k] = max(dp[i][j][k], dp[i+1][j][k-1] + board[i][j]);
				}
				if (j > 0) {
					dp[i][j][k] = max(dp[i][j][k], dp[i][j -1][k - 1] + board[i][j]);
				}
				if (j < m - 1) {
					dp[i][j][k] = max(dp[i][j][k], dp[i][j + 1][k - 1] + board[i][j]);
				}

			}
		}
	}
	int maxNum = 0;
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			maxNum = max(maxNum, dp[i][j][t]);
		}
	}
	cout << maxNum << endl;

}