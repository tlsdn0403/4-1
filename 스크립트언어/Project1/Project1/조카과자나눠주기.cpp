#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long M, N;
vector<long long> snacks;

bool check(long long length)
{
    long long count = 0;

    for (long long snack : snacks)
    {
        count += snack / length;
    }

    return count >= M;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> M >> N;

    snacks.resize(N);

    for (int i = 0; i < N; ++i)
    {
        cin >> snacks[i];
    }

    long long start = 1;
    long long end = *max_element(snacks.begin(), snacks.end());
    long long answer = 0;

    while (start <= end)
    {
        long long mid = (start + end) / 2;

        //ÂüÀÌ¶ó¸é
        if (check(mid)) {
            answer = max(answer, mid);
            // ¿À¸¥ÂÊ Å½»ö
            start = mid + 1;
        }
        else {
            //¿ÞÂÊ Å½»ö
            end = mid - 1;
        }


    }

    cout << answer;
}