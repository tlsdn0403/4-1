#include <string>
#include <vector>

using namespace std;

string getGene(int n, int p) {
    // 1세대는 무조건 Rr
    if (n == 1) {
        return "Rr";
    }

    // 부모 개체 번호
    int parentP = (p - 1) / 4 + 1;

    // 현재 개체가 부모의 몇 번째 자식인지
    int childIndex = (p - 1) % 4;

    string parent = getGene(n - 1, parentP);

    // 부모가 순종이면 자식도 전부 같은 순종
    if (parent == "RR") return "RR";
    if (parent == "rr") return "rr";

    // 부모가 Rr이면 RR, Rr, Rr, rr 순서
    if (childIndex == 0) return "RR";
    if (childIndex == 1) return "Rr";
    if (childIndex == 2) return "Rr";
    return "rr";
}

vector<string> solution(vector<vector<int>> queries) {
    vector<string> answer;

    for (auto q : queries) {
        int n = q[0];
        int p = q[1];

        answer.push_back(getGene(n, p));
    }

    return answer;
}