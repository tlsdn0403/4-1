#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long N, M; // N: 날짜 수, M: 최대 인출 횟수
vector<long long> money;

bool check(long long getMoney) {
    long long count = 1;          // 처음에 한 번 인출
    long long moneyHave = getMoney;

    for (long long cost : money) {
        // 현재 가진 돈으로 오늘 지출을 감당할 수 없으면 새로 인출
        if (moneyHave < cost) {
            count++;
            moneyHave = getMoney;
        }

        // 오늘 지출
        moneyHave -= cost;
    }

    // M번 이하로 인출 가능하면 true
    return count <= M;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M;

    money.resize(N);

    long long start = 0;
    long long end = 0;

    for (int i = 0; i < N; i++) {
        cin >> money[i];
        start = max(start, money[i]); // 최소 인출 금액은 하루 최대 지출 이상
        end += money[i];              // 최대는 전체 지출 합
    }

    long long answer = end;

    while (start <= end) {
        long long mid = (start + end) / 2;

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
