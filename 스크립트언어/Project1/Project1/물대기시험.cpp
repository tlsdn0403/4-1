#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int n;
struct Edge {
    int u, v;
    long long cost;
};

vector<int> parent;

int findParent(int x) {
    if (x == parent[x]) return x;
    // 찾아서 얻은 루트노드를 현재 부모테이블 값으로 갱신하다. 각각의 루트노드가 들어가도록 갱신
    return parent[x] = findParent(parent[x]);
}

void unionParent(int a, int b) {
    a = findParent(a);
    b = findParent(b);

    if (a < b) parent[b] = a;
    else parent[a] = b;
}

int main() {


    // 논의 개수
    cin >> n;

    vector<Edge> edges;

    // 논의 비용
    for (int i = 1; i <= n; i++) {
        long long cost;
        cin >> cost;
        edges.push_back({ 0, i, cost });
    }

    // 논들 사이의 물을 길어오는 비용
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            long long cost;
            cin >> cost;
            // 중복 간선을 방지
            if (i < j) {
                edges.push_back({ i, j, cost });
            }
        }
    }

    sort(edges.begin(), edges.end() , []( Edge a,  Edge b) {
        return a.cost < b.cost;
    });

    // 부모 배열 초기화
    parent.resize(n + 1);
    for (int i = 0; i <= n; i++) parent[i] = i;

    long long answer = 0;
    int count = 0;

    for (const Edge& edge : edges) {
        // 같은 부모가 없다면 연결
        if (findParent(edge.u) != findParent(edge.v)) {
            unionParent(edge.u, edge.v);
            answer += edge.cost;
            count++;
            //  n개의 간선이 연결되면 끝 
            if (count == n) break;
        }
    }

    cout << answer << "\n";

    return 0;
}
