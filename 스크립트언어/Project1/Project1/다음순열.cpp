#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, K;
    cin >> N >> K;

    for (int t = 0; t < K; t++) {
        vector<int> arr(N);

        for (int i = 0; i < N; i++) {
            cin >> arr[i];
        }

        next_permutation(arr.begin(), arr.end());

        for (int i = 0; i < N; i++) {
            cout << arr[i] << ' ';
        }
        cout << '\n';
    }

    return 0;
}