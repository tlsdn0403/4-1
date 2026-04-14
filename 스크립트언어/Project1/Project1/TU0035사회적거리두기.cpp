#include <iostream>
#include <vector>
#include <string>
using namespace std;

int n;
string s;
vector<int> ones;

bool can(int D) {
    // 기존 학생들끼리 이미 D보다 가까우면 불가능
    for (int i = 1; i < (int)ones.size(); i++) {
        if (ones[i] - ones[i - 1] < D) return false;
    }

    int cnt = 0;
    int p = 0;                  // ones 포인터
    int last = -1000000000;     // 왼쪽 마지막 학생 위치(기존 or 신규)

    for (int i = 0; i < n; i++) {
        // 현재 칸이 기존 학생이면 그냥 반영
        if (s[i] == '1') {
            last = i;
            p++;
            continue;
        }

        // 오른쪽에서 가장 가까운 기존 학생 위치
        int rightOne = (p < (int)ones.size() ? ones[p] : 1000000000);

        // 새 학생 배치 가능?
        if (i - last >= D && rightOne - i >= D) {
            cnt++;
            last = i;   // 새 학생도 이제 점유 상태
            if (cnt >= 2) return true;
        }
    }

    return false;
}

int main() {
    cin >> n >> s;

    for (int i = 0; i < n; i++) {
        if (s[i] == '1') ones.push_back(i);
    }

    int lo = 1, hi = n - 1;
    int ans = 0;

    while (lo <= hi) {
        // 가운데
        int mid = (lo + hi) / 2;
        if (can(mid)) {
            ans = mid;
            lo = mid + 1;
        }
        else {
            hi = mid - 1;
        }
    }

    cout << ans << '\n';
    return 0;
}