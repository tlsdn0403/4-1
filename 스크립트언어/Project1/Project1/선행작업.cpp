#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> dp(N + 1, 0);

    for (int i = 1; i <= N; ++i)
    {
        int time, cnt;
        cin >> time >> cnt;

        int maxPrevTime = 0;

        for (int j = 0; j < cnt; ++j)
        {
            int prev;
            cin >> prev;

            maxPrevTime = max(maxPrevTime, dp[prev]);
        }

        dp[i] = maxPrevTime + time;
    }

    int answer = 0;

    for (int i = 1; i <= N; ++i)
    {
        answer = max(answer, dp[i]);
    }

    cout << answer;

    return 0;
}