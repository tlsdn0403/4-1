#include <string>
#include <vector>
#include<algorithm>
using namespace std;

// 0번째 집을 터는 dp테이블
int dp[1000001]{ 0 };
// 0번째 대신 마지막 집을 터는 dp 테이블
int dp1[1000001]{0};


int solution(vector<int> money) {
	dp[0] = money[0];
	dp[1] = max(money[1], dp[0]);

	dp1[1] = money[1];
	dp1[2] = max(money[2], dp1[1]);

	for (int i = 2; i < money.size(); ++i) {
		//dp1은 첫집 X
		if (i != 2) {
			dp1[i] = max(dp1[i - 2] + money[i], dp1[i - 1]);
		}
		// dp는 마지막집 x
		if (i != money.size() - 1) {
			dp[i] = max(dp[i - 2] + money[i], dp[i - 1]);
		}


	}
	int answer = max(dp1[money.size() - 1], dp[money.size() - 2]);
	return answer;
}