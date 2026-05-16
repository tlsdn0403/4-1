#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

long long n, m;
// desk 의 포지션을 일일히 받으면 안됨
vector<pair<long long, long long>> desk;

bool check(long long distance)
{

    long long count = 0;
    // 전 학생의 포지션
    long long lastPos = -1;
    bool hasStudent = false;

    for (auto [left, right] : desk)
    {
        // 처음 앉을 수 있는 위치
        long long pos;

        if (!hasStudent)
        {
            pos = left;
        }
        else
        {
            // 맨 왼쪽과 직전 위치 + 거리중 큰 값.
            pos = max(left, lastPos + distance);
        }
        // 범위 밖임
        if (pos > right)
        {
            continue;
        }
        // 책상에 앉을 수 있는 학생의 개수
        long long sitStudent = (right - pos) / distance + 1;

        count += sitStudent;

        // 가장 오른쪽에 앉은 학생 = 가장 왼쪽에 앉은 학생 + (거리 * (앉은 학생 수 -1))
        lastPos = pos + (sitStudent - 1) * distance;
        hasStudent = true;

        // 학생수보다 많이 앉을 수 있으면 가능한거다
        if (count >= n)
        {
            return true;
        }
    }

    return false;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    desk.resize(m);

    for (int i = 0; i < m; ++i)
    {
        long long first, last;
        cin >> first >> last;

        desk[i] = { first, last };
    }

    sort(desk.begin(), desk.end());

    long long start = 1;
    long long end = desk.back().second - desk.front().first;
    long long answer = 0;

    while (start <= end)
    {
        long long mid = (start + end) / 2;

        if (check(mid))
        {
            answer = mid;
            start = mid + 1;
        }
        else
        {
            end = mid - 1;
        }
    }

    cout << answer;

    return 0;
}