#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

// 닭의 마리수, 소의 마리수
int C, N;

vector<int> chicken;

// 소가 건널 수 있는 시작 시간, 끝 시간
vector<pair<int, int>> cow;

int main() {
    cin >> C >> N;

    for (int i = 0; i < C; i++) {
        int c;
        cin >> c;
        chicken.push_back(c);
    }

    for (int i = 0; i < N; i++) {
        int start, end;
        cin >> start >> end;
        cow.push_back({ start, end });
    }

    // 닭 시간 오름차순 정렬
    sort(chicken.begin(), chicken.end());

    // 소는 시작 시간 기준 오름차순 정렬
    sort(cow.begin(), cow.end());

    // 현재 닭이 도와줄 수 있는 소들의 end 시간을 저장
    priority_queue<int, vector<int>, greater<int>> pq;

    int cowIndex = 0;
    int answer = 0;

    for (int i = 0; i < C; i++) {
        int currentChickenTime = chicken[i];

        // 닭이 소를 옮겨줄 수 있다면 큐에 넣음
        while (cowIndex < N && cow[cowIndex].first <= currentChickenTime) {
            pq.push(cow[cowIndex].second);
            cowIndex++;
        }

        // 이미 현재 닭 시간보다 end가 작으면 도와줄 수 없음
        while (!pq.empty() && pq.top() < currentChickenTime) {
            pq.pop();
        }
        // 도와줄 수 있는 소가 있다면, end가 가장 빠른 소를 도와줌
        if (!pq.empty()) {
            pq.pop();
            answer++;
        }
    }

    cout << answer;

    return 0;
}