#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long N, M; // N: 강의 수, M: 블루레이 수
vector<long long> lesson;

bool check(long long size) {
    int count = 1;
    long long sum = 0;

    for (long long x : lesson) {
		// size 크기의 블루레이에 강의를 담을 수 있는지 확인
        if (sum + x <= size) {
            sum += x;
        }
        // 담을 수 없다면 새로운 블루레이 추가
        else {
            count++;
            sum = x;
        }
    }

    return count <= M;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    lesson.resize(N);

    long long start = 0;
    long long end = 0;

    for (int i = 0; i < N; i++) {
        cin >> lesson[i];
        start = max(start, lesson[i]);
        end += lesson[i];
    }

    long long answer = end;

    while (start <= end) {
        long long mid = (start + end) / 2;

		// mid 크기의 블루레이로 강의를 나눌 수 있는지 확인
        if (check(mid)) {
            answer = mid;
            end = mid - 1;
        }
        else {
            start = mid + 1;
        }
    }

    cout << answer << '\n';

    return 0;
}
