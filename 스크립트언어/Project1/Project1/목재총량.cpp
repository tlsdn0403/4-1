#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int M, N;
    cin >> M >> N;

    vector<vector<long long>> dp(M + 1, vector<long long>(N + 1, 0));

    for (int i = 1; i <= M; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            long long x;
            cin >> x;

            dp[i][j] = x+ dp[i - 1][j]+ dp[i][j - 1] - dp[i - 1][j - 1];
        }
    }

    int num;
    cin >> num;

    while (num--)
    {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        long long answer = dp[r2][c2] - dp[r1 - 1][c2] - dp[r2][c1 - 1] + dp[r1 - 1][c1 - 1];
        cout << answer << '\n';
    }

    return 0;
}