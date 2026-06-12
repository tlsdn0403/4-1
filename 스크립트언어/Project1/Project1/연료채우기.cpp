#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

// 주유소의 개수 , 성경이 위치까지 거리 , 원래 있던 연료양
long long N , L, P;

int main() {


    // 입력부분

    cin >> N;
	vector<pair<int, int>> stations(N);
    


    for (size_t i = 0; i < N; i++) {
        // 거리 , 채울 수 있는 연료
        cin >> stations[i].first >> stations[i].second;
	}

   
    cin >> L >> P;

    // 주유소 위치 기준 오름차순 정렬
    sort(stations.begin(), stations.end(), [](pair<int , int> pa , pair<int, int> pb) {
        if (pa.first == pb.first) {
            return pa.second < pb.second;
        }
        return pa.first < pb.first;
        });

    priority_queue<int> pq;
   

    int ans = 0; // 주유소 들른 횟수
    int idx = 0; // 현재 확인 중인 주유소 인덱스


    while (P < L) {
        // 현재 연료 갈 수 있는 거 다넣음
        while (idx < N && stations[idx].first <= P) {
            pq.push(stations[idx].second);
            idx++;
        }

        if (pq.empty()) {
            cout << -1 << '\n';
        }

        // 가장 연료를 많이 주는 주유소에서 주유
        P += pq.top();
        pq.pop();
        ans++;
    }

    cout << ans << "\n";

    return 0;
}
