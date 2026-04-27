#include <vector>
#include <algorithm>
using namespace std;

struct Stage {
    int stage;
    int fail;
    double rate;
};

vector<int> solution(int N, vector<int> stages) {
    vector<int> failCount(N + 2, 0);

    for (int x : stages) {
        if (x <= N) failCount[x]++;
    }

    vector<Stage> s;
    int reached = stages.size();

    for (int i = 1; i <= N; i++) {
        double rate = 0.0;
        if (reached > 0) {
            rate = (double)failCount[i] / reached;
        }

        s.push_back({ i, failCount[i], rate });
        // 지금 스테이지 실패한 사람들 뺴
        reached -= failCount[i];
    }

    sort(s.begin(), s.end(), [](const Stage& a, const Stage& b) {
        if (a.rate == b.rate) return a.stage < b.stage;
        return a.rate > b.rate;
        });

    vector<int> answer;
    for (auto& x : s) {
        answer.push_back(x.stage);
    }

    return answer;
}