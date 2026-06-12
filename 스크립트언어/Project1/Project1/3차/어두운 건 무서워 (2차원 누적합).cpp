/*
 호근이는 어두운 것을 싫어한다. 사진을 보여주려는데, 특정 직사각형 영역의 평균 밝기가 일정 수준 이상이어야만 본다고 한다. 
 R x C 크기의 사진의 각 픽셀 밝기가 주어진다. 
 Q개의 쿼리가 주어질 때, 각 쿼리에서 지정한 좌표 (r1, c1)부터 (r2, c2)까지 직사각형 부분의 평균 밝기를 구하여라. (평균은 정수 부분만 취한다.)

	input : 
		5 6 1
		4 1 3 4 9 5
		5 4 2 8 3 9
		5 9 7 2 1 4
		3 8 4 1 6 4
		2 5 8 6 7 5
		2 2 4 5
	output : 
		4
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int R, C, Q;
	cin >> R >> C >> Q;

	// 1. 2차원 누적합 배열 S 세팅 (1-based index 사용 필수)
	vector<vector<int>> S(R + 1, vector<int>(C + 1, 0));

	for (int i = 1; i <= R; ++i) {
		for (int j = 1; j <= C; ++j) {
			int value;
			cin >> value;
			// [핵심] 2차원 누적합 공식: (위쪽 영역) + (왼쪽 영역) - (중복 영역) + (현재 값)
			S[i][j] = S[i - 1][j] + S[i][j - 1] - S[i - 1][j - 1] + value;
		}
	}

	// 2. 쿼리 처리
	for (int i = 0; i < Q; ++i) {
		int r1, c1, r2, c2;
		cin >> r1 >> c1 >> r2 >> c2;

		// [핵심] 원하는 구간의 합 구하기: 전체 - 위쪽 잘라내기 - 왼쪽 잘라내기 + 중복해서 뺀 부분 복구
		int total_sum = S[r2][c2] - S[r1 - 1][c2] - S[r2][c1 - 1] + S[r1 - 1][c1 - 1];

		// 칸의 개수 구하기
		int count = (r2 - r1 + 1) * (c2 - c1 + 1);

		// 평균 밝기 (정수 버림)
		cout << total_sum / count << '\n';
	}

	return 0;
}