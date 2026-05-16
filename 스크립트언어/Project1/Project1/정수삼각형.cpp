#include <string>
#include <vector>
#include<algorithm>
#include<iostream>
using namespace std;


int solution(vector<vector<int>> triangle) {
    int answer = 0;
	vector<vector<int>> dp(triangle.size(), vector<int>(triangle.size(), 0));
	dp[0][0] = triangle[0][0];
	// 0,0 넣었으니까 반복문 i = 1부터
	for (size_t i = 1; i < triangle.size(); ++i) {
		for (int j = 0; j < triangle[i].size(); ++j) {
			// 가장 왼쪽에 있는 경우
			if (j == 0) {
				dp[i][j] = max(dp[i][j], triangle[i][j] + dp[i-1][j]);
			}
			//가장 오른쪽에 있는 경우
			else if (j == triangle[i].size() - 1) {
				dp[i][j] = max(dp[i][j], triangle[i][j] + dp[i-1][j - 1]);
			}
			else {
				dp[i][j] =  max(triangle[i][j] + dp[i - 1][j - 1] , triangle[i][j] + dp[i-1][j]);
			}
		}
	}
	for (int j = 0; j < triangle[triangle.size() - 1].size(); ++j) {
		answer = max(dp[triangle.size() - 1][j], answer);
	}
    return answer;
}

int n;
int main()
{
	int n;
	cin >> n;

	vector<vector<int>> triangle(n);

	for (int i = 0; i < n; ++i)
	{
		triangle[i].resize(i + 1);

		for (int j = 0; j <= i; ++j)
		{
			cin >> triangle[i][j];
		}
	}

	cout << solution(triangle);

	return 0;
}