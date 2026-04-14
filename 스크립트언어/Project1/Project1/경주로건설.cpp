//설회사의 설계사인 죠르디는 고객사로부터 자동차 경주로 건설에 필요한 견적을 의뢰받았습니다.
//제공된 경주로 설계 도면에 따르면 경주로 부지는 N x N 크기의 정사각형 격자 형태이며 각 격자는 1 x 1 크기입니다.
//설계 도면에는 각 격자의 칸은 0 또는 1 로 채워져 있으며, 0은 칸이 비어 있음을 1은 해당 칸이 벽으로 채워져 있음을 나타냅니다.
//경주로의 출발점은(0, 0) 칸(좌측 상단)이며, 도착점은(N - 1, N - 1) 칸(우측 하단)입니다.죠르디는 출발점인(0, 0) 칸에서 출발한 자동차가 도착점인(N - 1, N - 1) 칸까지 무사히 도달할 수 있게 중간에 끊기지 않도록 경주로를 건설해야 합니다.
//경주로는 상, 하, 좌, 우로 인접한 두 빈 칸을 연결하여 건설할 수 있으며, 벽이 있는 칸에는 경주로를 건설할 수 없습니다.
//이때, 인접한 두 빈 칸을 상하 또는 좌우로 연결한 경주로를 직선 도로 라고 합니다.
//또한 두 직선 도로가 서로 직각으로 만나는 지점을 코너 라고 부릅니다.
//건설 비용을 계산해 보니 직선 도로 하나를 만들 때는 100원이 소요되며, 코너를 하나 만들 때는 500원이 추가로 듭니다.
//죠르디는 견적서 작성을 위해 경주로를 건설하는 데 필요한 최소 비용을 계산해야 합니다.
//
//예를 들어, 아래 그림은 직선 도로 6개와 코너 4개로 구성된 임의의 경주로 예시이며, 건설 비용은 6 x 100 + 4 x 500 = 2600원 입니다.

#include <vector>
#include <queue>
#include <cstdlib>

using namespace std;

struct Car {
    int r, c, dir, cost;
};

int min_cost = 0x7fffffff;
int dir_r[4] = { -1, 0, 1, 0 };
int dir_c[4] = { 0, 1, 0, -1 };

int solution(vector<vector<int>> board) {
    int n = board.size();
    queue<Car> q;
    q.push({ 0, 0, 5, 0 });
    board[0][0] = 1;

    while (!q.empty()) {
        Car car = q.front();
        q.pop();

        int cost = car.cost;

        if (car.r == n - 1 && car.c == n - 1) {
            if (cost < min_cost) min_cost = cost;
            continue;
        }

        for (int i = 0; i < 4; i++) {
            if (abs(i - car.dir) == 2) continue;

            int next_r = car.r + dir_r[i];
            int next_c = car.c + dir_c[i];

            if (next_r >= 0 && next_r < n && next_c >= 0 && next_c < n
                && board[next_r][next_c] != 1) {

                int new_cost = cost;
                if (i == car.dir || (car.r == 0 && car.c == 0)) new_cost += 100;
                else new_cost += 600;

                if (board[next_r][next_c] == 0 || board[next_r][next_c] >= new_cost) {
                    q.push({ next_r, next_c, i, new_cost });
                    board[next_r][next_c] = new_cost;
                }
            }
        }
    }

    return min_cost;
}