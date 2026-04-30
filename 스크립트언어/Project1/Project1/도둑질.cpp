#include <string>
#include <vector>
#include<algorithm>
using namespace std;

int dp[1000001];
int dp2[1000001];

int solution(vector<int> money) {

    dp[0] = money[0];
    dp[1] = max(money[0],money[1]);

    dp2[1] = money[1];
    dp2[2] = max(money[1], money[2]);
    for (int i = 2; i < money.size(); ++i) {
        if (i != 2) {
            dp2[i] = max(dp2[i - 2] + money[i], dp2[i - 1]);
        }
        if (i != money.size() - 1) {
            dp[i] = max(dp[i - 2] + money[i], dp[i - 1]);
        }
        
    }
    int answer = max(dp[money.size()-2] , dp2[money.size() - 1]);
    return answer;
}