#include <string>
#include <vector>
#include<algorithm>
#include<iostream>
using namespace std;


int dp[101][101]{ 0, };
bool bPuddles[101][101]{ false };
int solution(int m, int n, vector<vector<int>> puddles) {
    dp[1][1] = 1;

    for (int i = 0; i < puddles.size(); ++i) {
        dp[puddles[i][0]][puddles[i][1]] = 0;
        bPuddles[puddles[i][0]][puddles[i][1]] = true;
    }

    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (bPuddles[i][j] == true) {
                continue;
            }
            // 가장 왼쪽에 있는 경우 위에서 내려오는 것만 ㄱㄴ하다
            if (i == 1) {
                dp[i][j] = max(dp[i][j], (dp[i][j] + dp[i][j - 1]) % 1000000007);
            }
            // 가장 윗쪽에 있는 경우 왼->오 만 ㄱㄴ하다
            else if (j == 1) {
                dp[i][j] = max(dp[i][j], (dp[i][j] + dp[i-1][j]) % 1000000007);
            }
            else {
                dp[i][j]= max(dp[i][j], (dp[i][j] + dp[i - 1][j] + dp[i][j - 1])% 1000000007);
            }
        }
    }
    
    int answer = dp[m][n];
    return answer;
}

//void main() {
//    vector<vector<int>> puddles = {{ 2,2 }};
//    cout<<solution(4, 3, puddles);
//
//}