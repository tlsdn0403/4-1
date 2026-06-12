/*
 공대방에 걸린 도현이는 겹치는 것을 매우 싫어한다. 
 길이가 N인 100,000 이하의 양의 정수로 이루어진 수열이 주어진다. 
 같은 원소가 K개 이하로 들어있는 최장 연속 부분 수열의 길이를 구하는 프로그램을 작성해보자.

	input : 
		9 2
		3 2 5 5 6 4 4 5 7
	
	output :
		7
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int cnt[100001]; // 각 숫자의 등장 횟수를 기록할 배열

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int N, K;
	cin >> N >> K;

	vector<int> arr(N);
	for (int i = 0; i < N; ++i) cin >> arr[i];

	int start = 0, end = 0;
	int max_len = 0;

	// 투 포인터 탐색 (애벌레 전진)
	while (end < N) {
		// 새로 들어온 숫자가 K개를 초과해버린 경우
		if (cnt[arr[end]] == K) {
			// 조건이 만족될 때까지 꼬리(start)를 자르며 뱉어냄
			cnt[arr[start]]--;
			start++;
		}
		// 아직 여유가 있는 경우 (머리 전진)
		else {
			cnt[arr[end]]++;
			// 현재 유효한 구간의 길이 갱신
			max_len = max(max_len, end - start + 1);
			end++;
		}
	}

	cout << max_len << '\n';
}