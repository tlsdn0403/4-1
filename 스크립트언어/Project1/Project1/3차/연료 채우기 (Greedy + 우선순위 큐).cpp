/*
 성경이가 트럭을 몰고 목적지까지 가려고 한다. 목적지까지 가는 길에 N개의 주유소가 있다. 
 각 주유소의 위치(거리)와 거기서 채울 수 있는 연료의 양이 주어진다.
 성경이의 트럭은 1km를 갈 때 연료 1을 쓴다. 
 목적지까지 가기 위해 멈춰야 하는 주유소의 최소 횟수를 구하시오. (도착할 수 없다면 -1 출력)

	input : 
		4
		4 4
		5 2
		11 5
		15 10
		25 10

	output :
		3
*/


#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N;
	cin >> N;

	// 주유소 정보: {거리, 연료량}
	vector<pair<int, int>> stations(N);
	for (int i = 0; i < N; ++i) {
		cin >> stations[i].first >> stations[i].second;
	}

	int L, P;
	cin >> L >> P;

	// 1. 거리가 가까운 주유소부터 접근하기 위해 오름차순 정렬
	sort(stations.begin(), stations.end());

	// 2. 우선순위 큐 (가장 많은 연료를 우선적으로 뽑기 위해 Max-Heap 사용)
	priority_queue<int> pq;

	int ans = 0; // 주유소 들른 횟수
	int idx = 0; // 현재 확인 중인 주유소 인덱스

	while (P < L) {
		// 현재 연료(P)로 갈 수 있는 모든 주유소의 연료량을 큐에 넣음
		while (idx < N && stations[idx].first <= P) {
			pq.push(stations[idx].second);
			idx++;
		}

		// 연료가 부족한데 갈 수 있는 주유소도 없다면 도착 불가
		if (pq.empty()) {
			cout << -1 << '\n';
			return 0;
		}

		// 가장 연료를 많이 주는 주유소에서 주유
		P += pq.top();
		pq.pop();
		ans++;
	}

	cout << ans << '\n';
	return 0;
}