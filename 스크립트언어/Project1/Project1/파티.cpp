#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INF = 1e9;

int N, M, X;

int d[1001];
int backD[1001];

vector<pair<int, int>> graph[1001];
vector<pair<int, int>> BackGraph[1001];

void dijkstra(int start, vector<pair<int, int>> g[], int dist[]) {
    fill(dist, dist + 1001, INF);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start] = 0;

    // {거리, 노드} 로 넣어야함 우선순위큐가 first로 비교
    pq.push({ 0, start });

    while (!pq.empty()) {
        int currentDistance = pq.top().first;
        int current = pq.top().second;
        pq.pop();

        // 이미 더 짧은 거리로 처리된 적이 있으면 무시
        if (dist[current] < currentDistance) {
            continue;
        }

        for (int i = 0; i < g[current].size(); i++) {
            int next = g[current][i].first;
            int nextDistance = g[current][i].second;

            if (dist[next] > currentDistance + nextDistance) {
                dist[next] = currentDistance + nextDistance;
                pq.push({ dist[next], next });
            }
        }
    }
}

int main() {
    cin >> N >> M >> X;

    for (int i = 0; i < M; i++) {
        int a, b, c;
        cin >> a >> b >> c;

        // a -> b
        graph[a].push_back({ b, c });

        // b -> a, 역방향 그래프
        BackGraph[b].push_back({ a, c });
    }

    // X -> i
    dijkstra(X, graph, d);

    // i -> X
    dijkstra(X, BackGraph, backD);

    int maxNum = 0;

    for (int i = 1; i <= N; i++) {
        maxNum = max(maxNum, d[i] + backD[i]);
    }

    cout << maxNum;

    return 0;
}