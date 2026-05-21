#include <string>
#include <vector>

using namespace std;
const int INF = 1e9;

//지점 개수 , 시작 지점 , A의 도착 지점 , B의 도착 지점 , 요금 정보
int solution(int n, int s, int a, int b, vector<vector<int>> fares) {
    // 2차원 distance table
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, INF));
    
    // 자기가 자기한테 가는 것은 0으로 설정
    for(int i = 1; i <= n; i++) {
        dist[i][i] = 0;
	}
    for (int i = 0; i < fares.size(); i++) {
        int u = fares[i][0];
        int v = fares[i][1];
        int w = fares[i][2];

        dist[u][v] = w;
        dist[v][u] = w;
    }
     // k가 무조건 바깥에 있어야 한다. i,j는 상관없다
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
    long long answer = INF;
    for (int i = 1; i <= n; i++) {
		long long cost = dist[s][i] + dist[i][a] + dist[i][b];
        answer = min(answer, cost);
    }

    return answer;
}