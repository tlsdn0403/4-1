#include <string>
#include <vector>

using namespace std;

void dp(vector<vector<int>>& triangle, int x, int y) {
    if (x == triangle.size() - 1) {
        return;
    }
    dp(triangle, x + 1, y);
    dp(triangle, x + 1, y + 1);
    triangle[x][y] += max(triangle[x + 1][y], triangle[x + 1][y + 1]);
}

int solution(vector<vector<int>> triangle) {
    int answer = 0;
    return answer;
}