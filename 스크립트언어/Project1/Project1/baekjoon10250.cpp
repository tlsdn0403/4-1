#include<iostream>

using namespace std;

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