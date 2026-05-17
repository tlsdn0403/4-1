#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1e9;

int main() {
    int N, M;
    cin >> N >> M;

    vector<vector<int>> fuel(N, vector<int>(M));

    // 연료 정보 입력
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            cin >> fuel[i][j];
        }
    }

    /*
        0: 왼쪽 아래로 이동   
        1: 바로 아래로 이동  
        2: 오른쪽 아래로 이동 

        dp[i][j][d]:
        i행 j열에 도착했을 때,
        직전에 사용한 방향이 d인 경우의 최소 연료
    */
    // 3차원 DP 배열
    vector<vector<vector<int>>> dp(
        N, vector<vector<int>>(M, vector<int>(3, INF))
    );

    // 첫 번째 줄에서는 어느 칸에서나 출발 가능하다.
    // 아직 이동 방향이 없으므로 세 방향 모두 같은 값으로 초기화한다.
    for (int j = 0; j < M; j++) {
        for (int d = 0; d < 3; d++) {
            dp[0][j][d] = fuel[0][j];
        }
    }

    // 두 번째 줄부터 마지막 줄까지 내려가며 DP 계산
    for (int i = 1; i < N; i++) {
        for (int j = 0; j < M; j++) {
            for (int d = 0; d < 3; d++) {
                int prevCol;

                // 현재 방향 d로 i행 j열에 왔다면,
                // 이전 행에서 어느 열에 있었는지 계산한다.
                if (d == 0) {
                    prevCol = j + 1; // 왼쪽 아래로 이동해서 현재 칸에 도착
                }
                else if (d == 1) {
                    prevCol = j;     // 바로 아래로 이동
                }
                else {
                    prevCol = j - 1; // 오른쪽 아래로 이동해서 현재 칸에 도착
                }

                // 이전 열이 범위를 벗어나면 이동 불가능
                if (prevCol < 0 || prevCol >= M) {
                    continue;
                }

                // 같은 방향으로 두 번 연속 이동할 수 없으므로
                // 이전 방향 prevD와 현재 방향 d가 달라야 한다.
                for (int prevD = 0; prevD < 3; prevD++) {
                    if (prevD == d) {
                        continue;
                    }

                    dp[i][j][d] = min(
                        dp[i][j][d],
                        dp[i - 1][prevCol][prevD] + fuel[i][j]
                    );
                }
            }
        }
    }

    int answer = INF;

    // 마지막 줄의 모든 칸, 모든 마지막 방향 중 최솟값을 찾는다.
    for (int j = 0; j < M; j++) {
        for (int d = 0; d < 3; d++) {
            answer = min(answer, dp[N - 1][j][d]);
        }
    }

    cout << answer << '\n';

    return 0;
}