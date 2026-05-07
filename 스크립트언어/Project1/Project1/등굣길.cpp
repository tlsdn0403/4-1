#include <string>
#include <vector>
#include<algorithm>
using namespace std;


// 1,000,000,007로 나눈 나머지를 return 하도록
// dp [i][j] : i, j 까지 갈 수 있는 최단 경로의 개수
// dp[i][j] =0  물웅덩이
// dp[i][j] = dp[i-1][j] + dp[i][j-1] i 와 c 가 물웅덩이가 아니라면
vector<vector<int>> dp(101, vector<int>(101, 0)); //m , n 까지 갈 수 있는 최단 경로의 개수


int solution(int m, int n, vector<vector<int>> puddles) {
	vector<vector<int>> puddleList(101, vector<int>(101, 0));
    for (int i = 0; i < puddles.size(); ++i) {
        puddleList[puddles[i][0]][puddles[i][1]] = 1;
    }

    dp[1][2] = 1;
    dp[2][1] = 1;

    for (int i = 1; i < m+1; ++i) {
        for (int j = 1; j < n + 1; ++j) {
            if (i == 1 && j == 1) {
                dp[i][j] = 1;

            }
            else if (puddleList[i][j] == 1) {
				dp[i][j] = 0;
            }
            else {
                dp[i][j] = (dp[i - 1][j] + dp[i][j - 1]) % 1000000007;
            }
           
        }
           
    }
    int answer = dp[m][n];
    return answer;
}