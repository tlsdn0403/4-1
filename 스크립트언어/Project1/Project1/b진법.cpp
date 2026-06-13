#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int b, N, M;

int main() {
    cin >> b >> N >> M;

    vector<int> vN(N);
    vector<int> vM(M);

    for (int i = 0; i < N; ++i) {
        cin >> vN[i];
    }

    for (int i = 0; i < M; ++i) {
        cin >> vM[i];
    }

    vector<int> result(N + M, 0);

    // 각 자리 곱셈
    for (int i = N - 1; i >= 0; --i) {
        for (int j = M - 1; j >= 0; --j) {
            result[i + j + 1] += vN[i] * vM[j];
        }
    }

    // 자리올림 처리
    for (int i = N + M - 1; i > 0; --i) {
        result[i - 1] += result[i] / b;
        result[i] %= b;
    }

    // 앞쪽 0 제거
    int start = 0;
    while (start < result.size() - 1 && result[start] == 0) {
        start++;
    }

    cout << result.size() - start << '\n';

    for (int i = start; i < result.size(); ++i) {
        cout << result[i] << ' ';
    }

    return 0;
}