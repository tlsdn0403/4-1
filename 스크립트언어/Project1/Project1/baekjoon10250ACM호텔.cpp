#include<iostream>

using namespace std;

//손님들은 호텔 정문으로부터 걸어서 가장 짧은 거리에 있는 방을 선호한다. 
// 호텔 정문으로부터 걷는 거리가 가장 짧도록 방을 배정하는 프로그램을 작성하고자 한다.
//손님은 엘리베이터를 타고 이동하는 거리는 신경 쓰지 않는다.
// 다만 걷는 거리가 같을 때에는 아래층의 방을 더 선호한다.예를 들면 102 호 방보다는 301 호 방을 더 선호한다.
//초기에 모든 방이 비어있다고 가정하에 이 정책에 따라 N 번째로 도착한 손님에게 배정될 방 번호를 계산하는 프로그램이다.


int main() {
	int T,H, W, N;
	cin >> T;

	for (int i = 0; i < T; ++i) {
		cin >> H >> W >> N;

		int H_count = 0;
		int W_count = 0;
		for (int j = 0; j < N; ++j) {
			if (j % H == 0) {
				W_count++;

				H_count = 0;
			}
			H_count++;
		}
		int answer = H_count * 100 + W_count;
		cout << answer << '\n';
	}
}